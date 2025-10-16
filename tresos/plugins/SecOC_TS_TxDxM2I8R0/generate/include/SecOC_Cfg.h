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

#ifndef SECOC_CFG_H
#define SECOC_CFG_H

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

[!// This file contains the verification of the PDU IDs uniqueness
[!INCLUDE "SecOC_Checks.m"!][!//
[!//
[!// This file contains macros for configuration values
[!INCLUDE "../../generate_macros/SecOC_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Rx_Macros.m"!][!//
[!INCLUDE "../../generate_macros/SecOC_Tx_Macros.m"!][!//
[!//

#include <SecOC_Types.h>
#include <SecOC_Rx_Cfg.h>
#include <SecOC_Tx_Cfg.h>

/*==================[macros]======================================================================*/

/* !LINKSTO SecOC.PB.Impl.Hash,1 */
#if (defined SECOC_CFG_SIGNATURE)
#error SECOC_CFG_SIGNATURE already defined
#endif
#define SECOC_CFG_SIGNATURE [!"asc:getConfigSignature(as:modconf('SecOC')[1]//*[not(child::*) and (node:configclass() = 'PreCompile') ])"!]U

#if (defined SECOC_PUBLIC_INFO_SIGNATURE)
#error SECOC_PUBLIC_INFO_SIGNATURE already defined
#endif
#define SECOC_PUBLIC_INFO_SIGNATURE [!"asc:getConfigSignature(node:difference(as:modconf('SecOC')[1]/CommonPublishedInformation//*[not(child::*) and (node:configclass() = 'PublishedInformation') ], as:modconf('SecOC')[1]/CommonPublishedInformation/Release))"!]U

/* !LINKSTO SecOC.PB.Impl.PbCfgM,1 */
#if (defined SECOC_PBCFGM_SUPPORT_ENABLED)
#error SECOC_PBCFGM_SUPPORT_ENABLED already defined
#endif
#define SECOC_PBCFGM_SUPPORT_ENABLED [!IF "node:contains(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/*/PbcfgMBswModuleRef), as:modconf('SecOC')) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ----- Pre-processor switch to enable/disable relocatable post build configuration ----- */

#if (defined SECOC_RELOCATABLE_CFG_ENABLE)
#error SECOC_RELOCATABLE_CFG_ENABLE already defined
#endif
#if (SECOC_PBCFGM_SUPPORT_ENABLED == STD_ON)
/* !LINKSTO SecOC.PB.Impl.PbcfgM.Relocatable,1 */
#define SECOC_RELOCATABLE_CFG_ENABLE [!IF "as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#else
/* !LINKSTO SecOC.PB.Impl.NoPbcfgM.Relocatable,1 */
#define SECOC_RELOCATABLE_CFG_ENABLE [!IF "as:modconf('SecOC')[1]/SecOCEbGeneral/SecOCRelocatablePbcfgEnable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#endif

/** \brief Flag to indicate if PduR_SecOCCancelTransmit is available
 */
#if (defined SECOC_PDUR_SECOCCANCELTRANSMIT)
#error SECOC_PDUR_SECOCCANCELTRANSMIT already defined
#endif
#define SECOC_PDUR_SECOCCANCELTRANSMIT [!IF "'true' = node:value(as:modconf('PduR')/PduRBswModules/SecOC/PduRTransportProtocol) and 'true' = node:value(as:modconf('PduR')/PduRBswModules/SecOC/PduRCancelTransmit)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!SELECT "as:modconf('SecOC')"!][!//

/** \brief Macro, which defines the length in bytes of the Data ID element
 */
#if (defined SECOC_NR_PARTITIONS)
#error SECOC_NR_PARTITIONS already defined
#endif
#define SECOC_NR_PARTITIONS [!"num:i(count(node:refs(SecOCMainFunctionRx/*/SecOCMainFunctionRxPartitionRef | SecOCMainFunctionTx/*/SecOCMainFunctionTxPartitionRef)))"!]U

/** \brief Macro, which defines the number of partitions where SecOC main functions are running
 */
#if (defined SECOC_DATAID_LENGTH)
#error SECOC_DATAID_LENGTH already defined
#endif
#define SECOC_DATAID_LENGTH [!IF "node:value(SecOCEbGeneral/SecOCDataIdLength) = 'UINT8'"!]1U[!ELSEIF "node:value(SecOCEbGeneral/SecOCDataIdLength) = 'UINT16'"!]2U[!ELSE!]4U[!ENDIF!]

/** \brief Macro, which defines whether AUTOSAR 4.0.3 APIs or 4.2.1 APIs of the PduR shall be used.
 *
 * STD_ON, if AUTOSAR 4.0.3 APIs are used.
 * STD_OFF, if AUTOSAR 4.2.1 APIs are used.
 */
#if (defined SECOC_ASR403_API)
#error SECOC_ASR403_API already defined
#endif
#define SECOC_ASR403_API [!IF "'true' = node:value(SecOCEbGeneral/SecOCASR403)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro, which defines whether Rte usage is configured for the SecOC.
 *
 * STD_ON, if Rte usage is enabled.
 * STD_OFF, if Rte usage is disabled.
 */
#if (defined SECOC_INCLUDE_RTE)
#error SECOC_INCLUDE_RTE already defined
#endif
#define SECOC_INCLUDE_RTE [!IF "'true' = node:value(SecOCEbGeneral/SecOCRteUsage)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro, which defines whether Det usage is configured for the SecOC.
 *
 * STD_ON, if development error detection is enabled.
 * STD_OFF, if development error detection is disabled.
 */
#if (defined SECOC_DET_ENABLED)
#error SECOC_DET_ENABLED already defined
#endif
#define SECOC_DET_ENABLED STD_OFF

/** \brief Macro, which defines whether the SecOC provides the API SecOC_GetVersionInfo()
 *
 * STD_ON, if SecOC_GetVersionInfo() is available.
 * STD_OFF, if SecOC_GetVersionInfo() is not available.
 */
#if (defined SECOC_VERSION_INFO_API)
#error SECOC_VERSION_INFO_API already defined
#endif
#define SECOC_VERSION_INFO_API [!IF "'true' = node:value(SecOCGeneral/SecOCVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the authenticator length is passed to the cryptographic
 *         algorithm in bits or in bytes
 *         STD_ON:  Authenticator is passed in bits to the cryptographic algorithm
 *         STD_OFF: Authenticator is passed in bytes to the cryptographic algorithm
 */
#if (defined SECOC_AUTH_LENGTH_BITS)
#error SECOC_AUTH_LENGTH_BITS already defined
#endif
#define SECOC_AUTH_LENGTH_BITS [!IF "'true' = node:value(SecOCEbGeneral/SecOCCryptoBitLength)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Macro which defines whether the secured area within a PDU shall be used or not.
  *        STD_ON: Secured area within a PDU is used, the secured part of the authentic PDU will be sent authenticator
  *        STD_OFF: Secured area within a PDU is not used, the complete authentic PDU will be sent to the authenticator
  */
#if (defined SECOC_PDU_SECURED_AREA)
  #error SECOC_PDU_SECURED_AREA is already defined
#endif
#define  SECOC_PDU_SECURED_AREA [!IF "'true' = node:value(SecOCEbGeneral/SecOCUseSecuredArea)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  How the current freshness value shall be determined.
 */
[!IF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'RTE'"!][!//
#if (defined SECOC_QUERY_FRESHNESS_VALUE)
#error SECOC_QUERY_FRESHNESS_VALUE already defined
#endif
#define SECOC_QUERY_FRESHNESS_VALUE SECOC_FRESHNESS_RTE
[!ELSEIF "node:value(SecOCGeneral/SecOCQueryFreshnessValue) = 'CFUNC'"!][!//
#if (defined SECOC_QUERY_FRESHNESS_VALUE)
#error SECOC_QUERY_FRESHNESS_VALUE already defined
#endif
#define SECOC_QUERY_FRESHNESS_VALUE SECOC_FRESHNESS_CFUNC
[!ELSE!][!//
#if (defined SECOC_QUERY_FRESHNESS_VALUE)
#error SECOC_QUERY_FRESHNESS_VALUE already defined
#endif
#define SECOC_QUERY_FRESHNESS_VALUE SECOC_FRESHNESS_NONE
[!ENDIF!][!//

/** \brief Macro, which defines if SecOC calls during the initialization phase for every PDU an
 *         external API defined by SecOCCsmJobRefCallout to obtain the Csm job ID that shall be
 *         used together with the Csm services
 *
 * STD_ON, the callout will be executed to obtain the Csm job ID
 * STD_OFF, no callout shall be done
 */
#if (defined SECOC_USE_CSMJOBREF_CALLOUT)
#error SECOC_USE_CSMJOBREF_CALLOUT already defined
#endif
#define SECOC_USE_CSMJOBREF_CALLOUT [!"node:when($UseCsmJobRefCallout = 'true', 'STD_ON', 'STD_OFF')"!]

[!IF "$UseCsmJobRefCallout = 'true'"!][!//
/** \brief Macro, which defines the name of the callout function
 *         used to obtain the Csm job ID
 */
#if (defined SECOC_CSMJOBREF_CALLOUT)
#error SECOC_CSMJOBREF_CALLOUT already defined
#endif
#define SECOC_CSMJOBREF_CALLOUT     [!"node:value(SecOCEbGeneral/SecOCCsmJobRefCallout)"!]
[!ENDIF!][!//

/** \brief Macro, which switches the reporting of security events to the IdsM.
 *
 * STD_ON,  Security Event Reporting is enabled.
 * STD_OFF  Security Event Reporting is disabled.
 */
#if (defined SECOC_ENABLE_SEC_EVENT_REPORTING)
#error SECOC_ENABLE_SEC_EVENT_REPORTING already defined
#endif
#define SECOC_ENABLE_SEC_EVENT_REPORTING [!IF "'true' = node:value(SecOCGeneral/SecOCEnableSecurityEventReporting)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

[!IF "$UseCsmJobRefCallout = 'true'"!][!//

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/** \brief This function is used by the SecOC to obtain the Csm job ID which shall be used
 *         when calling the Csm services. The call will be made during the initialization phase
 *         for every Rx and Tx PDU configured
 *
 * \param[in]       JobId          the Csm job ID extracted from service references,
 *                                 set during the pre-compile time, during the configuration phase
 *
 */
/* !LINKSTO  SecOC.EB.RxTx.SWS_SecOC_00012,1 */
extern FUNC(uint32, SECOC_APPL_CODE) [!"SecOCEbGeneral/SecOCCsmJobRefCallout"!]
(
   uint32 JobId
);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

[!ENDIF!][!//
[!ENDSELECT!][!//

#endif /* #ifndef SECOC_CFG_H */

/*==================[end of file]=================================================================*/
