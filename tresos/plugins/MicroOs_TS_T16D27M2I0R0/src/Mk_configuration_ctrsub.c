/* Mk_configuration_ctrsub.c
 *
 * This file contains the configured counter subsystem function table for the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_ctrsubindex.h>
#include <private/Mk_ctrsub.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* Define the counter subsystem functions that haven't already been defined in the configuration.
*/
#define MK_CTRSUB_SETRELALARM					OS_MkwSetRelAlarm
#define MK_CTRSUB_SETABSALARM					OS_MkwSetAbsAlarm
#define MK_CTRSUB_CANCELALARM					OS_MkwCancelAlarm
#define MK_CTRSUB_GETALARM						OS_MkwGetAlarm
#define MK_CTRSUB_INCREMENTCOUNTER				OS_MkwIncrementCounter
#define MK_CTRSUB_GETCOUNTERVALUE				OS_MkwGetCounterValue
#define MK_CTRSUB_SIMTIMERADVANCE				OS_MkwSimTimerAdvance
#define MK_CTRSUB_STARTSCHEDULETABLE			OS_MkwStartScheduleTable
#define MK_CTRSUB_NEXTSCHEDULETABLE				OS_MkwNextScheduleTable
#define MK_CTRSUB_STOPSCHEDULETABLE				OS_MkwStopScheduleTable
#define MK_CTRSUB_STARTSCHEDULETABLESYNCHRON	OS_MkwStartScheduleTableSynchron
#define MK_CTRSUB_SYNCSCHEDULETABLE				OS_MkwSyncScheduleTable
#define MK_CTRSUB_SETSCHEDULETABLEASYNC			OS_MkwSetScheduleTableAsync
#define MK_CTRSUB_UPDATECOUNTER					OS_MkwUpdateCounter
#define MK_CTRSUB_TERMINATEAPPLICATION			OS_MkwTerminateApplication
#define MK_CTRSUB_STARTOS						OS_MkwStartOs

/* MK_CSSVC_ALARM() defines a counter subsystem service for alarms.
 *
 * If there are no alarms configured, all the services that operate on alarms are disabled.
 * Otherwise the services are defined using the OS service macro (MK_CTRSUB_xxx) and the AlarmToCore mapping table.
 *
 * Using the OS service macro still allows individual services to be left out if desired, but the microkernel
 * plays no role in this.
*/
#if MK_CFG_NALARMS == 0

#define MK_CSSVC_ALARM(fp, sid, sy)			MK_CSSVC(MK_UnknownCtrSubCall, 0, MK_NULL, (sid), (sy))

#else

static const mk_ctrsubobjprops_t MK_AlarmProperties[MK_CFG_NALARMS] = { MK_CFG_ALARMPROPERTIES };

#define MK_CSSVC_ALARM(fp, sid, sy)			MK_CSSVC((fp), MK_CFG_NALARMS, MK_AlarmProperties, (sid), (sy))

#endif

#define MK_CSSVC_SETRELALARM			MK_CSSVC_ALARM(MK_CTRSUB_SETRELALARM, MK_sid_SetRelAlarm, 0)
#define MK_CSSVC_SETABSALARM			MK_CSSVC_ALARM(MK_CTRSUB_SETABSALARM, MK_sid_SetAbsAlarm, 0)
#define MK_CSSVC_CANCELALARM			MK_CSSVC_ALARM(MK_CTRSUB_CANCELALARM, MK_sid_CancelAlarm, 0)
#define MK_CSSVC_GETALARM				MK_CSSVC_ALARM(MK_CTRSUB_GETALARM,    MK_sid_GetAlarm, 1)

/* MK_CSSVC_COUNTER() defines a counter subsystem service for counters.
 *
 * If there are no counters configured, all the services that operate on counters are disabled.
 * Otherwise the services are defined using the OS service macro (MK_CTRSUB_xxx) and the CounterToCore mapping table.
 *
 * Using the OS service macro still allows individual services to be left out if desired, but the microkernel
 * plays no role in this.
*/
#if MK_CFG_NCOUNTERS == 0

#define MK_CSSVC_COUNTER(fp, sid, sy)	MK_CSSVC(MK_UnknownCtrSubCall, 0, MK_NULL, (sid), (sy))

#else

