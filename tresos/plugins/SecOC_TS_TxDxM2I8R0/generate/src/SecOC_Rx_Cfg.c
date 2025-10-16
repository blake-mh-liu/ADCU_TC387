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
[!SELECT "as:modconf('SecOC')"!][!//
/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

[!// This files contains macros for configuration values
[!INCLUDE "../../generate_macros/SecOC_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Rx_Macros.m"!][!//
[!//
[!IF "$RxPduNum > 0"!][!//
#include <SecOC_Rx_Cfg.h>
#include <SecOC_Rx_Int.h>

[!IF "'true' = node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCRteUsage)"!][!//
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0 and num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
#include <Rte_SecOC.h>
[!ELSE!][!//
[!LOOP "node:refs(SecOCMainFunctionRx/*/SecOCMainFunctionRxPartitionRef | SecOCMainFunctionTx/*/SecOCMainFunctionTxPartitionRef)"!][!//
[!VAR "ecucPartition" = "node:name(.)"!][!//
#include <SecOC_Rx_[!"string($ecucPartition)"!].h>
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ELSE!][!//
#include <TSCompiler.h>

TS_PREVENTEMPTYTRANSLATIONUNIT
[!ENDIF!][!//

/*==================[macros]======================================================================*/

[!IF "$RxPduNum > 0"!][!//
/* Macro, which defines the default value for the dummy Csm job ID */
#if (defined SECOC_DUMMY_CSM_JOB_ID)
#error SECOC_DUMMY_CSM_JOB_ID already defined
#endif
#define SECOC_DUMMY_CSM_JOB_ID   4294967295U

[!VAR "RxBufferIndex" = "0"!][!//
[!LOOP "node:order(node:refs(SecOCRxPduProcessing/*[node:exists(./SecOCSameBufferPduRef) = true()]/SecOCSameBufferPduRef))"!][!//
/** \brief Macro which indicates the position of the "currently being used" flag for
 *         [!"node:name(.)"!] buffer inside the SecOC_RxBufferUsedFlags flags array
 */
#if (defined SECOC_RX_BUFFER_USED_FLAG_[!"text:toupper(node:name(.))"!])
#error SECOC_RX_BUFFER_USED_FLAG_[!"text:toupper(node:name(.))"!] already defined
#endif
#define SECOC_RX_BUFFER_USED_FLAG_[!"text:toupper(node:name(.))"!] [!"num:i($RxBufferIndex)"!]U

[!VAR "RxBufferIndex" = "$RxBufferIndex + 1"!][!//
[!ENDLOOP!][!//
[!//
[!IF "$RxUseRecvStrategyQueue = 'true'"!][!//
[!VAR "RxStoredPduLengthInd" = "0"!][!//
[!LOOP "node:order(SecOCRxPduProcessing/*[SecOCReceptionOverflowStrategy = 'QUEUE'])"!][!//
/** \brief Macro which indicates the position of the stored PDU length for
 *         [!"node:name(.)"!] buffer inside the SecOC_RxStoredReceivedSecuredPduLength array
 */
#if (defined SECOC_RX_STORED_PDU_LENGTH_IND_[!"text:toupper(node:name(.))"!])
#error SECOC_RX_STORED_PDU_LENGTH_IND_[!"text:toupper(node:name(.))"!] already defined
#endif
#define SECOC_RX_STORED_PDU_LENGTH_IND_[!"text:toupper(node:name(.))"!] [!"num:i($RxStoredPduLengthInd)"!]U

[!VAR "RxStoredPduLengthInd" = "$RxStoredPduLengthInd + node:value(./SecOCReceptionQueueSize)"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!//
/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

[!IF "$RxPduNum > 0"!][!//
#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

[!IF "$RxUseSameBufferPdu = 'true'"!][!//
/**
 * \brief Flags indicating, if the buffer is currently being used
 */
static VAR(uint8, SECOC_VAR) SecOC_RxBufferUsedFlags[[!"num:i(count(node:refs(SecOCRxPduProcessing/*[node:exists(./SecOCSameBufferPduRef) = true()]/SecOCSameBufferPduRef)))"!]];

[!ENDIF!][!//
[!//
[!IF "$RxUseRecvStrategyQueue = 'true'"!][!//
/**
 * \brief Currently stored buffer length for each buffer slot when reception overflow strategy is a queue
 */
static VAR(PduLengthType, SECOC_VAR) SecOC_RxStoredReceivedSecuredPduLength[[!"num:i(sum(SecOCRxPduProcessing/*[SecOCReceptionOverflowStrategy = 'QUEUE']/SecOCReceptionQueueSize))"!]];

[!ENDIF!][!//
[!//
[!IF "$UseGetRxFreshnessAuthData = 'true'"!][!//
[!LOOP "node:order(SecOCRxPduProcessing/*)"!][!//
[!//
[!IF "'true' = node:value(./SecOCUseAuthDataFreshness)"!][!//
[!VAR "AuthDataFreshnessBufferLen" = "ceiling((node:value(./SecOCAuthDataFreshnessLen) + (node:value(./SecOCAuthDataFreshnessStartPosition) mod 8)) div 8)"!][!//
[!ELSE!][!//
[!VAR "AuthDataFreshnessBufferLen" = "0"!][!//
[!ENDIF!][!//
[!//
[!IF "$AuthDataFreshnessBufferLen > 0"!][!//
static VAR(uint8, SECOC_VAR) SecOC_RxAuthDataFreshnessValue_[!"node:name(.)"!][[!"num:i($AuthDataFreshnessBufferLen)"!]U];

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external constants]==========================================================*/

[!IF "$RxPduNum > 0"!][!//
[!IF "num:i(count(SecOCMainFunctionRx/*)) > 0"!][!//
#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

[!LOOP "node:order(SecOCMainFunctionRx/*)"!][!//
[!VAR "MainFuncRx" = "node:name(.)"!][!//
CONST(uint16, SECOC_CONST) SecOC_RxInstIdxList_[!"$MainFuncRx"!][SECOC_NUMBER_RX_PDUS_[!"text:toupper(node:name(.))"!]] =
{
[!VAR "RxPduIndex" = "0"!][!//
[!LOOP "node:order(as:modconf('SecOC')/SecOCRxPduProcessing/*)"!][!//
[!IF "node:name(as:ref(./SecOCRxPduMainFunctionRef)) = $MainFuncRx"!][!//
  /* RxPduIndex */
  [!"num:i($RxPduIndex)"!]U, /* [!"node:name(.)"!] */
[!ENDIF!][!//
[!VAR "RxPduIndex" = "$RxPduIndex + 1"!][!//
[!ENDLOOP!][!//
};

[!ENDLOOP!][!//
#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>
[!ENDIF!][!//
[!//
[!IF "$RxUseCsmAsync = 'true'"!][!//
[!CALL "CreateJobRxPduAssoc"!][!//

#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

CONST(uint16, SECOC_CONST) SecOC_RxCbkIdx[[!"$cbkRxRefNum"!]U] =
{
[!LOOP "text:split($cbkRxAssocIndices, '|')"!][!//
  /* Cbk: [!"text:split(., ':')[1]"!] */
  [!LOOP "text:split(text:split(., ':')[2], ';')"!][!//
  [!"."!]U,
  [!ENDLOOP!][!//
[!ENDLOOP!][!//
};

#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "$RxPduNum > 0"!][!//

#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

[!IF "(count(SecOCGeneral/SecOCVerificationStatusCallout/*) > 0) and ($RxUsePropVerStatus = 'true')"!][!//
CONST(SecOC_VerificationStatusCalloutType, SECOC_VAR) SecOC_RxVerificationStatusCallout[SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP] =
{
[!LOOP "SecOCGeneral/SecOCVerificationStatusCallout/*"!][!//
  &[!"node:value(.)"!],
[!ENDLOOP!][!//
};

[!ENDIF!][!//
[!//
CONST(SecOC_RxConfigType, SECOC_CONST) SecOC_RxConfig[SECOC_NUMBER_RX_PDUS] =
{
[!VAR "RxPduIndex" = "0"!][!//
[!LOOP "node:order(SecOCRxPduProcessing/*)"!][!//
[!//
[!IF "$UseGetRxFreshnessAuthData = 'true'"!][!//
[!IF "'true' = node:value(./SecOCUseAuthDataFreshness)"!][!//
[!VAR "AuthDataFreshnessLen" = "node:value(./SecOCAuthDataFreshnessLen)"!][!//
[!VAR "AuthDataFreshnessStartPosition" = "node:value(./SecOCAuthDataFreshnessStartPosition)"!][!//
[!ELSE!][!//
[!VAR "AuthDataFreshnessLen" = "0"!][!//
[!VAR "AuthDataFreshnessStartPosition" = "0"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!//
  /* SecOC_RxConfig[[!"num:i($RxPduIndex)"!]] - [!"node:name(node:current())"!] */
  {
[!IF "node:value(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification) = 'true'"!][!//
    /* CsmJobId */
    CsmConf_CsmJob_[!"as:name(as:ref(./SecOCRxAuthServiceConfigRef))"!],
[!ELSE!][!//
    /* CsmJobId (dummy Csm job ID */
    SECOC_DUMMY_CSM_JOB_ID,
[!ENDIF!][!//
[!IF "'true' = node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCRteUsage)"!][!//
[!IF "node:exists(./SecOCRxPduMainFunctionRef) = 'true'"!][!//
    /* MainFunctionIndex */
    [!"node:pos(node:ref(./SecOCRxPduMainFunctionRef))"!]U,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "($UseGetRxFreshnessAuthData = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC')"!][!//
[!IF "node:value(./SecOCUseAuthDataFreshness) = 'true'"!][!//
    /* GetRxFreshnessAuthData */
    &[!"node:value(./SecOCFreshnessValueFuncName)"!],
[!ELSE!][!//
    /* GetRxFreshnessAuthData */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "($UseGetRxFreshness = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC')"!][!//
[!IF "node:value(./SecOCUseAuthDataFreshness) = 'false'"!][!//
    /* GetRxFreshness */
    &[!"node:value(./SecOCFreshnessValueFuncName)"!],
[!ELSE!][!//
    /* GetRxFreshness */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "SecOCRxSecuredPduLayer = 'SecOCRxSecuredPdu'"!][!//
[!IF "($RxUseSecuredCollection = 'true') and ($RxUseMessageLink = 'true')"!][!//
    /* MessageLinkLength */
    0U,
    /* MessageLinkPos */
    0U,
[!ENDIF!][!//
[!ELSE!][!//
[!IF "$RxUseMessageLink = 'true'"!][!//
[!IF "node:exists(./SecOCRxSecuredPduLayer/SecOCUseMessageLink/SecOCMessageLinkLen) = 'true'"!][!//
    /* MessageLinkLength */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCUseMessageLink/SecOCMessageLinkLen)"!]U,
    /* MessageLinkPos */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCUseMessageLink/SecOCMessageLinkPos)"!]U,
[!ELSE!][!//
    /* MessageLinkLength */
    0U,
    /* MessageLinkPos */
    0U,
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "SecOCRxSecuredPduLayer = 'SecOCRxSecuredPdu'"!][!//
    /* PduIdForSecuredPduAtSecOC */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId)"!]U,
[!ELSE!][!//
    /* PduIdForSecuredPduAtSecOC */
    0U,
[!ENDIF!][!//
[!IF "$RxUseSecuredCollection = 'true'"!][!//
[!IF "SecOCRxSecuredPduLayer = 'SecOCRxSecuredPduCollection'"!][!//
    /* PduIdForReceivedAuthPduAtSecOC */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId)"!]U,
    /* PduIdForCryptoPduAtSecOC */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId)"!]U,
[!ELSE!][!//
    /* PduIdForReceivedAuthPduAtSecOC */
    0U,
    /* PduIdForCryptoPduAtSecOC */
    0U,
[!ENDIF!][!//
[!ENDIF!][!//
    /* MaxFVSyncAttempts */
    [!"node:value(./SecOCAuthenticationVerifyAttempts)"!]U,
    /* MaxAuthAttempts */
    [!"node:value(./SecOCAuthenticationBuildAttempts)"!]U,
[!IF "$UseGetRxFreshnessAuthData = 'true'"!][!//
    /* AuthDataFreshnessValueLength */
    [!"num:i($AuthDataFreshnessLen)"!]U,
    /* AuthDataFreshnessValueStartPosition */
    [!"num:i($AuthDataFreshnessStartPosition)"!]U,
[!ENDIF!][!//
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!][!//
[!IF "node:exists(./SecOCEnableMetaData) = 'true' and node:value(./SecOCEnableMetaData) = 'true'"!][!//
    /* PduIdForSecuredPduAtEcuC */
    [!"node:value(node:refs(./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduRef)/PduId)"!]U,
    /* PduIdForAuthPduAtEcuC */
    [!"node:value(node:refs(./SecOCRxAuthenticPduLayer/SecOCRxAuthenticLayerPduRef)/PduId)"!]U,
[!ELSE!][!//
    /* PduIdForSecuredPduAtEcuC */
    0XFFFFU,
    /* PduIdForAuthPduAtEcuC */
    0XFFFFU,
[!ENDIF!][!//
[!ENDIF!][!//
    /* ReceptionStrategy */
    [!IF "node:value(./SecOCReceptionOverflowStrategy) = 'REJECT'"!]SECOC_REJECT_INCOMING_PDU[!ELSEIF "node:value(./SecOCReceptionOverflowStrategy) = 'QUEUE'"!]SECOC_QUEUE_INCOMING_PDU[!ELSE!]SECOC_REPLACE_CURRENT_PDU[!ENDIF!],
[!IF "node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
    /* GetRxFreshnessFuncType */
    [!IF "node:value(./SecOCUseAuthDataFreshness) = 'true'"!]SECOC_GET_RX_FRESHNESS_AUTHDATA_FUNC_TYPE[!ELSE!]SECOC_GET_RX_FRESHNESS_FUNC_TYPE[!ENDIF!],
[!ENDIF!][!//
    /* CsmFuncType */
    [!IF "node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification) and node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'"!]SECOC_RX_MACVERIFY_FUNC_TYPE[!ELSE!]SECOC_RX_SIGNATUREVERIFY_FUNC_TYPE[!ENDIF!],
[!IF "$RxUseSecuredHeader = 'true'"!][!//
[!IF "node:exists(./SecOCRxSecuredPduLayer/SecOCAuthPduHeaderLength) = 'true'"!][!//
    /* SecuredPduHeaderLength */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCAuthPduHeaderLength)"!]U,
[!ELSEIF "node:exists(./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCAuthPduHeaderLength) = 'true'"!][!//
    /* SecuredPduHeaderLength */
    [!"node:value(./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCAuthPduHeaderLength)"!]U,
[!ELSE!][!//
    /* SecuredPduHeaderLength */
    0U,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!][!//
[!IF "node:exists(./SecOCEnableMetaData) = 'true' and node:value(./SecOCEnableMetaData) = 'true'"!][!//
    /* MetaDataLength */
    [!"num:i(sum(node:refs(node:refs(./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduRef)/MetaDataTypeRef)/MetaDataItem/*/MetaDataItemLength))"!]U,
[!ELSE!][!//
    /* MetaDataLength */
    0U,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$RxUseSecuredCollection = 'true'"!][!//
    /* UseSecPduCollection */
    [!IF "'SecOCRxSecuredPduCollection' = SecOCRxSecuredPduLayer"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
[!IF "node:exists(as:modconf('SecOC')/SecOCEbGeneral/SecOCRxShapeFuncName) = 'true'"!][!//
    /* UseShapeSecuredPdu*/
    [!IF "node:value(./SecOCRxUseShapeFunc) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
[!IF "$RxUseCsmAsync = 'true'"!][!//
    /* UseCsmAsync */
    [!IF "node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification) and node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'"!][!//
    [!IF "node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing) = 'CSM_ASYNCHRONOUS'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
    [!ELSEIF "node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification) and node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'"!][!//
    [!IF "node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing) = 'CSM_ASYNCHRONOUS'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
    [!ELSE!][!//
    FALSE,
    [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$RxSkipVerification = 'true'"!][!//
    /* SkipVerification */
    [!IF "node:value(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification) = 'false'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
    /* UseTp */
    [!IF "'SECOC_TPPDU' = node:value(./SecOCRxAuthenticPduLayer/SecOCPduType)"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!IF "$RxUseSyncPduProcessing = 'true'"!][!//
    /* UseSyncProcessing */
    [!IF "node:value(./SecOCRxSyncPduProcessing) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
[!IF "SecOCRxSecuredPduLayer = 'SecOCRxSecuredPduCollection'"!][!//
[!IF "node:exists(as:ref(./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduRef)/DynamicLength) = 'true'"!][!//
    /* UseDynamicLength */
    [!IF "node:value(as:ref(./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduRef)/DynamicLength) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ELSE!][!//
    /* UseDynamicLength */
    TRUE,
[!ENDIF!][!//
[!ELSE!][!//
[!IF "node:exists(as:ref(./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduRef)/DynamicLength) = 'true'"!][!//
    /* UseDynamicLength */
    [!IF "node:value(as:ref(./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduRef)/DynamicLength) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ELSE!][!//
    /* UseDynamicLength */
    TRUE,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!][!//
[!IF "node:exists(./SecOCEnableMetaData) = 'true' and node:value(./SecOCEnableMetaData) = 'true'"!][!//
    /* UseMetaData */
    TRUE,
[!ELSE!][!//
    /* UseMetaData */
    FALSE,
[!ENDIF!][!//
[!ENDIF!][!//
  },
[!VAR "RxPduIndex" = "$RxPduIndex + 1"!][!//
[!ENDLOOP!][!//
};

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

[!IF "num:i(count(SecOCRxPduProcessing/*)) > 0"!][!//
[!//
#define SECOC_START_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>

VAR(SecOC_RxDataType, SECOC_VAR) SecOC_RxData[SECOC_NUMBER_RX_PDUS] =
{
[!VAR "RxPduIndex" = "0"!][!//
[!LOOP "node:order(SecOCRxPduProcessing/*)"!][!//
  /* SecOC_RxData[[!"num:i($RxPduIndex)"!]] - [!"node:name(node:current())"!] */
  {
[!IF "$UseCsmJobRefCallout = 'true'"!][!//
    /* CsmJobIdPostDefined */
    0U,
[!ENDIF!][!//
[!IF "$RxUseSameBufferPdu = 'true'"!][!//
[!IF "node:exists(./SecOCSameBufferPduRef) = true()"!][!//
    /* BufferUsed */
    &SecOC_RxBufferUsedFlags[SECOC_RX_BUFFER_USED_FLAG_[!"text:toupper(node:name(as:ref(./SecOCSameBufferPduRef)))"!]],
[!ELSE!][!//
    /* BufferUsed */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    /* ReceivedSecuredPdu */
    {NULL_PTR, 0U},
[!IF "$RxUseSecuredCollection = 'true'"!][!//
    /* ReceivedAuthPdu */
    {NULL_PTR, 0U},
    /* CryptoPdu */
    {NULL_PTR, 0U},
[!ENDIF!][!//
    /* SecuredPdu */
    {NULL_PTR, 0U},
    /* DataToAuthenticator */
    NULL_PTR,
    /* FreshnessVerifyValue */
    NULL_PTR,
    /* Authenticator */
    NULL_PTR,
[!IF "$UseGetRxFreshnessAuthData = 'true'"!][!//
[!IF "node:value(./SecOCUseAuthDataFreshness) = 'true' and node:value(./SecOCAuthDataFreshnessLen) > 0"!][!//
    /* AuthDataFreshnessValueBuffer */
    SecOC_RxAuthDataFreshnessValue_[!"node:name(.)"!],
[!ELSE!][!//
    /* AuthDataFreshnessValueBuffer */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!][!//
    /* SecuredPduMetaData */
    NULL_PTR,
[!ENDIF!][!//
[!IF "$RxUseRecvStrategyQueue = 'true'"!][!//
    /* Queue */
    {
      /* WritePtr */
      NULL_PTR,
      /* ReadPtr */
      NULL_PTR,
      /* StoredPduLength */
[!IF "node:value(./SecOCReceptionOverflowStrategy) = 'QUEUE'"!][!//
      &SecOC_RxStoredReceivedSecuredPduLength[SECOC_RX_STORED_PDU_LENGTH_IND_[!"text:toupper(node:name(.))"!]],
[!ELSE!][!//
      NULL_PTR,
[!ENDIF!][!//
      /* QueueSize */
[!IF "node:value(./SecOCReceptionOverflowStrategy) = 'QUEUE'"!][!//
      [!"num:i(node:value(./SecOCReceptionQueueSize))"!]U,
[!ELSE!][!//
      0U,
[!ENDIF!][!//
      /* Count */
      0U,
      /* WriteRemainingBytes */
      0U,
      /* ReadBufferIndex */
      0U,
      /* WriteBufferIndex */
      0U,
      /* WriteInProgress */
      FALSE
    },
[!ENDIF!][!//
    /* DataLength */
    0U,
    /* AuthAttempts */
    0U,
    /* FVSyncAttempts */
    0U,
    /* VerificationResult */
    SECOC_VERIFICATIONFAILURE,
    /* VerifyStatusOverride */
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbVerifyStatusOverrideApiVersion) = 'SECOC_API_VERSION_430'"!][!//
    SECOC_OVERRIDESTATUS_CANCEL,
[!ELSE!][!//
    SECOC_OVERRIDE_CANCEL,
[!ENDIF!][!//
    /* NumMsgToOverride */
    0U,
    /* State */
    0U,
    /* PduREvent */
    0U,
[!IF "$RxUseSecuredCollection = 'true'"!][!//
    /* PduRIndicationForAuth */
    0U,
    /* PduRIndicationForCrypto */
    0U,
[!ENDIF!][!//
[!IF "$RxUseCsmAsync = 'true'"!][!//
    /* CsmEvent */
    0U,
[!ENDIF!][!//
    /* CsmVerificationResult */
    0U,
[!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) = 'EB_CUSTOM'"!][!//
    /* CsmVerificationReturn */
    E_NOT_OK,
[!ENDIF!][!//
    /* PduInProcess */
    FALSE,
    /* ProcessingVerification */
    FALSE,
    /* RenewedVerStatus */
    FALSE
  },
[!VAR "RxPduIndex" = "$RxPduIndex + 1"!][!//
[!ENDLOOP!][!//
};

#define SECOC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external function definitions]===============================================*/

[!IF "$RxPduNum > 0"!][!//
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

[!IF "$RxUseCsmAsync = 'true'"!][!//
[!CALL "CreateJobRxPduAssoc"!][!//
[!LOOP "text:split($CsmRxCbks, ';')"!][!//
/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00012,1 */
FUNC(void, SECOC_CODE) [!"."!]
(
  P2CONST(Crypto_JobType, AUTOMATIC, SECOC_APPL_DATA) job,
          Std_ReturnType                              result
)
{
[!CALL "GetCbkAssocRxPduSlice", "cbkName"="."!][!//
  SecOC_Rx_CsmCallbackNotification(job, [!"$cbkSliceStart"!]U, [!"$cbkSliceEnd"!]U, result);
}

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!LOOP "SecOCMainFunctionRx/*"!][!//
FUNC(void, SECOC_CODE) SecOC_MainFunctionRx_[!"node:name(.)"!]
(
  void
)
{
  SecOC_MainFunctionRx(&SecOC_RxInstIdxList_[!"node:name(.)"!][0], SECOC_NUMBER_RX_PDUS_[!"text:toupper(node:name(.))"!]);
}

[!ENDLOOP!][!//
[!//
[!IF "not(num:i(count(SecOCMainFunctionRx/*)) > 0 and node:value(SecOCEbGeneral/SecOCRteUsage) = 'true')"!][!//
[!IF "node:value(SecOCEbGeneral/SecOCEbVerifyStatusOverrideApiVersion) = 'SECOC_API_VERSION_430'"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_VerifyStatusOverride
(
  uint16  freshnessValueId,
  uint8   overrideStatus,
  uint8   numberOfMessagesToOverride
)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = SecOC_Rx_VerifyStatusOverride_43
            (
              NULL_PTR,
              SECOC_NUMBER_RX_PDUS,
              freshnessValueId,
              overrideStatus,
              numberOfMessagesToOverride
            );
  return retVal;
}

[!ELSE!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_VerifyStatusOverride
(
  uint16                   ValueId,
  SecOC_OverrideStatusType overrideStatus,
  uint8                    numberOfMessagesToOverride
)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = SecOC_Rx_VerifyStatusOverride_44
            (
              NULL_PTR,
              SECOC_NUMBER_RX_PDUS,
              ValueId,
              overrideStatus,
              numberOfMessagesToOverride
            );
  return retVal;
}

[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
[!IF "$UseGetRxFreshness = 'true'"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_Freshness
(
          uint16                              instId,
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
          uint16                              SecOCCounterSyncAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
)
{
  Std_ReturnType  retVal = E_NOT_OK;

[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
  retVal = SecOC_RxConfig[instId].GetRxFreshness(
                                                  SecOCFreshnessValueID,
                                                  SecOCTruncatedFreshnessValue,
                                                  SecOCTruncatedFreshnessValueLength,
                                                  SecOCCounterSyncAttempts,
                                                  SecOCFreshnessValue,
                                                  SecOCFreshnessValueLength
                                                );
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  retVal = Rte_Call_PS_RxFreshnessManagement_GetRxFreshness(
                                                  SecOCFreshnessValueID,
                                                  SecOCTruncatedFreshnessValue,
                                                  SecOCTruncatedFreshnessValueLength,
                                                  SecOCCounterSyncAttempts,
                                                  SecOCFreshnessValue,
                                                  SecOCFreshnessValueLength
                                                );
[!ELSE!][!//
  switch(SecOC_RxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionRx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncRx" = "node:name(.)"!][!//
[!IF "count(../../SecOCRxPduProcessing/*[node:name(node:ref(./SecOCRxPduMainFunctionRef)) = $MainFuncRx and node:value(./SecOCUseAuthDataFreshness) = 'false']) > 0"!][!//
    case [!"node:pos(.)"!]U:
        retVal = SecOC_Rx_Get_[!"$MainFuncRx"!]_Freshness(
                                                  SecOCFreshnessValueID,
                                                  SecOCTruncatedFreshnessValue,
                                                  SecOCTruncatedFreshnessValueLength,
                                                  SecOCCounterSyncAttempts,
                                                  SecOCFreshnessValue,
                                                  SecOCFreshnessValueLength
                                                );
      break;
[!ENDIF!][!//
[!ENDLOOP!][!//
    default:
      /* do nothing */
      break;
  }
[!ENDIF!][!//
[!ENDIF!][!//

  return retVal;
}

[!ENDIF!][!//
[!//
[!IF "$UseGetRxFreshnessAuthData = 'true'"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_Freshness_AuthData
(
          uint16                              instId,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCAuthDataFreshnessValue,
          uint16                              SecOCAuthDataFreshnessValueLength,
          uint16                              SecOCAuthVerifyAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
)
{
  Std_ReturnType  retVal = E_NOT_OK;

[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
  retVal = SecOC_RxConfig[instId].GetRxFreshnessAuthData(
                                                          SECOC_GET_RX_FRESHNESS_ID(instId),
                                                          SecOCTruncatedFreshnessValue,
                                                          SecOCTruncatedFreshnessValueLength,
                                                          SecOCAuthDataFreshnessValue,
                                                          SecOCAuthDataFreshnessValueLength,
                                                          SecOCAuthVerifyAttempts,
                                                          SecOCFreshnessValue,
                                                          SecOCFreshnessValueLength
                                                        );
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0"!][!//
  retVal = Rte_Call_PS_RxFreshnessManagement_GetRxFreshnessAuthData(
                                                          SECOC_GET_RX_FRESHNESS_ID(instId),
                                                          SecOCTruncatedFreshnessValue,
                                                          SecOCTruncatedFreshnessValueLength,
                                                          SecOCAuthDataFreshnessValue,
                                                          SecOCAuthDataFreshnessValueLength,
                                                          SecOCAuthVerifyAttempts,
                                                          SecOCFreshnessValue,
                                                          SecOCFreshnessValueLength
                                                        );
[!ELSE!][!//
  switch(SecOC_RxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionRx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncRx" = "node:name(.)"!][!//
[!IF "count(../../SecOCRxPduProcessing/*[node:name(node:ref(./SecOCRxPduMainFunctionRef)) = $MainFuncRx and node:value(./SecOCUseAuthDataFreshness) = 'true']) > 0"!][!//
    case [!"node:pos(.)"!]U:
        retVal = SecOC_Rx_Get_[!"$MainFuncRx"!]_Freshness_AuthData(
                                                          SECOC_GET_RX_FRESHNESS_ID(instId),
                                                          SecOCTruncatedFreshnessValue,
                                                          SecOCTruncatedFreshnessValueLength,
                                                          SecOCAuthDataFreshnessValue,
                                                          SecOCAuthDataFreshnessValueLength,
                                                          SecOCAuthVerifyAttempts,
                                                          SecOCFreshnessValue,
                                                          SecOCFreshnessValueLength
                                                        );
      break;
[!ENDIF!][!//
[!ENDLOOP!][!//
    default:
      /* do nothing */
      break;
  }
[!ENDIF!][!//
[!ENDIF!][!//

  return retVal;
}

[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) != 'NONE' and 'true' = node:value(SecOCEbGeneral/SecOCRteUsage)"!][!//
FUNC(void, SECOC_CODE) SecOC_Rx_Write_VerificationStatus
(
        uint16                                                    instId,
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
)
{
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  (void)Rte_Write_PS_VerificationStatus_verificationStatus(SecOC_RxVerificationStatus);
[!ELSE!][!//
  switch(SecOC_RxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionRx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncRx" = "node:name(.)"!][!//
    case [!"node:pos(.)"!]U:
        (void)SecOC_Rx_Write_[!"$MainFuncRx"!]_VerificationStatus(SecOC_RxVerificationStatus);
      break;
[!ENDLOOP!][!//
    default:
      /* do nothing */
      break;
  }
[!ENDIF!][!//
}

[!ENDIF!][!//
[!//
[!IF "node:value(SecOCEbGeneral/SecOCEbClientServerPropagateVerificationStatusApiVersion) != 'NONE'"!][!//
FUNC(void, SECOC_CODE) SecOC_Rx_Call_VerificationStatusIndication
(
        uint16                                                    instId,
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
)
{
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  (void)Rte_Call_PS_VerificationStatusIndication_VerifyStatus(SecOC_RxVerificationStatus);
[!ELSE!][!//
  switch(SecOC_RxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionRx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncRx" = "node:name(.)"!][!//
    case [!"node:pos(.)"!]U:
        SecOC_Rx_Call_[!"$MainFuncRx"!]_VerificationStatusIndication(SecOC_RxVerificationStatus);
      break;
[!ENDLOOP!][!//
    default:
      /* do nothing */
      break;
  }
[!ENDIF!][!//
}

[!ENDIF!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!ENDSELECT!][!//
/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
