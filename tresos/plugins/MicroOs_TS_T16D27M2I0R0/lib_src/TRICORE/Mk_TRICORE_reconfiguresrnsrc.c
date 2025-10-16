/* Mk_TRICORE_reconfiguresrnsrc.c
 *
 * This file contains interrupt controller configuration functions.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function can call itself again indirectly via MK_Panic. This happens if an error is
 *  detected here and MK_Panic is called to shut down the system. During shutdown, MK_InitInterrupts
 *  is invoked, which calls this function again. If the error persists, MK_Panic will be called
 *  again, but will detect this and as a consequence call MK_PanicStop to halt the system
 *  immediately. So there is a maximum nesting of two calls to this function possible.
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains two external functions. Those functions are
 *  MK_ReconfigureSrnSrc() and MK_WaitForSrcUpdateInLwsr().
 *  This is acceptable because MK_WaitForSrcUpdateInLwsr() (and also MK_WaitForSrcUpdateInLwsrOfTos())
 *  is actually just a helper function for MK_ReconfigureSrnSrc().
 *  MK_WaitForSrcUpdateInLwsr() requires external linkage because
 *  MK_WaitForSrcUpdateInLwsrOfTos() needs to call it.
 *  MK_WaitForSrcUpdateInLwsrOfTos() needs to be in a different file because
 *  it contains code which isn't applicable to all derivatives.
*/
/* Deviation DCG-1 <*> */

#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

/* MK_ReconfigureSrnSrc()
 *
 * This function reconfigures a src register
 * according to section "16.3.1.2 Changing the SRN configuration" of the TC2xx UM (e.g. TC29xB_um_v1.3.pdf)
 * and section "19.4.1.2 Changing the SRN configuration" of TC3xx TS V2.1.0.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_ReconfigureSrnSrc, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
void MK_ReconfigureSrnSrc(mk_reg32_t *src, mk_uint32_t value)
{
	const mk_uint32_t srpn_tos_mask = MK_SRC_SRPN_MASK | MK_SRC_TOS_MASK;
	mk_uint32_t oldSrcValue;
	mk_uint32_t tos;

	/* Get the old value of the SRC, so we can check whether it appears in the LSWR. */
	oldSrcValue = *src;

	/* Disable the SRN and make sure it is disabled. */
	MK_SetAndCheckSrcValue(src, (*src) & ~MK_SRC_SRE);

	/* Handle changes of SRPN or TOS.
	 * If neither SRPN nor TOS is meant to be changed, then we don't need to poll LWSR.
	*/
	if ((oldSrcValue & srpn_tos_mask) != (value & srpn_tos_mask))
	{
		/* Poll LSWR of the current TOS. */
		tos = (oldSrcValue & MK_SRC_TOS_MASK) >> MK_SRC_TOS_SHIFT;
		MK_WaitForSrcUpdateInLwsrOfTos(tos, oldSrcValue);
		/* Change SRPN and TOS. */
		*src = (*src & ~srpn_tos_mask) | (value & srpn_tos_mask);
		/* Do a readback. */
		(void) *src;
	}

	/* Set the configuration which was actually requested.
	 * This is about setting the enable bit to the desired value
	 * and clearing the pending bits, if requested.
	*/
	MK_SetAndCheckSrcValue(src, value);
}

/* MK_WaitForSrcUpdateInLwsr()
 *
 * This function waits until the old SRC value vanishes from the LSWR register.
 * This is a helper function for MK_ReconfigureSrnSrc, to avoid un-coverable branches
 * on derivatives where the TOS can't be invalid.
*/
void MK_WaitForSrcUpdateInLwsr(mk_int_icu_t *icu, mk_uint32_t oldSrcValue)
{
	/* Read the old src value. */
	const mk_uint32_t oldSrpn = MK_GetSrcSrpn(oldSrcValue);
	const mk_uint32_t oldEcc = MK_GetSrcEcc(oldSrcValue);
	const mk_uint32_t oldEccLwsr = MK_ShiftLeftU32(oldEcc, MK_INT_LWSR_ECC_SHIFT);

	/* if LWSRx.STAT=1 and LWSRx.SRPN and LWSRx.ECC are equal to the (old) SRC value check again. */
	/* if LWSRx.STAT=0 or LWSRx.SRPN or LWSRx.ECC are not equal to the old SRC values any more go on. */
	const mk_uint32_t lwsrMask = MK_INT_LWSR_STAT_VALID_BIT | MK_INT_LWSR_PN_MASK | MK_INT_LWSR_ECC_MASK;
	const mk_uint32_t outdatedLwsr = MK_INT_LWSR_STAT_VALID_BIT | oldSrpn | oldEccLwsr;

	/* The LSWR register of the responsible ICU. */
	const mk_reg32_t * const lswr = &(icu->lwsr);

	/* The LWSR register can get stuck.
	 * Therefore, we just continue if the countdown expires.
	 * The countdown value must be large enough, so we can assume that the interrupt controller
	 * finished processing our changes.
	*/
	mk_uint32_t countdown = 300u;

	/* check the register LWSRx */
	while ((((*lswr) & lwsrMask) == outdatedLwsr) && (countdown != 0u))
	{
		MK_DSYNC(); /* Wait a bit... */
		countdown--;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
