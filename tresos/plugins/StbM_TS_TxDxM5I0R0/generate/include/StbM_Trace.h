/**
 * \file
 *
 * \brief AUTOSAR StbM
 *
 * This file contains the implementation of the AUTOSAR
 * module StbM.
 *
 * \version 5.0.9
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef STBM_TRACE_H
#define STBM_TRACE_H
/*==================[inclusions]============================================*/

[!IF "node:exists(as:modconf('Dbg'))"!]
#include <Dbg.h>
[!ENDIF!]

/*==================[macros]================================================*/

#ifndef DBG_STBM_INIT_ENTRY
/** \brief Entry point of function StbM_Init */
#define DBG_STBM_INIT_ENTRY(a)
#endif

#ifndef DBG_STBM_INIT_EXIT
/** \brief Exit point of function StbM_Init */
#define DBG_STBM_INIT_EXIT(a)
#endif


#ifndef DBG_STBM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function StbM_GetVersionInfo */
#define DBG_STBM_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_STBM_GETVERSIONINFO_EXIT
/** \brief Exit point of function StbM_GetVersionInfo */
#define DBG_STBM_GETVERSIONINFO_EXIT(a)
#endif


#ifndef DBG_STBM_MAINFUNCTION_ENTRY
/** \brief Entry point of function StbM_MainFunction */
#define DBG_STBM_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_STBM_MAINFUNCTION_EXIT
/** \brief Exit point of function StbM_MainFunction */
#define DBG_STBM_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_STBM_GETCURRENTTIME_ENTRY
/** \brief Entry point of function StbM_GetCurrentTime */
#define DBG_STBM_GETCURRENTTIME_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_GETCURRENTTIME_EXIT
/** \brief Exit point of function StbM_GetCurrentTime */
#define DBG_STBM_GETCURRENTTIME_EXIT(a,b,c,d)
#endif


#ifndef DBG_STBM_GETCURRENTTIMEEXTENDED_ENTRY
/** \brief Entry point of function StbM_GetCurrentTimeExtended */
#define DBG_STBM_GETCURRENTTIMEEXTENDED_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_GETCURRENTTIMEEXTENDED_EXIT
/** \brief Exit point of function StbM_GetCurrentTimeExtended */
#define DBG_STBM_GETCURRENTTIMEEXTENDED_EXIT(a,b,c,d)
#endif


#ifndef DBG_STBM_GETTXFRESHNESS_ENTRY
/** \brief Entry point of function StbM_GetTxFreshness */
#define DBG_STBM_GETTXFRESHNESS_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_GETTXFRESHNESS_EXIT
/** \brief Exit point of function StbM_GetTxFreshness */
#define DBG_STBM_GETTXFRESHNESS_EXIT(a,b,c,d)
#endif

#ifndef DBG_STBM_GETTXFRESHNESSTRUNCDATA_ENTRY
/** \brief Entry point of function StbM_GetTxFreshnessTruncData */
#define DBG_STBM_GETTXFRESHNESSTRUNCDATA_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_STBM_GETTXFRESHNESSTRUNCDATA_EXIT
/** \brief Exit point of function StbM_GetTxFreshnessTruncData */
#define DBG_STBM_GETTXFRESHNESSTRUNCDATA_EXIT(a,b,c,d,e,f)
#endif


#ifndef DBG_STBM_GETRXFRESHNESS_ENTRY
/** \brief Entry point of function StbM_GetRxFreshness */
#define DBG_STBM_GETRXFRESHNESS_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_STBM_GETRXFRESHNESS_EXIT
/** \brief Exit point of function StbM_GetRxFreshness */
#define DBG_STBM_GETRXFRESHNESS_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_STBM_SPDUTXCONFIRMATION_ENTRY
/** \brief Entry point of function StbM_SPduTxConfirmation */
#define DBG_STBM_SPDUTXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_STBM_SPDUTXCONFIRMATION_EXIT
/** \brief Exit point of function StbM_SPduTxConfirmation */
#define DBG_STBM_SPDUTXCONFIRMATION_EXIT(a)
#endif


#ifndef DBG_STBM_GETMASTERCONFIG_ENTRY
/** \brief Entry point of function StbM_GetMasterConfig */
#define DBG_STBM_GETMASTERCONFIG_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETMASTERCONFIG_EXIT
/** \brief Exit point of function StbM_GetMasterConfig */
#define DBG_STBM_GETMASTERCONFIG_EXIT(a,b,c)
#endif

