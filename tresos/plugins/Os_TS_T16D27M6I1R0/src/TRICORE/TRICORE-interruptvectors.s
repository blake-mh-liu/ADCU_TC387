/* TRICORE-interruptvectors.s
 *
 * This file contains the interrupt vectors for TRICORE
 * This file is compiled at configuration (system build) time.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#ifndef OS_ASM
#define OS_ASM
#endif

#include <Os_asm_common.h>
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_kernel.h>
#include <board.h>
#include <Os_configuration.h>
#include <Os_libconfig.h>
#include <TRICORE/Os_TRICORE_cpu.h>

/* Select the appropriate alignment of the vector table.
 *
 * The interrupt vector table must be aligned such that the bits representing
 * the offset of the vector in the table are 0 in the base address. This is
 * because the Tricore ORs the offset with the base address rather than adding
 * it
 *
 * Each vector is 32 bytes, so the alignment is no_of_vectors * 32.
*/
#define OS_INTVEC_ALIGN_ABS	8192
#define OS_INTVEC_ALIGN_EXP	13

#define OS_Cat1Handler	OS_Cat1Entry
#define OS_Cat2Handler	OS_Cat2Entry
#define OS_CatKHandler	OS_CatKEntry

/* GENVECTOR - this macro generates a single interrupt vector
*/
#define GENVECTOR(inum) \
	GenIntVector	OS_IRQ##inum##_NAME,		\
					OS_IRQ##inum##_BISRPRIO,	\
					OS_IRQ##inum##_ISRID,		\
					OS_IRQ##inum##_ENTRY,		\
					OS_IRQ##inum##_EXIT

/* DIRECTVECTOR - this macro generates a direct ISR call bypassing all handlers
 */
#define DIRECTVECTOR(inum) \
	DirectVector	OS_IRQ##inum##_NAME,		\
					OS_IRQ##inum##_ENTRY

