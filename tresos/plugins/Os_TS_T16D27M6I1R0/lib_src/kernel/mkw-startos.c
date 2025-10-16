/* mkw-startos.c
 *
 * This file contains the OS_MkwStartOs function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_LEVEL]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  The function OS_UpdateAppMode needs to implement an algorithm that performs
 *  multiple nested loops to negotiate the application mode for all configured
 *  cores. In the innermost loop, it has to choose between multiple
 *  alternatives that depend on complex conditions. This invariably leads to
 *  lots of if/else statements that drive up the HIS_LEVEL metric.
 *  The code presents these alternatives in a legible and understandable form,
 *  thus this violation of the HIS_LEVEL metric is tolerable.
*/

#include <Os_types.h>
#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_usr_api.h>
#include <Os_mkctrsub.h>
#include <Os_kernel.h>
#include <Os_panic.h>
#include <Os_tool.h>
#include <Os_Trace.h>

#if (MK_UNINITIALIZED_APPMODE != OS_INCONSISTENT_APPMODE)
#error "MK_UNINITIALIZED_APPMODE must equal OS_INCONSISTENT_APPMODE!"
#endif

#if (MK_DONOTCARE_APPMODE != OS_NULLAPPMODE)
#error "MK_DONOTCARE_APPMODE must equal OS_NULLAPPMODE!"
#endif

/* Definitions for OS_ERROR
*/
#define OS_SID	OS_SID_StartOs
#define OS_SIF	OS_svc_StartOs

#include <memmap/Os_mm_code_begin.h>

#if (OS_N_CORES > 1)
/* Helper function for updating the AppMode.
*/
static void OS_UpdateAppMode(os_appmodeid_t);
#endif

/*!
 * OS_MkwStartOs
 *
 * SafetyOS counter subsystem part of StartOS.
 *
 *  - Determines the AppMode
 *  - Runs all initialization functions
 *
 * !LINKSTO Kernel.API.OSControl.StartOS.API, 1
 *
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
mk_parametertype_t OS_MkwStartOs(
	mk_parametertype_t p0,
	mk_parametertype_t p1,
	mk_parametertype_t p2 )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t res = OS_E_UNKNOWN;
	const os_initfunc_t * fct;
	os_appmodeid_t const mode = (os_appmodeid_t)p0;
	os_boolean_t validAppmode = OS_FALSE;
	OS_PARAMETERACCESS_DECL
	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)mode);
	/* COVPT-1 */
	OS_TRACE_STARTOS_ENTRY(mode);

	OS_PARAM_UNUSED(p1);
	OS_PARAM_UNUSED(p2);

	/* COVPT-2 */
	if (mode >= OS_nStartModes)
	{
		validAppmode = OS_FALSE;
		/* In multi-core systems, cores are allowed to start with DONOTCARE. */
#if (OS_N_CORES > 1)
		/* COVPT-3 */
		if (mode == OS_NULLAPPMODE)
		{
			validAppmode = OS_TRUE;
		}
#endif
	}
	else
	{
		validAppmode = OS_TRUE;
	}

	/* COVPT-4 */
	if (validAppmode)
	{
		/* !LINKSTO Kernel.API.OSControl.StartOS.StartOS, 1
		*/
#if (OS_N_CORES > 1)
		OS_UpdateAppMode(mode);
#endif
		fct = &OS_initFunc[0];
		/* COVPT-5 */
		while (*fct != OS_NULL)
		{
			(*fct)();
			fct++;
		}
		/* StartupHooks aren't called here.
		 * They are run by special threads.
		*/
		/* ASCOS-3488 MK: The StartupHook is meant to be called by a hidden task */
		OS_CALLSTARTUPHOOK();
		res = OS_E_OK;
	}
	else
	{
		res = OS_ERROR(OS_ERROR_InvalidStartMode, OS_GET_PARAMETER_VAR());
	}
	OS_TRACE_STARTOS_EXIT_P(mode);

	/* The return type of StartOS is void, so it doesn't matter what we return.
	 * This result will be ignored.
	*/
	return res;
}
#include <memmap/Os_mm_code_end.h>

#include <memmap/Os_mm_code_begin.h>

#if (OS_N_CORES > 1)
/*!
 * OS_UpdateAppMode
 *
 * Checks, that the application modes passed to StartOS() are consistent.
 * When this is not the case, an endless loop is entered. See [OS608] in
 * AUTOSAR 4.0 Rev 3.
 * At least one call of StartOS() must provide a different value than OS_NULLAPPMODE
 * (same as DONOTCARE). See [OS610] in AUTOSAR 4.0 Rev 3.
 *
 * See also sec. 7.9.15.1 in AUTOSAR 4.0 Rev 3.
 */
/* Deviation DCG-1 */
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_UpdateAppMode(os_appmodeid_t mode)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_coreid_t myOwnCoreId;
	os_boolean_t appModeIsValid;

	/* COVPT-6 */
	myOwnCoreId = (os_coreid_t)GetCoreID();

	/* This core's AppMode vote was written by the microkernel, when StartOS was called.
	 * If our own AppMode vote hasn't been written correctly, hang here.
	*/
	/* COVPT-7 */
	while (MK_LibGetAppModeVoteOfCore(myOwnCoreId) != mode) { }

	/* Wait until every core has written its proposal and check whether they fit together.
	 * If they don't fit, we will hang here [OS608].
	*/
	do
	{
		os_coreid_t coreId;
		os_appmodeid_t resultMode;
		resultMode = OS_NULLAPPMODE;
		appModeIsValid = 1;
		/* COVPT-8 */
		for (coreId = 0; coreId < (os_coreid_t)OS_N_CORES_MAX; ++coreId)
		{
			/* COVPT-9 */
			if (MK_LibIsCoreInUse(coreId))
			{
				os_appmodeid_t coreMode = MK_LibGetAppModeVoteOfCore(coreId);
				/* COVPT-10 */
				if (coreMode == OS_INCONSISTENT_APPMODE)
				{
					/* Not all cores (which are in use) have written their proposal,
					 * so we can't determine the AppMode.
					*/
					appModeIsValid = 0;
				}
				/* COVPT-11 */
				else if (coreMode == OS_NULLAPPMODE)
				{
					/* We read a DONOTCARE - so we do not care.
					 * The AppMode of the other cores will be used [OS609].
					*/
				}
				/* COVPT-12 */
				else if (resultMode == OS_NULLAPPMODE)
				{
					/* We've seen no "real" AppModes yet and coreMode is a "real" AppMode,
					 * so either coreMode is the final resultMode [OS609],
					 * or we have inconsistent AppModes [OS608].
					*/
					resultMode = coreMode;
				}
				else
				{
					/* coreMode is a "real" AppMode.
					 * resultMode is a "real" AppMode or OS_INCONSISTENT_APPMODE.
					 * If coreMode and resultMode aren't equal, we have inconsistent AppModes [OS608].
					*/
					/* COVPT-13 */
					if (coreMode != resultMode)
					{
						resultMode = OS_INCONSISTENT_APPMODE;
						appModeIsValid = 0;
					}
				}
			}
		}
		/* If we've only seen DONOTCARES, we don't have a valid AppMode [OS610].
		*/
		/* COVPT-14 */
		if (resultMode == OS_NULLAPPMODE)
		{
			appModeIsValid = 0;
		}
	}
	/* COVPT-15 */
	while (!appModeIsValid);
}
#endif
#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mkw_startos_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
