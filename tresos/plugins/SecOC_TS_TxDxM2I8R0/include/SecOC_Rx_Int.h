/**
 * \file
 *
 * \brief AUTOSAR SecOC
 *
 * This file contains the implementation of the AUTOSAR
 * module SecOC.
 *
 * \version 2.8.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef SECOC_RX_INT_H
#define SECOC_RX_INT_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <SecOC.h>

#if (SECOC_NUMBER_RX_PDUS > 0)

#include <SecOC_Rx.h>

#include <TSMem.h>
#include <SchM_SecOC.h>
#include <PduR_SecOC.h>

#if (STD_ON == SECOC_PBCFGM_SUPPORT_ENABLED)
#include <PbcfgM.h>
#endif /* #if (STD_ON == SECOC_PBCFGM_SUPPORT_ENABLED) */

#if (STD_ON == SECOC_USE_META_DATA)
#include <EcuC.h>
#endif /* #if (STD_ON == SECOC_USE_META_DATA) */

#if (defined TS_RELOCATABLE_CFG_ENABLE)
#error TS_RELOCATABLE_CFG_ENABLE already defined!
#endif /* #if (defined TS_RELOCATABLE_CFG_ENABLE) */
#define TS_RELOCATABLE_CFG_ENABLE SECOC_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig_Access.h>
#include <TSPBConfig_Signature.h>

/*==================[macros]======================================================================*/

/* Relocatable post build elements access macros. */
#if (defined SECOC_RX_PBCFG_ACCESS)
#error SECOC_RX_PBCFG_ACCESS already defined
#endif /* #if (defined SECOC_RX_PBCFG_ACCESS) */
#define SECOC_RX_PBCFG_ACCESS(type, element)   \
    (TS_UNCHECKEDGETCFG(SecOC_ConfigPtr, type, SECOC, SecOC_ConfigPtr->element))

#if (defined SECOC_GET_RXPDU_CFG)
#error SECOC_GET_RXPDU_CFG already defined
#endif /* #if (defined SECOC_GET_RXPDU_CFG) */
#define SECOC_GET_RXPDU_CFG(Index)   \
    (SECOC_RX_PBCFG_ACCESS(SecOC_RxPduConfigType, RxPduConfigPtr)[(Index)])

#if (defined SECOC_GET_RX_DATA_ID)
#error SECOC_GET_RX_DATA_ID already defined
#endif /* #if (defined SECOC_GET_RX_DATA_ID) */
#define SECOC_GET_RX_DATA_ID(Index) (SECOC_GET_RXPDU_CFG(Index).DataId)

#if (defined SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR)
#error SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR already defined
#endif /* #if (defined SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR) */
#define SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(Index)   \
    (SECOC_GET_RXPDU_CFG(Index).AuthenticLayerPduIdAtPduR)

#if (STD_ON == SECOC_PDU_SECURED_AREA)
#if (defined SECOC_GET_RX_SECURED_AREA_LEN)
#error SECOC_GET_RX_SECURED_AREA_LEN already defined
#endif /* #if (defined SECOC_GET_RX_SECURED_AREA_LEN) */
#define SECOC_GET_RX_SECURED_AREA_LEN(Index) (SECOC_GET_RXPDU_CFG(Index).SecuredRxPduLength)

#if (defined SECOC_GET_RX_SECURED_AREA_OFFSET)
#error SECOC_GET_RX_SECURED_AREA_OFFSET already defined
#endif /* #if (defined SECOC_GET_RX_SECURED_AREA_OFFSET) */
#define SECOC_GET_RX_SECURED_AREA_OFFSET(Index) (SECOC_GET_RXPDU_CFG(Index).SecuredRxPduOffset)

#if (defined SECOC_GET_RX_USE_SECURED_AREA)
#error SECOC_GET_RX_USE_SECURED_AREA already defined
#endif /* #if (defined SECOC_GET_RX_USE_SECURED_AREA) */
#define SECOC_GET_RX_USE_SECURED_AREA(Index) (SECOC_GET_RXPDU_CFG(Index).UseRxSecuredArea)
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */

#if (defined SECOC_GET_RX_FRESHNESS_ID)
#error SECOC_GET_RX_FRESHNESS_ID already defined
#endif /* #if (defined SECOC_GET_RX_FRESHNESS_ID) */
#define SECOC_GET_RX_FRESHNESS_ID(Index) (SECOC_GET_RXPDU_CFG(Index).FreshnessValueId)

