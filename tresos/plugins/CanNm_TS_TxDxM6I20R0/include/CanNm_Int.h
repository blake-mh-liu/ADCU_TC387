/**
 * \file
 *
 * \brief AUTOSAR CanNm
 *
 * This file contains the implementation of the AUTOSAR
 * module CanNm.
 *
 * \version 6.20.6
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CANNM_INT_H
#define CANNM_INT_H

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 * Reason:
 * The macro is used in function parameter declarations and definitions where the number of
 * parentheses matter.
 *
 */

/*===============================[includes]=================================*/

#include <TSAutosar.h>          /* EB specific standard types */
/* !LINKSTO CanNm.SWS_CanNm_00309,1 */
#include <NmStack_Types.h>      /* Nm specific types */

#include <CanNm_Api.h>              /* Types and decl. from public API */
#include <CanNm_Hsm.h>          /* public API of CanNm_Hsm.c */
#include <CanNm_Cfg.h>          /* Module configuration */
/* !LINKSTO CanNm.SWS_CanNm_00305,1 */
#include <ComStack_Types.h>     /* Include for PduInfoType */

#if (defined TS_RELOCATABLE_CFG_ENABLE)
#error TS_RELOCATABLE_CFG_ENABLE is already defined
#endif
#define TS_RELOCATABLE_CFG_ENABLE CANNM_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig.h>           /* relocatable post-build macros */
#include <TSPBConfig_Access.h>

#if (CANNM_MULTICORE_ENABLED == STD_ON)
#include <SchM_CanNm.h>
#endif

#if ((CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON) && (CANNM_DEV_ERROR_DETECT == STD_ON))
#include <Os.h>
#endif

/*===========================[macro definitions]============================*/

#if (defined CANNM_DET_REPORT_ERROR)
#error CANNM_DET_REPORT_ERROR already defined
#endif

/* define function like macro for development error reporting,
 * if development error detection is enabled */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO CanNm.ASR403.CANNM019,1 */
/** \brief Macro for reporting an error to DET
 **
 ** \param[in] InstanceId Instance ID of the API function
 ** \param[in] ServiceId Service ID of the API function
 ** \param[in] ErrorCode Error code reported to Det module */
#define CANNM_DET_REPORT_ERROR(InstanceId, ServiceId, ErrorCode)    \
  ((void)Det_ReportError(CANNM_MODULE_ID, (InstanceId), (ServiceId), (ErrorCode)))
#else
#define CANNM_DET_REPORT_ERROR(InstanceId, ServiceId, ErrorCode)
#endif /* if (COMM_DEV_ERROR_DETECT == STD_ON) */

/* define function like macro for runtime development error reporting */
#if (CANNM_DET_RUNTIME_CHECKS == STD_ON)
#if (defined CANNM_DET_REPORT_RUNTIME_ERROR)
#error CANNM_DET_REPORT_RUNTIME_ERROR already defined
#endif
/** \brief Macro for reporting a runtime error to DET
 **
 ** \param[in] InstanceId Instance ID of the API function
 ** \param[in] ServiceId Service ID of the API function
 ** \param[in] ErrorCode Error code reported to Det module */
#define CANNM_DET_REPORT_RUNTIME_ERROR(InstanceId, ServiceId, ErrorCode)    \
  ((void)Det_ReportRuntimeError(CANNM_MODULE_ID, (InstanceId), (ServiceId), (ErrorCode)))
#endif /* (CANNM_DET_RUNTIME_CHECKS == STD_ON) */

/** \brief Macro to create a bitmask with single bit set at specified position
 ** (BitPos)
 **
 ** \param[in] BitPos - Bit position */
#if (defined CANNM_BITPOS2MASK)
#error CANNM_BITPOS2MASK is already defined
#endif
#define CANNM_BITPOS2MASK(BitPos) ((uint8)(1U << (BitPos)))

/** \brief Define CANNM_BUSLOADREDACTIVE */
#if (defined CANNM_BUSLOADREDACTIVE)
#error CANNM_BUSLOADREDACTIVE is already defined
#endif
#define CANNM_BUSLOADREDACTIVE          0U

/** \brief The maximum PDU size */
#if (defined CANNM_MAX_PDU_SIZE)
#error CANNM_MAX_PDU_SIZE is already defined
#endif
#define CANNM_MAX_PDU_SIZE             8U

/* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00045,2 */
/** \brief Bit position of the Repeat message bit in the TX/RX PDU */
#if (defined CANNM_CBV_REPEATMESSAGEBIT)
#error CANNM_CBV_REPEATMESSAGEBIT is already defined
#endif
#define CANNM_CBV_REPEATMESSAGEBIT      0U

/* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00045,2 */
/** \brief Bit position of the Active Wake Up Bit in the CBV */
#if (defined CANNM_CBV_ACTIVEWAKEUPBIT)
#error CANNM_CBV_ACTIVEWAKEUPBIT is already defined
#endif
#define CANNM_CBV_ACTIVEWAKEUPBIT       4U

/* Internal State */
/* The numbers describe bit positions */
#if (defined CANNM_COM_DISABLED_BIT)
#error CANNM_COM_DISABLED_BIT is already defined
#endif
#define CANNM_COM_DISABLED_BIT               0U

#if (defined CANNM_NET_REQUESTED_BIT)
#error CANNM_NET_REQUESTED_BIT is already defined
#endif
#define CANNM_NET_REQUESTED_BIT             1U

/* bit 3 is used for setting Remote sleep indication status */
#if (defined CANNM_RSI_TRUE_BIT)
#error CANNM_RSI_TRUE_BIT is already defined
#endif
#define CANNM_RSI_TRUE_BIT 3U

#if (defined CANNM_RMS_ENTERED_FROM_NM_BIT)
#error CANNM_RMS_ENTERED_FROM_NM_BIT already defined
#endif
#define CANNM_RMS_ENTERED_FROM_NM_BIT         0U