static const mk_ctrsubobjprops_t MK_CounterProperties[MK_CFG_NCOUNTERS] = { MK_CFG_COUNTERPROPERTIES };

#define MK_CSSVC_COUNTER(fp, sid, sy)	MK_CSSVC((fp), MK_CFG_NCOUNTERS, MK_CounterProperties, (sid), (sy))

#endif

#define MK_CSSVC_INCREMENTCOUNTER		MK_CSSVC_COUNTER(MK_CTRSUB_INCREMENTCOUNTER, MK_sid_IncrementCounter, 0)
#define MK_CSSVC_GETCOUNTERVALUE		MK_CSSVC_COUNTER(MK_CTRSUB_GETCOUNTERVALUE,  MK_sid_GetCounterValue, 1)
#define MK_CSSVC_UPDATECOUNTER			MK_CSSVC_COUNTER(MK_CTRSUB_UPDATECOUNTER,    MK_sid_UpdateCounter, 1)

/* MK_CSSVC_TIMER() defines a counter subsystem service for timers.
 *
 * If there are no timers configured, all the services that operate on timers are disabled.
 * Otherwise the services are defined using the OS service macro (MK_CTRSUB_xxx) and the TimerToCore mapping table.
 *
 * Using the OS service macro still allows individual services to be left out if desired, but the microkernel
 * plays no role in this.
*/
#if MK_CFG_NTIMERS == 0

#define MK_CSSVC_TIMER(fp, sid, sy)		MK_CSSVC(MK_UnknownCtrSubCall, 0, MK_NULL, (sid), (sy))

#else

static const mk_ctrsubobjprops_t MK_TimerProperties[MK_CFG_NTIMERS] = { MK_CFG_TIMERPROPERTIES };

#define MK_CSSVC_TIMER(fp, sid, sy)		MK_CSSVC((fp), MK_CFG_NTIMERS, MK_TimerProperties, (sid), (sy))

#endif

#define MK_CSSVC_SIMTIMERADVANCE		MK_CSSVC_TIMER(MK_CTRSUB_SIMTIMERADVANCE, MK_sid_SimTimerAdvance, 0)

/* MK_CSSVC_ST() defines a counter subsystem service for schedule tables.
 *
 * If there are no schedule tables configured, all the services that operate on schedule tables are disabled.
 * Otherwise the services are defined using the OS service macro (MK_CTRSUB_xxx)
 * and the ScheduleTableToCore mapping table.
 *
 * Using the OS service macro still allows individual services to be left out if desired, but the microkernel
 * plays no role in this.
*/
#if MK_CFG_NSCHEDULETABLES == 0

#define MK_CSSVC_ST(fp, sid, sy)		MK_CSSVC(MK_UnknownCtrSubCall, 0, MK_NULL, (sid), (sy))

#else

static const mk_ctrsubobjprops_t MK_ScheduleTableProperties[MK_CFG_NSCHEDULETABLES] =
{
	MK_CFG_SCHEDULETABLEPROPERTIES
};

#define MK_CSSVC_ST(fp, sid, sy)		MK_CSSVC((fp), MK_CFG_NSCHEDULETABLES, MK_ScheduleTableProperties, (sid), (sy))

#endif

#define MK_CSSVC_STARTSCHEDULETABLE		MK_CSSVC_ST(MK_CTRSUB_STARTSCHEDULETABLE,     MK_sid_StartScheduleTable, 0)
#define MK_CSSVC_NEXTSCHEDULETABLE		MK_CSSVC_ST(MK_CTRSUB_NEXTSCHEDULETABLE,      MK_sid_NextScheduleTable, 0)
#define MK_CSSVC_STOPSCHEDULETABLE		MK_CSSVC_ST(MK_CTRSUB_STOPSCHEDULETABLE,      MK_sid_StopScheduleTable, 0)
#define MK_CSSVC_STARTSCHEDULETABLESYNCHRON	MK_CSSVC_ST(MK_CTRSUB_STARTSCHEDULETABLESYNCHRON, \
																				MK_sid_StartScheduleTableSynchron, 0)
#define MK_CSSVC_SYNCSCHEDULETABLE		MK_CSSVC_ST(MK_CTRSUB_SYNCSCHEDULETABLE,      MK_sid_SyncScheduleTable, 0)
#define MK_CSSVC_SETSCHEDULETABLEASYNC	MK_CSSVC_ST(MK_CTRSUB_SETSCHEDULETABLEASYNC,  MK_sid_SetScheduleTableAsync, 0)