#if (defined SECOC_GET_RX_FRESHNESS_LEN)
#error SECOC_GET_RX_FRESHNESS_LEN already defined
#endif /* #if (defined SECOC_GET_RX_FRESHNESS_LEN) */
#define SECOC_GET_RX_FRESHNESS_LEN(Index) (SECOC_GET_RXPDU_CFG(Index).FreshnessValueLength)

#if (defined SECOC_GET_RX_FRESHNESSTX_LEN)
#error SECOC_GET_RX_FRESHNESSTX_LEN already defined
#endif /* #if (defined SECOC_GET_RX_FRESHNESSTX_LEN) */
#define SECOC_GET_RX_FRESHNESSTX_LEN(Index) (SECOC_GET_RXPDU_CFG(Index).FreshnessValueTxLength)

#if (defined SECOC_GET_RX_AUTHINFOTX_LEN)
#error SECOC_GET_RX_AUTHINFOTX_LEN already defined
#endif /* #if (defined SECOC_GET_RX_AUTHINFOTX_LEN) */
#define SECOC_GET_RX_AUTHINFOTX_LEN(Index) (SECOC_GET_RXPDU_CFG(Index).AuthInfoTxLength)

#if (SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED)
#if (defined SECOC_GET_RX_VERSTATUS_PROP_MODE)
#error SECOC_GET_RX_VERSTATUS_PROP_MODE already defined
#endif /* #if (defined SECOC_GET_RX_VERSTATUS_PROP_MODE) */
#define SECOC_GET_RX_VERSTATUS_PROP_MODE(Index)   \
    (SECOC_GET_RXPDU_CFG(Index).VerificationStatusPropagationMode)
#endif /* #if (STD_ON == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

#if (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)
#if (defined SECOC_GET_RX_CS_VERSTATUS_PROP_MODE)
#error SECOC_GET_RX_CS_VERSTATUS_PROP_MODE already defined
#endif /* #if (defined SECOC_GET_RX_CS_VERSTATUS_PROP_MODE) */
#define SECOC_GET_RX_CS_VERSTATUS_PROP_MODE(Index)   \
    (SECOC_GET_RXPDU_CFG(Index).CSVerificationStatusPropagationMode)
#endif /* #if (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP) */

#if (defined SECOC_GET_RX_RECVSECURED_PDU_ADR)
#error SECOC_GET_RX_RECVSECURED_PDU_ADR already defined
#endif /* #if (defined SECOC_GET_RX_RECVSECURED_PDU_ADR) */
#define SECOC_GET_RX_RECVSECURED_PDU_ADR(Index)    \
    (&SecOC_PB_PduBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.ReceivedSecuredPduBufferIndex])

#if (defined SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR)
#error SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR already defined
#endif /* #if (defined SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR) */
#define SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR(Index, Offset)    \
    (&SecOC_PB_PduBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.ReceivedSecuredPduBufferIndex + (Offset)])

#if (STD_ON == SECOC_RX_USE_SECURED_PDU_COL)
#if (defined SECOC_GET_RX_RECVAUTH_PDU_ADR)
#error SECOC_GET_RX_RECVAUTH_PDU_ADR already defined
#endif /* #if (defined SECOC_GET_RX_RECVAUTH_PDU_ADR) */
#define SECOC_GET_RX_RECVAUTH_PDU_ADR(Index)   \
    (&SecOC_PB_PduBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.ReceivedAuthPduBufferIndex])

#if (defined SECOC_GET_RX_CRYPTO_PDU_ADR)
#error SECOC_GET_RX_CRYPTO_PDU_ADR already defined
#endif /* #if (defined SECOC_GET_RX_CRYPTO_PDU_ADR) */
#define SECOC_GET_RX_CRYPTO_PDU_ADR(Index)     \
    (&SecOC_PB_PduBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.CryptoPduBufferIndex])
#endif /* #if (STD_ON == SECOC_RX_USE_SECURED_PDU_COL) */

#if (defined SECOC_GET_RX_SECURED_PDU_ADR)
#error SECOC_GET_RX_SECURED_PDU_ADR already defined
#endif /* #if (defined SECOC_GET_RX_SECURED_PDU_ADR) */
#define SECOC_GET_RX_SECURED_PDU_ADR(Index)    \
    (&SecOC_PB_PduBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.SecuredPduBufferIndex])

#if (defined SECOC_GET_RX_SECURED_PDU_OFFSET_ADR)
#error SECOC_GET_RX_SECURED_PDU_OFFSET_ADR already defined
#endif /* #if (defined SECOC_GET_RX_SECURED_PDU_OFFSET_ADR) */
#define SECOC_GET_RX_SECURED_PDU_OFFSET_ADR(Index, Offset)    \
    (&SecOC_PB_PduBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.SecuredPduBufferIndex + (Offset)])

