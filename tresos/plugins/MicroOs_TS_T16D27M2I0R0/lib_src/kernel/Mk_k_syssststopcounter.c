/* Mk_k_syssststopcounter.c
 *
 * This file contains the function MK_SysSstStopCounter()
 *
 * (c) Elektrobit Automotive GmbH
*/


#include <public/Mk_public_api.h>
#include <private/Mk_syscall.h>
#include <private/Mk_sst.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_tool.h>
#include <private/Mk_errorhandling.h>


/*
 * MK_SysSstStopCounter() - check parameters and call MK_LocalSstStopCounter()
 *
 * !LINKSTO Microkernel.Function.MK_SysSstStopCounter, 1
 * !doctype src
*/
void MK_SysSstStopCounter(mk_kernelcontrol_t * coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	/* Intentional deviation from standard system call parameter handling.
	 * See ASCMICROOS-4019 for details.
	*/
	mk_objectid_t sstId = (mk_objectid_t)MK_HwGetParameter1(caller->regs);
	mk_errorid_t errorCode = MK_eid_Unknown;

	if (sstId < MK_nScheduleTables)
	{
		errorCode = MK_eid_InvalidSstId;
	}
	else
	{
		/* All schedule tables in the system have different ids.
		 * Ids of simple schedule tables are offset by the number of counter subsystem schedule tables,
		 * which is stored in MK_nScheduleTables.
		 * This means, ids of simple schedule tables start right above the largest id of
		 * all counter subsystem schedule tables. In other words, the smallest SST id is equal to
		 * MK_nScheduleTables.
		 */
		sstId -= MK_nScheduleTables;

		if ( sstId >= MK_nSsts )
		{
			errorCode = MK_eid_InvalidSstId;
		}
#if MK_MAXCORES > 1
		else if (MK_sstConfigsBase[sstId].coreIndex != coreVars->coreIndex)
		{
			errorCode = MK_eid_CoreIdOutOfRange;
		}
#endif
		else
		{
			mk_sstcounter_t *sstCntr = MK_sstConfigsBase[sstId].counter;

			errorCode = MK_LocalSstStopCounter(sstCntr);
		}
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_SstStopCounter, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
