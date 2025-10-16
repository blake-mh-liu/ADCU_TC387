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

#ifndef SECOC_RX_[!"text:toupper($partition.name)"!]_H
#define SECOC_RX_[!"text:toupper($partition.name)"!]_H

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

[!LOOP "node:order(SecOCMainFunctionRx/*[node:name(node:ref(./SecOCMainFunctionRxPartitionRef)) = $partition.name])"!][!//
[!VAR "mainFuncName" = "node:name(.)"!][!//
[!IF "node:value(../../SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
[!IF "count(../../SecOCRxPduProcessing/*[node:name(node:ref(./SecOCRxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCUseAuthDataFreshness) = 'false']) > 0"!][!//
/** \brief  This function is used by SecOC to provide the freshenss from the received secured PDU
 **         and to obtain the current freshness which shall be used for the verification procedure
 **         of Rx PDUs which are processed the SecOC_MainFunctionRx_[!"$mainFuncName"!] main function.
 **
 ** \param[in]   SecOCFreshnessValueID               Holds the identifier of the freshness.
 ** \param[out]  SecOCTruncatedFreshnessValue        Holds the pointer to the memory location where
 **                                                  the freshenss from the received secured PDU
 **                                                  shall be stored.
 ** \param[in]   SecOCTruncatedFreshnessValueLength  Holds the pointer to the memory location where
 **                                                  the length in bits of the freshness from the
 **                                                  secured PDU is stored.
 ** \param[in]   SecOCAuthVerifyAttempts             Holds the number of authentication verify
 **                                                  attempts of this PDU since the last reception.
 **                                                  The value is 0 for the first attempt and
 **                                                  incremented on every unsuccessful verification
 **                                                  attempt.
 ** \param[out]  SecOCFreshnessValue                 Holds the pointer to the memory location where
 **                                                  the freshenss used to authentication shall be
 **                                                  stored.
 ** \param[in]   SecOCFreshnessValueLength           Holds a pointer to the memory location in which
 **                                                  the length in bits of the required freshness
 **                                                  for authentication is stored.
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
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_[!"$mainFuncName"!]_Freshness
(
          uint16                              SecOCFreshnessValueID,
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue,
          uint32                              SecOCTruncatedFreshnessValueLength,
          uint16                              SecOCAuthVerifyAttempts,
    P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
);

[!ENDIF!][!//
[!IF "count(../../SecOCRxPduProcessing/*[node:name(node:ref(./SecOCRxPduMainFunctionRef)) = $mainFuncName and node:value(./SecOCUseAuthDataFreshness) = 'true']) > 0"!][!//
/** \brief  This function is used by SecOC to provide the freshenss from the received secured PDU
 **         and to obtain the current freshness which shall be used for the verification procedure
 **         of Rx PDUs which are processed the SecOC_MainFunctionRx_[!"$mainFuncName"!] main function.
 **         It provides also a part of the payload via SecOCAuthDataFreshnessValue.
 **
 ** \param[in]   SecOCFreshnessValueID               Holds the identifier of the freshness.
 ** \param[out]  SecOCTruncatedFreshnessValue        Holds the pointer to the memory location where
 **                                                  the freshenss from the received secured PDU
 **                                                  shall be stored.
 ** \param[in]   SecOCTruncatedFreshnessValueLength  Holds the pointer to the memory location where
 **                                                  the length in bits of the freshness from the
 **                                                  secured PDU is stored.
 ** \param[in]   SecOCAuthDataFreshnessValue         Holds the pointer to the memory location where
 **                                                  a part of the payload from the received
 **                                                  secured PDU, not yet authenticated is stored.
 ** \param[in]   SecOCAuthDataFreshnessValueLength   Holds the pointer to the memory location where
 **                                                  the length in bits of the provided data is stored.
 ** \param[in]   SecOCAuthVerifyAttempts             Holds the number of authentication verify
 **                                                  attempts of this PDU since the last reception.
 **                                                  The value is 0 for the first attempt and
 **                                                  incremented on every unsuccessful verification
 **                                                  attempt.
 ** \param[out]  SecOCFreshnessValue                 Holds the pointer to the memory location where
 **                                                  the freshenss used to authentication shall be
 **                                                  stored.
 ** \param[in]   SecOCFreshnessValueLength           Holds a pointer to the memory location in which
 **                                                  the length in bits of the required freshness
 **                                                  for authentication is stored.
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
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_Get_[!"$mainFuncName"!]_Freshness_AuthData
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
[!ENDIF!][!//
[!IF "node:value(../../SecOCEbGeneral/SecOCEbPropagateVerificationStatusApiVersion) != 'NONE'"!][!//
/** \brief This function is used to report the status of the MAC Verification service via
 **        a sender receiver interface type.
 **        It shall be used only for the Rx PDUs which are processed under
 **        the SecOC_MainFunctionRx_[!"$mainFuncName"!] main function.
 **
 ** \param[in]  SecOC_RxVerificationStatus  Holds the pointer to the memory location where the
 **                                         the status of the MAC Verification service is stored.
 **/
extern FUNC(void, SECOC_CODE) SecOC_Rx_Write_[!"$mainFuncName"!]_VerificationStatus
(
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
);

[!ENDIF!][!//
[!IF "node:value(../../SecOCEbGeneral/SecOCEbClientServerPropagateVerificationStatusApiVersion) != 'NONE'"!][!//
/** \brief This function is used to report the status of the MAC Verification service via
 **        a client server interface type.
 **        It shall be used only for the Rx PDUs which are processed under
 **        the SecOC_MainFunctionRx_[!"$mainFuncName"!] main function.
 **
 ** \param[in]  SecOC_RxVerificationStatus  Holds the pointer to the memory location where the
 **                                         the status of the MAC Verification service is stored.
 **/
extern FUNC(void, SECOC_CODE) SecOC_Rx_Call_[!"$mainFuncName"!]_VerificationStatusIndication
(
  P2VAR(SecOC_VerificationStatusType, AUTOMATIC, SECOC_APPL_DATA) SecOC_RxVerificationStatus
);

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef SECOC_RX_[!"text:toupper($partition.name)"!]_H */

/*==================[end of file]=================================================================*/
