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
#ifndef DLT_INT_H
#define DLT_INT_H

/* This file contains or includes all internal identifiers of
 * the AUTOSAR module Dlt. */

/*==================[inclusions]============================================*/

#include <Dlt_Int_Cfg.h>
#include <Dlt_Cfg.h>

#if (DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL == TS_PROD_ERR_REP_TO_DEM)
#include <Dem.h>
#endif
#if ((DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL == TS_PROD_ERR_REP_TO_DET) || (DLT_DEV_ERROR_DETECT == STD_ON) || (DLT_DET_RUNTIME_CHECKS == STD_ON))
#include <Det.h>
#endif

#if (DLT_IMPLEMENT_NV_RAM_STORAGE ==  STD_ON)
#include <NvM.h> /* NvM API */
#endif

#if (DLT_IMPLEMENT_TIMESTAMP == STBM_TIMESTAMP)
#include <StbM.h>
#endif /* DLT_IMPLEMENT_TIMESTAMP == STBM_TIMESTAMP */

/*==================[macros]================================================*/
#if (defined DLT_SESSIONID_SIZE)
#error DLT_SESSIONID_SIZE already defined
#endif
/** \brief Macro to define session id size */
#define DLT_SESSIONID_SIZE        0x04U

#if(defined DLT_SESSION_ID_NULL)
#error DLT_SESSION_ID_NULL already defined
#endif
/** \brief Macro to define a session ID of NULL value */
#define DLT_SESSION_ID_NULL        0x00U

#if (defined DLT_VERBOSE_MODE_ON)
#error DLT_VERBOSE_MODE_ON already defined
#endif
/** \brief Macro to define verbose mode ON */
#define DLT_VERBOSE_MODE_ON        0x01U

#if (defined DLT_VERBOSE_MODE_OFF)
#error DLT_VERBOSE_MODE_OFF already defined
#endif
/** \brief Macro to define verbose mode OFF */
#define DLT_VERBOSE_MODE_OFF        0x00U

#if (defined DLT_STORED_DATA_UPDATED)
#error DLT_STORED_DATA_UPDATED already defined
#endif
/** \brief State of stored data into Nv memory */
#define DLT_STORED_DATA_UPDATED        0x01U

#if (defined DLT_NVM_APPID_INDEX)
#error DLT_NVM_APPID_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_APPID_INDEX          0x00U

#if (defined DLT_NVM_CTXID_INDEX)
#error DLT_NVM_CTXID_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ContextId information in the selected data set
 ** index */
#define DLT_NVM_CTXID_INDEX          DLT_APPID_LENGTH

#if (defined DLT_NVM_LOGLEVEL_INDEX)
#error DLT_NVM_LOGLEVEL_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the log level of the current AppId and ContextId pair
 ** in the selected data set index */
#define DLT_NVM_LOGLEVEL_INDEX          (DLT_NVM_CTXID_INDEX + DLT_CTXID_LENGTH)

#if (defined DLT_NVM_TRACESTATUS_INDEX)
#error DLT_NVM_TRACESTATUS_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the trace status of the current AppId and ContextId
 ** pair in the selected data set index */
#define DLT_NVM_TRACESTATUS_INDEX       (DLT_NVM_LOGLEVEL_INDEX + 1U)

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)

#if (defined APPCTXT_NO_DESCRIPTION)
#error APPCTXT_NO_DESCRIPTION already defined
#endif
#define APPCTXT_NO_DESCRIPTION       0x00U

#endif

#if (defined DLT_SWC_SESSION_REGISTERED)
#error DLT_SWC_SESSION_REGISTERED already defined
#endif

#if (DLT_INCLUDE_RTE == STD_OFF) || (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)
#if (defined DLT_NUM_SESSION_IDS)
#error DLT_NUM_SESSION_IDS already defined
#endif
/** \brief When DltServiceAPI == AUTOSAR_431 or DltServiceAPI == AUTOSAR_20_11, the Dlt_SessionMapping.h file
  *        does not exist to provide this macro's definition. */
#define DLT_NUM_SESSION_IDS              0U
#endif

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)
/** \brief Registered sessions */
#define DLT_SWC_SESSION_REGISTERED       DLT_SWC_REGISTERED_NO
#else
/** \brief Registered sessions */
#define DLT_SWC_SESSION_REGISTERED       DLT_NUM_SESSION_IDS
#endif

#if (defined DLT_NVM_SESSIONID_INDEX)
#error DLT_NVM_SESSIONID_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the sessionID of the current AppId and ContextId
 ** pair in the selected data set index */
#define DLT_NVM_SESSIONID_INDEX (DLT_NVM_TRACESTATUS_INDEX + 1U)

#if (defined DLT_NVM_UPDATE_INDEX)
#error DLT_NVM_UPDATE_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the updated state of current AppId and ContextId pair
 ** written in the selected data set index */
#define DLT_NVM_UPDATE_INDEX            DLT_NVM_SESSIONID_INDEX + DLT_SESSIONID_SIZE

#if (defined DLT_NVM_VERBOSEMODE_INDEX)
#error DLT_NVM_VERBOSEMODE_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the verbose mode of the current AppId and ContextId pair
 ** in the selected data set index */
#define DLT_NVM_VERBOSEMODE_INDEX       DLT_NVM_UPDATE_INDEX + 1U

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)

#if (defined DLT_NVM_CHANNEL_NAME_INDEX)
#error DLT_NVM_CHANNEL_NAME_INDEX already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the trace status of the current AppId and ContextId
 ** pair in the selected data set index */
#define DLT_NVM_CHANNEL_NAME_INDEX       (DLT_NVM_VERBOSEMODE_INDEX + 1U)
#endif

#if (defined DLT_NVM_DEFAULT_SESSIONID)
#error DLT_NVM_DEFAULT_SESSIONID already defined
#endif
/** \brief Default value for session ID when restoring the
 ** data from  persistent storage
 */
#define DLT_NVM_DEFAULT_SESSIONID      0x00U

#if (defined DLT_NVM_FILTER_MSG_NATIVE_IDX)
#error DLT_NVM_FILTER_MSG_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltFilterMessage runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_FILTER_MSG_NATIVE_IDX                    0x00U

#if (defined DLT_NVM_DEFAULT_MAX_LOG_LEVEL_NATIVE_IDX)
#error DLT_NVM_DEFAULT_MAX_LOG_LEVEL_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltDefaultMaxLogLevel runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_DEFAULT_MAX_LOG_LEVEL_NATIVE_IDX         0x01U

#if (defined DLT_NVM_HDR_USE_TIMESTAMP_NATIVE_IDX)
#error DLT_NVM_HDR_USE_TIMESTAMP_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltHeaderUseTimestamp runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_HDR_USE_TIMESTAMP_NATIVE_IDX             0x02U


#if (defined DLT_NVM_HDR_USE_EXTENDEDHDR_NATIVE_IDX)
#error DLT_NVM_HDR_USE_EXTENDEDHDR_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltHeaderUseExtendedHeader runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_HDR_USE_EXTENDEDHDR_NATIVE_IDX           0x04U

#if (DLT_PROTOCOL_VERSION == 2U)

#if (defined DLT_NVM_HDR_USE_ECUID_NATIVE_IDX)
#error DLT_NVM_HDR_USE_ECUID_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltHeaderUseEcuId runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_HDR_USE_ECUID_NATIVE_IDX                 0x02U

#if (defined DLT_NVM_HDR_USE_SESSIONID_NATIVE_IDX)
#error DLT_NVM_HDR_USE_SESSIONID_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltHeaderUseSessionId runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_HDR_USE_SESSIONID_NATIVE_IDX             0x03U

#if (defined DLT_NVM_HDR_USE_VERBOSEMODE_NATIVE_IDX)
#error DLT_NVM_HDR_USE_VERBOSEMODE_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_HeaderUseVerboseMode
 **
 **/
#define DLT_NVM_HDR_USE_VERBOSEMODE_NATIVE_IDX             0x04U

#if (defined DLT_NVM_BANDWIDTH_DIAGCH_NATIVE_IDX)
#error DLT_NVM_BANDWIDTH_DIAGCH_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_BandwidthForDiagChannel
 **
 ** This preprocessor macro belongs to a runtime variable which is not supported by the
 ** current implementation. It is available for completeness reasons only.
 **/
#define DLT_NVM_BANDWIDTH_DIAGCH_NATIVE_IDX               0x05U

#if (defined DLT_NVM_BANDWIDTH_COM_NATIVE_IDX)
#error DLT_NVM_BANDWIDTH_COM_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_BandwidthForComModule
 **
 ** This preprocessor macro belongs to a runtime variable which is not supported by the
 ** current implementation. It is available for completeness reasons only.
 **/
#define DLT_NVM_BANDWIDTH_COM_NATIVE_IDX                   0x06U

#if (defined DLT_NVM_VFB_TRACELOGLEVEL_NATIVE_IDX)
#error DLT_NVM_VFB_TRACELOGLEVEL_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_VfbTraceLogLevel
 **
 ** This preprocessor macro belongs to a runtime variable which is not supported by the
 ** current implementation. It is available for completeness reasons only.
 **/
#define DLT_NVM_VFB_TRACELOGLEVEL_NATIVE_IDX                0x0AU

#if (defined DLT_NVM_DEFAULT_TRACE_STATUS_NATIVE_IDX)
#error DLT_NVM_DEFAULT_TRACE_STATUS_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltDefaultTraceStatus runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_DEFAULT_TRACE_STATUS_NATIVE_IDX          0x0BU

#if (defined DLT_NVM_GLOBAL_LOG_STATUS_NATIVE_IDX)
#error DLT_NVM_GLOBAL_LOG_STATUS_NATIVE_IDX already defined
#endif
/** \brief Internal index for Dlt_GlobalLogStatus runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_GLOBAL_LOG_STATUS_NATIVE_IDX             0x0CU

#if (defined DLT_NVM_LOG_CHANNELS_TRACE_NATIVE_IDX)
#error DLT_NVM_LOG_CHANNELS_TRACE_NATIVE_IDX already defined
#endif
/** \brief Internal index for Dlt Threshold value and status runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_LOG_CHANNELS_TRACE_NATIVE_IDX             0x0DU

#else /* DLT_PROTOCOL_VERSION == 1U */

#if (defined DLT_NVM_HDR_USE_ECUID_NATIVE_IDX)
#error DLT_NVM_HDR_USE_ECUID_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltHeaderUseEcuId runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_HDR_USE_ECUID_NATIVE_IDX                 0x03U

#if (defined DLT_NVM_HDR_USE_SESSIONID_NATIVE_IDX)
#error DLT_NVM_HDR_USE_SESSIONID_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltHeaderUseSessionId runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_HDR_USE_SESSIONID_NATIVE_IDX             0x05U

#if (defined DLT_NVM_HDR_USE_VERBOSEMODE_NATIVE_IDX)
#error DLT_NVM_HDR_USE_VERBOSEMODE_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_HeaderUseVerboseMode
 **
 **/
#define DLT_NVM_HDR_USE_VERBOSEMODE_NATIVE_IDX             0x06U

#if (defined DLT_NVM_BANDWIDTH_DIAGCH_NATIVE_IDX)
#error DLT_NVM_BANDWIDTH_DIAGCH_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_BandwidthForDiagChannel
 **
 ** This preprocessor macro belongs to a runtime variable which is not supported by the
 ** current implementation. It is available for completeness reasons only.
 **/
#define DLT_NVM_BANDWIDTH_DIAGCH_NATIVE_IDX               0x07U

#if (defined DLT_NVM_BANDWIDTH_COM_NATIVE_IDX)
#error DLT_NVM_BANDWIDTH_COM_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_BandwidthForComModule
 **
 ** This preprocessor macro belongs to a runtime variable which is not supported by the
 ** current implementation. It is available for completeness reasons only.
 **/
#define DLT_NVM_BANDWIDTH_COM_NATIVE_IDX                   0x08U

#if (defined DLT_NVM_VFB_TRACELOGLEVEL_NATIVE_IDX)
#error DLT_NVM_VFB_TRACELOGLEVEL_NATIVE_IDX already defined
#endif
/** \brief Internal index for runtime variable Dlt_VfbTraceLogLevel
 **
 ** This preprocessor macro belongs to a runtime variable which is not supported by the
 ** current implementation. It is available for completeness reasons only.
 **/
#define DLT_NVM_VFB_TRACELOGLEVEL_NATIVE_IDX                0x0CU

