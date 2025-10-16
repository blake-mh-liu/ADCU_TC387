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
[!INCLUDE "WdgM_Cfg.m"!][!//
[!CODE!][!//
#ifndef WDGM_CFG_H
#define WDGM_CFG_H

/*==================[includes]===================================================================*/
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure09,1 */
#include <WdgM_Callouts.h>                                                /* WdgM's callout APIs */

/*==================[macros]=====================================================================*/

/* ***************** Symbolic name values ****************************************************** */

/* List of watchdog modes */
[!LOOP "util:distinct(node:order(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!//

#if (defined WdgMConf_WdgMMode_[!"as:name(.)"!])
#error WdgMConf_WdgMMode_[!"as:name(.)"!] is already defined
#endif
/** \brief Export symbolic name value for watchdog mode */
#define WdgMConf_WdgMMode_[!"as:name(.)"!] [!"WdgMModeId"!]U

#if (defined WDGM_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined WdgM_[!"as:name(.)"!])
#error WdgM_[!"as:name(.)"!] is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only
 * (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define WdgM_[!"as:name(.)"!] [!"WdgMModeId"!]U
#endif /* defined WDGM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

/* List of supervised entities and its checkpoints*/
[!IF "count(WdgMGeneral/WdgMSupervisedEntity/eb-list::*) > 0"!][!//
[!LOOP "util:distinct(node:order(WdgMGeneral/WdgMSupervisedEntity/eb-list::*, 'WdgMSupervisedEntityId'))"!][!//

#if (defined WdgMConf_WdgMSupervisedEntity_[!"as:name(.)"!])
#error WdgMConf_WdgMSupervisedEntity_[!"as:name(.)"!] is already defined
#endif
/** \brief Export symbolic name value for supervised entity with ID [!"WdgMSupervisedEntityId"!] */
#define WdgMConf_WdgMSupervisedEntity_[!"as:name(.)"!] [!"WdgMSupervisedEntityId"!]U
[!IF "count(WdgMCheckpoint/eb-list::*) > 0"!][!//
[!IF "($ASR40ServiceAPIEnabled = 'false') and ($DefaultServiceAPI != 'AUTOSAR_40')"!][!//
/* List of checkpoints of this supervised entities*/
[!LOOP "util:distinct(node:order(WdgMCheckpoint/eb-list::*, 'WdgMCheckpointId'))"!][!//

#if (defined WdgMConf_WdgMCheckpoint_[!"as:name(.)"!])
#error WdgMConf_WdgMCheckpoint_[!"as:name(.)"!] is already defined
#endif
/* \brief Export symbolic name value for checkpoint with ID [!"WdgMCheckpointId"!] */
#define WdgMConf_WdgMCheckpoint_[!"as:name(.)"!] [!"WdgMCheckpointId"!]U
[!ENDLOOP!][!//
[!ELSE!][!//
/* Checkpoints symbolic names are defined by RTE in Rte_WdgM_Type.h when ASR40 service is used */
[!ENDIF!][!//
[!ENDIF!][!//

#if (defined WDGM_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined WdgM_[!"as:name(.)"!])
#error WdgM_[!"as:name(.)"!] is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only
 * (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define WdgM_[!"as:name(.)"!] [!"WdgMSupervisedEntityId"!]U
[!IF "count(WdgMCheckpoint/eb-list::*) > 0"!][!//
/* List of checkpoints of this supervised entities*/
[!LOOP "util:distinct(node:order(WdgMCheckpoint/eb-list::*, 'WdgMCheckpointId'))"!][!//

#if (defined WdgM_[!"as:name(.)"!])
#error WdgM_[!"as:name(.)"!] is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only
 * (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define WdgM_[!"as:name(.)"!] [!"WdgMCheckpointId"!]U
[!ENDLOOP!][!//
[!ENDIF!][!//
#endif /* defined WDGM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//
[!ENDIF!][!//

/* List of watchdog devices */
[!/* Note: WdgMWatchdogName is derived from the Container name, therefore @name can be used */!][!//
[!LOOP "WdgMGeneral/WdgMWatchdog/eb-list::*"!][!//

#if (defined WdgMConf_WdgMWatchdog_[!"WdgMWatchdogName"!])
#error WdgMConf_WdgMWatchdog_[!"WdgMWatchdogName"!] is already defined
#endif
/** \brief Export symbolic name value for watchdog mode */
#define WdgMConf_WdgMWatchdog_[!"WdgMWatchdogName"!] [!"as:ref(WdgMWatchdogDeviceRef)/WdgIfDeviceIndex"!]U

#if (defined WDGM_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined WdgM_[!"WdgMWatchdogName"!])
#error WdgM_[!"WdgMWatchdogName"!] is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only
 * (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define WdgM_[!"WdgMWatchdogName"!] [!"as:ref(WdgMWatchdogDeviceRef)/WdgIfDeviceIndex"!]U
#endif /* defined WDGM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

/* !LINKSTO WdgM.SWS_WdgM_00104,1 */
/* ***************** ASR specific macros ******************************************************* */

#if (defined WDGM_DEV_ERROR_DETECT)
#error WDGM_DEV_ERROR_DETECT already defined
#endif
/** \brief Macro for DET usage */
#define WDGM_DEV_ERROR_DETECT [!//
[!IF "$DevErrorDetectEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_VERSION_INFO_API)
#error WDGM_VERSION_INFO_API already defined
#endif
/** \brief Macro for DET usage */
#define WDGM_VERSION_INFO_API [!//
[!IF "$VersionInfoApiEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_DEM_ALIVE_SUPERVISION_REPORT)
#error WDGM_DEM_ALIVE_SUPERVISION_REPORT already defined
#endif
/** \brief reporting to diagnostic event manager **/
#define WDGM_DEM_ALIVE_SUPERVISION_REPORT [!//
[!IF "$DemStoppedSupervisionReportEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_IMMEDIATE_RESET)
#error WDGM_IMMEDIATE_RESET already defined
#endif
/** \brief immediate MCU reset in case of alive-supervision failure */
#define WDGM_IMMEDIATE_RESET [!//
[!IF "$ImmediateResetEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_OFF_MODE_ENABLED)
#error WDGM_OFF_MODE_ENABLED already defined
#endif
/** \brief "off mode" enabled/disabled */
#define WDGM_OFF_MODE_ENABLED [!//
[!IF "$OffModeEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_DEFENSIVE_BEHAVIOR)
#error WDGM_DEFENSIVE_BEHAVIOR already defined
#endif
/** \brief availability of Rte */
#define WDGM_DEFENSIVE_BEHAVIOR [!//
[!IF "$DefensiveBehaviorEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_PARTITION_RESET)
#error WDGM_PARTITION_RESET already defined
#endif
/** \brief Partition reset in case of a supervision failure */
#define WDGM_PARTITION_RESET [!//
[!IF "$WdgMPartitionResetEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_MIXED_CRITICALITY)
#error WDGM_MIXED_CRITICALITY already defined
#endif
/** \brief Enable different safety levels for cores. */
#define WDGM_MIXED_CRITICALITY [!//
[!IF "$WdgMMixedCriticalityEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ***************** General EB specific macros ************************************************ */

#if (defined WDGM_EB_WDG_INST_NUM)
#error WDGM_EB_WDG_INST_NUM already defined
#endif
/** \brief Number of watchdog drivers */
#define WDGM_EB_WDG_INST_NUM [!"$NumberOfWdgDrivers"!]U

#if (defined WDGM_EB_CALLERIDS_NUM)
#error WDGM_EB_CALLERIDS_NUM already defined
#endif
/** \brief Number of caller IDs */
#define WDGM_EB_CALLERIDS_NUM [!"$NumberOfCallerIds"!]U

#if (defined WDGM_EB_MODE_NUM)
#error WDGM_EB_MODE_NUM already defined
#endif
/** \brief Number of watchdog modes */
#define WDGM_EB_MODE_NUM [!"$NumberOfWdgModes"!]U

#if (defined WDGM_EB_INTERNAL_GRAPH_NUM)
#error WDGM_EB_INTERNAL_GRAPH_NUM already defined
#endif

/** \brief Number of graphs is sum of configured internal graphs */
#define WDGM_EB_INTERNAL_GRAPH_NUM [!"$NumberOfInternalGraphs"!]U

#if (defined WDGM_EB_EXTERNAL_GRAPH_NUM)
#error WDGM_EB_EXTERNAL_GRAPH_NUM already defined
#endif

/** \brief Number of graphs is sum of configured external graphs */
#define WDGM_EB_EXTERNAL_GRAPH_NUM [!"$NumberOfExternalGraphs"!]U

#if (defined WDGM_EB_OPTIMIZED_EXTERNAL_GRAPH_ENABLED)
#error WDGM_EB_OPTIMIZED_EXTERNAL_GRAPH_ENABLED already defined
#endif

/** \brief Enables the use of optimized algorithm for chosen external graphs */
#define WDGM_EB_OPTIMIZED_EXTERNAL_GRAPH_ENABLED [!//
[!IF "$OptimizedExternalGraphsEnabled > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_DM_NUM)
#error WDGM_EB_DM_NUM already defined
#endif
/** \brief Number of deadline supervision configurations */
#define WDGM_EB_DM_NUM [!"$NumberOfDMs"!]U

#if (defined WDGM_CONFIG_NAME)
#error WDGM_CONFIG_NAME already defined
#endif
/** \brief Name of the data structure storing configuration data
* A pointer to this structure must be given to WdgM_Init(). */
#define WDGM_CONFIG_NAME [!"as:name(WdgMConfigSet/eb-list::*[1])"!]

#if (defined WDGM_EB_SUPERVISION_DEM_EVENT_ID)
#error WDGM_EB_SUPERVISION_DEM_EVENT_ID already defined
#endif
/** \brief Supervision failure Dem event Id **/
#define WDGM_EB_SUPERVISION_DEM_EVENT_ID [!//
[!IF "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_MONITORING)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_MONITORING)))"!][!//
[!ENDIF!]

#if (defined WDGM_EB_SET_MODE_DEM_EVENT_ID)
#error WDGM_EB_SET_MODE_DEM_EVENT_ID already defined
#endif
/** \brief Mode switch failure Dem event Id **/
#define WDGM_EB_SET_MODE_DEM_EVENT_ID [!//
[!IF "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_SET_MODE)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_SET_MODE)))"!][!//
[!ENDIF!]

#if (defined WDGM_EB_IMPROPER_CALLER_DEM_EVENT_ID)
#error WDGM_EB_IMPROPER_CALLER_DEM_EVENT_ID already defined
#endif
/** \brief Improper caller Dem event Id **/
#define WDGM_EB_IMPROPER_CALLER_DEM_EVENT_ID [!//
[!IF "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_IMPROPER_CALLER)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_IMPROPER_CALLER)))"!][!//
[!ENDIF!]

#if (defined WDGM_EB_MF_TIMINGVIOLATION_DEM_EVENT_ID)
#error WDGM_EB_MF_TIMINGVIOLATION_DEM_EVENT_ID already defined
#endif
/** \brief Mainfunction timing violation Dem event Id **/
#define WDGM_EB_MF_TIMINGVIOLATION_DEM_EVENT_ID [!//
[!IF "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_MF_TIMINGVIOLATION)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_MF_TIMINGVIOLATION)))"!][!//
[!ENDIF!]

#if (defined WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID)
#error WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID already defined
#endif
/** \brief Data corruption Dem event Id **/
#define WDGM_EB_DATA_CORRUPTION_DEM_EVENT_ID [!//
[!IF "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_DATA_CORRUPTION)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_DATA_CORRUPTION)))"!][!//
[!ENDIF!]
#if (defined WDGM_EB_ENABLE_SETMODE_SYNCHRON)
#error WDGM_EB_ENABLE_SETMODE_SYNCHRON already defined
#endif
/** \brief This macro enable WdgM_SetMode synchronously switch to the new mode. **/
#define WDGM_EB_ENABLE_SETMODE_SYNCHRON [!//
[!IF "$WdgMSetModeSynchronEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_GET_ALL_EXPIRED_SE)
#error WDGM_EB_GET_ALL_EXPIRED_SE already defined
#endif
/** \brief This macro enables the possibility to retrieve all the expired supervised entities **/
#define WDGM_EB_GET_ALL_EXPIRED_SE [!//
[!IF "$WdgMGetAllExpiredSEIDs"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_PROD_ERR_REP_TO_DEM)
#error WDGM_PROD_ERR_REP_TO_DEM already defined
#endif

/** \brief definition of production error reporting defines - report to Dem
 *
 * The production error reporting could be configured to Dem, Det and off.
 * WDGM_PROD_ERR_REP_TO_DEM is used if the production error is reported
 * towards the Dem.
 */
#define WDGM_PROD_ERR_REP_TO_DEM 0U

#if (defined WDGM_PROD_ERR_REP_TO_DET)
#error WDGM_PROD_ERR_REP_TO_DET already defined
#endif

/** \brief definition of production error reporting defines - report to Det
 *
 * The production error reporting could be configured to Dem, Det and off.
 * WDGM_PROD_ERR_REP_TO_DET is used if the production error is reported
 * towards the Det.
 */
#define WDGM_PROD_ERR_REP_TO_DET 1U

#if (defined WDGM_PROD_ERR_DISABLE)
#error WDGM_PROD_ERR_DISABLE already defined
#endif

/** \brief definition of production error reporting defines - off
 *
 * The production error reporting could be configured to Dem, Det and off.
 * WDGM_PROD_ERR_DISABLE is used if the production error reporting is
 * switched off.
 */
#define WDGM_PROD_ERR_DISABLE 2U

#if (defined WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED)
#error WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED already defined
#endif
/** \brief This macro enables the possibility to trigger Wdg driver from slave instance **/
#define WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED [!//
[!IF "$WdgMTriggerWdgDriverMulticore"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ***************** EB specific macros regarding enhancements ********************************* */




/*------------------[Defensive programming]---------------------------------*/
[!SELECT "WdgMDefensiveProgramming"!][!//

#if (defined WDGM_DEFENSIVE_PROGRAMMING_ENABLED)
#error WDGM_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define WDGM_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(../WdgMGeneral/WdgMDevErrorDetect  = 'true') and (WdgMDefProgEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_PRECONDITION_ASSERT_ENABLED)
#error WDGM_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define WDGM_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(../WdgMGeneral/WdgMDevErrorDetect  = 'true') and (WdgMDefProgEnabled = 'true') and (WdgMPrecondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_POSTCONDITION_ASSERT_ENABLED)
#error WDGM_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define WDGM_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(../WdgMGeneral/WdgMDevErrorDetect  = 'true') and (WdgMDefProgEnabled = 'true') and (WdgMPostcondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_UNREACHABLE_CODE_ASSERT_ENABLED)
#error WDGM_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define WDGM_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(../WdgMGeneral/WdgMDevErrorDetect  = 'true') and (WdgMDefProgEnabled = 'true') and (WdgMUnreachAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_INVARIANT_ASSERT_ENABLED)
#error WDGM_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define WDGM_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(../WdgMGeneral/WdgMDevErrorDetect  = 'true') and (WdgMDefProgEnabled = 'true') and (WdgMInvariantAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_STATIC_ASSERT_ENABLED)
#error WDGM_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define WDGM_STATIC_ASSERT_ENABLED           [!//
[!IF "(../WdgMGeneral/WdgMDevErrorDetect  = 'true') and (WdgMDefProgEnabled = 'true') and (WdgMStaticAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


/*------------------[ASR compatibility flags]----------------------------------------------------*/

#if (defined WDGM_EB_BSW_COMPATIBILITY_ASR32)
#error WDGM_EB_BSW_COMPATIBILITY_ASR32 already defined
#endif
/** \brief Definition that the syntax of the WdgM BSW APIs are AUTOSAR 3.2 compliant **/
#define WDGM_EB_BSW_COMPATIBILITY_ASR32 32U

#if (defined WDGM_EB_BSW_COMPATIBILITY_ASR40)
#error WDGM_EB_BSW_COMPATIBILITY_ASR40 already defined
#endif
/** \brief Definition that the syntax of the WdgM BSW APIs are AUTOSAR 4.0 compliant **/
#define WDGM_EB_BSW_COMPATIBILITY_ASR40 40U

#if (defined WDGM_EB_BSW_COMPATIBILITY_ASR43)
#error WDGM_EB_BSW_COMPATIBILITY_ASR43 already defined
#endif
/** \brief Definition that the syntax of the WdgM BSW APIs are AUTOSAR 4.3 compliant **/
#define WDGM_EB_BSW_COMPATIBILITY_ASR43 43U

#if (defined WDGM_EB_BSW_COMPATIBILITY)
#error WDGM_EB_BSW_COMPATIBILITY already defined
#endif
/** \brief Definition of WdgM BSW API Compatibility mode **/
#define WDGM_EB_BSW_COMPATIBILITY                          [!//
[!IF "$BswCompatibilityMode = 'AUTOSAR_32'"!]WDGM_EB_BSW_COMPATIBILITY_ASR32
[!ELSEIF "$BswCompatibilityMode = 'AUTOSAR_40'"!]WDGM_EB_BSW_COMPATIBILITY_ASR40
[!ELSE!]WDGM_EB_BSW_COMPATIBILITY_ASR43
[!ENDIF!][!//

#if (defined WDGM_EB_SERVICE_API_NONE)
#error WDGM_EB_SERVICE_API_NONE already defined
#endif
/** \brief Definition that no default service API is set **/
#define WDGM_EB_SERVICE_API_NONE   0U

#if (defined WDGM_EB_SERVICE_API_ASR32)
#error WDGM_EB_SERVICE_API_ASR32 already defined
#endif
/** \brief Definition that AUTOSAR 3.2 service API is set as default **/
#define WDGM_EB_SERVICE_API_ASR32 32U

#if (defined WDGM_EB_SERVICE_API_ASR40)
#error WDGM_EB_SERVICE_API_ASR40 already defined
#endif
/** \brief Definition that AUTOSAR 4.0 service API is set as default **/
#define WDGM_EB_SERVICE_API_ASR40 40U

#if (defined WDGM_EB_SERVICE_API_ASR43)
#error WDGM_EB_SERVICE_API_ASR43 already defined
#endif
/** \brief Definition that AUTOSAR 4.3 service API is set as default **/
#define WDGM_EB_SERVICE_API_ASR43 43U

#if (defined WDGM_EB_ENABLE_ASR32_SERVICE_API)
#error WDGM_EB_ENABLE_ASR32_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 3.2 service API for WdgM is enabled **/
#define WDGM_EB_ENABLE_ASR32_SERVICE_API                   [!//
[!IF "$ASR32ServiceAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_ENABLE_ASR40_SERVICE_API)
#error WDGM_EB_ENABLE_ASR40_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 4.0 service API for WdgM is enabled **/
#define WDGM_EB_ENABLE_ASR40_SERVICE_API                   [!//
[!IF "$ASR40ServiceAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_ENABLE_ASR43_SERVICE_API)
#error WDGM_EB_ENABLE_ASR43_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 4.3 service API for WdgM is enabled **/
#define WDGM_EB_ENABLE_ASR43_SERVICE_API                   [!//
[!IF "$ASR43ServiceAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_DEFAULT_ASR_SERVICE_API)
#error WDGM_EB_DEFAULT_ASR_SERVICE_API already defined
#endif
/** \brief Definition of default service API **/
#define WDGM_EB_DEFAULT_ASR_SERVICE_API                    [!//
[!IF "$DefaultServiceAPI = 'AUTOSAR_32'"!]WDGM_EB_SERVICE_API_ASR32
[!ELSEIF "$DefaultServiceAPI = 'AUTOSAR_40'"!]WDGM_EB_SERVICE_API_ASR40
[!ELSEIF "$DefaultServiceAPI = 'AUTOSAR_43'"!]WDGM_EB_SERVICE_API_ASR43
[!ELSE!]WDGM_EB_SERVICE_API_NONE
[!ENDIF!][!//

#if (defined WDGM_EB_ENABLE_ASR32_ACTALIVESUPERV_API)
#error WDGM_EB_ENABLE_ASR32_ACTALIVESUPERV_API already defined
#endif
/** \brief Definition whether AUTOSAR 3.2 service API ActivateAliveSupervision is provided **/
#define WDGM_EB_ENABLE_ASR32_ACTALIVESUPERV_API            [!//
[!IF "$ActivateAliveSupervisionAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_ASR32_ACTALIVESUPERV_API)
#error WDGM_EB_ASR32_ACTALIVESUPERV_API already defined
#endif
/** \brief Definition of callout API for AUTOSAR 3.2 service API ActivateAliveSupervision **/
#define WDGM_EB_ASR32_ACTALIVESUPERV_API                   [!"$ActivateAliveSupervisionAPIName"!]

#if (defined WDGM_EB_ENABLE_ASR32_DEACTALIVESUPERV_API)
#error WDGM_EB_ENABLE_ASR32_DEACTALIVESUPERV_API already defined
#endif
/** \brief Definition whether AUTOSAR 3.2 service API DeactivateAliveSupervision is provided **/
#define WDGM_EB_ENABLE_ASR32_DEACTALIVESUPERV_API          [!//
[!IF "$DeactivateAliveSupervisionAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_ASR32_DEACTALIVESUPERV_API)
#error WDGM_EB_ASR32_DEACTALIVESUPERV_API already defined
#endif
/** \brief Definition of callout API for AUTOSAR 3.2 service API ActivateAliveSupervision **/
#define WDGM_EB_ASR32_DEACTALIVESUPERV_API                 [!"$DeactivateAliveSupervisionAPIName"!]

/*------------------[Error reporting flags]------------------------------------------------------*/

#if (defined WDGM_EB_PROD_ERR_HANDLING_SUPERVISION)
#error WDGM_EB_PROD_ERR_HANDLING_SUPERVISION already defined
#endif
/** \brief Switch for DEM to DET reporting */
#define WDGM_EB_PROD_ERR_HANDLING_SUPERVISION [!//
[!IF "node:exists(ReportToDem/WdgMSupervisionReportToDem) and (ReportToDem/WdgMSupervisionReportToDem = 'DEM')"!][!//
WDGM_PROD_ERR_REP_TO_DEM
[!ELSEIF "node:exists(ReportToDem/WdgMSupervisionReportToDem) and (ReportToDem/WdgMSupervisionReportToDem = 'DET')"!][!//
WDGM_PROD_ERR_REP_TO_DET
[!ELSE!][!//
WDGM_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "node:exists(ReportToDem/WdgMSupervisionReportToDem) and (ReportToDem/WdgMSupervisionReportToDem = 'DET')"!][!//
#if (defined WDGM_EB_E_DEMTODET_SUPERVISION)
#error WDGM_EB_E_DEMTODET_SUPERVISION already defined
#endif
/* !LINKSTO WdgM.EB.ReportToDem.Supervision.5,1 */
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define WDGM_EB_E_DEMTODET_SUPERVISION [!"ReportToDem/WdgMSupervisionDemDetErrId"!]U
[!ENDIF!][!//

#if (defined WDGM_EB_PROD_ERR_HANDLING_SET_MODE)
#error WDGM_EB_PROD_ERR_HANDLING_SET_MODE already defined
#endif
/** \brief Switch for DEM to DET reporting */
#define WDGM_EB_PROD_ERR_HANDLING_SET_MODE                 [!//
[!IF "node:exists(ReportToDem/WdgMSetModeReportToDem) and (ReportToDem/WdgMSetModeReportToDem = 'DEM')"!][!//
WDGM_PROD_ERR_REP_TO_DEM
[!ELSEIF "node:exists(ReportToDem/WdgMSetModeReportToDem) and (ReportToDem/WdgMSetModeReportToDem = 'DET')"!][!//
WDGM_PROD_ERR_REP_TO_DET
[!ELSE!][!//
WDGM_PROD_ERR_DISABLE
[!ENDIF!][!//
[!IF "node:exists(ReportToDem/WdgMSetModeReportToDem) and (ReportToDem/WdgMSetModeReportToDem = 'DET')"!][!//
#if (defined WDGM_EB_E_DEMTODET_SET_MODE)
#error WDGM_EB_E_DEMTODET_SET_MODE already defined
#endif
/* !LINKSTO WdgM.EB.ReportToDem.SetMode.5,1 */
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define WDGM_EB_E_DEMTODET_SET_MODE [!"ReportToDem/WdgMSetModeDemDetErrId"!]U
[!ENDIF!][!//

#if (defined WDGM_EB_PROD_ERR_HANDLING_IMPROPER_CALLER)
#error WDGM_EB_PROD_ERR_HANDLING_IMPROPER_CALLER already defined
#endif
/** \brief Switch for DEM to DET reporting */
#define WDGM_EB_PROD_ERR_HANDLING_IMPROPER_CALLER          [!//
[!IF "node:exists(ReportToDem/WdgMImproperCallerReportToDem) and (ReportToDem/WdgMImproperCallerReportToDem = 'DEM')"!][!//
WDGM_PROD_ERR_REP_TO_DEM
[!ELSEIF "node:exists(ReportToDem/WdgMImproperCallerReportToDem) and (ReportToDem/WdgMImproperCallerReportToDem = 'DET')"!][!//
WDGM_PROD_ERR_REP_TO_DET
[!ELSE!][!//
WDGM_PROD_ERR_DISABLE
[!ENDIF!][!//
[!IF "node:exists(ReportToDem/WdgMImproperCallerReportToDem) and (ReportToDem/WdgMImproperCallerReportToDem = 'DET')"!][!//
#if (defined WDGM_EB_E_DEMTODET_IMPROPER_CALLER)
#error WDGM_EB_E_DEMTODET_IMPROPER_CALLER already defined
#endif
/* !LINKSTO WdgM.EB.ReportToDem.ImproperCaller.5,1 */
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define WDGM_EB_E_DEMTODET_IMPROPER_CALLER [!"ReportToDem/WdgMImproperCallerDemDetErrId"!]U
[!ENDIF!][!//

#if (defined WDGM_EB_PROD_ERR_HANDLING_MF_TIMINGVIOLATION)
#error WDGM_EB_PROD_ERR_HANDLING_MF_TIMINGVIOLATION already defined
#endif
/** \brief Switch for DEM to DET reporting */
#define WDGM_EB_PROD_ERR_HANDLING_MF_TIMINGVIOLATION       [!//
[!IF "node:exists(ReportToDem/WdgMMFTimingViolationReportToDem) and (ReportToDem/WdgMMFTimingViolationReportToDem = 'DEM')"!][!//
WDGM_PROD_ERR_REP_TO_DEM
[!ELSEIF "node:exists(ReportToDem/WdgMMFTimingViolationReportToDem) and (ReportToDem/WdgMMFTimingViolationReportToDem = 'DET')"!][!//
WDGM_PROD_ERR_REP_TO_DET
[!ELSE!][!//
WDGM_PROD_ERR_DISABLE
[!ENDIF!][!//
[!IF "node:exists(ReportToDem/WdgMMFTimingViolationReportToDem) and (ReportToDem/WdgMMFTimingViolationReportToDem = 'DET')"!][!//
#if (defined WDGM_EB_E_DEMTODET_MF_TIMINGVIOLATION)
#error WDGM_EB_E_DEMTODET_MF_TIMINGVIOLATION already defined
#endif
/* !LINKSTO WdgM.EB.ReportToDem.MfTimingViolation.5,1 */
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define WDGM_EB_E_DEMTODET_MF_TIMINGVIOLATION [!"ReportToDem/WdgMMFTimingViolationDemDetErrId"!]U
[!ENDIF!][!//

#if (defined WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION)
#error WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION already defined
#endif
/** \brief Switch for DEM to DET reporting */
#define WDGM_EB_PROD_ERR_HANDLING_DATA_CORRUPTION          [!//
[!IF "node:exists(ReportToDem/WdgMDataCorruptionReportToDem) and (ReportToDem/WdgMDataCorruptionReportToDem = 'DEM')"!][!//
WDGM_PROD_ERR_REP_TO_DEM
[!ELSEIF "node:exists(ReportToDem/WdgMDataCorruptionReportToDem) and (ReportToDem/WdgMDataCorruptionReportToDem = 'DET')"!][!//
WDGM_PROD_ERR_REP_TO_DET
[!ELSE!][!//
WDGM_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "node:exists(ReportToDem/WdgMDataCorruptionReportToDem) and (ReportToDem/WdgMDataCorruptionReportToDem = 'DET')"!][!//
#if (defined WDGM_EB_E_DEMTODET_DATA_CORRUPTION)
#error WDGM_EB_E_DEMTODET_DATA_CORRUPTION already defined
#endif
/* !LINKSTO WdgM.EB.ReportToDem.DataCorruption.5,1 */
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define WDGM_EB_E_DEMTODET_DATA_CORRUPTION [!"ReportToDem/WdgMDataCorruptionDemDetErrId"!]U
[!ENDIF!][!//

/*------------------[TimEPM specific flags]------------------------------------------------------*/

#if (defined WDGM_EB_ENABLE_SUPERVISOR_CALLOUTS)
#error WDGM_EB_ENABLE_SUPERVISOR_CALLOUTS already defined
#endif
/** \brief Definition whether WdgM shall poll information from the Supervisor. **/
#define WDGM_EB_ENABLE_SUPERVISOR_CALLOUTS                 [!//
[!IF "$SupervisorCalloutsEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_GET_EXPECTED_INIT_STATE_ENABLED)
#error WDGM_EB_EXT_GET_EXPECTED_INIT_STATE_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_GET_EXPECTED_INIT_STATE_ENABLED [!//
[!IF "$GetExpectedInitStateCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_GET_EXPECTED_INIT_STATE)
#error WDGM_EB_EXT_GET_EXPECTED_INIT_STATE already defined
#endif
/** \brief Name of the external callout API for getting the expected (de-)init state */
#define WDGM_EB_EXT_GET_EXPECTED_INIT_STATE [!"$GetExpectedInitStateCalloutName"!]

#if (defined WDGM_EB_EXT_INIT_REDIRCALLOUT_ENABLED)
#error WDGM_EB_EXT_INIT_REDIRCALLOUT_ENABLED already defined
#endif
/** \brief Defines whether a call to WdgM_Init shall be redirected to a different API. */
#define WDGM_EB_EXT_INIT_REDIRCALLOUT_ENABLED [!//
[!IF "$InitRedirectionCalloutAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_INIT_REDIRCALLOUT)
#error WDGM_EB_EXT_INIT_REDIRCALLOUT already defined
#endif
/** \brief Name of the API used for redirecting a call to WdgM_Init */
#define WDGM_EB_EXT_INIT_REDIRCALLOUT [!"$InitRedirectionCalloutAPIName"!]

#if (defined WDGM_EB_EXT_DEINIT_REDIRCALLOUT_ENABLED)
#error WDGM_EB_EXT_DEINIT_REDIRCALLOUT_ENABLED already defined
#endif
/** \brief Defines whether a call to WdgM_DeInit shall be redirected to a different API. */
#define WDGM_EB_EXT_DEINIT_REDIRCALLOUT_ENABLED [!//
[!IF "$DeInitRedirectionCalloutAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_DEINIT_REDIRCALLOUT)
#error WDGM_EB_EXT_DEINIT_REDIRCALLOUT already defined
#endif
/** \brief Name of the API used for redirecting a call to WdgM_DeInit */
#define WDGM_EB_EXT_DEINIT_REDIRCALLOUT [!"$DeInitRedirectionCalloutAPIName"!]

#if (defined WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE_ENABLED)
#error WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE_ENABLED [!//
[!IF "$GetExpectedWdgMModeCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE)
#error WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE already defined
#endif
/** \brief Name of the external callout API for getting the expected WdgM mode */
#define WDGM_EB_EXT_GET_EXPECTED_WDGM_MODE [!"$GetExpectedWdgMModeCalloutName"!]

#if (defined WDGM_EB_EXT_SETMODE_REDIRCALLOUT_ENABLED)
#error WDGM_EB_EXT_SETMODE_REDIRCALLOUT_ENABLED already defined
#endif
/** \brief Defines whether a call to WdgM_SetMode shall be redirected to a different API. */
#define WDGM_EB_EXT_SETMODE_REDIRCALLOUT_ENABLED [!//
[!IF "$SetModeRedirectionCalloutAPIEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_SETMODE_REDIRCALLOUT)
#error WDGM_EB_EXT_SETMODE_REDIRCALLOUT already defined
#endif
/** \brief Name of the API used for redirecting a call to WdgM_SetMode */
#define WDGM_EB_EXT_SETMODE_REDIRCALLOUT [!"$SetModeRedirectionCalloutAPIName"!]

#if (defined WDGM_EB_EXT_GET_TIME_ENABLED)
#error WDGM_EB_EXT_GET_TIME_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_GET_TIME_ENABLED [!//
[!IF "$GetTimeCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_GET_TIME)
#error WDGM_EB_EXT_GET_TIME already defined
#endif
/** \brief Name of the external callout API for retrieving the actual timer ticks */
#define WDGM_EB_EXT_GET_TIME [!"$GetTimeCalloutName"!]

#if (defined WDGM_EB_EXT_MAINFUNCTION_VIOLATION_ENABLED)
#error WDGM_EB_EXT_MAINFUNCTION_VIOLATION_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_MAINFUNCTION_VIOLATION_ENABLED [!//
[!IF "$MainFunctionViolationCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_MAINFUNCTION_VIOLATION)
#error WDGM_EB_EXT_MAINFUNCTION_VIOLATION already defined
#endif
/** \brief Name of the external callout API for indicating a violation of main function schedule time */
#define WDGM_EB_EXT_MAINFUNCTION_VIOLATION [!"$MainFunctionViolationCalloutName"!]

#if (defined WDGM_EB_EXT_IS_PERFORM_RESET_ENABLED)
#error WDGM_EB_EXT_IS_PERFORM_RESET_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_IS_PERFORM_RESET_ENABLED [!//
[!IF "$IsPerformResetCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_IS_PERFORM_RESET)
#error WDGM_EB_EXT_IS_PERFORM_RESET already defined
#endif
/** \brief Name of the external callout API for retrieving the actual timer ticks */
#define WDGM_EB_EXT_IS_PERFORM_RESET [!"$IsPerformResetCalloutName"!]

#if (defined WDGM_EB_EXT_SUPERVISION_EXPIRED_ENABLED)
#error WDGM_EB_EXT_SUPERVISION_EXPIRED_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_SUPERVISION_EXPIRED_ENABLED [!//
[!IF "$SupervisionExpiredCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_SUPERVISION_EXPIRED)
#error WDGM_EB_EXT_SUPERVISION_EXPIRED already defined
#endif
/** \brief Name of the external callout API for retrieving the actual timer ticks */
#define WDGM_EB_EXT_SUPERVISION_EXPIRED [!"$SupervisionExpiredCalloutName"!]

#if (defined WDGM_EB_EXT_INDIVIDUAL_MODE_SWITCH_ENABLED)
#error WDGM_EB_EXT_INDIVIDUAL_MODE_SWITCH_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_INDIVIDUAL_MODE_SWITCH_ENABLED [!//
[!IF "$IndividualModeSwitchCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_INDIVIDUAL_MODE_SWITCH)
#error WDGM_EB_EXT_INDIVIDUAL_MODE_SWITCH already defined
#endif
/** \brief Name of the external callout API for retrieving the actual timer ticks */
#define WDGM_EB_EXT_INDIVIDUAL_MODE_SWITCH [!"$IndividualModeSwitchCalloutName"!]

#if (defined WDGM_EB_EXT_GLOBAL_MODE_SWITCH_ENABLED)
#error WDGM_EB_EXT_GLOBAL_MODE_SWITCH_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_GLOBAL_MODE_SWITCH_ENABLED [!//
[!IF "$GlobalModeSwitchCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_GLOBAL_MODE_SWITCH)
#error WDGM_EB_EXT_GLOBAL_MODE_SWITCH already defined
#endif
/** \brief Name of the external callout API for retrieving the actual timer ticks */
#define WDGM_EB_EXT_GLOBAL_MODE_SWITCH [!"$GlobalModeSwitchCalloutName"!]

#if (defined WDGM_EB_EXT_DET_ENABLED)
#error WDGM_EB_EXT_DET_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_DET_ENABLED [!//
[!IF "$DetCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_DET)
#error WDGM_EB_EXT_DET already defined
#endif
/** \brief Name of the external callout API for retrieving the actual timer ticks */
#define WDGM_EB_EXT_DET [!"$DetCalloutName"!]

#if (defined WDGM_EXT_GET_CORE_ID_ENABLED)
#error WDGM_EXT_GET_CORE_ID_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EXT_GET_CORE_ID_ENABLED [!//
[!IF "$GetCoreIdCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EXT_GET_CORE_ID)
#error WDGM_EXT_GET_CORE_ID already defined
#endif
/** \brief Name of the external callout API for retrieving the core Id */
#define WDGM_EXT_GET_CORE_ID() [!"$GetCoreIdCalloutName"!]

#if (defined WDGM_EB_EXT_REQUEST_PARTITION_RESET_ENABLED)
#error WDGM_EB_EXT_REQUEST_PARTITION_RESET_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_REQUEST_PARTITION_RESET_ENABLED [!//
[!IF "$RequestPartitionResetCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_REQUEST_PARTITION_RESET)
#error WDGM_EB_EXT_REQUEST_PARTITION_RESET already defined
#endif
/** \brief Name of the external callout API for requesting a partition reset */
#define WDGM_EB_EXT_REQUEST_PARTITION_RESET [!"$RequestPartitionResetCalloutName"!]

#if (defined WDGM_EB_EXT_GET_APPLICATION_STATE_ENABLED)
#error WDGM_EB_EXT_GET_APPLICATION_STATE_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_GET_APPLICATION_STATE_ENABLED [!//
[!IF "$GetApplicationStateCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_GET_APPLICATION_STATE)
#error WDGM_EB_EXT_GET_APPLICATION_STATE already defined
#endif
/** \brief Name of the external callout API for retrieving the state of an Os application. */
#define WDGM_EB_EXT_GET_APPLICATION_STATE [!"$GetApplicationStateCalloutName"!]

#if (defined WDGM_EB_PARTITIONING_ENABLED)
#error WDGM_EB_PARTITIONING_ENABLED already defined
#endif
/** \brief Definition whether memory partitioning is used or not **/
#define WDGM_EB_PARTITIONING_ENABLED [!//
[!IF "$WdgMPartitioningEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_DM_TIMEGRANULARITY)
#error WDGM_EB_DM_TIMEGRANULARITY already defined
#endif
/** \brief Real-time granularity in micro seconds for external GetElapsedTime API.
 * Equals 0 if Deadline Monitoring is not used. */
#define WDGM_EB_DM_TIMEGRANULARITY [!"num:i(round(num:f(num:mul($TimeGranularity, 1000000))))"!]UL

#if (defined WDGM_EB_DM_MAINFUNCTIONCYCLETIME)
#error WDGM_EB_DM_MAINFUNCTIONCYCLETIME already defined
#endif
/** \brief Time units between two Main Function calls in granularity stated in
 * macro WDGM_EB_DM_TIMEGRANULARITY.
 * Equals 0 if Deadline Monitoring is not used. */
#define WDGM_EB_DM_MAINFUNCTIONCYCLETIME [!"$MainFunctionCycleTime"!]U

#if (defined WDGM_EB_DM_MAINFUNCTIONTOLERANCETIME)
#error WDGM_EB_DM_MAINFUNCTIONTOLERANCETIME already defined
#endif
/** \brief Tolerance time which is allowed between two Main Function calls.
 * The time unit is with respect to the value of macro WDGM_EB_DM_TIMEGRANULARITY.
 * Equals 0 if Deadline Monitoring is not used. */
#define WDGM_EB_DM_MAINFUNCTIONTOLERANCETIME [!"$MainFunctionToleranceTime"!]U

/*------------------[WdgM Multi-Core implementation macros]-----------------------*/

#if (defined WDGM_EB_MULTICORE_ENABLED)
#error WDGM_EB_MULTICORE_ENABLED already defined
#endif

/** \brief Preprocessor macro verifying if the multicore functionality is enabled. */
#define WDGM_EB_MULTICORE_ENABLED [!//
[!IF "$WdgMMulticoreEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_NUMBER_OF_CORES)
#error WDGM_EB_NUMBER_OF_CORES  already defined
#endif
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020111_Conf,1 */
/** \brief Preprocessor macro defining the number of cores configured. */
#define WDGM_EB_NUMBER_OF_CORES  [!"$WdgMNumberOfCores"!]U

#if (defined WDGM_EB_GET_FIRST_EXPIRED_ENABLED)
#error WDGM_EB_GET_FIRST_EXPIRED_ENABLED already defined
#endif
/** \brief Preprocessor macro defining if the GET_FIRST_EXPIRED is enabled. */
#define WDGM_EB_GET_FIRST_EXPIRED_ENABLED                            [!//
[!IF "$WdgMExpiredAPI"!]STD_ON
[!ELSE!]STD_OFF
[!ENDIF!][!//

[!IF "$WdgMMulticoreEnabled"!][!//
#if (defined WDGM_EB_EXT_SATELLITE_ALIVENESS_ENABLED)
#error WDGM_EB_EXT_SATELLITE_ALIVENESS_ENABLED already defined
#endif
/** \brief Defines whether an extern callout API shall be called. */
#define WDGM_EB_EXT_SATELLITE_ALIVENESS_ENABLED [!//
[!IF "$SatelliteAlivenessCalloutEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_EXT_SATELLITE_ALIVENESS_FAILURE)
#error WDGM_EB_EXT_SATELLITE_ALIVENESS_FAILURE already defined
#endif
/** \brief Name of the external callout API for indicating a violation of a satellite main function */
#define WDGM_EB_EXT_SATELLITE_ALIVENESS_FAILURE [!"$SatelliteAlivenessCalloutName"!]

#if (defined WDGM_EB_SAT_ALIVENESS_FAILURE_DEM_EVENT_ID)
#error WDGM_EB_SAT_ALIVENESS_FAILURE_DEM_EVENT_ID already defined
#endif
/** \brief Satellite Mainfunction aliveness violation Dem event Id **/
#define WDGM_EB_SAT_ALIVENESS_FAILURE_DEM_EVENT_ID [!//
[!IF "node:exists(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_MF_SATELLITE_ERROR)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(WdgMConfigSet/eb-list::*[1]/WdgMDemEventParameterRefs/WDGM_E_MF_SATELLITE_ERROR)))"!][!//
[!ENDIF!]

#if (defined WDGM_EB_PROD_ERR_SATELLITE_ALIVENESS_FAILURE)
#error WDGM_EB_PROD_ERR_SATELLITE_ALIVENESS_FAILURE already defined
#endif
/** \brief Switch for DEM to DET reporting */
#define WDGM_EB_PROD_ERR_SATELLITE_ALIVENESS_FAILURE          [!//
[!IF "node:exists(ReportToDem/WdgMSatelliteAlivenessReportToDem) and (ReportToDem/WdgMSatelliteAlivenessReportToDem = 'DEM')"!][!//
WDGM_PROD_ERR_REP_TO_DEM
[!ELSEIF "node:exists(ReportToDem/WdgMSatelliteAlivenessReportToDem) and (ReportToDem/WdgMSatelliteAlivenessReportToDem = 'DET')"!][!//
WDGM_PROD_ERR_REP_TO_DET
[!ELSE!][!//
WDGM_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "node:exists(ReportToDem/WdgMSatelliteAlivenessReportToDem) and (ReportToDem/WdgMSatelliteAlivenessReportToDem = 'DET')"!][!//
#if (defined WDGM_EB_E_DEMTODET_SATELLITE_ALIVENESS_FAILURE)
#error WDGM_EB_E_DEMTODET_SATELLITE_ALIVENESS_FAILURE already defined
#endif
/* !LINKSTO WdgM.EB.ReportToDem.MfSatelliteFailure.5,1 */
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define WDGM_EB_E_DEMTODET_SATELLITE_ALIVENESS_FAILURE [!"ReportToDem/WdgMSatelliteAlivenessDemDetErrId"!]U
[!ENDIF!][!//

#if (defined WDGM_EB_SATELLITE_ALIVENESS_CHECK_PERIOD)
#error WDGM_EB_SATELLITE_ALIVENESS_CHECK_PERIOD already defined
#endif
/** \brief Prepocessor Macro that specifies the number Master Core Mainfunction
* cycles between Satellite Mainfunction aliveness check. */
#define WDGM_EB_SATELLITE_ALIVENESS_CHECK_PERIOD [!"num:i($SatelliteAlivenessPeriodCheck)"!]U

#if (defined WDGM_EB_EXT_SATELLITE_ALIVENESS_COREID_DISABLED)
#error WDGM_EB_EXT_SATELLITE_ALIVENESS_COREID_DISABLED already defined
#endif
/** \brief Preprocessor macro specifying that the CoreId of the failed satellite shall or shall not be returned */
#define WDGM_EB_EXT_SATELLITE_ALIVENESS_COREID_DISABLED [!//
[!IF "$SatelliteAlivenessCoreIdDisable"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!/* IF $WdgMMulticoreEnabled */!][!//

#if (defined WDGM_EB_MASTER_INSTANCE)
#error WDGM_EB_MASTER_INSTANCE already defined
#endif
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020113_Conf,1 */
/** \brief Preprocessor macro defining the core configured as master core. */
#define WDGM_EB_MASTER_INSTANCE [!"$WdgMMasterCoreId"!]U

#if (defined WDGM_EB_MASTER_WAIT_SLAVE_MODE_SWITCH)
#error WDGM_EB_MASTER_WAIT_SLAVE_MODE_SWITCH already defined
#endif
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020119_Conf,1 */
/** \brief   Preprocessor macro that defines the amount of time the WdgM Master Instance
* shall wait until WdgM Satellite Instances finish the mode switch or initialization.
* Unit: Number of master main function. */
#define WDGM_EB_MASTER_WAIT_SLAVE_MODE_SWITCH [!"$WdgMMasterWaitSlaveModeSwitch"!]U

[!IF "$WdgMMulticoreEnabled"!][!//
#if (defined WDGM_EB_SE_NUM)
#error WDGM_EB_SE_NUM already defined
#endif
/** \brief Overall number of supervised entities */
#define WDGM_EB_SE_NUM [!"$NumberOfSupervisedEntities"!]U
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!/*
*/!][!VAR "SupEntExistPerCore" = "false()"!][!/*
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
    */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!/*
        */!][!VAR "SupEntExistPerCore" = "true()"!][!/*
    */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!IF "$SupEntExistPerCore"!]
#if (defined WDGM_EB_SE_NUM_CORE[!"$index_i"!])
#error WDGM_EB_SE_NUM_CORE[!"$index_i"!] already defined
#endif
/** \brief Number of supervised entities per core */
#define WDGM_EB_SE_NUM_CORE[!"$index_i"!] [!CALL "GetNumSEPerCore", "Core"="$index_i"!]U
[!ENDIF!][!/* IF $SupEntExistPerCore */!][!//
[!ENDFOR!][!/*

*/!][!ELSE!][!/* IF $WdgMMulticoreEnabled */!][!//
#if (defined WDGM_EB_SE_NUM)
#error WDGM_EB_SE_NUM already defined
#endif
/** \brief Overall number of supervised entities */
#define WDGM_EB_SE_NUM [!"$NumberOfSupervisedEntities"!]U[!//
[!ENDIF!][!/* IF $WdgMMulticoreEnabled */!][!//

[!IF "$WdgMMulticoreEnabled"!][!//
#if (defined WDGM_EB_CHECKPOINTS_NUM)
#error WDGM_EB_CHECKPOINTS_NUM already defined
#endif
/** \brief Overall number of configured checkpoints */
#define WDGM_EB_CHECKPOINTS_NUM [!"$NumberOfCheckpoints"!]U
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!/*
*/!][!VAR "SupEntExistPerCore" = "false()"!][!/*
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
    */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!/*
        */!][!VAR "SupEntExistPerCore" = "true()"!][!/*
    */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!IF "$SupEntExistPerCore"!]
#if (defined WDGM_EB_CHECKPOINTS_NUM_CORE[!"$index_i"!])
#error WDGM_EB_CHECKPOINTS_NUM_CORE[!"$index_i"!] already defined
#endif
/** \brief Number of configured checkpoints per core */
#define WDGM_EB_CHECKPOINTS_NUM_CORE[!"$index_i"!] [!CALL "GetNumOfCheckpointsPerCore", "Core"="$index_i"!]U
[!ENDIF!][!/* IF $SupEntExistPerCore */!][!//
[!ENDFOR!][!//

#if (defined WDGM_EB_GET_MASTER_STATUS)
#error WDGM_EB_GET_MASTER_STATUS already defined
#endif
/** \brief WdgM master instance is initialized */
#define WDGM_EB_GET_MASTER_STATUS       WdgM_EB_GetMasterInitStatus()

[!ELSE!][!/* IF $WdgMMulticoreEnabled */!]
#if (defined WDGM_EB_CHECKPOINTS_NUM)
#error WDGM_EB_CHECKPOINTS_NUM already defined
#endif
/** \brief Overall number of configured checkpoints */
#define WDGM_EB_CHECKPOINTS_NUM [!"$NumberOfCheckpoints"!]U
[!ENDIF!][!/* IF $WdgMMulticoreEnabled */!][!//

[!VAR "index_i" = "0"!][!/*
*/!][!LOOP "util:distinct(node:order(as:modconf('WdgM')[1]/WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!/*
  */!][!LOOP "WdgMExternalLogicalSupervision/eb-list::*"!][!/*
    */!][!VAR "tmpText"!][!ENDVAR!][!/*
    */!][!LOOP "WdgMExternalTransition/eb-list::*"!][!/*
      */!][!VAR "tmpText"!][!"$tmpText"!]:[!"num:i(as:ref(WdgMExternalTransitionSourceRef)/../../WdgMSupervisedEntityId)"!]:[!"num:i(as:ref(WdgMExternalTransitionDestRef)/../../WdgMSupervisedEntityId)"!][!ENDVAR!][!/*
    */!][!ENDLOOP!][!//
#if (defined WDGM_EB_SE_NUM_GRAPHID_[!"num:i($index_i)"!])
#error WDGM_EB_SE_NUM_GRAPHID_[!"num:i($index_i)"!] already defined
#endif
/** \brief Number of configured SE per external graph */
#define WDGM_EB_SE_NUM_GRAPHID_[!"num:i($index_i)"!] [!"num:i(count(text:order(text:split($tmpText,':'))))"!]U

[!/**/!][!VAR "index_i" = "$index_i + 1"!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!//

[!IF "$WdgMMulticoreEnabled"!][!//
[!FOR "index_i" = "0" TO "num:i($WdgMNumberOfCores)-1"!][!/*
*/!][!VAR "SupEntExistPerCore" = "false()"!][!/*
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
    */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($index_i)"!][!/*
        */!][!VAR "SupEntExistPerCore" = "true()"!][!/*
    */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!IF "$SupEntExistPerCore"!]
#if (defined WDGM_EB_NUM_OS_PARTITIONS_CORE[!"$index_i"!])
#error WDGM_EB_NUM_OS_PARTITIONS_CORE[!"$index_i"!] already defined
#endif
/** \brief Number of Os partitions mapped to a WdgM Core ID. */
#define WDGM_EB_NUM_OS_PARTITIONS_CORE[!"$index_i"!] [!CALL "GetNumOsPartitionsPerCore", "Core"="$index_i"!]U
[!ENDIF!][!/* IF $SupEntExistPerCore */!][!//
[!ENDFOR!][!/*
*/!][!ELSE!][!/* IF $WdgMMulticoreEnabled */!][!//
#if (defined WDGM_EB_NUM_OS_PARTITIONS)
#error WDGM_EB_NUM_OS_PARTITIONS already defined
#endif
/** \brief Number of Os partitions mapped to the WdgM instance. */
#define WDGM_EB_NUM_OS_PARTITIONS [!CALL "GetNumOsPartitionsPerCore", "Core"="0"!]U
[!ENDIF!][!/* IF $WdgMMulticoreEnabled */!][!//

/*------------------[Optional internal mode switch during de-initialization]---------------------*/

#if (defined WDGM_EB_DEINIT_MODE_ENABLED)
#error WDGM_EB_DEINIT_MODE_ENABLED already defined
#endif
/** \brief DeInit mode */
#define WDGM_EB_DEINIT_MODE_ENABLED [!//
[!IF "$SleepModeEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*------------------[WdgM Interface version check]-----------------------------------------------*/

#if (defined WDGM_EB_STATICIF_VERSION) /* to prevent double declaration */
#error WDGM_EB_STATICIF_VERSION already defined
#endif
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020202,1 */
/** \brief WdgM Static interface version */
#define WDGM_EB_STATICIF_VERSION          1

#if (defined WDGM_EB_GENIF_VERSION_REQ) /* to prevent double declaration */
#error WDGM_EB_GENIF_VERSION_REQ already defined
#endif
/* !LINKSTO WDGM.EB.TIMEPM.WDGM020203,1 */
/** \brief WdgM Generated interface version required by component WdgM Static */
#define WDGM_EB_GENIF_VERSION_REQ         1

#if (defined WDGM_EB_GENIF_VERSION_CHECK) /* to prevent double declaration */
#error WDGM_EB_GENIF_VERSION_CHECK already defined
#endif

/* !LINKSTO WDGM.EB.TIMEPM.WDGM020204,1 */
/** \brief Interface compatibility check macro for component WdgM Generated
 *
 * \param[in] staticif_req the required interface version of WdgM Static
 * \param[in] generatedif the interface version of WdgM Generated
 *
 * \retval TRUE The two components WdgM Static and WdgM Generated are compatible
 * \retval FALSE The two components WdgM Static and WdgM Generated are not compatible
 */
#define WDGM_EB_GENIF_VERSION_CHECK(staticif_req, generatedif)   \
    ((WDGM_EB_STATICIF_VERSION >= (staticif_req)) &&             \
     (WDGM_EB_GENIF_VERSION_REQ <= (generatedif)))

/* ***************** EB specific macros regarding optimizations ******************************** */

#if (defined WDGM_EB_INCLUDE_RTE)
#error WDGM_EB_INCLUDE_RTE already defined
#endif
/** \brief availability of Rte */
#define WDGM_EB_INCLUDE_RTE [!//
[!IF "$RteUsageEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_CALLERIDS_ENABLED)
#error WDGM_EB_CALLERIDS_ENABLED already defined
#endif
/** \brief Number of supervised entities */
#define WDGM_EB_CALLERIDS_ENABLED [!//
[!IF "$CallerIdsEnabled"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined WDGM_EB_LOGICAL_SUPERVISION_ENABLED)
#error WDGM_EB_LOGICAL_SUPERVISION_ENABLED already defined
#endif
/** \brief Usage of logical supervision */
#if (WDGM_EB_INTERNAL_GRAPH_NUM > 0U) || (WDGM_EB_EXTERNAL_GRAPH_NUM > 0U)
#define WDGM_EB_LOGICAL_SUPERVISION_ENABLED STD_ON
#else
#define WDGM_EB_LOGICAL_SUPERVISION_ENABLED STD_OFF
#endif

#if (defined WDGM_EB_DEADLINE_SUPERVISION_ENABLED)
#error WDGM_EB_DEADLINE_SUPERVISION_ENABLED already defined
#endif
/** \brief Usage of deadline supervision */
#if (WDGM_EB_DM_NUM > 0U)
#define WDGM_EB_DEADLINE_SUPERVISION_ENABLED STD_ON
#else
#define WDGM_EB_DEADLINE_SUPERVISION_ENABLED STD_OFF
#endif

#if ((WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON) && \
     ((WDGM_EB_PROD_ERR_HANDLING_MF_TIMINGVIOLATION == WDGM_PROD_ERR_REP_TO_DEM) || \
      ((WDGM_EB_PROD_ERR_HANDLING_MF_TIMINGVIOLATION == WDGM_PROD_ERR_REP_TO_DET) && \
       (WDGM_DEV_ERROR_DETECT == STD_ON))))
/** \brief Check if MainFunction timing violations shall be detected */
#define WDGM_EB_CHECK_MAINFUNCTION_TIMING STD_ON
#else
#define WDGM_EB_CHECK_MAINFUNCTION_TIMING STD_OFF
#endif

/* ***************** EB specific macros regarding inter-core communication ******************************** */
[!IF "$WdgMMulticoreEnabled = 'false'"!]
/* Internal macro to get the specific run time data of the WdgM. */
#define WdgM_GetCoreInstance() ((WdgM_EB_CoreContextType *)&WdgM_EB_Context)
[!ENDIF!][!//

#if (defined WDGM_EB_GET_CORE_ID)
#error WDGM_EB_GET_CORE_ID already defined
#endif
/* Internal macro for link external callout API for retrieving the core Id */
#define WDGM_EB_GET_CORE_ID() WDGM_EXT_GET_CORE_ID()

#define WDGM_INSTANCE_ID (WDGM_EB_GET_CORE_ID())

#if (defined WDGM_SID_MAIN_FUNCTION)
#error WDGM_SID_MAIN_FUNCTION already defined
#endif
/** \brief Service id of WdgM_MainFunction() */
#define WDGM_SID_MAIN_FUNCTION          0x08U

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

[!IF "($WdgMMulticoreEnabled = 'true')"!][!//
[!VAR "MULTICORE_NUM_CORES" = "node:value(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores)"!][!//
[!VAR "WDGM_MASTER_CORE_ID" = "node:value(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMMasterCoreId)"!][!//
[!IF "$DefaultServiceAPI = 'NONE'"!][!//
[!FOR "Index" = "0" TO "$MULTICORE_NUM_CORES - 1"!][!//
[!IF "$Index != $WDGM_MASTER_CORE_ID"!][!//
[!VAR "SupEntExistPerCore" = "false()"!][!//
[!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!//
[!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i($Index)"!][!//
[!VAR "SupEntExistPerCore" = "true()"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$SupEntExistPerCore"!][!//
#define WDGM_1_CORE_[!"num:i($Index)"!]_START_SEC_CODE_ASIL_D
#include <WdgM_1_CORE_[!"num:i($Index)"!]_MemMap.h>

FUNC(void, WDGM_1_CORE_[!"num:i($Index)"!]_CODE) WdgM_1_CORE_[!"num:i($Index)"!]_MainFunction(void);

#define WDGM_1_CORE_[!"num:i($Index)"!]_STOP_SEC_CODE_ASIL_D
#include <WdgM_1_CORE_[!"num:i($Index)"!]_MemMap.h>
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//

/*==================[external constants]=========================================================*/

#define WDGM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

/** \brief Data structure storing configuration data
 *
 * A pointer to this structure must be given to WdgM_Init().  The name of this
 * structure is defined by the container name of the first entry of the WdgM
 * configuration set list. */
extern CONST(WdgM_ConfigType, WDGM_APPL_CONST) [!"as:name(WdgMConfigSet/eb-list::*[1])"!];

#define WDGM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>


/*==================[external data]==============================================================*/

#endif /* ifndef WDGM_CFG_H */
/*==================[end of file]================================================================*/
[!ENDCODE!][!//
