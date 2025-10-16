/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!CODE!]
[!AUTOSPACING!]

#ifndef CANTSYN_CFG_H
#define CANTSYN_CFG_H

/*==================[includes]==============================================*/

[!INCLUDE "CanTSyn_PrecompileMacros.m"!][!//

#include <TSAutosar.h>              /* global configuration */
#include <CanTSyn_Types.h>

/*==================[macros]=================================================*/

#if (defined CANTSYN_DEV_ERROR_DETECT) /* to prevent double declaration */
#error CANTSYN_DEV_ERROR_DETECT is already defined
#endif /* if (defined CANTSYN_DEV_ERROR_DETECT) */

/** \brief Switch for DET usage */ /* !LINKSTO CanTSyn.ECUC_CanTSyn_00002,1 */
#define CANTSYN_DEV_ERROR_DETECT        STD_[!IF "CanTSynGeneral/CanTSynDevErrorDetect = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED)
#error CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED is already defined
#endif /* if (defined CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED) */
/** \brief Switch for DEM to DET reporting */
#define CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED   [!//
[!IF "CanTSynReportError/CanTSynSyncFailedReportError = 'DEM'"!][!//
TS_PROD_ERR_REP_TO_DEM
[!ELSEIF "CanTSynReportError/CanTSynSyncFailedReportError = 'DET'"!][!//
TS_PROD_ERR_REP_TO_DET
[!ELSE!][!//
TS_PROD_ERR_DISABLE
[!ENDIF!][!//

[!IF "CanTSynReportError/CanTSynSyncFailedReportError = 'DET'"!][!//

#if (defined CANTSYN_E_DET_SYNC_FAILED)
#error CANTSYN_E_DET_SYNC_FAILED is already defined
#endif /* if (defined CANTSYN_E_DET_SYNC_FAILED) */

/** \brief Det error ID, if DEM to DET reporting is enabled */
#define CANTSYN_E_DET_SYNC_FAILED          [!"CanTSynReportError/CanTSynSyncFailedReportErrorDetErrorId"!]U

[!ELSEIF "CanTSynReportError/CanTSynSyncFailedReportError = 'DEM'"!][!//

#if (defined CANTSYN_E_DEM_SYNC_FAILED)
#error CANTSYN_E_DEM_SYNC_FAILED is already defined
#endif /* if (defined CANTSYN_E_DEM_SYNC_FAILED) */

#define CANTSYN_E_DEM_SYNC_FAILED(id)      (CanTSyn_TimeSlaveConfig[(id)].EventIdSyncFailed)

[!ENDIF!][!//


[!IF "CanTSynReportError/CanTSynSyncFailedReportError != 'DISABLE'"!][!//

#if (defined CANTSYN_REPORT_WRONG_LENGTH)
#error CANTSYN_REPORT_WRONG_LENGTH is already defined
#endif /* if (defined CANTSYN_REPORT_WRONG_LENGTH) */
/** \brief This constant defines whether the frame which was dropped because of wrong length shall be reported or not to Dem/Det. */
#define CANTSYN_REPORT_WRONG_LENGTH    STD_[!IF "CanTSynReportError/CanTSynReportWrongLength = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_REPORT_WRONG_TIMEDOMAINID)
#error CANTSYN_REPORT_WRONG_TIMEDOMAINID is already defined
#endif /* if (defined CANTSYN_REPORT_WRONG_TIMEDOMAINID) */
/** \brief This constant defines whether the frame which was dropped because of wrong time domain id shall be reported or not to Dem/Det. */
#define CANTSYN_REPORT_WRONG_TIMEDOMAINID    STD_[!IF "CanTSynReportError/CanTSynReportWrongTimeDomainId = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_REPORT_WRONG_CRC)
#error CANTSYN_REPORT_WRONG_CRC is already defined
#endif /* if (defined CANTSYN_REPORT_WRONG_CRC) */
/** \brief This constant defines whether the frame which was dropped because of wrong CRC shall be reported or not to Dem/Det. */
#define CANTSYN_REPORT_WRONG_CRC    STD_[!IF "CanTSynReportError/CanTSynReportWrongCRC = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_REPORT_WRONG_MSGTYPE)
#error CANTSYN_REPORT_WRONG_MSGTYPE is already defined
#endif /* if (defined CANTSYN_REPORT_WRONG_MSGTYPE) */
/** \brief This constant defines whether the frame which was dropped because of wrong message type shall be reported or not to Dem/Det. */
#define CANTSYN_REPORT_WRONG_MSGTYPE    STD_[!IF "CanTSynReportError/CanTSynReportWrongMessageType = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_REPORT_WRONG_SC)
#error CANTSYN_REPORT_WRONG_SC is already defined
#endif /* if (defined CANTSYN_REPORT_WRONG_SC) */
/** \brief This constant defines whether the frame which was dropped because of wrong SC shall be reported or not to Dem/Det. */
#define CANTSYN_REPORT_WRONG_SC    STD_[!IF "CanTSynReportError/CanTSynReportWrongSequenceCounter= 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE)
#error CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE is already defined
#endif /* if (defined CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE) */
/** \brief This constant defines whether the frame which was dropped because of exceeded nanoseconds range shall be reported or not to Dem/Det. */
#define CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE    STD_[!IF "CanTSynReportError/CanTSynReportExceededNanosecondsRange = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!ENDIF!][!//


#if (defined CANTSYN_DET_RUNTIME_CHECK) /* to prevent double declaration */
#error CANTSYN_DET_RUNTIME_CHECK is already defined
#endif /* if (defined CANTSYN_DET_RUNTIME_CHECK) */

/** \brief Switch for DET runtime error reporting */
#define CANTSYN_DET_RUNTIME_CHECK        STD_[!IF "CanTSynGeneral/CanTSynDetRuntimeChecks = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_VERSION_INFO_API)
#error CANTSYN_VERSION_INFO_API is already defined
#endif /* if (defined CANTSYN_VERSION_INFO_API) */

/** \brief Support of CanTSyn_GetVersionInfo()
  ** This constant defines whether the CanTSyn_GetVersionInfo is
  ** provided.
  ** STD_ON    Function is provided
  ** STD_OFF   Function is not provided
*/
/* !LINKSTO CanTSyn.ECUC_CanTSyn_00023,1 */
#define CANTSYN_VERSION_INFO_API       STD_[!IF "CanTSynGeneral/CanTSynVersionInfoApi = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_TX_CRC_USED)
#error CANTSYN_TX_CRC_USED is already defined
#endif /* if (defined CANTSYN_TX_CRC_USED) */

/** \brief Support of Crc_CalculateCRC8H2F()
  ** This constant defines whether the Crc_CalculateCRC8H2F is
  ** used for the master feature.
  ** STD_ON    Function is used
  ** STD_OFF   Function is not used
*/
[!CALL "IsTxCRCUsed"!]
#define CANTSYN_TX_CRC_USED            STD_[!IF "$isTxCRCUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_TX_IMMEDIATE_TRANSMISSION)
#error CANTSYN_TX_IMMEDIATE_TRANSMISSION is already defined
#endif /* if (defined CANTSYN_TX_IMMEDIATE_TRANSMISSION) */

 /** \brief Support for immediate transmission of TimeSync messages.
   ** This constant defines whether Immediate Transmission is
   ** supported for the master feature or not.
   ** STD_ON    Immediate Transmission is used
   ** STD_OFF   Immediate Transmission is not used
 */
 [!CALL "IsTxImmediateTransmissionUsed"!]
#define CANTSYN_TX_IMMEDIATE_TRANSMISSION   STD_[!IF "$IsTxImmediateTransmissionUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_RX_CRC_USED)
#error CANTSYN_RX_CRC_USED is already defined
#endif /* if (defined CANTSYN_RX_CRC_USED) */

/** \brief Support of Crc_CalculateCRC8H2F()
  ** This constant defines whether the Crc_CalculateCRC8H2F is
  ** used for the Slave feature.
  ** STD_ON    Function is used
  ** STD_OFF   Function is not used
*/
[!CALL "IsRxCRCUsed"!]
#define CANTSYN_RX_CRC_USED            STD_[!IF "$isRxCRCUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_RX_SC_HYSTERESIS_USED)
#error CANTSYN_RX_SC_HYSTERESIS_USED is already defined
#endif /* if (defined CANTSYN_RX_SC_HYSTERESIS_USED) */

/** \brief
  ** This constant defines sequence counter Hysteresis is
  ** used for the Slave feature.
  ** STD_ON    SC Hysteresis is used
  ** STD_OFF   SC Hysteresis is not used
*/
[!CALL "IsScHysteresisUsed"!]
#define CANTSYN_RX_SC_HYSTERESIS_USED            STD_[!IF "$IsScHysteresisUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_TX_OFFSET_USED)
#error CANTSYN_TX_OFFSET_USED is already defined
#endif /* if (defined CANTSYN_TX_OFFSET_USED) */

/** \brief Support of TxOffset functionality
  ** This constant defines whether the Tx Offset functionality is
  ** available.
  ** STD_ON    Functionality available
  ** STD_OFF   Functionality is not available
*/
[!CALL "IsTxOffsetUsed"!]
#define CANTSYN_TX_OFFSET_USED    STD_[!IF "$isTxOffsetUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_RX_OFFSET_USED)
#error CANTSYN_RX_OFFSET_USED is already defined
#endif /* if (defined CANTSYN_RX_OFFSET_USED) */

/** \brief Support of RxOffset functionality
  ** This constant defines whether the Rx Offset functionality is
  ** available.
  ** STD_ON    Functionality available
  ** STD_OFF   Functionality is not available
*/
[!CALL "IsRxOffsetUsed"!]
#define CANTSYN_RX_OFFSET_USED    STD_[!IF "$isRxOffsetUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_OFNS_FRAME_USED)
#error CANTSYN_OFNS_FRAME_USED is already defined
#endif /* if (defined CANTSYN_OFNS_FRAME_USED) */

/** \brief Support of OFNS frame handling functionality
  ** This constant defines whether OFNS frame handling functionality
  ** is needed for the current configuration.
  ** STD_ON    Functionality available
  ** STD_OFF   Functionality is not available
*/
[!CALL "IsOFNSFrameUsed"!]
#define CANTSYN_OFNS_FRAME_USED   STD_[!IF "$isOFNSFrameUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_TX_SYNC_USED)
#error CANTSYN_TX_SYNC_USED is already defined
#endif /* if (defined CANTSYN_TX_SYNC_USED) */

/** \brief Support of TxSync functionality
  ** This constant defines whether the TX Sync functionality is
  ** available.
  ** STD_ON    Functionality available
  ** STD_OFF   Functionality is not available */
[!CALL "IsTxSyncUsed"!]
#define CANTSYN_TX_SYNC_USED     STD_[!IF "$isTxSyncUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_MULTICORE_ENABLED) /* to prevent double declaration */
#error CANTSYN_MULTICORE_ENABLED is already defined
#endif /* if (defined CANTSYN_MULTICORE_ENABLED) */

/** \brief Support of MULTICORE functionality
  ** This constant defines whether the multicore functionality is
  ** enabled or not.
  ** STD_ON    Multicore enabled
  ** STD_OFF   Multicore is not enabled
*/
/* !LINKSTO CanTSyn.ECUC_CanTSyn_00002,1 */
#define CANTSYN_MULTICORE_ENABLED        STD_[!IF "CanTSynGeneral/CanTSynMultiCoreSupport = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_RX_SYNC_USED)
#error CANTSYN_RX_SYNC_USED is already defined
#endif /* if (defined CANTSYN_RX_SYNC_USED) */

/** \brief Support of RxSync functionality
  ** This constant defines whether the Rx Sync functionality is
  ** available.
  ** STD_ON    Functionality available
  ** STD_OFF   Functionality is not available
*/
 [!CALL "IsRxSyncUsed"!]
 #define CANTSYN_RX_SYNC_USED     STD_[!IF "$isRxSyncUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_NUMBER_OF_SYNC_MASTERS)
#error CANTSYN_NUMBER_OF_SYNC_MASTERS is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_SYNC_MASTERS) */

/** \brief Number of the Time Master Domains with Domain Ids used for SYNC-FUP sequence */
#define CANTSYN_NUMBER_OF_SYNC_MASTERS        [!"num:i($CanTSyn_SyncTMSize)"!]U

#if (defined CANTSYN_NUMBER_OF_OFFSET_MASTERS)
#error CANTSYN_NUMBER_OF_OFFSET_MASTERS is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_OFFSET_MASTERS) */

/** \brief Number of the Time Master Domains with Domain Ids used for OFS-OFNS sequence */
#define CANTSYN_NUMBER_OF_OFFSET_MASTERS        [!"num:i($CanTSyn_OffsetTMSize)"!]U

#if (defined CANTSYN_NUMBER_OF_MASTERS)
#error CANTSYN_NUMBER_OF_MASTERS is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_MASTERS) */

/** \brief Number of the total Time Master Domains */
#define CANTSYN_NUMBER_OF_MASTERS               [!"num:i($CanTSyn_SyncTMSize + $CanTSyn_OffsetTMSize)"!]U

#if (defined CANTSYN_NUMBER_OF_SYNC_SLAVES)
#error CANTSYN_NUMBER_OF_SYNC_SLAVES is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_SYNC_SLAVES) */

/** \brief Number of the Time Slave Domains with Domain Ids used for SYNC-FUP sequence */
#define CANTSYN_NUMBER_OF_SYNC_SLAVES           [!"num:i($CanTSyn_SyncTSSize)"!]U

#if (defined CANTSYN_NUMBER_OF_OFFSET_SLAVES)
#error CANTSYN_NUMBER_OF_OFFSET_SLAVES is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_OFFSET_SLAVES) */

/** \brief Number of the Time Slave Domains with Domain Ids used for OFS-OFNS sequence */
#define CANTSYN_NUMBER_OF_OFFSET_SLAVES        [!"num:i($CanTSyn_OffsetTSSize)"!]U

#if (defined CANTSYN_NUMBER_OF_SLAVES)
#error CANTSYN_NUMBER_OF_SLAVES is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_SLAVES) */

/** \brief Number of the total Time Slave Domains */
#define CANTSYN_NUMBER_OF_SLAVES                [!"num:i($CanTSyn_SyncTSSize + $CanTSyn_OffsetTSSize)"!]U

#if (defined CANTSYN_NUMBER_OF_CONTROLLERS)
#error CANTSYN_NUMBER_OF_CONTROLLERS is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_CONTROLLERS) */

/** \brief Number of referenced controllers */
#define CANTSYN_NUMBER_OF_CONTROLLERS           [!"num:i($CanTSyn_CtrlSize)"!]U

#if (defined CANTSYN_NUMBER_OF_ICV_MASTERS)
#error CANTSYN_NUMBER_OF_ICV_MASTERS is already defined
#endif /* if (defined CANTSYN_NUMBER_OF_ICV_MASTERS) */

/** \brief Number of Master Time Domains which support ICV authentication */
#define CANTSYN_NUMBER_OF_ICV_MASTERS [!"$CanTSyn_IcvTMSize"!]

#if (defined CANTSYN_NUMBER_OF_ICV_SLAVES)
#error CANTSYN_NUMBER_OF_ICV_SLAVES is already defined
#endif /* if(CANTSYN_NUMBER_OF_ICV_SLAVES) */

/** \brief Number of Slave Time Domains which support ICV authentication */
#define CANTSYN_NUMBER_OF_ICV_SLAVES [!"$CanTSyn_IcvTSSize"!]

/** \brief Macros used for the CRC support for each Master Time Domain */

#if (defined CANTSYN_CRC_SUPPORTED)
#error CANTSYN_CRC_SUPPORTED is already defined
#endif /* if (defined CANTSYN_CRC_SUPPORTED) */
#define CANTSYN_CRC_SUPPORTED                 0U

#if (defined CANTSYN_CRC_NOT_SUPPORTED)
#error CANTSYN_CRC_NOT_SUPPORTED is already defined
#endif /* if (defined CANTSYN_CRC_NOT_SUPPORTED) */
#define CANTSYN_CRC_NOT_SUPPORTED             1U

 /** \brief Macros used for the CRC support for each Slave Time Domain */

#if (defined CANTSYN_CRC_VALIDATED)
#error CANTSYN_CRC_VALIDATED is already defined
#endif /* if (defined CANTSYN_CRC_VALIDATED) */
#define CANTSYN_CRC_VALIDATED                 0U

#if (defined CANTSYN_CRC_OPTIONAL)
#error CANTSYN_CRC_OPTIONAL is already defined
#endif /* if (defined CANTSYN_CRC_OPTIONAL) */
#define CANTSYN_CRC_OPTIONAL                  1U

#if (defined CANTSYN_CRC_NOT_VALIDATED)
#error CANTSYN_CRC_NOT_VALIDATED is already defined
#endif /* if (defined CANTSYN_CRC_NOT_VALIDATED) */
#define CANTSYN_CRC_NOT_VALIDATED             2U

#if (defined CANTSYN_CRC_IGNORED)
#error CANTSYN_CRC_IGNORED is already defined
#endif /* if (defined CANTSYN_CRC_IGNORED) */
#define CANTSYN_CRC_IGNORED                   3U

 /** \brief Macros used for the ICV support for each Master Time Domain */

#if (defined CANTSYN_ICV_SUPPORTED)
#error CANTSYN_ICV_SUPPORTED is already defined
#endif /* if (defined CANTSYN_ICV_SUPPORTED) */
#define CANTSYN_ICV_SUPPORTED                 1U

#if (defined CANTSYN_ICV_NOT_SUPPORTED)
#error CANTSYN_ICV_NOT_SUPPORTED is already defined
#endif /* if (defined CANTSYN_ICV_NOT_SUPPORTED) */
#define CANTSYN_ICV_NOT_SUPPORTED             0U

 /** \brief Macros used for the ICV support for each Slave Time Domain */

#if (defined CANTSYN_ICV_IGNORED)
#error CANTSYN_ICV_IGNORED is already defined
#endif /* if (defined CANTSYN_ICV_IGNORED) */
#define CANTSYN_ICV_IGNORED                   0U

#if (defined CANTSYN_ICV_NOT_VERIFIED)
#error CANTSYN_ICV_NOT_VERIFIED is already defined
#endif /* if (defined CANTSYN_ICV_NOT_VERIFIED) */
#define CANTSYN_ICV_NOT_VERIFIED              1U

#if (defined CANTSYN_ICV_OPTIONAL)
#error CANTSYN_ICV_OPTIONAL is already defined
#endif /* if (defined CANTSYN_ICV_OPTIONAL) */
#define CANTSYN_ICV_OPTIONAL                  2U

#if (defined CANTSYN_ICV_VERIFIED)
#error CANTSYN_ICV_VERIFIED is already defined
#endif /* if (defined CANTSYN_ICV_VERIFIED) */
#define CANTSYN_ICV_VERIFIED                  3U

[!CALL "isIcvGenerationSupported"!]
#define CANTSYN_ICV_GENERATION_SUPPORTED STD_[!IF "$isIcvGenerationSupported = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isIcvVerificationSupported"!]
#define CANTSYN_ICV_VERIFICATION_SUPPORTED STD_[!IF "$isIcvVerificationSupported = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isFvUsedInIcvGeneration"!]
#define CANTSYN_ICV_GENERATION_FV_USED  STD_[!IF "$isFvUsedInIcvGeneration = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isFvUsedInIcvVerification"!]
#define CANTSYN_ICV_VERIFICATION_FV_USED STD_[!IF "$isFvUsedInIcvVerification = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isTruncatedFvUsed"!]
#if (defined CANTSYN_TRUNCATED_FV_USED)
#error CANTSYN_TRUNCATED_FV_USED is already defined
#endif /* if (defined CANTSYN_TRUNCATED_FV_USED) */
#define CANTSYN_TRUNCATED_FV_USED   STD_[!IF "$isTruncatedFvUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!IF "($isIcvGenerationSupported = 'true') or ($isIcvVerificationSupported = 'true')"!]

[!CALL "getIcvTotalDataLength"!]
#if (defined CANTSYN_ICV_DATA_ARRAY_SIZE)
#error CANTSYN_ICV_DATA_ARRAY_SIZE is already defined
#endif /* if (defined CANTSYN_ICV_DATA_ARRAY_SIZE) */
#define CANTSYN_ICV_DATA_ARRAY_SIZE           [!"num:i($IcvTotalDataLength)"!]U

[!CALL "getComputedIcvTotalLength"!]
#if (defined CANTSYN_ICV_COMPUTED_ARRAY_SIZE)
#error CANTSYN_ICV_COMPUTED_ARRAY_SIZE is already defined
#endif /* if (defined CANTSYN_ICV_COMPUTED_ARRAY_SIZE) */
#define CANTSYN_ICV_COMPUTED_ARRAY_SIZE       [!"num:i($IcvComputedTotalLength)"!]U

[!CALL "isCsmMacGenerateUsed"!]
#if (defined CANTSYN_ICV_MAC_GENERATE_USAGE)
#error CANTSYN_ICV_MAC_GENERATE_USAGE is already defined
#endif /* if (defined CANTSYN_ICV_MAC_GENERATE_USAGE) */
#define CANTSYN_ICV_MAC_GENERATE_USAGE        STD_[!IF "$CsmMacGenerateUsage = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isCsmSignatureGenerateUsed"!]
#if (defined CANTSYN_ICV_SIGNATURE_GENERATE_USAGE)
#error CANTSYN_ICV_SIGNATURE_GENERATE_USAGE is already defined
#endif /* if (defined CANTSYN_ICV_SIGNATURE_GENERATE_USAGE) */
#define CANTSYN_ICV_SIGNATURE_GENERATE_USAGE        STD_[!IF "$CsmSignatureGenerateUsage = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isCsmMacVerifyUsed"!]
#if (defined CANTSYN_ICV_MAC_VERIFY_USAGE)
#error CANTSYN_ICV_MAC_VERIFY_USAGE is already defined
#endif /* if (defined CANTSYN_ICV_MAC_VERIFY_USAGE) */
#define CANTSYN_ICV_MAC_VERIFY_USAGE        STD_[!IF "$CsmMacVerifyUsage = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!CALL "isCsmSignatureVerifyUsed"!]
#if (defined CANTSYN_ICV_SIGNATURE_VERIFY_USAGE)
#error CANTSYN_ICV_SIGNATURE_VERIFY_USAGE is already defined
#endif /* if (defined CANTSYN_ICV_SIGNATURE_VERIFY_USAGE) */
#define CANTSYN_ICV_SIGNATURE_VERIFY_USAGE        STD_[!IF "$CsmSignatureVerifyUsage = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!IF "($isFvUsedInIcvGeneration = 'true') or ($isFvUsedInIcvVerification = 'true')"!]
  [!CALL "getMaxFreshnessValueLength"!]
#if (defined CANTSYN_FV_MAX_LENGTH)
#error CANTSYN_FV_MAX_LENGTH is already defined
#endif /* if (defined CANTSYN_FV_MAX_LENGTH) */
#define CANTSYN_FV_MAX_LENGTH    [!"num:i($FvMaxLength)"!]U

#if (defined CANTSYN_TRUNC_FV_MAX_LENGTH)
#error CANTSYN_TRUNC_FV_MAX_LENGTH is already defined
#endif /* if (defined CANTSYN_TRUNC_FV_MAX_LENGTH) */
#define CANTSYN_TRUNC_FV_MAX_LENGTH    [!"num:i($TruncFvMaxLength)"!]U
[!ENDIF!]

 /** \brief Macros used for the ICV generation base selection */

#if (defined CANTSYN_ICV_MAC)
#error CANTSYN_ICV_MAC is already defined
#endif /* if (defined CANTSYN_ICV_MAC) */
#define CANTSYN_ICV_MAC                       0U

#if (defined CANTSYN_ICV_SIGNATURE)
#error CANTSYN_ICV_SIGNATURE is already defined
#endif /* if (defined CANTSYN_ICV_SIGNATURE) */
#define CANTSYN_ICV_SIGNATURE                 1U


#if (defined CANTSYN_ICV_CSM_SYNCHRONOUS)
#error CANTSYN_ICV_CSM_SYNCHRONOUS is already defined
#endif /* if (defined CANTSYN_ICV_CSM_SYNCHRONOUS) */
#define CANTSYN_ICV_CSM_SYNCHRONOUS      0U

#if (defined CANTSYN_ICV_CSM_ASYNCHRONOUS)
#error CANTSYN_ICV_CSM_ASYNCHRONOUS is already defined
#endif /* if (defined CANTSYN_ICV_CSM_ASYNCHRONOUS) */
#define CANTSYN_ICV_CSM_ASYNCHRONOUS     1U

[!ENDIF!]

/** \brief Value of unused parameters for ICV generation or verification */

#if (defined CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS)
#error CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS is already defined
#endif /* if (defined CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS) */
#define CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS     0xFFU

#if (defined CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS)
#error CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS is already defined
#endif /* if (defined CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS) */
#define CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS    0xFFFFU

#if (defined CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS)
#error CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS is already defined
#endif /* if (defined CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS) */
#define CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS    0xFFFFFFFFU

#if (defined CANTSYN_SECURED_MSG_LEN)
#error CANTSYN_SECURED_MSG_LEN is already defined
#endif /* if (defined CANTSYN_SECURED_MSG_LEN) */
#define CANTSYN_SECURED_MSG_LEN             64U

#if (defined CANTSYN_TX_MAX_MSG_LEN)
#error CANTSYN_TX_MAX_MSG_LEN is already defined
#endif /* if (defined CANTSYN_TX_MAX_MSG_LEN) */
[!IF "$CanTSyn_NumTxExtendedMsgFormat > 0"!]
#define CANTSYN_TX_MAX_MSG_LEN                   16U
[!ELSE!]
#define CANTSYN_TX_MAX_MSG_LEN                   8U
[!ENDIF!]

#if (defined CANTSYN_RX_MAX_MSG_LEN)
#error CANTSYN_RX_MAX_MSG_LEN is already defined
#endif /* if (defined CANTSYN_RX_MAX_MSG_LEN) */
[!IF "$CanTSyn_NumRxExtendedMsgFormat > 0"!]
#define CANTSYN_RX_MAX_MSG_LEN                   16U
[!ELSE!]
#define CANTSYN_RX_MAX_MSG_LEN                   8U
[!ENDIF!]

#if (defined CANTSYN_TX_USE_EXTENDED_MSG)
#error CANTSYN_TX_USE_EXTENDED_MSG is already defined
#endif /* if (defined CANTSYN_TX_USE_EXTENDED_MSG) */
[!IF "$CanTSyn_NumTxExtendedMsgFormat > 0"!]
#define CANTSYN_TX_USE_EXTENDED_MSG              STD_ON
[!ELSE!]
#define CANTSYN_TX_USE_EXTENDED_MSG              STD_OFF
[!ENDIF!]

#if (defined CANTSYN_RX_USE_EXTENDED_MSG)
#error CANTSYN_RX_USE_EXTENDED_MSG is already defined
#endif /* if (defined CANTSYN_RX_USE_EXTENDED_MSG) */
[!IF "$CanTSyn_NumRxExtendedMsgFormat > 0"!]
#define CANTSYN_RX_USE_EXTENDED_MSG              STD_ON
[!ELSE!]
#define CANTSYN_RX_USE_EXTENDED_MSG              STD_OFF
[!ENDIF!]

#if (defined CANTSYN_IS_TX_PDUINDEX_USED)
#error CANTSYN_IS_TX_PDUINDEX_USED is already defined
#endif /* if (defined CANTSYN_IS_TX_PDUINDEX_USED) */

#define CANTSYN_IS_TX_PDUINDEX_USED     STD_[!IF "(($isTxSyncUsed = 'true') or ($isTxOffsetUsed = 'true'))"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_IS_RX_PDUINDEX_USED)
#error CANTSYN_IS_RX_PDUINDEX_USED is already defined
#endif /* if (defined CANTSYN_IS_RX_PDUINDEX_USED) */

#define CANTSYN_IS_RX_PDUINDEX_USED     STD_[!IF "(($isRxSyncUsed = 'true') or ($isRxOffsetUsed = 'true'))"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT)
#error CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT is already defined
#endif /* if (defined CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT) */

[!CALL "IsMasterTimeValidationSupported"!]
#define CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT STD_[!IF "$isMasterTimeValidationSupported = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined CANTSYN_SLAVE_TIME_DOMAIN_VALIDATION_SUPPORT)
#error CANTSYN_SLAVE_TIME_DOMAIN_VALIDATION_SUPPORT is already defined
#endif /* if (defined CANTSYN_SLAVE_TIME_DOMAIN_VALIDATION_SUPPORT) */

[!CALL "IsSlaveTimeValidationSupported"!]
#define CANTSYN_SLAVE_TIME_DOMAIN_VALIDATION_SUPPORT STD_[!IF "$isSlaveTimeValidationSupported = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined CANTSYN_TS_SIZE)
#error CANTSYN_TS_SIZE is already defined
#endif /* if (defined CANTSYN_TS_SIZE) */
#define CANTSYN_TS_SIZE [!"num:i($CanTSyn_TSSize)"!]U

/** \brief Support of CanTSyn_TxConfirmation() according to AUTOSAR R20-11.
  ** This constant defines whether the reliable TxConfirmation feature is used.
  ** STD_ON    feature is used
  ** STD_OFF   feature is not used
*/
#if (defined CANTSYN_RELIABLE_TXCONF)
#error CANTSYN_RELIABLE_TXCONF is already defined
#endif
/** \brief Pre-processor switch for supporting CanTSyn_TxConfirmation() according to AUTOSAR R20-11. */
#define CANTSYN_RELIABLE_TXCONF STD_[!IF "CanTSynGeneral/CanTSynReliableTxConfirmation = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Value of NetworkSegmentId when CanTSynEnableTimeValidation is false */
[!IF "($isMasterTimeValidationSupported = 'true') or ($isSlaveTimeValidationSupported = 'true')"!]
  #define CANTSYN_SEGMENTID_UNUSED 255U
[!ENDIF!]

/** \brief Switches the reporting of security events to IdsM.
  ** STD_ON     reporting is enabled.
  ** STD_OFF    reporting is disabled.
*/
#if (defined CANTSYN_ENABLE_SECURITY_EVENT_REPORTING)
#error CANTSYN_ENABLE_SECURITY_EVENT_REPORTING is already defined
#endif /* (defined CANTSYN_ENABLE_SECURITY_EVENT_REPORTING) */

/* !LINKSTO CanTSyn.ASR22-11.ECUC_CanTSyn_00055,1 */
#define CANTSYN_ENABLE_SECURITY_EVENT_REPORTING STD_[!IF "$isSecurityEventReportingEnabled = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Definitions of symbolic names for all ICV related references */
[!IF "$isSecurityEventReportingEnabled = 'true'"!]
  [!IF "node:exists(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE)"!]
#if (defined CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE)
#error CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE is already defined
#endif /* (defined CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE) */

#define CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE [!"node:value(as:ref(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE)/IdsMInternalEventId)"!]U
  [!ENDIF!]
  [!IF "node:exists(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_ICV_GENERATION_FAILED)"!]
#if (defined CANTSYN_SEV_ICV_GENERATION_FAILED)
#error CANTSYN_SEV_ICV_GENERATION_FAILED is already defined
#endif /* (defined CANTSYN_SEV_ICV_GENERATION_FAILED) */

#define CANTSYN_SEV_ICV_GENERATION_FAILED [!"node:value(as:ref(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_ICV_GENERATION_FAILED)/IdsMInternalEventId)"!]U
  [!ENDIF!]
  [!IF "node:exists(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_ICV_VERIFICATION_FAILED)"!]
#if (defined CANTSYN_SEV_ICV_VERIFICATION_FAILED)
#error CANTSYN_SEV_ICV_VERIFICATION_FAILED is already defined
#endif /* (defined CANTSYN_SEV_ICV_VERIFICATION_FAILED) */

#define CANTSYN_SEV_ICV_VERIFICATION_FAILED [!"node:value(as:ref(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_ICV_VERIFICATION_FAILED)/IdsMInternalEventId)"!]U
  [!ENDIF!]
  [!IF "node:exists(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR)"!]
#if (defined CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR)
#error CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR is already defined
#endif /* (defined CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR) */

#define CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR [!"node:value(as:ref(CanTSynGeneral/CanTSynSecurityEventRefs/CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR)/IdsMInternalEventId)"!]U
  [!ENDIF!]
[!ENDIF!]



/* !LINKSTO CanTSyn.ECUC_CanTSyn_00008,1 */
/** \brief Definitions of symbolic names for all CanTSynGlobalTimeMasterConfirmationHandleIds */
[!LOOP "util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[node:exists(CanTSynGlobalTimeMaster)], './CanTSynGlobalTimeDomainId'))"!]
  [!VAR "prefix" = "string('CanTSynConf_CanTSynGlobalTimeMasterPdu_')"!]
  [!VAR "masterConfirmationHandleId" = "num:i(node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimeMasterConfirmationHandleId))"!]
  [!VAR "timeDomainName" = "as:name(.)"!]
  [!VAR "finalDefineMaster" = "concat($prefix, $timeDomainName, string('  '), $masterConfirmationHandleId)"!]
#define [!"$finalDefineMaster"!]U
[!ENDLOOP!]

/* !LINKSTO CanTSyn.ECUC_CanTSyn_00013,1 */
/** \brief Definitions of symbolic names for all CanTSynGlobalTimeSlaveHandleIds */
[!LOOP "util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[node:exists(CanTSynGlobalTimeSlave)], './CanTSynGlobalTimeDomainId'))"!]
  [!VAR "prefix" = "string('CanTSynConf_CanTSynGlobalTimeSlavePdu_')"!]
  [!VAR "slaveHandleId" = "num:i(node:value(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimeSlaveHandleId))"!]
  [!VAR "timeDomainName" = "as:name(.)"!]
  [!VAR "finalDefineSlave" = "concat($prefix, $timeDomainName, string('  '), $slaveHandleId)"!]
#define [!"$finalDefineSlave"!]U
[!ENDLOOP!]

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

#define CANTSYN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

[!IF "$CanTSyn_TMSize != 0"!]
/** \brief CanTSyn Master configuration
 **
 ** This is the CanTSyn Master configuration.
 ** Please note that the name of this element is configuration dependent.
 */
extern CONST(CanTSyn_TimeMasterDomainConfigType, CANTSYN_APPL_CONST) CanTSyn_TimeMasterConfig[[!"num:i($CanTSyn_TMSize)"!]];
[!ENDIF!]

[!IF "$CanTSyn_TSSize != 0"!]
/** \brief CanTSyn Slave configuration
 **
 ** This is the CanTSyn Slave configuration.
 ** Please note that the name of this element is configuration dependent.
 */
extern CONST(CanTSyn_TimeSlaveDomainConfigType, CANTSYN_APPL_CONST) CanTSyn_TimeSlaveConfig[[!"num:i($CanTSyn_TSSize)"!]];
[!ENDIF!]

#define CANTSYN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef CANTSYN_CFG_H */

/*==================[end of file]============================================*/

[!ENDCODE!]


