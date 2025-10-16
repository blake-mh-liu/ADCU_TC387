/* Mk_TRICORE_board_pll_tc3xx.h - Tricore PLL module description for the "tc3xx" variant.
 *
 * This file contains a minimal description of Tricore's clock configuration registers (the
 * variant used on the TC3xx "Aurix" processors). It is part of the SCU module.
 *
 * This file only provides the addresses and and bitmasks of the SCU
 * registers that are actually used in the PLL configuration template
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_pll_tc3xx.h 29747 2017-07-14 10:48:04Z aniv261689 $
*/
#ifndef MK_TRICORE_BOARD_PLL_TC3XX_H
#define MK_TRICORE_BOARD_PLL_TC3XX_H

#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

/* 
 * Per CPU watch-dog timer control and status registers:
 * WDTCPUxCON0, WDTCPUxCON1, WDTCPUxSR
*/
struct mk_tricore_wdt_s
{
	mk_reg32_t con0;			/* base+0+i*12	: CPUi WDT Control Register 0					*/
	mk_reg32_t con1;			/* base+4+i*12	: CPUi WDT Control Register 1					*/
	mk_reg32_t sr;				/* base+8+i*12	: CPUi WDT Status Register						*/
};
typedef struct mk_tricore_wdt_s mk_tricore_wdt_t;

