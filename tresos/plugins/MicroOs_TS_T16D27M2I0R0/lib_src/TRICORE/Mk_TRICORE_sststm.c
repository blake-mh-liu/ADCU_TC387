/* Mk_TRICORE_sststm.c
 *
 * This file contains the implementation of the ticker interface for the SST
 * feature.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains related microkernel functions, which implement the SST hardware
 *  abstraction and hence, are always used together. This exception is permitted by the DCG.
*/
/* Deviation DCG-1 <*> */

#include <public/Mk_public_types.h>
#include <public/Mk_hw_characteristics.h>
#include <private/TRICORE/Mk_TRICORE_stm.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>
#include <private/Mk_sst.h>
#include <private/Mk_errorhandling.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>

#ifndef MK_N_STMS
#error "MK_N_STMS is not defined. Please check the header file of your derivate."
#endif

/* STM module identification
*/
#define MK_STM_MODULE_EXP_IDENT	0x0000C000u
#define MK_STM_MODULE_REV_MASK	0x000000ffu

/* CMCON register
*/
#define MK_STM_MSIZE0		0x0000001fu
#define MK_STM_MSIZE1		0x001f0000u
#define MK_STM_CMCON0		0x0000ffffu
#define MK_STM_CMCON1		0xffff0000u

/* ICR register
*/
#define MK_STM_CMP0EN		0x00000001u	/* Enable CMP0 */
#define MK_STM_CMP0MK_IR0	0x00000000u	/* CMP0 IRQ --> IR0 */
#define MK_STM_CMP1EN		0x00000010u	/*	... same for CMP1 */
#define MK_STM_CMP1MK_IR1	0x00000040u
#define MK_STM_CMP0			0x00000007u
#define MK_STM_CMP1			0x00000070u

/* ISCR register
*/
#define MK_STM_CMP0IRR		0x00000001u		/* Reset CMP0 irq */
#define MK_STM_CMP1IRR		0x00000004u		/* Reset CMP1 irq */

/* The number of comparators in a STM. */
#define MK_STM_NCMPS		2

/* A ticker id is generated as follows:
 *   tickerId = 2 * major + minor
 * with major and minor referring to the respective numbers as configured
 * in a *.conf file.
*/
#define MK_GetMajorIdFromTickerId(tickerId) ((mk_unsigned_t)(((mk_unsigned_t)(tickerId)) >> 1))
#define MK_GetMinorIdFromTickerId(tickerId) (((mk_unsigned_t)(tickerId)) & 0x1u)

/* Structure storing bitmasks to control the two comparators of a STM.
*/
typedef struct mk_stmmasks_s mk_stmmasks_t;
struct mk_stmmasks_s
{
	mk_uint32_t iscrRstFlag;	/* Interrupt request reset flag for this CMP. */
	mk_uint32_t icrMask;		/* Interrupt control register mask containing all bits for this CMP. */
	mk_uint32_t icrCmpXEn;		/* Interrupt enable bit for this CMP. */
	mk_uint32_t icrCmpXOs;		/* Interrupt output selector for this CMP. */
	mk_uint32_t	cmconMask;		/* Mask containing all bits of this CMPs configuration fields. */
	mk_uint32_t	cmconValue;		/* Configuration of this CMP. */
};

static const mk_stmmasks_t MK_stmMasks[MK_STM_NCMPS] =
{
	/* for comparator 0 (CMP0) */
	{
		MK_STM_CMP0IRR,			/* ISCR.CMP0IRR = 1 */
		MK_STM_CMP0,			/* mask for ICR.CMP0EN, ICR.CMP0IR and ICR.CMP0OS */
		MK_STM_CMP0EN,			/* ISCR.CMP0EN = 1 */
		MK_STM_CMP0MK_IR0,		/* ISCR.CMP0OS = 0 */
		MK_STM_CMCON0,			/* mask for CMCON.MSIZE0 and CMCON.MSTART0 */
		MK_STM_MSIZE0			/* CMCON.MSIZE0 = 32, CMCON.MSTART0 = 0 */
	},
	/* for comparator 1 (CMP1) */
	{
		MK_STM_CMP1IRR,			/* ISCR.CMP1IRR = 1 */
		MK_STM_CMP1,			/* mask for ICR.CMP1EN, ICR.CMP1IR and ICR.CMP1OS */
		MK_STM_CMP1EN,			/* ISCR.CMP1EN = 1 */
		MK_STM_CMP1MK_IR1,		/* ISCR.CMP1OS = 1 */
		MK_STM_CMCON1,			/* mask for CMCON.MSIZE1 and CMCON.MSTART1 */
		MK_STM_MSIZE1			/* CMCON.MSIZE1 = 32, CMCON.MSTART1 = 0 */
	}
};

