/* TRICORE_timer_stm.c - Tricore STM driver for AutosarOS
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.2 (required)
 * There shall be no dead code.
 *
 * Reason:
 * This code is required by the hardware protocol.
 */

#include <Os_kernel.h>

#include <TRICORE/Os_TRICORE_timer_stm.h>
#include <TRICORE/Os_TRICORE_stm.h>
#include <TRICORE/Os_TRICORE_cpu.h>
#include <Os_tool.h>

#if !defined(OS_STM_HAS_COMPARE)
#error "OS_STM_HAS_COMPARE is not defined: check the derivative spec file"
#elif OS_STM_HAS_COMPARE==0
#error "STM on this variant has no compare registers. Check your Makefiles!"
#endif

#if !defined(OS_N_STM)
#error "OS_N_STM is not defined: check the derivative spec file"
#endif

/* some fallbacks for the "old" (i.e., pre-Aurix) Tricores */
#if (OS_N_STM == 1) && (!(defined OS_STM0_BASE))
#define OS_STM0_BASE	OS_STM_BASE
#define OS_SRC_STM0SR0	OS_STM_SRC0
#define OS_SRC_STM0SR1	OS_STM_SRC1
#endif

#if ((OS_TRICOREARCH == OS_TRICOREARCH_16EP) || (OS_TRICOREARCH == OS_TRICOREARCH_162))
/* If the OS is running above the microkernel, it doesn't have the rights to
 * write the SRC-registers... and doesn't need to. Probably it may not even be
 * necessary in the other case, but this behaviour is kept for backwards
 * compatibility.
*/
#if OS_KERNEL_TYPE == OS_MICROKERNEL
#define OS_STM_WRITE_SRC	0
#else
#define OS_STM_WRITE_SRC	1
#endif
#elif (OS_TRICOREARCH == OS_TRICOREARCH_18)
/* On CPUs with virtualization, accesses to SRN/SRC registers either need to go through para-virtualization
 * or through full emulation. Full emulation is too expensive to perform it at runtime.
 * Because the interrupts are already reset via the STM's ISCR,
 * it is not necessary to additionally clear the interrupt via the SRN/SRC.
*/
#define OS_STM_WRITE_SRC	0
#else /* OS_TRICOREARCH */
#error "Unexpected OS_TRICOREARCH"
#endif /* OS_TRICOREARCH */

/* stmdescr_t
 *
 * Struct storing the base address of an STM, as well as the base addresses of the
 * SRC-registers in the respective SRNs for both comparators. The latters are not
 * needed if the OS runs on top of the microkernel.
 *
*/
typedef struct stmdescr_s stmdescr_t;
struct stmdescr_s
{
	os_tricorestm_t *base;
#if (OS_STM_WRITE_SRC == 1)
	os_tricoresrn_t *src[2];
#endif
};

#if (OS_STM_WRITE_SRC == 1)
#define OS_STMDESCR_INIT(base, src0, src1) { (os_tricorestm_t *)(base), {(src0), (src1)} }
#else
#define OS_STMDESCR_INIT(base, src0, src1) { (os_tricorestm_t *)(base) }
#endif

/* stmmasks_t
 *
 * Struct storing bitmasks for STM registers where control bits for the different
 * registers are contained in the same register at different positions.
*/
typedef struct stmmasks_s stmmasks_t;
struct stmmasks_s
{
	os_uint32_t setFlag;
	os_uint32_t rstFlag;
	os_uint32_t icrMask;
	os_uint32_t icrCmpXEn;
	os_uint32_t icrCmpXOs;
	os_uint32_t	cmconMask;
	os_uint32_t	cmconValue;
};

/* Prototypes of STM driver functions.
*/
static void OS_StmInit(const os_hwt_t *);
static os_timervalue_t OS_StmRead(const os_hwt_t *);
static os_boolean_t OS_StmStart(const os_hwt_t *, os_timervalue_t, os_tick_t);
static void OS_StmStop(const os_hwt_t *);