#if (defined DLT_NVM_DEFAULT_TRACE_STATUS_NATIVE_IDX)
#error DLT_NVM_DEFAULT_TRACE_STATUS_NATIVE_IDX already defined
#endif
/** \brief Internal index for DltDefaultTraceStatus runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_DEFAULT_TRACE_STATUS_NATIVE_IDX          0x0DU

#if (defined DLT_NVM_GLOBAL_LOG_STATUS_NATIVE_IDX)
#error DLT_NVM_GLOBAL_LOG_STATUS_NATIVE_IDX already defined
#endif
/** \brief Internal index for Dlt_GlobalLogStatus runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_GLOBAL_LOG_STATUS_NATIVE_IDX             0x0EU

#if (defined DLT_NVM_LOG_CHANNELS_TRACE_NATIVE_IDX)
#error DLT_NVM_LOG_CHANNELS_TRACE_NATIVE_IDX already defined
#endif
/** \brief Internal index for Dlt Threshold value and status runtime variable in
 ** native NvM block used for store/restore request */
#define DLT_NVM_LOG_CHANNELS_TRACE_NATIVE_IDX             0x0FU
#endif


/* functional macros */
#if (defined DLT_NVM_READ_BLOCK_API_ID)
#error DLT_NVM_READ_BLOCK_API_ID already defined
#endif
/** \brief Defines API ID of function NvM_ReadBlock() */
#define DLT_NVM_READ_BLOCK_API_ID                        0x06U

#if (defined DLT_NVM_WRITE_BLOCK_API_ID)
#error DLT_NVM_WRITE_BLOCK_API_ID already defined
#endif
/** \brief Defines API ID of function NvM_WriteBlock() */
#define DLT_NVM_WRITE_BLOCK_API_ID                       0x07U

#if (defined DLT_NVM_APPID_B1)
#error DLT_NVM_APPID_B1 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_APPID_B1                                 0x00U

#if (defined DLT_NVM_APPID_B2)
#error DLT_NVM_APPID_B2 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_APPID_B2                                0x01U

#if (defined DLT_NVM_APPID_B3)
#error DLT_NVM_APPID_B3 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_APPID_B3                                0x02U

#if (defined DLT_NVM_APPID_B4)
#error DLT_NVM_APPID_B4 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_APPID_B4                                0x03U

#if (defined DLT_NVM_CTXID_B1)
#error DLT_NVM_CTXID_B1 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_CTXID_B1                                 0x04U

#if (defined DLT_NVM_CTXID_B2)
#error DLT_NVM_CTXID_B2 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_CTXID_B2                                0x05U

#if (defined DLT_NVM_CTXID_B3)
#error DLT_NVM_CTXID_B3 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_CTXID_B3                                0x06U

#if (defined DLT_NVM_CTXID_B4)
#error DLT_NVM_CTXID_B4 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the ApplicationId information in the selected data set
 ** index */
#define DLT_NVM_CTXID_B4                                0x07U

#if (defined DLT_NVM_SESID_B1)
#error DLT_NVM_SESID_B1 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the SessionID information in the selected data set
 ** index */
#define DLT_NVM_SESID_B1                                 0x0AU

#if (defined DLT_NVM_SESID_B2)
#error DLT_NVM_SESID_B2 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the SessionID information in the selected data set
 ** index */
#define DLT_NVM_SESID_B2                                0x0BU

#if (defined DLT_NVM_SESID_B3)
#error DLT_NVM_SESID_B3 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the SessionID information in the selected data set
 ** index */
#define DLT_NVM_SESID_B3                                0x0CU

#if (defined DLT_NVM_SESID_B4)
#error DLT_NVM_SESID_B4 already defined
#endif
/** \brief Index for NvM internal buffer for storing or restoring
 ** the SessionID information in the selected data set
 ** index */
#define DLT_NVM_SESID_B4                                0x0DU

/** \brief This type is used for the state-values of the initialization state
 ** of the Dlt module
 */
#if (defined DLT_UNINITIALIZED)
#error DLT_UNINITIALIZED already defined
#endif
/** \brief Defines connection status of DLT module for connected. */
#define DLT_UNINITIALIZED                                   0U

#if (defined DLT_INITIALIZED)
#error DLT_INITIALIZED already defined
#endif
/** \brief Defines connection status of DLT module for connected. */
#define DLT_INITIALIZED                                     1U

#if (defined DLT_INITIALIZED_PERSISTENT)
#error DLT_INITIALIZED_PERSISTENT already defined
#endif
/** \brief Defines connection status of DLT module for connected. */
#define DLT_INITIALIZED_PERSISTENT                          2U

#define DLT_IS_REGISTER        0x01U

#define DLT_IS_UNREGISTER      0x00U

#if (defined DLT_VFB_MESSAGE_ID_SIZE)
#error DLT_VFB_MESSAGE_ID_SIZE is already defined
#endif
/** \brief Size of the MessageId, in bytes */
#define DLT_VFB_MESSAGE_ID_SIZE 4U

#if (defined DLT_VFB_PAYLOAD_BUFFER_OFFSET)
#error DLT_VFB_PAYLOAD_BUFFER_OFFSET is already defined
#endif
/** \brief Space occupied (in bytes) by the
 *         ContextId, TraceDataLength and MessageId in the VFB buffer */
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_VFB_PAYLOAD_BUFFER_OFFSET 10U
#else
#define DLT_VFB_PAYLOAD_BUFFER_OFFSET 12U
#endif

#if (DLT_IMPLEMENT_VFB_TRACE == STD_ON)

#if (defined DLT_VFB_TRACE_PAYLOAD_BUFFER_SIZE)
#error DLT_VFB_TRACE_PAYLOAD_BUFFER_SIZE is already defined
#endif

#if (DLT_VFB_TRACE_NO_OF_INTERRUPTS == 0U)

/** \brief Total size of the buffer that handles the VFB trace function payloads
 *         If no interrupts are possible within the system, then the buffer size
 *         will be equal to the maximum payload size configured by the user */
#define DLT_VFB_TRACE_PAYLOAD_BUFFER_SIZE DLT_VFB_TRACE_PAYLOAD_MAX_SIZE

#else /* #if (DLT_VFB_TRACE_NO_OF_INTERRUPTS != 0U) */

/** \brief Total size of the buffer that handles the VFB trace function payloads
 *         If multiple interrupts are possible within the system, then the buffer size will be:
 *         Take for example a 15 byte payload:
 *         - 1 interrupt: buffer with a size of 30 bytes
 *         - 2 interrupts: buffer with a size of 45 bytes
 *         - 3 interrupts: buffer with a size of 60 bytes, and so on. */
#define DLT_VFB_TRACE_PAYLOAD_BUFFER_SIZE (DLT_VFB_TRACE_PAYLOAD_MAX_SIZE * (DLT_VFB_TRACE_NO_OF_INTERRUPTS + 1U))

#endif /* #if (DLT_VFB_TRACE_NO_OF_INTERRUPTS == 0U) */

#if (defined DLT_VFB_CTX_ID_PAYLOAD_LEN)
#error DLT_VFB_CTX_ID_PAYLOAD_LEN is already defined
#endif
/** \brief Size (in bytes) of the ContextId and the payload length in Dlt_TraceData[] */
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_VFB_CTX_ID_PAYLOAD_LEN 6U
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_VFB_CTX_ID_PAYLOAD_LEN 8U
#endif /* #if (TS_SIZE_PduLengthType == 2U) */

#if (defined DLT_VFB_PAYLOAD_LEN)
#error DLT_VFB_PAYLOAD_LEN is already defined
#endif
/** \brief Size (in bytes) of the payload length in Dlt_TraceData[] */
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_VFB_PAYLOAD_LEN 2U
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_VFB_PAYLOAD_LEN 4U
#endif /* #if (TS_SIZE_PduLengthType == 2U) */

#if (defined DLT_VFB_PAYLOAD_LEN_OFFSET)
#error DLT_VFB_PAYLOAD_LEN_OFFSET is already defined
#endif
/** \brief Offset (in bytes) of the payload length in Dlt_TraceData[] */
#define DLT_VFB_PAYLOAD_LEN_OFFSET 4U

#if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11))

#if ((DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))

#if (defined DLT_VFB_APP_ID)
#error DLT_VFB_APP_ID is already defined
#endif
/** \brief Application Id of VFB traces */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_VFB_APP_ID {DLT_VFB_APP_ID_MSB}
#else
/** \brief 0x56=V, 0x46=F, 0x42=B, 0x54=T -> "VFBT" */
#define DLT_VFB_APP_ID {0x56U, 0x46U, 0x42U, 0x54U}
#endif

#else /* #if ((DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)) */

#if (defined DLT_VFB_APP_ID)
#error DLT_VFB_APP_ID is already defined
#endif
/** \brief Application Id of VFB traces */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_VFB_APP_ID {DLT_VFB_APP_ID_LSB}
#else
/** \brief 0x54=T, 0x42=B, 0x46=F, 0x56=V -> "TBFV" */
#define DLT_VFB_APP_ID {0x54U, 0x42U, 0x46U, 0x56U}
#endif

#endif /* #if ((DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)) */

#if (defined DLT_VFB_CONTEXT_ID)
#error DLT_VFB_CONTEXT_ID is already defined
#endif
/** \brief Initial Context Id of VFB traces */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_VFB_CONTEXT_ID {DLT_VFB_CONTEXT_ID_VAR}
#else
#define DLT_VFB_CONTEXT_ID {0x00U, 0x00U, 0x00U, 0x00U}
#endif

#else /* #if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) */

#if (defined DLT_VFB_APP_ID)
#error DLT_VFB_APP_ID is already defined
#endif
/** \brief 0x56=V, 0x46=F, 0x42=B, 0x54=T -> "VFBT" */
#define DLT_VFB_APP_ID 0x56464254U

#if (defined DLT_VFB_CONTEXT_ID)
#error DLT_VFB_CONTEXT_ID is already defined
#endif
/** \brief Initial Context Id of VFB traces */
#define DLT_VFB_CONTEXT_ID 0U

#endif /* #if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) */

#endif /* #if (DLT_IMPLEMENT_VFB_TRACE == STD_ON) */

/* Macros for Dlt_DetForwardErrorTrace() */

#if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11))

#if ((DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))

#if (defined DLT_DET_APP_ID)
#error DLT_DET_APP_ID is already defined
#endif
/** \brief ApplicationId of Det - 0x44U, 0x45U, 0x54U ("DET") */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_DET_APP_ID {DLT_DET_APP_ID_MSB}
#else
#define DLT_DET_APP_ID {0x44U, 0x45U, 0x54U, '\0'}
#endif

#if (defined DLT_DET_CONTEXT_ID)
#error DLT_DET_CONTEXT_ID is already defined
#endif
/** \brief Context Id of Det - 0x53U, 0x54U, 0x44U ("STD") */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_DET_CONTEXT_ID {DLT_DET_CONTEXT_ID_MSB}
#else
#define DLT_DET_CONTEXT_ID {0x53U, 0x54U, 0x44U, '\0'}
#endif

#else /* #if ((DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)) */

#if (defined DLT_DET_APP_ID)
#error DLT_DET_APP_ID is already defined
#endif
/** \brief ApplicationId of Det - 0x54U, 0x45U, 0x44U ("TED") */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_DET_APP_ID {DLT_DET_APP_ID_LSB}
#else
#define DLT_DET_APP_ID {0x54U, 0x45U, 0x44U, '\0'}
#endif

#if (defined DLT_DET_CONTEXT_ID)
#error DLT_DET_CONTEXT_ID is already defined
#endif
/** \brief Context Id of Det - 0x44U, 0x54U, 0x53U ("TDS") */
#if (DLT_PROTOCOL_VERSION == 2U)
#define DLT_DET_CONTEXT_ID {DLT_DET_CONTEXT_ID_LSB}
#else
#define DLT_DET_CONTEXT_ID {0x44U, 0x54U, 0x53U, '\0'}
#endif

#endif /* #if ((DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)) */

#else /* #if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) */

#if (defined DLT_DET_APP_ID)
#error DLT_DET_APP_ID is already defined
#endif
/** \brief ApplicationId of Det - 0x44U, 0x45U, 0x54U ("DET") */
#define DLT_DET_APP_ID 0x444554U

#if (defined DLT_DET_CONTEXT_ID)
#error DLT_DET_CONTEXT_ID is already defined
#endif
/** \brief Context Id of Det - 0x53U, 0x54U, 0x44U ("STD") */
#define DLT_DET_CONTEXT_ID 0x535444U

#endif /* #if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) */

#if (defined DLT_DET_MODULE_ID)
#error DLT_DET_MODULE_ID is already defined
#endif
/** \brief ModuleId of the Det module */
#define DLT_DET_MODULE_ID 15U

#if (defined DLT_DET_CONTEXT_COUNT)
#error DLT_DET_CONTEXT_COUNT is already defined
#endif
/** \brief Number of ContextIds for the Det module */
#define DLT_DET_CONTEXT_COUNT 1U

