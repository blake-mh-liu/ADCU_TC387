/* Os_TRICORE_pwr.h - Tricore PWR module description
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/*	This file contains a description of Tricore's PWR module which
 *	contains the PLL control registers, watchdog, etc. On some variants
 *	this module is called the System Control Unit (SCU)
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * The type definition is used in macro to refer type specific address.
*/

#ifndef OS_TRICORE_PWR_H
#define OS_TRICORE_PWR_H

#include <Os_types.h>
#include <Os_usuffix.h>
#include <TRICORE/Os_TRICORE_core.h>
#include <TRICORE/Os_TRICORE_aurix_wdt.h>
#include <TRICORE/Os_TRICORE_module.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OS_N_CORES_MAX
#error "OS_N_CORES_MAX is needed for the definition of os_tricorepwr_s"
#endif

#ifndef OS_ASM

/* Deviation MISRAC2012-1 */
typedef struct os_tricorepwr_s os_tricorepwr_t;
#if OS_TRICOREARCH == OS_TRICOREARCH_16EP
/* This is used for all the Aurix (TC2x) processors */

struct os_tricorepwr_s
{
	os_tricoremodule_t	pwr_module_hdr;

	os_reg32_t		reserved1[1];		/* 0xC */
	os_reg32_t		pwr_osccon;			/* 0x10 OSC Control */
	os_reg32_t		pwr_pllstat;		/* 0x14	PLL Status */
	os_reg32_t		pwr_pllcon[3];		/* 0x18	PLL Configuration 0-2 */
	os_reg32_t		pwr_plleraystat;	/* 0x24	PLL_ERAY Status */
	os_reg32_t		pwr_plleraycon[2];	/* 0x28 PLL_ERAY Configuration 0 and 1 */
	os_reg32_t		pwr_ccucon[2];		/* 0x30	CCU Control 0 and 1 */
	os_reg32_t		pwr_fdr;			/* 0x38	Fractional Divider */
	os_reg32_t		pwr_extcon;			/* 0x3C	External Clock Control */
	os_reg32_t		pwr_ccucon_2[4];	/* 0x40 CCU Control 2, 3, 4 and 5 */
	os_reg32_t		pwr_rststat;		/* 0x50	Reset Status */
	os_reg32_t		reserved3[1];		/* 0x54 */
	os_reg32_t		pwr_rstcon;			/* 0x58 Reset CON */
	os_reg32_t		pwr_arstdis;		/* 0x5C	Application Reset Disable */
	os_reg32_t		pwr_swrstcon;		/* 0x60	Software Reset Configuration */
	os_reg32_t		pwr_rstcon2;		/* 0x64	Additional reset control */
	os_reg32_t		reserved4[1];		/* 0x68 */
	os_reg32_t		pwr_evrrstcon;		/* 0x6C EVR Reset Control */
	os_reg32_t		pwr_esrcfg[2];		/* 0x70 ESR0 and 1 Configuration */
	os_reg32_t		pwr_esrocfg;		/* 0x78 ESR Reset Output Configuration */
	os_reg32_t		pwr_syscon;			/* 0x7C System Control */

	os_reg32_t		pwr_ccucon6;		/* 0x80 CCU Control 6 */
#if (OS_N_CORES_MAX >= 2u)
	os_reg32_t		pwr_ccucon7;		/* 0x84 CCU Control 7 */
#endif
#if (OS_N_CORES_MAX >= 3u)
	os_reg32_t		pwr_ccucon8;		/* 0x88 CCU Control 7 */
#endif
#if (OS_N_CORES_MAX < 3u)
	os_reg32_t		reserved5[3u-(OS_N_CORES_MAX)];	/* 0x84/0x88 */
#endif

	os_reg32_t		pwr_ccucon9;		/* 0x8C CCU Control 9 */
	os_reg32_t		reserved5_1[3];		/* 0x90 */

