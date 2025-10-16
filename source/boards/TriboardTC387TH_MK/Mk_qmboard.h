/* Mk_qmboard.h - board specific header file for Triboard
 * 
 * Contains definitions to be used by routines in Mk_board.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_qmboard.h 32972 2018-05-24 10:57:08Z mist9353 $
*/
#ifndef MK_QMBOARD_H
#define MK_QMBOARD_H

#include <Mk_board.h>
#include <Mk_board_leds.h>
#include <public/Mk_public_types.h>
#include <Mk_TRICORE_board_startup.h>

#ifndef MK_TS5_TEST
#ifdef OS_KERNEL_TYPE
#include <TRICORE/Os_defs_TRICORE.h>					/* QM-OS compatibility */
#endif
#endif

/*
 * Note: If you change TMPL_SYS_FREQ, update the NsToTicks and TicksToNs macros accordingly
*/
#ifndef TMPL_XTAL_FREQ
#define TMPL_XTAL_FREQ				20000000u			/* 20 MHz crystal frequency */
#endif
#define TMPL_SYS_FREQ				200000000u			/* CPU clock [Hz] */

/* Calclulate dividers/multipliers for setting up the PLL
 *
 * According to the formula: (f_osc * N) / (P * K2) = f_pll,
 * where f_osc = TMPL_XTAL_FREQ, and f_pll = TMPL_SYS_FREQ.
 *
 * P	- 3-bit input divider: divide 'f_osc' on PLL entance
 * N	- 7-bit feedback divider: PLL multiplication factor
 * K2	- 3-bit output divider: output to the CPUs
 * K3	- 3-bit output divider: output to some other peripherals
 *
 * check1: ((f_osc * N) / P) must be within 400MHz - 800MHz range (DCO frequency range)
*/
#if (TMPL_XTAL_FREQ==20000000u) && (TMPL_SYS_FREQ==200000000u)
/*
 * Input: f_osc = 20MHz
 * Output: f_pll = 200MHz
 * (20MHz * 30) / (1 * 3) = 200MHz
 * check1: ((20MHz * 30) / 1) = 600MHz (OK)
*/
#define TMPL_P						1u
#define TMPL_N						30u
#define TMPL_K2						3u
#define TMPL_K3						3u
#elif (TMPL_XTAL_FREQ==25000000u) && (TMPL_SYS_FREQ==200000000u)
#define TMPL_P						1u
#define TMPL_N						16u
#define TMPL_K2						2u
#define TMPL_K3						2u

/*
 * Note: 300MHz is the maximal clock speed for TC39x
*/
#elif (TMPL_XTAL_FREQ==20000000u) && (TMPL_SYS_FREQ==300000000u)
/* 
 * Input:	f_osc = 20MHz
 * Output:	f_pll = 300MHz
 * (20MHz * 30) / (1 * 2) = 180MHz
 * check1: ((20MHz * 30) / 1) = 600 (OK)
*/
#define TMPL_P						1u
#define TMPL_N						30u
#define TMPL_K2						2u
#define TMPL_K3						3u

#else
#error "No dividers are specified for the given TMPL_XTAL_FREQ and TMPL_SYS_FREQ"
#endif

#define TMPL_PLL0_FREQ_HZ	((TMPL_N * TMPL_XTAL_FREQ) / (TMPL_P * TMPL_K2))

/*
 * Fields in OSCCON
*/
#define TMPL_OSCCON_PLLLV			(0x1u << 1)			/* Oscillator for PLL Low Valid			*/
#define TMPL_OSCCON_OSCRES			(0x1u << 2)			/* Oscillator watchdog reset			*/
#define TMPL_OSCCON_PLLHV			(0x1u << 8)			/* Oscillator for PLL High Valid 		*/
#if (TMPL_XTAL_FREQ==20000000u)
#define TMPL_CCUCON_OSCVAL			(0x5u << 16)		/* 20 MHz reference clock				*/
#elif (TMPL_XTAL_FREQ==25000000u)
#define TMPL_CCUCON_OSCVAL			(0xau << 16)		/* 25 MHz reference clock				*/
#else
#error "Crystal clock not properly defined."
#endif
#define TMPL_OSCCON_MODE_MASK		(0x3u << 5)			/* 00 enables ext. osc; 11 disables 	*/
#define TMPL_OSCSTABLE				(TMPL_OSCCON_PLLLV | TMPL_OSCCON_PLLHV)