/* Here we point all undefined interrupts to the built-in
 * OS_UnknownInterruptHandler handler.
 *
 * For unused interrupts, the BISR priority is set to 255.
*/
#ifndef OS_IRQ01_NAME
#define OS_IRQ01_NAME		OS_Ivector_01
#define OS_IRQ01_BISRPRIO	255
#define OS_IRQ01_ISRID		1
#define OS_IRQ01_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ01_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ02_NAME
#define OS_IRQ02_NAME		OS_Ivector_02
#define OS_IRQ02_BISRPRIO	255
#define OS_IRQ02_ISRID		2
#define OS_IRQ02_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ02_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ03_NAME
#define OS_IRQ03_NAME		OS_Ivector_03
#define OS_IRQ03_BISRPRIO	255
#define OS_IRQ03_ISRID		3
#define OS_IRQ03_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ03_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ04_NAME
#define OS_IRQ04_NAME		OS_Ivector_04
#define OS_IRQ04_BISRPRIO	255
#define OS_IRQ04_ISRID		4
#define OS_IRQ04_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ04_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ05_NAME
#define OS_IRQ05_NAME		OS_Ivector_05
#define OS_IRQ05_BISRPRIO	255
#define OS_IRQ05_ISRID		5
#define OS_IRQ05_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ05_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ06_NAME
#define OS_IRQ06_NAME		OS_Ivector_06
#define OS_IRQ06_BISRPRIO	255
#define OS_IRQ06_ISRID		6
#define OS_IRQ06_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ06_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ07_NAME
#define OS_IRQ07_NAME		OS_Ivector_07
#define OS_IRQ07_BISRPRIO	255
#define OS_IRQ07_ISRID		7
#define OS_IRQ07_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ07_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ08_NAME
#define OS_IRQ08_NAME		OS_Ivector_08
#define OS_IRQ08_BISRPRIO	255
#define OS_IRQ08_ISRID		8
#define OS_IRQ08_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ08_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ09_NAME
#define OS_IRQ09_NAME		OS_Ivector_09
#define OS_IRQ09_BISRPRIO	255
#define OS_IRQ09_ISRID		9
#define OS_IRQ09_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ09_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ0a_NAME
#define OS_IRQ0a_NAME		OS_Ivector_0a
#define OS_IRQ0a_BISRPRIO	255
#define OS_IRQ0a_ISRID		10
#define OS_IRQ0a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ0a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ0b_NAME
#define OS_IRQ0b_NAME		OS_Ivector_0b
#define OS_IRQ0b_BISRPRIO	255
#define OS_IRQ0b_ISRID		11
#define OS_IRQ0b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ0b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ0c_NAME
#define OS_IRQ0c_NAME		OS_Ivector_0c
#define OS_IRQ0c_BISRPRIO	255
#define OS_IRQ0c_ISRID		12
#define OS_IRQ0c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ0c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ0d_NAME
#define OS_IRQ0d_NAME		OS_Ivector_0d
#define OS_IRQ0d_BISRPRIO	255
#define OS_IRQ0d_ISRID		13
#define OS_IRQ0d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ0d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ0e_NAME
#define OS_IRQ0e_NAME		OS_Ivector_0e
#define OS_IRQ0e_BISRPRIO	255
#define OS_IRQ0e_ISRID		14
#define OS_IRQ0e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ0e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ0f_NAME
#define OS_IRQ0f_NAME		OS_Ivector_0f
#define OS_IRQ0f_BISRPRIO	255
#define OS_IRQ0f_ISRID		15
#define OS_IRQ0f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ0f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ10_NAME
#define OS_IRQ10_NAME		OS_Ivector_10
#define OS_IRQ10_BISRPRIO	255
#define OS_IRQ10_ISRID		16
#define OS_IRQ10_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ10_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ11_NAME
#define OS_IRQ11_NAME		OS_Ivector_11
#define OS_IRQ11_BISRPRIO	255
#define OS_IRQ11_ISRID		17
#define OS_IRQ11_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ11_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ12_NAME
#define OS_IRQ12_NAME		OS_Ivector_12
#define OS_IRQ12_BISRPRIO	255
#define OS_IRQ12_ISRID		18
#define OS_IRQ12_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ12_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ13_NAME
#define OS_IRQ13_NAME		OS_Ivector_13
#define OS_IRQ13_BISRPRIO	255
#define OS_IRQ13_ISRID		19
#define OS_IRQ13_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ13_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ14_NAME
#define OS_IRQ14_NAME		OS_Ivector_14
#define OS_IRQ14_BISRPRIO	255
#define OS_IRQ14_ISRID		20
#define OS_IRQ14_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ14_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ15_NAME
#define OS_IRQ15_NAME		OS_Ivector_15
#define OS_IRQ15_BISRPRIO	255
#define OS_IRQ15_ISRID		21
#define OS_IRQ15_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ15_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ16_NAME
#define OS_IRQ16_NAME		OS_Ivector_16
#define OS_IRQ16_BISRPRIO	255
#define OS_IRQ16_ISRID		22
#define OS_IRQ16_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ16_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ17_NAME
#define OS_IRQ17_NAME		OS_Ivector_17
#define OS_IRQ17_BISRPRIO	255
#define OS_IRQ17_ISRID		23
#define OS_IRQ17_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ17_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ18_NAME
#define OS_IRQ18_NAME		OS_Ivector_18
#define OS_IRQ18_BISRPRIO	255
#define OS_IRQ18_ISRID		24
#define OS_IRQ18_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ18_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ19_NAME
#define OS_IRQ19_NAME		OS_Ivector_19
#define OS_IRQ19_BISRPRIO	255
#define OS_IRQ19_ISRID		25
#define OS_IRQ19_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ19_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ1a_NAME
#define OS_IRQ1a_NAME		OS_Ivector_1a
#define OS_IRQ1a_BISRPRIO	255
#define OS_IRQ1a_ISRID		26
#define OS_IRQ1a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ1a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ1b_NAME
#define OS_IRQ1b_NAME		OS_Ivector_1b
#define OS_IRQ1b_BISRPRIO	255
#define OS_IRQ1b_ISRID		27
#define OS_IRQ1b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ1b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ1c_NAME
#define OS_IRQ1c_NAME		OS_Ivector_1c
#define OS_IRQ1c_BISRPRIO	255
#define OS_IRQ1c_ISRID		28
#define OS_IRQ1c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ1c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ1d_NAME
#define OS_IRQ1d_NAME		OS_Ivector_1d
#define OS_IRQ1d_BISRPRIO	255
#define OS_IRQ1d_ISRID		29
#define OS_IRQ1d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ1d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ1e_NAME
#define OS_IRQ1e_NAME		OS_Ivector_1e
#define OS_IRQ1e_BISRPRIO	255
#define OS_IRQ1e_ISRID		30
#define OS_IRQ1e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ1e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ1f_NAME
#define OS_IRQ1f_NAME		OS_Ivector_1f
#define OS_IRQ1f_BISRPRIO	255
#define OS_IRQ1f_ISRID		31
#define OS_IRQ1f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ1f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ20_NAME
#define OS_IRQ20_NAME		OS_Ivector_20
#define OS_IRQ20_BISRPRIO	255
#define OS_IRQ20_ISRID		32
#define OS_IRQ20_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ20_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ21_NAME
#define OS_IRQ21_NAME		OS_Ivector_21
#define OS_IRQ21_BISRPRIO	255
#define OS_IRQ21_ISRID		33
#define OS_IRQ21_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ21_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ22_NAME
#define OS_IRQ22_NAME		OS_Ivector_22
#define OS_IRQ22_BISRPRIO	255
#define OS_IRQ22_ISRID		34
#define OS_IRQ22_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ22_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ23_NAME
#define OS_IRQ23_NAME		OS_Ivector_23
#define OS_IRQ23_BISRPRIO	255
#define OS_IRQ23_ISRID		35
#define OS_IRQ23_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ23_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ24_NAME
#define OS_IRQ24_NAME		OS_Ivector_24
#define OS_IRQ24_BISRPRIO	255
#define OS_IRQ24_ISRID		36
#define OS_IRQ24_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ24_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ25_NAME
#define OS_IRQ25_NAME		OS_Ivector_25
#define OS_IRQ25_BISRPRIO	255
#define OS_IRQ25_ISRID		37
#define OS_IRQ25_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ25_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ26_NAME
#define OS_IRQ26_NAME		OS_Ivector_26
#define OS_IRQ26_BISRPRIO	255
#define OS_IRQ26_ISRID		38
#define OS_IRQ26_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ26_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ27_NAME
#define OS_IRQ27_NAME		OS_Ivector_27
#define OS_IRQ27_BISRPRIO	255
#define OS_IRQ27_ISRID		39
#define OS_IRQ27_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ27_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ28_NAME
#define OS_IRQ28_NAME		OS_Ivector_28
#define OS_IRQ28_BISRPRIO	255
#define OS_IRQ28_ISRID		40
#define OS_IRQ28_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ28_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ29_NAME
#define OS_IRQ29_NAME		OS_Ivector_29
#define OS_IRQ29_BISRPRIO	255
#define OS_IRQ29_ISRID		41
#define OS_IRQ29_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ29_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ2a_NAME
#define OS_IRQ2a_NAME		OS_Ivector_2a
#define OS_IRQ2a_BISRPRIO	255
#define OS_IRQ2a_ISRID		42
#define OS_IRQ2a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ2a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ2b_NAME
#define OS_IRQ2b_NAME		OS_Ivector_2b
#define OS_IRQ2b_BISRPRIO	255
#define OS_IRQ2b_ISRID		43
#define OS_IRQ2b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ2b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ2c_NAME
#define OS_IRQ2c_NAME		OS_Ivector_2c
#define OS_IRQ2c_BISRPRIO	255
#define OS_IRQ2c_ISRID		44
#define OS_IRQ2c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ2c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ2d_NAME
#define OS_IRQ2d_NAME		OS_Ivector_2d
#define OS_IRQ2d_BISRPRIO	255
#define OS_IRQ2d_ISRID		45
#define OS_IRQ2d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ2d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ2e_NAME
#define OS_IRQ2e_NAME		OS_Ivector_2e
#define OS_IRQ2e_BISRPRIO	255
#define OS_IRQ2e_ISRID		46
#define OS_IRQ2e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ2e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ2f_NAME
#define OS_IRQ2f_NAME		OS_Ivector_2f
#define OS_IRQ2f_BISRPRIO	255
#define OS_IRQ2f_ISRID		47
#define OS_IRQ2f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ2f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ30_NAME
#define OS_IRQ30_NAME		OS_Ivector_30
#define OS_IRQ30_BISRPRIO	255
#define OS_IRQ30_ISRID		48
#define OS_IRQ30_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ30_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ31_NAME
#define OS_IRQ31_NAME		OS_Ivector_31
#define OS_IRQ31_BISRPRIO	255
#define OS_IRQ31_ISRID		49
#define OS_IRQ31_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ31_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ32_NAME
#define OS_IRQ32_NAME		OS_Ivector_32
#define OS_IRQ32_BISRPRIO	255
#define OS_IRQ32_ISRID		50
#define OS_IRQ32_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ32_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ33_NAME
#define OS_IRQ33_NAME		OS_Ivector_33
#define OS_IRQ33_BISRPRIO	255
#define OS_IRQ33_ISRID		51
#define OS_IRQ33_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ33_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ34_NAME
#define OS_IRQ34_NAME		OS_Ivector_34
#define OS_IRQ34_BISRPRIO	255
#define OS_IRQ34_ISRID		52
#define OS_IRQ34_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ34_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ35_NAME
#define OS_IRQ35_NAME		OS_Ivector_35
#define OS_IRQ35_BISRPRIO	255
#define OS_IRQ35_ISRID		53
#define OS_IRQ35_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ35_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ36_NAME
#define OS_IRQ36_NAME		OS_Ivector_36
#define OS_IRQ36_BISRPRIO	255
#define OS_IRQ36_ISRID		54
#define OS_IRQ36_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ36_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ37_NAME
#define OS_IRQ37_NAME		OS_Ivector_37
#define OS_IRQ37_BISRPRIO	255
#define OS_IRQ37_ISRID		55
#define OS_IRQ37_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ37_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ38_NAME
#define OS_IRQ38_NAME		OS_Ivector_38
#define OS_IRQ38_BISRPRIO	255
#define OS_IRQ38_ISRID		56
#define OS_IRQ38_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ38_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ39_NAME
#define OS_IRQ39_NAME		OS_Ivector_39
#define OS_IRQ39_BISRPRIO	255
#define OS_IRQ39_ISRID		57
#define OS_IRQ39_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ39_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ3a_NAME
#define OS_IRQ3a_NAME		OS_Ivector_3a
#define OS_IRQ3a_BISRPRIO	255
#define OS_IRQ3a_ISRID		58
#define OS_IRQ3a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ3a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ3b_NAME
#define OS_IRQ3b_NAME		OS_Ivector_3b
#define OS_IRQ3b_BISRPRIO	255
#define OS_IRQ3b_ISRID		59
#define OS_IRQ3b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ3b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ3c_NAME
#define OS_IRQ3c_NAME		OS_Ivector_3c
#define OS_IRQ3c_BISRPRIO	255
#define OS_IRQ3c_ISRID		60
#define OS_IRQ3c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ3c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ3d_NAME
#define OS_IRQ3d_NAME		OS_Ivector_3d
#define OS_IRQ3d_BISRPRIO	255
#define OS_IRQ3d_ISRID		61
#define OS_IRQ3d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ3d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ3e_NAME
#define OS_IRQ3e_NAME		OS_Ivector_3e
#define OS_IRQ3e_BISRPRIO	255
#define OS_IRQ3e_ISRID		62
#define OS_IRQ3e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ3e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ3f_NAME
#define OS_IRQ3f_NAME		OS_Ivector_3f
#define OS_IRQ3f_BISRPRIO	255
#define OS_IRQ3f_ISRID		63
#define OS_IRQ3f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ3f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ40_NAME
#define OS_IRQ40_NAME		OS_Ivector_40
#define OS_IRQ40_BISRPRIO	255
#define OS_IRQ40_ISRID		64
#define OS_IRQ40_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ40_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ41_NAME
#define OS_IRQ41_NAME		OS_Ivector_41
#define OS_IRQ41_BISRPRIO	255
#define OS_IRQ41_ISRID		65
#define OS_IRQ41_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ41_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ42_NAME
#define OS_IRQ42_NAME		OS_Ivector_42
#define OS_IRQ42_BISRPRIO	255
#define OS_IRQ42_ISRID		66
#define OS_IRQ42_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ42_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ43_NAME
#define OS_IRQ43_NAME		OS_Ivector_43
#define OS_IRQ43_BISRPRIO	255
#define OS_IRQ43_ISRID		67
#define OS_IRQ43_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ43_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ44_NAME
#define OS_IRQ44_NAME		OS_Ivector_44
#define OS_IRQ44_BISRPRIO	255
#define OS_IRQ44_ISRID		68
#define OS_IRQ44_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ44_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ45_NAME
#define OS_IRQ45_NAME		OS_Ivector_45
#define OS_IRQ45_BISRPRIO	255
#define OS_IRQ45_ISRID		69
#define OS_IRQ45_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ45_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ46_NAME
#define OS_IRQ46_NAME		OS_Ivector_46
#define OS_IRQ46_BISRPRIO	255
#define OS_IRQ46_ISRID		70
#define OS_IRQ46_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ46_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ47_NAME
#define OS_IRQ47_NAME		OS_Ivector_47
#define OS_IRQ47_BISRPRIO	255
#define OS_IRQ47_ISRID		71
#define OS_IRQ47_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ47_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ48_NAME
#define OS_IRQ48_NAME		OS_Ivector_48
#define OS_IRQ48_BISRPRIO	255
#define OS_IRQ48_ISRID		72
#define OS_IRQ48_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ48_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ49_NAME
#define OS_IRQ49_NAME		OS_Ivector_49
#define OS_IRQ49_BISRPRIO	255
#define OS_IRQ49_ISRID		73
#define OS_IRQ49_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ49_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ4a_NAME
#define OS_IRQ4a_NAME		OS_Ivector_4a
#define OS_IRQ4a_BISRPRIO	255
#define OS_IRQ4a_ISRID		74
#define OS_IRQ4a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ4a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ4b_NAME
#define OS_IRQ4b_NAME		OS_Ivector_4b
#define OS_IRQ4b_BISRPRIO	255
#define OS_IRQ4b_ISRID		75
#define OS_IRQ4b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ4b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ4c_NAME
#define OS_IRQ4c_NAME		OS_Ivector_4c
#define OS_IRQ4c_BISRPRIO	255
#define OS_IRQ4c_ISRID		76
#define OS_IRQ4c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ4c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ4d_NAME
#define OS_IRQ4d_NAME		OS_Ivector_4d
#define OS_IRQ4d_BISRPRIO	255
#define OS_IRQ4d_ISRID		77
#define OS_IRQ4d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ4d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ4e_NAME
#define OS_IRQ4e_NAME		OS_Ivector_4e
#define OS_IRQ4e_BISRPRIO	255
#define OS_IRQ4e_ISRID		78
#define OS_IRQ4e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ4e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ4f_NAME
#define OS_IRQ4f_NAME		OS_Ivector_4f
#define OS_IRQ4f_BISRPRIO	255
#define OS_IRQ4f_ISRID		79
#define OS_IRQ4f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ4f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ50_NAME
#define OS_IRQ50_NAME		OS_Ivector_50
#define OS_IRQ50_BISRPRIO	255
#define OS_IRQ50_ISRID		80
#define OS_IRQ50_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ50_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ51_NAME
#define OS_IRQ51_NAME		OS_Ivector_51
#define OS_IRQ51_BISRPRIO	255
#define OS_IRQ51_ISRID		81
#define OS_IRQ51_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ51_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ52_NAME
#define OS_IRQ52_NAME		OS_Ivector_52
#define OS_IRQ52_BISRPRIO	255
#define OS_IRQ52_ISRID		82
#define OS_IRQ52_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ52_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ53_NAME
#define OS_IRQ53_NAME		OS_Ivector_53
#define OS_IRQ53_BISRPRIO	255
#define OS_IRQ53_ISRID		83
#define OS_IRQ53_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ53_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ54_NAME
#define OS_IRQ54_NAME		OS_Ivector_54
#define OS_IRQ54_BISRPRIO	255
#define OS_IRQ54_ISRID		84
#define OS_IRQ54_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ54_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ55_NAME
#define OS_IRQ55_NAME		OS_Ivector_55
#define OS_IRQ55_BISRPRIO	255
#define OS_IRQ55_ISRID		85
#define OS_IRQ55_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ55_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ56_NAME
#define OS_IRQ56_NAME		OS_Ivector_56
#define OS_IRQ56_BISRPRIO	255
#define OS_IRQ56_ISRID		86
#define OS_IRQ56_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ56_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ57_NAME
#define OS_IRQ57_NAME		OS_Ivector_57
#define OS_IRQ57_BISRPRIO	255
#define OS_IRQ57_ISRID		87
#define OS_IRQ57_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ57_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ58_NAME
#define OS_IRQ58_NAME		OS_Ivector_58
#define OS_IRQ58_BISRPRIO	255
#define OS_IRQ58_ISRID		88
#define OS_IRQ58_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ58_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ59_NAME
#define OS_IRQ59_NAME		OS_Ivector_59
#define OS_IRQ59_BISRPRIO	255
#define OS_IRQ59_ISRID		89
#define OS_IRQ59_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ59_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ5a_NAME
#define OS_IRQ5a_NAME		OS_Ivector_5a
#define OS_IRQ5a_BISRPRIO	255
#define OS_IRQ5a_ISRID		90
#define OS_IRQ5a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ5a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ5b_NAME
#define OS_IRQ5b_NAME		OS_Ivector_5b
#define OS_IRQ5b_BISRPRIO	255
#define OS_IRQ5b_ISRID		91
#define OS_IRQ5b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ5b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ5c_NAME
#define OS_IRQ5c_NAME		OS_Ivector_5c
#define OS_IRQ5c_BISRPRIO	255
#define OS_IRQ5c_ISRID		92
#define OS_IRQ5c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ5c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ5d_NAME
#define OS_IRQ5d_NAME		OS_Ivector_5d
#define OS_IRQ5d_BISRPRIO	255
#define OS_IRQ5d_ISRID		93
#define OS_IRQ5d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ5d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ5e_NAME
#define OS_IRQ5e_NAME		OS_Ivector_5e
#define OS_IRQ5e_BISRPRIO	255
#define OS_IRQ5e_ISRID		94
#define OS_IRQ5e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ5e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ5f_NAME
#define OS_IRQ5f_NAME		OS_Ivector_5f
#define OS_IRQ5f_BISRPRIO	255
#define OS_IRQ5f_ISRID		95
#define OS_IRQ5f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ5f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ60_NAME
#define OS_IRQ60_NAME		OS_Ivector_60
#define OS_IRQ60_BISRPRIO	255
#define OS_IRQ60_ISRID		96
#define OS_IRQ60_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ60_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ61_NAME
#define OS_IRQ61_NAME		OS_Ivector_61
#define OS_IRQ61_BISRPRIO	255
#define OS_IRQ61_ISRID		97
#define OS_IRQ61_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ61_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ62_NAME
#define OS_IRQ62_NAME		OS_Ivector_62
#define OS_IRQ62_BISRPRIO	255
#define OS_IRQ62_ISRID		98
#define OS_IRQ62_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ62_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ63_NAME
#define OS_IRQ63_NAME		OS_Ivector_63
#define OS_IRQ63_BISRPRIO	255
#define OS_IRQ63_ISRID		99
#define OS_IRQ63_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ63_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ64_NAME
#define OS_IRQ64_NAME		OS_Ivector_64
#define OS_IRQ64_BISRPRIO	255
#define OS_IRQ64_ISRID		100
#define OS_IRQ64_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ64_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ65_NAME
#define OS_IRQ65_NAME		OS_Ivector_65
#define OS_IRQ65_BISRPRIO	255
#define OS_IRQ65_ISRID		101
#define OS_IRQ65_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ65_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ66_NAME
#define OS_IRQ66_NAME		OS_Ivector_66
#define OS_IRQ66_BISRPRIO	255
#define OS_IRQ66_ISRID		102
#define OS_IRQ66_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ66_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ67_NAME
#define OS_IRQ67_NAME		OS_Ivector_67
#define OS_IRQ67_BISRPRIO	255
#define OS_IRQ67_ISRID		103
#define OS_IRQ67_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ67_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ68_NAME
#define OS_IRQ68_NAME		OS_Ivector_68
#define OS_IRQ68_BISRPRIO	255
#define OS_IRQ68_ISRID		104
#define OS_IRQ68_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ68_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ69_NAME
#define OS_IRQ69_NAME		OS_Ivector_69
#define OS_IRQ69_BISRPRIO	255
#define OS_IRQ69_ISRID		105
#define OS_IRQ69_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ69_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ6a_NAME
#define OS_IRQ6a_NAME		OS_Ivector_6a
#define OS_IRQ6a_BISRPRIO	255
#define OS_IRQ6a_ISRID		106
#define OS_IRQ6a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ6a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ6b_NAME
#define OS_IRQ6b_NAME		OS_Ivector_6b
#define OS_IRQ6b_BISRPRIO	255
#define OS_IRQ6b_ISRID		107
#define OS_IRQ6b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ6b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ6c_NAME
#define OS_IRQ6c_NAME		OS_Ivector_6c
#define OS_IRQ6c_BISRPRIO	255
#define OS_IRQ6c_ISRID		108
#define OS_IRQ6c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ6c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ6d_NAME
#define OS_IRQ6d_NAME		OS_Ivector_6d
#define OS_IRQ6d_BISRPRIO	255
#define OS_IRQ6d_ISRID		109
#define OS_IRQ6d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ6d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ6e_NAME
#define OS_IRQ6e_NAME		OS_Ivector_6e
#define OS_IRQ6e_BISRPRIO	255
#define OS_IRQ6e_ISRID		110
#define OS_IRQ6e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ6e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ6f_NAME
#define OS_IRQ6f_NAME		OS_Ivector_6f
#define OS_IRQ6f_BISRPRIO	255
#define OS_IRQ6f_ISRID		111
#define OS_IRQ6f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ6f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ70_NAME
#define OS_IRQ70_NAME		OS_Ivector_70
#define OS_IRQ70_BISRPRIO	255
#define OS_IRQ70_ISRID		112
#define OS_IRQ70_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ70_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ71_NAME
#define OS_IRQ71_NAME		OS_Ivector_71
#define OS_IRQ71_BISRPRIO	255
#define OS_IRQ71_ISRID		113
#define OS_IRQ71_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ71_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ72_NAME
#define OS_IRQ72_NAME		OS_Ivector_72
#define OS_IRQ72_BISRPRIO	255
#define OS_IRQ72_ISRID		114
#define OS_IRQ72_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ72_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ73_NAME
#define OS_IRQ73_NAME		OS_Ivector_73
#define OS_IRQ73_BISRPRIO	255
#define OS_IRQ73_ISRID		115
#define OS_IRQ73_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ73_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ74_NAME
#define OS_IRQ74_NAME		OS_Ivector_74
#define OS_IRQ74_BISRPRIO	255
#define OS_IRQ74_ISRID		116
#define OS_IRQ74_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ74_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ75_NAME
#define OS_IRQ75_NAME		OS_Ivector_75
#define OS_IRQ75_BISRPRIO	255
#define OS_IRQ75_ISRID		117
#define OS_IRQ75_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ75_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ76_NAME
#define OS_IRQ76_NAME		OS_Ivector_76
#define OS_IRQ76_BISRPRIO	255
#define OS_IRQ76_ISRID		118
#define OS_IRQ76_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ76_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ77_NAME
#define OS_IRQ77_NAME		OS_Ivector_77
#define OS_IRQ77_BISRPRIO	255
#define OS_IRQ77_ISRID		119
#define OS_IRQ77_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ77_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ78_NAME
#define OS_IRQ78_NAME		OS_Ivector_78
#define OS_IRQ78_BISRPRIO	255
#define OS_IRQ78_ISRID		120
#define OS_IRQ78_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ78_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ79_NAME
#define OS_IRQ79_NAME		OS_Ivector_79
#define OS_IRQ79_BISRPRIO	255
#define OS_IRQ79_ISRID		121
#define OS_IRQ79_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ79_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ7a_NAME
#define OS_IRQ7a_NAME		OS_Ivector_7a
#define OS_IRQ7a_BISRPRIO	255
#define OS_IRQ7a_ISRID		122
#define OS_IRQ7a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ7a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ7b_NAME
#define OS_IRQ7b_NAME		OS_Ivector_7b
#define OS_IRQ7b_BISRPRIO	255
#define OS_IRQ7b_ISRID		123
#define OS_IRQ7b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ7b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ7c_NAME
#define OS_IRQ7c_NAME		OS_Ivector_7c
#define OS_IRQ7c_BISRPRIO	255
#define OS_IRQ7c_ISRID		124
#define OS_IRQ7c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ7c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ7d_NAME
#define OS_IRQ7d_NAME		OS_Ivector_7d
#define OS_IRQ7d_BISRPRIO	255
#define OS_IRQ7d_ISRID		125
#define OS_IRQ7d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ7d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ7e_NAME
#define OS_IRQ7e_NAME		OS_Ivector_7e
#define OS_IRQ7e_BISRPRIO	255
#define OS_IRQ7e_ISRID		126
#define OS_IRQ7e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ7e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ7f_NAME
#define OS_IRQ7f_NAME		OS_Ivector_7f
#define OS_IRQ7f_BISRPRIO	255
#define OS_IRQ7f_ISRID		127
#define OS_IRQ7f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ7f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ80_NAME
#define OS_IRQ80_NAME		OS_Ivector_80
#define OS_IRQ80_BISRPRIO	255
#define OS_IRQ80_ISRID		128
#define OS_IRQ80_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ80_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ81_NAME
#define OS_IRQ81_NAME		OS_Ivector_81
#define OS_IRQ81_BISRPRIO	255
#define OS_IRQ81_ISRID		129
#define OS_IRQ81_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ81_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ82_NAME
#define OS_IRQ82_NAME		OS_Ivector_82
#define OS_IRQ82_BISRPRIO	255
#define OS_IRQ82_ISRID		130
#define OS_IRQ82_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ82_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ83_NAME
#define OS_IRQ83_NAME		OS_Ivector_83
#define OS_IRQ83_BISRPRIO	255
#define OS_IRQ83_ISRID		131
#define OS_IRQ83_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ83_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ84_NAME
#define OS_IRQ84_NAME		OS_Ivector_84
#define OS_IRQ84_BISRPRIO	255
#define OS_IRQ84_ISRID		132
#define OS_IRQ84_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ84_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ85_NAME
#define OS_IRQ85_NAME		OS_Ivector_85
#define OS_IRQ85_BISRPRIO	255
#define OS_IRQ85_ISRID		133
#define OS_IRQ85_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ85_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ86_NAME
#define OS_IRQ86_NAME		OS_Ivector_86
#define OS_IRQ86_BISRPRIO	255
#define OS_IRQ86_ISRID		134
#define OS_IRQ86_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ86_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ87_NAME
#define OS_IRQ87_NAME		OS_Ivector_87
#define OS_IRQ87_BISRPRIO	255
#define OS_IRQ87_ISRID		135
#define OS_IRQ87_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ87_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ88_NAME
#define OS_IRQ88_NAME		OS_Ivector_88
#define OS_IRQ88_BISRPRIO	255
#define OS_IRQ88_ISRID		136
#define OS_IRQ88_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ88_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ89_NAME
#define OS_IRQ89_NAME		OS_Ivector_89
#define OS_IRQ89_BISRPRIO	255
#define OS_IRQ89_ISRID		137
#define OS_IRQ89_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ89_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ8a_NAME
#define OS_IRQ8a_NAME		OS_Ivector_8a
#define OS_IRQ8a_BISRPRIO	255
#define OS_IRQ8a_ISRID		138
#define OS_IRQ8a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ8a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ8b_NAME
#define OS_IRQ8b_NAME		OS_Ivector_8b
#define OS_IRQ8b_BISRPRIO	255
#define OS_IRQ8b_ISRID		139
#define OS_IRQ8b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ8b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ8c_NAME
#define OS_IRQ8c_NAME		OS_Ivector_8c
#define OS_IRQ8c_BISRPRIO	255
#define OS_IRQ8c_ISRID		140
#define OS_IRQ8c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ8c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ8d_NAME
#define OS_IRQ8d_NAME		OS_Ivector_8d
#define OS_IRQ8d_BISRPRIO	255
#define OS_IRQ8d_ISRID		141
#define OS_IRQ8d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ8d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ8e_NAME
#define OS_IRQ8e_NAME		OS_Ivector_8e
#define OS_IRQ8e_BISRPRIO	255
#define OS_IRQ8e_ISRID		142
#define OS_IRQ8e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ8e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ8f_NAME
#define OS_IRQ8f_NAME		OS_Ivector_8f
#define OS_IRQ8f_BISRPRIO	255
#define OS_IRQ8f_ISRID		143
#define OS_IRQ8f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ8f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ90_NAME
#define OS_IRQ90_NAME		OS_Ivector_90
#define OS_IRQ90_BISRPRIO	255
#define OS_IRQ90_ISRID		144
#define OS_IRQ90_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ90_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ91_NAME
#define OS_IRQ91_NAME		OS_Ivector_91
#define OS_IRQ91_BISRPRIO	255
#define OS_IRQ91_ISRID		145
#define OS_IRQ91_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ91_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ92_NAME
#define OS_IRQ92_NAME		OS_Ivector_92
#define OS_IRQ92_BISRPRIO	255
#define OS_IRQ92_ISRID		146
#define OS_IRQ92_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ92_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ93_NAME
#define OS_IRQ93_NAME		OS_Ivector_93
#define OS_IRQ93_BISRPRIO	255
#define OS_IRQ93_ISRID		147
#define OS_IRQ93_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ93_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ94_NAME
#define OS_IRQ94_NAME		OS_Ivector_94
#define OS_IRQ94_BISRPRIO	255
#define OS_IRQ94_ISRID		148
#define OS_IRQ94_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ94_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ95_NAME
#define OS_IRQ95_NAME		OS_Ivector_95
#define OS_IRQ95_BISRPRIO	255
#define OS_IRQ95_ISRID		149
#define OS_IRQ95_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ95_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ96_NAME
#define OS_IRQ96_NAME		OS_Ivector_96
#define OS_IRQ96_BISRPRIO	255
#define OS_IRQ96_ISRID		150
#define OS_IRQ96_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ96_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ97_NAME
#define OS_IRQ97_NAME		OS_Ivector_97
#define OS_IRQ97_BISRPRIO	255
#define OS_IRQ97_ISRID		151
#define OS_IRQ97_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ97_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ98_NAME
#define OS_IRQ98_NAME		OS_Ivector_98
#define OS_IRQ98_BISRPRIO	255
#define OS_IRQ98_ISRID		152
#define OS_IRQ98_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ98_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ99_NAME
#define OS_IRQ99_NAME		OS_Ivector_99
#define OS_IRQ99_BISRPRIO	255
#define OS_IRQ99_ISRID		153
#define OS_IRQ99_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ99_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ9a_NAME
#define OS_IRQ9a_NAME		OS_Ivector_9a
#define OS_IRQ9a_BISRPRIO	255
#define OS_IRQ9a_ISRID		154
#define OS_IRQ9a_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ9a_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ9b_NAME
#define OS_IRQ9b_NAME		OS_Ivector_9b
#define OS_IRQ9b_BISRPRIO	255
#define OS_IRQ9b_ISRID		155
#define OS_IRQ9b_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ9b_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ9c_NAME
#define OS_IRQ9c_NAME		OS_Ivector_9c
#define OS_IRQ9c_BISRPRIO	255
#define OS_IRQ9c_ISRID		156
#define OS_IRQ9c_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ9c_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ9d_NAME
#define OS_IRQ9d_NAME		OS_Ivector_9d
#define OS_IRQ9d_BISRPRIO	255
#define OS_IRQ9d_ISRID		157
#define OS_IRQ9d_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ9d_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ9e_NAME
#define OS_IRQ9e_NAME		OS_Ivector_9e
#define OS_IRQ9e_BISRPRIO	255
#define OS_IRQ9e_ISRID		158
#define OS_IRQ9e_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ9e_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQ9f_NAME
#define OS_IRQ9f_NAME		OS_Ivector_9f
#define OS_IRQ9f_BISRPRIO	255
#define OS_IRQ9f_ISRID		159
#define OS_IRQ9f_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQ9f_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa0_NAME
#define OS_IRQa0_NAME		OS_Ivector_a0
#define OS_IRQa0_BISRPRIO	255
#define OS_IRQa0_ISRID		160
#define OS_IRQa0_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa0_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa1_NAME
#define OS_IRQa1_NAME		OS_Ivector_a1
#define OS_IRQa1_BISRPRIO	255
#define OS_IRQa1_ISRID		161
#define OS_IRQa1_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa1_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa2_NAME
#define OS_IRQa2_NAME		OS_Ivector_a2
#define OS_IRQa2_BISRPRIO	255
#define OS_IRQa2_ISRID		162
#define OS_IRQa2_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa2_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa3_NAME
#define OS_IRQa3_NAME		OS_Ivector_a3
#define OS_IRQa3_BISRPRIO	255
#define OS_IRQa3_ISRID		163
#define OS_IRQa3_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa3_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa4_NAME
#define OS_IRQa4_NAME		OS_Ivector_a4
#define OS_IRQa4_BISRPRIO	255
#define OS_IRQa4_ISRID		164
#define OS_IRQa4_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa4_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa5_NAME
#define OS_IRQa5_NAME		OS_Ivector_a5
#define OS_IRQa5_BISRPRIO	255
#define OS_IRQa5_ISRID		165
#define OS_IRQa5_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa5_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa6_NAME
#define OS_IRQa6_NAME		OS_Ivector_a6
#define OS_IRQa6_BISRPRIO	255
#define OS_IRQa6_ISRID		166
#define OS_IRQa6_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa6_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa7_NAME
#define OS_IRQa7_NAME		OS_Ivector_a7
#define OS_IRQa7_BISRPRIO	255
#define OS_IRQa7_ISRID		167
#define OS_IRQa7_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa7_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa8_NAME
#define OS_IRQa8_NAME		OS_Ivector_a8
#define OS_IRQa8_BISRPRIO	255
#define OS_IRQa8_ISRID		168
#define OS_IRQa8_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa8_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQa9_NAME
#define OS_IRQa9_NAME		OS_Ivector_a9
#define OS_IRQa9_BISRPRIO	255
#define OS_IRQa9_ISRID		169
#define OS_IRQa9_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQa9_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQaa_NAME
#define OS_IRQaa_NAME		OS_Ivector_aa
#define OS_IRQaa_BISRPRIO	255
#define OS_IRQaa_ISRID		170
#define OS_IRQaa_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQaa_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQab_NAME
#define OS_IRQab_NAME		OS_Ivector_ab
#define OS_IRQab_BISRPRIO	255
#define OS_IRQab_ISRID		171
#define OS_IRQab_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQab_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQac_NAME
#define OS_IRQac_NAME		OS_Ivector_ac
#define OS_IRQac_BISRPRIO	255
#define OS_IRQac_ISRID		172
#define OS_IRQac_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQac_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQad_NAME
#define OS_IRQad_NAME		OS_Ivector_ad
#define OS_IRQad_BISRPRIO	255
#define OS_IRQad_ISRID		173
#define OS_IRQad_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQad_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQae_NAME
#define OS_IRQae_NAME		OS_Ivector_ae
#define OS_IRQae_BISRPRIO	255
#define OS_IRQae_ISRID		174
#define OS_IRQae_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQae_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQaf_NAME
#define OS_IRQaf_NAME		OS_Ivector_af
#define OS_IRQaf_BISRPRIO	255
#define OS_IRQaf_ISRID		175
#define OS_IRQaf_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQaf_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb0_NAME
#define OS_IRQb0_NAME		OS_Ivector_b0
#define OS_IRQb0_BISRPRIO	255
#define OS_IRQb0_ISRID		176
#define OS_IRQb0_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb0_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb1_NAME
#define OS_IRQb1_NAME		OS_Ivector_b1
#define OS_IRQb1_BISRPRIO	255
#define OS_IRQb1_ISRID		177
#define OS_IRQb1_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb1_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb2_NAME
#define OS_IRQb2_NAME		OS_Ivector_b2
#define OS_IRQb2_BISRPRIO	255
#define OS_IRQb2_ISRID		178
#define OS_IRQb2_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb2_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb3_NAME
#define OS_IRQb3_NAME		OS_Ivector_b3
#define OS_IRQb3_BISRPRIO	255
#define OS_IRQb3_ISRID		179
#define OS_IRQb3_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb3_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb4_NAME
#define OS_IRQb4_NAME		OS_Ivector_b4
#define OS_IRQb4_BISRPRIO	255
#define OS_IRQb4_ISRID		180
#define OS_IRQb4_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb4_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb5_NAME
#define OS_IRQb5_NAME		OS_Ivector_b5
#define OS_IRQb5_BISRPRIO	255
#define OS_IRQb5_ISRID		181
#define OS_IRQb5_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb5_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb6_NAME
#define OS_IRQb6_NAME		OS_Ivector_b6
#define OS_IRQb6_BISRPRIO	255
#define OS_IRQb6_ISRID		182
#define OS_IRQb6_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb6_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb7_NAME
#define OS_IRQb7_NAME		OS_Ivector_b7
#define OS_IRQb7_BISRPRIO	255
#define OS_IRQb7_ISRID		183
#define OS_IRQb7_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb7_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb8_NAME
#define OS_IRQb8_NAME		OS_Ivector_b8
#define OS_IRQb8_BISRPRIO	255
#define OS_IRQb8_ISRID		184
#define OS_IRQb8_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb8_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQb9_NAME
#define OS_IRQb9_NAME		OS_Ivector_b9
#define OS_IRQb9_BISRPRIO	255
#define OS_IRQb9_ISRID		185
#define OS_IRQb9_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQb9_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQba_NAME
#define OS_IRQba_NAME		OS_Ivector_ba
#define OS_IRQba_BISRPRIO	255
#define OS_IRQba_ISRID		186
#define OS_IRQba_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQba_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQbb_NAME
#define OS_IRQbb_NAME		OS_Ivector_bb
#define OS_IRQbb_BISRPRIO	255
#define OS_IRQbb_ISRID		187
#define OS_IRQbb_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQbb_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQbc_NAME
#define OS_IRQbc_NAME		OS_Ivector_bc
#define OS_IRQbc_BISRPRIO	255
#define OS_IRQbc_ISRID		188
#define OS_IRQbc_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQbc_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQbd_NAME
#define OS_IRQbd_NAME		OS_Ivector_bd
#define OS_IRQbd_BISRPRIO	255
#define OS_IRQbd_ISRID		189
#define OS_IRQbd_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQbd_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQbe_NAME
#define OS_IRQbe_NAME		OS_Ivector_be
#define OS_IRQbe_BISRPRIO	255
#define OS_IRQbe_ISRID		190
#define OS_IRQbe_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQbe_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQbf_NAME
#define OS_IRQbf_NAME		OS_Ivector_bf
#define OS_IRQbf_BISRPRIO	255
#define OS_IRQbf_ISRID		191
#define OS_IRQbf_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQbf_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc0_NAME
#define OS_IRQc0_NAME		OS_Ivector_c0
#define OS_IRQc0_BISRPRIO	255
#define OS_IRQc0_ISRID		192
#define OS_IRQc0_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc0_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc1_NAME
#define OS_IRQc1_NAME		OS_Ivector_c1
#define OS_IRQc1_BISRPRIO	255
#define OS_IRQc1_ISRID		193
#define OS_IRQc1_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc1_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc2_NAME
#define OS_IRQc2_NAME		OS_Ivector_c2
#define OS_IRQc2_BISRPRIO	255
#define OS_IRQc2_ISRID		194
#define OS_IRQc2_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc2_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc3_NAME
#define OS_IRQc3_NAME		OS_Ivector_c3
#define OS_IRQc3_BISRPRIO	255
#define OS_IRQc3_ISRID		195
#define OS_IRQc3_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc3_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc4_NAME
#define OS_IRQc4_NAME		OS_Ivector_c4
#define OS_IRQc4_BISRPRIO	255
#define OS_IRQc4_ISRID		196
#define OS_IRQc4_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc4_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc5_NAME
#define OS_IRQc5_NAME		OS_Ivector_c5
#define OS_IRQc5_BISRPRIO	255
#define OS_IRQc5_ISRID		197
#define OS_IRQc5_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc5_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc6_NAME
#define OS_IRQc6_NAME		OS_Ivector_c6
#define OS_IRQc6_BISRPRIO	255
#define OS_IRQc6_ISRID		198
#define OS_IRQc6_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc6_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc7_NAME
#define OS_IRQc7_NAME		OS_Ivector_c7
#define OS_IRQc7_BISRPRIO	255
#define OS_IRQc7_ISRID		199
#define OS_IRQc7_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc7_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc8_NAME
#define OS_IRQc8_NAME		OS_Ivector_c8
#define OS_IRQc8_BISRPRIO	255
#define OS_IRQc8_ISRID		200
#define OS_IRQc8_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc8_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQc9_NAME
#define OS_IRQc9_NAME		OS_Ivector_c9
#define OS_IRQc9_BISRPRIO	255
#define OS_IRQc9_ISRID		201
#define OS_IRQc9_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQc9_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQca_NAME
#define OS_IRQca_NAME		OS_Ivector_ca
#define OS_IRQca_BISRPRIO	255
#define OS_IRQca_ISRID		202
#define OS_IRQca_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQca_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQcb_NAME
#define OS_IRQcb_NAME		OS_Ivector_cb
#define OS_IRQcb_BISRPRIO	255
#define OS_IRQcb_ISRID		203
#define OS_IRQcb_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQcb_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQcc_NAME
#define OS_IRQcc_NAME		OS_Ivector_cc
#define OS_IRQcc_BISRPRIO	255
#define OS_IRQcc_ISRID		204
#define OS_IRQcc_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQcc_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQcd_NAME
#define OS_IRQcd_NAME		OS_Ivector_cd
#define OS_IRQcd_BISRPRIO	255
#define OS_IRQcd_ISRID		205
#define OS_IRQcd_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQcd_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQce_NAME
#define OS_IRQce_NAME		OS_Ivector_ce
#define OS_IRQce_BISRPRIO	255
#define OS_IRQce_ISRID		206
#define OS_IRQce_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQce_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQcf_NAME
#define OS_IRQcf_NAME		OS_Ivector_cf
#define OS_IRQcf_BISRPRIO	255
#define OS_IRQcf_ISRID		207
#define OS_IRQcf_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQcf_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd0_NAME
#define OS_IRQd0_NAME		OS_Ivector_d0
#define OS_IRQd0_BISRPRIO	255
#define OS_IRQd0_ISRID		208
#define OS_IRQd0_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd0_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd1_NAME
#define OS_IRQd1_NAME		OS_Ivector_d1
#define OS_IRQd1_BISRPRIO	255
#define OS_IRQd1_ISRID		209
#define OS_IRQd1_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd1_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd2_NAME
#define OS_IRQd2_NAME		OS_Ivector_d2
#define OS_IRQd2_BISRPRIO	255
#define OS_IRQd2_ISRID		210
#define OS_IRQd2_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd2_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd3_NAME
#define OS_IRQd3_NAME		OS_Ivector_d3
#define OS_IRQd3_BISRPRIO	255
#define OS_IRQd3_ISRID		211
#define OS_IRQd3_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd3_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd4_NAME
#define OS_IRQd4_NAME		OS_Ivector_d4
#define OS_IRQd4_BISRPRIO	255
#define OS_IRQd4_ISRID		212
#define OS_IRQd4_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd4_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd5_NAME
#define OS_IRQd5_NAME		OS_Ivector_d5
#define OS_IRQd5_BISRPRIO	255
#define OS_IRQd5_ISRID		213
#define OS_IRQd5_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd5_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd6_NAME
#define OS_IRQd6_NAME		OS_Ivector_d6
#define OS_IRQd6_BISRPRIO	255
#define OS_IRQd6_ISRID		214
#define OS_IRQd6_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd6_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd7_NAME
#define OS_IRQd7_NAME		OS_Ivector_d7
#define OS_IRQd7_BISRPRIO	255
#define OS_IRQd7_ISRID		215
#define OS_IRQd7_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd7_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd8_NAME
#define OS_IRQd8_NAME		OS_Ivector_d8
#define OS_IRQd8_BISRPRIO	255
#define OS_IRQd8_ISRID		216
#define OS_IRQd8_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd8_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQd9_NAME
#define OS_IRQd9_NAME		OS_Ivector_d9
#define OS_IRQd9_BISRPRIO	255
#define OS_IRQd9_ISRID		217
#define OS_IRQd9_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQd9_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQda_NAME
#define OS_IRQda_NAME		OS_Ivector_da
#define OS_IRQda_BISRPRIO	255
#define OS_IRQda_ISRID		218
#define OS_IRQda_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQda_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQdb_NAME
#define OS_IRQdb_NAME		OS_Ivector_db
#define OS_IRQdb_BISRPRIO	255
#define OS_IRQdb_ISRID		219
#define OS_IRQdb_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQdb_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQdc_NAME
#define OS_IRQdc_NAME		OS_Ivector_dc
#define OS_IRQdc_BISRPRIO	255
#define OS_IRQdc_ISRID		220
#define OS_IRQdc_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQdc_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQdd_NAME
#define OS_IRQdd_NAME		OS_Ivector_dd
#define OS_IRQdd_BISRPRIO	255
#define OS_IRQdd_ISRID		221
#define OS_IRQdd_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQdd_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQde_NAME
#define OS_IRQde_NAME		OS_Ivector_de
#define OS_IRQde_BISRPRIO	255
#define OS_IRQde_ISRID		222
#define OS_IRQde_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQde_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQdf_NAME
#define OS_IRQdf_NAME		OS_Ivector_df
#define OS_IRQdf_BISRPRIO	255
#define OS_IRQdf_ISRID		223
#define OS_IRQdf_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQdf_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe0_NAME
#define OS_IRQe0_NAME		OS_Ivector_e0
#define OS_IRQe0_BISRPRIO	255
#define OS_IRQe0_ISRID		224
#define OS_IRQe0_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe0_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe1_NAME
#define OS_IRQe1_NAME		OS_Ivector_e1
#define OS_IRQe1_BISRPRIO	255
#define OS_IRQe1_ISRID		225
#define OS_IRQe1_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe1_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe2_NAME
#define OS_IRQe2_NAME		OS_Ivector_e2
#define OS_IRQe2_BISRPRIO	255
#define OS_IRQe2_ISRID		226
#define OS_IRQe2_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe2_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe3_NAME
#define OS_IRQe3_NAME		OS_Ivector_e3
#define OS_IRQe3_BISRPRIO	255
#define OS_IRQe3_ISRID		227
#define OS_IRQe3_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe3_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe4_NAME
#define OS_IRQe4_NAME		OS_Ivector_e4
#define OS_IRQe4_BISRPRIO	255
#define OS_IRQe4_ISRID		228
#define OS_IRQe4_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe4_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe5_NAME
#define OS_IRQe5_NAME		OS_Ivector_e5
#define OS_IRQe5_BISRPRIO	255
#define OS_IRQe5_ISRID		229
#define OS_IRQe5_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe5_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe6_NAME
#define OS_IRQe6_NAME		OS_Ivector_e6
#define OS_IRQe6_BISRPRIO	255
#define OS_IRQe6_ISRID		230
#define OS_IRQe6_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe6_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe7_NAME
#define OS_IRQe7_NAME		OS_Ivector_e7
#define OS_IRQe7_BISRPRIO	255
#define OS_IRQe7_ISRID		231
#define OS_IRQe7_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe7_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe8_NAME
#define OS_IRQe8_NAME		OS_Ivector_e8
#define OS_IRQe8_BISRPRIO	255
#define OS_IRQe8_ISRID		232
#define OS_IRQe8_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe8_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQe9_NAME
#define OS_IRQe9_NAME		OS_Ivector_e9
#define OS_IRQe9_BISRPRIO	255
#define OS_IRQe9_ISRID		233
#define OS_IRQe9_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQe9_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQea_NAME
#define OS_IRQea_NAME		OS_Ivector_ea
#define OS_IRQea_BISRPRIO	255
#define OS_IRQea_ISRID		234
#define OS_IRQea_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQea_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQeb_NAME
#define OS_IRQeb_NAME		OS_Ivector_eb
#define OS_IRQeb_BISRPRIO	255
#define OS_IRQeb_ISRID		235
#define OS_IRQeb_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQeb_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQec_NAME
#define OS_IRQec_NAME		OS_Ivector_ec
#define OS_IRQec_BISRPRIO	255
#define OS_IRQec_ISRID		236
#define OS_IRQec_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQec_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQed_NAME
#define OS_IRQed_NAME		OS_Ivector_ed
#define OS_IRQed_BISRPRIO	255
#define OS_IRQed_ISRID		237
#define OS_IRQed_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQed_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQee_NAME
#define OS_IRQee_NAME		OS_Ivector_ee
#define OS_IRQee_BISRPRIO	255
#define OS_IRQee_ISRID		238
#define OS_IRQee_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQee_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQef_NAME
#define OS_IRQef_NAME		OS_Ivector_ef
#define OS_IRQef_BISRPRIO	255
#define OS_IRQef_ISRID		239
#define OS_IRQef_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQef_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf0_NAME
#define OS_IRQf0_NAME		OS_Ivector_f0
#define OS_IRQf0_BISRPRIO	255
#define OS_IRQf0_ISRID		240
#define OS_IRQf0_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf0_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf1_NAME
#define OS_IRQf1_NAME		OS_Ivector_f1
#define OS_IRQf1_BISRPRIO	255
#define OS_IRQf1_ISRID		241
#define OS_IRQf1_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf1_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf2_NAME
#define OS_IRQf2_NAME		OS_Ivector_f2
#define OS_IRQf2_BISRPRIO	255
#define OS_IRQf2_ISRID		242
#define OS_IRQf2_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf2_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf3_NAME
#define OS_IRQf3_NAME		OS_Ivector_f3
#define OS_IRQf3_BISRPRIO	255
#define OS_IRQf3_ISRID		243
#define OS_IRQf3_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf3_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf4_NAME
#define OS_IRQf4_NAME		OS_Ivector_f4
#define OS_IRQf4_BISRPRIO	255
#define OS_IRQf4_ISRID		244
#define OS_IRQf4_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf4_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf5_NAME
#define OS_IRQf5_NAME		OS_Ivector_f5
#define OS_IRQf5_BISRPRIO	255
#define OS_IRQf5_ISRID		245
#define OS_IRQf5_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf5_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf6_NAME
#define OS_IRQf6_NAME		OS_Ivector_f6
#define OS_IRQf6_BISRPRIO	255
#define OS_IRQf6_ISRID		246
#define OS_IRQf6_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf6_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf7_NAME
#define OS_IRQf7_NAME		OS_Ivector_f7
#define OS_IRQf7_BISRPRIO	255
#define OS_IRQf7_ISRID		247
#define OS_IRQf7_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf7_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf8_NAME
#define OS_IRQf8_NAME		OS_Ivector_f8
#define OS_IRQf8_BISRPRIO	255
#define OS_IRQf8_ISRID		248
#define OS_IRQf8_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf8_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQf9_NAME
#define OS_IRQf9_NAME		OS_Ivector_f9
#define OS_IRQf9_BISRPRIO	255
#define OS_IRQf9_ISRID		249
#define OS_IRQf9_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQf9_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQfa_NAME
#define OS_IRQfa_NAME		OS_Ivector_fa
#define OS_IRQfa_BISRPRIO	255
#define OS_IRQfa_ISRID		250
#define OS_IRQfa_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQfa_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQfb_NAME
#define OS_IRQfb_NAME		OS_Ivector_fb
#define OS_IRQfb_BISRPRIO	255
#define OS_IRQfb_ISRID		251
#define OS_IRQfb_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQfb_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQfc_NAME
#define OS_IRQfc_NAME		OS_Ivector_fc
#define OS_IRQfc_BISRPRIO	255
#define OS_IRQfc_ISRID		252
#define OS_IRQfc_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQfc_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQfd_NAME
#define OS_IRQfd_NAME		OS_Ivector_fd
#define OS_IRQfd_BISRPRIO	255
#define OS_IRQfd_ISRID		253
#define OS_IRQfd_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQfd_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQfe_NAME
#define OS_IRQfe_NAME		OS_Ivector_fe
#define OS_IRQfe_BISRPRIO	255
#define OS_IRQfe_ISRID		254
#define OS_IRQfe_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQfe_EXIT		OS_NullFunction
#endif

