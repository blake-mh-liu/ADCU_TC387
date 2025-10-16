/**
 * \file
 *
 * \brief AUTOSAR Atomics
 *
 * This file contains the implementation of the AUTOSAR
 * module Atomics.
 *
 * \version 1.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2017 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.5 (required)
 *  Identifiers shall be distinct from macro names.
 *
 * Reason:
 *  If ATOMICS_USE_GENERIC_IMPL is set to 0, the generic Atomics functions are
 *  redirected to specialized OS functions using macros.
 *
 *
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 *  Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 *  If ATOMICS_USE_GENERIC_IMPL is set to 0, the generic Atomics functions are
 *  redirected to specialized OS functions using macros.
 *
 *
 * MISRAC2012-3) Deviated Rule: 10.4 (required)
 *  Both operands of an operator in which the usual arithmetic conversions are performed shall have the same essential type category.
 *
 * Reason:
 *  E_OK is set in the OS. Depending on the OS version, it might still be signed.
 *  As it is set to 0, this is not an issue.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W588
 * W588: dead assignment to "success" eliminated
 *
 * Reason:
 * This compiler warning is caused by the symmetry between ATOMICS_USER_LOCK_OBJECT() and ATOMICS_USER_UNLOCK_OBJECT() macros.
 * The assignment to the output pointer "success" in the latter macro is currently not used because errors cannot be reported.
 * A custom implementation may use it, though.
 *
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * When ATOMICS_USER_MULTICORE is set to 0, the generic ATOMICS_USER_LOCK_OBJECT() always succeeds.
 */

/* This file contains the generic implementation of the compatibility functions
 * for atomic bit set/clear and interrupt control operations.
 */

#include <Os.h>
#include <Atomics.h>
#include <Atomics_TSPlatforms.h>
#include <Atomics_platform_types.h>
#include <TSAutosar.h>

/* The generic implementation of the atomic bit-set operation. */
#define TSP_GENERIC_SET_IMPL(addr, bitIdx, T)               \
    do {                                                    \
        VAR(boolean, AUTOMATIC) success;                    \
                                                            \
        ATOMICS_USER_THREAD_FENCE();                        \
        ATOMICS_USER_LOCK_OBJECT((addr), &success);         \
        if (success)                                        \
        {                                                   \
            *(addr) = *(addr) | (T)((T)1u << (bitIdx));     \
            ATOMICS_USER_UNLOCK_OBJECT((addr), &success);   \
            ATOMICS_USER_THREAD_FENCE();                    \
        }                                                   \
    } while (0)

/* The generic implementation of the atomic bit-clear operation. */
#define TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, T)             \
    do {                                                    \
        VAR(boolean, AUTOMATIC) success;                    \
                                                            \
        ATOMICS_USER_THREAD_FENCE();                        \
        ATOMICS_USER_LOCK_OBJECT((addr), &success);         \
        if (success)                                        \
        {                                                   \
            *(addr) = *(addr) & (T)~((T)((T)1u << (bitIdx)));\
            ATOMICS_USER_UNLOCK_OBJECT((addr), &success);   \
            ATOMICS_USER_THREAD_FENCE();                    \
        }                                                   \
    } while (0)

#define ATOMICS_START_SEC_CODE
#include <Atomics_MemMap.h>

/* !LINKSTO Atomics.TS.BitSet, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_8(
    volatile P2VAR(uint8, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
#pragma warning 549, 588
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint8);
#pragma warning default
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_8(
    volatile P2VAR(uint8, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
#pragma warning 549, 588
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint8);
#pragma warning default
}

/* !LINKSTO Atomics.TS.BitSet, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_16(
    volatile P2VAR(uint16, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
#pragma warning 549, 588
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint16);
#pragma warning default
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_16(
    volatile P2VAR(uint16, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
#pragma warning 549, 588
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint16);
#pragma warning default
}

/* !LINKSTO Atomics.TS.BitSet, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_32(
    volatile P2VAR(uint32, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
#pragma warning 549, 588 
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint32);
#pragma warning default
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_32(
    volatile P2VAR(uint32, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
#pragma warning 549, 588
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint32);
#pragma warning default
}

#if CPU_TYPE == CPU_TYPE_64
/* !LINKSTO Atomics.TS.BitSet, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_64(
    volatile P2VAR(uint64, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint64);
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_64(
    volatile P2VAR(uint64, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-3 <+1>, TASKING-1 <1>, TASKING-2 <1> */
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint64);
}
#endif /* CPU_TYPE == CPU_TYPE_64 */

/* !LINKSTO Atomics.TS.InterruptControl.Disable, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
TS_IntStatusType TS_IntDisable(void)
{
    SuspendAllInterrupts();
    return 0u;
}

/* !LINKSTO Atomics.TS.InterruptControl.Restore, 1 */
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void TS_IntRestore(VAR(TS_IntStatusType, AUTOMATIC) intStatus)
{
    TS_PARAM_UNUSED(intStatus);
    ResumeAllInterrupts();
}

#define ATOMICS_STOP_SEC_CODE
#include <Atomics_MemMap.h>
