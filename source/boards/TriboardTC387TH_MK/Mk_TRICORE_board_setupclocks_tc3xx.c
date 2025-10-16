/* Mk_TRICORE_board_setupclocks_tc3xx.c
 *
 * This file contains the function Tmpl_SetupClocks(), which
 * initializes the TRICORE PLL and clock dividers.
 *
 * The PLL is normally initialized during startup before the
 * data sections are initialized. Switching to a higher frequency clock source
 * allows to complete the rest of the initialization in a shorter time.
 *
 * After power-on or after a reset the system operates on the back-up clock.
 * SRI-Bus, CPUs run with back-up clock frequency (~100 MHz)
 * Peripherals and SPB-Bus run with half back-up clock frequency (~50MHz)
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setupclocks_tc3xx.c 31280 2018-01-18 12:53:56Z mist9353 $
*/

#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include <Mk_TRICORE_board_pll.h>

#include "Mk_qmboard.h"

static void Tmpl_BoardWait(mk_uint32_t) MK_ATTR_NO_INLINE MK_ATTR_ALIGN(32);
static void Tmpl_BoardWaitValsEqual(mk_reg32_t*, mk_uint32_t);
static void Tmpl_BoardWaitForCCUCONIsUnlocked(mk_reg32_t*);
static void Tmpl_BoardWaitBitSet(mk_reg32_t*, mk_uint32_t);


static void Tmpl_BoardWait(mk_uint32_t delay)
{
	mk_reg32_t vltCnt;
	/* 
	 * The PLL setup on TC39XX requires long waiting periods, but 
	 * the safety-endinit protection can be limited by time.
	 * To make sure not to overrun the time-limit let's re-set protection.
	*/
	MK_WriteSafetyEndinit(1);
	for (vltCnt=0; vltCnt < delay; vltCnt++)
	{
		/* do nothing */
	}
	MK_WriteSafetyEndinit(0);
}

static void Tmpl_BoardWaitValsEqual(mk_reg32_t* vLeft, mk_uint32_t vRight)
{
	mk_reg32_t vltCounter = 0;
	mk_uint32_t iterStep = TMPL_FREQ_STBL_DELAY >> 3;
	while ((*vLeft != vRight) && (vltCounter < TMPL_FREQ_STBL_DELAY))
	{
		Tmpl_BoardWait(iterStep);
		vltCounter += iterStep;
	}
}

#if (TMPL_CCUCON0_LCK == TMPL_CCUCON1_LCK) && (TMPL_CCUCON0_LCK == TMPL_CCUCON2_LCK)
static void Tmpl_BoardWaitForCCUCONIsUnlocked(mk_reg32_t* lockReg)
{
	mk_reg32_t vltCounter = 0;
	mk_uint32_t iterStep = TMPL_FREQ_STBL_DELAY >> 3;
	while (((*lockReg & TMPL_CCUCON0_LCK) != 0) && (vltCounter < TMPL_FREQ_STBL_DELAY))
	{
		Tmpl_BoardWait(iterStep);
		vltCounter += iterStep;
	}
}
#else
#error Tmpl_BoardWaitForCCUCONIsUnlocked has to be adapted
#endif

static void Tmpl_BoardWaitBitSet(mk_reg32_t* val, mk_uint32_t bitMask)
{
	mk_reg32_t vltCounter = 0;
	mk_uint32_t iterStep = TMPL_FREQ_STBL_DELAY >> 3;
	while (((*val & bitMask) != bitMask) && (vltCounter < TMPL_FREQ_STBL_DELAY))
	{
		Tmpl_BoardWait(iterStep);
		vltCounter += iterStep;
	}
}

/* Note: flash wait state configuration has been excluded from this file.
 * In case of a problem, check the TC29X-related files or the AutoCore OS code of TC3xx
*/