#if (defined SECOC_GET_RX_SECURED_PDU_LEN)
#error SECOC_GET_RX_SECURED_PDU_LEN already defined
#endif /* #if (defined SECOC_GET_RX_SECURED_PDU_LEN) */
#define SECOC_GET_RX_SECURED_PDU_LEN(Index)    \
    (SECOC_GET_RXPDU_CFG(Index).BuffersConfig.SecuredPduBufferLength)

#if (defined SECOC_GET_RX_AUTH_PDU_LEN)
#error SECOC_GET_RX_AUTH_PDU_LEN already defined
#endif /* #if (defined SECOC_GET_RX_AUTH_PDU_LEN) */
#define SECOC_GET_RX_AUTH_PDU_LEN(Index)       \
    (SECOC_GET_RXPDU_CFG(Index).BuffersConfig.AuthPduBufferLength)

#if (defined SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN)
#error SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN already defined
#endif
#define SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN(Index)       \
    (SECOC_GET_RXPDU_CFG(Index).BuffersConfig.RecvAuthenticPduLength)

#if (STD_ON == SECOC_RX_USE_SECURED_PDU_COL)
#if (defined SECOC_GET_RX_CRYPTO_PDU_LEN)
#error SECOC_GET_RX_CRYPTO_PDU_LEN already defined
#endif /* #if (defined SECOC_GET_RX_CRYPTO_PDU_LEN) */
#define SECOC_GET_RX_CRYPTO_PDU_LEN(Index)     \
    (SECOC_GET_RXPDU_CFG(Index).BuffersConfig.CryptoPduBufferLength)
#endif /* #if (STD_ON == SECOC_RX_USE_SECURED_PDU_COL) */

#if (defined SECOC_GET_RX_AUTHENTICATOR_ADR)
#error SECOC_GET_RX_AUTHENTICATOR_ADR already defined
#endif /* #if (defined SECOC_GET_RX_AUTHENTICATOR_ADR) */
#define SECOC_GET_RX_AUTHENTICATOR_ADR(Index)  \
    (&SecOC_PB_IntBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.AuthenticatorIndex])

#if (defined SECOC_GET_RX_DATATOAUTH_ADR)
#error SECOC_GET_RX_DATATOAUTH_ADR already defined
#endif /* #if (defined SECOC_GET_RX_DATATOAUTH_ADR) */
#define SECOC_GET_RX_DATATOAUTH_ADR(Index)     \
    (&SecOC_PB_IntBuffer[SECOC_GET_RXPDU_CFG(Index).BuffersConfig.DataToAuthenticatorIndex])

/** \brief Macro to calculate the sum of the Rx authentication information length that is comprised
 *         of the truncated authenticator value and the truncated freshness value
 */
#if (defined SECOC_RX_AUTHENTICATION_INFO_LEN)
#error SECOC_RX_AUTHENTICATION_INFO_LEN already defined
#endif /* #if (defined SECOC_RX_AUTHENTICATION_INFO_LEN) */
#define SECOC_RX_AUTHENTICATION_INFO_LEN(Id) ((uint32)(SECOC_GET_RX_AUTHINFOTX_LEN((Id))) + \
                                              (uint32)(SECOC_GET_RX_FRESHNESSTX_LEN((Id))))

/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00149,1 */
#ifndef SECOC_VERIFICATIONSUCCESS
/** \brief Verification successful
 */
#define SECOC_VERIFICATIONSUCCESS                                                       0U
#endif /* #ifndef SECOC_VERIFICATIONSUCCESS */

#ifndef SECOC_VERIFICATIONFAILURE
/** \brief Verification not successful
 */
#define SECOC_VERIFICATIONFAILURE                                                       1U
#endif /* #ifndef SECOC_VERIFICATIONFAILURE */

#ifndef SECOC_FRESHNESSFAILURE
/** \brief Verification not successful because of wrong freshness value.
 */
#define SECOC_FRESHNESSFAILURE                                                          2U
#endif /* #ifndef SECOC_FRESHNESSFAILURE */

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
#ifndef SECOC_AUTHENTICATIONBUILDFAILURE
/** \brief Authentication could not be built. Freshness attempt or authentication calculation
 *         failure.(Compatible with AUTOSAR 430)
 */
#define SECOC_AUTHENTICATIONBUILDFAILURE                                      SECOC_FRESHNESSFAILURE
#endif /* #ifndef SECOC_AUTHENTICATIONBUILDFAILURE */
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
#ifndef SECOC_AUTHENTICATIONBUILDFAILURE
/** \brief Authentication could not be built. Freshness attempt or authentication calculation
 *         failure.(Compatible with AUTOSAR 20-11)
 */