#if (defined DLT_DET_MESSAGE_ID)
#error DLT_DET_MESSAGE_ID is already defined
#endif
/** \brief MessageId of the Det module */
#define DLT_DET_MESSAGE_ID 0x00000002U

#if (((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) && (DLT_PROTOCOL_VERSION == 2U))

#if (defined DLT_DET_APP_ID_INTERNAL)
#error DLT_DET_APP_ID_INTERNAL is already defined
#endif
/** \brief ApplicationId of Det - 0x44U, 0x45U, 0x54U ("DET") */
#define DLT_DET_APP_ID_INTERNAL {DLT_DET_APP_ID_MSB}

#if (defined DLT_DET_CONTEXT_ID_INTERNAL)
#error DLT_DET_CONTEXT_ID_INTERNAL is already defined
#endif
/** \brief Context Id of Det - 0x53U, 0x54U, 0x44U ("STD") */
#define DLT_DET_CONTEXT_ID_INTERNAL {DLT_DET_CONTEXT_ID_MSB}

#else

#if (defined DLT_DET_APP_ID_INTERNAL)
#error DLT_DET_APP_ID_INTERNAL is already defined
#endif
/** \brief ApplicationId of Det - 0x44U, 0x45U, 0x54U ("DET") */
#define DLT_DET_APP_ID_INTERNAL 0x444554U

#if (defined DLT_DET_CONTEXT_ID_INTERNAL)
#error DLT_DET_CONTEXT_ID_INTERNAL is already defined
#endif
/** \brief Context Id of Det - 0x53U, 0x54U, 0x44U ("STD") */
#define DLT_DET_CONTEXT_ID_INTERNAL 0x535444U

#endif

/*------------------[API function service IDs]------------------------------*/

#if (defined DLT_SID_ComTxConfirmation)
#error DLT_SID_ComTxConfirmation already defined
#endif
/** \brief Service Id for Dlt_ComTxConfirmation() */
#define DLT_SID_ComTxConfirmation          0x10U

/** \brief Length of standard header */
#if (defined DLT_MAX_STD_HEADER_LENGTH)
#error DLT_MAX_STD_HEADER_LENGTH already defined
#endif
#if (DLT_PROTOCOL_VERSION == 2U)
/** \brief HTYP2 (Header Type)         - 4 bytes
 *         MCNT  (Message Counter)     - 1 byte
 *         LEN   (Message Length)      - 2 bytes
 *         MSIN  (Message Info)        - 1 byte  (conditional)
 *         NOAR  (Number of arguments) - 1 byte  (conditional)
 *         TMSP2 (Timestamp)           - 9 bytes (conditional)
 *         MSID  (Message ID)          - 4 bytes (conditional)
 */
#define DLT_MAX_STD_HEADER_LENGTH       (DLT_MIN_HEADER_LENGTH + DLT_MSIN_HEADER_LEN + \
                                         DLT_NOAR_HEADER_LEN + DLT_TMSP_HEADER_LENGTH + DLT_MSID_HEADER_LENGTH)
#else
/** \brief HTYP (Header Type)     - 1 byte
 *         MCNT (Message Counter) - 1 byte
 *         LEN  (Message Length)  - 2 bytes
 *         ECU  (ECU ID)          - 4 bytes (optional)
 *         SEID (Session ID)      - 4 bytes (optional)
 *         TMSP (Timestamp)       - 4 bytes (optional)
 */
#define DLT_MAX_STD_HEADER_LENGTH       (DLT_MIN_HEADER_LENGTH + DLT_ECU_HEADER_LENGTH + \
                                         DLT_SEID_HEADER_LENGTH + DLT_TMSP_HEADER_LENGTH)
#endif

#if (DLT_PROTOCOL_VERSION == 2U)
/** \brief Maximum header length */
#define DLT_MAX_HEADER_LENGTH           (DLT_MAX_STD_HEADER_LENGTH + DLT_EXT_HEADER_LENGTH_MAX)
/** \brief Standard header for control messages - 7 bytes always available, MSIN (1), NOAR (1) */
#define DLT_STD_HEADER_LENGTH_CONTROL_MESSAGE   9U
#else
#define DLT_MAX_HEADER_LENGTH           (DLT_MAX_STD_HEADER_LENGTH + DLT_EXT_HEADER_LENGTH)
#endif

#if (DLT_PROTOCOL_VERSION == 2U)
/** \brief Position of the HTYPE header field */
#define DLT_HTYP_HEADER_OFFSET          0x00U
/** \brief Position of the MCNT header field */
#define DLT_MCNT_HEADER_OFFSET          0x04U
/** \brief Position of the LEN header field */
#define DLT_LEN_HEADER_OFFSET           0x05U
#define DLT_NOAR_CTRL_MSG_HEADER_OFFSET  0x08U
/** \brief Flag for WPVL value in HTYP2 field */
#define DLT_WPVL_FIELD_FLAG             0x04U
#else
/** \brief Position of the HTYPE header field */
#define DLT_HTYP_HEADER_OFFSET          0x00U
/** \brief Position of the MCNT header field */
#define DLT_MCNT_HEADER_OFFSET          0x01U
/** \brief Position of the LEN header field */
#define DLT_LEN_HEADER_OFFSET           0x02U
#endif

/* !LINKSTO EB.Req.DltMessageOptionsBitField, 1 */
#if (DLT_MESSAGE_OPTIONS_BITFIELD == AUTOSAR_421)

/* !LINKSTO Dlt.ASR421.SWS_Dlt_00229, 1 */
/** \brief Message type bits in Dlt_MessageOptionsType */
#define DLT_OPT_MESSAGE_TYPE_MASK        0x07U
/** \brief Verbose mode flag in Dlt_MessageOptionsType */
#define DLT_OPT_VERBOSE_MODE_MASK        0x08U
/** \brief Message type bit position in Dlt_MessageOptionsType */
#define DLT_OPT_MESSAGE_TYPE_POS         0x00U
/** \brief Verbose mode flag bit position in Dlt_MessageOptionsType */
#define DLT_OPT_VERBOSE_MODE_POS         0x03U
/** \brief Message type bit position in Dlt_MessageOptionsType */
#define DLT_OPT_MESSAGE_TYPE_MSTP_BSHIFT 0x01U

#else /* #if (DLT_MESSAGE_OPTIONS_BITFIELD == AUTOSAR_431) */

/* !LINKSTO Dlt.SWS_Dlt_00229, 1 */
/** \brief Message type bits in Dlt_MessageOptionsType */
#define DLT_OPT_MESSAGE_TYPE_MASK        0x0EU
/** \brief Verbose mode flag in Dlt_MessageOptionsType */
#define DLT_OPT_VERBOSE_MODE_MASK        0x01U
/** \brief Message type bit position in Dlt_MessageOptionsType */
#define DLT_OPT_MESSAGE_TYPE_POS         0x01U
/** \brief Verbose mode flag bit position in Dlt_MessageOptionsType */
#define DLT_OPT_VERBOSE_MODE_POS         0x00U
/** \brief Message type bit position in Dlt_MessageOptionsType */
#define DLT_OPT_MESSAGE_TYPE_MSTP_BSHIFT 0x00U

#endif /* #if (DLT_MESSAGE_OPTIONS_BITFIELD == AUTOSAR_421) */

/** \brief Log level type bits in Dlt_MessageLogLevelType */
#define DLT_LOG_LEVEL_TYPE_MASK         0x07U
/** \brief Trace type bits in Dlt_MessageTraceType */
#define DLT_TRACE_TYPE_MASK             0x07U

/** \brief Bit position of log or trace type in MSIN field */
#define DLT_LOG_TRACE_TYPE_POS          0x04U

/** \brief Bit position in Flags member of Dlt_ContextIdTableType indicating a notification for log level changed is pending */
#define DLT_CNTX_LOG_NOTIFY_POS         0x00U
/** \brief Bit position in Flags member of Dlt_ContextIdTableType indicating a notification for trace status changed is pending */
#define DLT_CNTX_TRACE_NOTIFY_POS       0x01U
/** \brief Bit position in Flags member of Dlt_ContextIdTableType indicating a notification for verbose mode changed is pending */
#define DLT_CNTX_VERBOSE_NOTIFY_POS     0x02U
/** \brief Mask for Flags member of Dlt_ContextIdTableType indicating a notification for log level changed is pending */
#define DLT_CNTX_LOG_NOTIFY_MASK        0x01U
/** \brief Mask for Flags member of Dlt_ContextIdTableType indicating a notification for trace status changed is pending */
#define DLT_CNTX_TRACE_NOTIFY_MASK      0x02U
/** \brief Mask for Flags member of Dlt_ContextIdTableType indicating a notification for verbose mode changed is pending */
#define DLT_CNTX_VERBOSE_NOTIFY_MASK    0x04U

/* !LINKSTO Dlt.ASR421.SWS_Dlt_00318,1, Dlt.ASR421.SWS_Dlt_00299,1 */
#define DLT_HEADER_PROTOCOL_VERSION_BIT ((DLT_PROTOCOL_VERSION)<<5U)

#define DLT_BUF_EMPTY          0x00U
#define DLT_BUF_FULL           0x01U
#define DLT_BUF_OVERFLOW       0x02U
#define DLT_BUF_BUSY           0x03U
#define DLT_BUF_INVALID        0x04U

/** \brief The message entry may be overwritten */
#define DLT_MSG_UNLOCKED       0x00U
/** \brief The message entry is currently sent and may not be overwritten */
#define DLT_MSG_LOCKED         0x01U
/* !LINKSTO Dlt.BswDistribution.InstanceId,1 */
/** \brief Instance ID of the Dlt.
 * If multicore support is enabled, the Instance IDs
 * correspond with the core IDs given by the OS.
 * If multicore support is disabled, the Instance ID
 * is 0U.
 */
#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)
#define DLT_INSTANCE_ID        GetCoreID()
#else
#define DLT_INSTANCE_ID        0U
#endif

/** \brief Special value to indicate not a specific satellite index, but all of them */
#define DLT_ALL_SATELLITES     0xFFU





/*------------------------[Defensive programming]----------------------------*/

#if (defined DLT_PRECONDITION_ASSERT)
#error DLT_PRECONDITION_ASSERT is already defined
#endif

#if (defined DLT_PRECONDITION_ASSERT_NO_EVAL)
#error DLT_PRECONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (DLT_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define DLT_PRECONDITION_ASSERT(InstId, Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), DLT_MODULE_ID, (InstId), (ApiId))

/** \brief Report an assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define DLT_PRECONDITION_ASSERT_NO_EVAL(InstId, Condition, ApiId) \
  DET_PRECONDITION_ASSERT_NO_EVAL((Condition), DLT_MODULE_ID, (InstId), (ApiId))
#else
#define DLT_PRECONDITION_ASSERT(InstId, Condition, ApiId)
#define DLT_PRECONDITION_ASSERT_NO_EVAL(InstId, Condition, ApiId)
#endif

#if (defined DLT_POSTCONDITION_ASSERT)
#error DLT_POSTCONDITION_ASSERT is already defined
#endif

#if (defined DLT_POSTCONDITION_ASSERT_NO_EVAL)
#error DLT_POSTCONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (DLT_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define DLT_POSTCONDITION_ASSERT(InstId, Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), DLT_MODULE_ID, (InstId), (ApiId))

/** \brief Report an assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define DLT_POSTCONDITION_ASSERT_NO_EVAL(InstId, Condition, ApiId) \
  DET_POSTCONDITION_ASSERT_NO_EVAL((Condition), DLT_MODULE_ID, (InstId), (ApiId))
#else
#define DLT_POSTCONDITION_ASSERT(InstId, Condition, ApiId)
#define DLT_POSTCONDITION_ASSERT_NO_EVAL(InstId, Condition, ApiId)
#endif

#if (defined DLT_INVARIANT_ASSERT)
#error DLT_INVARIANT_ASSERT is already defined
#endif

#if (defined DLT_INVARIANT_ASSERT_NO_EVAL)
#error DLT_INVARIANT_ASSERT_NO_EVAL is already defined
#endif

#if (DLT_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define DLT_INVARIANT_ASSERT(InstId, Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), DLT_MODULE_ID, (InstId), (ApiId))

/** \brief Report an assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define DLT_INVARIANT_ASSERT_NO_EVAL(InstId, Condition, ApiId) \
  DET_INVARIANT_ASSERT_NO_EVAL((Condition), DLT_MODULE_ID, (InstId), (ApiId))
#else
#define DLT_INVARIANT_ASSERT(InstId, Condition, ApiId)
#define DLT_INVARIANT_ASSERT_NO_EVAL(InstId, Condition, ApiId)
#endif

#if (defined DLT_STATIC_ASSERT)
# error DLT_STATIC_ASSERT is already defined
#endif
#if (DLT_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define DLT_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define DLT_STATIC_ASSERT(expr)
#endif

#if (defined DLT_UNREACHABLE_CODE_ASSERT)
#error DLT_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (DLT_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **
 ** \param[in] InstId The Dlt instance which peforms the assertion
 ** \param[in] ApiId Service ID of the API function */
