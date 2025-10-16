/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \version 3.1.33
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/** \brief  Macro that specifies Csm source code.
 **/
#define CSM_SRC
/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 8.3 (required)
 *   All declarations of an object or function shall use the same names and type qualifiers.
 *
 *   Reason:
 *   This is due to deviation made in order to make hardware platfrom compitable with ASR440.
 */

/*==================[includes]====================================================================*/

#include <Csm_Int.h>

#include <SchM_Csm.h>

#include <Csm_[!"$partition.name"!].h>
#include <Rte_Csm_[!"$partition.name"!].h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmAEADDecrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_AEADDecrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
          uint32                                              ciphertextLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
          uint32                                              associatedDataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) tagPtr,
          uint32                                              tagLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  return Csm_AEADDecrypt(jobId,
                         mode,
                         ciphertextPtr,
                         ciphertextLength,
                         associatedDataPtr,
                         associatedDataLength,
                         tagPtr,
                         tagLength,
                         plaintextPtr,
                         plaintextLengthPtr,
                         verifyPtr
                        );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmAEADEncrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_AEADEncrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
          uint32                                              plaintextLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
          uint32                                              associatedDataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) tagPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
)
{
  return Csm_AEADEncrypt(jobId,
                         mode,
                         plaintextPtr,
                         plaintextLength,
                         associatedDataPtr,
                         associatedDataLength,
                         ciphertextPtr,
                         ciphertextLengthPtr,
                         tagPtr,
                         tagLengthPtr
                        );
}
[!ENDIF!][!//

[!IF "num:i(0) != (num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true'  and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/*)) - num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true'  and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmRandomGenerate))) or
        (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != (num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true'  and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/*))))"!][!//
#if ((CSM_API_ENABLED_SERVICE_GENERAL == STD_ON) && (CSM_API_VERSION != CSM_API_VERSION_440))
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_CancelJob
(
  uint32                   job,
  Crypto_OperationModeType mode
)
{
  return Csm_CancelJob(job,
                       mode
                      );
}
#endif /* #if ((CSM_API_ENABLED_SERVICE_GENERAL == STD_ON) && (CSM_API_VERSION != CSM_API_VERSION_440)) */
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_CertificateParse
(
  uint32 keyId
)
{
  return Csm_CertificateParse(keyId
                             );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_CertificateVerify
(
        uint32                                             keyId,
        uint32                                             verifyCryIfKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  return Csm_CertificateVerify(keyId,
                               verifyCryIfKeyId,
                               verifyPtr
                              );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmDecrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Decrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  return Csm_Decrypt(jobId,
                     mode,
                     dataPtr,
                     dataLength,
                     resultPtr,
                     resultLengthPtr
                    );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmEncrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Encrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  return Csm_Encrypt(jobId,
                     mode,
                     dataPtr,
                     dataLength,
                     resultPtr,
                     resultLengthPtr
                    );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmHash/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Hash
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  return Csm_Hash(jobId,
                  mode,
                  dataPtr,
                  dataLength,
                  resultPtr,
                  resultLengthPtr
                 );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyCopy
(
  uint32 keyId,
  uint32 targetKeyId
)
{
  return Csm_KeyCopy(keyId,
                     targetKeyId
                    );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyDerive
(
  uint32 keyId,
  uint32 targetKeyId
)
{
  return Csm_KeyDerive(keyId,
                       targetKeyId
                      );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyElementCopy
(
  uint32 keyId,
  uint32 keyElementId,
  uint32 targetKeyId,
  uint32 targetKeyElementId
)
{
  return Csm_KeyElementCopy(keyId,
                            keyElementId,
                            targetKeyId,
                            targetKeyElementId
                           );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyElementGet
(
        uint32                            keyId,
        uint32                            keyElementId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
)
{
  return Csm_KeyElementGet(keyId,
                           keyElementId,
                           keyPtr,
                           keyLengthPtr
                          );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyElementSet
(
          uint32                            keyId,
          uint32                            keyElementId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) keyPtr,
          uint32                            keyLength
)
{
  return Csm_KeyElementSet(keyId,
                           keyElementId,
                           keyPtr,
                           keyLength
                          );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyExchangeCalcPubVal
(
        uint32                            keyId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
  return Csm_KeyExchangeCalcPubVal(keyId,
                                   publicValuePtr,
                                   publicValueLengthPtr
                                  );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyExchangeCalcSecret
(
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
          uint32                            partnerPublicValueLength
)
{
  return Csm_KeyExchangeCalcSecret(keyId,
                                   partnerPublicValuePtr,
                                   partnerPublicValueLength
                                  );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyGenerate
(
  uint32 keyId
)
{
  return Csm_KeyGenerate(keyId
                        );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeySetValid
(
  uint32 keyId
)
{
  return Csm_KeySetValid(keyId
                        );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmMacGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_MacGenerate
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) macPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) macLengthPtr
)
{
  return Csm_MacGenerate(jobId,
                         mode,
                         dataPtr,
                         dataLength,
                         macPtr,
                         macLengthPtr
                        );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmMacVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_MacVerify
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) macPtr,
          uint32                                              macLength,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  return Csm_MacVerify(jobId,
                       mode,
                       dataPtr,
                       dataLength,
                       macPtr,
                       macLength,
                       verifyPtr
                      );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmRandomGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_RandomGenerate
(
        uint32                            jobId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  return Csm_RandomGenerate(jobId,
                            resultPtr,
                            resultLengthPtr
                           );
}
[!ENDIF!][!//

[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_RandomSeed
(
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) seedPtr,
          uint32                            seedLength
)
{
  return Csm_RandomSeed(keyId,
                        seedPtr,
                        seedLength
                       );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmSignatureGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_SignatureGenerate
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  return Csm_SignatureGenerate(jobId,
                               mode,
                               dataPtr,
                               dataLength,
                               resultPtr,
                               resultLengthPtr
                              );
}
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmSignatureVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_SYNCHRONOUS']))"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_SignatureVerify
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) signaturePtr,
          uint32                                              signatureLength,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  return Csm_SignatureVerify(jobId,
                             mode,
                             dataPtr,
                             dataLength,
                             signaturePtr,
                             signatureLength,
                             verifyPtr
                            );
}
[!ENDIF!][!//

#if (CSM_API_VERSION == CSM_API_VERSION_440)
[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name and node:refexists(./CsmJobKeyRef) and node:value(node:ref(./CsmJobKeyRef)/CsmKeyUsePort) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_KeyElementCopyPartial
(
  uint32 keyId,
  uint32 keyElementId,
  uint32 keyElementSourceOffset,
  uint32 keyElementTargetOffset,
  uint32 keyElementCopyLength,
  uint32 targetKeyId,
  uint32 targetKeyElementId
)
{
  return Csm_KeyElementCopyPartial(keyId,
                                   keyElementId,
                                   keyElementSourceOffset,
                                   keyElementTargetOffset,
                                   keyElementCopyLength,
                                   targetKeyId,
                                   targetKeyElementId
                                  );
}
[!ENDIF!][!//
#endif /* if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmAEADDecrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_AEADDecrypt_OAW (R0440) --------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_AEADDecrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    ciphertextBuffer,
        uint32                                              ciphertextLength,
        Csm_ConstDataPtr                                    associatedDataBuffer,
        uint32                                              associatedDataLength,
        Csm_ConstDataPtr                                    tagBuffer,
        uint32                                              tagLength,
        Csm_DataPtr                                         plaintextBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) plaintextLength,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  return Csm_AEADDecrypt(                                                             jobId,
                                                                                      mode,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) ciphertextBuffer,
                                                                                      ciphertextLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) associatedDataBuffer,
                                                                                      associatedDataLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) tagBuffer,
                                                                                      tagLength,
                         (  P2VAR(uint8,                   AUTOMATIC, CSM_APPL_DATA)) plaintextBuffer,
                                                                                      plaintextLength,
                                                                                      resultBuffer
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_AEADDecrypt_OAW (R2011) --------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_AEADDecrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             ciphertextPtr,
  uint32                   ciphertextLength,
  ConstVoidPtr             associatedDataPtr,
  uint32                   associatedDataLength,
  ConstVoidPtr             tagPtr,
  uint32                   tagLength,
  VoidPtr                  plaintextPtr,
  Csm_LengthPtr            plaintextLengthPtr,
  Csm_VerifyResultPtr      verifyPtr
)
{
  return Csm_AEADDecrypt(                                                             jobId,
                                                                                      mode,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) ciphertextPtr,
                                                                                      ciphertextLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) associatedDataPtr,
                                                                                      associatedDataLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) tagPtr,
                                                                                      tagLength,
                         (  P2VAR(uint8,                   AUTOMATIC, CSM_APPL_DATA)) plaintextPtr,
                                                                                      plaintextLengthPtr,
                         (  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA)) verifyPtr
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmAEADEncrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_AEADEncrypt_OAW (R0440) --------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_AEADEncrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    plaintextBuffer,
        uint32                                              plaintextLength,
        Csm_ConstDataPtr                                    associatedDataBuffer,
        uint32                                              associatedDataLength,
        Csm_DataPtr                                         ciphertextBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
        Csm_DataPtr                                         tagBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) tagLength
)
{
  return Csm_AEADEncrypt(                                            jobId,
                                                                     mode,
                         (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) plaintextBuffer,
                                                                     plaintextLength,
                         (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) associatedDataBuffer,
                                                                     associatedDataLength,
                         (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) ciphertextBuffer,
                                                                     ciphertextLengthPtr,
                         (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) tagBuffer,
                                                                     tagLength
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_AEADEncrypt_OAW (R2011) --------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_AEADEncrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             plaintextPtr,
  uint32                   plaintextLength,
  ConstVoidPtr             associatedDataPtr,
  uint32                   associatedDataLength,
  VoidPtr                  ciphertextPtr,
  Csm_LengthPtr            ciphertextLengthPtr,
  VoidPtr                  tagPtr,
  Csm_LengthPtr            tagLengthPtr
)
{
  return Csm_AEADEncrypt(                                           jobId,
                                                                    mode,
                         (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) plaintextPtr,
                                                                    plaintextLength,
                         (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) associatedDataPtr,
                                                                    associatedDataLength,
                         (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) ciphertextPtr,
                                                                    ciphertextLengthPtr,
                         (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) tagPtr,
                                                                    tagLengthPtr
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != (num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true'  and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/*)))"!][!//
/* --- Csm_CancelJob_OAW (R0440) ----------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_CancelJob_OAW
(
  uint32                   job,
  Crypto_OperationModeType mode
)
{
  return Csm_CancelJob(job,
                       mode
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_CancelJob_OAW (R2011) ----------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_CancelJob_OAW
(
  uint32                   job,
  Crypto_OperationModeType mode
)
{
  return Csm_CancelJob(job,
                       mode
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmDecrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_Decrypt_OAW (R0440) ------------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Decrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_Decrypt(                                            jobId,
                                                                 mode,
                     (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                 dataLength,
                     (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                 resultLength
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_Decrypt_OAW (R2011) ------------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Decrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_Decrypt(                                           jobId,
                                                                mode,
                     (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                dataLength,
                     (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                resultLengthPtr
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmEncrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_Encrypt_OAW (R0440) ------------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Encrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_Encrypt(                                            jobId,
                                                                 mode,
                     (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                 dataLength,
                     (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                 resultLength
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_Encrypt_OAW (R2011) ------------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Encrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_Encrypt(                                           jobId,
                                                                mode,
                     (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                dataLength,
                     (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                resultLengthPtr
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmHash/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_Hash_OAW (R0440) ---------------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Hash_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_Hash(                                            jobId,
                                                              mode,
                  (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                              dataLength,
                  (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                              resultLength
                 );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_Hash_OAW (R2011) ---------------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_Hash_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_Hash(                                           jobId,
                                                             mode,
                  (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                             dataLength,
                  (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                             resultLengthPtr
                 );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmMacGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_MacGenerate_OAW (R0440) --------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_MacGenerate_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         compareBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) macLength
)
{
  return Csm_MacGenerate(                                            jobId,
                                                                     mode,
                         (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                     dataLength,
                         (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) compareBuffer,
                                                                     macLength
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_MacGenerate_OAW (R2011) --------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_MacGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  macPtr,
  Csm_LengthPtr            macLengthPtr
)
{
  return Csm_MacGenerate(                                           jobId,
                                                                    mode,
                         (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                    dataLength,
                         (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) macPtr,
                                                                    macLengthPtr
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmMacVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_MacVerify_OAW (R0440) ----------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_MacVerify_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_ConstDataPtr                                    compareBuffer,
        uint32                                              compareLength,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  return Csm_MacVerify(                                                             jobId,
                                                                                    mode,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                                    dataLength,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) compareBuffer,
                                                                                    compareLength,
                                                                                    resultBuffer
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_MacVerify_OAW (R2011) ----------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_MacVerify_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  ConstVoidPtr             macPtr,
  uint32                   macLength,
  Csm_VerifyResultPtr      verifyPtr
)
{
  return Csm_MacVerify(                                                             jobId,
                                                                                    mode,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                                    dataLength,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) macPtr,
                                                                                    macLength,
                       (  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA)) verifyPtr
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmRandomGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_RandomGenerate_OAW (R0440) ------------------------------------------------------------ */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_RandomGenerate_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_RandomGenerate(                                          jobId,
                            (P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                      resultLength
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_RandomGenerate_OAW (R2011) ------------------------------------------------------------ */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_RandomGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_RandomGenerate(                                         jobId,
                            (P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                     resultLengthPtr
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmSignatureGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_SignatureGenerate_OAW (R0440) --------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_SignatureGenerate_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_SignatureGenerate(                                            jobId,
                                                                           mode,
                               (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                           dataLength,
                               (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                           resultLength
                              );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_SignatureGenerate_OAW (R2011) --------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_SignatureGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_SignatureGenerate(                                           jobId,
                                                                          mode,
                               (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                          dataLength,
                               (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                          resultLengthPtr
                              );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmSignatureVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_SignatureVerify_OAW (R0440) ----------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_SignatureVerify_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_ConstDataPtr                                    compareBuffer,
        uint32                                              compareLength,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  return Csm_SignatureVerify(                                                             jobId,
                                                                                          mode,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                                          dataLength,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) compareBuffer,
                                                                                          compareLength,
                                                                                          resultBuffer
                            );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_SignatureVerify_OAW (R2011) ----------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_SignatureVerify_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  ConstVoidPtr             signaturePtr,
  uint32                   signatureLength,
  Csm_VerifyResultPtr      verifyPtr
)
{
  return Csm_SignatureVerify(                                                             jobId,
                                                                                          mode,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                                          dataLength,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) signaturePtr,
                                                                                          signatureLength,
                             (  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA)) verifyPtr
                            );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobKeySetValid/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobKeySetValid_OAW (R0440) ------------------------------------------------------------ */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobKeySetValid_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeySetValid(jobId,
                            key
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobRandomSeed/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobRandomSeed_OAW (R0440) ------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobRandomSeed_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key,
  Csm_ConstDataPtr         seedBuffer,
  uint32                   seedLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobRandomSeed(                                           jobId,
                                                                      key,
                           (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) seedBuffer,
                                                                      seedLength
                          );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobKeyGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobKeyGenerate_OAW (R0440) ------------------------------------------------------------ */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobKeyGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyGenerate(jobId,
                            key
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobKeyDerive/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobKeyDerive_OAW (R0440) -------------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobKeyDerive_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key,
  uint32                   targetKeyId
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyDerive(jobId,
                          key,
                          targetKeyId
                         );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobKeyExchangeCalcPubVal/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobKeyExchangeCalcPubVal_OAW (R0440) -------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobKeyExchangeCalcPubVal_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        uint32                                              key,
        Csm_DataPtr                                         publicValueBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) publicValueLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyExchangeCalcPubVal(                                          jobId,
                                                                                key,
                                      (P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) publicValueBuffer,
                                                                                publicValueLength
                                     );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobKeyExchangeCalcSecret/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobKeyExchangeCalcSecret_OAW (R0440) -------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobKeyExchangeCalcSecret_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key,
  Csm_ConstDataPtr         partnerPublicValueBuffer,
  uint32                   partnerPublicValueLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyExchangeCalcSecret(                                           jobId,
                                                                                 key,
                                      (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) partnerPublicValueBuffer,
                                                                                 partnerPublicValueLength
                                     );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobCertificateParse/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobCertificateParse_OAW (R0440) ------------------------------------------------------- */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobCertificateParse_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobCertificateParse(jobId,
                                 key
                                );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]/CsmJobPrimitiveRef)/CsmJobCertificateVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!][!//
/* --- Csm_JobCertificateVerify_OAW (R0440) ------------------------------------------------------ */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_[!"$partition.name"!]_JobCertificateVerify_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        uint32                                              key,
        uint32                                              verifyKeyId,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobCertificateVerify(                                                      jobId,
                                                                                        key,
                                                                                        verifyKeyId,
                                                                                        resultBuffer
                                 );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

[!ENDIF!][!//

[!IF "(node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440') or (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'true')"!][!//
[!LOOP "node:order(./CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name],'node:value(./CsmJobId)')"!][!//
[!VAR "vJob" = "node:name(.)"!][!//
[!IF "node:exists(node:ref(./CsmJobPrimitiveRef)/*) = 'true' and node:value(node:ref(./CsmJobPrimitiveRef)/*/*/*[contains(node:name(.),'Processing')]) = 'CSM_ASYNCHRONOUS'"!][!//
FUNC(void, CSM_APPL_CODE) Csm_Call_[!"$vJob"!]_CallbackNotification_CallbackNotification
(
  Std_ReturnType result
)
{
[!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) != 'CSM_API_VERSION_440'"!][!//
  (void) Rte_Call_CallbackNotification_[!"$vJob"!]_CallbackNotification(result);
[!ELSE!][!//
  (void) Rte_Call_[!"$vJob"!]_CallbackNotification_CallbackNotification(result);
[!ENDIF!][!//
}
[!ENDIF!][!//
[!ENDLOOP!]
[!ENDIF!][!//

[!IF "(node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) != 'CSM_API_VERSION_440') and (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'false')"!][!//
[!LOOP "as:modconf('Csm')/CsmCallbacks/CsmCallback/*[node:empty(./CsmCallbackFunc)]"!][!//
[!VAR "cbkName" = "node:name(.)"!][!//
[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:exists(./CsmJobPrimitiveCallbackRef)][node:name(node:ref(./CsmJobPrimitiveCallbackRef)) = $cbkName][node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]) > 0"!][!//
FUNC(void, CSM_APPL_CODE) Csm_Call_[!"$cbkName"!]_CallbackNotification_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
          Std_ReturnType                            result
)
{
  (void) Rte_Call_[!"$cbkName"!]_CallbackNotification_CallbackNotification(job, result);
}

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
