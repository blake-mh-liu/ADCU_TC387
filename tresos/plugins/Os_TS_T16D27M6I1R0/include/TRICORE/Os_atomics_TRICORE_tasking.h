/* Os_atomics_TRICORE_tasking.h
 *
 * This file contains implementations details of the atomic functions for the
 * Tasking toolchain.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TRICORE_TASKING_H
#define OS_ATOMICS_TRICORE_TASKING_H 1

#include <Os_types.h>
#include <TRICORE/Os_atomics_TRICORE_gnu_impl.h>

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
	/* TASKING offers the following intrinsic at least in 4.2r2 and 6.0r1:
	 * unsigned int __cmpswapw(unsigned int * memory, unsigned int value, unsigned int compare).
	*/
	return (os_atomic_value_t) __cmpswapw((unsigned int *) object, newValue, expected);
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

	/* TASKING offers the following intrinsic at least in 4.2r2 and 6.0r1:
	 * unsigned int __swapmskw(unsigned int * memory, unsigned int value, unsigned int mask).
	*/
	return (os_atomic_value_t) __swapmskw((unsigned int *) object, value, mask);
}

/* LdMdSt(object, value, mask):
 *  *object = (*object & ~mask) | (value & mask);
*/
static OS_TOOL_INLINE_KEYWORD void OS_ImplAtomicLdMdSt(
	os_atomic_t volatile *object,
	os_atomic_value_t value,
	os_atomic_value_t mask)
{
	/* TASKING offers the following intrinsic at least in 4.2r2 and 6.0r1:
	 * void __ldmst(unsigned int * address, unsigned int mask, unsigned int value).
	*/
	__ldmst((unsigned int *) object, mask, value);
}

#endif /* OS_ATOMICS_TRICORE_TASKING_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
