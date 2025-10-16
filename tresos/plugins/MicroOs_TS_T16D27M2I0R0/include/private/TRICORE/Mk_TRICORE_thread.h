/* Mk_TRICORE_thread.h - TRICORE thread handling
 *
 * This file contains the TRICORE-specific part of the definitions for
 * thread handling.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function
 *  and any other type.
 *
 * Reason:
 *  To set the address where to start or return to, the C language function
 *  pointer must be converted to its bare value so that hardware can interpret
 *  it correctly. That's because hardware has no notion of C language types.
*/

#ifndef MK_TRICORE_THREAD_H
#define MK_TRICORE_THREAD_H

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>
#include <public/Mk_misra.h>
#include <private/Mk_tool.h>


#ifndef MK_ASM
/* The thread registers structure contains:
 * - PCXI value (after saving lower context)
 * - d15 value (system call, trap ID)
 * - pointer to upper and lower context for ease of access
*/
typedef struct mk_tricorethreadregisters_s mk_hwthreadregisters_t;

struct mk_tricorethreadregisters_s
{
	mk_uint32_t pcxi;
	mk_uint32_t trapCode;	/* system call index or trap identification (from d15), or interrupt vector code */
	mk_upperctx_t *upper;
	mk_lowerctx_t *lower;
};

/* The processor status (PS) of a thread is represented by a combination of the PSW and PCXI.
 * The privilege mode is part of the PSW. The interrupt level and interrupt enable flag are
 * saved in the PCXI.PCPN and PCXI.PIE fields respectively.
*/
typedef struct mk_hwps_s mk_hwps_t;

struct mk_hwps_s
{
	mk_uint32_t	psw;	/* Maps 1:1 to PSW register in upper context */
	mk_uint32_t pcxi;	/* Only contains PCPN and PIE; will be ORed to PCXI of lower context */
};
#endif


/* MK_HwResumeThread() - gets called by the common dispatcher.
 *
 * The Tricore implementation calls MK_TricoreResumeThread with the PCXI value to restore
*/
#ifndef MK_ASM
#define MK_HwResumeThread(cv,t)	MK_TricoreResumeThread((t)->regs->pcxi)

void MK_TricoreResumeThread(mk_uint32_t) MK_ATTR_NORETURN;
#endif

/* MK_GetSyscallIndex() etc.
 *
 * These macros are used to get values (parameters etc.) out of a thread's context and to
 * put values (return value, thread-main etc.) into a thread's context.
 *
 * In a system call the following registers are used:
 *	d15 - system-call index (saved in trapCode member of register store)
 *  d4  - 1st parameter
 *  d5  - 2nd parameter
 *  d6  - 3rd parameter
 *  d7  - 4th parameter
 *  d2  - Return value
 *  d3  - 2nd return value
 *
 * !LINKSTO Microkernel.TRICORE.RegisterStore.Copy, 1,
 * !        Microkernel.TRICORE.RegisterStore.MainFuncParameter, 1,
 * !        Microkernel.TRICORE.RegisterStore.MainFuncReturn, 1,
 * !        Microkernel.TRICORE.RegisterStore.SystemCall, 1
 * !doctype src
*/
#define MK_HwGetSyscallIndex(regs)			((regs)->trapCode)
#define MK_HwIsRegisterStoreValid(regs)		((regs)->lower != MK_NULL)
#define MK_HwGetParameter1(regs)			((regs)->lower->d4)
#define MK_HwGetParameter2(regs)			((regs)->lower->d5)
#define MK_HwGetParameter3(regs)			((regs)->lower->d6)
#define MK_HwGetParameter4(regs)			((regs)->lower->d7)
#define MK_HwGetIntLevel(regs)				(MK_GetPcpnFromPcxi((regs)->pcxi))

#define MK_HwSetReturnValue1(regs, rv)		\
	do {									\
		mk_uint32_t d2 = (mk_uint32_t)(rv);	\
		(regs)->lower->d2 =d2;				\
	} while (0)
#define MK_HwSetReturnValue2(regs, rv)		do { (regs)->lower->d3 = (mk_uint32_t)(rv); } while (0)
/* Deviation MISRAC2012-1 <+2> */
#define MK_HwSetProgramCounter(regs, addr)	do { (regs)->lower->pc = (mk_uint32_t)(addr); } while (0)
#define MK_HwSetReturnAddress(regs, addr)	do { (regs)->upper->ra = (mk_uint32_t)(addr); } while (0)
#define MK_HwSetPs(regs, ps)	\
	do {	\
		(regs)->upper->psw = (ps).psw; \
		(regs)->lower->pcxi = MK_SetPsInPcxi((regs)->lower->pcxi, (ps).pcxi); \
	} while (0)
