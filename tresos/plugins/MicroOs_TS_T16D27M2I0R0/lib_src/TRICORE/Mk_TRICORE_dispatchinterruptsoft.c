/* Mk_TRICORE_dispatchinterruptsoft.c
 *
 * This file contains the function MK_TricoreDispatchInterruptSoft()
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>
#include <private/Mk_softvector.h>

/* MK_TricoreDispatchInterruptSoft()
 *
 * This function is entered via a jump instruction from every interrupt vector.
 * The vector provides the thread's PCXI value as parameter. The given PCXI points to the
 * lower context that has been saved in the entry stub. The PCPN field in this PCXI already
 * contains the SRPN of the interrupt we are just handling. We obtain the vector code by
 * subtracting 1 from the PCPN, to avoid a hole in the beginning of our soft vector table.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_TricoreDispatchInterruptSoft, 2
 * !doctype src
*/
void MK_TricoreDispatchInterruptSoft(mk_uint32_t pcxiValue)
{
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();
	mk_hwvectorcode_t vectorCode = MK_GetPcpnFromPcxi(pcxiValue) - 1u;

	/* Doesn't return if exception/interrupt is not "sane" */
	MK_ExceptionHandlerCommon(pcxiValue, vectorCode, coreVars, MK_exc_Interrupt, MK_FALSE);

	MK_DispatchInterruptSoft(vectorCode);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
