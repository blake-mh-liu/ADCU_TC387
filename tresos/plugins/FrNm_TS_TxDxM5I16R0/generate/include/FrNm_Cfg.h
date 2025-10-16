/**
 * \file
 *
 * \brief AUTOSAR FrNm
 *
 * This file contains the implementation of the AUTOSAR
 * module FrNm.
 *
 * \version 5.16.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* !LINKSTO FrNm.ASR403.FRNM369,1 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.5 (required)
 * An external object or function shall be declared once in one and only one file.
 *
 * Reason:
 * The files SchM_FrNm.h and FrNm.h contain declarations of FrNm_MainFunction. This should be fixed
 * in a future version of the Rte.
 */

[!INCLUDE "../../generate_macros/FrNm_Macros.m"!][!//
#ifndef FRNM_CFG_H
#define FRNM_CFG_H

/*------------------[Defensive programming]---------------------------------*/
[!SELECT "FrNmDefensiveProgramming"!][!//

#if (defined FRNM_DEFENSIVE_PROGRAMMING_ENABLED)
#error FRNM_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define FRNM_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmDevErrorDetect)) and (node:existsAndTrue(FrNmDefProgEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_PRECONDITION_ASSERT_ENABLED)
#error FRNM_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define FRNM_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmDevErrorDetect)) and (node:existsAndTrue(FrNmDefProgEnabled)) and (node:existsAndTrue(FrNmPrecondAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_POSTCONDITION_ASSERT_ENABLED)
#error FRNM_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define FRNM_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmDevErrorDetect)) and (node:existsAndTrue(FrNmDefProgEnabled)) and (node:existsAndTrue(FrNmPostcondAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_UNREACHABLE_CODE_ASSERT_ENABLED)
#error FRNM_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define FRNM_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmDevErrorDetect)) and (node:existsAndTrue(FrNmDefProgEnabled)) and (node:existsAndTrue(FrNmUnreachAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_INVARIANT_ASSERT_ENABLED)
#error FRNM_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define FRNM_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmDevErrorDetect)) and (node:existsAndTrue(FrNmDefProgEnabled)) and (node:existsAndTrue(FrNmInvariantAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_STATIC_ASSERT_ENABLED)
#error FRNM_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define FRNM_STATIC_ASSERT_ENABLED           [!//
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmDevErrorDetect)) and (node:existsAndTrue(FrNmDefProgEnabled)) and (node:existsAndTrue(FrNmStaticAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//

/*==================[includes]==============================================*/

#include <TSAutosar.h>    /* EB specific standard types */

#ifndef FRNM_NO_CFGCLASSMIX_REQUIRED
#include <FrNm_SymbolicNames_PBcfg.h>
#endif /* FRNM_NO_CFGCLASSMIX_REQUIRED */

#undef FRNM_NO_CFGCLASSMIX_REQUIRED

/*==================[macros]================================================*/

#if (defined FRNM_CFG_SIGNATURE)
#error FRNM_CFG_SIGNATURE is already defined
#endif
#define FRNM_CFG_SIGNATURE [!"asc:getConfigSignature(as:modconf('FrNm')[1]//*[not(child::*) and (node:configclass() = 'PreCompile') ])"!]U /* Compile time verification value */

#if (defined FRNM_PUBLIC_INFO_SIGNATURE)
#error FRNM_PUBLIC_INFO_SIGNATURE is already defined
#endif
#define FRNM_PUBLIC_INFO_SIGNATURE [!"asc:getConfigSignature(node:difference(as:modconf('FrNm')[1]/CommonPublishedInformation//*[not(child::*) and (node:configclass() = 'PublishedInformation') ], as:modconf('FrNm')[1]/CommonPublishedInformation/Release))"!]U /* PublicInfoSignature */

/* !LINKSTO FrNm.EB.Impl.PbCfgM,1 */
#if (defined FRNM_PBCFGM_SUPPORT_ENABLED)
#error FRNM_PBCFGM_SUPPORT_ENABLED is already defined
#endif
#define FRNM_PBCFGM_SUPPORT_ENABLED [!IF "node:existsAndTrue(node:contains(util:distinct(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef)), as:modconf('FrNm')))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ----- Pre-processor switch to enable/diable relocateable postbuild config ----- */
/* !LINKSTO FrNm.EB.Impl.Relocatable,1 */
#if (defined FRNM_RELOCATABLE_CFG_ENABLE)
#error FRNM_RELOCATABLE_CFG_ENABLE is already defined
#endif
#if (FRNM_PBCFGM_SUPPORT_ENABLED == STD_ON)
#define FRNM_RELOCATABLE_CFG_ENABLE [!IF "node:exists(as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable) and (node:existsAndTrue(as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#else
#define FRNM_RELOCATABLE_CFG_ENABLE [!IF "node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGeneral/FrNmRelocatablePbcfgEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#endif

[!SELECT "FrNmGlobalConfig/FrNmGlobalProperties"!][!//
/** \brief Macro switch for version info API usage */
#if (defined FRNM_VERSION_INFO_API)
#error FRNM_VERSION_INFO_API is already defined
#endif
#define FRNM_VERSION_INFO_API            [!//
[!IF "node:existsAndTrue(FrNmVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Switch for DET usage */
#if (defined FRNM_DEV_ERROR_DETECT)
#error FRNM_DEV_ERROR_DETECT is already defined
#endif
#define FRNM_DEV_ERROR_DETECT            [!//
[!IF "node:existsAndTrue(FrNmDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_MAIN_ACROSS_FR_CYCLE)
#error FRNM_MAIN_ACROSS_FR_CYCLE is already defined
#endif
#define FRNM_MAIN_ACROSS_FR_CYCLE            [!//
[!IF "node:existsAndTrue(FrNmMainAcrossFrCycle)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//




[!SELECT "FrNmGeneral"!][!//

#if (defined FRNM_DET_RUNTIME_CHECKS)
#error FRNM_DET_RUNTIME_CHECKS is already defined
#endif
/** \brief DET runtime checks reporting
 **
 ** En- or disables the reporting of the DET runtime checks */
#define FRNM_DET_RUNTIME_CHECKS   [!//
[!IF "FrNmDetRuntimeChecks = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//



[!SELECT "FrNmGlobalConfig/FrNmGlobalFeatures"!][!//
#if (defined FRNM_STATE_CHANGE_INDICATION_ENABLED)
#error FRNM_STATE_CHANGE_INDICATION_ENABLED is already defined
#endif
#define FRNM_STATE_CHANGE_INDICATION_ENABLED    [!//
[!IF "node:existsAndTrue(FrNmStateChangeIndicationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_PASSIVE_MODE_ENABLED)
#error FRNM_PASSIVE_MODE_ENABLED is already defined
#endif
#define FRNM_PASSIVE_MODE_ENABLED        [!//
[!IF "node:existsAndTrue(FrNmPassiveModeEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_PDU_RX_INDICATION_ENABLED)
#error FRNM_PDU_RX_INDICATION_ENABLED is already defined
#endif
#define FRNM_PDU_RX_INDICATION_ENABLED   [!//
[!IF "node:existsAndTrue(FrNmPduRxIndicationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_USER_DATA_ENABLED)
#error FRNM_USER_DATA_ENABLED is already defined
#endif
#define FRNM_USER_DATA_ENABLED           [!//
[!IF "node:existsAndTrue(FrNmUserDataEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "node:existsAndTrue(FrNmPassiveModeEnabled)"!]
/* FrNm0040_Conf : If passive mode is enabled, then FrNmNodeDetectionEnabled is false.*/
#if (defined FRNM_NODE_DETECTION_ENABLED)
#error FRNM_NODE_DETECTION_ENABLED is already defined
#endif
#define FRNM_NODE_DETECTION_ENABLED STD_OFF

/* FrNm0040_Conf:Value of FrNmSourceNodeIdentifierEnabled is same as FrNmNodeDetectionEnabled.*/
#if (defined FRNM_SOURCE_NODE_IDENTIFIER_ENABLED)
#error FRNM_SOURCE_NODE_IDENTIFIER_ENABLED is already defined
#endif
#define FRNM_SOURCE_NODE_IDENTIFIER_ENABLED  STD_OFF

/*FrNm0040_Conf : FrNmControlBitVectorEnabled has dependency to FrNmNodeDetectionEnabled */
#if (defined FRNM_CONTROL_BIT_VECTOR_ENABLED)
#error FRNM_CONTROL_BIT_VECTOR_ENABLED is already defined
#endif
#define FRNM_CONTROL_BIT_VECTOR_ENABLED STD_OFF
[!ELSE!]
#if (defined FRNM_NODE_DETECTION_ENABLED)
#error FRNM_NODE_DETECTION_ENABLED is already defined
#endif
#define FRNM_NODE_DETECTION_ENABLED      [!//
[!IF "count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*[node:existsAndTrue(FrNmChannelIdentifiers/FrNmNodeDetectionEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_SOURCE_NODE_IDENTIFIER_ENABLED)
#error FRNM_SOURCE_NODE_IDENTIFIER_ENABLED is already defined
#endif
#define FRNM_SOURCE_NODE_IDENTIFIER_ENABLED   [!//
[!IF "count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*[node:existsAndTrue(FrNmChannelIdentifiers/FrNmSourceNodeIdentifierEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_CONTROL_BIT_VECTOR_ENABLED)
#error FRNM_CONTROL_BIT_VECTOR_ENABLED is already defined
#endif
#define FRNM_CONTROL_BIT_VECTOR_ENABLED      [!//
[!IF "node:existsAndTrue(FrNmControlBitVectorEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDIF!]
#if (defined FRNM_BUS_SYNCHRONIZATION_ENABLED)
#error FRNM_BUS_SYNCHRONIZATION_ENABLED is already defined
#endif
#define FRNM_BUS_SYNCHRONIZATION_ENABLED [!//
[!IF "node:existsAndTrue(FrNmBusSynchronizationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_REPEAT_MSG_BIT_ENABLED)
#error FRNM_REPEAT_MSG_BIT_ENABLED is already defined
#endif
#define FRNM_REPEAT_MSG_BIT_ENABLED      [!//
[!IF "node:existsAndTrue(FrNmRepeatMessageBitEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_DUAL_CHANNEL_PDU_ENABLE)
#error FRNM_DUAL_CHANNEL_PDU_ENABLE is already defined
#endif
#define FRNM_DUAL_CHANNEL_PDU_ENABLE      [!//
[!IF "node:existsAndTrue(FrNmDualChannelPduEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_COM_USER_DATA_SUPPORT)
#error FRNM_COM_USER_DATA_SUPPORT is already defined
#endif
#define FRNM_COM_USER_DATA_SUPPORT      [!//
[!IF "node:existsAndTrue(FrNmComUserDataSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_CYCLE_COUNTER_EMULATION)
#error FRNM_CYCLE_COUNTER_EMULATION is already defined
#endif
#define FRNM_CYCLE_COUNTER_EMULATION      [!//
[!IF "node:existsAndTrue(FrNmCycleCounterEmulation)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_HW_VOTE_ENABLE)
#error FRNM_HW_VOTE_ENABLE is already defined
#endif
#define FRNM_HW_VOTE_ENABLE      [!//
[!IF "node:existsAndTrue(FrNmHwVoteEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_REMOTE_SLEEP_INDICATION_ENABLED)
#error FRNM_REMOTE_SLEEP_INDICATION_ENABLED is already defined
#endif
#define FRNM_REMOTE_SLEEP_INDICATION_ENABLED      [!//
[!IF "node:existsAndTrue(FrNmRemoteSleepIndicationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_COORDINATOR_SYNC_SUPPORT)
#error FRNM_COORDINATOR_SYNC_SUPPORT is already defined
#endif
#define FRNM_COORDINATOR_SYNC_SUPPORT  [!//
[!IF "node:existsAndTrue(FrNmCoordinatorSyncSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* !LINKSTO FrNm.EB.FrNmMultiCoreSupport,1 */
/** \brief Enable multicore support */
#if (defined FRNM_MULTICORE_ENABLED)
#error FRNM_MULTICORE_ENABLED already defined
#endif
#define FRNM_MULTICORE_ENABLED           [!//
[!IF "node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGeneral/FrNmMultiCoreSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* !LINKSTO FrNm.EB.FrNmMultiCoreUseSingleCS,1 */
/** \brief Specifies in single client server is used for FrNm_PassiveStartup, FrNm_NetworkRequest, FrNm_NetworkRelease and FrNm_NetworkGwEraRequest */
#if (defined FRNM_MULTICORE_USE_SINGLE_CS)
#error FRNM_MULTICORE_USE_SINGLE_CS already defined
#endif
#define FRNM_MULTICORE_USE_SINGLE_CS           [!//
[!IF "node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGeneral/FrNmMultiCoreUseSingleCS)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!] 

/** FrNmVoteBitValue **/
[!IF "node:exists(FrNmVoteBitValue)"!]
#if (defined FRNM_FORCE_VOTE_BIT)
#error FRNM_FORCE_VOTE_BIT is already defined
#endif
#define FRNM_FORCE_VOTE_BIT      STD_ON

#if (defined FRNM_VOTE_BIT)
#error FRNM_VOTE_BIT is already defined
#endif
#define FRNM_VOTE_BIT      [!//
  [!IF "num:i(FrNmVoteBitValue) = 0"!][!/*
  */!]0x00U[!//
  [!ELSE!][!/*
  */!]0x07U[!//
  [!ENDIF!]
[!ELSE!]
#if (defined FRNM_FORCE_VOTE_BIT)
#error FRNM_FORCE_VOTE_BIT is already defined
#endif
#define FRNM_FORCE_VOTE_BIT      STD_OFF
[!ENDIF!]

#if (defined FRNM_SYNCH_ERR_EXTENDED)
#error FRNM_SYNCH_ERR_EXTENDED is already defined
#endif
#define FRNM_SYNCH_ERR_EXTENDED  [!//
[!IF "(node:exists(FrNmSynchErrExtended)) and (node:existsAndTrue(FrNmSynchErrExtended))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//

#if (defined FRNM_SYNCHRONIZATIONPOINT_ENABLED)
#error FRNM_SYNCHRONIZATIONPOINT_ENABLED is already defined
#endif
#define FRNM_SYNCHRONIZATIONPOINT_ENABLED   [!//
[!IF "num:i(count(FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers[node:existsAndTrue(FrNmSynchronizationPointEnabled)])) != 0"!][!//
STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_REPEAT_MESSAGE_BIT_ACTIVE)
#error FRNM_REPEAT_MESSAGE_BIT_ACTIVE is already defined
#endif
#define FRNM_REPEAT_MESSAGE_BIT_ACTIVE  [!//
[!IF "num:i(count(FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers[node:existsAndTrue(FrNmRepeatMessageBitActive)])) != 0"!][!//
STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_NUMBER_OF_CLUSTERS)
#error FRNM_NUMBER_OF_CLUSTERS is already defined
#endif
#define FRNM_NUMBER_OF_CLUSTERS   [!//
[!"num:i(FrNmGlobalConfig/FrNmGlobalConstants/FrNmNumberOfClusters)"!]U


/** \brief Maximum number of Active channels */
#if (defined FRNM_NUMBER_OF_CHANNELS)
#error FRNM_NUMBER_OF_CHANNELS is already defined
#endif
#define FRNM_NUMBER_OF_CHANNELS               [!//
[!"num:i(count(FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*))"!]U

#if (defined FRNM_NUMBER_OF_RX_PDUS)
#error FRNM_NUMBER_OF_RX_PDUS is already defined
#endif
#define FRNM_NUMBER_OF_RX_PDUS   [!//
[!"num:i(count(FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers/FrNmRxPdu/eb-list::*))"!]U

#if (defined FRNM_NUMBER_OF_TX_PDUS)
#error FRNM_NUMBER_OF_TX_PDUS is already defined
#endif
#define FRNM_NUMBER_OF_TX_PDUS   [!//
[!"num:i(count(FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers/FrNmTxPdu/eb-list::*))"!]U

#if (defined FRNM_SEND_NEGATIVE_VOTE_IN_READYSLEEP_STATE)
#error FRNM_SEND_NEGATIVE_VOTE_IN_READYSLEEP_STATE is already defined
#endif
#define FRNM_SEND_NEGATIVE_VOTE_IN_READYSLEEP_STATE   [!//
[!IF "node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalFeatures/FrNmSendNegativeVoteInReadySleepState)"!] STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "num:i(count(FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers/FrNmTxPdu/eb-list::*)) !=0"!]
/* Maximum size of associated Pdus. This size is used to define local buffer when sending data */
#if (defined FRNM_TX_BUFFER_SIZE)
#error FRNM_TX_BUFFER_SIZE is already defined
#endif
#define FRNM_TX_BUFFER_SIZE  8U
[!ENDIF!]

[!LOOP "FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/eb-list::*/FrNmRxPdu/eb-list::*"!][!//

#if (defined FrNmConf_[!"node:name(..)"!]_[!"as:name(.)"!])
#error FrNmConf_[!"node:name(..)"!]_[!"as:name(.)"!] already defined
#endif

/** \brief Symbolic name of FrNmRxPdu with Id "[!"FrNmRxPduId"!]" for
 *  the channel [!"as:name(../../..)"!] */
#define FrNmConf_[!"node:name(..)"!]_[!"as:name(.)"!]   [!"FrNmRxPduId"!]U

#if (defined FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(.)"!])
#error [!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value without prefix
 * (AUTOSAR version <= 3.1 rev4) [!"FrNmRxPduId"!] */
#define [!"as:name(.)"!]                     [!"FrNmRxPduId"!]U

#if (defined FrNm_[!"as:name(.)"!])
#error FrNm_[!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FrNm_[!"as:name(.)"!]   [!"FrNmRxPduId"!]U
#endif /* FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!]


[!LOOP "FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/eb-list::*/FrNmTxPdu/eb-list::*"!][!//

#if (defined FrNmConf_[!"node:name(..)"!]_[!"as:name(.)"!])
#error FrNmConf_[!"node:name(..)"!]_[!"as:name(.)"!] already defined
#endif

/** \brief Symbolic name of FrNmRxPdu with Id "[!"FrNmTxConfirmationPduId"!]"
 *  for the channel [!"as:name(../../..)"!] */
#define FrNmConf_[!"node:name(..)"!]_[!"as:name(.)"!]   [!"FrNmTxConfirmationPduId"!]U

#if (defined FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(.)"!])
#error [!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value without prefix
 * (AUTOSAR version <= 3.1 rev4) [!"FrNmTxConfirmationPduId"!] */
#define [!"as:name(.)"!]                     [!"FrNmTxConfirmationPduId"!]U

#if (defined FrNm_[!"as:name(.)"!])
#error FrNm_[!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FrNm_[!"as:name(.)"!]   [!"FrNmTxConfirmationPduId"!]U
#endif /* FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!]

[!LOOP "FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers/FrNmUserDataTxPdu"!][!//
[!CALL "GetSymbolName","ShortNameRef"="'.'"!][!//

#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined
#endif

/** \brief Symbolic name of FrNmTxUserDataPduId with Id
 * "[!"FrNmTxUserDataPduId"!]" for the channel [!"as:name(../..)"!]
 */
#define [!"$SymbolName"!]   [!"FrNmTxUserDataPduId"!]U

#if (defined FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(../..)"!]_FrNmUserDataTxPdu)
#error [!"as:name(../..)"!]_FrNmUserDataTxPdu already defined
#endif

/** \brief Export symbolic name value without prefix
 * (AUTOSAR version <= 3.1 rev4) [!"FrNmTxUserDataPduId"!]
 */
#define [!"as:name(../..)"!]_FrNmUserDataTxPdu           [!"FrNmTxUserDataPduId"!]U

#if (defined FrNm_[!"as:name(../..)"!]_FrNmUserDataTxPdu)
#error FrNm_[!"as:name(../..)"!]_FrNmUserDataTxPdu already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)
 */
#define FrNm_[!"as:name(../..)"!]_FrNmUserDataTxPdu   [!"FrNmTxUserDataPduId"!]U
#endif /* FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!]

[!LOOP "FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelIdentifiers/FrNmUserDataRxPdu"!][!//
[!CALL "GetSymbolName","ShortNameRef"="'.'"!][!//

#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined
#endif

/** \brief Symbolic name of FrNmRxUserDataPduId with Id
 * "[!"FrNmRxUserDataPduId"!]" for the channel [!"as:name(../..)"!]
 */
#define [!"$SymbolName"!]   [!"FrNmRxUserDataPduId"!]U

#if (defined FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(../..)"!]_FrNmUserDataRxPdu)
#error [!"as:name(../..)"!]_FrNmUserDataRxPdu already defined
#endif

/** \brief Export symbolic name value without prefix
 * (AUTOSAR version <= 3.1 rev4) [!"FrNmRxUserDataPduId"!]
 */
#define [!"as:name(../..)"!]_FrNmUserDataRxPdu           [!"FrNmRxUserDataPduId"!]U

#if (defined FrNm_[!"as:name(../..)"!]_FrNmUserDataRxPdu)
#error FrNm_[!"as:name(../..)"!]_FrNmUserDataRxPdu already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)
 */
#define FrNm_[!"as:name(../..)"!]_FrNmUserDataRxPdu   [!"FrNmRxUserDataPduId"!]U
#endif /* FRNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!]

#if (defined FRNM_ACTIVE_WAKEUP_BIT_ENABLED)
#error FRNM_ACTIVE_WAKEUP_BIT_ENABLED is already defined
#endif
#define FRNM_ACTIVE_WAKEUP_BIT_ENABLED [!//
[!IF "num:i(count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*[(node:exists(FrNmChannelIdentifiers/FrNmActiveWakeupBitEnabled)) and (node:existsAndTrue(FrNmChannelIdentifiers/FrNmActiveWakeupBitEnabled))])) != 0"!][!//
STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_CARWAKEUP_RX_ENABLED)
#error FRNM_CARWAKEUP_RX_ENABLED is already defined
#endif

#define FRNM_CARWAKEUP_RX_ENABLED        [!//
[!IF "count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*[node:existsAndTrue(FrNmChannelIdentifiers/FrNmCarWakeUpRxEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*------------------[PN Extensions]-------------------------------------*/
[!SELECT "FrNmGlobalConfig"!]
[!IF "node:existsAndTrue(../FrNmGeneral/FrNmPnSupported)"!]

/* !LINKSTO FrNm.ECUC_FrNm_00063,1 */
#if (defined FRNM_PN_INFO_LENGTH)
#error FRNM_PN_INFO_LENGTH is already defined
#endif
#define FRNM_PN_INFO_LENGTH     [!//
              [!"FrNmGlobalFeatures/FrNmPnInfo/FrNmPnInfoLength"!]U

#if (defined FRNM_PN_EIRA_TIMER_SIZE)
#error FRNM_PN_EIRA_TIMER_SIZE is already defined
#endif
#define FRNM_PN_EIRA_TIMER_SIZE  (FRNM_PN_INFO_LENGTH * 8U)

/* !LINKSTO FrNm.ECUC_FrNm_00062,1 */
#if (defined FRNM_PN_INFO_OFFSET)
#error FRNM_PN_INFO_OFFSET is already defined
#endif
#define FRNM_PN_INFO_OFFSET     [!//
              [!"FrNmGlobalFeatures/FrNmPnInfo/FrNmPnInfoOffset"!]U

/** FrNmPnEiraCalcEnabled **/
#if (defined FRNM_PN_EIRA_CALC_ENABLED)
#error FRNM_PN_EIRA_CALC_ENABLED is already defined
#endif
#define FRNM_PN_EIRA_CALC_ENABLED             [!//
[!IF "node:existsAndTrue(FrNmGlobalFeatures/FrNmPnEiraCalcEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** FrNmPnEraCalcEnabled **/
#if (defined FRNM_PN_ERA_CALC_ENABLED)
#error FRNM_PN_ERA_CALC_ENABLED is already defined
#endif
#define FRNM_PN_ERA_CALC_ENABLED             [!//
[!IF "count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*[node:existsAndTrue(FrNmChannelIdentifiers/FrNmPnEraCalcEnabled)])>0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** FrNmPnResetTime **/
#if (defined FRNM_PN_RESET_TIME)
#error FRNM_PN_RESET_TIME is already defined
#endif
#define FRNM_PN_RESET_TIME [!//
    [!"num:i(((FrNmGlobalFeatures/FrNmPnResetTime) * 1000) div ((num:min(../FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*/FrNmChannelTiming/FrNmMainFunctionPeriod)) * 1000))"!]U

[!/* get Eira PduId by EcuC reference from PduR, existence is checked in xdm */!][!//
[!IF "node:existsAndTrue(FrNmGlobalFeatures/FrNmPnEiraCalcEnabled)"!][!//

#if (defined FRNM_PN_EIRA_PDUID)
#error FRNM_PN_EIRA_PDUID is already defined
#endif
#define FRNM_PN_EIRA_PDUID  [!//
    [!"as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*/PduRSrcPdu[PduRSrcPduRef=node:current()/FrNmGlobalFeatures/FrNmPnEiraRxNSduRef
]/PduRSourcePduHandleId"!]U/* FrNmPnEiraRx Id*/
[!ENDIF!]

#if (defined FRNM_PN_SUPPORTED)
#error FRNM_PN_SUPPORTED is already defined
#endif
#define FRNM_PN_SUPPORTED  STD_ON


[!CALL "GetSynchronizedPncShutdownEnabled"!]
/** FrNmSynchronizedPncShutdownEnabled **/
#if (defined FRNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
#error FRNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED is already defined
#endif
#define FRNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED             [!//
[!IF "node:existsAndTrue($SynchronizedPncShutdownEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED)
#error FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED is already defined
#endif
[!IF "node:exists(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmPnShutdownMessageRetransmissionDuration)"!]
#define FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED STD_ON
[!ELSE!] [!/*[!IF "node:exists(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmPnShutdownMessageRetransmissionDuration)"!]*/!]
#define FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED STD_OFF
[!ENDIF!] [!/*[!IF "node:exists(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalProperties/FrNmPnShutdownMessageRetransmissionDuration)"!]*/!]

/** Number of active gateways with synchronized shutdown enabled **/
#if (defined FRNM_PN_GATEWAY_TYPE_ACTIVE_NUM)
#error FRNM_PN_GATEWAY_TYPE_ACTIVE_NUM is already defined
#endif
#define FRNM_PN_GATEWAY_TYPE_ACTIVE_NUM [!"num:i(count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*[ node:exists(node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType) and
                                                                                                                  (node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_ACTIVE') and
                                                                                                                   node:exists(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled) and (node:existsAndTrue(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled))]))"!]


/** Number of passive gateways with synchronized shutdown enabled **/
#if (defined FRNM_PN_GATEWAY_TYPE_PASSIVE_NUM)
#error FRNM_PN_GATEWAY_TYPE_PASSIVE_NUM is already defined
#endif
#define FRNM_PN_GATEWAY_TYPE_PASSIVE_NUM [!"num:i(count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*[ node:exists(node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType) and
                                                                                                                  (node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE') and
                                                                                                                   node:exists(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled) and (node:existsAndTrue(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled))]))"!]
[!ELSE!]
#if (defined FRNM_PN_SUPPORTED)
#error FRNM_PN_SUPPORTED is already defined
#endif
#define FRNM_PN_SUPPORTED  STD_OFF

#if (defined FRNM_PN_ERA_CALC_ENABLED)
#error FRNM_PN_ERA_CALC_ENABLED is already defined
#endif
#define FRNM_PN_ERA_CALC_ENABLED STD_OFF

#if (defined FRNM_PN_EIRA_CALC_ENABLED)
#error FRNM_PN_EIRA_CALC_ENABLED is already defined
#endif
#define FRNM_PN_EIRA_CALC_ENABLED STD_OFF

#if (defined FRNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
#error FRNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED is already defined
#endif
#define FRNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED STD_OFF

#if (defined FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED)
#error FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED is already defined
#endif
#define FRNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_ENABLED STD_OFF

/** Number of active gateways with synchronized shutdown enabled **/
#if (defined FRNM_PN_GATEWAY_TYPE_ACTIVE_NUM)
#error FRNM_PN_GATEWAY_TYPE_ACTIVE_NUM is already defined
#endif
#define FRNM_PN_GATEWAY_TYPE_ACTIVE_NUM 0U


/** Number of passive gateways with synchronized shutdown enabled **/
#if (defined FRNM_PN_GATEWAY_TYPE_PASSIVE_NUM)
#error FRNM_PN_GATEWAY_TYPE_PASSIVE_NUM is already defined
#endif
#define FRNM_PN_GATEWAY_TYPE_PASSIVE_NUM 0U

[!ENDIF!]

[!ENDSELECT!][!//

[!IF "(node:existsAndTrue(FrNmGlobalConfig/FrNmGlobalFeatures/FrNmPnEiraCalcEnabled)) or (count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*/FrNmChannel/eb-list::*[node:existsAndTrue(FrNmChannelIdentifiers/FrNmPnEraCalcEnabled)]) > 0)"!]
[!VAR "EiraMaxTimerSize" = "0"!][!//
[!IF "node:exists(FrNmGeneral/FrNmMaxPn)"!][!//
[!VAR "EiraMaxTimerSize" = "node:value(FrNmGeneral/FrNmMaxPn)"!][!//
[!ELSE!][!//
[!VAR "EiraMaxTimerSize" = "node:value(FrNmGlobalConfig/FrNmGlobalFeatures/FrNmPnInfo/FrNmPnInfoLength) * 8"!][!//
[!ENDIF!][!//
#if (defined FRNM_EIRA_MAX_TIMER_SIZE)
#error FRNM_EIRA_MAX_TIMER_SIZE is already defined
#endif
#define FRNM_EIRA_MAX_TIMER_SIZE    [!"num:i($EiraMaxTimerSize)"!]U  /* FrNm Eira Maximum Timer array size */
[!ENDIF!]

/*------------------[Hsm configuration]-------------------------------------*/

#if (defined FRNM_HSM_INST_MULTI_ENABLED)
#error FRNM_HSM_INST_MULTI_ENABLED is already defined
#endif
#if (FRNM_NUMBER_OF_CHANNELS > 1U)
#define FRNM_HSM_INST_MULTI_ENABLED STD_ON
#else
#define FRNM_HSM_INST_MULTI_ENABLED STD_OFF
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/
#define FRNM_START_SEC_CODE
#include <FrNm_MemMap.h>
/* Deviation MISRAC2012-1 */
[!FOR "I"="0" TO "num:i(FrNmGlobalConfig/FrNmGlobalConstants/FrNmNumberOfClusters)-1"!]
#ifndef RTE_SCHM_SWCBSW_FRNM_MAINFUNCTION_[!"num:i($I)"!]
#define RTE_SCHM_SWCBSW_FRNM_MAINFUNCTION_[!"num:i($I)"!]
extern FUNC(void, FRNM_CODE) FrNm_MainFunction_[!"num:i($I)"!](void);
#endif
[!ENDFOR!]
#define FRNM_STOP_SEC_CODE
#include <FrNm_MemMap.h>
/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef FRNM_CFG_H */
/*==================[end of file]===========================================*/
