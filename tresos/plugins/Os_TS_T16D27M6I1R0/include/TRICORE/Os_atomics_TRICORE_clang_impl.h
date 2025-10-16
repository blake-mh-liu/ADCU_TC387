/* Os_atomics_TRICORE_clang_impl.h
 *
 * This file contains a part of the implementation of atomic functions for
 * TRICORE, which is shared by clang-compatible toolchains.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TRICORE_CLANG_IMPL_H
#define OS_ATOMICS_TRICORE_CLANG_IMPL_H

#include <Os_types.h>

/* The clobber list of the inline assembly language statements in the following
 * inline functions contain 'memory' to preclude compiler optimizations,
 * which otherwise might move read/write operations across this statement.
 * This constitutes a compiler optimization barrier.
 *
 * See also Os_atomics_TRICORE.h for general comments.
 */

/* !LINKSTO Kernel.Atomics.Fence, 1
 */
static OS_TOOL_INLINE_KEYWORD void OS_AtomicThreadFence(void)
{
	OS_TOOL_ASM_KEYWORD volatile (
		"dsync"
		: /* no outputs */
		: /* no inputs */
		: "memory"
	);
}

/* !LINKSTO Kernel.Atomics.Exchange, 1
 */
static OS_TOOL_INLINE_KEYWORD os_atomic_value_t OS_AtomicExchange(
	os_atomic_t volatile *object,
	os_atomic_value_t newValue)
{
	register os_atomic_value_t old;

	OS_TOOL_ASM_KEYWORD volatile(
		"dsync\n\t"
		"swap.w [%1]0, %2\n\t"
		"dsync"
		: "=d" (old)
		: "a" (object), "0" (newValue)
		: "memory"
	);

	return old;
}

#endif /* OS_ATOMICS_TRICORE_CLANG_IMPL_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

