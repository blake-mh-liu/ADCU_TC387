/* Os_configuration_TRICORE.c
 *
 * This file provides architecture-specific kernel configuration data
 * for TRICORE.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.6 (required)
 * An identifier with external linkage shall have exactly one external
 * definition.
 *
 * Reason:
 * These are not true variables; they are symbols set up by the linker.
 *
 *
 * MISRAC2012-2) Deviated Rule: 8.5 (required)
 * An external object or function shall be declared once in one and only one file.
 *
 * Reason:
 * These are not true variables; they are symbols set up by the linker.
 *
 *
 * MISRAC2012-3) Deviated Rule: 21.2 (required)
 * A reserved identifier or macro name shall not be declared.
 *
 * Reason:
 * These are not true variables; they are symbols set up by the linker.
*/

#include <Os_configuration.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_syscalls.h>
#include <Os_kernel.h>
#include <board.h>
#include <Os_api.h>
#include <TRICORE/Os_TRICORE_cpu.h>
#include <TRICORE/Os_TRICORE_stm.h>
#include <Os_Version.h>			/* To support pathing older versions */

#include <memmap/Os_mm_const_begin.h>

/*!
 * OS_intDisableLevel
 *
 * The interrupt level for disabling OS (category 2) interrupts
*/
const os_intstatus_t OS_intDisableLevel = OS_CAT2LOCK|OS_ICR_IE;

/*!
 * OS_kernDisableLevel
 *
 * The interrupt level for disabling OS (category 2) interrupts AND
 * kernel interrupts.
*/
const os_intstatus_t OS_kernDisableLevel = OS_KERNLOCK|OS_ICR_IE;

/*!
 * OS_intDisableLevelAll
 *
 * The interrupt level for disabling all (category 1 and 2) interrupts
*/
const os_intstatus_t OS_intDisableLevelAll = OS_CAT1LOCK|OS_ICR_IE;

/*!
 * OS_kernOnlyXcoreLevel
 *
 * The interrupt level for disabling all interrupts except the inter-core notification
*/
const os_intstatus_t OS_kernOnlyXcoreLevel = OS_XCOREUNLOCK|OS_ICR_IE;

/*!
 * OS_intDisableLevelMax
 *
 * The interrupt disable level to disable ALL possible interrupts. This includes
 * CAT2, CAT1 and OS interrupts, i.e. the maximum of all lock levels.
 */
#if (OS_KERNLOCK < OS_CAT1LOCK)
const os_intstatus_t OS_intDisableLevelMax = OS_CAT1LOCK|OS_ICR_IE;
#else
const os_intstatus_t OS_intDisableLevelMax = OS_KERNLOCK|OS_ICR_IE;
#endif

/* OS_timestampStm
 *
 * The pointer to the STM module configured as timestamp timer
*/
os_tricorestm_t * const OS_timestampStm = (os_tricorestm_t *)OS_TRICORE_TIMESTAMPSTMBASE;

/* OS_kernDpr, OS_kernCpr, OS_kernDpm, OS_kernCpm
 *
 * Data and code protection register settings (set 0) for kernel mode.
 * The kernel is allowed read, write and execute access anywhere in the
 * physical address range (0x80000000 and up)
*/
const os_uint32_t OS_kernDpr[OS_N_DPR * 2] =
{	OS_PHYS_ADDR_SPACE_START, 0xffffffffu,	/* Entire physical space, read/write */
	0, 0,					/* Not used */
	0, 0,					/* Not used */
	0, 0,					/* Not used */
	0, 0					/* Not used */
};

const os_uint32_t OS_kernCpr[OS_N_CPR * 2] =
{	OS_PHYS_ADDR_SPACE_START, 0xffffffffu,	/* Entire physical space, executable */
	0, 0					/* Not used */
};

#include <memmap/Os_mm_const_end.h>

/* Explicitly assign a section to data symbols,
 * so compilers/linkers don't try to treat them as if they were part of an SDA.
*/
/* Deviation MISRAC2012-2, MISRAC2012-3 <START> */
#define OS_TRICORE_LINKERSYMBOL_DATA(id) \
	extern os_char_t \
		OS_SECTION_ATTRIB_PRE_DECL(.data.shared.os.tricore) \
		(id) \
		OS_SECTION_ATTRIB_POST_DECL(.data.shared.os.tricore)
/* Deviation MISRAC2012-2, MISRAC2012-3 <STOP> */

/*!
 * __GLBL_TEXT_START and __GLBL_TEXT_END mark the boundary of the area of
 * memory that is executable by non-privileged tasks.
 *
 * __GLBL_RODATA_START and __GLBL_RODATA_END mark the boundary of ROM memory
 * that is readable by non-privileged tasks.
 *
 * __GLBL_DATA_START and __GLBL_DATA_END mark the boundary of RAM memory that
 * is readable by non-privileged tasks.
 *
 * These are not true variables; they are symbols set up by the linker.
*/
/* CHECK: SAVE
 * CHECK: RULE 401 OFF (these are linker-generated symbols, not variables)
*/
/* Deviation MISRAC2012-1, MISRAC2012-2, MISRAC2012-3 <START> */
extern const os_char_t __GLBL_TEXT_START;
extern const os_char_t __GLBL_TEXT_END;
extern const os_char_t __GLBL_RODATA_START;
extern const os_char_t __GLBL_RODATA_END;
OS_TRICORE_LINKERSYMBOL_DATA(__GLBL_DATA_START);
OS_TRICORE_LINKERSYMBOL_DATA(__GLBL_DATA_END);
/* Deviation MISRAC2012-1, MISRAC2012-2, MISRAC2012-3 <STOP> */
/* CHECK: RESTORE
*/

#include <memmap/Os_mm_const_begin.h>
/* All applications can run any code that is in the global text section
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Code.Share, 1
*/
const os_uint32_t OS_globalCpr[OS_N_CPR * 2] =
{
	(os_uint32_t)&__GLBL_TEXT_START,
	(os_uint32_t)&__GLBL_TEXT_END,
	0,	/* If these are ever used, macro TRICORE_CheckGlobalMemoryAccess() */
	0	/* needs attention */
};
const os_uint32_t OS_globalDpr[6] =
{
	/* read-only data in the ROM */
	(os_uint32_t)&__GLBL_RODATA_START,
	(os_uint32_t)&__GLBL_RODATA_END,
	/* read-only access to data in the RAM */
	(os_uint32_t)&__GLBL_DATA_START,
	(os_uint32_t)&__GLBL_DATA_END,
	/* read-only access to the time-stamp STM */
	((os_uint32_t)OS_TRICORE_TIMESTAMPSTMBASE) + OS_STM_LOW_OFFSET,
	((os_uint32_t)OS_TRICORE_TIMESTAMPSTMBASE) + OS_STM_HIGH_OFFSET + sizeof(os_uint32_t)
};

#if OS_N_CORES > 1
os_tricoresrn_t * const OS_xCoreSrc[OS_N_CORES_MAX] = OS_TRICORE_XCORESRCS;
#endif

/*
 * !LINKSTO Kernel.Misc.VirtualizationSupport, 1
*/
#ifndef OS_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER
#define OS_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER 0
#endif
#if (!OS_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER)
const os_int_ir_config_driver_t OS_intIrConfigDriver = OS_InitIntIrConfigDriver(
	&OS_SetupIsrImpl, &OS_EnableIsrImpl, &OS_DisableIsrImpl, &OS_ClearIsrImpl);
#endif

#include <memmap/Os_mm_const_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_Os_configuration_TRICORE_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
