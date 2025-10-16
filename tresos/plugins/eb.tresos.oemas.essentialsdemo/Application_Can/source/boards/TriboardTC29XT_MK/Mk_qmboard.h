/* Mk_qmboard.h - board specific header file for Triboard
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_qmboard.h 23795 2016-06-18 10:36:22Z mist8519 $
*/
#ifndef MK_QMBOARD_H
#define MK_QMBOARD_H

#include <Mk_board.h>

/* All settings, defines, etc. which are used my the routines in Mk_board.c
 * should go into this header file.
*/
#include <public/Mk_public_types.h>
#include <Mk_TRICORE_board_startup.h>

/* QM-OS compatibility */
#ifndef MK_TS5_TEST
#ifdef OS_KERNEL_TYPE
#include <TRICORE/Os_defs_TRICORE.h>
#endif
#endif

/* 20 MHz crystal frequency.
*/
#define MK_XTAL_FREQ		20000000U

/* Select the desired CPU frequency from one of these values:
 * MK_SYS_FREQ == 200000000 yields 200 MHz CPU clock,
 * MK_SYS_FREQ == 180000000 yields 180 MHz CPU clock,
 * MK_SYS_FREQ == 150000000	yields 150 MHz CPU clock.
 *
 * The PLL must be programmed to achieve these frequencies.
 *
 * If any other frequency is required the correct PLL settings will need to be determined.
 * If you change the running frequency of the board, you must
 * also change the NsToTicks and TicksToNs macros below.
*/
#define MK_SYS_FREQ			180000000U			/* CPU clock [Hz] */

/* By default the SCU clocks the STM modules with f_source/2, whereat f_sys is the PLL's output in
 * this configuration (see register CCUCON1 field STMDIV).
 * If the user changes this during startup, the following macro needs to be adapted.
*/
#define MK_Fstm_FREQ			((MK_SYS_FREQ)/2U)

#if (MK_XTAL_FREQ==20000000U) && (MK_SYS_FREQ==200000000U)
/*
 * P    = 1; N    = 30; K2    = 3;
 *
 * Input to VCO is 20MHz/1 = 20 MHz.
 * PLL runs at 20MHz*30 = 600 MHz, which is within the 400 - 720MHz operating range.
 * Output is 600MHz/3 = 200 MHz.
 *
 * The macros MK_P, MK_N, MK_K1, MK_K2 and MK_K3 are the "true" values of P, N, K1, K2 and K3
*/
#define MK_P					1U
#define MK_N					30U
#define MK_K2					3U

#define MK_K1					1U
#define MK_K3					3U

#elif (MK_XTAL_FREQ==20000000U) && (MK_SYS_FREQ==180000000U)
/*
 * P    = 2; N    = 72; K2    = 4;
 * PDIV = 1; NDIV = 71; K2DIV = 3;
 *
 * Input to VCO is 20MHz/2 = 10 MHz.
 * PLL runs at 10MHz*72 = 720 MHz, which is within the 400 - 720MHz operating range.
 * Output is 720MHz/4 = 180 MHz.
 *
 * The macros MK_P, MK_N, MK_K1, MK_K2 and MK_K3 are the "true" values of P, N, K1, K2 and K3
*/
#define MK_P					2U
#define MK_N					72U
#define MK_K2					4U

#define MK_K1					1U
#define MK_K3					4U

#elif (MK_XTAL_FREQ==20000000U) && (MK_SYS_FREQ==150000000U)
/*
 * P = 2;  N = 60;  K2 = 4;
 *
 * Input to VCO is 20MHz/2 = 10 MHz.
 * PLL runs at 10MHz*60 = 600 MHz, which is within the 400 - 720MHz operating range.
 * Output is 600MHz/4 = 150 MHz.
 *
 * The macros MK_P, MK_N, MK_K1, MK_K2 and MK_K3 are the "true" values of P, N, K1, K2 and K3
*/
#define MK_P					2U
#define MK_N					60U
#define MK_K2					4U

#define MK_K1					1U
#define MK_K3					4U

#else
#error "You must define appropriate P, N, K1 and K2 values for this combination of crystal and CPU speed."
#endif

#if defined(MK_P) && defined(MK_N) && defined(MK_K1) && defined(MK_K2)
/*
 * These definitions should work for all valid combinations of P, N, K1 and K2.
 * The macros represent the base values of PLLCON0 and PLLCON1; extra bits that need
 * to be set and then cleared in order to kick-start the PLL are added by software in board.c
 *
 * The bit OSCDISCDIS is set.
 *
 * Besides PLL settings, the clock dividers inside the clock control unit (CCU) are set up.
*/
#define MK_QMBOARD_PLLCON0		(     ((MK_P - 1u) << 24) 		\
									| ((MK_N - 1u) << 9) 		\
									| TMPL_PLLCON0_OSCDISCDIS	\
									| TMPL_PLLCON0_PLLPWD		\
								)
#define MK_QMBOARD_PLLCON1		(     ((MK_K1 - 1u) << 16)	\
									| ((MK_K3 - 1u) <<  8)	\
									| (MK_K2 - 1u)			\
								)

#else
#error "The crystal versus CPU speed selection above does not set the divider macros correctly!"
#endif

