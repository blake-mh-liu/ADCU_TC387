/* Os_TRICORE_core.h - Tricore core header
 *
 * This file contains definitions for features that are common across all
 * the Tricore CPUs, including the structure of context-save areas (CSAs)
 * and the addresses of the core special-function registers (CSFRs)
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * Upper and lower context types are used in macros and functions.
*/

#ifndef OS_TRICORE_CORE_H
#define OS_TRICORE_CORE_H

#include <Os_types.h>
#include <TRICORE/Os_tool_TRICORE_inline.h>
#include <TRICORE/Os_TRICORE_cpu.h>
#include <TRICORE/Os_TRICORE_module.h>

#ifdef __cplusplus
extern "C" {
#endif

/* We check if the architecture is defined. The Os_<DERIVATE>.h file should set it. */

#ifndef OS_TRICOREARCH
#error "OS_TRICOREARCH not defined. Check Os_<DERIVATE>.h"
#endif
#ifndef OS_SRNVERSION
#define OS_SRNVERSION OS_SRNVERSION_16
#endif

/* We need to know about the interrupt controller. */

/* Bit definitions for CLC */
#define OS_CLC_RMC	OS_U(0x0000ff00)	/* Clock divider (Rate mode control?) */
#define OS_CLC_FSOE	OS_U(0x00000020)	/* Fast shut-off enable */
#define OS_CLC_SBWE	OS_U(0x00000010)	/* Suspend bit write enable */
#define OS_CLC_EDIS	OS_U(0x00000008)	/* External request disable */
#define OS_CLC_SPEN	OS_U(0x00000004)	/* Suspend enable bit */
#define OS_CLC_DISS	OS_U(0x00000002)	/* Disable status bit */
#define OS_CLC_DISR	OS_U(0x00000001)	/* Disable request bit */

/* Bit definitions for ID */
#define OS_ID_MOD	OS_U(0xffff0000)	/* Module identification number */
#define OS_ID_TYPE	OS_U(0x0000ff00)	/* Module type */
#define OS_ID_MOD16	OS_U(0x0000ff00)	/* Module id (used to be 16-bit register) */
#define OS_ID_MOD32	OS_U(0x0000c000)	/* Indicates 32-bit register */
#define OS_ID_REV	OS_U(0x000000ff)	/* Module revision number */


/*	Move an integer value to the appropriate field. */
#define OS_CLC_RMCval(div)	(	(os_uint32_t)							\
								( ((os_uint32_t)(div) & 0xffffu) << 8 )	\
							)

/*	Extract the module ident (shifted to LSB) using appropriate field,
 *	taking account of 16/32 bit register types.
*/
#define Os_ModuleId(v)	( (((v)&OS_ID_MOD16) == OS_ID_MOD32)	\
							? ( ((v)>>16) & OS_U(0xffff) )		\
							: ( ((v)>>8) & OS_U(0xff) )			\
						)

/*! os_tricoresrn_t
 *
 * Data type for interrupt service request node. All generation of
 * interrupts on Tricore is done through one of these SRN registers.
 * We can use common code to program the priority, enable/disable, etc.
*/
#ifndef OS_ASM
typedef os_reg32_t os_tricoresrn_t;
#endif

#define OS_SRN_SETR		OS_U(0x04000000)	/* Request set bit */
#define OS_SRN_CLRR		OS_U(0x02000000)	/* Request clear bit */
#define OS_SRN_SRR		OS_U(0x01000000)	/* Service request bit */
#define	OS_SRN_SRPN		OS_U(0x000000ff)	/* Priority */
/* OS_SRN_SRE - Service request enable */
/* OS_SRN_OS_MASK - The bits which may be accessed by the OS */
#if (OS_SRNVERSION == OS_SRNVERSION_16)
#define OS_SRN_SRE		OS_U(0x00000400)
#define OS_SRN_OS_MASK	OS_U(0xffffffff)
#elif (OS_SRNVERSION == OS_SRNVERSION_18)
#define OS_SRN_SRE		OS_U(0x00800000)
#define OS_SRN_VM_MASK	OS_U(0x00000700)
#define OS_SRN_OS_MASK	(~OS_SRN_VM_MASK)
#else
#error "Unknown SRN version."
#endif /* OS_SRNVERSION */

