/**
 * \file
 *
 * \brief AUTOSAR Dlt
 *
 * This file contains the implementation of the AUTOSAR
 * module Dlt.
 *
 * \version 1.9.2
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef DLT_CFG_H
#define DLT_CFG_H

/* This file contains all target independent public configuration declarations
 * for the AUTOSAR module Dlt. */
/* !LINKSTO Dlt.swdd.DltConfig.Template.Dlt_Cfg_h,1 */

[!INCLUDE "Dlt_Vars.m"!][!//
/*==================[includes]==============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <TSAutosar.h>                        /* EB specific standard types */

#include <ComStack_Cfg.h>

[!IF "DltGeneral/DltRteUsage = 'true'"!]
#include <Rte_Dlt_Type.h>
[!ELSEIF "(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!]
#include <Rte_Type.h>
[!ENDIF!]
/*==================[macros]================================================*/

[!IF "node:exists(DltMultipleConfigurationContainer/DltPduConfig/DltRxPduId)"!][!//
  [!VAR "DltOnEthernet" = "'false'"!][!//
  [!VAR "DltSocketId" = "0"!][!//
  [!IF "node:exists(as:modconf('PduR')) and node:exists(as:modconf('SoAd'))  and node:exists(DltMultipleConfigurationContainer/DltPduConfig/DltRxPduRef) and node:exists(as:ref(as:modconf('PduR')/PduRRoutingTables/*/PduRRoutingTable/*/PduRRoutingPath/*/PduRDestPdu/*/PduRDestPduRef)) "!][!//
    [!VAR "DltRxPduName" = "(node:name((as:ref(DltMultipleConfigurationContainer/DltPduConfig/DltRxPduRef))))"!][!//
    [!IF "node:exists(as:modconf('PduR')/PduRRoutingTables/*/PduRRoutingTable/*/PduRRoutingPath/*/PduRDestPdu/*/PduRDestPduRef[node:name(as:ref(.))=string($DltRxPduName)])"!][!//
      [!VAR "PduRUpperRefName" = "node:name(as:ref(as:modconf('PduR')/PduRRoutingTables/*/PduRRoutingTable/*/PduRRoutingPath/*/PduRDestPdu/*/PduRDestPduRef[node:name(as:ref(.))=string($DltRxPduName)]/../../../PduRSrcPdu/PduRSrcPduRef))"!][!//
      [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/*/SoAdSocketRoute/*/SoAdSocketRouteDest/*/SoAdRxPduRef[node:name(node:ref(.))=string($PduRUpperRefName)])"!][!//
        [!VAR "DltOnEthernet" = "'true'"!][!//
        [!VAR "DltSocketId" = "as:ref(as:modconf('SoAd')/SoAdConfig/*/SoAdSocketRoute/*/SoAdSocketRouteDest/*/SoAdRxPduRef[node:name(as:ref(.))=string($PduRUpperRefName)]/../../../SoAdRxSocketConnOrSocketConnBundleRef)/SoAdSocketId"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
#if (defined DLT_ON_ETHERNET)
#error DLT_ON_ETHERNET already defined
#endif
/** \brief Switch indicating whether the underlying communication layer is Ethernet or not  */
#define DLT_ON_ETHERNET          [!IF "$DltOnEthernet"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_RX_SOCKET_ID)
#error DLT_RX_SOCKET_ID already defined
#endif
/** \brief The Socket ID on which the reception happens if Dlt is on Ethernet  */
#define DLT_RX_SOCKET_ID         [!IF "$DltOnEthernet"!][!"$DltSocketId"!][!ELSE!]0xFFU[!ENDIF!]
[!ENDIF!][!//

#if (defined STBM_TIMESTAMP)
#error STBM_TIMESTAMP already defined
#endif
#define STBM_TIMESTAMP                        1U

#if (defined OS_TIMESTAMP)
#error OS_TIMESTAMP already defined
#endif
#define OS_TIMESTAMP                          2U

#define AUTOSAR_421                           0U
#define AUTOSAR_422                           1U
#define AUTOSAR_431                           2U
#define AUTOSAR_20_11                         3U
#define AUTOSAR_22_11                         4U

#if (defined DLT_LITTLE_ENDIAN)
#error DLT_LITTLE_ENDIAN already defined
#endif
/** \brief Symbolic name for little endianness */
#define DLT_LITTLE_ENDIAN                     0U

#if (defined DLT_BIG_ENDIAN)
#error DLT_BIG_ENDIAN already defined
#endif
/** \brief Symbolic name for big endianness */
#define DLT_BIG_ENDIAN                        1U

#if (defined DLT_MSIN_HEADER_LEN)
#error DLT_MSIN_HEADER_LEN already defined
#endif
/** \brief Length of the "Message info" header field */
#define DLT_MSIN_HEADER_LEN             1U

#if (defined DLT_NOAR_HEADER_LEN)
#error DLT_NOAR_HEADER_LEN already defined
#endif
/** \brief Length of the "Number of arguments" header field */
#define DLT_NOAR_HEADER_LEN             1U

[!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltProtocolVersion)"!][!//
#if (defined DLT_PROTOCOL_VERSION)
#error DLT_PROTOCOL_VERSION is already defined.
#endif
/** \brief Defines the protocol version that is used by Dlt */
#define DLT_PROTOCOL_VERSION              [!"as:modconf('Dlt')/DltGeneral/DltProtocolVersion"!]U
[!ELSE!][!//
#define DLT_PROTOCOL_VERSION              1U
[!ENDIF!][!//

#if (defined DLT_DET_FORWARDERRORTRACE)
#error DLT_DET_FORWARDERRORTRACE is already defined.
#endif
[!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace)) and (as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace = 'true')"!][!//
#define DLT_DET_FORWARDERRORTRACE STD_ON
[!ELSE!][!//
#define DLT_DET_FORWARDERRORTRACE STD_OFF
[!ENDIF!][!//

[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#if (defined DLT_MAX_COUNT_APP_IDS_FOR_GET_LOG_INFO)
#error DLT_MAX_COUNT_APP_IDS_FOR_GET_LOG_INFO is already defined.
#endif
/** \brief The maximum number of registered AppIds that will be returned by the GetLogInfo operation through the Rte */
[!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltMaxCountAppIdsForGetLogInfo)"!][!//
#define DLT_MAX_COUNT_APP_IDS_FOR_GET_LOG_INFO [!"num:i(as:modconf('Dlt')/DltGeneral/DltMaxCountAppIdsForGetLogInfo)"!]U
[!ELSE!][!//
#define DLT_MAX_COUNT_APP_IDS_FOR_GET_LOG_INFO [!"num:i($TotalAppNo)"!]U
[!ENDIF!][!//

#if (defined DLT_MAX_COUNT_CTX_IDS_FOR_GET_LOG_INFO)
#error DLT_MAX_COUNT_CTX_IDS_FOR_GET_LOG_INFO is already defined.
#endif
/** \brief The maximum number of registered ContextIds that will be returned by the GetLogInfo operation through the Rte */
[!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltMaxCountCtxIdsForGetLogInfo)"!][!//
#define DLT_MAX_COUNT_CTX_IDS_FOR_GET_LOG_INFO [!"num:i(as:modconf('Dlt')/DltGeneral/DltMaxCountCtxIdsForGetLogInfo)"!]U
[!ELSE!][!//
#define DLT_MAX_COUNT_CTX_IDS_FOR_GET_LOG_INFO [!"num:i($TotalNoOfConfiguredContextIds)"!]U
[!ENDIF!][!//

#if (defined DLT_GET_LOG_INFO_RETURN_SIZE)
#error DLT_GET_LOG_INFO_RETURN_SIZE is already defined.
#endif
/** \brief The size of the byte array that gets written by the Dlt_GetLogInfo() API for the GetLogInfo operation. */
#define DLT_GET_LOG_INFO_RETURN_SIZE (2U + (DLT_MAX_COUNT_APP_IDS_FOR_GET_LOG_INFO * (DLT_APPCTX_DESC_LEN + 7U)) + \
                                           (DLT_MAX_COUNT_CTX_IDS_FOR_GET_LOG_INFO * (DLT_APPCTX_DESC_LEN + 7U)))
[!ENDIF!][!//

[!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
#if (defined DLT_APPID_LENGTH)
#error DLT_APPID_LENGTH already defined
#endif
#define DLT_APPID_LENGTH                       [!"num:i(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)"!]U

#if (defined DLT_CTXID_LENGTH)
#error DLT_CTXID_LENGTH already defined
#endif
#define DLT_CTXID_LENGTH                       [!"num:i(as:modconf('Dlt')/DltGeneral/DltContextIdLength)"!]U

[!ELSE!][!//
#if (defined DLT_APPID_LENGTH)
#error DLT_APPID_LENGTH already defined
#endif
#define DLT_APPID_LENGTH                      4U

#if (defined DLT_CTXID_LENGTH)
#error DLT_CTXID_LENGTH already defined
#endif
#define DLT_CTXID_LENGTH                      4U
[!ENDIF!][!//

[!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
#if (defined DLT_APP_ID_NULL)
#error DLT_APP_ID_NULL already defined
#endif
/** \brief Macro to define an application ID of NULL value */
#define DLT_APP_ID_NULL        [!"$NullApplicationId"!]

#if (defined DLT_CTX_ID_NULL)
#error DLT_CTX_ID_NULL already defined
#endif
/** \brief Macro to define a context ID of NULL value */
#define DLT_CTX_ID_NULL        [!"$NullContextId"!]

[!ELSE!][!//
#if (defined DLT_APP_ID_NULL)
#error DLT_APP_ID_NULL already defined
#endif
/** \brief Macro to define an application ID of NULL value */
#define DLT_APP_ID_NULL        0x00U

#if (defined DLT_CTX_ID_NULL)
#error DLT_CTX_ID_NULL already defined
#endif
/** \brief Macro to define a context ID of NULL value */
#define DLT_CTX_ID_NULL        0x00U
[!ENDIF!][!//

[!IF "as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2"!][!//
#if (defined DLT_INIT_HEADER_LENGTH)
#error DLT_INIT_HEADER_LENGTH already defined
#endif
#define DLT_INIT_HEADER_LENGTH                 9U

[!IF "('Callout' = as:modconf('Dlt')[1]/DltMultipleConfigurationContainer/DltProtocol/DltEcuIdChoice)"!][!//
#if (defined DLT_ECUID_LENGTH)
#error DLT_ECUID_LENGTH already defined
#endif
#define DLT_ECUID_LENGTH                       [!"DltGeneral/DltEcuIdLength"!]U
[!ELSE!][!//
#if (defined DLT_ECUID_LENGTH)
#error DLT_ECUID_LENGTH already defined
#endif
#define DLT_ECUID_LENGTH                       [!"num:i(string-length(node:value(as:modconf('Dlt')/DltMultipleConfigurationContainer/DltProtocol/DltEcuId)))"!]U
[!ENDIF!][!//

#if (defined DLT_USE_APPID_CTXID_IN_HEADER)
#error DLT_USE_APPID_CTXID_IN_HEADER already defined
#endif
#define DLT_USE_APPID_CTXID_IN_HEADER          [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseAppIdandCtxId = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_MSID_HEADER_LENGTH)
#error DLT_MSID_HEADER_LENGTH already defined
#endif
#define DLT_MSID_HEADER_LENGTH                4U

#if (defined DLT_HEADER_CONFIG_SESSION_ID_BIT)
#error DLT_HEADER_CONFIG_SESSION_ID_BIT already defined
#endif
#define DLT_HEADER_CONFIG_SESSION_ID_BIT      [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseSessionID = 'true'"!]0x10[!ELSE!]0x00[!ENDIF!]U
[!ELSE!][!//

#if (defined DLT_INIT_HEADER_LENGTH)
#error DLT_INIT_HEADER_LENGTH already defined
#endif
#define DLT_INIT_HEADER_LENGTH                ((DLT_MIN_HEADER_LENGTH)[!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseEcuId = 'true'"!] + (DLT_ECU_HEADER_LENGTH)[!ENDIF!][!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseSessionID = 'true'"!] + (DLT_SEID_HEADER_LENGTH)[!ENDIF!][!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseTimestamp = 'true'"!] + (DLT_TMSP_HEADER_LENGTH)[!ENDIF!][!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseExtendedHeader = 'true'"!] + (DLT_EXT_HEADER_LENGTH)[!ENDIF!])

#if (defined DLT_ECUID_LENGTH)
#error DLT_ECUID_LENGTH already defined
#endif
#define DLT_ECUID_LENGTH                      4U

#if (defined DLT_USE_APPID_CTXID_IN_HEADER)
#error DLT_USE_APPID_CTXID_IN_HEADER already defined
#endif
#define DLT_USE_APPID_CTXID_IN_HEADER         SDT_OFF

#if (defined DLT_HEADER_CONFIG_SESSION_ID_BIT)
#error DLT_HEADER_CONFIG_SESSION_ID_BIT already defined
#endif
#define DLT_HEADER_CONFIG_SESSION_ID_BIT      [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseSessionID = 'true'"!]0x08[!ELSE!]0x00[!ENDIF!]U
[!ENDIF!][!//

[!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
#if (defined DLT_VFB_APP_ID_MSB)
#error DLT_VFB_APP_ID_MSB already defined
#endif
/** \brief Id of VFB in MSB format */
#define DLT_VFB_APP_ID_MSB    [!"$VFBApplicationIdMSB"!]

#if (defined DLT_DET_APP_ID_MSB)
#error DLT_DET_APP_ID_MSB already defined
#endif
/** \brief ApplicationId of Det in MSB format */
#define DLT_DET_APP_ID_MSB    [!"$DetApplicationIdMSB"!]

#if (defined DLT_DET_CONTEXT_ID_MSB)
#error DLT_DET_CONTEXT_ID_MSB is already defined
#endif
/** \brief ContextId of Det in MSB format */
#define DLT_DET_CONTEXT_ID_MSB [!"$DetContextIdMSB"!]

#if (defined DLT_VFB_APP_ID_LSB)
#error DLT_VFB_APP_ID_LSB already defined
#endif
/** \brief ApplicationId of VFB in LSB format */
#define DLT_VFB_APP_ID_LSB    [!"$VFBApplicationIdLSB"!]

#if (defined DLT_DET_APP_ID_LSB)
#error DLT_DET_APP_ID_LSB already defined
#endif
/** \brief ApplicationId of Det in LSB format */
#define DLT_DET_APP_ID_LSB    [!"$DetApplicationIdLSB"!]

#if (defined DLT_DET_CONTEXT_ID_LSB)
#error DLT_DET_CONTEXT_ID_LSB is already defined
#endif
/** \brief ContextId of Det in LSB format */
#define DLT_DET_CONTEXT_ID_LSB [!"$DetContextIdLSB"!]

[!ELSE!][!//

#if (defined DLT_VFB_APP_ID_MSB)
#error DLT_VFB_APP_ID_MSB already defined
#endif
/** \brief Id of VFB in MSB format */
#define DLT_VFB_APP_ID_MSB    0x56464254U
[!ENDIF!][!//

#if (defined DLT_VFB_CONTEXT_ID_VAR)
#error DLT_VFB_CONTEXT_ID_VAR is already defined
#endif
#define DLT_VFB_CONTEXT_ID_VAR [!"$VFBContextId"!]

[!IF "as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 1"!][!//
#if (defined DLT_APID_HEADER_LEN)
#error DLT_APID_HEADER_LEN already defined
#endif
/** \brief Length of the "Application ID" header field */
#define DLT_APID_HEADER_LEN             4U

#if (defined DLT_CTID_HEADER_LEN)
#error DLT_CTID_HEADER_LEN already defined
#endif
/** \brief Length of the "Context ID" header field */
#define DLT_CTID_HEADER_LEN             4U
[!ELSE!][!//
[!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11))"!][!//
#if (defined DLT_APID_HEADER_LEN)
#error DLT_APID_HEADER_LEN already defined
#endif
/** \brief Length of the "AP ID" header field */
#define DLT_APID_HEADER_LEN             (DLT_APPID_LENGTH + 1U)

#if (defined DLT_CTID_HEADER_LEN)
#error DLT_CTID_HEADER_LEN already defined
#endif
/** \brief Length of the "CT ID" header field */
#define DLT_CTID_HEADER_LEN             (DLT_CTXID_LENGTH + 1U)
[!ELSE!][!//
#if (defined DLT_APID_HEADER_LEN)
#error DLT_APID_HEADER_LEN already defined
#endif
/** \brief Length of the "Application ID" header field */
#define DLT_APID_HEADER_LEN             5U

#if (defined DLT_CTID_HEADER_LEN)
#error DLT_CTID_HEADER_LEN already defined
#endif
/** \brief Length of the "Context ID" header field */
#define DLT_CTID_HEADER_LEN             5U
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2"!][!//
#if (defined DLT_MIN_HEADER_LENGTH)
#error DLT_MIN_HEADER_LENGTH already defined
#endif
/** \brief Minimum header length (mandatory HTYP2, MCNT and LEN fields */
#define DLT_MIN_HEADER_LENGTH           7U
/** \brief Additional base header length due to elements that are required 
 *         for control messages when DltProtocolVersion is set to 2:
 *
 *           HTYP2: 4 bytes (always present)
 *           MCNT: 1 byte (always present)
 *           LEN:  2 bytes (always present)
 *           MSIN: 1 byte (always present for control messages)
 *           NOAR: 1 byte (always present for control messages)
 */
#if (defined DLT_BASE_HEADER_CONTROL_COND_ELEMENTS_LENGTH)
#error DLT_BASE_HEADER_CONTROL_COND_ELEMENTS_LENGTH already defined
#endif
#define DLT_BASE_HEADER_CONTROL_COND_ELEMENTS_LENGTH  2U

#if (defined DLT_MESSAGE_INFO_HEADER_LENGTH)
#error DLT_MESSAGE_INFO_HEADER_LENGTH already defined
#endif
/** \brief Length of the "Message Info" header field */
#define DLT_MESSAGE_INFO_HEADER_LENGTH  1U

#if (defined DLT_TMSP_HEADER_LENGTH)
#error DLT_TMSP_HEADER_LENGTH already defined
#endif
/** \brief Length of the "Timestamp" header field */
#define DLT_TMSP_HEADER_LENGTH          9U

#if (defined DLT_MSG_ID_HEADER_LENGTH)
#error DLT_MSG_ID_HEADER_LENGTH already defined
#endif
/** \brief Length of the "Message ID" header field */
#define DLT_MSG_ID_HEADER_LENGTH        4U

/*  Extension Header  */

#if (defined DLT_SEID_HEADER_LENGTH)
#error DLT_SEID_HEADER_LENGTH already defined
#endif
/** \brief Length of the "Session ID" header field */
#define DLT_SEID_HEADER_LENGTH          4U

#if (defined DLT_ECU_HEADER_LENGTH)
#error DLT_ECU_HEADER_LENGTH already defined
#endif
/** \brief Length of the "ECU ID" header field */
#define DLT_ECU_HEADER_LENGTH           (DLT_ECUID_LENGTH + 1U)

#if (defined DLT_EXT_HEADER_LENGTH_STATIC)
#error DLT_EXT_HEADER_LENGTH_STATIC already defined
#endif
/** \brief Size of the extended header - independent of the configuration */
#define DLT_EXT_HEADER_LENGTH_STATIC    (DLT_ECU_HEADER_LENGTH + DLT_APID_HEADER_LEN + DLT_CTID_HEADER_LEN + DLT_SEID_HEADER_LENGTH)

#if (defined DLT_EXT_HEADER_LENGTH)
#error DLT_EXT_HEADER_LENGTH already defined
#endif
/** \brief Length of extended header */
#define DLT_EXT_HEADER_LENGTH           0U

#if (defined DLT_EXT_HEADER_LENGTH_MAX)
#error DLT_EXT_HEADER_LENGTH_MAX already defined
#endif
#define DLT_EXT_HEADER_LENGTH_MAX       (DLT_ECU_HEADER_LENGTH + DLT_SEID_HEADER_LENGTH + DLT_APID_HEADER_LEN + DLT_CTID_HEADER_LEN)

[!ELSE!][!//

/* !LINKSTO Dlt.ASR421.SWS_Dlt_00458,1 */
#if (defined DLT_MIN_HEADER_LENGTH)
#error DLT_MIN_HEADER_LENGTH already defined
#endif
/** \brief Minimum header length (mandatory HTYP, MCNT and LEN fields */
#define DLT_MIN_HEADER_LENGTH           4U

#if (defined DLT_ECU_HEADER_LENGTH)
#error DLT_ECU_HEADER_LENGTH already defined
#endif
/** \brief Length of the "ECU ID" header field */
#define DLT_ECU_HEADER_LENGTH           4U

#if (defined DLT_SEID_HEADER_LENGTH)
#error DLT_SEID_HEADER_LENGTH already defined
#endif
/** \brief Length of the "Session ID" header field */
#define DLT_SEID_HEADER_LENGTH          4U

#if (defined DLT_TMSP_HEADER_LENGTH)
#error DLT_TMSP_HEADER_LENGTH already defined
#endif
/** \brief Length of the "Timestamp" header field */
#define DLT_TMSP_HEADER_LENGTH          4U

#if (defined DLT_EXT_HEADER_LENGTH)
#error DLT_EXT_HEADER_LENGTH already defined
#endif
/** \brief Length of extended header */
#define DLT_EXT_HEADER_LENGTH           (DLT_MSIN_HEADER_LEN + DLT_NOAR_HEADER_LEN + \
                                         DLT_APID_HEADER_LEN + DLT_CTID_HEADER_LEN)
[!ENDIF!][!//

#if (defined DLT_DEFAULT_ASR_RETVAL)
#error DLT_DEFAULT_ASR_RETVAL already defined
#endif
/** \brief AUTOSAR in use APIs */
#define DLT_DEFAULT_ASR_RETVAL          [!"num:i($DltServiceAPI)"!]

#if (defined DLT_MESSAGE_OPTIONS_BITFIELD)
#error DLT_MESSAGE_OPTIONS_BITFIELD is already defined.
#endif
/* !LINKSTO EB.Req.DltMessageOptionsBitField, 1 */
/** \brief Defines which AUTOSAR release is used for the "options" member bit fields */
#define DLT_MESSAGE_OPTIONS_BITFIELD     [!"as:modconf('Dlt')/DltGeneral/DltMessageOptionsBitField"!]

#if (defined DLT_VERSION_INFO_API)
#error DLT_VERSION_INFO_API is already defined.
#endif
/** \brief Switch, indicating if Version Info is activated for Dlt */
#define DLT_VERSION_INFO_API             [!IF "(node:exists(DltGeneral/DltVersionInfoApi)) and (DltGeneral/DltVersionInfoApi = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_DEV_ERROR_DETECT)
#error DLT_DEV_ERROR_DETECT is already defined.
#endif
#define DLT_DEV_ERROR_DETECT             [!IF "DltGeneral/DltDevErrorDetect = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]




[!SELECT "DltGeneral"!][!//

#if (defined DLT_DET_RUNTIME_CHECKS)
#error DLT_DET_RUNTIME_CHECKS is already defined
#endif
/** \brief DET runtime checks reporting
 **
 ** En- or disables the reporting of the DET runtime checks */
#define DLT_DET_RUNTIME_CHECKS   [!//
[!IF "DltDetRuntimeChecks = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


#if (defined DLT_INCLUDE_RTE)
#error DLT_INCLUDE_RTE is already defined.
#endif
/** \brief Defines whether a Rte module configuration is available.
 **        If it is available then it is automatically used by the Dlt module.
 **        STD_ON:  Rte configuration is available.
 **        STD_OFF: Rte configuration is not available.
 **/
#define DLT_INCLUDE_RTE                    [!IF "DltGeneral/DltRteUsage = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_CONTROL_SERVICE_PORT)
#error DLT_CONTROL_SERVICE_PORT already defined
#endif
/** \brief Macro used for the visibility of symbols generated by the Rte for the DltControlService interface when DltServiceAPI == AUTOSAR_431, AUTOSAR_20_11 or AUTOSAR_22_11 */
#define DLT_CONTROL_SERVICE_PORT           [!IF "count(DltSwc/*[(DltProvideControlServicePort = 'true')]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_MESSAGE_SERVICE_PORT)
#error DLT_MESSAGE_SERVICE_PORT already defined
#endif
/** \brief Macro used for the visibility of symbols generated by the Rte for the DltSwcMessageService interface when DltServiceAPI == AUTOSAR_431, AUTOSAR_20_11 or AUTOSAR_22_11 */
#define DLT_MESSAGE_SERVICE_PORT           [!IF "count(DltSwc/*[(DltProvideSwcMessageServicePort = 'true')]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_IMPLEMENT_EXTENDED_HEADER)
#error DLT_IMPLEMENT_EXTENDED_HEADER already defined
#endif
[!IF "as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2"!][!//
#define DLT_IMPLEMENT_EXTENDED_HEADER      STD_ON
[!ELSE!][!//
#define DLT_IMPLEMENT_EXTENDED_HEADER      [!IF "as:modconf('Dlt')/DltGeneral/DltImplementExtendedHeader = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

#if (defined DLT_IMPLEMENT_FILTER_MESSAGES)
#error DLT_IMPLEMENT_FILTER_MESSAGES is already defined.
#endif
#define DLT_IMPLEMENT_FILTER_MESSAGES      [!IF "DltGeneral/DltImplementFilterMessages = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_IMPLEMENT_TIMESTAMP)
#error DLT_IMPLEMENT_TIMESTAMP already defined
#endif
[!IF "node:exists(DltGeneral/DltGeneralStbMTimeBaseRef) and node:refvalid(DltGeneral/DltGeneralStbMTimeBaseRef)"!][!//
#define DLT_IMPLEMENT_TIMESTAMP            STBM_TIMESTAMP

#if (defined DLT_STBM_TIMEBASE_REF_ID)
#error DLT_STBM_TIMEBASE_REF_ID already defined
#endif
#define DLT_STBM_TIMEBASE_REF_ID           [!"node:value(as:ref(./DltGeneral/DltGeneralStbMTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier)"!]U
[!ELSEIF "DltGeneral/DltImplementTimestamp = 'true'"!][!//
/* !LINKSTO Dlt.Config.StbMTimeBaseRef.NotConfigured,2 */
#define DLT_IMPLEMENT_TIMESTAMP            OS_TIMESTAMP
[!ELSE!][!//
#define DLT_IMPLEMENT_TIMESTAMP            STD_OFF
[!ENDIF!][!//

#if (defined DLT_IMPLEMENT_VERBOSE)
#error DLT_IMPLEMENT_VERBOSE is already defined.
#endif
/* !LINKSTO Dlt.ASR421.SWS_Dlt_00014,1 */
#define DLT_IMPLEMENT_VERBOSE              [!IF "DltGeneral/DltImplementVerboseMode  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_IMPLEMENT_NV_RAM_STORAGE)
#error DLT_IMPLEMENT_NV_RAM_STORAGE is already defined.
#endif
#define DLT_IMPLEMENT_NV_RAM_STORAGE       [!IF "DltGeneral/DltImplementNVRamStorage = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_IMPLEMENT_VFB_TRACE)
#error DLT_IMPLEMENT_VFB_TRACE is already defined.
#endif
#define DLT_IMPLEMENT_VFB_TRACE            [!IF "DltGeneral/DltImplementVfbTrace = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "DltGeneral/DltImplementVfbTrace = 'true'"!][!//
[!IF "DltGeneral/DltVfbSendHookFunctionParameters = 'false'"!][!//
#if (defined DLT_VFB_TRACE_PAYLOAD_MAX_SIZE)
#error DLT_VFB_TRACE_PAYLOAD_MAX_SIZE is already defined
#endif
/** \brief Maximum size of the payload for a configured VFB hook function:
 *         - 4 bytes represent the MessageId;
 *         - 6 bytes represent the ContextId and the payload length when PduLengthType is uint16
 *         - 8 bytes represent the ContextId and the payload length when PduLengthType is uint32 */
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_VFB_TRACE_PAYLOAD_MAX_SIZE  10U
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_VFB_TRACE_PAYLOAD_MAX_SIZE  12U
#endif /* #if (TS_SIZE_PduLengthType == 2U) */
[!ELSE!][!//
/** \brief Maximum size of the payload for a configured VFB hook function:
 *         - configurable amount of bytes for payload
 *         - 6 bytes represent the ContextId and the payload length when PduLengthType is uint16
 *         - 8 bytes represent the ContextId and the payload length when PduLengthType is uint32 */
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_VFB_TRACE_PAYLOAD_MAX_SIZE  ([!"DltGeneral/DltVfbTracePayloadMaxSize"!]U + 6U)
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_VFB_TRACE_PAYLOAD_MAX_SIZE  ([!"DltGeneral/DltVfbTracePayloadMaxSize"!]U + 8U)
#endif /* #if (TS_SIZE_PduLengthType == 2U) */
[!ENDIF!][!//

[!IF "node:exists(DltGeneral/DltVfbMainFunctionPeriod)"!][!//
#if (defined DLT_VFB_MAINFUNCTION_PERIOD)
#error DLT_VFB_MAINFUNCTION_PERIOD is already defined
#endif
/** \brief Period (in milliseconds) of Dlt_VfbMainFunction() */
#define DLT_VFB_MAINFUNCTION_PERIOD        [!"num:i(DltGeneral/DltVfbMainFunctionPeriod * 1000)"!]U
[!ENDIF!][!//

#if (defined DLT_VFB_TRACE_NO_OF_INTERRUPTS)
#error DLT_VFB_TRACE_NO_OF_INTERRUPTS is already defined
#endif
/** \brief The maximum number of interrupts possible within the system */
#define DLT_VFB_TRACE_NO_OF_INTERRUPTS  [!"DltGeneral/DltVfbTraceNoOfInterrupts"!]U

#if (defined DLT_RTE_MODULE_ID)
#error DLT_RTE_MODULE_ID is already defined
#endif
/* !LINKSTO Dlt.ASR43.VfbTracing.RteModuleIdAsTraceFunctionSessionId, 1 */
/** \brief ModuleId of the Rte module to be used as SessionId for the VFB hook functions */
#define DLT_RTE_MODULE_ID               [!"num:i(as:modconf('Rte')/CommonPublishedInformation/ModuleId)"!]U
[!ENDIF!][!//

[!IF "ReportToDem/DltVfbBufferFullReportToDem = 'DET'"!][!//
#if (defined DLT_E_DEMTODET_VFB_BUFFER_FULL)
#error DLT_E_DEMTODET_VFB_BUFFER_FULL already defined
#endif
/* DET error Id for Dlt full VFB buffer */
#define DLT_E_DEMTODET_VFB_BUFFER_FULL  [!//
[!"ReportToDem/DltVfbBufferFullDemDetErrorId"!]U
[!ELSEIF "ReportToDem/DltVfbBufferFullReportToDem = 'DEM'"!]
#if (defined DLT_E_VFB_BUFFER_FULL_DEM_EVENT_ID)
#error DLT_E_VFB_BUFFER_FULL_DEM_EVENT_ID already defined
#endif
/** \brief DEM Event ID for Dlt bull VFB buffer */
#define DLT_E_VFB_BUFFER_FULL_DEM_EVENT_ID [!//
[!"node:value(as:ref(DltGeneral/DltDemEventParameterRefs/DLT_E_VFB_BUFFER_FULL)/DemEventId)"!]U
[!ENDIF!][!//

#if (defined DLT_VFB_CONTEXT_COUNT)
#error DLT_VFB_CONTEXT_COUNT already defined
#endif
/* !LINKSTO Dlt.ASR43.VfbTracing.ContextInternalHandling, 1 */
/** \brief No of ContextIds (VFB trace functions in this case) registered by the Rte */
#define DLT_VFB_CONTEXT_COUNT              [!"num:i($VfbTraceFunctionCount)"!]U

#if (defined DLT_MAX_CONTROL_MESSAGE_RESPONSE_SIZE)
#error DLT_MAX_CONTROL_MESSAGE_RESPONSE_SIZE already defined
#endif
/** \brief  maximum response size for services */
#define DLT_MAX_CONTROL_MESSAGE_RESPONSE_SIZE [!IF "node:exists(DltGeneral/DltControlMessageMaxResponseSize)"!][!"DltGeneral/DltControlMessageMaxResponseSize"!]U[!ELSE!]4U[!ENDIF!]

[!IF "num:i($DltServiceAPI) < $AUTOSAR_431"!][!//
#if (defined DLT_MAX_COUNT_APP_IDS)
#error DLT_MAX_COUNT_APP_IDS already defined
#endif
/** \brief No of unique application ids that can be registered by the user. */
#define DLT_MAX_COUNT_APP_IDS              [!"DltMemory/DltMaxCountAppIds"!]U

#if (defined DLT_MAX_COUNT_CONTEXT_IDS)
#error DLT_MAX_COUNT_CONTEXT_IDS already defined
#endif
/** \brief No of unique context ids that can be registered by the user. */
#define DLT_MAX_COUNT_CONTEXT_IDS          [!"DltMemory/DltMaxCountContextIds"!]U
[!ELSE!][!//

#if (defined DLT_MAX_COUNT_CONTEXT_IDS)
#error DLT_MAX_COUNT_CONTEXT_IDS already defined
#endif
/** \brief No of unique context ids registered in the configuration. */
[!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace)) and (as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace = 'true')"!][!//
#define DLT_MAX_COUNT_CONTEXT_IDS          ([!"num:i(count(DltSwc/*/DltSwcContext/*) + 1)"!]U + DLT_VFB_CONTEXT_COUNT)
[!ELSE!][!//
#define DLT_MAX_COUNT_CONTEXT_IDS          ([!"num:i(count(DltSwc/*/DltSwcContext/*))"!]U + DLT_VFB_CONTEXT_COUNT)
[!ENDIF!][!//

#if (defined DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID)
#error DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID already defined
#endif
/** \brief Maximum number of contexts allowed to be registered per application. */
#define DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID  [!"num:i($MaxCountCtxtPerAPP)"!]U

#if (defined DLT_MAX_COUNT_APP_IDS)
#error DLT_MAX_COUNT_APP_IDS already defined
#endif
[!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace)) and (as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace = 'true')"!][!//
#define DLT_MAX_COUNT_APP_IDS [!IF "(num:i($VfbTraceFunctionCount) > 0)"!][!"num:i($TotalAppNo + 2)"!]U[!ELSE!][!"num:i($TotalAppNo + 1)"!]U[!ENDIF!]
[!ELSE!][!//
#define DLT_MAX_COUNT_APP_IDS [!IF "(num:i($VfbTraceFunctionCount) > 0)"!][!"num:i($TotalAppNo + 1)"!]U[!ELSE!][!"num:i($TotalAppNo)"!]U[!ENDIF!]
[!ENDIF!][!//

#if (defined MAX_APP_NO)
#error MAX_APP_NO already defined
#endif
/** \brief No of unique application ids registered in the configuration. */
[!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace)) and (as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace = 'true')"!][!//
#define MAX_APP_NO [!IF "(num:i($VfbTraceFunctionCount) > 0)"!][!"num:i($MaxAppNo + 2)"!]U[!ELSE!][!"num:i($MaxAppNo + 1)"!]U[!ENDIF!]
[!ELSE!][!//
#define MAX_APP_NO [!IF "(num:i($VfbTraceFunctionCount) > 0)"!][!"num:i($MaxAppNo + 1)"!]U[!ELSE!][!"num:i($MaxAppNo)"!]U[!ENDIF!]
[!ENDIF!][!//

#if (defined MAX_COUNT_CTXT_PER_APP)
#error MAX_COUNT_CTXT_PER_APP already defined
#endif
#define MAX_COUNT_CTXT_PER_APP [!"num:i($MaxCountCtxtPerAPP)"!]

#if (defined DLT_APPCTX_DESC_LEN)
#error DLT_APPCTX_DESC_LEN already defined
#endif
/** \brief Maximum length of application/context description information */
#define DLT_APPCTX_DESC_LEN       [!"as:modconf('Dlt')/DltGeneral/DltAppCtxDescriptionMaximumLength"!]U

#if (defined DLT_APP_BUFFER_SIZE_WITHOUT_DESC)
#error DLT_APP_BUFFER_SIZE_WITHOUT_DESC already defined
#endif
/** \brief 4 bytes of application id and 2 bytes for no of application registered (index or total no)
 * depending either the requested application is wildcard or not */
#define DLT_APP_BUFFER_SIZE_WITHOUT_DESC          6U

#if (defined DLT_CTXT_BUFFER_SIZE_WITHOUT_DESC)
#error DLT_CTXT_BUFFER_SIZE_WITHOUT_DESC already defined
#endif
/** \brief 4 bytes of context id + 1 byte for log level + 1 byte for trace status  */
#define DLT_CTXT_BUFFER_SIZE_WITHOUT_DESC         6U

#if (defined DLT_APP_BUFFER_SIZE_WITH_DESC)
#error DLT_APP_BUFFER_SIZE_WITH_DESC already defined
#endif
/** \brief 4 bytes of application id and 2 bytes for no of application registered (index or total no)
* depending either the requested application is wildcard or not */
#define DLT_APP_BUFFER_SIZE_WITH_DESC          7U

#if (defined DLT_CTXT_BUFFER_SIZE_WITH_DESC)
#error DLT_CTXT_BUFFER_SIZE_WITH_DESC already defined
#endif
/** \brief 4 bytes of context id + 1 byte for log level + 1 byte for trace status  */
#define DLT_CTXT_BUFFER_SIZE_WITH_DESC         7U

#if (defined DLT_REGISTERED_APP_OR_CTXT_NO_SIZE)
#error DLT_REGISTERED_APP_OR_CTXT_NO_SIZE already defined
#endif
/** \brief 2 bytes for describing the no of registered application or context */
#define DLT_REGISTERED_APP_OR_CTXT_NO_SIZE        2U

[!ENDIF!][!//

[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#if (defined DLT_REGISTER_CONTEXT_NOTIFICATION)
#error DLT_REGISTER_CONTEXT_NOTIFICATION already defined
#endif
/** \brief Macro for Unregister/Register Notification for each ContextId/ApplicationId tuple*/
#define DLT_REGISTER_CONTEXT_NOTIFICATION    [!IF "DltGeneral/DltGeneralRegisterContextNotification = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_DEFAULT_MAX_LOG_LEVEL)
#error DLT_DEFAULT_MAX_LOG_LEVEL already defined
#endif
/** \brief Default max Log Level Threshold for tuple ApplicationId/ContextId */
#define DLT_DEFAULT_MAX_LOG_LEVEL             [!"DltConfigSet/*/DltLogLevelSetting/*/DltDefaultLogLevel"!]

#if (defined DLT_DEFAULT_TRACE_STATUS)
#error DLT_DEFAULT_TRACE_STATUS already defined
#endif
/** \brief Default Trace Status for tuple ApplicationId/ContextId */
#define DLT_DEFAULT_TRACE_STATUS              [!IF "DltConfigSet/*/DltTraceStatusSetting/*/DltDefaultTraceStatus = 'true'"!]DLT_TRACE_STATUS_ON[!ELSE!]DLT_TRACE_STATUS_OFF[!ENDIF!]
[!ELSE!]
#if (defined DLT_REGISTER_CONTEXT_NOTIFICATION)
#error DLT_REGISTER_CONTEXT_NOTIFICATION already defined
#endif
/** \brief Macro for Unregister/Register Notification for each ContextId/ApplicationId tuple*/
#define DLT_REGISTER_CONTEXT_NOTIFICATION     STD_OFF

#if (defined DLT_DEFAULT_MAX_LOG_LEVEL)
#error DLT_DEFAULT_MAX_LOG_LEVEL already defined
#endif
#define DLT_DEFAULT_MAX_LOG_LEVEL             [!"DltMultipleConfigurationContainer/DltMessageFiltering/DltDefaultMaxLogLevel"!]U

#if (defined DLT_DEFAULT_TRACE_STATUS)
#error DLT_DEFAULT_TRACE_STATUS already defined
#endif
#define DLT_DEFAULT_TRACE_STATUS              [!IF "DltMultipleConfigurationContainer/DltMessageFiltering/DltDefaultTraceStatus = 'true'"!]DLT_TRACE_STATUS_ON[!ELSE!]DLT_TRACE_STATUS_OFF[!ENDIF!]

#if (defined DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID)
#error DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID already defined
#endif
/** \brief This is the maximum count for Context IDs per Application ID.*/
#define DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID  [!"DltMemory/DltMaxCountContextIdsPerAppId"!]U

#if (defined DLT_MESSAGE_BUFFER_SIZE)
#error DLT_MESSAGE_BUFFER_SIZE already defined
#endif
/** \brief Buffer size for storing Dlt messages for waiting to transmit over the Network (send buffer).*/
#define DLT_MESSAGE_BUFFER_SIZE               [!"DltMemory/DltMessageBufferSize"!]U

#if (defined DLT_FACTORY_DEFAULT_MAX_LOG_LEVEL)
#error DLT_FACTORY_DEFAULT_MAX_LOG_LEVEL already defined
#endif
 /** \brief The maximum log level a received message (from SW-C to Dlt) can have.*/
#define DLT_FACTORY_DEFAULT_MAX_LOG_LEVEL     [!"DltMultipleConfigurationContainer/DltMessageFiltering/DltFactoryDefaultMaxLogLevel"!]U

#if (defined DLT_MAX_MESSAGE_LENGTH)
#error DLT_MAX_MESSAGE_LENGTH already defined
#endif
/** \brief The maximum length of a Dlt log or trace message.*/
#define DLT_MAX_MESSAGE_LENGTH                [!"DltMultipleConfigurationContainer/DltProtocol/DltMaxMessageLength"!]U
[!ENDIF!]

[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#if (defined DLT_POLL_BUFFER_SPACE)
#error DLT_POLL_BUFFER_SPACE is already defined
#endif
/** \brief Defines whether support for polling available buffer size is enabled or not. */
#define DLT_POLL_BUFFER_SPACE      [!IF "DltGeneral/DltPollingBufferRemainingSpace = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_POLL_BUFFER_SPACE_ON_RTE)
#error DLT_POLL_BUFFER_SPACE_ON_RTE is already defined
#endif
/** \brief Defines whether support for polling available buffer size on Rte is enabled or not. */
#define DLT_POLL_BUFFER_SPACE_ON_RTE    [!IF "DltGeneral/DltPollingBufferRemainingSpace = 'true' and count(DltSwc/*[DltProvideDltBufferSizePollingPort = 'true']) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_NOTIFY_USER_THRESHOLD_REACHED)
#error DLT_NOTIFY_USER_THRESHOLD_REACHED is already defined
#endif
/** \brief Defines whether support for notify when a threshold is reached in internal buffer. */
#define DLT_NOTIFY_USER_THRESHOLD_REACHED   [!IF "count(as:modconf('Dlt')/DltConfigSet/*/DltLogOutput/*/DltLogChannel/*/DltBufferThresholdForNotification) != 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!]

#if (defined DLT_NUM_SWCS_TO_NOTIFY)
#error DLT_NUM_SWCS_TO_NOTIFY already defined
#endif
/** \brief Number of software components that are configured to be notified in case of log level and trace status changes. */
#define DLT_NUM_SWCS_TO_NOTIFY                [!"num:i($DltNumSwcsToNotify)"!]U

#if (defined DLT_BUFFER_THRSH_SWCS_TO_NOTIFY)
#error DLT_BUFFER_THRSH_SWCS_TO_NOTIFY is already defined
#endif
#define DLT_BUFFER_THRSH_SWCS_TO_NOTIFY       [!"num:i($DltNumOfTHRHReachedNotifications)"!]U

#if (defined DLT_FILTER_MESSAGES)
#error DLT_FILTER_MESSAGES is already defined
#endif
#define DLT_FILTER_MESSAGES                   [!IF "DltMultipleConfigurationContainer/DltMessageFiltering/DltFilterMessages = 'true'"!]DLT_FILTER_MESSAGES_ON[!ELSE!]DLT_FILTER_MESSAGES_OFF[!ENDIF!]

#if (defined DLT_HEADER_PAYLOAD_ENDIANES)
#error DLT_HEADER_PAYLOAD_ENDIANES is already defined
#endif
#define DLT_HEADER_PAYLOAD_ENDIANES           [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderPayloadEndianes = 'LittleEndian'"!]DLT_LITTLE_ENDIAN[!ELSE!]DLT_BIG_ENDIAN[!ENDIF!]

#if (defined DLT_HEADER_USE_ECU_ID)
#error DLT_HEADER_USE_ECU_ID is already defined
#endif
#define DLT_HEADER_USE_ECU_ID                 [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseEcuId = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_HEADER_USE_EXTENDED_HEADER)
#error DLT_HEADER_USE_EXTENDED_HEADER is already defined
#endif
#define DLT_HEADER_USE_EXTENDED_HEADER        [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseExtendedHeader = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_HEADER_USE_SESSION_ID)
#error DLT_HEADER_USE_SESSION_ID is already defined
#endif
#define DLT_HEADER_USE_SESSION_ID             [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseSessionID = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "DltGeneral/DltImplementTimestamp = 'true'"!][!//
#if (defined DLT_HEADER_USE_TIMESTAMP)
#error DLT_HEADER_USE_TIMESTAMP is already defined
#endif
#define DLT_HEADER_USE_TIMESTAMP              [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseTimestamp = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

#if (defined DLT_USE_VERBOSE_MODE)
#error DLT_USE_VERBOSE_MODE is already defined
#endif
#define DLT_USE_VERBOSE_MODE                  [!IF "DltMultipleConfigurationContainer/DltProtocol/DltUseVerboseMode = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "DltMultipleConfigurationContainer/DltProtocol/DltEcuIdChoice = 'Value'"!][!//
#if (defined DLT_ECU_ID)
#error DLT_ECU_ID is already defined
#endif
#define DLT_ECU_ID                            [!"$EcuId"!]
[!ENDIF!][!//

#if (defined DLT_HEADER_PAYLOAD_ENDIANES_BIT)
#error DLT_HEADER_PAYLOAD_ENDIANES_BIT is already defined
#endif
#define DLT_HEADER_PAYLOAD_ENDIANES_BIT       [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderPayloadEndianes = 'BigEndian'"!]0x02[!ELSE!]0x00[!ENDIF!]U

#if (defined DLT_HEADER_CONFIG_ECU_ID_BIT)
#error DLT_HEADER_CONFIG_ECU_ID_BIT is already defined
#endif
#define DLT_HEADER_CONFIG_ECU_ID_BIT          [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseEcuId = 'true'"!]0x04[!ELSE!]0x00[!ENDIF!]U

#if (defined DLT_HEADER_CONFIG_EXTENDED_HEADER_BIT)
#error DLT_HEADER_CONFIG_EXTENDED_HEADER_BIT is already defined
#endif
#define DLT_HEADER_CONFIG_EXTENDED_HEADER_BIT [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseExtendedHeader = 'true'"!]0x01[!ELSE!]0x00[!ENDIF!]U

#if (DLT_IMPLEMENT_TIMESTAMP != STD_OFF)
#if (defined DLT_HEADER_CONFIG_TIMESTAMP_BIT)
#error DLT_HEADER_CONFIG_TIMESTAMP_BIT is already defined
#endif
#define DLT_HEADER_CONFIG_TIMESTAMP_BIT       [!IF "DltMultipleConfigurationContainer/DltProtocol/DltHeaderUseTimestamp = 'true'"!]0x10[!ELSE!]0x00[!ENDIF!]U
#endif

/* !LINKSTO Dlt.RxPath.MessageReception.RxPDU, 1 */
[!IF "node:exists(DltMultipleConfigurationContainer/DltPduConfig/DltRxPduId)"!]
#if (defined DLT_RX_PDU_ID)
#error DLT_RX_PDU_ID is already defined
#endif
#define DLT_RX_PDU_ID                              [!"DltMultipleConfigurationContainer/DltPduConfig/DltRxPduId"!]U

#if (defined DLT_RX_MESSAGE_BUFFER_SIZE)
#error DLT_RX_MESSAGE_BUFFER_SIZE is already defined
#endif
#define DLT_RX_MESSAGE_BUFFER_SIZE                 [!"DltMemory/DltReceptionBufferSize"!]U

#if (defined DLT_RECEPTION_CONTROL_MESSAGES_ENABLED)
#error DLT_RECEPTION_CONTROL_MESSAGES_ENABLED is already defined
#endif
#define DLT_RECEPTION_CONTROL_MESSAGES_ENABLED     STD_ON
[!ELSE!]
#if (defined DLT_RECEPTION_CONTROL_MESSAGES_ENABLED)
#error DLT_RECEPTION_CONTROL_MESSAGES_ENABLED is already defined
#endif
#define DLT_RECEPTION_CONTROL_MESSAGES_ENABLED     STD_OFF
[!ENDIF!]
[!IF "num:i($DltServiceAPI) < $AUTOSAR_431"!][!//
#if (defined DLT_TX_PDU_ID)
#error DLT_TX_PDU_ID is already defined
#endif
#define DLT_TX_PDU_ID                         [!"DltMultipleConfigurationContainer/DltPduConfig/DltTxPduId"!]U
[!ENDIF!]

#if (defined DLT_ENABLE_MULTIPLE_FRAMES)
#error DLT_ENABLE_MULTIPLE_FRAMES is already defined
#endif
#define DLT_ENABLE_MULTIPLE_FRAMES            [!IF "DltMultipleConfigurationContainer/DltPduConfig/DltEnableMultipleFrames = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_DISCARD_MSG_TX_FAIL)
#error DLT_DISCARD_MSG_TX_FAIL is already defined
#endif
/** \brief Defines if DLT messages are discarded or not when transmit
 ** request to PduR return an error. */
/* !LINKSTO Dlt.Transmit.DltDiscardMsgTxFail.Config,1 */
#define DLT_DISCARD_MSG_TX_FAIL            [!IF "DltMultipleConfigurationContainer/DltPduConfig/DltDiscardMsgTxFail = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_TRAFFIC_SHAPER_ENABLED)
#error DLT_TRAFFIC_SHAPER_ENABLED is already defined
#endif
/* !LINKSTO Dlt.TrafficShaper.ParamConfig,1 */
#define DLT_TRAFFIC_SHAPER_ENABLED            [!IF "DltGeneral/DltEnableTrafficShaper = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_MAINFUNCTION_PERIOD)
#error DLT_MAINFUNCTION_PERIOD is already defined
#endif
/* Dlt_MainFunction() period in milliseconds */
#define DLT_MAINFUNCTION_PERIOD               [!"num:i(DltMultipleConfigurationContainer/DltMainFunctionPeriod * 1000)"!]U

#if (defined DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE)
#error DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE is already defined
#endif
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#define DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE        [!IF "DltGeneral/DltTupleEndianness = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE STD_OFF
[!ENDIF!]

[!IF "DltGeneral/DltEnableTrafficShaper = 'true'"!]
#if (defined DLT_BANDWIDTH_FOR_COM_MODULE)
#error DLT_BANDWIDTH_FOR_COM_MODULE is already defined
#endif
/* !LINKSTO Dlt.TrafficShaping.ComModule,1 */
/* Convert kbits/s into bytes/s */
#define DLT_BANDWIDTH_FOR_COM_MODULE          [!"num:i((DltMultipleConfigurationContainer/DltBandwidth/DltBandwidthForComModule * 1000) div 8)"!]U

#if (defined DLT_TIME_PERIOD_TRAFFIC_SHAPING)
#error DLT_TIME_PERIOD_TRAFFIC_SHAPING is already defined
#endif
/* Traffic shaping integration window in milliseconds */
#define DLT_TIME_PERIOD_TRAFFIC_SHAPING       [!"num:i(DltMultipleConfigurationContainer/DltBandwidth/DltTimePeriodTrafficShaping * 1000)"!]U

#if (defined DLT_BYTES_PER_MILLISECOND)
#error DLT_BYTES_PER_MILLISECOND is already defined
#endif
/* This is the maximum number of bytes per milliseconds */
#define DLT_BYTES_PER_MILLISECOND             (Dlt_BandwidthForComModule / 1000U)

#if (defined DLT_INTEGRATION_WINDOW)
#error DLT_INTEGRATION_WINDOW is already defined
#endif
/* How many Dlt_MainFunction() calls correspond to the integration window */
/* !LINKSTO Dlt.swdd.Dlt_MainFunction.IntegrationWindow.Calculate,1, Dlt.ASR421.SWS_Dlt_00056,1 */
#define DLT_INTEGRATION_WINDOW                (DLT_TIME_PERIOD_TRAFFIC_SHAPING / DLT_MAINFUNCTION_PERIOD)

#if (defined DLT_MAXIMUM_NUMBER_OF_BYTES)
#error DLT_MAXIMUM_NUMBER_OF_BYTES is already defined
#endif
/* The maximum number of bytes allowed in the integration window */
/* !LINKSTO Dlt.swdd.MaxNoOfBytesTransmittedWithinWindow,1 */
#define DLT_MAXIMUM_NUMBER_OF_BYTES           ((Dlt_BandwidthForComModule * DLT_TIME_PERIOD_TRAFFIC_SHAPING) / 1000U)

#if (defined DLT_BYTES_PER_MAINFUNCTION)
#error DLT_BYTES_PER_MAINFUNCTION is already defined
#endif
/* How many bytes are transmitted in one Dlt_MainFunction() call at maximum bandwidth */
/* !LINKSTO Dlt.swdd.BytesTransmittedPerMainFunction,1 */
#define DLT_BYTES_PER_MAINFUNCTION            ((Dlt_BandwidthForComModule * DLT_MAINFUNCTION_PERIOD) / 1000U)

[!ELSE!]
#if (defined DLT_BANDWIDTH_FOR_COM_MODULE)
#error DLT_BANDWIDTH_FOR_COM_MODULE is already defined
#endif
#define DLT_BANDWIDTH_FOR_COM_MODULE           0U
[!ENDIF!]

#if (defined DLT_STARTUP_DELAY_TIMER)
#error DLT_STARTUP_DELAY_TIMER is already defined
#endif
/* Delay for starting the transmission of messages after the Dlt module has been initialized. In milliseconds */
[!IF "node:exists(DltGeneral/DltGeneralStartUpDelayTimer)"!]
#define DLT_STARTUP_DELAY_TIMER [!"num:i(DltGeneral/DltGeneralStartUpDelayTimer * 1000)"!]U
[!ELSE!]
#define DLT_STARTUP_DELAY_TIMER 0U
[!ENDIF!]

#if (defined DLT_ENABLE_BSW_DISTRIBUTION)
#error DLT_ENABLE_BSW_DISTRIBUTION is already defined
#endif
/* Switch indicating whether support for basic software distribuiton (multi-core support) is enabled or disabled */
#define DLT_ENABLE_BSW_DISTRIBUTION           [!IF "(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_NUMBER_OF_SATELLITES)
#error DLT_NUMBER_OF_SATELLITES is already defined
#endif
/* Value indicating the number of configured satellite cores (slave cores).
   If multicore support is disabled the number of slave cores shall be 0U.
   If basic software distribution is enabled, the number of cores shall be configurable. */
#define DLT_NUMBER_OF_SATELLITES              [!IF "(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!][!"DltMultipleConfigurationContainer/DltBswDistribution/DltNumberOfSatellites"!]U[!ELSE!]0U[!ENDIF!]

#if (defined DLT_MASTER_CORE)
#error DLT_MASTER_CORE is already defined
#endif
/* Value indicating the CoreId of the selected master core. */
#define DLT_MASTER_CORE                       [!IF "(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!][!"node:ref(DltMultipleConfigurationContainer/DltBswDistribution/DltMasterCore)/OsCoreId"!]U[!ELSE!]0U[!ENDIF!]

[!IF "DltGeneral/DltImplementNVRamStorage = 'true'"!]
  [!VAR "GeneralBlockIdRef" = "as:ref(./DltMultipleConfigurationContainer/DltNvRamBlockRef)/NvMNvramBlockIdentifier"!]
  [!VAR "GeneralBlockIdLength" = "as:ref(./DltMultipleConfigurationContainer/DltNvRamBlockRef)/NvMNvBlockLength "!]
#if (defined DLT_STORE_NATIVE_NVRAM_BLOCK_ID)
#error DLT_STORE_NATIVE_NVRAM_BLOCK_ID is already defined.
#endif
/** \brief The NvM block ID used to store runtime variables for Dlt module */
#define DLT_STORE_NATIVE_NVRAM_BLOCK_ID   [!"$GeneralBlockIdRef"!]U

#if (defined DLT_STORE_NATIVE_NVRAM_BLOCK_LENGTH)
#error DLT_STORE_NATIVE_NVRAM_BLOCK_LENGTH already defined
#endif
/** \brief The length of the NvM block used to store the runtime variables for Dlt module */
#define DLT_STORE_NATIVE_NVRAM_BLOCK_LENGTH   [!"$GeneralBlockIdLength"!]U
[!ENDIF!]

[!IF "DltGeneral/DltImplementNVRamStorage = 'true'"!]
  [!VAR "DataSetBlockIdRef" = "as:ref(./DltMultipleConfigurationContainer/DltNvRamDataSetBlockRef)/NvMNvramBlockIdentifier"!]
  [!VAR "DataSetBlockIdLength" = "as:ref(./DltMultipleConfigurationContainer/DltNvRamDataSetBlockRef)/NvMNvBlockLength "!]
#if (defined DLT_STORE_DATASET_NVRAM_BLOCK_ID)
#error DLT_STORE_DATASET_NVRAM_BLOCK_ID is already defined.
#endif
/** \brief The NvM block ID used to store information related to a registered pair of
 **        ApplicationId and ContextId for Dlt module
 **/
#define DLT_STORE_DATASET_NVRAM_BLOCK_ID   [!"$DataSetBlockIdRef"!]U

#if (defined DLT_STORE_DATASET_NVRAM_BLOCK_LENGTH)
#error DLT_STORE_DATASET_NVRAM_BLOCK_LENGTH is already defined.
#endif
/** \brief The length of the NvM block used to store information related to
 **        a pair of ApplicationID and ContextID for Dlt module.
 **/
#define DLT_STORE_DATASET_NVRAM_BLOCK_LENGTH   [!"$DataSetBlockIdLength"!]U
[!ENDIF!]
[!IF "DltGeneral/DltImplementNVRamStorage = 'true'"!]
  [!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
    [!VAR "DataSetBlockNumber" = "num:i(count(DltSwc/*/DltSwcContext/*))"!]
  [!ELSE!]
    [!VAR "DataSetBlockNumber" = "num:integer(number(DltMemory/DltMaxCountContextIds))"!]
  [!ENDIF!]
#if (defined DLT_STORE_DATASET_NVRAM_BLOCK_NUMBER)
#error DLT_STORE_DATASET_NVRAM_BLOCK_NUMBER is already defined.
#endif
/** \brief The NvM total number of data set block used to store information related to
 **        a pair of ApplicationID and ContextID for Dlt module.
 ** Note: the maximum number of dataset has to fulfill two requirements:
 **       1. It cannot be smaller than the total number of ApplicationID and ContextId
 **          which can be registered. Therefore in the current implementation the number
 **          of dataset is equal to the maximum number of pairs which can be registered.
 **       2. The range of data set NvM block index:
 **          0x00...(2^NvMDatasetSelectionBits-1)
 ** In the current implementation there are no checks performed for
 **/
#define DLT_STORE_DATASET_NVRAM_BLOCK_NUMBER   ([!"$DataSetBlockNumber"!]U + DLT_VFB_CONTEXT_COUNT)
[!ENDIF!]
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#if (defined DLT_SWC_REGISTERED_NO)
#error DLT_SWC_REGISTERED_NO is already defined.
#endif
/** \brief Current no. of registered SW-Cs */
[!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace)) and (as:modconf('Dlt')/DltGeneral/DltDetForwardErrorTrace = 'true')"!][!//
#define DLT_SWC_REGISTERED_NO                  [!IF "(num:i($VfbTraceFunctionCount) > 0)"!][!"num:i(count(DltSwc/*) + 2)"!]U[!ELSE!][!"num:i(count(DltSwc/*) + 1)"!]U[!ENDIF!]
[!ELSE!][!//
#define DLT_SWC_REGISTERED_NO                  [!IF "(num:i($VfbTraceFunctionCount) > 0)"!][!"num:i(count(DltSwc/*) + 1)"!]U[!ELSE!][!"num:i(count(DltSwc/*))"!]U[!ENDIF!]
[!ENDIF!][!//
  [!VAR "TotalNoOfRegCtxt" = "0"!]
  [!LOOP "DltSwc/*"!]
#if (defined DLT_NO_OF_REG_CTX_[!"node:name(.)"!])
#error DLT_NO_OF_REG_CTX_[!"node:name(.)"!] is already defined.
#endif
/** \brief Current no of registered context on [!"node:name(.)"!] */
#define DLT_NO_OF_REG_CTX_[!"node:name(.)"!]  [!"num:i(count(DltSwcContext/*))"!]U
    [!VAR "TotalNoOfRegCtxt" = "$TotalNoOfRegCtxt + num:i(count(DltSwcContext/*))"!]
  [!ENDLOOP!]

  [!IF "node:refvalid(./DltConfigSet/*[1]/DltLogOutput/*[1]/DltDefaultLogChannelRef) and node:exists(as:ref(./DltConfigSet/*[1]/DltLogOutput/*[1]/DltDefaultLogChannelRef)/DltLogChannelId)"!]
    [!VAR "defaultlogChn" = "num:i(node:pos(node:ref(./DltConfigSet/*[1]/DltLogOutput/*[1]/DltDefaultLogChannelRef)))"!]
#if (defined DEFAULT_LOG_CHN_IDX)
#error DEFAULT_LOG_CHN_IDX is already defined.
#endif
/** \brief Current default log channel configured for the transmission in case of a send log / send trace message */
#define DEFAULT_LOG_CHN_IDX [!"$defaultlogChn"!]U
  [!ENDIF!]
#if (defined DLT_TXPDU_NO)
#error DLT_TXPDU_NO is already defined.
#endif
 /** \brief Current no of configured log channels */
#define DLT_TXPDU_NO [!"num:i(count(DltConfigSet/*/DltLogOutput/*/DltLogChannel/*))"!]U
[!ELSE!]
#if (defined DLT_TXPDU_NO)
#error DLT_TXPDU_NO is already defined.
#endif
 /** \brief Current no of configured log channels */
#define DLT_TXPDU_NO  1U
[!ENDIF!]

#if (defined DLT_GETSOFTWAREVERSION_CONTROL_MESSAGE)
#error DLT_GETSOFTWAREVERSION_CONTROL_MESSAGE is already defined.
#endif
 /** \brief Macro for enabling/disabling the GetSoftwareVersion control message */
[!IF "DltMultipleConfigurationContainer/DltProtocol/DltGetSoftwareVersion = 'true'"!]
#define DLT_GETSOFTWAREVERSION_CONTROL_MESSAGE     STD_ON

#if (defined DLT_GETSOFTWAREVERSION_LENGTH)
#error DLT_GETSOFTWAREVERSION_LENGTH is already defined.
#endif
 /** \brief The length of the ECU software version string in bytes */
#define DLT_GETSOFTWAREVERSION_LENGTH   [!"DltMultipleConfigurationContainer/DltProtocol/DltGetSoftwareVersionLength"!]U
[!ELSE!]
#define DLT_GETSOFTWAREVERSION_CONTROL_MESSAGE     STD_OFF
[!ENDIF!]

#if (defined DLT_GETECUID_AT_RUNTIME)
#error DLT_GETECUID_AT_RUNTIME is already defined.
#endif
 /** \brief Macro to enable/disable the retrieval of the EcuId at run-time */
[!IF "DltMultipleConfigurationContainer/DltProtocol/DltEcuIdChoice = 'Callout'"!][!//
#define DLT_GETECUID_AT_RUNTIME               STD_ON
[!ELSE!]
#define DLT_GETECUID_AT_RUNTIME               STD_OFF
[!ENDIF!]

/*==================[type definitions]======================================*/

/*------------------[Dlt_ConfigType]----------------------------------------*/
/* !LINKSTO Dlt.SWS_Dlt_00437,1 */
/** \brief This type of the external data structure shall contain the post
 **  build initialization data for the Dlt.
 **
 ** \note Type is unused, as only pre-compile time support is implemented. */
typedef uint8 Dlt_ConfigType;

/** \brief Type that represents the length of a Dlt message */
#ifndef RTE_TYPE_Dlt_MsgLengthType
#define RTE_TYPE_Dlt_MsgLengthType
/* !LINKSTO Dlt.ASR421.SWS_Dlt_00320, 1 */
typedef PduLengthType Dlt_MsgLengthType;
#endif

[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
/* !LINKSTO Dlt.SWS_Dlt_00232,1 */
/** \brief This type describes the LogChannel name. */
#ifndef RTE_TYPE_Dlt_LogChannelNameType
#define RTE_TYPE_Dlt_LogChannelNameType
typedef uint8 Dlt_LogChannelNameType[4U];
#endif

/* !LINKSTO Dlt.LogChannelNameArrayType, 1 */
/** \brief This type describes the list of log channel names */
#ifndef RTE_TYPE_Dlt_LogChannelNameArrayType
#define RTE_TYPE_Dlt_LogChannelNameArrayType
typedef Dlt_LogChannelNameType Dlt_LogChannelNameArrayType[DLT_TXPDU_NO];
#endif

/** \brief This type for ApplicationId/ContextId tuple. */
typedef struct{
[!IF "(num:i($DltServiceAPI) != $AUTOSAR_22_11) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
  uint8 DltSwCApplicationId[DLT_APPID_LENGTH];
  uint8 DltSwCContextId[DLT_CTXID_LENGTH];
[!ELSE!][!//
  uint32 DltSwCApplicationId;
  uint32 DltSwCContextId;
[!ENDIF!][!//
}Dlt_AppCtxTupleType;

#ifndef RTE_TYPE_AppCtxDesc
#define RTE_TYPE_AppCtxDesc
 /** \brief Typedef for application/context description accepted size */
typedef uint8 AppCtxDesc[DLT_APPCTX_DESC_LEN];
#endif

 /** \brief This type for Application description length.
  ** AppDesc: Application description
  ** AppDescLen: Application description length */
#ifndef RTE_TYPE_Dlt_AppDescType
#define RTE_TYPE_Dlt_AppDescType
typedef struct{
  AppCtxDesc AppDesc;
  uint8 AppDescLen;
} Dlt_AppDescType;
#endif

/** \brief This type describes the LogChannel information.
 ** DltLogChannelBufferOverflowTimer: Cycle time in seconds for resetting
 **                                   the buffer overflow flag in case a
 **                                   buffer overflow occurred.
 ** DltLogChannelTransmitCycle: Specifies the cycle time in seconds of the
 **                             transmit functionality of this log channel.
 ** DltLogChannelTrafficShapingBandwidth: Set the maximum possible bandwidth in bit/s.
 ** DltLogChannelBufferSize : Buffer size in bytes for the LogChannel specific message buffer.
 ** DltMessageTxBuffer: Address for the transmission buffer
 ** DltLogChannelMaxMessageLength: The maximum length of a Dlt log or trace message
 ** DltITxPduHandleId: Pdu Tx Handle Id for a specific log channel
 ** DltLogChannelId: This is the 4 ASCII character long name of the log channel
 ** DltLogChannelMaxNumOfRetries: The maximum length of a Dlt log or trace message. */
typedef struct{
  uint32  DltLogChannelBufferOverflowTimer;
  uint32  DltLogChannelTransmitCycle;
  uint32  DltLogChannelTrafficShapingBandwidth;
  uint32  DltLogChannelBufferSize;
  uint8 * DltMessageTxBuffer;
  Dlt_MsgLengthType DltLogChannelMaxMessageLength;
  PduIdType DltITxPduHandleId;
  Dlt_LogChannelNameType  DltLogChannelId;
  uint8   DltLogChannelMaxNumOfRetries;
}Dlt_LogChannelType;

/** \brief This type describes the Threshold information for log channels.
 ** DltLogChannelThreshold: LogLevel Threshold for a specific Channel
 ** DltLogTraceStatusFlag: Parameter to turn on/off trace for this channel completely */
typedef struct{
  uint8  DltLogChannelThreshold;
  boolean DltLogTraceStatusFlag;
}Dlt_LogChannelThresholdInfoType;

/** \brief This type describes SW context info for SW-C.
 ** Dlt_AppCtxTuple: Information regarding the ApplcationId/ContextId tuple
 ** DltLoglevel: Specific log level for the tuple
 ** DltLogChannelIdx: boolean status for each channel that
 **                   indicates whether the channel is assigned
 **                   or not to the context
 ** DltTraceStatus: Specific trace status for the tuple */
typedef struct{
  Dlt_AppCtxTupleType Dlt_AppCtxTuple;
  /* Log level for log messages */
  uint8 DltLoglevel;
  boolean  DltLogChannelIdx[DLT_TXPDU_NO];
  /* Trace status for trace messages */
  boolean DltTraceStatus;
}Dlt_SwCContextType;

/** \brief This type describes Log info for SW-C.
** DltSwCSessionId:          An ECU wide unique ID to identify the port a SWC (instance) uses
** MaxSwCLogMessageLength:   Defines the maximum allowed length (Dlt_MsgLengthType) for LogMessages.
** MaxSwCTraceMessageLength: Defines the maximum allowed length (Dlt_MsgLengthType) for TraceMessages.
** SwCCtxRef:                address of the SwContext info variable
** DltSwCSupportLogLevelChangeNotification: Flag indicating, whether Dlt has to
**                                          provide a R-Port for the notification
**                                          of the SWC about LogLevel changes */
typedef struct{
  uint32 DltSwCSessionId;
  Dlt_MsgLengthType MaxSwCLogMessageLength;
  Dlt_MsgLengthType MaxSwCTraceMessageLength;
  boolean DltSwCSupportLogLevelChangeNotification;
}Dlt_SwCLogType;

/** \brief This type describes how many contexts ids are registered per application id.
** DltSwCApplicationId : Application id
** CtxtNo : No of contexts registered per application*/
typedef struct{
[!IF "(num:i($DltServiceAPI) != $AUTOSAR_22_11) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
[!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)"!][!//
  uint8 DltSwCApplicationId[[!"as:modconf('Dlt')/DltGeneral/DltApplicationIdLength"!]];
[!ELSE!][!//
  uint8 DltSwCApplicationId[4U];
[!ENDIF!][!//
[!ELSE!][!//
  uint32  DltSwCApplicationId;
[!ENDIF!][!//
  uint32  CtxtNo;
}Dlt_CtxtPerApplType;
[!ENDIF!][!//

[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
[!IF "count(DltConfigSet/*/DltLogOutput/*/DltLogChannel/*/DltBufferThresholdForNotification) != 0"!][!//
/** \brief Function pointer type for UserCalloutThresholdReached function */
typedef struct
{
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, UserCalloutThresholdReached)(P2CONST(uint8, AUTOMATIC, DLT_APPL_DATA) logChannelName);
} Dlt_UserThresholdReachedType;
[!ENDIF!][!//
[!ENDIF!][!//

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define DLT_START_SEC_CONST_8
#include <Dlt_MemMap.h>

extern CONST(Dlt_ConfigType, DLT_CONST) Dlt_ConfigSet_0;

#define DLT_STOP_SEC_CONST_8
#include <Dlt_MemMap.h>

[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#define DLT_START_SEC_VAR_INIT_UNSPECIFIED
#include <Dlt_MemMap.h>

[!IF "(node:exists(DltSwc/*)) and (num:i(count(DltSwc/*)) > 0)"!][!//
extern P2CONST(Dlt_SwCContextType, AUTOMATIC, DLT_APPL_DATA) DltSwCContextInfoPtr[DLT_SWC_REGISTERED_NO];
[!ENDIF!][!//
extern VAR(Dlt_CtxtPerApplType, DLT_VAR) Dlt_MaxCtxtPerApplication[MAX_APP_NO];

#define DLT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Dlt_MemMap.h>

#define DLT_START_SEC_CONST_32
#include <Dlt_MemMap.h>

[!IF "count(as:modconf('Dlt')/DltConfigSet/*/DltLogOutput/*/DltLogChannel/*/DltBufferThresholdForNotification) > 0"!]
extern CONST(uint32, DLT_CONST) Dlt_CfgLogChannelThreshold[DLT_TXPDU_NO];
[!ENDIF!]

#define DLT_STOP_SEC_CONST_32
#include <Dlt_MemMap.h>

#define DLT_START_SEC_CONST_8
#include <Dlt_MemMap.h>

[!IF "num:i(count(DltSwc/*)) > 0"!][!//
extern CONST(uint8, DLT_CONST) Dlt_MaxCtxAppIdPerSwC[DLT_SWC_REGISTERED_NO];
[!ENDIF!][!//
extern CONST(Dlt_LogChannelThresholdInfoType, DLT_CONST) Dlt_CfgLogChannelThresholdInfo[DLT_TXPDU_NO];

#define DLT_STOP_SEC_CONST_8
#include <Dlt_MemMap.h>


#define DLT_START_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>

extern CONST(Dlt_LogChannelType, DLT_CONST) Dlt_CfgLogChannel[DLT_TXPDU_NO];
[!IF "num:i(count(DltSwc/*)) > 0"!][!//
extern CONST(Dlt_SwCLogType, DLT_CONST) Dlt_SwCLogInfo[DLT_SWC_REGISTERED_NO];
[!ENDIF!][!//

#define DLT_STOP_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>

[!ENDIF!][!//

#define DLT_START_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>

[!IF "count(DltConfigSet/*/DltLogOutput/*/DltLogChannel/*/DltBufferThresholdForNotification) != 0"!][!//
extern CONST(Dlt_UserThresholdReachedType, DLT_CONST) Dlt_ThresholdReachedNotification[DLT_BUFFER_THRSH_SWCS_TO_NOTIFY];
[!ENDIF!]

#define DLT_STOP_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>
/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef DLT_CFG_H */
/*==================[end of file]===========================================*/
