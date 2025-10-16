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

#include <SecOC_Tx_Int.h>
#include <SecOC_Tx_[!"$partition.name"!].h>
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

[!LOOP "node:order(SecOCMainFunctionTx/*[node:name(node:ref(./SecOCMainFunctionTxPartitionRef)) = $partition.name])"!][!//
[!VAR "mainFuncName" = "node:name(.)"!][!//
[!IF "node:value(../../SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'false']) > 0"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_[!"$mainFuncName"!]_Freshness
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
)
{
  Std_ReturnType  retVal = E_NOT_OK;

  retVal = Rte_Call_PS_TxFreshnessManagement_[!"$mainFuncName"!]_GetTxFreshness(
                                                           SecOCFreshnessValueID,
                                                           SecOCFreshnessValue,
                                                           SecOCFreshnessValueLength
                                                         );

  return retVal;
}

[!ENDIF!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'true']) > 0"!][!//
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_[!"$mainFuncName"!]_Freshness_TruncData
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
)
{
  Std_ReturnType  retVal = E_NOT_OK;

  retVal = Rte_Call_PS_TxFreshnessManagement_[!"$mainFuncName"!]_GetTxFreshnessTruncData(
                                                           SecOCFreshnessValueID,
                                                           SecOCFreshnessValue,
                                                           SecOCFreshnessValueLength,
                                                           SecOCTruncatedFreshnessValue,
                                                           SecOCTruncatedFreshnessValueLength
                                                         );

  return retVal;
}

[!ENDIF!][!//
[!IF "((num:i(count(SecOCTxPduProcessing/*[node:exists(SecOCUseTxConfirmation) = 'true' and node:value(SecOCUseTxConfirmation) = 'true'])) > 0) and node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]
FUNC(void, SECOC_CODE) SecOC_Tx_[!"$mainFuncName"!]_SPDU_Confirmation
(
  uint16 SecOCFreshnessValueID
)
{
  (void)Rte_Call_PS_TxFreshnessManagement_[!"$mainFuncName"!]_SPduTxConfirmation(SecOCFreshnessValueID);
}
[!ENDIF!][!//

[!ENDIF!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName and node:value(SecOCMacGenerateStatusPropagationMode) != 'NONE']) > 0"!][!//
FUNC(void, SECOC_CODE) SecOC_Tx_Write_[!"$mainFuncName"!]_MacGenerateStatus
(
  P2VAR(SecOC_MacGenerateStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_TxMacGenerateStatus
)
{
  (void)Rte_Write_PS_MacGenerateStatus_[!"$mainFuncName"!]_macGenerateStatus(SecOC_TxMacGenerateStatus);
}

[!ENDIF!][!//

[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName]) > 0"!][!//]
[!IF "'true' = node:exists(../../SecOCGeneral/SecOCDefaultAuthenticationInformationPattern)"!]
FUNC(Std_ReturnType, SECOC_CODE) SecOC_SendDefaultAuthenticationInformation_[!"$mainFuncName"!]
(
  uint16 FreshnessValueID,
  boolean sendDefaultAuthenticationInformation
)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = SecOC_Tx_SendDefaultAuthenticationInformation
            (
              SecOC_TxInstIdxList_[!"$mainFuncName"!],
              SECOC_NUMBER_TX_PDUS_[!"text:toupper($mainFuncName)"!],
              FreshnessValueID,
              sendDefaultAuthenticationInformation
            );

  return retVal;
}
[!ENDIF!][!//
[!ENDIF!][!//

[!ENDLOOP!][!//
[!ENDSELECT!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
