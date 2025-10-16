/* kern-recvactivatetaskasyn.c
 *
 * This file contains the function OS_RecvActivateTaskAsyn().
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#define OS_SID OS_SID_ActivateTask
#define OS_SIF OS_svc_ActivateTask

/* Note: this comment is needed for asc_Os/tools/errdb-to-c.pl
 *
 * OS_ERRORCODE_CHECK(OS_ERROR_CoreIsDown)
*/

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>
#include <Os_panic.h>

/*!
 * OS_RecvActivateTaskAsyn()
 *
 * Handles cross-core ActivateTaskAsyn() calls.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvActivateTaskAsyn(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_taskid_t const tid = (os_taskid_t)msg->parameter[0];
	os_errorresult_t e;
	OS_PARAMETERACCESS_DECL
	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)tid);

	/* COVPT-1 */
	if (OS_IsValidTaskId(tid) && (msg->result == OS_NULL))
	{
		e = OS_LocalActivateTask(&OS_taskTableBase[tid]);
		if ( e != OS_ERRORCODE_NOCHECK(OS_ERROR_NoError) )
		{
			/* !LINKSTO Kernel.Autosar.Multicore.ActivateTaskAsyn.Errorhandling, 1
			*/
			(void)OS_ERROR_NOCHECK(e, OS_GET_PARAMETER_VAR());
		}
	}
	else
	{
		(void)OS_PANIC(OS_PANIC_CrosscoreCommunicationError);
	}
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_recvactivatetaskasyn_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
