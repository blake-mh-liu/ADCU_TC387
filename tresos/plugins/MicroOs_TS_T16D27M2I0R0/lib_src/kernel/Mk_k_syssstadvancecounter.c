/* Mk_k_syssstadvancecounter.c
 *
 * This file contains the function MK_SysSstAdvanceCounter()
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_NAMING_070]
 *  Unused parameters shall have their identifiers prefixed with unused_.
 *
 * Reason:
 *  The use of coreVars depends on the configuration. In multi-core configurations the variable is
 *  used while in single-core configurations the variable is not used. Therefore adding the unused_
 *  prefix does not make sense here.
 *  The macro MK_PARAM_UNUSED() is used in a corresponding preprocessor #if-#endif block. The CGC
 *  cannot identify this.
*/

#include <public/Mk_public_api.h>
#include <private/Mk_syscall.h>
#include <private/Mk_sst.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_tool.h>
#include <private/Mk_errorhandling.h>

static mk_errorid_t MK_CheckSstId(mk_kernelcontrol_t * coreVars, mk_objectid_t sstId)
{
	mk_objectid_t sstIdLocal = sstId;
	mk_errorid_t errorCode = MK_eid_Unknown;

#if (MK_MAXCORES == 1)
	/* Deviation DCG-1 <+1> */
	MK_PARAM_UNUSED(coreVars);
#endif

	if (sstIdLocal < MK_nScheduleTables)
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
		sstIdLocal -= MK_nScheduleTables;

		if ( sstIdLocal >= MK_nSsts )
		{
			errorCode = MK_eid_InvalidSstId;
		}
#if MK_MAXCORES > 1
		else if (MK_sstConfigsBase[sstIdLocal].coreIndex != coreVars->coreIndex)
		{
			errorCode = MK_eid_CoreIdOutOfRange;
		}
#endif
		else
		{
			/* nothing */
		}
	}
	return errorCode;
}

/*
 * MK_SysSstAdvanceCounter() - check parameters and call MK_LocalSstAdvanceCounter()
 *
 * !LINKSTO Microkernel.Function.MK_SysSstAdvanceCounter, 1
 * !doctype src
*/
void MK_SysSstAdvanceCounter(mk_kernelcontrol_t * coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	/* Intentional deviation from standard system call parameter handling.
	 * See ASCMICROOS-4019 for details.
	*/
	mk_objectid_t sstId = (mk_objectid_t)MK_HwGetParameter1(caller->regs);
	mk_errorid_t errorCode = MK_CheckSstId(coreVars, sstId);

	mk_sstcounter_t *sstCntr;
	mk_tick_t delta;

	if ( errorCode == MK_eid_Unknown )
	{
		sstId -= MK_nScheduleTables;
		sstCntr = MK_sstConfigsBase[sstId].counter;
		delta = (mk_tick_t)MK_HwGetParameter2(caller->regs);

		if ( (delta <= 0u) || (delta >= sstCntr->counterModulus) )
		{
			errorCode = MK_eid_InvalidSstDelta;
		}
		else if ( sstCntr->state == MK_SST_STOPPED )
		{
			errorCode = MK_eid_OsNotRunning;
		}
		else if ( sstCntr->tickerId >= 0 )
		{
			/* A counter with a HW incrementer must not be concurrently advanced by software. */
			errorCode = MK_eid_InvalidSstId;
		}
		else
		{
			errorCode = MK_LocalSstAdvanceCounter(sstCntr, delta);
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
		osekError = MK_InternReportError(coreVars, MK_sid_SstAdvanceCounter, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
