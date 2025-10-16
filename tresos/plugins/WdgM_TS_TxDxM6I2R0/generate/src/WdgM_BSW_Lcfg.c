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

/*
 * MISRA-C:2012 Deviations:
 *
 * MISRAC2012-1) Deviated Rule: 20.7
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The AUTOSAR compiler abstraction requires these definitions in this way
 * and the arguments cannot be enclosed in parentheses due to C syntax.

 * MISRAC2012-2) Deviated Rule: 8.9 (advisory)
 * An object should be defined at block scope if its identifier only appears
 * in a single function.
 *
 * Reason:
 * The object is defined in this way because the values that are stored
 * in them are required for the next call of this function and should be
 * hold in the data segment memory.
 *
 * MISRAC2012-3) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be 
 * unique.
 *
 * Reason:
 * There can be no confusion because one is a variable with external linkage and 
 * the other one is element of a structure.
 */
[!INCLUDE "../include/WdgM_Cfg.m"!][!//
[!INCLUDE "../include/WdgM_Macros.m"!][!//
[!INCLUDE "../include/WdgM_Checks.m"!][!//
[!CODE!][!//

/*==================[inclusions]=================================================================*/
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure03,1 */
#include <WdgM_Trace_Stc.h>
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure05,1 */
#include <WdgM_Lcfg.h>                               /* Module internal BSW declarations and API */
[!IF "$WdgMMulticoreEnabled = 'true'"!]
    [!IF "$DefaultServiceAPI = 'NONE'"!][!//
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure04,1 */
#include <WdgM.h>                                   /* For WdgM_MainFunction() */
    [!ENDIF!][!//
[!VAR "MULTICORE_NUM_CORES" = "node:value(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores)"!]
[!ELSE!][!//
[!VAR "MULTICORE_NUM_CORES" = "1"!]
[!ENDIF!][!//
[!IF "node:exists(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMMasterCoreId)"!][!//
[!VAR "WDGM_MASTER_CORE_ID" = "node:value(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMMasterCoreId)"!][!//
[!ELSE!][!//
[!VAR "WDGM_MASTER_CORE_ID" = "'0'"!][!//
[!ENDIF!][!//

/*------------------[macros for EB Defensive Programming if not provided by Det]-----------------*/
#if (WDGM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
#ifndef DET_UNREACHABLE_CODE_ASSERT
/** \brief Report a unreachable code assertion (if not already defined by Det)
 **
 ** Use this macro in BSW modules to mark unreachable code as part of
 ** defensive programming.
 **
 ** \param[in] ModuleId The id of the reporting module
 ** \param[in] InstanceId The instance Id of the reporting module
 ** \param[in] ApiId The Api function where the check failed */
#define DET_UNREACHABLE_CODE_ASSERT(ModuleId, InstanceId, ApiId)        \
  do                                                                    \
  {                                                                     \
    WDGM_EB_DET((ApiId), DET_E_UNREACHABLE_CODE_ASSERT_FAILED);         \
  }                                                                     \
  while (0)
#endif
#endif /* (WDGM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */
/*==================[macros]=====================================================================*/

[!AUTOSPACING!][!//
[!//

[!IF "$WdgMMulticoreEnabled"!]
#if (defined WDGM_EB_SATELLITE_ALIVENESS_FAILURE)
#error WDGM_EB_SATELLITE_ALIVENESS_FAILURE already defined
#endif
  [!IF "$SatelliteAlivenessCalloutEnabled"!]
    [!IF "$SatelliteAlivenessCoreIdDisable = 'false'"!]
#define WDGM_EB_SATELLITE_ALIVENESS_FAILURE(CoreId) WDGM_EB_EXT_SATELLITE_ALIVENESS_FAILURE(CoreId)
    [!ELSE!]
#define WDGM_EB_SATELLITE_ALIVENESS_FAILURE() WDGM_EB_EXT_SATELLITE_ALIVENESS_FAILURE()
    [!ENDIF!]
  [!ELSE!]
#define WDGM_EB_SATELLITE_ALIVENESS_FAILURE()
  [!ENDIF!]
[!ENDIF!][!//
/*==================[type definitions]===========================================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal data]==============================================================*/

/*==================[external data]==============================================================*/

/* !LINKSTO WDGM.EB.TIMEPM.WDGM020304,2 */
#if (WDGM_EB_PARTITIONING_ENABLED == STD_ON)
#define WDGM_START_SEC_VAR_CLEARED_SHARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#endif

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable3,1,WDGM.EB.DesignDecision.InternalVariable5,1,
 WDGM.EB.DesignDecision.InternalVariable8,1 */
[!LOOP "WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
/* Checkpoint individual run-time data for each SE */
VAR(WdgM_EB_CPDataType,WDGM_VAR) WdgM_EB_CPData_[!"as:name(.)"!][[!"num:i(count(WdgMCheckpoint/eb-list::*))"!]];
[!ENDLOOP!][!//



#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
#if (WDGM_EB_DM_NUM > 0)
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable4,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable11,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable9,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable24,1 */
VAR(WdgM_EB_DMDataType,WDGM_VAR) WdgM_EB_DMData[WDGM_EB_DM_NUM];
#else
VAR(WdgM_EB_DMDataType,WDGM_VAR) WdgM_EB_DMData[1];
#endif
#endif

#if (WDGM_EB_PARTITIONING_ENABLED == STD_ON)
#define WDGM_STOP_SEC_VAR_CLEARED_SHARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#endif

[!IF "$WdgMPartitionResetEnabled = 'true'"!]
#define WDGM_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
            [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!][!//

/** \brief
 **  Status of WdgM partitions configured by mapped SEs to OS applications of Core [!"num:i($index_i)"!].
 **/
static VAR(uint8, WDGM_VAR) WdgM_EB_Core[!"num:i($index_i)"!]_PartitionStatus[[!"num:i($WdgMNumOfPartitionsPerCore)"!]U] = 
{
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
  WDGM_EB_PARTITION_ACTIVE, /* [!"as:name(as:ref(./WdgMOsApplicationRef))"!] */
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
  WDGM_EB_PARTITION_ACTIVE, /* [!"as:name(as:ref(./WdgMOsApplicationRef))"!] */
          [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
};

[!ENDIF!][!//
[!ENDFOR!][!//
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>

#define WDGM_START_SEC_VAR_INIT_ASIL_D_32
#include <WdgM_MemMap.h>
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
            [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]

[!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!][!//
/** \brief
 **  Holds the supervision cycle counter for alive supervision of
 **  WdgM partitions configured by mapped SEs to OS applications of Core [!"num:i($index_i)"!].
 **/
static VAR(uint32, WDGM_VAR) WdgM_EB_Core[!"num:i($index_i)"!]PartitionSupervisionCycleCnt[[!"num:i($WdgMNumOfPartitionsPerCore)"!]U] = 
{
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
            [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
              [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
  0U, /* [!"as:name(as:ref(./WdgMOsApplicationRef))"!] */
            [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
  0U, /* [!"as:name(as:ref(./WdgMOsApplicationRef))"!] */
          [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
};

[!ENDIF!][!//
[!ENDFOR!][!//
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_32
#include <WdgM_MemMap.h>

[!ENDIF!][!//
/*==================[internal constants]=========================================================*/

#define WDGM_START_SEC_CONST_ASIL_D_16
#include <WdgM_MemMap.h>

[!IF "node:exists(WdgMGeneral/WdgMCallerIds) and (count(WdgMGeneral/WdgMCallerIds/WdgMCallerId/eb-list::*) > 0) and $GetExpectedWdgMModeCalloutEnabled = 'false'"!][!//
/*------------------[Allowed Caller IDs]------------------------------------*/
/* Deviation MISRAC2012-2 */
CONST(uint16, WDGM_CONST) WdgM_EB_CallerIds[WDGM_EB_CALLERIDS_NUM] =
{
  [!LOOP "WdgMGeneral/WdgMCallerIds/WdgMCallerId/eb-list::*"!][!//
  [!"node:value(.)"!]U,
  [!ENDLOOP!][!// WdgMCallerIds /*
};
[!ENDIF!][!//

#define WDGM_STOP_SEC_CONST_ASIL_D_16
#include <WdgM_MemMap.h>

#define WDGM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

/*------------------[trigger and watchdog configuration]--------------------*/

[!LOOP "util:distinct(node:order(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
[!IF "count(WdgMTrigger/eb-list::*) > 0"!][!//
/* trigger configuration for mode [!"as:name(.)"!] */
static CONST(WdgM_EB_TriggerCfgType,WDGM_CONST) WdgM_EB_TrigCfg_M[!"WdgMModeId"!][[!"num:i(count(WdgMTrigger/eb-list::*))"!]] =
{
  [!LOOP "WdgMTrigger/eb-list::*"!][!//
  { /* [!"as:name(.)"!] */
    [!"WdgMWatchdogMode"!], /* watchdog trigger mode */
    [!"WdgMTriggerConditionValue"!]U, /* TriggerCondition */
    [!"as:ref(as:ref(WdgMTriggerWatchdogRef)/WdgMWatchdogDeviceRef)/WdgIfDeviceIndex"!]U, /* watchdog device index */
[!IF "$WdgMTriggerWdgDriverMulticore"!]
[!IF "(node:existsAndTrue(as:ref(WdgMTriggerWatchdogRef)/WdgMMulticoreWdgEnable))"!]
    TRUE, /* triggered from all cores */
[!ELSE!][!//
    FALSE, /* triggered from all cores */
[!ENDIF!][!//
[!IF "node:exists(as:ref(WdgMTriggerWatchdogRef)/WdgMMulticoreWdgCoreId)"!]
  [!VAR "WdgMCoreId" = "num:i(node:value(as:ref(WdgMTriggerWatchdogRef)/WdgMMulticoreWdgCoreId))"!]
  [!VAR "SupEntExistPerCore" = "false()"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = $WdgMCoreId"!]
      [!VAR "SupEntExistPerCore" = "true()"!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "$SupEntExistPerCore"!]
    [!"node:value(as:ref(WdgMTriggerWatchdogRef)/WdgMMulticoreWdgCoreId)"!]U /* triggered from a specific core */
  [!ELSE!][!//
      [!ERROR "The configured Core ID (WdgMMulticoreWdgCoreId) does not belong to any Supervised Entity."!]
  [!ENDIF!][!//
[!ELSE!][!//
    WDGM_EB_MASTER_INSTANCE /* triggered from a specific core - disabled default value */
[!ENDIF!][!//
[!ENDIF!][!//
  },
  [!ENDLOOP!][!// WdgM triggers /*
};
[!ELSE!][!//
/* no triggers configured for mode [!"as:name(.)"!] */
[!ENDIF!][!//

[!ENDLOOP!][!// WdgM modes /*

/*------------------[SE configuration]--------------------------------------*/

[!VAR "BaseIntGraphId" = "0"!][!//
[!VAR "DMId" = "0"!][!//
/* !LINKSTO WdgM.SWS_WdgM_00366,1 */
[!LOOP "WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
/*------------------Internal configuration data for SE: [!"as:name(.)"!] */

[!VAR "SEName" = "as:name(.)"!][!//
[!VAR "ExtSEId" = "num:i(WdgMSupervisedEntityId)"!][!//
[!VAR "IntSEId" = "node:pos(.)"!][!//
[!LOOP "util:distinct(node:order(WdgMCheckpoint/eb-list::*, 'WdgMCheckpointId'))"!][!//
[!VAR "CPName" = "as:name(.)"!][!//
[!VAR "IntCPId" = "WdgMCheckpointId"!][!//
[!VAR "BaseExtGraphId" = "0"!][!//
[!LOOP "util:distinct(node:order(../../../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
[!VAR "IntModeId" = "WdgMModeId"!][!//
[!VAR "tempText"!][!ENDVAR!][!//
[!LOOP "WdgMAliveSupervision/eb-list::*[(num:i(as:ref(WdgMAliveSupervisionCheckpointRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMAliveSupervisionCheckpointRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]"!][!//
/* alive supervision of CP [!"$CPName"!] in mode [!"$IntModeId"!] */
static CONST(WdgM_EB_CPAliveCfgType,WDGM_CONST) WdgM_EB_CPAliveCfg_[!"$IntSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!] =
{
  [!"num:i(WdgMExpectedAliveIndications)"!]U, /* ExpextedAliveIndication */
  [!"num:i(WdgMSupervisionReferenceCycle)"!]U, /* Amount of supervision reference cycles */
  [!"num:i(WdgMMaxMargin)"!]U, /* max margin */
  [!"num:i(WdgMMinMargin)"!]U /* min margin */
};

[!ENDLOOP!][!//
[!/*
Generate Configuration for external supervision graph
=====================================================
*/!][!//
[!/* Check if checkpoint is a destination node of some external transition
*/!][!//
[!VAR "NumConfiguredPredecessors" = "num:i(count(WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalTransition/eb-list::*[(num:i(as:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]))"!][!//
[!IF "$NumConfiguredPredecessors > 0"!][!//
[!VAR "ExtGraphIdOffset" = "num:i(node:pos(WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalTransition/eb-list::*[(num:i(as:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)][1]/../..))"!][!//
/* predecessor points of CP [!"$CPName"!] in mode [!"$IntModeId"!] */
static CONST(WdgM_EB_CPType,WDGM_CONST) WdgM_EB_CPPred_[!"$ExtSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!][[!"$NumConfiguredPredecessors"!]] =
{
  [!LOOP "WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalTransition/eb-list::*[(num:i(as:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]"!][!//
  [!VAR "PredecessorSEID" = "num:i(node:pos(as:ref(WdgMExternalTransitionSourceRef)/../..))"!][!//
  [!VAR "PredecessorCPID" = "num:i(as:ref(WdgMExternalTransitionSourceRef)/WdgMCheckpointId)"!][!//
  {
    [!"$PredecessorSEID"!]U, /* Internal SEId of predecessor 0 */
    [!"$PredecessorCPID"!]U /* CPId of predecessor 0 */
  },
  [!ENDLOOP!][!//
};
[!VAR "tempText"!][!"$tempText"!][!"num:i($ExtSEId)"!]-[!"num:i($IntCPId)"!]:[!"num:i($IntModeId)"!][!ENDVAR!][!//

/* External logical supervision of CP [!"$CPName"!] in mode [!"$IntModeId"!] */
static CONST(WdgM_EB_CPLogicalCfgType,WDGM_CONST) WdgM_EB_CPExtLogicalCfg_[!"$ExtSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!] =
{
  WdgM_EB_CPPred_[!"$ExtSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!], /* pointer to predecessor CPs */
  [!"num:i($BaseExtGraphId+$ExtGraphIdOffset)"!]U, /* graph id */
  [!CALL "GetSEIndexMapped", "SEIdCPIdModeId"="$tempText"!], /* checkpoint sequence */
  [!"$NumConfiguredPredecessors"!]U, /* number of predecessors */
  [!IF "count(WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalCheckpointFinalRef/eb-list::*[(num:i(node:ref(.)/WdgMCheckpointId) = $IntCPId) and ((num:i(node:ref(.)/../../WdgMSupervisedEntityId)) = $ExtSEId)]) > 0"!]  TRUE[!ELSE!]  FALSE[!ENDIF!], /* isFinal */
  [!IF "$OptimizedExternalGraphsEnabled > 0"!][!//
    [!IF "node:existsAndTrue(WdgMExternalLogicalSupervision/eb-list::*[WdgMExternalTransition/eb-list::*[((num:i(node:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and ((num:i(node:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId)) = $ExtSEId))]]/WdgMExtLogicalOptimization)"!][!//
  TRUE /* flag for external graph optimization. */
    [!ELSE!][!//
  FALSE /* flag for external graph optimization. */
    [!ENDIF!][!//
  [!ENDIF!][!//
};
[!ELSE!][!//
[!/* Check if the checkpoint is an initial node of some graph and not already treated before
*/!][!//
[!LOOP "WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalCheckpointInitialRef/eb-list::*[(num:i(as:ref(.)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(.)/../../WdgMSupervisedEntityId) = $ExtSEId)]"!][!//
[!VAR "ExtGraphIdOffset" = "num:i(node:pos(../..))"!][!//
[!VAR "tempText"!][!"$tempText"!][!"num:i($ExtSEId)"!]-[!"num:i($IntCPId)"!]:[!"num:i($IntModeId)"!][!ENDVAR!][!//
/* External logical supervision of CP [!"$CPName"!] in mode [!"$IntModeId"!] */
static CONST(WdgM_EB_CPLogicalCfgType,WDGM_CONST) WdgM_EB_CPExtLogicalCfg_[!"$ExtSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!] =
{
  NULL_PTR, /* initial node has no predecessor CPs */
  [!"num:i($BaseExtGraphId+$ExtGraphIdOffset)"!]U, /* graph id */
  [!CALL "GetSEIndexMapped", "SEIdCPIdModeId"="$tempText"!], /* checkpoint sequence */
  0U, /* number of predecessors */
  FALSE, /* isFinal */
  [!IF "$OptimizedExternalGraphsEnabled > 0"!][!//
    [!IF "node:existsAndTrue(./../../WdgMExtLogicalOptimization)"!][!//
  TRUE /* flag for external graph optimization. */
    [!ELSE!][!//
  FALSE /* flag for external graph optimization. */ 
    [!ENDIF!][!//
  [!ENDIF!][!//
};
[!ENDLOOP!][!//
[!ENDIF!][!//
[!/* continuously increment base graph id
*/!][!//
[!VAR "BaseExtGraphId" = "$BaseExtGraphId + num:i(count(WdgMExternalLogicalSupervision/eb-list::*))"!][!//
[!ENDLOOP!][!/* WdgM modes
*/!][!//
[!/*
Generate Configuration for internal supervision graph
=====================================================
Check if internal supervision is configured at all for the CPs of actual SE
*/!][!//
/* !LINKSTO WdgM.SWS_WdgM_00366,1 */
[!VAR "IsInternalLogicalSupervisionConfigured" = "count(../../WdgMInternalTransition/eb-list::*[((num:i(as:ref(WdgMInternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMInternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)) or ((num:i(as:ref(WdgMInternalTransitionSourceRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMInternalTransitionSourceRef)/../../WdgMSupervisedEntityId) = $ExtSEId))]) > 0"!][!//
[!IF "$IsInternalLogicalSupervisionConfigured"!][!//
[!VAR "NumConfiguredPredecessors" = "num:i(count(../../WdgMInternalTransition/eb-list::*[(num:i(as:ref(WdgMInternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMInternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]))"!][!//
[!IF "$NumConfiguredPredecessors > 0"!][!//
/* predecessor points of CP [!"$CPName"!] */
static CONST(WdgM_EB_CPType,WDGM_CONST) WdgM_EB_CPPred_[!"$IntSEId"!]_[!"$IntCPId"!][[!"$NumConfiguredPredecessors"!]] =
{
  [!LOOP "../../WdgMInternalTransition/eb-list::*[(num:i(as:ref(WdgMInternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMInternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]"!][!//
  [!VAR "PredecessorSEID" = "num:i(node:pos(as:ref(WdgMInternalTransitionSourceRef)/../..))"!][!//
  [!VAR "PredecessorCPID" = "num:i(as:ref(WdgMInternalTransitionSourceRef)/WdgMCheckpointId)"!][!//
  {
    [!"$PredecessorSEID"!]U, /* Internal SEId of predecessor 0 */
    [!"$PredecessorCPID"!]U /* CPId of predecessor 0 */
  },
  [!ENDLOOP!][!//
};

/* Internal logical supervision of [!"$CPName"!] */
static CONST(WdgM_EB_CPLogicalCfgType,WDGM_CONST) WdgM_EB_CPIntLogicalCfg_[!"$IntSEId"!]_[!"$IntCPId"!] =
{
  WdgM_EB_CPPred_[!"$IntSEId"!]_[!"$IntCPId"!], /* pointer to predecessor CPs */
  [!"num:i($BaseIntGraphId)"!]U, /* graph id */
  0U, /* checkpoint sequence for internal logical supervision is not used */
  [!"$NumConfiguredPredecessors"!]U, /* number of predecessors */
  [!IF "count(../../WdgMInternallCheckpointFinalRef/eb-list::*[(num:i(node:ref(.)/WdgMCheckpointId) = $IntCPId) and ((num:i(node:ref(.)/../../WdgMSupervisedEntityId)) = $ExtSEId)]) > 0"!]  TRUE[!ELSE!]
  FALSE[!ENDIF!], /* isFinal */
  [!IF "$OptimizedExternalGraphsEnabled > 0"!][!//
  FALSE /* flag for external graph optimization. */
  [!ENDIF!][!//
};

[!ELSEIF "node:refvalid(../../WdgMInternalCheckpointInitialRef) and (num:i(node:ref(../../WdgMInternalCheckpointInitialRef)/WdgMCheckpointId) = $IntCPId) and (num:i(node:ref(../../WdgMInternalCheckpointInitialRef)/../../WdgMSupervisedEntityId) = $ExtSEId)"!][!//
/* predecessor points of CP [!"$CPName"!] */
static CONST(WdgM_EB_CPType,WDGM_CONST) WdgM_EB_CPPred_[!"$IntSEId"!]_[!"$IntCPId"!][1] =
{
  {
    WDGM_EB_DUMMY_SEID, /* SEId of predecessor 0 */
    WDGM_EB_DUMMY_CPID /* CPId of predecessor 0 */
  }
};

/* Internal logical supervision of [!"$CPName"!] */
static CONST(WdgM_EB_CPLogicalCfgType,WDGM_CONST) WdgM_EB_CPIntLogicalCfg_[!"$IntSEId"!]_[!"$IntCPId"!] =
{
  WdgM_EB_CPPred_[!"$IntSEId"!]_[!"$IntCPId"!], /* pointer to predecessor CPs */
  [!"num:i($BaseIntGraphId)"!]U, /* graph id */
  0U, /* checkpoint sequence for internal logical supervision is not used */
  0U, /* number of predecessors */
  FALSE, /* isFinal */
  [!IF "$OptimizedExternalGraphsEnabled > 0"!][!//
  FALSE /* flag for external graph optimization. */
  [!ENDIF!][!//
};

[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!// Checkpoints
[!/*
Generate Configuration for deadline supervision
===============================================
*/!][!//
[!LOOP "util:distinct(node:order(../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
[!VAR "IntModeId" = "WdgMModeId"!][!//
[!VAR "ListOfGeneratedCPIds" = "''"!][!//
[!FOR "MaxSimpleSortLoop" = "0" TO "count(../../../../WdgMGeneral/WdgMSupervisedEntity/eb-list::*[WdgMSupervisedEntityId = $ExtSEId]/WdgMCheckpoint/eb-list::*)"!]
[!VAR "IsContinueSimpleSortLoop" = "'false'"!][!//
[!LOOP "util:distinct(node:order(../../../../WdgMGeneral/WdgMSupervisedEntity/eb-list::*[number(WdgMSupervisedEntityId) = $ExtSEId]/WdgMCheckpoint/eb-list::*, 'WdgMCheckpointId'))"!][!//
[!VAR "CPName" = "as:name(.)"!][!//
[!VAR "IntCPId" = "WdgMCheckpointId"!][!//
[!SELECT "../../../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*[number(WdgMModeId) = $IntModeId]"!][!//
[!IF "not(text:contains( text:split($ListOfGeneratedCPIds), $IntCPId))"!][!//
[!VAR "IsDeadlineSupervisionStartConfiguration" = "count(WdgMDeadlineSupervision/eb-list::*[((num:i(as:ref(WdgMDeadlineStartRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStartRef)/../../WdgMSupervisedEntityId) = $ExtSEId))]) = 1"!][!//
[!IF "$IsDeadlineSupervisionStartConfiguration"!][!//
  [!VAR "DeadlineSupervisionStartConfigurationDMMax" = "WdgMDeadlineSupervision/eb-list::*[((num:i(as:ref(WdgMDeadlineStartRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStartRef)/../../WdgMSupervisedEntityId) = $ExtSEId))][1]/WdgMDeadlineMax"!][!//
  [!VAR "DeadlineSupervisionStartConfigurationDMMin" = "WdgMDeadlineSupervision/eb-list::*[((num:i(as:ref(WdgMDeadlineStartRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStartRef)/../../WdgMSupervisedEntityId) = $ExtSEId))][1]/WdgMDeadlineMin"!][!//
  [!VAR "DeadlineSupervisionStartConfigurationDMStopRef" = "WdgMDeadlineSupervision/eb-list::*[((num:i(as:ref(WdgMDeadlineStartRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStartRef)/../../WdgMSupervisedEntityId) = $ExtSEId))][1]/WdgMDeadlineStopRef"!][!//
  [!VAR "IsPrevDeadlineSupervisionConfiguration" = "count(WdgMDeadlineSupervision/eb-list::*[((num:i(as:ref(WdgMDeadlineStopRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStopRef)/../../WdgMSupervisedEntityId) = $ExtSEId))]) > 0"!][!//
  [!VAR "DoGenerateCPId" = "'true'"!][!//
  [!IF "$IsPrevDeadlineSupervisionConfiguration"!][!//
    [!VAR "PrevDeadlineSupervisionConfiguration" = "WdgMDeadlineSupervision/eb-list::*[((num:i(as:ref(WdgMDeadlineStopRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStopRef)/../../WdgMSupervisedEntityId) = $ExtSEId))][1]/WdgMDeadlineStartRef"!][!//
    [!VAR "PrevDeadlineSupervisionIntCPId" = "num:i(as:ref($PrevDeadlineSupervisionConfiguration)/WdgMCheckpointId)"!][!//
    [!VAR "PrevDeadlineSupervisionIntSEId" = "num:i(node:pos(as:ref($PrevDeadlineSupervisionConfiguration)/../..))"!][!//
    [!VAR "IsPrevDeadlineSupervisionConfigurationNotGenerated" = "not(text:contains( text:split($ListOfGeneratedCPIds), $PrevDeadlineSupervisionIntCPId))"!][!//
    [!IF "$IsPrevDeadlineSupervisionConfigurationNotGenerated"!][!//
      [!VAR "IsContinueSimpleSortLoop" = "'true'"!][!//
      [!VAR "DoGenerateCPId" = "'false'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!IF "$DoGenerateCPId = 'true'"!][!//
    [!VAR "ListOfGeneratedCPIds" = "concat($ListOfGeneratedCPIds, ' ', $IntCPId)"!][!//
/* deadline configuration for start CP [!"$CPName"!] in mode [!"$IntModeId"!] */
static CONST(WdgM_EB_CPDeadlineCfgType,WDGM_CONST) WdgM_EB_CPDeadlineCfg_[!"$IntSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!] =
{
  [!"num:i(round(num:f(num:div($DeadlineSupervisionStartConfigurationDMMax, $TimeGranularity))))"!]U, /* maximum Deadline in granularity of [!"num:i(num:mul($TimeGranularity, 1000000))"!]us */
  [!"num:i(round(num:f(num:div($DeadlineSupervisionStartConfigurationDMMin, $TimeGranularity))))"!]U, /* minimum Deadline in granularity of [!"num:i(num:mul($TimeGranularity, 1000000))"!]us */
  [!"num:i(num:div(num:i(num:i(round(num:f(num:div($DeadlineSupervisionStartConfigurationDMMax, $TimeGranularity)))) + $MainFunctionCycleTime - 1), $MainFunctionCycleTime))"!]U, /* maximum allowed main function calls until deadline violation */
  [!IF "$IsPrevDeadlineSupervisionConfiguration"!][!//
  &(WdgM_EB_CPDeadlineCfg_[!"$PrevDeadlineSupervisionIntSEId"!]_[!"$PrevDeadlineSupervisionIntCPId"!]_[!"$IntModeId"!]),
  [!ELSE!][!//
  NULL_PTR,
  [!ENDIF!][!//
  [!"num:i($DMId)"!]U, /* internal Deadline Monitoring ID for runtime data */
  [!"num:i($IntCPId)"!]U, /* Internal Checkpoint id of start checkpoint */
  [!"num:i(as:ref($DeadlineSupervisionStartConfigurationDMStopRef)/WdgMCheckpointId)"!]U, /* Internal Checkpoint id of stop checkpoint */
};
[!VAR "DMId" = "num:i($DMId + 1)"!][!//

  [!ENDIF!][!// DoGenerateCPId
[!ENDIF!][!// $IsDeadlineSupervisionStartConfiguration
[!ENDIF!][!// not(text:contains( text:split($ListOfGeneratedCPIds), $IntCPId))
[!ENDSELECT!][!//
[!ENDLOOP!][!// Checkpoints
[!IF "$IsContinueSimpleSortLoop = 'false'"!][!//
  [!BREAK!][!//
[!ENDIF!][!//
[!ENDFOR!][!// MaxSimpleSortLoop: Ensures that all Checkpoints are generated in worst-case
[!ENDLOOP!][!// WdgMModes

/* checkpoint configuration of SE [!"$SEName"!] */
static CONST(WdgM_EB_CPCfgType,WDGM_CONST) WdgM_EB_CPCfg_[!"$SEName"!][[!"num:i(count(WdgMCheckpoint/eb-list::*))"!]] =
{
[!LOOP "util:distinct(node:order(WdgMCheckpoint/eb-list::*, 'WdgMCheckpointId'))"!][!//
[!VAR "IntCPId" = "WdgMCheckpointId"!][!//
[!VAR "IntSupervExists" = "WdgMCheckpointId"!][!//
[!VAR "IsInternalLogicalSupervisionConfigured" = "count(../../WdgMInternalTransition/eb-list::*[((num:i(as:ref(WdgMInternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMInternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)) or ((num:i(as:ref(WdgMInternalTransitionSourceRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMInternalTransitionSourceRef)/../../WdgMSupervisedEntityId) = $ExtSEId))]) > 0"!][!//
  {
    /* CP [!"as:name(.)"!]*/
    {
      /* alive supervision per WdgM mode */
      [!LOOP "util:distinct(node:order(../../../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
      [!VAR "IntModeId" = "WdgMModeId"!][!//
      [!IF "count(WdgMAliveSupervision/eb-list::*[(num:i(as:ref(WdgMAliveSupervisionCheckpointRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMAliveSupervisionCheckpointRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]) = 1"!][!//
      &(WdgM_EB_CPAliveCfg_[!"$IntSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!]),
      [!ELSE!][!//
      NULL_PTR,
      [!ENDIF!][!//
      [!ENDLOOP!][!// WdgMMode
    },
#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
    /* deadline monitoring per WdgM mode */
    {
      [!LOOP "util:distinct(node:order(../../../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
        [!VAR "IntModeId" = "WdgMModeId"!][!//
        [!VAR "IsDeadlineSupervisionStartConfiguration" = "count(WdgMDeadlineSupervision/eb-list::*[(num:i(as:ref(WdgMDeadlineStartRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStartRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]) > 0"!][!//
        [!VAR "IsDeadlineSupervisionStopConfiguration" = "count(WdgMDeadlineSupervision/eb-list::*[(num:i(as:ref(WdgMDeadlineStopRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStopRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]) > 0"!][!//
        [!IF "($IsDeadlineSupervisionStartConfiguration = 'true') or ($IsDeadlineSupervisionStopConfiguration = 'true')"!][!//
          [!IF "$IsDeadlineSupervisionStartConfiguration"!]
            [!VAR "IntStartCPId" = "$IntCPId"!][!//
            [!VAR "IntStartSEId" = "$IntSEId"!][!//
          [!ELSE!][!//
            [!VAR "DeadlineSupervisionConfiguration" = "WdgMDeadlineSupervision/eb-list::*[(num:i(as:ref(WdgMDeadlineStopRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMDeadlineStopRef)/../../WdgMSupervisedEntityId) = $ExtSEId)]/WdgMDeadlineStartRef"!][!//
            [!VAR "IntStartCPId" = "num:i(as:ref($DeadlineSupervisionConfiguration)/WdgMCheckpointId)"!][!//
            [!VAR "IntStartSEId" = "num:i(node:pos(as:ref($DeadlineSupervisionConfiguration)/../..))"!][!//
          [!ENDIF!][!//
      &(WdgM_EB_CPDeadlineCfg_[!"$IntStartSEId"!]_[!"$IntStartCPId"!]_[!"$IntModeId"!]),
        [!ELSE!][!//
      NULL_PTR,
        [!ENDIF!][!//
      [!ENDLOOP!][!// WdgMMode
    },
#endif
#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
    /* internal logical supervision per WdgM mode */
    {
      [!LOOP "util:distinct(node:order(../../../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
        [!VAR "IntModeId" = "WdgMModeId"!][!//
        [!VAR "IsExternalLogicalSupervisionConfigured" = "count(WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalTransition/eb-list::*[((num:i(as:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)) or ((num:i(as:ref(WdgMExternalTransitionSourceRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionSourceRef)/../../WdgMSupervisedEntityId) = $ExtSEId))]) > 0"!][!//
        [!VAR "SupervisedEntityIsReferencedInMode" = "count(WdgMLocalStatusParams/eb-list::*[(num:i(as:ref(WdgMLocalStatusSupervisedEntityRef)/WdgMSupervisedEntityId)) = $ExtSEId]) > 0"!][!//
        [!IF "($IsInternalLogicalSupervisionConfigured = 'true') and ($SupervisedEntityIsReferencedInMode = 'true')"!][!//
      &(WdgM_EB_CPIntLogicalCfg_[!"$IntSEId"!]_[!"$IntCPId"!]),
        [!ELSE!][!//
      NULL_PTR,
        [!ENDIF!][!//
      [!ENDLOOP!][!// WdgMMode
    },
    /* external logical supervision per WdgM mode */
    {
      [!LOOP "util:distinct(node:order(../../../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//
        [!VAR "IntModeId" = "WdgMModeId"!][!//
        [!VAR "IsExternalLogicalSupervisionConfigured" = "count(WdgMExternalLogicalSupervision/eb-list::*/WdgMExternalTransition/eb-list::*[((num:i(as:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId) = $ExtSEId)) or ((num:i(as:ref(WdgMExternalTransitionSourceRef)/WdgMCheckpointId) = $IntCPId) and (num:i(as:ref(WdgMExternalTransitionSourceRef)/../../WdgMSupervisedEntityId) = $ExtSEId))]) > 0"!][!//
        [!VAR "SupervisedEntityIsReferencedInMode" = "count(WdgMLocalStatusParams/eb-list::*[(num:i(as:ref(WdgMLocalStatusSupervisedEntityRef)/WdgMSupervisedEntityId)) = $ExtSEId]) > 0"!][!//
        [!IF "$IsExternalLogicalSupervisionConfigured"!][!//
      &(WdgM_EB_CPExtLogicalCfg_[!"$ExtSEId"!]_[!"$IntCPId"!]_[!"$IntModeId"!]),
        [!ELSE!][!//
      NULL_PTR,
        [!ENDIF!][!//
      [!ENDLOOP!][!// WdgMMode
    },
#endif
  },
[!ENDLOOP!][!// Checkpoints
};
[!/* Supervised Entity contains an internal graph => increment counter for graph id */!][!//
[!IF "count(WdgMInternalTransition/eb-list::*) > 0"!][!//
[!VAR "BaseIntGraphId" = "num:i($BaseIntGraphId + 1)"!][!//
[!ENDIF!][!//
[!//
[!ENDLOOP!][!// Supervised Entities
#define WDGM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>


/*==================[external constants]=========================================================*/

#define WDGM_START_SEC_CONST_ASIL_D_8
#include <WdgM_MemMap.h>

/* Deviation MISRAC2012-2 */
CONST(WdgM_ModeType,WDGM_CONST) WdgM_EB_InitialModeId =
    WdgMConf_WdgMMode_[!"as:name(as:ref(WdgMConfigSet/eb-list::*[1]/WdgMInitialMode))"!];

[!IF "$SleepModeEnabled"!][!//
/* Deviation MISRAC2012-2 */
CONST(WdgM_ModeType,WDGM_CONST) WdgM_EB_DeInitModeId =
    WdgMConf_WdgMMode_[!"as:name(as:ref(WdgMConfigSet/eb-list::*[1]/WdgMSleepMode))"!];

[!ENDIF!][!//

/* Deviation MISRAC2012-2 */
CONST(WdgM_ModeType,WDGM_CONST) WdgM_EB_ModeCfgSize = WDGM_EB_MODE_NUM;

/* Deviation MISRAC2012-2 */
CONST(WdgM_EB_SEIdType, WDGM_CONST) WdgM_EB_SEIntSEId[WDGM_EB_SE_NUM] =
{
  [!LOOP "util:distinct(node:order(WdgMGeneral/WdgMSupervisedEntity/eb-list::*, 'WdgMSupervisedEntityId'))"!][!//
  [!VAR "IntSEId" = "node:pos(.)"!][!//
  [!VAR "SEName" = "as:name(.)"!][!//
  [!"$IntSEId"!]U, /* Internal Id of [!"$SEName"!] */
  [!ENDLOOP!][!//
};

[!IF "$WdgMMulticoreEnabled = 'true'"!]
[!VAR "SECoreIdx"!][!ENDVAR!][!//
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!/*
*/!][!VAR "SupEntPerCore" = "0"!][!/*
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
   */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!/*
       */!][!VAR "SECoreIdx"!][!"$SECoreIdx"!][!"num:i(node:pos(.))"!]:[!"num:i($index_i)"!]:[!"num:i($SupEntPerCore)"!];[!ENDVAR!][!/*
       */!][!VAR "SupEntPerCore" = "$SupEntPerCore + 1"!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!//
[!ENDFOR!][!//

CONST(WdgM_EB_SEIdType, WDGM_CONST) WdgM_EB_SELocalCoreIdx[WDGM_EB_SE_NUM] =
{
[!LOOP "util:distinct(node:order(WdgMGeneral/WdgMSupervisedEntity/eb-list::*, 'node:pos(.)'))"!][!//
  [!VAR "IntSEId" = "node:pos(.)"!][!//
  [!VAR "SEName" = "as:name(.)"!][!//
  [!LOOP "text:split($SECoreIdx, ';')"!]
    [!VAR "SEIndex" = "text:split( ., ':' )[1]"!]
    [!VAR "CoreId" = "text:split( ., ':' )[2]"!]
    [!VAR "CoreIdx" = "text:split( ., ':' )[3]"!]
     [!IF "$SEIndex = $IntSEId"!]
  [!"$CoreIdx"!]U, /* Maps internal Id of [!"$SEName"!] to Idx in Core [!"$CoreId"!] status array*/
     [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDLOOP!][!//

};
[!ENDIF!][!//

[!IF "$WdgMPartitionResetEnabled = 'true'"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]

  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
            [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]

[!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!]

/** \brief
 ** Identifier of Os application of each WdgM SE with Os application
 ** mapping to Core [!"num:i($index_i)"!] .
 **/
static CONST(ApplicationType, WDGM_CONST) WdgM_EB_Core[!"num:i($index_i)"!]PartitionId[[!"num:i($WdgMNumOfPartitionsPerCore)"!]U] = 
{
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
  [!"as:name(as:ref(./WdgMOsApplicationRef))"!], /* Os application identifier */
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
  [!"as:name(as:ref(./WdgMOsApplicationRef))"!], /* Os application identifier */
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
};

[!ENDIF!][!//

[!ENDFOR!][!//
[!ENDIF!][!//

#define WDGM_STOP_SEC_CONST_ASIL_D_8
#include <WdgM_MemMap.h>

/*------------------[mode configuration]------------------------------------*/
#define WDGM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

CONST(WdgM_EB_ModeCfgType, WDGM_CONST) WdgM_EB_ModeCfg[WDGM_EB_MODE_NUM] =
{
  [!LOOP "util:distinct(node:order(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!]
  { /* mode [!"as:name(.)"!] (id [!"WdgMModeId"!]) */
    [!CALL "getModeSpecificLCM", "modeRef" = "as:path(.)"!]U, /* least common multiple of all reference cycle values */
    [!IF "count(WdgMTrigger/eb-list::*) > 0"!]
    WdgM_EB_TrigCfg_M[!"WdgMModeId"!], /* trigger configuration */
    [!ELSE!]
    NULL_PTR, /* no triggers in this mode */
    [!ENDIF!]
    [!"WdgMExpiredSupervisionCycleTol"!]U, /* number of supervision cycles in stats EXPIRED */
    [!"num:i(count(WdgMTrigger/eb-list::*))"!]U /* number of watchdogs (triggers) */
  },
  [!ENDLOOP!][!// WdgMMode/eb-list::*
};

/* -----------------[SE configuration]--------------------- */

CONST(WdgM_EB_SECfgType,WDGM_CONST) WdgM_EB_SECfg[WDGM_EB_SE_NUM] =
{
  [!LOOP "WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
  [!VAR "ExtSEId" = "num:i(WdgMSupervisedEntityId)"!]
  { /* SE [!"as:name(.)"!] (internal SEId: [!"node:pos(.)"!]) */
    WdgM_EB_CPCfg_[!"as:name(.)"!], /* pointer to the array of checkpoints */
    WdgM_EB_CPData_[!"as:name(.)"!], /* pointer to the run-time data of the CPs */
    WdgMConf_WdgMSupervisedEntity_[!"as:name(.)"!], /* external SEId */
    [!"num:i(count(WdgMCheckpoint/eb-list::*))"!]U, /* number of CPs in this SE */
    [!WS!][!WS!][!WS!][!WS!][!IF "node:existsAndTrue(WdgMErrorRecoveryEnabled)"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* Support for Error Recovery */
    [!IF "$WdgMPartitionResetEnabled = 'true'"!]
    [!IF "node:exists(WdgMOsApplicationRef)"!]
    TRUE, /* Support for mapping the SE to an Os partition. */
    [!"as:name(as:ref(WdgMOsApplicationRef))"!], /* identifier of referenced Os Application */
    [!IF "$WdgMMulticoreEnabled"!]
    WdgM_EB_Core[!"WdgMSupervisedEntityCoreId"!]_PartitionStatus, /* status of WdgM partition */ /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable29,1 */
    [!ELSE!]
    WdgM_EB_Core0_PartitionStatus, /* status of WdgM partition */ /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable29,1 */
    [!ENDIF!]
    [!ELSE!]
    FALSE, /* Support for mapping the SE to an Os partition. */
    INVALID_OSAPPLICATION, /* identifier of referenced Os Application */
    NULL_PTR, /* status of WdgM partition (no WdgMOsApplicationRef exists for this SE entry) */
    [!ENDIF!]
    [!ENDIF!][!//
    /* number of tolerated reference cycles which are allowed to fail in each WdgM mode*/
    {
      [!LOOP "util:distinct(node:order(../../../WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!]
      [!IF "count(WdgMLocalStatusParams/eb-list::*[number(as:ref(WdgMLocalStatusSupervisedEntityRef)/WdgMSupervisedEntityId) = $ExtSEId]) > 0"!]
      [!"WdgMLocalStatusParams/eb-list::*[number(as:ref(WdgMLocalStatusSupervisedEntityRef)/WdgMSupervisedEntityId) = $ExtSEId]/WdgMFailedAliveSupervisionRefCycleTol"!]U, /* WdgM mode [!"as:name(.)"!] */
      [!ELSE!]
      WDGM_EB_DUMMY_FAILEDREFCYCLETOL, /* WdgM mode [!"as:name(.)"!] */
      [!ENDIF!]
      [!ENDLOOP!][!// /*
    [!IF "$WdgMMulticoreEnabled"!]
    },
    [!"WdgMSupervisedEntityCoreId"!]U, /* the core id of a SE */
  },
    [!ELSE!]
    }
  },
    [!ENDIF!]
  [!ENDLOOP!][!//
};

/* Dummy module configuration structure*/
CONST(WdgM_ConfigType, WDGM_APPL_CONST) WDGM_CONFIG_NAME = 0;

#define WDGM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

/*============[WdgM internal data]===============*/
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_SATELLITE_R_VAR_INIT_16
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

#if (WDGM_EB_EXT_GET_EXPECTED_INIT_STATE_ENABLED == STD_OFF || WDGM_EB_MULTICORE_ENABLED == STD_ON)
/* For multicore this variable is also used by the master to announce the satellites of the
 * result of the WdgMGetExpectedInitStateCallout(), so this is not under the
 * WDGM_EB_EXT_GET_EXPECTED_INIT_STATE_ENABLED == STD_OFF compiler switch. */
/** \brief Expected initialization state of the WdgM module */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable18,1 */
/* Deviation MISRAC2012-3 */
VAR(WdgM_EB_InitStatusType, WDGM_VAR) WdgM_EB_ExpectedInitState = WDGM_EB_INIT_STATUS_DEINIT;
#endif

#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_SATELLITE_R_VAR_INIT_16
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

/* !LINKSTO WDGM.EB.TIMEPM.WDGM020307,2 */
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_SATELLITE_R_VAR_INIT_8
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable2,1 */
/* !LINKSTO WdgM.SWS_WdgM_00387,1 */
/** \brief WdgM global supervision status */
VAR(WdgM_GlobalStatusType, WDGM_VAR) WdgM_EB_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;

#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_SATELLITE_R_VAR_INIT_8
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>

[!IF "$WdgMMulticoreEnabled = 'false'"!]
/* !LINKSTO WdgM.SWS_WdgM_00200,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable1,4 */
/** \brief defines the local statuses of all SE */
/* Deviation MISRAC2012-3 */
VAR(WdgM_LocalStatusType, WDGM_VAR) WdgM_EB_SELocalStatus[WDGM_EB_SE_NUM];
[!ENDIF!][!//

#if (WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE_ENABLED == STD_OFF)
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable17,1 */
VAR(WdgM_ModeType, WDGM_VAR) WdgM_EB_ExpectedWdgMModeId;
#endif

#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>

#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_VAR_CLEARED_16
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable26,1 */
/** \brief has the expired SEId been set? */
#if (WDGM_MIXED_CRITICALITY == STD_ON)
VAR(uint16, WDGM_VAR) WdgM_EB_IsExpiredSEIdSet;
#else
VAR(boolean, WDGM_VAR) WdgM_EB_IsExpiredSEIdSet;
#endif

#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_VAR_CLEARED_16
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

[!IF "$WdgMMulticoreEnabled = 'false'"!]
[!IF "$WdgMGetAllExpiredSEIDs = 'true'"!]
#define WDGM_START_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_MemMap.h>

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable27,1 */
/** \brief List of expired supervised entities */
static VAR(WdgM_EB_ExpiredSEIDType, WDGM_VAR_POWER_ON_INIT) WdgM_EB_ExpiredSEIDs[WDGM_EB_SE_NUM] = 
{
[!LOOP "util:distinct(node:order(WdgMGeneral/WdgMSupervisedEntity/eb-list::*, 'WdgMSupervisedEntityId'))"!][!//
  0xFF00U,
[!ENDLOOP!][!//
};

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable28,1 */
/** \brief The number of expired supervised entities */
static VAR(WdgM_EB_ExpiredSEIDType, WDGM_VAR_POWER_ON_INIT) WdgM_EB_ExpiredSEIDsCounter = 0xFF00U;

#define WDGM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_MemMap.h>
[!ENDIF!]
[!ENDIF!][!//

#define WDGM_START_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_MemMap.h>

/** \brief the Supervised Entity Id which first expired */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable19,1 */
VAR(WdgM_EB_ExpiredSEIDType, WDGM_VAR_POWER_ON_INIT) WdgM_EB_ExpiredSEID = 0U;

#define WDGM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_MemMap.h>

[!IF "$WdgMMulticoreEnabled"!]

[!IF "$WdgMGetAllExpiredSEIDs = 'true'"!]
[!VAR "SupEntExistPerCore" = "false()"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_POWER_ON_INIT_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif
[!ELSE!][!//
#define WDGM_START_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_MemMap.h>
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable27,1 */
/** \brief List of expired supervised entities on core [!"num:i($index_i)"!] */
static VAR(WdgM_EB_ExpiredSEIDType, WDGM_VAR_POWER_ON_INIT) WdgM_EB_ExpiredSEIDs_Core[!"num:i($index_i)"!][WDGM_EB_SE_NUM_CORE[!"$index_i"!]] = {
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
    0xFF00U,
    [!ENDIF!]
  [!ENDLOOP!]
};

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable28,1 */
/** \brief The number of expired supervised entities on core [!"num:i($index_i)"!] */
static VAR(WdgM_EB_ExpiredSEIDType, WDGM_VAR_POWER_ON_INIT) WdgM_EB_ExpiredSEIDsCounter_Core[!"num:i($index_i)"!] = 0xFF00U;

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_POWER_ON_INIT_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif
[!ELSE!][!//
#define WDGM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_D_16
#include <WdgM_MemMap.h>

[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]

[!ENDIF!]

[!VAR "SupEntExistPerCore" = "false()"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_CLEARED_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif
[!ELSE!][!//
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020307,2 */
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_SATELLITE_R_VAR_CLEARED_16
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>
#endif
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable14,1 */
/** \brief through this variable, the WdgM master instance announces the WdgM satellite instances that the mode switch has been performed.
* The WdgM satellite instances read the value of this variable to change and update their mode. */
static VAR(WdgM_EB_ModeType, WDGM_VAR) WdgM_EB_CoreSwitchMode_Core[!"$index_i"!];

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_CLEARED_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif
[!ELSE!][!//
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_SATELLITE_R_VAR_CLEARED_16
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>
#endif
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
   [!ENDIF!][!/* IF $SupEntExistPerCore */!]
   [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]

[!VAR "SupEntExistPerCore" = "false()"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_INIT_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif
[!ELSE!][!//
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020306,1 */
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_VAR_16
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]

/* !LINKSTO WDGM.EB.MulticoreInit.4,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable15,3 */
/** \brief WdgM/WdgM core instance initialization status */
static VAR(WdgM_EB_InitStatusType, WDGM_VAR) WdgM_EB_InitStatus_Core[!"$index_i"!] = WDGM_EB_INIT_STATUS_DEINIT;

[!IF "$WdgMTriggerWdgDriverMulticore"!]
  [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable34,1 */
/** \brief Indicates an error in setting the mode for satellite controlled watchdog drivers */
static VAR(WdgM_EB_SatelliteWdgIfSetModeFailedType, WDGM_VAR) WdgM_EB_SatelliteWdgIfSetModeFailed_Core[!"num:i($index_i)"!] = WDGM_EB_FALSE;
  [!ENDIF!]
[!ENDIF!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_INIT_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif

[!ELSE!][!//
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_VAR_16
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]

[!VAR "SupEntExistPerCore" = "false()"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]
  [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
    [!IF "$SatelliteAlivenessCalloutEnabled"!]
#define WDGM_START_SEC_VAR_INIT_ASIL_D_32
#include <WdgM_MemMap.h>
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable37,1 */
/** \brief Stores the last satellite alive counter value for comparison reasons, this variable is updated by the master core*/
static VAR(uint32, WDGM_VAR) WdgM_MasterCounter_Core[!"num:i($index_i)"!] = 0xFFFFFFFFU;
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_32
#include <WdgM_MemMap.h>

#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_INIT_32
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable36,1 */
/** \brief Stores the current satellite alive counter value, this variable is updated by the satellite core*/
#if (WDGM_MIXED_CRITICALITY == STD_ON)
static VAR(uint32, WDGM_VAR) WdgM_EB_Satellite_Core[!"num:i($index_i)"!]_AliveCounter = 0xFFFF0000U;
#else
static VAR(uint32, WDGM_VAR) WdgM_EB_Satellite_Core[!"num:i($index_i)"!]_AliveCounter = 0U;
#endif
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_INIT_32
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
    [!ENDIF!]
  [!ENDIF!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]

[!VAR "SupEntExistPerCore" = "false()"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_INIT_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif
[!ELSE!][!//
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020306,1 */
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_VAR_INIT_LOCAL_16
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>
#endif
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]

[!VAR "NumSePerCore"="0"!]
[!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
  [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
    [!VAR "NumSePerCore" = "$NumSePerCore + 1"!]
  [!ENDIF!]
[!ENDLOOP!]
/* !LINKSTO WDGM.EB.MulticoreLocalStatus2,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable1,4 */
/** \brief defines the local statuses of all SE from core [!"num:i($index_i)"!] */
[!IF "(node:existsAndTrue(as:modconf('WdgM')[1]/WdgMGeneral/WdgMMixedSafetyCriticalityEnabled))"!]
static VAR(WdgM_EB_LocalStatusType, WDGM_VAR) WdgM_EB_SELocalStatus_Core[!"num:i($index_i)"!][WDGM_EB_SE_NUM_CORE[!"$index_i"!]] = 
{
[!FOR "idx" = "0" TO "num:i($NumSePerCore)-1"!]
  0xFF00,
[!ENDFOR!]
};
[!ELSE!]
static VAR(WdgM_EB_LocalStatusType, WDGM_VAR) WdgM_EB_SELocalStatus_Core[!"num:i($index_i)"!][WDGM_EB_SE_NUM_CORE[!"$index_i"!]];
[!ENDIF!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_INIT_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#else
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
#endif

[!ELSE!][!//
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_VAR_INIT_LOCAL_16
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]

[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_CLEARED_ASIL_D_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
[!ELSE!][!//
#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_16
#include <WdgM_MemMap.h>
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable25,1 */
/** \brief Internal RAM data holding a copy of the alive counter values for each checkpoint */
static VAR(WdgM_EB_CPInternalDataType, WDGM_VAR) WdgM_EB_IntRAMData_Core[!"$index_i"!][WDGM_EB_CHECKPOINTS_NUM_CORE[!"$index_i"!]];

/* !LINKSTO WdgM.SWS_WdgM_00085.3,1, WDGM.EB.DesignDecision.InternalVariable10,3 */
/** \brief failed reference cycle counter for the SE  */
static VAR(uint16, WDGM_VAR) WdgM_EB_FailedAliveSupervisionRefCycleCnt_Core[!"$index_i"!][WDGM_EB_SE_NUM_CORE[!"$index_i"!]];

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_CLEARED_ASIL_D_16
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>

[!ELSE!][!//
#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_16
#include <WdgM_MemMap.h>

[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#define WDGM_1_CORE_[!"num:i($index_i)"!]_START_SEC_VAR_INIT_ASIL_D_LOCAL_UNSPECIFIED
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>
[!ELSE!][!//
#define WDGM_START_SEC_VAR_INIT_ASIL_D_LOCAL_UNSPECIFIED
#include <WdgM_MemMap.h>
[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]

  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]

/** \brief The WdgM core specific context data.
 ** This variable holds the core-specific run time data of the WdgM. */
/* Deviation MISRAC2012-2 */
static VAR(WdgM_EB_CoreContextType, WDGM_VAR) WdgM_EB_Core[!"num:i($index_i)"!]_Context =
{
  WdgM_EB_SELocalStatus_Core[!"num:i($index_i)"!],
[!IF "$WdgMTriggerWdgDriverMulticore"!]
  [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
  &WdgM_EB_SatelliteWdgIfSetModeFailed_Core[!"num:i($index_i)"!],
  [!ELSE!][!//
  NULL_PTR,
  [!ENDIF!]
[!ENDIF!]
[!IF "$SatelliteAlivenessCalloutEnabled"!]
 [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
  &WdgM_EB_Satellite_Core[!"num:i($index_i)"!]_AliveCounter,
  [!ELSE!][!//
  NULL_PTR,
  [!ENDIF!]
[!ENDIF!]
[!IF "$WdgMGetAllExpiredSEIDs = 'true'"!]
  WdgM_EB_ExpiredSEIDs_Core[!"num:i($index_i)"!],
  WDGM_EB_SE_NUM_CORE[!"num:i($index_i)"!],
  &WdgM_EB_ExpiredSEIDsCounter_Core[!"num:i($index_i)"!],
[!ENDIF!]
  WdgM_EB_FailedAliveSupervisionRefCycleCnt_Core[!"num:i($index_i)"!],
  WdgM_EB_IntRAMData_Core[!"num:i($index_i)"!],
  &WdgM_EB_InitStatus_Core[!"num:i($index_i)"!],
  &WdgM_EB_CoreSwitchMode_Core[!"$index_i"!],
  0U,
  0U,
  FALSE,
#if (WDGM_EB_CHECK_MAINFUNCTION_TIMING == STD_ON)
  0U,
#endif
  [!"num:i($index_i)"!]U,
[!IF "$WdgMPartitionResetEnabled = 'true'"!][!//
  [!WS!][!WS!][!"num:i($WdgMNumOfPartitionsPerCore)"!]U,
[!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!][!//
  WdgM_EB_Core[!"num:i($index_i)"!]PartitionSupervisionCycleCnt /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable30,1 */
[!ELSE!][!//
  NULL_PTR
[!ENDIF!][!//
[!ENDIF!][!//
};

[!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
#define WDGM_1_CORE_[!"num:i($index_i)"!]_STOP_SEC_VAR_INIT_ASIL_D_LOCAL_UNSPECIFIED
#include <WdgM_1_CORE_[!"num:i($index_i)"!]_MemMap.h>

[!ELSE!][!//
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_LOCAL_UNSPECIFIED
#include <WdgM_MemMap.h>

[!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]

#define WDGM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

  [!VAR "SECoreIdx"!][!ENDVAR!][!//
  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!/*
   */!][!VAR "SupEntPerCore" = "0"!][!/*
   */!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
   */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!/*
       */!][!VAR "SECoreIdx"!][!"$SECoreIdx"!][!"num:i(node:pos(.))"!]:[!"num:i($index_i)"!][[!"num:i($SupEntPerCore)"!]];[!ENDVAR!][!/*
       */!][!VAR "SupEntPerCore" = "$SupEntPerCore + 1"!][!/*
   */!][!ENDIF!][!/*
   */!][!ENDLOOP!][!//
  [!ENDFOR!][!//

static CONSTP2CONST(WdgM_EB_LocalStatusType,WDGM_CONST,WDGM_APPL_CONST) WdgM_EB_SELocalStatusMapArray[]= {
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!VAR "nodepos" = "num:i(node:pos(.))"!]
    [!LOOP "text:split($SECoreIdx, ';')"!]
       [!VAR "Index" = "text:split( ., ':' )[1]"!]
       [!IF "num:i($Index) = $nodepos"!]
        [!VAR "CoreIdx" = "text:split( ., ':' )[2]"!]
        &WdgM_EB_SELocalStatus_Core[!"$CoreIdx"!],
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDLOOP!]
  };

#define WDGM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

#define WDGM_START_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>

/* Deviation MISRAC2012-1 */
FUNC_P2VAR(WdgM_EB_CoreContextType, WDGM_APPL_DATA, WDGM_CODE) WdgM_GetCoreInstance(void)
{
  P2VAR(WdgM_EB_CoreContextType, AUTOMATIC, WDGM_APPL_DATA) inst = NULL_PTR;

  const WdgM_EB_CoreIdType coreID = WDGM_EB_GET_CORE_ID();

  switch(coreID)
  {
    [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
      [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
        [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
          [!VAR "SupEntExistPerCore" = "true()"!]
        [!ENDIF!]
      [!ENDLOOP!]
     [!IF "$SupEntExistPerCore"!]
    case [!"num:i($index_i)"!]:
    {
      inst = &WdgM_EB_Core[!"num:i($index_i)"!]_Context;
      break;
    }
     [!ENDIF!][!/* IF $SupEntExistPerCore */!]
     [!VAR "SupEntExistPerCore" = "false()"!]
    [!ENDFOR!]
    default:
    {
      /* No WdgM instance exists for core. */
      break;
    }
  }

  return inst;
}

/* !LINKSTO WDGM.EB.MulticoreInit.4,1 */
/* Deviation MISRAC2012-1 */
FUNC(WdgM_EB_InitStatusType, WDGM_CODE) WdgM_EB_GetGlobalInitStatus(void)
{
  WdgM_EB_InitStatusType GlobalInitStatus = WDGM_EB_INIT_STATUS_INIT;
  if(
  [!VAR "FirstSupEnt" = "true()"!]
  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
      [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
        [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
          [!VAR "SupEntExistPerCore" = "true()"!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$SupEntExistPerCore"!]
        [!IF "$FirstSupEnt = 'false'"!]
            ||
        [!ENDIF!]
          (WDGM_EB_INIT_STATUS_DEINIT == WdgM_EB_InitStatus_Core[!"num:i($index_i)"!])
        [!VAR "FirstSupEnt" = "false()"!]
      [!ENDIF!]
      [!VAR "SupEntExistPerCore" = "false()"!]
  [!ENDFOR!]
  )
  {
    GlobalInitStatus = WDGM_EB_INIT_STATUS_DEINIT;
  }

  return GlobalInitStatus;
}

/* Deviation MISRAC2012-1 */
FUNC(WdgM_EB_InitStatusType, WDGM_CODE) WdgM_EB_GetMasterInitStatus(void)
{
  return WdgM_EB_InitStatus_Core[!"$WDGM_MASTER_CORE_ID"!];
}

[!VAR "SECoreIdx"!][!ENDVAR!][!//
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!/*
*/!][!VAR "SupEntPerCore" = "0"!][!/*
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
   */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!/*
       */!][!VAR "SECoreIdx"!][!"$SECoreIdx"!][!"num:i(node:pos(.))"!]:[!"num:i($index_i)"!][[!"num:i($SupEntPerCore)"!]];[!ENDVAR!][!/*
       */!][!VAR "SupEntPerCore" = "$SupEntPerCore + 1"!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!//
[!ENDFOR!][!//

/* !LINKSTO WDGM.EB.MulticoreLocalStatus2,1 */
/* Deviation MISRAC2012-1 */
FUNC(WdgM_EB_LocalStatusType, WDGM_CODE) WdgM_EB_GetSELocalStatus(WdgM_EB_SEIdType IntSEId, uint8 ApiId)
{
  WdgM_EB_LocalStatusType LocalStatus = 0xFF;

  WDGM_EB_PARAM_UNUSED(ApiId);

  LocalStatus = *WdgM_EB_SELocalStatusMapArray[IntSEId];
  return LocalStatus;
}

[!IF "$WdgMTriggerWdgDriverMulticore"!]
FUNC(WdgM_EB_SatelliteWdgIfSetModeFailedType, WDGM_CODE) WdgM_EB_GetSatelliteWdgIfSetModeFailed(void)
{
  uint8 LocalCounter = 0;

  WdgM_EB_SatelliteWdgIfSetModeFailedType LocalStatus = WDGM_EB_FALSE;

  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
    [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
      [!VAR "SupEntExistPerCore" = "true()"!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "$SupEntExistPerCore"!]
    [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
    {
      LocalStatus = WdgM_EB_SatelliteWdgIfSetModeFailed_Core[!"num:i($index_i)"!];
#if (WDGM_MIXED_CRITICALITY == STD_ON)
      if ((LocalStatus == WDGM_EB_FALSE) || (LocalStatus == WDGM_EB_TRUE))
#endif
      {
        if(LocalStatus == WDGM_EB_TRUE)
        {
          LocalCounter++;
        }
      }
#if (WDGM_MIXED_CRITICALITY == STD_ON)
      else
      {
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
        WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
        WDGM_EB_DET(WDGM_SID_MAIN_FUNCTION, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
        LocalCounter++;
      }
#endif
    }
    [!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
  [!ENDIF!][!/* IF $SupEntExistPerCore */!]
  [!VAR "SupEntExistPerCore" = "false()"!]
  [!ENDFOR!]

  return (LocalCounter > 0U)? WDGM_EB_TRUE : WDGM_EB_FALSE;
}
[!ENDIF!]

[!IF "$SatelliteAlivenessCalloutEnabled"!]
FUNC(void, WDGM_CODE) WdgM_EB_CheckSatelliteAliveCounter(void)
{
  static uint8 MainCyclesCounter = 1U;
  [!IF "$SatelliteAlivenessCoreIdDisable"!]
  boolean FailureFlag = FALSE;
  [!ENDIF!]
  [!IF "$WdgMMixedCriticalityEnabled"!]
  uint16 TempValueRedundantData16;
  Std_ReturnType RetValCheck;
  [!ENDIF!]

  /* !LINKSTO WDGM.EB.Dbg4,1 */
  DBG_WDGM_EB_CHECKSATELLITEALIVECOUNTER_ENTRY();

  if(MainCyclesCounter >= WDGM_EB_SATELLITE_ALIVENESS_CHECK_PERIOD)
  {
    [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]
      [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
        [!IF "$WdgMMixedCriticalityEnabled"!]
        RetValCheck = WdgM_EB_GetCheckedRedundantData16 (WdgM_EB_Satellite_Core[!"num:i($index_i)"!]_AliveCounter, &TempValueRedundantData16);
        if(RetValCheck!= E_OK)
        {
          /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020469,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
          WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
          WDGM_EB_DET(WDGM_SID_MAIN_FUNCTION, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
          [!IF "$SatelliteAlivenessCoreIdDisable = 'false'"!]
          /* !LINKSTO WDGM.EB.TIMEPM.WDGM020455,1 */
          WDGM_EB_SATELLITE_ALIVENESS_FAILURE([!"num:i($index_i)"!]);
          [!ELSE!]
          FailureFlag = TRUE;
          [!ENDIF!]
        }
        else
        {
          if(WdgM_MasterCounter_Core[!"num:i($index_i)"!] != TempValueRedundantData16)
          {
            WdgM_MasterCounter_Core[!"num:i($index_i)"!] = TempValueRedundantData16;
          }
          else
        [!ELSE!]
        if(WdgM_MasterCounter_Core[!"num:i($index_i)"!] != WdgM_EB_Satellite_Core[!"num:i($index_i)"!]_AliveCounter)
        {
          WdgM_MasterCounter_Core[!"num:i($index_i)"!] = WdgM_EB_Satellite_Core[!"num:i($index_i)"!]_AliveCounter;
        }
        else
        [!ENDIF!]
        {
          /* !LINKSTO WDGM.EB.TIMEPM.WDGM020488,1,WDGM.EB.TIMEPM.WDGM020489,1 */
#if (WDGM_EB_PROD_ERR_SATELLITE_ALIVENESS_FAILURE == WDGM_PROD_ERR_REP_TO_DEM)
          WDGM_EB_DEM(WDGM_EB_SAT_ALIVENESS_FAILURE_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_SATELLITE_ALIVENESS_FAILURE == WDGM_PROD_ERR_REP_TO_DET)
          WDGM_EB_DET(WDGM_SID_MAIN_FUNCTION, WDGM_EB_E_DEMTODET_SATELLITE_ALIVENESS_FAILURE);
#endif
        [!IF "$SatelliteAlivenessCoreIdDisable = 'false'"!]
          WDGM_EB_SATELLITE_ALIVENESS_FAILURE([!"num:i($index_i)"!]);
        [!ELSE!]
          FailureFlag = TRUE;
        [!ENDIF!]
        }

        [!IF "$WdgMMixedCriticalityEnabled"!]
        }
        [!ENDIF!]
      [!ENDIF!][!/* IF "$index_i != $WDGM_MASTER_CORE_ID" */!]
    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
    [!ENDFOR!]
  }

  MainCyclesCounter = (MainCyclesCounter >= WDGM_EB_SATELLITE_ALIVENESS_CHECK_PERIOD)? 1U : MainCyclesCounter + 1U;

  [!IF "$SatelliteAlivenessCoreIdDisable"!]
  if(FailureFlag)
  {
   /* !LINKSTO WDGM.EB.TIMEPM.WDGM020490,1 */
    WDGM_EB_SATELLITE_ALIVENESS_FAILURE();
  }
  [!ENDIF!]

  /* !LINKSTO WDGM.EB.Dbg4,1 */
  DBG_WDGM_EB_CHECKSATELLITEALIVECOUNTER_EXIT();
}
[!ENDIF!]

[!IF "$WdgMGetAllExpiredSEIDs = 'true'"!]
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, WDGM_CODE) WdgM_EB_GetAllExpiredSEIDsHelper
(
  P2VAR(uint8, AUTOMATIC, WDGM_APPL_DATA) Counter,
  P2VAR(uint8, AUTOMATIC, WDGM_APPL_DATA) ExpiredSEIDs
)
{
  uint8 LocalIndex;
  uint8 LocalStoreIndex = 0U;
  Std_ReturnType RetVal;
  RetVal = E_OK;

  /* !LINKSTO WDGM.EB.GetAllExpiredSEID.CoreSpecific.Read, 1 */

  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]
  {
    WdgM_EB_SEIdType LocalExpiredCounter_Core[!"num:i($index_i)"!];
    Std_ReturnType RetVal_Core[!"num:i($index_i)"!];

    RetVal_Core[!"num:i($index_i)"!] = WdgM_EB_GetCheckedRedundantData8 (WdgM_EB_ExpiredSEIDsCounter_Core[!"num:i($index_i)"!], &LocalExpiredCounter_Core[!"num:i($index_i)"!]);
    if (RetVal_Core[!"num:i($index_i)"!] != E_OK)
    {
      /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020468,1,WDGM.EB.TIMEPM.WDGM020475,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
      WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
      WDGM_EB_DET(WDGM_SID_GET_ALL_EXPIRED_SEID, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
      RetVal = E_NOT_OK;
    }
    else
    {
      for (LocalIndex = 0U; LocalIndex < LocalExpiredCounter_Core[!"num:i($index_i)"!]; LocalIndex++)
      {
        WdgM_EB_SEIdType LocalExpiredSEID;
        Std_ReturnType localRetVal;

        localRetVal = WdgM_EB_GetCheckedRedundantData8 (WdgM_EB_ExpiredSEIDs_Core[!"num:i($index_i)"!][LocalIndex], &LocalExpiredSEID);
        if (localRetVal != E_OK)
        {
          /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020468,1,WDGM.EB.TIMEPM.WDGM020475,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
          WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
          WDGM_EB_DET(WDGM_SID_GET_ALL_EXPIRED_SEID, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
          RetVal = E_NOT_OK;
        }
        else
        {
          ExpiredSEIDs[LocalStoreIndex] = LocalExpiredSEID;
          LocalStoreIndex++;
        }
      }
    }
  }

    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
  [!ENDFOR!]

  /* Return the number of expired supervised entities (if any) */
  *Counter = LocalStoreIndex;
  return RetVal;
}

FUNC(Std_ReturnType, WDGM_CODE) WdgM_EB_ResetAllExpiredSEIDs(void)
{
  uint8 LocalIndex;
  Std_ReturnType RetVal;
  RetVal = E_OK;

  /* !LINKSTO WDGM.EB.Dbg4,1 */
  DBG_WDGM_EB_RESETALLEXPIREDSEIDS_ENTRY();

  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SupEntExistPerCore" = "true()"!]
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$SupEntExistPerCore"!]
    
  {
    WdgM_EB_SEIdType LocalExpiredCounter_Core[!"num:i($index_i)"!];
    Std_ReturnType RetVal_Core[!"num:i($index_i)"!];

    RetVal_Core[!"num:i($index_i)"!] = WdgM_EB_GetCheckedRedundantData8 (WdgM_EB_ExpiredSEIDsCounter_Core[!"num:i($index_i)"!], &LocalExpiredCounter_Core[!"num:i($index_i)"!]);
    if (RetVal_Core[!"num:i($index_i)"!] != E_OK)
    {
      /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020468,1,WDGM.EB.TIMEPM.WDGM020475,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
      WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
      WDGM_EB_DET(WDGM_SID_GET_ALL_EXPIRED_SEID, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
      RetVal = E_NOT_OK;
    }
    else
    {
      for (LocalIndex = 0U; LocalIndex < LocalExpiredCounter_Core[!"num:i($index_i)"!]; LocalIndex++)
      {
        WdgM_EB_StoreRedundantData8(&WdgM_EB_ExpiredSEIDs_Core[!"num:i($index_i)"!][LocalIndex], 0U);
      }
      WdgM_EB_StoreRedundantData8(&WdgM_EB_ExpiredSEIDsCounter_Core[!"num:i($index_i)"!], 0U);
    }
  }

    [!ENDIF!][!/* IF $SupEntExistPerCore */!]
    [!VAR "SupEntExistPerCore" = "false()"!]
  [!ENDFOR!]

  /* !LINKSTO WDGM.EB.Dbg4,1 */
  DBG_WDGM_EB_RESETALLEXPIREDSEIDS_EXIT(RetVal);
  return RetVal;
}
[!ENDIF!]

/* Deviation MISRAC2012-1 */
FUNC(WdgM_EB_ModeType, WDGM_CODE) WdgM_EB_GetCoreSwitchMode(WdgM_EB_CoreIdType CoreId)
{
#if (WDGM_MIXED_CRITICALITY == STD_ON)
  WdgM_EB_ModeType LocalMode = 0x00FF;
#else
  WdgM_EB_ModeType LocalMode = 0xFF;
#endif

  switch(CoreId)
  {
[!VAR "SupEntExistPerCore" = "false()"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
    [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
      [!VAR "SupEntExistPerCore" = "true()"!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "$SupEntExistPerCore"!]
    case [!"$index_i"!]: LocalMode = WdgM_EB_CoreSwitchMode_Core[!"$index_i"!];
      break;
  [!ENDIF!][!/* IF $SupEntExistPerCore */!]
  [!VAR "SupEntExistPerCore" = "false()"!]
[!ENDFOR!]
     /* CHECK: NOPARSE */
    default: WDGM_UNREACHABLE_CODE_ASSERT(WDGM_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE*/
  }

  return LocalMode;
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, WDGM_CODE) WdgM_EB_AllCoresSameMode(void)
{
  boolean AllCoresSameMode = TRUE;

[!VAR "SlaveWdgMSE" = "false()"!][!//
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!//
  [!IF "$index_i != $WDGM_MASTER_CORE_ID"!][!//
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SlaveWdgMSE" = "true()"!][!//
      [!ENDIF!][!//
      [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//

[!IF "$SlaveWdgMSE"!]
  if(
  [!VAR "FirstSupEnt" = "true()"!]
  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
      [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
        [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
          [!VAR "SupEntExistPerCore" = "true()"!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$SupEntExistPerCore"!]
        [!IF "$FirstSupEnt = 'false'"!]
    ||
        [!ENDIF!]
    (WdgM_EB_CoreSwitchMode_Core[!"$WDGM_MASTER_CORE_ID"!] != WdgM_EB_CoreSwitchMode_Core[!"num:i($index_i)"!])
        [!VAR "FirstSupEnt" = "false()"!]
      [!ENDIF!]
      [!VAR "SupEntExistPerCore" = "false()"!]
    [!ENDIF!]
  [!ENDFOR!]
  )
  {
    AllCoresSameMode = FALSE;
  }
[!ENDIF!]

  return AllCoresSameMode;
}

FUNC(boolean, WDGM_CODE) WdgM_EB_CheckSatelliteInitStatus(void)
{
  boolean AllSatellitesSameInit = TRUE;

[!VAR "SlaveWdgMSE" = "false()"!][!//
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!//
  [!IF "$index_i != $WDGM_MASTER_CORE_ID"!][!//
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
        [!VAR "SlaveWdgMSE" = "true()"!][!//
      [!ENDIF!][!//
      [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//

[!IF "$SlaveWdgMSE"!]
  if(
  [!VAR "FirstSupEnt" = "true()"!]
  [!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
    [!IF "$index_i != $WDGM_MASTER_CORE_ID"!]
      [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
        [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!//
          [!VAR "SupEntExistPerCore" = "true()"!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$SupEntExistPerCore"!]
        [!IF "$FirstSupEnt = 'false'"!]
    ||
        [!ENDIF!]
    (WdgM_EB_InitStatus_Core[!"$WDGM_MASTER_CORE_ID"!] != WdgM_EB_InitStatus_Core[!"num:i($index_i)"!])
        [!VAR "FirstSupEnt" = "false()"!]
      [!ENDIF!]
      [!VAR "SupEntExistPerCore" = "false()"!]
    [!ENDIF!]
  [!ENDFOR!]
  )
  {
    AllSatellitesSameInit = FALSE;
  }
[!ENDIF!]

  return AllSatellitesSameInit;
}

#define WDGM_STOP_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>

[!IF "$DefaultServiceAPI = 'NONE'"!][!//
  [!FOR "Index" = "0" TO "$MULTICORE_NUM_CORES - 1"!]
    [!IF "$Index != $WDGM_MASTER_CORE_ID"!]
      [!VAR "SupEntExistPerCore" = "false()"!][!//
      [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
        [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Index)"!][!//
          [!VAR "SupEntExistPerCore" = "true()"!][!//
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$SupEntExistPerCore"!][!//
#define WDGM_1_CORE_[!"num:i($Index)"!]_START_SEC_CODE_ASIL_D
#include <WdgM_1_CORE_[!"num:i($Index)"!]_MemMap.h>
FUNC(void, WDGM_1_CORE_[!"num:i($Index)"!]_CODE) WdgM_1_CORE_[!"num:i($Index)"!]_MainFunction(void)
{
  WdgM_MainFunction();
}
#define WDGM_1_CORE_[!"num:i($Index)"!]_STOP_SEC_CODE_ASIL_D
#include <WdgM_1_CORE_[!"num:i($Index)"!]_MemMap.h>
      [!ENDIF!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]
[!ELSE!][!/* IF $WdgMMulticoreEnabled */!]

#define WDGM_START_SEC_VAR_CLEARED_ASIL_D_16
#include <WdgM_MemMap.h>

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable25,1 */
/** \brief Internal RAM data holding a copy of the alive counter values for each checkpoint */
/* Deviation MISRAC2012-3 */
VAR(WdgM_EB_CPInternalDataType, WDGM_VAR) WdgM_EB_IntRAMData[WDGM_EB_CHECKPOINTS_NUM];

/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable10,3 */
/** \brief failed reference cycle counter for the SE  */
/* Deviation MISRAC2012-3 */
VAR(uint16, WDGM_VAR) WdgM_EB_FailedAliveSupervisionRefCycleCnt[WDGM_EB_SE_NUM];

#define WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_16
#include <WdgM_MemMap.h>

#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_START_SEC_VAR_INIT_16
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

/** \brief WdgM global initialization status */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable15,3 */
/* Deviation MISRAC2012-3 */
VAR(WdgM_EB_InitStatusType, WDGM_VAR) WdgM_EB_InitStatus = WDGM_EB_INIT_STATUS_DEINIT;

#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_STOP_SEC_VAR_INIT_16
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
#endif

#define WDGM_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "node:exists(./WdgMOsApplicationRef)"!]
      [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
      [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
        [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
        [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]

/** \brief The WdgM specific context data.
 ** This variable holds the specific run time data of the WdgM. */
VAR(WdgM_EB_CoreContextType, WDGM_VAR) WdgM_EB_Context =
{
  WdgM_EB_SELocalStatus,
[!IF "$WdgMGetAllExpiredSEIDs = 'true'"!]
  WdgM_EB_ExpiredSEIDs,
  WDGM_EB_SE_NUM,
  &WdgM_EB_ExpiredSEIDsCounter,
[!ENDIF!]
  WdgM_EB_FailedAliveSupervisionRefCycleCnt,
  WdgM_EB_IntRAMData,
  &WdgM_EB_InitStatus,
  0U,
  0U,
  FALSE,
#if (WDGM_EB_CHECK_MAINFUNCTION_TIMING == STD_ON)
  0U,
#endif
  0U,
[!IF "$WdgMPartitionResetEnabled = 'true'"!][!//
  [!WS!][!WS!][!"num:i($WdgMNumOfPartitionsPerCore)"!]U,
  WdgM_EB_Core0PartitionSupervisionCycleCnt /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable30,1 */
[!ENDIF!][!//
};

#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

[!IF "$WdgMGetAllExpiredSEIDs = 'true'"!]
#define WDGM_START_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, WDGM_CODE) WdgM_EB_GetAllExpiredSEIDsHelper
(
  P2VAR(uint8, AUTOMATIC, WDGM_APPL_DATA) Counter,
  P2VAR(uint8, AUTOMATIC, WDGM_APPL_DATA) ExpiredSEIDs
)
{
  uint8 LocalIndex;
  uint8 LocalStoreIndex = 0U;
  Std_ReturnType RetVal;
  RetVal = E_OK;

  {
    WdgM_EB_SEIdType LocalExpiredCounter;
    Std_ReturnType RetValRedundantData;

    RetValRedundantData = WdgM_EB_GetCheckedRedundantData8 (WdgM_EB_ExpiredSEIDsCounter, &LocalExpiredCounter);
    if (RetValRedundantData != E_OK)
    {
      /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020468,1,WDGM.EB.TIMEPM.WDGM020475,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
      WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
      WDGM_EB_DET(WDGM_SID_GET_ALL_EXPIRED_SEID, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
      RetVal = E_NOT_OK;
    }
    else
    {
      for (LocalIndex = 0U; LocalIndex < LocalExpiredCounter; LocalIndex++)
      {
        WdgM_EB_SEIdType LocalExpiredSEID;
        Std_ReturnType localRetVal;
      
        localRetVal = WdgM_EB_GetCheckedRedundantData8 (WdgM_EB_ExpiredSEIDs[LocalIndex], &LocalExpiredSEID);
        if (localRetVal != E_OK)
        {
          /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020468,1,WDGM.EB.TIMEPM.WDGM020475,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
          WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
          WDGM_EB_DET(WDGM_SID_GET_ALL_EXPIRED_SEID, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
          RetVal = E_NOT_OK;
        }
        else
        {
          ExpiredSEIDs[LocalStoreIndex] = LocalExpiredSEID;
          LocalStoreIndex++;
        }
      }
    }
  }

  /* Return the number of expired supervised entities (if any) */
  *Counter = LocalStoreIndex;
  
  return RetVal;
}

FUNC(Std_ReturnType, WDGM_CODE) WdgM_EB_ResetAllExpiredSEIDs(void)
{
  uint8 LocalIndex;
  WdgM_EB_SEIdType LocalExpiredCounter;
  Std_ReturnType RetValRedundantData;
  Std_ReturnType RetVal;
  RetVal = E_OK;

  /* !LINKSTO WDGM.EB.Dbg4,1 */
  DBG_WDGM_EB_RESETALLEXPIREDSEIDS_ENTRY();

    RetValRedundantData = WdgM_EB_GetCheckedRedundantData8 (WdgM_EB_ExpiredSEIDsCounter, &LocalExpiredCounter);
    if (RetValRedundantData != E_OK)
    {
      /* !LINKSTO WDGM.EB.TIMEPM.WDGM020466,1,WDGM.EB.TIMEPM.WDGM020468,1,WDGM.EB.TIMEPM.WDGM020475,1 */
#if (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DEM)
      WDGM_EB_DEM(WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#elif (WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION == WDGM_PROD_ERR_REP_TO_DET)
      WDGM_EB_DET(WDGM_SID_GET_ALL_EXPIRED_SEID, WDGM_EB_E_DEMTODET_DATA_CORRUPTION);
#endif
      RetVal = E_NOT_OK;
    }
    else
    {
      for (LocalIndex = 0U; LocalIndex < LocalExpiredCounter; LocalIndex++)
      {
        WdgM_EB_StoreRedundantData8(&WdgM_EB_ExpiredSEIDs[LocalIndex], 0U);
      }
      WdgM_EB_StoreRedundantData8(&WdgM_EB_ExpiredSEIDsCounter, 0U);
    }

  /* !LINKSTO WDGM.EB.Dbg4,1 */
  DBG_WDGM_EB_RESETALLEXPIREDSEIDS_EXIT(RetVal);
  return RetVal;
}

#define WDGM_STOP_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>
[!ENDIF!]

[!ENDIF!][!/* IF $WdgMMulticoreEnabled */!]

[!IF "$WdgMPartitionResetEnabled = 'true'"!]
#define WDGM_START_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>
[!VAR "WdgMOsAppRefNameList" = "''"!][!//
[!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
  [!IF "node:exists(./WdgMOsApplicationRef)"!][!//
    [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!][!//
    [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!][!//
/** \brief
 **  List of internal IDs for all SEs mapped to [!"$WdgMOsAppRefName"!]
 **/
static VAR(WdgM_EB_SEIdType, WDGM_VAR) WdgM_EB_SE_[!"$WdgMOsAppRefName"!]_Mapping[WDGM_EB_NUM_SE_[!"$WdgMOsAppRefName"!]] = 
{
    [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!IF "as:name(as:ref(./WdgMOsApplicationRef)) = $WdgMOsAppRefName"!]
  [!"node:pos(.)"!], /* internal SEId of the [!"as:name(.)"!] SE */
        [!ENDIF!]
      [!ENDIF!]
    [!ENDLOOP!]
};

      [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_8
#include <WdgM_MemMap.h>

#define WDGM_START_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

[!VAR "WdgMOsAppRefNameList" = "''"!]
[!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
  [!IF "node:exists(./WdgMOsApplicationRef)"!]
    [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
    [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]

  [!VAR "WdgMNumOfSEPerPartition"="0"!][!//
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
      [!IF "node:exists(./WdgMOsApplicationRef)"!][!//
        [!IF "as:name(as:ref(./WdgMOsApplicationRef)) = $WdgMOsAppRefName"!][!//
            [!VAR "WdgMNumOfSEPerPartition" = "$WdgMNumOfSEPerPartition + 1"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
  [!ENDLOOP!][!//

/** \brief
 ** Holds information about SEs mapped to [!"$WdgMOsAppRefName"!] and their total number
 **/
/* Deviation MISRAC2012-2 */
static VAR(WdgM_EB_SE_Type, WDGM_VAR) WdgM_EB_SE_[!"$WdgMOsAppRefName"!] = 
{
  WdgM_EB_SE_[!"$WdgMOsAppRefName"!]_Mapping, /* List of SEs mapped to OsApplication */
  [!WS!][!WS!][!"num:i($WdgMNumOfSEPerPartition)"!]U  /* total number of SEs mapped to OsApplication */
};

      [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]

#define WDGM_STOP_SEC_VAR_INIT_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>
[!ENDIF!]

#if (WDGM_EB_PARTITIONING_ENABLED == STD_ON)
[!IF "$WdgMMulticoreEnabled = 'true'"!]
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020308,1 */
#define WDGM_START_SEC_VAR_CLEARED_SHARED_MC_UNSPECIFIED
#include <WdgM_MemMap.h>
[!ELSE!][!/* IF $WdgMMulticoreEnabled */!][!//
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020304,2 */
#define WDGM_START_SEC_VAR_CLEARED_SHARED_UNSPECIFIED
#include <WdgM_MemMap.h>
[!ENDIF!]
#else
#define WDGM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#endif

#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
#if (WDGM_EB_EXTERNAL_GRAPH_NUM > 0U)
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable12,1,WDGM.EB.DesignDecision.InternalVariable13,1 */
VAR(WdgM_EB_GraphDataType,WDGM_VAR) WdgM_EB_ExternalGraphData[WDGM_EB_EXTERNAL_GRAPH_NUM];
[!FOR "index_i" = "0" TO "num:i($NumberOfExternalGraphs)-1"!][!//
/** \brief run-time data for each external graph to store the sequence
  *  number of checkpoint for each supervised entity */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable16,1 */
static VAR(WdgM_EB_ExtGraphDataSeqArrayType, WDGM_VAR) WdgM_EB_ExtGraphDataSeq_[!"num:i($index_i)"!][WDGM_EB_SE_NUM_GRAPHID_[!"num:i($index_i)"!]];

[!ENDFOR!][!//
#else
VAR(WdgM_EB_GraphDataType,WDGM_VAR) WdgM_EB_ExternalGraphData[1];
#endif

#if (WDGM_EB_INTERNAL_GRAPH_NUM > 0U)
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable6,2,WDGM.EB.DesignDecision.InternalVariable7,2 */
VAR(WdgM_EB_GraphDataType,WDGM_VAR) WdgM_EB_InternalGraphData[WDGM_EB_INTERNAL_GRAPH_NUM];
#else
VAR(WdgM_EB_GraphDataType,WDGM_VAR) WdgM_EB_InternalGraphData[1];
#endif
#endif

#if (WDGM_EB_PARTITIONING_ENABLED == STD_ON)
[!IF "$WdgMMulticoreEnabled = 'true'"!]
#define WDGM_STOP_SEC_VAR_CLEARED_SHARED_MC_UNSPECIFIED
#include <WdgM_MemMap.h>
[!ELSE!][!/* IF $WdgMMulticoreEnabled */!][!//
#define WDGM_STOP_SEC_VAR_CLEARED_SHARED_UNSPECIFIED
#include <WdgM_MemMap.h>
[!ENDIF!]
#else
#define WDGM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#endif

#define WDGM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

#if (WDGM_EB_EXTERNAL_GRAPH_NUM > 0U)
/** \brief array of pointers to the run-time data for each external graph and length of the pointed arrays */
CONST(WdgM_EB_ExtGraphDataSeqType,WDGM_CONST) WdgM_EB_ExtGraphDataSeqPtr[WDGM_EB_EXTERNAL_GRAPH_NUM] =
{
[!FOR "index_i" = "0" TO "num:i($NumberOfExternalGraphs)-1"!][!//
 /* pointer to the run-time data for each external graph and length of the array */
 { &WdgM_EB_ExtGraphDataSeq_[!"num:i($index_i)"!][0], WDGM_EB_SE_NUM_GRAPHID_[!"num:i($index_i)"!] },
[!ENDFOR!][!//
};
#endif

#define WDGM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

/*==================[external function definitions]==============================================*/
[!IF "$WdgMPartitionResetEnabled = 'true'"!]
#define WDGM_START_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>

FUNC(uint8, WDGM_CODE) WdgM_EB_GetPartitionIndex
(
  P2VAR(WdgM_EB_CoreContextType, AUTOMATIC, WDGM_APPL_CONST) CoreInstance,
  ApplicationType PartitionId
)
{
  uint8 RetVal = 0xFFU;
  uint8 CorePartitionIdx;

[!IF "$WdgMMulticoreEnabled = 'true'"!]
  WdgM_EB_CoreIdType localCoreID = CoreInstance->CoreID;

  switch(localCoreID)
  {
[!FOR "Index" = "0" TO "$MULTICORE_NUM_CORES - 1"!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Index)"!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!][!//
    case [!"num:i($Index)"!]:
    {
      for (CorePartitionIdx = 0; CorePartitionIdx < CoreInstance->NumOsPartitions; CorePartitionIdx++)
      {
        if (PartitionId == WdgM_EB_Core[!"num:i($Index)"!]PartitionId[CorePartitionIdx])
        {
          RetVal = CorePartitionIdx;
        }
      }
      break;
    }
[!ENDIF!]
[!ENDFOR!]
    /* CHECK: NOPARSE */
    default:
      WDGM_UNREACHABLE_CODE_ASSERT(WDGM_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE */
  }
[!ELSE!][!/* IF $WdgMMulticoreEnabled */!][!//
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
  [!ENDLOOP!]
[!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!][!//
    for (CorePartitionIdx = 0; CorePartitionIdx < CoreInstance->NumOsPartitions; CorePartitionIdx++)
    {
      if (PartitionId == WdgM_EB_Core0PartitionId[CorePartitionIdx])
      {
        RetVal = CorePartitionIdx;
      }
    }
[!ENDIF!]
[!ENDIF!]

  return RetVal;
}

FUNC(ApplicationType, WDGM_CODE) WdgM_EB_GetPartitionId
(
  WdgM_EB_CoreIdType CoreId,
  ApplicationType PartitionIndex
)
{
  ApplicationType ApplicationId = INVALID_OSAPPLICATION;

  switch(CoreId)
  {
  [!FOR "Index" = "0" TO "$MULTICORE_NUM_CORES - 1"!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Index)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
            [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!]
    case [!"num:i($Index)"!]:
    {
      ApplicationId = WdgM_EB_Core[!"num:i($Index)"!]PartitionId[PartitionIndex];
      break;
    }
  [!ENDIF!]
  [!ENDFOR!]
    /* CHECK: NOPARSE */
    default:
      WDGM_UNREACHABLE_CODE_ASSERT(WDGM_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE */
  }

  return ApplicationId;
}

FUNC(ApplicationType, WDGM_CODE) WdgM_EB_GetPartitionStatus
(
  WdgM_EB_CoreIdType CoreId,
  ApplicationType PartitionIndex
)
{
  uint8 PartitionStatus = 0xFF;

  switch(CoreId)
  {
  [!FOR "Index" = "0" TO "$MULTICORE_NUM_CORES - 1"!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Index)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
            [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!]
    case [!"num:i($Index)"!]:
    {
      /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable29,1 */
      PartitionStatus = WdgM_EB_Core[!"num:i($Index)"!]_PartitionStatus[PartitionIndex];
      break;
    }
  [!ENDIF!]
  [!ENDFOR!]
    /* CHECK: NOPARSE */
    default:
      WDGM_UNREACHABLE_CODE_ASSERT(WDGM_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE */
  }

  return PartitionStatus;
}

FUNC(void, WDGM_CODE) WdgM_EB_SetPartitionStatus
(
  WdgM_EB_CoreIdType WdgMCoreId,
  ApplicationType PartitionIndex,
  uint8 PartitionStatus
)
{
  switch(WdgMCoreId)
  {
  [!FOR "Index" = "0" TO "$MULTICORE_NUM_CORES - 1"!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
    [!IF "$WdgMMulticoreEnabled = 'true'"!]
      [!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Index)"!]
        [!IF "node:exists(./WdgMOsApplicationRef)"!]
          [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
          [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
            [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
            [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "node:exists(./WdgMOsApplicationRef)"!]
        [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
        [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
          [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
          [!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "num:i($WdgMNumOfPartitionsPerCore) != 0"!]
    case [!"num:i($Index)"!]:
    {
      WdgM_EB_Core[!"num:i($Index)"!]_PartitionStatus[PartitionIndex] = PartitionStatus;
      break;
    }
  [!ENDIF!]
  [!ENDFOR!]
    /* CHECK: NOPARSE */
    default:
      WDGM_UNREACHABLE_CODE_ASSERT(WDGM_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE */
  }
}

FUNC_P2VAR(WdgM_EB_SEIdType, WDGM_APPL_DATA, WDGM_CODE) WdgM_EB_GetSEfromOsApp
(
  ApplicationType ApplicationId,
  P2VAR(uint8, AUTOMATIC, WDGM_APPL_DATA) Size
)
{
  P2VAR(WdgM_EB_SEIdType, AUTOMATIC, WDGM_APPL_CONST) SEPtr = NULL_PTR;

  switch(ApplicationId)
  {
[!VAR "WdgMOsAppRefNameList" = "''"!]
[!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!]
  [!IF "node:exists(./WdgMOsApplicationRef)"!]
  [!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!]
    [!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!]
    case [!"$WdgMOsAppRefName"!]:
    {
      SEPtr = &WdgM_EB_SE_[!"$WdgMOsAppRefName"!].WdgM_EB_SE[0U];
      *Size = WdgM_EB_SE_[!"$WdgMOsAppRefName"!].WdgM_EB_Size;
      break;
    }
    [!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]
    /* CHECK: NOPARSE */
    default:
      WDGM_UNREACHABLE_CODE_ASSERT(WDGM_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE */
  }

  return SEPtr;
}

#define WDGM_STOP_SEC_CODE_ASIL_D
#include <WdgM_MemMap.h>
[!ENDIF!][!//
/*==================[internal function definitions]==============================================*/

/*==================[end of file]================================================================*/
[!ENDCODE!][!//
