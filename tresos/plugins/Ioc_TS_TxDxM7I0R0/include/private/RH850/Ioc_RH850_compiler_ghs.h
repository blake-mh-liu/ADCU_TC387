/* Ioc_RH850_compiler_ghs.h
 *
 * This file defines macros to permit the inter os-application communicator to be compiled
 * with the GHS compiler
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

#ifndef IOC_RH850_COMPILER_GHS_H
#define IOC_RH850_COMPILER_GHS_H

/* Function qualifier and attribute for inline functions
*/
/* Deviation DCG-1 <+1> */
#ifdef EB_STATIC_CHECK
#define IOC_QUAL_INLINE	static
#define IOC_ATTR_INLINE

extern void IOC_SYNCM(void);

#else /* here comes the real stuff */

#ifndef IOC_ASM

/* Memory barrier. */
__asm void IOC_SYNCM(void)
{
%
	syncm
}
#endif /* IOC_ASM */

#endif /* real stuff */

#endif /* IOC_RH850_COMPILER_GHS_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