#define DLT_UNREACHABLE_CODE_ASSERT(InstId, ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(DLT_MODULE_ID, (InstId), (ApiId))
#else
#define DLT_UNREACHABLE_CODE_ASSERT(InstId, ApiId)
#endif

#if (defined DLT_INTERNAL_API_ID)
#error DLT_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define DLT_INTERNAL_API_ID DET_INTERNAL_API_ID



/** \brief The message is a log message */
#define DLT_MESSAGE_TYPE_LOG   0x00U
/** \brief the message is a trace message */
#define DLT_MESSAGE_TYPE_TRACE 0x01U

/** \brief The log level is returned at accessing the default log level
 ** before the Dlt module is initialized */
#define DLT_DFT_INVALID_LOGLEVEL             0xAAU
/** \brief The log level is returned at accessing the default trace status
 ** before the Dlt module is initialized */
#define DLT_DFT_INVALID_TRACESTATUS          0xAAU
/** \brief The log level is returned at accessing the message filtering status
 ** before the Dlt module is initialized */
#define DLT_INVALID_MESSAGEFILTERINGSTS      0xAAU
/** \brief The log level is returned at accessing the global log status
 ** before the Dlt module is initialized */
#define DLT_INVALID_GLOBALLOGSTATUS         0xAAU

/** \brief Session Id base for trace messages from SW-Cs */
#define DLT_SWC_SESSION_ID_BASE             0x1000U

/** \brief No SessionID has been registered for the corresponding context in Dlt_ContextIdTable. */
#define DLT_NO_SESSION_ID                   0xFFFFFFFFU

/** \brief DLT_DET_REPORT_ERROR() call Det_ReportError()
 **
 ** In development mode, this macro calls Det_ReportError() with the given
 ** ServiceId and ErrorCode as parameters. The ModuleId and InstanceId
 ** expected by Det are filled in automatically.
 **
 ** In production mode this macro does nothing.
*/
/* !LINKSTO Dlt.OptionalInterfaces, 1 */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
#define DLT_DET_REPORT_ERROR(ServiceId,ErrorCode)                       \
  ((void)Det_ReportError(DLT_MODULE_ID, DLT_INSTANCE_ID, (ServiceId), (ErrorCode)))
#endif /* DLT_DEV_ERROR_DETECT == STD_ON */

#ifndef DLT_REPORT_VFB_BUFFER_FULL
/** \brief definition of the full VFB buffer */
#if (DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL == TS_PROD_ERR_REP_TO_DEM)
    /* Report DEM */
#define DLT_REPORT_VFB_BUFFER_FULL(SidId) \
    Dem_ReportErrorStatus(DLT_E_VFB_BUFFER_FULL_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED)
#elif (DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL == TS_PROD_ERR_REP_TO_DET)
    /* Report DET */
#define DLT_REPORT_VFB_BUFFER_FULL(SidId) \
    DLT_DET_REPORT_ERROR(SidId, DLT_E_DEMTODET_VFB_BUFFER_FULL)
#endif
#endif

/** \brief Wrapper macro for the Det_ReportRuntimeError() call
 **
 ** The ModuleId and InstanceId expected by Det are filled in automatically.
 **
*/

#if (DLT_DET_RUNTIME_CHECKS == STD_ON)

#ifndef DLT_DET_REPORT_RUNTIME_ERROR
#define DLT_DET_REPORT_RUNTIME_ERROR(ApiId,ErrorId)                       \
  ((void)Det_ReportRuntimeError(DLT_MODULE_ID, 0U, (ApiId), (ErrorId)))
#endif

#endif /* DLT_DET_RUNTIME_CHECKS == STD_ON */

#if (defined DLT_MSTP_MASK)
#error DLT_MSTP_MASK already defined
#endif
/** \brief Mask for MSTP field  */
#define DLT_MSTP_MASK                                               0x0EU

#if (defined DLT_CHANNEL_NAME_SIZE)
#error DLT_CHANNEL_NAME_SIZE already defined
#endif
/** \brief Size of the channel name  */
#define DLT_CHANNEL_NAME_SIZE                                       4U

#if (defined DLT_CHANNEL_IDX_SIZE)
#error DLT_CHANNEL_IDX_SIZE already defined
#endif
/** \brief Size of the channel index  */
#define DLT_CHANNEL_IDX_SIZE                                        1U

#if (defined DLT_SESSION_ID_SIZE)
#error DLT_SESSION_ID_SIZE already defined
#endif
/** \brief Size of the session id  */
#define DLT_SESSION_ID_SIZE                                         4U

#if (defined DLT_MTIN_MASK)
#error DLT_MTIN_MASK already defined
#endif
/** \brief Mask for MTIN field  */
#define DLT_MTIN_MASK                                               0xF0U
/** \brief length of the channel id in bytes */
#define DLT_CHANNEL_ID_LENGTH 4U
/** \brief CONTROL_RESPONSE bits to be writte in MSIN field. */
#define DLT_CONTROL_RESPONSE_BITS_IN_MSIN          ((DLT_CONTROL_RESPONSE) << 4U)

#if (DLT_PROTOCOL_VERSION == 2U)
/** \brief Length of the SEID field - independent of the configuration */
#define DLT_HEADER_SEID_LENGTH_STATIC                    4U
/** \brief Length of the LINR field - independent of the configuration */
#define DLT_HEADER_LINR_LENGTH_STATIC                    4U
/** \brief Verbose mode data message */
#define DLT_VERBOSE_MODE_DATA_MESSAGE                    0U
/** \brief Non-Verbose mode data message */
#define DLT_NON_VERBOSE_MODE_DATA_MESSAGE                1U
/** \brief Control message */
#define DLT_CONTROL_MESSAGE                              2U
/** \brief mask for CNTI field in header */
#define DLT_CNTI_MASK                                    3U
#else /* (DLT_PROTOCOL_VERSION == 1U) */
/** \brief Size of the  timestamp field in the header - independent of the configuration */
#define DLT_TMSP_HEADER_LENGTH_STATIC                    4U
/** \brief Size of the extended header - independent of the configuration */
#define DLT_EXT_HEADER_LENGTH_STATIC                     10U
#endif /* (DLT_PROTOCOL_VERSION == 2U) */

/** \brief Size of the ecu ID field in the header - independent of the configuration */
#define DLT_ECU_HEADER_LENGTH_STATIC                     4U
/** \brief Length of the APID field - independent of the configuration */
#define DLT_HEADER_APPID_LENGTH_STATIC                   4U
/** \brief Length of the CTID field - independent of the configuration */
#define DLT_HEADER_CTXID_LENGTH_STATIC                   4U
/** \brief Size of the  session ID field in the header - independent of the configuration */
#define DLT_SEID_HEADER_LENGTH_STATIC                    4U

#if (DLT_PROTOCOL_VERSION == 2U)
/** \brief Enabled-state value of the EcuId message header field */
#define DLT_HEADER_ECU_ID_BIT          0x04U
/** \brief Enabled-state value of the AppID and Context ID message header field */
#define DLT_HEADER_APP_CTX_ID_BIT      0x08U
/** \brief Enabled-state value of the SessionID message header field */
#define DLT_HEADER_SESSION_ID_BIT      0x10U
/** \brief Enabled-state value of the Source File Name and Line Number message header field */
#define DLT_HEADER_WSFLN_ID_BIT        0x08U
/** \brief Enabled-state value of the Tags message header field */
#define DLT_HEADER_TAGS_BIT            0x02U
/** \brief Enabled-state value of the Privacy Level message header field */
#define DLT_HEADER_PRIVACY_LVL_BIT     0x04U
#else /* (DLT_PROTOCOL_VERSION == 1U) */
/** \brief Enabled-state value of the EcuId message header field */
#define DLT_HEADER_ECU_ID_BIT          0x04U
/** \brief Enabled-state value of the SessionID message header field */
#define DLT_HEADER_SESSION_ID_BIT      0x08U
/** \brief Enabled-state value of the Timestamp message header field */
#define DLT_HEADER_TIMESTAMP_BIT       0x10U
/** \brief Macro for global Tx Pdu */
#define DLT_CONTROL_TX_PDU        0x01U
#endif /* (DLT_PROTOCOL_VERSION == 2U) */

/** \brief Enabled-state value of the Timestamp message header field */
#define DLT_HEADER_TIMESTAMP_BIT       0x10U

/** \brief Enabled-state value of the ExtendedHeader message header field */
#define DLT_HEADER_EXTENDED_HEADER_BIT 0x01U

/** \brief Macro for the RegisterContext notification */
#define DLT_STATUS_REGISTER   0x06U
/** \brief Macro for the UnregisterContext notification */
#define DLT_STATUS_UNREGISTER 0x05U

#if ( (DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) )

/** \brief Macro for converting Vfb tuples */
#define DLT_UINT32_CONVERT_VFB_TUPLE_MSB(ptr) ( (uint32) \
                                             ( ((uint32)((ptr)[0]) << 24U) \
                                             | ((uint32)((ptr)[1]) << 16U) \
                                             | ((uint32)((ptr)[2]) << 8U)  \
                                             | ((uint32)((ptr)[3]) ) ) )

#define DLT_UINT32_FROM_BYTE_ARRAY_VFB_HEADER(ptr) DLT_UINT32_CONVERT_VFB_TUPLE_MSB(ptr)

#else /* #if ( (DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_OFF) && (CPU_BYTE_ORDER == LOW_BYTE_FIRST) ) */

#define DLT_UINT32_CONVERT_VFB_TUPLE_LSB(ptr) ( (uint32) \
                                          ( ((uint32)((ptr)[3]) << 24U) \
                                          | ((uint32)((ptr)[2]) << 16U) \
                                          | ((uint32)((ptr)[1]) << 8U)  \
                                          | ((uint32)((ptr)[0]) ) ) )

#define DLT_UINT32_FROM_BYTE_ARRAY_VFB_HEADER(ptr) DLT_UINT32_CONVERT_VFB_TUPLE_LSB(ptr)

#endif /* #if ( (DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) ) */

/** \brief Fill a 2-byte buffer with the most significant byte first */
#define DLT_FILL_BUFFER_16_MSB(buffer, offset, data)             \
  do                                                             \
  {                                                              \
    (buffer)[(offset)]      = (uint8)(((data) & 0xff00U) >> 8U); \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x00ffU));       \
  } while(0)

/** \brief Create an uint16 value representing the payload length from the VFB circular buffer, MSB */
#define DLT_UINT16_FROM_VFB_BYTE_ARRAY_MSB(ptr, idx) ( (uint16) \
                                                    ( ((uint16)((ptr)[idx + 4U]) << 8U) \
                                                    | ((uint16)((ptr)[idx + 5U]) ) ) )

/** \brief Fill a 4-byte buffer with the most significant byte first */
#define DLT_FILL_BUFFER_32_MSB(buffer, offset, data)                  \
  do                                                                  \
  {                                                                   \
    (buffer)[(offset)]      = (uint8)(((uint32)(data) & 0xff000000U) >> 24U); \
    (buffer)[(offset) + 1U] = (uint8)(((uint32)(data) & 0x00ff0000U) >> 16U); \
    (buffer)[(offset) + 2U] = (uint8)(((uint32)(data) & 0x0000ff00U) >>  8U); \
    (buffer)[(offset) + 3U] = (uint8)(((uint32)(data) & 0x000000ffU));        \
  } while(0)

/** \brief Fill a 4-byte buffer with value 0 */
#define DLT_FILL_BUFFER_NULL_VALUE(buffer, offset)                  \
  do                                                                  \
  {                                                                   \
    (buffer)[(offset)]      = (uint8)(0U); \
    (buffer)[(offset) + 1U] = (uint8)(0U); \
    (buffer)[(offset) + 2U] = (uint8)(0U); \
    (buffer)[(offset) + 3U] = (uint8)(0U); \
  } while(0)

#if (defined DLT_FILL_BUFFER_MSB)
#error DLT_FILL_BUFFER_MSB already defined
#endif
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_FILL_BUFFER_MSB(buffer, offset, data) DLT_FILL_BUFFER_16_MSB(buffer, offset, data)
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_FILL_BUFFER_MSB(buffer, offset, data) DLT_FILL_BUFFER_32_MSB(buffer, offset, data)
#endif /* #if (TS_SIZE_PduLengthType == 2U) */

/** \brief Create an uint32 value from the first four elements of the uint8 array. MSB first (big endian) */
#define DLT_UINT32_FROM_VFB_BYTE_ARRAY_MSB(ptr) ( (uint32) \
                                          ( ((uint32)((ptr)[0]) << 24U) \
                                          | ((uint32)((ptr)[1]) << 16U) \
                                          | ((uint32)((ptr)[2]) << 8U)  \
                                          | ((uint32)((ptr)[3]) ) ) )

