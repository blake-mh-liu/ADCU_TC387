/* Os_atomics_tsplatforms.h
 *
 * This file is the main header file for the set of legacy atomic functions and
 * types which are provided for backward compatibility with the asc_Platforms
 * module. Back in the day, that module offered this set of functions and types
 * for atomic bit-manipulation of 8-, 16-, 32-, and 64-bit types and interrupt
 * control. All this was moved to asc_Os.
 *
 * In contrast to those functions in Os_atomics.h, the legacy atomic functions
 * accessible via this header file shall not be used directly; they shall only
 * be used indirectly via the Atomics module. This is the reason why they are
 * not publicly documented in the OS documentation. In the Atomics module, the
 * respective functions have the prefix "TS_" and are mapped by that module to
 * the respective OS functions that have the prefixes "OS_AtomicTS" or
 * "OS_UserAtomicTS" as documented in this header file.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TSPLATFORMS_H
#define OS_ATOMICS_TSPLATFORMS_H

#include <Os_defs.h>

#if (OS_ARCH == OS_PA)
#include <PA/Os_atomics_tsplatforms_PA.h>
#elif (OS_ARCH == OS_TRICORE)
#include <TRICORE/Os_atomics_tsplatforms_TRICORE.h>
#elif (OS_ARCH == OS_RH850)
#include <RH850/Os_atomics_tsplatforms_RH850.h>
#elif (OS_ARCH == OS_CORTEXM)
#include <CORTEXM/Os_atomics_tsplatforms_CORTEXM.h>
#elif (OS_ARCH == OS_ARM)
#include <ARM/Os_atomics_tsplatforms_ARM.h>
#elif ((OS_ARCH == OS_ARC) || \
	  (OS_ARCH == OS_ARM64) || \
	  (OS_ARCH == OS_WINDOWS) || \
	  (OS_ARCH == OS_LINUX))
#include <Os_atomics_tsplatforms_generic_bits_reservations.h>
#include <Os_atomics_tsplatforms_generic_intlocks.h>
#else
#error "The TS_*() compatibility functions for atomic operations are not implemented for this architecture."
#endif

/* void OS_AtomicTSSetBit_8(
 *  os_uint8_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically sets the selected bit.
 *
 * The bit at index 'bitIdx' in the byte pointed to by 'addr' is atomically
 * set. The argument 'bitIdx' must be out of 0 to 7 (inclusive).
 */

/* void OS_AtomicTSClearBit_8(
 *  os_uint8_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically clears the selected bit.
 *
 * The bit at index 'bitIdx' in the byte pointed to by 'addr' is atomically
 * cleared. The argument 'bitIdx' must be out of 0 to 7 (inclusive).
 */

/* void OS_AtomicTSSetBit_16(
 *  os_uint16_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically sets the selected bit.
 *
 * The bit at index 'bitIdx' in the short pointed to by 'addr' is atomically
 * set. The argument 'bitIdx' must be out of 0 to 15 (inclusive).
 */

/* void OS_AtomicTSClearBit_16(
 *  os_uint16_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically clears the selected bit.
 *
 * The bit at index 'bitIdx' in the short pointed to by 'addr' is atomically
 * cleared. The argument 'bitIdx' must be out of 0 to 15 (inclusive).
 */

/* void OS_AtomicTSSetBit_32(
 *  os_uint32_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically sets the selected bit.
 *
 * The bit at index 'bitIdx' in the short pointed to by 'addr' is atomically
 * set. The argument 'bitIdx' must be out of 0 to 31 (inclusive).
 */

/* void OS_AtomicTSClearBit_32(
 *  os_uint32_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically clears the selected bit.
 *
 * The bit at index 'bitIdx' in the short pointed to by 'addr' is atomically
 * cleared. The argument 'bitIdx' must be out of 0 to 31 (inclusive).
 */

/* void OS_AtomicTSSetBit_64(
 *  os_uint64_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically sets the selected bit.
 *
 * The bit at index 'bitIdx' in the short pointed to by 'addr' is atomically
 * set. The argument 'bitIdx' must be out of 0 to 63 (inclusive).
 */

/* void OS_AtomicTSClearBit_64(
 *  os_uint64_t volatile *addr,
 *  os_uint32_t bitIdx);
 *
 * Atomically clears the selected bit.
 *
 * The bit at index 'bitIdx' in the short pointed to by 'addr' is atomically
 * cleared. The argument 'bitIdx' must be out of 0 to 63 (inclusive).
 */

/* os_intstatus_t OS_UserAtomicTSIntDisable(void);
 *
 * This function suspends all interrupts and
 * returns the current interrupt status. This status can be passed
 * to OS_UserAtomicTSIntRestore() to resume interrupts later on.
 *
 * Please note, that each call of OS_UserAtomicTSIntDisable() must be accompanied
 * by a call of OS_UserAtomicTSIntRestore(). Furthermore, the value passed to
 * OS_UserAtomicTSIntRestore() must be the return value of the most recent call
 * of OS_UserAtomicTSIntDisable().
 * Violations might result in unexpected bahavior.
 */

/* void OS_UserAtomicTSIntRestore(os_intstatus_t status);
 *
 * This function restores the interrupt status passed to it.
 * This status is the return value of the most recent OS_UserAtomicTSIntDisable()
 * call.
 */

#endif /* OS_ATOMICS_TSPLATFORMS_H */
