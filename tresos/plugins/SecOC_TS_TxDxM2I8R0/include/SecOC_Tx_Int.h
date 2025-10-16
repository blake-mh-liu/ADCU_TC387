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

#ifndef SECOC_TX_INT_H
#define SECOC_TX_INT_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <SecOC.h>

#if (SECOC_NUMBER_TX_PDUS > 0)

#include <SecOC_Tx.h>

#include <TSMem.h>
#include <SchM_SecOC.h>
#include <PduR_SecOC.h>

#if (STD_ON == SECOC_PBCFGM_SUPPORT_ENABLED)
#include <PbcfgM.h>
#endif /* #if (STD_ON == SECOC_PBCFGM_SUPPORT_ENABLED) */

#if (STD_ON == SECOC_USE_META_DATA)
#include <EcuC.h>
#endif /* #if (STD_ON == SECOC_USE_META_DATA) */

#if (defined TS_RELOCATABLE_CFG_ENABLE)
#error TS_RELOCATABLE_CFG_ENABLE already defined!
#endif /* #if (defined TS_RELOCATABLE_CFG_ENABLE) */
#define TS_RELOCATABLE_CFG_ENABLE SECOC_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig_Access.h>
#include <TSPBConfig_Signature.h>

/*==================[macros]======================================================================*/

/* Relocatable post build elements access macros. */
#if (defined SECOC_TX_PBCFG_ACCESS)
#error SECOC_TX_PBCFG_ACCESS already defined
#endif /* #if (defined SECOC_TX_PBCFG_ACCESS) */
#define SECOC_TX_PBCFG_ACCESS(type, element)   \
    (TS_UNCHECKEDGETCFG(SecOC_ConfigPtr, type, SECOC, SecOC_ConfigPtr->element))

#if (defined SECOC_GET_TXPDU_CFG)
#error SECOC_GET_TXPDU_CFG already defined
#endif /* #if (defined SECOC_GET_TXPDU_CFG) */
#define SECOC_GET_TXPDU_CFG(Index)   \
    (SECOC_TX_PBCFG_ACCESS(SecOC_TxPduConfigType, TxPduConfigPtr)[(Index)])

#if (defined SECOC_GET_TX_DATA_ID)
#error SECOC_GET_TX_DATA_ID already defined
#endif /* #if (defined SECOC_GET_TX_DATA_ID) */
#define SECOC_GET_TX_DATA_ID(Index) (SECOC_GET_TXPDU_CFG(Index).DataId)

#if (defined SECOC_GET_TX_SEC_PDU_ID_AT_PDUR)
#error SECOC_GET_TX_SEC_PDU_ID_AT_PDUR already defined
#endif /* #if (defined SECOC_GET_TX_SEC_PDU_ID_AT_PDUR) */
#define SECOC_GET_TX_SEC_PDU_ID_AT_PDUR(Index)  \
    (SECOC_GET_TXPDU_CFG(Index).SecuredLayerPduIdAtPduR)

#if (STD_ON == SECOC_TX_USE_SECURED_PDU_COL)
#if (defined SECOC_GET_TX_SENT_AUTH_PDU_ID_AT_PDUR)
#error SECOC_GET_TX_SENT_AUTH_PDU_ID_AT_PDUR already defined
#endif /* #if (defined SECOC_GET_TX_SENT_AUTH_PDU_ID_AT_PDUR) */
#define SECOC_GET_TX_SENT_AUTH_PDU_ID_AT_PDUR(Index)   \
    (SECOC_GET_TXPDU_CFG(Index).SentAuthLayerPduIdAtPduR)

#if (defined SECOC_GET_TX_CRYPTO_PDU_ID_AT_PDUR)
#error SECOC_GET_TX_CRYPTO_PDU_ID_AT_PDUR already defined
#endif /* #if (defined SECOC_GET_TX_CRYPTO_PDU_ID_AT_PDUR) */
#define SECOC_GET_TX_CRYPTO_PDU_ID_AT_PDUR(Index)   \
    (SECOC_GET_TXPDU_CFG(Index).CryptoLayerPduIdAtPduR)
#endif /* #if (STD_ON == SECOC_TX_USE_SECURED_PDU_COL) */

#if (defined SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR)
#error SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR already defined
#endif /* #if (defined SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR) */
#define SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(Index)  \
    (SECOC_GET_TXPDU_CFG(Index).ULAuthLayerPduIdAtPduR)