/** \brief Create an uint32 value from the specific four elements of the uint8 array. MSB first (big endian) */
#define DLT_UINT32_FROM_VFB_BYTE_ARRAY_MSB_IDX(ptr, idx) ( (uint32) \
                                          ( ((uint32)((ptr)[idx + 4U]) << 24U) \
                                          | ((uint32)((ptr)[idx + 5U]) << 16U) \
                                          | ((uint32)((ptr)[idx + 6U]) << 8U)  \
                                          | ((uint32)((ptr)[idx + 7U]) ) ) )

#if (defined DLT_UINT_FROM_VFB_BYTE_ARRAY_MSB)
#error DLT_UINT_FROM_VFB_BYTE_ARRAY_MSB already defined
#endif
#if (TS_SIZE_PduLengthType == 2U)
#define DLT_UINT_FROM_VFB_BYTE_ARRAY_MSB(ptr, idx) DLT_UINT16_FROM_VFB_BYTE_ARRAY_MSB(ptr, idx)
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_UINT_FROM_VFB_BYTE_ARRAY_MSB(ptr, idx) DLT_UINT32_FROM_VFB_BYTE_ARRAY_MSB_IDX(ptr, idx)
#endif /* #if (TS_SIZE_PduLengthType == 2U) */

#if ( (DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) )

/* !LINKSTO Dlt.Config.DltTupleEndianness.Enabled,1 */
/** \brief Create an uint32 value from the first four elements of the uint8 array. MSB first (big endian) */
#define DLT_UINT32_TUPLE_MSB_FIRST(ptr) ( (uint32) \
                                          ( ((uint32)((ptr)[0]) << 24U) \
                                          | ((uint32)((ptr)[1]) << 16U) \
                                          | ((uint32)((ptr)[2]) << 8U)  \
                                          | ((uint32)((ptr)[3]) ) ) )

#define DLT_UINT32_CONVERT_TUPLE(ptr) DLT_UINT32_TUPLE_MSB_FIRST(ptr)

/** \brief Fill a 4-byte buffer with the most significant byte first */
#define DLT_FILL_BUFFER_32(buffer, offset, data)                      \
  do                                                                  \
  {                                                                   \
    (buffer)[(offset) + 0U] = (uint8)(((data) & 0xff000000U) >> 24U); \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x00ff0000U) >> 16U); \
    (buffer)[(offset) + 2U] = (uint8)(((data) & 0x0000ff00U) >>  8U); \
    (buffer)[(offset) + 3U] = (uint8)(((data) & 0x000000ffU));        \
  } while(0)

#else /* (DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */

/** \brief Create an uint32 value from the first four elements of the uint8 array. LSB first (little endian) */
/* !LINKSTO Dlt.Config.DltTupleEndianness.Disabled,1 */
#define DLT_UINT32_TUPLE_LSB_FIRST(ptr) ( (uint32) \
                                          ( ((uint32)((ptr)[3]) << 24U) \
                                          | ((uint32)((ptr)[2]) << 16U) \
                                          | ((uint32)((ptr)[1]) << 8U)  \
                                          | ((uint32)((ptr)[0]) ) ) )

#define DLT_UINT32_CONVERT_TUPLE(ptr) DLT_UINT32_TUPLE_LSB_FIRST(ptr)

/** \brief Fill a 4-byte buffer with the least significant byte first */
#define DLT_FILL_BUFFER_32(buffer, offset, data)                      \
  do                                                                  \
  {                                                                   \
    (buffer)[(offset) + 3U] = (uint8)(((data) & 0xff000000U) >> 24U); \
    (buffer)[(offset) + 2U] = (uint8)(((data) & 0x00ff0000U) >> 16U); \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x0000ff00U) >>  8U); \
    (buffer)[(offset) + 0U] = (uint8)(((data) & 0x000000ffU));        \
  } while(0)

#endif /* (DLT_TUPLE_PLATFORM_ENDIANNESS_DISABLE == STD_ON) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */

#if (((DLT_PROTOCOL_VERSION == 1U) && (DLT_HEADER_PAYLOAD_ENDIANES_BIT != 0U)) || (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))

/** \brief Fill a 2-byte buffer with the most significant byte first */
#define DLT_FILL_BUFFER_16_HDR_EDNS(buffer, offset, data)            \
  do                                                                 \
  {                                                                  \
    (buffer)[(offset) + 0U] = (uint8)(((data) & 0x0000ff00U) >> 8U); \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x000000ffU));       \
  } while(0)

/** \brief Fill a 4-byte buffer with the most significant byte first */
#define DLT_FILL_BUFFER_32_HDR_EDNS(buffer, offset, data)             \
  do                                                                  \
  {                                                                   \
    (buffer)[(offset) + 0U] = (uint8)(((data) & 0xff000000U) >> 24U); \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x00ff0000U) >> 16U); \
    (buffer)[(offset) + 2U] = (uint8)(((data) & 0x0000ff00U) >>  8U); \
    (buffer)[(offset) + 3U] = (uint8)(((data) & 0x000000ffU));        \
  } while(0)

#else

/** \brief Fill a 2-byte buffer with the least significant byte first */
#define DLT_FILL_BUFFER_16_HDR_EDNS(buffer, offset, data)            \
  do                                                                 \
  {                                                                  \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x0000ff00U) >> 8U); \
    (buffer)[(offset) + 0U] = (uint8)(((data) & 0x000000ffU));       \
  } while(0)

/** \brief Fill a 4-byte buffer with the least significant byte first */
#define DLT_FILL_BUFFER_32_HDR_EDNS(buffer, offset, data)             \
  do                                                                  \
  {                                                                   \
    (buffer)[(offset) + 3U] = (uint8)(((data) & 0xff000000U) >> 24U); \
    (buffer)[(offset) + 2U] = (uint8)(((data) & 0x00ff0000U) >> 16U); \
    (buffer)[(offset) + 1U] = (uint8)(((data) & 0x0000ff00U) >>  8U); \
    (buffer)[(offset) + 0U] = (uint8)(((data) & 0x000000ffU));        \
  } while(0)

#endif

#if (defined DLT_DETFORWARD_ERROR_TRACE_PAYLOAD_SIZE)
#error DLT_DETFORWARD_ERROR_TRACE_PAYLOAD_SIZE is already defined
#endif
#if ((DLT_PROTOCOL_VERSION == 1U) && (DLT_USE_VERBOSE_MODE == STD_OFF))
/** \brief MessageId  (4 bytes)
 *         ModuleId   (2 bytes)
 *         InstanceId (1 byte)
 *         ApiId      (1 byte)
 *         ErrorId    (1 byte) */
#define DLT_DETFORWARD_ERROR_TRACE_PAYLOAD_SIZE 9U
#else
/** \brief ModuleId   (2 bytes)
 *         InstanceId (1 byte)
 *         ApiId      (1 byte)
 *         ErrorId    (1 byte) */
#define DLT_DETFORWARD_ERROR_TRACE_PAYLOAD_SIZE 5U
#endif

/*==================[type definitions]======================================*/

typedef uint8 Dlt_MessageType;
typedef uint8 Dlt_ChnIdTableIdxType;

/** \brief Pointer to variable element in ::Dlt_ContextIdTable[] */
typedef P2VAR(Dlt_ContextIdTableType, TYPEDEF, DLT_VAR_CLEARED) Dlt_ContextIdTablePtrType;
/** \brief Pointer to elements in Dlt_AppIdTable[] */
typedef P2VAR(Dlt_AppIdTableType, TYPEDEF, DLT_VAR_CLEARED) Dlt_AppIdTablePtrType;
/** \brief Pointer to elements in Dlt_AppToContextIdTable[] */
typedef P2VAR(Dlt_AppToContextIdTableType, TYPEDEF, DLT_VAR_CLEARED) Dlt_AppToContextIdTablePtrType;
/** \brief Pointer to elements in Dlt_AppToContextIdTableIdx[] */
typedef P2VAR(Dlt_AppToContextIdTableIdxType, TYPEDEF, DLT_VAR_CLEARED) Dlt_AppToContextIdTableIdxPtrType;

/** \brief Type for storing common context information for all type of cores (satellite or master) */
typedef struct
{
  /* Init state of the Dlt core */
  /* !LINKSTO Dlt.swdd.BSWDistribution.InitStateOfCores,1 */
  P2VAR(uint8, AUTOMATIC, DLT_VAR) InitState;
  /* Next free entry in Dlt_ContextIdTable */
  P2VAR(uint32, AUTOMATIC, DLT_VAR) ContextIdTableIdx;
  /* Default log level for log messages */
  P2VAR(Dlt_MessageLogLevelType, AUTOMATIC, DLT_VAR) DefaultLogLevel;
  /* Default trace status for trace messages */
  P2VAR(Dlt_MessageTraceStatusType, AUTOMATIC, DLT_VAR) DefaultTraceStatus;
  /* Message filtering status */
  P2VAR(Dlt_FilterMessagesType, AUTOMATIC, DLT_VAR) FilterMessages;
  /* Context information */
  P2VAR(Dlt_ContextIdTableType, AUTOMATIC, DLT_VAR) ContextIdTable;
#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)
  /* Number of currently registered ApplicationIds */
  P2VAR(Dlt_AppIdTableIdxType, AUTOMATIC, DLT_VAR) MaxRegisteredAppldTableEntry;
  /* ApplicationId table */
  P2VAR(Dlt_AppIdTableType, AUTOMATIC, DLT_VAR) AppIdTable;
  /* ContextIds per ApplicationId */
  P2VAR(Dlt_AppToContextIdTableType, AUTOMATIC, DLT_VAR) AppToContextIdTable;
  /* Next free entry in AppToContextIdTable */
  P2VAR(Dlt_AppToContextIdTableIdxType, AUTOMATIC, DLT_VAR) AppToContextIdTableIdx;
  /* SessionIds table */
  /* !LINKSTO Dlt.swdd.DltConfig.Misc.JetTemplates.Dlt_SessionIdTableType,1 */
  P2VAR(Dlt_SessionIdTableType, AUTOMATIC, DLT_VAR) SessionIdTable;
#endif
} Dlt_BSWDistributionCommonType;

/** \brief Function pointer type for generic SchM_Entry/Exit_ExclusiveArea
 ** function. */
typedef P2FUNC(void, DLT_CODE, Dlt_EnterExclusiveAreaFctPtrType)(void);

typedef P2FUNC(void, DLT_CODE, Dlt_ExitExclusiveAreaFctPtrType)(void);

#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)

/** \brief Function pointer type for Dlt_SlaveSendContextMessage
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_SlaveSendContextMessageFctPtrType)
    (P2CONST(Dlt_IOCRegisterContextMessageType, AUTOMATIC, RTE_APPL_DATA) data);

/** \brief Function pointer type for Dlt_SlaveSendSessionId
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_SlaveSendSessionIdFctPtrType)
    (Dlt_SessionIDType data);

/** \brief Function pointer type for Dlt_SlaveSendMessage
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_SlaveSendMessageFctPtrType)
    (P2CONST(Dlt_IOCSendMessageType, AUTOMATIC, RTE_APPL_DATA) data);

/** \brief Function pointer type for Dlt_SlaveReceiveSyncTable
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_SlaveReceiveSyncTableFctPtrType)
    (P2VAR(Dlt_IOCSyncTableType, AUTOMATIC, RTE_APPL_DATA) data);

/** \brief Array of function pointer type for Dlt_MasterSendSyncTable
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, (Dlt_MasterSendSyncTableFctPtrArr[DLT_NUMBER_OF_SATELLITES]))
    (P2CONST(Dlt_IOCSyncTableType, AUTOMATIC, RTE_APPL_DATA) data);

/** \brief Function pointer type for Dlt_MasterReceiveSessionId
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_MasterReceiveSessionIdFctPtr)
    (P2VAR(Dlt_SessionIDType, AUTOMATIC, RTE_APPL_DATA) data);

/** \brief Function pointer type for Dlt_MasterReceiveContextMessage
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_MasterReceiveContextMessageFctPtr)
    (P2VAR(Dlt_IOCRegisterContextMessageType, AUTOMATIC, RTE_APPL_DATA) data);

/** \brief Function pointer type for Dlt_MasterReceiveMessage
 ** function */
typedef
  P2FUNC(Std_ReturnType, RTE_CODE, Dlt_MasterReceiveMessageFctPtr)
    (P2VAR(Dlt_IOCSendMessageType, AUTOMATIC, RTE_APPL_DATA) data);


/** \brief Type for storing context information of satellite cores if
 **        BSW distribution is enabled. If BSW distribution is disabled,
 **        this type does not exist. */
