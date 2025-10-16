/**EB_Automotive_C_Source_File */

#ifndef COMM_TRACE_H
#define COMM_TRACE_H

/*==[Includes]================================================================*/

#include <EBStubs_Cfg.h>
#include <ComM.h>

/*==[Macros]==================================================================*/

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE
#define EBSTUBS_UNIT_FUNCTION_TRACE STD_OFF
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM STD_ON
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER */

#ifndef EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION
#define EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION EBSTUBS_UNIT_FUNCTION_TRACE_COMM
#endif /* EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION */

/* These macros define how the names of the dummy functions are composed. */
#ifndef EBTEST_FCT_ENTRY
#define EBTEST_FCT_ENTRY(x) (x)
#endif

#ifndef EBTEST_FCT_EXIT
#define EBTEST_FCT_EXIT(x) (x##_Exit)
#endif

/*==[Macros]==================================================================*/

#if (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON)

/* --- Function: ComM_Init--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT == STD_ON)
#ifndef DBG_COMM_INIT_ENTRY
/** \brief Entry point of function ComM_Init() */
#define DBG_COMM_INIT_ENTRY(p1) \
    EbTest_ComM_Init_Entry( EBTEST_FCT_ENTRY(&ComM_Init) )
#else
#error DBG_COMM_INIT_ENTRY already defined!
#endif

#ifndef DBG_COMM_INIT_EXIT
/** \brief Exit point of function ComM_Init() */
#define DBG_COMM_INIT_EXIT(p1) \
  EbTest_ComM_Init_Exit( EBTEST_FCT_EXIT(&ComM_Init) )
#else
#error DBG_COMM_INIT_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT == STD_ON) */

/* --- Function: ComM_IsValidConfig--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG == STD_ON)
#ifndef DBG_COMM_ISVALIDCONFIG_ENTRY
/** \brief Entry point of function ComM_IsValidConfig() */
#define DBG_COMM_ISVALIDCONFIG_ENTRY(p1) \
    EbTest_ComM_IsValidConfig_Entry( EBTEST_FCT_ENTRY(&ComM_IsValidConfig) )
#else
#error DBG_COMM_ISVALIDCONFIG_ENTRY already defined!
#endif

#ifndef DBG_COMM_ISVALIDCONFIG_EXIT
/** \brief Exit point of function ComM_IsValidConfig() */
#define DBG_COMM_ISVALIDCONFIG_EXIT(retval, p1) \
  EbTest_ComM_IsValidConfig_Exit( EBTEST_FCT_EXIT(&ComM_IsValidConfig) )
#else
#error DBG_COMM_ISVALIDCONFIG_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG == STD_ON) */

/* --- Function: ComM_DeInit--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT == STD_ON)
#ifndef DBG_COMM_DEINIT_ENTRY
/** \brief Entry point of function ComM_DeInit() */
#define DBG_COMM_DEINIT_ENTRY() \
    EbTest_ComM_DeInit_Entry( EBTEST_FCT_ENTRY(&ComM_DeInit) )
#else
#error DBG_COMM_DEINIT_ENTRY already defined!
#endif

#ifndef DBG_COMM_DEINIT_EXIT
/** \brief Exit point of function ComM_DeInit() */
#define DBG_COMM_DEINIT_EXIT() \
  EbTest_ComM_DeInit_Exit( EBTEST_FCT_EXIT(&ComM_DeInit) )
#else
#error DBG_COMM_DEINIT_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT == STD_ON) */

/* --- Function: ComM_GetState--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE == STD_ON)
#ifndef DBG_COMM_GETSTATE_ENTRY
/** \brief Entry point of function ComM_GetState() */
#define DBG_COMM_GETSTATE_ENTRY(p1, p2) \
    EbTest_ComM_GetState_Entry( EBTEST_FCT_ENTRY(&ComM_GetState) )
#else
#error DBG_COMM_GETSTATE_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETSTATE_EXIT
/** \brief Exit point of function ComM_GetState() */
#define DBG_COMM_GETSTATE_EXIT(retval, p1, p2) \
  EbTest_ComM_GetState_Exit( EBTEST_FCT_EXIT(&ComM_GetState) )
#else
#error DBG_COMM_GETSTATE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE == STD_ON) */

/* --- Function: ComM_GetStatus--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS == STD_ON)
#ifndef DBG_COMM_GETSTATUS_ENTRY
/** \brief Entry point of function ComM_GetStatus() */
#define DBG_COMM_GETSTATUS_ENTRY(p1) \
    EbTest_ComM_GetStatus_Entry( EBTEST_FCT_ENTRY(&ComM_GetStatus) )