#if (defined CANNM_MESSAGE_SENT_ON_CYCLE_BIT)
#error CANNM_MESSAGE_SENT_ON_CYCLE_BIT already defined
#endif
#define CANNM_MESSAGE_SENT_ON_CYCLE_BIT       1U

#if (defined CANNM_EXECUTE_IMMEDIATE_RESTART_BIT)
#error CANNM_EXECUTE_IMMEDIATE_RESTART_BIT already defined
#endif
#define CANNM_EXECUTE_IMMEDIATE_RESTART_BIT   2U

#if (defined CANNM_IN_REPEAT_MESSAGE_STATE_BIT)
#error CANNM_IN_REPEAT_MESSAGE_STATE_BIT already defined
#endif
#define CANNM_IN_REPEAT_MESSAGE_STATE_BIT     3U

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
/* PnSyncShutdown flag used to indicate a PN sync shutdown was received */
#if (defined CANNM_PN_SYNC_SHUTDOWN_RCV_BIT)
#error CANNM_PN_SYNC_SHUTDOWN_RCV_BIT already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_RCV_BIT        1U

#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
/* PnSyncShutdown flag used to indicate a PN sync shutdown Tx confirmation was received */
#if (defined CANNM_PN_SYNC_SHUTDOWN_TX_BIT)
#error CANNM_PN_SYNC_SHUTDOWN_TX_BIT already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_TX_BIT         2U
#endif /* (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0) */

/* message flag used to indicate a PN sync shutdown message was
   received on an active channel */
#if (defined CANNM_PN_SYNC_SHUTDOWN_INVMSG_BIT)
#error CANNM_PN_SYNC_SHUTDOWN_INVMSG_BIT already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_INVMSG_BIT    4U

#if (defined CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX_BIT)
#error CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX_BIT already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX_BIT    5U

#if (defined CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD_BIT)
#error CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD_BIT already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD_BIT   6U

#endif /* (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON) */

/* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00045,2 */
/** \brief Bit position of the Partial Netork Information Bit in the TX/RX PDU
 */
#if (defined CANNM_CBV_PNINFOBIT)
#error CANNM_CBV_PNINFOBIT is already defined
#endif
#define CANNM_CBV_PNINFOBIT                                6U

#if (defined CANNM_CBV_PNINFOBITMASK)
#error CANNM_CBV_PNINFOBITMASK is already defined
#endif
#define CANNM_CBV_PNINFOBITMASK CANNM_BITPOS2MASK(CANNM_CBV_PNINFOBIT)

/** \brief Bit position of the PN Shutdown Request Bit (PNSR) Bit in the TX/RX PDU
 */
#if (defined CANNM_CBV_PNSRBIT)
#error CANNM_CBV_PNSRBIT is already defined
#endif
#define CANNM_CBV_PNSRBIT                                  1U

#if (defined CANNM_CBV_PNSRBITMASK)
#error CANNM_CBV_PNSRBITMASK is already defined
#endif
#define CANNM_CBV_PNSRBITMASK CANNM_BITPOS2MASK(CANNM_CBV_PNSRBIT)

/* Macro when EIRA Timer usage is not used. It is used for mapping
 * PN Index and EIRA timer array */
#if (defined CANNM_EIRA_TIMER_INVALID)
#error CANNM_EIRA_TIMER_INVALID is already defined
#endif
#define CANNM_EIRA_TIMER_INVALID    0xFFFFU

/* bit 3 is used for setting Remote sleep indication status */
#if (defined CANNM_RSI_TRUE)
#error CANNM_RSI_TRUE is already defined
#endif
#define CANNM_RSI_TRUE                     \
   CANNM_BITPOS2MASK(CANNM_RSI_TRUE_BIT)

/* Bitmasks for Internal States */
#if (defined CANNM_COM_DISABLED)
#error CANNM_COM_DISABLED is already defined
#endif
#define CANNM_COM_DISABLED                     \
   CANNM_BITPOS2MASK(CANNM_COM_DISABLED_BIT)

#if (defined CANNM_NETWORK_REQUESTED)
#error CANNM_NETWORK_REQUESTED is already defined
#endif
#define CANNM_NETWORK_REQUESTED               \
   CANNM_BITPOS2MASK(CANNM_NET_REQUESTED_BIT)

#if (defined CANNM_BUS_LOAD_RED_ENABLED)
#error CANNM_BUS_LOAD_RED_ENABLED is already defined
#endif
#define CANNM_BUS_LOAD_RED_ENABLED            \
   CANNM_BITPOS2MASK(CANNM_BUS_LOAD_RED)

#if (defined CANNM_CHANNEL_CONFIG_BUSLOADREDACTIVE)
#error CANNM_CHANNEL_CONFIG_BUSLOADREDACTIVE is already defined
#endif
#define CANNM_CHANNEL_CONFIG_BUSLOADREDACTIVE(a) \
   ((CANNM_CHANNEL_CONFIG(a).CCFlags & CANNM_BITPOS2MASK(CANNM_BUSLOADREDACTIVE)) != 0U)

#if (defined CANNM_RMS_ENTERED_FROM_NM)
#error CANNM_RMS_ENTERED_FROM_NM is already defined
#endif
#define CANNM_RMS_ENTERED_FROM_NM \
   CANNM_BITPOS2MASK(CANNM_RMS_ENTERED_FROM_NM_BIT)

#if (defined CANNM_MESSAGE_SENT_ON_CYCLE)
#error CANNM_MESSAGE_SENT_ON_CYCLE is already defined
#endif
#define CANNM_MESSAGE_SENT_ON_CYCLE \
   CANNM_BITPOS2MASK(CANNM_MESSAGE_SENT_ON_CYCLE_BIT)

#if (defined CANNM_EXECUTE_IMMEDIATE_RESTART)
#error CANNM_EXECUTE_IMMEDIATE_RESTART is already defined
#endif
#define CANNM_EXECUTE_IMMEDIATE_RESTART \
   CANNM_BITPOS2MASK(CANNM_EXECUTE_IMMEDIATE_RESTART_BIT)

