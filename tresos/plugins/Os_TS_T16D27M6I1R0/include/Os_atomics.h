/* Os_atomics.h
 *
 * This file represents the main header file for the set of atomic functions
 * offered by EB tresos AutoCore OS. Only this file shall be #include'd to use
 * these functions.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_H
#define OS_ATOMICS_H

#include <Os_defs.h>
#include <Os_types.h>

#ifndef EB_STATIC_CHECK

#include <Os_hwsel.h>
#include OS_HWSEL_ATOMICS

#else /* EB_STATIC_CHECK defined */

#if OS_ARCH_HAS_64BIT
typedef os_uint64_t os_atomic_t;
typedef os_uint64_t os_atomic_value_t;
#else
typedef os_uint32_t os_atomic_t;
typedef os_uint32_t os_atomic_value_t;
#endif

extern void OS_AtomicThreadFence(void);
extern void OS_AtomicInit(os_atomic_t volatile*, os_atomic_value_t);
extern void OS_AtomicStore(os_atomic_t volatile*, os_atomic_value_t);
extern os_atomic_value_t OS_AtomicLoad(os_atomic_t const volatile*);
extern os_atomic_value_t OS_AtomicExchange(os_atomic_t volatile*, os_atomic_value_t);
extern os_boolean_t OS_AtomicCompareExchange(os_atomic_t volatile*, os_atomic_value_t *, os_atomic_value_t);
extern os_atomic_value_t OS_AtomicFetchAdd(os_atomic_t volatile*, os_atomic_value_t);
extern os_atomic_value_t OS_AtomicFetchSub(os_atomic_t volatile*, os_atomic_value_t);
extern os_atomic_value_t OS_AtomicFetchOr(os_atomic_t volatile*, os_atomic_value_t);
extern os_atomic_value_t OS_AtomicFetchAnd(os_atomic_t volatile*, os_atomic_value_t);
extern os_atomic_value_t OS_AtomicFetchXor(os_atomic_t volatile*, os_atomic_value_t);
extern os_boolean_t OS_AtomicTestAndSetFlag(os_atomic_t volatile*, os_atomic_value_t);
extern void OS_AtomicClearFlag(os_atomic_t volatile*, os_atomic_value_t);

#endif /* EB_STATIC_CHECK */

/* The following comments describe the API.
 * The atomic functions are comprised of this set of functions.
 */

/* void OS_AtomicThreadFence(void)
 * 
 * Creates a sequentially consistent acquire and release fence.
 * 
 * The behavior is the same as what C11 specifies for the following call.
 *   atomic_thread_fence(memory_order_seq_cst);
 *
 * It may also serve as a compiler-barrier, which stops the compiler
 * from moving instructions across it either way for optimization purposes.
 */

/* OS_ATOMIC_OBJECT_INITIALIZER
 *
 * Initializes an atomic object at program load time with the given initial value.
 * You must initialize an atomic object, before use. Failing to do so, ensues
 * undefined behavior.
 *
 * Atomic objects with static storage duration are initialized with the initial
 * value zero.
 *
 * See also OS_AtomicInit(), which does the same at runtime.
 *
 * The behavior is as defined by C11 for the following:
 *   ATOMIC_VAR_INIT(initValue)
 */
/* !LINKSTO Kernel.Atomics.Init, 1 */
#ifndef OS_ATOMIC_OBJECT_INITIALIZER
#define OS_ATOMIC_OBJECT_INITIALIZER(initValue) (initValue)
#endif

/* void OS_AtomicInit(os_atomic_t volatile *object, os_atomic_value_t initValue)
 *
 * Initializes the given atomic object at runtime with the given initial value.
 * You must initialize an atomic object, before use. Failing to do so, ensues
 * undefined behavior.
 *
 * See also OS_ATOMIC_OBJECT_INITIALIZER, which does the same at load time.
 *
 * The behavior is as defined by C11 for the following call:
 *   atomic_init(object, initValue);
 */

/* void OS_AtomicStore(os_atomic_t volatile *object, os_atomic_value_t newValue)
 * 
 * Stores 'newValue' into '*object' atomically.
 *
 * The given 'newValue' is stored atomically into the memory location pointed
 * to by 'object' and sequential consistency is ensured.
 * 
 * The behavior is as defined by C11 for the following call:
 *   atomic_store(object, newValue);
 */

/* os_atomic_value_t OS_AtomicLoad(os_atomic_t const volatile *object)
 *
 * Loads from '*object' atomically.
 *
 * Atomically loads the value in the memory location pointed to by 'object'
 * and returns it. Sequential consistency is ensured.
 * 
 * The behavior is as defined by C11 for the following call:
 *   atomic_load(object);
 */