#define TMPL_FSI_DIV	2u	/* max. FSI freq is 100 MHz */
#define TMPL_FSI2_DIV	1u

#define TMPL_CCUCON0_BAUD1DIV		(0u  <<  0)
#define TMPL_CCUCON0_BAUD2DIV		(0u  <<  4)
#define TMPL_CCUCON0_SRIDIV			(1u  <<  8)
#define TMPL_CCUCON0_LPDIV			(0u  <<  12)
#define TMPL_CCUCON0_SPBDIV			(2u  <<  16)
#define TMPL_CCUCON0_FSI2DIV		(TMPL_FSI2_DIV <<  20)
#define TMPL_CCUCON0_FSIDIV			(TMPL_FSI_DIV  <<  24)

#define TMPL_CCUCON1_CANDIV			(1u  <<  0)
#define TMPL_CCUCON1_ERAYDIV		(1u  <<  4)
#define TMPL_CCUCON1_STMDIV			(2u  <<  8)
#define TMPL_CCUCON1_GTMDIV			(2u  <<  12)
#define TMPL_CCUCON1_ETHDIV			(0u  <<  16)
#define TMPL_CCUCON1_ASCLINFDIV		(0u  <<  20)
#define TMPL_CCUCON1_ASCLINSDIV		(0u  <<  24)

#define MK_QMBOARD_CCUCON0	\
( \
	  TMPL_CCUCON0_BAUD1DIV \
	| TMPL_CCUCON0_BAUD2DIV \
	| TMPL_CCUCON0_SRIDIV \
	| TMPL_CCUCON0_LPDIV \
	| TMPL_CCUCON0_SPBDIV \
	| TMPL_CCUCON0_FSI2DIV \
	| TMPL_CCUCON0_FSIDIV \
	| TMPL_CCUCON0_CLKSEL_FPLL \
)

#define MK_QMBOARD_CCUCON1	\
( \
	  TMPL_CCUCON1_CANDIV \
	| TMPL_CCUCON1_ERAYDIV \
	| TMPL_CCUCON1_STMDIV \
	| TMPL_CCUCON1_GTMDIV \
	| TMPL_CCUCON1_ETHDIV \
	| TMPL_CCUCON1_ASCLINFDIV \
	| TMPL_CCUCON1_ASCLINSDIV \
	| TMPL_CCUCON1_INSEL_FOSC0 \
)

/*!
 * OS_BoardNsToTicks() and OS_BoardTicksToNs()
 *
 * OS_BoardNsToTicks() converts nanoseconds (nS) to ticks. This macro must
 * compute entirely in the preprocessor, because it is used to initialise time
 * tables.
 *
*/
#define OS_BoardNsToTicks(ns)	MK_TimestampNsToTicks(ns)
#define OS_BoardTicksToNs(tik)	MK_TimestampTicksToNs(tik)

#ifndef MK_TS5_TEST
#ifdef OS_KERNEL_TYPE
#define OS_STM_PRESCALE		1	/* Prescaler (RMC) value */
#define OS_STM_CMPPOS0		0	/* Comparator 0 position (MSTART0) */
#define OS_STM_CMPPOS1		0	/* Comparator 1 position (MSTART1) */
#ifndef MK_ASM
#include <TRICORE/Os_TRICORE_stmconfig.h>
#endif
#endif
#endif


/* disable watchdog - remove or choose any other value to leave it enabled */
#define MK_BOARD_DISABLE_WATCHDOG	0xa4420810


/* GPIO port configuration structure; used for LED access */
#ifndef MK_ASM
typedef	struct mk_qmtricoreport_s
{
		/*	This module	has	no module	header!
		*/
		mk_reg32_t			p_out;						/* Output */
		mk_reg32_t			p_omr;						/* Output modification */
		mk_reg32_t			reserved1[2];
		mk_reg32_t			p_iocr[4];					/* I/O control 0,4,8 and 12	(!)	*/
		mk_reg32_t			reserved2[1];
		mk_reg32_t			p_in;						/* Input */
		mk_reg32_t			reserved3[6];
		mk_reg32_t			p_pdr[2];					/* Pad driver mode */
		mk_reg32_t			reserved4[2];
		mk_reg32_t			p_esr;						/* Emergency stop (not all ports) */
		mk_reg32_t			reserved5[43];
}	mk_qmtricoreport_t;
#endif


/* LED there be light */
#define	MK_QM_P33		((mk_qmtricoreport_t *)0xf003d300)[0]
#define	MK_QM_LEDMASK	0xffu
#define	MK_QM_LEDSHIFT	6

#define	LEDS_SET(x)\
			do {					\
					MK_QM_P33.p_out = (MK_QM_P33.p_out & ~(MK_QM_LEDMASK<<MK_QM_LEDSHIFT)) \
						| ((~(x)& MK_QM_LEDMASK)<<MK_QM_LEDSHIFT); \
			} while (0)

#define	LEDS_INIT()\
			do {	\
					MK_QM_P33.p_out |= (MK_QM_LEDMASK << MK_QM_LEDSHIFT);\
					MK_QM_P33.p_iocr[1] = 0x80801010u;\
					MK_QM_P33.p_iocr[2] = 0x80808080u;\
					MK_QM_P33.p_iocr[3] = 0x10108080u;\
			} while (0)

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