#ifndef OS_IRQff_NAME
#define OS_IRQff_NAME		OS_Ivector_ff
#define OS_IRQff_BISRPRIO	255
#define OS_IRQff_ISRID		255
#define OS_IRQff_ENTRY		OS_UnknownInterruptHandler
#define OS_IRQff_EXIT		OS_NullFunction
#endif

/*!
 * OS_interruptTable
 *
 * Interrupt vectors
*/
#if (OS_TOOL==OS_tasking)
		.sdecl	"OS_InterruptVectors",code
		.sect	"OS_InterruptVectors"
#else
		.section	"OS_InterruptVectors","a"
#endif

	_GLOBAL		OS_interruptTable
	_GTYPE(OS_interruptTable,@function)
	_EXTERN		boot					/* In boardAsm.s */

	_align(OS_INTVEC_ALIGN_ABS,OS_INTVEC_ALIGN_EXP)

/*!
 * Vector 0 is a jump to the startup code, so that the vector table can
 * be located at the reset address.
*/
_TTYPE(OS_interruptTable,FUNC)
/* Interrupt vector 0 can never be reached by an interrupt. A jump to the
 * boot address and the BOARD_TRICORE_BOOTWORD are placed here so that the
 * interrupt vector table can be placed at the ROM boot location, which
 * is often a very good place for alignment reasons.
*/
	j	boot
	.word	BOARD_TRICORE_BOOTWORD