#if (defined CANNM_IN_REPEAT_MESSAGE_STATE)
#error CANNM_IN_REPEAT_MESSAGE_STATE_BIT is already defined
#endif
#define CANNM_IN_REPEAT_MESSAGE_STATE \
   CANNM_BITPOS2MASK(CANNM_IN_REPEAT_MESSAGE_STATE_BIT)

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
#if (defined CANNM_PN_SYNC_SHUTDOWN_RCV)
#error CANNM_PN_SYNC_SHUTDOWN_RCV is already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_RCV \
   CANNM_BITPOS2MASK(CANNM_PN_SYNC_SHUTDOWN_RCV_BIT)

#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
#if (defined CANNM_PN_SYNC_SHUTDOWN_TX)
#error CANNM_PN_SYNC_SHUTDOWN_TX is already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_TX \
   CANNM_BITPOS2MASK(CANNM_PN_SYNC_SHUTDOWN_TX_BIT)
#endif /* (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0) */

#if (defined CANNM_PN_SYNC_SHUTDOWN_INVMSG)
#error CANNM_PN_SYNC_SHUTDOWN_INVMSG is already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_INVMSG \
   CANNM_BITPOS2MASK(CANNM_PN_SYNC_SHUTDOWN_INVMSG_BIT)

#if (defined CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX)
#error CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX is already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX \
   CANNM_BITPOS2MASK(CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX_BIT)

#if (defined CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD)
#error CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD is already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD \
   CANNM_BITPOS2MASK(CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD_BIT)

#if (defined CANNM_GATEWAY_TYPE_UNUSED)
#error CANNM_GATEWAY_TYPE_UNUSED already defined
#endif
#define CANNM_GATEWAY_TYPE_UNUSED     0U

#if (defined CANNM_GATEWAY_TYPE_PASSIVE)
#error CANNM_GATEWAY_TYPE_PASSIVE already defined
#endif
#define CANNM_GATEWAY_TYPE_PASSIVE    1U

#if (defined CANNM_GATEWAY_TYPE_ACTIVE)
#error CANNM_GATEWAY_TYPE_ACTIVE already defined
#endif
#define CANNM_GATEWAY_TYPE_ACTIVE     2U

#endif /* (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON) */

#if (defined CANNM_CHANNEL_STATUS)
#error CANNM_CHANNEL_STATUS is already defined
#endif

#if (defined CANNM_CHANNEL_CONFIG)
#error CANNM_CHANNEL_CONFIG is already defined
#endif

#if (defined CANNM_CHANNEL_BUFFER_OFFSET)
#error CANNM_CHANNEL_BUFFER_OFFSET already defined
#endif

#if (defined CANNM_CHANNEL_USERDATALENGTH)
#error CANNM_CHANNEL_USERDATALENGTH is already defined
#endif

#if (defined CANNM_CHANNEL_MSGCYCLEOFFSET)
#error CANNM_CHANNEL_MSGCYCLEOFFSET is already defined
#endif

#if (defined CANNM_CHANNEL_PDULENGTH)
#error CANNM_CHANNEL_PDULENGTH is already defined
#endif

#if (defined CANNM_CHANNEL_USERTXCONFPDUID)
#error CANNM_CHANNEL_USERTXCONFPDUID is already defined
#endif

#if (defined CANNM_CHANNEL_USERRXPDUID)
#error CANNM_CHANNEL_USERRXPDUID is already defined
#endif

#if (defined CANNM_CHANNEL_TXPDUID)
#error CANNM_CHANNEL_TXPDUID is already defined
#endif

#if (defined CANNM_CHANNEL_NODEID)
#error CANNM_CHANNEL_NODEID is already defined
#endif

#if (defined CANNM_CHANNEL_PNENABLED)
#error CANNM_CHANNEL_PNENABLED is already defined
#endif

#if (defined CANNM_CHANNEL_PN_HANDLE_MULTI_REQ)
#error CANNM_CHANNEL_PN_HANDLE_MULTI_REQ is already defined
#endif

#if (defined CANNM_CHANNEL_USERRXPDUENABLED)
#error CANNM_CHANNEL_USERRXPDUENABLED is already defined
#endif


#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
#define CANNM_CHANNEL_STATUS(a)            CanNm_ChanStatus[(a)]
#define CANNM_CHANNEL_CONFIG(a)            CanNm_ChanConfig[(a)]
#define CANNM_CHANNEL_BUFFER_OFFSET(a)    (CanNm_RootPtr->BufferOffsets[(a)])
#define CANNM_CHANNEL_USERDATALENGTH(a)   (CanNm_RootPtr->CanNm_ChannelData[(a)].UserDataLength)
#define CANNM_CHANNEL_MSGCYCLEOFFSET(a)   (CanNm_RootPtr->CanNm_ChannelData[(a)].CanNmMsgCycleOffset)
#define CANNM_CHANNEL_PDULENGTH(a)        (CanNm_RootPtr->CanNm_ChannelData[(a)].RxPduLength)
#define CANNM_CHANNEL_USERTXCONFPDUID(a)  (CanNm_RootPtr->CanNm_ChannelData[(a)].UserTxConfPduId)
#define CANNM_CHANNEL_USERRXPDUID(a)      (CanNm_RootPtr->CanNm_ChannelData[(a)].UserRxPduId)
#define CANNM_CHANNEL_TXPDUID(a)          (CanNm_RootPtr->CanNm_ChannelData[(a)].TxPduId)
#define CANNM_CHANNEL_NODEID(a)           (CanNm_RootPtr->CanNm_ChannelData[(a)].CanNmNodeId)
#define CANNM_CHANNEL_PNENABLED(a)        (CanNm_RootPtr->CanNm_ChannelData[(a)].PnEnabled)
#define CANNM_CHANNEL_PN_HANDLE_MULTI_REQ(a)    \
                                          (CanNm_RootPtr->CanNm_ChannelData[(a)].PnHandleMultipleNetworkRequests)
