/**EB_Automotive_C_Source_File */

#ifndef COMM_BUSSM_H
#define COMM_BUSSM_H

/*==[Includes]================================================================*/

#include <ComM_StubCfg.h>
#include <ComStack_Types.h>
#include <ComM.h>

/*==[Macros]==================================================================*/

/* Configuration macros */
#ifndef EBSTUBS_MAX_CALLS_COMM
#define EBSTUBS_MAX_CALLS_COMM 1U
#endif /* EBSTUBS_MAX_CALLS_COMM */

#ifndef EBSTUBS_MAX_CALLS_COMM_BUSSM_BUSSLEEPMODE
#define EBSTUBS_MAX_CALLS_COMM_BUSSM_BUSSLEEPMODE EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_BUSSM_BUSSLEEPMODE */

#ifndef EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION
#define EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION */

#ifndef EBSTUBS_FUNCENABLED_COMM
#define EBSTUBS_FUNCENABLED_COMM STD_ON
#endif /* EBSTUBS_FUNCENABLED_COMM */

#ifndef EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION
#define EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION */

#ifndef EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE
#define EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE */

/*==[Types]===================================================================*/

#if (EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION == STD_ON)
typedef void(*ComM_BusSM_ModeIndication_CalloutType)
(
   NetworkHandleType,
   P2VAR(ComM_ModeType, TYPEDEF, EBSTUBS_APPL_DATA)
);
typedef struct
{
   uint32 Count;
   ComM_BusSM_ModeIndication_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION > 1)
    NetworkHandleType Channel_Ary[EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION];
    P2VAR(ComM_ModeType, TYPEDEF, EBSTUBS_APPL_DATA) ComMode_Ary[EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION];
#endif /* (EBSTUBS_MAX_CALLS_COMM_BUSSM_MODEINDICATION > 1) */

    NetworkHandleType Channel;
    P2VAR(ComM_ModeType, TYPEDEF, EBSTUBS_APPL_DATA) ComMode;
} ComM_BusSM_ModeIndication_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE == STD_ON)
typedef void(*ComM_BusSM_BusSleepMode_CalloutType)
(
   NetworkHandleType
);
typedef struct
{
   uint32 Count;
   ComM_BusSM_BusSleepMode_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_BUSSM_BUSSLEEPMODE > 1)
    NetworkHandleType Channel_Ary[EBSTUBS_MAX_CALLS_COMM_BUSSM_BUSSLEEPMODE];
#endif /* (EBSTUBS_MAX_CALLS_COMM_BUSSM_BUSSLEEPMODE > 1) */

    NetworkHandleType Channel;
} ComM_BusSM_BusSleepMode_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE == STD_ON) */

/*==[Declaration of functions with external linkage]==========================*/

#define EBSTUBS_START_SEC_CODE
#include <EBStubs_MemMap.h>

#if (EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_BusSM_ModeIndication
(
  NetworkHandleType Channel,
  P2VAR(ComM_ModeType, AUTOMATIC, EBSTUBS_APPL_DATA) ComMode
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_BusSM_BusSleepMode
(
  NetworkHandleType Channel
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE == STD_ON) */

#define EBSTUBS_STOP_SEC_CODE
#include <EBStubs_MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#define EBSTUBS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <EBStubs_MemMap.h>

#if (EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE == STD_ON)
extern VAR(ComM_BusSM_BusSleepMode_StubType, EBSTUBS_VAR)
   ComM_BusSM_BusSleepMode_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_BUSSM_BUSSLEEPMODE == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION == STD_ON)
extern VAR(ComM_BusSM_ModeIndication_StubType, EBSTUBS_VAR)
   ComM_BusSM_ModeIndication_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_BUSSM_MODEINDICATION == STD_ON) */


#define EBSTUBS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <EBStubs_MemMap.h>

/* stub extension header file */
#include <ComM_StubExt.h>

#endif /* COMM_BUSSM_H */