#include <memmap/Os_mm_const_begin.h>
static const stmmasks_t stmMasks[2] =
{
	{
		OS_STM_CMP0IRS,
		OS_STM_CMP0IRR,
		/* we need to set CMP1OS as well to prevent interrupt overload (see ASCOS-6059) */
		OS_STM_CMP0 | OS_STM_CMP1OS,
		OS_STM_CMP0EN,
		OS_STM_CMPXOS_IRX,
		OS_STM_CMCON0,
		OS_STM_MSIZE0
	},
	{
		OS_STM_CMP1IRS,
		OS_STM_CMP1IRR,
		/* we need to set CMP0OS as well to prevent interrupt overload (see ASCOS-6059) */
		OS_STM_CMP1 | OS_STM_CMP0OS,
		OS_STM_CMP1EN,
		OS_STM_CMPXOS_IRX,
		OS_STM_CMCON1,
		OS_STM_MSIZE1
	}
};

#if OS_TRICOREARCH == OS_TRICOREARCH_18
static const stmdescr_t stmDescr[OS_N_STM] =
{
	OS_STMDESCR_INIT( OS_STM0_BASE, &OS_SRC_STM0SR2, &OS_SRC_STM0SR3 ),
#if ( OS_N_STM > 1 )
	OS_STMDESCR_INIT( OS_STM1_BASE, &OS_SRC_STM1SR2, &OS_SRC_STM1SR3 ),
#endif
#if ( OS_N_STM > 2 )
	OS_STMDESCR_INIT( OS_STM2_BASE, &OS_SRC_STM2SR2, &OS_SRC_STM2SR3 ),
#endif
#if ( OS_N_STM > 3 )
	OS_STMDESCR_INIT( OS_STM3_BASE, &OS_SRC_STM3SR2, &OS_SRC_STM3SR3 ),
#endif
#if ( OS_N_STM > 4 )
	OS_STMDESCR_INIT( OS_STM4_BASE, &OS_SRC_STM4SR2, &OS_SRC_STM4SR3 ),
#endif
#if ( OS_N_STM > 5 )
	OS_STMDESCR_INIT( OS_STM5_BASE, &OS_SRC_STM5SR2, &OS_SRC_STM5SR3 ),
#endif
};

#else

static const stmdescr_t stmDescr[OS_N_STM] =
{
	OS_STMDESCR_INIT( OS_STM0_BASE, &OS_SRC_STM0SR0, &OS_SRC_STM0SR1 ),
#if ( OS_N_STM > 1 )
	OS_STMDESCR_INIT( OS_STM1_BASE, &OS_SRC_STM1SR0, &OS_SRC_STM1SR1 ),
#endif
#if ( OS_N_STM > 2 )
	OS_STMDESCR_INIT( OS_STM2_BASE, &OS_SRC_STM2SR0, &OS_SRC_STM2SR1 ),
#endif
#if ( OS_N_STM > 3 )
	OS_STMDESCR_INIT( OS_STM3_BASE, &OS_SRC_STM3SR0, &OS_SRC_STM3SR1 ),
#endif
#if ( OS_N_STM > 4 )
	OS_STMDESCR_INIT( OS_STM4_BASE, &OS_SRC_STM4SR0, &OS_SRC_STM4SR1 ),
#endif
#if ( OS_N_STM > 5 )
	OS_STMDESCR_INIT( OS_STM5_BASE, &OS_SRC_STM5SR0, &OS_SRC_STM5SR1 ),
#endif
};
#endif /* OS_TRICOREARCH == OS_TRICOREARCH_18 */

const os_hwtdrv_t OS_stmDriver =
{
	&OS_StmInit,
	&OS_StmRead,
	&OS_StmStart,
	&OS_StmStop
};
#include <memmap/Os_mm_const_end.h>

/* Necessity of atomic operations for STM register accesses:
 * - stm_icr  : Atomic operations required. There is only one ICR register per STM,
 *               which might be concurrently modified from two different cores (one per minor index).
 * - stm_iscr : No LDMST required. ISCR doesn't contain readable information.
 *               There are no read-modify-write accesses. No lost updates possible.
 * - stm_cmcon: Atomic operations required. There is only one CMCON register per STM,
 *               which might be concurrently modified from two different cores.
 * - src      : No atomic operations required. There is one SRC register per minor STM index,
 *               which belongs to exactly one hardware counter,
 *               therefore, this register is only modified by a single core.
 * - stm_cmp  : No atomic operations required. There is one CMP register per minor STM index,
 *               which belongs to exactly one hardware counter,
 *               therefore, this register is only modified by a single core.
 * - stm_tim0/stm_abs : No LDMST required. Can't be written.
 *                      Must be read with the macro OS_StmReadTimeLow32().
*/