#ifndef DBG_STBM_BUSGETCURRENTTIME_ENTRY
/** \brief Entry point of function StbM_BusGetCurrentTime */
#define DBG_STBM_BUSGETCURRENTTIME_ENTRY(a,b,c,d)
#endif

#ifndef DBG_STBM_BUSGETCURRENTTIME_EXIT
/** \brief Exit point of function StbM_BusGetCurrentTime */
#define DBG_STBM_BUSGETCURRENTTIME_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_STBM_GETCURRENTVIRTUALLOCALTIME_ENTRY
/** \brief Entry point of function StbM_GetCurrentVirtualLocalTime */
#define DBG_STBM_GETCURRENTVIRTUALLOCALTIME_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETCURRENTVIRTUALLOCALTIME_EXIT
/** \brief Exit point of function StbM_GetCurrentVirtualLocalTime */
#define DBG_STBM_GETCURRENTVIRTUALLOCALTIME_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_SETGLOBALTIME_ENTRY
/** \brief Entry point of function StbM_SetGlobalTime */
#define DBG_STBM_SETGLOBALTIME_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_SETGLOBALTIME_EXIT
/** \brief Exit point of function StbM_SetGlobalTime */
#define DBG_STBM_SETGLOBALTIME_EXIT(a,b,c,d)
#endif


#ifndef DBG_STBM_CANSETMASTERTIMINGDATA_ENTRY
/** \brief Entry point of function StbM_CanSetMasterTimingData */
#define DBG_STBM_CANSETMASTERTIMINGDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_CANSETMASTERTIMINGDATA_EXIT
/** \brief Exit point of function StbM_CanSetMasterTimingData */
#define DBG_STBM_CANSETMASTERTIMINGDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_FRSETMASTERTIMINGDATA_ENTRY
/** \brief Entry point of function StbM_FrSetMasterTimingData */
#define DBG_STBM_FRSETMASTERTIMINGDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_FRSETMASTERTIMINGDATA_EXIT
/** \brief Exit point of function StbM_FrSetMasterTimingData */
#define DBG_STBM_FRSETMASTERTIMINGDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_ETHSETMASTERTIMINGDATA_ENTRY
/** \brief Entry point of function StbM_EthSetMasterTimingData */
#define DBG_STBM_ETHSETMASTERTIMINGDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_ETHSETMASTERTIMINGDATA_EXIT
/** \brief Exit point of function StbM_EthSetMasterTimingData */
#define DBG_STBM_ETHSETMASTERTIMINGDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_CANSETSLAVETIMINGDATA_ENTRY
/** \brief Entry point of function StbM_CanSetSlaveTimingData */
#define DBG_STBM_CANSETSLAVETIMINGDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_CANSETSLAVETIMINGDATA_EXIT
/** \brief Exit point of function StbM_CanSetSlaveTimingData */
#define DBG_STBM_CANSETSLAVETIMINGDATA_EXIT(a,b,c)
#endif



#ifndef DBG_STBM_FRSETSLAVETIMINGDATA_ENTRY
/** \brief Entry point of function StbM_FrSetSlaveTimingData */
#define DBG_STBM_FRSETSLAVETIMINGDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_FRSETSLAVETIMINGDATA_EXIT
/** \brief Exit point of function StbM_FrSetSlaveTimingData */
#define DBG_STBM_FRSETSLAVETIMINGDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_ETHSETSLAVETIMINGDATA_ENTRY
/** \brief Entry point of function StbM_EthSetSlaveTimingData */
#define DBG_STBM_ETHSETSLAVETIMINGDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_ETHSETSLAVETIMINGDATA_EXIT
/** \brief Exit point of function StbM_EthSetSlaveTimingData */
#define DBG_STBM_ETHSETSLAVETIMINGDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_ETHSETPDELAYINITIATORDATA_ENTRY
/** \brief Entry point of function StbM_EthSetPdelayInitiatorData */
#define DBG_STBM_ETHSETPDELAYINITIATORDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_ETHSETPDELAYINITIATORDATA_EXIT
/** \brief Exit point of function StbM_EthSetPdelayInitiatorData */
#define DBG_STBM_ETHSETPDELAYINITIATORDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_ETHSETPDELAYRESPONDERDATA_ENTRY
/** \brief Entry point of function StbM_EthSetPdelayResponderData */
#define DBG_STBM_ETHSETPDELAYRESPONDERDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_ETHSETPDELAYRESPONDERDATA_EXIT
/** \brief Exit point of function StbM_EthSetPdelayResponderData */
#define DBG_STBM_ETHSETPDELAYRESPONDERDATA_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_STARTTIMER_ENTRY
/** \brief Entry point of function StbM_StartTimer */
#define DBG_STBM_STARTTIMER_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_STARTTIMER_EXIT
/** \brief Exit point of function StbM_StartTimer */
#define DBG_STBM_STARTTIMER_EXIT(a,b,c,d)
#endif


