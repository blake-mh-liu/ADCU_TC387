/* Mk_TRICORE_wdt.h - Tricore WDT module description
 *
 * This file includes the header file that describes the WDT variant used on the
 * particular Tricore microcontroller that is selected.
 *
 * The WDT (watchdog timer) is part of the SCU (system control unit) hardware peripheral.
 * The WDT is used by the microkernel for the purpose of turning the ENDINIT flag on and off.
 *
 * The name given here to each WDT variant is merely the first microcontroller on which the variant
 * was encountered. The name is not specified by Infineon.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_WDT_H
#define MK_TRICORE_WDT_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

#if MK_TRICORE_SCU == MK_SCU_TC2XX

/* Module base offset for TC24x, TC26x, TC27x, and TC29x processors */
#define MK_MODBASE_WDTS		(MK_MODBASE_SCU + 0x0F0u)
#define MK_MODBASE_WDTX		(MK_MODBASE_SCU + 0x100u)

#elif MK_TRICORE_SCU == MK_SCU_TC3XX

/* Module base offset for TC3xx processors */
#define MK_MODBASE_WDTS		(MK_MODBASE_SCU + 0x2A8u)
#define MK_MODBASE_WDTX		(MK_MODBASE_SCU + 0x24Cu)

#else
#error "Unknown or unsupported SCU variant. Check your CPU characteristics file!"
#endif

/* Bit fields in Watchdog Timer Control Register 0 */
#define MK_ENDINIT			0x00000001u		/* End of initialization control					*/
#define MK_WDTLCK			0x00000002u		/* Lock												*/
#define MK_WDTPW_LSB		0x00000004u		/* Least significant bit of password field			*/
#define MK_WDTPW0_MSK		0x000000FCu		/* Bits 7:2 of password field						*/
#define MK_WDTPW1_MSK		0x0000FF00u		/* Bits 15:8 of password field						*/
#define MK_WDTREL_MSK		0xFFFF0000u		/* Reload value for watchdog timer					*/
#define MK_WDT_PAS			0x00000080u		/* Password auto-sequence status flag				*/
#define MK_WDT_TCS			0x00000100u		/* Timer check status flag							*/
#define MK_WDT_TIMEGUESS	0x00010000u		/* Estimated time for password computation			*/
#define MK_WDTPW_MSK		(MK_WDTPW0_MSK|MK_WDTPW1_MSK)

#ifndef MK_ASM
struct mk_wdtcon_s
{
	mk_reg32_t	wdtxcon0;	/* Control Register 0	*/
	mk_reg32_t	wdtxcon1;	/* Control Register 1	*/
	mk_reg32_t	wdtxssr;	/* Status Register		*/
};

typedef struct mk_wdtcon_s mk_wdtcon_t;

/* MK_GetScuWdtCpuCon()
 *
 * Get a pointer to the watchdog registers of the current core.
*/
#define MK_GetScuWdtCpuCon() (&(((mk_wdtcon_t *)MK_MODBASE_WDTX)[MK_HwGetCoreIndex()]))

/* MK_scu_wdtscon
 *
 * Pointer-like macro to the safety watchdog registers.
*/
#define MK_scu_wdtscon	((mk_wdtcon_t *)MK_MODBASE_WDTS)

MK_ATTR_NO_STACKPROT void MK_WriteSafetyEndinit(mk_uint32_t);
MK_ATTR_NO_STACKPROT void MK_WriteEndinit(mk_uint32_t);

#endif /* ifndef MK_ASM */


#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
