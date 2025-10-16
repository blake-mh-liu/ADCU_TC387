/* Mk_TRICORE_board_pll_tc2xx.h - Tricore PLL module description for the "tc2xx" variant.
 *
 * This file contains a minimal description of Tricore's clock configuration registers (the
 * variant used on the TC2xx "Aurix" processors). It is part of the SCU module.
 *
 * This file only provides the addresses and and bitmasks of the SCU
 * registers that are actually used in the PLL configuration template
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_pll_tc2xx.h 23787 2016-06-17 13:48:02Z mist8519 $
*/
#ifndef MK_TRICORE_BOARD_PLL_TC2XX_H
#define MK_TRICORE_BOARD_PLL_TC2XX_H

#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

#define TMPL_SCU_OSCCON			(*((mk_reg32_t *)(MK_MODBASE_SCU+0x10)))
#define TMPL_SCU_PLLSTAT		(*((mk_reg32_t *)(MK_MODBASE_SCU+0x14)))
#define TMPL_SCU_PLLCON0		(*((mk_reg32_t *)(MK_MODBASE_SCU+0x18)))
#define TMPL_SCU_PLLCON1		(*((mk_reg32_t *)(MK_MODBASE_SCU+0x1C)))
#define TMPL_SCU_CCUCON0		(*((mk_reg32_t *)(MK_MODBASE_SCU+0x30)))
#define TMPL_SCU_CCUCON1		(*((mk_reg32_t *)(MK_MODBASE_SCU+0x34)))

/* Fields in OSCCON */
#define TMPL_OSCCON_PLLLV		0x00000001
#define TMPL_OSCCON_PLLHV		0x00000010
#define TMPL_OSCSTABLE	(TMPL_OSCCON_PLLLV | TMPL_OSCCON_PLLHV)

/* Common Field for all CCUCONx registers */
#define TMPL_CCUCON_LCK_LOCKED	0x80000000
#define TMPL_CCUCON_UP			0x40000000

/* Fields in CCUCON0 */
#define TMPL_CCUCON0_CLKSEL_MASK	0x30000000
#define TMPL_CCUCON0_CLKSEL_FPLL	0x10000000

/* Fields in CCUCON1 */
#define TMPL_CCUCON1_INSEL_MASK	0x30000000
#define TMPL_CCUCON1_INSEL_FOSC0	0x10000000

/* Fields in PLLCON0 */
#define TMPL_PLLCON0_VCOBYP		0x00000001
#define TMPL_PLLCON0_SETFINDIS	0x00000010
#define TMPL_PLLCON0_CLRFINDIS	0x00000020
#define TMPL_PLLCON0_OSCDISCDIS	0x00000040
#define TMPL_PLLCON0_PLLPWD		0x00010000
#define TMPL_PLLCON0_RESLD		0x00040000

/* Fields in PLLCON1 */
#define TMPL_PLLCON1_K2_MASK		0x0000007f
#define TMPL_PLLCON1_K3_MASK		0x00007f00
#define TMPL_PLLCON1_K1_MASK		0x007f0000

/* Fields in PLLSTAT */
#define TMPL_PLLSTAT_VCOBYST		0x00000001
#define TMPL_PLLSTAT_VCOLOCK		0x00000004
#define TMPL_PLLSTAT_K1RDY		0x00000010
#define TMPL_PLLSTAT_K2RDY		0x00000020



#ifndef MK_ASM
void Tmpl_SetupClocks(mk_uint32_t, mk_uint32_t, mk_uint32_t, mk_uint32_t);
#endif


#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