#ifndef DBG_STBM_TIMERCALLBACK_ENTRY
/** \brief Entry point of function StbM_TimerCallback */
#define DBG_STBM_TIMERCALLBACK_ENTRY()
#endif

#ifndef DBG_STBM_TIMERCALLBACK_EXIT
/** \brief Exit point of function StbM_TimerCallback */
#define DBG_STBM_TIMERCALLBACK_EXIT()
#endif


#ifndef DBG_STBM_UPDATEGLOBALTIME_ENTRY
/** \brief Entry point of function StbM_UpdateGlobalTime */
#define DBG_STBM_UPDATEGLOBALTIME_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_UPDATEGLOBALTIME_EXIT
/** \brief Exit point of function StbM_UpdateGlobalTime */
#define DBG_STBM_UPDATEGLOBALTIME_EXIT(a,b,c,d)
#endif

#ifndef DBG_STBM_SETUSERDATA_ENTRY
/** \brief Entry point of function StbM_SetUserData */
#define DBG_STBM_SETUSERDATA_ENTRY(a,b)
#endif

#ifndef DBG_STBM_SETUSERDATA_EXIT
/** \brief Exit point of function StbM_SetUserData */
#define DBG_STBM_SETUSERDATA_EXIT(a,b,c)
#endif

#ifndef DBG_STBM_SETOFFSET_ENTRY
/** \brief Entry point of function StbM_SetOffset */
#define DBG_STBM_SETOFFSET_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_SETOFFSET_EXIT
/** \brief Exit point of function StbM_SetOffset */
#define DBG_STBM_SETOFFSET_EXIT(a,b,c,d)
#endif

#ifndef DBG_STBM_GETOFFSET_ENTRY
/** \brief Entry point of function StbM_GetOffset */
#define DBG_STBM_GETOFFSET_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_GETOFFSET_EXIT
/** \brief Exit point of function StbM_GetOffset */
#define DBG_STBM_GETOFFSET_EXIT(a,b,c,d)
#endif

#ifndef DBG_STBM_BUSSETGLOBALTIME_ENTRY
/** \brief Entry point of function StbM_BusSetGlobalTime */
#define DBG_STBM_BUSSETGLOBALTIME_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_STBM_BUSSETGLOBALTIME_EXIT
/** \brief Exit point of function StbM_BusSetGlobalTime */
#define DBG_STBM_BUSSETGLOBALTIME_EXIT(a,b,c,d,e,f)
#endif


#ifndef DBG_STBM_TRIGGERTIMETRANSMISSION_ENTRY
/** \brief Entry point of function StbM_TriggerTimeTransmission */
#define DBG_STBM_TRIGGERTIMETRANSMISSION_ENTRY(a)
#endif

#ifndef DBG_STBM_TRIGGERTIMETRANSMISSION_EXIT
/** \brief Entry point of function StbM_TriggerTimeTransmission */
#define DBG_STBM_TRIGGERTIMETRANSMISSION_EXIT(a,b)
#endif

#ifndef DBG_STBM_GETTIMEBASEUPDATECOUNTER_ENTRY
/** \brief Entry point of function StbM_GetTimeBaseUpdateCounter */
#define DBG_STBM_GETTIMEBASEUPDATECOUNTER_ENTRY(a)
#endif

#ifndef DBG_STBM_GETTIMEBASEUPDATECOUNTER_EXIT
/** \brief Entry point of function StbM_GetTimeBaseUpdateCounter */
#define DBG_STBM_GETTIMEBASEUPDATECOUNTER_EXIT(a,b)
#endif