/* MK_CSSVC_APP() defines a counter subsystem service for OS-applications.
 *
 * If there are no OS-applications configured, all the services that operate on OS-applications are disabled.
 * Otherwise the services are defined using the OS service macro (MK_CTRSUB_xxx). No mapping table is used
 * because the microkernel has internal mechanisms for mapping applications to cores.
*/
#if MK_CFG_NAPPLICATIONS == 0

#define MK_CSSVC_APP(fp, sid, sy)		MK_CSSVC(MK_UnknownCtrSubCall, 0, MK_NULL, (sid), (sy))

#else

#define MK_CSSVC_APP(fp, sid, sy)		MK_CSSVC((fp), MK_CFG_NAPPLICATIONS, MK_NULL, (sid), (sy))

#endif

#define MK_CSSVC_TERMINATEAPPLICATION	MK_CSSVC_APP(MK_CTRSUB_TERMINATEAPPLICATION, MK_sid_TerminateApplication, 0)

/* MK_CSSVC_OS() defines a counter subsystem service for OS control.
 *
 * The services are defined using the OS service macro (MK_CTRSUB_xxx). No mapping table is used
 * because the parameter is system-wide.
*/
#if MK_CFG_NSTARTMODES == 0

#define MK_CSSVC_OS(fp, sid, sy)		MK_CSSVC(MK_UnknownCtrSubCall, 0, MK_NULL, (sid), (sy))

#else

#define MK_CSSVC_OS(fp, sid, sy)		MK_CSSVC((fp), MK_CFG_NSTARTMODES, MK_NULL, (sid), (sy))

#endif

#define MK_CSSVC_STARTOS				MK_CSSVC_OS(MK_CTRSUB_STARTOS, MK_sid_StartOs, 1)

/* MK_ctrsubService - table of counter subsystem services
 *
 * Each service is configured with the function to use, the no. of objects, a core mapping for the objects
 * and a service ID.
*/
const mk_ctrsubservicedescriptor_t MK_ctrsubService[MK_N_CTRSUBFUNCS] =
{
	MK_CSSVC_SETRELALARM,
	MK_CSSVC_SETABSALARM,
	MK_CSSVC_CANCELALARM,
	MK_CSSVC_INCREMENTCOUNTER,
	MK_CSSVC_STARTSCHEDULETABLE,
	MK_CSSVC_STARTSCHEDULETABLESYNCHRON,
	MK_CSSVC_NEXTSCHEDULETABLE,
	MK_CSSVC_STOPSCHEDULETABLE,
	MK_CSSVC_SYNCSCHEDULETABLE,
	MK_CSSVC_SETSCHEDULETABLEASYNC,
	MK_CSSVC_SIMTIMERADVANCE,
	MK_CSSVC_GETCOUNTERVALUE,
	MK_CSSVC_GETALARM,
	MK_CSSVC_UPDATECOUNTER,
	MK_CSSVC_TERMINATEAPPLICATION,
	MK_CSSVC_STARTOS
};

const mk_objquantity_t MK_nAlarms = MK_CFG_NALARMS;
const mk_objquantity_t MK_nCounters = MK_CFG_NCOUNTERS;
const mk_objquantity_t MK_nScheduleTables = MK_CFG_NSCHEDULETABLES;
#if (MK_CFG_NALARMS > 0)
const mk_ctrsubobjprops_t * const MK_AlarmPropertyTable = MK_AlarmProperties;
#else
const mk_ctrsubobjprops_t * const MK_AlarmPropertyTable = MK_NULL;
#endif
#if (MK_CFG_NCOUNTERS > 0)
const mk_ctrsubobjprops_t * const MK_CounterPropertyTable = MK_CounterProperties;
#else
const mk_ctrsubobjprops_t * const MK_CounterPropertyTable = MK_NULL;
#endif
#if (MK_CFG_NSCHEDULETABLES > 0)
const mk_ctrsubobjprops_t * const MK_ScheduleTablePropertyTable = MK_ScheduleTableProperties;
#else
const mk_ctrsubobjprops_t * const MK_ScheduleTablePropertyTable = MK_NULL;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
