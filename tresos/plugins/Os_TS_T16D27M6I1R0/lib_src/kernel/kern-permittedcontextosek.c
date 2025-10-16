/* kern-permittedcontextosek.c
 *
 * This file contains the OS_permittedContextOsek array
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/* OS_permittedContextOsek
 *
 * This table implements the relaxed OSEK/VDX rules for calling context.
 * Using this table the only checks that are made are for errors that
 * would cause problems for the kernel. The calling contexts for
 * Autosar APIs remain restrictive as for Autosar, because selecting this
 * table is only meant for backwards compatibility.
 *
 * The table contains an entry for each system service, identified by its
 * SID (see Os_error.h).
 *
 * A system-service's entry in this table contains a bit for each possible
 * calling context. If the bit is 1, the service is permitted to be called
 * from the context.
*/
const os_callermask_t OS_permittedContextOsek[OS_SID_XXX] =
{
	OS_INTASKMASK|						/* 0: GetApplicationID		*/
	OS_INCAT2MASK|
	OS_INERRORHOOKMASK|
	OS_INPRETASKHOOKMASK|
	OS_INPOSTTASKHOOKMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INSHUTDOWNHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 1: GetISRID					*/
	OS_INCAT2MASK|
	OS_INCAT1MASK|
	OS_INACBMASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK,

	OS_INTASKMASK|						/* 2: CallTrustedFunction		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 3: CheckIsrMemoryAccess		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK,

	OS_INTASKMASK|						/* 4: CheckTaskMemoryAccess	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK,

	OS_INTASKMASK|						/* 5: CheckObjectAccess		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK,

	OS_INTASKMASK|						/* 6: CheckObjectOwnership		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK,

	OS_INTASKMASK|						/* 7: StartScheduleTableRel	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 8: StartScheduleTableAbs	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 9: StopScheduleTable		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 10: ChainScheduleTable/NextScheduleTable	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 11: StartScheduleTableSynchron	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 12: SyncScheduleTable		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 13: SetScheduleTableAsync	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 14: GetScheduleTableStatus	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 15: Advance/IncrementCounter	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 16: GetCounterValue	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 17: GetElapsedCounterValue/GetElapsedValue	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 18: TerminateApplication		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK,

	OS_INTASKMASK|						/* 19: AllowAccess				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 20: GetApplicationState		*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INERRORHOOKMASK|
	OS_INPRETASKHOOKMASK|
	OS_INPOSTTASKHOOKMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INSHUTDOWNHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_INTRUSTEDMASK,

	OS_INALLMASK,						/* 21: UnknownSyscall			*/

	OS_INTASKMASK|						/* 22: ActivateTask				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK,						/* 23: TerminateTask			*/

	OS_INTASKMASK,						/* 24: ChainTask				*/

	OS_INTASKMASK,						/* 25: Schedule					*/

	OS_INALLMASK,						/* 26: GetTaskID				*/

	OS_INALLMASK,						/* 27: GetTaskState				*/

	OS_INTASKMASK|						/* 28: SuspendOSInterrupts,SuspendAllInterrupts,DisableAllInterrupts	*/
	OS_INCAT2MASK|
	OS_INCAT1MASK|
	OS_INERRORHOOKMASK|
	OS_INPRETASKHOOKMASK|
	OS_INPOSTTASKHOOKMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INSHUTDOWNHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_INACBMASK|
	OS_INBOOTMASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 29: ResumeOSInterrupts,ResumeAllInterrupts,EnableAllInterrupts		*/
	OS_INCAT2MASK|
	OS_INCAT1MASK|
	OS_INERRORHOOKMASK|
	OS_INPRETASKHOOKMASK|
	OS_INPOSTTASKHOOKMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INSHUTDOWNHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_INACBMASK|
	OS_INBOOTMASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 30: GetResource				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 31: ReleaseResource			*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 32: SetEvent					*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK,						/* 33: ClearEvent				*/

	OS_INALLMASK,						/* 34: GetEvent					*/

	OS_INTASKMASK,						/* 35: WaitEvent				*/

	OS_INALLMASK,						/* 36: GetAlarmBase				*/

	OS_INALLMASK,						/* 37: GetAlarm					*/

	OS_INTASKMASK|						/* 38: SetRelAlarm				*/
	OS_INCAT2MASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_ININTERNALMASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 39: SetAbsAlarm				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 40: CancelAlarm				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INPROTECTIONHOOKMASK,

	OS_INALLMASK,						/* 41: GetActiveApplicationMode	*/

	OS_INBOOTMASK,						/* 42: StartOS					*/

	OS_INTASKMASK|						/* 43: ShutdownOS				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_INACBMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_INERRORHOOKMASK|
	OS_INSTARTUPHOOKMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 44: GetStackInfo				*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 45: DisableInterruptSource	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 46: EnableInterruptSource	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 47: TryToGetSpinlock */
	OS_INCAT2MASK,

	OS_INTASKMASK|						/* 48: ReleaseSpinlock */
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 49: ShutdownAllCores */
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_ININTERNALMASK,

	OS_INTASKMASK|						/* 50: ActivateTaskAsyn */
	OS_INCAT2MASK|
	OS_ININTERNALMASK,
	
	OS_INTASKMASK|						/* 51: SetEventAsyn */
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK|
	OS_ININTERNALMASK,
	
	OS_INTASKMASK|						/* 52: ClearPendingInterrupt	*/
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,
	
	OS_INTASKMASK|						/* 53: ControlIdle */
	OS_INCAT2MASK|
	OS_INTRUSTEDMASK,

	OS_INTASKMASK|						/* 54: GetCurrentApplicationID      */
	OS_INCAT2MASK|
	OS_INERRORHOOKMASK|
	OS_INPRETASKHOOKMASK|
	OS_INPOSTTASKHOOKMASK|
	OS_INSTARTUPHOOKMASK|
	OS_INSHUTDOWNHOOKMASK|
	OS_INPROTECTIONHOOKMASK|
	OS_INTRUSTEDMASK


	/* 55: OS_SID_XXX */

};

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_permittedcontextosek_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
