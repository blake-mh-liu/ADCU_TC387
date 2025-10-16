/**
 * \file
 *
 * \brief AUTOSAR WdgM
 *
 * This file contains the implementation of the AUTOSAR
 * module WdgM.
 *
 * \version 6.2.7
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef WDGM_INT_H
#define WDGM_INT_H

/*==================[inclusions]=================================================================*/
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure08,1 */
#include <WdgM_Types.h>                                             /* WdgM's types */
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure02,1 */
#include <WdgM_Version.h>
#if (WDGM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                                               /* Det error reporting interface */
#endif
#if (WDGM_DEM_ALIVE_SUPERVISION_REPORT == STD_ON)                        \
    || (WDGM_EB_PROD_ERR_HANDLING_SUPERVISION == WDGM_PROD_ERR_REP_TO_DEM) \
    || (WDGM_EB_PROD_ERR_HANDLING_SET_MODE == WDGM_PROD_ERR_REP_TO_DEM)    \
    || (WDGM_EB_PROD_ERR_HANDLING_IMPROPER_CALLER == WDGM_PROD_ERR_REP_TO_DEM) \
    || (WDGM_EB_PROD_ERR_HANDLING_MF_TIMINGVIOLATION == WDGM_PROD_ERR_REP_TO_DEM) \
    || (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM) \
/* !LINKSTO WdgM.ASR40.SWS_WdgM_00126,1 */
#include <Dem.h>                                                       /* Dem_ReportErrorStatus */
#endif
/*==================[macros]=====================================================================*/

/** \brief simplified error reporting */
#if (defined WDGM_EB_DET_REPORT_ERROR)
#error WDGM_EB_DET_REPORT_ERROR already defined
#endif
#if (WDGM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO WdgM.ASR40.SWS_WdgM_00048,1 */
#define WDGM_EB_DET_REPORT_ERROR(sid, error)          \
  (void)Det_ReportError(                              \
      ((uint16) WDGM_MODULE_ID),                      \
      ((uint8)  WDGM_EB_GET_CORE_ID()),               \
      ((uint8) (sid)),                                \
      ((uint8) (error))                               \
      )
#else
/* empty define only needed for the case (WDGM_DEV_ERROR_DETECT == STD_OFF) &&
 * ((WDGM_EB_PROD_ERR_HANDLING_SUPERVISION == WDGM_PROD_ERR_REP_TO_DET) ||
 * ((WDGM_EB_PROD_ERR_HANDLING_SET_MODE == WDGM_PROD_ERR_REP_TO_DET) ||
 * ((WDGM_EB_PROD_ERR_HANDLING_IMPROPER_CALLER == WDGM_PROD_ERR_REP_TO_DET))
 */
#define WDGM_EB_DET_REPORT_ERROR(sid, error)
#endif

#if (defined WDGM_EB_DET)
#error WDGM_EB_DET already defined
#endif
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020302,1 */
#if (WDGM_EB_EXT_DET_ENABLED == STD_ON)
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020440,1,WDGM.EB.TIMEPM.WDGM020443,1,WDGM.EB.TIMEPM.WDGM020446,1 */
#define WDGM_EB_DET(SID, ErrorID) WDGM_EB_EXT_DET((SID), (ErrorID))
#else
#define WDGM_EB_DET(SID, ErrorID) WDGM_EB_DET_REPORT_ERROR((SID), (ErrorID))
#endif

#if (defined WDGM_EB_DEM)
#error WDGM_EB_DEM already defined
#endif
#define WDGM_EB_DEM(EventID, EventStatus) Dem_ReportErrorStatus((EventID), (EventStatus))





/*------------------------[Defensive programming]----------------------------*/

#if (defined WDGM_PRECONDITION_ASSERT)
#error WDGM_PRECONDITION_ASSERT is already defined
#endif

#if (defined WDGM_PRECONDITION_ASSERT_NO_EVAL)
#error WDGM_PRECONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (WDGM_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define WDGM_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define WDGM_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_PRECONDITION_ASSERT_NO_EVAL((Condition), WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))
#else
#define WDGM_PRECONDITION_ASSERT(Condition, ApiId)
#define WDGM_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined WDGM_POSTCONDITION_ASSERT)
#error WDGM_POSTCONDITION_ASSERT is already defined
#endif

#if (defined WDGM_POSTCONDITION_ASSERT_NO_EVAL)
#error WDGM_POSTCONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (WDGM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define WDGM_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define WDGM_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT_NO_EVAL((Condition), WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))
#else
#define WDGM_POSTCONDITION_ASSERT(Condition, ApiId)
#define WDGM_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined WDGM_INVARIANT_ASSERT)
#error WDGM_INVARIANT_ASSERT is already defined
#endif

