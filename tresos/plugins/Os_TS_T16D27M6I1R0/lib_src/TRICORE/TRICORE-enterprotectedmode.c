/* TRICORE-enterprotectedmode.c
 *
 * This file contains the OS_EnterProtectedMode function for TRICORE.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/* OS_EnterProtectedMode
 *
 * This function switches the CPU from "normal" mode in which it starts
 * to "proteced" mode. To do this, the PROTEN bit of SYSCON is set to 1.
 *
 * Before that can happen, however, the appropriate IO mode (SU) and
 * and protection register set (0) must be selected in PSW. Then the
 * registers of protection register set 0 are initialised to give read,
 * write and execute access.
 *
 * The current used mapping is the following:
 *
 * CPR0: 0x8000000 to 0xffffffff [SV] Fix
 * CPR1: entire .text section (execute) [User] Fix
 *
 * DPR0: application data (read/write) [User,SV]
 * DPR1: task/isr private data (read/write) [User,SV]
 * DPR2: stack (read/write) [User,SV]
 * DPR3: global data (read-only) [User,SV] Fix
 * DPR4: whole memory (read/write) [SV] Fix
 *
 * Furthermore 2 protection sets are used:
 * Set 0 for supervisor
 * Set 1 for user modes (Tasks, etc.)
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection, 1
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_EnterProtectedMode(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t pswVal;
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	os_uint32_t protsfrseBase;
	os_uint32_t protsfrseVal;
	os_coreid_t coreId;
#endif
	/* First setup the whole memory. */
	OS_MTCR(OS_CPR0_L, OS_kernCpr[0]);
	OS_MTCR(OS_CPR0_U, OS_kernCpr[1]);

	/* Then setup the whole .text as executable */
	OS_MTCR(OS_CPR1_L, OS_globalCpr[0]);
	OS_MTCR(OS_CPR1_U, OS_globalCpr[1]);


	/* Now the data ranges */

	/* Ranges 0 to 2 are set by OS_SetProtection */
	/* 0: (A) Application data range */
	/* 1: (T) Task data range */
	/* 2: (S) Stack data range */

	/* 3: (R) GLBL_RODATA */
	OS_MTCR(OS_DPR3_L, OS_globalDpr[0]);
	OS_MTCR(OS_DPR3_U, OS_globalDpr[1]);

	/* 4: (D) GLBL_DATA */
	OS_MTCR(OS_DPR4_L, OS_globalDpr[2]);
	OS_MTCR(OS_DPR4_U, OS_globalDpr[3]);

	/* 5: (X) whole memory */
	OS_MTCR(OS_DPR5_L, OS_kernDpr[0]);
	OS_MTCR(OS_DPR5_U, OS_kernDpr[1]);

	/* 6: (C) time stamp */
	OS_MTCR(OS_DPR6_L, OS_globalDpr[4]);
	OS_MTCR(OS_DPR6_U, OS_globalDpr[5]);

	/* Setup set 0 for supervisor mode */
	/*  ranges:                 C X D  R S T A */
	OS_MTCR(OS_DPRE_0,0x20); /* 0 1 0  0 0 0 0 */
	OS_MTCR(OS_DPWE_0,0x20); /* 0 1 0  0 0 0 0 */
	OS_MTCR(OS_CPXE_0,0x01);

	/* Setup set 1 for user mode */
	/*  ranges:                 C X D  R S T A */
	OS_MTCR(OS_DPRE_1,0x5f); /* 1 0 1  1 1 1 1 */
	OS_MTCR(OS_DPWE_1,0x07); /* 0 0 0  0 1 1 1 */
	OS_MTCR(OS_CPXE_1,0x02);

	/* Select PRS 0, supervisor mode, enable write to global address
	 * registers, disable call depth counting.
	*/
	pswVal = OS_MFCR(OS_PSW);
	pswVal &= (os_uint32_t) ~((os_uint32_t) OS_PSW_PRS | OS_PSW_IO | OS_PSW_GW | OS_PSW_CDE | OS_PSW_CDC);
	pswVal |= (OS_PSW_PRS_0 | OS_PSW_IO_SU | OS_PSW_GW | OS_PSW_CDC_DIS);
	OS_MTCR(OS_PSW, pswVal);

#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	coreId=OS_ArchGetCoreId();
	protsfrseBase=OS_CPUSFR(coreId);
	protsfrseVal=OS_MFCCR(protsfrseBase,OS_PROTSFRSE);
	/* CPUx PROTSFR register safe endinit - PROTSFRSE Config (unlocked state) */
	if ((protsfrseVal & OS_PROT_STATE_MASK) != OS_PROT_STATE_CONF)
	{
		OS_MTCCR(protsfrseBase,OS_PROTSFRSE,((protsfrseVal & (~OS_PROT_STATE_MASK)) | OS_PROTSFRSE_SWEN | OS_PROT_STATE_CONF));
	}
#endif
	/* Turn on protected mode */
	OS_MTCR(OS_SYSCON, OS_SYSCON_PROTEN);
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	/* CPUx PROTSFR register safe endinit - PROTSFRSE Run (locked state) */
	OS_MTCCR(protsfrseBase,OS_PROTSFRSE,((protsfrseVal & (~OS_PROT_STATE_MASK)) | OS_PROTSFRSE_SWEN | OS_PROT_STATE_RUN));
#endif
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_enterprotectedmode_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
