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
[!INCLUDE "../../generate_macros/SecOC_Tx_Macros.m"!][!//
[!//
[!IF "$TxPduNum > 0"!][!//
#include <SecOC_Tx_Cfg.h>
#include <SecOC_Tx_Int.h>

[!IF "'true' = node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCRteUsage)"!][!//
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0 and num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
#include <Rte_SecOC.h>
[!ELSE!][!//
[!LOOP "node:refs(SecOCMainFunctionRx/*/SecOCMainFunctionRxPartitionRef | SecOCMainFunctionTx/*/SecOCMainFunctionTxPartitionRef)"!][!//
[!VAR "ecucPartition" = "node:name(.)"!][!//
#include <SecOC_Tx_[!"string($ecucPartition)"!].h>
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ELSE!][!//
#include <TSCompiler.h>

TS_PREVENTEMPTYTRANSLATIONUNIT
[!ENDIF!][!//

/*==================[macros]======================================================================*/

[!IF "$TxPduNum > 0"!][!//
[!VAR "TxBufferIndex" = "0"!][!//
[!LOOP "node:order(node:refs(SecOCTxPduProcessing/*[node:exists(./SecOCSameBufferPduRef) = true()]/SecOCSameBufferPduRef))"!][!//
/** \brief Macro which indicates the position of the "currently being used" flag for
 *         [!"node:name(.)"!] buffer inside the SecOC_TxBufferUsedFlags flags array
 */
#if (defined SECOC_TX_BUFFER_USED_FLAG_[!"text:toupper(node:name(.))"!])
#error SECOC_TX_BUFFER_USED_FLAG_[!"text:toupper(node:name(.))"!] already defined
#endif
#define SECOC_TX_BUFFER_USED_FLAG_[!"text:toupper(node:name(.))"!] [!"num:i($TxBufferIndex)"!]U

[!VAR "TxBufferIndex" = "$TxBufferIndex + 1"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

[!IF "$TxUseSameBufferPdu = 'true'"!][!//
#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

/**
 * \brief Flags indicating, if the buffer is currently being used
 */
static VAR(uint8, SECOC_VAR) SecOC_TxBufferUsedFlags[[!"num:i(count(node:refs(SecOCTxPduProcessing/*[node:exists(./SecOCSameBufferPduRef) = true()]/SecOCSameBufferPduRef)))"!]];

#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>
[!ENDIF!][!//
[!//
/*==================[external constants]==========================================================*/

[!IF "$TxPduNum > 0"!][!//
[!IF "num:i(count(SecOCMainFunctionTx/*)) > 0"!][!//
#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

[!LOOP "node:order(SecOCMainFunctionTx/*)"!][!//
[!VAR "MainFuncTx" = "node:name(.)"!][!//
CONST(uint16, SECOC_CONST) SecOC_TxInstIdxList_[!"$MainFuncTx"!][SECOC_NUMBER_TX_PDUS_[!"text:toupper(node:name(.))"!]] =
{
[!VAR "TxPduIndex" = "0"!][!//
[!LOOP "node:order(as:modconf('SecOC')/SecOCTxPduProcessing/*, 'SecOCTxAuthenticPduLayer/SecOCTxAuthenticLayerPduId')"!][!//
[!IF "node:name(as:ref(./SecOCTxPduMainFunctionRef)) = $MainFuncTx"!][!//
  /* TxPduIndex */
  [!"num:i($TxPduIndex)"!]U, /* [!"node:name(.)"!] */
[!ENDIF!][!//
[!VAR "TxPduIndex" = "$TxPduIndex + 1"!][!//
[!ENDLOOP!][!//
};

[!ENDLOOP!][!//
#define SECOC_STOP_SEC_CONST_16
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!//
[!IF "$TxUseCsmAsync = 'true'"!][!//
[!CALL "CreateJobTxPduAssoc"!][!//
#define SECOC_START_SEC_CONST_16
#include <SecOC_MemMap.h>

CONST(uint16, SECOC_CONST) SecOC_TxCbkIdx[[!"$cbkTxRefNum"!]U] =
{
[!LOOP "text:split($cbkTxAssocIndices, '|')"!][!//
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
[!IF "$TxPduNum > 0"!][!//
#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

[!IF "($TxUseMacStatusPropagate = 'true') and (count(SecOCGeneral/SecOCMacGenerateStatusCallout/*) > 0)"!][!//
CONST(SecOC_MacGenerateStatusCalloutType, SECOC_VAR) SecOC_TxMacGenerateStatusCallout[SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP] =
{
[!LOOP "SecOCGeneral/SecOCMacGenerateStatusCallout/*"!][!//
  &[!"node:value(.)"!],
[!ENDLOOP!][!//
};

[!ENDIF!][!//
[!//
CONST(SecOC_TxConfigType, SECOC_CONST) SecOC_TxConfig[SECOC_NUMBER_TX_PDUS] =
{
[!VAR "TxPduIndex" = "0"!][!//
[!LOOP "node:order(SecOCTxPduProcessing/*, 'SecOCTxAuthenticPduLayer/SecOCTxAuthenticLayerPduId')"!][!//
  /* SecOC_TxConfig[[!"num:i($TxPduIndex)"!]] - [!"node:name(node:current())"!] */
  {
[!IF "$TxUseConfirmationTimeout = 'true'"!][!//
    /* ConfirmationTimeoutThreshold */
    [!"num:i(node:value(./SecOCTxConfirmationTimeout) div node:value(./../../SecOCGeneral/SecOCMainFunctionPeriodTx))"!]U,
[!ENDIF!][!//
    /* CsmJobId */
    CsmConf_CsmJob_[!"as:name(as:ref(./SecOCTxAuthServiceConfigRef))"!],
[!IF "'true' = node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCRteUsage)"!][!//
[!IF "node:exists(./SecOCTxPduMainFunctionRef) = 'true'"!][!//
    /* MainFunctionIndex */
    [!"node:pos(node:ref(./SecOCTxPduMainFunctionRef))"!]U,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "($UseGetTxFreshnessTruncData = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC')"!][!//
[!IF "node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'true'"!][!//
    /* GetTxFreshnessTruncData */
    &[!"node:value(./SecOCFreshnessValueFuncName)"!],
[!ELSE!][!//
    /* GetTxFreshnessTruncData */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "($UseGetTxFreshness = 'true') and (node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC')"!][!//
[!IF "node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'false'"!][!//
    /* GetTxFreshness */
    &[!"node:value(./SecOCFreshnessValueFuncName)"!],
[!ELSE!][!//
    /* GetTxFreshness */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
    /* SPduTxConfirmation */
    &[!"node:value(./SecOCSecuredPDUTransmittedFuncName)"!],
[!ENDIF!][!//
[!IF "SecOCTxSecuredPduLayer = 'SecOCTxSecuredPdu'"!][!//
    /* PduIdForSecuredPduAtSecOC */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId)"!]U,
[!IF "$TxUseSecuredCollection = 'true'"!][!//
    /* PduIdForSentAuthPduAtSecOC */
    0U,
    /* PduIdForCryptoPduAtSecOC */
    0U,
[!ENDIF!][!//
[!ELSE!][!//
    /* PduIdForSecuredPduAtSecOC */
    0U,
    /* PduIdForSentAuthPduAtSecOC */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId)"!]U,
    /* PduIdForCryptoPduAtSecOC */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId)"!]U,
[!ENDIF!][!//
[!IF "SecOCTxSecuredPduLayer = 'SecOCTxSecuredPdu'"!][!//
[!IF "($TxUseSecuredCollection = 'true') and ($TxUseMessageLink = 'true')"!][!//
    /* MessageLinkLength */
    0U,
    /* MessageLinkPos */
    0U,
[!ENDIF!][!//
[!ELSE!][!//
[!IF "$TxUseMessageLink = 'true'"!][!//
[!IF "node:exists(./SecOCTxSecuredPduLayer/SecOCUseMessageLink) = 'true'"!][!//
    /* MessageLinkLength */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCUseMessageLink/SecOCMessageLinkLen)"!]U,
    /* MessageLinkPos */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCUseMessageLink/SecOCMessageLinkPos)"!]U,
[!ELSE!][!//
    /* MessageLinkLength */
    0U,
    /* MessageLinkPos */
    0U,
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
    /* MaxAuthAttempts */
    [!"node:value(./SecOCAuthenticationBuildAttempts)"!]U,
[!IF "$TxUseMacStatusPropagate = 'true'"!][!//
    /* MacGenerateStatusPropagationMode */
    SECOC_STATUS_PROP_[!"node:value(./SecOCMacGenerateStatusPropagationMode)"!],
[!ENDIF!][!//
[!IF "node:value(as:modconf('SecOC')/SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
    /* GetTxFreshnessFuncType */
    [!IF "node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'true'"!]SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE[!ELSE!]SECOC_GET_TX_FRESHNESS_FUNC_TYPE[!ENDIF!],
[!ENDIF!][!//
    /* CsmFuncType */
    [!IF "node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'"!]SECOC_TX_MACGENERATE_FUNC_TYPE[!ELSE!]SECOC_TX_SIGNATUREGENERATE_FUNC_TYPE[!ENDIF!],
[!IF "$TxUseSecuredHeader = 'true'"!][!//
[!IF "node:exists(./SecOCTxSecuredPduLayer/SecOCAuthPduHeaderLength) = 'true'"!][!//
    /* SecuredPduHeaderLength */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCAuthPduHeaderLength)"!]U,
[!ELSEIF "node:exists(./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCAuthPduHeaderLength) = 'true'"!][!//
    /* SecuredPduHeaderLength */
    [!"node:value(./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCAuthPduHeaderLength)"!]U,
[!ELSE!][!//
    /* SecuredPduHeaderLength */
    0U,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$TxUseSecuredCollection = 'true'"!][!//
    /* UseSecPduCollection */
    [!IF "'SecOCTxSecuredPduCollection' = SecOCTxSecuredPduLayer"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
[!IF "node:exists(as:modconf('SecOC')/SecOCEbGeneral/SecOCTxShapeFuncName) = 'true'"!][!//
    /* UseShapeSecuredPdu */
    [!IF "node:value(./SecOCTxUseShapeFunc) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
[!IF "$TxUseCsmAsync = 'true'"!][!//
    /* UseCsmAsync */
    [!IF "node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'"!][!//
    [!IF "node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing) = 'CSM_ASYNCHRONOUS'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
    [!ELSEIF "node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'"!][!//
    [!IF "node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing) = 'CSM_ASYNCHRONOUS'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
    [!ELSE!][!//
    FALSE,
    [!ENDIF!][!//
[!ENDIF!][!//
    /* UseTp */
    [!IF "'SECOC_TPPDU' = node:value(./SecOCTxAuthenticPduLayer/SecOCPduType)"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!IF "$TxUseSyncPduProcessing = 'true'"!][!//
    /* UseSyncProcessing */
    [!IF "node:value(./SecOCTxSyncPduProcessing) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
[!IF "SecOCTxSecuredPduLayer = 'SecOCTxSecuredPduCollection'"!][!//
[!IF "node:exists(as:ref(./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduRef)/DynamicLength) = 'true'"!][!//
    /* UseDynamicLength */
    [!IF "node:value(as:ref(./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduRef)/DynamicLength) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ELSE!][!//
    /* UseDynamicLength */
    TRUE,
[!ENDIF!][!//
[!ELSE!][!//
[!IF "node:exists(as:ref(./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduRef)/DynamicLength) = 'true'"!][!//
    /* UseDynamicLength */
    [!IF "node:value(as:ref(./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduRef)/DynamicLength) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ELSE!][!//
    /* UseDynamicLength */
    TRUE,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "'true' = $TxUseSPduConfirmation"!][!//
    /* UseTxConfirmation */
    [!IF "node:exists(./SecOCUseTxConfirmation) = 'true' and node:value(./SecOCUseTxConfirmation) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
[!ENDIF!][!//
  },
[!VAR "TxPduIndex" = "$TxPduIndex + 1"!][!//
[!ENDLOOP!][!//
};

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

[!IF "$TxPduNum > 0"!][!//
#define SECOC_START_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>

VAR(SecOC_TxDataType, SECOC_VAR) SecOC_TxData[SECOC_NUMBER_TX_PDUS] =
{
[!VAR "TxPduIndex" = "0"!][!//
[!LOOP "node:order(SecOCTxPduProcessing/*, 'SecOCTxAuthenticPduLayer/SecOCTxAuthenticLayerPduId')"!][!//
  /* SecOC_TxData[[!"num:i($TxPduIndex)"!]] - [!"node:name(node:current())"!] */
  {
[!IF "$UseCsmJobRefCallout = 'true'"!][!//
    /* CsmJobIdPostDefined */
    0U,
[!ENDIF!][!//
[!IF "$TxUseConfirmationTimeout = 'true'"!][!//
    /* ConfirmationTimeoutCounter */
    0U,
[!ENDIF!][!//
    /* AuthenticatorLength */
    0U,
[!IF "$TxUseSameBufferPdu = 'true'"!][!//
[!IF "node:exists(./SecOCSameBufferPduRef) = true()"!][!//
    /* BufferUsed */
    &SecOC_TxBufferUsedFlags[SECOC_TX_BUFFER_USED_FLAG_[!"text:toupper(node:name(as:ref(./SecOCSameBufferPduRef)))"!]],
[!ELSE!][!//
    /* BufferUsed */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    /* ReceivedAuthPdu */
    {NULL_PTR, 0U},
    /* SecuredPdu */
    { NULL_PTR, 0U },
[!IF "$TxUseSecuredCollection = 'true'"!][!//
    /* SentAuthPdu */
    { NULL_PTR, 0U },
    /* CryptoPdu */
    { NULL_PTR, 0U },
[!ENDIF!][!//
    /* DataToAuthenticator */
    NULL_PTR,
    /* Authenticator */
    NULL_PTR,
    /* DataLength */
    0U,
    /* CopiedDataFromSecLength */
    0U,
[!IF "$TxUseSecuredCollection = 'true'"!][!//
    /* CopiedDataFromAuthLength */
    0U,
    /* CopiedDataFromCryptoLength */
    0U,
[!ENDIF!][!//
    /* AuthAttempts */
    0U,
    /* State */
    0U,
    /* PduREvent */
    0U,
[!IF "$TxUseSecuredCollection = 'true'"!][!//
    /* PduRConfirmationForAuth */
    0U,
    /* PduRConfirmationForCrypto */
    0U,
[!ENDIF!][!//
    /* TransmitEvent */
    0U,
[!IF "$TxUseCsmAsync = 'true'"!][!//
    /* CsmEvent */
    0U,
[!ENDIF!][!//
[!IF "'true' = node:exists(as:modconf('SecOC')/SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!][!//
    /* DefaultAuthInfoPatternState */
    SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED,
[!ENDIF!][!//
[!IF "$TxUseMacStatusPropagate = 'true'"!][!//
    /* MacGenerateResult */
    E_NOT_OK,
[!ENDIF!][!//
    /* ProcessingAuthentication */
    FALSE
  },
[!VAR "TxPduIndex" = "$TxPduIndex + 1"!][!//
[!ENDLOOP!][!//
};

#define SECOC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>
[!ENDIF!][!//

/*==================[external function definitions]===============================================*/

[!IF "$TxPduNum > 0"!][!//
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

[!LOOP "SecOCMainFunctionTx/*"!][!//
FUNC(void, SECOC_CODE) SecOC_MainFunctionTx_[!"node:name(.)"!]
(
  void
)
{
  /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00276, 1 */
  SecOC_MainFunctionTx(&SecOC_TxInstIdxList_[!"node:name(.)"!][0], SECOC_NUMBER_TX_PDUS_[!"text:toupper(node:name(.))"!]);
}

[!ENDLOOP!][!//
[!//
[!IF "$TxUseCsmAsync = 'true'"!][!//
[!CALL "CreateJobTxPduAssoc"!][!//
[!LOOP "text:split($CsmTxCbks, ';')"!][!//
/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00012,1 */
FUNC(void, SECOC_CODE) [!"."!]
(
  P2CONST(Crypto_JobType, AUTOMATIC, SECOC_APPL_DATA) job,
          Std_ReturnType                              result
)
{
[!CALL "GetCbkAssocTxPduSlice", "cbkName"="."!][!//
  SecOC_Tx_CsmCallbackNotification(job, [!"$cbkSliceStart"!]U, [!"$cbkSliceEnd"!]U, result);
}

[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
[!IF "$UseGetTxFreshness = 'true'"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_Freshness
(
        uint16                              instId,
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
)
{
  Std_ReturnType retVal = E_NOT_OK;

[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
  retVal = SecOC_TxConfig[instId].GetTxFreshness(
                                                  SecOCFreshnessValueID,
                                                  SecOCFreshnessValue,
                                                  SecOCFreshnessValueLength
                                                );
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  retVal = Rte_Call_PS_TxFreshnessManagement_GetTxFreshness(
                                                  SecOCFreshnessValueID,
                                                  SecOCFreshnessValue,
                                                  SecOCFreshnessValueLength
                                                );
[!ELSE!][!//
  switch(SecOC_TxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionTx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncTx" = "node:name(.)"!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $MainFuncTx and node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'false']) > 0"!][!//
    case [!"node:pos(.)"!]U:
        retVal = SecOC_Tx_Get_[!"$MainFuncTx"!]_Freshness(
                                                  SecOCFreshnessValueID,
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
[!IF "$UseGetTxFreshnessTruncData = 'true'"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_Freshness_TruncData
(
        uint16                              instId,
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
)
{
  Std_ReturnType retVal = E_NOT_OK;

[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
  retVal = SecOC_TxConfig[instId].GetTxFreshnessTruncData(
                                                           SecOCFreshnessValueID,
                                                           SecOCFreshnessValue,
                                                           SecOCFreshnessValueLength,
                                                           SecOCTruncatedFreshnessValue,
                                                           SecOCTruncatedFreshnessValueLength
                                                         );
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  retVal = Rte_Call_PS_TxFreshnessManagement_GetTxFreshnessTruncData(
                                                           SecOCFreshnessValueID,
                                                           SecOCFreshnessValue,
                                                           SecOCFreshnessValueLength,
                                                           SecOCTruncatedFreshnessValue,
                                                           SecOCTruncatedFreshnessValueLength
                                                         );
[!ELSE!][!//
  switch(SecOC_TxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionTx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncTx" = "node:name(.)"!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $MainFuncTx and node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'true']) > 0"!][!//
    case [!"node:pos(.)"!]U:
        retVal = SecOC_Tx_Get_[!"$MainFuncTx"!]_Freshness_TruncData(
                                                           SecOCFreshnessValueID,
                                                           SecOCFreshnessValue,
                                                           SecOCFreshnessValueLength,
                                                           SecOCTruncatedFreshnessValue,
                                                           SecOCTruncatedFreshnessValueLength
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
[!IF "$TxUseSPduConfirmation = 'true'"!][!//
FUNC(void, SECOC_CODE) SecOC_Tx_SPDU_Confirmation
(
  uint16 instId,
  uint16 SecOCFreshnessValueID
)
{
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
  SecOC_TxConfig[instId].SPduTxConfirmation(SecOCFreshnessValueID);
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  (void)Rte_Call_PS_TxFreshnessManagement_SPduTxConfirmation(SecOCFreshnessValueID);
[!ELSE!][!//
  switch(SecOC_TxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionTx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncTx" = "node:name(.)"!][!//
    case [!"node:pos(.)"!]U:
        SecOC_Tx_[!"$MainFuncTx"!]_SPDU_Confirmation(SecOCFreshnessValueID);
      break;
[!ENDLOOP!][!//
    default:
      /* do nothing */
      break;
  }
[!ENDIF!][!//
[!ENDIF!][!//
}
[!ENDIF!][!//

[!ENDIF!][!//
[!//
[!IF "$TxUseMacStatusPropagate = 'true' and node:value(SecOCEbGeneral/SecOCRteUsage) = 'true'"!][!//
FUNC(void, SECOC_CODE) SecOC_Tx_Write_MacGenerateStatus
(
        uint16                                                   instId,
  P2VAR(SecOC_MacGenerateStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_TxMacGenerateStatus
)
{
[!IF "num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
  SECOC_PARAM_UNUSED(instId);
  (void)Rte_Write_PS_MacGenerateStatus_macGenerateStatus(SecOC_TxMacGenerateStatus);
[!ELSE!][!//
  switch(SecOC_TxConfig[instId].MainFunctionIndex)
  {
[!LOOP "node:order(SecOCMainFunctionTx/*, 'node:value(.)')"!][!//
[!VAR "MainFuncTx" = "node:name(.)"!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $MainFuncTx and node:value(./SecOCMacGenerateStatusPropagationMode) != 'NONE']) > 0"!][!//
    case [!"node:pos(.)"!]U:
        SecOC_Tx_Write_[!"$MainFuncTx"!]_MacGenerateStatus(SecOC_TxMacGenerateStatus);
      break;
[!ENDIF!][!//
[!ENDLOOP!][!//
    default:
      /* do nothing */
      break;
  }
[!ENDIF!][!//
}
[!ENDIF!][!//

[!IF "not(num:i(count(SecOCMainFunctionTx/*)) > 0 and node:value(SecOCEbGeneral/SecOCRteUsage) = 'true')"!][!//
[!IF "'true' = node:exists(SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_SendDefaultAuthenticationInformation
(
  uint16 FreshnessValueID,
  boolean sendDefaultAuthenticationInformation
)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = SecOC_Tx_SendDefaultAuthenticationInformation
            (
              NULL_PTR,
              SECOC_NUMBER_TX_PDUS,
              FreshnessValueID,
              sendDefaultAuthenticationInformation
            );

  return retVal;
}
[!ENDIF!][!//
[!ENDIF!][!//

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!ENDSELECT!][!//
/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