static mk_tricorestm_t * const MK_stmBaseAddr[MK_N_STMS] =
{
	(mk_tricorestm_t *)MK_STM0_BASE,
#if ( MK_N_STMS > 1 )
	(mk_tricorestm_t *)MK_STM1_BASE,
#endif
#if ( MK_N_STMS > 2 )
	(mk_tricorestm_t *)MK_STM2_BASE,
#endif
#if ( MK_N_STMS > 3 )
	(mk_tricorestm_t *)MK_STM3_BASE,
#endif
#if ( MK_N_STMS > 4 )
	(mk_tricorestm_t *)MK_STM4_BASE,
#endif
#if ( MK_N_STMS > 5 )
	(mk_tricorestm_t *)MK_STM5_BASE,
#endif
};

/* Necessity of atomic operations for STM register accesses:
 * - ICR  : Atomic operations required. There is only one ICR register per STM,
 *          which might be concurrently modified from two different cores (one per minor index).
 * - ISCR : No LDMST required. ISCR doesn't contain readable information.
 *          There are no read-modify-write accesses. No lost updates possible.
 * - CMCON: Atomic operations required. There is only one CMCON register per STM,
 *          which might be concurrently modified from two different cores.
 * - SRC  : No atomic operations required. There is one SRC register per minor STM index,
 *          which belongs to exactly one hardware counter,
 *          therefore, this register is only modified by a single core.
 * - CMPx : No atomic operations required. There is one CMP register per minor STM index,
 *          which belongs to exactly one hardware counter,
 *          therefore, this register is only modified by a single core.
 * - TIMx : No LDMST required. Can't be written.
*/

/* MK_HwCheckTickerId()
 *
 * Checks the given ticker id and returns MK_TRUE if it's a valid one.
 * Otherwise MK_FALSE is returned.
 *
 * !LINKSTO Microkernel.SST.HwCheckTickerId, 1
*/
mk_boolean_t MK_HwCheckTickerId(mk_objectid_t tickerId)
{
	mk_boolean_t isOk = MK_FALSE;
	mk_unsigned_t major;

	if (tickerId >= 0)
	{
		major = MK_GetMajorIdFromTickerId(tickerId);

		if (major < (mk_unsigned_t) MK_N_STMS)
		{
			isOk = MK_TRUE;
		}
	}

	return isOk;
}

/* MK_HwInitTicker()
 *
 * Initializes the STM identified by the ticker id. This id has to be verified by the caller.
 *
 * !LINKSTO Microkernel.SST.HwInitTicker, 1
*/
void MK_HwInitTicker(mk_objectid_t tickerId)
{
	mk_unsigned_t const major = MK_GetMajorIdFromTickerId(tickerId);
	mk_unsigned_t const minor = MK_GetMinorIdFromTickerId(tickerId);
	mk_tricorestm_t *stm;
	mk_stmmasks_t const *sm;

	stm = MK_stmBaseAddr[major];
	sm = &MK_stmMasks[minor];

	if ((stm->id & ((mk_uint32_t)(~((mk_uint32_t)MK_STM_MODULE_REV_MASK)))) != MK_STM_MODULE_EXP_IDENT)
	{
		MK_StartupPanic(MK_panic_UnexpectedHardwareResponse);
	}

	/* Put the comparator into a known state.
	 */
	MK_TricoreAtomicModifyFlag(&(stm->stm_icr), sm->icrMask, sm->icrCmpXOs);

	/* Clear any pending interrupt.
	 */
	stm->stm_iscr = sm->iscrRstFlag;

	/* Configure the compare register.
	 */
	MK_TricoreAtomicModifyFlag(&(stm->stm_cmcon), sm->cmconMask, sm->cmconValue);
}