/*!
 * OS_StmInit()
 *
 * Initialises the STM specified in the HW timer descriptor.
 *
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_StmInit(const os_hwt_t *td)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_tricorestm_t * const stm = stmDescr[td->major].base;
	stmmasks_t const * const sm = &stmMasks[td->minor];
	os_uint32_t cmpOsFixed = sm->icrCmpXOs;

	/* Put the comparator into a known state.
	*/
	OS_ArchAtomicModifyFlag(&(stm->stm_icr), sm->icrMask, cmpOsFixed);

	/* Clear any pending interrupt.
	*/
	stm->stm_iscr = sm->rstFlag;

	/* Configure the compare register.
	*/
	OS_ArchAtomicModifyFlag(&(stm->stm_cmcon), sm->cmconMask, sm->cmconValue);
}

/*!
 * OS_StmRead()
 *
 * On Tricore 1.8(TC4) the counter is stored in a 64-bit location and a downcast is performed
 * to return the lower half of the counter.
 *
 * !LINKSTO Kernel.Autosar.Counter.Types.HARDWARE.Value, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static os_timervalue_t OS_StmRead(const os_hwt_t *td)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	return OS_StmReadTimeLow32(stmDescr[td->major].base);
}

/*!
 * OS_StmStart()
 *
 * Initialises and starts the STM comparator as specified in the HW timer descriptor.
 *
 * The absolute value given by (old + delta) is stored into the comparator. If the
 * value is already in the past, the timer interrupt is triggered. The "in the past"
 * computation uses the given old value as a limit for times that are less than the
 * new timer position but must be considered to be in the future.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static os_boolean_t OS_StmStart(const os_hwt_t *td, os_timervalue_t old, os_tick_t delta)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_tricorestm_t * const stm = stmDescr[td->major].base;
	stmmasks_t const * const sm = &stmMasks[td->minor];
	os_timervalue_t new;

	/* Clear any pending interrupt.
	*/
	stm->stm_iscr = sm->rstFlag;
#if (OS_STM_WRITE_SRC == 1)
	*(stmDescr[td->major].src[td->minor]) |= OS_SRN_CLRR;
#endif

	/* Set the compare register to the absolute value specified.
	 * We don't need to handle wraparound specially, because the
	 * timer is 32-bit, so the wrap point is the same as the integer
	 * overflow point.
	*/
	stm->stm_cmp[td->minor] = (old + delta);

	/* Enable the comparator and the interrupt.
	*/
	OS_ArchAtomicOr(&(stm->stm_icr), sm->icrCmpXEn);
#if (OS_STM_WRITE_SRC == 1)
	*(stmDescr[td->major].src[td->minor]) |= OS_SRN_SRE;

	/* Attempt to flush the CPU pipelines
	 *
	 * According to Infineon it is only necessary to read back the last register that was written.
	*/
	/* Deviation MISRAC2012-1 <+1> */
	*(stmDescr[td->major].src[td->minor]);
#else
	/* Deviation MISRAC2012-1 <+1> */
	stm->stm_icr;
#endif

	/* Look at the stm value again. If the before and after values straddle the
	 * programmed value, we return TRUE to indicate that the time is in the past.
	 * Overflows here don't matter - all we're interested in are the relative distances.
	*/
	new = OS_StmReadTimeLow32(stm);

	return (delta <= (new - old));
}

/*!
 * OS_StmStop()
 *
 * Disables the STM comparator as specified in the HW timer descriptor.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_StmStop(const os_hwt_t *td)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_tricorestm_t * const stm = stmDescr[td->major].base;
	stmmasks_t const * const sm = &stmMasks[td->minor];

	/* Disable the comparator clear any pending interrupt.
	 *
	 * According to Infineon it is only necessary to read back the last register that was written.
	 * In this case we need to ensure that the comparator is really disabled before clearing the
	 * interrupt flag and enabling the interrupt.
	*/
	OS_ArchAtomicAndNot(&(stm->stm_icr), sm->icrCmpXEn);
	/* Deviation MISRAC2012-1 <+1> */
	stm->stm_icr;

	stm->stm_iscr = sm->rstFlag;

#if (OS_STM_WRITE_SRC == 1)
	*(stmDescr[td->major].src[td->minor]) |= OS_SRN_CLRR;
	/* Deviation MISRAC2012-1 <+1> */
	*(stmDescr[td->major].src[td->minor]);
#else
	/* Deviation MISRAC2012-1 <+1> */
	stm->stm_iscr;
#endif

}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
