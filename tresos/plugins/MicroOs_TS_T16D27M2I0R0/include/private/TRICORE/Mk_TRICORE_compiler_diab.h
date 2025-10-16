/* Mk_TRICORE_compiler_diab.h
 *
 * This file defines macros to permit the microkernel to be compiled with the WindRiver compiler (diab).
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef directives are not permitted!
 *
 * Reason:
 *  We must use #ifndef here, because the macro EB_STATIC_CHECK is provided by
 *  external tooling outside the control of the microkernel build.
 *  EB_STATIC_CHECK is used, to hide tool specific extensions,
 *  which would otherwise break the MISRA checker run and to provide replacements for them,
 *  which should resemble the actual behavior as good as possible.
*/

#ifndef MK_TRICORE_COMPILER_DIAB_H
#define MK_TRICORE_COMPILER_DIAB_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <public/Mk_public_types.h>


/* Hide all the assembly macros from static checkers.
*/
/* Deviation DCG-1 <+1> */
#ifdef EB_STATIC_CHECK

#define MK_QUAL_INLINE				static
#define MK_ATTR_INLINE
#define MK_DSYNC()					do { } while (0)
#define MK_ISYNC()					do { } while (0)
#define MK_MFCR(csfrid)				((mk_uint32_t)0u)
#define MK_MTCR(csfrid, val)		do { } while (0)
#define MK_MTA9(val)				do { } while (0)
#define MK_MFA9()					MK_coreTable[0]
extern void MK_CompilerMemBarrier(const volatile void *);

MK_QUAL_INLINE mk_uint32_t MK_AtomicSwap(volatile mk_uint32_t *addr, mk_uint32_t val)
{
	mk_uint32_t const old = *addr;
	*addr = val;
	return old;
}

#else /* !EB_STATIC_CHECK */

/* Function qualifier and attribute for inline functions:
*/
#define MK_QUAL_INLINE	static __inline__
#define MK_ATTR_INLINE	__attribute__((always_inline))

#ifndef MK_ASM

#include <diab/asm.h>

__asm volatile void MK_DSYNC(void)
{
!
	dsync
}

__asm volatile void MK_ISYNC(void)
{
!
	isync
}

/* MK_MFCR/MK_MTCR reads/writes the content of a core special function register.
*/
#define MK_MFCR(csfr)		_mfcr(csfr)
#define MK_MTCR(csfr, val)	do {		\
		_mtcr((csfr),(val));			\
		MK_ISYNC();						\
	} while(0)

/* MK_MTA9() writes an address to register A9.
*/
__asm volatile void MK_MTA9(void* val)
{
%reg val
! "%a9"
	mov.aa %a9, val
}

/* MK_MFA9() yields the address stored in register A9.
*/
__asm volatile void *MK_MFA9(void)
{
! "%a2"
	mov.aa %a2, %a9
}

/* MK_CompilerMemBarrier() will make the compiler believe p is used here.
 * Since diab treats embedded assembler as blackbox,
 * it doesn't know whether we read or write
 * or which kind of addressing we use.
*/
#define MK_CompilerMemBarrier(p) MK_CompilerMemBarrierAsm()
__asm volatile void MK_CompilerMemBarrierAsm(void)
{
!
	nop
}

/* MK_AtomicSwap() atomically fetches the value stored at memory location 'addr'
 * and replaces its value by 'val'.
*/
__asm volatile mk_uint32_t MK_AtomicSwap(volatile mk_uint32_t *addr, mk_uint32_t val)
{
%reg addr,val
! "%d2"
	mov		%d2, val
	swap.w [addr]0, %d2
%reg addr; con val
! "%d2"
	mov		%d2, val
	swap.w	[addr]0, %d2
}

#define MK_TricoreAtomicModifyFlag(addr, mask, value) MK_TricoreAtomicModifyFlagImpl((addr), (value), (mask))

/* From the WindRiver TC manual:
 * Arguments to a macro are assigned to registers following the usual calling conventions.
 * For example, four int arguments will use registers %d4, %d5, %d6, and %d7, or in non-scratch registers.
 * Hence we have to move the mask/value to d4/d5 first for the operation, but know that this may
 * be unneeded but also not destroy anything.
*/
__asm volatile void MK_TricoreAtomicModifyFlagImpl(volatile void *address, mk_uint32_t value, mk_uint32_t mask)
{
%reg address, value, mask;
! "%d4", "%d5"
	mov		%d4, value
	mov		%d5, mask
	ldmst	[address]0, %e4
}

#define MK_TricoreAtomicAndNot(address, mask) MK_TricoreAtomicModifyFlag((address), (mask), 0u)

/* This macro opens a new block and a local variable MK_TricoreAtomicOrValue to avoid repetition of
 * side-effects related to parameter value. For example, if it's called like "MK_TricoreAtomicOr(adr, val++)"
 * the post-increment of 'val' shall happen only once.
*/
#define MK_TricoreAtomicOr(address, value) \
	do {\
		mk_uint32_t MK_TricoreAtomicOrValue;\
		MK_TricoreAtomicOrValue = (mk_uint32_t)(value);\
		MK_TricoreAtomicModifyFlag((address), MK_TricoreAtomicOrValue, MK_TricoreAtomicOrValue);\
	} while(0)

#endif /* !MK_ASM */

#endif /* EB_STATIC_CHECK */

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
