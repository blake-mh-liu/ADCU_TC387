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

#ifndef SECOC_RX_CFG_H
#define SECOC_RX_CFG_H
[!SELECT "as:modconf('SecOC')"!][!//
/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

[!// This files contains macros for configuration values
[!INCLUDE "../../generate_macros/SecOC_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Rx_Macros.m"!][!//
[!//

[!IF "num:i(count(SecOCRxPduProcessing/*)) > 0"!][!//
#include <SecOC_Cfg.h>
[!ENDIF!][!//

/*==================[macros]======================================================================*/

/** \brief Number of configured Rx Pdus, which shall be verified by the SecOC module
 */
#if (defined SECOC_NUMBER_RX_PDUS)
#error SECOC_NUMBER_RX_PDUS already defined
#endif
#define SECOC_NUMBER_RX_PDUS [!"$RxPduNum"!]U

/** \brief Macro, which defines if user-defined main functions for RX PDUs are enabled or not
  *        STD_ON: User has configured main functions for RX PDUs
  *        STD_OFF: User has not configured any main functions for RX PDUs, default main functions will be used.
 */
#if (defined SECOC_USER_DEFINED_RX_MAINFUNCTIONS)
#error SECOC_USER_DEFINED_RX_MAINFUNCTIONS already defined
#endif
#define SECOC_USER_DEFINED_RX_MAINFUNCTIONS     [!IF "num:i(count(SecOCMainFunctionRx/*)) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "num:i(count(SecOCMainFunctionRx/*)) > 0"!][!//
[!LOOP "as:modconf('SecOC')/SecOCMainFunctionRx/*"!][!//
[!VAR "MainFuncRx" = "node:name(.)"!][!//
/** \brief Number of configured RX Pdus, which shall be verified by [!"node:name(node:current())"!] main function
 */
#if (defined SECOC_NUMBER_RX_PDUS_[!"text:toupper(node:name(.))"!])
#error SECOC_NUMBER_RX_PDUS_[!"text:toupper(node:name(.))"!] already defined
#endif
#define SECOC_NUMBER_RX_PDUS_[!"text:toupper(node:name(.))"!] [!"num:i(count(as:modconf('SecOC')/SecOCRxPduProcessing/*[node:name(as:ref(./SecOCRxPduMainFunctionRef)) = $MainFuncRx]))"!]U

[!ENDLOOP!][!//
[!ENDIF!][!//

/** \brief Macro, which defines if only the last verification status shall be reported or
 *         every verification attemp shall be reported
 */
#if (defined SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS)
#error SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS already defined
#endif
#define SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS [!IF "node:value(SecOCGeneral/SecOCPropagateOnlyFinalVerificationStatus) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the GetRxFreshnessAuthData function shall be used or not.
  *        STD_ON: The GetRxFreshnessAuthData function shall be used based on the configuration
  *        STD_OFF: The GetRxFreshnessAuthData function is not used
  */
#if (defined SECOC_RX_AUTH_DATA_FRESHNESS)
  #error SECOC_RX_AUTH_DATA_FRESHNESS is already defined
#endif
#define  SECOC_RX_AUTH_DATA_FRESHNESS [!IF "($UseGetRxFreshnessAuthData = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the GetRxFreshness function shall be used or not.
  *        STD_ON: The GetRxFreshness function shall be used based on the configuration
  *        STD_OFF: The GetRxFreshness function is not used
  */
#if (defined SECOC_RX_FRESHNESS)
  #error SECOC_RX_FRESHNESS is already defined
#endif
#define  SECOC_RX_FRESHNESS [!IF "($UseGetRxFreshness = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the Csm_MacVerify function shall be used or not.
  *        STD_ON: The Csm_MacVerify function shall be used based on the configuration
  *        STD_OFF: The Csm_MacVerify function is not used
  */
#if (defined SECOC_RX_USE_MACVERIFY)
  #error SECOC_RX_USE_MACVERIFY is already defined
#endif
#define  SECOC_RX_USE_MACVERIFY [!IF "$UseCsmMacVerify = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the Csm_SignatureVerify function shall be used or not.
  *        STD_ON: The Csm_SignatureVerify function shall be used based on the configuration
  *        STD_OFF: The Csm_SignatureVerify function is not used
  */
#if (defined SECOC_RX_USE_SIGNATUREVERIFY)
  #error SECOC_RX_USE_SIGNATUREVERIFY is already defined
#endif
#define  SECOC_RX_USE_SIGNATUREVERIFY [!IF "$UseCsmSignatureVerify = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined SECOC_RX_SYNC_PDU_PROCESSING)
#error SECOC_RX_SYNC_PDU_PROCESSING already defined
#endif
/** \brief Macro which defines whether there is at least one rx Pdu using synchronous processing or not.
*         STD_ON: One or more rx pdus are using synchronous processing
*         STD_OFF: Synchronous processing is not used by any rx Pdu
*/
/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00018,1 */
/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00019,1 */
#define SECOC_RX_SYNC_PDU_PROCESSING [!"node:when($RxUseSyncPduProcessing = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the secured PDU collection is used or not.
 *
 * STD_ON, if at least one Rx PDU is configured with the secured PDU collection.
 * STD_OFF, if no Rx PDU is configured with the secured PDU collection.
 */
#if (defined SECOC_RX_USE_SECURED_PDU_COL)
#error SECOC_RX_USE_SECURED_PDU_COL already defined
#endif
#define SECOC_RX_USE_SECURED_PDU_COL [!"node:when($RxUseSecuredCollection = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the message linker in the cryptographic Rx
 *         PDU is used or not.
 *
 * STD_ON, if at least one cryptographic PDU is configured to contain the message linker.
 * STD_OFF, if no cryptographic PDU is configured to contain the message linker.
 */
#if (defined SECOC_RX_USE_MESS_LINKER)
#error SECOC_RX_USE_MESS_LINKER already defined
#endif
#define SECOC_RX_USE_MESS_LINKER [!"node:when($RxUseMessageLink = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the shaping of the secured PDU on the Rx side
 *         will be performed or not
 *
 * STD_ON, if the shaping of the secured PDU will be performed.
 * STD_OFF, if the shaping of the secured PDU will not be performed.
 */
#if (defined SECOC_RX_SHAPE_SEC_PDU)
#error SECOC_RX_SHAPE_SEC_PDU already defined
#endif
#define SECOC_RX_SHAPE_SEC_PDU [!IF "'true' = node:exists(SecOCEbGeneral/SecOCRxShapeFuncName)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "'true' = node:exists(SecOCEbGeneral/SecOCRxShapeFuncName)"!]
/** \brief Macro, which defines the name of the shaping function on the Rx side
 */
#if (defined SECOC_RX_SHAPE_FUNC)
#error SECOC_RX_SHAPE_FUNC already defined
#endif
#define SECOC_RX_SHAPE_FUNC [!"SecOCEbGeneral/SecOCRxShapeFuncName"!]
[!ENDIF!]

/** \brief Macro, which defines whether the Csm services for the Rx side are used
 *         also in asynchronous mode.
 *
 * STD_ON, if asynchronous mode is used for at least one configured PDU.
 * STD_OFF, if asynchronous mode is not used.
 */
#if (defined SECOC_RX_CSM_ASYNC)
#error SECOC_RX_CSM_ASYNC already defined
#endif
#define SECOC_RX_CSM_ASYNC [!"node:when($RxUseCsmAsync = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the secured PDU header shall be used or not.
 *
 * STD_ON, the secured PDU header is enabled.
 * STD_OFF, the secured PDU header is disabled.
 */
#if (defined SECOC_RX_USE_SEC_PDU_HEADER)
#error SECOC_RX_USE_SEC_PDU_HEADER already defined
#endif
#define SECOC_RX_USE_SEC_PDU_HEADER [!"node:when($RxUseSecuredHeader = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Configuration switch indicating whether the "same buffer PDU collection" shall be used or not on the Rx side
 */
#if (defined SECOC_RX_USE_SAME_BUFFER)
#error SECOC_RX_USE_SAME_BUFFER already defined
#endif
#define SECOC_RX_USE_SAME_BUFFER [!"node:when($RxUseSameBufferPdu = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro switch for TP Interface for reception
 */
#if (defined SECOC_RX_USETP)
#error SECOC_RX_USETP already defined
#endif
#define SECOC_RX_USETP [!IF "count(SecOCRxPduProcessing/*[node:value(./SecOCRxAuthenticPduLayer/SecOCPduType)='SECOC_TPPDU']) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Configuration switch indicating whether the verification status shall be propagated for any Rx PDU
 */
#if (defined SECOC_VERIFICATION_STATUS_PROP_ENABLED)
#error SECOC_VERIFICATION_STATUS_PROP_ENABLED already defined
#endif
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) = 'SECOC_API_VERSION_430' or node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) = 'SECOC_API_VERSION_20_11'"!][!//
#define SECOC_VERIFICATION_STATUS_PROP_ENABLED                  SECOC_VERIFICATION_STATUS_PROP_AUTOSAR
[!ELSEIF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) = 'EB_CUSTOM'"!][!//
#define SECOC_VERIFICATION_STATUS_PROP_ENABLED                  SECOC_VERIFICATION_STATUS_PROP_EB
[!ELSE!][!//
#define SECOC_VERIFICATION_STATUS_PROP_ENABLED                  SECOC_VERIFICATION_STATUS_PROP_NONE
[!ENDIF!][!//

/** \brief Configuration switch indicating whether the verification status shall
 *         be propagated throw client server interface
 */
#if (defined SECOC_CS_VERIFICATION_STATUS_PROP)
#error SECOC_CS_VERIFICATION_STATUS_PROP already defined
#endif
#define SECOC_CS_VERIFICATION_STATUS_PROP [!IF "count(SecOCRxPduProcessing/*[node:value(./SecOCClientServerVerificationStatusPropagationMode)!='NONE']) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines the number of callout functions that propagates the verification status
 */
#if (defined SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP)
#error SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP already defined
#endif
#define SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP [!"num:i(count(SecOCGeneral/SecOCVerificationStatusCallout/*))"!]U

/** \brief Macro, which defines whether the MAC verification shall be performed on Secured I-PDU
 *
 * STD_ON, if verification is not performed.
 * STD_OFF, if verification is performed.
 */
#if (defined SECOC_SKIP_RX_PDU_VERIFICATION)
#error SECOC_SKIP_RX_PDU_VERIFICATION already defined
#endif
#define SECOC_SKIP_RX_PDU_VERIFICATION [!"node:when($RxSkipVerification = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the reception overflow strategy 'QUEUE' is used or not
 *
 * STD_ON, if the reception overflow strategy is set to 'QUEUE' for at least one configured PDU.
 * STD_OFF, if the reception overflow strategy 'QUEUE' is not used.
 */
#if (defined SECOC_QUEUE_INCOMING_PDU_ENABLED)
#error SECOC_QUEUE_INCOMING_PDU_ENABLED already defined
#endif
#define SECOC_QUEUE_INCOMING_PDU_ENABLED [!"node:when($RxUseRecvStrategyQueue = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the reception overflow strategy 'REPLACE' is used or not
 *
 * STD_ON, if the reception overflow strategy is set to 'REPLACE' for at least one configured PDU.
 * STD_OFF, if the reception overflow strategy 'REPLACE' is not used.
 */
#if (defined SECOC_REPLACE_CURRENT_PDU_ENABLED)
#error SECOC_REPLACE_CURRENT_PDU_ENABLED already defined
#endif
#define SECOC_REPLACE_CURRENT_PDU_ENABLED [!"node:when($RxUseRecvStrategyReplace = 'true', 'STD_ON', 'STD_OFF')"!]

#if (defined SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
#error SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION is already defined
#endif
/** \brief  This Macro determines the AUTOSAR version that is configured for VerifyStatusOverride **/
#define SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION [!"node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbVerifyStatusOverrideApiVersion)"!]

[!IF "'SECOC_API_VERSION_20_11' = node:value(SecOCEbGeneral/SecOCEbVerifyStatusOverrideApiVersion)"!][!//
#if (defined SECOC_USE_DATA_ID_FOR_OVERRIDE)
#error SECOC_USE_DATA_ID_FOR_OVERRIDE is already defined
#endif
/** \brief  This Macro determines if the data ID or the freshness value id is used for the Override API **/
#define SECOC_USE_DATA_ID_FOR_OVERRIDE [!IF "node:value(SecOCGeneral/SecOCOverrideStatusWithDataId) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!//
[!ENDIF!][!//

#if (defined SECOC_USE_META_DATA)
#error SECOC_USE_META_DATA is already defined
#endif
/** \brief  This Macro determines if the MetaData option is enabled or not **/
#define SECOC_USE_META_DATA [!IF "node:value(SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!//

/** \brief Macro, which defines whether the function SecOC_VerifyStatusOverride provides the ability
 *         to override the VerifyStatus with "pass" or not.
 *
 * STD_ON, if SecOC_VerifyStatusOverride provides the ability to set the result to "pass".
 * STD_OFF, if SecOC_VerifyStatusOverride does not provide the ability to set the result to "pass".
 */
#if (defined SECOC_OVERRIDE_VERIFYSTATUS_PASS)
#error SECOC_OVERRIDE_VERIFYSTATUS_PASS defined
#endif
#define SECOC_OVERRIDE_VERIFYSTATUS_PASS [!IF "'true' = node:value(SecOCGeneral/SecOCEnableForcedPassOverride)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro, which defines whether the verification result of the secured I-PDU shall be
 *         ignored.
 *
 * STD_ON,  verification result is ignored and PduR_SecOCRxIndication is called for secured I-PDU.
 * STD_OFF  only for verified secured I-PDU the PduR_SecOCRxIndication is called.
 */
#if (defined SECOC_IGNORE_VER_RESULT)
#error SECOC_IGNORE_VER_RESULT already defined
#endif
#define SECOC_IGNORE_VER_RESULT [!IF "'true' = node:value(SecOCGeneral/SecOcIgnoreVerificationResult)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro, which defines whether the FvM result of the secured I-PDU shall be
 *         ignored.
 *
 * STD_ON,  FvM function result is ignored and PduR_SecOCRxIndication is called for secured I-PDU.1
 * STD_OFF  FvM function result is not ignored
 */
#if (defined SECOC_IGNORE_FVM_FAILURES)
#error SECOC_IGNORE_FVM_FAILURES already defined
#endif
#define SECOC_IGNORE_FVM_FAILURES [!IF "'true' = node:value(SecOCEbGeneral/SecOCIgnoreFvMFailures)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

[!IF "num:i(count(SecOCMainFunctionRx/*)) > 0"!][!//
#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

[!LOOP "node:order(SecOCMainFunctionRx/*)"!][!//
/**
 * \brief List of RX instances assigned to [!"node:name(node:current())"!] main function
 */
extern CONST(uint16, SECOC_CONST) SecOC_RxInstIdxList_[!"node:name(.)"!][SECOC_NUMBER_RX_PDUS_[!"text:toupper(node:name(.))"!]];

[!ENDLOOP!][!//
#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>
[!ENDIF!][!//

[!IF "$RxUseCsmAsync = 'true'"!][!//
[!CALL "CreateJobRxPduAssoc"!][!//

#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>
/**
 * \brief List of translations between callback and Rx PDU ctx
 */
extern CONST(uint16, SECOC_CONST) SecOC_RxCbkIdx[[!"$cbkRxRefNum"!]U];

#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

[!IF "$RxPduNum > 0"!][!//
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

[!IF "'true' = node:exists(SecOCEbGeneral/SecOCRxShapeFuncName)"!][!//
/** \brief This interface is used by the SecOC to remove the padding within the secured PDU.
 **
 ** \param[in]      SecOCPduID          Holds the identifier of the secured PDU
 **                                     or the identifier of the received authentic PDU,
 **                                     when the Secured PDU Collection is used, at SecOC.
 ** \param[in,out]  SecPdu              Holds the secured PDU.
 ** \param[in]      SrcSecPduLength     Holds the length of the received secured PDU.
 ** \param[in,out]  DstSecPduLength     in: Holds the maximum length of the secured PDU.
 **                                     out:Holds the length of the secured PDU without the padding.
 ** \param[in]      AuthenticatorLength Holds the length of the authenticator.
 **/
extern FUNC(void, SECOC_APPL_CODE) [!"SecOCEbGeneral/SecOCRxShapeFuncName"!]
(
          PduIdType                                  SecOCPduID,
    P2VAR(uint8,         AUTOMATIC, SECOC_APPL_DATA) SecPdu,
  P2CONST(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) SrcSecPduLength,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) DstSecPduLength,
          uint32                                     AuthenticatorLength
);

[!ENDIF!][!//
[!//
[!IF "$RxUsePropVerStatus = 'true'"!][!//
[!LOOP "SecOCGeneral/SecOCVerificationStatusCallout/*"!][!//
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00119,1 */
/** \brief Function which reports the status of the verification procedure
 **
 ** \param[in] verificationStatus  Holds the pointer to the memory location where the
 **                               the status of the MAC Verification service is stored.
 **/
extern FUNC(void, SECOC_APPL_CODE) [!"node:value(.)"!]
(
  SecOC_VerificationStatusType verificationStatus
);

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
[!VAR "lastFuncName" = "''"!][!//
[!LOOP "node:order(SecOCRxPduProcessing/*[SecOCUseAuthDataFreshness = 'false'], './SecOCFreshnessValueFuncName')"!][!//
[!IF "$lastFuncName != node:value(./SecOCFreshnessValueFuncName)"!][!//
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00250,3 */
/**
 ** \brief This interface is used by the SecOC to obtain the current freshness value.
 **
 ** \param[in]   SecOCFreshnessValueID              Holds the identifier of the freshness value.
 ** \param[in]   SecOCTruncatedFreshnessValue       Holds the truncated freshness value that was
 **                                                 contained in the Secured I-PDU.
 ** \param[in]   SecOCTruncatedFreshnessValueLength Holds the length in bits of the truncated
 **                                                 freshness value.
 ** \param[in]   SecOCCounterSyncAttempts           Holds the number of authentication verify
 **                                                 attempts of this PDU since the last reception.
 **                                                 The value is 0 for the first attempt and
 **                                                 incremented on every unsuccessful verification
 **                                                 attempt.
 ** \param[out]  SecOCFreshnessValue                Holds the freshness value to be used for the
 **                                                 calculation of the authenticator.
 ** \param[in]   SecOCFreshnessValueLength          Holds the length in bits of the freshness value.
 **
 ** \returns whether the request was successful or not.
 ** \retval E_OK     Request successful.
 ** \retval E_NOT_OK Request failed, a freshness value cannot be provided due to general issues for
 **                  freshness or this FreshnessValueId.
 ** \retval E_BUSY   The freshness information can temporarily not be provided.
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) [!"node:value(./SecOCFreshnessValueFuncName)"!]
(
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
          uint16                              SecOCCounterSyncAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!VAR "lastFuncName" = "node:value(./SecOCFreshnessValueFuncName)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!VAR "lastFuncName" = "''"!][!//
[!LOOP "node:order(SecOCRxPduProcessing/*[SecOCUseAuthDataFreshness = 'true'], './SecOCFreshnessValueFuncName')"!][!//
[!IF "$lastFuncName != node:value(./SecOCFreshnessValueFuncName)"!][!//
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_91006,1 */
/**
 ** \brief This interface is used by the SecOC to obtain the current freshness value.
 **
 ** \param[in]   SecOCFreshnessValueID              Holds the identifier of the freshness value.
 ** \param[in]   SecOCTruncatedFreshnessValue       Holds the truncated freshness value that was
 **                                                 contained in the Secured I-PDU.
 ** \param[in]   SecOCTruncatedFreshnessValueLength Holds the length in bits of the truncated
 **                                                 freshness value.
 ** \param[in]   SecOCAuthDataFreshnessValue        The parameter holds a part of the
 **                                                 received, not yet authenticated PDU.
 ** \param[in]   SecOCAuthDataFreshnessValueLength  This is the length value in bits that holds
 **                                                 the freshness from the authentic PDU.
 ** \param[in]   SecOCAuthVerifyAttempts            Holds the number of authentication verify
 **                                                 attempts of this PDU since the last reception.
 **                                                 The value is 0 for the first attempt and
 **                                                 incremented on every unsuccessful verification
 **                                                 attempt.
 ** \param[out]  SecOCFreshnessValue                Holds the freshness value to be used for the
 **                                                 calculation of the authenticator.
 ** \param[in]   SecOCFreshnessValueLength          Holds the length in bits of the freshness value.
 **
 ** \returns whether the request was successful or not.
 ** \retval E_OK     Request successful.
 ** \retval E_NOT_OK Request failed, a freshness value cannot be provided due to general issues for
 **                  freshness or this FreshnessValueId.
 ** \retval E_BUSY   The freshness information can temporarily not be provided.
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) [!"node:value(./SecOCFreshnessValueFuncName)"!]
(
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCAuthDataFreshnessValue,
          uint16                              SecOCAuthDataFreshnessValueLength,
          uint16                              SecOCAuthVerifyAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!VAR "lastFuncName" = "node:value(./SecOCFreshnessValueFuncName)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "'false' = node:value(SecOCEbGeneral/SecOCRteUsage)"!]
[!LOOP "SecOCMainFunctionRx/*"!][!//
/**
 ** \brief This function performs the processing of the SecOC module's
 **        verification for the Rx path (for the Rx PDUs which where configured to be handled by
 **        this main function).
 **/
#ifndef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONRX_[!"text:toupper(node:name(.))"!]
#define RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONRX_[!"text:toupper(node:name(.))"!]
extern FUNC(void, SECOC_CODE) SecOC_MainFunctionRx_[!"node:name(.)"!](void);
#endif /* #ifndef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONRX_[!"text:toupper(node:name(.))"!] */

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
[!IF "$UseGetRxFreshness = 'true'"!][!//
/** \brief  This function is used by SecOC to provide the freshenss from the received secured PDU
 **         and to obtain the current freshness which shall be used for the verification procedure.
 **
 ** \param[in]   instId                              Identifier of the state machine instance.
 ** \param[in]   SecOCFreshnessValueID               Holds the identifier of the freshness.
 ** \param[out]  SecOCTruncatedFreshnessValue        Holds the pointer to the memory location where
 **                                                  the freshenss from the received secured PDU
 **                                                  shall be stored.
 ** \param[in]   SecOCTruncatedFreshnessValueLength  Holds the pointer to the memory location where
 **                                                  the length in bits of the freshness from the
 **                                                  secured PDU is stored.
 ** \param[in]   SecOCAuthVerifyAttempts             Holds the number of authentication verify
 **                                                  attempts of this PDU since the last reception.
 **                                                  The value is 0 for the first attempt and
 **                                                  incremented on every unsuccessful verification
 **                                                  attempt.
 ** \param[out]  SecOCFreshnessValue                 Holds the pointer to the memory location where
 **                                                  the freshenss used to authentication shall be
 **                                                  stored.
 ** \param[in]   SecOCFreshnessValueLength           Holds a pointer to the memory location in which
 **                                                  the length in bits of the required freshness
 **                                                  for authentication is stored.
 **
 ** \returns  Result of the request.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   E_BUSY                  request failed, service is still busy
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant for different freshenss ID}
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_Freshness
(
          uint16                              instId,
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
          uint16                              SecOCCounterSyncAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!ENDIF!][!//
[!//
[!IF "$UseGetRxFreshnessAuthData = 'true'"!][!//
/** \brief  This function is used by SecOC to provide the freshenss from the received secured PDU
 **         and to obtain the current freshness which shall be used for the verification procedure.
 **         It provides also a part of the payload via SecOCAuthDataFreshnessValue.
 **
 ** \param[in]   instId                              Identifier of the state machine instance.
 ** \param[out]  SecOCTruncatedFreshnessValue        Holds the pointer to the memory location where
 **                                                  the freshenss from the received secured PDU
 **                                                  shall be stored.
 ** \param[in]   SecOCTruncatedFreshnessValueLength  Holds the pointer to the memory location where
 **                                                  the length in bits of the freshness from the
 **                                                  secured PDU is stored.
 ** \param[in]   SecOCAuthDataFreshnessValue         Holds the pointer to the memory location where
 **                                                  a part of the payload from the received
 **                                                  secured PDU, not yet authenticated is stored.
 ** \param[in]   SecOCAuthDataFreshnessValueLength   Holds the pointer to the memory location where
 **                                                  the length in bits of the provided data is stored.
 ** \param[in]   SecOCAuthVerifyAttempts             Holds the number of authentication verify
 **                                                  attempts of this PDU since the last reception.
 **                                                  The value is 0 for the first attempt and
 **                                                  incremented on every unsuccessful verification
 **                                                  attempt.
 ** \param[out]  SecOCFreshnessValue                 Holds the pointer to the memory location where
 **                                                  the freshenss used to authentication shall be
 **                                                  stored.
 ** \param[in]   SecOCFreshnessValueLength           Holds a pointer to the memory location in which
 **                                                  the length in bits of the required freshness
 **                                                  for authentication is stored.
 **
 ** \returns  Result of the request.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   E_BUSY                  request failed, service is still busy
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant for different freshenss ID}
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_Freshness_AuthData
(
          uint16                              instId,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCAuthDataFreshnessValue,
          uint16                              SecOCAuthDataFreshnessValueLength,
          uint16                              SecOCAuthVerifyAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) != 'NONE' and 'true' = node:value(SecOCEbGeneral/SecOCRteUsage)"!][!//
/** \brief This function is used to report the status of the MAC Verification service via
 **        a sender receiver interface type..
 **
 ** \param[in]  instId                      Identifier of the state machine instance.
 ** \param[in]  SecOC_RxVerificationStatus  Holds the pointer to the memory location where the
 **                                         the status of the MAC Verification service is stored.
 **/
extern FUNC(void, SECOC_CODE) SecOC_Rx_Write_VerificationStatus
(
        uint16                                                    instId,
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
);

[!ENDIF!][!//
[!//
[!IF "node:value(SecOCEbGeneral/SecOCEbClientServerPropagateVerificationStatusApiVersion) != 'NONE'"!][!//
/** \brief This function is used to report the status of the MAC Verification service via
 **        a client server interface type.
 **
 ** \param[in]  instId                      Identifier of the state machine instance.
 ** \param[in]  SecOC_RxVerificationStatus  Holds the pointer to the memory location where the
 **                                         the status of the MAC Verification service is stored.
 **/
extern FUNC(void, SECOC_CODE) SecOC_Rx_Call_VerificationStatusIndication
(
        uint16                                                    instId,
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
);

[!ENDIF!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!ENDSELECT!][!//
#endif /* #ifndef SECOC_RX_CFG_H */

/*==================[end of file]=================================================================*/
