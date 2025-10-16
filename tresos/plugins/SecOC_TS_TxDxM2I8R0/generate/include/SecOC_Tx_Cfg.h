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

#ifndef SECOC_TX_CFG_H
#define SECOC_TX_CFG_H
[!SELECT "as:modconf('SecOC')"!][!//
/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

[!// This files contains macros for configuration values
[!INCLUDE "../../generate_macros/SecOC_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Tx_Macros.m"!][!//
[!//

[!IF "$TxPduNum > 0"!][!//
#include <SecOC_Cfg.h>
[!ENDIF!][!//

/*==================[macros]======================================================================*/

/** \brief Number of configured Tx Pdus, which shall be authenticated by the SecOC module
 */
#if (defined SECOC_NUMBER_TX_PDUS)
#error SECOC_NUMBER_TX_PDUS already defined
#endif
#define SECOC_NUMBER_TX_PDUS [!"$TxPduNum"!]U

/** \brief Macro, which defines if user-defined main functions for TX PDUs are enabled or not
  *        STD_ON: User has configured main functions for TX PDUs
  *        STD_OFF: User has not configured any main functions for TX PDUs, default main functions will be used.
 */
#if (defined SECOC_USER_DEFINED_TX_MAINFUNCTIONS)
#error SECOC_USER_DEFINED_TX_MAINFUNCTIONS already defined
#endif
#define SECOC_USER_DEFINED_TX_MAINFUNCTIONS     [!IF "num:i(count(SecOCMainFunctionTx/*)) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "num:i(count(SecOCMainFunctionTx/*)) > 0"!][!//
[!LOOP "as:modconf('SecOC')/SecOCMainFunctionTx/*"!][!//
[!VAR "MainFuncTx" = "node:name(.)"!][!//
/** \brief Number of configured TX Pdus, which shall be authenticated by [!"node:name(node:current())"!] main function
 */
#if (defined SECOC_NUMBER_TX_PDUS_[!"text:toupper(node:name(.))"!])
#error SECOC_NUMBER_TX_PDUS_[!"text:toupper(node:name(.))"!] already defined
#endif
#define SECOC_NUMBER_TX_PDUS_[!"text:toupper(node:name(.))"!] [!"num:i(count(as:modconf('SecOC')/SecOCTxPduProcessing/*[node:name(as:ref(./SecOCTxPduMainFunctionRef)) = $MainFuncTx]))"!]U

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
/** \brief Macro which defines whether the GetTxFreshnessTruncData function shall be used or not.
  *        STD_ON: The GetTxFreshnessTruncData function shall be used based on the configuration
  *        STD_OFF: The GetTxFreshnessTruncData function is not used
  */
#if (defined SECOC_TX_FRESHNESS_TRUNC_DATA)
  #error SECOC_TX_FRESHNESS_TRUNC_DATA is already defined
#endif
#define  SECOC_TX_FRESHNESS_TRUNC_DATA [!IF "($UseGetTxFreshnessTruncData = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the GetTxFreshness function shall be used or not.
  *        STD_ON: The GetTxFreshness function shall be used based on the configuration
  *        STD_OFF: The GetTxFreshness function is not used
  */
#if (defined SECOC_TX_FRESHNESS)
  #error SECOC_TX_FRESHNESS is already defined
#endif
#define  SECOC_TX_FRESHNESS [!IF "($UseGetTxFreshness = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the Csm_MacGenerate function shall be used or not.
  *        STD_ON: The Csm_MacGenerate function shall be used based on the configuration
  *        STD_OFF: The Csm_MacGenerate function is not used
  */
#if (defined SECOC_TX_USE_MACGENERATE)
  #error SECOC_TX_USE_MACGENERATE is already defined
#endif
#define  SECOC_TX_USE_MACGENERATE [!IF "$UseCsmMacGenerate = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the Csm_SignatureGenerate function shall be used or not.
  *        STD_ON: The Csm_SignatureGenerate function shall be used based on the configuration
  *        STD_OFF: The Csm_SignatureGenerate function is not used
  */
#if (defined SECOC_TX_USE_SIGNATUREGENERATE)
  #error SECOC_TX_USE_SIGNATUREGENERATE is already defined
#endif
#define  SECOC_TX_USE_SIGNATUREGENERATE [!IF "$UseCsmSignatureGenerate = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined SECOC_TX_SYNC_PDU_PROCESSING)
#error SECOC_TX_SYNC_PDU_PROCESSING already defined
#endif
/** \brief Macro which defines whether there is at least one tx Pdu using synchronous processing or not.
*         STD_ON: One or more tx pdus are using synchronous processing
*         STD_OFF: Synchronous processing is not used by any tx Pdu
*/
/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00024,1 */
/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00025,1 */
#define SECOC_TX_SYNC_PDU_PROCESSING [!"node:when($TxUseSyncPduProcessing = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the secured PDU collection is used or not.
 *
 * STD_ON, if at least one Tx PDU is configured with the secured PDU collection.
 * STD_OFF, if no Tx PDU is configured with the secured PDU collection.
 */
#if (defined SECOC_TX_USE_SECURED_PDU_COL)
#error SECOC_TX_USE_SECURED_PDU_COL already defined
#endif
#define SECOC_TX_USE_SECURED_PDU_COL [!"node:when($TxUseSecuredCollection = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the message linker in the cryptographic Tx PDU
 *         is used or not.
 *
 * STD_ON, if at least one cryptographic PDU is configured to contain the message linker.
 * STD_OFF, if no cryptographic PDU is configured to contain the message linker.
 */
#if (defined SECOC_TX_USE_MESS_LINKER)
#error SECOC_TX_USE_MESS_LINKER already defined
#endif
#define SECOC_TX_USE_MESS_LINKER [!"node:when($TxUseMessageLink = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the shaping of the secured PDU on the Tx side
 *         will be performed or not
 *
 * STD_ON, if the shaping of the secured PDU will be performed.
 * STD_OFF, if the shaping of the secured PDU will not be performed.
 */
#if (defined SECOC_TX_SHAPE_SEC_PDU)
#error SECOC_TX_SHAPE_SEC_PDU already defined
#endif
#define SECOC_TX_SHAPE_SEC_PDU [!IF "'true' = node:exists(SecOCEbGeneral/SecOCTxShapeFuncName)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "'true' = node:exists(SecOCEbGeneral/SecOCTxShapeFuncName)"!][!//
/** \brief Macro, which defines the name of the shaping function on the Tx side
 */
#if (defined SECOC_TX_SHAPE_FUNC)
#error SECOC_TX_SHAPE_FUNC already defined
#endif
#define SECOC_TX_SHAPE_FUNC [!"SecOCEbGeneral/SecOCTxShapeFuncName"!]

[!ENDIF!][!//
[!//
/** \brief Macro, which defines whether the Csm services for the Tx side are used
 *         also in asynchronous mode.
 *
 * STD_ON, if asynchronous mode is used for at least one configured PDU.
 * STD_OFF, if asynchronous mode is not used.
 */
#if (defined SECOC_TX_CSM_ASYNC)
#error SECOC_TX_CSM_ASYNC already defined
#endif
#define SECOC_TX_CSM_ASYNC [!"node:when($TxUseCsmAsync = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether the secured PDU header shall be used or not.
 *
 * STD_ON, the secured PDU header is enabled.
 * STD_OFF, the secured PDU header is disabled.
 */
#if (defined SECOC_TX_USE_SEC_PDU_HEADER)
#error SECOC_TX_USE_SEC_PDU_HEADER already defined
#endif
#define SECOC_TX_USE_SEC_PDU_HEADER [!"node:when($TxUseSecuredHeader = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Configuration switch indicating whether the "same buffer PDU collection" shall be used or not on the Tx side
 */
#if (defined SECOC_TX_USE_SAME_BUFFER)
#error SECOC_TX_USE_SAME_BUFFER already defined
#endif
#define SECOC_TX_USE_SAME_BUFFER [!"node:when($TxUseSameBufferPdu = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro switch for TP Interface for transmission
 */
#if (defined SECOC_TX_USETP)
#error SECOC_TX_USETP already defined
#endif
#define SECOC_TX_USETP [!IF "count(SecOCTxPduProcessing/*[node:value(./SecOCTxAuthenticPduLayer/SecOCPduType)='SECOC_TPPDU']) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Configuration switch indicating whether the MAC Generate status shall be propagated for any Tx PDU
 */
#if (defined SECOC_MACGENERATE_STATUS_PROP_ENABLED)
#error SECOC_MACGENERATE_STATUS_PROP_ENABLED already defined
#endif
#define SECOC_MACGENERATE_STATUS_PROP_ENABLED [!"node:when($TxUseMacStatusPropagate = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro which defines the number of callout functions that propagates the MAC Generate status
 */
#if (defined SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP)
#error SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP already defined
#endif
#define SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP [!"num:i(count(SecOCGeneral/SecOCMacGenerateStatusCallout/*))"!]U

/** \brief Macro, which defines whether the Tx confirmation timeout is used or not.
 *
 * STD_ON, if Tx confirmation timeout is used.
 * STD_OFF, if Tx confirmation timeout is not used.
 */
#if (defined SECOC_USE_TX_CONFIRMATION_TIMEOUT)
#error SECOC_USE_TX_CONFIRMATION_TIMEOUT already defined
#endif
#define SECOC_USE_TX_CONFIRMATION_TIMEOUT [!"node:when($TxUseConfirmationTimeout = 'true', 'STD_ON', 'STD_OFF')"!]

/** \brief Macro, which defines whether SecOC provides the ability to bypass the authentication routine or not
 *
 * STD_ON, the bypass mechanism is available
 * STD_OFF, the bypass mechanism is not available
 */
#if (defined SECOC_BYPASS_AUTHENTICATION_ROUTINE)
#error SECOC_BYPASS_AUTHENTICATION_ROUTINE already defined
#endif
#define SECOC_BYPASS_AUTHENTICATION_ROUTINE [!IF "'true' = node:exists(SecOCEbGeneral/SecOCBypassAuthenticationRoutine)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "'true' = node:exists(SecOCEbGeneral/SecOCBypassAuthenticationRoutine)"!][!//
/** \brief Macro, which defines the default authentication information value that shall be used
 *         to create the secured PDU when the bypass mechanism is enabled.
 */
#if (defined SECOC_BYPASS_DEFAULT_AUTHINFO_VALUE)
#error SECOC_BYPASS_DEFAULT_AUTHINFO_VALUE already defined
#endif
#define SECOC_BYPASS_DEFAULT_AUTHINFO_VALUE [!"num:i(SecOCEbGeneral/SecOCBypassAuthenticationRoutine/SecOCDefaultAuthenticationInfoValue)"!]U

[!ENDIF!][!//
[!//
/** \brief Macro, which defines whether SecOC sends secured PDUS when the MAC could not be
 *         generated and is replaced by the configured default MAC.
 *
 * STD_ON, the secured PDUS are sent with the default configured MAC when the MAC could not be generated.
 * STD_OFF, the secured PDUS are not sent when the MAC could not be generated.
 */
#if (defined SECOC_USE_DEFAULT_AUTH)
#error SECOC_USE_DEFAULT_AUTH already defined
#endif
#define SECOC_USE_DEFAULT_AUTH [!IF "'true' = node:exists(SecOCEbGeneral/SecOCDefaultAuthenticatorValue)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "'true' = node:exists(SecOCEbGeneral/SecOCDefaultAuthenticatorValue)"!][!//
/** \brief Macro, which defines the default MAC value that shall be used to create the secured PDU
 *         when the MAC could not be generated.
 */
#if (defined SECOC_DEFAULT_AUTH_VALUE)
#error SECOC_DEFAULT_AUTH_VALUE already defined
#endif
#define SECOC_DEFAULT_AUTH_VALUE [!"num:i(SecOCEbGeneral/SecOCDefaultAuthenticatorValue)"!]U

[!ENDIF!][!//
[!//
/** \brief Macro, which defines whether SecOC sends secured PDUS when the authentication build counter
 *         has reached the configuration value SecOCAuthenticationBuildAttempts or the query of the freshness
 *         function returns E_NOT_OK or the calculation of the authenticator has returned a non-recoverable error.
 *         The authenticator is replaced by the configured default pattern.
 *
 * STD_ON, the secured PDUS are sent with the default configured authentication information pattern
 * STD_OFF, the secured PDUS are not sent upon failure
 */
#if (defined SECOC_USE_DEFAULT_AUTH_INFO_PATTERN)
#error SECOC_USE_DEFAULT_AUTH_INFO_PATTERN already defined
#endif
#define SECOC_USE_DEFAULT_AUTH_INFO_PATTERN [!IF "'true' = node:exists(SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "'true' = node:exists(SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!][!//
/** \brief Macro, which defines the value of the default authentication information pattern
 */
#if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_VALUE)
#error SECOC_DEFAULT_AUTH_INFO_PATTERN_VALUE already defined
#endif
#define SECOC_DEFAULT_AUTH_INFO_PATTERN_VALUE [!"num:i(SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!]U

[!ENDIF!][!//
[!//
/** \brief Macro, which defines whether the function SecOC_SPduTxConfirmation call is enabled.
 *
 * STD_ON, the function SecOC_SPduTxConfirmation call is enabled.
 * STD_OFF, the function SecOC_SPduTxConfirmation call is disabled.
 */
#if (defined SECOC_USE_TX_SPDU_CONFIRMATION)
#error SECOC_USE_TX_SPDU_CONFIRMATION already defined
#endif
#define SECOC_USE_TX_SPDU_CONFIRMATION [!IF "'true' = $TxUseSPduConfirmation"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

[!IF "num:i(count(SecOCMainFunctionTx/*)) > 0"!][!//
#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

[!LOOP "node:order(SecOCMainFunctionTx/*)"!][!//
/**
 * \brief List of TX instances assigned to [!"node:name(node:current())"!] main function
 */
extern CONST(uint16, SECOC_CONST) SecOC_TxInstIdxList_[!"node:name(.)"!][SECOC_NUMBER_TX_PDUS_[!"text:toupper(node:name(.))"!]];

[!ENDLOOP!][!//
#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!//
[!IF "$TxUseCsmAsync = 'true'"!][!//
[!CALL "CreateJobTxPduAssoc"!][!//
#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

/**
 * \brief List of translations between callback and Tx PDU ctx
 */
extern CONST(uint16, SECOC_CONST) SecOC_TxCbkIdx[[!"$cbkTxRefNum"!]U];

#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

[!IF "$TxPduNum > 0"!][!//
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

[!IF "'true' = node:exists(SecOCEbGeneral/SecOCTxShapeFuncName)"!][!//
/** \brief This interface is used by the SecOC to to add the required padding within
 **         the secured PDU to maintain a fixed layout.
 **
 ** \param[in]      SecOCPduID           Holds the identifier of the received authentic PDU at SecOC.
 ** \param[in,out]  SecPdu               Holds the secured PDU.
 ** \param[in]      SrcSecPduLength      Holds the length of the generated secured PDU without
 **                                      the required padding.
 ** \param[in,out]  DstSecPduLength      in:  Holds the maximum length of the secured PDU.
 **                                      out: Holds the length of the secured PDU with the padding.
 ** \param[in]      AuthenticatorLength  Holds the length of the authenticator.
 **/
extern FUNC(void, SECOC_APPL_CODE) [!"SecOCEbGeneral/SecOCTxShapeFuncName"!]
(
          PduIdType                                  SecOCPduID,
    P2VAR(uint8,         AUTOMATIC, SECOC_APPL_DATA) SecPdu,
  P2CONST(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) SrcSecPduLength,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) DstSecPduLength,
          uint32                                     AuthenticatorLength
);

[!ENDIF!][!//
[!//
[!IF "$TxUseMacStatusPropagate = 'true'"!][!//
[!LOOP "SecOCGeneral/SecOCMacGenerateStatusCallout/*"!][!//
/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00013,2 */
/** \brief Function which reports the status of the MAC Generate service
 **
 ** \param[in]  macGenerateStatus  Holds the pointer to the memory location where the
 **                                the status of the MAC Generate service is stored.
 **/
extern FUNC(void, SECOC_APPL_CODE) [!"node:value(.)"!]
(
  SecOC_MacGenerateStatusType macGenerateStatus
);

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
[!VAR "lastFuncName" = "''"!][!//
[!LOOP "node:order(SecOCTxPduProcessing/*[SecOCProvideTxTruncatedFreshnessValue = 'false'], './SecOCFreshnessValueFuncName')"!][!//
[!IF "$lastFuncName != node:value(./SecOCFreshnessValueFuncName)"!][!//
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00231,3 */
/**
 ** \brief This interface is used by the SecOC to obtain the current freshness value.
 **
 ** \param[in]   SecOCFreshnessValueID      Holds the identifier of the freshness value.
 ** \param[out]  SecOCFreshnessValue        Holds the current freshness value.
 ** \param[in]   SecOCFreshnessValueLength  Holds the length of the required freshness value in bits.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed, a freshness value cannot be provided due to general issues
 **                    for freshness or this FreshnessValueId.
 ** \retval  E_BUSY    The freshness information can temporarily not be provided.
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) [!"node:value(./SecOCFreshnessValueFuncName)"!]
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!VAR "lastFuncName" = "node:value(./SecOCFreshnessValueFuncName)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!VAR "lastFuncName" = "''"!][!//
[!LOOP "node:order(SecOCTxPduProcessing/*[SecOCProvideTxTruncatedFreshnessValue = 'true'], './SecOCFreshnessValueFuncName')"!][!//
[!IF "$lastFuncName != node:value(./SecOCFreshnessValueFuncName)"!][!//
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00230,1 */
/**
 ** \brief This interface is used by the SecOC to obtain the current freshness value.
 **
 ** \param[in]   SecOCFreshnessValueID               Holds the identifier of the freshness value.
 ** \param[in]   SecOCFreshnessValueLength           Holds the length of the required freshness value
 **                                                  in bits.
 ** \param[in]   SecOCTruncatedFreshnessValueLength  Holds the length of the required truncated
 **                                                  freshness value in bits.
 ** \param[out]  SecOCFreshnessValue                 Holds the current freshness value.
 ** \param[out]  SecOCTruncatedFreshnessValue        Holds the current truncated freshness value.
 **
 ** \returns  Result of the request.
 **
 ** \retval E_OK     Request successful.
 ** \retval E_NOT_OK Request failed, a freshness value cannot be provided due to general issues for
 **                  freshness or this FreshnessValueId.
 ** \retval E_BUSY   The freshness information can temporarily not be provided.
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) [!"node:value(./SecOCFreshnessValueFuncName)"!]
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
);

[!VAR "lastFuncName" = "node:value(./SecOCFreshnessValueFuncName)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!VAR "lastFuncName" = "''"!][!//
[!LOOP "node:order(SecOCTxPduProcessing/*, './SecOCSecuredPDUTransmittedFuncName')"!][!//
[!IF "$lastFuncName != node:value(./SecOCSecuredPDUTransmittedFuncName)"!][!//
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00232,3 */
/**
 ** \brief This interface is used by the SecOC to indicate that the Secured I-PDU has been initiated
 **        for transmission.
 **
 ** \param[in]  SecOCFreshnessValueID  Holds the identifier of the freshness value.
 **/
extern FUNC(void, SECOC_CODE) [!"node:value(./SecOCSecuredPDUTransmittedFuncName)"!]
(
  uint16 SecOCFreshnessValueID
);

[!VAR "lastFuncName" = "node:value(./SecOCSecuredPDUTransmittedFuncName)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCEbGeneral/SecOCRteUsage) = 'false'"!][!//
[!LOOP "SecOCMainFunctionTx/*"!][!//
/**
 ** \brief This function performs the processing of the SecOC module's
 **        authentication for the Tx path (for the Tx PDUs which where configured to be handled by
 **        this main function).
 **/
#ifndef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONTX_[!"text:toupper(node:name(.))"!]
#define RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONTX_[!"text:toupper(node:name(.))"!]
extern FUNC(void, SECOC_CODE) SecOC_MainFunctionTx_[!"node:name(.)"!](void);
#endif /* #ifndef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONTX_[!"text:toupper(node:name(.))"!] */

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
[!IF "$UseGetTxFreshness = 'true'"!][!//
/** \brief  This function is used by SecOC to obtain the current freshness used
 **         for the authentication procedure.
 **
 ** \param[in]   instId                     Identifier of the state machine instance.
 ** \param[in]   SecOCFreshnessValueID      Holds the identifier of the freshness value.
 ** \param[out]  SecOCFreshnessValue        Holds the pointer to the memory location where the
 **                                         freshenss shall be stored.
 ** \param[in]   SecOCFreshnessValueLength  Holds a pointer to the memory location in which
 **                                         the length in bits of the required freshness is
 **                                         stored.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 ** \retval  E_BUSY    request failed, service is still busy
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant for different freshenss ID}
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_Freshness
(
        uint16                              instId,
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!ENDIF!][!//
[!//
[!IF "$UseGetTxFreshnessTruncData = 'true'"!][!//
/** \brief  This function is used by SecOC to obtain the current freshness used
 **         for the authentication procedure.
 **         It provides also the truncated freshness which shall be transmitted in the secured PDU.
 **
 ** \param[in]   instId                              Identifier of the state machine instance.
 ** \param[in]   SecOCFreshnessValueID               Holds the identifier of the freshness.
 ** \param[out]  SecOCFreshnessValue                 Holds the pointer to the memory location where
 **                                                  the freshenss shall be stored.
 ** \param[in]   SecOCFreshnessValueLength           Holds a pointer to the memory location in which
 **                                                  the length in bits of the required freshness is
 **                                                  stored.
 ** \param[out]  SecOCTruncatedFreshnessValue        Holds the pointer to the memory location where
 **                                                  the truncated freshenss shall be stored.
 ** \param[in]   SecOCTruncatedFreshnessValueLength  Holds a pointer to the memory location in which
 **                                                  the length in bits of the required truncated
 **                                                  freshness is stored.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 ** \retval  E_BUSY    request failed, service is still busy
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant for different freshenss ID}
 **/
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_Freshness_TruncData
(
        uint16                              instId,
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
);

[!ENDIF!][!//
[!//
[!IF "$TxUseSPduConfirmation = 'true'"!][!//
/** \brief  This function is used by SecOC to indicate that the transmition of the secured PDU
 **         was initiated.
 **
 ** \param[in]  instId                 Identifier of the state machine instance.
 ** \param[in]  SecOCFreshnessValueID  Holds the identifier of the freshness.
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant for different freshenss ID}
 **/
extern FUNC(void, SECOC_CODE) SecOC_Tx_SPDU_Confirmation
(
  uint16                       instId,
  uint16                       SecOCFreshnessValueID
);
[!ENDIF!][!//

[!ENDIF!][!//
[!//
[!IF "$TxUseMacStatusPropagate = 'true' and node:value(SecOCEbGeneral/SecOCRteUsage) = 'true'"!][!//
/** \brief This function is used to report the status of the MAC Generate service.
 **
 ** \param[in]  instId                     Identifier of the state machine instance.
 ** \param[in]  SecOC_TxMacGenerateStatus  Holds the pointer to the memory location where the
 **                                        the status of the MAC Generate service is stored.
 **
 **/
extern FUNC(void, SECOC_CODE) SecOC_Tx_Write_MacGenerateStatus
(
        uint16                                                   instId,
  P2VAR(SecOC_MacGenerateStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_TxMacGenerateStatus
);

[!ENDIF!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!ENDSELECT!][!//
#endif /* #ifndef SECOC_TX_CFG_H */

/*==================[end of file]=================================================================*/