#define CANNM_CHANNEL_USERRXPDUENABLED(a) (CanNm_RootPtr->CanNm_ChannelData[(a)].UserRxPduEnabled)
#else
#define CANNM_CHANNEL_STATUS(a)            CanNm_ChanStatus[0]
#define CANNM_CHANNEL_CONFIG(a)            CanNm_ChanConfig[0]
#define CANNM_CHANNEL_BUFFER_OFFSET(a)    (CanNm_RootPtr->BufferOffsets[(0)])
#define CANNM_CHANNEL_USERDATALENGTH(a)   (CanNm_RootPtr->CanNm_ChannelData[(0)].UserDataLength)
#define CANNM_CHANNEL_MSGCYCLEOFFSET(a)   (CanNm_RootPtr->CanNm_ChannelData[(0)].CanNmMsgCycleOffset)
#define CANNM_CHANNEL_PDULENGTH(a)        (CanNm_RootPtr->CanNm_ChannelData[(0)].RxPduLength)
#define CANNM_CHANNEL_USERTXCONFPDUID(a)  (CanNm_RootPtr->CanNm_ChannelData[(0)].UserTxConfPduId)
#define CANNM_CHANNEL_USERRXPDUID(a)      (CanNm_RootPtr->CanNm_ChannelData[(0)].UserRxPduId)
#define CANNM_CHANNEL_TXPDUID(a)          (CanNm_RootPtr->CanNm_ChannelData[0].TxPduId)
#define CANNM_CHANNEL_NODEID(a)           (CanNm_RootPtr->CanNm_ChannelData[(0)].CanNmNodeId)
#define CANNM_CHANNEL_PNENABLED(a)        (CanNm_RootPtr->CanNm_ChannelData[(0)].PnEnabled)
#define CANNM_CHANNEL_PN_HANDLE_MULTI_REQ(a)    \
                                          (CanNm_RootPtr->CanNm_ChannelData[(0)].PnHandleMultipleNetworkRequests)
#define CANNM_CHANNEL_USERRXPDUENABLED(a) (CanNm_RootPtr->CanNm_ChannelData[(0)].UserRxPduEnabled)
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_NetworkStartIndication,1 */
#if (defined CANNM_CALL_NM_NETWORKSTARTINDICATION)
#error CANNM_CALL_NM_NETWORKSTARTINDICATION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_NetworkMode,1 */
#if (defined CANNM_CALL_NM_NETWORKMODE)
#error CANNM_CALL_NM_NETWORKMODE already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_BusSleepMode,1 */
#if (defined CANNM_CALL_NM_BUSSLEEPMODE)
#error CANNM_CALL_NM_BUSSLEEPMODE already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_PrepareBusSleepMode,1 */
#if (defined CANNM_CALL_NM_PREPAREBUSSLEEPMODE)
#error CANNM_CALL_NM_PREPAREBUSSLEEPMODE already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_RemoteSleepIndication,1 */
#if (defined CANNM_CALL_NM_REMOTESLEEPINDICATION)
#error CANNM_CALL_NM_REMOTESLEEPINDICATION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_RemoteSleepCancellation,1 */
#if (defined CANNM_CALL_NM_REMOTESLEEPCANCELLATION)
#error CANNM_CALL_NM_REMOTESLEEPCANCELLATION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_PduRxIndication,1 */
#if (defined CANNM_CALL_NM_PDURXINDICATION)
#error CANNM_CALL_NM_PDURXINDICATION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_StateChangeNotification,1 */
#if (defined CANNM_CALL_NM_STATECHANGENOTIFICATION)
#error CANNM_CALL_NM_STATECHANGENOTIFICATION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_RepeatMessageIndication,1 */
#if (defined CANNM_CALL_NM_REPEATMESSAGEINDICATION)
#error CANNM_CALL_NM_REPEATMESSAGEINDICATION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_TxTimeoutException,1 */
#if (defined CANNM_CALL_NM_TXTIMEOUTEXCEPTION)
#error CANNM_CALL_NM_TXTIMEOUTEXCEPTION already defined
#endif

/* !LINKSTO CanNm.EB.SchM_Call_Nm_CarWakeUpIndication,1 */
#if (defined CANNM_CALL_NM_CARWAKEUPINDICATION)
#error CANNM_CALL_NM_CARWAKEUPINDICATION already defined
#endif

/* !LINKSTO CanNm.EB.Config.CanNmMultiCoreSupport,1 */
#if(CANNM_MULTICORE_ENABLED == STD_ON)

/** \brief SchM_Call for Nm_NetworkStartIndication */
#define CANNM_CALL_NM_NETWORKSTARTINDICATION(idx) \
   CANNM_CHANNEL_CONFIG(idx).NetworkStartIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_NetworkMode */