#else
#error DBG_COMM_GETSTATUS_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETSTATUS_EXIT
/** \brief Exit point of function ComM_GetStatus() */
#define DBG_COMM_GETSTATUS_EXIT(retval, p1) \
  EbTest_ComM_GetStatus_Exit( EBTEST_FCT_EXIT(&ComM_GetStatus) )
#else
#error DBG_COMM_GETSTATUS_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS == STD_ON) */

/* --- Function: ComM_GetInhibitionStatus--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS == STD_ON)
#ifndef DBG_COMM_GETINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_GetInhibitionStatus() */
#define DBG_COMM_GETINHIBITIONSTATUS_ENTRY(p1, p2) \
    EbTest_ComM_GetInhibitionStatus_Entry( EBTEST_FCT_ENTRY(&ComM_GetInhibitionStatus) )
#else
#error DBG_COMM_GETINHIBITIONSTATUS_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_GetInhibitionStatus() */
#define DBG_COMM_GETINHIBITIONSTATUS_EXIT(retval, p1, p2) \
  EbTest_ComM_GetInhibitionStatus_Exit( EBTEST_FCT_EXIT(&ComM_GetInhibitionStatus) )
#else
#error DBG_COMM_GETINHIBITIONSTATUS_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS == STD_ON) */

/* --- Function: ComM_RequestComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE == STD_ON)
#ifndef DBG_COMM_REQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_RequestComMode() */
#define DBG_COMM_REQUESTCOMMODE_ENTRY(p1, p2) \
    EbTest_ComM_RequestComMode_Entry( EBTEST_FCT_ENTRY(&ComM_RequestComMode) )
#else
#error DBG_COMM_REQUESTCOMMODE_ENTRY already defined!
#endif

#ifndef DBG_COMM_REQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_RequestComMode() */
#define DBG_COMM_REQUESTCOMMODE_EXIT(retval, p1, p2) \
  EbTest_ComM_RequestComMode_Exit( EBTEST_FCT_EXIT(&ComM_RequestComMode) )
#else
#error DBG_COMM_REQUESTCOMMODE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE == STD_ON) */

/* --- Function: ComM_GetMaxComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE == STD_ON)
#ifndef DBG_COMM_GETMAXCOMMODE_ENTRY
/** \brief Entry point of function ComM_GetMaxComMode() */
#define DBG_COMM_GETMAXCOMMODE_ENTRY(p1, p2) \
    EbTest_ComM_GetMaxComMode_Entry( EBTEST_FCT_ENTRY(&ComM_GetMaxComMode) )
#else
#error DBG_COMM_GETMAXCOMMODE_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETMAXCOMMODE_EXIT
/** \brief Exit point of function ComM_GetMaxComMode() */
#define DBG_COMM_GETMAXCOMMODE_EXIT(retval, p1, p2) \
  EbTest_ComM_GetMaxComMode_Exit( EBTEST_FCT_EXIT(&ComM_GetMaxComMode) )
#else
#error DBG_COMM_GETMAXCOMMODE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE == STD_ON) */

/* --- Function: ComM_GetRequestedComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE == STD_ON)
#ifndef DBG_COMM_GETREQUESTEDCOMMODE_ENTRY
/** \brief Entry point of function ComM_GetRequestedComMode() */
#define DBG_COMM_GETREQUESTEDCOMMODE_ENTRY(p1, p2) \
    EbTest_ComM_GetRequestedComMode_Entry( EBTEST_FCT_ENTRY(&ComM_GetRequestedComMode) )
#else
#error DBG_COMM_GETREQUESTEDCOMMODE_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETREQUESTEDCOMMODE_EXIT
/** \brief Exit point of function ComM_GetRequestedComMode() */
#define DBG_COMM_GETREQUESTEDCOMMODE_EXIT(retval, p1, p2) \
  EbTest_ComM_GetRequestedComMode_Exit( EBTEST_FCT_EXIT(&ComM_GetRequestedComMode) )
#else
#error DBG_COMM_GETREQUESTEDCOMMODE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE == STD_ON) */

/* --- Function: ComM_GetCurrentComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE == STD_ON)
#ifndef DBG_COMM_GETCURRENTCOMMODE_ENTRY
/** \brief Entry point of function ComM_GetCurrentComMode() */
#define DBG_COMM_GETCURRENTCOMMODE_ENTRY(p1, p2) \
    EbTest_ComM_GetCurrentComMode_Entry( EBTEST_FCT_ENTRY(&ComM_GetCurrentComMode) )
