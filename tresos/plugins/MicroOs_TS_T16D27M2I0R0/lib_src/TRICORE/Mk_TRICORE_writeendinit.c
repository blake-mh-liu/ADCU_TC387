/* Mk_TRICORE_writeendinit.c
 *
 * This file contains the functions MK_WriteEndinit() and MK_WriteSafetyEndinit() for
 * the endinit mechanism as used by the "Aurix" and the "Aurix 2G" processors.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains two external functions that are merely small interfaces to the
 *  common helper function they both use.
 *
 * DCG-2) Deviated Rule: [OS_C_LAYOUT_030]
 *  All source files (*.c) shall adhere to the following layout:
 *   1. File header
 *   2. Deviation justification(s)
 *   3. Preprocessor #include directives
 *   4. Non-function definitions (if any)
 *   5. Functions definitions having internal linkage (if any)
 *   6. Functions definitions having external linkage
 *  Note: Definitions of macros, variables and types should be grouped logically.
 *
 * Reason:
 *  This is a false positive. All functions with external linkage are placed after the
 *  last definition in this file.
*/

/* Deviation DCG-1 <*>, DCG-2 <*> */

#include <public/Mk_basic_types.h>
#include <private/Mk_panic.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>

static MK_ATTR_NO_STACKPROT void MK_DoWriteEndinit(mk_wdtcon_t *, mk_uint32_t);

/* MK_DoWriteEndinit
 *
 * This function sets the ENDINIT flag in the referenced WDTCON register to the value given in v.
 *
 * Currently only plain ENDINIT handling (without LFSR password) is implemented
*/

static MK_ATTR_NO_STACKPROT void MK_DoWriteEndinit(mk_wdtcon_t *wdtcon, mk_uint32_t v)
{
	mk_uint32_t ei = 0;
	mk_uint32_t wdtcon0;
	mk_uint32_t password;
	mk_uint32_t reload;
	mk_uint32_t modify;
	mk_uint32_t wdtStatus;

	if ( v != 0u )
	{
		ei = MK_ENDINIT;
	}

	/* To write the ENDINIT bit, we need to perform a "password"-protected
	 * modify access to the WDTxCON0 register.
	*/

	/* Read the status and WDTxCON0 register
	*/
	wdtStatus = wdtcon->wdtxssr;
	wdtcon0 = wdtcon->wdtxcon0;

	/* Read password and watchdog timer reload value.
	*/
	password = (wdtcon0 & MK_WDTPW1_MSK) | ((~wdtcon0) & MK_WDTPW0_MSK);
	reload = wdtcon0 & MK_WDTREL_MSK;

	/* Calculate value for "modify access" (LCK set, ENDINIT as requested)
	*/
	modify = reload | password | MK_WDTLCK | ei;

	/* Calculate password for "password access", i.e. perform password sequencing and time guessing
	 * if the hardware expects so.
	*/
	if ( (wdtStatus & MK_WDT_PAS) != 0u )
	{
		mk_uint32_t lsb;

		/* Calculate XOR of bits 15, 14, 13 and 3 into bit 2. The other bits contain junk after all the
		 * shifting and XORing, so discard them.
		*/
		lsb = ((password >> 13) ^ (password >> 12) ^ (password >> 11) ^ (password >> 1)) & MK_WDTPW_LSB;

		/* Shift the password one to left and add newly calculated LSB.
		*/
		password = (password << 1) & MK_WDTPW_MSK;
		password = password | lsb;

		/* password now contains the next password of the auto-generated sequence.
		*/
	}

	if ( (wdtStatus & MK_WDT_TCS) != 0u )
	{
		/* Calculate the time estimate for the password. This uses the fact that the TIM field of
		 * WDTxSR is in the same place (upper 16 bits) as the REL field of WDTxCON0.
		 * The TIMEGUESS must be shifted up there too.
		*/
		reload =  (~(wdtcon->wdtxssr + MK_WDT_TIMEGUESS)) & MK_WDTREL_MSK;
	}

	/* Unlock wdtcon0 (LCK not set, ENDINIT set).
	*/
	wdtcon->wdtxcon0 = reload | password | MK_ENDINIT;

	/* Write requested ENDINIT-value, i.e. perform "modify access".
	*/
	wdtcon->wdtxcon0 = modify;

	/* Read back value; this is done to give the hardware enough time to process it.
	 *
	 * This is recommended by the derivative's manual, section "The Endinit Functions":
	 * Note: The clearing of an ENDINIT bit takes some time. Accesses to Endinit-protected
	 * registers after the clearing of an ENDINT bit must only be done when the ENDINIT
	 * bit is really cleared. As a solution the ENDINIT bit should be read back once before
	 * Endinit-protected registers are accessed the first time after bit ENDINIT has been
	 * cleared.
	*/
	if ( (wdtcon->wdtxcon0 & MK_ENDINIT) != ei )
	{
		MK_StartupPanic(MK_panic_UnexpectedHardwareResponse);
	}
}

/* MK_WriteEndinit
 *
 * Sets the ENDINIT flag on the core the microkernel is running on.
 *
 * Note: this function is a *restricted C function*, i.e. it must not rely on the content
 * of global variables.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_WriteEndInit, 1
 * !doctype src
*/

MK_ATTR_NO_STACKPROT void MK_WriteEndinit(mk_uint32_t v)
{
	MK_DoWriteEndinit(MK_GetScuWdtCpuCon(), v);
}

/* MK_WriteSafetyEndinit
 *
 * Sets the system-wide Safety-ENDINIT flag.
 *
 * Note: this function is a *restricted C function*, i.e. it must not rely on the content
 * of global variables.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_WriteSafetyEndinit, 1
 * !doctype src
*/

MK_ATTR_NO_STACKPROT void MK_WriteSafetyEndinit(mk_uint32_t v)
{
	MK_DoWriteEndinit(MK_scu_wdtscon, v);
}


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
