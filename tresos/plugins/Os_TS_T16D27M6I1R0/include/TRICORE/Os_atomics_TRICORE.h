/* Os_atomics_TRICORE.h
 *
 * This file redirects to more specific files depending on the selected toolchain.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TRICORE_H
#define OS_ATOMICS_TRICORE_H 1

/* General comment for the #includ'ed files below.
 *
 * The dsync instruction heads the inline assembly language snippets in the files
 * included below to ensure that all write operations are globally visible.
 * Even though, this may not be required by a certain derivate, it doesn't
 * affect the functional behavior.
 *
 * Bibliography
 * [EABI] Infineon: "Embedded Applications Binary Interface (EABI) V1.3x and
 *     V1.6x TriCore™ Architectures", v3.0, 2016-04
 */

#include <Os_defs.h>
#include <TRICORE/Os_TRICORE_cpu.h>
#include <Os_tool.h>

#if (OS_TRICOREARCH != OS_TRICOREARCH_16EP \
		&& OS_TRICOREARCH != OS_TRICOREARCH_162 \
		&& OS_TRICOREARCH != OS_TRICOREARCH_18)
#error "The atomic functions are not supported on this TriCore architecture yet"
#endif

#include <TRICORE/Os_atomics_TRICORE_common.h>

#if (OS_TOOL == OS_gnu)
#include <TRICORE/Os_atomics_TRICORE_gnu.h>
#elif (OS_TOOL == OS_clang)
#include <TRICORE/Os_atomics_TRICORE_clang.h>
#elif (OS_TOOL == OS_tasking)
#include <TRICORE/Os_atomics_TRICORE_tasking.h>
#elif (OS_TOOL == OS_diab)
#include <TRICORE/Os_atomics_TRICORE_diab.h>
#else
#error "The atomic functions are not supported for the selected toolchain."
#endif


/* !LINKSTO Kernel.Atomics.Init, 1
 */
static OS_TOOL_INLINE_KEYWORD void OS_AtomicInit(
	os_atomic_t volatile *object,
	os_atomic_value_t initValue)
{
	*object = initValue;
}

/* !LINKSTO Kernel.Atomics.LoadStore, 1
 */
static OS_TOOL_INLINE_KEYWORD void OS_AtomicStore(
	os_atomic_t volatile *object,
	os_atomic_value_t newValue)
{
	OS_AtomicThreadFence();
	*object = newValue;
	OS_AtomicThreadFence();
}

/* !LINKSTO Kernel.Atomics.LoadStore, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicLoad(
	os_atomic_t const volatile *object)
{
	os_atomic_value_t value;

	OS_AtomicThreadFence();
	value = *object;
	OS_AtomicThreadFence();

	return value;
}

/* !LINKSTO Kernel.Atomics.CompareExchange, 1
 */
static OS_TOOL_INLINE_KEYWORD os_boolean_t OS_AtomicCompareExchange(
	os_atomic_t volatile *object,
	os_atomic_value_t *expected,
	os_atomic_value_t newValue)
{
	os_atomic_value_t previous, expVal;
	os_boolean_t res;

	expVal = *expected;

	OS_AtomicThreadFence();
	previous = OS_ImplAtomicCmpSwapW(object, newValue, expVal);
	OS_AtomicThreadFence();

	*expected = previous;
	res = (previous == expVal);
	return res;
}

/* !LINKSTO Kernel.Atomics.ArithmeticOps, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicFetchAdd(
	os_atomic_t volatile *object,
	os_atomic_value_t operand)
{
	os_atomic_value_t previous, oldVal;

	OS_AtomicThreadFence();
	previous = *object;
	do {
		os_atomic_value_t newVal;

		oldVal = previous;
		newVal = oldVal + operand;
		previous = OS_ImplAtomicCmpSwapW(object, newVal, oldVal);
	} while (previous != oldVal);
	OS_AtomicThreadFence();

	return previous;
}

/* !LINKSTO Kernel.Atomics.ArithmeticOps, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicFetchSub(
	os_atomic_t volatile *object,
	os_atomic_value_t operand)
{
	os_atomic_value_t previous, oldVal;

	OS_AtomicThreadFence();
	previous = *object;
	do {
		os_atomic_value_t newVal;

		oldVal = previous;
		newVal = oldVal - operand;
		previous = OS_ImplAtomicCmpSwapW(object, newVal, oldVal);
	} while (previous != oldVal);
	OS_AtomicThreadFence();

	return previous;
}

/* !LINKSTO Kernel.Atomics.BoolOps, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicFetchOr(
	os_atomic_t volatile *object,
	os_atomic_value_t operand)
{
	/* required:
	 *  previous = *object;
	 *  *object = previous | operand;
	 *  return previous;
	 * implementation:
	 *  previous = *object;
	 *  *object = (previous & ~operand) | (operand & operand);
	 *  return previous;
	*/
	os_atomic_value_t previous, value;

	value = operand;
	OS_AtomicThreadFence();
	previous = OS_ImplAtomicSwapMskW(object, value, value);
	OS_AtomicThreadFence();

	return previous;
}

/* !LINKSTO Kernel.Atomics.BoolOps, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicFetchAnd(
	os_atomic_t volatile *object,
	os_atomic_value_t operand)
{
	/* required:
	 *  previous = *object;
	 *  *object = previous & operand;
	 *  return previous;
	 * implementation:
	 *  previous = *object;
	 *  *object = (previous & ~~operand) | (0 & ~operand);
	 *  return previous;
	*/
	os_atomic_value_t previous, notValue;

	notValue = ~operand;
	OS_AtomicThreadFence();
	previous = OS_ImplAtomicSwapMskW(object, 0, notValue);
	OS_AtomicThreadFence();

	return previous;
}

/* !LINKSTO Kernel.Atomics.BoolOps, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicFetchXor(
	os_atomic_t volatile *object,
	os_atomic_value_t operand)
{
	os_atomic_value_t previous, oldVal;

	OS_AtomicThreadFence();
	previous = *object;
	do {
		os_uint32_t newVal;

		oldVal = previous;
		newVal = oldVal ^ operand;
		previous = OS_ImplAtomicCmpSwapW(object, newVal, oldVal);
	} while (previous != oldVal);
	OS_AtomicThreadFence();

	return previous;
}

/* !LINKSTO Kernel.Atomics.FlagOps, 1
 */
static OS_TOOL_INLINE_KEYWORD os_boolean_t OS_AtomicTestAndSetFlag(
	os_atomic_t volatile *object,
	os_atomic_value_t flagSelectionMask)
{
	/* required:
	 *  previous = *object;
	 *  *object = previous | flagSelectionMask;
	 *  return (previous & flagSelectionMask) != 0;
	*/
	os_atomic_value_t previous, mask;

	mask = flagSelectionMask;
	previous = OS_AtomicFetchOr(object, mask);
	return (previous & mask) != 0;
}

/* !LINKSTO Kernel.Atomics.FlagOps, 1
 */
static OS_TOOL_INLINE_KEYWORD void OS_AtomicClearFlag(
	os_atomic_t volatile *object,
	os_atomic_value_t flagSelectionMask)
{
	OS_AtomicThreadFence();
	OS_ImplAtomicLdMdSt(object, 0, flagSelectionMask);
	OS_AtomicThreadFence();
}


#endif /* OS_ATOMICS_TRICORE_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