#if (STD_ON == SECOC_PDU_SECURED_AREA)
#if (defined SECOC_GET_TX_SECURED_AREA_LEN)
#error SECOC_GET_TX_SECURED_AREA_LEN already defined
#endif /* #if (defined SECOC_GET_TX_SECURED_AREA_LEN) */
#define SECOC_GET_TX_SECURED_AREA_LEN(Index) (SECOC_GET_TXPDU_CFG(Index).SecuredTxPduLength)

#if (defined SECOC_GET_TX_SECURED_AREA_OFFSET)
#error SECOC_GET_TX_SECURED_AREA_OFFSET already defined
#endif /* #if (defined SECOC_GET_TX_SECURED_AREA_OFFSET) */
#define SECOC_GET_TX_SECURED_AREA_OFFSET(Index) (SECOC_GET_TXPDU_CFG(Index).SecuredTxPduOffset)

#if (defined SECOC_GET_TX_USE_SECURED_AREA)
#error SECOC_GET_TX_USE_SECURED_AREA already defined
#endif /* #if (defined SECOC_GET_TX_USE_SECURED_AREA) */
#define SECOC_GET_TX_USE_SECURED_AREA(Index) (SECOC_GET_TXPDU_CFG(Index).UseTxSecuredArea)
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */

#if (defined SECOC_GET_TX_USE_REAUTHENTICATE)
#error SECOC_GET_TX_USE_REAUTHENTICATE already defined
#endif /* #if (defined SECOC_GET_TX_USE_REAUTHENTICATE) */
#define SECOC_GET_TX_USE_REAUTHENTICATE(Index) (SECOC_GET_TXPDU_CFG(Index).UseReAuthenticate)

#if (defined SECOC_GET_TX_FRESHNESS_ID)
#error SECOC_GET_TX_FRESHNESS_ID already defined
#endif /* #if (defined SECOC_GET_TX_FRESHNESS_ID) */
#define SECOC_GET_TX_FRESHNESS_ID(Index) (SECOC_GET_TXPDU_CFG(Index).FreshnessValueId)

#if (defined SECOC_GET_TX_FRESHNESS_LEN)
#error SECOC_GET_TX_FRESHNESS_LEN already defined
#endif /* #if (defined SECOC_GET_TX_FRESHNESS_LEN) */
#define SECOC_GET_TX_FRESHNESS_LEN(Index) (SECOC_GET_TXPDU_CFG(Index).FreshnessValueLength)

#if (defined SECOC_GET_TX_FRESHNESSTX_LEN)
#error SECOC_GET_TX_FRESHNESSTX_LEN already defined
#endif /* #if (defined SECOC_GET_TX_FRESHNESSTX_LEN) */
#define SECOC_GET_TX_FRESHNESSTX_LEN(Index) (SECOC_GET_TXPDU_CFG(Index).FreshnessValueTxLength)

#if (defined SECOC_GET_TX_AUTHINFOTX_LEN)
#error SECOC_GET_TX_AUTHINFOTX_LEN already defined
#endif /* #if (defined SECOC_GET_TX_AUTHINFOTX_LEN) */
#define SECOC_GET_TX_AUTHINFOTX_LEN(Index) (SECOC_GET_TXPDU_CFG(Index).AuthInfoTxLength)

#if (defined SECOC_GET_TX_SECURED_PDU_ADR)
#error SECOC_GET_TX_SECURED_PDU_ADR already defined
#endif /* #if (defined SECOC_GET_TX_SECURED_PDU_ADR) */
#define SECOC_GET_TX_SECURED_PDU_ADR(Index)    \
    (&SecOC_PB_PduBuffer[SECOC_GET_TXPDU_CFG(Index).BuffersConfig.SecuredPduBufferIndex])

#if (defined SECOC_GET_TX_ULAUTH_PDU_ADR)
#error SECOC_GET_TX_ULAUTH_PDU_ADR already defined
#endif /* #if (defined SECOC_GET_TX_ULAUTH_PDU_ADR) */
#define SECOC_GET_TX_ULAUTH_PDU_ADR(Index)   \
    (&SecOC_PB_PduBuffer[SECOC_GET_TXPDU_CFG(Index).BuffersConfig.ULAuthPduBufferIndex])

#if (defined SECOC_GET_TX_SECURED_PDU_LEN)
#error SECOC_GET_TX_SECURED_PDU_LEN already defined
#endif /* #if (defined SECOC_GET_TX_SECURED_PDU_LEN) */
#define SECOC_GET_TX_SECURED_PDU_LEN(Index)    \
    (SECOC_GET_TXPDU_CFG(Index).BuffersConfig.SecuredPduBufferLength)

