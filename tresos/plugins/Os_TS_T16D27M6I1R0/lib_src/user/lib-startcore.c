/* lib-startcore.c
 *
 * Starts a core.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_api.h>
#include <Os_spinlock.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_StartCore - Starts a core.
 *
 * The ID of the core to start is 'c'. The result is returned in the variable, where 'status' points to.
 * Note, this function must be called from privileged mode. This is because special processor registers
 * must be accessed to start a core and to ensure proper locking.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.StartCore, 1
 * Look! No ErrorHook!
 * !LINKSTO Kernel.Autosar.API.SystemServices.StartCore.NoErrorHook, 1
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StartCore(os_coreid_t core, os_result_t* status)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_intstatus_t const is = OS_TakeInternalLock(OS_CORESTARTED_LOCKID);
	{
		os_result_t result;

		OS_CacheInvalidate(OS_coreStarted, sizeof(OS_coreStarted));

		if ( OS_GetKernelData()->inFunction != OS_INBOOT )
		{
			/* Must be called BEFORE StartOS(). */
			result = OS_E_ACCESS;
		}
		else if (core >= OS_N_CORES_MAX)
		{
			/* Invalid Core ID */
			result = OS_E_ID;
		}
		else if ((core == OS_INITCORE) /* We don't start our own init-core. */
				 || OS_coreStarted[core])
		{
			/* Core 'core' was already started.
			 * !LINKSTO Kernel.Autosar.API.SystemServices.StartCore.WrongState, 1
			*/
			result = OS_E_STATE;
		}
		/* COVPT-1 */
		else if (!OS_CoreIsInUse(core))
		{
			/* This isn't an AUTOSAR core (from our point of view).
			 * Returning OS_E_STATE, because this is some kind of OS680.
			 *
			 * !LINKSTO Kernel.Autosar.API.SystemServices.StartCore.WrongState, 1
			*/
			result = OS_E_STATE;
		}
		else
		{
			result = OS_E_OK;
			OS_ArchStartCore(core);

			OS_coreStarted[core] = OS_TRUE;
			OS_CacheFlush(OS_coreStarted, sizeof(OS_coreStarted));
		}

		if ((OS_configMode & OS_EXTENDED) != 0u)
		{
			*status = result;
		}
		else
		{
			*status = OS_E_OK;
		}
	}
	OS_DropInternalLock(OS_CORESTARTED_LOCKID, is);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
const os_uint8_t OS_dummy_lib_startcore_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