#else
#error DBG_COMM_GETCURRENTCOMMODE_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETCURRENTCOMMODE_EXIT
/** \brief Exit point of function ComM_GetCurrentComMode() */
#define DBG_COMM_GETCURRENTCOMMODE_EXIT(retval, p1, p2) \
  EbTest_ComM_GetCurrentComMode_Exit( EBTEST_FCT_EXIT(&ComM_GetCurrentComMode) )
#else
#error DBG_COMM_GETCURRENTCOMMODE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE == STD_ON) */

/* --- Function: ComM_PreventWakeUp--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP == STD_ON)
#ifndef DBG_COMM_PREVENTWAKEUP_ENTRY
/** \brief Entry point of function ComM_PreventWakeUp() */
#define DBG_COMM_PREVENTWAKEUP_ENTRY(p1, p2) \
    EbTest_ComM_PreventWakeUp_Entry( EBTEST_FCT_ENTRY(&ComM_PreventWakeUp) )
#else
#error DBG_COMM_PREVENTWAKEUP_ENTRY already defined!
#endif

#ifndef DBG_COMM_PREVENTWAKEUP_EXIT
/** \brief Exit point of function ComM_PreventWakeUp() */
#define DBG_COMM_PREVENTWAKEUP_EXIT(retval, p1, p2) \
  EbTest_ComM_PreventWakeUp_Exit( EBTEST_FCT_EXIT(&ComM_PreventWakeUp) )
#else
#error DBG_COMM_PREVENTWAKEUP_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP == STD_ON) */

/* --- Function: ComM_LimitChannelToNoComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE == STD_ON)
#ifndef DBG_COMM_LIMITCHANNELTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_LimitChannelToNoComMode() */
#define DBG_COMM_LIMITCHANNELTONOCOMMODE_ENTRY(p1, p2) \
    EbTest_ComM_LimitChannelToNoComMode_Entry( EBTEST_FCT_ENTRY(&ComM_LimitChannelToNoComMode) )
#else
#error DBG_COMM_LIMITCHANNELTONOCOMMODE_ENTRY already defined!
#endif

#ifndef DBG_COMM_LIMITCHANNELTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_LimitChannelToNoComMode() */
#define DBG_COMM_LIMITCHANNELTONOCOMMODE_EXIT(retval, p1, p2) \
  EbTest_ComM_LimitChannelToNoComMode_Exit( EBTEST_FCT_EXIT(&ComM_LimitChannelToNoComMode) )
#else
#error DBG_COMM_LIMITCHANNELTONOCOMMODE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE == STD_ON) */

/* --- Function: ComM_LimitECUToNoComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE == STD_ON)
#ifndef DBG_COMM_LIMITECUTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_LimitECUToNoComMode() */
#define DBG_COMM_LIMITECUTONOCOMMODE_ENTRY(p1) \
    EbTest_ComM_LimitECUToNoComMode_Entry( EBTEST_FCT_ENTRY(&ComM_LimitECUToNoComMode) )
#else
#error DBG_COMM_LIMITECUTONOCOMMODE_ENTRY already defined!
#endif

#ifndef DBG_COMM_LIMITECUTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_LimitECUToNoComMode() */
#define DBG_COMM_LIMITECUTONOCOMMODE_EXIT(retval, p1) \
  EbTest_ComM_LimitECUToNoComMode_Exit( EBTEST_FCT_EXIT(&ComM_LimitECUToNoComMode) )
#else
#error DBG_COMM_LIMITECUTONOCOMMODE_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE == STD_ON) */

/* --- Function: ComM_ReadInhibitCounter--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER == STD_ON)
#ifndef DBG_COMM_READINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ReadInhibitCounter() */
#define DBG_COMM_READINHIBITCOUNTER_ENTRY(p1) \
    EbTest_ComM_ReadInhibitCounter_Entry( EBTEST_FCT_ENTRY(&ComM_ReadInhibitCounter) )
#else
#error DBG_COMM_READINHIBITCOUNTER_ENTRY already defined!
#endif

#ifndef DBG_COMM_READINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ReadInhibitCounter() */
#define DBG_COMM_READINHIBITCOUNTER_EXIT(retval, p1) \
  EbTest_ComM_ReadInhibitCounter_Exit( EBTEST_FCT_EXIT(&ComM_ReadInhibitCounter) )
#else
#error DBG_COMM_READINHIBITCOUNTER_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER == STD_ON) */

/* --- Function: ComM_ResetInhibitCounter--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER == STD_ON)
#ifndef DBG_COMM_RESETINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ResetInhibitCounter() */
#define DBG_COMM_RESETINHIBITCOUNTER_ENTRY() \
    EbTest_ComM_ResetInhibitCounter_Entry( EBTEST_FCT_ENTRY(&ComM_ResetInhibitCounter) )