#ifndef OS_ASM
#define OS_SRN_TOS_CPU	OS_SRN_TOSval(OS_TricoreGetCoreId())	/* Interrupt the CPU */
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
#define OS_SRN_TOSval(tos)	(OS_ShiftLeftU32(((tos) & 0x7u), 12u))
#elif (OS_TRICOREARCH == OS_TRICOREARCH_162)
#define OS_SRN_TOSval(tos)	(((tos)==0u)?0u:(OS_ShiftLeftU32((((tos) & 0x7u)+1u),11u)))
#elif (OS_TRICOREARCH == OS_TRICOREARCH_16EP)
#define OS_SRN_TOSval(tos)	(OS_ShiftLeftU32(((tos) & 0x3u), 11u))
#else /* OS_TRICOREARCH */
#error "Unexpected TRICORE architecture in OS_TRICOREARCH"
#endif /* OS_TRICOREARCH */
#endif /* OS_ASM */

#ifndef OS_ASM

void OS_SetupCache(os_boolean_t, os_boolean_t);

/* os_cx_t represents a CSA.
 * Such a CSA can be interpreted as upper context (os_uppercx_t)
 * or lower context (os_lowercx_t).
*/
typedef struct os_cx_s os_cx_t;
struct os_cx_s
{
	os_reg32_t pcxi;			/* link word */
	os_uint32_t reserved[15];	/* other registers depending on lower/upper context */
};
/* Deviation MISRAC2012-1 */
typedef struct os_uppercx_s os_uppercx_t;
struct os_uppercx_s
{
	os_reg32_t pcxi;	/* link word */
	os_reg32_t psw;		/* processor status word : TC4-csa_PSW {{PSW[31:16], PPRS[2], PSW.[14], PPRS[1:0], PSW[11:0]} , TC[3,2]-PSW {{PSW[31:16], PRS[2], PSW.[14], PRS[1:0], PSW[11:0]}*/
	os_reg32_t a10;		/* Stack pointer. */
	os_reg32_t a11;		/* Return address register. */
	os_reg32_t d8;
	os_reg32_t d9;
	os_reg32_t d10;
	os_reg32_t d11;
	os_reg32_t a12;
	os_reg32_t a13;
	os_reg32_t a14;
	os_reg32_t a15;
	os_reg32_t d12;
	os_reg32_t d13;
	os_reg32_t d14;
	os_reg32_t d15;
};

/* Deviation MISRAC2012-1 */
typedef struct os_lowercx_s os_lowercx_t;
struct os_lowercx_s
{
	os_reg32_t pcxi;	/* link word */
	os_reg32_t a11;		/* return address register. */
	os_reg32_t a2;
	os_reg32_t a3;
	os_reg32_t d0;
	os_reg32_t d1;
	os_reg32_t d2;
	os_reg32_t d3;
	os_reg32_t a4;
	os_reg32_t a5;
	os_reg32_t a6;
	os_reg32_t a7;
	os_reg32_t d4;
	os_reg32_t d5;
	os_reg32_t d6;
	os_reg32_t d7;
};

#endif

/*	Offsets of saved registers in CSAs.
 *	For use in assembler modules - should never be used in C
*/
#ifdef OS_ASM

#define UPPERCX_PCXI	0x00
#define UPPERCX_PSW		0x04
#define UPPERCX_A10		0x08
#define UPPERCX_A11		0x0c

#define UPPERCX_D8		0x10
#define UPPERCX_D9		0x14
#define UPPERCX_D10		0x18
#define UPPERCX_D11		0x1c
#define UPPERCX_A12		0x20
#define UPPERCX_A13		0x24
#define UPPERCX_A14		0x28
#define UPPERCX_A15		0x2c
#define UPPERCX_D12		0x30
#define UPPERCX_D13		0x34
#define UPPERCX_D14		0x38
#define UPPERCX_D15		0x3c

