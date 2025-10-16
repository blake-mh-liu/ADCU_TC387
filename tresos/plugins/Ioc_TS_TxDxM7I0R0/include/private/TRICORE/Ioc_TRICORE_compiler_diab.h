/* Ioc_TRICORE_compiler_diab.h
 *
 * This file defines macros to permit the inter os-application communicator to be compiled
 * with the Diab compiler
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef directives are not permitted.
 *
 * Reason:
 *  This is a toolchain-dependent file and it uses toolchain-specific extensions (e.g. inline assembler).
 *  A static code analysis tool, that operates only on standard C, would not be able to parse this
 *  and report false positives and/or halt. This is avoided by running static code checkers with the EB_STATIC_CHECK
 *  macro defined and using conditional compilation to prevent the checker from parsing toolchain-dependent code.
*/

#ifndef IOC_TRICORE_COMPILER_DIAB_H
#define IOC_TRICORE_COMPILER_DIAB_H

/* Function qualifier and attribute for inline functions
*/
/* Deviation DCG-1 <+1> */
#ifdef EB_STATIC_CHECK
#define IOC_QUAL_INLINE	static
#define IOC_ATTR_INLINE

extern ioc_uint32_t IOC_AtomicSwap(volatile ioc_uint32_t *, ioc_uint32_t);
extern void IOC_DSYNC(void);

#else /* here comes the real stuff */
#define IOC_QUAL_INLINE	static __inline__
#define IOC_ATTR_INLINE	__attribute__((always_inline))

#ifndef IOC_ASM
/* IOC_AtomicSwap() atomically fetches the value stored at memory location 'addr'
 * and replaces its value by 'val'.
*/
__asm volatile ioc_uint32_t IOC_AtomicSwap(volatile ioc_uint32_t *addr, ioc_uint32_t val)
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

/* Just a DSYNC. */
__asm volatile void IOC_DSYNC(void)
{
!
.set noreorder
	dsync
}
#endif /* IOC_ASM */

#endif /* real stuff */

#endif /* IOC_TRICORE_COMPILER_DIAB_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