typedef struct
{
  Dlt_CoreIdType                        OsCoreId;
  Dlt_BSWDistributionCommonType         CoreContext;
    /**< Basic information field */
  Dlt_EnterExclusiveAreaFctPtrType      EnterExclusiveArea;
    /**< Pointer to wrapper function Dlt_EnterExclusiveAreaSatelliteCoreId<n>() */
  Dlt_ExitExclusiveAreaFctPtrType       ExitExclusiveArea;
    /**< Pointer to wrapper function Dlt_ExitExclusiveAreaSatelliteCoreId<n>() */
  Dlt_SlaveSendContextMessageFctPtrType SlaveSendContextMessage;
    /**<  ptr to SchM_Send_Dlt_1_Core_[]_SlaveSendContextMessagePort() function */
#if (DLT_IMPLEMENT_NV_RAM_STORAGE == STD_ON)
  Dlt_SlaveSendSessionIdFctPtrType      SlaveSendSessionId;
    /**<  ptr to SchM_Send_Dlt_1_Core_[]_SlaveSendSessionIdPort() function */
#endif
  Dlt_SlaveSendMessageFctPtrType        SlaveSendMessage;
    /**<  ptr to SchM_Send_Dlt_1_Core_[]_SlaveSendMessagePort() function */
  Dlt_SlaveReceiveSyncTableFctPtrType   SlaveReceiveSyncTable;
    /**<  ptr to SchM_Send_Dlt_1_Core_[]_SlaveReceiveSyncTablePort_<n>() function */
} Dlt_BSWSatelliteContextType;

/** \brief Type pointer to Dlt_BSWSatelliteContextType type. */
typedef P2CONST(Dlt_BSWSatelliteContextType, AUTOMATIC, DLT_VAR)
  Dlt_BSWSatelliteContextPtrType;

extern CONST(Dlt_CoreIdType, DLT_CONST) Dlt_CoreIds[DLT_NUMBER_OF_SATELLITES + 1U];

#endif /* (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON) */

/** \brief Type for storing context information of master core if
 **        BSW distribution is enabled. If BSW distribution is disabled,
 **        this type stores only a pointer to the context Id table. */
typedef struct
{
  Dlt_BSWDistributionCommonType         CoreContext;
    /**< Basic information field */
  Dlt_EnterExclusiveAreaFctPtrType      EnterExclusiveArea;
    /**< Pointer to wrapper function Dlt_EnterExclusiveAreaMaster() */
  Dlt_ExitExclusiveAreaFctPtrType       ExitExclusiveArea;
    /**< Pointer to wrapper function Dlt_ExitExclusiveAreaMaster() */
#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)
  Dlt_MasterSendSyncTableFctPtrArr      MasterSendSyncTable;
    /**< Array of pointers to SchM_Send_Dlt_MasterSendSyncTablePort_<n>() functions */
  Dlt_MasterReceiveMessageFctPtr        MasterReceiveMessage;
    /**< Pointer to SchM_Receive_Dlt_MasterReceiveMessagePort */
  Dlt_MasterReceiveContextMessageFctPtr MasterReceiveContextMessage;
    /**< Pointer to SchM_Receive_Dlt_MasterReceiveContextMessagePort */
#if (DLT_IMPLEMENT_NV_RAM_STORAGE == STD_ON)
  Dlt_MasterReceiveSessionIdFctPtr      MasterReceiveSession;
    /**< Pointer to SchM_Receive_Dlt_MasterReceiveSessionIdPort */
#endif /* (DLT_IMPLEMENT_NV_RAM_STORAGE == STD_ON) */

#endif /* (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON) */
} Dlt_BSWMasterContextType;

/*==================[external function declarations]========================*/
#define DLT_START_SEC_CODE
#include <Dlt_MemMap.h>

/** \brief Wrapper functions for entering and exiting exclusive areas
 ** on the currently active Dlt instance.
 **/
extern FUNC(void, DLT_CODE) Dlt_EnterExclusiveAreaAnyCoreContext(void);
extern FUNC(void, DLT_CODE) Dlt_ExitExclusiveAreaAnyCoreContext(void);

/** \brief Function to copy a 32 bit data into byte array
 **
 ** Use this function to copy specified 32 bit data to
 ** specified destination.
 **
 ** \param[in]      Dword       Data source
 ** \param[out]     DesPtr      Address of the data destination */
extern FUNC(void, DLT_CODE) Dlt_WriteDwordToByteArray
(
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DesPtr,
  uint32 Dword
);
/** \brief Function for internal handling of registered pairs of contextID and
 ** Application ID
 **
 ** \param[in] session_id number of the module (Module ID within BSW,
 **     port defined argument value within SW-C)
 ** \param[in] app_id the Application ID
 ** \param[in] context_id the Context ID
 ** \param[in] app_description Points to description string for the
 **     provided application id. At maximum 255 characters are
 **     interpreted.
 ** \param[in] LogLevel the log level
 ** \param[in] TraceStatus the trace status
 ** \param[in] VerboseMode the verbose mode
 ** \param[in] OverwriteEntry TRUE  - the existing entries will be overwritten
 **                           FALSE - error is returned in case of existing registration
 **
 ** \return Result of registering the context
 ** \retval DLT_E_OK context has been registered successfully
 ** \retval DLT_E_NOT_OK context has not been registered successfully
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 ** */
extern FUNC(Dlt_ReturnType, DLT_CODE) Dlt_InternalRegisterContext(
    Dlt_SessionIDType session_id,
    Dlt_Internal_ApplicationIDType app_id,
    Dlt_Internal_ContextIDType context_id,
    P2VAR(Dlt_BSWDistributionCommonType, DLT_VAR, DLT_VAR) CoreContext,
    P2CONST(uint8, DLT_CONST, DLT_CONST) AppDesc,
    uint8 AppDescLen,
    boolean OverwriteEntry);

/** \brief Find entry in ApplicationId Table
  * This function returns the index of the entry in the AppId table if an entry exists.
  * If no entry exists, the function returns the index of the next free entry.
  ** \param[in] app_id application ID
  ** \param[in] LocalCoreContext pointer to the working context table
  ** \param[in-out] aIdx ApplicationId index of the entry/next free entry
  ** \return Result of search True if the entry was found / was created
  **                          False if a new entry was not possible
  */
extern FUNC(void, DLT_CODE) Dlt_FindApplicationIDEntry(
    Dlt_SessionIDType session_id,
    Dlt_Internal_ApplicationIDType app_id,
    CONSTP2CONST(Dlt_BSWDistributionCommonType, AUTOMATIC, DLT_APPL_DATA) LocalCoreContext,
    P2VAR(Dlt_AppIdTableIdxType, AUTOMATIC, DLT_APPL_DATA) aIdx);

/** \brief Find if the context requested to be registered already exists or not.
 **  This function checks whether the context_id has already been registered
 **  for the given app_id, identified by the index of the applciationId.
 **
 ** \param[in]  contextId    context ID
 ** \param[in]  aIdx          ApplicationId index
 ** \param[out] citIdx        ContextIdTable index. If the context is already registered,
 **                           it contains the index of that entry in Dlt_ContextIdTable.
 **                           If the context is not registered, the index points to the
 **                           next free entry in the Dlt_ContextIdTable.
 ** \param[out] applToCitIdx  Index of a registered ContextId to the given ApplicationId index.
 **                           If the contextId is already registered, it contains the index of
 **                           that entry in Dlt_AppToContextIdTable.
 **                           If the contextId is not registered, the index points to the
 **                           last free entry in Dlt_AppToContextIdTable table.
 **
 ** \return boolean   Result of search.
 ** \retval TRUE      The context to be registered with the applicationID is not found.
 ** \retval FALSE     The context is already registered.
 */
extern FUNC(boolean, DLT_CODE) Dlt_CheckForRegisteredContext(
    Dlt_Internal_ContextIDType contextId,
    Dlt_AppIdTableIdxType aIdx,
    P2VAR(Dlt_ContextIdTableIdxType, AUTOMATIC, DLT_APPL_DATA) citIdx,
    P2VAR(Dlt_AppToContextIdTableIdxType, AUTOMATIC, DLT_APPL_DATA) applToCitIdx);

/** \brief Common send message service
 **
 ** This is the common service used by Dlt_SendLogMessage and
 ** Dlt_SendTraceMessage to create and send Dlt messages.
 **
 ** \param[in] session_id Session id of the message
 ** \param[in] msg_info Common message info struct
 ** \param[in] msg_data Pointer to the message payload
 ** \param[in] msg_data_length Length of the message
 ** \param[in] ServiceId ServiceId corresponding to the message type (log or trace message)
 ** \param[in] timestamp Continuous time / ticks from the ECU at the moment the message
                         is sent to Dlt.
 **
 ** \return Result of sending the message
 ** \retval DLT_E_OK The required operation succeeded
 ** \retval DLT_E_MSG_TOO_LARGE The message is too large for
 **                             sending over the network
 ** \retval DLT_E_IF_NOT_AVAILABLE The interface is not
 **                                available
 ** \retval DLT_E_UNKNOWN_SESSION_ID The provided session id
 **                                  is unknown
 ** \retval DLT_E_NOT_IN_VERBOSE_MODE Unable to send the message
 **                                   in verbose mode
 **/
#if (DLT_PROTOCOL_VERSION == 2U)
extern FUNC(Dlt_ReturnType, DLT_CODE) Dlt_InternalSendMessage(
    Dlt_ChnIdTableIdxType chnIdx,
    Dlt_SessionIDType session_id,
    P2CONST(Dlt_MessageCommonInfoType, AUTOMATIC, DLT_APPL_CONST) msg_info,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) msg_data,
    Dlt_MsgLengthType msg_data_length,
    uint8 ServiceId,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) timestamp,
    P2CONST(Dlt_MessageAttributesType, AUTOMATIC, DLT_APPL_CONST) attributes);
#else
extern FUNC(Dlt_ReturnType, DLT_CODE) Dlt_InternalSendMessage(
    Dlt_ChnIdTableIdxType chnIdx,
    Dlt_SessionIDType session_id,
    P2CONST(Dlt_MessageCommonInfoType, AUTOMATIC, DLT_APPL_CONST) msg_info,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) msg_data,
    Dlt_MsgLengthType msg_data_length,
    uint8 ServiceId,
    uint32 timestamp);
#endif
#if (DLT_IMPLEMENT_VFB_TRACE == STD_ON)

/** \brief Calls Dlt_SendTraceMessage() for VFB hook functions
 **
 ** This function handles the transmission of the trace hook function messages.
 **
 **/
extern FUNC(void, DLT_CODE) Dlt_SendTraceMessageForHookFunctions(void);

#if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11))
extern FUNC(boolean, DLT_CODE) Dlt_CheckTraceStatusForContextId(P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) ContextId);
#else
extern FUNC(boolean, DLT_CODE) Dlt_CheckTraceStatusForContextId(Dlt_ContextIDType ContextId);
#endif

#if ((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11))
extern FUNC(void, DLT_CODE) Dlt_WriteCtxIdPayloadLengthMessageIdInVfbBuffer(
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) ContextId,
    const Dlt_MsgLengthType TraceDataLength,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) MessageId);
#else
extern FUNC(void, DLT_CODE) Dlt_WriteCtxIdPayloadLengthMessageIdInVfbBuffer(
    Dlt_ContextIDType ContextId,
    const Dlt_MsgLengthType TraceDataLength,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) MessageId);
#endif

extern FUNC(void, DLT_CODE) Dlt_WriteArgsInVfbBuffer(
    CONSTP2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) ArgumentName,
    const Dlt_MsgLengthType ArgumentSize);

extern FUNC(boolean, DLT_CODE) Dlt_IsSpaceAvailableInVfbBuffer(
    const Dlt_MsgLengthType TraceDataLength);

/** \brief Register VFB tracing hooks
 **
 ** This function registers the contexts assigned to the VFB
 ** tracing hooks in the Dlt module. The function itself is
 ** generated code, depending on the amount and type of VFB
 ** data to trace. It is called during Dlt_Init().
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DLT_CODE) Dlt_RegisterVFBContexts(void);

#endif /* #if (DLT_IMPLEMENT_VFB_TRACE == STD_ON) */

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)
FUNC(Dlt_ReturnType, DLT_CODE) Dlt_SendLogMessageWithAttributesWrapper(
    Dlt_SessionIDType session_id,
    P2CONST(Dlt_MessageLogInfoType, AUTOMATIC, DLT_APPL_CONST) log_info,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) log_data,
    uint16 log_data_length,
    P2CONST(Dlt_MessageAttributesType, AUTOMATIC, DLT_APPL_CONST) attributes);

