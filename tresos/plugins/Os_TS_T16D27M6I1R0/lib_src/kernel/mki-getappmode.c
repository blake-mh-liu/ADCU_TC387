/* mki-getappmode.c
 *
 * This file contains the OS_MkiGetAppMode() function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>

/*!
 * OS_MkiGetAppMode()
 *
 * Determine the "application mode" (startup mode),
 * in a Safety OS.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_appmodeid_t OS_MkiGetAppMode(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_appmodeid_t resultMode = OS_NULLAPPMODE;

#if OS_N_CORES_MAX > 1
	mk_uint32_t coreId;

	/* COVPT-1 +2 */
	/* COVPT-2 */
	for (coreId = 0; coreId < OS_N_CORES_MAX; ++coreId)
	{
		/* During StartOS we already checked, whether the application modes are
		 * consistent. When we see the first "real" application mode, it is the
		 * application mode of the whole system.
		*/

		/* COVPT-3 */
		if (MK_LibIsCoreInUse(coreId))
		{
			os_appmodeid_t coreMode = MK_LibGetAppModeVoteOfCore(coreId);
			/* COVPT-4 +2 */
			if ((coreMode != OS_INCONSISTENT_APPMODE)
				&& (coreMode != OS_NULLAPPMODE))
			{
				resultMode = coreMode;
				break;
			}
		}
	}
#else
	/* COVPT-5 */
	resultMode = MK_LibGetAppModeVoteOfCore(OS_INITCORE);
#endif

	return resultMode;
}

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mki_getappmode_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
