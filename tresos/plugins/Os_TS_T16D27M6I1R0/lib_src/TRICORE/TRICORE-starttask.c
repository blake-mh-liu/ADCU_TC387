/* TRICORE-starttask.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any
 * other type.
 *
 * Reason:
 * The pointer is passed to hardware, which is only interested in its value
 * and not in its type.
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to
 * object.
 *
 * Reason:
 * A pointer is read from hardware, which doesn't provide C language type
 * information. Hence, a type cast is required.
 *
 * MISRAC2012-3) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 * A value is read from hardware, which essentially represents a pointer.
 * The hardware, though, has no notion of C language types. Hence, the type
 * cast is required.
 */

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <TRICORE/Os_TRICORE_core.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_StartTask
 *
 * Starts the new task t. The task's dynamic state has already been set.
 * All that remains is for us to set up the registers for the task and then
 * "goto" the entry point.
 *
 * For TRICORE, we need to pay attention to the PCXI context list. The PCXI
 * register has already been set to zero by the system-call dispatcher. When
 * this function is called by the dispatcher a CSA is pushed onto the "used"
 * list. This CSA is filled with the the register contents for the
 * for the task. When the task is running in its "main" function, PCXI is
 * therefore zero, so that if the task returns, the resulting PCX==0 exception
 * can be trapped and handled accordingly.
 *
 * Notes on the values that OS_StartTask() poke into the CSA that is on the list:
 *  1. PSW for task represents the task's priveleges.
 *  2. Stack pointer for task must be word-aligned.
 *  3. Return address for task points to a dummy function rather than being
 *     OS_NULL. This ensures that of all the possible exceptions that could be
 *     caused by the task returning from its main function, only PCX-Underflow
 *     can happen, no matter in what order the Tricore checks things.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StartTask(const os_task_t *t)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uppercx_t *cx;
	os_uint32_t sp = (((os_uint32_t)t->stackBase) + t->stackLen)
					 & (os_uint32_t) ~((os_uint32_t)3u);
	os_uint32_t px;
	os_uint32_t pxLvl;
	const os_appcontext_t *a = OS_GET_APP(t->app);

	/* Ensure that the function call is complete before reading PCXI
	*/
	OS_DSYNC();

	px = OS_MFCR(OS_PCXI);
	/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
	cx = (os_uppercx_t *)OS_AddrFromCx(px);

	/* cx now points to the topmost CSA on the list. The contents of this
	 * CSA will be restored by the RFE at the end of this routine.
	 * Contents:
	 *		pcxi	0	(causes a pcxi==0 trap on return from task function)
	 *		psw		from application context, |1 for a call depth of 1
	 *		a10		Task SP (forced to 32-bit alignment - see above)
	 *		a11		"Return Address" for task. Shouldn't be needed.
	 *		a12-15	don't care
	 *		d8-15	don't care
	*/
	if ( OS_AppIsNull(t->app) )
	{
		/* Task has no application. Use default supervisor PSW instead */
		cx->psw = (OS_PSW_PRS_0|OS_PSW_IO_SU|OS_PSW_CDC_DIS);
		/* Deviation MISRAC2012-1 <+1> */
		cx->a11 = (os_uint32_t)&OS_NullFunction;
	}
	else
	{
		cx->psw = a->archapp.psw | 1u;	/* trace mode -> off */
		/* Deviation MISRAC2012-1 <+1> */
		cx->a11 = (os_uint32_t)&OS_NullFunction;
	}
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	/*RES 31:3 - Reserved , PPRS 2:0 rwh Previous PRS*/
	OS_MTCR(OS_PPRS,OS_PSW_GET_PPRS(cx->psw));
#endif

	cx->a10 = sp;
	cx->pcxi = 0;

	/* We set our RA (A11) to the task's entry point.
	 * Then we fiddle the call-depth counter in the PSW so that we
	 * can RFE from here.
	 *
	 * Internal resources at interrupt level are not permitted. However,
	 * if that changes in the future, the PCPN will need to be set to
	 * the resource's interrupt level here.
	*/
	pxLvl = OS_PCXI_PIE;
	px = (px & (OS_CX_CX|OS_PCXI_UL)) | pxLvl;
	OS_MTCR(OS_PCXI,px);
	OS_MTRA_FUNCPTR(t->entry);
	OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);
	OS_RFE();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_starttask_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
