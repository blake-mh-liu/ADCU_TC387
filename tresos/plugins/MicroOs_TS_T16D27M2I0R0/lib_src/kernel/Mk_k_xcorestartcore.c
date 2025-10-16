/* Mk_k_xcorestartcore.c
 *
 * This file contains the function MK_XcoreStartCore().
 *
 * (c) Elektrobit Automotive GmbH
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: Dir 4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
 *
 *
 * MISRAC2012-2) Deviated Rule: D4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_thread.h>
#include <public/Mk_error.h>

/* MK_XcoreStartCore() - start the core, so that it runs its configured "main" function.
 *
 * !LINKSTO Microkernel.Function.MK_XcoreStartCore, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_XcoreStartCore(mk_kernelcontrol_t *coreVars, mk_msgptr_t msg, mk_objectid_t fromCore)
{
	mk_errorid_t eid;
	mk_parametertype_t reply[MK_MSG_MAXPARAM];

	if ( coreVars->coreState == MK_coreState_Startup )
	{
		/* All OK; set the core state to Run and activate the "main" thread if there is one.
		 * (This is a core which has to be started manually, because otherwise it would already run.)
		*/
		eid = MK_eid_NoError;
		coreVars->coreState = MK_coreState_Run;

		/* Create the initialization thread that runs main() (or whatever has been configured as "main").
		 * All parameters to the thread are set to zero, to tell main that it has no arguments.
		*/
		if ( MK_initThreadConfig[coreVars->coreIndex] != MK_NULL )
		{
			MK_StartThread(	&coreVars->threadQueueHead,
							coreVars->aux2Thread,
							MK_initThreadConfig[coreVars->coreIndex]);
			MK_HwSetParameter1(coreVars->aux2Thread->regs, 0u);
			MK_HwSetParameter2(coreVars->aux2Thread->regs, 0u);
			MK_HwSetParameter3(coreVars->aux2Thread->regs, 0u);
			MK_HwSetParameter4(coreVars->aux2Thread->regs, 0u);
		}
	}
	else
	{
		eid = MK_eid_CoreIsAlreadyStarted;
	}

	reply[0] = (mk_parametertype_t)MK_ErrorInternalToOsek(eid);
	reply[1] = 0u;
	reply[2] = 0u;
	reply[3] = 0u;
	(void)MK_SendMessage(coreVars, fromCore, MK_xcore_Reply, msg->callerCookie, reply);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
