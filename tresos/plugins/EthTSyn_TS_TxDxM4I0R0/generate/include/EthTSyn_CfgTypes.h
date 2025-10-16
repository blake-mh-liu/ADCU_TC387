/**
 * \file
 *
 * \brief AUTOSAR EthTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module EthTSyn.
 *
 * \version 4.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]

#ifndef ETHTSYN_CFGTYPES_H
#define ETHTSYN_CFGTYPES_H

/*==================[includes]==============================================*/
#include <TSAutosar.h>              /* global configuration */
[!INCLUDE "EthTSyn_Precompile.m"!]
[!IF "$useDEM = 'true'"!]
#include <Dem.h>                    /* AUTOSAR Dem */
[!ENDIF!]
/*==================[macros]================================================*/

/* check for defined STD_ON macro value */
#ifndef STD_ON
#error STD_ON not defined
#endif  /* STD_ON */

/* check for defined STD_OFF macro value */
#ifndef STD_OFF
#error STD_OFF not defined
#endif  /* STD_OFF */

/*====== Configuration ====== */
#if (defined ETHTSYN_DEV_ERROR_DETECT)
#error ETHTSYN_DEV_ERROR_DETECT is already defined
#endif
/** \brief Pre-processor switch for enabling development error detection. */
#define ETHTSYN_DEV_ERROR_DETECT [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynDevErrorDetect = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_DEV_RUNTIME_ERROR_DETECT)
#error ETHTSYN_DEV_RUNTIME_ERROR_DETECT is already defined
#endif
/** \brief Pre-processor switch for enabling development error detection. */
#define ETHTSYN_DEV_RUNTIME_ERROR_DETECT [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynDetReportRuntimeError = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION)
#error ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION is already defined
#endif
/** \brief Pre-processor switch for enabling master/slave conflict detection and notification. */
#define ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynMasterSlaveConflictDetection = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined ETHTSYN_DEM_REPORTING)
#error ETHTSYN_DEM_REPORTING is already defined
#endif /* if (defined ETHTSYN_DEM_REPORTING) */