	os_reg32_t		pwr_pdr;			/* 0x9C Pad Driver Mode */
	os_reg32_t		pwr_iocr;			/* 0xA0 Input/Output Control */
	os_reg32_t		pwr_out;			/* 0xA4	Output */
	os_reg32_t		pwr_omr;			/* 0xA8 Output Modification */
	os_reg32_t		pwr_in;				/* 0xAC	Input */
	os_reg32_t		pwr_evrstat;		/* 0xB0	EVR Status */
	os_reg32_t		reserved6[1];		/* 0xB4 */
	os_reg32_t		pwr_evr13con;		/* 0xB8	EVR13 Control */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		reserved18;			/* 0xBC */
#else
	os_reg32_t		pwr_evr33con;		/* 0xBC	EVR33 Control */
#endif

	os_reg32_t		pwr_ststat;			/* 0xC0 Start-up Status */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		reserved17;			/* 0xC4 */
#else
	os_reg32_t		pwr_stcon;			/* 0xC4	Start-up Configuration */
#endif

	os_reg32_t		pwr_pmswcr0;		/* 0xC8	Standby and Wakeup Control 0 */
	os_reg32_t		pwr_pmswstat;		/* 0xCC	Standby and Wakeup Status */
	os_reg32_t		pwr_pmswstatclr;	/* 0xD0 Standby and Wakeup Status Clear */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		pwr_pmcsr[1];		/* 0xD4 CPU0 Power Management Control and Status */
	os_reg32_t		reserved19[2];		/* 0xD8 */
#else
	os_reg32_t		pwr_pmcsr[3];		/* 0xD4 CPU0, 1 and 2 Power Management Control and Status */
#endif

	os_reg32_t		pwr_dtsstat;		/* 0xE0	Die Temperature Sensor Status */
	os_reg32_t		pwr_dtscon;			/* 0xE4 Die Temperature Sensor Control */
	os_reg32_t		pwr_pmswcr1;		/* 0xE8 Standby and Wakeup Control 1 */
	os_reg32_t		reserved7[1];		/* 0xEC */
	os_tricore_aurix_wdt_t pwr_swdt;	/* 0xF0 Safety WDT */
	os_reg32_t		pwr_emsr;			/* 0xFC Emergency Stop */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_tricore_aurix_wdt_t pwr_wdt[1];	/* 0x100 CPU WDT module */
	os_reg32_t		reserved20[6];		/* 0x10C */
#else
	os_tricore_aurix_wdt_t pwr_wdt[3];	/* 0x100 3 CPU WDT modules */
#endif

	os_reg32_t		pwr_trapstat;		/* 0x124 Trap Status */
	os_reg32_t		pwr_trapset;		/* 0x128 Trap Set */
	os_reg32_t		pwr_trapclr;		/* 0x12C Trap Clear */
	os_reg32_t		pwr_trapdis;		/* 0x130 Trap Disable */
	os_reg32_t		pwr_lclcon[2];		/* 0x134 CPU0 and 1 Lockstep Control */
	os_reg32_t		pwr_lcltest;		/* 0x13C Lockstep Test */
	os_reg32_t		pwr_chipid;			/* 0x140 Chip Identification */
	os_reg32_t		pwr_manid;			/* 0x144 Manufacture Identification */
	os_reg32_t		reserved8[7];		/* 0x148 */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		pwr_lbistctrl[3];	/* 0x164 Logic BIST Control 0, 1 and 2 */
	os_reg32_t		reserved9[9];		/* 0x170 */
#else
	os_reg32_t		pwr_lbistctrl[2];	/* 0x164 Logic BIST Control 0 and 1 */
	os_reg32_t		reserved9[10];		/* 0x16C */
#endif

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		reserved16;			/* 0x194 */
#else
	os_reg32_t		pwr_ccuconsm;		/* 0x194 CCU Control Security Monitor */
#endif

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		reserved10[1];		/* 0x198 */
	os_reg32_t		pwr_evradcstat;		/* 0x19C EVR ADC Status */
#else
	os_reg32_t		reserved10[2];		/* 0x198 */
#endif