#if (defined SECOC_GET_TX_AUTH_PDU_LEN)
#error SECOC_GET_TX_AUTH_PDU_LEN already defined
#endif /* #if (defined SECOC_GET_TX_AUTH_PDU_LEN) */
#define SECOC_GET_TX_AUTH_PDU_LEN(Index)       \
    (SECOC_GET_TXPDU_CFG(Index).BuffersConfig.AuthPduBufferLength)

#if (STD_ON == SECOC_TX_USE_SECURED_PDU_COL)
#if (defined SECOC_GET_TX_CRYPTO_PDU_LEN)
#error SECOC_GET_TX_CRYPTO_PDU_LEN already defined
#endif /* #if (defined SECOC_GET_TX_CRYPTO_PDU_LEN) */
#define SECOC_GET_TX_CRYPTO_PDU_LEN(Index)     \
    (SECOC_GET_TXPDU_CFG(Index).BuffersConfig.CryptoPduBufferLength)
#endif /* #if (STD_ON == SECOC_TX_USE_SECURED_PDU_COL) */

#if (defined SECOC_GET_TX_AUTHENTICATOR_ADR)
#error SECOC_GET_TX_AUTHENTICATOR_ADR already defined
#endif /* #if (defined SECOC_GET_TX_AUTHENTICATOR_ADR) */
#define SECOC_GET_TX_AUTHENTICATOR_ADR(Index)  \
    (&SecOC_PB_IntBuffer[SECOC_GET_TXPDU_CFG(Index).BuffersConfig.AuthenticatorIndex])

#if (defined SECOC_GET_TX_DATATOAUTH_ADR)
#error SECOC_GET_TX_DATATOAUTH_ADR already defined
#endif /* #if (defined SECOC_GET_TX_DATATOAUTH_ADR) */
#define SECOC_GET_TX_DATATOAUTH_ADR(Index)    \
    (&SecOC_PB_IntBuffer[SECOC_GET_TXPDU_CFG(Index).BuffersConfig.DataToAuthenticatorIndex])

/** \brief Macro, which defines what Tx internal data shall be used when calling the Csm service
 */
#if (defined SECOC_TX_CSM_JOB_ID)
#error SECOC_TX_CSM_JOB_ID already defined
#endif /* #if (defined SECOC_TX_CSM_JOB_ID) */
#if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON)
#define SECOC_TX_CSM_JOB_ID(Id)                  SecOC_TxData[(Id)].CsmJobIdPostDefined
#else /* #if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON) */
#define SECOC_TX_CSM_JOB_ID(Id)                  SecOC_TxConfig[(Id)].CsmJobId
#endif /* #if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON) */

/** \brief Macro, which defines what value shall be used when looking up Tx Pdus associated to the callback
 */
#if (defined SECOC_TX_CBK_ID)
#error SECOC_TX_CBK_ID already defined
#endif /* #if (defined SECOC_TX_CBK_ID) */
#define SECOC_TX_CBK_ID(Id)                      SecOC_TxCbkIdx[(Id)]

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)

/** \brief Macro used when some buffer is not used
 */
#if (defined SECOC_BUFFER_FREE)
#error SECOC_BUFFER_FREE already defined
#endif /* #if (defined SECOC_BUFFER_FREE) */
#define SECOC_BUFFER_FREE           0x00U

/** \brief Macro used when some buffer is currently being used
 */
#if (defined SECOC_BUFFER_USED)
#error SECOC_BUFFER_USED already defined
#endif /* #if (defined SECOC_BUFFER_USED) */
#define SECOC_BUFFER_USED           0x01U

/** \brief Macro used to set the status of the Tx buffer used to store the upper layer authentic PDU
 */
#if (defined SECOC_TX_SET_BUFFER_LVL1_STATUS)
#error SECOC_TX_SET_BUFFER_LVL1_STATUS already defined
#endif /* #if (defined SECOC_TX_SET_BUFFER_LVL1_STATUS) */
#define SECOC_TX_SET_BUFFER_LVL1_STATUS(Id, Value)  \
  do \
  { \
    if (SecOC_TxData[Id].BufferUsed != NULL_PTR) \
    { \
      if (Value == SECOC_BUFFER_FREE) \
      { \
        *SecOC_TxData[Id].BufferUsed &= ~(1U); \
      } \
      else\
      { \
        *SecOC_TxData[Id].BufferUsed |= 1U; \
      } \
    } \
  } while (0U)

/** \brief Macro used to set the status of the Tx buffer used to store the secured PDU
 */
