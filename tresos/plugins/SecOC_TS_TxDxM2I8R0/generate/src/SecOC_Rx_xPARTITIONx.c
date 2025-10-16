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
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <SecOC_Rx_Int.h>
#include <SecOC_Rx_[!"$partition.name"!].h>
#include <Rte_SecOC_[!"$partition.name"!].h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

[!LOOP "node:order(SecOCMainFunctionRx/*[node:name(node:ref(./SecOCMainFunctionRxPartitionRef)) = $partition.name])"!][!//
[!VAR "mainFuncName" = "node:name(.)"!][!//
[!IF "node:value(../../SecOCEbGeneral/SecOCEbVerifyStatusOverrideApiVersion) = 'SECOC_API_VERSION_430'"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_VerifyStatusOverride_[!"$mainFuncName"!]
(
  uint16  freshnessValueId,
  uint8   overrideStatus,
  uint8   numberOfMessagesToOverride
)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = SecOC_Rx_VerifyStatusOverride_43
            (
              SecOC_RxInstIdxList_[!"$mainFuncName"!],
              SECOC_NUMBER_RX_PDUS_[!"text:toupper($mainFuncName)"!],
              freshnessValueId,
              overrideStatus,
              numberOfMessagesToOverride
            );

  return retVal;
}

[!ELSE!]
FUNC(Std_ReturnType, CSM_APPL_CODE) SecOC_VerifyStatusOverride_[!"$mainFuncName"!]
(
  uint16                   ValueId,
  SecOC_OverrideStatusType overrideStatus,
  uint8                    numberOfMessagesToOverride
)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = SecOC_Rx_VerifyStatusOverride_44
            (
              SecOC_RxInstIdxList_[!"$mainFuncName"!],
              SECOC_NUMBER_RX_PDUS_[!"text:toupper($mainFuncName)"!],
              ValueId,
              overrideStatus,
              numberOfMessagesToOverride
            );

  return retVal;
}

[!ENDIF!]

[!IF "node:value(../../SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "count(../../SecOCRxPduProcessing/*[node:name(node:ref(./SecOCRxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCUseAuthDataFreshness) = 'false']) > 0"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_[!"$mainFuncName"!]_Freshness
(
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
          uint16                              SecOCAuthVerifyAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
)
{
  Std_ReturnType  retVal = E_NOT_OK;

  retVal = Rte_Call_PS_RxFreshnessManagement_[!"$mainFuncName"!]_GetRxFreshness(
                                                  SecOCFreshnessValueID,
                                                  SecOCTruncatedFreshnessValue,
                                                  SecOCTruncatedFreshnessValueLength,
                                                  SecOCAuthVerifyAttempts,
                                                  SecOCFreshnessValue,
                                                  SecOCFreshnessValueLength
                                                );

  return retVal;
}

[!ENDIF!][!//
[!IF "count(../../SecOCRxPduProcessing/*[node:name(node:ref(./SecOCRxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCUseAuthDataFreshness) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_[!"$mainFuncName"!]_Freshness_AuthData
(
          uint16                              SecOCFreshnessValueID,
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

  retVal = Rte_Call_PS_RxFreshnessManagement_[!"$mainFuncName"!]_GetRxFreshnessAuthData(
                                                          SecOCFreshnessValueID,
                                                          SecOCTruncatedFreshnessValue,
                                                          SecOCTruncatedFreshnessValueLength,
                                                          SecOCAuthDataFreshnessValue,
                                                          SecOCAuthDataFreshnessValueLength,
                                                          SecOCAuthVerifyAttempts,
                                                          SecOCFreshnessValue,
                                                          SecOCFreshnessValueLength
                                                        );

  return retVal;
}

[!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:value(../../SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) != 'NONE'"!][!//
FUNC(void, SECOC_CODE) SecOC_Rx_Write_[!"$mainFuncName"!]_VerificationStatus
(
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
)
{
  (void)Rte_Write_PS_VerificationStatus_[!"$mainFuncName"!]_verificationStatus(SecOC_RxVerificationStatus);
}

[!ENDIF!][!//
[!IF "node:value(../../SecOCEbGeneral/SecOCEbClientServerPropagateVerificationStatusApiVersion) != 'NONE'"!][!//
FUNC(void, SECOC_CODE) SecOC_Rx_Call_[!"$mainFuncName"!]_VerificationStatusIndication
(
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
)
{
  (void)Rte_Call_PS_VerificationStatusIndication_[!"$mainFuncName"!]_VerifyStatus(SecOC_RxVerificationStatus);
}

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