#else
#error DBG_COMM_RESETINHIBITCOUNTER_ENTRY already defined!
#endif

#ifndef DBG_COMM_RESETINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ResetInhibitCounter() */
#define DBG_COMM_RESETINHIBITCOUNTER_EXIT(retval) \
  EbTest_ComM_ResetInhibitCounter_Exit( EBTEST_FCT_EXIT(&ComM_ResetInhibitCounter) )
#else
#error DBG_COMM_RESETINHIBITCOUNTER_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER == STD_ON) */

/* --- Function: ComM_SetECUGroupClassification--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION == STD_ON)
#ifndef DBG_COMM_SETECUGROUPCLASSIFICATION_ENTRY
/** \brief Entry point of function ComM_SetECUGroupClassification() */
#define DBG_COMM_SETECUGROUPCLASSIFICATION_ENTRY(p1) \
    EbTest_ComM_SetECUGroupClassification_Entry( EBTEST_FCT_ENTRY(&ComM_SetECUGroupClassification) )
#else
#error DBG_COMM_SETECUGROUPCLASSIFICATION_ENTRY already defined!
#endif

#ifndef DBG_COMM_SETECUGROUPCLASSIFICATION_EXIT
/** \brief Exit point of function ComM_SetECUGroupClassification() */
#define DBG_COMM_SETECUGROUPCLASSIFICATION_EXIT(retval, p1) \
  EbTest_ComM_SetECUGroupClassification_Exit( EBTEST_FCT_EXIT(&ComM_SetECUGroupClassification) )
#else
#error DBG_COMM_SETECUGROUPCLASSIFICATION_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION == STD_ON) */

/* --- Function: ComM_GetVersionInfo--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO == STD_ON)
#ifndef DBG_COMM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function ComM_GetVersionInfo() */
#define DBG_COMM_GETVERSIONINFO_ENTRY(p1) \
    EbTest_ComM_GetVersionInfo_Entry( EBTEST_FCT_ENTRY(&ComM_GetVersionInfo) )
#else
#error DBG_COMM_GETVERSIONINFO_ENTRY already defined!
#endif

#ifndef DBG_COMM_GETVERSIONINFO_EXIT
/** \brief Exit point of function ComM_GetVersionInfo() */
#define DBG_COMM_GETVERSIONINFO_EXIT(p1) \
  EbTest_ComM_GetVersionInfo_Exit( EBTEST_FCT_EXIT(&ComM_GetVersionInfo) )
#else
#error DBG_COMM_GETVERSIONINFO_EXIT already defined!
#endif
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO == STD_ON) */

#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON) */

/*==[Declaration of functions with external linkage]==========================*/

#define EBTEST_START_SEC_CODE
#include <Testing_MemMap.h>

#if (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON)

/* --- Function: ComM_Init--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT == STD_ON)
/** \brief Trace check function for ComM_Init() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_Init_Entry(
  void(*FctPtr)
    (const ComM_ConfigType* p1)
);

/** \brief Trace check function for ComM_Init() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_Init_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_Init_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT == STD_ON) */

/* --- Function: ComM_IsValidConfig--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG == STD_ON)
/** \brief Trace check function for ComM_IsValidConfig() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_IsValidConfig_Entry(
  Std_ReturnType(*FctPtr)
    (const void* p1)
);

/** \brief Trace check function for ComM_IsValidConfig() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_IsValidConfig_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_IsValidConfig_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG == STD_ON) */

/* --- Function: ComM_DeInit--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT == STD_ON)
/** \brief Trace check function for ComM_DeInit() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_DeInit_Entry(
  void(*FctPtr)
    (void)
);

/** \brief Trace check function for ComM_DeInit() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_DeInit_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_DeInit_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT == STD_ON) */

/* --- Function: ComM_GetState--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE == STD_ON)
/** \brief Trace check function for ComM_GetState() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetState_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, ComM_StateType* p2)
);

/** \brief Trace check function for ComM_GetState() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetState_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetState_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE == STD_ON) */

/* --- Function: ComM_GetStatus--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS == STD_ON)
/** \brief Trace check function for ComM_GetStatus() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetStatus_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_InitStatusType* p1)
);

/** \brief Trace check function for ComM_GetStatus() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetStatus_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetStatus_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS == STD_ON) */