/* MK_HwStartTicker()
 *
 * Initializes and starts the STM comparator as specified by the ticker id.
 * The ticker will generate an interrupt -- unless it's stopped -- in delta ticks.
 *
 * !LINKSTO Microkernel.SST.HwStartTicker, 1
*/
void MK_HwStartTicker(mk_objectid_t tickerId, mk_tick_t delta)
{
	mk_unsigned_t const major = MK_GetMajorIdFromTickerId(tickerId);
	mk_unsigned_t const minor = MK_GetMinorIdFromTickerId(tickerId);
	mk_tricorestm_t *stm;
	mk_stmmasks_t const *sm;

	stm = MK_stmBaseAddr[major];
	sm = &MK_stmMasks[minor];

	/* Clear any pending interrupt.
	*/
	stm->stm_iscr = sm->iscrRstFlag;

	/* Set the compare register to the absolute value specified.
	 * We don't need to handle wraparound specially, because the
	 * timer is 32-bit, so the wrap point is the same as the integer
	 * overflow point.
	*/
	stm->stm_cmp[minor] = stm->stm_tim0 + delta;

	/* Enable the comparator.
	*/
	MK_TricoreAtomicOr(&(stm->stm_icr), sm->icrCmpXEn);
}

/* MK_HwStopTicker()
 *
 * Disables the STM comparator as specified by the ticker id.
 *
 * !LINKSTO Microkernel.SST.HwStopTicker, 1
*/
void MK_HwStopTicker(mk_objectid_t tickerId)
{
	mk_unsigned_t const major = MK_GetMajorIdFromTickerId(tickerId);
	mk_unsigned_t const minor = MK_GetMinorIdFromTickerId(tickerId);
	mk_tricorestm_t *stm;
	mk_stmmasks_t const *sm;

	stm = MK_stmBaseAddr[major];
	sm = &MK_stmMasks[minor];

	/* Disable the comparator clear any pending interrupt.
	*/
	MK_TricoreAtomicAndNot(&(stm->stm_icr), sm->icrCmpXEn);
	stm->stm_iscr = sm->iscrRstFlag;
}

/* MK_HwReloadTicker()
 *
 * Reloads the STM comparator as specified by the ticker id to expire in delta ticks.
 *
 * !LINKSTO Microkernel.SST.HwReloadTicker, 1
 */
void MK_HwReloadTicker(mk_objectid_t tickerId, mk_tick_t delta)
{
	mk_unsigned_t const major = MK_GetMajorIdFromTickerId(tickerId);
	mk_unsigned_t const minor = MK_GetMinorIdFromTickerId(tickerId);
	mk_tricorestm_t *stm;
	mk_stmmasks_t const *sm;
	mk_uint32_t oldCmp;

	stm = MK_stmBaseAddr[major];
	sm = &MK_stmMasks[minor];

	/* Disable the comparator.
	*/
	MK_TricoreAtomicAndNot(&(stm->stm_icr), sm->icrCmpXEn);

	/* Clear any pending interrupt.
	*/
	stm->stm_iscr = sm->iscrRstFlag;

	/* Set the compare register to the absolute value specified.
	 * We don't need to handle wraparound specially, because the
	 * timer is 32-bit, so the wrap point is the same as the integer
	 * overflow point.
	*/
	oldCmp = stm->stm_cmp[minor];
	stm->stm_cmp[minor] = oldCmp + delta;

	/* In-the-past check: if the current point in time is farther than delta
	 * ticks away from the point in time the STM comparator should have woken
	 * us up (oldCmp), then we missed one reload interval. To avoid waiting for
	 * another whole STM period -- i.e., until stm->stm_tim0 wraps around and
	 * equals the current comparator value again -- this is reported to the user.
	*/
	if ((stm->stm_tim0 - oldCmp) >= delta)
	{
		/* Deviation MISRAC2012-1 <+1> */
		MK_ReportProtectionFault(MK_GetCoreVarsFromThread(),
					 MK_sid_ExceptionHandling,
					 MK_eid_SstInThePast);
	}

	/* Enable the comparator.
	*/
	MK_TricoreAtomicOr(&(stm->stm_icr), sm->icrCmpXEn);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