	os_reg32_t		pwr_evruvmon;		/* 0x1A0 EVR Undervoltage Monitor */
	os_reg32_t		pwr_evrovmon;		/* 0x1A4 EVR Overvoltage Monitor */
	os_reg32_t		pwr_evrmonctrl;		/* 0x1A8 EVR Monitor Control */
	os_reg32_t		reserved11[1];		/* 0x1AC */
	os_reg32_t		pwr_evrsdctrl1;		/* 0x1B0 EVR SD Control 1 */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		pwr_evrsdctrl2;		/* 0x1B4 EVR SD Control 2 */
	os_reg32_t		pwr_evrsdctrl3;		/* 0x1B8 EVR SD Control 3 */
	os_reg32_t		reserved12[2];		/* 0x1BC */
	os_reg32_t		pwr_evrsdcoeff2;	/* 0x1C4 EVR SD Coefficient 2 */
	os_reg32_t		reserved12_1[5];	/* 0x1C8 */
	os_reg32_t		pwr_pmswutcnt;		/* 0x1DC Standby WUT Count */
#else
	os_reg32_t		reserved12[11];		/* 0x1B4 */
#endif

	os_reg32_t		pwr_ovcenable;		/* 0x1E0 Overlay Enable */
	os_reg32_t		pwr_ovccon;			/* 0x1E4 Overlay Control */
	os_reg32_t		reserved13[10];		/* 0x1E8 */
	os_reg32_t		pwr_eicr[4];		/* 0x210 External Input Channel 0, 1, 2 and 3 */
	os_reg32_t		pwr_eifr;			/* 0x220 External Input Flag */
	os_reg32_t		pwr_fmr;			/* 0x224 Flag Modification */
	os_reg32_t		pwr_pdrr;			/* 0x228 Pattern Detection Result */
	os_reg32_t		pwr_igcr[4];		/* 0x22C Interrupt Gating 0, 1, 2 and 3 */
	os_reg32_t		reserved14[1];		/* 0x23C */
	os_reg32_t		pwr_dtslim;			/* 0x240 Die Temperature Sensor Limit */

#if (OS_CPU == OS_TC23XL) || (OS_CPU == OS_TC22XL)
	os_reg32_t		reserved15[47];		/* 0x244 */
	os_reg32_t		pwr_pmswcr3;		/* 0x300 Standby and Wakeup Control 3 */
	os_reg32_t		reserved15_1[61];	/* 0x304 */
#else
	os_reg32_t		reserved15[109];	/* 0x244 */
#endif

	os_reg32_t		pwr_accen1;			/* 0x3F8 Access Enable 1 */
	os_reg32_t		pwr_accen0;			/* 0x3FC Access Enable 0 */
};

#elif OS_TRICOREARCH == OS_TRICOREARCH_162
/* This is used for newer (TC3x) processors */

struct os_tricorepwr_s
{
	os_tricoremodule_t	pwr_module_hdr;