#define CANNM_CALL_NM_NETWORKMODE(idx) \
   CANNM_CHANNEL_CONFIG(idx).NetworkMode(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_BusSleepMode */
#define CANNM_CALL_NM_BUSSLEEPMODE(idx) \
   CANNM_CHANNEL_CONFIG(idx).BusSleepMode(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_PrepareBusSleepMode */
#define CANNM_CALL_NM_PREPAREBUSSLEEPMODE(idx) \
   CANNM_CHANNEL_CONFIG(idx).PrepareBusSleepMode(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_RemoteSleepIndication */
#define CANNM_CALL_NM_REMOTESLEEPINDICATION(idx) \
   CANNM_CHANNEL_CONFIG(idx).RemoteSleepIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_RemoteSleepCancellation */
#define CANNM_CALL_NM_REMOTESLEEPCANCELLATION(idx) \
   CANNM_CHANNEL_CONFIG(idx).RemoteSleepCancellation(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_PduRxIndication */
#define CANNM_CALL_NM_PDURXINDICATION(idx) \
   CANNM_CHANNEL_CONFIG(idx).PduRxIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_StateChangeNotification */
#define CANNM_CALL_NM_STATECHANGENOTIFICATION(idx,v0,v1) \
   CANNM_CHANNEL_CONFIG(idx).StateChangeNotification(CANNM_CHANNEL_CONFIG(idx).nmChannelId,v0,v1)

/** \brief SchM_Call for Nm_RepeatMessageIndication */
#define CANNM_CALL_NM_REPEATMESSAGEINDICATION(idx) \
   CANNM_CHANNEL_CONFIG(idx).RepeatMessageIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_TxTimeoutException */
#define CANNM_CALL_NM_TXTIMEOUTEXCEPTION(idx) \
   CANNM_CHANNEL_CONFIG(idx).TxTimeoutException(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

/** \brief SchM_Call for Nm_CarWakeUpIndication */
#define CANNM_CALL_NM_CARWAKEUPINDICATION(idx) \
   CANNM_CHANNEL_CONFIG(idx).CarWakeUpIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#else
#define CANNM_CALL_NM_NETWORKSTARTINDICATION(idx) \
   Nm_NetworkStartIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_NETWORKMODE(idx) \
   Nm_NetworkMode(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_BUSSLEEPMODE(idx) \
   Nm_BusSleepMode(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_PREPAREBUSSLEEPMODE(idx) \
   Nm_PrepareBusSleepMode(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_REMOTESLEEPINDICATION(idx) \
   Nm_RemoteSleepIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_REMOTESLEEPCANCELLATION(idx) \
   Nm_RemoteSleepCancellation(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_PDURXINDICATION(idx) \
   Nm_PduRxIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_STATECHANGENOTIFICATION(idx,v0,v1) \
   Nm_StateChangeNotification(CANNM_CHANNEL_CONFIG(idx).nmChannelId,v0,v1)

#define CANNM_CALL_NM_REPEATMESSAGEINDICATION(idx) \
   Nm_RepeatMessageIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_TXTIMEOUTEXCEPTION(idx) \
   Nm_TxTimeoutException(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#define CANNM_CALL_NM_CARWAKEUPINDICATION(idx) \
   Nm_CarWakeUpIndication(CANNM_CHANNEL_CONFIG(idx).nmChannelId)

#endif

#if (defined CANNM_TX_BUFFER_OFFSET)
#error CANNM_TX_BUFFER_OFFSET already defined
#endif
#define CANNM_TX_BUFFER_OFFSET            (CanNm_RootPtr->TxBufferOffset)

#if (defined PB_REQUIRED_CFG_RAM_SIZE)
#error PB_REQUIRED_CFG_RAM_SIZE already defined
#endif
#define PB_REQUIRED_CFG_RAM_SIZE          (LocalConfigPtr->PbRequiredCfgRamSize)

/** \brief Start Tx Timeout Timer.
 ** \param instIdx index of state machine instance to work on */
#if (defined CANNM_TX_TIMER_START)
#error CANNM_TX_TIMER_START is already defined
#endif
#define CANNM_TX_TIMER_START(instIdx,TimeoutTime)       \
  do                                                    \
  {                                                     \
    CANNM_CHANNEL_STATUS(instIdx).TimeoutTimer          \
      = (TimeoutTime);   \
  } while (0)

/** \brief Stop Tx Timeout Timer.
 ** \param instIdx index of state machine instance to work on */
#if (defined CANNM_TX_TIMER_STOP)
#error CANNM_TX_TIMER_STOP is already defined
#endif
#define CANNM_TX_TIMER_STOP(instIdx)                    \
  do                                                    \
  {                                                     \
    CANNM_CHANNEL_STATUS(instIdx).TimeoutTimer = 0U;    \
  } while (0)

#if (defined CANNM_NETWORK_GW_ERA_REQUEST_AWB)
#error CANNM_NETWORK_GW_ERA_REQUEST_AWB already defined
#endif /* if (defined CANNM_NETWORK_GW_ERA_REQUEST_AWB) */
#define CANNM_NETWORK_GW_ERA_REQUEST_AWB                   3U

#if (defined CANNM_PASSIVE_STARTUP_AWB)
#error CANNM_PASSIVE_STARTUP_AWB already defined
#endif /* if (defined CANNM_PASSIVE_STARTUP_AWB) */
#define CANNM_PASSIVE_STARTUP_AWB                          2U

#if (defined CANNM_NETWORK_REQUEST_AWB)
#error CANNM_NETWORK_REQUEST_AWB already defined
#endif /* if (defined CANNM_NETWORK_REQUEST_AWB) */
#define CANNM_NETWORK_REQUEST_AWB                          1U

#if (defined CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA)
#error CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA already defined
#endif /* #if (defined CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA) */

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
#define CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(instIdx) CANNM_CHANNEL_CONFIG(instIdx).ChannelEnterExclusiveArea()
#else
#define CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(instIdx) SchM_Enter_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_0()
#endif

#if (defined CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA)
#error CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA already defined
#endif /* #if (defined CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA) */

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
#define CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(instIdx) CANNM_CHANNEL_CONFIG(instIdx).ChannelExitExclusiveArea()
#else
#define CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(instIdx) SchM_Exit_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_0()
#endif

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
/** \brief Invalid channel handle */
#if (defined CANNM_MAIN_PARTITION_HANDLE)
#error CANNM_MAIN_PARTITION_HANDLE is already defined
#endif
#define CANNM_MAIN_PARTITION_HANDLE    0xFFU
#endif

/** \brief Represent the mask on the last 3 bits.
 ** This macro is used for getting the bit index from a uint8
 */
#if (defined MASK_3_BITS)
#error MASK_3_BITS already defined
#endif
#define MASK_3_BITS  0x07U
/** \brief Represent the 3 LSB masked by MASK_3_BITS
 ** This macro is used for getting the byte index from an array of uint8
 ** The 5 MSB represents the byte array index
 */
#if (defined SHIFT_3_BITS)
#error SHIFT_3_BITS already defined
#endif
#define SHIFT_3_BITS 0x03U

/** \brief Macro to indicate the value of operation passive startup
 */
#if (defined CANNM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
#error CANNM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP is already defined
#endif
#define CANNM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP 0U

/** \brief Macro to indicate the value of operation network request
 */
#if (defined CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)
#error CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST is already defined
#endif
#define CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST 1U

/** \brief Macro to indicate the value of operation network release
 */
#if (defined CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)
#error CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE is already defined
#endif
#define CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE 2U

/*==================[type definitions]======================================*/

/** \brief Definition of the CanNm_TimeType */
typedef uint16 CanNm_TimeType;

/** \brief Definition of the CanNm_NodeIdType */
typedef uint8 CanNm_NodeIdType;

#if (CANNM_MULTICORE_ENABLED == STD_ON)
typedef Std_ReturnType (*CanNm_Nm_CallsFctPtrType1)(uint8 data);
typedef Std_ReturnType (*CanNm_Nm_CallsFctPtrType2)(uint8 data0,uint8 data1,uint8 data2);
#endif

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
typedef Std_ReturnType (*CanNm_ChannelPnInfo_SchmSend_FctPtr)(P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) data);
typedef Std_ReturnType (*CanNm_MainPnInfo_SchmRecieve_FctPtr)(P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) data);
typedef void (*CanNm_ChannelEnterExclusiveArea_FctPtr)(void);
typedef void (*CanNm_ChannelExitExclusiveArea_FctPtr)(void);
#endif

/** \brief Type for the channel configuration
 **
 ** This type stores the static data of a CANNM channels */
typedef struct
{
#if (CANNM_MULTICORE_ENABLED == STD_ON)
  CanNm_Nm_CallsFctPtrType1 NetworkStartIndication;
  CanNm_Nm_CallsFctPtrType1 NetworkMode;
  CanNm_Nm_CallsFctPtrType1 BusSleepMode;
  CanNm_Nm_CallsFctPtrType1 PrepareBusSleepMode;
#if (CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
  CanNm_Nm_CallsFctPtrType1 RemoteSleepIndication;
  CanNm_Nm_CallsFctPtrType1 RemoteSleepCancellation;
#endif
#if (CANNM_PDU_RX_INDICATION_ENABLED == STD_ON)
  CanNm_Nm_CallsFctPtrType1 PduRxIndication;
#endif
#if (CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
  CanNm_Nm_CallsFctPtrType2 StateChangeNotification;
#endif
#if (CANNM_REPEAT_MSG_IND_ENABLED == STD_ON)
  CanNm_Nm_CallsFctPtrType1 RepeatMessageIndication;
#endif
#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && \
     (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
  CanNm_Nm_CallsFctPtrType1 TxTimeoutException;
#endif
#if (CANNM_CARWAKEUP_RX_ENABLED == STD_ON)
  CanNm_Nm_CallsFctPtrType1 CarWakeUpIndication;
#endif
#endif
  CanNm_TimeType    CanNmTime;
  CanNm_TimeType    RMSTime;
  CanNm_TimeType    WBSTime;
  CanNm_TimeType    RSITime;
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if (CANNM_IMMEDIATE_TRANSMISSION == STD_ON)
  CanNm_TimeType    ImmediateNmTransmissions;
  CanNm_TimeType    ImmediateNmCycleTime;
#endif /* (CANNM_IMMEDIATE_TRANSMISSION == STD_ON) */
  CanNm_TimeType    MsgCycleTime;
#if (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
  CanNm_TimeType    MsgTimeoutTime;
#endif
#if (CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
  CanNm_TimeType    ReducedTime;
#endif
#endif /* passive mode not enabled */
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  PduIdType         TxConfPduId;
#endif
#if ((CANNM_REPEAT_MSG_IND_ENABLED == STD_ON) &&  \
     (CANNM_NODE_DETECTION_ENABLED == STD_ON))
  PduIdType         RxPduId;
#endif
#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
  PduIdType         UserTxPduId;
#endif
#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
  PduIdType         EraPduId;
  uint8             EraCalcEnabled;
#endif
  uint8             CCFlags;
  uint8             NidPos;
  uint8             CbvPos;
  uint8             UDFBPos;
  NetworkHandleType nmChannelId;
  boolean           AllNmMessagesKeepAwake; /* CANNM068_Conf */
#if (CANNM_CARWAKEUP_RX_ENABLED == STD_ON)
  uint8             CanNmCarWakeUpBitPosition;
  uint8             CanNmCarWakeUpBytePosition;
  uint8             CanNmCarWakeUpFilterNodeId;
  boolean           CanNmCarWakeUpFilterEnabled;
  boolean           CanNmCarWakeUpRxEnabled;
#endif
  boolean           CanNmRepeatMsgIndEnabled;
  boolean           CanNmNodeDetectionEnabled;
  boolean           CanNmNodeIdEnabled;
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
  CanNm_ChannelPnInfo_SchmSend_FctPtr ChannelPnInfoSend;
#endif
  CanNm_ChannelEnterExclusiveArea_FctPtr ChannelEnterExclusiveArea;
  CanNm_ChannelExitExclusiveArea_FctPtr ChannelExitExclusiveArea;
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  ApplicationType   ChannelApplicationID;
#endif
#endif
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
  uint8             CanNmTypeOfGateway;
#endif
} CanNm_ChanConfigType;

#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)  || (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
typedef struct
{
  /* !LINKSTO CanNm.SWS_CanNm_00438,1, CanNm.SWS_CanNm_00428,1 */
  CanNm_TimeType    PnTimer[CANNM_EIRA_MAX_TIMER_SIZE];
  uint8             PnValue[CANNM_PN_INFO_LENGTH];
  uint8             PnInfo[CANNM_PN_INFO_LENGTH];
  uint8             PnTempInfo[CANNM_PN_INFO_LENGTH];
}CanNm_PnStatusType;
#endif

/** \brief Type for PN ids
 **
 ** This type stores PN ids, and PN retransmision timer during a PNC synchronized shutdown */
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
typedef struct
{
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
  CanNm_TimeType    PnRetransmissionTimer;
  /* stores PnIds sent for wich there was trasnmitted a synchronized shutdown */
  uint8             PnInfoSent[CANNM_PN_INFO_LENGTH];
#endif
  /* stores all requests received from CanNm_RequestSynchronizedPncShutdown calls */
  uint8             PnInfoRcv[CANNM_PN_INFO_LENGTH];
  /* aggregates all CanNm_RequestSynchronizedPncShutdown received between 2 main functions calls */
  uint8             PnInfoAgg[CANNM_PN_INFO_LENGTH];
} CanNm_SynchronizedPncShutdownIdsType;

typedef struct
{
  /* stores all PN synchronized shutdown requests from messages from Bus */
  uint8 PnInfoRx[CANNM_PN_INFO_LENGTH];
#if (CANNM_MULTICORE_ENABLED == STD_ON)
  /* snapshot(buffer copy) of PnInfoRx on main function execution */
  Nm_PnSyncShutdown_BusNm_To_Nm_DataType PnInfoRxAgg;
#else
  /* snapshot(buffer copy) of PnInfoRx on main function execution */
  uint8 PnInfoRxAgg[CANNM_PN_INFO_LENGTH];
#endif
} CanNm_SynchronizedPncShutdownRxIdsType;
#endif

/** \brief Type for the channel state
 **
 ** This type stores the dynamic data of a CanNm channel; e.g. timers
 ** and states. */
typedef struct
{
  P2VAR(uint8, TYPEDEF, CANNM_VAR_CLEARED) RxPduPtr;
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  P2VAR(uint8, TYPEDEF, CANNM_VAR_CLEARED) TxPduPtr;
#endif
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
  P2VAR(CanNm_SynchronizedPncShutdownIdsType, TYPEDEF, CANNM_VAR_CLEARED)
                    CanNm_SynchronizedPncShutdownIdsPtr;
  P2VAR(CanNm_SynchronizedPncShutdownRxIdsType, TYPEDEF, CANNM_VAR_CLEARED)
                    CanNm_SynchronizedPncShutdownRxIdsPtr;
#endif
  CanNm_TimeType    CanNmTimer;
  CanNm_TimeType    UniversalTimer;
  CanNm_TimeType    RmsTimer;
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if (CANNM_IMMEDIATE_TRANSMISSION == STD_ON)
  CanNm_TimeType    ImmediateNmTransmissionCounter;
#endif /* (CANNM_IMMEDIATE_TRANSMISSION == STD_ON) */
  CanNm_TimeType    MsgCycleTimer;
#if (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
  CanNm_TimeType    TimeoutTimer;
#endif
#endif
#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
  CanNm_PnStatusType    Era;
#endif
  Nm_StateType      CurState;
  uint8             ChanStatus;
  uint8             MessageFlags;
#if (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
  uint8             ActiveWakeUp1;
  uint8             ActiveWakeUp2;
#endif
#if (CANNM_PN_SUPPORTED == STD_ON)
  boolean           PnFilterEnabled;
#endif
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
  uint8             PnSyncShutdownFlags;
#endif
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  boolean           NmTimerExpired;
  boolean           FirstCanIfTransmitOk;
#endif
} CanNm_ChanStatusType;

/*=====================[external function declarations]=====================*/
#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON) || (CANNM_PN_ERA_CALC_ENABLED == STD_ON)

/** \brief checks whether the received message is valid or not
 **
 ** This function checks whether the received message is valid or not.
 **
 ** \param[in] PduId Pdu Id of the received PDU.
 **
 ** \return Received message is valid or not.
 */
extern FUNC(boolean, CANNM_CODE) CanNm_IsValidPnMessage
(
  PduIdType PduId
);
#endif
#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>
/*=====================[internal function declarations]=====================*/

/* !LINKSTO CanNm.ASR403.CANNM311,1 */
#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>

/** \brief Process all timers.
 ** \param instIdx index of state machine instance to work on */
/* Deviation MISRAC2012-1 */
extern FUNC(void, CANNM_CODE) CanNm_HandleTimerTick(
  CANNM_PDL_SF(uint8 instIdx));

#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON) || (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
/** \brief Handles the EIRA/ERA accumulation
 **
 ** This function accumulate requests in the EIRA/ERA vector. If a change occur the timer is
 ** reseted and the PduR is notified via PduR_CanNmRxIndication callback.
 **
 ** \param[in] PnStatePtr Pointer to EIRA/ERA structure
 ** \param[in] PduId Id of the PDU used in CanNm_RxIndication callback
 ** \param[in] ChannelIndex index of channel for which ERA is handled, or
               CANNM_NUMBER_OF_CHANNELS value, for when EIRA data is processed
               on main partition
 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePnInfo
(
  P2VAR(CanNm_PnStatusType, AUTOMATIC, CANNM_VAR_CLEARED) PnStatePtr,
  PduIdType PduId,
  NetworkHandleType ChannelIndex
);
#else
/** \brief Handles the EIRA/ERA accumulation
 **
 ** This function accumulate requests in the EIRA/ERA vector. If a change occur the timer is
 ** reseted and the PduR is notified via PduR_CanNmRxIndication callback.
 **
 ** \param[in] PnStatePtr Pointer to EIRA/ERA structure
 ** \param[in] PduId Id of the PDU used in CanNm_RxIndication callback
 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePnInfo
(
  P2VAR(CanNm_PnStatusType, AUTOMATIC, CANNM_VAR_CLEARED) PnStatePtr,
  PduIdType PduId
);
#endif

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
/** \brief Handles sync shutdown requests accumulation
 **
 ** This function handles PN synchronous shutdown operations.
 **
 ** \param[in] index of channel
 */
/* Deviation MISRAC2012-1 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown
(
  CANNM_PDL_SF(uint8 index)
);

/** \brief Handles sync shutdown aggregation of requests on active channel
 **
 ** This function handles aggregation pn sync shutdown requests on active channel.
 **
 ** \param[in] index of channel
 */
/* Deviation MISRAC2012-1 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown_ActiveChAggregateReq
(
  CANNM_PDL_SF(uint8 index)
);

#if (CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED == STD_ON)
/** \brief Handles invalid pnsr bit reception on an active channel
 **
 ** This function handles invalid pnsr bit reception on an active channel.
 **
 ** \param[in] index of channel
 */
/* Deviation MISRAC2012-1 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown_ActiveChInvMsg
(
  CANNM_PDL_SF(uint8 index)
);
#endif

/** \brief Handles sync shutdown requests accumulation on passive channel
 **
 ** This function handles PN synchronous shutdown operations on passive channel.
 **
 ** \param[in] index of channel
 */
/* Deviation MISRAC2012-1 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown_PassiveCh
(
  CANNM_PDL_SF(uint8 index)
);

/** \brief Forwards PN sync shutdown info from received messages on bus to NM
 **
 ** This function handles NM forward synchronized Pnc shutdowns.
 **
 ** \param[in] index of channel
 */
/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdownForwardReq(
  CANNM_PDL_SF(uint8 index)
);

#endif

/** \brief Process the EIRA/ERA timers
 **
 ** This function decrement the timer for EIRA/ERA
 ** If the timer expires the change is communicate to PduR via the PduR_CanNmRxIndication callback
 **
 ** \param[in] pPnStatus Pointer to EIRA/ERA structure
 ** \param[in] PduId Id of the PDU used in PduR_CanNmRxIndication callback
 */
extern FUNC(void, CANNM_CODE) CanNm_HandlePnTimers
(
    P2VAR(CanNm_PnStatusType, AUTOMATIC, CANNM_VAR_CLEARED) pPnStatus,
    PduIdType PduId
);

/** \brief Aggregate the EIRA/ERA
 **
 ** This function aggregate and filter(based on CanNm_PnFilterMask) the recieved requests
 **
 ** \param[in] PnInfo Pointer to the EIRA/ERA structure member where the unfiltered
 **            requests are stored
 ** \param[in] pPnStatus Pointer to EIRA/ERA structure member where the filtered PN requests
 **            will be aggregated
 */
extern FUNC(void, CANNM_CODE) CanNm_AggregatePnInfo
(
  P2CONST(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfo,
  P2VAR(CanNm_PnStatusType, AUTOMATIC, CANNM_VAR_CLEARED) pPnStatus
);

/** \brief Aggregate the PN information
 **
 ** This function aggregates and filter(based on CanNm_PnFilterMask) PN information
 **
 ** \param[in] PnInfoDest Pointer to PN information structure member where the filtered PN
 **            information will be aggregated
 ** \param[in] PnInfoSrc Pointer to the PN information structure member where the unfiltered
 **            PN information is stored
 ** \param[in] PnInfoSetBits Boolean that indicates to set or unset bits in PnInfoDest for the
 **            bits hat are set in PnInfoSrc
 **            TRUE set bits in PnInfoDest that are also set in PnInfoSrc
 **            FALSE unset bits in PnInfoDest that are set in PnInfoSrc
 */
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
FUNC(void, CANNM_CODE) CanNm_AggregatePnInfoSyncShutdown
(
  P2VAR(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfoDest,
  P2CONST(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfoSrc
);
#endif

#endif

#if ((CANNM_COM_USER_DATA_SUPPORT == STD_ON) || (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))

extern FUNC(void, CANNM_CODE) CanNm_GetPduUserData
(
  uint8 instIdx,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) pduInfo
);

#endif

#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>

/*=====================[external constants declarations]====================*/
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include <CanNm_MemMap.h>

extern CONST(CanNm_ChanConfigType, CANNM_CONST)
   CanNm_ChanConfig[CANNM_NUMBER_OF_CHANNELS];

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include <CanNm_MemMap.h>

#define CANNM_START_SEC_CONST_8
#include <CanNm_MemMap.h>

extern CONST(NetworkHandleType, CANNM_CONST)
   CanNm_IndexFromNmChannelHandle[CANNM_INDEXFROMNMCHANNELHANDLE_NUM];

#define CANNM_STOP_SEC_CONST_8
#include <CanNm_MemMap.h>

/*=====================[internal constants declarations]====================*/

/*=======================[external data declarations]=======================*/

#define CANNM_START_SEC_VAR_INIT_8
#include <CanNm_MemMap.h>

/** \brief Intialization information of CanNm module */
extern VAR(boolean, CANNM_VAR) CanNm_Initialized;

#define CANNM_STOP_SEC_VAR_INIT_8
#include <CanNm_MemMap.h>

#define CANNM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanNm_MemMap.h>

/** \brief Declaration of the extern variable CanNm_ChanStatus */
extern VAR(CanNm_ChanStatusType, CANNM_VAR_CLEARED)
   CanNm_ChanStatus[CANNM_NUMBER_OF_CHANNELS];

extern P2CONST(CanNm_ConfigType, CANNM_VAR_CLEARED, CANNM_APPL_DATA) CanNm_RootPtr;

#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
extern VAR(CanNm_PnStatusType, CANNM_VAR_CLEARED) CanNm_EiraStatus;
#endif

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
#if (CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM > 0)
extern VAR(CanNm_SynchronizedPncShutdownIdsType, CANNM_VAR_CLEARED)
  CanNm_SynchronizedPncShutdownIds[CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM];
#endif

#if (CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM > 0)
extern VAR(CanNm_SynchronizedPncShutdownRxIdsType, CANNM_VAR_CLEARED)
  CanNm_SynchronizedPncShutdownRxIds[CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM];
#endif
#endif

#define CANNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanNm_MemMap.h>

#undef TS_RELOCATABLE_CFG_ENABLE

#endif /* ifndef CANNM_INT_H */

/*==============================[end of file]===============================*/
