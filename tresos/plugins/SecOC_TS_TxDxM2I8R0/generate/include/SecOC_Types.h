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

#ifndef SECOC_TYPES_H
#define SECOC_TYPES_H
[!SELECT "as:modconf('SecOC')"!][!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

[!// This file contains macros for configuration values
[!INCLUDE "../../generate_macros/SecOC_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Rx_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Tx_Macros.m"!][!//
[!//

/* !LINKSTO SecOC.ASR430.SWS_SecOC_00002,1 */
#include <ComStack_Types.h>
#include <Csm.h>
#include <SecOC_Version.h>

[!IF "'true' = node:value(SecOCEbGeneral/SecOCRteUsage)"!][!//
[!IF "num:i(count(SecOCMainFunctionRx/*)) = 0 and num:i(count(SecOCMainFunctionTx/*)) = 0"!][!//
#include <Rte_SecOC_Type.h>
[!ELSE!][!//
[!LOOP "node:refs(SecOCMainFunctionRx/*/SecOCMainFunctionRxPartitionRef | SecOCMainFunctionTx/*/SecOCMainFunctionTxPartitionRef)"!][!//
[!VAR "ecucPartition" = "node:name(.)"!][!//
#include <Rte_SecOC_[!"string($ecucPartition)"!]_Type.h>
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//

/*==================[macros]======================================================================*/

/** \brief SecOC module is not initialized
 */
#if (defined SECOC_UNINIT)
#error SECOC_UNINIT already defined
#endif
#define SECOC_UNINIT                                                                    0U

/** \brief SecOC module is initialized
 */
#if (defined SECOC_INIT)
#error SECOC_INIT already defined
#endif
#define SECOC_INIT                                                                      1U

/** \brief Return value for a successful "get freshness value" request
 */
#if (defined SECOC_E_OK)
#error SECOC_E_OK already defined
#endif
#define SECOC_E_OK                                                                      0U

/** \brief Return value for an unsuccessful "get freshness value" request
 */
#if (defined SECOC_E_NOT_OK)
#error SECOC_E_NOT_OK already defined
#endif
#define SECOC_E_NOT_OK                                                                  1U

/** \brief Return value if the "get freshness value" service is currently busy
 */
#if (defined SECOC_E_BUSY)
#error SECOC_E_BUSY already defined
#endif
#define SECOC_E_BUSY                                                                    2U

/** \brief Defines, that Both 'True' and 'False' AuthenticationStatus is propagated
 */
#if (defined SECOC_STATUS_PROP_BOTH)
#error SECOC_STATUS_PROP_BOTH already defined
#endif
#define SECOC_STATUS_PROP_BOTH                                                          2U

/** \brief Defines, that Only 'False' AuthenticationStatus is propagated
 */
#if (defined SECOC_STATUS_PROP_FAILURE_ONLY)
#error SECOC_STATUS_PROP_FAILURE_ONLY already defined
#endif
#define SECOC_STATUS_PROP_FAILURE_ONLY                                                  1U

/** \brief Defines, that No AuthenticationStatus is propagated
 */
#if (defined SECOC_STATUS_PROP_NONE)
#error SECOC_STATUS_PROP_NONE already defined
#endif
#define SECOC_STATUS_PROP_NONE                                                          0U

/** \brief SecOC does not queries the freshness.
 */
#if (defined SECOC_FRESHNESS_NONE)
#error SECOC_FRESHNESS_NONE already defined
#endif
#define SECOC_FRESHNESS_NONE                                                            0U

/** \brief SecOC queries the freshness for every PDU to process using the Rte service port
 *         FreshnessManagement.
 */
#if (defined SECOC_FRESHNESS_RTE)
#error SECOC_FRESHNESS_RTE already defined
#endif
#define SECOC_FRESHNESS_RTE                                                             1U

/** \brief SecOC queries the freshness for every PDU to process using the C function defined by the
 *         configuration parameter SecOCFreshnessValueFuncName.
 */
#if (defined SECOC_FRESHNESS_CFUNC)
#error SECOC_FRESHNESS_CFUNC already defined
#endif
#define SECOC_FRESHNESS_CFUNC                                                           2U

/** \brief SecOC does not propagate the verification status.
 */
#if (defined SECOC_VERIFICATION_STATUS_PROP_NONE)
#error SECOC_VERIFICATION_STATUS_PROP_NONE already defined
#endif
#define SECOC_VERIFICATION_STATUS_PROP_NONE   0U

/** \brief SecOC propagates the verification status via the AUTOSAR defined API(s).
 */
#if (defined SECOC_VERIFICATION_STATUS_PROP_AUTOSAR)
#error SECOC_VERIFICATION_STATUS_PROP_AUTOSAR already defined
#endif
#define SECOC_VERIFICATION_STATUS_PROP_AUTOSAR    1U

/** \brief SecOC propagates the verification status via the custom API(s).
 */
#if (defined SECOC_VERIFICATION_STATUS_PROP_EB)
#error SECOC_VERIFICATION_STATUS_PROP_EB already defined
#endif
#define SECOC_VERIFICATION_STATUS_PROP_EB  2U

/** \brief Macro which defines that the GetTxFreshness function shall be used to
 *         obtain the freshness value.
 */
#if (defined SECOC_GET_TX_FRESHNESS_FUNC_TYPE)
#error SECOC_GET_TX_FRESHNESS_FUNC_TYPE already defined
#endif
#define SECOC_GET_TX_FRESHNESS_FUNC_TYPE                                                0U

/** \brief Macro which defines that the GetTxFreshnessTruncData function shall be used to
 *         obtain the freshness value.
 */
#if (defined SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE)
#error SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE already defined
#endif
#define SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE                                      1U

/** \brief Macro which defines that the GetTxFreshness function shall be used to
 *         obtain the freshness value.
 */
#if (defined SECOC_GET_RX_FRESHNESS_FUNC_TYPE)
#error SECOC_GET_RX_FRESHNESS_FUNC_TYPE already defined
#endif
#define SECOC_GET_RX_FRESHNESS_FUNC_TYPE                                                0U

/** \brief Macro which defines that the GetRxFreshnessAuthData function shall be used to
 *         obtain the freshness value.
 */
#if (defined SECOC_GET_RX_FRESHNESS_AUTHDATA_FUNC_TYPE)
#error SECOC_GET_RX_FRESHNESS_AUTHDATA_FUNC_TYPE already defined
#endif
#define SECOC_GET_RX_FRESHNESS_AUTHDATA_FUNC_TYPE                                       1U

/** \brief Macro which defines that the Csm_MacGenerate function shall be used to generate
 *         the authentication information.
 */
#if (defined SECOC_TX_MACGENERATE_FUNC_TYPE)
#error SECOC_TX_MACGENERATE_FUNC_TYPE already defined
#endif
#define SECOC_TX_MACGENERATE_FUNC_TYPE                                                  0U

/** \brief Macro which defines that the Csm_SignatureGenerate function shall be used to generate
 *         the authentication information.
 */
#if (defined SECOC_TX_SIGNATUREGENERATE_FUNC_TYPE)
#error SECOC_TX_SIGNATUREGENERATE_FUNC_TYPE already defined
#endif
#define SECOC_TX_SIGNATUREGENERATE_FUNC_TYPE                                            1U

/** \brief Macro which defines that the Csm_MacVerify function shall be used to verify
 *         the authentication information.
 */
#if (defined SECOC_RX_MACVERIFY_FUNC_TYPE)
#error SECOC_RX_MACVERIFY_FUNC_TYPE already defined
#endif
#define SECOC_RX_MACVERIFY_FUNC_TYPE                                                    0U

/** \brief Macro which defines that the Csm_SignatureVerify function shall be used to verify
 *         the authentication information.
 */
#if (defined SECOC_RX_SIGNATUREVERIFY_FUNC_TYPE)
#error SECOC_RX_SIGNATUREVERIFY_FUNC_TYPE already defined
#endif
#define SECOC_RX_SIGNATUREVERIFY_FUNC_TYPE                                              1U

/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00115,1 */
[!IF "'true' = node:value(SecOCGeneral/SecOCEnableSecurityEventReporting)"!][!//
[!IF "'true' = node:refvalid(as:modconf('SecOC')/SecOCGeneral/SecOCSecurityEventRefs/SECOC_SEV_MAC_VERIFICATION_FAILED)"!][!//
/** \brief Macro which defines the security event for failure of MAC verification of a
 *         received PDU.
 */
#if (defined SECOC_SEV_MAC_VERIFICATION_FAILED)
#error SECOC_SEV_MAC_VERIFICATION_FAILED already defined
#endif
#define SECOC_SEV_MAC_VERIFICATION_FAILED                                               [!"node:value(node:ref(as:modconf('SecOC')/SecOCGeneral/SecOCSecurityEventRefs/SECOC_SEV_MAC_VERIFICATION_FAILED)/IdsMInternalEventId)"!]U[!//
[!ELSE!]
#define SECOC_SEV_MAC_VERIFICATION_FAILED                                               0xFFFFU[!//
[!ENDIF!]

/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00115,1 */
/* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00115,1 */
[!IF "'true' = node:refvalid(as:modconf('SecOC')/SecOCGeneral/SecOCSecurityEventRefs/SECOC_SEV_FRESHNESS_NOT_AVAILABLE)"!][!//
/** \brief Macro which defines the security event for failure of MAC verification of a
 *         received PDU.
 */
#if (defined SECOC_SEV_FRESHNESS_NOT_AVAILABLE)
#error SECOC_SEV_FRESHNESS_NOT_AVAILABLE already defined
#endif
#define SECOC_SEV_FRESHNESS_NOT_AVAILABLE                                               [!"node:value(node:ref(as:modconf('SecOC')/SecOCGeneral/SecOCSecurityEventRefs/SECOC_SEV_FRESHNESS_NOT_AVAILABLE)/IdsMInternalEventId)"!]U[!//
[!ELSE!]
#define SECOC_SEV_FRESHNESS_NOT_AVAILABLE                                               0xFFFFU[!//
[!ENDIF!]
[!ENDIF!]

/*==================[type definitions]============================================================*/

[!IF "'false' = node:value(SecOCEbGeneral/SecOCRteUsage)"!][!//
/* \cond SECOC_DOC_INTERNAL_MACROS */
/* \endcond */
/** \brief States of the SecOC module.
 *
 * Range: SECOC_UNINIT, SECOC_INIT.
 */
typedef uint8 SecOC_StateType;
[!ENDIF!][!//

/** \brief Length type of the Data ID element.
 */
[!IF "node:value(SecOCEbGeneral/SecOCDataIdLength) = 'UINT8'"!][!//
typedef uint8 SecOC_DataIdLengthType;
[!ELSE!][!//
[!IF "node:value(SecOCEbGeneral/SecOCDataIdLength) = 'UINT16'"!][!//
typedef uint16 SecOC_DataIdLengthType;
[!ELSE!][!//
typedef uint32 SecOC_DataIdLengthType;
[!ENDIF!][!//
[!ENDIF!][!//

/**
 * \brief state machine state type
 */
typedef P2FUNC(void, TYPEDEF, SecOC_SmStateType) (uint16 instId);

[!IF "$RxPduNum > 0"!][!//
#ifndef RTE_TYPE_SecOC_VerificationResultType
/* \cond SECOC_DOC_INTERNAL_MACROS */
#define RTE_TYPE_SecOC_VerificationResultType
/* \endcond */
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00149,3, SecOC.ASR20-11.Rx.SWS_SecOC_00149,1 */
/** \brief Type, to indicate verification results
 *
 * Range: SECOC_VERIFICATIONSUCCESS, SECOC_VERIFICATIONFAILURE, SECOC_FRESHNESSFAILURE,
 *        SECOC_AUTHENTICATIONBUILDFAILURE, SECOC_NO_VERIFICATION, SECOC_MACSERVICEFAILURE.
 */
typedef uint8 SecOC_VerificationResultType;
#endif /* #ifndef RTE_TYPE_SecOC_VerificationResultType */

/** \brief This type defines the possibilities that are available to override the verification status
 */
#ifndef RTE_TYPE_SecOC_OverrideStatusType
/** \cond SECOC_DOC_INTERNAL_MACROS */
#define RTE_TYPE_SecOC_OverrideStatusType
/** \endcond */
/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00991,1 */
typedef uint8 SecOC_OverrideStatusType;
#endif

#ifndef RTE_TYPE_SecOC_VerificationStatusType
/** \cond SECOC_DOC_INTERNAL_MACROS */
#define RTE_TYPE_SecOC_VerificationStatusType
/** \endcond */
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00160,4, SecOC.ASR20-11.Rx.SWS_SecOC_00160,1 */
/**
 * \struct SecOC_VerificationStatusType
 * \brief Data structure to bundle the status of a verification attempt for a specific Freshness
 *        Value and Data ID.
 *//**
 * \var SecOC_VerificationStatusType::freshnessValueID
 * \brief Identifier of the Freshness Value which resulted in the Verification Result
 *//**
 * \var SecOC_VerificationStatusType::verificationStatus
 * \brief Result of verification attempt.
 *//**
 * \var SecOC_VerificationStatusType::secOCDataId
 * \brief Identifier for the Secured I-PDU.
 *//**
 * \var SecOC_VerificationStatusType::verificationReturn
 * \brief Result of verification attempt.
 */
typedef struct
{
  uint16                       freshnessValueID;
  SecOC_VerificationResultType verificationStatus;
  SecOC_DataIdLengthType       secOCDataId;
[!IF "node:value(SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) = 'EB_CUSTOM'"!][!//
  Std_ReturnType               verificationReturn;
[!ENDIF!][!//
}
SecOC_VerificationStatusType;
#endif
[!//
[!IF "(count(SecOCGeneral/SecOCVerificationStatusCallout/*) > 0) and ($RxUsePropVerStatus = 'true')"!][!//

/**
 * \brief Pointer to verification status callout function type
 */
typedef P2FUNC(void, TYPEDEF, SecOC_VerificationStatusCalloutType) (SecOC_VerificationStatusType verificationStatus);
[!ENDIF!][!//

[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
[!IF "($UseGetRxFreshnessAuthData = 'true')"!][!//
/**
 * \brief Pointer to the external GetRxFreshnessAuthData function.
 */
typedef P2FUNC(Std_ReturnType, SECOC_CODE, GetRxFreshnessAuthDataType)
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
[!ENDIF!][!//

[!IF "($UseGetRxFreshness = 'true')"!][!//
/**
 * \brief Pointer to the external GetRxFreshness function.
 */
typedef P2FUNC(Std_ReturnType, SECOC_CODE, GetRxFreshnessType)
(
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
          uint16                              SecOCCounterSyncAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "($RxUseRecvStrategyQueue = 'true')"!][!//
/**
 * \struct SecOC_RxQueueType
 * \brief Data format used to store the received secured PDUs in a queue
 */
typedef struct
{
  /* Pointer to the next valid address to write */
       P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA)      WritePtr;
  /* Pointer to the next valid address to read */
       P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA)      ReadPtr;
  /* Stored received secured PDU buffer length currently in the buffer */
  CONSTP2VAR(PduLengthType, TYPEDEF, SECOC_VAR)       StoredPduLength;
  /* Maximum number of PDUs in the buffer */
             uint16                                   QueueSize;
  /* Number of PDUs currently in the buffer */
             uint16                                   Count;
  /* Partial write remaining bytes */
             PduLengthType                            WriteRemainingBytes;
  /* Read buffer index */
             uint16                                   ReadBufferIndex;
  /* Write buffer index */
             uint16                                   WriteBufferIndex;
  /* Flag which indicates if a partial write operation is in progress */
             boolean                                  WriteInProgress;
} SecOC_RxQueueType;
[!ENDIF!][!//

/**
 * \struct SecOC_RxConfigType
 * \brief SecOC Configuration type for Rx Pdus, which shall be verified by the SecOC module.
 */
typedef struct
{
  /* Csm Job ID */
  uint32                             CsmJobId;
[!IF "('true' = node:value(SecOCEbGeneral/SecOCRteUsage)) and (num:i(count(SecOCMainFunctionRx/*)) > 0)"!][!//
  uint32                             MainFunctionIndex;
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
[!IF "($UseGetRxFreshnessAuthData = 'true')"!][!//
  /* Pointer to the GetRxFreshnessAuthData function */
  GetRxFreshnessAuthDataType         GetRxFreshnessAuthData;
[!ENDIF!][!//
[!IF "($UseGetRxFreshness = 'true')"!][!//
  /* Pointer to the GetRxFreshness function */
  GetRxFreshnessType                 GetRxFreshness;
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$RxUseMessageLink = 'true'"!][!//
  /* Length of message link in the Pdu */
  uint16                             MessageLinkLength;
  /* Position of message linker inside the authentic I-PDU */
  uint16                             MessageLinkPos;
[!ENDIF!][!//
  /* ID of the secured Pdu at SecOC (used for e.g. SecOC_StartOfReception) */
  uint16                             PduIdForSecuredPduAtSecOC;
[!IF "$RxUseSecuredCollection = 'true'"!][!//
  /* ID of the received authentic Pdu at SecOC (used for e.g. SecOC_StartOfReception) */
  uint16                             PduIdForReceivedAuthPduAtSecOC;
  /* ID of the cryptographic Pdu at SecOC (used for e.g. SecOC_StartOfReception) */
  uint16                             PduIdForCryptoPduAtSecOC;
[!ENDIF!][!//
  /* Max allowed Freshness Value sync Attempts */
  uint16                             MaxFVSyncAttempts;
  /* Max allowed of authentication build attempts that are to be carried out  */
  uint16                             MaxAuthAttempts;
[!IF "($UseGetRxFreshnessAuthData = 'true') and (node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!][!//
  /* The length (in bits) of the area within the Pdu which will be provided to the freshness value manager */
  uint16                             AuthDataFreshnessValueLength;
  /* The start position (offset in bits) of the area within the Pdu which will be provided to the freshness value manager */
  uint16                             AuthDataFreshnessValueStartPosition;
[!ENDIF!][!//
[!IF "node:value(SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!]
  /* Id of the Secured I-PDU at EcuC level */
  uint16                             PduIdForSecuredPduAtEcuC;
  /* Id of the Authemtic I-PDU at EcuC level */
  uint16                             PduIdForAuthPduAtEcuC;
[!ENDIF!][!//
  /* Flag which indicates the reception overflow strategy */
  uint8                              ReceptionStrategy;
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
  /* Defines which freshness function should be called */
  uint8                              GetRxFreshnessFuncType;
[!ENDIF!][!//
  /* Defines which Csm function should be called */
  uint8                              CsmFuncType;
[!IF "$RxUseSecuredHeader = 'true'"!][!//
  /* Length of the secured PDU header which reprensents the payload length inside the secured PDU or lower layer authentic PDU */
  uint8                              SecuredPduHeaderLength;
[!ENDIF!][!//
[!IF "node:value(SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!]
  /* Length of the MetaData */
  uint8                              MetaDataLength;
[!ENDIF!][!//
[!IF "$RxUseSecuredCollection = 'true'"!][!//
  /* Flag which indicates whether the secured PDU collection is used or not */
  boolean                            UseSecPduCollection;
[!ENDIF!][!//
[!IF "'true' = node:exists(SecOCEbGeneral/SecOCRxShapeFuncName)"!]
  /* Flag which indicates whether the functionality to shape the secured PDU is used or not */
  boolean                            UseShapeSecuredPdu;
[!ENDIF!][!//
[!IF "$RxUseCsmAsync = 'true'"!][!//
  /* Flag which indicates whether the Csm service is used in asynchronous mode or not */
  boolean                            UseCsmAsync;
[!ENDIF!][!//
[!IF "$RxSkipVerification = 'true'"!][!//
  /* Flag which indicates whether the MAC verification will be skipped or performed */
  boolean                            SkipVerification;
[!ENDIF!][!//
  /* Flag which indicates whether the TP interfaces (in the communication with PduR) will be used or not */
  boolean                            UseTp;
[!IF "$RxUseSyncPduProcessing = 'true'"!][!//
  /* Flag indicating whether synchronous processing will be used or not */
  boolean                            UseSyncProcessing;
[!ENDIF!][!//
  /* Flag indicating if the dynamic length of the PDU is accepted or not */
  boolean                            UseDynamicLength;
[!IF "node:value(SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!][!//
  /* Flag indicating whether MetaData will be used or not */
  boolean                            UseMetaData;
[!ENDIF!][!//
}
SecOC_RxConfigType;

/**
 * \struct SecOC_RxDataType
 * \brief Structure holding the Datas of a Rx Pdu
 */
typedef struct
{
[!IF "$UseCsmJobRefCallout = 'true'"!][!//
  /* !LINKSTO  SecOC.EB.Rx.SWS_SecOC_00021,1 */
  /* The Csm Job ID that shall be used (if SecOCCsmJobRefCallout enabled) */
  uint32                                   CsmJobIdPostDefined;
[!ENDIF!][!//
[!IF "$RxUseSameBufferPdu = 'true'"!][!//
  /* Flag which indicates if the buffer is available or used */
  CONSTP2VAR(uint8, TYPEDEF, SECOC_VAR)    BufferUsed;
[!ENDIF!][!//
  /* Holds the length and the pointer to buffer holding the received secured Pdu */
  PduInfoType                              ReceivedSecuredPdu;
[!IF "$RxUseSecuredCollection = 'true'"!][!//
  /* Holds the length and the pointer to buffer holding the received authentic Pdu */
  PduInfoType                              ReceivedAuthPdu;
  /* Holds the length and the pointer to buffer holding the cryptographic Pdu */
  PduInfoType                              CryptoPdu;
[!ENDIF!][!//
  /* Holds the length and the pointer to buffer holding the secured Pdu */
  PduInfoType                              SecuredPdu;
  /* Pointer to buffer holding the data to authenticator (used for eg. MAC services) */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         DataToAuthenticator;
  /* Pointer to buffer holding the complete freshness value */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         FreshnessVerifyValue;
  /* Pointer to buffer holding the authenticator (eg. MAC) */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         Authenticator;
[!IF "($UseGetRxFreshnessAuthData = 'true') and (node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]
  /* Pointer to buffer holding the part of the secured Pdu that will be sent to the freshness value manager */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         AuthDataFreshnessValueBuffer;
[!ENDIF!][!//
[!IF "node:value(SecOCEbGeneral/SecOCEnableMetaDataUse) = 'true'"!]
  /* Pointer to buffer holding the MetaData */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         SecuredPduMetaData;
[!ENDIF!][!//
[!IF "$RxUseRecvStrategyQueue = 'true'"!][!//
  /* Queue used to stored the received secured PDUs */
  SecOC_RxQueueType                        Queue;
[!ENDIF!][!//
  /* The length of the payload within the secured PDU (authentic data) */
  PduLengthType                            DataLength;
  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00234,1 */
  /* Number of authentication (build) attempts */
  uint16                                   AuthAttempts;
  /* Number of sync attempts */
  uint16                                   FVSyncAttempts;
  /* The verification procedure result */
  SecOC_VerificationResultType             VerificationResult;
  /* The verification override status (on init, nothing shall be overridden) */
  uint8                                    VerifyStatusOverride;
  /* The number of messages to override (on init, nothing shall be overridden) */
  uint8                                    NumMsgToOverride;
  /* The index of the SecOC Rx state machine for each PDU configured */
  uint8                                    State;
  /* Rx state machine events emitted by APIs to the PduR */
  uint8                                    PduREvent;
[!IF "$RxUseSecuredCollection = 'true'"!][!//
  /* Rx state machine events emitted by APIs to the PduR */
  uint8                                    PduRIndicationForAuth;
  /* Tx state state machine events emitted by APIs to the PduR */
  uint8                                    PduRIndicationForCrypto;
[!ENDIF!][!//
[!IF "$RxUseCsmAsync = 'true'"!][!//
  /* Rx state machine events emitted by APIs to the verifier */
  uint8                                    CsmEvent;
[!ENDIF!][!//
  /* Variable to hold the verification result of the Csm */
  Crypto_VerifyResultType                  CsmVerificationResult;
[!IF "node:value(SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) = 'EB_CUSTOM'"!][!//
  /* The return value of the MAC verification or get freshness procedure */
  Std_ReturnType                           CsmVerificationReturn;
[!ENDIF!][!//
  /* Flag which indicates if the buffers corresponding to a Pdu are currently in use */
  boolean                                  PduInProcess;
  /* Flag which indicates if the verification of the Secured I-PDU is currently ongoing */
  boolean                                  ProcessingVerification;
  /* Flag which indicates if the SecOC_RxRenewVerifyStatusOverride was already called */
  boolean                                  RenewedVerStatus;
}
SecOC_RxDataType;
[!ENDIF!][!//

[!IF "$TxPduNum > 0"!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
[!IF "($UseGetTxFreshnessTruncData = 'true')"!][!//
/**
 * \brief Pointer to the external GetTxFreshnessTruncData function.
 */
typedef P2FUNC(Std_ReturnType, SECOC_CODE, GetTxFreshnessTruncDataType)
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
);
[!ENDIF!][!//

[!IF "($UseGetTxFreshness = 'true')"!][!//
/**
 * \brief Pointer to the external GetTxFreshness function.
 */
typedef P2FUNC(Std_ReturnType, SECOC_CODE, GetTxFreshnessType)
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);
[!ENDIF!][!//

/**
 * \brief Pointer to the external TxPduConfirmation function.
 */
typedef P2FUNC(void, SECOC_CODE, SPduTxConfirmationType)
(
  uint16 SecOCFreshnessValueID
);
[!ENDIF!][!//

/**
 * \struct SecOC_TxConfigType
 * \brief SecOC Configuration type for Tx Pdus, which shall be authenticated by the SecOC module.
 */
typedef struct
{
[!IF "$TxUseConfirmationTimeout = 'true'"!][!//
  /* Timeout for TxConfirmation threshold */
  uint32                            ConfirmationTimeoutThreshold;
[!ENDIF!][!//
  /* Csm Job ID */
  uint32                            CsmJobId;
[!IF "('true' = node:value(SecOCEbGeneral/SecOCRteUsage)) and (num:i(count(SecOCMainFunctionTx/*)) > 0)"!][!//
  uint32                            MainFunctionIndex;
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
[!IF "$UseGetTxFreshnessTruncData = 'true'"!][!//
  /* Pointer to the GetTxFreshnessTruncData function */
  GetTxFreshnessTruncDataType       GetTxFreshnessTruncData;
[!ENDIF!][!//
[!IF "$UseGetTxFreshness = 'true'"!][!//
  /* Pointer to the GetTxFreshness function */
  GetTxFreshnessType                GetTxFreshness;
[!ENDIF!][!//
  /* Pointer to the SPduTxConfirmation function */
  SPduTxConfirmationType            SPduTxConfirmation;
[!ENDIF!][!//
  /* ID of the secured Pdu at SecOC (used for e.g. SecOC_TxConfirmation) */
  uint16                            PduIdForSecuredPduAtSecOC;
[!IF "$TxUseSecuredCollection = 'true'"!][!//
  /* ID of the authentic Pdu at SecOC (used for e.g. SecOC_TxConfirmation) */
  uint16                            PduIdForSentAuthPduAtSecOC;
  /* ID of the cryptographic Pdu at SecOC (used for e.g. SecOC_TxConfirmation) */
  uint16                            PduIdForCryptoPduAtSecOC;
[!ENDIF!][!//
[!IF "$TxUseMessageLink = 'true'"!][!//
  /* Length of message link in the Pdu */
  uint16                            MessageLinkLength;
  /* Position of message linker inside the authentic I-PDU */
  uint16                            MessageLinkPos;
[!ENDIF!][!//
  /* Number of maximal allowed authentication attempts */
  uint16                            MaxAuthAttempts;
[!IF "$TxUseMacStatusPropagate = 'true'"!][!//
  /* Defines how the MAC Generate status shall be propagated */
  uint8                             MacGenerateStatusPropagationMode;
[!ENDIF!][!//
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE'"!][!//
  /* Defines which freshness function should be called */
  uint8                             GetTxFreshnessFuncType;
[!ENDIF!][!//
  /* Defines which Csm function should be called */
  uint8                             CsmFuncType;
[!IF "$TxUseSecuredHeader = 'true'"!][!//
  /* Length of the secured PDU header which reprensents the payload length inside the secured PDU or lower layer authentic PDU */
  uint8                             SecuredPduHeaderLength;
[!ENDIF!][!//
[!IF "$TxUseSecuredCollection = 'true'"!][!//
  /* Flag which indicates whether the secured PDU collection is used or not */
  boolean                           UseSecPduCollection;
[!ENDIF!][!//
[!IF "'true' = node:exists(SecOCEbGeneral/SecOCTxShapeFuncName)"!][!//
  /* Flag which indicates whether the functionality to shape the secured PDU is used or not */
  boolean                           UseShapeSecuredPdu;
[!ENDIF!][!//
[!IF "$TxUseCsmAsync = 'true'"!][!//
  /* Flag which indicates whether the Csm service is used in asynchronous mode or not */
  boolean                           UseCsmAsync;
[!ENDIF!][!//
  /* Flag which indicates whether the TP interfaces (in the communication with PduR) will be used or not */
  boolean                           UseTp;
[!IF "$TxUseSyncPduProcessing = 'true'"!][!//
  /* Flag indicating whether synchronous processing will be used or not */
  boolean                           UseSyncProcessing;
[!ENDIF!][!//
  /* Flag indicating if the dynamic length of the PDU is accepted or not */
  boolean                           UseDynamicLength;
[!IF "'true' = $TxUseSPduConfirmation"!][!//
  /* Flag indicating if the SecOC_SPduTxConfirmation of the PDU shall be called or not */
  boolean                           UseTxConfirmation;
[!ENDIF!][!//
}
SecOC_TxConfigType;

/**
 * \struct SecOC_TxDataType
 * \brief Structure holding the Datas of a Tx Pdu
 */
typedef struct
{
[!IF "$UseCsmJobRefCallout = 'true'"!][!//
  /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00031,1 */
  /* The Csm Job ID that shall be used (if SecOCCsmJobRefCallout enabled) */
  uint32                                   CsmJobIdPostDefined;
[!ENDIF!][!//
[!IF "$TxUseConfirmationTimeout = 'true'"!][!//
  /* Timeout counter for TxConfirmation */
  uint32                                   ConfirmationTimeoutCounter;
[!ENDIF!][!//
  /* Variable passed to the authentication algorithm, where the length result is stored */
  uint32                                   AuthenticatorLength;
[!IF "$TxUseSameBufferPdu = 'true'"!][!//
  /* Flag which indicates if the buffer is available or used */
  CONSTP2VAR(uint8, TYPEDEF, SECOC_VAR)    BufferUsed;
[!ENDIF!][!//
  /* Holds the length and the pointer to buffer holding the received authentic Pdu */
  PduInfoType                              ReceivedAuthPdu;
  /* Holds the length and the pointer to buffer holding the secured Pdu */
  PduInfoType                              SecuredPdu;
[!IF "$TxUseSecuredCollection = 'true'"!][!//
  /* Holds the length and the pointer to buffer holding the sent authentic Pdu */
  PduInfoType                              SentAuthPdu;
  /* Holds the length and the pointer to buffer holding the cryptographic Pdu */
  PduInfoType                              CryptoPdu;
[!ENDIF!][!//
  /* Pointer to buffer holding the data to authenticator (used for eg. MAC services) */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         DataToAuthenticator;
  /* Pointer to buffer holding the authenticator (eg. MAC) */
  P2VAR(uint8, TYPEDEF, SECOC_VAR)         Authenticator;
  /* The length of the payload within the secured PDU (authentic data) */
  PduLengthType                            DataLength;
  /* Copied data from the secured PDU length (copied via SecOC_CopyTxData) */
  PduLengthType                            CopiedDataFromSecLength;
[!IF "$TxUseSecuredCollection = 'true'"!][!//
  /* Copied data from the sent authentic PDU length (copied via SecOC_CopyTxData) */
  PduLengthType                            CopiedDataFromAuthLength;
  /* Copied data from the cryptographic PDU length (copied via SecOC_CopyTxData) */
  PduLengthType                            CopiedDataFromCryptoLength;
[!ENDIF!][!//
  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00225,1 */
  /* Number of authentication (build) attempts */
  uint16                                   AuthAttempts;
  /* The index of the SecOC Tx state machine for each PDU configured */
  uint8                                    State;
  /* Tx state machine events emitted by APIs to the PduR */
  uint8                                    PduREvent;
[!IF "$TxUseSecuredCollection = 'true'"!][!//
  /* Tx state machine events emitted by APIs to the PduR */
  uint8                                    PduRConfirmationForAuth;
  /* Tx state machine events emitted by APIs to the PduR */
  uint8                                    PduRConfirmationForCrypto;
[!ENDIF!][!//
  /* Tx state machine events emitted by SecOC_Transmit */
  uint8                                    TransmitEvent;
[!IF "$TxUseCsmAsync = 'true'"!][!//
 /* Tx state machine events emitted by APIs to the authenticator */
  uint8                                    CsmEvent;
[!ENDIF!][!//
[!IF "'true' = node:exists(SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!][!//
  /* Flag which indicates if the default authentication pattern is enabled, disabled or in use for the current transmission */
  uint8                                    DefaultAuthInfoPatternState;
[!ENDIF!][!//
[!IF "$TxUseMacStatusPropagate = 'true'"!][!//
  /* Status of the MAC Generate procedure */
  Std_ReturnType                           MacGenerateResult;
[!ENDIF!][!//
  /* Flag which indicates if the authentication of the I-PDU is currently ongoing */
  boolean                                  ProcessingAuthentication;
}
SecOC_TxDataType;

#ifndef RTE_TYPE_SecOC_MacGenerateStatusType
/** \cond SECOC_DOC_INTERNAL_MACROS */
#define RTE_TYPE_SecOC_MacGenerateStatusType
/** \endcond */
/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00014,2 */
/**
 * \struct SecOC_MacGenerateStatusType
 * \brief Data structure to bundle the status of a MAC generate attempt for a specific Freshness
 *        Value and Data ID.
 *//**
 * \var SecOC_MacGenerateStatusType::freshnessValueID
 * \brief Identifier of the Freshness Value which resulted in the Verification Result
 *//**
 * \var SecOC_MacGenerateStatusType::macGenerateStatus
 * \brief Result of the MAC Generate procedure.
 *//**
 * \var SecOC_MacGenerateStatusType::secOCDataId
 * \brief Identifier for the Secured I-PDU.
 */
typedef struct
{
  uint16                 freshnessValueID;
  Std_ReturnType         macGenerateStatus;
  SecOC_DataIdLengthType secOCDataId;
}
SecOC_MacGenerateStatusType;
#endif

[!IF "(count(SecOCGeneral/SecOCMacGenerateStatusCallout/*) > 0) and ($TxUseMacStatusPropagate = 'true')"!][!//
/**
 * \brief Pointer to MAC Generate status callout function type
 */
typedef P2FUNC(void, TYPEDEF, SecOC_MacGenerateStatusCalloutType) (SecOC_MacGenerateStatusType macGenerateStatus);

[!ENDIF!][!//
[!ENDIF!][!//
[!//

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/
[!ENDSELECT!][!//
#endif /* #ifndef SECOC_TYPES_H */

/*==================[end of file]=================================================================*/

