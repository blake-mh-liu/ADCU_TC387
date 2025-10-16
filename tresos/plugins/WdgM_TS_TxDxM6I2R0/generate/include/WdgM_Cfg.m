[!/**
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
 */!][!//
[!NOCODE!][!//

[!// Included by generated pre-compile time configuration file



[!IF "not(var:defined('WDGM_CFG_M'))"!]
[!VAR "WDGM_CFG_M"="'true'"!]

[!// EXPORTED VARIABLES (boolean parameters) -------------------------------------------------------

[!VAR "BswCompatibilityMode" = "node:value(WdgMGeneral/WdgMBSWCompatibilityMode)"!]
[!VAR "DevErrorDetectEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMDevErrorDetect)"!]
[!VAR "VersionInfoApiEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMVersionInfoApi)"!]
[!VAR "DemStoppedSupervisionReportEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMDemStoppedSupervisionReport)"!]
[!VAR "ImmediateResetEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMImmediateReset)"!]
[!VAR "OffModeEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMOffModeEnabled)"!]
[!VAR "RteUsageEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMRteUsage)"!]
[!VAR "DefensiveBehaviorEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMDefensiveBehavior)"!]
[!VAR "CallerIdsEnabled" = "node:exists(WdgMGeneral/WdgMCallerIds)"!]
[!VAR "SleepModeEnabled" = "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMSleepMode)"!]
[!VAR "ServiceAPIEnabled" = "node:exists(WdgMGeneral/WdgMServiceAPI)"!]
[!VAR "SupervisorCalloutsEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts)"!]
[!VAR "GetExpectedInitStateCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetExpectedInitStateCallout)"!]
[!VAR "GetExpectedWdgMModeCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetExpectedWdgMModeCallout)"!]
[!VAR "GetTimeCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetElapsedTimeCallout)"!]
[!VAR "MainFunctionViolationCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMMainFunctionViolationCallout)"!]
[!VAR "SatelliteAlivenessCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMSatelliteAlivenessCallout)"!]
[!VAR "IsPerformResetCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMIsPerformResetCallout)"!]
[!VAR "SupervisionExpiredCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMSupervisionExpiredCallout)"!]
[!VAR "IndividualModeSwitchCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMIndividualModeSwitchCallout)"!]
[!VAR "GlobalModeSwitchCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMGlobalModeSwitchCallout)"!]
[!VAR "DetCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMDetCallout)"!]
[!VAR "WdgMPartitioningEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMPartitioningEnabled)"!]
[!VAR "WdgMMulticoreEnabled" = "node:exists(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores) and as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores > 1"!]
[!VAR "WdgMSetModeSynchronEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMSetModeSynchron)"!]
[!VAR "WdgMGetAllExpiredSEIDs" = "node:existsAndTrue(WdgMGeneral/WdgMGetAllExpiredSEIDs)"!]
[!VAR "WdgMGetFirstExpiredEnable" = "node:existsAndTrue(WdgMGeneral/WdgMGeneralMulticore/WdgMGetFirstExpiredEnable)"!]
[!VAR "RequestPartitionResetCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMRequestPartitionResetCallout)"!]
[!VAR "GetApplicationStateCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetApplicationStateCallout)"!]

[!VAR "WdgMTriggerWdgDriverMulticore" = "'false'"!]
[!LOOP "as:modconf('WdgM')[1]/WdgMConfigSet[1]/eb-list::*/WdgMMode/eb-list::*/WdgMTrigger/eb-list::*"!]
  [!IF "(node:existsAndTrue(as:ref(WdgMTriggerWatchdogRef)/WdgMMulticoreWdgEnable)) or node:exists(as:ref(WdgMTriggerWatchdogRef)/WdgMMulticoreWdgCoreId)"!]
    [!VAR "WdgMTriggerWdgDriverMulticore" = "'true'"!]
  [!ENDIF!]
[!ENDLOOP!]

[!IF "$ServiceAPIEnabled"!]
[!VAR "ActivateAliveSupervisionAPIEnabled" = "node:exists(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR32ActivateAliveSupervisionAPI)"!]
[!VAR "DeactivateAliveSupervisionAPIEnabled" = "node:exists(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR32DeactivateAliveSupervisionAPI)"!]
[!VAR "ASR32ServiceAPIEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR32ServiceAPI)"!]
[!VAR "ASR40ServiceAPIEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR40ServiceAPI)"!]
[!VAR "ASR43ServiceAPIEnabled" = "node:existsAndTrue(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR43ServiceAPI)"!]
[!VAR "DefaultServiceAPI" = "node:value(WdgMGeneral/WdgMServiceAPI/WdgMDefaultASRServiceAPI)"!]

[!ELSE!]
[!VAR "ASR32ServiceAPIEnabled" = "'false'"!]
[!VAR "ASR40ServiceAPIEnabled" = "'false'"!]
[!VAR "ASR43ServiceAPIEnabled" = "'false'"!]
[!VAR "ActivateAliveSupervisionAPIEnabled" = "'false'"!]
[!VAR "DeactivateAliveSupervisionAPIEnabled" = "'false'"!]
[!VAR "DefaultServiceAPI" = "'NONE'"!]
[!ENDIF!]

[!IF "$SupervisorCalloutsEnabled"!]
[!VAR "InitRedirectionCalloutAPIEnabled" = "not(node:empty(WdgMGeneral/WdgMSupervisorCallouts/WdgMInitRedirectionCallout))"!]
[!VAR "DeInitRedirectionCalloutAPIEnabled" = "not(node:empty(WdgMGeneral/WdgMSupervisorCallouts/WdgMDeInitRedirectionCallout))"!]
[!VAR "SetModeRedirectionCalloutAPIEnabled" = "not(node:empty(WdgMGeneral/WdgMSupervisorCallouts/WdgMSetModeRedirectionCallout))"!]
[!ELSE!]
[!VAR "InitRedirectionCalloutAPIEnabled" = "'false'"!]
[!VAR "DeInitRedirectionCalloutAPIEnabled" = "'false'"!]
[!VAR "SetModeRedirectionCalloutAPIEnabled" = "'false'"!]
[!ENDIF!]

[!VAR "NumberOfWdgModes" = "num:i(count(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*))"!]
[!VAR "NumberOfWdgDrivers" = "num:i(count(WdgMGeneral/WdgMWatchdog/eb-list::*))"!]
[!IF "$CallerIdsEnabled = 'true'"!]
[!VAR "NumberOfCallerIds" = "num:i(count(WdgMGeneral/WdgMCallerIds/WdgMCallerId/eb-list::*))"!]
[!ELSE!]
[!VAR "NumberOfCallerIds" = "num:i(0)"!]
[!ENDIF!]

[!// Number of optimized external graphs is sum of optimized configured external graphs (for all WdgM modes)
[!VAR "OptimizedExternalGraphsEnabled" = "num:i(count(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*/WdgMExternalLogicalSupervision/eb-list::*[node:existsAndTrue(WdgMExtLogicalOptimization) and (num:i(count(WdgMExternalTransition/eb-list::*)) > 0)]))"!]

[!// Number of internal graphs is sum of configured internal graphs (for all WdgM modes)
[!VAR "NumberOfInternalGraphs" = "num:i(count(WdgMGeneral/WdgMSupervisedEntity/eb-list::*[num:i(count(WdgMInternalTransition/eb-list::*))>0]))"!]

[!// Number of external graphs is sum of configured external graphs (for all WdgM modes)
[!VAR "NumberOfExternalGraphs" = "num:i(count(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*/WdgMExternalLogicalSupervision/eb-list::*))"!]

[!// Number of DMs is sum of configured deadline supervision configs (for all WdgM modes)
[!VAR "NumberOfDMs" = "num:i(count(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*/WdgMDeadlineSupervision/eb-list::*))"!]

[!// EXPORTED VARIABLES (string parameters) --------------------------------------------------------

[!IF "$ActivateAliveSupervisionAPIEnabled"!]
[!VAR "ActivateAliveSupervisionAPIName" = "node:value(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR32ActivateAliveSupervisionAPI)"!]
[!ELSE!]
[!VAR "ActivateAliveSupervisionAPIName" = "''"!]
[!ENDIF!]

[!IF "$DeactivateAliveSupervisionAPIEnabled"!]
[!VAR "DeactivateAliveSupervisionAPIName" = "node:value(WdgMGeneral/WdgMServiceAPI/WdgMEnableASR32DeactivateAliveSupervisionAPI)"!]
[!ELSE!]
[!VAR "DeactivateAliveSupervisionAPIName" = "''"!]
[!ENDIF!]

[!IF "$InitRedirectionCalloutAPIEnabled"!]
[!VAR "InitRedirectionCalloutAPIName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMInitRedirectionCallout)"!]
[!ELSE!]
[!VAR "InitRedirectionCalloutAPIName" = "''"!]
[!ENDIF!]

[!IF "$DeInitRedirectionCalloutAPIEnabled"!]
[!VAR "DeInitRedirectionCalloutAPIName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMDeInitRedirectionCallout)"!]
[!ELSE!]
[!VAR "DeInitRedirectionCalloutAPIName" = "''"!]
[!ENDIF!]

[!IF "$SetModeRedirectionCalloutAPIEnabled"!]
[!VAR "SetModeRedirectionCalloutAPIName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMSetModeRedirectionCallout)"!]
[!ELSE!]
[!VAR "SetModeRedirectionCalloutAPIName" = "''"!]
[!ENDIF!]

[!IF "$GetExpectedInitStateCalloutEnabled"!]
[!VAR "GetExpectedInitStateCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetExpectedInitStateCallout)"!]
[!ELSE!]
[!VAR "GetExpectedInitStateCalloutName" = "''"!]
[!ENDIF!]

[!IF "$GetExpectedWdgMModeCalloutEnabled"!]
[!VAR "GetExpectedWdgMModeCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetExpectedWdgMModeCallout)"!]
[!ELSE!]
[!VAR "GetExpectedWdgMModeCalloutName" = "''"!]
[!ENDIF!]

[!IF "$GetTimeCalloutEnabled"!]
[!VAR "GetTimeCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetElapsedTimeCallout)"!]
[!VAR "TimeGranularity" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMTimeGranularity)"!]
[!VAR "MainFunctionCycleTime" = "num:i(round(num:f(num:div(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*[1]/WdgMSupervisionCycle, WdgMGeneral/WdgMSupervisorCallouts/WdgMTimeGranularity))))"!]
[!IF "$MainFunctionCycleTime = 0"!]
[!VAR "MainFunctionCycleTime" = "num:i(1)"!]
[!ENDIF!]
[!VAR "MainFunctionToleranceTime" = "num:i(round(num:f(num:div(node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMMainFunctionPeriodTolerance),node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMTimeGranularity)))))"!]
[!ELSE!]
[!VAR "GetTimeCalloutName" = "''"!]
[!VAR "TimeGranularity" = "num:i(0)"!]
[!VAR "MainFunctionCycleTime" = "num:i(0)"!]
[!VAR "MainFunctionToleranceTime" = "num:i(0)"!]
[!ENDIF!]

[!IF "$MainFunctionViolationCalloutEnabled"!]
[!VAR "MainFunctionViolationCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMMainFunctionViolationCallout)"!]
[!ELSE!]
[!VAR "MainFunctionViolationCalloutName" = "''"!]
[!ENDIF!]

[!IF "$WdgMMulticoreEnabled"!]
  [!IF "$SatelliteAlivenessCalloutEnabled"!]
    [!VAR "SatelliteAlivenessCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMSatelliteAlivenessCallout)"!]
    [!VAR "SatelliteAlivenessPeriodCheck" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMSatelliteAlivenessPeriodCheck)"!]
    [!VAR "SatelliteAlivenessCoreIdDisable" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMSatelliteAlivenessCoreIdDisable)"!]
  [!ELSE!]
    [!VAR "SatelliteAlivenessCalloutName" = "''"!]
    [!VAR "SatelliteAlivenessPeriodCheck" = "num:i(0)"!]
    [!VAR "SatelliteAlivenessCoreIdDisable" = "'false'"!]
  [!ENDIF!]
[!ENDIF!]

[!IF "$IsPerformResetCalloutEnabled"!]
[!VAR "IsPerformResetCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMIsPerformResetCallout)"!]
[!ELSE!]
[!VAR "IsPerformResetCalloutName" = "''"!]
[!ENDIF!]

[!IF "$SupervisionExpiredCalloutEnabled"!]
[!VAR "SupervisionExpiredCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMSupervisionExpiredCallout)"!]
[!ELSE!]
[!VAR "SupervisionExpiredCalloutName" = "''"!]
[!ENDIF!]

[!IF "$IndividualModeSwitchCalloutEnabled"!]
[!VAR "IndividualModeSwitchCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMIndividualModeSwitchCallout)"!]
[!ELSE!]
[!VAR "IndividualModeSwitchCalloutName" = "''"!]
[!ENDIF!]

[!IF "$GlobalModeSwitchCalloutEnabled"!]
[!VAR "GlobalModeSwitchCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGlobalModeSwitchCallout)"!]
[!ELSE!]
[!VAR "GlobalModeSwitchCalloutName" = "''"!]
[!ENDIF!]

[!IF "$DetCalloutEnabled"!]
[!VAR "DetCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMDetCallout)"!]
[!ELSE!]
[!VAR "DetCalloutName" = "''"!]
[!ENDIF!]

[!IF "$RequestPartitionResetCalloutEnabled"!]
[!VAR "RequestPartitionResetCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMRequestPartitionResetCallout)"!]
[!ELSE!]
[!VAR "RequestPartitionResetCalloutName" = "''"!]
[!ENDIF!]

[!IF "$GetApplicationStateCalloutEnabled"!]
[!VAR "GetApplicationStateCalloutName" = "node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetApplicationStateCallout)"!]
[!ELSE!]
[!VAR "GetApplicationStateCalloutName" = "''"!]
[!ENDIF!]

[!IF "$WdgMMulticoreEnabled"!]
[!VAR "GetCoreIdCalloutEnabled" = "node:exists(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetCoreIdCallout)"!]
   [!IF "$GetCoreIdCalloutEnabled"!]
   [!VAR "GetCoreIdCalloutName" = "concat(node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetCoreIdCallout),'()')"!]
   [!VAR "GetCoreIdCalloutNameExtern" = "concat(node:value(WdgMGeneral/WdgMSupervisorCallouts/WdgMGetCoreIdCallout),'(void)')"!]
   [!ELSE!]
   [!VAR "GetCoreIdCalloutName" = "'((WdgM_EB_CoreIdType)GetCoreID())'"!]
   [!ENDIF!]
[!VAR "WdgMNumberOfCores" = "as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores"!]
[!VAR "WdgMMasterCoreId" = "as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMMasterCoreId"!]
[!VAR "WdgMMasterWaitSlaveModeSwitch" = "node:value(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMMasterWaitSlaveModeSwitch)"!]
[!ELSE!]
[!VAR "GetCoreIdCalloutEnabled" = "''"!]
[!VAR "GetCoreIdCalloutName" = "'0U'"!]
[!VAR "WdgMNumberOfCores" = "'1'"!]
[!VAR "WdgMMasterCoreId" = "'0'"!]
[!VAR "WdgMMasterWaitSlaveModeSwitch" = "'0'"!]
[!ENDIF!]

[!VAR "WdgMExpiredAPI" = "'true'"!]
[!IF "$WdgMMulticoreEnabled"!]
  [!VAR "NumberOfSupervisedEntities" = "num:i(count(WdgMGeneral/WdgMSupervisedEntity/eb-list::*))"!]
  [!VAR "NumberOfSupEntPerCore"="0"!]
  [!IF "$WdgMGetFirstExpiredEnable"!]
    [!VAR "WdgMExpiredAPI" = "'true'"!]
  [!ELSE!]
    [!VAR "WdgMExpiredAPI" = "'false'"!]
  [!ENDIF!]
  [!MACRO "GetNumSEPerCore", "Core"!][!/*
  */!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
      */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Core)"!][!/*
          */!][!VAR "NumberOfSupEntPerCore" = "$NumberOfSupEntPerCore + 1"!][!/*
      */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!"num:i($NumberOfSupEntPerCore)"!][!/*
  */!][!VAR "NumberOfSupEntPerCore" = "0"!][!/*
*/!][!ENDMACRO!]
[!ELSE!]
  [!VAR "NumberOfSupervisedEntities" = "num:i(count(WdgMGeneral/WdgMSupervisedEntity/eb-list::*))"!]
[!ENDIF!]

[!VAR "WdgMPartitionResetEnabled"="'false'"!]
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
    */!][!IF "node:exists(WdgMOsApplicationRef)"!][!/*
        */!][!VAR "WdgMPartitionResetEnabled"="'true'"!][!/*
    */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

*/!][!VAR "WdgMMixedCriticalityEnabled"="'false'"!][!/*
*/!][!IF "(node:existsAndTrue(as:modconf('WdgM')[1]/WdgMGeneral/WdgMMixedSafetyCriticalityEnabled))"!][!/*
    */!][!VAR "WdgMMixedCriticalityEnabled"="'true'"!][!/*
*/!][!ENDIF!][!/*

[!IF "$WdgMPartitionResetEnabled = 'true'"!]
  */!][!VAR "WdgMOsAppRefNameList" = "''"!][!/*
  */!][!VAR "WdgMNumOfPartitions"="0"!][!/*
  */!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
      */!][!IF "node:exists(./WdgMOsApplicationRef)"!][!/*
          */!][!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!][!/*
          */!][!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!][!/*
            */!][!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!][!/*
            */!][!VAR "WdgMNumOfPartitions" = "$WdgMNumOfPartitions + 1"!][!/*
          */!][!ENDIF!][!/*
      */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
[!ENDIF!]

[!/* Macro used to retrieve the number of Os Partitions mapped to a WdgM Core */!]
  [!VAR "WdgMOsAppRefNameList" = "''"!]
  [!VAR "WdgMNumOfPartitionsPerCore"="0"!]
  [!MACRO "GetNumOsPartitionsPerCore", "Core"!][!/*
  */!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
      */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Core)"!][!/*
        */!][!IF "node:exists(./WdgMOsApplicationRef)"!][!/*
            */!][!VAR "WdgMOsAppRefName"="as:name(as:ref(./WdgMOsApplicationRef))"!][!/*
            */!][!IF "not(contains($WdgMOsAppRefNameList,concat(' ',$WdgMOsAppRefName,' ')))"!][!/*
              */!][!VAR "WdgMOsAppRefNameList" = "concat($WdgMOsAppRefNameList,' ',$WdgMOsAppRefName,' ')"!][!/*
              */!][!VAR "WdgMNumOfPartitionsPerCore" = "$WdgMNumOfPartitionsPerCore + 1"!][!/*
            */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!"num:i($WdgMNumOfPartitionsPerCore)"!][!/*
  */!][!VAR "WdgMNumOfPartitionsPerCore"="0"!][!/*
*/!][!ENDMACRO!]

[!IF "$WdgMMulticoreEnabled"!]
  [!VAR "NumberOfCheckpoints"="num:i(count(WdgMGeneral/WdgMSupervisedEntity/eb-list::*/WdgMCheckpoint/eb-list::*))"!]
  [!VAR "NumberOfCheckpointsPerCore" = "0"!]
  [!MACRO "GetNumOfCheckpointsPerCore", "Core"!][!/*
  */!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
      */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Core)"!][!/*
          */!][!LOOP "WdgMCheckpoint/eb-list::*"!][!/*
              */!][!VAR "NumberOfCheckpointsPerCore" = "$NumberOfCheckpointsPerCore + 1"!][!/*
          */!][!ENDLOOP!][!/*
      */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!"num:i($NumberOfCheckpointsPerCore)"!][!/*
  */!][!VAR "NumberOfCheckpointsPerCore" = "0"!][!/*
*/!][!ENDMACRO!]
[!ELSE!]
  [!/* Number of Alive Supervisions equals number of Checkpoints) */!]
  [!VAR "NumberOfCheckpoints" = "num:i(count(WdgMGeneral/WdgMSupervisedEntity/eb-list::*/WdgMCheckpoint/eb-list::*))"!]
[!ENDIF!]

[!IF "$WdgMMulticoreEnabled"!]
[!VAR "WdgMMasterPositionInGlobalInitStatus" = "bit:shl(1,$WdgMMasterCoreId)"!]
[!VAR "WdgMAllCoresInitialized" = "num:i(0)"!]
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!]
  [!VAR "WdgMAllCoresInitialized" = "bit:or($WdgMAllCoresInitialized,bit:shl(1,$index_i))"!]
[!ENDFOR!]
[!ENDIF!]

[!/* This macro is used to generate the mapping index betwen the SEs and CPs which are part of an external graph  */!][!//

[!MACRO "GetSEIndexMapped", "SEIdCPIdModeId"!][!/*
    */!][!VAR "tmpDest"!][!ENDVAR!][!/*
    */!][!VAR "LocalVarForCheckDest"!][!ENDVAR!][!/*
    */!][!VAR "LocalVarForCheckSameSEId"!][!ENDVAR!][!/*

    */!][!/* go trough all modes */!][!/*
    */!][!LOOP "util:distinct(node:order(as:modconf('WdgM')[1]/WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!/*
        */!][!VAR "Local_WdgMModeId" = "num:i(WdgMModeId)"!][!/*

        */!][!/* go trough all external logical supervision */!][!/*
        */!][!LOOP "WdgMExternalLogicalSupervision/eb-list::*"!][!/*
            */!][!VAR "index_j" = "0"!][!/*
            */!][!VAR "tmpSameId" = "num:i(as:ref(./WdgMExternalCheckpointInitialRef/eb-list::*[1])/../../WdgMSupervisedEntityId)"!][!/*

           */!][!/* get all initial checkpoint references and save the SEId, CPId, ModeId and the index (the index indicates
                at what position must be written the sequence number in WdgM_EB_ExtGraphDataSeq_GRAPHID array) */!][!/*
            */!][!LOOP "WdgMExternalCheckpointInitialRef/eb-list::*"!][!/*

                */!][!VAR "FlagFindSameId" = "0"!][!/*
                */!][!/* LocalVarForCheckSameSEId variable is used to store the current SEId */!][!/*
                */!][!VAR "LocalVarForCheckSameSEId"!][!"num:i(as:ref(.)/../../WdgMSupervisedEntityId)"!][!ENDVAR!][!/*
                */!][!VAR "IndexIFtmpSameId" = "0"!][!/*

                */!][!/* go trough all tmpSameId elements and check if current SEId is already in the tmpSameId */!][!/*
                */!][!LOOP "text:split($tmpSameId,';')"!][!/*
                    */!][!IF "number(.) = $LocalVarForCheckSameSEId"!][!/*
                        */!][!VAR "FlagFindSameId" = "1"!][!/*
                    */!][!ENDIF!][!/*
                */!][!ENDLOOP!][!/*

                */!][!/* if SEId is not found in tmpSameId, add to the tmpSameId current SEId */!][!/*
                */!][!IF "num:i($FlagFindSameId) = 0"!][!/*
                    */!][!VAR "tmpSameId"!][!"$tmpSameId"!];[!"$LocalVarForCheckSameSEId"!][!ENDVAR!][!/*

                */!][!/* if SEId is found in tmpSameId */!][!/*
                */!][!ELSE!][!/*
                    */!][!/* go trough all tmpDest elements and check if current SEId is already in the tmpDest */!][!/*
                    */!][!LOOP "text:split($tmpDest,';')"!][!/*
                        */!][!LOOP "text:split(.,'-')"!][!/*
                            */!][!IF "number(.) = $LocalVarForCheckSameSEId"!][!/*
                                */!][!VAR "Flag" = "1"!][!/*
                            */!][!ENDIF!][!/*

                            */!][!/* if current SEId is already in tmpDest, get the index */!][!/*
                            */!][!IF "(. != num:i($LocalVarForCheckSameSEId)) and (num:i($Flag) = 1)"!][!/*
                                */!][!VAR "Flag" = "0"!][!/*
                                */!][!LOOP "text:split(.,'+')"!][!/*
                                    */!][!/* get the index */!][!/*
                                    */!][!VAR "IndexIFtmpSameId" = "."!][!/*
                                */!][!ENDLOOP!][!/*
                            */!][!ENDIF!][!/*
                        */!][!ENDLOOP!][!/*
                    */!][!ENDLOOP!][!/*
                */!][!ENDIF!][!/*

                */!][!/* if current SEId already in the list use the same index for current CP */!][!/*
                */!][!IF "num:i($FlagFindSameId) = 1"!][!/*
                    */!][!VAR "tmpDest"!][!"$tmpDest"!];[!"num:i(as:ref(.)/../../WdgMSupervisedEntityId)"!]-[!"num:i(as:ref(.)/WdgMCheckpointId)"!]:[!"num:i($Local_WdgMModeId)"!]+[!"num:i($IndexIFtmpSameId)"!][!ENDVAR!][!/*
                */!][!ELSE!][!/*
                    */!][!/* if current SEId is not in the tmpDest, increment index */!][!/*
                    */!][!VAR "index_j" = "$index_j + 1"!][!/*
                    */!][!VAR "tmpDest"!][!"$tmpDest"!];[!"num:i(as:ref(.)/../../WdgMSupervisedEntityId)"!]-[!"num:i(as:ref(.)/WdgMCheckpointId)"!]:[!"num:i($Local_WdgMModeId)"!]+[!"num:i($index_j)"!][!ENDVAR!][!/*
                */!][!ENDIF!][!/*

            */!][!ENDLOOP!][!/*

            */!][!/* go trough all external transition and save the SEId, CPId and ModeId */!][!/*
            */!][!LOOP "WdgMExternalTransition/eb-list::*"!][!/*
                */!][!VAR "FlagFindDestIntmpDest" = "0"!][!/*
                */!][!VAR "FlagFindSameId" = "0"!][!/*
                */!][!VAR "Flag" = "0"!][!/*
                */!][!VAR "IndexIFtmpSameId" = "0"!][!/*

                */!][!/* LocalVarForCheckDest variable is used to store the current SEId, CPId and ModeId */!][!/*
                */!][!VAR "LocalVarForCheckDest"!][!"num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId)"!]-[!"num:i(as:ref(WdgMExternalTransitionDestRef)/WdgMCheckpointId)"!]:[!"num:i($Local_WdgMModeId)"!][!ENDVAR!][!/*
                */!][!/* LocalVarForCheckSameSEId variable is used to store the current SEId */!][!/*
                */!][!VAR "LocalVarForCheckSameSEId"!][!"num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId)"!][!ENDVAR!][!/*

                */!][!/* go trough all tmpDest elements and check if current SEId, CPId and ModeId are already in the tmpDest */!][!/*
                */!][!LOOP "text:split($tmpDest,';')"!][!/*
                    */!][!LOOP "text:split(.,'+')"!][!/*
                        */!][!IF "string(.) = $LocalVarForCheckDest"!][!/*
                            */!][!VAR "FlagFindDestIntmpDest" = "1"!][!/*
                        */!][!ENDIF!][!/*
                    */!][!ENDLOOP!][!/*
                */!][!ENDLOOP!][!/*

                */!][!/* go trough all tmpSameId elements and check if current SEId is already in the tmpSameId */!][!/*
                */!][!LOOP "text:split($tmpSameId,';')"!][!/*
                    */!][!IF "number(.) = $LocalVarForCheckSameSEId"!][!/*
                        */!][!VAR "FlagFindSameId" = "1"!][!/*
                    */!][!ENDIF!][!/*
                */!][!ENDLOOP!][!/*

                */!][!/* if SEId is not found in tmpSameId, add to the tmpSameId current SEId */!][!/*
                */!][!IF "num:i($FlagFindSameId) = 0"!][!/*
                    */!][!VAR "tmpSameId"!][!"$tmpSameId"!];[!"$LocalVarForCheckSameSEId"!][!ENDVAR!][!/*

                */!][!/* if SEId is found in tmpSameId */!][!/*
                */!][!ELSE!][!/*
                    */!][!/* go trough all tmpDest elements and check if current SEId is already in the tmpDest */!][!/*
                    */!][!LOOP "text:split($tmpDest,';')"!][!/*
                        */!][!LOOP "text:split(.,'-')"!][!/*
                            */!][!IF "number(.) = $LocalVarForCheckSameSEId"!][!/*
                                */!][!VAR "Flag" = "1"!][!/*
                            */!][!ENDIF!][!/*

                            */!][!/* if current SEId is already in tmpDest, get the index */!][!/*
                            */!][!IF "(. != num:i($LocalVarForCheckSameSEId)) and (num:i($Flag) = 1)"!][!/*
                                */!][!VAR "Flag" = "0"!][!/*
                                */!][!LOOP "text:split(.,'+')"!][!/*
                                    */!][!/* get the index */!][!/*
                                    */!][!VAR "IndexIFtmpSameId" = "."!][!/*
                                */!][!ENDLOOP!][!/*
                            */!][!ENDIF!][!/*
                        */!][!ENDLOOP!][!/*
                    */!][!ENDLOOP!][!/*
                */!][!ENDIF!][!/*

                */!][!/* if current SEId, CPId and ModeId are not in the tmpDest  */!][!/*
                */!][!IF "num:i($FlagFindDestIntmpDest) = 0"!][!/*
                    */!][!/* if current SEId is not in the tmpDest  */!][!/*
                    */!][!IF "num:i($FlagFindSameId) = 0"!][!/*
                        */!][!/* if current SEId is not in the tmpDest, add new element with the correct index */!][!/*
                        */!][!VAR "index_j" = "$index_j + 1"!][!/*
                        */!][!VAR "tmpDest"!][!"$tmpDest"!];[!"$LocalVarForCheckDest"!]+[!"num:i($index_j)"!][!ENDVAR!][!/*
                    */!][!ELSE!][!/*
                        */!][!/* if current SEId is already in the tmpDest, add new element with the correct index  */!][!/*
                        */!][!VAR "tmpDest"!][!"$tmpDest"!];[!"$LocalVarForCheckDest"!]+[!"num:i($IndexIFtmpSameId)"!][!ENDVAR!][!/*
                    */!][!ENDIF!][!/*
                */!][!ENDIF!][!/*
             */!][!ENDLOOP!][!/*
        */!][!ENDLOOP!][!/*
    */!][!ENDLOOP!][!/*

    */!][!/* search in tmpDest variable, the matching SEId, CPId and ModeId, if found, print the index mapped to this element */!][!/*
    */!][!LOOP "text:split($tmpDest,';')"!][!/*
        */!][!LOOP "text:split(.,'+')"!][!/*
            */!][!IF "string(.) = $SEIdCPIdModeId"!][!/*
                */!][!VAR "Flag" = "1"!][!/*
            */!][!ENDIF!][!/*
        */!][!ENDLOOP!][!/*

        */!][!IF "$Flag = 1"!][!/*
            */!][!LOOP "text:split(.,'+')"!][!/*
                */!][!IF "string(.) != $SEIdCPIdModeId"!][!/*
                    */!]  [!"."!]U[!/*
                    */!][!VAR "Flag" = "0"!][!/*
                */!][!ENDIF!][!/*
            */!][!ENDLOOP!][!/*
        */!][!ENDIF!][!/*
    */!][!ENDLOOP!][!/*
 */!][!ENDMACRO!][!//

[!// MACROS ----------------------------------------------------------------------------------------

[!// CONSISTENCY CHECKS ----------------------------------------------------------------------------

[!ENDIF!][!// multiple inclusion protection

[!ENDNOCODE!][!//