/* Interrupt vectors 1 to 3 (0x01 to 0x03).
*/
#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ01_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(01)
#else
	GENVECTOR(01)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ02_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(02)
#else
	GENVECTOR(02)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ03_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(03)
#else
	GENVECTOR(03)
#endif


/* Interrupt vectors 4 to 15 (0x04 to 0x0f).
*/
#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ04_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(04)
#else
	GENVECTOR(04)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ05_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(05)
#else
	GENVECTOR(05)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ06_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(06)
#else
	GENVECTOR(06)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ07_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(07)
#else
	GENVECTOR(07)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ08_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(08)
#else
	GENVECTOR(08)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ09_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(09)
#else
	GENVECTOR(09)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ0a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(0a)
#else
	GENVECTOR(0a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ0b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(0b)
#else
	GENVECTOR(0b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ0c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(0c)
#else
	GENVECTOR(0c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ0d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(0d)
#else
	GENVECTOR(0d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ0e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(0e)
#else
	GENVECTOR(0e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ0f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(0f)
#else
	GENVECTOR(0f)
#endif

/* Interrupt vectors 16 to 63 (0x10 to 0x3f).
*/
#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ10_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(10)
#else
	GENVECTOR(10)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ11_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(11)
#else
	GENVECTOR(11)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ12_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(12)
#else
	GENVECTOR(12)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ13_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(13)
#else
	GENVECTOR(13)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ14_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(14)
#else
	GENVECTOR(14)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ15_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(15)
#else
	GENVECTOR(15)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ16_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(16)
#else
	GENVECTOR(16)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ17_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(17)
#else
	GENVECTOR(17)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ18_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(18)
#else
	GENVECTOR(18)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ19_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(19)
#else
	GENVECTOR(19)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ1a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(1a)
#else
	GENVECTOR(1a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ1b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(1b)
#else
	GENVECTOR(1b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ1c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(1c)
#else
	GENVECTOR(1c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ1d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(1d)
#else
	GENVECTOR(1d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ1e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(1e)
#else
	GENVECTOR(1e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ1f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(1f)
#else
	GENVECTOR(1f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ20_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(20)
#else
	GENVECTOR(20)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ21_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(21)
#else
	GENVECTOR(21)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ22_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(22)
#else
	GENVECTOR(22)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ23_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(23)
#else
	GENVECTOR(23)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ24_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(24)
#else
	GENVECTOR(24)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ25_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(25)
#else
	GENVECTOR(25)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ26_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(26)
#else
	GENVECTOR(26)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ27_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(27)
#else
	GENVECTOR(27)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ28_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(28)
#else
	GENVECTOR(28)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ29_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(29)
#else
	GENVECTOR(29)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ2a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(2a)
#else
	GENVECTOR(2a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ2b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(2b)
#else
	GENVECTOR(2b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ2c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(2c)
#else
	GENVECTOR(2c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ2d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(2d)
#else
	GENVECTOR(2d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ2e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(2e)
#else
	GENVECTOR(2e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ2f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(2f)
#else
	GENVECTOR(2f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ30_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(30)
#else
	GENVECTOR(30)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ31_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(31)
#else
	GENVECTOR(31)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ32_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(32)
#else
	GENVECTOR(32)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ33_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(33)
#else
	GENVECTOR(33)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ34_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(34)
#else
	GENVECTOR(34)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ35_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(35)
#else
	GENVECTOR(35)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ36_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(36)
#else
	GENVECTOR(36)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ37_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(37)
#else
	GENVECTOR(37)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ38_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(38)
#else
	GENVECTOR(38)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ39_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(39)
#else
	GENVECTOR(39)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ3a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(3a)
#else
	GENVECTOR(3a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ3b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(3b)
#else
	GENVECTOR(3b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ3c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(3c)
#else
	GENVECTOR(3c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ3d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(3d)
#else
	GENVECTOR(3d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ3e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(3e)
#else
	GENVECTOR(3e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ3f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(3f)
#else
	GENVECTOR(3f)
#endif

/* Interrupt vectors 64 to 255 (0x40 to 0xff).
*/
#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ40_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(40)
#else
	GENVECTOR(40)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ41_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(41)
#else
	GENVECTOR(41)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ42_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(42)
#else
	GENVECTOR(42)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ43_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(43)
#else
	GENVECTOR(43)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ44_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(44)
#else
	GENVECTOR(44)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ45_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(45)
#else
	GENVECTOR(45)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ46_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(46)
#else
	GENVECTOR(46)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ47_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(47)
#else
	GENVECTOR(47)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ48_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(48)
#else
	GENVECTOR(48)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ49_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(49)
#else
	GENVECTOR(49)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ4a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(4a)
#else
	GENVECTOR(4a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ4b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(4b)
#else
	GENVECTOR(4b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ4c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(4c)
#else
	GENVECTOR(4c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ4d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(4d)
#else
	GENVECTOR(4d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ4e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(4e)
#else
	GENVECTOR(4e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ4f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(4f)
#else
	GENVECTOR(4f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ50_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(50)
#else
	GENVECTOR(50)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ51_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(51)
#else
	GENVECTOR(51)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ52_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(52)
#else
	GENVECTOR(52)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ53_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(53)
#else
	GENVECTOR(53)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ54_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(54)
#else
	GENVECTOR(54)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ55_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(55)
#else
	GENVECTOR(55)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ56_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(56)
#else
	GENVECTOR(56)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ57_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(57)
#else
	GENVECTOR(57)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ58_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(58)
#else
	GENVECTOR(58)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ59_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(59)
#else
	GENVECTOR(59)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ5a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(5a)
#else
	GENVECTOR(5a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ5b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(5b)
#else
	GENVECTOR(5b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ5c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(5c)
#else
	GENVECTOR(5c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ5d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(5d)
#else
	GENVECTOR(5d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ5e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(5e)
#else
	GENVECTOR(5e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ5f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(5f)
#else
	GENVECTOR(5f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ60_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(60)
#else
	GENVECTOR(60)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ61_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(61)
#else
	GENVECTOR(61)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ62_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(62)
#else
	GENVECTOR(62)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ63_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(63)
#else
	GENVECTOR(63)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ64_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(64)
#else
	GENVECTOR(64)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ65_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(65)
#else
	GENVECTOR(65)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ66_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(66)
#else
	GENVECTOR(66)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ67_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(67)
#else
	GENVECTOR(67)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ68_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(68)
#else
	GENVECTOR(68)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ69_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(69)
#else
	GENVECTOR(69)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ6a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(6a)
#else
	GENVECTOR(6a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ6b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(6b)
#else
	GENVECTOR(6b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ6c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(6c)
#else
	GENVECTOR(6c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ6d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(6d)
#else
	GENVECTOR(6d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ6e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(6e)
#else
	GENVECTOR(6e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ6f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(6f)
#else
	GENVECTOR(6f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ70_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(70)
#else
	GENVECTOR(70)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ71_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(71)
#else
	GENVECTOR(71)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ72_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(72)
#else
	GENVECTOR(72)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ73_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(73)
#else
	GENVECTOR(73)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ74_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(74)
#else
	GENVECTOR(74)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ75_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(75)
#else
	GENVECTOR(75)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ76_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(76)
#else
	GENVECTOR(76)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ77_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(77)
#else
	GENVECTOR(77)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ78_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(78)
#else
	GENVECTOR(78)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ79_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(79)
#else
	GENVECTOR(79)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ7a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(7a)
#else
	GENVECTOR(7a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ7b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(7b)
#else
	GENVECTOR(7b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ7c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(7c)
#else
	GENVECTOR(7c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ7d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(7d)
#else
	GENVECTOR(7d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ7e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(7e)
#else
	GENVECTOR(7e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ7f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(7f)
#else
	GENVECTOR(7f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ80_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(80)
#else
	GENVECTOR(80)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ81_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(81)
#else
	GENVECTOR(81)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ82_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(82)
#else
	GENVECTOR(82)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ83_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(83)
#else
	GENVECTOR(83)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ84_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(84)
#else
	GENVECTOR(84)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ85_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(85)
#else
	GENVECTOR(85)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ86_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(86)
#else
	GENVECTOR(86)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ87_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(87)
#else
	GENVECTOR(87)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ88_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(88)
#else
	GENVECTOR(88)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ89_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(89)
#else
	GENVECTOR(89)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ8a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(8a)
#else
	GENVECTOR(8a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ8b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(8b)
#else
	GENVECTOR(8b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ8c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(8c)
#else
	GENVECTOR(8c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ8d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(8d)
#else
	GENVECTOR(8d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ8e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(8e)
#else
	GENVECTOR(8e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ8f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(8f)
#else
	GENVECTOR(8f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ90_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(90)
#else
	GENVECTOR(90)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ91_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(91)
#else
	GENVECTOR(91)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ92_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(92)
#else
	GENVECTOR(92)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ93_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(93)
#else
	GENVECTOR(93)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ94_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(94)
#else
	GENVECTOR(94)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ95_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(95)
#else
	GENVECTOR(95)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ96_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(96)
#else
	GENVECTOR(96)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ97_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(97)
#else
	GENVECTOR(97)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ98_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(98)
#else
	GENVECTOR(98)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ99_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(99)
#else
	GENVECTOR(99)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ9a_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(9a)
#else
	GENVECTOR(9a)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ9b_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(9b)
#else
	GENVECTOR(9b)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ9c_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(9c)
#else
	GENVECTOR(9c)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ9d_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(9d)
#else
	GENVECTOR(9d)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ9e_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(9e)
#else
	GENVECTOR(9e)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQ9f_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(9f)
#else
	GENVECTOR(9f)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa0_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a0)
#else
	GENVECTOR(a0)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa1_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a1)
#else
	GENVECTOR(a1)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa2_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a2)
#else
	GENVECTOR(a2)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa3_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a3)
#else
	GENVECTOR(a3)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa4_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a4)
#else
	GENVECTOR(a4)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa5_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a5)
#else
	GENVECTOR(a5)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa6_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a6)
#else
	GENVECTOR(a6)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa7_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a7)
#else
	GENVECTOR(a7)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa8_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a8)
#else
	GENVECTOR(a8)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQa9_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(a9)
#else
	GENVECTOR(a9)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQaa_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(aa)
#else
	GENVECTOR(aa)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQab_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ab)
#else
	GENVECTOR(ab)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQac_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ac)
#else
	GENVECTOR(ac)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQad_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ad)
#else
	GENVECTOR(ad)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQae_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ae)
#else
	GENVECTOR(ae)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQaf_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(af)
#else
	GENVECTOR(af)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb0_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b0)
#else
	GENVECTOR(b0)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb1_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b1)
#else
	GENVECTOR(b1)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb2_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b2)
#else
	GENVECTOR(b2)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb3_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b3)
#else
	GENVECTOR(b3)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb4_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b4)
#else
	GENVECTOR(b4)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb5_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b5)
#else
	GENVECTOR(b5)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb6_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b6)
#else
	GENVECTOR(b6)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb7_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b7)
#else
	GENVECTOR(b7)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb8_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b8)
#else
	GENVECTOR(b8)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQb9_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(b9)
#else
	GENVECTOR(b9)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQba_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ba)
#else
	GENVECTOR(ba)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQbb_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(bb)
#else
	GENVECTOR(bb)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQbc_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(bc)
#else
	GENVECTOR(bc)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQbd_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(bd)
#else
	GENVECTOR(bd)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQbe_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(be)
#else
	GENVECTOR(be)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQbf_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(bf)
#else
	GENVECTOR(bf)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc0_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c0)
#else
	GENVECTOR(c0)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc1_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c1)
#else
	GENVECTOR(c1)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc2_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c2)
#else
	GENVECTOR(c2)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc3_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c3)
#else
	GENVECTOR(c3)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc4_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c4)
#else
	GENVECTOR(c4)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc5_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c5)
#else
	GENVECTOR(c5)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc6_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c6)
#else
	GENVECTOR(c6)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc7_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c7)
#else
	GENVECTOR(c7)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc8_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c8)
#else
	GENVECTOR(c8)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQc9_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(c9)
#else
	GENVECTOR(c9)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQca_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ca)
#else
	GENVECTOR(ca)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQcb_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(cb)
#else
	GENVECTOR(cb)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQcc_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(cc)
#else
	GENVECTOR(cc)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQcd_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(cd)
#else
	GENVECTOR(cd)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQce_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ce)
#else
	GENVECTOR(ce)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQcf_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(cf)
#else
	GENVECTOR(cf)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd0_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d0)
#else
	GENVECTOR(d0)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd1_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d1)
#else
	GENVECTOR(d1)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd2_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d2)
#else
	GENVECTOR(d2)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd3_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d3)
#else
	GENVECTOR(d3)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd4_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d4)
#else
	GENVECTOR(d4)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd5_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d5)
#else
	GENVECTOR(d5)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd6_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d6)
#else
	GENVECTOR(d6)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd7_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d7)
#else
	GENVECTOR(d7)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd8_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d8)
#else
	GENVECTOR(d8)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQd9_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(d9)
#else
	GENVECTOR(d9)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQda_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(da)
#else
	GENVECTOR(da)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQdb_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(db)
#else
	GENVECTOR(db)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQdc_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(dc)
#else
	GENVECTOR(dc)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQdd_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(dd)
#else
	GENVECTOR(dd)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQde_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(de)
#else
	GENVECTOR(de)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQdf_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(df)
#else
	GENVECTOR(df)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe0_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e0)
#else
	GENVECTOR(e0)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe1_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e1)
#else
	GENVECTOR(e1)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe2_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e2)
#else
	GENVECTOR(e2)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe3_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e3)
#else
	GENVECTOR(e3)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe4_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e4)
#else
	GENVECTOR(e4)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe5_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e5)
#else
	GENVECTOR(e5)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe6_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e6)
#else
	GENVECTOR(e6)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe7_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e7)
#else
	GENVECTOR(e7)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe8_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e8)