#define SECOC_AUTHENTICATIONBUILDFAILURE                                                3U
#endif /* #ifndef SECOC_AUTHENTICATIONBUILDFAILURE */
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

#ifndef SECOC_NO_VERIFICATION
/** \brief Verification has been skipped.
 */
#define SECOC_NO_VERIFICATION                                                           4U
#endif /* #ifndef SECOC_NO_VERIFICATION */

#if (SECOC_API_VERSION_20_11 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
#ifndef SECOC_VERIFICATIONFAILURE_OVERWRITTEN

/** \brief Verification failed, but the I-PDU was passed on to the upper layer due to the override
 *          status for this PDU failure.
 */
#define SECOC_VERIFICATIONFAILURE_OVERWRITTEN                                           5U
#endif /* #ifndef SECOC_VERIFICATIONFAILURE_OVERWRITTEN */
#endif /* #if (SECOC_API_VERSION_20_11 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

#ifndef SECOC_MACSERVICEFAILURE
/** \brief Verification not successful because of wrong freshness value.
 */
#define SECOC_MACSERVICEFAILURE                                                         8U
#endif /* #ifndef SECOC_MACSERVICEFAILURE */

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
/** \brief indicates that a VerifyStatus shall be overwritten with fail until further notice
 */
#ifndef SECOC_OVERRIDESTATUS_FAIL
#define SECOC_OVERRIDESTATUS_FAIL                      0U
#endif /* #ifndef SECOC_OVERRIDESTATUS_FAIL */

/** \brief indicates that a VerifyStatus shall be overwritten with fail until a number of messages
 *         is reached
 */
#ifndef SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER
#define SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER           1U
#endif /* #ifndef SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER */

/** \brief indicates that a VerifyStatus shall not be overwritten any more
 */
#ifndef SECOC_OVERRIDESTATUS_CANCEL
#define SECOC_OVERRIDESTATUS_CANCEL                    2U
#endif /* #ifndef SECOC_OVERRIDESTATUS_CANCEL */

#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
/** \brief indicates that a VerifyStatus shall be overwritten with pass until a number of messages
 *         is reached
 */
#ifndef SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER
#define SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER          41U
#endif /* #ifndef SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER */

#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */

/** \brief indicates that the verification will not be performed
 */
#ifndef SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE
#define SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE        43U
#endif /* #ifndef SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE */

#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00991,1 */
/** \brief indicates that a VerifyStatus shall be overwritten with fail until further notice
 */
#ifndef SECOC_OVERRIDE_DROP_UNTIL_NOTICE
#define SECOC_OVERRIDE_DROP_UNTIL_NOTICE               0x00U
#endif /* #ifndef SECOC_OVERRIDE_DROP_UNTIL_NOTICE */

/** \brief indicates that a VerifyStatus shall be overwritten with fail until a number of messages
 *         is reached
 */
#ifndef SECOC_OVERRIDE_DROP_UNTIL_LIMIT
#define SECOC_OVERRIDE_DROP_UNTIL_LIMIT                0x01U
#endif /* #ifndef SECOC_OVERRIDE_DROP_UNTIL_LIMIT */

/** \brief indicates that a VerifyStatus shall not be overwritten any more
 */
#ifndef SECOC_OVERRIDE_CANCEL
#define SECOC_OVERRIDE_CANCEL                          0x02U
#endif /* #ifndef SECOC_OVERRIDE_CANCEL */

#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
/** \brief indicates that a VerifyStatus shall be overwritten with pass until further notice
 */
#ifndef SECOC_OVERRIDE_PASS_UNTIL_NOTICE
#define SECOC_OVERRIDE_PASS_UNTIL_NOTICE               0x40U
#endif /* #ifndef SECOC_OVERRIDE_PASS_UNTIL_NOTICE */

/** \brief indicates that the verification will not be performed until a number of messages
 *         is reached
 */
#ifndef SECOC_OVERRIDE_SKIP_UNTIL_LIMIT
#define SECOC_OVERRIDE_SKIP_UNTIL_LIMIT                0x41U
#endif /* #ifndef SECOC_OVERRIDE_SKIP_UNTIL_LIMIT */

/** \brief indicates that the verification shall be overwritten with pass until a number of messages
 *         is reached
 */
#ifndef SECOC_OVERRIDE_PASS_UNTIL_LIMIT
#define SECOC_OVERRIDE_PASS_UNTIL_LIMIT                0x42U
#endif /* #ifndef SECOC_OVERRIDE_PASS_UNTIL_LIMIT */

