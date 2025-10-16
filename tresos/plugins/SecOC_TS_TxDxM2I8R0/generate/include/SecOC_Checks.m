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

[!NOCODE!]
[!IF "not(var:defined('SECOC_CHECKS.M'))"!][!//
  [!VAR "SECOC_CHECKS.M" = "'true'"!][!//
    [!VAR "NumberOfRxPduWithCollection" = "num:i(count(as:modconf('SecOC')/SecOCRxPduProcessing/*[SecOCRxSecuredPduLayer = 'SecOCRxSecuredPduCollection']))"!][!//
    [!LOOP "node:order(as:modconf('SecOC')/SecOCRxPduProcessing/*)"!][!//
      [!IF "$NumberOfRxPduWithCollection = 0"!][!//
        [!IF "SecOCRxSecuredPduLayer = 'SecOCRxSecuredPdu'"!][!//
          [!IF "node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId, ./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId) = true()"!][!//
            [!ERROR!]For [!"node:name(.)"!] the SecOCRxSecuredLayerPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!IF "SecOCRxSecuredPduLayer = 'SecOCRxSecuredPdu'"!][!//
          [!IF "(node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId, ./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId, ./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId, ./SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId)) = true()"!][!//
              [!ERROR!]For [!"node:name(.)"!] the SecOCRxSecuredLayerPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!IF "(node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId, ./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId, ./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId) or
                 node:containsValue(../*/SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId, ./SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId)) = true()"!][!//
              [!ERROR!]For [!"node:name(.)"!] the SecOCRxAuthenticPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
          [!IF "(node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxSecuredLayerPduId, ./SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId) or
                 node:containsValue(../*/SecOCRxSecuredPduLayer/SecOCRxAuthenticPdu/SecOCRxAuthenticPduId, ./SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId, ./SecOCRxSecuredPduLayer/SecOCRxCryptographicPdu/SecOCRxCryptographicPduId)) = true()"!][!//
              [!ERROR!]For [!"node:name(.)"!] the SecOCRxCryptographicPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "
        (count(node:refs(node:refs(as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing) = 'CSM_ASYNCHRONOUS']/SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc) +
         count(node:refs(node:refs(as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing) = 'CSM_ASYNCHRONOUS']/SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc))
          < (count(node:refs(as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing) = 'CSM_ASYNCHRONOUS']/SecOCRxPduMainFunctionRef)) +
             count(node:refs(as:modconf('SecOC')/SecOCRxPduProcessing/*[node:existsAndTrue(./SecOCRxSecuredPduLayer/SecOCSecuredRxPduVerification)][node:exists(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify) = 'true'][node:value(as:ref(as:ref(./SecOCRxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing) = 'CSM_ASYNCHRONOUS']/SecOCRxPduMainFunctionRef)))"!][!//
          [!ERROR!]At least a callback function should be defined for each EcucPartition referenced by asynchronous SecOCRxPdus.[!ENDERROR!][!//
    [!ENDIF!][!//

    [!VAR "NumberOfTxPduWithCollection" = "num:i(count(as:modconf('SecOC')/SecOCTxPduProcessing/*[SecOCTxSecuredPduLayer = 'SecOCTxSecuredPduCollection']))"!][!//
    [!LOOP "node:order(as:modconf('SecOC')/SecOCTxPduProcessing/*)"!][!//
      [!IF "$NumberOfTxPduWithCollection = 0"!][!//
        [!IF "SecOCTxSecuredPduLayer = 'SecOCTxSecuredPdu'"!][!//
          [!IF "node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId, ./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId) = true()"!][!//
            [!ERROR!]For [!"node:name(.)"!] the SecOCTxSecuredLayerPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!IF "SecOCTxSecuredPduLayer = 'SecOCTxSecuredPdu'"!][!//
          [!IF "(node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId, ./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId, ./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId, ./SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId)) = true()"!][!//
              [!ERROR!]For [!"node:name(.)"!] the SecOCTxSecuredLayerPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!IF "(node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId, ./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId, ./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId) or
                 node:containsValue(../*/SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId, ./SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId)) = true()"!][!//
              [!ERROR!]For [!"node:name(.)"!] the SecOCTxAuthenticPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
          [!IF "(node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxSecuredLayerPduId, ./SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId) or
                 node:containsValue(../*/SecOCTxSecuredPduLayer/SecOCTxAuthenticPdu/SecOCTxAuthenticPduId, ./SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId) or
                 node:containsValue(../*[node:name(node:current()) != node:name(.)]/SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId, ./SecOCTxSecuredPduLayer/SecOCTxCryptographicPdu/SecOCTxCryptographicPduId)) = true()"!][!//
              [!ERROR!]For [!"node:name(.)"!] the SecOCTxCryptographicPduId has to be unique.[!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "
        (count(node:refs(node:refs(as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing) = 'CSM_ASYNCHRONOUS']/SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc) +
         count(node:refs(node:refs(as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing) = 'CSM_ASYNCHRONOUS']/SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveCallbackRef)/CsmCallbackFunc))
          < (count(node:refs(as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing) = 'CSM_ASYNCHRONOUS']/SecOCTxPduMainFunctionRef)) +
             count(node:refs(as:modconf('SecOC')/SecOCTxPduProcessing/*[node:exists(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate) = 'true'][node:value(as:ref(as:ref(./SecOCTxAuthServiceConfigRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing) = 'CSM_ASYNCHRONOUS']/SecOCTxPduMainFunctionRef)))"!]
      [!ERROR!]A callback function should be defined for each EcucPartition referenced by asynchronous SecOCTxPdus.[!ENDERROR!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!]