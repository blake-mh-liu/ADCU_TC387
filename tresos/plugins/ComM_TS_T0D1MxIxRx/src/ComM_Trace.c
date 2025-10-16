/**EB_Automotive_C_Source_File */

/*==[Includes]================================================================*/

#include <ComM_Trace.h>

#if (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON)
#include <Dcm_Test_Trace.h>
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON) */

/*==[Declaration of functions with external linkage]==========================*/

#define EBTEST_START_SEC_CODE
#include <Testing_MemMap.h>

#if (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON)

/* --- Function: ComM_Init--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_Init_Entry(
  void(*FctPtr)
    (const ComM_ConfigType* p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_Init_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_Init_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_INIT == STD_ON) */

/* --- Function: ComM_IsValidConfig--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_IsValidConfig_Entry(
  Std_ReturnType(*FctPtr)
    (const void* p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_IsValidConfig_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_IsValidConfig_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_ISVALIDCONFIG == STD_ON) */

/* --- Function: ComM_DeInit--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_DeInit_Entry(
  void(*FctPtr)
    (void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_DeInit_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_DeInit_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_DEINIT == STD_ON) */

/* --- Function: ComM_GetState--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetState_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, ComM_StateType* p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetState_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetState_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATE == STD_ON) */

/* --- Function: ComM_GetStatus--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetStatus_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_InitStatusType* p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetStatus_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetStatus_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETSTATUS == STD_ON) */

/* --- Function: ComM_GetInhibitionStatus--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetInhibitionStatus_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, ComM_InhibitionStatusType* p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetInhibitionStatus_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetInhibitionStatus_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETINHIBITIONSTATUS == STD_ON) */

/* --- Function: ComM_RequestComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_RequestComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_RequestComMode_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_RequestComMode_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_REQUESTCOMMODE == STD_ON) */

/* --- Function: ComM_GetMaxComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetMaxComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType* p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetMaxComMode_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetMaxComMode_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETMAXCOMMODE == STD_ON) */

/* --- Function: ComM_GetRequestedComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetRequestedComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType* p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetRequestedComMode_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetRequestedComMode_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETREQUESTEDCOMMODE == STD_ON) */

/* --- Function: ComM_GetCurrentComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetCurrentComMode_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_UserHandleType p1, ComM_ModeType* p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetCurrentComMode_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetCurrentComMode_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETCURRENTCOMMODE == STD_ON) */

/* --- Function: ComM_PreventWakeUp--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_PreventWakeUp_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, boolean p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_PreventWakeUp_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_PreventWakeUp_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_PREVENTWAKEUP == STD_ON) */

/* --- Function: ComM_LimitChannelToNoComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_LimitChannelToNoComMode_Entry(
  Std_ReturnType(*FctPtr)
    (NetworkHandleType p1, boolean p2)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_LimitChannelToNoComMode_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_LimitChannelToNoComMode_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITCHANNELTONOCOMMODE == STD_ON) */

/* --- Function: ComM_LimitECUToNoComMode--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_LimitECUToNoComMode_Entry(
  Std_ReturnType(*FctPtr)
    (boolean p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_LimitECUToNoComMode_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_LimitECUToNoComMode_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_LIMITECUTONOCOMMODE == STD_ON) */

/* --- Function: ComM_ReadInhibitCounter--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_ReadInhibitCounter_Entry(
  Std_ReturnType(*FctPtr)
    (uint16* p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_ReadInhibitCounter_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_ReadInhibitCounter_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_READINHIBITCOUNTER == STD_ON) */

/* --- Function: ComM_ResetInhibitCounter--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_ResetInhibitCounter_Entry(
  Std_ReturnType(*FctPtr)
    (void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_ResetInhibitCounter_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_ResetInhibitCounter_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_RESETINHIBITCOUNTER == STD_ON) */

/* --- Function: ComM_SetECUGroupClassification--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_SetECUGroupClassification_Entry(
  Std_ReturnType(*FctPtr)
    (ComM_InhibitionStatusType p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_SetECUGroupClassification_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_SetECUGroupClassification_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_SETECUGROUPCLASSIFICATION == STD_ON) */

/* --- Function: ComM_GetVersionInfo--- */
#if (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO == STD_ON)
FUNC(void, EBTEST_CODE) EbTest_ComM_GetVersionInfo_Entry(
  void(*FctPtr)
    (Std_VersionInfoType* p1)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) EbTest_ComM_GetVersionInfo_Exit(
  void(*FctPtr)(void)
)
{
  if (EbTest_InternalApiTracing != FALSE)
  {
    EBSTUBS_TRACE_PUSH(FctPtr);
  }
}

FUNC(void, EBTEST_CODE) ComM_GetVersionInfo_Exit(void) { }
#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE_COMM_GETVERSIONINFO == STD_ON) */

#endif /* (EBSTUBS_UNIT_FUNCTION_TRACE == STD_ON) */
#define EBTEST_STOP_SEC_CODE
#include <Testing_MemMap.h>

