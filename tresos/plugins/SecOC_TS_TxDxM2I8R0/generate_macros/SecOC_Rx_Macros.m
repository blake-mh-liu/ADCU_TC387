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
*/!][!IF "not(var:defined('SECOC_RX_MACROS_M'))"!][!//
[!VAR "SECOC_RX_MACROS_M"="'true'"!][!/*

*** Macro used to establish the Csm Job to Rx Pdu association
*/!]
[!MACRO "CreateJobRxPduAssoc"!][!NOCODE!]
[!IF "not(var:defined('CsmRxCbks'))"!]
  [!VAR "CsmRxCbks" = "text:join(node:refs(node:refs(as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing) = 'CSM_ASYNCHRONOUS']/SecOCRxAuthServiceConfigRef | as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing) = 'CSM_ASYNCHRONOUS']/SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc, ';')"!]

  [!VAR "cbkRxAssocIndices" = "''"!]
  [!VAR "cbkRxAssocSlices" = "''"!]

  [!VAR "startIdx" = "0"!]
  [!VAR "cbkPduOrder" = "''"!]
  [!VAR "cbkPduOrderIdx" = "0"!]
  [!LOOP "node:order(as:modconf('SecOC')/SecOCRxPduProcessing/*)"!]
    [!VAR "cbkPduOrder" = "concat($cbkPduOrder, node:name(.), ':', num:i($cbkPduOrderIdx), '|')"!]
    [!VAR "cbkPduOrderIdx" = "$cbkPduOrderIdx + 1"!]
  [!ENDLOOP!]
  [!FOR "i" = "1" TO "count(text:split($CsmRxCbks, ';'))"!]
    [!VAR "numRef" = "0"!]
    [!VAR "cbkFunc" = "text:split($CsmRxCbks, ';')[position() = $i]"!]
    [!VAR "indices" = "''"!]
    [!LOOP "as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing) = 'CSM_ASYNCHRONOUS'][string(node:ref(node:ref(SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc) = $cbkFunc] | as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing) = 'CSM_ASYNCHRONOUS'][string(node:ref(node:ref(SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc) = $cbkFunc]"!]
      [!VAR "numRef" = "$numRef + 1"!]
      [!VAR "indices" = "concat($indices, text:split(text:grep(text:split($cbkPduOrder, '|'), concat('^', node:name(.), '\:\d+$'))[1], ':')[2], ';')"!]
    [!ENDLOOP!]
    [!VAR "endIdx" = "$startIdx + $numRef"!]
    [!VAR "cbkRxAssocSlices" = "concat($cbkRxAssocSlices, $cbkFunc, ':', num:i($startIdx), ':', num:i($endIdx), '|')"!]
    [!VAR "cbkRxAssocIndices" = "concat($cbkRxAssocIndices, $cbkFunc, ':', $indices, '|')"!]
    [!VAR "startIdx" = "$endIdx"!]
  [!ENDFOR!]
  [!VAR "cbkRxRefNum" = "num:i($endIdx)"!]

[!ENDIF!][!// not(var:defined('CsmRxCbks'))
[!ENDNOCODE!][!ENDMACRO!][!/*

*** Macro used to establish the Csm Job to Rx Pdu association
*/!]
[!MACRO "GetCbkAssocRxPduSlice", "cbkName"!][!NOCODE!]
  [!VAR "cbkSliceStart" = "num:i(0)"!]
  [!VAR "ind" = "$cbkRxAssocIndices"!]
  [!VAR "slcs" = "$cbkRxAssocSlices"!]
  [!VAR "cbkSliceEnd" = "num:i($RxPduNum)"!]

  [!VAR "cbkPduIdxs" = "text:split(text:grep(text:split($ind, '|'), concat('^', $cbkName, '.*$'))[1], ':')[2]"!]
  [!VAR "sCbk" = "text:grep(text:split($slcs, '|'), concat('^', $cbkName, '.*$'))[1]"!]
  [!VAR "cbkSliceStart" = "text:split($sCbk, ':' )[2]"!]
  [!VAR "cbkSliceEnd" = "text:split($sCbk, ':')[3]"!]
[!ENDNOCODE!][!ENDMACRO!][!/*

*** Determine whether GetRxFreshness() is used ***
*/!][!VAR "UseGetRxFreshness" = "node:exists(SecOCRxPduProcessing/*[SecOCUseAuthDataFreshness = 'false'])"!][!/*

*** Determine whether GetRxFreshnessAuthData() is used ***
*/!][!VAR "UseGetRxFreshnessAuthData" = "node:exists(SecOCRxPduProcessing/*[SecOCUseAuthDataFreshness = 'true'])"!][!/*

*** Determine whether Csm_MacVerify() is used ***
*/!][!VAR "UseCsmMacVerify" = "node:exists(SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'])"!][!/*

*** Determine whether Csm_SignatureVerify() is used ***
*/!][!VAR "UseCsmSignatureVerify" = "node:exists(SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'])"!][!/*

*** Number of configured PDUs on the Rx side ***
*/!][!VAR "RxPduNum" = "num:i(count(SecOCRxPduProcessing/*))"!][!/*

*** Determine whether the propagation of the reception overflow strategy is used or not ***
*/!][!VAR "RxUseRecvStrategyReplace" = "node:exists(SecOCRxPduProcessing/*[node:value(./SecOCReceptionOverflowStrategy) = 'REPLACE'])"!][!/*

*** Determine whether the reception overflow strategy "QUEUE" is used or not ***
*/!][!VAR "RxUseRecvStrategyQueue" = "node:exists(SecOCRxPduProcessing/*[node:value(./SecOCReceptionOverflowStrategy) = 'QUEUE'])"!][!/*

*** Determine whether the secured PDU collection is used ***
*/!][!VAR "RxUseSecuredCollection" = "node:exists(SecOCRxPduProcessing/*[SecOCRxSecuredPduLayer = 'SecOCRxSecuredPduCollection'])"!][!/*

*** Determine whether the secured PDU collection is used with message link ***
*/!][!VAR "RxUseMessageLink" = "node:exists(SecOCRxPduProcessing/*/SecOCRxSecuredPduLayer/SecOCUseMessageLink)"!][!/*

*** Determine whether the same buffer PDU is used ***
*/!][!VAR "RxUseSameBufferPdu" = "node:exists(SecOCRxPduProcessing/*[node:exists(./SecOCSameBufferPduRef) = 'true'])"!][!/*

*** Determine whether the sync processing of PDUs is used ***
*/!][!VAR "RxUseSyncPduProcessing" = "node:exists(SecOCRxPduProcessing/*[node:value(SecOCRxSyncPduProcessing) = 'true'])"!][!/*

*** Determine whether the secured header is used ***
*/!][!VAR "RxUseSecuredHeader" = "node:exists(SecOCRxPduProcessing/*[node:exists(./SecOCRxSecuredPduLayer/SecOCAuthPduHeaderLength)]) or node:exists(SecOCRxPduProcessing/*[node:exists(./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCAuthPduHeaderLength)])"!][!/*

*** Determine whether Csm is used asynchronously ***
*/!][!VAR "RxUseCsmAsync" = "node:exists(SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing) = 'CSM_ASYNCHRONOUS']) or node:exists(SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing) = 'CSM_ASYNCHRONOUS'])"!][!/*

*** Determine whether the verification is done or not ***
*/!][!VAR "RxSkipVerification" = "node:exists(SecOCRxPduProcessing/*[SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification = 'false'])"!][!/*

*** Determine whether the meta data is handled or not by SecOC ***
*/!][!VAR "RxUseMetaData" = "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEnableMetaDataUse)"!][!/*

*** Determine whether the propagation of the verification status is used or not ***
*/!][!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) != 'NONE'"!][!/*
*/!][!VAR "RxUsePropVerStatus" = "'true'"!][!/*
*/!][!ELSE!][!/*
*/!][!VAR "RxUsePropVerStatus" = "'false'"!][!/*
*/!][!ENDIF!][!/*

*** Determine whether the propagation of the verification status is used or not ***
*/!][!VAR "RxUseCSPropVerStatus" = "node:exists(SecOCRxPduProcessing/*[node:value(./SecOCClientServerVerificationStatusPropagationMode)!='NONE'])"!][!/*

*** End of file ***
*/!][!ENDIF!][!//