FUNC(Dlt_ReturnType, DLT_CODE) Dlt_SendTraceMessageWithAttributesWrapper(
    Dlt_SessionIDType session_id,
    P2CONST(Dlt_MessageTraceInfoType, AUTOMATIC, DLT_APPL_CONST) trace_info,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) trace_data,
    uint16 trace_data_length,
    P2CONST(Dlt_MessageAttributesType, AUTOMATIC, DLT_APPL_CONST) attributes);

#if (DLT_PROTOCOL_VERSION == 2U)
FUNC(Dlt_ReturnType, DLT_CODE) Dlt_SendLogMessageV2Wrapper(
    Dlt_SessionIDType session_id,
    P2CONST(Dlt_MessageLogInfoType, AUTOMATIC, DLT_APPL_CONST) log_info,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) log_data,
    uint16 log_data_length);

FUNC(Dlt_ReturnType, DLT_CODE) Dlt_SendTraceMessageV2Wrapper(
    Dlt_SessionIDType session_id,
    P2CONST(Dlt_MessageTraceInfoType, AUTOMATIC, DLT_APPL_CONST) trace_info,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) trace_data,
    uint16 trace_data_length);
#endif
#endif

#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)

/** \brief Send settings to satellites
 **
 ** On the master core:
 ** This function sends required config information to the
 ** satellites via SchM. The transmitted information is the
 ** default log level, the default trace status, the global
 ** filter status as well as the context id table.
 **
 ** On a satellite core:
 ** This function returns without action.
 **
 ** \param[in] SatelliteIndex The Satellite index (into Dlt_RetrySendSyncTable) for which to send
 **                         config info. DLT_ALL_SATELLITES  value can be used for transmission
 **                         to all satellites.
 */
extern FUNC(void, DLT_CODE) Dlt_SendTablesToSatellites(uint8 SatelliteIndex);

/** \brief Receive settings from master
 **
 ** On the master core:
 ** This function returns without action.
 **
 ** On a satellite core:
 ** This function receives required config information from the
 ** master via SchM. The transmitted information is the
 ** default log level, the default trace status, the global
 ** filter status as well as the context id table.
 ** If a configuration setting has changed and the SW-C affected
 ** by that change is running on the same core as the satellite,
 ** this function also calls the SW-C's notification callback
 ** (if configured).
 */
extern FUNC(void, DLT_CODE) Dlt_ReceiveTablesFromMaster(void);

/** \brief Function to retrieve the correct context of the slaves */
extern FUNC_P2CONST(Dlt_BSWSatelliteContextType, AUTOMATIC, DLT_CODE) Dlt_GetSatelliteContextPtr(void);

#endif /* (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON) */

/** \brief Wrapper functions for entering and exiting exclusive areas
 ** on the master Dlt instance.
 **/
extern FUNC(void, DLT_CODE) Dlt_EnterExclusiveAreaMaster(void);
extern FUNC(void, DLT_CODE) Dlt_ExitExclusiveAreaMaster(void);

#if (DLT_IMPLEMENT_NV_RAM_STORAGE == STD_ON)
/** \brief Retrieve last registered index for a pair of ApplicationId and ContextId.
 **
 ** This function shall be used when persistent storage functionality is enabled
 ** and default data is restored via NvMInitCbk. The indexes shall be used in order
 ** to correctly access the registered pair of ApplicationId and ContextId when
 ** NvMWriteCbk is called after the NvMInitCbk.
 **
 ** \param[out] appIdIdx        Index of last registered ApplicationId
 ** \param[out] appToCtxRefIdx  Index of last registered ContextId for the given ApplcationId
 **
 */
extern FUNC(void, DLT_CODE) Dlt_GetLastRegisteredIndex
(
    P2VAR(Dlt_AppIdTableIdxType, AUTOMATIC, DLT_APPL_DATA) appIdIdx,
    P2VAR(Dlt_AppToContextIdTableIdxType, AUTOMATIC, DLT_APPL_DATA) appToCtxRefIdx
);

/** \brief Issues the requests to write into NvM blocks
 **
 ** This function fills the extended header fields into hdrbuf,
 ** according to the msg_info parameter and the global Dlt
 ** configuration settings.
 **
 ** \param[in] none
 **
 ** \return Result consistent with the write request to NvM,
 **                if it was accepted or not
 ** \retval DLT_E_ERROR_UNKNOWN The required operation failed.
 ** \retval DLT_E_OK The required operation succeeded.
 **
 **/
extern FUNC(Dlt_ReturnType, DLT_CODE) Dlt_IssueWriteRequestToNvM(void);

#endif /* DLT_IMPLEMENT_NV_RAM_STORAGE == STD_ON */

#if (DLT_RECEPTION_CONTROL_MESSAGES_ENABLED == STD_ON)

/** \brief Function to initialize receive processor
 **
 ** This function Initializes all variables used by
 ** receive processor. */
extern FUNC(void, DLT_CODE) Dlt_InitReceiveProcessor(void);

/** \brief Function to unpack receive data
 **
 ** This function unpacks the receive data and calls for execution of control
 ** messages. */
extern FUNC(void, DLT_CODE) Dlt_UnpackRxData(void);

/** \brief Trigger the response by storing the response in message buffer
 **
 ** \param[in] header Pointer to the source buffer containing the message header
 ** \param[in] payload Pointer to the source buffer containing the message payload
 ** \param[in] headerlen Length of the message header
 ** \param[in] datalen Length of the message payload
 **
 **/
#endif /* DLT_RECEPTION_CONTROL_MESSAGES_ENABLED == STD_ON */
#if (((DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431) && (DLT_REGISTER_CONTEXT_NOTIFICATION == STD_ON)) \
    || (DLT_RECEPTION_CONTROL_MESSAGES_ENABLED == STD_ON))
/** \brief Function to copy a 32 bit data into byte array
 **
 ** Use this function to copy specified 32 bit data to
 ** specified destination. The difference between
 **
 **
 ** \param[in]      Dword       Data source
 ** \param[out]     DesPtr      Address of the data destination
*/
extern FUNC(void, DLT_CODE) Dlt_WriteDwordToByteArrayPayload
(
  P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) DesPtr,
  uint32 Dword
);

extern FUNC(void, DLT_CODE) Dlt_SendResponse
(
  P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) header,
  P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) payload,
  uint8  headerlen,
  Dlt_MsgLengthType datalen
);

/** \brief This functions calculates Total Header Length for the response
 **
 ** \param[out] TotalHeaderLength response value;
 */
extern FUNC(uint8, DLT_CODE) Dlt_CalculateRespHdrLength(void);
#endif

#if (((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) && (DLT_PROTOCOL_VERSION == 2U))
extern FUNC(void, DLT_CODE) Dlt_CalculateAppIdLen(P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) AppId, P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) AppIdLength);
extern FUNC(void, DLT_CODE) Dlt_CalculateCtxIdLen(P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) CtxId, P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) CtxIdLength);
#endif

/** \brief Creates standard header fields
 **
 ** This function fills the standard header fields into hdrbuf,
 ** according to the session_id parameter and the global Dlt
 ** configuration settings.
 **
 ** \param[in] chidx Channel index for message counter
 ** \param[in] session_id The session id the data belongs to
 ** \param[in] hdrbuf Pointer to the header buffer array
 ** \param[in] nextidx Pointer to the index within the header buffer array
 ** \param[in] msglen The length of the message
 ** \param[in] timestamp The timestamp of the message
 **
 **/

#if (DLT_PROTOCOL_VERSION == 1U)
FUNC(void, DLT_CODE) Dlt_CreateStandardHeader(
   uint8 chidx,
   Dlt_SessionIDType session_id,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) hdrbuf,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) nexthdridx,
   Dlt_MsgLengthType MsgLen, uint32 timestamp);
#else
FUNC(void, DLT_CODE) Dlt_CreateStandardHeader(
   uint8 chidx,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) hdrbuf,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) nexthdridx,
   Dlt_MsgLengthType MsgLen,
   P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) timestamp,
   P2CONST(Dlt_MessageCommonInfoType, AUTOMATIC, DLT_APPL_CONST) msg_info,
   P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) msg_data,
   P2CONST(Dlt_MessageAttributesType, AUTOMATIC, DLT_APPL_CONST) attributes);
#endif

#if ((DLT_IMPLEMENT_EXTENDED_HEADER == STD_ON) || (DLT_PROTOCOL_VERSION == 2U))
/** \brief Creates extended header fields
 **
 ** This function fills the extended header fields into hdrbuf,
 ** according to the msg_info parameter and the global Dlt
 ** configuration settings.
 **
 ** \param[in] msg_info pointer to message's info structure
 ** \param[in] hdrbuf Pointer to the header buffer array
 ** \param[in] nextidx Pointer to the index within the header buffer array
 **
 ** \return The next free index within the header buffer array
 **/
#if (DLT_PROTOCOL_VERSION == 2U)
extern FUNC(void, DLT_CODE) Dlt_CreateExtendedHeader(
   P2CONST(Dlt_MessageCommonInfoType, AUTOMATIC, DLT_APPL_CONST) msg_info,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) hdrbuf,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) nexthdridx,
   Dlt_SessionIDType session_id,
   uint8 AppIdLen,
   uint8 CtxIdLen,
   P2CONST(Dlt_MessageAttributesType, AUTOMATIC, DLT_APPL_CONST) attributes);
#else
extern FUNC(void, DLT_CODE) Dlt_CreateExtendedHeader(
   P2CONST(Dlt_MessageCommonInfoType, AUTOMATIC, DLT_APPL_CONST) msg_info,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) hdrbuf,
   P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) nexthdridx);
#endif
#endif /* ((DLT_IMPLEMENT_EXTENDED_HEADER == STD_ON) || (DLT_PROTOCOL_VERSION == 2U)) */

/** \brief Get timestamp for the current message request
 **
 ** This function returns the value of the timestamp based on the chosen
 ** provider in the configuration. If the Os is chosen, the OS_GetTimeStamp API is used.
 ** If the StbM is chosen, the StbM_GetCurrentTime API is used.
 ** If the timestamp functionality is disabled, the function returns a timestamp equal to 0U.
 **
 ** \return Value of the timestamp
 **
 ** \retval Timestamp provided by the StbM module
 ** \retval Timestamp provided by the Os module
 ** \retval Timestamp equal to 0U when the timestamp functionality is disabled
 **
 **/
extern FUNC(uint32, DLT_CODE) Dlt_GetTimestamp(void);

#if (DLT_PROTOCOL_VERSION == 2U)
/** \brief Get timestamp for the current message request
 **
 ** This function calculates the timestamp for version 2 of the Dlt protocol.
 **/
extern FUNC(void, DLT_CODE) Dlt_GetTimestampVersion2(P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) Buffer);
#endif

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)

/** \brief Find entry in Channel ID Table
  * This function returns the index of the entry in the LogChannel table if an entry exists.
  * If no entry exists, the function returns the index of the next free entry.
  ** \param[in] LogChannelId Name of the log channel
  ** \param[out] logChannelIndex Index from the configuration tables of the log channel found
  */
extern FUNC(void, DLT_CODE) Dlt_FindChannelIdEntry(
    P2VAR(Dlt_ChnIdTableIdxType, AUTOMATIC, DLT_APPL_DATA) logChannelIndex,
    P2CONST(uint8, AUTOMATIC, DLT_APPL_CONST) LogChannelId
    );


/** \brief Function which returns log channel names to a specified buffer
 **
 ** The function returns to the caller all log channel names copied from the configuration tables.
 **
 ** \param[in/out] LogChannelBuffer Buffer where data shall be copied
 ** \param[in] logChannelIndex index of the log channel in the configuration tables
 **/
extern FUNC(void, DLT_CODE) Dlt_ReturnLogChannelName
(
    P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) LogChannelBuffer,
    Dlt_ChnIdTableIdxType logChannelIndex
);

#endif

#if (((DLT_DEFAULT_ASR_RETVAL == AUTOSAR_431) || (DLT_DEFAULT_ASR_RETVAL == AUTOSAR_20_11)) && (DLT_PROTOCOL_VERSION == 2U))
/** \brief Function which copies the AppId in the expected endianness
 **
 ** \param[out] dest Buffer where data shall be copied
 ** \param[in] source Pointer to the array from which data is copied
 **/
extern FUNC(void, DLT_CODE) Dlt_PrepareAppId(
  P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) dest,
  P2CONST(uint8, DLT_CONST, DLT_CONST) source);

/** \brief Function which copies the CtxId in the expected endianness
 **
 ** \param[out] dest Buffer where data shall be copied
 ** \param[in] source Pointer to the array from which data is copied
 **/
extern FUNC(void, DLT_CODE) Dlt_PrepareCtxId(
  P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) dest,
  P2CONST(uint8, DLT_CONST, DLT_CONST) source);