/* --- Function: ComM_GetInhibitionStatus--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS == STD_ON)
/** \brief Trace check function for ComM_GetInhibitionStatus() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetInhibitionStatus_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, ComM_InhibitionStatusType* p2)
);

/** \brief Trace check function for ComM_GetInhibitionStatus() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetInhibitionStatus_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetInhibitionStatus_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS == STD_ON) */

/* --- Function: ComM_RequestComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE == STD_ON)
/** \brief Trace check function for ComM_RequestComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_RequestComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType p2)
);

/** \brief Trace check function for ComM_RequestComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_RequestComMode_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_RequestComMode_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE == STD_ON) */

/* --- Function: ComM_GetMaxComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE == STD_ON)
/** \brief Trace check function for ComM_GetMaxComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetMaxComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType* p2)
);

/** \brief Trace check function for ComM_GetMaxComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetMaxComMode_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetMaxComMode_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE == STD_ON) */

/* --- Function: ComM_GetRequestedComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE == STD_ON)
/** \brief Trace check function for ComM_GetRequestedComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetRequestedComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType* p2)
);

/** \brief Trace check function for ComM_GetRequestedComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetRequestedComMode_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetRequestedComMode_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE == STD_ON) */

/* --- Function: ComM_GetCurrentComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE == STD_ON)
/** \brief Trace check function for ComM_GetCurrentComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetCurrentComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType* p2)
);

/** \brief Trace check function for ComM_GetCurrentComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetCurrentComMode_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetCurrentComMode_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE == STD_ON) */

/* --- Function: ComM_PreventWakeUp--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP == STD_ON)
/** \brief Trace check function for ComM_PreventWakeUp() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_PreventWakeUp_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, boolean p2)
);

/** \brief Trace check function for ComM_PreventWakeUp() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_PreventWakeUp_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_PreventWakeUp_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP == STD_ON) */

/* --- Function: ComM_LimitChannelToNoComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE == STD_ON)
/** \brief Trace check function for ComM_LimitChannelToNoComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_LimitChannelToNoComMode_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, boolean p2)
);

/** \brief Trace check function for ComM_LimitChannelToNoComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_LimitChannelToNoComMode_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_LimitChannelToNoComMode_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE == STD_ON) */

/* --- Function: ComM_LimitECUToNoComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE == STD_ON)
/** \brief Trace check function for ComM_LimitECUToNoComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_LimitECUToNoComMode_Entry(
  Std_ReturnType(*FctPtr)
    (boolean p1)
);

/** \brief Trace check function for ComM_LimitECUToNoComMode() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_LimitECUToNoComMode_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_LimitECUToNoComMode_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE == STD_ON) */

/* --- Function: ComM_ReadInhibitCounter--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER == STD_ON)
/** \brief Trace check function for ComM_ReadInhibitCounter() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_ReadInhibitCounter_Entry(
  Std_ReturnType(*FctPtr)
    (uint16* p1)
);

/** \brief Trace check function for ComM_ReadInhibitCounter() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_ReadInhibitCounter_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_ReadInhibitCounter_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER == STD_ON) */

/* --- Function: ComM_ResetInhibitCounter--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER == STD_ON)
/** \brief Trace check function for ComM_ResetInhibitCounter() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_ResetInhibitCounter_Entry(
  Std_ReturnType(*FctPtr)
    (void)
);

/** \brief Trace check function for ComM_ResetInhibitCounter() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_ResetInhibitCounter_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_ResetInhibitCounter_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER == STD_ON) */

/* --- Function: ComM_SetECUGroupClassification--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION == STD_ON)
/** \brief Trace check function for ComM_SetECUGroupClassification() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_SetECUGroupClassification_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_InhibitionStatusType p1)
);

/** \brief Trace check function for ComM_SetECUGroupClassification() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_SetECUGroupClassification_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_SetECUGroupClassification_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION == STD_ON) */

/* --- Function: ComM_GetVersionInfo--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO == STD_ON)
/** \brief Trace check function for ComM_GetVersionInfo() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetVersionInfo_Entry(
  void(*FctPtr)
    (Std_VersionInfoType* p1)
);

/** \brief Trace check function for ComM_GetVersionInfo() */
extern FUNC(void, EBTEST_CODE) EbTest_ComM_GetVersionInfo_Exit(
  void(*FctPtr)(void)
);

/** \brief Dummy function to have an Exit trace point */
extern FUNC(void, EBTEST_CODE) ComM_GetVersionInfo_Exit(void);
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO == STD_ON) */

#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON) */

#define EBTEST_STOP_SEC_CODE
#include <Testing_MemMap.h>

#endif /* COMM_TRACE_H */