/** \brief indicates that the verification will not be performed until further notice
 */
#ifndef SECOC_OVERRIDE_SKIP_UNTIL_NOTICE
#define SECOC_OVERRIDE_SKIP_UNTIL_NOTICE               0x43U
#endif /* #ifndef SECOC_OVERRIDE_SKIP_UNTIL_NOTICE */

#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

/** \brief indicates that the reception overflow strategy is to reject the incoming PDU
 *         because SecOC is busy processing another PDU with the same PDU ID
 */
#if (defined SECOC_REJECT_INCOMING_PDU)
#error SECOC_REJECT_INCOMING_PDU already defined
#endif /* #if (defined SECOC_REJECT_INCOMING_PDU) */
#define SECOC_REJECT_INCOMING_PDU                0U

/** \brief indicates that the reception overflow strategy is to replace the current PDU which is
 *         under verification (if there is any)
 */
#if (defined SECOC_REPLACE_CURRENT_PDU)
#error SECOC_REPLACE_CURRENT_PDU already defined
#endif /* #if (defined SECOC_REPLACE_CURRENT_PDU) */
#define SECOC_REPLACE_CURRENT_PDU                1U

/** \brief indicates that the reception overflow strategy is to queue the incoming PDU
 *
 */
#if (defined SECOC_QUEUE_INCOMING_PDU)
#error SECOC_QUEUE_INCOMING_PDU already defined
#endif /* #if (defined SECOC_QUEUE_INCOMING_PDU) */
#define SECOC_QUEUE_INCOMING_PDU                 2U

/** \brief Macro, which defines what Rx internal data shall be used when calling the Csm service
 */
#if (defined SECOC_RX_CSM_JOB_ID)
#error SECOC_RX_CSM_JOB_ID already defined
#endif /* #if (defined SECOC_RX_CSM_JOB_ID) */
#if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON)
#define SECOC_RX_CSM_JOB_ID(Id)                  SecOC_RxData[(Id)].CsmJobIdPostDefined
#else /* #if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON) */
#define SECOC_RX_CSM_JOB_ID(Id)                  SecOC_RxConfig[(Id)].CsmJobId
#endif /* #if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON) */

/** \brief Macro, which defines what value shall be used when looking up Rx Pdus associated to the callback
 */
#if (defined SECOC_RX_CBK_ID)
#error SECOC_RX_CBK_ID already defined
#endif /* #if (defined SECOC_RX_CBK_ID) */
#define SECOC_RX_CBK_ID(Id)                      SecOC_RxCbkIdx[(Id)]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/** \brief Array holding the configuration of each configured RxPduProcessing
 */
extern CONST(SecOC_RxConfigType, SECOC_CONST) SecOC_RxConfig[SECOC_NUMBER_RX_PDUS];

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

#if (SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP > 0)
#if (SECOC_VERIFICATION_STATUS_PROP_ENABLED != SECOC_VERIFICATION_STATUS_PROP_NONE)
#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/**
 * \brief Variable which holds the configured callout functions for propagating the verification status
 */
extern CONST(SecOC_VerificationStatusCalloutType, SECOC_VAR) SecOC_RxVerificationStatusCallout[SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP];

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_ENABLED != SECOC_VERIFICATION_STATUS_PROP_NONE) */
#endif /* #if (SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP > 0) */

/*==================[external data]===============================================================*/

#define SECOC_START_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>

/** \brief Data structure holding the Data for Rx Pdus, which shall be verified.
 */
extern VAR(SecOC_RxDataType, SECOC_VAR) SecOC_RxData[SECOC_NUMBER_RX_PDUS];

#define SECOC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>

/*==================[external function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_VerifyStatusOverride_43
(
  P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) rxInstIdxList,
          uint16                               numberOfRxPdus,
          uint16                               freshnessValueId,
          uint8                                overrideStatus,
          uint8                                numberOfMessagesToOverride
);
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_VerifyStatusOverride_44
(
  P2CONST(uint16,                     AUTOMATIC, SECOC_APPL_CONST) rxInstIdxList,
          uint16                                                   numberOfRxPdus,
          uint16                                                   ValueId,
          SecOC_OverrideStatusType                                 overrideStatus,
          uint8                                                    numberOfMessagesToOverride
);
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#undef TS_RELOCATABLE_CFG_ENABLE

/*================================================================================================*/

#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#endif /* #ifndef SECOC_RX_INT_H */

/*==================[end of file]=================================================================*/

