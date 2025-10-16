[!/**
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
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('SECOC_TX_MACROS_M'))"!][!//
[!VAR "SECOC_TX_MACROS_M"="'true'"!][!/*

*** Macro used to establish the Csm Job to Tx Pdu association
*/!]
[!MACRO "CreateJobTxPduAssoc"!][!NOCODE!]
[!IF "not(var:defined('CsmTxCbks'))"!]
  [!VAR "CsmTxCbks" = "text:join(node:refs(node:refs(as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing) = 'CSM_ASYNCHRONOUS']/SecOCTxAuthServiceConfigRef | as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing) = 'CSM_ASYNCHRONOUS']/SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc, ';')"!]

  [!VAR "cbkTxAssocIndices" = "''"!]
  [!VAR "cbkTxAssocSlices" = "''"!]

    [!VAR "startIdx" = "0"!]
    [!VAR "cbkPduOrder" = "''"!]
    [!VAR "cbkPduOrderIdx" = "0"!]
    [!LOOP "node:order(as:modconf('SecOC')/SecOCTxPduProcessing/*, 'SecOCTxAuthenticPduLayer/SecOCTxAuthenticLayerPduId')"!]
      [!VAR "cbkPduOrder" = "concat($cbkPduOrder, node:name(.), ':', num:i($cbkPduOrderIdx), '|')"!]
      [!VAR "cbkPduOrderIdx" = "$cbkPduOrderIdx + 1"!]
    [!ENDLOOP!]
    [!FOR "i" = "1" TO "count(text:split($CsmTxCbks, ';'))"!]
      [!VAR "numRef" = "0"!]
      [!VAR "cbkFunc" = "text:split($CsmTxCbks, ';')[position() = $i]"!]
      [!VAR "indices" = "''"!]
      [!LOOP "as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing) = 'CSM_ASYNCHRONOUS'][string(node:ref(node:ref(SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc) = $cbkFunc] | as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing) = 'CSM_ASYNCHRONOUS'][string(node:ref(node:ref(SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc) = $cbkFunc]"!]
        [!VAR "numRef" = "$numRef + 1"!]
        [!VAR "indices" = "concat($indices, text:split(text:grep(text:split($cbkPduOrder, '|'), concat('^', node:name(.), '\:\d+$'))[1], ':')[2], ';')"!]
      [!ENDLOOP!]
      [!VAR "endIdx" = "$startIdx + $numRef"!]
      [!VAR "cbkTxAssocSlices" = "concat($cbkTxAssocSlices, $cbkFunc, ':', num:i($startIdx), ':', num:i($endIdx), '|')"!]
      [!VAR "cbkTxAssocIndices" = "concat($cbkTxAssocIndices, $cbkFunc, ':', $indices, '|')"!]
      [!VAR "startIdx" = "$endIdx"!]
    [!ENDFOR!]
    [!VAR "cbkTxRefNum" = "num:i($endIdx)"!]

[!ENDIF!][!// not(var:defined('CsmTxCbks'))
[!ENDNOCODE!][!ENDMACRO!][!/*

*** Macro used to establish the Csm Job to Tx Pdu association
*/!]
[!MACRO "GetCbkAssocTxPduSlice", "cbkName"!][!NOCODE!]
  [!VAR "cbkSliceStart" = "num:i(0)"!]
  [!VAR "ind" = "$cbkTxAssocIndices"!]
  [!VAR "slcs" = "$cbkTxAssocSlices"!]
  [!VAR "cbkSliceEnd" = "num:i($TxPduNum)"!]

  [!VAR "cbkPduIdxs" = "text:split(text:grep(text:split($ind, '|'), concat('^', $cbkName, '.*$'))[1], ':')[2]"!]
  [!VAR "sCbk" = "text:grep(text:split($slcs, '|'), concat('^', $cbkName, '.*$'))[1]"!]
  [!VAR "cbkSliceStart" = "text:split($sCbk, ':' )[2]"!]
  [!VAR "cbkSliceEnd" = "text:split($sCbk, ':')[3]"!]
[!ENDNOCODE!][!ENDMACRO!][!/*

*** Determine whether GetTxFreshness() is used ***
*/!][!VAR "UseGetTxFreshness" = "node:exists(SecOCTxPduProcessing/*[SecOCProvideTxTruncatedFreshnessValue = 'false'])"!][!/*

*** Determine whether GetTxFreshnessTruncData() is used ***
*/!][!VAR "UseGetTxFreshnessTruncData" = "node:exists(SecOCTxPduProcessing/*[SecOCProvideTxTruncatedFreshnessValue = 'true'])"!][!/*

*** Determine whether Csm_MacGenerate() is used ***
*/!][!VAR "UseCsmMacGenerate" = "node:exists(SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'])"!][!/*

*** Determine whether Csm_SignatureGenerate() is used ***
*/!][!VAR "UseCsmSignatureGenerate" = "node:exists(SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'])"!][!/*

*** Number of configured PDUs on the Tx side ***
*/!][!VAR "TxPduNum" = "num:i(count(SecOCTxPduProcessing/*))"!][!/*

*** Determine whether Csm is used asynchronously ***
*/!][!VAR "TxUseCsmAsync" = "node:exists(SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing) = 'CSM_ASYNCHRONOUS']) or node:exists(SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing) = 'CSM_ASYNCHRONOUS'])"!][!/*

*** Determine whether MAC generation result is propagated ***
*/!][!VAR "TxUseMacStatusPropagate" = "node:exists(SecOCTxPduProcessing/*[node:value(SecOCMacGenerateStatusPropagationMode) != 'NONE'])"!][!/*

*** Determine whether the secured PDU collection is used ***
*/!][!VAR "TxUseSecuredCollection" = "node:exists(SecOCTxPduProcessing/*[SecOCTxSecuredPduLayer = 'SecOCTxSecuredPduCollection'])"!][!/*

*** Determine whether the secured PDU collection is used with message link ***
*/!][!VAR "TxUseMessageLink" = "node:exists(SecOCTxPduProcessing/*/SecOCTxSecuredPduLayer/SecOCUseMessageLink)"!][!/*

*** Determine whether the same buffer PDU is used ***
*/!][!VAR "TxUseSameBufferPdu" = "node:exists(SecOCTxPduProcessing/*[node:exists(./SecOCSameBufferPduRef) = 'true'])"!][!/*

*** Determine whether the Tx confirmation timeout is used ***
*/!][!VAR "TxUseConfirmationTimeout" = "node:exists(SecOCTxPduProcessing/*[SecOCTxConfirmationTimeout > 0])"!][!/*

*** Determine whether the sync processing of PDUs is used ***
*/!][!VAR "TxUseSyncPduProcessing" = "node:exists(SecOCTxPduProcessing/*[node:value(SecOCTxSyncPduProcessing) = 'true'])"!][!/*

*** Determine whether the secured header is used ***
*/!][!VAR "TxUseSecuredHeader" = "node:exists(SecOCTxPduProcessing/*[node:exists(./SecOCTxSecuredPduLayer/SecOCAuthPduHeaderLength)]) or node:exists(SecOCTxPduProcessing/*[node:exists(./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCAuthPduHeaderLength)])"!][!/*

*** Determine whether the function SecOC_SPduTxConfirmation is used ***
*/!][!VAR "TxUseSPduConfirmation" = "((num:i(count(SecOCTxPduProcessing/*[node:exists(SecOCUseTxConfirmation) = 'true' and node:value(SecOCUseTxConfirmation) = 'true'])) > 0) and node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!][!/*

*** End of file ***
*/!][!ENDIF!][!//