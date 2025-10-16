/* Mk_TRICORE_board_setupclocks_tc2xx.c
 *
 * This file contains the function Tmpl_SetupClocks() to initialize the TRICORE PLL and clock dividers.
 *
 * The PLL is normally initialized during startup -- probably from the board callout
 * function before the data sections are initialized.
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setupclocks_tc2xx.c 23817 2016-06-20 05:48:06Z mist8519 $
*/
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include <Mk_TRICORE_board_pll.h>

#include "Mk_qmboard.h"

/* Flash configuration
 *
 * These values are good for the following flash timings (check your datasheet):
 *   tPF = 30ns, tPFECC = 10ns, tDF = 100ns, tDFECC = 20ns
 *
 * All Aurix Flashes supported at the time of this writing have these timings.
 */

#define TMPL_FLASH0_BASE	0xF8001000u
#define TMPL_FLASH0_FCON	(*(mk_reg32_t *)(TMPL_FLASH0_BASE+0x1014u))
#define TMPL_FCON_WS_MASK	0x7fffu

#if ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 200000000u )
#define TMPL_WSPFLASH 5u
#elif ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 233333333u )
#define TMPL_WSPFLASH 6u
#elif ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 266666666u )
#define TMPL_WSPFLASH 7u
#elif ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 300000000u )
#define TMPL_WSPFLASH 8u
#else
#error "Unsupported FSI2 clock"
#endif

#if ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 100000000u )
#define TMPL_WSECPF   1u
#elif ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 200000000u )
#define TMPL_WSECPF   2u
#elif ( (MK_SYS_FREQ / TMPL_FSI2_DIV) <= 300000000u )
#define TMPL_WSECPF   2u
#else
#error "Unsupported FSI2 clock"
#endif

/* we don't use the DFLASH, just configure wait states sufficient for the current FSI max 100 MHz */
#if ( (MK_SYS_FREQ / TMPL_FSI_DIV) <= 100000000u )
#define TMPL_WSDFLASH 9u
#define TMPL_WSECDF   1u
#else
#error "Unsupported FSI clock"
#endif

/* Set initial K2-divier to 30 (--> value to be written is 29).
*/
#define TMPL_PLLCON1_K2_INITIAL	29

/* Note: The OSC bits never indicate a stable status on our Aurix-boards, but PLL _does_ get
 * stable. Disable this check for now.
*/
#define TMPL_WAIT_UNTIL_OSC_STABLE	0

