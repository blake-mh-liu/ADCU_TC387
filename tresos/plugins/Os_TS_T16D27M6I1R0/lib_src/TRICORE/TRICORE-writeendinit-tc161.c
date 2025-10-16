/* TRICORE-wrinteendinit.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_types.h>
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_Version.h>
#include <Os_kernel.h>
#include <Os_tool.h>
#include <TRICORE/Os_defs_TRICORE.h>

#include <TRICORE/Os_TRICORE_aurix_wdt.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_WriteEndinitAurix
 *
 * This helper function perform an ENDINIT modification on a WDTCON0 register
 * on Aurix platforms.
 *
 * Keeping the desired value in the first parameter means that the compiled code
 * does not need to shuffle registers around before loading the second parameter.
 *
 * This routine writes the parameter (either 0 or 1) to the Safety-ENDINIT bit.
 * A secret handshake is required before this can be done.
 *
*/
static void OS_WriteEndinitAurix(os_uint32_t, os_tricore_aurix_wdt_t*);
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_WriteEndinitAurix(os_uint32_t v, os_tricore_aurix_wdt_t *pWdt)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t modify, password, ei, wmode, lsfr, lsb;
	OS_DSYNC();

	/* This is the target value of the ENDINIT bit
	*/
	ei = (( v == 0u ) ? (os_uint32_t)0u : (os_uint32_t)OS_ENDINIT);

	/* This is a local copy of the WDTxSR, from which we use the PAS and TCS bits.
	*/
	wmode = pWdt->wdt_sr;

	/* Read the current password and re-invert the bits that are supplied inverted.
	 * Also clear the LCK bit.
	*/
	password = ((pWdt->wdt_con[0] ^ OS_WDT_PW_INV) & ((os_uint32_t)~(os_uint32_t)OS_WDT_LCK)) | OS_ENDINIT;

	/* Calculate the value to use in the modify access.
	 * This value sets the LCK bit again and has ENDINIT as requested.
	*/
	modify = (password & ((os_uint32_t)~(os_uint32_t)OS_ENDINIT)) | OS_WDT_LCK | ei;

	if ( (wmode & OS_WDT_PAS) != 0u )
	{
		/* Calculate the next password from the current password. This first step isolates
		 * the existing password.
		*/
		lsfr = password & OS_WDT_PW;

		/* Calculate XOR of bits 15, 14, 13 and 3 into bit 2. The other bits contain junk after all the
		 * shifting and XORing, so discard them.
		*/
		lsb = ((lsfr >> 13) ^ (lsfr >> 12) ^ (lsfr >> 11) ^ (lsfr >> 1)) & OS_WDT_PW_LSB;

		/* Calculate the lsfr shifted left. Discard the upper bit of the field.
		 * This shifts a zero into the LSB.
		*/
		lsfr = (lsfr << 1) & OS_WDT_PW;

		/* Put the shifted password and the calculated lsb back into the password field.
		*/
		password = (password & ((os_uint32_t)~(os_uint32_t)OS_WDT_PW)) | lsfr | lsb;
	}

	if ( (wmode & OS_WDT_TCS) != 0u )
	{
		/* Calculate the time estimate for the password. This uses the fact that the TIM field of
		 * WDTxSR is in the same place (upper 16 bits) as the REL field of WDTxCON0.
		 * The TIMEGUESS must be shifted up there too.
		*/
		password = (password & ~OS_WDT_REL) | ( (~(pWdt->wdt_sr + OS_WDT_TIMEGUESS)) & OS_WDT_REL);
	}

	/* Perform "Password Access" to WDTxCON0 to clear the LCK bit and enable modification of ENDINIT.
	*/
	pWdt->wdt_con[0] = password;

	/* Perform "Modify Access" to WDTxCON0 to change ENDINIT and set the LCK bit again.
	*/
	pWdt->wdt_con[0] = modify;

	/* Wait until ENDINIT really is the expected value.
	*/
	while ( (pWdt->wdt_con[0] & OS_ENDINIT) != ei )
	{
		/* If the processor hangs here, the password was probably wrong. */
	}
}

/* OS_WriteEndinit() - write to the ENDINIT bit
 *
 * This routine writes the parameter (either 0 or 1) to the ENDINIT bit.
 * A secret handshake is required before this can be done.
 *
 * If the processor is a member of the Aurix family, the helper function is called.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_WriteEndinit(os_uint32_t v)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_coreid_t coreId = OS_TricoreGetCoreId();
	OS_WriteEndinitAurix(v, &OS_pwr.pwr_wdt[coreId]);
}

/* OS_WriteSafetyEndinit() - write to the Safety-ENDINIT bit
 *
 * It calls OS_WriteEndinitAurix() to do the job.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_WriteSafetyEndinit(os_uint32_t v)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_WriteEndinitAurix(v, &OS_pwr.pwr_swdt);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_writeendinit_tc161_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
