/* Os_atomics_tsplatforms_generic_bits_hwlock.h
 *
 * This file contains the implementation of the legacy atomic functions
 * OS_AtomicTSSet/ClearBit_*(). The basis for it is a hardware module that is
 * used to protect agains concurrent accesses from other cores. For example,
 * this could be achieved by means of a SEMA4 module, but any other hardware
 * module with similar functionality may also be used as well.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#ifndef OS_ATOMICS_TSPLATFORMS_GENERIC_BITS_HWLOCK_H
#define OS_ATOMICS_TSPLATFORMS_GENERIC_BITS_HWLOCK_H

#include <Os_defs.h>
#include <Os_types.h>
#include <Os_atomics.h>

#if (OS_ARCH == OS_PA)
#include <PA/Os_atomics_tsplatforms_intlock_PA.h>
#include <PA/Os_atomics_tsplatforms_sema4_hwlock_PA.h>

#elif (OS_ARCH == OS_CORTEXM)
#include <CORTEXM/Os_atomics_tsplatforms_intlock_CORTEXM.h>

#if (OS_HAS_SEMA4 == 1)
#include <CORTEXM/Os_atomics_tsplatforms_sema4_hwlock_CORTEXM.h>
#elif (OS_HAS_IPC == 1)
#include <CORTEXM/Os_atomics_tsplatforms_ipc_hwlock_CORTEXM.h>
#endif

#elif (OS_ARCH == OS_ARM)
#include <ARM/Os_atomics_tsplatforms_intlock_ARM.h>
#include <ARM/Os_atomics_tsplatforms_sema4_hwlock_ARM.h>

#else
#error "This architecture is not configured to use a hardware-lock module to implement the legacy atomic functions."
#endif


/* Note, the documentation of the following functions is in Os_atomics_tsplatforms.h.
 *
 * In the following functions, a global hardware lock is used for mutual exclusion
 * of different cores that access the same atomic object. To ensure that every
 * core has the same view of system memory, the thread fences must be right
 * around the update of an atomic object in these functions. The thread fence
 * right after an update ensures that the modified value reaches system memory
 * before the global hardware lock is released to allow other cores to access the
 * same atomic object. The thread fence right before an update ensures that the
 * current value of an atomic object is used and not a prefetched copy.
 */


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSSetBit_8(
	os_uint8_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint8_t)(*addr | (1U << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSClearBit_8(
	os_uint8_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint8_t)(*addr & ~(1U << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSSetBit_16(
	os_uint16_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint16_t)(*addr | (1U << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSClearBit_16(
	os_uint16_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint16_t)(*addr & ~(1U << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSSetBit_32(
	os_uint32_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint32_t)(*addr | (1U << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSClearBit_32(
	os_uint32_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint32_t)(*addr & ~(1U << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


#if OS_ARCH_HAS_64BIT
static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSSetBit_64(
	os_uint64_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint64_t)(*addr | (1UL << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}


static OS_TOOL_INLINE_KEYWORD void OS_AtomicTSClearBit_64(
	os_uint64_t volatile *addr,
	os_uint32_t bitIdx)
{
	os_uint32_t savedIntState;

	savedIntState = OS_AtomicsIntDisable();
	OS_AtomicsTakeHardwareLock(savedIntState);

	OS_AtomicThreadFence();

	*addr = (os_uint64_t)(*addr & ~(1UL << bitIdx));

	OS_AtomicThreadFence();

	OS_AtomicsDropHardwareLock();
	OS_AtomicsIntRestore(savedIntState);
}
#endif /* OS_ARCH_HAS_64BIT */

#endif /* OS_ATOMICS_TSPLATFORMS_GENERIC_BITS_HWLOCK_H */