#define LOWERCX_PCXI	0x00
#define LOWERCX_A11		0x04
#define LOWERCX_A2		0x08
#define LOWERCX_A3		0x0c
#define LOWERCX_D0		0x10
#define LOWERCX_D1		0x14
#define LOWERCX_D2		0x18
#define LOWERCX_D3		0x1c
#define LOWERCX_A4		0x20
#define LOWERCX_A5		0x24
#define LOWERCX_A6		0x28
#define LOWERCX_A7		0x2c
#define LOWERCX_D4		0x30
#define LOWERCX_D5		0x34
#define LOWERCX_D6		0x38
#define LOWERCX_D7		0x3c

#endif

/*	CSFR offsets. These offsets can be used
 *	with the mtcr/mfcr instructions, or can be added to a base address
 *	to get the absolute address for accesses via the bus.
*/

#define	OS_DPR0_L	0xc000	/* Data protection register 0, lower */
#define	OS_DPR0_U	0xc004	/* Data protection register 0, upper */
#define	OS_DPR1_L	0xc008	/* Data protection register 1, lower */
#define	OS_DPR1_U	0xc00c	/* Data protection register 1, upper */
#define	OS_DPR2_L	0xc010	/* Data protection register 2, lower */
#define	OS_DPR2_U	0xc014	/* Data protection register 2, upper */
#define	OS_DPR3_L	0xc018	/* Data protection register 3, lower */
#define	OS_DPR3_U	0xc01c	/* Data protection register 3, upper */
#define	OS_DPR4_L	0xc020	/* Data protection register 4, lower */
#define	OS_DPR4_U	0xc024	/* Data protection register 4, upper */
#define	OS_DPR5_L	0xc028	/* Data protection register 5, lower */
#define	OS_DPR5_U	0xc02c	/* Data protection register 5, upper */
#define	OS_DPR6_L	0xc030	/* Data protection register 6, lower */
#define	OS_DPR6_U	0xc034	/* Data protection register 6, upper */
#define	OS_CPR0_L	0xd000	/* Code protection register 0, lower */
#define	OS_CPR0_U	0xd004	/* Code protection register 0, upper */
#define	OS_CPR1_L	0xd008	/* Code protection register 1, lower */
#define	OS_CPR1_U	0xd00c	/* Code protection register 1, upper */
#define	OS_CPXE_0	0xe000	/* Code protection execute enable set config register 0 */
#define	OS_CPXE_1	0xe004	/* Code protection execute enable set config register 1 */
#define	OS_DPRE_0	0xe010	/* Data protection read enable set config register 0 */
#define	OS_DPRE_1	0xe014	/* Data protection read enable set config register 1 */
#define	OS_DPWE_0	0xe020	/* Data protection write enable set config register 0 */
#define	OS_DPWE_1	0xe024	/* Data protection write enable set config register 1 */

/* CSFR IDs/offsets */
#define OS_PMA0		0x8100
#define OS_PMA1		0x8104
#define OS_PCON0	0x920c
#define OS_DCON0	0x9040

#define	OS_DBGSR	0xfd00	/* Debug status register */
#define	OS_GPRWB	0xfd04	/* GPR write back trigger */
#define	OS_EXEVT	0xfd08	/* External break input event specifier */
#define	OS_CREVT	0xfd0c	/* Emulator resource protection event specifier */
#define	OS_SWEVT	0xfd10	/* Software break event specifier */
#define	OS_TR0EVT	0xfd20	/* Trigger event 0 specifier */
#define	OS_TR1EVT	0xfd24	/* Trigger event 1 specifier */

#define OS_DMS		0xfd40	/* Debug monitor start address register */
#define OS_DCX		0xfd44	/* Debug context save area pointer */

#define	OS_PCXI		0xfe00	/* Previous context information register */
#define	OS_PSW		0xfe04	/* Program status word */
#define	OS_PC		0xfe08	/* Program counter */
#define	OS_DBITEN	0xfe0c	/* Register bank dual bit enable register */
#define	OS_SYSCON	0xfe14	/* System configuration register */
#define	OS_BIV		0xfe20	/* Base address of interrupt vector table */
#define	OS_BTV		0xfe24	/* Base address of trap vector table */
#define	OS_ISP		0xfe28	/* Interrupt stack pointer */
#define	OS_ICR		0xfe2c	/* Interrupt unit control register */
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
#define	OS_PPRS		0xfe34	/* previous protection register set register */
#endif
#define	OS_FCX		0xfe38	/* Free CSA list head pointer */
#define	OS_LCX		0xfe3c	/* Free CSA list limit pointer */
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
#define OS_BOOTCON	0xfe60	/* Boot control */
#endif

