/* Os_atomics_TRICORE_diab.h
 *
 * This file contains the implementation of the atomic functions
 * for TRICORE and the WindRiver DIAB toolchain.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TRICORE_DIAB_H
#define OS_ATOMICS_TRICORE_DIAB_H 1

#include <Os_types.h>

/* See also Os_atomics_TRICORE.h for general comments.
*/

/* Note that functions having an OS_ImplAtomic prefix are not part of the official API.
*/

/* CmpSwapW(object, newValue, expected):
 *  tmp = *object,
 *  *object = (tmp == expected)? newVal : tmp;
 *  return tmp;
*/
OS_TOOL_ASM_KEYWORD volatile os_atomic_value_t OS_ImplAtomicCmpSwapW(
	os_atomic_t volatile *object,
	os_atomic_value_t newValue,
	os_atomic_value_t expected)
{
% reg object; reg newValue; reg expected;
! "%d2", "%d4", "%d5"
.set noreorder
	mov %d4, newValue
	mov %d5, expected
	cmpswap.w [object], %e4
	mov %d2, %d4
.set reorder
}

/* SwapMskW(object, value, mask):
 *  tmp = *object;
 *  *object = (tmp & ~mask) | (value & mask);
 *  return tmp;
*/
OS_TOOL_ASM_KEYWORD volatile os_atomic_value_t OS_ImplAtomicSwapMskW(
	os_atomic_t volatile *object,
	os_atomic_value_t value,
	os_atomic_value_t mask)
{
% reg object; reg value; reg mask;
! "%d2", "%d4", "%d5"
.set noreorder
	mov %d4, value
	mov %d5, mask
	swapmsk.w [object], %e4
	mov %d2, %d4
.set reorder
}

/* LdMdSt(object, value, mask):
 *  *object = (*object & ~mask) | (value & mask);
*/
OS_TOOL_ASM_KEYWORD volatile void OS_ImplAtomicLdMdSt(
	os_atomic_t volatile *object,
	os_atomic_value_t value,
	os_atomic_value_t mask)
{
% reg object; reg value; reg mask;
! "%d4", "%d5"
.set noreorder
	mov %d4, value
	mov %d5, mask
	ldmst [object], %e4
.set reorder
}


/* !LINKSTO Kernel.Atomics.Fence, 1
 */
OS_TOOL_ASM_KEYWORD volatile void OS_AtomicThreadFence(void)
{
! /* no registers clobbered */
	dsync
}

/* !LINKSTO Kernel.Atomics.Exchange, 1
 */
OS_TOOL_ASM_KEYWORD volatile os_atomic_value_t OS_AtomicExchange(
	os_atomic_t volatile *object,
	os_atomic_value_t newValue)
{
% reg object; reg newValue;
! "%d2"
.set noreorder
	dsync
	swap.w [object], newValue
	mov %d2, newValue
	dsync
.set reorder
}

#endif /* OS_ATOMICS_TRICORE_DIAB_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