/** \brief Function which copies the AppId in the expected endianness
 **
 ** \param[out] dest Buffer where data shall be copied
 ** \param[in] source Pointer to the array from which data is copied
 **/
extern FUNC(void, DLT_CODE) Dlt_FillAppIdInBuffer(
  P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) dest,
  P2CONST(uint8, DLT_CONST, DLT_CONST) source,
  uint8 length);

/** \brief Function which copies the CtxId in the expected endianness
 **
 ** \param[out] dest Buffer where data shall be copied
 ** \param[in] source Pointer to the array from which data is copied
 **/
extern FUNC(void, DLT_CODE) Dlt_FillCtxIdInBuffer(
  P2VAR(uint8, AUTOMATIC, DLT_APPL_DATA) dest,
  P2CONST(uint8, DLT_CONST, DLT_CONST) source,
  uint8 length);

/** \brief Function to check the value of the AppId/CtxId.
 **
 ** \param[out] dest Buffer where data shall be copied
 ** \param[in] source Pointer to the array from which data is copied
 ** \param[in] size Number of elements that shall be copied
 **/
extern FUNC(boolean, DLT_CODE) Dlt_CompareAppOrCtxId(
  CONSTP2CONST(uint8, DLT_CONST, DLT_CONST) dest,
  CONSTP2CONST(uint8, DLT_CONST, DLT_CONST) source,
  CONST(uint8, DLT_CONST) size);

/** \brief Function to check if the AppId value is Null AppId.
 **
 ** \param[in] value Pointer to the array where the AppId value is held
 **/
extern FUNC(boolean, DLT_CODE) Dlt_CheckIfAppIdIsNull(Dlt_ApplicationIDType Value);

/** \brief Function to check if the ContextId value is Null AppId.
 **
 ** \param[in] value Pointer to the array where the ContextId value is held
 **/
extern FUNC(boolean, DLT_CODE) Dlt_CheckIfCtxIdIsNull(Dlt_ContextIDType Value);
#endif

#define DLT_STOP_SEC_CODE
#include <Dlt_MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
/** \brief byte index of least significant byte in a uint32 value for little
 * endian architectures */
#define DLT_UINT32_SB0_IDX 0U
/** \brief byte index of 2nd least significant byte in a uint32 value for
 * little endian architectures */
#define DLT_UINT32_SB1_IDX 1U
/** \brief byte index of 3rd least significant byte in a uint32 value for
 * little endian architectures */
#define DLT_UINT32_SB2_IDX 2U
/** \brief byte index of 4th least significant byte in a uint32 value for
 * little endian architectures */
#define DLT_UINT32_SB3_IDX 3U
#else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */

/** \brief byte index of least significant byte in a uint32 value for big
 * endian architectures */
#define DLT_UINT32_SB0_IDX 3U
/** \brief byte index of 2nd least significant byte in a uint32 value for big
 * endian architectures */
#define DLT_UINT32_SB1_IDX 2U
/** \brief byte index of 3rd least significant byte in a uint32 value for big
 * endian architectures */
#define DLT_UINT32_SB2_IDX 1U
/** \brief byte index of 4th least significant byte in a uint32 value for big
 * endian architectures */
#define DLT_UINT32_SB3_IDX 0U

#endif /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
/*==================[external data]=========================================*/

#define DLT_START_SEC_VAR_CLEARED_8
#include <Dlt_MemMap.h>

/** \brief Global message counter **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderMessageCounter[DLT_TXPDU_NO];

#define DLT_STOP_SEC_VAR_CLEARED_8
#include <Dlt_MemMap.h>

#define DLT_START_SEC_VAR_INIT_8
#include <Dlt_MemMap.h>

/** \brief Bit value of the WEID standard header field **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderUseEcuId;
#if (DLT_PROTOCOL_VERSION == 1U)
/** \brief Bit value of the UEH standard header field **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderUseExtendedHeader;
#endif
/** \brief Bit value of the WSID standard header field **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderUseSessionID;
#if ((DLT_PROTOCOL_VERSION == 1U) && (DLT_IMPLEMENT_TIMESTAMP != STD_OFF))
/** \brief Bit value of the WTMS standard header field **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderUseTimestamp;

#endif
/** \brief Value of the verbose mode **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderUseVerboseMode;
/** \brief Default log level for log messages */
extern VAR(Dlt_MessageLogLevelType, DLT_VAR) Dlt_DefaultLogLevel;
/** \brief Default trace status for trace messages */
extern VAR(Dlt_MessageTraceStatusType, DLT_VAR) Dlt_DefaultTraceStatus;
/** \brief Default status for message filtering */
extern VAR(Dlt_FilterMessagesType, DLT_VAR) Dlt_FilterMessages;

/** \brief Current length of the message header **/
extern VAR(uint8, DLT_VAR) Dlt_HeaderLength;

extern VAR(uint8, DLT_VAR) Dlt_InitStateMaster;

#if (DLT_IMPLEMENT_VFB_TRACE == STD_ON)
extern VAR(uint8, DLT_VAR) Dlt_TraceData[DLT_VFB_TRACE_PAYLOAD_BUFFER_SIZE];
extern VAR(uint8, DLT_VAR) Dlt_LocalTraceData[DLT_VFB_TRACE_PAYLOAD_MAX_SIZE];
extern VAR(uint8, DLT_VAR) Dlt_NoOfMessagesInVfbBuffer;
extern VAR(boolean, DLT_VAR) Dlt_IsVfbBufferFull;
#endif /* #if (DLT_IMPLEMENT_VFB_TRACE == STD_ON) */

#define DLT_STOP_SEC_VAR_INIT_8
#include <Dlt_MemMap.h>

#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)

#define DLT_START_SEC_VAR_INIT_MC_SHARED_8
#include <Dlt_MemMap.h>

/** \brief Global logging enable / disable flag */
extern VAR(Dlt_GlobalLogStatusType, DLT_VAR) Dlt_GlobalLogStatus;

#define DLT_STOP_SEC_VAR_INIT_MC_SHARED_8
#include <Dlt_MemMap.h>

#else /* DLT_ENABLE_BSW_DISTRIBUTION == STD_OFF */

#define DLT_START_SEC_VAR_INIT_8
#include <Dlt_MemMap.h>

/** \brief Global logging enable / disable flag */
extern VAR(Dlt_GlobalLogStatusType, DLT_VAR) Dlt_GlobalLogStatus;

#define DLT_STOP_SEC_VAR_INIT_8
#include <Dlt_MemMap.h>

#endif /* DLT_ENABLE_BSW_DISTRIBUTION == STD_ON */

#if (DLT_IMPLEMENT_VFB_TRACE == STD_ON)

#if (TS_SIZE_PduLengthType == 2U)
#define DLT_START_SEC_VAR_INIT_16
#include <Dlt_MemMap.h>

extern VAR(Dlt_MsgLengthType, DLT_VAR) Dlt_TraceDataWriteIdx;
extern VAR(Dlt_MsgLengthType, DLT_VAR) Dlt_TraceDataReadIdx;

#define DLT_STOP_SEC_VAR_INIT_16
#include <Dlt_MemMap.h>
#else /* #if (TS_SIZE_PduLengthType == 4U) */
#define DLT_START_SEC_VAR_INIT_32
#include <Dlt_MemMap.h>

extern VAR(Dlt_MsgLengthType, DLT_VAR) Dlt_TraceDataWriteIdx;
extern VAR(Dlt_MsgLengthType, DLT_VAR) Dlt_TraceDataReadIdx;

#define DLT_STOP_SEC_VAR_INIT_32
#include <Dlt_MemMap.h>
#endif /* #if (TS_SIZE_PduLengthType == 2U) */

#endif /* #if (DLT_IMPLEMENT_VFB_TRACE == STD_ON) */

#define DLT_START_SEC_VAR_INIT_32
#include <Dlt_MemMap.h>
/** \brief The current maximum bandwidth allowed by the traffic shaper */
extern VAR(uint32, DLT_VAR) Dlt_BandwidthForComModule;
#define DLT_STOP_SEC_VAR_INIT_32
#include <Dlt_MemMap.h>

#define DLT_START_SEC_VAR_CLEARED_32
#include <Dlt_MemMap.h>

/** \brief Next free entry in Dlt_ContextIdTable */
extern VAR(Dlt_ContextIdTableIdxType, DLT_VAR)       Dlt_ContextIdTableIdx;

#define DLT_STOP_SEC_VAR_CLEARED_32
#include <Dlt_MemMap.h>

#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)

#define DLT_START_SEC_VAR_CLEARED_MC_SHARED_UNSPECIFIED
#include <Dlt_MemMap.h>

/** \brief Next free entry in Dlt_AppIdTable */
extern VAR(Dlt_AppIdTableIdxType, DLT_VAR) Dlt_MaxRegisteredAppldTableEntry;
/** \brief Next free entry in Dlt_AppToContextIdTable */
extern VAR(Dlt_AppToContextIdTableIdxType, DLT_VAR) Dlt_AppToContextIdTableIdx[DLT_MAX_COUNT_APP_IDS];
/** \brief Mapping between Application Id and Context Id table */
extern VAR(Dlt_AppIdTableType, DLT_VAR) Dlt_AppIdTable[DLT_MAX_COUNT_APP_IDS];
/** \brief List of Context Ids per Application Id */
extern VAR(Dlt_AppToContextIdTableType, DLT_VAR) Dlt_AppToContextIdTable[DLT_MAX_COUNT_APP_IDS];
/** \brief Mapping between Context Ids and Session Ids */
extern VAR(Dlt_ContextIdTableType, DLT_VAR) Dlt_ContextIdTable[DLT_MAX_COUNT_CONTEXT_IDS];

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)
#if (DLT_SWC_REGISTERED_NO > 0U)
/** \brief Session Id table */
extern VAR(Dlt_SessionIdTableType, DLT_VAR) Dlt_SessionIdTable[DLT_SWC_REGISTERED_NO];
#endif
/** \brief Runtime variable for channel id table */
extern VAR(Dlt_LogChannelThresholdInfoType, DLT_VAR) Dlt_LogChannelThresholdInfo[DLT_TXPDU_NO];
#endif

#define DLT_STOP_SEC_VAR_CLEARED_MC_SHARED_UNSPECIFIED
#include <Dlt_MemMap.h>

#else /* DLT_ENABLE_BSW_DISTRIBUTION == STD_OFF */

#define DLT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dlt_MemMap.h>

/** \brief Next free entry in Dlt_AppIdTable */
extern VAR(Dlt_AppIdTableIdxType, DLT_VAR) Dlt_MaxRegisteredAppldTableEntry;
/** \brief Next free entry in Dlt_AppToContextIdTable */
extern VAR(Dlt_AppToContextIdTableIdxType, DLT_VAR) Dlt_AppToContextIdTableIdx[DLT_MAX_COUNT_APP_IDS];
/** \brief Mapping between Application Id and Context Id table */
extern VAR(Dlt_AppIdTableType, DLT_VAR) Dlt_AppIdTable[DLT_MAX_COUNT_APP_IDS];
/** \brief List of Context Ids per Application Id */
extern VAR(Dlt_AppToContextIdTableType, DLT_VAR) Dlt_AppToContextIdTable[DLT_MAX_COUNT_APP_IDS];
/** \brief Mapping between Context Ids and Session Ids */
extern VAR(Dlt_ContextIdTableType, DLT_VAR) Dlt_ContextIdTable[DLT_MAX_COUNT_CONTEXT_IDS];

#if (DLT_DEFAULT_ASR_RETVAL >= AUTOSAR_431)
#if (DLT_SWC_REGISTERED_NO > 0U)
/** \brief Session Id table */
extern VAR(Dlt_SessionIdTableType, DLT_VAR) Dlt_SessionIdTable[DLT_SWC_REGISTERED_NO];
#endif
/** \brief Runtime variable for channel id table */
extern VAR(Dlt_LogChannelThresholdInfoType, DLT_VAR) Dlt_LogChannelThresholdInfo[DLT_TXPDU_NO];
#endif

#define DLT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dlt_MemMap.h>

#endif /* DLT_ENABLE_BSW_DISTRIBUTION == STD_ON */

#define DLT_START_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>

extern CONSTP2CONST(Dlt_BSWMasterContextType, DLT_CONST, DLT_CONST) Dlt_BSWMasterContextPtr;

extern CONST(Dlt_BSWMasterContextType, DLT_CONST) Dlt_BSWMasterContext;
#if (DLT_ENABLE_BSW_DISTRIBUTION == STD_ON)
/** \brief This table contains pointers to the contexts of different cores. */
extern CONST(Dlt_BSWSatelliteContextType, DLT_CONST) Dlt_BSWSatelliteContextTable[DLT_NUMBER_OF_SATELLITES];
#endif

#define DLT_STOP_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>


/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef DLT_INT_H */
/*==================[end of file]===========================================*/