#define OS_D0		0xff00	/* Data Register 0 */
#define OS_D1		0xff04	/* Data Register 1 */
#define OS_D2		0xff08	/* Data Register 2 */
#define OS_D3		0xff0c	/* Data Register 3 */
#define OS_D4		0xff10	/* Data Register 4 */
#define OS_D5		0xff14	/* Data Register 5 */
#define OS_D6		0xff18	/* Data Register 6 */
#define OS_D7		0xff1c	/* Data Register 7 */
#define OS_D8		0xff20	/* Data Register 8 */
#define OS_D9		0xff24	/* Data Register 9 */
#define OS_D10		0xff28	/* Data Register 10 */
#define OS_D11		0xff2c	/* Data Register 11 */
#define OS_D12		0xff30	/* Data Register 12 */
#define OS_D13		0xff34	/* Data Register 13 */
#define OS_D14		0xff38	/* Data Register 14 */
#define OS_D15		0xff3c	/* Data Register 15 */
#define OS_A0		0xff80	/* Address Register 0 */
#define OS_A1		0xff84	/* Address Register 1 */
#define OS_A2		0xff88	/* Address Register 2 */
#define OS_A3		0xff8c	/* Address Register 3 */
#define OS_A4		0xff90	/* Address Register 4 */
#define OS_A5		0xff94	/* Address Register 5 */
#define OS_A6		0xff98	/* Address Register 6 */
#define OS_A7		0xff9c	/* Address Register 7 */
#define OS_A8		0xffa0	/* Address Register 8 */
#define OS_A9		0xffa4	/* Address Register 9 */
#define OS_A10		0xffa8	/* Address Register 10 */
#define OS_A11		0xffac	/* Address Register 11 */
#define OS_A12		0xffb0	/* Address Register 12 */
#define OS_A13		0xffb4	/* Address Register 13 */
#define OS_A14		0xffb8	/* Address Register 14 */
#define OS_A15		0xffbc	/* Address Register 15 */

#define OS_CORE_ID	0xfe1c	/* core id register */

#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
/* The PROTSFRSE register controls lock / unlock
* of the local Safe Endinit (SE) protected control registers
*/
#define OS_PROTSFRSE 0xE088
#endif