	os_reg32_t		reserved1[1];		/* 0xC */
	os_reg32_t		pwr_osccon;			/* 0x10 OSC Control */
	os_reg32_t		pwr_pllstat;		/* 0x14	PLL Status */
	os_reg32_t		pwr_pllcon[3];		/* 0x18	PLL Configuration 0-2 */
	os_reg32_t		unused1[3];			/* 0x24 registers not used by OS */
	os_reg32_t		pwr_ccucon0;		/* 0x30	CCU Control 0 */
	os_reg32_t		pwr_ccucon1;		/* 0x34	CCU Control 1 */
	os_reg32_t		unused2[2] ;		/* 0x38 registers not used by OS */
	os_reg32_t		pwr_ccucon2;	    /* 0x40 CCU Control 2 */
	os_reg32_t		unused3[14];		/* 0x44 registers not used by OS */
	os_reg32_t		pwr_syscon;			/* 0x7C System Control */
	os_reg32_t		pwr_ccucon6;		/* 0x80 CCU Control 6 */
	os_reg32_t		pwr_ccucon7;		/* 0x84 CCU Control 7 */
	os_reg32_t		pwr_ccucon8;		/* 0x88 CCU Control 8 */
	os_reg32_t		pwr_ccucon9;		/* 0x8C CCU Control 9 */
	os_reg32_t		pwr_ccucon10;		/* 0x90 CCU Control 10 */
	os_reg32_t		pwr_ccucon11;		/* 0x94 CCU Control 11 */
	os_reg32_t		unused4[35];		/* 0x98 registers not used by OS */
	os_reg32_t		pwr_trapstat;		/* 0x124 Trap Status */
	os_reg32_t		pwr_trapset;		/* 0x128 Trap Set */
	os_reg32_t		pwr_trapclr;		/* 0x12C Trap Clear */
	os_reg32_t		pwr_trapdis;		/* 0x130 Trap Disable */
	os_reg32_t		unused5[70];		/* 0x134 registers not used by OS */
	os_tricore_aurix_wdt_t pwr_wdt[6];	/* 0x24c 6 CPU WDT modules */
	os_reg32_t		unused6[5];			/* 0x294 registers not used by OS */
	os_tricore_aurix_wdt_t pwr_swdt;	/* 0x2A8 System WDT */
};

#elif OS_TRICOREARCH == OS_TRICOREARCH_18
/* This is used for TC4xx processors */

typedef struct os_tricoretrapsetclr_s os_tricoretrapsetclr_t;
struct os_tricoretrapsetclr_s
{
	os_reg32_t	setclren;	/* 0x0 Set/Clr Enable register */
	os_reg32_t	set;		/* 0x4 Set register */
	os_reg32_t	clr;		/* 0x8 Clear register */
};

struct os_tricorepwr_s
{
	os_tricoremodule_t		pwr_module_hdr;
	os_reg32_t				reserved1[3];			/* 0xC */
	os_reg32_t				pwr_prote;				/* 0x18 PROT register Endinit */
	os_reg32_t				pwr_protse;				/* 0x1C PROT register safe Endinit */
	os_reg32_t				pwr_protcse;			/* 0x20 PROT register Cyber-Secure Endinit */
	os_reg32_t				pwr_protcsae;			/* 0x24 PROT register Cyber-Secure APU Endinit */
	os_tricoreaccen_t		pwr_accennom;			/* 0x28 ACCENOM */
	os_tricoreaccen_t		pwr_accengrp[4];		/* 0x48 ACCENGRP */
	os_tricoreaccen_t		pwr_accencs;			/* 0xC8 ACCENCS */
	os_reg32_t				pwr_trapctrl;			/* 0xE8 Trap control for CPU 0-5 */
	os_tricoretrapsetclr_t	pwr_trapsetclr[4];		/* 0xEC Trap SET/CLR for CPU 0-5 */
	os_reg32_t				pwr_trapstat;			/* 0x11C Trap status for CPU 0-5 */
	os_reg32_t				pwr_trapdis[6];			/* 0x120 Trap disable for CPUy */
	os_reg32_t				pwr_trapcsctrl;			/* 0x138 Trap control for CS */
	os_tricoretrapsetclr_t	pwr_trapcssetclr;		/* 0x13C Trap SET/CLR for CS */
	os_reg32_t				pwr_trapcsstat;			/* 0x148 Trap status for CS */
	os_reg32_t				pwr_trapcsdis;			/* 0x14C Trap disable for CS */
	os_reg32_t				pwr_erueifilt;			/* 0x150 External Input Filter */
	os_reg32_t				pwr_erueicr[8];			/* 0x154 External Input Channel Register */
	os_reg32_t				pwr_erueifr;			/* 0x174 External Input Flag Register */
	os_reg32_t				pwr_erufmr;				/* 0x178 Flag modification */
	os_reg32_t				pwr_eruigcr[8];			/* 0x17C Interrupt gating control */
	os_reg32_t				pwr_erupdrr;			/* 0x19C Pattern detection result */
	os_reg32_t				pwr_ovcenable;			/* 0x1A0 Overlay enable */
	os_reg32_t				pwr_ovccon;				/* 0x1A4 Overlay control */
	os_reg32_t				pwr_chipinfo;			/* 0x1A8 Chip information */
	os_reg32_t				pwr_sotactrl;			/* 0x1AC SOTA */
};
#else /* OS_TRICOREARCH */
#error "Unexpected TRICORE architecture in OS_TRICOREARCH"
#endif /* OS_TRICOREARCH */

