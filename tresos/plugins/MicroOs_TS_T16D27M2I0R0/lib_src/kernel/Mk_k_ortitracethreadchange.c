/* Mk_k_ortitracethreadchange.c
 *
 * This file contains the MK_OrtiTraceThreadChange function.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <Mk_kconfig.h>
#include <private/Mk_core.h>

#if MK_USE_ORTI_TRACE

#define MK_KERNEL_MARKER	0x20000000u
#define MK_TASK_MARKER		0x40000000u
#define MK_ISR_MARKER		0x60000000u
#define MK_HOOK_MARKER		0xa0000000u
#define MK_TF_MARKER		0xc0000000u

#define MK_SHUTDOWN_HOOK_MAGIC		0x00u
#define MK_ERROR_HOOK_MAGIC			0x01u
#define MK_PROTECTION_HOOK_MAGIC	0x02u

/* MK_OrtiTraceThreadChange updates the magic thread ID variables.
 *
 * This function is called via the MK_TRACE_THREAD_STATE macro mechanism if
 * enabled to provide a thread tracing facility for ORTI debuggers.
 *
 * !LINKSTO Microkernel.Function.MK_OrtiTraceThreadChange, 1
 * !doctype src
*/
void MK_OrtiTraceThreadChange
(
	mk_objecttype_t objType,
	mk_objectid_t objId,
	mk_threadstate_t newState
)
{
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();
	mk_uint32_t magicId = 0u;

	if ( newState == MK_THS_RUNNING )
	{
		switch (objType)
		{
		case MK_OBJTYPE_KERNEL:
			magicId = MK_KERNEL_MARKER | (mk_uint32_t)objId;
			break;

		case MK_OBJTYPE_TASK:
			magicId = MK_TASK_MARKER | (mk_uint32_t)objId;
			break;

		case MK_OBJTYPE_ISR:
		case MK_OBJTYPE_CTRSUBISR:
			magicId = MK_ISR_MARKER | (mk_uint32_t)objId;
			break;

		case MK_OBJTYPE_SHUTDOWNHOOK:
			magicId = MK_HOOK_MARKER | MK_SHUTDOWN_HOOK_MAGIC;
			break;

		case MK_OBJTYPE_ERRORHOOK:
			magicId = MK_HOOK_MARKER | MK_ERROR_HOOK_MAGIC;
			break;

		case MK_OBJTYPE_PROTECTIONHOOK:
			magicId = MK_HOOK_MARKER | MK_PROTECTION_HOOK_MAGIC;
			break;

		case MK_OBJTYPE_TRUSTEDFUNCTION:
			magicId = MK_TF_MARKER | (mk_uint32_t)objId;
			break;

		default:
			/* The incoming thread is of an auxiliary type: keep the old value. */
			break;
		}

		/* Only update the magic variable when the thread is of a relevant type.
		 * This improves the tracing results.
		*/
		if ( magicId != 0u )
		{
			*MK_ortiRunningThread[coreVars->coreIndex] = magicId;
		}
	}
}

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