#if (defined SECOC_TX_SET_BUFFER_LVL2_STATUS)
#error SECOC_TX_SET_BUFFER_LVL2_STATUS already defined
#endif /* #if (defined SECOC_TX_SET_BUFFER_LVL2_STATUS) */
#define SECOC_TX_SET_BUFFER_LVL2_STATUS(Id, Value)  \
  do \
  { \
    if (SecOC_TxData[Id].BufferUsed != NULL_PTR) \
    { \
      if (Value == SECOC_BUFFER_FREE) \
      { \
        *SecOC_TxData[Id].BufferUsed &= ~(1U << 1U); \
      } \
      else\
      { \
        *SecOC_TxData[Id].BufferUsed |= (1U << 1U); \
      } \
    } \
  } while (0U)

/** \brief Macro used to get the status of the Tx buffer used to store the upper layer authentic PDU
 */
#if (defined SECOC_TX_GET_BUFFER_LVL1_STATUS)
#error SECOC_TX_GET_BUFFER_LVL1_STATUS already defined
#endif /* #if (defined SECOC_TX_GET_BUFFER_LVL1_STATUS) */
#define SECOC_TX_GET_BUFFER_LVL1_STATUS(Id, Value)  \
  do\
  { \
    if (SecOC_TxData[Id].BufferUsed != NULL_PTR) \
    { \
      Value = *SecOC_TxData[Id].BufferUsed & 1U; \
    } \
    else \
    { \
      Value = SECOC_BUFFER_FREE; \
    } \
  } while (0U)

/** \brief Macro used to get the status of the Tx buffer used to store the secured PDU
 */
#if (defined SECOC_TX_GET_BUFFER_LVL2_STATUS)
#error SECOC_TX_GET_BUFFER_LVL2_STATUS already defined
#endif /* #if (defined SECOC_TX_GET_BUFFER_LVL2_STATUS) */
#define SECOC_TX_GET_BUFFER_LVL2_STATUS(Id, Value)  \
  do\
  { \
    if (SecOC_TxData[Id].BufferUsed != NULL_PTR) \
    { \
      Value = (*SecOC_TxData[Id].BufferUsed >> 1U) & 1U; \
    } \
    else \
    { \
      Value = SECOC_BUFFER_FREE; \
    } \
  } while (0U)

#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */

#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)

/** \brief Macro used to indicate that the default authentication information pattern is disabled
 */
#if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED)
#error SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED already defined
#endif /* #if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED) */
#define SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED      0U

/** \brief Macro used to indicate that the default authentication information pattern is enabled
 */
#if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED)
#error SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED already defined
#endif /* #if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED) */
#define SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED       1U

/** \brief Macro used to indicate that the default authentication information pattern is currently in use
 */
#if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE)
#error SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE already defined
#endif /* #if (defined SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE) */
#define SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE           2U

#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/** \brief Array holding the configuration of each configured TxPduProcessing
 */
extern CONST(SecOC_TxConfigType, SECOC_CONST) SecOC_TxConfig[SECOC_NUMBER_TX_PDUS];

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

#if (SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP > 0)
#if (SECOC_MACGENERATE_STATUS_PROP_ENABLED == STD_ON)
#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/**
 * \brief Variable which holds the configured callout functions for propagating the MAC Generate status
 */
extern CONST(SecOC_MacGenerateStatusCalloutType, SECOC_VAR) SecOC_TxMacGenerateStatusCallout[SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP];

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>
#endif /* #if (SECOC_MACGENERATE_STATUS_PROP_ENABLED == STD_ON) */
#endif /* #if (SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP > 0) */

/*==================[external data]===============================================================*/

#define SECOC_START_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>

/** \brief Data structure holding the Data for Tx Pdus, which shall be authenticated.
 */
extern VAR(SecOC_TxDataType, SECOC_VAR) SecOC_TxData[SECOC_NUMBER_TX_PDUS];

#define SECOC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <SecOC_MemMap.h>

#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)

#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

/**
 * \brief Flag which indicates the bypass mechanism state (enabled or disabled)
 */
extern VAR(uint8, SECOC_VAR) SecOC_TxBypassAuthRoutineState;

#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */

/*==================[external function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_SendDefaultAuthenticationInformation
(
    P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) txInstIdxList,
            uint16                               numberOfTxPdus,
            uint16                               FreshnessValueID,
            boolean                              sendDefaultAuthenticationInformation
);
#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#undef TS_RELOCATABLE_CFG_ENABLE

/*================================================================================================*/

#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
#endif /* #ifndef SECOC_TX_INT_H */

/*==================[end of file]=================================================================*/

