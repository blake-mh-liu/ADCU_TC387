/* Mk_k_multicallctrsub.c
 *
 * This file contains the MK_MultiCallCtrSub() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_ctrsubindex.h>
#include <private/Mk_core.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_message.h>

#if MK_MAXCORES <= 1
#error "This file is not needed for single-core systems."
#endif

/* MK_MultiCallCtrSub() requests a thread to run the given counter subsystem function with up to three parameters.
 *
 * This function makes a request to start a counter subsystem thread, either locally (by calling MK_LocalCallCtrSub)
 * or remotely by sending a message to the target core.
 *
 * !LINKSTO Microkernel.Function.MK_MultiCallCtrSub, 1
 * !doctype src
*/
mk_errorid_t MK_MultiCallCtrSub(mk_kernelcontrol_t *coreVars, mk_objectid_t functionIndex, mk_xcall_t callType)
{
	mk_thread_t *caller = coreVars->currentThread;
	const mk_ctrsubservicedescriptor_t *ctrsubDescr = &MK_ctrsubService[functionIndex];
	mk_parametertype_t p[MK_MSG_MAXPARAM];
	mk_objectid_t tgtCore;
	mk_parametertype_t objId;
	mk_errorid_t errorCode = MK_eid_Unknown;

	/* Get the first parameter to the counter subsystem service.
	*/
	objId = MK_HwGetParameter2(caller->regs);

	/* Range check on the object ID.
	*/
	if ( objId < (mk_parametertype_t) ctrsubDescr->nObjects )
	{
		/* Get the core that the counter subsystem object is allocated to.
		*/
		tgtCore = ctrsubDescr->props[objId].coreIndex;

		/* If the core is the core we're running on, activate the job locally.
		*/
		if ( tgtCore == coreVars->coreIndex )
		{
			/* Same core
			*/
			errorCode = MK_LocalCallCtrSub(coreVars, functionIndex, ctrsubDescr, objId, callType);
		}
		else
		{
			/* Cross-core
			*/
			p[0] = (mk_parametertype_t)functionIndex;
			p[1] = objId;
			p[2] = MK_HwGetParameter3(caller->regs);
			p[3] = MK_HwGetParameter4(caller->regs);

			errorCode = MK_SendMessage(coreVars, tgtCore, callType, MK_NULLCOOKIE, p);

			if ( (errorCode == MK_eid_NoError) && (callType == MK_xcore_CallCtrSub) )
			{
				/* Set up the mechanism for waiting for and receiving the reply.
				*/
				caller->xcoreReply.statusCode = MK_E_WAITFORREPLY;
				caller->xcoreReply.requestedValue = MK_WAITCOOKIE(coreVars->cookieGen, tgtCore);
				errorCode = MK_eid_WaitForReply;
			}
		}
	}
	else
	{
		errorCode = MK_eid_InvalidCtrSubObjectId;
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