/* os_atomic_value_t OS_AtomicExchange(os_atomic_t volatile *object,
 *   os_atomic_value_t newValue)
 * 
 * Atomically exchanges the given values
 *
 * This function atomically exchanges the value pointed to by 'object'
 * with the value 'newValue'. It returns the value the memory location at
 * 'object' had before this exchange.
 *
 * The behavior is as specified in C11 when calling the following function:
 *    atomic_exchange(object, newValue);
 */

/* os_boolean_t OS_AtomicCompareExchange(
 *   os_atomic_t volatile *object,
 *   os_atomic_value_t *expected,
 *   os_atomic_value_t newValue)
 * 
 * Atomically exchanges the given values if the comparison succeeds.
 *
 * If the values at 'object' and 'expected' are equal, 'newValue' is written
 * atomically into the the memory location pointed to by 'object' and OS_TRUE is
 * returned.
 *
 * If the values at 'object' and 'expected' are not equal, the current value at
 * 'object' is written into the the memory location pointed to by 'expected' and
 * OS_FALSE is returned.
 *
 * Sequential consistency is ensured.
 * 
 * The behavior is as specified in C11 when calling the following function:
 *   atomic_compare_exchange_strong(object, expected, newValue);
 */

/* os_atomic_value_t OS_AtomicFetchAdd(os_atomic_t volatile *object,
 *   os_atomic_value_t operand)
 * 
 * Atomically adds the given number.
 *
 * This function atomically adds 'operand' to the value in memory at
 * location 'object'. The value in this location before the operation
 * is returned.
 *
 * The behavior is as specified in C11 when calling the function:
 *   atomic_fetch_add(object, operand);
 */

/* os_atomic_value_t OS_AtomicFetchSub(os_atomic_t volatile *object,
 *   os_atomic_value_t operand)
 * 
 * Atomically subtracts the given number.
 *
 * This function atomically subtracts 'operand' from the value in memory at
 * location 'object'. The value in this location before the operation is
 * returned.
 *
 * The behavior is as specified in C11 when calling the function:
 *   atomic_fetch_sub(object, operand);
 */

/* os_atomic_value_t OS_AtomicFetchOr(os_atomic_t volatile *object,
 *   os_atomic_value_t operand)
 * 
 * Atomically performs a boolean OR operation.
 *
 * This function atomically performs a boolean OR operation of 'operand' and
 * the value in memory pointed to by 'object' and stores the result into that
 * location. It returns the value in that location before the operation.
 *
 * The behavior is as specified in C11 when calling the function:
 *   atomic_fetch_or(object, operand);
 */

/* os_atomic_value_t OS_AtomicFetchAnd(os_atomic_t volatile *object,
 *   os_atomic_value_t operand)
 *
 * Atomically performs a boolean AND operation.
 *
 * The same as OS_AtomicFetchOr() but for AND.
 *
 * The behavior is as specified in C11 when calling the function:
 *   atomic_fetch_and(object, operand);
 */

/* os_atomic_value_t OS_AtomicFetchXor(os_atomic_t volatile *object,
 *   os_atomic_value_t operand)
 *
 * Atomically performs a boolean XOR operation.
 *
 * The same as OS_AtomicFetchOr() but for XOR.
 *
 * The behavior is as specified in C11 when calling the function:
 *   atomic_fetch_xor(object, operand);
 */

/* os_boolean_t OS_AtomicTestAndSetFlag(
 *   os_atomic_t volatile *object,
 *   os_atomic_value_t flagSelectionMask)
 *
 * Atomically sets a selected bit.
 *
 * Atomically sets the bit selected by 'flagSelectionMask' in the memory
 * location pointed to be 'object'. It returns the state of this bit before
 * the operation, i.e., OS_TRUE, if it was already set and OS_FALSE otherwise.
 * Only one bit may be selected by 'flagSelectionMask'.
 *
 * The behavior is similar as specified in C11 when calling the function:
 *    atomic_flag_test_and_set(object);
 * but more than just one flag are fitted into an os_atomic_t object.
 */

/* void OS_AtomicClearFlag(os_atomic_t volatile *object,
 *   os_atomic_value_t flagSelectionMask)
 *
 * Atomically clears a selected bit.
 *
 * This function atomically clears the bit selected by 'flagSelectionMask'
 * in the memory location pointed to by 'object'.
 *
 * The behavior is similar as specified in C11 when calling the function:
 *    atomic_flag_clear(object);
 * but more than just one flag is fitted into an os_atomic_t object.
 */

#endif /* OS_ATOMICS_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