/* 
 * TRICORE TC3xx SCU memory layout
 * All names correspond to AURIX TC3xx Target specification v.2.0.1
 * with the exceptions of:	WDTCPUxCON0, WDTCPUxCON1, WDTCPUxSR,
 * which are accessed as:	wdtcpu[i]->con0, wdtcpu[i]->con1, wdtcpu[i]->sr
*/
struct mk_tricore_scu_s			/* Base address	: 0xF0036000									*/
{
	mk_reg32_t padding_1[2];	/* 0xF0036000	: Reserved space								*/
	mk_reg32_t id;				/* 0xF0036008	: Identification register						*/
	mk_reg32_t padding_2;		/* 0xF003600C	: Reserved space								*/
	mk_reg32_t osccon;			/* 0xF0036010	: OSC Control Register							*/
	mk_reg32_t syspllstat;		/* 0xF0036014	: System PLL Status Register					*/
	mk_reg32_t syspllcon0;		/* 0xF0036018	: System PLL Configuration Register 0			*/
	mk_reg32_t syspllcon1;		/* 0xF003601C	: System PLL Configuration Register 1			*/
	mk_reg32_t syspllcon2;		/* 0xF0036020	: System PLL Configuration Register 2			*/
	mk_reg32_t perpllstat;		/* 0xF0036024	: Peripheral PLL Status Register				*/
	mk_reg32_t perpllcon0;		/* 0xF0036028	: Peripheral PLL Configuration Register 0		*/
	mk_reg32_t perpllcon1;		/* 0xF003602C	: Peripheral PLL Configuration Register 1		*/
	mk_reg32_t ccucon0;			/* 0xF0036030	: CCU Clock Control Register 0					*/
	mk_reg32_t ccucon1;			/* 0xF0036034	: CCU Clock Control Register 1					*/
	mk_reg32_t fdr;				/* 0xF0036038	: Fractional Divider Degister					*/
	mk_reg32_t extcon;			/* 0xF003603C	: External Clock Control Register				*/
	mk_reg32_t ccucon2;			/* 0xF0036040	: CCU Clock Control Register 2					*/
	mk_reg32_t padding_3[3];	/* 0xF0036044	: Reserved space								*/
	mk_reg32_t rststat;			/* 0xF0036050	: Reset Status Register							*/
	mk_reg32_t padding_4;		/* 0xF0036054	: Reserved space								*/
	mk_reg32_t rstcon;			/* 0xF0036058	: Reset Configuration Register					*/
	mk_reg32_t arstdis;			/* 0xF003605C	: Application Reset Disable Register			*/
	mk_reg32_t swrstcon;		/* 0xF0036060	: Software Reset Configuration Register			*/
	mk_reg32_t rstcon2;			/* 0xF0036064	: Reset Configuration Register 2				*/
	mk_reg32_t rstcon3;			/* 0xF0036068	: Reset Configuration Register 3				*/
	mk_reg32_t padding_5;		/* 0xF003606C	: Reserved space								*/
	mk_reg32_t esrcfg1;			/* 0xF0036070	: ESR1 Input Configuration Register				*/
	mk_reg32_t esrcfg2;			/* 0xF0036074	: ESR2 Input Configuration Register				*/
	mk_reg32_t esrocfg;			/* 0xF0036078	: ESR Output Configuration Register				*/
	mk_reg32_t syscon;			/* 0xF003607C	: System Control Register						*/
	mk_reg32_t ccucon6;			/* 0xF0036080	: CCU Clock Control Register					*/
	mk_reg32_t ccucon7;			/* 0xF0036084	: CCU Clock Control Register					*/
	mk_reg32_t ccucon8;			/* 0xF0036088	: CCU Clock Control Register					*/
	mk_reg32_t ccucon9;			/* 0xF003608C	: CCU Clock Control Register					*/
	mk_reg32_t ccucon10;		/* 0xF0036090	: CCU Clock Control Register					*/
	mk_reg32_t ccucon11;		/* 0xF0036094	: CCU Clock Control Register					*/
	mk_reg32_t padding_6;		/* 0xF0036098	: Reserved space								*/
	mk_reg32_t pdr;				/* 0xF003609C 	: ESR Pad Driver Mode Register					*/
	mk_reg32_t iocr;			/* 0xF00360A0 	: Input/Output Control Register					*/
	mk_reg32_t out;				/* 0xF00360A4 	: ESR Output Register							*/
	mk_reg32_t omr;				/* 0xF00360A8 	: ESR Output Modification Register				*/
	mk_reg32_t in;				/* 0xF00360AC 	: ESR Input Register							*/
	mk_reg32_t padding_7[4];	/* 0xF00360B0	: Reserved space								*/
	mk_reg32_t ststat;			/* 0xF00360C0 	: Start-up Status Register						*/
	mk_reg32_t padding_8;		/* 0xF00360C4	: Reserved space								*/
	mk_reg32_t pmcsr3;			/* 0xF00360C8 	: Power Management Control & Status Register 3	*/
	mk_reg32_t pmcsr4;			/* 0xF00360CC 	: Power Management Control & Status Register 4	*/
	mk_reg32_t pmcsr5;			/* 0xF00360D0 	: Power Management Control & Status Register 5	*/
	mk_reg32_t pmcsr0;			/* 0xF00360D4 	: Power Management Control & Status Register 0	*/
	mk_reg32_t pmcsr1;			/* 0xF00360D8 	: Power Management Control & Status Register 1	*/
	mk_reg32_t pmcsr2;			/* 0xF00360DC 	: Power Management Control & Status Register 2	*/
	mk_reg32_t padding_9;		/* 0xF00360E0	: Reserved space								*/
	mk_reg32_t pmstat0;			/* 0xF00360E4 	: Power Management Status Register 0			*/
	mk_reg32_t pmswcr1;			/* 0xF00360E8 	: Standby & Wake-up Control Register 1			*/
	mk_reg32_t padding_10[4];	/* 0xF00360EC	: Reserved space								*/
	mk_reg32_t emsr;			/* 0xF00360FC 	: Emergency Stop Register						*/
	mk_reg32_t padding_11[8];	/* 0xF0036100	: Reserved space								*/
	mk_reg32_t trapdis1;		/* 0xF0036120 	: Trap Disable Register 1						*/
	mk_reg32_t trapstat;		/* 0xF0036124 	: Trap Status Register							*/
	mk_reg32_t trapset;			/* 0xF0036128 	: Trap Set Register								*/
	mk_reg32_t trapclr;			/* 0xF003612C 	: Trap Clear Register							*/
	mk_reg32_t trapdis0;		/* 0xF0036130 	: Trap Disable Register 0						*/
	mk_reg32_t lclcon0;			/* 0xF0036134 	: LCL CPU0 Control Register						*/
	mk_reg32_t lclcon1;			/* 0xF0036138 	: LCL CPU1 Control Register						*/
	mk_reg32_t lcltest;			/* 0xF003613C 	: LCL Test Register								*/
	mk_reg32_t chipid;			/* 0xF0036140 	: Chip Identification Register					*/
	mk_reg32_t manid;			/* 0xF0036144 	: Manufacturer Identification Register			*/
	mk_reg32_t padding_12[7];	/* 0xF0036148	: Reserved space								*/
	mk_reg32_t lbistctrl0;		/* 0xF0036164 	: Logic BIST Control Register 0					*/
	mk_reg32_t lbistctrl1;		/* 0xF0036168 	: Logic BIST Control Register 1					*/
	mk_reg32_t lbistctrl2;		/* 0xF003616C 	: Logic BIST Control Register 2					*/
	mk_reg32_t lbistctrl3;		/* 0xF0036170 	: Logic BIST Control Register 3					*/
	mk_reg32_t padding_13[6];	/* 0xF0036174	: Reserved space								*/
	mk_reg32_t pdisc;			/* 0xF003618C 	: Pad Disable Control Register					*/
	mk_reg32_t padding_14[2];	/* 0xF0036190	: Reserved space								*/
	mk_reg32_t pmtrcsr0;		/* 0xF0036198 	: Pow. Management Transit. Control & Status 0	*/
	mk_reg32_t pmtrcsr1;		/* 0xF003619C 	: Pow. Management Transit. Control & Status 1	*/
	mk_reg32_t pmtrcsr2;		/* 0xF00361A0 	: Pow. Management Transit. Control & Status 2	*/
	mk_reg32_t pmtrcsr3;		/* 0xF00361A4 	: Pow. Management Transit. Control & Status 3	*/
	mk_reg32_t padding_15[14];	/* 0xF00361A8	: Reserved space								*/
	mk_reg32_t ovcenable;		/* 0xF00361E0 	: Overlay Enable Register						*/
	mk_reg32_t ovccon;			/* 0xF00361E4 	: Overlay Control Register						*/
	mk_reg32_t padding_16[9];	/* 0xF00361E8	: Reserved space								*/
	mk_reg32_t eifilt;			/* 0xF003620C 	: External Input Filter Register				*/
	mk_reg32_t eicr_0;			/* 0xF0036210 	: External Input Channel Register 0				*/
	mk_reg32_t eicr_1;			/* 0xF0036214 	: External Input Channel Register 1				*/
	mk_reg32_t eicr_2;			/* 0xF0036218 	: External Input Channel Register 2				*/
	mk_reg32_t eicr_3;			/* 0xF003621C 	: External Input Channel Register 3				*/
	mk_reg32_t eifr;			/* 0xF0036220 	: External Input Flag Register					*/
	mk_reg32_t fmr;				/* 0xF0036224 	: Flag Modification Register					*/
	mk_reg32_t pdrr;			/* 0xF0036228 	: Pattern Detection Result Register				*/
	mk_reg32_t igcr0;			/* 0xF003622C 	: Flag Gating Register 0						*/
	mk_reg32_t igcr1;			/* 0xF0036230 	: Flag Gating Register 1						*/
	mk_reg32_t igcr2;			/* 0xF0036234 	: Flag Gating Register 2						*/
	mk_reg32_t igcr3;			/* 0xF0036238 	: Flag Gating Register 3						*/
	mk_reg32_t padding_17[4];	/* 0xF003623C	: Reserved space								*/
	mk_tricore_wdt_t wdtcpu[6];	/* 0xF003624C	: Per CPU WDT Structure	(12 byte  * 6 CPUs)		*/
	mk_reg32_t padding_18[2];	/* 0xF0036294	: Reserved space								*/
	mk_reg32_t eicon0;			/* 0xF003629C 	: ENDINIT Global Control Register 0				*/
	mk_reg32_t eicon1;			/* 0xF00362A0 	: ENDINIT Global Control Register 1				*/
	mk_reg32_t eisr;			/* 0xF00362A4 	: ENDINIT Timeout Counter Status Register		*/
	mk_reg32_t wdtscon0;		/* 0xF00362A8 	: System WDT Control Register 0					*/
	mk_reg32_t wdtscon1;		/* 0xF00362AC 	: System WDT Control Register 1					*/
	mk_reg32_t wdtssr;			/* 0xF00362B0 	: System WDT Status Register					*/
	mk_reg32_t seicon0;			/* 0xF00362B4 	: Safety ENDINIT Control Register 0				*/
	mk_reg32_t seicon1;			/* 0xF00362B8 	: Safety ENDINIT Control Register 1				*/
	mk_reg32_t seisr;			/* 0xF00362BC 	: Safety ENDINIT Timeout Status Register		*/
	mk_reg32_t padding_19[76];	/* 0xF00362C0	: Reserved space								*/
	mk_reg32_t accen11;			/* 0xF00363F0 	: Access Enable Register 11						*/
	mk_reg32_t accen10;			/* 0xF00363F4 	: Access Enable Register 10						*/
	mk_reg32_t accen01;			/* 0xF00363F8 	: Access Enable Register 01						*/
	mk_reg32_t accen00;			/* 0xF00363FC 	: Access Enable Register 00						*/
};
typedef struct mk_tricore_scu_s mk_tricore_scu_t;


/* Common Field for all CCUCONx registers */
#define TMPL_CCUCON_LCK_LOCKED		0x80000000u
#define TMPL_CCUCON_UP				0x40000000u

/* Fields in CCUCON0 */
#define TMPL_CCUCON0_CLKSEL_MASK	0x30000000u
#define TMPL_CCUCON0_CLKSEL_FPLL	0x10000000u

/* Fields in CCUCON1 */
#define TMPL_CCUCON1_INSEL_MASK		0x30000000u
#define TMPL_CCUCON1_INSEL_FOSC0	0x10000000u

#ifndef MK_ASM
void Tmpl_SetupClocks(void);
#endif


#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