#endif /* OS_ASM */

#if (OS_TRICOREARCH == OS_TRICOREARCH_16EP) || (OS_TRICOREARCH == OS_TRICOREARCH_162)
/* PLL Clock Control Register */

/* pwr_pll_con[0]: Bits for PLL configuration register 0 */
#define OS_PLL_RESLD		OS_U(0x00040000)		/* Reset lock detection */
#define OS_PLL_PLLPWD		OS_U(0x00010000)		/* Power saving mode (doc incorrect?) */
#define OS_PLL_OSCDISCDIS	OS_U(0x00000040)		/* Clear FINDIS on loss of lock */
#define OS_PLL_CLRFINDIS	OS_U(0x00000020)		/* Write 1 here to CLEAR FINDIS! */
#define OS_PLL_SETFINDIS	OS_U(0x00000010)		/* Disconnect OSC from VCO. */
#define OS_PLL_VCOBYP		OS_U(0x00000001)		/* VCO bypass */

#if OS_TRICOREARCH == OS_TRICOREARCH_162
#define OS_PLLCON0_INSEL_MASK					(3u << 30u) /* Mask to select all bits in the INSEL field. */
#define OS_PLLCON0_INSEL_BACKUP_AS_CLK_SOURCE	0			/* Use backup clock as PLL input. */
#define OS_PLLCON0_INSEL_FOSC_AS_CLK_SOURCE		(1u << 30u) /* Use f_osc as PLL input. */
#endif

/* pwr_pllstat: Bits for PLL status register */
#define OS_VCO_LOCK			OS_U(0x00000004)		/* PLL VCO Lock Status */

#define OS_PLL_SET_P(p)		( ((p)-1u) << 24u )		/* PLLCON0 : 1 <= p <= 16 */
#define OS_PLL_SET_N(n)		( ((n)-1u) << 9u )		/* PLLCON0 : 1 <= n <= 128 */
#define OS_PLL_SET_K1(k1)	( ((k1)-1u) << 16u)		/* PLLCON1 : 1 <= k1 <= 128 */
#define OS_PLL_SET_K2(k2)	((k2)-1u)				/* PLLCON1 : 1 <= k2 <= 128 */
#define OS_PLL_SET_K3(k3)	(((k3)-1u) << 8u)		/* PLLCON1 : 1 <= k3 <= 128 */

/* pwr_ccucon: Bits and masks for clock control register. */
#define OS_CCUCON_LCK_LOCKED					(1u << 31u) /* Register is locked and can't be updated anymore. */
#define OS_CCUCON_UP							(1u << 30u) /* Update Request */
#define OS_CCUCON0_CLKSEL_MASK					(3u << 28u) /* Mask to select all bits in the CLKSEL field. */
#define OS_CCUCON0_CLKSEL_BACKUP_CLK_AS_FSOURCE 0			/* Use backup clock as f_source. */
#define OS_CCUCON0_CLKSEL_PLL_CLK_AS_FSOURCE	(1u << 28u) /* Use PLL output as f_source. */

#if OS_TRICOREARCH == OS_TRICOREARCH_16EP
#define OS_CCUCON1_INSEL_MASK					(3u << 28u) /* Mask to select all bits in the INSEL field. */
#define OS_CCUCON1_INSEL_BACKUP_AS_CLK_SOURCE	0			/* Use backup clock as clock source. */
#define OS_CCUCON1_INSEL_FOSC_AS_CLK_SOURCE		(1u << 28u) /* Use f_osc as clock source. */
#endif
#endif /* OS_TRICOREARCH == OS_TRICOREARCH_16EP || OS_TRICOREARCH == OS_TRICOREARCH_162 */