#if (defined WDGM_INVARIANT_ASSERT_NO_EVAL)
#error WDGM_INVARIANT_ASSERT_NO_EVAL is already defined
#endif

#if (WDGM_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define WDGM_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define WDGM_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_INVARIANT_ASSERT_NO_EVAL((Condition), WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))
#else
#define WDGM_INVARIANT_ASSERT(Condition, ApiId)
#define WDGM_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined WDGM_STATIC_ASSERT)
# error WDGM_STATIC_ASSERT is already defined
#endif
#if (WDGM_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define WDGM_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define WDGM_STATIC_ASSERT(expr)
#endif

#if (defined WDGM_UNREACHABLE_CODE_ASSERT)
#error WDGM_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (WDGM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **

 ** \param[in] ApiId Service ID of the API function */
#define WDGM_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(WDGM_MODULE_ID, WDGM_INSTANCE_ID, (ApiId))
#else
#define WDGM_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined WDGM_INTERNAL_API_ID)
#error WDGM_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define WDGM_INTERNAL_API_ID DET_INTERNAL_API_ID



#if (defined WDGM_EB_PARAM_UNUSED)
#error WDGM_EB_PARAM_UNUSED already defined
#endif
#if (defined EB_STATIC_CHECK)
/** \brief This macro can be used to avoid compiler warnings
 * It is left empty for static code analyze only with EB specific
 * tooling in order not to produce a false positive for MISRA 14.2 */
#define WDGM_EB_PARAM_UNUSED(x)
#else
/** \brief This macro can be used to avoid compiler warnings */
#define WDGM_EB_PARAM_UNUSED(x) ((void) (x))
#endif

#if (defined WDGM_EB_RESULT_CORRECT)
#error WDGM_EB_RESULT_CORRECT is already defined
#endif

/** \brief value for a correct result */
#define WDGM_EB_RESULT_CORRECT 0xB4U

#if (defined WDGM_EB_RESULT_INCORRECT)
#error WDGM_EB_RESULT_INCORRECT is already defined
#endif

/** \brief value for an incorrect result (quite different from correct, but not bit-inverse) */
#define WDGM_EB_RESULT_INCORRECT 0xCBU

#if (defined WDGM_EB_RESULT_NOTEVALUATED)
#error WDGM_EB_RESULT_NOTEVALUATED is already defined
#endif

/** \brief value for a not evaluated result */
#define WDGM_EB_RESULT_NOTEVALUATED 0xA3U

#if (defined WDGM_EB_MAX_ALIVE_COUNTER_VALUE)
#error WDGM_EB_MAX_ALIVE_COUNTER_VALUE is already defined
#endif

#if (defined WDGM_EB_E_SAME_MODE)
#error WDGM_EB_E_SAME_MODE is already defined
#endif

/** \brief WdgM_SetMode function is called consecutive with the same mode */
#define WDGM_EB_E_SAME_MODE 0xA4U

/** \brief maximum value for an alive counter */
#define WDGM_EB_MAX_ALIVE_COUNTER_VALUE 0xFFFFUL

/*------------------[WdgM Partition Restart macros]------------------------------------*/

#if (defined WDGM_EB_PARTITION_ACTIVE)
#error WDGM_EB_PARTITION_ACTIVE is already defined
#endif
/** \brief Active status of a WdgM partition. */
#define WDGM_EB_PARTITION_ACTIVE            0x01U

#if (defined WDGM_EB_PARTITION_RESTARTING)
#error WDGM_EB_PARTITION_RESTARTING is already defined
#endif
/** \brief Restarting status of a WdgM partition. */
#define WDGM_EB_PARTITION_RESTARTING        0x02U

#if (defined WDGM_EB_PARTITION_POST_RESTARTED)
#error WDGM_EB_PARTITION_POST_RESTARTED is already defined
#endif
/** \brief Post Restarted status of a WdgM partition. */
#define WDGM_EB_PARTITION_POST_RESTARTED    0x03U

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

#define WDGM_START_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>

#if (WDGM_EB_INCLUDE_RTE == STD_ON)

#if (WDGM_EB_DEFAULT_ASR_SERVICE_API != WDGM_EB_SERVICE_API_NONE)
/** \brief Signal individual SE mode change via RTE
 *
 * The function receives SE Id and status from the WdgM point of view and has to
 * translate them into the values expected by the RTE. The reported values depend
 * on the AUTOSAR service API selected as default.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] SEID  supervised entity whose status has changed
 * \param[in] LocalStatus  new alive supervision status
 * \param[in] CoreID  id of the core from which the function is called
 */
FUNC(void, WDGM_CODE) WdgM_RteIndividualModeSwitch (
  WdgM_SupervisedEntityIdType       SEID,
  WdgM_LocalStatusType              LocalStatus,
  WdgM_EB_CoreIdType                CoreID
);

