/* Mk_TRICORE_bootword_tc2xx.s - startup file for Tricore
 *
 * This file contains an Aurix boot mode header that sets the startup code address
 * to 0xa0002000. This boot mode header must be placed in the BMHD0 location (0xa0000000),
 * because it contains a CRC that has been cacluclated from the expected values at this location.
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_bootword_tc2xx.s 22320 2016-03-02 16:05:32Z mist8519 $
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  This file contains no code at all, only data.
 *
 * DCG-2) Deviated Rule: [OS_PREPROC_050]
 *   An opening parenthesis for a preprocessor macro shall not be preceded by a whitespace character!
 *
 * Reason:
 *  MK_HWORD is not a function like macro. The opening parenthesis doesn't begin an argument list
 *  for this macro.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */

/* If set to 1, selects a BMH that enables lockstep on core 0
*/
#define MK_QM_USE_LOCKSTEP	1

/* Boot mode header ID - must be 0xB359
*/
#define MK_QM_TRICORE_BMHDID	0xB359

/* Boot mode index defines
*/
#define MK_QM_BMI_PINDIS			0x0008	/* Disable boot mode selection by hw pins. */
#define MK_QM_BMI_HWCFG_INTERNAL	0x0070	/* Boot from internal flash. */
#define MK_QM_BMI_HWCFG_ABM			0x0060	/* Alternate Boot Mode */
#define MK_QM_BMI_HWCFG_GENERIC		0x0040	/* Generic Bootstrap Loader */
#define MK_QM_BMI_HWCFG_ASC			0x0030	/* ASC Bootstrap Loader */
#define MK_QM_BMI_LCL0LSEN			0x0100	/* Enable lockstep on core 0 */
#define MK_QM_BMI_LCL1LSEN			0x0200	/* Enable lockstep on core 1 */

	MK_file(Mk_TRICORE_bootword_tc2xx.s)

	MK_global	MK_QM_TRICORE_bootblock

	MK_ASM_SDECL_BOOTWORD
	MK_ASM_SECTION_BOOTWORD

	/* Note: All CRC calculations are CRC32, but interpret 32-bit words in *big* endian byte order!
	 *       Lauterbach's Trace32 ships with example code that can be used to calculate them.
	*/

MK_QM_TRICORE_bootblock:

#if (MK_QM_USE_LOCKSTEP == 0)
	MK_WORD   0xa0000020			/* This is where the processor shall start executing our code */
	MK_HWORD  MK_QM_BMI_HWCFG_ABM	/* alternative boot mode: start at address given above */
	MK_HWORD  MK_QM_TRICORE_BMHDID
	MK_WORD   0xa0000000			/* CRC Range start (for simplicity we use the start address above) */
	MK_WORD   0xa0000003			/* CRC Range end */
	MK_WORD   0x5741e6d1			/* CRC of Range */
	MK_WORD   0xa8be192e			/* ~CRC of Range */
	MK_WORD   0x898f7dc6			/* CRC of everything above */
	MK_WORD   0x76708239			/* ~CRC of everything above */
#else
	MK_WORD   0xa0000020			/* This is where the processor shall start executing our code */
	/* Deviation DCG-2 <1> */
	MK_HWORD  (MK_QM_BMI_HWCFG_ABM|MK_QM_BMI_LCL0LSEN)	/* alternative boot mode, core0 in lockstep */
	MK_HWORD  MK_QM_TRICORE_BMHDID
	MK_WORD   0xa0000000			/* CRC Range start (for simplicity we use the start address above) */
	MK_WORD   0xa0000003			/* CRC Range end */
	MK_WORD   0x5741e6d1			/* CRC of Range */
	MK_WORD   0xa8be192e			/* ~CRC of Range */
	MK_WORD   0x66ddcb27			/* CRC of everything above */
	MK_WORD   0x992234d8			/* ~CRC of everything above */
#endif


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