/* Set/Clear Trap Groups */
#define OS_SETCLRGRP		0x0						/* Default set/clear trap group */


/* External / ICU Clock Control Register */
#define OS_DISR				OS_U(0x00000001)		/* Disable request */
#define OS_DISS				OS_U(0x00000002)		/* Disable status */
#define OS_SUSPEN			OS_U(0x00000004)		/* Suspend enable */
#define OS_EXRDIS			OS_U(0x00000008)		/* External request disable */
#define OS_SBWE				OS_U(0x00000010)		/* Suspend write enable */
#define OS_DIVCLK_MSK		OS_U(0x00FF0000)		/* Clock divider */

/* Reset Status Register */
#define OS_RSSTM			OS_U(0x00000001)		/* Reset status system timer */
#define OS_RSDBG			OS_U(0x00000002)		/* Reset status debug unit */
#define OS_RSEXT			OS_U(0x00000004)		/* Reset status for external devices */
#define OS_HWCFG_MSK		OS_U(0x00070000)		/* Status of CFG[2..0] */
#define OS_HW_OCDS_E		OS_U(0x00080000)		/* Status of the OCDS_E pin */
#define OS_HW_BRK_IN		OS_U(0x00100000)		/* Status of the BRK_IN pin */
#define OS_PWORST			OS_U(0x08000000)		/* Power-on reset indicator */
#define OS_HDRST			OS_U(0x10000000)		/* Hardware reset indicator */
#define OS_SFTRST			OS_U(0x20000000)		/* Software reset indicator */
#define OS_WDTRST			OS_U(0x40000000)		/* Watchdog reset indicator */
#define OS_PWDRST			OS_U(0x80000000)		/* Power-down/Wake-up indicator */

/* Reset Request Register */
#define OS_RRSTM			OS_U(0x00000001)		/* System timer reset request */
#define OS_RRDBG			OS_U(0x00000002)		/* Debug unit reset request */
#define OS_RREXT			OS_U(0x00000004)		/* External devices reset request */
#define OS_SWCFG_MSK		OS_U(0x00070000)		/* Software boot configuration */
#define OS_SW_OCDS_E		OS_U(0x00080000)		/* Software OCDS_E signal boot value */
#define OS_SW_BRK_IN		OS_U(0x00100000)		/* Software BRK_IN signal boot value */
#define OS_SWBOOT			OS_U(0x01000000)		/* Software boot configuration */

/* NMI Status Register */
#define OS_NMI_EXT			OS_U(0x00000001)		/* External NMI */
#define OS_NMI_PLL			OS_U(0x00000002)		/* PLL loss of lock */
#define OS_NMI_WDT			OS_U(0x00000004)		/* Watchdog time-out */

#if (OS_TRICOREARCH!=OS_TRICOREARCH_18)
#ifndef OS_ASM
void OS_WriteEndinit(os_uint32_t);

#define OS_ClearEndinit(s) \
	do {						\
		(s) = OS_MFCR(OS_ICR);	\
		OS_DISABLE();			\
		OS_WriteEndinit(0);		\
	} while (0)

#define OS_SetEndinit(s) \
	do {						\
		OS_WriteEndinit(1);		\
		OS_MTCR(OS_ICR, s);		\
	} while (0)
#endif /* OS_ASM */
#else /* OS_TRICOREARCH!=OS_TRICOREARCH_18 */
#define OS_ClearEndinit(s)	OS_PARAM_UNUSED(s)
#define OS_SetEndinit(s)	OS_PARAM_UNUSED(s)
#endif /* OS_TRICOREARCH!=OS_TRICOREARCH_18 */

#ifdef __cplusplus
}
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