/** \brief Signal global mode change via RTE
 *
 * The function receives the status from the WdgM point of view and  has to
 * translate them into the values expected by the RTE. The reported values depend
 * on the AUTOSAR service API selected as default.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] GlobalStatus  new global alive supervision status */
FUNC(void, WDGM_CODE) WdgM_RteGlobalModeSwitch (
  WdgM_GlobalStatusType GlobalStatus
);
#endif /* (WDGM_EB_DEFAULT_ASR_SERVICE_API != WDGM_EB_SERVICE_API_NONE) */

#if (WDGM_EB_ENABLE_ASR32_SERVICE_API == STD_ON)
/** \brief Signal individual SE mode change via RTE
 *
 * The function receives SE Id and status from the WdgM point of view and has to
 * translate them into the AUTOSAR 3.2 values expected by the RTE.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] SEID  supervised entity whose status has changed
 * \param[in] LocalStatus  new alive supervision status
 * \param[in] CoreID  id of the core from which the function is called
 *
 * \note This function is called from WdgM_MainFunction and thus uses the
 * AUTOSAR 4.0 argument types. The mapping to the corresponding
 * AUTOSAR 3.2 types is done in the function definition. */
FUNC(void, WDGM_CODE) WdgM_ASR32_RteIndividualModeSwitch (
  WdgM_SupervisedEntityIdType       SEID,
  WdgM_LocalStatusType              LocalStatus,
  WdgM_EB_CoreIdType                CoreID
);

/** \brief Signal global mode change via RTE
 *
 * The function receives the status from the WdgM point of view and  has to
 * translate them into the AUTOSAR 3.2 values expected by the RTE.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] GlobalStatus  new global alive supervision status */
FUNC(void, WDGM_CODE) WdgM_ASR32_RteGlobalModeSwitch (
  WdgM_GlobalStatusType GlobalStatus
);
#endif /* (WDGM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) */

#if (WDGM_EB_ENABLE_ASR40_SERVICE_API == STD_ON)
/** \brief Signal individual SE mode change via RTE
 *
 * The function receives SE Id and status from the WdgM point of view and has to
 * translate them into the AUTOSAR 4.0 values expected by the RTE.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] SEID  supervised entity whose status has changed
 * \param[in] LocalStatus  new alive supervision status
 * \param[in] CoreID  id of the core from which the function is called
 */
FUNC(void, WDGM_CODE) WdgM_ASR40_RteIndividualModeSwitch (
  WdgM_SupervisedEntityIdType       SEID,
  WdgM_LocalStatusType              LocalStatus,
  WdgM_EB_CoreIdType                CoreID
);

/** \brief Signal global mode change via RTE
 *
 * The function receives the status from the WdgM point of view and  has to
 * translate them into the AUTOSAR 4.0 values expected by the RTE.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] GlobalStatus  new global alive supervision status */
FUNC(void, WDGM_CODE) WdgM_ASR40_RteGlobalModeSwitch (
  WdgM_GlobalStatusType GlobalStatus
);
#endif /* (WDGM_EB_ENABLE_ASR40_SERVICE_API == STD_ON) */

#if (WDGM_EB_ENABLE_ASR43_SERVICE_API == STD_ON)
/** \brief Signal individual SE mode change via RTE
 *
 * The function receives SE Id and status from the WdgM point of view and has to
 * translate them into the AUTOSAR 4.3 values expected by the RTE.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] SEID  supervised entity whose status has changed
 * \param[in] LocalStatus  new alive supervision status
 * \param[in] CoreID  id of the core from which the function is called
 */
FUNC(void, WDGM_CODE) WdgM_ASR43_RteIndividualModeSwitch (
  WdgM_SupervisedEntityIdType       SEID,
  WdgM_LocalStatusType              LocalStatus,
  WdgM_EB_CoreIdType                CoreID
);

/** \brief Signal global mode change via RTE
 *
 * The function receives the status from the WdgM point of view and  has to
 * translate them into the AUTOSAR 4.3 values expected by the RTE.
 *
 * The return value of the RTE call is ignored on purpose because the WdgM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] GlobalStatus  new global alive supervision status */
FUNC(void, WDGM_CODE) WdgM_ASR43_RteGlobalModeSwitch (
  WdgM_GlobalStatusType GlobalStatus
);
#endif /* (WDGM_EB_ENABLE_ASR43_SERVICE_API == STD_ON) */
#endif /* (WDGM_EB_INCLUDE_RTE == STD_ON) */

#define WDGM_STOP_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

#endif /* ifndef WDGM_INT_H */
/*==================[end of file]================================================================*/