#else
	GENVECTOR(e8)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQe9_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(e9)
#else
	GENVECTOR(e9)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQea_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ea)
#else
	GENVECTOR(ea)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQeb_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(eb)
#else
	GENVECTOR(eb)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQec_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ec)
#else
	GENVECTOR(ec)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQed_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ed)
#else
	GENVECTOR(ed)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQee_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ee)
#else
	GENVECTOR(ee)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQef_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ef)
#else
	GENVECTOR(ef)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf0_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f0)
#else
	GENVECTOR(f0)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf1_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f1)
#else
	GENVECTOR(f1)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf2_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f2)
#else
	GENVECTOR(f2)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf3_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f3)
#else
	GENVECTOR(f3)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf4_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f4)
#else
	GENVECTOR(f4)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf5_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f5)
#else
	GENVECTOR(f5)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf6_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f6)
#else
	GENVECTOR(f6)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf7_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f7)
#else
	GENVECTOR(f7)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf8_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f8)
#else
	GENVECTOR(f8)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQf9_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(f9)
#else
	GENVECTOR(f9)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQfa_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(fa)
#else
	GENVECTOR(fa)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQfb_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(fb)
#else
	GENVECTOR(fb)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQfc_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(fc)
#else
	GENVECTOR(fc)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQfd_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(fd)
#else
	GENVECTOR(fd)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQfe_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(fe)
#else
	GENVECTOR(fe)
#endif

#if (OS_CAT1_DIRECTCALL == 1) && (OS_IRQff_TYPE == OS_VECTOR_TYPE_CAT1)
	DIRECTVECTOR(ff)
#else
	GENVECTOR(ff)
#endif


#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
