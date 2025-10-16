/* Ioc_TRICORE_compiler_tasking.h
 *
 * This file defines macros to permit the inter os-application communicator to be compiled
 * with the Tasking compiler
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.3 (Mandatory)
 *  A function shall not be declared implicitly
 *
 * Reason:
 *  __swap is an intrinsic function of the tasking compiler. We could use an
 *  inline assembler statement instead, but this would also cause a MISRA violation.
 *  This is an inline function. It does not occupy memory, when it is not used.
 *  This is not a portability issue, since this is a tool-dependent header.
 *
 * MISRAC2012-2) Deviated Rule: 11.8 (required)
 *  A cast shall not remove any const or volatile qualification
 *  from the type pointed to by a pointer.
 *
 * Reason:
 *  Data addressed by an atomic swap operation is clearly volatile, so we can't remove
 *  the volatile qualification from the parameter list. Unfortunately tasking's intrinsic
 *  function __swap doesn't have a volatile qualification for this parameter, so we cast
 *  it away. This cast has no effect on the resulting code: A SWAP instruction will be emitted.
 *
 * MISRAC2012-3) Deviated Rule: 8.5 (required)
 *  An external object or function shall be declared once in one and only one file.
 *
 * Reason:
 *  False positive. This is not a declaration. The function __swap() is an intrinsic
 *  function of the compiler and hence, implicitly declared.
 *
 * MISRAC2012-4) Deviated Rule: 11.3 (required)
 *  A cast shall not be performed between a pointer to object type and a pointer
 *  to a different object type.
 *
 * Reason:
 *  The type conversions are necessary to adapt to the declaration of the intrinsic
 *  functin __swap().
*/

/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.31
 *  Declare identifiers before using them
 *
 * Reason:
 *  __swap is a intrinsic function of the tasking compiler. We could use an
 *  inline assembler statement instead, but this would also cause a MISRA violation.
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

#ifndef IOC_TRICORE_COMPILER_TASKING_H
#define IOC_TRICORE_COMPILER_TASKING_H

/* Function qualifier and attribute for inline functions
*/
/* Deviation DCG-2 <+1> */
#ifdef EB_STATIC_CHECK
#define IOC_QUAL_INLINE	static
/* Some MISRA checkers are not able to parse function prototypes having an attribute.
 * Therefore we hide this attribute from the MISRA checker (so they don't crash).
 * Using EB_STATIC_CHECK is allowed in compiler headers only,
 * because MISRA checkers are some kind of compilers.
*/
#define IOC_ATTR_INLINE
extern void IOC_DSYNC(void);
#else
#define IOC_QUAL_INLINE	static inline
#define IOC_ATTR_INLINE	__attribute__((always_inline))
#endif

#ifndef IOC_ASM
/* IOC_AtomicSwap() atomically fetches the value stored at memory location 'addr'
 * and replaces its value by 'val'.
*/
IOC_QUAL_INLINE ioc_uint32_t IOC_AtomicSwap(volatile ioc_uint32_t *, ioc_uint32_t) IOC_ATTR_INLINE;
IOC_QUAL_INLINE ioc_uint32_t IOC_AtomicSwap(volatile ioc_uint32_t *addr, ioc_uint32_t val)
{
	/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1>, MISRAC2012-3 <+1>, MISRAC2012-4 <+1>, CERTC-1 <+1> */
	return (ioc_uint32_t) __swap((ioc_unsigned_t*)addr, (ioc_unsigned_t)val);
}
/* Deviation DCG-1 <+1> */
#ifndef EB_STATIC_CHECK
IOC_QUAL_INLINE void IOC_DSYNC(void) IOC_ATTR_INLINE;
IOC_QUAL_INLINE void IOC_DSYNC(void)
{
	/* dsync */
	__asm(" dsync" ::: "memory");
	return ;
}
#endif /* EB_STATIC_CHECK */
#endif /* IOC_ASM */

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