#define ETHTSYN_DEM_REPORTING     [!IF "$useDEM = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Switch for DEM to DET reporting */
#define ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED   [!//
[!IF "EthTSynReportError/EthTSynSyncFailedReportError = 'DEM'"!][!//
TS_PROD_ERR_REP_TO_DEM
[!ELSEIF "EthTSynReportError/EthTSynSyncFailedReportError = 'DET'"!][!//
TS_PROD_ERR_REP_TO_DET
[!ELSE!][!//
TS_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "EthTSynReportError/EthTSynSyncFailedReportError = 'DET'"!][!//
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define ETHTSYN_E_DET_SYNC_FAILED          [!"EthTSynReportError/EthTSynSyncFailedReportErrorDetErrorId"!]U
[!ENDIF!][!//

/** \brief Switch for DEM to DET reporting */
#define ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED   [!//
[!IF "EthTSynReportError/EthTSynPdelayFailedReportError = 'DEM'"!][!//
TS_PROD_ERR_REP_TO_DEM
[!ELSEIF "EthTSynReportError/EthTSynPdelayFailedReportError = 'DET'"!][!//
TS_PROD_ERR_REP_TO_DET
[!ELSE!][!//
TS_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "EthTSynReportError/EthTSynPdelayFailedReportError = 'DET'"!][!//
/** \brief Det error ID, if DEM to DET reporting is enabled */
#define ETHTSYN_E_DET_PDELAY_FAILED         [!"EthTSynReportError/EthTSynPdelayFailedReportErrorDetErrorId"!]U
[!ENDIF!][!//

/** \brief Switch for DEM to DET reporting */
#define ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC  [!//
[!IF "EthTSynReportError/EthTSynUnexpectedSyncReportError = 'DEM'"!][!//
TS_PROD_ERR_REP_TO_DEM
[!ELSEIF "EthTSynReportError/EthTSynUnexpectedSyncReportError = 'DET'"!][!//
TS_PROD_ERR_REP_TO_DET
[!ELSE!][!//
TS_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "EthTSynReportError/EthTSynUnexpectedSyncReportError = 'DET'"!][!//
/** \brief Det error ID, if EthTSynUnexpectedSyncReportError is set to DET */
#define ETHTSYN_E_TMCONFLICT_CONFIGURED       [!"EthTSynReportError/EthTSynUnexpectedSyncReportErrorDetErrorId"!]U
[!ENDIF!][!//

/* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00144, 1 */
#if (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
/** \brief Det error ID, if EthTSynMasterSlaveConflictDetection is enabled */
#define ETHTSYN_E_TMCONFLICT       0x01U
#endif

/* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00144, 1 */
/** \brief Det error ID, if EthTSynMasterSlaveConflictDetection is enabled */
#if (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
#define ETHTSYN_E_TSCONFLICT       0x02U
#endif

/* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00144, 1 */
/** \brief Det error ID, if no FV available from FVM is enabled */
#define ETHTSYN_E_FRESHNESSFAILURE   0x03U

#if (defined  ETHTSYN_PBCFG_COMPILE)
#error  ETHTSYN_PBCFG_COMPILE is already defined
#endif
/** \brief Pre-processor switch for choosing between EthTSyn compilation rules or other environment rules. */
#define  ETHTSYN_PBCFG_COMPILE [!IF "EthTSynOptimization/EthTSynPBGeneratedFilesCompilation = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_VERSION_INFO_API)
#error ETHTSYN_VERSION_INFO_API is already defined
#endif
/** \brief Pre-processor switch for enabling version info API support. */
#define ETHTSYN_VERSION_INFO_API [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynVersionInfoApi = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_SEND_ANNOUNCEFRAMES)
#error ETHTSYN_SEND_ANNOUNCEFRAMES is already defined
#endif
/** \brief Pre-processor switch for enabling announce frame sending. */
#define ETHTSYN_SEND_ANNOUNCEFRAMES [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynAnnounceFrameSupport = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* !LINKSTO EthTSyn.SWS_EthTSyn_00212, 1 */
#if (defined ETHTSYN_TIME_RECORDING)
#error ETHTSYN_TIME_RECORDING is already defined
#endif
/** \brief Pre-processor switch for enabling time recording for time validation for a specific Time Domain. */
#define ETHTSYN_TIME_RECORDING [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynTimeValidationSupport  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_HW_TIMESTAMP_SUPPORT)
#error ETHTSYN_HW_TIMESTAMP_SUPPORT is already defined
#endif
/** \brief Pre-processor switch for enabling hardware time stamping support. */
#define ETHTSYN_HW_TIMESTAMP_SUPPORT [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynHardwareTimestampSupport = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_MESSAGE_COMPLIANCE)
#error ETHTSYN_MESSAGE_COMPLIANCE is already defined
#endif
/** \brief Pre-processor switch which defines if IEEE TLV (for STD_ON) or AUTOSAR TLV (for STD_OFF) is used */
#define ETHTSYN_MESSAGE_COMPLIANCE [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynMessageCompliance = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT)
#error ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT is already defined
#endif
/** \brief Pre-processor switch for enabling Device Authentication support. */
#define ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynEnableDeviceAuthenticationSupport = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES)
#error ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES is already defined
#endif
/** \brief Holds configured value of EthTSynMaxNumberOfTransmitRetries */
#define ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES [!"as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynMaxNumberOfTransmitRetries"!]


/** \brief Support of sending only one sync frame on the host port.
           EthSwt will handle the transmission of the sync frames on the other ports.
  ** This constant defines whether the switch feature is used
  ** STD_ON    feature is used
  ** STD_OFF   feature is not used
*/
#if (defined ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT)
#error ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT is already defined
#endif
/** \brief Pre-processor switch for removing sync2 frame. */
#define ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSendSyncFrameOnlyOnHostPort = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Support of EthTSyn_TxConfirmation() according to AUTOSAR R20-11.
  ** This constant defines whether the reliable TxConfirmation feature is used.
  ** STD_ON    feature is used
  ** STD_OFF   feature is not used
*/
#if (defined ETHTSYN_RELIABLE_TXCONF)
#error ETHTSYN_RELIABLE_TXCONF is already defined
#endif
/** \brief Pre-processor switch for supporting EthTSyn_TxConfirmation() according to AUTOSAR R20-11. */
#define ETHTSYN_RELIABLE_TXCONF [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynReliableTxConfirmationSupport = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_BRIDGE_WITH_GTM_MGM_CPU)
#error ETHTSYN_BRIDGE_WITH_GTM_MGM_CPU is already defined
#endif /* if (defined ETHTSYN_BRIDGE_WITH_GTM_MGM_CPU) */

[!CALL "IsSwtUsed"!]
#define ETHTSYN_BRIDGE_WITH_GTM_MGM_CPU     [!IF "$IsSwtUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* !LINKSTO EthTSyn.EB.BridgeWithGTMnotMgmCPU, 1 */
/** \brief Support of SWT bridge functionality
  ** This constant defines whether the switch bridge feature is used
  ** STD_ON    feature is used
  ** STD_OFF   feature is not used
*/
#if (defined ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU)
#error ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU is already defined
#endif /* if (defined ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU) */

[!CALL "IsSwtBridgeUsed"!]
#define ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU     [!IF "$IsSwtBridgeUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Support of SWT functionality
  ** This constant defines whether the switch feature is used
  ** STD_ON    feature is used
  ** STD_OFF   feature is not used
*/
#if (defined ETHTSYN_SWITCH_USED)
#error ETHTSYN_SWITCH_USED is already defined
#endif /* if (defined ETHTSYN_SWITCH_USED) */

#define ETHTSYN_SWITCH_USED     [!IF "$IsSwtUsed = 'true' or $IsSwtBridgeUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* The case when ETHTSYN_MAX_CTRL == ETHTSYN_MAX_SLAVE is the case when only Slave ports are configured in EthTSyn */
/* !LINKSTO EthTSyn.EB.NoMasterConfigured, 1 */
#if (defined ETHTSYN_MAX_CTRL)
#error ETHTSYN_MAX_CTRL is already defined
#endif
/** \brief Maximum possible number of EthTSyn controllers supported. */
#define ETHTSYN_MAX_CTRL [!"num:i($EthTSyn_MaxCtrl)"!]U

/* !LINKSTO EthTSyn.EB.NoSlaveConfigured, 1 */
#if (defined ETHTSYN_MAX_SLAVE)
#error ETHTSYN_MAX_SLAVE is already defined
#endif
[!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynVariantHandlingIsUsed = 'true'"!][!//
[!IF "node:exists(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSyNumberOfConfiguredSlaves)"!][!//
#define ETHTSYN_MAX_SLAVE [!"node:value(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSyNumberOfConfiguredSlaves)"!]U
[!ELSE!]
#define ETHTSYN_MAX_SLAVE 0U
[!ENDIF!]
[!ELSE!]
/** \brief Maximum possible number of EthTSyn slaves supported. */
#define ETHTSYN_MAX_SLAVE [!"num:i($EthTSyn_MaxSlave)"!]U
[!ENDIF!]


#if (defined ETHTSYN_SWITCH_PORTS_CONFIGURED)
#error ETHTSYN_SWITCH_PORTS_CONFIGURED is already defined
#endif
[!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynVariantHandlingIsUsed = 'true'"!][!//
[!IF "node:exists(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynMaxNumberOfSwtPorts)"!][!//
/** \brief Configured switch ports */
#define ETHTSYN_SWITCH_PORTS_CONFIGURED [!"node:value(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynMaxNumberOfSwtPorts)"!]U
[!ELSE!]
#define ETHTSYN_SWITCH_PORTS_CONFIGURED 0U
[!ENDIF!]
[!ELSE!]
/** \brief Configured switch ports */
#define ETHTSYN_SWITCH_PORTS_CONFIGURED [!CALL "EthTSyn_MaxSwtPorts"!]U
[!ENDIF!]

/** \brief Macros used for the CRC support for each Master Time Domain */
#if (defined ETHTSYN_TX_CRC_USED)
#error ETHTSYN_TX_CRC_USED is already defined
#endif /* if (defined ETHTSYN_TX_CRC_USED) */

/** \brief Support of Crc_CalculateCRC8H2F()
  ** This constant defines whether the Crc_CalculateCRC8H2F is
  ** used for the master feature.
  ** STD_ON    Function is used
  ** STD_OFF   Function is not used
*/
[!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynVariantHandlingIsUsed = 'true'"!][!//
#define ETHTSYN_TX_CRC_USED STD_ON
[!ELSE!]
[!CALL "IsTxCRCUsed"!]
#define ETHTSYN_TX_CRC_USED     [!IF "$isTxCRCUsed = 'true' or $IsSwtBridgeUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!]

#if (defined ETHTSYN_RX_CRC_USED)
#error ETHTSYN_RX_CRC_USED is already defined
#endif /* if (defined ETHTSYN_RX_CRC_USED) */

/** \brief Support of Crc_CalculateCRC8H2F()
  ** This constant defines whether the Crc_CalculateCRC8H2F is
  ** used for the Slave feature.
  ** STD_ON    Function is used
  ** STD_OFF   Function is not used
*/
[!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynVariantHandlingIsUsed = 'true'"!][!//
#define ETHTSYN_RX_CRC_USED STD_ON
[!ELSE!]
[!CALL "IsRxCRCUsed"!]
#define ETHTSYN_RX_CRC_USED     [!IF "$isRxCRCUsed = 'true' or $IsSwtBridgeUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!]

/** \brief Support of EthTSynInitialGlobalTimeTxPdelayReqPeriod
  ** This constant defines what PdelayTimer will be used.
  ** used for the Slave feature.
  ** STD_ON    EthTSynInitialGlobalTimeTxPdelayReqPeriod is used
  ** STD_OFF   EthTSynGlobalTimeTxPdelayReqPeriod is used
*/
#if (defined ETHTSYN_INITIAL_PDELAY_TIMER)
#error ETHTSYN_INITIAL_PDELAY_TIMER is already defined
#endif /* if (defined ETHTSYN_INITIAL_PDELAY_TIMER) */

[!CALL "IsInitialPdelay"!]
#define ETHTSYN_INITIAL_PDELAY_TIMER     [!IF "$IsInitialPdelay = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_ICV_USED)
#error ETHTSYN_ICV_USED is already defined
#endif /* if (defined ETHTSYN_ICV_USED) */

/** \brief Support of EthTSynGlobalTimeIcv
  ** STD_ON    ICV is used
  ** STD_OFF   ICV is not used
*/
[!CALL "IsICVUsed"!]
#define ETHTSYN_ICV_USED     [!IF "$IsICVUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_MASTER_FV_USED)
#error ETHTSYN_MASTER_FV_USED is already defined
#endif /* if (defined ETHTSYN_MASTER_FV_USED) */

/** \brief Support of FV for master ports.
  ** STD_ON    FV is used
  ** STD_OFF   FV is not used
*/
[!CALL "IsTxFVUsed"!]
#define ETHTSYN_MASTER_FV_USED     [!IF "$IsTxFVUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_TRUNC_FV_USED)
#error ETHTSYN_TRUNC_FV_USED is already defined
#endif /* if (defined ETHTSYN_TRUNC_FV_USED) */

/** \brief Support for freshness value with truncated length
  ** STD_ON   Truncated FV is used
  ** STD_OFF  Truncated FV is not used
*/
[!CALL "IsTruncFVUsed"!]
#define ETHTSYN_TRUNC_FV_USED   [!IF "$IsTruncFVUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_SLAVE_FV_USED)
#error ETHTSYN_SLAVE_FV_USED is already defined
#endif /* if (defined ETHTSYN_SLAVE_FV_USED) */

/** \brief Support of FV for slave ports.
  ** STD_ON    FV is used
  ** STD_OFF   FV is not used
*/
[!CALL "IsRxFVUsed"!]
#define ETHTSYN_SLAVE_FV_USED     [!IF "$IsRxFVUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined ETHTSYN_ICV_BASE_MAC)
#error ETHTSYN_ICV_BASE_MAC is already defined
#endif /* if (defined ETHTSYN_ICV_BASE_MAC) */

/** \brief Macro that holds EthTSynIcvVerificationBase or EthTSynIcvGenerationBase values
  ** STD_ON    EthTSynIcvVerificationBase or EthTSynIcvGenerationBase is ICV_MAC
  ** STD_OFF   EthTSynIcvVerificationBase or EthTSynIcvGenerationBase is not ICV_MAC
*/
[!CALL "IcvBaseMAC"!]
#define ETHTSYN_ICV_BASE_MAC     [!IF "$IcvBaseMAC = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_ICV_BASE_SIGNATURE)
#error ETHTSYN_ICV_BASE_SIGNATURE is already defined
#endif /* if (defined ETHTSYN_ICV_BASE_SIGNATURE) */

/** \brief Macro that holds EthTSynIcvVerificationBase or EthTSynIcvGenerationBase values
  ** STD_ON    EthTSynIcvVerificationBase or EthTSynIcvGenerationBase is ICV_SIGNATURE
  ** STD_OFF   EthTSynIcvVerificationBase or EthTSynIcvGenerationBase is not ICV_SIGNATURE
*/
[!CALL "IcvBaseSIGNATURE"!]
#define ETHTSYN_ICV_BASE_SIGNATURE     [!IF "$IcvBaseSIGNATURE = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined ETHTSYN_TOTAL_ICVTXLENGTH)
#error ETHTSYN_TOTAL_ICVTXLENGTH is already defined
#endif /* if (defined ETHTSYN_TOTAL_ICVTXLENGTH) */

/** \brief Sum EthTSynIcvTxLength of all master ports that have Synchronous behaviour. */
#define ETHTSYN_TOTAL_ICVTXLENGTH [!CALL "IcvTxLength"!]U

#if (defined ETHTSYN_MAX_TIMEAUTH_ICV_LENGTH)
#error ETHTSYN_MAX_TIMEAUTH_ICV_LENGTH is already defined
#endif /* if (defined ETHTSYN_MAX_TIMEAUTH_ICV_LENGTH) */

/** \brief Maximum value of EthTSynIcvRxLength out of all TimeDomains. */
#define ETHTSYN_MAX_TIMEAUTH_ICV_LENGTH [!CALL "MaxRxIcvSize"!]U

/* ------------------------ IdsM start ------------------------ */

#if (defined ETHTSYN_SECURITYEVENT_REPORTING)
#error ETHTSYN_SECURITYEVENT_REPORTING is already defined
#endif
/** \brief Pre-processor switch for enabling Security event reporting to IdsM. */
#define ETHTSYN_SECURITYEVENT_REPORTING [!IF "as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynEnableSecurityEventReporting = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)

#if (defined ETHTSYN_SEV_ICV_GENERATION_FAILED)
#error ETHTSYN_SEV_ICV_GENERATION_FAILED  already defined!
#endif /* #if( defined ETHTSYN_SEV_ICV_GENERATION_FAILED* )*/

[!IF "node:refvalid(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_ICV_GENERATION_FAILED)"!]
#define ETHTSYN_SEV_ICV_GENERATION_FAILED  [!"node:value(node:ref(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_ICV_GENERATION_FAILED)/IdsMInternalEventId)"!]U
[!ELSE!]
#define ETHTSYN_SEV_ICV_GENERATION_FAILED 0xFFFFU
[!ENDIF!]

#if (defined ETHTSYN_SEV_ICV_VERIFICATION_FAILED)
#error ETHTSYN_SEV_ICV_VERIFICATION_FAILED  already defined!
#endif /* #if( defined ETHTSYN_SEV_ICV_VERIFICATION_FAILED* )*/

[!IF "node:refvalid(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_ICV_VERIFICATION_FAILED)"!]
#define ETHTSYN_SEV_ICV_VERIFICATION_FAILED  [!"node:value(node:ref(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_ICV_VERIFICATION_FAILED)/IdsMInternalEventId)"!]U
[!ELSE!]
#define ETHTSYN_SEV_ICV_VERIFICATION_FAILED 0xFFFFU
[!ENDIF!]

#if (defined ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE)
#error ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE  already defined!
#endif /* #if( defined ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE* )*/

[!IF "node:refvalid(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE)"!]
#define ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE  [!"node:value(node:ref(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE)/IdsMInternalEventId)"!]U
[!ELSE!]
#define ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE 0xFFFFU
[!ENDIF!]

#if (defined ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR)
#error ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR  already defined!
#endif /* #if( defined ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR* )*/

[!IF "node:refvalid(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR)"!]
#define ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR  [!"node:value(node:ref(as:modconf('EthTSyn')[1]/EthTSynGeneral/EthTSynSecurityEventRefs/ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR)/IdsMInternalEventId)"!]U
[!ELSE!]
#define ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR 0xFFFFU
[!ENDIF!]

#endif

/* ------------------------ IdsM end ------------------------ */




#if (defined ETHTSYN_OFSTIMEBASES_CONFIGURED)
#error ETHTSYN_OFSTIMEBASES_CONFIGURED is already defined
#endif /* if (defined ETHTSYN_OFSTIMEBASES_CONFIGURED) */

/** \brief Configured offset timebases  */
#define ETHTSYN_OFSTIMEBASES_CONFIGURED [!CALL "EthTSyn_SlaveOfsTimeDomains"!]U

/** \brief Support of SWT functionality
  ** This constant defines whether the switch feature is used
  ** STD_ON    feature is used
  ** STD_OFF   feature is not used
*/

[!CALL "IsPTPUsed"!]
#define ETHTSYN_IEEE1588_CONFIGURED     [!IF "$IsPTPUsed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_CRC_SUPPORTED)
#error ETHTSYN_CRC_SUPPORTED is already defined
#endif /* if (defined ETHTSYN_CRC_SUPPORTED) */
#define ETHTSYN_CRC_SUPPORTED                 0U

#if (defined ETHTSYN_CRC_NOT_SUPPORTED)
#error ETHTSYN_CRC_NOT_SUPPORTED is already defined
#endif /* if (defined ETHTSYN_CRC_NOT_SUPPORTED) */
#define ETHTSYN_CRC_NOT_SUPPORTED             1U

 /** \brief Macros used for the CRC support for each Slave Time Domain */
#if (defined ETHTSYN_CRC_VALIDATED)
#error ETHTSYN_CRC_VALIDATED is already defined
#endif /* if (defined ETHTSYN_CRC_VALIDATED) */
#define ETHTSYN_CRC_VALIDATED                 0U

#if (defined ETHTSYN_CRC_NOT_VALIDATED)
#error ETHTSYN_CRC_NOT_VALIDATED is already defined
#endif /* if (defined ETHTSYN_CRC_NOT_VALIDATED) */
#define ETHTSYN_CRC_NOT_VALIDATED             1U

#if (defined ETHTSYN_CRC_IGNORED)
#error ETHTSYN_CRC_IGNORED is already defined
#endif /* if (defined ETHTSYN_CRC_IGNORED) */
#define ETHTSYN_CRC_IGNORED                   2U

#if (defined ETHTSYN_CRC_OPTIONAL)
#error ETHTSYN_CRC_OPTIONAL is already defined
#endif /* if (defined ETHTSYN_CRC_OPTIONAL) */
#define ETHTSYN_CRC_OPTIONAL                   3U


 /** \brief Macros used for the ICV support for each Slave Time Domain */
#if (defined ETHTSYN_ICV_VERIFIED)
#error ETHTSYN_ICV_VERIFIED is already defined
#endif /* if (defined ETHTSYN_ICV_VERIFIED) */
#define ETHTSYN_ICV_VERIFIED                 0U

#if (defined ETHTSYN_ICV_NOT_VERIFIED)
#error ETHTSYN_ICV_NOT_VERIFIED is already defined
#endif /* if (defined ETHTSYN_ICV_NOT_VERIFIED) */
#define ETHTSYN_ICV_NOT_VERIFIED             1U

#if (defined ETHTSYN_ICV_IGNORED)
#error ETHTSYN_ICV_IGNORED is already defined
#endif /* if (defined ETHTSYN_ICV_IGNORED) */
#define ETHTSYN_ICV_IGNORED                   2U

#if (defined ETHTSYN_ICV_OPTIONAL)
#error ETHTSYN_ICV_OPTIONAL is already defined
#endif /* if (defined ETHTSYN_ICV_OPTIONAL) */
#define ETHTSYN_ICV_OPTIONAL                   3U
/*==================[type definitions]======================================*/

/** \brief Type for internal port index */
typedef uint8 EthTSyn_IntPortIdxType;

typedef struct
{
  uint8 OfsGlobalTimeDomainId;  /* The ID of the Offset TimeDomain */
  uint8 OffsetTimeBaseId;       /* The ID of the StbM Offset timebase */
} EthTSyn_OffsetTimeBaseType;

/** \brief Defines the type of the EthTSyn controller configuration structure. */
typedef struct
{
  uint32 GlobalTimeDebounceTime;
  uint32 CyclicMsgResumeTime;
  /* Number of main function cycles until next sync frame sent. */
  uint32 SyncTxInterval;
  /* Number of main function cycles until next Pdelay request frame sent. */
  uint32 PdelayReqTxInterval;
  uint32 InitialPdelayReqTxInterval;
  /* Timeout value for Pdelay_Resp and Pdelay_Resp_Follow_Up after a Pdelay_Req
     has been transmitted resp. a Pdelay_Resp has been received.
     A value of 0 deactivates this timeout observation.*/
  uint32 PdelayRespAndRespFollowUpTimeout;
  uint32 DefaultPdelayNs;
  /* Timeout value of the Follow_Up message (of the subsequent Sync message). */
  uint32 GlobalTimeFollowUpTimeout;
  uint32 GlobalTimeRxDebounceTime;
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  uint32 ReceiveSyncFupPairTimeout;
#endif
#if(ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
  uint32 PdelayRespFupPairsPeriod;
#endif
  uint32 PdelayLatencyThreshold; /* EthTSynPdelayLatencyThreshold */
#if(ETHTSYN_ICV_USED == STD_ON)
  uint32 EthTSynIcvGenerationTimeout;
  uint32 EthTSynIcvVerificationTimeout;
  uint32 CsmJobId;
#endif
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  uint32 BridgeTxPeriod; /* EthTSynBridgeTxPeriod */
#endif
  uint16 SequenceCounterJumpWidth; /* EthTSynGlobalTimeSequenceCounterJumpWidth */
#if(ETHTSYN_ICV_USED == STD_ON)
  uint16 EthTSynIcvTxLength; /* Length of ICV to be transmitted within Follow_Up Message on the bus (in bytes). */
  uint16 EthTSynIcvTxOffset;
  uint16 EthTSynIcvRxLength; /* Length of ICV to be received within Follow_Up Message (in bytes). */
  uint16 EthTSynIcvRxOffset;
  uint16 EthTSynIcvVerificationAttempts; /* Relevant only for the Slave . */
  uint16 FreshnessValueId;
  uint8 FreshnessValueLength;
  uint8 FreshnessValueTruncLength;
#endif
  EthTSyn_OffsetTimeBaseType OfsInfo[16U]; /* Contains the ofs relevant ids */
  uint8 SequenceCounterHysteresis; /* EthTSynGlobalTimeSequenceCounterHysteresis */
  uint8 EthIfCtrlIdx;
  uint8 SyncGlobalTimeDomainId; /* The ID of the Sync TimeDomain */
  uint8 TotalOfsTimebase; /* The total number of used Ofs time bases. */
  uint8 OfsIndex; /* The index in the global array. */
  uint8 TimeBaseId;
  uint8 PdelayRefTimbaseId; /* A remote pdelay will be used. */
  /* Filtering (Slave: Pdelay): Number of shifts performed on the delta between old and new
     value. */
  uint8 SyncTxMsgLogInterval; /* Sync Tx period in 2^x format. */
  uint8 PdelayTxMsgLogInterval; /* Pdelay Tx period in 2^x format. */
  uint8 FilterDeltaShift; /* The value of the Pdelay filter */
  uint8 FramePriority; /* Ethernet frame priority for VLAN */
  uint8 IsTxCrcSecuredUsed; /* Configuration parameter that activates/deactivates the CRC support */
  uint8 RxCrcValidated; /* Configuration parameter that activates/deactivates the CRC support */
#if(ETHTSYN_ICV_USED == STD_ON)
  uint8 RxIcvValidated; /* Configuration parameter that activates/deactivates the ICV validation support */
#endif
  uint8 DataIdList[16U];
  EthTSyn_IntPortIdxType PortStart;
  EthTSyn_IntPortIdxType PortCount;
  EthTSyn_IntPortIdxType PortMgt;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  EthTSyn_IntPortIdxType PortSlave;
  boolean SimpleBridge;
  boolean SynchronizeSimpleBridge;
  boolean SimpleBridgeValidateSync;
  boolean SimpleBridgeTSynSendSync;
#endif
#if(ETHTSYN_ICV_USED == STD_ON)
  boolean EthTSynIcvGenerationBase; /* True if symmetric cryptography, false if asymmetric */
  boolean EthTSynIcvVerificationBase; /* True if symmetric cryptography, false if asymmetric */
#endif
  boolean VltStbMIsEthFreerunningCounter;
  boolean TimeSyncMaster; /* TRUE if master, FALSE if slave. */
  boolean PdelayRespEnable;
  boolean ImmediateTimeSync;
  boolean TLVFollowUpTimeSubTLV; /* Enable or disable AUTOSAR Follow_Up TLV Time Sub-TLV */
  boolean TLVFollowUpStatusSubTLV; /* Enable or disable AUTOSAR Follow_Up TLV Status Sub-TLV */
  boolean TLVFollowUpUserDataSubTLV; /* Enable or disable AUTOSAR Follow_Up TLV User Data Sub-TLV */
  boolean TLVFollowUpOFSSubTLV; /* Enable or disable AUTOSAR Follow_Up TLV Ofs Sub-TLV */
#if(ETHTSYN_ICV_USED == STD_ON)
  boolean TLVFollowUpICVSubTLV; /* Enable or disable AUTOSAR Follow_Up TLV ICV Sub-TLV */
#endif
  boolean CrcMessageLength;
  boolean CrcDomainNumber;
  boolean CrcCorrectionField;
  boolean CrcSourcePortIdentity;
  boolean CrcSequenceId;
  boolean CrcPreciseOriginTimestamp;
#if(ETHTSYN_SWITCH_USED == STD_ON)
  boolean SwtPortIdxInCorrField;
  boolean SwtDebouncingPerPort;
#endif
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  /* Time recording for time validation for a specific Time Base */
  boolean TimeValidationEnabled;
#endif
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  boolean PTPMechanismEnabled; /* Enable or disable the used sync mechanism (PTP or gPtp) */
  /* Send delay_req on the next mainfunction after Sync\Fup pair was receuved or respect the DelayReqTxPeriod. */
  boolean TransmitDelayReqAfterFup;
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
#if(ETHTSYN_DEM_REPORTING == STD_ON)
  Dem_EventIdType EventIdSyncFailed;      /**< Event Id to be passed to Dem */
  Dem_EventIdType EventIdPdelayFailed;    /**< Event Id to be passed to Dem */
  Dem_EventIdType EventIdUnexpectedSync;  /**< Event Id to be passed to Dem */
#endif
} EthTSyn_ControllerConfigType;

#if(ETHTSYN_SWITCH_USED == STD_ON)
/** \brief  */
typedef struct
{
  uint32 EthTSynPortDebounceTime;
  uint16 EthSwtIdx;
  uint16 EthSwtPortIdx;
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
  uint16 EthTSynSourcePortId;
#endif /* ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF */
  boolean PdelayRespEnable;
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  /* Time recording for time validation for a specific Port */
  boolean TimeValidationEnabled;
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
} EthTSyn_SwitchConfigType;
#endif /* ETHTSYN_SWITCH_USED == STD_ON */

/** \brief Defines the type of EthTSyn configuration structure. */
/* !LINKSTO EthTSyn.SWS_EthTSyn_00032, 1 */
typedef struct
{
  CONST(uint8, ETHTSYN_APPL_CONST) MaxEthTSynCtrlIdx;
  CONST(uint8, ETHTSYN_APPL_CONST) MaxEthTSynSlaveIdx;
  /* EthTSyn controller configuration. */
  CONST(EthTSyn_ControllerConfigType, ETHTSYN_APPL_CONST) EthTSynCtrl[[!"num:i($EthTSyn_MaxCtrl)"!]U];
#if((ETHTSYN_SWITCH_USED == STD_ON))
  /* Pointer to the relevant information of the configured switch */
  CONSTP2CONST(EthTSyn_SwitchConfigType, AUTOMATIC, ETHTSYN_APPL_CONST) SwitchConfig;
  uint8 NrOfSwitchPortsConfigured;
#endif
} EthTSyn_ConfigType;

/** \brief Defensive programming */
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)



/*------------------[Defensive programming]---------------------------------*/
[!SELECT "EthTSynDefensiveProgramming"!][!//

#if (defined ETHTSYN_DEFENSIVE_PROGRAMMING_ENABLED)
#error ETHTSYN_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define ETHTSYN_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(../EthTSynGeneral/EthTSynDevErrorDetect  = 'true') and (EthTSynDefProgEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_PRECONDITION_ASSERT_ENABLED)
#error ETHTSYN_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define ETHTSYN_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(../EthTSynGeneral/EthTSynDevErrorDetect  = 'true') and (EthTSynDefProgEnabled = 'true') and (EthTSynPrecondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_POSTCONDITION_ASSERT_ENABLED)
#error ETHTSYN_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define ETHTSYN_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(../EthTSynGeneral/EthTSynDevErrorDetect  = 'true') and (EthTSynDefProgEnabled = 'true') and (EthTSynPostcondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_UNREACHABLE_CODE_ASSERT_ENABLED)
#error ETHTSYN_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define ETHTSYN_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(../EthTSynGeneral/EthTSynDevErrorDetect  = 'true') and (EthTSynDefProgEnabled = 'true') and (EthTSynUnreachAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_INVARIANT_ASSERT_ENABLED)
#error ETHTSYN_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define ETHTSYN_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(../EthTSynGeneral/EthTSynDevErrorDetect  = 'true') and (EthTSynDefProgEnabled = 'true') and (EthTSynInvariantAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined ETHTSYN_STATIC_ASSERT_ENABLED)
#error ETHTSYN_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define ETHTSYN_STATIC_ASSERT_ENABLED           [!//
[!IF "(../EthTSynGeneral/EthTSynDevErrorDetect  = 'true') and (EthTSynDefProgEnabled = 'true') and (EthTSynStaticAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//






/*------------------------[Defensive programming]----------------------------*/

#if (defined ETHTSYN_PRECONDITION_ASSERT)
#error ETHTSYN_PRECONDITION_ASSERT is already defined
#endif

#if (defined ETHTSYN_PRECONDITION_ASSERT_NO_EVAL)
#error ETHTSYN_PRECONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (ETHTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define ETHTSYN_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define ETHTSYN_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_PRECONDITION_ASSERT_NO_EVAL((Condition), ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))
#else
#define ETHTSYN_PRECONDITION_ASSERT(Condition, ApiId)
#define ETHTSYN_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined ETHTSYN_POSTCONDITION_ASSERT)
#error ETHTSYN_POSTCONDITION_ASSERT is already defined
#endif

#if (defined ETHTSYN_POSTCONDITION_ASSERT_NO_EVAL)
#error ETHTSYN_POSTCONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (ETHTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define ETHTSYN_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define ETHTSYN_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT_NO_EVAL((Condition), ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))
#else
#define ETHTSYN_POSTCONDITION_ASSERT(Condition, ApiId)
#define ETHTSYN_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined ETHTSYN_INVARIANT_ASSERT)
#error ETHTSYN_INVARIANT_ASSERT is already defined
#endif

#if (defined ETHTSYN_INVARIANT_ASSERT_NO_EVAL)
#error ETHTSYN_INVARIANT_ASSERT_NO_EVAL is already defined
#endif

#if (ETHTSYN_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define ETHTSYN_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define ETHTSYN_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_INVARIANT_ASSERT_NO_EVAL((Condition), ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))
#else
#define ETHTSYN_INVARIANT_ASSERT(Condition, ApiId)
#define ETHTSYN_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined ETHTSYN_STATIC_ASSERT)
# error ETHTSYN_STATIC_ASSERT is already defined
#endif
#if (ETHTSYN_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define ETHTSYN_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define ETHTSYN_STATIC_ASSERT(expr)
#endif

#if (defined ETHTSYN_UNREACHABLE_CODE_ASSERT)
#error ETHTSYN_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (ETHTSYN_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **

 ** \param[in] ApiId Service ID of the API function */
#define ETHTSYN_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId))
#else
#define ETHTSYN_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined ETHTSYN_INTERNAL_API_ID)
#error ETHTSYN_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define ETHTSYN_INTERNAL_API_ID DET_INTERNAL_API_ID


#endif /* ETHIF_DEV_ERROR_DETECT == STD_ON */

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef ETHTSYN_CFGTYPES_H */
/*==================[end of file]===========================================*/
[!ENDCODE!]
