/* mki-reporterror.c
 *
 * This file contains the OS_MkiReportError() function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.4 (advisory)
 * Evaluation of constant expressions should not lead to unsigned integer
 * wrap-around.
 *
 * Reason:
 * Intentional wrap-around to represent an unused parameter.
 *
 *
 * MISRAC2012-2) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * This is a wrapper function between microkernel counter-subsystem.
 * For some arguments, microkernel uses different essential types.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>

/*!
 * OS_MkiReportError()
 *
 * Reports an error from the counter subsystem thread.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_MkiReportError(mk_serviceid_t sid, os_errorresult_t e, os_paramtype_t *p)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_paramtype_t p0, p1;
	/* COVPT-1 +2 */
	/* COVPT-2 */
	if (p == OS_NULL)
	{
		/* Deviation MISRAC2012-1 <+2> */
		p0 = (os_paramtype_t)-1;
		p1 = (os_paramtype_t)-1;
	}
	else
	{
		p0 = p[0];
		p1 = p[1];
	}
	/* Deviation MISRAC2012-2 <+1> */
	return (os_result_t) MK_UsrReportError(sid, (mk_errorid_t)e, p0, p1);
}

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mki_reporterror_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
