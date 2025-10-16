/**EB_Automotive_C_Source_File */

#ifndef COMM_ECUMBSWM_H
#define COMM_ECUMBSWM_H

/*==[Includes]================================================================*/

#include <ComM_StubCfg.h>
#include <ComStack_Types.h>

/*==[Macros]==================================================================*/

/* Configuration macros */
#ifndef EBSTUBS_MAX_CALLS_COMM
#define EBSTUBS_MAX_CALLS_COMM 1U
#endif /* EBSTUBS_MAX_CALLS_COMM */

#ifndef EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED
#define EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED */

#ifndef EBSTUBS_MAX_CALLS_COMM_ECUM_PNCWAKEUPINDICATION
#define EBSTUBS_MAX_CALLS_COMM_ECUM_PNCWAKEUPINDICATION EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_ECUM_PNCWAKEUPINDICATION */

#ifndef EBSTUBS_MAX_CALLS_COMM_ECUM_WAKEUPINDICATION
#define EBSTUBS_MAX_CALLS_COMM_ECUM_WAKEUPINDICATION EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_ECUM_WAKEUPINDICATION */

#ifndef EBSTUBS_FUNCENABLED_COMM
#define EBSTUBS_FUNCENABLED_COMM STD_ON
#endif /* EBSTUBS_FUNCENABLED_COMM */

#ifndef EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION
#define EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION */

#ifndef EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION
#define EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION */

#ifndef EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED
#define EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED */

/*==[Types]===================================================================*/

#if (EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION == STD_ON)
typedef void(*ComM_EcuM_WakeUpIndication_CalloutType)
(
   NetworkHandleType
);
typedef struct
{
   uint32 Count;
   ComM_EcuM_WakeUpIndication_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_ECUM_WAKEUPINDICATION > 1)
    NetworkHandleType Channel_Ary[EBSTUBS_MAX_CALLS_COMM_ECUM_WAKEUPINDICATION];
#endif /* (EBSTUBS_MAX_CALLS_COMM_ECUM_WAKEUPINDICATION > 1) */

    NetworkHandleType Channel;
} ComM_EcuM_WakeUpIndication_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION == STD_ON)
typedef void(*ComM_EcuM_PNCWakeUpIndication_CalloutType)
(
   PNCHandleType
);
typedef struct
{
   uint32 Count;
   ComM_EcuM_PNCWakeUpIndication_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_ECUM_PNCWAKEUPINDICATION > 1)
    PNCHandleType PNCid_Ary[EBSTUBS_MAX_CALLS_COMM_ECUM_PNCWAKEUPINDICATION];
#endif /* (EBSTUBS_MAX_CALLS_COMM_ECUM_PNCWAKEUPINDICATION > 1) */

    PNCHandleType PNCid;
} ComM_EcuM_PNCWakeUpIndication_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED == STD_ON)
typedef void(*ComM_CommunicationAllowed_CalloutType)
(
   NetworkHandleType,
   boolean
);
typedef struct
{
   uint32 Count;
   ComM_CommunicationAllowed_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED > 1)
    NetworkHandleType Channel_Ary[EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED];
    boolean Allowed_Ary[EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED];
#endif /* (EBSTUBS_MAX_CALLS_COMM_COMMUNICATIONALLOWED > 1) */

    NetworkHandleType Channel;
    boolean Allowed;
} ComM_CommunicationAllowed_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED == STD_ON) */

/*==[Declaration of functions with external linkage]==========================*/

#define EBSTUBS_START_SEC_CODE
#include <EBStubs_MemMap.h>

#if (EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_EcuM_WakeUpIndication
(
  NetworkHandleType Channel
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_EcuM_PNCWakeUpIndication
(
  PNCHandleType PNCid
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_CommunicationAllowed
(
  NetworkHandleType Channel,
  boolean Allowed
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED == STD_ON) */

#define EBSTUBS_STOP_SEC_CODE
#include <EBStubs_MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#define EBSTUBS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <EBStubs_MemMap.h>

#if (EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED == STD_ON)
extern VAR(ComM_CommunicationAllowed_StubType, EBSTUBS_VAR)
   ComM_CommunicationAllowed_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_COMMUNICATIONALLOWED == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION == STD_ON)
extern VAR(ComM_EcuM_PNCWakeUpIndication_StubType, EBSTUBS_VAR)
   ComM_EcuM_PNCWakeUpIndication_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_ECUM_PNCWAKEUPINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION == STD_ON)
extern VAR(ComM_EcuM_WakeUpIndication_StubType, EBSTUBS_VAR)
   ComM_EcuM_WakeUpIndication_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_ECUM_WAKEUPINDICATION == STD_ON) */


#define EBSTUBS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <EBStubs_MemMap.h>

/* stub extension header file */
#include <ComM_StubExt.h>

#endif /* COMM_ECUMBSWM_H */