/*
 * Enable external oscillator, set up the System PLL, Set up the Peripheral PLL,
 * Program the CCU, select the PLL clock as the input clock.
 * Step by step lower the K2 value to reach the target frequency.
*/
void Tmpl_SetupClocks()
{
	mk_reg32_t tmpVal_ccucon0, tmpVal_ccucon1, tmpVal_ccucon2;
	mk_tricore_scu_t * const scu = (mk_tricore_scu_t *)MK_MODBASE_SCU;

	/* Writing to PLL registers requires Safety-ENDINIT protection to be switched off */
	MK_WriteSafetyEndinit(0);
	
	/* Enable ext. oscillator, set reference clock to 20 MHz */
	scu->osccon = (scu->osccon & ~TMPL_OSCCON_MODE_MASK) | TMPL_CCUCON_OSCVAL | TMPL_OSCCON_OSCRES;
	Tmpl_BoardWaitBitSet(&scu->osccon, TMPL_OSCSTABLE);
	
	/* Set up the System PLL: 
	 * Clock source, power mode, and dividers (P, N, K2).
	 * And restart DCO Lock Detection
	*/
	scu->syspllcon0 = TMPL_SYSPLL_SRC | TMPL_SYSPLL_PWD | TMPL_SYSPLL_P | TMPL_SYSPLL_N;
	scu->syspllcon1 = TMPL_SYSPLL_K2_INIT;
	scu->syspllcon0 |= TMPL_SYSPLL_RESLD;
	Tmpl_BoardWaitBitSet(&scu->syspllstat, TMPL_SYSPLL_STAT_LOCK);
	
	/* Set up the Peripheral PLL:
	 * Power mode, and dividers (P, N, K2, K3)
	 * And restart DCO Lock Detection
	*/
	scu->perpllcon0 = TMPL_PERPLL_PWD | TMPL_PERPLL_P | TMPL_PERPLL_N;
	scu->perpllcon1 = TMPL_PERPLL_K2 | TMPL_PERPLL_K3;
	scu->perpllcon0 |= TMPL_PERPLL_RESLD;
	Tmpl_BoardWaitBitSet(&scu->perpllstat, TMPL_PERPLL_STAT_LOCK);
	
	/* Clock Control Unit:
	 * set up the clock distribution and the dividers for bus frequencies
	*/
	tmpVal_ccucon0 =	TMPL_CCUCON0_SRIDIV |
						TMPL_CCUCON0_FSIDIV	|
						TMPL_CCUCON0_FSI2DIV|
						TMPL_CCUCON0_STMDIV	|
						TMPL_CCUCON0_BBBDIV	|
						TMPL_CCUCON0_SPBDIV	|
						TMPL_CCUCON0_LPDIV	|
						TMPL_CCUCON0_GTMDIV;
	
	/* ccucon0 -- set value */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon0);
	scu->ccucon0 = tmpVal_ccucon0;
	Tmpl_BoardWaitValsEqual(&scu->ccucon0, tmpVal_ccucon0);

	/* ccucon1 -- set value */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon1);
	tmpVal_ccucon1 =	TMPL_CCUCON1_CLKSELQSPI	|
						TMPL_CCUCON1_QSPIDIV	|
						TMPL_CCUCON1_CLKSELMSC	|
						TMPL_CCUCON1_MSCDIV		|
						TMPL_CCUCON1_PLL1DIVDIS	|
						TMPL_CCUCON1_CLKSELMCAN	|
						TMPL_CCUCON1_MCANDIV;
	scu->ccucon1 = tmpVal_ccucon1;
	Tmpl_BoardWaitValsEqual(&scu->ccucon1, tmpVal_ccucon1);

	/* ccucon2 -- set value */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon2);
	tmpVal_ccucon2 =	TMPL_CCUCON2_CLKSELASCLINS	|
						TMPL_CCUCON2_ASCLINSDIV		|
						TMPL_CCUCON2_ASCLINFDIV;
	scu->ccucon2 = tmpVal_ccucon2;
	Tmpl_BoardWaitValsEqual(&scu->ccucon2, tmpVal_ccucon2);
	
	/* ccucon0 -- initialize an update */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon0);
	/* Request an update of the CCU */
	scu->ccucon0 = tmpVal_ccucon0 | TMPL_CCUCON0_UPDREQ;
	Tmpl_BoardWaitValsEqual(&scu->ccucon0, tmpVal_ccucon0);

	/* Select the PLL as the main clock source */
	tmpVal_ccucon0 |= TMPL_CCUCON0_CLKSEL;
	/* ccucon0 -- set value */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon0);
	scu->ccucon0 = tmpVal_ccucon0;
	Tmpl_BoardWaitValsEqual(&scu->ccucon0, tmpVal_ccucon0);
	
	/* ccucon0 -- initialize an update */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon0);
	/* Request an update of the CCU */
	scu->ccucon0 = tmpVal_ccucon0 | TMPL_CCUCON0_UPDREQ;
	Tmpl_BoardWaitValsEqual(&scu->ccucon0, tmpVal_ccucon0);
	
	/* 
	 * Ramp-up the frequency step-by-step.
	 * "After every frequency programming step a wait time is recommended
	 * until supply ripple caused by supply current transient is faded away"
	 */
#if (TMPL_SYSPLL_K2_INIT > TMPL_SYSPLL_K2)
	mk_uint32_t k2_tmp;
	for (k2_tmp = TMPL_SYSPLL_K2_INIT - 1; k2_tmp >= TMPL_SYSPLL_K2; k2_tmp--)
	{
		scu->syspllcon1 = k2_tmp;
		Tmpl_BoardWait(TMPL_FREQ_STBL_DELAY << 2);
	}
#endif
	
	Tmpl_BoardWait(TMPL_FREQ_STBL_DELAY << 7);
	
	/* ccucon0 -- initialize an update */
	Tmpl_BoardWaitForCCUCONIsUnlocked(&scu->ccucon0);
	/* Request an update of the CCU */
	scu->ccucon0 = tmpVal_ccucon0 | TMPL_CCUCON0_UPDREQ;
	Tmpl_BoardWaitValsEqual(&scu->ccucon0, tmpVal_ccucon0);

	MK_WriteSafetyEndinit(1);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