/* Bit definitions for PSW */
#define	OS_PSW_C			OS_U(0x80000000)		/* Carry */
#define	OS_PSW_V			OS_U(0x40000000)		/* Overflow */
#define OS_PSW_SV			OS_U(0x20000000)		/* Sticky overflow */
#define OS_PSW_AV			OS_U(0x10000000)		/* Advanced overflow */
#define OS_PSW_SAV			OS_U(0x08000000)		/* Sticky advanced overflow */
#if (OS_TRICOREARCH == OS_TRICOREARCH_162) || (OS_TRICOREARCH == OS_TRICOREARCH_18)
#define OS_PSW_PRS			OS_U(0x0000B000)		/* Protection register set (mask) */
#define OS_PSW_PRS_4		OS_U(0x00008000)		/*	--- Protection register set 5 */
#define OS_PSW_PRS_5		OS_U(0x00009000)		/*	--- Protection register set 6 */
#elif (OS_TRICOREARCH == OS_TRICOREARCH_16EP)
#define OS_PSW_PRS			OS_U(0x00003000)		/* Protection register set (mask) */
#else /* OS_TRICOREARCH */
#error "Unexpected TRICORE architecture in OS_TRICOREARCH"
#endif /* OS_TRICOREARCH */
#define OS_PSW_PRS_0		OS_U(0x00000000)		/*	--- Protection register set 1 */
#define OS_PSW_PRS_1		OS_U(0x00001000)		/*	--- Protection register set 2 */
#define OS_PSW_PRS_2		OS_U(0x00002000)		/*	--- Protection register set 3 */
#define OS_PSW_PRS_3		OS_U(0x00003000)		/*	--- Protection register set 4 */
#define OS_PSW_IO			OS_U(0x00000C00)		/* I/O privelege mode. */
#define OS_PSW_IO_U0		OS_U(0x00000000)		/*	--- User 0 */
#define OS_PSW_IO_U1		OS_U(0x00000400)		/*	--- User 1 */
#define OS_PSW_IO_SU		OS_U(0x00000800)		/*	--- Supervisor */
#define OS_PSW_IO_RES		OS_U(0x00000C00)		/*	--- Reserved */
#define OS_PSW_IS			OS_U(0x00000200)		/* Interrupt stack in use */
#define OS_PSW_GW			OS_U(0x00000100)		/* Global register write perm. */
#define OS_PSW_CDE			OS_U(0x00000080)		/* Call depth count enable */
#define OS_PSW_CDC			OS_U(0x0000007F)		/* Call depth counter */
#define OS_PSW_CDC_DIS		OS_U(0x0000007F)		/*	--- Disable call depth ctr */
#define OS_PSW_CDC_6		OS_U(0x00000000)		/*	--- 6-bit call depth counter */
#define OS_PSW_CDC_5		OS_U(0x00000040)		/*	--- 5-bit call depth counter */
#define OS_PSW_CDC_4		OS_U(0x00000060)		/*	--- 4-bit call depth counter */
#define OS_PSW_CDC_3		OS_U(0x00000070)		/*	--- 3-bit call depth counter */
#define OS_PSW_CDC_2		OS_U(0x00000078)		/*	--- 2-bit call depth counter */
#define OS_PSW_CDC_1		OS_U(0x0000007C)		/*	--- 1-bit call depth counter */
#define OS_PSW_CDC_TRA		OS_U(0x0000007E)		/*	--- Call trace */

#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
/* Extract PPRS from csa_PSW - PPRS[1:0] bits of csa_PSW rshift by 12 bits to extract PPRS[1:0]
* and PPRS[2] bit of csa_PSW rshift by 13 bits to extract PPRS[2]
*/
#define OS_CSA_PSW_PPRS1	OS_U(0x00003000) /* mask to get the PPRS[1:0]-field of csa_PSW */
#define OS_CSA_PSW_PPRS2	OS_U(0x00008000) /* mask to get the PPRS[2]-field of csa_PSW */
#define OS_PSW_GET_PPRS(csa_psw)	((((csa_psw) & OS_CSA_PSW_PPRS1)>>12) | \
										(((csa_psw) & OS_CSA_PSW_PPRS2)>>13))
#endif

/*	Bit definitions for all context pointer registers (PCXI,FCX,LCX)
*/
#define OS_CX_SEG			OS_U(0x000F0000)		/* Segment number of CSA. */
#define OS_CX_OFF			OS_U(0x0000FFFF)		/* Index of CSA. */
#define OS_CX_CX			(OS_CX_SEG|OS_CX_OFF)	/* Entire context */

/*	Additiional bit definitions for PCXI. */
#define OS_PCXI_PCPN		OS_U(0xFFC00000)		/* Previous CPU priority. */
#define OS_PCXI_PCPN_BIT	22						/* Start bit of PCPN. */
#define OS_PCXI_PIE			OS_U(0x00200000)		/* Previous interrupt enable. */
#define OS_PCXI_PIE_BIT		21						/* Previous interrupt enable (bit number for j(n)z.t instructions) */
#define OS_PCXI_UL			OS_U(0x00100000)		/* Upper/lower context flag. */


/* Bit definitions for ICR. */
#define OS_ICR_IE			OS_U(0x00008000)		/* Interrupt enable. */
#define OS_ICR_CONEC		OS_U(0)					/* no longer present in 1.6E/P */

#define OS_ICR_PIPN			OS_U(0x00FF0000)		/* Pending interrupt priority */
#define OS_ICR_CCPN			OS_U(0x000000FF)		/* Current CPU priority number. */

