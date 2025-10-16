/**EB_Automotive_C_Source_File */

#ifndef COMM_DCM_H
#define COMM_DCM_H

/*==[Includes]================================================================*/

#include <ComM_StubCfg.h>
#include <ComStack_Types.h>

/*==[Macros]==================================================================*/

/* Configuration macros */
#ifndef EBSTUBS_MAX_CALLS_COMM
#define EBSTUBS_MAX_CALLS_COMM 1U
#endif /* EBSTUBS_MAX_CALLS_COMM */

#ifndef EBSTUBS_MAX_CALLS_COMM_DCM_ACTIVEDIAGNOSTIC
#define EBSTUBS_MAX_CALLS_COMM_DCM_ACTIVEDIAGNOSTIC EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_DCM_ACTIVEDIAGNOSTIC */

#ifndef EBSTUBS_MAX_CALLS_COMM_DCM_INACTIVEDIAGNOSTIC
#define EBSTUBS_MAX_CALLS_COMM_DCM_INACTIVEDIAGNOSTIC EBSTUBS_MAX_CALLS_COMM
#endif /* EBSTUBS_MAX_CALLS_COMM_DCM_INACTIVEDIAGNOSTIC */

#ifndef EBSTUBS_FUNCENABLED_COMM
#define EBSTUBS_FUNCENABLED_COMM STD_ON
#endif /* EBSTUBS_FUNCENABLED_COMM */

#ifndef EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC
#define EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC */

#ifndef EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC
#define EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC EBSTUBS_FUNCENABLED_COMM
#endif /* EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC */

/*==[Types]===================================================================*/

#if (EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC == STD_ON)
typedef void(*ComM_DCM_ActiveDiagnostic_CalloutType)
(
   NetworkHandleType
);
typedef struct
{
   uint32 Count;
   ComM_DCM_ActiveDiagnostic_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_DCM_ACTIVEDIAGNOSTIC > 1)
    NetworkHandleType Channel_Ary[EBSTUBS_MAX_CALLS_COMM_DCM_ACTIVEDIAGNOSTIC];
#endif /* (EBSTUBS_MAX_CALLS_COMM_DCM_ACTIVEDIAGNOSTIC > 1) */

    NetworkHandleType Channel;
} ComM_DCM_ActiveDiagnostic_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC == STD_ON)
typedef void(*ComM_DCM_InactiveDiagnostic_CalloutType)
(
   NetworkHandleType
);
typedef struct
{
   uint32 Count;
   ComM_DCM_InactiveDiagnostic_CalloutType Callout;

#if (EBSTUBS_MAX_CALLS_COMM_DCM_INACTIVEDIAGNOSTIC > 1)
    NetworkHandleType Channel_Ary[EBSTUBS_MAX_CALLS_COMM_DCM_INACTIVEDIAGNOSTIC];
#endif /* (EBSTUBS_MAX_CALLS_COMM_DCM_INACTIVEDIAGNOSTIC > 1) */

    NetworkHandleType Channel;
} ComM_DCM_InactiveDiagnostic_StubType;
#endif /* (EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC == STD_ON) */

/*==[Declaration of functions with external linkage]==========================*/

#define EBSTUBS_START_SEC_CODE
#include <EBStubs_MemMap.h>

#if (EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_DCM_ActiveDiagnostic
(
  NetworkHandleType Channel
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC == STD_ON)
extern FUNC(void, EBSTUBS_CODE) ComM_DCM_InactiveDiagnostic
(
  NetworkHandleType Channel
);
#endif /* (EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC == STD_ON) */

#define EBSTUBS_STOP_SEC_CODE
#include <EBStubs_MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#define EBSTUBS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <EBStubs_MemMap.h>

#if (EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC == STD_ON)
extern VAR(ComM_DCM_ActiveDiagnostic_StubType, EBSTUBS_VAR)
   ComM_DCM_ActiveDiagnostic_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_DCM_ACTIVEDIAGNOSTIC == STD_ON) */

#if (EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC == STD_ON)
extern VAR(ComM_DCM_InactiveDiagnostic_StubType, EBSTUBS_VAR)
   ComM_DCM_InactiveDiagnostic_Stub;
#endif /* (EBSTUBS_FUNCENABLED_COMM_DCM_INACTIVEDIAGNOSTIC == STD_ON) */


#define EBSTUBS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <EBStubs_MemMap.h>

/* stub extension header file */
#include <ComM_StubExt.h>

#endif /* COMM_DCM_H */