#ifndef DBG_STBM_GETTIMEBASESTATUS_ENTRY
/** \brief Entry point of function StbM_GetTimeBaseStatus */
#define DBG_STBM_GETTIMEBASESTATUS_ENTRY(a,b,c)
#endif

#ifndef DBG_STBM_GETTIMEBASESTATUS_EXIT
/** \brief Entry point of function StbM_GetTimeBaseStatus */
#define DBG_STBM_GETTIMEBASESTATUS_EXIT(a,b,c,d)
#endif

#ifndef DBG_STBM_SETRATECORRECTION_ENTRY
/** \brief Entry point of function StbM_SetRateCorrection */
#define DBG_STBM_SETRATECORRECTION_ENTRY(a,b)
#endif

#ifndef DBG_STBM_SETRATECORRECTION_EXIT
/** \brief Entry point of function StbM_SetRateCorrection */
#define DBG_STBM_SETRATECORRECTION_EXIT(a,b,c)
#endif

#ifndef DBG_STBM_GETRATEDEVIATION_ENTRY
/** \brief Entry point of function StbM_GetRateDeviation */
#define DBG_STBM_GETRATEDEVIATION_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETRATEDEVIATION_EXIT
/** \brief Entry point of function StbM_GetRateDeviation */
#define DBG_STBM_GETRATEDEVIATION_EXIT(a,b,c)
#endif

#ifndef DBG_STBM_GETSYNCTIMERECORDHEAD_ENTRY
/** \brief Entry point of function StbM_GetSyncTimeRecordHead */
#define DBG_STBM_GETSYNCTIMERECORDHEAD_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETSYNCTIMERECORDHEAD_EXIT
/** \brief Exit point of function StbM_GetSyncTimeRecordHead */
#define DBG_STBM_GETSYNCTIMERECORDHEAD_EXIT(a,b,c)
#endif

#ifndef DBG_STBM_GETOFFSETTIMERECORDHEAD_ENTRY
/** \brief Entry point of function StbM_GetOffsetTimeRecordHead */
#define DBG_STBM_GETOFFSETTIMERECORDHEAD_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETOFFSETTIMERECORDHEAD_EXIT
/** \brief Exit point of function StbM_GetOffsetTimeRecordHead */
#define DBG_STBM_GETOFFSETTIMERECORDHEAD_EXIT(a,b,c)
#endif



#ifndef DBG_STBM_GETTIMELEAP_ENTRY
/** \brief Entry point of function StbM_GetTimeLeap */
#define DBG_STBM_GETTIMELEAP_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETTIMELEAP_EXIT
/** \brief Exit point of function StbM_GetTimeLeap */
#define DBG_STBM_GETTIMELEAP_EXIT(a,b,c)
#endif



#ifndef DBG_STBM_SETBUSPROTOCOLPARAM_ENTRY
/** \brief Entry point of function StbM_SetBusProtocolParam */
#define DBG_STBM_SETBUSPROTOCOLPARAM_ENTRY(a,b)
#endif

#ifndef DBG_STBM_SETBUSPROTOCOLPARAM_EXIT
/** \brief Exit point of function StbM_SetBusProtocolParam */
#define DBG_STBM_SETBUSPROTOCOLPARAM_EXIT(a,b,c)
#endif

#ifndef DBG_STBM_GETBUSPROTOCOLPARAM_ENTRY
/** \brief Entry point of function StbM_GetBusProtocolParam */
#define DBG_STBM_GETBUSPROTOCOLPARAM_ENTRY(a,b)
#endif

#ifndef DBG_STBM_GETBUSPROTOCOLPARAM_EXIT
/** \brief Exit point of function StbM_GetBusProtocolParam */
#define DBG_STBM_GETBUSPROTOCOLPARAM_EXIT(a,b,c)
#endif


#ifndef DBG_STBM_CLONETIMEBASE_ENTRY
/** \brief Entry point of function StbM_CloneTimeBase */
#define DBG_STBM_CLONETIMEBASE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_STBM_CLONETIMEBASE_EXIT
/** \brief Exit point of function StbM_CloneTimeBase */
#define DBG_STBM_CLONETIMEBASE_EXIT(a,b,c,d)
#endif


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* ifndef STBM_TRACE_H */
/*==================[end of file]===========================================*/
