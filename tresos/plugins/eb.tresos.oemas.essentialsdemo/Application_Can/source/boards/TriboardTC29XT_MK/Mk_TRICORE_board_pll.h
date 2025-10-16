/* Mk_TRICORE_pll.h - Tricore SCU module description (PLL relevant registers)
 *
 * This file includes the header file that describes the SCU variant used on the
 * particular Tricore microcontroller that is selected.
 *
 * The clock configuration is part of the SCU (system control unit) hardware peripheral.
 * It is used to configure the PLL and clock dividers
 *
 * The name given here to each PLL variant is merely the first microcontroller on which the variant
 * was encountered. The name is not specified by Infineon.
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_pll.h 23787 2016-06-17 13:48:02Z mist8519 $
*/
#ifndef MK_TRICORE_BOARD_PLL_H
#define MK_TRICORE_BOARD_PLL_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <public/Mk_public_types.h>

#if MK_TRICORE_SCU == MK_SCU_TC2XX
#include <Mk_TRICORE_board_pll_tc2xx.h>
#else
#error "Unknown or unsupported SCU variant. Check your CPU characteristics file!"
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
