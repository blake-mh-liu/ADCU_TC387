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

#ifndef SECOC_TX_[!"text:toupper($partition.name)"!]_H
#define SECOC_TX_[!"text:toupper($partition.name)"!]_H

[!SELECT "as:modconf('SecOC')"!][!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Rte_SecOC_[!"$partition.name"!]_Type.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

[!LOOP "node:order(SecOCMainFunctionTx/*[node:name(node:ref(./SecOCMainFunctionTxPartitionRef)) = $partition.name])"!][!//
[!VAR "mainFuncName" = "node:name(.)"!][!//
[!IF "node:value(../../SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'false']) > 0"!][!//
/** \brief  This function is used by SecOC to obtain the current freshness used
 **         for the authentication procedure of Tx PDUs which are processed under
 **         the SecOC_MainFunctionTx_[!"$mainFuncName"!] main function.
 **
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
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_[!"$mainFuncName"!]_Freshness
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!ENDIF!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCProvideTxTruncatedFreshnessValue) = 'true']) > 0"!][!//
/** \brief  This function is used by SecOC to obtain the current freshness used
 **         for the authentication procedure of Tx PDUs which are processed under
 **         the SecOC_MainFunctionTx_[!"$mainFuncName"!] main function.
 **         It provides also the truncated freshness which shall be transmitted in the secured PDU.
 **
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
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Get_[!"$mainFuncName"!]_Freshness_TruncData
(
        uint16                              SecOCFreshnessValueID,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
  P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
);

[!ENDIF!][!//
[!IF "((num:i(count(SecOCTxPduProcessing/*[node:exists(SecOCUseTxConfirmation) = 'true' and node:value(SecOCUseTxConfirmation) = 'true'])) > 0) and node:value(SecOCGeneral/SecOCQueryFreshnessValue) != 'NONE')"!]
/** \brief  This function is used by SecOC to indicate that the transmition of the secured PDU
 **         was initiated. It shall be used only for the Tx PDUs which are processed under
 **         the SecOC_MainFunctionTx_[!"$mainFuncName"!] main function.
 **
 ** \param[in]  SecOCFreshnessValueID  Holds the identifier of the freshness.
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant for different freshenss ID}
 **/
extern FUNC(void, SECOC_CODE) SecOC_Tx_[!"$mainFuncName"!]_SPDU_Confirmation
(
  uint16 SecOCFreshnessValueID
);
[!ENDIF!][!//

[!ENDIF!][!//
[!IF "count(../../SecOCTxPduProcessing/*[node:name(node:ref(./SecOCTxPduMainFunctionRef)) = $mainFuncName and node:value(SecOCMacGenerateStatusPropagationMode) != 'NONE']) > 0"!][!//
/** \brief This function is used to report the status of the MAC Generate service.
 **        It shall be used only for the Tx PDUs which are processed under
 **        the SecOC_MainFunctionTx_[!"$mainFuncName"!] main function.
 **
 ** \param[in]  SecOC_TxMacGenerateStatus  Holds the pointer to the memory location where the
 **                                        the status of the MAC Generate service is stored.
 **
 **/
extern FUNC(void, SECOC_CODE) SecOC_Tx_Write_[!"$mainFuncName"!]_MacGenerateStatus
(
  P2VAR(SecOC_MacGenerateStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_TxMacGenerateStatus
);

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef SECOC_TX_[!"text:toupper($partition.name)"!]_H */

/*==================[end of file]=================================================================*/
