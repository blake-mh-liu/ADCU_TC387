/* Os_defs.h
 *
 * This file contains definitions for the known architectures and toolchains,
 * for use when defining OS_TOOL and OS_ARCH.
 *
 * The Makefile must ensure that the OS_TOOL macro can be defined appropriately,
 * i.e. OSB_TOOL is defined on the command line.
 *
 * Example: -DOSB_TOOL=OSB_gnu
 *
 * Many architectures require the OS_CPU macro as well. The definitions
 * for the CPU are handled in the architecture-specific files. Overlap
 * of allocated numbers between architectures is not a problem, because
 * the architecture files will/should never be mixed.
 *
 * When compiling an assembler file with the C preprocessor, the macro
 * OS_ASM needs to be defined.
 *
 * The value 0 is never used in the TOOL list, because that is the
 * value that preprocessors often return for undefined symbols. In the
 * ARCH list the value 0 stands for NEWARCH, which is the template for
 * new architecture ports and doesn't exist as a real architecture.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_DEFS_H
#define OS_DEFS_H

#include <Os_usuffix.h>

#include <Os_hw.h>		/* OS_ARCH and OS_CPU */
#include <Os_kconfig.h>	/* Generated kernel config */

/* Macro for MISRA 10.1, 10.3 and 10.5.
*/
#define OS_ShiftLeft(type, value, index)	((type)((type)(value) << (index)))
#define OS_ShiftLeftU32(value, index)		OS_ShiftLeft(os_uint32_t, (value), (index))
#define OS_ShiftRight(type, value, index)	((type)((type)(value) >> (index)))
#define OS_ShiftRightU32(value, index)		OS_ShiftRight(os_uint32_t, (value), (index))


#ifndef OSB_TOOL
#error "OSB_TOOL is not defined. Check that your compiler options include -DOSB_TOOL=OSB_toolchain!"
#endif

/* Supported toolchains
 * In ProOSEK tradition, toolchain names in the makefiles are lowercase
 * CHECK: SAVE
 * CHECK: RULE 402 OFF (traditional naming)
*/
#define OSB_gnu			1
#define OSB_diab		2
#define OSB_tasking		3
#define OSB_ghs			4
#define OSB_cosmic		5
#define OSB_mwerks		6
#define OSB_softune		7
#define OSB_realview	8
#define OSB_iar			9
#define OSB_vc			10
#define OSB_renesas		11
#define OSB_cw			12
#define OSB_ticgt		13
#define OSB_mplabx		14
#define OSB_htgcc		15
#define OSB_armkeil		16
#define OSB_arm5		17
#define OSB_metaware	18
#define OSB_clang		19
/* CHECK: RESTORE
*/

#if (OSB_TOOL == OSB_gnu)
#define OS_TOOL OS_gnu
#elif (OSB_TOOL == OSB_clang)
#define OS_TOOL OS_clang
#elif (OSB_TOOL == OSB_diab)
#define OS_TOOL OS_diab
#elif (OSB_TOOL == OSB_tasking)
#define OS_TOOL OS_tasking
#elif (OSB_TOOL == OSB_ghs)
#define OS_TOOL OS_ghs
#elif (OSB_TOOL == OSB_cosmic)
#define OS_TOOL OS_cosmic
#elif (OSB_TOOL == OSB_mwerks)
#define OS_TOOL OS_mwerks
#elif (OSB_TOOL == OSB_softune)
#define OS_TOOL OS_softune
#elif (OSB_TOOL == OSB_realview)
#define OS_TOOL OS_realview
#elif (OSB_TOOL == OSB_iar)
#define OS_TOOL OS_iar
#elif (OSB_TOOL == OSB_vc)
#define OS_TOOL OS_vc
#elif (OSB_TOOL == OSB_renesas)
#define OS_TOOL OS_renesas
#elif (OSB_TOOL == OSB_cw)
#define OS_TOOL OS_cw
#elif (OSB_TOOL == OSB_ticgt)
#define OS_TOOL OS_ticgt
#elif (OSB_TOOL == OSB_mplabx)
#define OS_TOOL OS_mplabx
#elif (OSB_TOOL == OSB_htgcc)
#define OS_TOOL OS_htgcc
#elif (OSB_TOOL == OSB_armkeil)
#define OS_TOOL OS_armkeil
#elif (OSB_TOOL == OSB_arm5)
#define OS_TOOL OS_arm5
#elif (OSB_TOOL == OSB_metaware)
#define OS_TOOL OS_metaware
#else
#error "OSB_TOOL invalid. Check your compiler options!"
#endif


/* Supported toolchains
 * In ProOSEK tradition, toolchain names in the makefiles are lowercase
 * CHECK: SAVE
 * CHECK: RULE 402 OFF (traditional naming)
*/
#define OS_gnu			1
#define OS_diab			2
#define OS_tasking		3
#define OS_ghs			4
#define OS_cosmic		5
#define OS_mwerks		6
#define OS_softune		7
#define OS_realview		8
#define OS_iar			9
#define OS_vc			10
#define OS_renesas		11
#define OS_cw			12
#define OS_ticgt		13
#define OS_mplabx		14
#define OS_htgcc		15
#define OS_armkeil		16
#define OS_arm5			17
#define OS_metaware		18
#define OS_clang		19
/* CHECK: RESTORE
*/

/* Supported architectures. Not all toolchain/architecture combinations
 * are supported.
*/
#define OS_NEWARCH		0	/* For porting guide */
#define OS_PA			1
#define OS_TRICORE		2
#define OS_V850			3	/* obsolete */
#define OS_MB91			6	/* obsolete */
#define OS_WINDOWS		9
#define OS_ARM			11
#define OS_LINUX		13
#define OS_RH850		16
#define OS_CORTEXM		17
#define OS_ARM64		18
#define OS_ARC			19

/* Endianness. OS_ENDIAN must be one of these
*/
#define OS_LITTLEENDIAN	1
#define OS_BIGENDIAN	2

/* Stack direction. OS_STACKGROWS must be one of these
*/
#define OS_STACKGROWSDOWN	1
#define OS_STACKGROWSUP		2

/* Cache modes. OS_CACHE_MODE must be one of those.
 *
 * OS_CACHE_MODE_NONE
 *   No data caches are present or no cache maintenance operations are supported.
 * OS_CACHE_MODE_LINE
 *   Cache maintenance operations are performed on single cache lines. The size
 *   of a cache line is set by OS_CACHE_LINE_LEN.
 * OS_CACHE_MODE_BARRIER
 *   A barrier mechanism is used to drain and order all pending memory transactions.
 *   There are either no caches or they are consistent with all other memory.
*/
#define OS_CACHE_MODE_NONE		1
#define OS_CACHE_MODE_LINE		2
#define OS_CACHE_MODE_BARRIER	3

/* Kernel call type. OS_KERNEL_TYPE must be one of those
*/
#define	OS_FUNCTION_CALL	1
#define	OS_SYSTEM_CALL		2
#define	OS_MICROKERNEL		3

/* Toolchain-dependant implmentation detail: Needed as an assembler function
 * or supported by an inline assembly macro.
*/
#define OS_TOOL_ASM_FUNC	1
#define OS_TOOL_ASM_INLINE	2


/* Include CPU family-specific definitions.
 * This needs to be done after the common definitions, since the
 * common definitions are used here already.
*/
#include <Os_hwsel.h>
#include OS_HWSEL_DEFS

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

