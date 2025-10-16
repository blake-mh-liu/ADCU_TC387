/* Ioc_TRICORE_compiler_gnu.h
 *
 * This file defines macros to permit the inter os-application communicator to be compiled
 * with the GNU C compiler
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: D4.3 (required)
 *  Assembly language shall be encapsulated and isolated.
 *
 * Reason:
 *  The inline function serves exactly this purpose: it encapsulates and
 *  isolates the inline assembly statement.
 */

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_020]
 *  Permitted test for macro definitions
 *
 * Reason:
 *  We must use #ifndef here, because the macro EB_STATIC_CHECK is provided by
 *  external tooling outside the control of the IOC.
 *  EB_STATIC_CHECK is used to hide toolchain-specific extensions,
 *  which would impair the MISRA-C analysis.
 *
 * DCG-2) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef and the defined preprocessor operator shall not be used.
 *
 * Reason:
 *  We must use #ifdef here, because the macro EB_STATIC_CHECK is provided by
 *  external tooling outside the control of the IOC.
 *  EB_STATIC_CHECK is used to hide toolchain-specific extensions
 *  which would impair the MISRA-C analysis.
*/

#ifndef IOC_TRICORE_COMPILER_GNU_H
#define IOC_TRICORE_COMPILER_GNU_H

/* Function qualifier and attribute for inline functions
*/
#define IOC_QUAL_INLINE static __inline__

/* Deviation DCG-2 <+1> */
#ifdef EB_STATIC_CHECK
#define IOC_ATTR_INLINE
extern void IOC_DSYNC(void);
#else
#define IOC_ATTR_INLINE	__attribute__((always_inline))
#endif

#ifndef IOC_ASM
/* IOC_AtomicSwap() atomically fetches the value stored at memory location 'addr'
 * and replaces its value by 'val'.
*/
IOC_QUAL_INLINE ioc_uint32_t IOC_AtomicSwap(volatile ioc_uint32_t *, ioc_uint32_t) IOC_ATTR_INLINE;
IOC_QUAL_INLINE ioc_uint32_t IOC_AtomicSwap(volatile ioc_uint32_t *addr, ioc_uint32_t val)
{
	/* Deviation MISRAC2012-1 <+1> */
	__asm__ volatile ("swap.w [%1]0, %0" : "=d" (val) : "a" (addr), "0" (val));
	return val;
}

/* Deviation DCG-1 <+1> */
#ifndef EB_STATIC_CHECK
IOC_QUAL_INLINE void IOC_DSYNC(void) IOC_ATTR_INLINE;
IOC_QUAL_INLINE void IOC_DSYNC(void)
{
	__asm__ volatile (" dsync" ::: "memory");
	return ;
}
#endif /* EB_STATIC_CHECK */
#endif /* IOC_ASM */

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