#define MK_HwSetIntLevel(regs, lvl) \
	do { (regs)->lower->pcxi = MK_SetPcpnInPcxi((regs)->lower->pcxi, (lvl)); } while (0)
#define MK_HwSetStackPointer(regs, addr)	do { (regs)->upper->sp = (mk_uint32_t)(addr); } while (0)
#define MK_HwSetParameter1(regs, val)		do { (regs)->lower->d4 = (mk_uint32_t)(val); } while (0)
#define MK_HwSetParameter2(regs, val)		do { (regs)->lower->d5 = (mk_uint32_t)(val); } while (0)
#define MK_HwSetParameter3(regs, val)		do { (regs)->lower->d6 = (mk_uint32_t)(val); } while (0)
#define MK_HwSetParameter4(regs, val)		do { (regs)->lower->d7 = (mk_uint32_t)(val); } while (0)
#define MK_HwSetMain(regs, mf)				MK_HwSetProgramCounter(regs, mf)

/* The second parameter of a trusted function is an address value. On Tricore, we need to
 * pass this parameter in an address register to the trusted function
*/
#define MK_HwSetTfParameter2(regs, val) do { (regs)->lower->a4 = (mk_uint32_t)(val); } while (0)

/* On Tricore, transferring the interrupt level to the hardware is done automatically.
*/
#define MK_HwIntLevelThreadToHardware(regs)	do { /* Nothing */ } while (0)

/* Initial values for constant registers
 *
 * The "constant" registers (a0,a1,a8,a9) on Tricore are protected by hardware
 * so there's no need to ensure that each thread gets a clean set.
*/
#define MK_HwSetConstantRegisters(regs)		do { /* Nothing */ } while (0)


/* CSAs need to be allocated when a thread is created in order to start the thread.
 * When a thread terminates the CSAs that it occupies need to be freed.
*/
#ifndef MK_ASM
void MK_HwAllocateThreadRegisters(mk_hwthreadregisters_t *);
void MK_HwFreeThreadRegisters(mk_hwthreadregisters_t *);
#endif

/* TRICORE has no specific FPU status
*/
#define MK_HAS_FPUCRVALUE	0

/* MK_HwThreadReturn is simply an alias to the MK_UsrTerminateSelf system
 * call stub. It should not be reachable because a context-list underflow
 * exception is triggered when a thread returns from its entry function.
 */
#ifndef MK_ASM
void MK_HwThreadReturn(void);
#endif

/* MK_HwTerminateThreadAction is called in MK_TerminateThread to perform
 * hardware-specific tasks.
 *
 * This feature is not used on TRICORE.
*/
#define MK_HwTerminateThreadAction(coreVars, thread, lockLevel)  do {} while (0)

/* Standardized processor state macros
 *
 * !LINKSTO Microkernel.TRICORE.Design.CoreManagement.GRWP, 1
 * !doctype src
*/
#define MK_THRMODE_USER		MK_PSW_IO_U0
#define MK_THRMODE_SUPER	MK_PSW_IO_S
#define MK_THRIRQ_ENABLE	MK_PCX_PIE
#define MK_THRIRQ_DISABLE	MK_U(0)
#define MK_THRFPU_DISABLE	0 /* not used */
#define MK_THRFPU_ENABLE	0 /* not used */
#define MK_THRHWS_DEFAULT	(MK_PSW_CDC_DIS | MK_PSW_PRS_1)
#define MK_THRHWS_PRS1		(MK_PSW_CDC_DIS | MK_PSW_PRS_1)
#define MK_THRHWS_PRS2		(MK_PSW_CDC_DIS | MK_PSW_PRS_2)
#define MK_THRHWS_PRS3		(MK_PSW_CDC_DIS | MK_PSW_PRS_3)
#if (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define MK_THRHWS_PRS4		(MK_PSW_CDC_DIS | MK_PSW_PRS_4)
#define MK_THRHWS_PRS5		(MK_PSW_CDC_DIS | MK_PSW_PRS_5)
#endif

/* Safety task identifier
*/
#define MK_THRHWS_SAFEID	MK_PSW_S

/* Tricore-specific processor-state macros
*/
#define MK_THRMODE_USER1	MK_PSW_IO_U1

/* Inititalization macro for an mk_hwps_t (to be used with the macros defined above)
*/
#define MK_HWPS_INIT(pm, ilvl, ie, fpu, hwps) \
{										\
	(pm) | (hwps),		\
	MK_ShiftLeftU32((ilvl),MK_PCX_PCPN_SHFT) | (ie)	\
}

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