#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
#define OS_CORE_MASK		OS_U(0x7)
/* Bit definition for BOOTCON. */
#define OS_BOOTCON_BHALT	OS_U(0x00000001)		/* Boot halt status and release */
/* Bit definition for PROTSFRSE. */
#define OS_PROT_STATE_MASK					0x7u	/* PROTSFRSE : STATE[2:0] */
#define OS_PROTSFRSE_SWEN					0x8u	/* PROTSFRSE : SWEN[3] */
#define OS_PROT_STATE_RUN					0x4u	/* PROTSFRSE Run (locked state) */
#define OS_PROT_STATE_CONF					0x1u	/* PROTSFRSE Config (unlocked state) */
#endif /* OS_TRICOREARCH == OS_TRICOREARCH_18 */

/* Bit definitions for SYSCON. */
#if (OS_TRICOREARCH == OS_TRICOREARCH_162)
#define OS_SYSCON_BHALT		OS_U(0x01000000)		/* Boot halt status and release */
#endif /* OS_TRICOREARCH */
#define OS_SYSCON_PROTEN	OS_U(0x00000002)		/* Enable memory protection. */
#define OS_SYSCON_ENDINIT	OS_U(0x00000001)		/* End of initialisation. */

/* Bit definitions for DBGSR. */
#define OS_DBGSR_DE_MASK		OS_U(0x00000001)	/* mask to get the DE-field */
#define OS_DBGSR_HALT_MASK		OS_U(0x00000006)	/* mask to get the HALT-field */

#define OS_DBGSR_DE_DISABLE		OS_U(0x00000000)	/* disable DE flag */
#define OS_DBGSR_DE_ENABLE		OS_U(0x00000001)	/* enable DE flag */
#define OS_DBGSR_HALT_HALTED	OS_U(0x00000002)	/* processor halted */
#define OS_DBGSR_HALT_RUNNING	OS_U(0x00000000)	/* processor running */
#define OS_DBGSR_HALT_WE		OS_U(0x00000004)	/* enable change of HALT-bit on write */

#ifndef OS_ASM

void OS_FreeCxList(os_uint32_t);
void OS_FreeCxListTo(os_uint32_t, os_uint32_t);
os_uint32_t OS_Grab1Csa(void);
os_uint32_t OS_Grab2Csa(void);

#define OS_ArchGetCoreId()		OS_GetMyCoreId()

/* OS_MTCCR
 *
 * Writes a value to a CR of another core using the memory mapped mirror of the core registers
*/
OS_QUAL_INLINE void OS_MTCCR(os_uint32_t, os_uint32_t, os_uint32_t) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_MTCCR(os_uint32_t csfrBase, os_uint32_t csfrId, os_uint32_t val)
{
	os_address_t csfrAddr = csfrBase + csfrId;
	OS_DSYNC();
	*((os_reg32_t *)csfrAddr) = val;
	OS_ISYNC();
}

/* OS_MFCCR
 *
 * Reads the value from a CR of another core using the memory mapped mirror of the core registers
*/
OS_QUAL_INLINE os_uint32_t OS_MFCCR(os_uint32_t, os_uint32_t) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_MFCCR(os_uint32_t csfrBase, os_uint32_t csfrId)
{
	os_address_t csfrAddr = csfrBase+csfrId;
	return *((os_reg32_t *) csfrAddr);
}

/* OS_AddrFromCx() converts a CSA link word to an address.
 * No test is made for validity!
*/
OS_QUAL_INLINE os_address_t OS_AddrFromCx(os_uint32_t) OS_ATTR_INLINE;
OS_QUAL_INLINE os_address_t OS_AddrFromCx(os_uint32_t cx)
{
	os_address_t addr = ((cx & OS_CX_SEG) << 12u) + ((cx & OS_CX_OFF) << 6u);
	return addr;
}

/* OS_CxFromAddr() converts an address to a CSA link word.
 * No test is made for validity!
*/
OS_QUAL_INLINE os_uint32_t OS_CxFromAddr(os_address_t) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_CxFromAddr(os_address_t a)
{
	return ( ((a >> 6u) & OS_CX_OFF) + ((a >> 12u) & OS_CX_SEG) );
}

#endif /* OS_ASM */

#ifdef __cplusplus
}
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