/* Tmpl_SetupClocks
 *
 * This function takes the desired values for the SCU registers PLLCON0, PLLCON1, CCUCON0 and CCUCON1 as
 * parameters.
 *
 * It then configures the PLL according to the values from the PLLCON* parameters and finally programs the
 * CCU with the values from the respective parameters. The CCU parameters need to select the PLL clock as
 * input clock. Temporary settings for these registers are derived from the input parameters where necessary.
 *
 * Note: The implementation of this function follows the examples and recommendations provided in the TC27x
 *       User's Manual, Version 1.3.1, Sections 8.1.2.1 and 8.1.8.1
 *
*/
void Tmpl_SetupClocks(mk_uint32_t pllcon0, mk_uint32_t pllcon1, mk_uint32_t ccucon0, mk_uint32_t ccucon1)
{
	mk_uint32_t pllcon1_temp = (pllcon1 & (~TMPL_PLLCON1_K2_MASK)) | TMPL_PLLCON1_K2_INITIAL;

	/* Writing to PLL registers requires Safety-ENDINIT protection to be switched off.
	*/
	MK_WriteSafetyEndinit(0);

	/* Writing to FCON requires ENDINIT cleared
	*/
	MK_WriteEndinit(0);

	/* configure flash wait states. The reset values are good for the backup clock. */
	TMPL_FLASH0_FCON = (TMPL_FLASH0_FCON & ~TMPL_FCON_WS_MASK)
		| (TMPL_WSPFLASH)
		| (TMPL_WSECPF   << 4u)
		| (TMPL_WSDFLASH << 6u)
		| (TMPL_WSECDF   << 12u);

#if TMPL_WAIT_UNTIL_OSC_STABLE
	/* Step 1 - Wait until OSC is stable.
	*/
	while ( (TMPL_SCU_OSCCON & TMPL_OSCSTABLE) != TMPL_OSCSTABLE )
	{
	}
#endif

	/* Step 2 - Program the PLL
	*/

	/* Select PLL input clock.
	*/
	while ((TMPL_SCU_CCUCON1 & TMPL_CCUCON_LCK_LOCKED) != 0)
	{
		/* Wait until CCUCON1 is unlocked. */
	}
	TMPL_SCU_CCUCON1 = (TMPL_SCU_CCUCON1 & (~TMPL_CCUCON1_INSEL_MASK)) | (ccucon1 & TMPL_CCUCON1_INSEL_MASK);
	TMPL_SCU_CCUCON1 |= TMPL_CCUCON_UP;
	while ((TMPL_SCU_CCUCON1 & TMPL_CCUCON_LCK_LOCKED) != 0)
	{
		/* Wait until CCUCON1 is unlocked. */
	}

	/* Set K1 and switch to prescaler mode before changing P and N values.
	*/
	TMPL_SCU_PLLCON1 = (TMPL_SCU_PLLCON1 & (~TMPL_PLLCON1_K1_MASK)) | (pllcon1 & TMPL_PLLCON1_K1_MASK);
	while ((TMPL_SCU_PLLSTAT & TMPL_PLLSTAT_K1RDY) == 0)
	{
		/* Wait until K1 is ready. */
	}
	TMPL_SCU_PLLCON0 |= TMPL_PLLCON0_VCOBYP;
	while ((TMPL_SCU_PLLSTAT & TMPL_PLLSTAT_VCOBYST) == 0)
	{
		/* Wait until prescaler mode has been entered (VCOBYST==1). */
	}

	/* When configuring the PLL for the first time after a system reset it is recommended
	 * to disconnect the input clock f OSC before configuring P and / or N and to connect
	 * f OSC before checking for the lock status.
	 */
	TMPL_SCU_PLLCON0 |= TMPL_PLLCON0_SETFINDIS;	/* Disconnect VCO input. */
	TMPL_SCU_PLLCON0 = (TMPL_PLLCON0_SETFINDIS | pllcon0); /* Set user values; leave VCO disconnected */
	TMPL_SCU_PLLCON1 = pllcon1_temp;
	TMPL_SCU_PLLCON0 |= TMPL_PLLCON0_CLRFINDIS;	/* Re-connect VCO input. */

	while ((TMPL_SCU_PLLSTAT & TMPL_PLLSTAT_K2RDY) == 0)
	{
		/* Wait until K2 is ready. */
	}

	/* Step 3
	*/

	/* Reset the VCO Lock detection.
	*/
	TMPL_SCU_PLLCON0 |= TMPL_PLLCON0_RESLD;

	while ((TMPL_SCU_PLLSTAT & TMPL_PLLSTAT_VCOLOCK) == 0)
	{
		/* Wait for PLL lock. */
	}

	/* Switch to normal mode (i.e., disable bypass mode).
	*/
	TMPL_SCU_PLLCON0 &= (~TMPL_PLLCON0_VCOBYP);
	while ((TMPL_SCU_PLLSTAT & TMPL_PLLSTAT_VCOBYST) == TMPL_PLLSTAT_VCOBYST)
	{
		/* Wait until normal mode has been entered (VCOBYST==0). */
	}

	/* Now increase the frequency step-wise by reducing the K2 divider to desired value.
	 *
	 * Note: the algorithm here only works as long as K2 is in the least significant bits of PLLCON1
	*/
#if (TMPL_PLLCON1_K2_MASK != 0x0000007f)
#error "Tmpl_SetupClocks() is not compatible with TMPL_PLLCON1_K2_MASK"
#endif
	while (pllcon1_temp > pllcon1)
	{
		volatile mk_uint32_t i;

		pllcon1_temp--; /* Effectively decrements K2. */
		TMPL_SCU_PLLCON1 = pllcon1_temp;

		while ((TMPL_SCU_PLLSTAT & TMPL_PLLSTAT_K2RDY) == 0)
		{
			/* Wait until K2 is ready. */
		}

		/* Between the update of two K2-Divider values 6 cycles of fPLL should be waited.
		*/
		for (i=0; i<10; i++)
		{
		}
	}

	/* Step 4: Configure CCU as requested but do not switch to PLL yet.
	*/
	while ( ((TMPL_SCU_CCUCON0 & TMPL_CCUCON_LCK_LOCKED) != 0) ||
	        ((TMPL_SCU_CCUCON1 & TMPL_CCUCON_LCK_LOCKED) != 0) )
	{
		/* Wait until CCUCON0 & CCUCON1 are unlocked. */
	}
	TMPL_SCU_CCUCON0 = (ccucon0 & (~TMPL_CCUCON0_CLKSEL_MASK));
	TMPL_SCU_CCUCON1 = ccucon1;
	while ( ((TMPL_SCU_CCUCON0 & TMPL_CCUCON_LCK_LOCKED) != 0) ||
	        ((TMPL_SCU_CCUCON1 & TMPL_CCUCON_LCK_LOCKED) != 0) )
	{
		/* Wait until CCUCON0 & CCUCON1 are unlocked. */
	}

	TMPL_SCU_CCUCON0 |= TMPL_CCUCON_UP;	/* Commit changes to CCUCON0 and CCUCON1. */

	/* Step 5: Switch CCU input clock.
	*/
	while ((TMPL_SCU_CCUCON0 & TMPL_CCUCON_LCK_LOCKED) != 0)
	{
		/* Wait until CCUCON0 is unlocked. */
	}
	TMPL_SCU_CCUCON0 = ccucon0;
	TMPL_SCU_CCUCON0 |= TMPL_CCUCON_UP;	/* Commit changes */

	/* CPU should now be running at full speed: enable ENDINIT again
	*/
	MK_WriteEndinit(1);
	MK_WriteSafetyEndinit(1);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