/*
 * Fields in System PLL
*/
#define TMPL_SYSPLL_SRC				(0x1u << 30)		/* Select OSC as the input clock		*/
#define TMPL_SYSPLL_PWD				(0x1u << 16)		/* Power Saving: 0 - sleep; 1 active	*/
#define TMPL_SYSPLL_P				((TMPL_P - 1) << 24)/* System PLL P divider					*/
#define TMPL_SYSPLL_N				((TMPL_N - 1) << 9)	/* System PLL N divider					*/
#define TMPL_SYSPLL_K2				(TMPL_K2 - 1)		/* System PLL K2 divider				*/

/* 
 * Definitions to enable step-by-step frequency ramp-up
 * It is recommended to have an initial PLL frequency value same or slightly higher than
 * the frequency of the back-up clock, which is the initial clock source on startup.
 * For us it means setting the K2 divider to 6 (5+1) (600 MHz / 6 = 100 MHz)
 * and lower it gradually, increasing the output clock frequency.
*/
#define TMPL_FREQ_STBL_DELAY		10000u				/* Idle loop iterations per step		*/
#if (TMPL_SYSPLL_K2 > 5u)
#define TMPL_SYSPLL_K2_INIT			TMPL_SYSPLL_K2		/* No ramp-up, divider is big enough	*/
#else
#define TMPL_SYSPLL_K2_INIT			5u					/* Initial value of K2 divider			*/
#endif

/*
 * Feilds in System PLL Status Register
*/
#define TMPL_SYSPLL_RESLD			(0x1u << 18)		/* Restart lock detection				*/
#define TMPL_SYSPLL_STAT_LOCK		(0x1u << 2)			/* 1 if PLL produces stable frequency	*/

/*
 * Fields in Peripheral PLL
*/
#define TMPL_PERPLL_PWD				(0x1u << 16)		/* Power Saving: 0 - sleep; 1 active	*/
#define TMPL_PERPLL_P				((TMPL_P - 1) << 24)/* Peripheral PLL P divider				*/
#define TMPL_PERPLL_N				((TMPL_N - 1) << 9)	/* Peripheral PLL N divider				*/
#define TMPL_PERPLL_K2				(TMPL_K2 - 1)		/* Peripheral PLL K2 divider			*/
#define TMPL_PERPLL_K3				((TMPL_K3 - 1) << 8)/* Peripheral PLL K3 divider			*/

/*
 * Fields in Peripheral PLL Status Register
*/
#define TMPL_PERPLL_RESLD			(0x1u << 18)		/* Restart lock detection				*/
#define TMPL_PERPLL_STAT_LOCK		(0x1u << 2)			/* 1 if PLL produces stable frequency	*/

/* Select clock.
*/
#define TMPL_CLKSEL_BACKUP		0u
#define TMPL_CLKSEL_PLL0		1u
#define TMPL_CLKSEL				TMPL_CLKSEL_PLL0
#define TMPL_CLKSRC0_FREQ_HZ	TMPL_PLL0_FREQ_HZ

/* Choose STM divider.
*/
#define TMPL_STMDIV				(TMPL_CLKSRC0_FREQ_HZ / BOARD_STM_FREQ_HZ)
/* Assert 1 <= TMPL_STMDIV < 16. */
#if (TMPL_STMDIV < 1)
#error "STM divider must fulfil '1 <= TMPL_STMDIV < 16'. It was less than 1."
#endif
#if (TMPL_STMDIV > 15)
#error "STM divider must fulfil '1 <= TMPL_STMDIV < 16'. It was greater than 15."
#endif
/* 7, 9, 11, 13, 14 are not allowed as STM dividers. */
#if (TMPL_STMDIV == 7)
#error "TMPL_STMDIV must not be one of _7_, 9, 11, 13, 14."
#endif
#if (TMPL_STMDIV == 9)
#error "TMPL_STMDIV must not be one of 7, _9_, 11, 13, 14."
#endif
#if (TMPL_STMDIV == 11)
#error "TMPL_STMDIV must not be one of 7, 9, _11_, 13, 14."
#endif
#if (TMPL_STMDIV == 13)
#error "TMPL_STMDIV must not be one of 7, 9, 11, _13_, 14."
#endif
#if (TMPL_STMDIV == 14)
#error "TMPL_STMDIV must not be one of 7, 9, 11, 13, _14_."
#endif


