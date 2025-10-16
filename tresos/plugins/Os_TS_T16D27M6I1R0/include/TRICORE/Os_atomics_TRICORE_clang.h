/* Os_atomics_TRICORE_clang.h
 *
 * This file contains the implementation of the atomic functions
 * for TRICORE and the clang toolchain.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TRICORE_CLANG_H
#define OS_ATOMICS_TRICORE_CLANG_H 1

#include <Os_types.h>
#include <TRICORE/Os_atomics_TRICORE_clang_impl.h>

/* Note that functions having an OS_ImplAtomic prefix are not part of the official API.
*/

/* CmpSwapW(object, newValue, expected):
 *  tmp = *object,
 *  *object = (tmp == expected)? newVal : tmp;
 *  return tmp;
*/
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_ImplAtomicCmpSwapW(
	os_atomic_t volatile *object,
	os_atomic_value_t newValue,
	os_atomic_value_t expected)
{
	/* regValue and regExpected have to be passed as asm input, to make sure they live in their respective registers.
	 * Note that %d4 is %e4[31:0] and %d5 is %e4[63:32].
	*/
	register os_uint32_t regValue    __asm__ ("%d4");
	register os_uint32_t regExpected __asm__ ("%d5");
	regValue = newValue;
	regExpected = expected;
	__asm__ __volatile__ (
		"cmpswap.w [%0]0, %%e4\n"
		: "=a"(object), "=d" (regValue)                     /*output*/
		: "0" (object), "d" (regValue), "d" (regExpected)   /*input*/
		: "memory"                                          /*clobber*/
	);

	return regValue;
}

/* SwapMskW(object, value, mask):
 *  tmp = *object;
 *  *object = (tmp & ~mask) | (value & mask);
 *  return tmp;
*/
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_ImplAtomicSwapMskW(
	os_atomic_t volatile *object,
	os_atomic_value_t value,
	os_atomic_value_t mask)
{
	/* regValue and regMask have to be passed as asm input, to make sure they live in their respective registers.
	 * Note that %d4 is %e4[31:0] and %d5 is %e4[63:32].
	*/
	register os_uint32_t regValue __asm__ ("%d4");
	register os_uint32_t regMask  __asm__ ("%d5");
	regValue = value;
	regMask = mask;
	__asm__ __volatile__ (
		"swapmsk.w [%0]0, %%e4\n"
		: "=a"(object), "=d" (regValue)                 /*output*/
		: "0" (object), "d" (regMask), "d" (regValue)   /*input*/
		: "memory"                                      /*clobber*/
	);

	return regValue;
}

/* LdMdSt(object, value, mask):
 *  *object = (*object & ~mask) | (value & mask);
*/
static OS_TOOL_INLINE_KEYWORD void OS_ImplAtomicLdMdSt(
	os_atomic_t volatile *object,
	os_atomic_value_t value,
	os_atomic_value_t mask)
{
	/* regValue and regMask have to be passed as asm input, to make sure they live in their respective registers.
	 * Note that %d4 is %e4[31:0] and %d5 is %e4[63:32].
	*/
	register os_uint32_t regValue __asm__ ("%d4");
	register os_uint32_t regMask  __asm__ ("%d5");
	regValue = value;
	regMask = mask;
	__asm__ __volatile__ (
		"ldmst [%0]0, %%e4\n"
		: "=a"(object)                                  /*output*/
		: "0" (object), "d" (regMask), "d" (regValue)   /*input*/
		: "memory"                                      /*clobber*/
	);
}

#endif /* OS_ATOMICS_TRICORE_CLANG_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