/*
 * Fields in the Clock Control Unit (defines clock
 * distribution and frequencies of the on-chip buses)
 * CCUCON0 reset value is 0x3512_0112
 *         shift values:    2221 1
 *                          8406 2840
 * CCUCON1 reset value is 0x1010_0302
 * CCUCON2 reset value is 0x0700_0101
*/
#define TMPL_CCUCON0_LCK			(       0x1u << 31)		/* Lock status							*/
#define TMPL_CCUCON0_UPDREQ			(       0x1u << 30)		/* Request an update of the CCU			*/
#define TMPL_CCUCON0_CLKSEL			(TMPL_CLKSEL << 28)		/* Src0=PLL0, Src1=(PLL1)/2, Src2=PLL2	*/
#define TMPL_CCUCON0_SRIDIV			(       0x1u <<  8)		/* SRI freq. = Src0 freq.				*/
#define TMPL_CCUCON0_FSIDIV			(       0x1u << 24)		/* FSI freq. = SRI freq.				*/
#define TMPL_CCUCON0_FSI2DIV		(       0x1u << 26)		/* FSI2 freq. = SRI freq.				*/
#define TMPL_CCUCON0_STMDIV			(TMPL_STMDIV <<  0)		/* STM frequency = Src0 / STMDIV		*/
#define TMPL_CCUCON0_BBBDIV			(       0x2u << 20)		/* Back Bone Bus, BBB_f = 1/2 src_f		*/
#define TMPL_CCUCON0_SPBDIV			(       0x2u << 16)		/* SPB freq. = Src0 / 2					*/
#define TMPL_CCUCON0_LPDIV			(       0x0u << 12)		/* Stopped - clock gated				*/
#define TMPL_CCUCON0_GTMDIV			(       0x2u <<  4)		/* GTM frequency = SrcGtm / 2			*/

#define TMPL_CCUCON1_LCK			(       0x1u << 31)		/* Lock status							*/
#define TMPL_CCUCON1_CLKSELQSPI		(       0x0u << 28)		/* Stopped - clock gated				*/
#define TMPL_CCUCON1_QSPIDIV		(       0x0u << 24)		/* Stopped - clock gated				*/
#define TMPL_CCUCON1_CLKSELMSC		(       0x0u << 20)		/* Stopped - clock gated				*/
#define TMPL_CCUCON1_MSCDIV			(       0x0u << 16)		/* Stopped - clock gated				*/
#define TMPL_CCUCON1_PLL1DIVDIS		(       0x0u <<  7)		/* if 1, PLL1 divider (/2) is bypassed	*/
#define TMPL_CCUCON1_CLKSELMCAN		(       0x0u <<  4)		/* Stopped - clock gated				*/
#define TMPL_CCUCON1_MCANDIV		(       0x0u <<  0)		/* Stopped - clock gated				*/

#define TMPL_CCUCON2_LCK			(       0x1u << 31)		/* Lock status							*/
#define TMPL_CCUCON2_CLKSELASCLINS	(       0x0u << 12)		/* Stopped - clock gated				*/
#define TMPL_CCUCON2_ASCLINSDIV		(       0x0u <<  8)		/* Stopped - clock gated				*/
#define TMPL_CCUCON2_ASCLINFDIV		(       0x0u <<  0)		/* Stopped - clock gated				*/


/* Perform sanity checks.
*/
#if (BOARD_STM_FREQ_HZ != (TMPL_CLKSRC0_FREQ_HZ / TMPL_STMDIV))
#error "STM clock frequency configuration is inconsistent."
#endif
#if (TMPL_SYS_FREQ != TMPL_CLKSRC0_FREQ_HZ)
#error "System clock frequency configuration is inconsistent."
#endif

/*!
 * OS_BoardNsToTicks() and OS_BoardTicksToNs()
 *
 * OS_BoardNsToTicks() converts nanoseconds (nS) to ticks. This macro must
 * compute entirely in the preprocessor, because it is used to initialise time
 * tables.
 *
*/
#define OS_BoardNsToTicks(ns)		MK_TimestampNsToTicks(ns)
#define OS_BoardTicksToNs(tik)		MK_TimestampTicksToNs(tik)

#ifndef MK_TS5_TEST
#ifdef OS_KERNEL_TYPE
#define OS_STM_PRESCALE				1					/* Prescaler (RMC) value				*/
#define OS_STM_CMPPOS0				0					/* Comparator 0 position (MSTART0)		*/
#define OS_STM_CMPPOS1				0					/* Comparator 1 position (MSTART1)		*/
#ifndef MK_ASM
#include <TRICORE/Os_TRICORE_stmconfig.h>
#endif
#endif
#endif

/* disable watchdog - remove or choose any other value to leave it enabled */
#define MK_BOARD_DISABLE_WATCHDOG	0xa4420810

/* This macro contains an endless loop that attempts to avoid a compiler warning on endless loops.
*/
#define TMPL_ENDLESSLOOP() \
	do \
	{ \
		mk_uint32_t confusion; \
		for(confusion=0u; confusion!=1u; confusion^=2u) \
		{ \
			/* Compiler hopefully does not recognize this as an endless loop */ \
		} \
	} while(0)

#endif

/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
