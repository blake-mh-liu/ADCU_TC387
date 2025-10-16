/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/*
 *
 *  MISRAC2012-1) Deviated Rule: 8.9 (Advisory)
 *    An object should be defined at block scope if its identifier only appears in a single
 *    function.
 *
 *    Reason:
 *    - Object identifier is only seen in a single function because of compiler switch but otherwise
 *    appears in more than one function.
 *
 *  MISRAC2012-3) Deviated Rule: 8.4 (Advisory)
 *    A compatible declaration shall be visible when an object or function with external linkage
 *    is defined
 *
 *    Reason:
 *    CanTSyn_IcvGenerationIndication and CanTSyn_IcvVerificationIndication are declared by Csm.
 *
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 *
 * TASKING-2) Deviated Rule: W529
 * W529: overflow in constant expression of type "unsigned long int"
 *
 * Reason:
 * False-positive from the Tasking 63r1p5 compiler (see justification in ASCCANTSYN-203)
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h> /* Specific standard types */
#include <TSMem.h> /* EB memcopy */
#include <CanTSyn.h> /* Module public API */
#include <CanTSyn_Int.h>
#include <CanTSyn_Trace.h> /* Debug and trace */
#include <CanIf.h> /* Module public API */
#include <SchM_CanTSyn.h> /* SchM interface header */

#if((CANTSYN_TX_CRC_USED == STD_ON) || (CANTSYN_RX_CRC_USED == STD_ON))
#include <Crc.h> /* CRC support */
#endif/* (CANTSYN_TX_CRC_USED == STD_ON) || (CANTSYN_RX_CRC_USED == STD_ON) */
#if(CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
#include <IdsM.h> /* security event reporting support */
#endif /* if(CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON) */
#if((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON))
#include <Csm.h> /* ICV authentication support */
#endif /* if((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)) */

/*==================[version check]=========================================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef CANTSYN_VENDOR_ID /* configuration check */
#error CANTSYN_VENDOR_ID must be defined
#endif

#if (CANTSYN_VENDOR_ID != 1U) /* vendor check */
#error CANTSYN_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef CANTSYN_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error CANTSYN_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANTSYN_AR_RELEASE_MAJOR_VERSION != 4U)
#error CANTSYN_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef CANTSYN_AR_RELEASE_MINOR_VERSION /* configuration check */
#error CANTSYN_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANTSYN_AR_RELEASE_MINOR_VERSION != 7U )
#error CANTSYN_AR_RELEASE_MINOR_VERSION wrong (!= 7U)
#endif

#ifndef CANTSYN_AR_RELEASE_REVISION_VERSION /* configuration check */
#error CANTSYN_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (CANTSYN_AR_RELEASE_REVISION_VERSION != 0U )
#error CANTSYN_AR_RELEASE_REVISION_VERSION wrong (!= 0U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef CANTSYN_SW_MAJOR_VERSION /* configuration check */
#error CANTSYN_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANTSYN_SW_MAJOR_VERSION != 5U)
#error CANTSYN_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#ifndef CANTSYN_SW_MINOR_VERSION /* configuration check */
#error CANTSYN_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANTSYN_SW_MINOR_VERSION < 0U)
#error CANTSYN_SW_MINOR_VERSION wrong (< 0U)
#endif

#ifndef CANTSYN_SW_PATCH_VERSION /* configuration check */
#error CANTSYN_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (CANTSYN_SW_PATCH_VERSION < 5U)
#error CANTSYN_SW_PATCH_VERSION wrong (< 5U)
#endif

/*==================[macros]================================================*/

#if (defined CANTSYN_MSG_SIZE) /* to prevent double declaration */
#error CANTSYN_MSG_SIZE is already defined
#endif /* if (defined CANTSYN_MSG_SIZE) */
#define CANTSYN_MSG_SIZE 8U /* Size of the CanTSyn messages */

#if (defined CANTSYN_EXTENDED_MSG_SIZE) /* to prevent double declaration */
#error CANTSYN_EXTENDED_MSG_SIZE is already defined
#endif /* if (defined CANTSYN_EXTENDED_MSG_SIZE) */
#define CANTSYN_EXTENDED_MSG_SIZE 16U /* Size of the CanTSyn extended messages */

#if (defined CANTSYN_NO_USERDATA) /* to prevent double declaration */
#error CANTSYN_NO_USERDATA is already defined
#endif /* if (defined CANTSYN_NO_USERDATA) */
#define CANTSYN_NO_USERDATA 0U /* No User Data support */

/* !LINKSTO CanTSyn.SWS_CanTSyn_00031,1 */
#if (defined CANTSYN_SYNC_WITHOUT_CRC) /* to prevent double declaration */
#error CANTSYN_SYNC_WITHOUT_CRC is already defined
#endif /* if (defined CANTSYN_SYNC_WITHOUT_CRC) */
#define CANTSYN_SYNC_WITHOUT_CRC 0x10U /* Sync Message with no CRC Type */

#if (defined CANTSYN_FUP_WITHOUT_CRC) /* to prevent double declaration */
#error CANTSYN_FUP_WITHOUT_CRC is already defined
#endif /* if (defined CANTSYN_FUP_WITHOUT_CRC) */
#define CANTSYN_FUP_WITHOUT_CRC  0x18U /* Fup Message with no CRC Type */

/* !LINKSTO CanTSyn.SWS_CanTSyn_00041,1 */

#if (defined CANTSYN_OFS_WITHOUT_CRC) /* to prevent double declaration */
#error CANTSYN_OFS_WITHOUT_CRC is already defined
#endif /* if (defined CANTSYN_OFS_WITHOUT_CRC) */
#define CANTSYN_OFS_WITHOUT_CRC  0x34U /* OFS Message with no CRC Type */

#if (defined CANTSYN_OFS_EXT_MSG_WITHOUT_CRC) /* to prevent double declaration */
#error CANTSYN_OFS_EXT_MSG_WITHOUT_CRC is already defined
#endif /* if (defined CANTSYN_OFS_EXT_MSG_WITHOUT_CRC) */
#define CANTSYN_OFS_EXT_MSG_WITHOUT_CRC  0x54U /* Extended OFS Message with no CRC Type */

#if (defined CANTSYN_OFNS_WITHOUT_CRC) /* to prevent double declaration */
#error CANTSYN_OFNS_WITHOUT_CRC is already defined
#endif /* if (defined CANTSYN_OFNS_WITHOUT_CRC) */
#define CANTSYN_OFNS_WITHOUT_CRC 0x3CU /* OFNS Message with no CRC Type */

#if (defined CANTSYN_SYNC_WITH_CRC) /* to prevent double declaration */
#error CANTSYN_SYNC_WITH_CRC is already defined
#endif /* if (defined CANTSYN_SYNC_WITH_CRC) */
#define CANTSYN_SYNC_WITH_CRC 0x20U /* Sync Message with CRC Type */

#if (defined CANTSYN_FUP_WITH_CRC) /* to prevent double declaration */
#error CANTSYN_FUP_WITH_CRC is already defined
#endif /* if (defined CANTSYN_FUP_WITH_CRC) */
#define CANTSYN_FUP_WITH_CRC  0x28U /* Fup Message with CRC Type */

#if (defined CANTSYN_OFS_WITH_CRC) /* to prevent double declaration */
#error CANTSYN_OFS_WITH_CRC is already defined
#endif /* if (defined CANTSYN_OFS_WITH_CRC) */
#define CANTSYN_OFS_WITH_CRC  0x44U /* Ofs Message with CRC Type */

#if (defined CANTSYN_OFS_EXT_MSG_WITH_CRC) /* to prevent double declaration */
#error CANTSYN_OFS_EXT_MSG_WITH_CRC is already defined
#endif /* if (defined CANTSYN_OFS_EXT_MSG_WIT_CRC) */
#define CANTSYN_OFS_EXT_MSG_WITH_CRC  0x64U /* Extended OFS Message with CRC Type */

#if (defined CANTSYN_OFNS_WITH_CRC) /* to prevent double declaration */
#error CANTSYN_OFNS_WITH_CRC is already defined
#endif /* if (defined CANTSYN_OFNS_WITH_CRC) */
#define CANTSYN_OFNS_WITH_CRC 0x4CU /* Ofns Message with CRC Type */

#if (defined CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH)
#error CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH)*/
#define CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH 0x78U

#if (defined CANTSYN_FUP_WITH_CRC_ICV_AUTH)
#error CANTSYN_FUP_WITH_CRC_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_FUP_WITH_CRC_ICV_AUTH)*/
#define CANTSYN_FUP_WITH_CRC_ICV_AUTH 0x88U

#if (defined CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH)
#error CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH)*/
#define CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH 0x94U

#if (defined CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH)
#error CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH)*/
#define CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH 0xA4U

#if (defined CANTSYN_SYNCMSG_SEND_WAIT) /* to prevent double declaration */
#error CANTSYN_SYNCMSG_SEND_WAIT is already defined
#endif /* if (defined CANTSYN_SYNCMSG_SEND_WAIT) */
#define CANTSYN_SYNCMSG_SEND_WAIT   0U /* The SYNC message is awaited to be sent */

#if (defined CANTSYN_SYNCMSG_WAIT_TXCONF) /* to prevent double declaration */
#error CANTSYN_SYNCMSG_WAIT_TXCONF is already defined
#endif /* if (defined CANTSYN_SYNCMSG_WAIT_TXCONF) */
#define CANTSYN_SYNCMSG_WAIT_TXCONF 1U /* Tx Confirmation for SYNC Message is awaited */

#if (defined CANTSYN_FUPMSG_SEND_WAIT) /* to prevent double declaration */
#error CANTSYN_FUPMSG_SEND_WAIT is already defined
#endif /* if (defined CANTSYN_FUPMSG_SEND_WAIT) */
#define CANTSYN_FUPMSG_SEND_WAIT    2U /* The FUP message is awaited to be sent */

#if (defined CANTSYN_FUPMSG_WAIT_TXCONF) /* to prevent double declaration */
#error CANTSYN_FUPMSG_WAIT_TXCONF is already defined
#endif /* if (defined CANTSYN_FUPMSG_WAIT_TXCONF) */
#define CANTSYN_FUPMSG_WAIT_TXCONF  3U /* Tx Confirmation for FUP Message is awaited */

#if (defined CANTSYN_OFSMSG_SEND_WAIT) /* to prevent double declaration */
#error CANTSYN_OFSMSG_SEND_WAIT is already defined
#endif /* if (defined CANTSYN_OFSMSG_SEND_WAIT) */
#define CANTSYN_OFSMSG_SEND_WAIT    4U /* The OFS message is awaited to be sent */

#if (defined CANTSYN_OFSMSG_WAIT_TXCONF) /* to prevent double declaration */
#error CANTSYN_OFSMSG_WAIT_TXCONF is already defined
#endif /* if (defined CANTSYN_OFSMSG_WAIT_TXCONF) */
#define CANTSYN_OFSMSG_WAIT_TXCONF  5U /* Tx Confirmation for OFS Message is awaited */

#if (defined CANTSYN_OFNSMSG_SEND_WAIT) /* to prevent double declaration */
#error CANTSYN_OFNSMSG_SEND_WAIT is already defined
#endif /* if (defined CANTSYN_OFNSMSG_SEND_WAIT) */
#define CANTSYN_OFNSMSG_SEND_WAIT   6U /* The OFNS message is awaited to be sent */

#if (defined CANTSYN_OFNSMSG_WAIT_TXCONF) /* to prevent double declaration */
#error CANTSYN_OFNSMSG_WAIT_TXCONF is already defined
#endif /* if (defined CANTSYN_OFNSMSG_WAIT_TXCONF) */
#define CANTSYN_OFNSMSG_WAIT_TXCONF 7U /* Tx Confirmation for OFNS Message is awaited */

#if (defined CANTSYN_SYNCMSG_RX_WAIT) /* to prevent double declaration */
#error CANTSYN_SYNCMSG_RX_WAIT is already defined
#endif /* if (defined CANTSYN_SYNCMSG_RX_WAIT) */
#define CANTSYN_SYNCMSG_RX_WAIT         0U /* The SYNC message is awaited to be received */

#if (defined CANTSYN_FUPMSG_RX_WAIT) /* to prevent double declaration */
#error CANTSYN_FUPMSG_RX_WAIT is already defined
#endif /* if (defined CANTSYN_FUPMSG_RX_WAIT) */
#define CANTSYN_FUPMSG_RX_WAIT          1U /* The FUP message is awaited to be received */

#if (defined CANTSYN_FUPMSG_RX_WAIT_TIMEOUT) /* to prevent double declaration */
#error CANTSYN_FUPMSG_RX_WAIT_TIMEOUT is already defined
#endif /* if (defined CANTSYN_FUPMSG_RX_WAIT_TIMEOUT) */
#define CANTSYN_FUPMSG_RX_WAIT_TIMEOUT  2U /* The FUP message is awaited to be received, FollowUpTimeout loaded */

#if (defined CANTSYN_OFSMSG_RX_WAIT) /* to prevent double declaration */
#error CANTSYN_OFSMSG_RX_WAIT is already defined
#endif /* if (defined CANTSYN_OFSMSG_RX_WAIT) */
#define CANTSYN_OFSMSG_RX_WAIT          3U /* The OFS message is awaited to be received */

#if (defined CANTSYN_OFNSMSG_RX_WAIT) /* to prevent double declaration */
#error CANTSYN_OFNSMSG_RX_WAIT is already defined
#endif /* if (defined CANTSYN_OFNSMSG_RX_WAIT) */
#define CANTSYN_OFNSMSG_RX_WAIT         4U /* The OFNS message is awaited to be received */

#if (defined CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT) /* to prevent double declaration */
#error CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT is already defined
#endif /* if (defined CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT) */
#define CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT 5U /* The OFNS message is awaited to be received, FollowUpTimeout loaded */

#if (defined CANTSYN_NANOSEC_MAX) /* to prevent double declaration */
#error CANTSYN_NANOSEC_MAX is already defined
#endif /* if (defined CANTSYN_NANOSEC_MAX) */
#define CANTSYN_NANOSEC_MAX (uint32)999999999U /* Maximum nanosecond value used to compute OVS (shall be 10^9ns-1) */

#if (defined CANTSYN_SC_MAXLIMIT) /* to prevent double declaration */
#error CANTSYN_SC_MAXLIMIT is already defined
#endif /* if (defined CANTSYN_SC_MAXLIMIT) */
#define CANTSYN_SC_MAXLIMIT 15U /* Limit of Sequence Counter */

#if (defined CANTSYN_SC_STARTUP_TIMEOUT) /* to prevent double declaration */
#error CANTSYN_SC_STARTUP_TIMEOUT is already defined
#endif /* if (defined CANTSYN_SC_STARTUP_TIMEOUT) */
#define CANTSYN_SC_STARTUP_TIMEOUT  (255U)

#if (defined CANTSYN_STBM_TIMEOUT) /* to prevent double declaration */
#error CANTSYN_STBM_TIMEOUT is already defined
#endif /* if (defined CANTSYN_STBM_TIMEOUT) */
#define CANTSYN_STBM_TIMEOUT  (1U)

/* Time Gateway synchronization status values */
#if (defined CANTSYN_SYNCTOGTM) /* to prevent double declaration */
#error CANTSYN_SYNCTOGTM is already defined
#endif /* if (defined CANTSYN_SYNCTOGTM) */
#define CANTSYN_SYNCTOGTM       0U

#if (defined CANTSYN_SYNCTOSUBDOMAIN) /* to prevent double declaration */
#error CANTSYN_SYNCTOSUBDOMAIN is already defined
#endif /* if (defined CANTSYN_SYNCTOSUBDOMAIN) */
#define CANTSYN_SYNCTOSUBDOMAIN 1U

#if (defined CANTSYN_SYNC_TO_GATEWAY_MASK) /* to prevent double declaration */
#error CANTSYN_SYNC_TO_GATEWAY_MASK is already defined
#endif /* if (defined CANTSYN_SYNC_TO_GATEWAY_MASK) */
#define CANTSYN_SYNC_TO_GATEWAY_MASK  4U

#if (defined CANTSYN_GLOBAL_TIME_BASE_MASK) /* to prevent double declaration */
#error CANTSYN_GLOBAL_TIME_BASE_MASK is already defined
#endif /* if (defined CANTSYN_GLOBAL_TIME_BASE_MASK) */
#define CANTSYN_GLOBAL_TIME_BASE_MASK 8U

#if (defined CANTSYN_TIMEOUTMASK) /* to prevent double declaration */
#error CANTSYN_TIMEOUTMASK is already defined
#endif /* if (defined CANTSYN_TIMEOUTMASK) */
#define CANTSYN_TIMEOUTMASK           1U

#if (defined CANTSYN_SC_MASK) /* to prevent double declaration */
#error CANTSYN_SC_MASK is already defined
#endif /* if (defined CANTSYN_SC_MASK) */
#define CANTSYN_SC_MASK               15U

#if (defined CANTSYN_OVS_MASK) /* to prevent double declaration */
#error CANTSYN_OVS_MASK is already defined
#endif /* if (defined CANTSYN_OVS_MASK) */
#define CANTSYN_OVS_MASK              3U

#if (defined CANTSYN_SGW_MASK) /* to prevent double declaration */
#error CANTSYN_SGW_MASK is already defined
#endif /* if (defined CANTSYN_SGW_MASK) */
#define CANTSYN_SGW_MASK              4U

#if (defined CANTSYN_START_VALUE_8H2F) /* to prevent double declaration */
#error CANTSYN_START_VALUE_8H2F is already defined
#endif /* if (defined CANTSYN_START_VALUE_8H2F) */
#define CANTSYN_START_VALUE_8H2F (0xFFU)

#if (defined CANTSYN_CRC_LENGTH) /* to prevent double declaration */
#error CANTSYN_CRC_LENGTH is already defined
#endif /* if (defined CANTSYN_CRC_LENGTH) */
#define CANTSYN_CRC_LENGTH     (7U)

#if (defined CANTSYN_CRC_EXT_LENGTH) /* to prevent double declaration */
#error CANTSYN_CRC_EXT_LENGTH is already defined
#endif /* if (defined CANTSYN_CRC_EXT_LENGTH) */
#define CANTSYN_CRC_EXT_LENGTH     (15U)

#if (defined CANTSYN_ICV_STATE_NOT_REQUESTED) /* to prevent double declaration */
#error CANTSYN_ICV_STATE_NOT_REQUESTED is already defined
#endif /* if (defined CANTSYN_ICV_STATE_NOT_REQUESTED) */
#define CANTSYN_ICV_STATE_NOT_REQUESTED      0U

#if (defined CANTSYN_ICV_STATE_PENDING) /* to prevent double declaration */
#error CANTSYN_ICV_STATE_PENDING is already defined
#endif /* if (defined CANTSYN_ICV_STATE_PENDING) */
#define CANTSYN_ICV_STATE_PENDING      1U

#if (defined CANTSYN_ICV_STATE_RECEIVED) /* to prevent double declaration */
#error CANTSYN_ICV_STATE_RECEIVED is already defined
#endif /* if (defined CANTSYN_ICV_STATE_RECEIVED) */
#define CANTSYN_ICV_STATE_RECEIVED      2U

#if (defined CANTSYN_ICV_STATE_VERIFIED) /* to prevent double declaration */
#error CANTSYN_ICV_STATE_VERIFIED is already defined
#endif /* if (defined CANTSYN_ICV_STATE_VERIFIED) */
#define CANTSYN_ICV_STATE_VERIFIED      3U

#if (defined CANTSYN_ICV_STATE_RECOV_ERROR) /* to prevent double declaration */
#error CANTSYN_ICV_STATE_RECOV_ERROR is already defined
#endif /* if (defined CANTSYN_ICV_STATE_RECOV_ERROR) */
#define CANTSYN_ICV_STATE_RECOV_ERROR      4U

#if (defined CANTSYN_ICV_STATE_FAILED) /* to prevent double declaration */
#error CANTSYN_ICV_STATE_FAILED is already defined
#endif /* if (defined CANTSYN_ICV_STATE_FAILED) */
#define CANTSYN_ICV_STATE_FAILED      5U

/* Icv helpers */

#if (defined CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE)
#error CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE is already defined
#endif /* if (defined CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE) */
#define CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE      1U

#if (defined CANTSYN_SYNC_PAYLOAD_LENGTH)
#error CANTSYN_SYNC_PAYLOAD_LENGTH is already defined
#endif /* if (defined CANTSYN_SYNC_PAYLOAD_LENGTH) */
#define CANTSYN_SYNC_PAYLOAD_LENGTH             8U

#if (defined CANTSYN_FUP_ICV_PAYLOAD_LENGTH)
#error CANTSYN_FUP_ICV_PAYLOAD_LENGTH is already defined
#endif /* if (defined CANTSYN_FUP_ICV_PAYLOAD_LENGTH) */
#define CANTSYN_FUP_ICV_PAYLOAD_LENGTH          10U

#if (defined CANTSYN_OFS_ICV_PAYLOAD_LENGTH)
#error CANTSYN_OFS_ICV_PAYLOAD_LENGTH is already defined
#endif /* if (defined CANTSYN_OFS_ICV_PAYLOAD_LENGTH) */
#define CANTSYN_OFS_ICV_PAYLOAD_LENGTH          18U

/* Byte numbers */

#if (defined CANTSYN_B0_MSG_TYPE) /* to prevent double declaration */
#error CANTSYN_B0_MSG_TYPE is already defined
#endif /* if (defined CANTSYN_B0_MSG_TYPE) */
#define CANTSYN_B0_MSG_TYPE     0U

#if (defined CANTSYN_B1_MSG) /* to prevent double declaration */
#error CANTSYN_B1_MSG is already defined
#endif /* if (defined CANTSYN_B1_MSG) */
#define CANTSYN_B1_MSG          1U

#if (defined CANTSYN_B2_MSG_DOMAIN) /* to prevent double declaration */
#error CANTSYN_B2_MSG_DOMAIN is already defined
#endif /* if (defined CANTSYN_B2_MSG_DOMAIN) */
#define CANTSYN_B2_MSG_DOMAIN   2U

#if (defined CANTSYN_B3_MSG_RESERVED) /* to prevent double declaration */
#error CANTSYN_B3_MSG_RESERVED is already defined
#endif /* if (defined CANTSYN_B3_MSG_RESERVED) */
#define CANTSYN_B3_MSG_RESERVED 3U

#if (defined CANTSYN_B3_MSG_GATEWAY) /* to prevent double declaration */
#error CANTSYN_B3_MSG_GATEWAY is already defined
#endif /* if (defined CANTSYN_B3_MSG_GATEWAY) */
#define CANTSYN_B3_MSG_GATEWAY  3U

#if (defined CANTSYN_B3_MSG) /* to prevent double declaration */
#error CANTSYN_B3_MSG is already defined
#endif /* if (defined CANTSYN_B3_MSG) */
#define CANTSYN_B3_MSG          3U

#if (defined CANTSYN_B4_MSG) /* to prevent double declaration */
#error CANTSYN_B4_MSG is already defined
#endif /* if (defined CANTSYN_B4_MSG) */
#define CANTSYN_B4_MSG          4U

#if (defined CANTSYN_B5_MSG) /* to prevent double declaration */
#error CANTSYN_B5_MSG is already defined
#endif /* if (defined CANTSYN_B5_MSG) */
#define CANTSYN_B5_MSG          5U

#if (defined CANTSYN_B6_MSG) /* to prevent double declaration */
#error CANTSYN_B6_MSG is already defined
#endif /* if (defined CANTSYN_B6_MSG) */
#define CANTSYN_B6_MSG          6U

#if (defined CANTSYN_B6_MSG_RESERVED) /* to prevent double declaration */
#error CANTSYN_B6_MSG_RESERVED is already defined
#endif /* if (defined CANTSYN_B6_MSG_RESERVED) */
#define CANTSYN_B6_MSG_RESERVED      6U

#if (defined CANTSYN_B7_MSG) /* to prevent double declaration */
#error CANTSYN_B7_MSG is already defined
#endif /* if (defined CANTSYN_B7_MSG) */
#define CANTSYN_B7_MSG          7U

#if (defined CANTSYN_B7_MSG_RESERVED) /* to prevent double declaration */
#error CANTSYN_B7_MSG_RESERVED is already defined
#endif /* if (defined CANTSYN_B7_MSG_RESERVED) */
#define CANTSYN_B7_MSG_RESERVED      7U

#if (defined CANTSYN_B8_RESERVED) /* to prevent double declaration */
#error CANTSYN_B8_RESERVED is already defined
#endif /* if (defined CANTSYN_B8_RESERVED) */
#define CANTSYN_B8_RESERVED          8U

#if (defined CANTSYN_B8_MSG) /* to prevent double declaration */
#error CANTSYN_B8_MSG is already defined
#endif /* if (defined CANTSYN_B8_MSG) */
#define CANTSYN_B8_MSG          8U

#if (defined CANTSYN_B8_FVL) /* to prevent double declaration */
#error CANTSYN_B8_FVL is already defined
#endif /* if (defined CANTSYN_B8_FVL) */
#define CANTSYN_B8_FVL          8U

#if (defined CANTSYN_B9_MSG) /* to prevent double declaration */
#error CANTSYN_B9_MSG is already defined
#endif /* if (defined CANTSYN_B9_MSG) */
#define CANTSYN_B9_MSG          9U

#if (defined CANTSYN_B9_ICVL) /* to prevent double declaration */
#error CANTSYN_B9_ICVL is already defined
#endif /* if (defined CANTSYN_B9_ICVL) */
#define CANTSYN_B9_ICVL          9U

#if (defined CANTSYN_B10_MSG) /* to prevent double declaration */
#error CANTSYN_B10_MSG is already defined
#endif /* if (defined CANTSYN_B10_MSG) */
#define CANTSYN_B10_MSG          10U

#if (defined CANTSYN_B10_FV) /* to prevent double declaration */
#error CANTSYN_B10_FV is already defined
#endif /* if (defined CANTSYN_B10_FV) */
#define CANTSYN_B10_FV           10U

#if (defined CANTSYN_B11_MSG) /* to prevent double declaration */
#error CANTSYN_B11_MSG is already defined
#endif /* if (defined CANTSYN_B11_MSG) */
#define CANTSYN_B11_MSG          11U

#if (defined CANTSYN_B12_MSG) /* to prevent double declaration */
#error CANTSYN_B12_MSG is already defined
#endif /* if (defined CANTSYN_B12_MSG) */
#define CANTSYN_B12_MSG          12U

#if (defined CANTSYN_B13_MSG) /* to prevent double declaration */
#error CANTSYN_B13_MSG is already defined
#endif /* if (defined CANTSYN_B13_MSG) */
#define CANTSYN_B13_MSG          13U

#if (defined CANTSYN_B14_MSG) /* to prevent double declaration */
#error CANTSYN_B14_MSG is already defined
#endif /* if (defined CANTSYN_B14_MSG) */
#define CANTSYN_B14_MSG          14U

#if (defined CANTSYN_B15_MSG) /* to prevent double declaration */
#error CANTSYN_B15_MSG is already defined
#endif /* if (defined CANTSYN_B15_MSG) */
#define CANTSYN_B15_MSG          15U

#if (defined CANTSYN_B16_FVL) /* to prevent double declaration */
#error CANTSYN_B16_FVL is already defined
#endif /* if (defined CANTSYN_B16_FVL) */
#define CANTSYN_B16_FVL          16U

#if (defined CANTSYN_B17_ICVL) /* to prevent double declaration */
#error CANTSYN_B17_ICVL is already defined
#endif /* if (defined CANTSYN_B17_ICVL) */
#define CANTSYN_B17_ICVL          17U

#if (defined CANTSYN_B18_FV) /* to prevent double declaration */
#error CANTSYN_B18_FV is already defined
#endif /* if (defined CANTSYN_B18_FV) */
#define CANTSYN_B18_FV          18U

#if (defined CANTSYN_GET_B3) /* to prevent double declaration */
#error CANTSYN_GET_B3 is already defined
#endif /* if (defined CANTSYN_GET_B3) */
#define CANTSYN_GET_B3 24U

#if (defined CANTSYN_GET_B2) /* to prevent double declaration */
#error CANTSYN_GET_B2 is already defined
#endif /* if (defined CANTSYN_GET_B2) */
#define CANTSYN_GET_B2 16U

#if (defined CANTSYN_GET_B1) /* to prevent double declaration */
#error CANTSYN_GET_B1 is already defined
#endif /* if (defined CANTSYN_GET_B1) */
#define CANTSYN_GET_B1 8U

#if (defined CANTSYN_SEC_PART_SIZE) /* to prevent double declaration */
#error CANTSYN_SEC_PART_SIZE is already defined
#endif /* if (defined CANTSYN_SEC_PART_SIZE) */
#define CANTSYN_SEC_PART_SIZE 4U

#if (defined CANTSYN_NSEC_PART_SIZE) /* to prevent double declaration */
#error CANTSYN_NSEC_PART_SIZE is already defined
#endif /* if (defined CANTSYN_NSEC_PART_SIZE) */
#define CANTSYN_NSEC_PART_SIZE 4U

#if (defined CANTSYN_STOP_IDX_OF_SYNC_MSGS) /* to prevent double declaration */
#error CANTSYN_STOP_IDX_OF_SYNC_MSGS is already defined
#endif /* if (defined CANTSYN_STOP_IDX_OF_SYNC_MSGS) */
#define CANTSYN_STOP_IDX_OF_SYNC_MSGS 15U

#if (defined CANTSYN_START_IDX_OF_OFS_MSGS) /* to prevent double declaration */
#error CANTSYN_START_IDX_OF_OFS_MSGS is already defined
#endif /* if (defined CANTSYN_START_IDX_OF_OFS_MSGS) */
#define CANTSYN_START_IDX_OF_OFS_MSGS 16U

#if (defined CANTSYN_NO_IMMEDIATE_TRANSMISSION) /* to prevent double declaration */
#error CANTSYN_NO_IMMEDIATE_TRANSMISSION is already defined
#endif /* if (defined CANTSYN_NO_IMMEDIATE_TRANSMISSION) */
#define CANTSYN_NO_IMMEDIATE_TRANSMISSION 0U

#if (defined CANTSYN_GET_B2_DOMAIN_SC) /* to prevent double declaration */
#error CANTSYN_GET_B2_DOMAIN_SC is already defined
#endif /* if (defined CANTSYN_GET_B2_DOMAIN_SC) */
#define CANTSYN_GET_B2_DOMAIN_SC(DomainId, SeqCount) (((uint8)((DomainId) << 4U)) | (SeqCount))

#if (defined CANTSYN_B3_SGW_OVS) /* to prevent double declaration */
#error CANTSYN_B3_SGW_OVS is already defined
#endif /* if (defined CANTSYN_B3_SGW_OVS) */
#define CANTSYN_B3_SGW_OVS(Index, Ovs)               ((uint8)(CanTSyn_SyncMaster[(Index)].SyncSGWBit << 2U) | (Ovs))


#if (defined CANTSYN_B3_SGW) /* to prevent double declaration */
#error CANTSYN_B3_SGW is already defined
#endif /* if (defined CANTSYN_B3_SGW) */
#define CANTSYN_B3_SGW(Index)               ((uint8)(CanTSyn_OffsetMaster[(Index)].OfsSGWBit))

#if (defined CANTSYN_GET_SEQ_COUNTER) /* to prevent double declaration */
#error CANTSYN_GET_SEQ_COUNTER is already defined
#endif /* if (defined CANTSYN_GET_SEQ_COUNTER) */
#define CANTSYN_GET_SEQ_COUNTER(SeqCounter)          (((SeqCounter) != 0U)?((SeqCounter)-1U):(CANTSYN_SC_MAXLIMIT))

#if (defined CANTSYN_SET_SEQ_COUNTER) /* to prevent double declaration */
#error CANTSYN_SET_SEQ_COUNTER is already defined
#endif /* if (defined CANTSYN_SET_SEQ_COUNTER) */
#define CANTSYN_SET_SEQ_COUNTER(SeqCounter)          (((SeqCounter) < CANTSYN_SC_MAXLIMIT)?((SeqCounter)+1U):(0U))

#if (defined CANTSYN_GET_USERBYTE0) /* to prevent double declaration */
#error CANTSYN_GET_USERBYTE0 is already defined
#endif /* if (defined CANTSYN_GET_USERBYTE0) */
#define CANTSYN_GET_USERBYTE0(UserData) (((UserData).userDataLength > 0U)?((UserData).userByte0):(0U))

#if (defined CANTSYN_GET_USERBYTE1) /* to prevent double declaration */
#error CANTSYN_GET_USERBYTE1 is already defined
#endif /* if (defined CANTSYN_GET_USERBYTE1) */
#define CANTSYN_GET_USERBYTE1(UserData) (((UserData).userDataLength > 1U)?((UserData).userByte1):(0U))

#if (defined CANTSYN_GET_USERBYTE2) /* to prevent double declaration */
#error CANTSYN_GET_USERBYTE2 is already defined
#endif /* if (defined CANTSYN_GET_USERBYTE2) */
#define CANTSYN_GET_USERBYTE2(UserData) (((UserData).userDataLength > 2U)?((UserData).userByte2):(0U))

#if (defined CANTSYN_GET_SC_SLAVE) /* to prevent double declaration */
#error CANTSYN_GET_SC_SLAVE is already defined
#endif /* if (defined CANTSYN_GET_SC_SLAVE) */
#define CANTSYN_GET_SC_SLAVE(Byte2)       ((Byte2) & 0x0FU)

#if (defined CANTSYN_GET_DOMAINID_SLAVE) /* to prevent double declaration */
#error CANTSYN_GET_DOMAINID_SLAVE is already defined
#endif /* if (defined CANTSYN_GET_DOMAINID_SLAVE) */
#define CANTSYN_GET_DOMAINID_SLAVE(Byte2) (uint8)((Byte2) >> 4U)

#if(CANTSYN_RX_SYNC_USED == STD_ON)

#if (defined CANTSYN_IS_CRC_VAL_SYNC) /* to prevent double declaration */
#error CANTSYN_IS_CRC_VAL_SYNC is already defined
#endif /* if (defined CANTSYN_IS_CRC_VAL_SYNC) */
#define CANTSYN_IS_CRC_VAL_SYNC(PduId, Type)     (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_VALIDATED) && \
                                                      ((Type) == 0x20U))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_NOT_VAL_SYNC) /* to prevent double declaration */
#error CANTSYN_IS_CRC_NOT_VAL_SYNC is already defined
#endif /* if (defined CANTSYN_IS_CRC_NOT_VAL_SYNC) */
#define CANTSYN_IS_CRC_NOT_VAL_SYNC(PduId, Type) (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                      ((Type) == 0x10U))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_IGNORED_SYNC) /* to prevent double declaration */
#error CANTSYN_IS_CRC_IGNORED_SYNC is already defined
#endif /* if (defined CANTSYN_IS_CRC_IGNORED_SYNC) */
#define CANTSYN_IS_CRC_IGNORED_SYNC(PduId, Type) (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                     (((Type) == 0x10U) || ((Type) == 0x20U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_OPTIONAL_SYNC) /* to prevent double declaration */
#error CANTSYN_IS_CRC_OPTIONAL_SYNC is already defined
#endif /* if (defined CANTSYN_IS_CRC_OPTIONAL_SYNC) */
#define CANTSYN_IS_CRC_OPTIONAL_SYNC(PduId, Type) (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                     (((Type) == 0x10U) || ((Type) == 0x20U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_SYNC_CRC_TYPE) /* to prevent double declaration */
#error CANTSYN_IS_SYNC_CRC_TYPE is already defined
#endif /* if (defined CANTSYN_IS_SYNC_CRC_TYPE) */
#define CANTSYN_IS_SYNC_CRC_TYPE(Type) (((Type) == 0x20U)?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_VAL_FUP) /* to prevent double declaration */
#error CANTSYN_IS_CRC_VAL_FUP is already defined
#endif /* if (defined CANTSYN_IS_CRC_VAL_FUP) */
#define CANTSYN_IS_CRC_VAL_FUP(PduId, Type)      (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_VALIDATED) && \
                                                      (((Type) == 0x28U) || ((Type) == 0x88U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_NOT_VAL_FUP) /* to prevent double declaration */
#error CANTSYN_IS_CRC_NOT_VAL_FUP is already defined
#endif /* if (defined CANTSYN_IS_CRC_NOT_VAL_FUP) */
#define CANTSYN_IS_CRC_NOT_VAL_FUP(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                      ((Type) == 0x18U))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_NOT_VAL_FUP_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_CRC_NOT_VAL_FUP_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_CRC_NOT_VAL_FUP_ICV_AUTH) */
#define CANTSYN_IS_CRC_NOT_VAL_FUP_ICV_AUTH(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                          ((Type) == 0x78U))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_IGNORED_FUP) /* to prevent double declaration */
#error CANTSYN_IS_CRC_IGNORED_FUP is already defined
#endif /* if (defined CANTSYN_IS_CRC_IGNORED_FUP) */
#define CANTSYN_IS_CRC_IGNORED_FUP(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                     (((Type) == 0x18U) || ((Type) == 0x28U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_IGNORED_FUP_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_CRC_IGNORED_FUP_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_CRC_IGNORED_FUP_ICV_AUTH) */
#define CANTSYN_IS_CRC_IGNORED_FUP_ICV_AUTH(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                          (((Type) == 0x78U) || ((Type) == 0x88U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_OPTIONAL_FUP) /* to prevent double declaration */
#error CANTSYN_IS_CRC_OPTIONAL_FUP is already defined
#endif /* if (defined CANTSYN_IS_CRC_OPTIONAL_FUP) */
#define CANTSYN_IS_CRC_OPTIONAL_FUP(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                     (((Type) == 0x18U) || ((Type) == 0x28U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_OPTIONAL_FUP_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_CRC_OPTIONAL_FUP_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_CRC_OPTIONAL_FUP_ICV_AUTH) */
#define CANTSYN_IS_CRC_OPTIONAL_FUP_ICV_AUTH(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                          (((Type) == 0x78U) || ((Type) == 0x88U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_FUP_CRC_TYPE) /* to prevent double declaration */
#error CANTSYN_IS_FUP_CRC_TYPE is already defined
#endif /* if (defined CANTSYN_IS_FUP_CRC_TYPE) */
#define CANTSYN_IS_FUP_CRC_TYPE(Type) (((Type) == 0x28U)?TRUE:FALSE)

#if (defined CANTSYN_IS_FUP_CRC_TYPE_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_FUP_CRC_TYPE_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_FUP_CRC_TYPE_ICV_AUTH) */
#define CANTSYN_IS_FUP_CRC_TYPE_ICV_AUTH(Type) (((Type) == 0x88U)?TRUE:FALSE)

#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */


#if(CANTSYN_RX_OFFSET_USED == STD_ON)

#if (defined CANTSYN_IS_CRC_VAL_OFS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_VAL_OFS is already defined
#endif /* if (defined CANTSYN_IS_CRC_VAL_OFS) */
#define CANTSYN_IS_CRC_VAL_OFS(PduId, Type)      (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_VALIDATED) && \
                                                      ((Type) == 0x44U))?TRUE:FALSE)

#if (defined CANTSYN_IS_EXT_CRC_VAL_OFS) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_VAL_OFS is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_VAL_OFS) */
#define CANTSYN_IS_EXT_CRC_VAL_OFS(PduId, Type)      (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_VALIDATED) && \
                                                      (((Type) == 0x64U) || ((Type) == 0xA4U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_NOT_VAL_OFS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_NOT_VAL_OFS is already defined
#endif /* if (defined CANTSYN_IS_CRC_NOT_VAL_OFS) */
#define CANTSYN_IS_CRC_NOT_VAL_OFS(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                      ((Type) == 0x34U))?TRUE:FALSE)

#if (defined CANTSYN_IS_EXT_CRC_NOT_VAL_OFS) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_NOT_VAL_OFS is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_NOT_VAL_OFS) */
#define CANTSYN_IS_EXT_CRC_NOT_VAL_OFS(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                      ((Type) == 0x54U))?TRUE:FALSE)

#if (defined CANTSYN_IS_EXT_CRC_NOT_VAL_OFS_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_NOT_VAL_OFS_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_NOT_VAL_OFS_ICV_AUTH) */
#define CANTSYN_IS_EXT_CRC_NOT_VAL_OFS_ICV_AUTH(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                            ((Type) == 0x94U))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_IGNORED_OFS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_IGNORED_OFS is already defined
#endif /* if (defined CANTSYN_IS_CRC_IGNORED_OFS) */
#define CANTSYN_IS_CRC_IGNORED_OFS(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                      (((Type) == 0x34U) || ((Type) == 0x44U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_EXT_CRC_IGNORED_OFS) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_IGNORED_OFS is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_IGNORED_OFS) */
#define CANTSYN_IS_EXT_CRC_IGNORED_OFS(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                      (((Type) == 0x54U) || ((Type) == 0x64U)))?TRUE:FALSE)
#if (defined CANTSYN_IS_EXT_CRC_IGNORED_OFS_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_IGNORED_OFS_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_IGNORED_OFS_ICV_AUTH) */
#define CANTSYN_IS_EXT_CRC_IGNORED_OFS_ICV_AUTH(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                              (((Type) == 0x94U) || ((Type) == 0xA4U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_OPTIONAL_OFS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_OPTIONAL_OFS is already defined
#endif /* if (defined CANTSYN_IS_CRC_OPTIONAL_OFS) */
#define CANTSYN_IS_CRC_OPTIONAL_OFS(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                      (((Type) == 0x34U) || ((Type) == 0x44U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_OFS_CRC_TYPE) /* to prevent double declaration */
#error CANTSYN_IS_OFS_CRC_TYPE is already defined
#endif /* if (defined CANTSYN_IS_OFS_CRC_TYPE) */
#define CANTSYN_IS_OFS_CRC_TYPE(Type) (((Type) == 0x44U)?TRUE:FALSE)

#if (defined CANTSYN_IS_EXT_CRC_OPTIONAL_OFS) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_OPTIONAL_OFS is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_OPTIONAL_OFS) */
#define CANTSYN_IS_EXT_CRC_OPTIONAL_OFS(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                      (((Type) == 0x54U) || ((Type) == 0x64U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_EXT_CRC_OPTIONAL_OFS_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_EXT_CRC_OPTIONAL_OFS_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_EXT_CRC_OPTIONAL_OFS_ICV_AUTH) */
#define CANTSYN_IS_EXT_CRC_OPTIONAL_OFS_ICV_AUTH(PduId, Type)  (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                              (CanTSyn_TimeSlaveConfig[(PduId)].IcvVerificationType != CANTSYN_ICV_NOT_VERIFIED) && \
                                                      (((Type) == 0x94U) || ((Type) == 0xA4U)))?TRUE:FALSE)

#if (defined CANTSYN_IS_OFS_EXT_CRC_TYPE) /* to prevent double declaration */
#error CANTSYN_IS_OFS_EXT_CRC_TYPE is already defined
#endif /* if (defined CANTSYN_IS_OFS_EXT_CRC_TYPE) */
#define CANTSYN_IS_OFS_EXT_CRC_TYPE(Type) (((Type) == 0x64U)?TRUE:FALSE)

#if (defined CANTSYN_IS_OFS_EXT_CRC_TYPE_ICV_AUTH) /* to prevent double declaration */
#error CANTSYN_IS_OFS_EXT_CRC_TYPE_ICV_AUTH is already defined
#endif /* if (defined CANTSYN_IS_OFS_EXT_CRC_TYPE_ICV_AUTH) */
#define CANTSYN_IS_OFS_EXT_CRC_TYPE_ICV_AUTH(Type) (((Type) == 0xA4U)?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_VAL_OFNS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_VAL_OFNS is already defined
#endif /* if (defined CANTSYN_IS_CRC_VAL_OFNS) */
#define CANTSYN_IS_CRC_VAL_OFNS(PduId, Type)     (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_VALIDATED) && \
                                                      ((Type) == 0x4CU))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_NOT_VAL_OFNS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_NOT_VAL_OFNS is already defined
#endif /* if (defined CANTSYN_IS_CRC_NOT_VAL_OFNS) */
#define CANTSYN_IS_CRC_NOT_VAL_OFNS(PduId, Type) (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_NOT_VALIDATED) && \
                                                      ((Type) == 0x3CU))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_IGNORED_OFNS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_IGNORED_OFNS is already defined
#endif /* if (defined CANTSYN_IS_CRC_IGNORED_OFNS) */
#define CANTSYN_IS_CRC_IGNORED_OFNS(PduId, Type) (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_IGNORED) && \
                                                      (((Type) == 0x3CU) || ((Type) == 0x4CU)))?TRUE:FALSE)

#if (defined CANTSYN_IS_CRC_OPTIONAL_OFNS) /* to prevent double declaration */
#error CANTSYN_IS_CRC_OPTIONAL_OFNS is already defined
#endif /* if (defined CANTSYN_IS_CRC_OPTIONAL_OFNS) */
#define CANTSYN_IS_CRC_OPTIONAL_OFNS(PduId, Type) (((CanTSyn_TimeSlaveConfig[(PduId)].RxCrcValidated == CANTSYN_CRC_OPTIONAL) && \
                                                      (((Type) == 0x3CU) || ((Type) == 0x4CU)))?TRUE:FALSE)

#if (defined CANTSYN_IS_OFNS_CRC_TYPE) /* to prevent double declaration */
#error CANTSYN_IS_OFNS_CRC_TYPE is already defined
#endif /* if (defined CANTSYN_IS_OFNS_CRC_TYPE) */
#define CANTSYN_IS_OFNS_CRC_TYPE(Type) (((Type) == 0x4CU)?TRUE:FALSE)

#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */


#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))

#if (defined CANTSYN_DELTA_SC) /* to prevent double declaration */
#error CANTSYN_DELTA_SC is already defined
#endif /* if (defined CANTSYN_DELTA_SC) */
#define CANTSYN_DELTA_SC(receivedSeqCount, seqCount)  (((receivedSeqCount) >= (seqCount))?(uint8)((receivedSeqCount) - (seqCount)) : \
                                                             (uint8)(((receivedSeqCount) + CANTSYN_SC_MAXLIMIT + 1U) - (seqCount)))
#endif/* (CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON) */

#if (defined CANTSYN_NS_PER_SEC) /* to prevent double declaration */
#error CANTSYN_NS_PER_SEC is already defined
#endif /* if (defined CANTSYN_NS_PER_SEC) */
#define CANTSYN_NS_PER_SEC 1000000000U /* Nanoseconds in one second */

#if (defined CANTSYN_MAX_32BIT_VALUE) /* to prevent double declaration */
#error CANTSYN_MAX_32BIT_VALUE is already defined
#endif /* if (defined CANTSYN_MAX_32BIT_VALUE) */
#define CANTSYN_MAX_32BIT_VALUE 0xFFFFFFFFU /* Maximum value of seconds portion */

#if (defined CANTSYN_GET_TIME_VAL) /* to prevent double declaration */
#error CANTSYN_GET_TIME_VAL is already defined
#endif /* if (defined CANTSYN_GET_TIME_VAL) */
#define CANTSYN_GET_TIME_VAL(DataPtr) (((((uint32) ((uint32) DataPtr[CANTSYN_B4_MSG]) << 24U)  | \
                                         ((uint32) ((uint32) DataPtr[CANTSYN_B5_MSG]) << 16U)) | \
                                         ((uint32) ((uint32) DataPtr[CANTSYN_B6_MSG]) << 8U))  | \
                                                   ((uint32) DataPtr[CANTSYN_B7_MSG]))

#define CANTSYN_GET_EXT_TIME_VAL(DataPtr) (((((uint32) ((uint32) DataPtr[CANTSYN_B8_MSG]) << 24U)  | \
                                             ((uint32) ((uint32) DataPtr[CANTSYN_B9_MSG]) << 16U)) | \
                                             ((uint32) ((uint32) DataPtr[CANTSYN_B10_MSG]) << 8U))  | \
                                                       ((uint32) DataPtr[CANTSYN_B11_MSG]))

#define CANTSYN_GET_EXT_NANO_TIME_VAL(DataPtr) (((((uint32) ((uint32) DataPtr[CANTSYN_B12_MSG]) << 24U)  | \
                                                  ((uint32) ((uint32) DataPtr[CANTSYN_B13_MSG]) << 16U)) | \
                                                  ((uint32) ((uint32) DataPtr[CANTSYN_B14_MSG]) << 8U))  | \
                                                            ((uint32) DataPtr[CANTSYN_B15_MSG]))

#if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON))

#if (defined CANTSYN_SET_FVL)
#error CANTSYN_SET_FVL is already defined
#endif /* if (defined CANTSYN_SET_FVL) */
#define CANTSYN_SET_FVL(Fvl)             ((uint8) ((Fvl) &~ (1U << 7U) ))

#if (defined CANTSYN_GET_FVL)
#error CANTSYN_GET_FVL is already defined
#endif /* if (defined CANTSYN_GET_FVL) */
#define CANTSYN_GET_FVL(Fvl)             ((uint32) ((Fvl) & (~(0x080U))))

#if (defined CANTSYN_COMPUTE_FVL_IN_BYTES)
#error CANTSYN_COMPUTE_FVL_IN_BYTES is already defined
#endif /* if (defined CANTSYN_COMPUTE_FVL_IN_BYTES) */
#define CANTSYN_COMPUTE_FVL_IN_BYTES(Fvl)         ((uint8) (((Fvl) + 7U) / 8U))

#if (defined CANTSYN_SET_ICVL)
#error CANTSYN_SET_ICVL is already defined
#endif /* if (defined CANTSYN_SET_ICVL) */
#define CANTSYN_SET_ICVL(Icvl)           ((uint8) ((Icvl) & (~(3U << 6U))))

#endif /* if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)) */

/* DET reporting macros */

#if (defined CANTSYN_MAX_DROPPED_SYNC_PAIRS)
#error CANTSYN_MAX_DROPPED_SYNC_PAIRS is already defined
#endif
#define CANTSYN_MAX_DROPPED_SYNC_PAIRS 5U


#if(CANTSYN_MULTICORE_ENABLED == STD_ON)

#if (defined CANTSYN_GET_TYPE_DIRECTION) /* to prevent double declaration */
#error CANTSYN_GET_TYPE_DIRECTION is already defined
#endif /* if (defined CANTSYN_GET_TYPE_DIRECTION) */
#define CANTSYN_GET_TYPE_DIRECTION(pduIndexTypeDirection)       ((pduIndexTypeDirection) & 3U)


#if (defined CANTSYN_SYNC_TX_PDUINDEX) /* to prevent double declaration */
#error CANTSYN_SYNC_TX_PDUINDEX is already defined
#endif /* if (defined CANTSYN_SYNC_TX_PDUINDEX) */
#define CANTSYN_SYNC_TX_PDUINDEX 0U

#if (defined CANTSYN_OFS_TX_PDUINDEX) /* to prevent double declaration */
#error CANTSYN_OFS_TX_PDUINDEX is already defined
#endif /* if (defined CANTSYN_OFS_TX_PDUINDEX) */
#define CANTSYN_OFS_TX_PDUINDEX 2U

#if (defined CANTSYN_SYNC_RX_PDUINDEX) /* to prevent double declaration */
#error CANTSYN_SYNC_RX_PDUINDEX is already defined
#endif /* if (defined CANTSYN_SYNC_RX_PDUINDEX) */
#define CANTSYN_SYNC_RX_PDUINDEX 1U

#if (defined CANTSYN_OFS_RX_PDUINDEX) /* to prevent double declaration */
#error CANTSYN_OFS_RX_PDUINDEX is already defined
#endif /* if (defined CANTSYN_OFS_RX_PDUINDEX) */
#define CANTSYN_OFS_RX_PDUINDEX 3U

#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
/*==================[internal function declarations]=======================*/

#define CANTSYN_START_SEC_CODE
#include <CanTSyn_MemMap.h>

#if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON))
/**
 * \brief Service to intialize Icv parameters for each domain.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_Icv_Init
(
  P2CONST(CanTSyn_ConfigType, AUTOMATIC, CANTSYN_APPL_CONST) configPtr
);
#endif /* ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)) */

#if(CANTSYN_TX_SYNC_USED == STD_ON)
/**
 * \brief Service to assemble the SYNC Frame.
 * \param[in] CanTSynPduIdx - Index of the active TxPdu.
 * \param[out] TxDataPtr - Pointer containing the corresponding data.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxSyncFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  uint8 CanTSynPduIdx
);

/**
 * \brief Service to assemble the FUP Frame.
 * \param[in] CanTSynPduIdx - Index of the active TxPdu.
 *            OvsBit - The OVS bit
 * \param[out] TxDataPtr - Pointer containing the corresponding data.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxFupFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  uint8 CanTSynPduIdx,
  uint8 CanTSynOvsBit
);

/**
 * \brief Service to clear the sync state machine of the CanTSyn module.
 * \param[in] ConfirmationHandleId - Index of the active TxPdu.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxSyncReset
(
  uint8 ConfirmationHandleId
);


/**
 * \brief Service to send the SYNC message to CanIf.
 * \param[in] ConfirmationHandleId        - Index of the TxPdu.
 *            IsImmediateSYNCTransmission - Indication if an immediate transmission takes place or not.
 * \return E_OK: CanTSyn message sent.
 *         E_NOT_OK: No message sent or CanIf returned E_NOT_OK.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SendSyncMessage
(
  uint8 ConfirmationHandleId,
  boolean IsImmediateSYNCTransmission
);


/**
 * \brief Service to sum two StbM_TimeStamps.
 * \param[in] timeStampAugendPtr        - pointer to first constant StbM_TimeStamp.
 *            timeStampAddendPtr        - pointer to second constant StbM_TimeStamp.
 * \return StbM_TimeStamp: resulted (sum of the two parameters) StbM_TimeStamp
 */
STATIC FUNC(StbM_TimeStampType, CANTSYN_CODE) CanTSyn_AddTimestamp
(
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAugendPtr,
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAddendPtr
);

#if (CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON)
/**
 * \brief Service to sum two StbM_TimeStamps.
 * \param[in] timeStampAugendPtr        - pointer to first constant StbM_TimeStamp.
 *            timeStampAddendPtr        - pointer to second constant StbM_TimeStamp.
 * \return StbM_TimeStamp: resulted (sum of the two parameters) StbM_TimeStamp
 */
STATIC FUNC(StbM_TimeStampType, CANTSYN_CODE) CanTSyn_AddTimestamp_TimeValidation
(
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAugendPtr,
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAddendPtr
);
#endif /* (CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON) */

/**
 * \brief Service to send the FUP message to CanIf.
 * \param[in] ConfirmationHandleId - Index of the TxPdu.
 *
 * \return E_OK: CanTSyn message sent.
 *         E_NOT_OK: No message sent or CanIf returned E_NOT_OK.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SendFupMessage
(
  uint8 ConfirmationHandleId
);

/**
 * \brief Service to enable the transmission of the SYNC message.
 * \param[in] NewTimeBaseCounter         - UpdateCounter received from StbM
 *            isImmediateTransmissionPtr - Indication if an immediate
 *                                         transmission takes place or not.
 *            PduId                      - Index of the TxPdu.
 * \return E_OK:     CanTSyn message shall be sent.
 *         E_NOT_OK: No message shall be sent until timeout or immediate transmission flag set.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsTxSYNCMessageAwaited
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) NewTimeBaseCounter,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) IsImmediateTransmissionPtr,
  uint8 PduId
);

/**
 * \brief Service to process the Tx SYNC messages of the CanTSyn module.
 * \param[in] ConfirmationHandleId - Index of the active TxPdu.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxProcessSyncMsg
(
  uint8 ConfirmationHandleId
);

/**
 * \brief Service to process the confirmation for Tx SYNC messages of the CanTSyn module.
 * \param[in] CanTSyn_PduActiveIndex - Index of the active TxPdu.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ConfirmSyncMsg
(
  uint8 CanTSyn_PduActiveIndex
);
#endif /* CANTSYN_TX_SYNC_USED == STD_ON */


#if(CANTSYN_TX_OFFSET_USED == STD_ON)
/**
 * \brief Service to process the confirmation for Tx OFS messages of the CanTSyn module.
 * \param[in] CanTSyn_PduActiveIndex - Index of the active TxPdu.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ConfirmOfsMsg
(
  uint8 CanTSyn_PduActiveIndex
);

/**
 * \brief Service to assemble the OFS Frame.
 * \param[in] CanTSynPduIdx - Index of the active TxPdu.
 *            CanTSynTimeStampPtr - The Seconds part(Lo and Hi) of the Offset.
 * \param[out] CanTSynTxDataPtr - Pointer containing the corresponding data.
 */

STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxOfsFrame
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSynTimeStampPtr,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) CanTSynTxDataPtr,
  uint8 CanTSynPduIdx
);

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
/**
 * \brief Service to assemble the OFNS Frame.
 * \param[in] CanTSynPduIdx - Index of the active TxPdu.
 *
 * \param[out] CanTSynTxDataPtr - Pointer containing the corresponding data.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxOfnsFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) CanTSynTxDataPtr,
  uint8 CanTSynPduIdx
);
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

/**
 * \brief Service to clear the offset state machine of the CanTSyn module.
 * \param[in] ConfirmationHandleId - Index of the active PduId.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxOffsetReset
(
  uint8 ConfirmationHandleId
);

/**
 * \brief Service to call the CanIf_Transmit API.
 * \param[in] SduData         - Pointer to the frame contents.
 *            CanTSynPduIndex - Index of the TxPdu.
 *            sduDataLength   - length of SduData
 *            CanTSynIsImmediateOFSTransmission - Indication if an immediate transmission takes place or not
 *            CanTSynTxStatus - Current Tx status.
 *
 * \return E_OK: CanTSyn message sent.
 *         E_NOT_OK: No message sent or CanIf returned E_NOT_OK.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_TransmitOfs
(
  P2VAR(uint8 ,AUTOMATIC, CANTSYN_APPL_DATA) SduData,
  uint8 CanTSynPduIndex,
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  uint8 sduDataLength,
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
  boolean CanTSynIsImmediateOFSTransmission,
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)*/
  uint8 CanTSynTxStatus
);

/**
 * \brief Service to send the OFS and OFNS message to CanIf.
 * \param[in] CanTSynPduIndex - Index of the TxPdu.
 *            CanTSynTxStatus - Current Tx status.
 *            CanTSynIsImmediateOFSTransmission - Indication if an immediate transmission takes place or not
 *
 * \return E_OK: CanTSyn message sent.
 *         E_NOT_OK: No message sent or CanIf returned E_NOT_OK.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SendOfsMessage
(
  uint8 CanTSynPduIndex,
  uint8 CanTSynTxStatus,
  boolean CanTSynIsImmediateOFSTransmission
);

/**
 * \brief Service to enable the transmission of the OFS message.
 * \param[in] NewTimeBaseCounter             - UpdateCounter received from StbM.
 *            isImmediateSYNCTransmissionPtr - Indication if an immediate
 *                                             transmission takes place or not.
 *            PduId                          - Index of the TxPdu.
 * \return E_OK:     CanTSyn message shall be sent.
 *         E_NOT_OK: No message shall be sent until timeout or immediate transmission flag set.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsTxOFSMessageAwaited
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) NewTimeBaseCounter,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) IsImmediateTransmissionPtr,
  uint8 PduId
);

/**
 * \brief Service to process the Tx OFS messages of the CanTSyn module.
 * \param[in] ConfirmationHandleId - Index of the active PduId.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxProcessOfsMsg
(
  uint8 ConfirmationHandleId
);

#endif /* CANTSYN_TX_OFFSET_USED == STD_ON */

#if (CANTSYN_TX_SYNC_USED == STD_ON)
/**
* \brief Service to subtract two StbM_VirtualLocalTimes.
* \param[in] virtualLocalTimeMinuendPtr     - pointer to constant StbM_VirtualLocalTime minuend.
*            virtualLocalTimeSubtrahendPtr  - pointer to constant StbM_VirtualLocalTime subtrahend.
* \return StbM_TimeStamp:          resulted StbM_VirtualLocalTime after subtraction and conversion
*/
STATIC FUNC(StbM_TimeStampType, CANTSYN_CODE) CanTSyn_SubtractVLT
(
    P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, CANTSYN_VAR) virtualLocalTimeMinuendPtr,
    P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, CANTSYN_VAR) virtualLocalTimeSubtrahendPtr
);
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) */

#if(CANTSYN_TX_CRC_USED == STD_ON)
/**
 * \brief Service to calculate the normal message CRC value.
 * \param[in] DataId    - Data Id value.
 *            TxDataPtr - The Seconds part(Lo and Hi) of the Offset.
 *            CrcLength - CRC Length 7 (Normal message) or 15 (Extended message)
 * \param[out] The CRC value.
 */
STATIC FUNC(uint8, CANTSYN_CODE) CanTSyn_CalculateCRC
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) TxDataPtr,
  CanTSyn_DataIDListType DataId,
  uint8 CrcLength
);
#endif /* CANTSYN_TX_CRC_USED == STD_ON */


#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
/**
 * \brief Service to validate the message length of an ICV auth message.
 * \param[in] RxPduId - The Slave Pdu ID.
 *
 * \param[in] PduInfoPtr  - Contains the length (SduLength) of the received PDU, a pointer to a buffer (SduDataPtr) containing the PDU.
 */
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_CheckAuthMsgLength
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr
);
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

/**
 * \brief Service to check if the message was received after the debounce time expired.
 * \param[in] RxPduId - The Slave Pdu ID.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckRxDebounceTime
(
  PduIdType RxPduId
);

/**
 * \brief Service to validate the arguments of CanTSyn_RxIndication.
 * \param[in] RxPduId - The Slave Pdu ID.
 *
 * \param[in] PduInfoPtr  - Contains the length (SduLength) of the received PDU, a pointer to a buffer (SduDataPtr) containing the PDU.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_RxIndication_Validation
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr
);

/**
 * \brief Service to get the status of the current Domain.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *
 * \param[out] RxStatusPtr  - The Seconds part(Lo and Hi) of the Offset.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_GetRxStatus
(
  uint8 SlavePduId,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) RxStatusPtr
);

#if(CANTSYN_RX_SYNC_USED == STD_ON)

#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
/**
 * \brief Service to check if received message is FUP type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *            isCrcType  - Indicates if this is a CRC secured message type
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsAuthFUPType
(
  uint8 SlavePduId,
  uint8 Type,
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType,
#endif
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

/**
 * \brief Service to check if received message is FUP type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsFUPType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);

/**
 * \brief Service to check if received message is SYNC type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsSYNCType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
/**
 * \brief Service to check if received message is OFNS type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFNSType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

/**
 * \brief Service to check if received message is OFS type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFSType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);

#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)

#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
/**
 * \brief Service to check if received message is an Extended OFS type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *            isCrcType  - Indicates if this is a CRC secured message type
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsAuthOFSExtenedType
(
  uint8 SlavePduId,
  uint8 Type,
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType,
#endif
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

/**
 * \brief Service to check if received message is an Extended OFS type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFSExtenedType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);
#endif /* CANTSYN_RX_USE_EXTENDED_MSG == STD_ON */

/**
 * \brief Service to check if received message is a Normal OFS type.
 * \param[in] SlavePduId - The Slave Pdu ID.
 *            Type       - Type of the message (read from SduDataPtr)
 *
 * \param[out] CrcValidation - Indication if the Crc validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFSNormalType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);
#endif /* CANTSYN_RX_OFFSET_USED == STD_ON */

/**
 * \brief Service to check the Message CRC of the received message.
 * \param[in] SlavePduId    - Slave Time Domain Id.
 *            RxStatus         - Status of the current Slave Time Domain.
 *            DataPtr          - Pointer containing the data needed for message
 *                               type and CRC computation.
 *
 * \param[out] CrcValidation - Indication if the CRC validation is to be performed.
 *
 * \return E_OK: Message Type accepted.
 *         E_NOT_OK: Message Type not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckMsgType
(
  uint8 SlavePduId,
  uint8 RxStatus,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
);

#if(CANTSYN_RX_CRC_USED == STD_ON)
/**
 * \brief Service to check the Message CRC of the received message.
 * \param[in] SlavePduId    - Slave Time Domain Id.
 *            RxStatus         - Status of the current Slave Time Domain.
 *            DataPtr          - Pointer containing the data needed for message
 *                               type and CRC computation.
 *
 * \return E_OK: Message CRC accepted.
 *         E_NOT_OK: Message CRC not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckMsgCRC
(
  uint8 SlavePduId,
  uint8 RxStatus,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
);
#endif /* CANTSYN_RX_CRC_USED == STD_ON */

/**
 * \brief Service to check if the Sequence Counter of the received message shall be accepted.
 * \param[in] RxPduId          - Slave Pdu Id.
 *            ReceivedSC       - The Sequence Counter received in the .
 *            IsSync           - Indication if the received message is a SYNC or a OFS message.
 *
 * \return E_OK: Message with received sequence counter accepted.
 *         E_NOT_OK: Message with received sequence counter not accepted for this RxPduId.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckSequenceCounter
(
  uint8 RxPduId,
  uint8 ReceivedSC,
  boolean IsSync
);
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON) */

#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_CRC_USED == STD_ON))
/**
 * \brief Function used for time slave configuration in the case of a RX wait for a SYNC message.
 * \param[in]  SlavePduId      - Slave Time Domain Id.
 * \param[in]  DataPtr         - Pointer containing the data needed for message
 *                               CRC computation.
 *
 * \return E_OK: Message Type and CRC accepted.
 *         E_NOT_OK: CRC not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SyncMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
);

/**
 * \brief Function used for time slave configuration in the case of a RX wait (wait timeout) for
 * a FUP message.
 * \param[in]  SlavePduId      - Slave Time Domain Id.
 * \param[in]  DataPtr         - Pointer containing the data needed for message
 *                               CRC computation.
 *
 * \return E_OK: Message Type and CRC accepted.
 *         E_NOT_OK: CRC not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_FupMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
);
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_CRC_USED == STD_ON) */

#if((CANTSYN_RX_OFFSET_USED == STD_ON) && (CANTSYN_RX_CRC_USED == STD_ON))
/**
 * \brief Function used for time slave configuration in the case of a RX wait for an OFS message.
 * \param[in]  SlavePduId      - Slave Time Domain Id.
 * \param[in]  DataPtr         - Pointer containing the data needed for message
 *                               CRC computation.
 *
 * \return E_OK: Message Type and CRC accepted.
 *         E_NOT_OK: CRC not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_OfsMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
);

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
/**
 * \brief Function used for time slave configuration in the case of a RX wait (wait timeout) for
 * an OFS message.
 * \param[in]  SlavePduId      - Slave Time Domain Id.
 * \param[in]  DataPtr         - Pointer containing the data needed for message
 *                               CRC computation.
 *
 * \return E_OK: Message Type and CRC accepted.
 *         E_NOT_OK: CRC not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_OfnsMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
);
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) && (CANTSYN_RX_CRC_USED == STD_ON) */

#if(CANTSYN_RX_SYNC_USED == STD_ON)
/**
 * \brief Service to process the received SYNC message.
 * \param[in] T2VLT      - T2 virtual local time.
 *            DataPtr    - Pointer containing the received data.
 *            PduId       - Slave Pdu Id.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxSyncFrame
(
  StbM_VirtualLocalTimeType T2VLT,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
);

/**
 * \brief Service to process the received FUP message.
 * \param[in] PduId       - Slave Pdu Id.
 *            DataPtr     - Pointer containing the received data.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxFupFrame
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
);

/**
 * \brief Service to clear the sync state machine of the CanTSyn module.
 * \param[in] CanTSyn_SlavePduActiveIndex - Index of the active RxPduId.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_RxSyncReset
(
  uint8 CanTSyn_SlavePduActiveIndex
);
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */

#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
/**
 * \brief Service to check the current state of the ICV verification.
 * \param[in] DataPtr     - Pointer containing the received data.
 *            PduId       - Slave Pdu Id.
 *            IcvIndex    - Icv Slave Index.
 *            isFup       - boolean to distinguish between FUP and ExtOFS frames.
 */
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_IcvCheckState
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId,
  uint8 IcvIndex,
  boolean isFup
);
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

/**
 * \brief Service to clear the state machine of the CanTSyn module.
 * \param[in] SlavePduId - pduId
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_RxReset
(
  uint8 SlavePduId
);

/**
 * \brief Service to process the received frame
 * \param[in] SlavePduId        - Slave Time Domain Id.
 *            RxStatus          - Status of the current Slave Time Domain.
 *            DataPtr           - Pointer containing the data needed for message
 *                                type and CRC computation.
 *            T_VLT             - Virtual local time
 *            messageLength     - rx frame length
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxFrame
(
  uint8 SlavePduId,
  uint8 RxStatus,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  StbM_VirtualLocalTimeType T_VLT,
  PduLengthType messageLength
);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON)) */



#if(CANTSYN_RX_CRC_USED == STD_ON)

/**
 * \brief Service to check the CRC of the received message (either normal or extended).
 * \param[in] DataID     - Data Id taken from configuration based on the
 *                         message type.
 *            DataPtr    - Pointer containing the data needed for message
 *                         CRC computation.
 *            CrcLength  - CRC Length 7 (Normal message) or 15 (Extended message)
 *
 * \return E_OK: Message Type and CRC accepted.
 *         E_NOT_OK: Message Type and CRC not accepted for this SlaveDomainId
 *                   and RxStatus.
 */
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckCRC
(
  uint8 DataID,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 CrcLength
);
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */


#if(CANTSYN_RX_OFFSET_USED == STD_ON)
/**
 * \brief Service to clear the sync state machine of the CanTSyn module.
 * \param[in] CanTSyn_SlavePduActiveIndex - Index of the active RxPduId.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_RxOffsetReset
(
  uint8 CanTSyn_SlavePduActiveIndex
);

#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
/**
 * \brief Service to process the extended length received OFS message.
 * \param[in] T_VLT       - Virtual local time.
 *            DataPtr     - Pointer containing the received data.
 *            PduId       - Slave PduId.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessExtRxOfsFrame
(
  StbM_VirtualLocalTimeType T_VLT,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
);
#endif

/**
 * \brief Service to process the received OFS message.
 * \param[in] DataPtr     - Pointer containing the received data.
 *            PduId       - Slave PduId.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxOfsFrame
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
);

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
/**
 * \brief Service to process the received OFNS message.
 * \param[in] T_VLT       - Virtual local time.
 *            DataPtr     - Pointer containing the received data.
 *            PduId       - Slave Pdu Id.
 *
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxOfnsFrame
(
  StbM_VirtualLocalTimeType T_VLT,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
);
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */


#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)

#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
/**
 * \brief Service to generate the freshness value from FvM.
 * \param[in] TxDataPtr       - Pointer containing the frame data.
 *            FV              - Pointer containing the freshness value.
 *            PduIdx          - Master Pdu Id.
 *            IcvIndex        - CanTSyn_IcvMaster array index to be used.
 *            BYTE_FVL        - Byte where freshness value length is stored inside the frame.
 *            BYTE_ICVL       - Byte where ICV length shall be stored inside the frame.
 *            BYTE_START_FVL  - Starting byte number for the freshness value.
 *            UsedFVLength    - - Pointer containing freshness value length
 *  in bits .
 */
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_GenerateFreshnessValue
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) FV,
  uint8 PduIdx,
  uint8 IcvIndex,
  uint8 BYTE_FVL,
  uint8 BYTE_ICVL,
  uint8 BYTE_START_FVL,
  P2VAR(uint32, AUTOMATIC, CANTSYN_APPL_DATA) UsedFVL
);
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */

/**
 * \brief Service to refill the Fup or ExtOFS frame and attach the asynchronously generated ICV to the frame.
 * \param[in] SduDataPtr  - Pointer containing the frame data.
 *            PduIdx      - Master Pdu Id.
 *            IcvIndex    - CanTSyn_IcvMaster array index to be used.
 *            Offset      - Offset inside the CanTSyn_IcvData array where the FUP or ExtOFS frame contents were saved.
 *            FrameLength - Length of the FUP or ExtOFS, excluding freshness value and ICV
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_AddFvAndIcvToFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) SduDataPtr,
  uint8 PduIdx,
  uint8 IcvIndex,
#if(CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 Offset,
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
  uint8 FrameLength
);

/**
 * \brief Service to load frame contents and freshness value to CanTSyn_IcvData array to be used for ICV generation.
 * \param[in] TxDataPtr  - Pointer containing the frame data.
 *            PduIdx      - Master Pdu Id.
 *            FV          - pointer to location where FV is stored.
 *            Offset      - Offset inside the CanTSyn_IcvData array where the FUP or ExtOFS frame contents were saved.
 *            FrameLength - Length of the FUP or ExtOFS, excluding freshness value and ICV
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_CopyFrameAndFvToIcvData
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 PduIdx,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) FV,
#endif /* #if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
  uint32 Offset,
  uint8 FrameLength
);

#if(CANTSYN_TX_OFFSET_USED == STD_ON)
/**
 * \brief Service to check the current state of the ICV generation.
 * \param[in]   SduDataPtr      - Pointer containing the frame data.
 *              CanTSynPduIndex - PDU index
 * \param[out]  MessageAccepted - Indicates if message contents should be processed.
 *              RetVal          - Result of the check.
 *              sduDataLength   - Determined by the result of the ICV generation.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_CheckIcvGenerationState
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) SduDataPtr,
  uint8 CanTSynPduIndex,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) MessageAccepted,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) RetVal,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) sduDataLength
);
#endif /* (CANTSYN_TX_OFFSET_USED == STD_ON) */

/**
 * \brief Service to retrieve the freshness value from FvM and trigger the ICV generation.
 * \param[in] TxDataPtr      - Pointer containing the frame data.
 *            PduIdx          - Master Pdu Id.
 *            IcvIndex        - CanTSyn_IcvMaster array index to be used.
 *            BYTE_FVL        - Byte where freshness value length shall be stored inside the frame.
 *            BYTE_ICVL       - Byte where ICV length shall be stored inside the frame.
 *            BYTE_START_FVL  - Starting byte number for the freshness value.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_GenerateIcv
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  uint8 PduIdx,
  uint8 IcvIndex,
  uint8 BYTE_FVL,
  uint8 BYTE_ICVL,
  uint8 BYTE_START_FVL
);
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
/**
 * \brief Service to retrieve the freshness value from FvM and trigger the ICV verification.
 * \param[in] CanTSyn_IcvSlavePtr - Pointer to the IcvSlave data structure.
 *            PduIndex            - Slave Pdu Id.
 *            isFUP               - Indicates if received auth message is of FUP type.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_CheckIcvVerificationState
(
  P2VAR(CanTSyn_IcvSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvSlavePtr,
  uint8 PduIndex,
  boolean isFUP
);

#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))

#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
/**
 * \brief Service to retrieve the freshness value from FvM.
 * \param[in] DataPtr         - Pointer containing the frame data.
 *            PduId           - Slave Pdu Id.
 *            offset          - Offset inside the CanTSyn_IcvData array
 *            frameLength     - 10U for secure FUP/ 18U for secure ExtOfs
 *            IcvIndex        - CanTSyn_IcvMaster array index to be used.
 *            BYTE_FVL        - Byte where freshness value length is stored inside the frame.
 *            BYTE_START_FVL  - Starting byte number for the freshness value.
 */
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_FetchFreshnessValue
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId,
  uint8 IcvIndex,
  uint8 offset,
  uint8 frameLength,
  uint8 BYTE_FVL,
  uint8 BYTE_START_FVL
);
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */

/**
 * \brief Service to trigger the ICV verification.
 * \param[in] DataPtr         - Pointer containing the frame data.
 *            PduId           - Slave Pdu Id.
 *            IcvIndex        - CanTSyn_IcvMaster array index to be used.
 *            BYTE_FVL        - Byte where freshness value length is stored inside the frame.
 *            BYTE_ICVL       - Byte where ICV length shall is inside the frame.
 *            BYTE_START_FVL  - Starting byte number for the freshness value.
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_VerifyIcv
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId,
  uint8 IcvIndex,
  uint8 BYTE_FVL,
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
  uint8 BYTE_START_FVL,
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
  uint8 BYTE_ICVL
);
#endif /* if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if (CANTSYN_RX_SYNC_USED == STD_ON)
/**
 * \brief Service to process dropped SYNC/FUP message.
 * \param[in] rxPduId - slave sync pdu id
 * \param[in] apiId   - api id to be passed to DET
 *
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_SyncFupDropped
(
  uint8 rxPduId,
  uint8 apiId
);

/**
 * \brief Service to process sync/fup pair timeout.
 * \param[in] syncPtr - slave sync pointer
 *
 * \return true: timer expired.
 *         false: timer is still ongoing
 *
 */
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_ProcessSyncTimeout
(
  CanTSyn_SyncSlaveType * syncPtr
);
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */

#if (CANTSYN_RX_OFFSET_USED == STD_ON)
/**
 * \brief Service to process dropped OFS/OFNS message.
 * \param[in] rxPduId - slave sync pdu id
 * \param[in] apiId   - api id to be passed to DET
 *
 */
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_OfsOfnsDropped
(
  uint8 rxPduId,
  uint8 apiId
);

/**
 * \brief Service to process ofs/ofns pair timeout.
 * \param[in] ofsPtr - slave ofs pointer
 *
 * \return true: timer expired.
 *         false: timer is still ongoing
 *
 */
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_ProcessOfsTimeout
(
  CanTSyn_OffsetSlaveType * ofsPtr
);
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

#define CANTSYN_STOP_SEC_CODE
#include <CanTSyn_MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define CANTSYN_START_SEC_VAR_INIT_8
#include <CanTSyn_MemMap.h>

/** \brief Variable to indicate that module was initialized. */
STATIC VAR(boolean, CANTSYN_VAR) CanTSyn_Initialized = FALSE;



#define CANTSYN_STOP_SEC_VAR_INIT_8
#include <CanTSyn_MemMap.h>


#define CANTSYN_START_SEC_VAR_CLEARED_8
#include <CanTSyn_MemMap.h>

#if((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON))
STATIC VAR(CanTSyn_TransmissionModeType, CANTSYN_VAR) CanTSyn_TxMode[CANTSYN_NUMBER_OF_CONTROLLERS];
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON) */

#if(CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON)
/** \brief Variable to hold the current Hysteresis value */
STATIC VAR(uint8, CANTSYN_VAR) CanTSyn_HysteresisArray[CANTSYN_TS_SIZE];
#endif /* (CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON) */

#if((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON))
/** \brief Array to hold data necessary for ICV authentication. */
STATIC VAR(uint8, CANTSYN_VAR) CanTSyn_IcvData[CANTSYN_ICV_DATA_ARRAY_SIZE];

/** \brief Array to hold the generated ICV for all time domains. */
  /* Deviation MISRAC2012-1 */
STATIC VAR(uint8, CANTSYN_VAR) CanTSyn_ComputedIcv[CANTSYN_ICV_COMPUTED_ARRAY_SIZE];
#endif

#define CANTSYN_STOP_SEC_VAR_CLEARED_8
#include <CanTSyn_MemMap.h>


#define CANTSYN_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanTSyn_MemMap.h>
/* !LINKSTO CanTSyn.dsn.PrecompileTimeConfig,1 */
#if(CANTSYN_TX_SYNC_USED == STD_ON)
/** \brief Sync Messages Master variable. */
STATIC VAR(CanTSyn_SyncMasterType, CANTSYN_VAR) CanTSyn_SyncMaster[CANTSYN_NUMBER_OF_SYNC_MASTERS];
#endif /* CANTSYN_TX_SYNC_USED == STD_ON */

#if(CANTSYN_TX_OFFSET_USED == STD_ON)
/** \brief Offset Messages Master variable. */
STATIC VAR(CanTSyn_OffsetMasterType, CANTSYN_VAR) CanTSyn_OffsetMaster[CANTSYN_NUMBER_OF_OFFSET_MASTERS];
#endif /* CANTSYN_TX_OFFSET_USED == STD_ON */

#if(CANTSYN_RX_SYNC_USED == STD_ON)
/** \brief Sync Messages Slave variable. */
STATIC VAR(CanTSyn_SyncSlaveType, CANTSYN_VAR) CanTSyn_SyncSlave[CANTSYN_NUMBER_OF_SYNC_SLAVES];
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
/** \brief Sync Messages Slave variable. */
STATIC VAR(CanTSyn_OffsetSlaveType, CANTSYN_VAR) CanTSyn_OffsetSlave[CANTSYN_NUMBER_OF_OFFSET_SLAVES];
#endif /* CANTSYN_RX_OFFSET_USED == STD_ON */

#if (CANTSYN_ICV_GENERATION_SUPPORTED)
/** \brief ICV Master variable. */
STATIC VAR(CanTSyn_IcvMasterType, CANTSYN_VAR) CanTSyn_IcvMaster[CANTSYN_NUMBER_OF_ICV_MASTERS];
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED) */

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED)
/** \brief ICV Slave variable. */
STATIC VAR(CanTSyn_IcvSlaveType, CANTSYN_VAR) CanTSyn_IcvSlave[CANTSYN_NUMBER_OF_ICV_SLAVES];
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED) */

#define CANTSYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanTSyn_MemMap.h>

/*==================[external function definitions]=========================*/
#define CANTSYN_START_SEC_CODE
#include <CanTSyn_MemMap.h>


#if(CANTSYN_VERSION_INFO_API == STD_ON)
/* !LINKSTO CanTSyn.SWS_CanTSyn_00094,1 */
FUNC(void, CANTSYN_CODE) CanTSyn_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CANTSYN_APPL_DATA) versioninfo
)
{
  DBG_CANTSYN_GETVERSIONINFO_ENTRY(versioninfo);

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* check if the versioninfo pointer is a Null Pointer */
  /* !LINKSTO CanTSyn.EB.GetVersionInfo.NullPtr,1 */
  if(NULL_PTR == versioninfo)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00088,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_GETVERSIONINFO, CANTSYN_E_NULL_POINTER);
  }
  else
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    /* Return version information */
    versioninfo->vendorID = CANTSYN_VENDOR_ID;
    versioninfo->moduleID = CANTSYN_MODULE_ID;
    versioninfo->sw_major_version = CANTSYN_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CANTSYN_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CANTSYN_SW_PATCH_VERSION;
  }

  DBG_CANTSYN_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* CANTSYN_VERSION_INFO_API */


#if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON))
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_Icv_Init
(
    P2CONST(CanTSyn_ConfigType, AUTOMATIC, CANTSYN_APPL_CONST) configPtr
)
{

  uint8 IcvIndex = 0U;
  uint8 PduIdx;

  TS_PARAM_UNUSED(configPtr);

#if (CANTSYN_ICV_GENERATION_SUPPORTED)
#if (CANTSYN_TX_SYNC_USED == STD_ON)
  /* Deviation TASKING-1 */
  for(PduIdx = 0U;
      PduIdx < CANTSYN_NUMBER_OF_SYNC_MASTERS;
      PduIdx++)
  {
    if(CanTSyn_TimeMasterConfig[PduIdx].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      CanTSyn_SyncMaster[PduIdx].IcvIndex = IcvIndex;

      /* initialize ICV auth state */
      /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Initial_NotRequested,1 */
      CanTSyn_IcvMaster[IcvIndex].IcvGenerationState = CANTSYN_ICV_STATE_NOT_REQUESTED;

      /* initialize ICV auth async generation timeout */
      CanTSyn_IcvMaster[IcvIndex].IcvGenerationTimeout = 0U;

      IcvIndex++;
    }
  }
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) */
#if(CANTSYN_TX_OFFSET_USED == STD_ON)
  /* Deviation TASKING-1 */
  for(PduIdx = 0U;
      PduIdx < CANTSYN_NUMBER_OF_OFFSET_MASTERS;
      PduIdx++)
  {
    if(CanTSyn_TimeMasterConfig[PduIdx + CANTSYN_NUMBER_OF_SYNC_MASTERS].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      CanTSyn_OffsetMaster[PduIdx].IcvIndex = IcvIndex;

      /* initialize ICV auth state */
      /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Initial_NotRequested,1 */
      CanTSyn_IcvMaster[IcvIndex].IcvGenerationState = CANTSYN_ICV_STATE_NOT_REQUESTED;

      /* initialize ICV auth async generation timeout */
      CanTSyn_IcvMaster[IcvIndex].IcvGenerationTimeout = 0U;

      IcvIndex++;
    }
  }
#endif /* (CANTSYN_TX_OFFSET_USED == STD_ON) */
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED) */

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED)
    IcvIndex = 0U;
#if (CANTSYN_RX_SYNC_USED == STD_ON)
  /* Deviation TASKING-1 */
  for(PduIdx = 0U;
      PduIdx < CANTSYN_NUMBER_OF_SYNC_SLAVES;
      PduIdx++)
  {
    if((CanTSyn_TimeSlaveConfig[PduIdx].IcvVerificationType == CANTSYN_ICV_VERIFIED) || ((CanTSyn_TimeSlaveConfig[PduIdx].IcvVerificationType == CANTSYN_ICV_OPTIONAL)))
    {

      CanTSyn_SyncSlave[PduIdx].IcvIndex = IcvIndex;

      /* initialize Icv verification attempts */
      CanTSyn_IcvSlave[IcvIndex].IcvVerificationAttempts = 0U;

      /* initialize timeout for async Icv verification */
      CanTSyn_IcvSlave[IcvIndex].IcvVerificationTimeout = 0U;

      /* initialize IcvVerificationState */
      /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Initial_NotRequested,1 */
      CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_NOT_REQUESTED;

      /* initialize recov error */
      CanTSyn_IcvSlave[IcvIndex].IcvFvRecovError = FALSE;

      IcvIndex++;
    }
  }
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */
#if(CANTSYN_RX_OFFSET_USED == STD_ON)
  /* Deviation TASKING-1 */
  for(PduIdx = 0U;
      PduIdx < CANTSYN_NUMBER_OF_OFFSET_SLAVES;
      PduIdx++)
  {
    if((CanTSyn_TimeSlaveConfig[PduIdx + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_VERIFIED) ||
      ((CanTSyn_TimeSlaveConfig[PduIdx + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_OPTIONAL)))
    {
      CanTSyn_OffsetSlave[PduIdx].IcvIndex = IcvIndex;

      /* initialize Icv verification attempts */
      CanTSyn_IcvSlave[IcvIndex].IcvVerificationAttempts = 0U;

      /* initialize timeout for async Icv verification */
      CanTSyn_IcvSlave[IcvIndex].IcvVerificationTimeout = 0U;

      /* initialize IcvVerificationState */
      /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Initial_NotRequested,1 */
      CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_NOT_REQUESTED;

      /* initialize recov error */
      CanTSyn_IcvSlave[IcvIndex].IcvFvRecovError = FALSE;

      IcvIndex++;
    }
  }
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED) */
}
#endif /* ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)) */

/* !LINKSTO CanTSyn.SWS_CanTSyn_00093,1 */
FUNC(void, CANTSYN_CODE) CanTSyn_Init
(
  P2CONST(CanTSyn_ConfigType, AUTOMATIC, CANTSYN_APPL_CONST) configPtr
)
{
  uint8 PduIdx;

  DBG_CANTSYN_INIT_ENTRY(configPtr);

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanTSyn.EB.Init.ConfigPtr,1 */
  /* current implementation supports only Precompile variant */
  if(NULL_PTR != configPtr)
  {
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_INIT, CANTSYN_E_INIT_FAILED);
  }
  else
#else
  TS_PARAM_UNUSED(configPtr);
#endif
  {

#if((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON))
    {
      uint8 CtrlIdx;
      /* !LINKSTO CanTSyn.dsn.Mode.Initialization,1 */
      /* Accept all transmit requests on all channels */
      /* Deviation TASKING-1 */
      for(CtrlIdx = 0U; CtrlIdx < CANTSYN_NUMBER_OF_CONTROLLERS; CtrlIdx++)
      {
        CanTSyn_TxMode[CtrlIdx] = CANTSYN_TX_ON;
      }
    }
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON) */

#if(CANTSYN_TX_SYNC_USED == STD_ON)
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00003,1 */
    /* Deviation TASKING-1 */
    for(PduIdx = 0U; PduIdx < CANTSYN_NUMBER_OF_SYNC_MASTERS; PduIdx++)
    {
      P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
            CanTSyn_MasterPtr = &CanTSyn_SyncMaster[PduIdx];

      /* initialize module variables */
      CanTSyn_TxSyncReset(PduIdx);

      /* Clear the Sequence Counter */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00007,1 */
      CanTSyn_MasterPtr->SeqCount = 0U;

      /* Clear the SGW Bit */
      CanTSyn_MasterPtr->SyncSGWBit = 0U;

      /* clear the Tx Period Time */
      CanTSyn_MasterPtr->TimeTxPeriod = 0U;

      /* initialize syncTimeBaseCounter */
      CanTSyn_MasterPtr->syncTimeBaseCounter = 0U;

#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
      /* initialize the transmition retries Counter */
      CanTSyn_MasterPtr->SyncTransRetriesCounter = 0U;
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */

#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
      /* initialize SYNC CyclicMsgResumeTime timer */
      CanTSyn_MasterPtr->CyclicMsgResumeTime = 0U;
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
    }
#endif /* CANTSYN_TX_SYNC_USED == STD_ON */

#if(CANTSYN_TX_OFFSET_USED == STD_ON)
    /* Deviation TASKING-1 */
    for(PduIdx = 0U;
        PduIdx < CANTSYN_NUMBER_OF_OFFSET_MASTERS;
        PduIdx++)
    {
      P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[PduIdx];

      /* initialize module variables */
      CanTSyn_TxOffsetReset(PduIdx);

      /* Clear the Sequence Counter */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00007,1 */
      CanTSyn_OffsetMasterPtr->SeqCount = 0U;

      /* Clear the Offset SGW Bit */
      CanTSyn_OffsetMasterPtr->OfsSGWBit = 0U;

      /* clear the Tx Period Time */
      CanTSyn_OffsetMasterPtr->TimeTxPeriod = 0U;

      /* initialize syncTimeBaseCounter */
      CanTSyn_OffsetMasterPtr->OfsTimeBaseCounter = 0U;

#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
      /* initialize the transmition retries Counter */
      CanTSyn_OffsetMasterPtr->OfsTransRetriesCounter = 0U;
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */

#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
      /* initialize OFS CyclicMsgResumeTime timer */
      CanTSyn_OffsetMasterPtr->CyclicMsgResumeTime = 0U;
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
    }
#endif /* CANTSYN_TX_OFFSET_USED == STD_ON */

#if(CANTSYN_RX_SYNC_USED == STD_ON)
    /* Deviation TASKING-1 */
    for(PduIdx = 0U;
        PduIdx < CANTSYN_NUMBER_OF_SYNC_SLAVES;
        PduIdx++)
    {
      /* initialize module variables */
      CanTSyn_SyncSlave[PduIdx].SeqCount = CANTSYN_SC_STARTUP_TIMEOUT;

      /* initialize Rx debounce time */
      CanTSyn_SyncSlave[PduIdx].RxDebounceTime = 0U;

      /* initialize SYNC RxStatus and all the variables for a new SYNC reception */
      /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_Init,1 */
      CanTSyn_RxSyncReset(PduIdx);


#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      /* reset the timer for DEM/DET reporting */
      CanTSyn_SyncSlave[PduIdx].SyncPairTimer = 0U;
#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
      /* reset the number of failed frames regarding DET reporting */
      CanTSyn_SyncSlave[PduIdx].SyncPairsDroppedCnt = 0U;
#endif
#endif
    }
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */

#if(CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON)
    /* Deviation TASKING-1 */
    for(PduIdx = 0U;
        PduIdx < CANTSYN_TS_SIZE;
        PduIdx++)
    {
      CanTSyn_HysteresisArray[PduIdx] = 0U;
    }
#endif /* (CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON) */

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    /* Deviation TASKING-1 */
    for(PduIdx = 0U;
        PduIdx < CANTSYN_NUMBER_OF_OFFSET_SLAVES;
        PduIdx++)
    {
      /* initialize module variables */
      CanTSyn_OffsetSlave[PduIdx].SeqCount = CANTSYN_SC_STARTUP_TIMEOUT;

      /* initialize Rx debounce time */
      CanTSyn_OffsetSlave[PduIdx].RxDebounceTime = 0U;

      /* initialize OFS RxStatus and all the variables for a new OFS reception */
      /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_Init,1 */
      CanTSyn_RxOffsetReset(PduIdx);

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      /* reset the timer for DEM/DET reporting */
      CanTSyn_OffsetSlave[PduIdx].OfsPairTimer = 0U;
#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
      /* reset the number of failed frames regarding DET reporting */
      CanTSyn_OffsetSlave[PduIdx].OfsPairsDroppedCnt = 0U;
#endif
#endif
    }
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */

#if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON))
    /* initialize the data structures used for ICV authentication */
    (void)(CanTSyn_Icv_Init(configPtr));
#endif /* ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) || (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)) */

    /* module initialized */
    CanTSyn_Initialized = TRUE;
  }

  DBG_CANTSYN_INIT_EXIT(configPtr);
}

#if((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON))
/* !LINKSTO CanTSyn.SWS_CanTSyn_00095,1 */
FUNC(void, CANTSYN_CODE) CanTSyn_SetTransmissionMode
(
  uint8 CtrlIdx,
  CanTSyn_TransmissionModeType Mode
)
{
  DBG_CANTSYN_SETTRANSMISSIONMODE_ENTRY(CtrlIdx, Mode);

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanTSyn.EB.SetTransmissionMode.Uninit,1 */
  if(FALSE == CanTSyn_Initialized)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00088,1 */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_SETTRANSMISSIONMODE, CANTSYN_E_UNINIT);
  }
  else if((CANTSYN_TX_ON != Mode) && (CANTSYN_TX_OFF != Mode))
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00134,1 */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_SETTRANSMISSIONMODE, CANTSYN_E_PARAM);
  }
  else
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 PduIndex;
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
    boolean ControllerFound = FALSE;
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
    for(PduIndex = 0U;
        /* Deviation TASKING-1 */
        PduIndex < (CANTSYN_NUMBER_OF_SYNC_MASTERS + CANTSYN_NUMBER_OF_OFFSET_MASTERS);
        PduIndex++)
    {
      if(CtrlIdx == CanTSyn_TimeMasterConfig[PduIndex].ControllerId)
      {
        /* set the Time Master mode to the requested one */
        CanTSyn_TxMode[CanTSyn_TimeMasterConfig[PduIndex].CtrlIndex] = Mode;
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
        ControllerFound = TRUE;
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
        break;
      }
    }
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
    if(FALSE == ControllerFound)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00134,1 */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
      CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_SETTRANSMISSIONMODE, CANTSYN_E_INV_CTRL_IDX);
    }
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
  }

  DBG_CANTSYN_SETTRANSMISSIONMODE_EXIT(CtrlIdx, Mode);
}
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON) */


#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_CheckAuthMsgLength
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr
)
{
  boolean wrongLength = TRUE;

  if(CanTSyn_TimeSlaveConfig[RxPduId].IcvVerificationType == CANTSYN_ICV_NOT_VERIFIED)
  {
    if((uint8)(PduInfoPtr->SduLength) == CANTSYN_EXTENDED_MSG_SIZE)
    {
      /* if this check is reached it means extended message format is supported */
      /* 16 bytes long frame is expected */
      wrongLength = FALSE;
    }
  }
  else if(CanTSyn_TimeSlaveConfig[RxPduId].IcvVerificationType == CANTSYN_ICV_IGNORED)
  {
    if((uint8)(PduInfoPtr->SduLength) >= CANTSYN_EXTENDED_MSG_SIZE)
    {
      /* frame must be at least 16 bytes long because extended message format is used */
      /* frame can be longer because it might contain ICV */
      wrongLength = FALSE;
    }
  }
  else /* if((CanTSyn_TimeSlaveConfig[RxPduId].IcvVerificationType == CANTSYN_ICV_OPTIONAL) ||  (CanTSyn_TimeSlaveConfig[RxPduId].IcvVerificationType == CANTSYN_ICV_VERIFIED)) */
  {
    if((uint8)(PduInfoPtr->SduLength) > 0U)
    {
      /* the frame is not empty */
      switch(PduInfoPtr->SduDataPtr[0])
      {
        /* FUP messages */
        /* Fall through */
        case CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH:
        case CANTSYN_FUP_WITH_CRC_ICV_AUTH:
        {
          if(((uint8)(PduInfoPtr->SduLength) == (CANTSYN_FUP_ICV_PAYLOAD_LENGTH + CanTSyn_TimeSlaveConfig[RxPduId].ExpectedSecurityPayloadLength)) ||
            ((uint8)(PduInfoPtr->SduLength) == (CANTSYN_FUP_ICV_PAYLOAD_LENGTH + CanTSyn_TimeSlaveConfig[RxPduId].IcvRxLength)))
          {
            /* frame length does match the expected length for an ICV authenticated message */
            wrongLength = FALSE;
          }
          break;
        }
        /* OFS messages */
        /* Fall through */
        case CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH:
        case CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH:
        {
          if(((uint8)(PduInfoPtr->SduLength) == (CANTSYN_OFS_ICV_PAYLOAD_LENGTH + CanTSyn_TimeSlaveConfig[RxPduId].ExpectedSecurityPayloadLength)) ||
            ((uint8)(PduInfoPtr->SduLength) == (CANTSYN_OFS_ICV_PAYLOAD_LENGTH + CanTSyn_TimeSlaveConfig[RxPduId].IcvRxLength)))
          {
            /* frame length does match the expected length for an ICV authenticated message */
            wrongLength = FALSE;
          }
          break;
        }
        default:
        {
          if((uint8)(PduInfoPtr->SduLength) == CANTSYN_EXTENDED_MSG_SIZE)
          {
            wrongLength = FALSE;
          }
          break;
        }
      }
    }
    if((CanTSyn_TimeSlaveConfig[RxPduId].IcvVerificationType == CANTSYN_ICV_OPTIONAL) && ((uint8)(PduInfoPtr->SduLength) == CANTSYN_EXTENDED_MSG_SIZE))
    {
      /* extended frames without ICV are accepted if ICV verification is optional  */
      wrongLength = FALSE;
    }
  }

  return wrongLength;
}
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */


#if ( (CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckRxDebounceTime
(
  PduIdType RxPduId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
  if((uint8)(RxPduId) < CANTSYN_NUMBER_OF_SYNC_SLAVES)
  {
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#if(CANTSYN_RX_SYNC_USED == STD_ON)
    /* sync domain */
    if(CanTSyn_SyncSlave[(uint8)(RxPduId)].RxDebounceTime > 0U)
    {
      /* RxDebounceTime still running, drop frame */
      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
    /* reset Rx debounce time */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00183.AlsoLoadDebounce,1 */
    CanTSyn_SyncSlave[RxPduId].RxDebounceTime = CanTSyn_TimeSlaveConfig[RxPduId].RxDebounceTime;
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
  }
  else
  {
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    if(CanTSyn_OffsetSlave[(uint8)(RxPduId) - (uint8)CANTSYN_NUMBER_OF_SYNC_SLAVES].RxDebounceTime > 0U)
    {
      /* RxDebounceTime still running, drop frame */
      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
    /* reset Rx debounce time */
    /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeRxDebounceTime.ExtOfs,1 */
    CanTSyn_OffsetSlave[RxPduId - CANTSYN_NUMBER_OF_SYNC_SLAVES].RxDebounceTime = CanTSyn_TimeSlaveConfig[RxPduId].RxDebounceTime;
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
  }
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */

  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  if(RetVal == E_NOT_OK)
  {
#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING)
  #ifdef CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR
    /* message received during rx debounce time; report event to IdsM */
    /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeRxDebounceTime.OfsOfnsPair,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00204,1 */
    IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR, &CanTSyn_TimeSlaveConfig[(uint8)RxPduId].TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING) */

    /* reset SYNC-FUP sequence (to start with a new SYNC) / reset OFS-OFNS sequence (to start with a new OFS) */
    CanTSyn_RxReset((uint8)RxPduId);
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_RxIndication_Validation
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* check if the module was initialized */
  if(FALSE == CanTSyn_Initialized)
  {
    /* !LINKSTO CanTSyn.EB.RxIndication.Uninit,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00088,1 */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_RXINDICATION, CANTSYN_E_UNINIT);
  }
  else if(NULL_PTR == PduInfoPtr)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00097.PduInfoPtr.E_NULL_POINTER.RxIndication,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_RXINDICATION, CANTSYN_E_NULL_POINTER);
  }
  else if(NULL_PTR == PduInfoPtr->SduDataPtr)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00097.SduDataPtr.E_NULL_POINTER.RxIndication,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_RXINDICATION, CANTSYN_E_NULL_POINTER);
  }
  /* check if received PduId exists */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
  else if( ( (uint8)CANTSYN_NUMBER_OF_SLAVES - (uint8)1U ) < (uint8)RxPduId )
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00097.INVALID_PDUID.RxIndication,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_RXINDICATION, CANTSYN_E_INVALID_PDUID);
  }
  else
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
  {

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_LENGTH == STD_ON)
    boolean reportEvent_WrongLength = FALSE;
#endif /* (CANTSYN_REPORT_WRONG_LENGTH == STD_ON) */
#if(CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON)
    boolean reportEvent_WrongTimeDomainId = FALSE;
#endif /* (CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

    /* check the received Pdu Length */
#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVNotSupported,1 */
    if(CanTSyn_TimeSlaveConfig[RxPduId].IsExtendedMessage == 1U )
    {
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
      /* returns TRUE in case of wrong length */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVSupported,1 */
      if(CanTSyn_CheckAuthMsgLength((uint8)RxPduId, PduInfoPtr) == FALSE)
      {
        RetVal = E_OK;
      }
#else /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
      if( (uint8)(PduInfoPtr->SduLength) == CANTSYN_EXTENDED_MSG_SIZE)
      {
        RetVal = E_OK;
      }
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
    }
    if((CanTSyn_TimeSlaveConfig[RxPduId].IsExtendedMessage == 1U) && (RetVal == E_NOT_OK))
    {
      /* !LINKSTO CanTSyn.EB.DLC.ExtendedMessage.INVALID_PDU_LENGTH.RxIndication,1 */
      /* reset RxStatus due to wrong length */
      CanTSyn_RxReset((uint8)RxPduId);

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_LENGTH == STD_ON)
      reportEvent_WrongLength = TRUE;
#endif /* (CANTSYN_REPORT_WRONG_LENGTH == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
    }
    else if( ( CanTSyn_TimeSlaveConfig[RxPduId].IsExtendedMessage == 0U ) && ( (uint8)(PduInfoPtr->SduLength) != CANTSYN_MSG_SIZE)  )
    {
      /* !LINKSTO CanTSyn.EB.DLC.NormalMessage.INVALID_PDU_LENGTH.RxIndication,1 */
      /* reset RxStatus due to wrong length */
      RetVal = E_NOT_OK;
      CanTSyn_RxReset((uint8)RxPduId);

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_LENGTH == STD_ON)
      reportEvent_WrongLength = TRUE;
#endif /* (CANTSYN_REPORT_WRONG_LENGTH == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
    }
#else /* CANTSYN_RX_USE_EXTENDED_MSG == STD_ON */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.NormalMessage,1 */
    if(  (uint8)(PduInfoPtr->SduLength) != CANTSYN_MSG_SIZE  )
    {
      /* !LINKSTO CanTSyn.EB.DLC.NormalMessage.INVALID_PDU_LENGTH.RxIndication,1 */
      /* reset RxStatus due to wrong length */
      RetVal = E_NOT_OK;
      CanTSyn_RxReset((uint8)RxPduId);

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_LENGTH == STD_ON)
      reportEvent_WrongLength = TRUE;
#endif /* (CANTSYN_REPORT_WRONG_LENGTH == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
    }
#endif /* CANTSYN_RX_USE_EXTENDED_MSG == STD_ON */
    /* check if received PduId exists */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
    else if( (CANTSYN_GET_DOMAINID_SLAVE(PduInfoPtr->SduDataPtr[2U]) != CanTSyn_TimeSlaveConfig[RxPduId].TimeDomainId) )
    {
      boolean resetState = FALSE;
      /* CanTSyn shall wait for a FUP/OFNS frame with a correct timeDomainId until RxFollowUpOffsetTimeout expires */

      RetVal = E_NOT_OK;
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      if(RxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
      {
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#if(CANTSYN_RX_SYNC_USED == STD_ON)
         if(((CanTSyn_SyncSlave[RxPduId].RxStatus == CANTSYN_FUPMSG_RX_WAIT) || (CanTSyn_SyncSlave[RxPduId].RxStatus == CANTSYN_FUPMSG_RX_WAIT_TIMEOUT)) && (CanTSyn_SyncSlave[RxPduId].TimeRxFollowUpOffset > 0U))
         {
           /* do nothing */
         }
         else
         {
           resetState = TRUE;
         }
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      }
      else
      {
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#if(CANTSYN_RX_OFFSET_USED == STD_ON)
         if(((CanTSyn_OffsetSlave[RxPduId - CANTSYN_NUMBER_OF_SYNC_SLAVES].RxStatus == CANTSYN_OFNSMSG_RX_WAIT) || (CanTSyn_OffsetSlave[RxPduId - CANTSYN_NUMBER_OF_SYNC_SLAVES].RxStatus == CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT)) && (CanTSyn_OffsetSlave[RxPduId - CANTSYN_NUMBER_OF_SYNC_SLAVES].TimeRxFollowUpOffset > 0U))
         {
           /* do nothing */
         }
         else
         {
           resetState = TRUE;
         }
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      }
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */

      if(resetState == TRUE)
      {
        /* reset RxStatus due to wrong time domain id */
        CanTSyn_RxReset((uint8)RxPduId);

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON)
        reportEvent_WrongTimeDomainId = TRUE;
#endif /* (CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
      }
    }
    else
    {
      RetVal = E_OK ;
    }


#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if((CANTSYN_REPORT_WRONG_LENGTH== STD_ON) && (CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON))
    if(reportEvent_WrongLength == TRUE)
    {
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      /* in case of wrong length, report dropped frame to DEM/DET */
      if(RxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongLength,1 */
        CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
      }
      else
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongLength,1 */
        CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
      }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongLength,1 */
      CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongLength,1 */
      CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
    }
    else if(reportEvent_WrongTimeDomainId == TRUE)
    {
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      /* in case of wrong timeDomainId, report dropped frame to DEM/DET */
      if(RxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongTimeDomainId,1 */
        CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
      }
      else
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongTimeDomainId,1 */
        CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
      }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongTimeDomainId,1 */
      CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongTimeDomainId,1 */
      CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
    }
    else
    {
      /* do nothing */
    }
#elif(CANTSYN_REPORT_WRONG_LENGTH == STD_ON)
    if (reportEvent_WrongLength == TRUE)
    {
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      /* in case of wrong length, report dropped frame to DEM/DET */
      if(RxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongLength,1 */
        CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
      }
      else
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongLength,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongLength,1 */
        CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
      }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongLength,1 */
      CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongLength,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongLength,1 */
      CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
    }
#elif(CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON)
    if (reportEvent_WrongTimeDomainId == TRUE)
    {
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      /* in case of wrong timeDomainId, report dropped frame to DEM/DET */
      if(RxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongTimeDomainId,1 */
        CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
      }
      else
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongTimeDomainId,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongTimeDomainId,1 */
        CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
      }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongTimeDomainId,1 */
      CanTSyn_SyncFupDropped((uint8)RxPduId, CANTSYN_SID_RXINDICATION);
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongTimeDomainId,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongTimeDomainId,1 */
      CanTSyn_OfsOfnsDropped((uint8)(RxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
    }
#endif /* ((CANTSYN_REPORT_WRONG_LENGTH== STD_ON) && (CANTSYN_REPORT_WRONG_TIMEDOMAINID == STD_ON)) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

  }

  if(RetVal == E_OK)
  {
    /* check that message was received after the debounce time expired */
    RetVal = CanTSyn_CheckRxDebounceTime(RxPduId);
  }

  return RetVal;
}
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON) */






/* !LINKSTO CanTSyn.EB.CanTSyn_RxIndication_PduInfoPtr,1 */
FUNC(void, CANTSYN_CODE) CanTSyn_RxIndication
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr
)
{
#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))

  DBG_CANTSYN_RXINDICATION_ENTRY(RxPduId, PduInfoPtr);

  if( CanTSyn_RxIndication_Validation(RxPduId, PduInfoPtr) == E_OK)
  {
    const uint8 rxPduId = (uint8)RxPduId;
    uint8 RxStatus;
    P2CONST(CanTSyn_TimeSlaveDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) SlaveConfigPtr = &CanTSyn_TimeSlaveConfig[rxPduId];
    P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) sduDataPtr = PduInfoPtr->SduDataPtr;
    boolean ProcessFrame = FALSE;
    boolean CrcValidation = FALSE;
    StbM_VirtualLocalTimeType T_VLT = {0U, 0U};
    StbM_SynchronizedTimeBaseType TimeBaseId;

    /* get the status */
    CanTSyn_GetRxStatus(rxPduId, &RxStatus);

    TimeBaseId = SlaveConfigPtr->SyncTimeBaseId;

    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00144.InterruptProtection,1 */
    SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_1();

    /* The CrcValidation will be TRUE if the time domain is configured to CRC_VALIDATION
       or CRC_OPTIONAL with message type indicating that CRC validation should be performed. */
    if(E_OK == CanTSyn_CheckMsgType(rxPduId, RxStatus, sduDataPtr, &CrcValidation))
    {
      /* !LINKSTO CanTSyn.EB.Rx_StbM_GetCurrentVirtualLocalTime_E_NOT_OK,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00144.RetrieveT1VLT,1 */
      if(E_OK == StbM_GetCurrentVirtualLocalTime(TimeBaseId, &T_VLT))
      {
        ProcessFrame = TRUE;
      }
    }

    SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_1();

    if(ProcessFrame)
    {
#if(CANTSYN_RX_CRC_USED == STD_ON)
    /* check if the received type shall be accepted */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
      Std_ReturnType CrcRetVal;
      if(TRUE == CrcValidation)
      {
        CrcRetVal = CanTSyn_CheckMsgCRC(rxPduId, RxStatus, sduDataPtr);
      }
      else
      {
        CrcRetVal = E_OK;
      }

      if(E_OK == CrcRetVal)
#endif /* CANTSYN_RX_CRC_USED == STD_ON */
      {
        /* process Rx frame */
        CanTSyn_ProcessRxFrame(rxPduId, RxStatus, sduDataPtr, T_VLT, PduInfoPtr->SduLength);
      }
#if(CANTSYN_RX_CRC_USED == STD_ON)
      else
      {
        /* reset RxStatus due to wrong CRC */
        CanTSyn_RxReset(rxPduId);
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_CRC== STD_ON)
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
        /* in case of failed CRC, report dropped frame to DEM/DET */
        if(rxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
        {
          /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongCRC,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongCRC,1 */
          CanTSyn_SyncFupDropped(rxPduId, CANTSYN_SID_RXINDICATION);
        }
        else
        {
          /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongCRC,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongCRC,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongCRC,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongCRC,1 */
          CanTSyn_OfsOfnsDropped((rxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
        }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
        /* in case of failed CRC, report dropped frame to DEM/DET */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongCRC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongCRC,1 */
        CanTSyn_SyncFupDropped(rxPduId, CANTSYN_SID_RXINDICATION);
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
        /* in case of failed CRC, report dropped frame to DEM/DET */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongCRC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongCRC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongCRC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongCRC,1 */
        CanTSyn_OfsOfnsDropped((rxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#endif /* (CANTSYN_REPORT_WRONG_CRC == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
      }
#endif /* CANTSYN_RX_CRC_USED == STD_ON */
    }
    else
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00206,1 */
      /* reset RxStatus due to wrong type */
      CanTSyn_RxReset(rxPduId);
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_MSGTYPE== STD_ON)
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
      /* in case of wrong frame type, report dropped frame to DEM/DET */
      if(rxPduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongMsgType,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongMsgType,1 */
        CanTSyn_SyncFupDropped(rxPduId, CANTSYN_SID_RXINDICATION);
      }
      else
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongMsgType,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongMsgType,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongMsgType,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongMsgType,1 */
        CanTSyn_OfsOfnsDropped((rxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
      }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
      /* in case of wrong frame type, report dropped frame to DEM/DET */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongMsgType,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongMsgType,1 */
      CanTSyn_SyncFupDropped(rxPduId, CANTSYN_SID_RXINDICATION);
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
      /* in case of wrong frame type, report dropped frame to DEM/DET */
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongMsgType,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongMsgType,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongMsgType,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongMsgType,1 */
      CanTSyn_OfsOfnsDropped((rxPduId-CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
#endif /* (CANTSYN_REPORT_WRONG_MSGTYPE == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
    }
  }
  /* else discard frame */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00206,1 */

  DBG_CANTSYN_RXINDICATION_EXIT(RxPduId, PduInfoPtr);
#else
  /* No support for Time Slave */
  TS_PARAM_UNUSED(RxPduId);
  TS_PARAM_UNUSED(PduInfoPtr);
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON) */
}


/* !LINKSTO CanTSyn.SWS_CanTSyn_00099,1 */
FUNC(void, CANTSYN_CODE) CanTSyn_TxConfirmation
(
  PduIdType TxPduId
#if(CANTSYN_RELIABLE_TXCONF == STD_ON)
  ,Std_ReturnType result
#endif /* CANTSYN_RELIABLE_TXCONF == STD_ON */
)
{
#if((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON))
#if(CANTSYN_RELIABLE_TXCONF == STD_OFF)
  DBG_CANTSYN_TXCONFIRMATION_ENTRY(TxPduId);
#else
  DBG_CANTSYN_TXCONFIRMATION_ENTRY(TxPduId,result);
#endif /* #if(CANTSYN_RELIABLE_TXCONF == STD_OFF) */

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* check if the module was initialized */
  if(FALSE == CanTSyn_Initialized)
  {
    /* !LINKSTO CanTSyn.EB.TxConfirmation.Uninit,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00088,1 */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_TXCONFIRMATION, CANTSYN_E_UNINIT);
  }
  /* check if the function was called with valid PduId */
  else
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    /* check PduId validity */
    if((CANTSYN_NUMBER_OF_MASTERS - 1U) < TxPduId)
    {
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00100,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00088,1 */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00089,1 */
      CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_TXCONFIRMATION, CANTSYN_E_INVALID_PDUID);
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
    }
    else
    {
#if(CANTSYN_TX_OFFSET_USED == STD_ON)
      /* check if the Confirmation is for a SYNC/FUP or OFS/OFNS received */
      if(TxPduId >= CANTSYN_NUMBER_OF_SYNC_MASTERS)
      {
#if(CANTSYN_RELIABLE_TXCONF == STD_ON)
        P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_VAR) CanTSyn_OfsMasterPtr =
                                             &CanTSyn_OffsetMaster[(uint8)TxPduId - CANTSYN_NUMBER_OF_SYNC_MASTERS];
        P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSyn_OfsTimeMasterDomainPtr =
            &CanTSyn_TimeMasterConfig[TxPduId];
        /* If the time is not expired and the result is E_Ok continue with processing
           the confirmation, else reload the debounce and reset the relevant data */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00042,1 */
        if((result == E_OK) && (CanTSyn_OfsMasterPtr->ConfirmationTimeout != 0U))
        {
#endif /* CANTSYN_RELIABLE_TXCONF == STD_ON */
          (void)CanTSyn_ConfirmOfsMsg((uint8)TxPduId - CANTSYN_NUMBER_OF_SYNC_MASTERS);
#if(CANTSYN_RELIABLE_TXCONF == STD_ON)
        }
        else
        {
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00037,1 */
          CanTSyn_TxOffsetReset((uint8)TxPduId - CANTSYN_NUMBER_OF_SYNC_MASTERS);
          if(result == E_OK)
          {
            /* load the Debounce Timeout, if the transmission was successful */
            /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
            CanTSyn_OfsMasterPtr->DebounceTime = CanTSyn_OfsTimeMasterDomainPtr->DebounceTime;
          }
        }
#endif /* CANTSYN_RELIABLE_TXCONF == STD_ON */
      }
      else
#endif /* (CANTSYN_TX_OFFSET_USED == STD_ON) */
      {
#if(CANTSYN_RELIABLE_TXCONF == STD_ON)
        P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_VAR) CanTSyn_MasterPtr =
                                                    &CanTSyn_SyncMaster[TxPduId];
        P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
                CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[TxPduId];
        /* If the time is not expired and the result is E_Ok continue with processing
           the confirmation, else reload the debounce and reset the relevant data */
         /* !LINKSTO CanTSyn.SWS_CanTSyn_00033,1 */
        if((result == E_OK) && (CanTSyn_MasterPtr->ConfirmationTimeout != 0U))
        {
#endif /* CANTSYN_RELIABLE_TXCONF == STD_ON */
          (void)CanTSyn_ConfirmSyncMsg((uint8)TxPduId);
#if(CANTSYN_RELIABLE_TXCONF == STD_ON)
        }
        else
        {
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00027,1 */
          CanTSyn_TxSyncReset((uint8)TxPduId);
          if(result == E_OK)
          {
            /* load the Debounce Timeout, if the transmission was successful */
            /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
            CanTSyn_MasterPtr->DebounceTime = CanTSyn_TimeMasterDomainPtr->DebounceTime;
          }
        }
#endif /* CANTSYN_RELIABLE_TXCONF == STD_ON */
      }
    }
  }
#if(CANTSYN_RELIABLE_TXCONF == STD_OFF)
  DBG_CANTSYN_TXCONFIRMATION_EXIT(TxPduId);
#else
  DBG_CANTSYN_TXCONFIRMATION_EXIT(TxPduId,result);
#endif /* #if(CANTSYN_RELIABLE_TXCONF == STD_OFF) */
#else

  /* No support for Time Master */
  TS_PARAM_UNUSED(TxPduId);
#if(CANTSYN_RELIABLE_TXCONF == STD_ON)
  TS_PARAM_UNUSED(result);
#endif /* #if(CANTSYN_RELIABLE_TXCONF == STD_ON) */
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON) */
}


/* !LINKSTO CanTSyn.SWS_CanTSyn_00102,1 */
FUNC(void, CANTSYN_CODE) CanTSyn_MainFunction(void)
{

  uint8 dummyPartition = CANTSYN_NUMBER_OF_PARTITIONS - 1U;

  DBG_CANTSYN_MAINFUNCTION_ENTRY();
#if((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON))
  CanTSyn_MainFunction_Tx(dummyPartition);
#endif /* ((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON)) */
#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
  CanTSyn_MainFunction_Rx(dummyPartition);
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON)) */

  DBG_CANTSYN_MAINFUNCTION_EXIT();
}








#if((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON))
FUNC(void, CANTSYN_CODE) CanTSyn_MainFunction_Tx(uint8 partitionIdx)
{
#if(CANTSYN_IS_TX_PDUINDEX_USED == STD_ON)
  uint8 PduIndex;
#endif /* (CANTSYN_IS_TX_PDUINDEX_USED == STD_ON) */
#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
  uint8 timeDomainIdx;
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
  DBG_CANTSYN_MAINFUNCTION_TX_ENTRY(partitionIdx);

  /* check if the module was initialized */
  if(TRUE == CanTSyn_Initialized)
  {
#if(CANTSYN_TX_SYNC_USED == STD_ON)
#if(CANTSYN_MULTICORE_ENABLED == STD_OFF)
/* !LINKSTO CanTSyn.EB.Multicore.MainFunctions_NormalHandling_Multicore_OFF,1 */
      TS_PARAM_UNUSED(partitionIdx);
      for(PduIndex = 0U;
          /* Deviation TASKING-1 */
          PduIndex < CANTSYN_NUMBER_OF_SYNC_MASTERS;
          PduIndex++)
#else /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
/* !LINKSTO CanTSyn.EB.Multicore.CanTSynGlobalTimeMaster_MainFunctions_NormalHandling_Multicore_ON,1 */
/* !LINKSTO CanTSyn.EB.Multicore.CanTSynGlobalTimeMaster_MainFunctions_MulticoreHandling_Multicore_ON,1 */
      for(timeDomainIdx = 0U;
          /* Deviation TASKING-1 */
          timeDomainIdx < CanTSyn_PartitionTimeDomainsList[partitionIdx].numberOfTimeDomains;
          timeDomainIdx++)
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_OFF) */
      {

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
        uint16 pduIndexTypeDirection = CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx];
        uint8 typeDirection = CANTSYN_GET_TYPE_DIRECTION(CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx]);
        /* only process Sync TX messages */
        if(typeDirection == CANTSYN_SYNC_TX_PDUINDEX)
        {
          /* get pduIndex */
          PduIndex = pduIndexTypeDirection >> 8U;
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */

          /* Send frame only if TxMode is TX_ON */
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00044,1 */
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00043,1 */
          if(CANTSYN_TX_ON == CanTSyn_TxMode[CanTSyn_TimeMasterConfig[PduIndex].CtrlIndex])
          {
            /* SYNC Pdu */
            CanTSyn_TxProcessSyncMsg(PduIndex);
          }

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
        }
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */

      }
#endif /* CANTSYN_TX_SYNC_USED == STD_ON */


#if(CANTSYN_TX_OFFSET_USED == STD_ON)
#if(CANTSYN_MULTICORE_ENABLED == STD_OFF)
#if(CANTSYN_TX_SYNC_USED == STD_OFF)
      TS_PARAM_UNUSED(partitionIdx);
#endif /* (CANTSYN_TX_SYNC_USED == STD_OFF) */
      for(PduIndex = 0U;
          /* Deviation TASKING-1 */
          PduIndex < CANTSYN_NUMBER_OF_OFFSET_MASTERS;
          PduIndex++)
#else /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
      for(timeDomainIdx = 0U;
          /* Deviation TASKING-1 */
          timeDomainIdx < CanTSyn_PartitionTimeDomainsList[partitionIdx].numberOfTimeDomains;
          timeDomainIdx++)
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_OFF) */
      {

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
        uint16 pduIndexTypeDirection = CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx];
        uint8 typeDirection = CANTSYN_GET_TYPE_DIRECTION(CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx]);
        /* only process Ofs TX messages */
        if(typeDirection == CANTSYN_OFS_TX_PDUINDEX)
        {
          /* get pduIndex */
          PduIndex = pduIndexTypeDirection >> 8U;

          PduIndex = PduIndex - CANTSYN_NUMBER_OF_SYNC_MASTERS;
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */

          /* Send frame only if TxMode is TX_ON */
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00044,1 */
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00043,1 */
          if(CANTSYN_TX_ON == CanTSyn_TxMode[CanTSyn_TimeMasterConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_MASTERS].CtrlIndex])
          {
            /* OFS Pdu */
            CanTSyn_TxProcessOfsMsg(PduIndex);
          }

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
        }
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
      }
#endif /* CANTSYN_TX_OFFSET_USED == STD_ON */
  }

  DBG_CANTSYN_MAINFUNCTION_TX_EXIT(partitionIdx);

}
#endif /* ((CANTSYN_TX_SYNC_USED == STD_ON) || (CANTSYN_TX_OFFSET_USED == STD_ON)) */




#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
FUNC(void, CANTSYN_CODE) CanTSyn_MainFunction_Rx(uint8 partitionIdx)
{

#if(CANTSYN_IS_RX_PDUINDEX_USED == STD_ON)
  uint8 PduIndex = 0U;
#endif /* (CANTSYN_IS_RX_PDUINDEX_USED == STD_ON) */
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
#if (CANTSYN_RX_SYNC_USED == STD_ON)
  boolean decreaseFupOfsset = TRUE;
#endif /* CANTSYN_RX_SYNC_USED == STD_ON) */
  P2VAR(CanTSyn_IcvSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvSlavePtr = NULL_PTR;
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

  DBG_CANTSYN_MAINFUNCTION_RX_ENTRY(partitionIdx);

  /* check if the module was initialized */
  if(TRUE == CanTSyn_Initialized)
  {
#if(CANTSYN_RX_SYNC_USED == STD_ON)
#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
    uint8 timeDomainIdx;
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
#if(CANTSYN_MULTICORE_ENABLED == STD_OFF)
/* !LINKSTO CanTSyn.EB.Multicore.MainFunctions_NormalHandling_Multicore_OFF,1 */
    TS_PARAM_UNUSED(partitionIdx);
    for(PduIndex = 0U;
        /* Deviation TASKING-1 */
        PduIndex < CANTSYN_NUMBER_OF_SYNC_SLAVES;
        PduIndex++)
#else /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
/* !LINKSTO CanTSyn.EB.Multicore.CanTSynGlobalTimeSlave_MainFunctions_NormalHandling_Multicore_ON,1 */
/* !LINKSTO CanTSyn.EB.Multicore.CanTSynGlobalTimeSlave_MainFunctions_MulticoreHandling_Multicore_ON,1 */
    for(timeDomainIdx = 0U;
        /* Deviation TASKING-1 */
        timeDomainIdx < CanTSyn_PartitionTimeDomainsList[partitionIdx].numberOfTimeDomains;
        timeDomainIdx++)
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_OFF) */
    {
      P2VAR(CanTSyn_SyncSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_SyncSlavePtr;

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      boolean syncTimerExpired = FALSE;
#endif

#if (CANTSYN_MULTICORE_ENABLED == STD_ON)
      uint16 pduIndexTypeDirection = CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx];
      uint8 typeDirection = CANTSYN_GET_TYPE_DIRECTION(CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx]);
      /* only process Sync RX messages */
      if(typeDirection == CANTSYN_SYNC_RX_PDUINDEX)
      {
        /* get pduIndex */
        PduIndex = pduIndexTypeDirection >> 8U;
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */

        CanTSyn_SyncSlavePtr = &CanTSyn_SyncSlave[PduIndex];
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
        CanTSyn_IcvSlavePtr = &CanTSyn_IcvSlave[CanTSyn_SyncSlavePtr->IcvIndex];
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

        SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

        /* update Rx debounce time */
        if(CanTSyn_SyncSlavePtr->RxDebounceTime != 0U)
        {
          CanTSyn_SyncSlavePtr->RxDebounceTime--;
        }

        SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

        switch(CanTSyn_SyncSlavePtr->RxStatus)
        {
          case CANTSYN_FUPMSG_RX_WAIT:
          {
            /* Protection needed for RxStatus, because a reception of a FUP message can interrupt
               CanTSyn_MainFunction_Rx and RxStatus will be set to CANTSYN_SYNCMSG_RX_WAIT
               and after that it will be set here to CANTSYN_FUPMSG_RX_WAIT_TIMEOUT
               which causes a new reception of a SYNC message to be ignored.
            */
            SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

            /* Load the Follow Up Offset Timeout */
            CanTSyn_SyncSlavePtr->TimeRxFollowUpOffset = CanTSyn_TimeSlaveConfig[PduIndex].RxFollowUpOffsetTimeout;

            /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeFollowUpTimeout.Awaited.FUP,2 */
            /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_SyncRXWAIT_NoFupReceived,1 */
            /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_SyncRXWAIT-FupRXWAITTIMEOUT,1 */
            /* change RxStatus, FollowUpOffsetTimeout loaded */
            CanTSyn_SyncSlavePtr->RxStatus = CANTSYN_FUPMSG_RX_WAIT_TIMEOUT;

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
            /* process timer for sync frames */
            syncTimerExpired = CanTSyn_ProcessSyncTimeout(CanTSyn_SyncSlavePtr);
#endif

            SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
          }
          break;

          case CANTSYN_FUPMSG_RX_WAIT_TIMEOUT:
          {
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
            if((CanTSyn_TimeSlaveConfig[PduIndex].IcvVerificationType == CANTSYN_ICV_VERIFIED) || (CanTSyn_TimeSlaveConfig[PduIndex].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
            {
              if(CanTSyn_IcvSlavePtr->IcvVerificationState != CANTSYN_ICV_STATE_NOT_REQUESTED)
              {
                /* if IcvVerificationState is not CANTSYN_ICV_STATE_NOT_REQUESTED it means that
                Fup message was already received and Icv verification is in progress */
                decreaseFupOfsset = FALSE;
              }
            }
            if(decreaseFupOfsset == TRUE)
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
            {
              /* Protection needed because a new reception can reset the TimeRxFollowUpOffset
                 before decrementation and when TimeRxFollowUpOffset will be decremented
                 it will cause an undefined behaviour */
              SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

              if(CanTSyn_SyncSlavePtr->TimeRxFollowUpOffset == 0U)
              {
                /* reset due to timeout */
                /* !LINKSTO CanTSyn.SWS_CanTSyn_00063,1 */
                /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_SyncRXWAIT,1 */
                CanTSyn_RxSyncReset(PduIndex);
              }
              else
              {
                /* decrease the time to wait for FUP message */
                CanTSyn_SyncSlavePtr->TimeRxFollowUpOffset--;
              }

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
              /* process timer for sync frames */
              syncTimerExpired = CanTSyn_ProcessSyncTimeout(CanTSyn_SyncSlavePtr);
#endif

              SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
            }
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
            if((CanTSyn_TimeSlaveConfig[PduIndex].IcvVerificationType == CANTSYN_ICV_VERIFIED) || (CanTSyn_TimeSlaveConfig[PduIndex].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
            {
              (void)CanTSyn_CheckIcvVerificationState(CanTSyn_IcvSlavePtr, PduIndex, TRUE);
            }
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

          }
          break;

          default:
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
          {
            SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
            /* process timer for sync frames */
            syncTimerExpired = CanTSyn_ProcessSyncTimeout(CanTSyn_SyncSlavePtr);
            SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
          }
#else
        /* nothing to do */
#endif
          break;
        }

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
        if (TRUE == syncTimerExpired)
        {
          /* !LINKSTO CanTSyn.EB.Diagnostic_CanTSynReceivePairsPeriod_Expire_1_DEM,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_CanTSynReceivePairsPeriod_Expire_1_DET,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_CanTSynReceivePairsPeriod_Expire_3_DEM,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_CanTSynReceivePairsPeriod_Expire_3_DET,1 */
          /* report that a sync frame failed to come in the expected time period */
          CanTSyn_SyncFupDropped(PduIndex, CANTSYN_SID_MAINFUNCTION);
        }
#endif

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
      }
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
    }
#else
    TS_PARAM_UNUSED(partitionIdx);
    /* if all CanTSyn Time Domains have CanTSynGlobalTimeFollowUpTimeout set to zero,
     * RxFollowUpTimeout shall not be handled and CanTSyn shall wait in
     * CANTSYN_FUPMSG_RX_WAIT state, until the awaited FUP arrives
     */
    /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeFollowUpTimeout.Awaited.FUP,2 */
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */



#if(CANTSYN_RX_OFFSET_USED == STD_ON)

#if(CANTSYN_MULTICORE_ENABLED == STD_OFF)
#if(CANTSYN_RX_SYNC_USED == STD_OFF)
    TS_PARAM_UNUSED(partitionIdx);
#endif /* (CANTSYN_RX_SYNC_USED == STD_OFF) */
    for(PduIndex = 0U;
        /* Deviation TASKING-1 */
        PduIndex < CANTSYN_NUMBER_OF_OFFSET_SLAVES;
        PduIndex++)
#else /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
    for(timeDomainIdx = 0U;
        /* Deviation TASKING-1 */
        timeDomainIdx < CanTSyn_PartitionTimeDomainsList[partitionIdx].numberOfTimeDomains;
        timeDomainIdx++)
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_OFF) */
    {
#if(CANTSYN_MULTICORE_ENABLED == STD_OFF)
      P2VAR(CanTSyn_OffsetSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_OffsetSlavePtr = &CanTSyn_OffsetSlave[PduIndex];
#else /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
      P2VAR(CanTSyn_OffsetSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_OffsetSlavePtr;
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_OFF) */

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      boolean ofsTimerExpired = FALSE;
#endif

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
      uint16 pduIndexTypeDirection = CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx];
      uint8 typeDirection = CANTSYN_GET_TYPE_DIRECTION(CanTSyn_PartitionTimeDomainsList[partitionIdx].partitionTimeDomainsList[timeDomainIdx]);
      /* only process Ofs RX messages */
      if(typeDirection == CANTSYN_OFS_RX_PDUINDEX)
      {
        /* get pduIndex */
        PduIndex = pduIndexTypeDirection >> 8U;

        PduIndex = PduIndex - CANTSYN_NUMBER_OF_SYNC_SLAVES;

        CanTSyn_OffsetSlavePtr = &CanTSyn_OffsetSlave[PduIndex];
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
        if((CanTSyn_TimeSlaveConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_VERIFIED) ||
          (CanTSyn_TimeSlaveConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
        {
          CanTSyn_IcvSlavePtr = &CanTSyn_IcvSlave[CanTSyn_OffsetSlavePtr->IcvIndex];
        }
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

        SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

        /* update Rx debounce time */
        if(CanTSyn_OffsetSlavePtr->RxDebounceTime != 0U)
        {
          CanTSyn_OffsetSlavePtr->RxDebounceTime--;
        }

        SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

        switch(CanTSyn_OffsetSlavePtr->RxStatus)
        {
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED)
          case CANTSYN_OFSMSG_RX_WAIT:
          {
            if((CanTSyn_TimeSlaveConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_VERIFIED) ||
            (CanTSyn_TimeSlaveConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
            {
              (void)CanTSyn_CheckIcvVerificationState(CanTSyn_IcvSlavePtr, PduIndex, FALSE);
            }
          }
          break;
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED) */
          case CANTSYN_OFNSMSG_RX_WAIT:
          {
            /* Protection needed, because a reception of a OFNS message can interrupt
               CanTSyn_MainFunction_Rx and RxStatus will be set to CANTSYN_OFSMSG_RX_WAIT
               and after that it will be set here to CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT
               which causes a new reception of a OFS message to be ignored */
            SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

            /* Load the Follow Up Offset Timeout */
            CanTSyn_OffsetSlavePtr->TimeRxFollowUpOffset = CanTSyn_TimeSlaveConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_SLAVES].RxFollowUpOffsetTimeout;

            /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeFollowUpTimeout.Awaited.OFNS,2 */
            /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfsRXWAIT-OfnsRXWAITTIMEOUT,1 */
            /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_OfsRXWAIT_NoOfnsReceived,1 */
            /* change RxStatus, FollowUpOffsetTimeout loaded */
            CanTSyn_OffsetSlavePtr->RxStatus = CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT;

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
          /* process timer for ofs frames */
          ofsTimerExpired = CanTSyn_ProcessOfsTimeout(CanTSyn_OffsetSlavePtr);
#endif

            SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
          }
          break;

          case CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT:
          {
            /* Protection needed because a new reception can reset the TimeRxFollowUpOffset
               before decrementation and when TimeRxFollowUpOffset will be decremented
               it will cause an undefined behaviour */
            SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

            if(CanTSyn_OffsetSlavePtr->TimeRxFollowUpOffset == 0U)
            {
              /* reset due to timeout */
              /* !LINKSTO CanTSyn.SWS_CanTSyn_00071,1 */
              /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_OfsRXWAIT,1 */
              CanTSyn_RxOffsetReset(PduIndex);
            }
            else
            {
              /* decrease the time to wait for OFNS message */
              CanTSyn_OffsetSlavePtr->TimeRxFollowUpOffset--;
            }

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
            /* process timer for ofs frames */
            ofsTimerExpired = CanTSyn_ProcessOfsTimeout(CanTSyn_OffsetSlavePtr);
#endif

            SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
          }
          break;

          default:
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
          {
            SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
            /* process timer for ofs frames */
            ofsTimerExpired = CanTSyn_ProcessOfsTimeout(CanTSyn_OffsetSlavePtr);
            SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
          }
#else
          /* nothing to do */
#endif
          break;
        }

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
        if (TRUE == ofsTimerExpired)
        {
          /* !LINKSTO CanTSyn.EB.Diagnostic_CanTSynReceivePairsPeriod_Expire_2_DEM,1 */
          /* !LINKSTO CanTSyn.EB.Diagnostic_CanTSynReceivePairsPeriod_Expire_2_DET,1 */
          /* report that a ofs frame failed to come in the expected time period */
          CanTSyn_OfsOfnsDropped(PduIndex, CANTSYN_SID_MAINFUNCTION);
        }
#endif

#if(CANTSYN_MULTICORE_ENABLED == STD_ON)
      }
#endif /* (CANTSYN_MULTICORE_ENABLED == STD_ON) */
    }
#else
    /* if all CanTSyn Time Domains have CanTSynGlobalTimeFollowUpTimeout set to zero,
     * RxFollowUpTimeout shall not be handled and CanTSyn shall wait in
     * CANTSYN_OFNSMSG_RX_WAIT state, until the awaited OFNS arrives
     */
    /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeFollowUpTimeout.Awaited.OFNS,2 */
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
  }

  DBG_CANTSYN_MAINFUNCTION_RX_EXIT(partitionIdx);
}
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON)) */


#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_CheckIcvVerificationState
(
  P2VAR(CanTSyn_IcvSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvSlavePtr,
  uint8 PduIndex,
  boolean isFUP
)
{
  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  if(CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_PENDING)
  {
    /* waiting for a verification indication from Csm */
    /* decrease the verification timeout */
    CanTSyn_IcvSlavePtr->IcvVerificationTimeout--;
    if(CanTSyn_IcvSlavePtr->IcvVerificationTimeout == 0U)
    {
      /* timeout expired; verification is considered to be failed; update state */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00200.StopICVVerification,1 */
      /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Pending_Failed_TimeoutExpired,1 */
      CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
    }
  }

  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  /* check if Icv verification is ongoing */
  if((CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_FAILED) ||
    (CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_VERIFIED) ||
    (CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_RECOV_ERROR))
  {
#if (CANTSYN_RX_SYNC_USED == STD_ON)
    if(isFUP == TRUE)
    {
      CanTSyn_ProcessRxFupFrame(&CanTSyn_IcvData[CanTSyn_TimeSlaveConfig[PduIndex].IcvDataStartIndex + CANTSYN_SYNC_PAYLOAD_LENGTH],
                                PduIndex);
    }
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */
#if((CANTSYN_RX_OFFSET_USED == STD_ON) && (CANTSYN_RX_USE_EXTENDED_MSG == STD_ON))
    if(isFUP == FALSE) /* ExtOFS frame */
    {

      CanTSyn_ProcessExtRxOfsFrame(CanTSyn_IcvSlavePtr->T5VLT,
                                   &CanTSyn_IcvData[CanTSyn_TimeSlaveConfig[PduIndex + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvDataStartIndex],
                                   PduIndex);
    }
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) && (CANTSYN_RX_USE_EXTENDED_MSG == STD_ON) */
  }
}
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

#if(CANTSYN_TX_SYNC_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxSyncFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  uint8 CanTSynPduIdx
)
{
  uint32 T0Seconds = CanTSyn_SyncMaster[CanTSynPduIdx].SyncTimeT0.seconds;
  uint8 seqCounter = CanTSyn_SyncMaster[CanTSynPduIdx].SeqCount;
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, AUTOMATIC) MasterConfigPtr = &CanTSyn_TimeMasterConfig[CanTSynPduIdx];

#if(CANTSYN_TX_CRC_USED == STD_ON)
  CanTSyn_DataIDListType DataId;
#endif /* (CANTSYN_TX_CRC_USED == STD_ON) */

  TxDataPtr[CANTSYN_B2_MSG_DOMAIN] = CANTSYN_GET_B2_DOMAIN_SC(MasterConfigPtr->TimeDomainId, seqCounter);
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00012,1 */ /* User Byte 0 */
  TxDataPtr[CANTSYN_B3_MSG_RESERVED] = CanTSyn_SyncMaster[CanTSynPduIdx].UserByte0;

  /* assemble Bytes 4-7 in Big Endian format */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00015.NormalMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00017.NormalMessage,1 */
  TxDataPtr[CANTSYN_B4_MSG] = ((uint8)(T0Seconds >> CANTSYN_GET_B3));
  TxDataPtr[CANTSYN_B5_MSG] = ((uint8)(T0Seconds >> CANTSYN_GET_B2));
  TxDataPtr[CANTSYN_B6_MSG] = ((uint8)(T0Seconds >> CANTSYN_GET_B1));
  TxDataPtr[CANTSYN_B7_MSG] = (uint8)T0Seconds;

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00015.ExtendedMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00017.ExtendedMessage,1 */
  if(MasterConfigPtr->IsExtendedMessage)
  {
    TS_MemBZero(&TxDataPtr[CANTSYN_B8_RESERVED], 8U);
  }
#endif

#if(CANTSYN_TX_CRC_USED == STD_ON)
  /* check if CRC supported */
  if(MasterConfigPtr->IsTxCrcSecuredUsed == CANTSYN_CRC_SUPPORTED)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00017.NormalMessage,1 */ /* Type with CRC support */
    TxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_SYNC_WITH_CRC;

    /* add the DataID Value based on the current sequence counter */ /* !LINKSTO CanTSyn.SWS_CanTSyn_00054,1 */
    DataId = MasterConfigPtr->SyncOfsDataIdListPtr[seqCounter];

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00017.ExtendedMessage,1 */
    if(MasterConfigPtr->IsExtendedMessage)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.ExtendedMessage,1 */
      TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&TxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_EXT_LENGTH);
    }
    else
#endif
    {
      /* get the CRC value */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00050,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.NormalMessage,1 */
      TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&TxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_LENGTH);
    }

  }
  else
#endif /* CANTSYN_TX_CRC_USED == STD_ON */
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00015.NormalMessage,1 */
    TxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_SYNC_WITHOUT_CRC; /* Type */ /* No CRC support */
    TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_SyncMaster[CanTSynPduIdx].UserByte1; /* User Byte 1 */
  }

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  if(MasterConfigPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
  {
#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_PRECONDITION_ASSERT((CanTSyn_TimeMasterConfig[CanTSynPduIdx].IcvDataStartIndex + CANTSYN_SYNC_PAYLOAD_LENGTH) < CANTSYN_ICV_DATA_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */
    /* load SYNC frame for Icv generation */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00161.Payload,1 */
    TS_MemCpy(&CanTSyn_IcvData[CanTSyn_TimeMasterConfig[CanTSynPduIdx].IcvDataStartIndex], TxDataPtr, CANTSYN_SYNC_PAYLOAD_LENGTH);
  }
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxFupFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  uint8 CanTSynPduIdx,
  uint8 CanTSynOvsBit
)
{
  P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
            CanTSyn_SyncMasterPtr = &CanTSyn_SyncMaster[CanTSynPduIdx];
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_DATA)
            CanTSyn_ConfigPtr = &CanTSyn_TimeMasterConfig[CanTSynPduIdx];
  uint32 T0Nanoseconds = CanTSyn_SyncMasterPtr->FupTimeT4.nanoseconds;
  uint8 FupSeqCount = CANTSYN_SC_MAXLIMIT;


#if(CANTSYN_TX_CRC_USED == STD_ON)
  CanTSyn_DataIDListType DataId;
#endif /* (CANTSYN_TX_CRC_USED == STD_ON) */

  /* Sequence Counter increased at SYNC */
  /* Use the same */
  FupSeqCount = CANTSYN_GET_SEQ_COUNTER(CanTSyn_SyncMasterPtr->SeqCount);

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00049_OFNS_SCUnchanged,1 */
  TxDataPtr[CANTSYN_B2_MSG_DOMAIN] = CANTSYN_GET_B2_DOMAIN_SC(CanTSyn_ConfigPtr->TimeDomainId, FupSeqCount);
  TxDataPtr[CANTSYN_B3_MSG_GATEWAY] = CANTSYN_B3_SGW_OVS(CanTSynPduIdx, CanTSynOvsBit);

  /* assemble Bytes 4-7 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00016.NormalMessage,1 */
  TxDataPtr[CANTSYN_B4_MSG] = (((uint8)(T0Nanoseconds >> CANTSYN_GET_B3)));
  TxDataPtr[CANTSYN_B5_MSG] = ((uint8)(T0Nanoseconds >> CANTSYN_GET_B2));
  TxDataPtr[CANTSYN_B6_MSG] = ((uint8)(T0Nanoseconds >> CANTSYN_GET_B1));
  TxDataPtr[CANTSYN_B7_MSG] = (uint8)T0Nanoseconds;

#if(CANTSYN_TX_CRC_USED == STD_ON)
  /* check if CRC supported */
  if(CanTSyn_ConfigPtr->IsTxCrcSecuredUsed == CANTSYN_CRC_SUPPORTED)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00018.NormalMessage,1 */ /* Type with CRC support */
    TxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_FUP_WITH_CRC;

    /* get DataId value based on the current sequence counter */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00054,1 */
    DataId = CanTSyn_TimeMasterConfig[CanTSynPduIdx].FupOfnsDataIdListPtr[FupSeqCount];

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00017.ExtendedMessage,1 */
    if(CanTSyn_ConfigPtr->IsExtendedMessage)
    {
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
      if(CanTSyn_ConfigPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00055.CRC.AuthenticatedExtendedMessage,1 */
        TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&TxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_LENGTH);
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00159,1 */
        TxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_FUP_WITH_CRC_ICV_AUTH;
      }
      else
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.ExtendedMessage,1 */
        TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&TxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_EXT_LENGTH);
      }
    }
    else
#endif
    {
      /* get the CRC value */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00050,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.NormalMessage,1 */
      TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&TxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_LENGTH);
    }

  }
  else
#endif /* CANTSYN_TX_CRC_USED == STD_ON */
  {
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
    if(CanTSyn_ConfigPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00159,1 */
      TxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH; /* Type */ /* No CRC support */ /* ICV secured */
    }
    else
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00016.NormalMessage,1 */
      TxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_FUP_WITHOUT_CRC; /* Type */ /* No CRC support */ /* No ICV */
    }
    TxDataPtr[CANTSYN_B1_MSG] = CanTSyn_SyncMasterPtr->UserByte2; /* User Byte 2 */
  }

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00016.ExtendedMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00018.ExtendedMessage,1 */
  if(CanTSyn_ConfigPtr->IsExtendedMessage)
  {
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_ConfigPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      CanTSyn_GenerateIcv(TxDataPtr, CanTSynPduIdx, CanTSyn_SyncMasterPtr->IcvIndex, CANTSYN_B8_FVL, CANTSYN_B9_ICVL, CANTSYN_B10_FV);
    }
    else
    {
      TS_MemBZero(&TxDataPtr[CANTSYN_B8_RESERVED], 8U);
    }
#else
    TS_MemBZero(&TxDataPtr[CANTSYN_B8_RESERVED], 8U);
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  }
#endif /* if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON) */


}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxSyncReset
(
  uint8 ConfirmationHandleId
)
{
  P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
          CanTSyn_MasterPtr = &CanTSyn_SyncMaster[ConfirmationHandleId];

  /* Protection needed because CanTSyn_TxSyncReset can be interrupted
     by CanTSyn_TxConfirmation where SyncTimeT0 will be read.
     If protection is not used, garbage data will be read for SyncTimeT0 variable
     Protection needed because CanTSyn_TxSyncReset can be interrupted
     by CanTSyn_TxConfirmation which also writes FupTimeT4 variable */
  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  /* Clear the Sync Time seconds portion */
  CanTSyn_MasterPtr->SyncTimeT0.seconds = 0U;

  /* Clear the Sync Time nanoseconds portion */
  CanTSyn_MasterPtr->SyncTimeT0.nanoseconds = 0U;

  /* Clear TxConfirmation Timeout */
  CanTSyn_MasterPtr->ConfirmationTimeout = 0U;

  /* Clear seconds portion of T4 needed for FUP message */
  CanTSyn_MasterPtr->FupTimeT4.seconds = 0U;

  /* Clear nanoseconds portion of T4 needed for FUP message */
  CanTSyn_MasterPtr->FupTimeT4.nanoseconds = 0U;

  /* Clear the debounceCounter */
  CanTSyn_MasterPtr->DebounceTime = 0U;

  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_Init,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00025,1 */
  /* each time synchronization Sync-Fup sequence starts with a SYNC message */
  CanTSyn_MasterPtr->TxStatus = CANTSYN_SYNCMSG_SEND_WAIT;

  /* clear User Data */
  CanTSyn_MasterPtr->UserByte0 = 0U;
  CanTSyn_MasterPtr->UserByte1 = 0U;
  CanTSyn_MasterPtr->UserByte2 = 0U;

  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

}
#endif /* CANTSYN_TX_SYNC_USED == STD_ON */


#if(CANTSYN_TX_OFFSET_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxOffsetReset
(
  uint8 ConfirmationHandleId
)
{
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
         CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[ConfirmationHandleId];

  /* Clear TxConfirmation Timeout */
  CanTSyn_OffsetMasterPtr->ConfirmationTimeout = 0U;

  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_Init,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00035,1 */
  /* each time synchronization Ofs-Ofns sequence starts with an OFS message */
  CanTSyn_OffsetMasterPtr->TxStatus = CANTSYN_OFSMSG_SEND_WAIT;

  /* Clear the debounceCounter */
  CanTSyn_OffsetMasterPtr->DebounceTime = 0U;

  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxOfsFrame
(
  P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSynTimeStampPtr,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) CanTSynTxDataPtr,
  uint8 CanTSynPduIdx
)
{
  uint8 seqCounter = CanTSyn_OffsetMaster[CanTSynPduIdx].SeqCount;
  uint32 seconds = CanTSynTimeStampPtr->seconds;
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS];

#if(CANTSYN_TX_CRC_USED == STD_ON)
  CanTSyn_DataIDListType DataId;
#endif /* (CANTSYN_TX_CRC_USED == STD_ON) */

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeMasterDomainPtr->IsExtendedMessage)
  {
    uint32 nanoseconds = CanTSyn_OffsetMaster[CanTSynPduIdx].OfsTimeNSec;

    CanTSynTxDataPtr[CANTSYN_B2_MSG_DOMAIN] = CANTSYN_GET_B2_DOMAIN_SC(CanTSyn_TimeMasterDomainPtr->TimeDomainId, seqCounter);
    CanTSynTxDataPtr[CANTSYN_B3_MSG] = CANTSYN_B3_SGW(CanTSynPduIdx); /* reserved (Bit 7 to Bit 1), default: 0
                                                          * SGW (Bit 0)
                                                          */

    CanTSynTxDataPtr[CANTSYN_B4_MSG] = CanTSyn_OffsetMaster[CanTSynPduIdx].UserByte0; /* User Byte 0, default: 0 */
    CanTSynTxDataPtr[CANTSYN_B5_MSG] = CanTSyn_OffsetMaster[CanTSynPduIdx].UserByte1; /* User Byte 1, default: 0 */

    CanTSynTxDataPtr[CANTSYN_B6_MSG_RESERVED] = 0x00U; /* reserved, default: 0 */
    CanTSynTxDataPtr[CANTSYN_B7_MSG_RESERVED] = 0x00U; /* reserved, default: 0 */

    /* Byte 8-11: OfsTimeSec = 32 Bit offset time value in seconds */
    CanTSynTxDataPtr[CANTSYN_B8_MSG] = (((uint8)(seconds >> CANTSYN_GET_B3)));
    CanTSynTxDataPtr[CANTSYN_B9_MSG] = ((uint8)(seconds >> CANTSYN_GET_B2));
    CanTSynTxDataPtr[CANTSYN_B10_MSG] = ((uint8)(seconds >> CANTSYN_GET_B1));
    CanTSynTxDataPtr[CANTSYN_B11_MSG] = (uint8)seconds;

    /* Byte 12-15: OfsTimeNSec = 32 Bit offset time value in nanoseconds */
    CanTSynTxDataPtr[CANTSYN_B12_MSG] = (((uint8)(nanoseconds >> CANTSYN_GET_B3)));
    CanTSynTxDataPtr[CANTSYN_B13_MSG] = ((uint8)(nanoseconds >> CANTSYN_GET_B2));
    CanTSynTxDataPtr[CANTSYN_B14_MSG] = ((uint8)(nanoseconds >> CANTSYN_GET_B1));
    CanTSynTxDataPtr[CANTSYN_B15_MSG] = (uint8)nanoseconds;

#if(CANTSYN_TX_CRC_USED == STD_ON)
    /* check if CRC supported */
    if(CanTSyn_TimeMasterDomainPtr->IsTxCrcSecuredUsed == CANTSYN_CRC_SUPPORTED)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00112,1 */
      DataId = CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS].SyncOfsDataIdListPtr[seqCounter];

      /* !LINKSTO CanTSyn.SWS_CanTSyn_00128,1 */ /* Type with CRC support */
      CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFS_EXT_MSG_WITH_CRC;
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
      if(CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
      {
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00160,1 */
        CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH;
      }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
      /*  CanTSynTxDataPtr[CANTSYN_B1_MSG] calculated last, CRC calculation necessary */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.ExtendedMessage,1 */
      CanTSynTxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&CanTSynTxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_EXT_LENGTH);
    }
    else
#endif /* CANTSYN_TX_CRC_USED == STD_ON */
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00111,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00126,1 */
      CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFS_EXT_MSG_WITHOUT_CRC; /* Type */ /* No CRC support */
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
      if(CanTSyn_TimeMasterConfig[CanTSynPduIdx + CANTSYN_NUMBER_OF_SYNC_MASTERS].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
      {
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00160,1 */
        CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH;
      }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
      CanTSynTxDataPtr[CANTSYN_B1_MSG] = CanTSyn_OffsetMaster[CanTSynPduIdx].UserByte2; /* User Byte 2, default: 0 */
    }
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_TimeMasterConfig[CanTSynPduIdx + CANTSYN_NUMBER_OF_SYNC_MASTERS].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      /* compute and add ICV to OFS frame */
      CanTSyn_GenerateIcv(CanTSynTxDataPtr,
                          CanTSynPduIdx + CANTSYN_NUMBER_OF_SYNC_MASTERS,
                          CanTSyn_OffsetMaster[CanTSynPduIdx].IcvIndex,
                          CANTSYN_B16_FVL,
                          CANTSYN_B17_ICVL,
                          CANTSYN_B18_FV);
    }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  }
  else
#endif /* CANTSYN_TX_USE_EXTENDED_MSG == STD_ON */
  {
    CanTSynTxDataPtr[CANTSYN_B2_MSG_DOMAIN] = CANTSYN_GET_B2_DOMAIN_SC(CanTSyn_TimeMasterDomainPtr->TimeDomainId, seqCounter);
    CanTSynTxDataPtr[CANTSYN_B3_MSG_RESERVED] = CanTSyn_OffsetMaster[CanTSynPduIdx].UserByte0; /* User Byte 0, default: 0 */

    /* assemble Bytes 4-7 in Big Endian format */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
    CanTSynTxDataPtr[CANTSYN_B4_MSG] = (((uint8)(seconds >> CANTSYN_GET_B3)));
    CanTSynTxDataPtr[CANTSYN_B5_MSG] = ((uint8)(seconds >> CANTSYN_GET_B2));
    CanTSynTxDataPtr[CANTSYN_B6_MSG] = ((uint8)(seconds >> CANTSYN_GET_B1));
    CanTSynTxDataPtr[CANTSYN_B7_MSG] = (uint8)seconds;

#if(CANTSYN_TX_CRC_USED == STD_ON)
    /* check if CRC supported */
    if(CanTSyn_TimeMasterDomainPtr->IsTxCrcSecuredUsed == CANTSYN_CRC_SUPPORTED)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00128,1 */ /* Type with CRC support */
      CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFS_WITH_CRC;

      /* get DataId value based on the current sequence counter */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00054,1 */
      DataId = CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS].SyncOfsDataIdListPtr[seqCounter];

      /* get the CRC value */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00050,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.NormalMessage,1 */
      CanTSynTxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&CanTSynTxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_LENGTH);
    }
    else
#endif /* CANTSYN_TX_CRC_USED == STD_ON */
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00126,1 */
      CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFS_WITHOUT_CRC; /* Type */ /* No CRC support */
      CanTSynTxDataPtr[CANTSYN_B1_MSG] = CanTSyn_OffsetMaster[CanTSynPduIdx].UserByte1; /* User Byte 1, default: 0 */
    }
  }

}

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_FillTxOfnsFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) CanTSynTxDataPtr,
  uint8 CanTSynPduIdx
)
{
  uint8 seqCounter = CANTSYN_SC_MAXLIMIT;
  uint32 nanoseconds = CanTSyn_OffsetMaster[CanTSynPduIdx].OfsTimeNSec;

#if(CANTSYN_TX_CRC_USED == STD_ON)
  CanTSyn_DataIDListType DataId;
#endif /* (CANTSYN_TX_CRC_USED == STD_ON) */

  /* Sequence Counter increased at OFS */
  /* Use the same */
  seqCounter = CANTSYN_GET_SEQ_COUNTER(CanTSyn_OffsetMaster[CanTSynPduIdx].SeqCount);

  CanTSynTxDataPtr[CANTSYN_B2_MSG_DOMAIN] = CANTSYN_GET_B2_DOMAIN_SC(CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS].TimeDomainId, seqCounter);
  CanTSynTxDataPtr[CANTSYN_B3_MSG_RESERVED] = CANTSYN_B3_SGW(CanTSynPduIdx); /* reserved (Bit 7 to Bit 1), default: 0
                                                                              * SGW (Bit 0)
                                                                              */

  /* assemble Bytes 4-7 in Big Endian format */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  CanTSynTxDataPtr[CANTSYN_B4_MSG] = (((uint8)(nanoseconds >> CANTSYN_GET_B3)));
  CanTSynTxDataPtr[CANTSYN_B5_MSG] = ((uint8)(nanoseconds >> CANTSYN_GET_B2));
  CanTSynTxDataPtr[CANTSYN_B6_MSG] = ((uint8)(nanoseconds >> CANTSYN_GET_B1));
  CanTSynTxDataPtr[CANTSYN_B7_MSG] = (uint8)nanoseconds;

#if(CANTSYN_TX_CRC_USED == STD_ON)
  /* check if CRC supported */
  if(CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS].IsTxCrcSecuredUsed == CANTSYN_CRC_SUPPORTED)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00129,1 */ /* Type with CRC support */
    CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFNS_WITH_CRC;

    /* get DataId value based on the current sequence counter */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00054,1 */
    DataId = CanTSyn_TimeMasterConfig[CanTSynPduIdx+CANTSYN_NUMBER_OF_SYNC_MASTERS].FupOfnsDataIdListPtr[seqCounter];

    /* get the CRC value */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00050,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00085.CRC.NormalMessage,1 */
    CanTSynTxDataPtr[CANTSYN_B1_MSG] = CanTSyn_CalculateCRC(&CanTSynTxDataPtr[CANTSYN_B2_MSG_DOMAIN], DataId, CANTSYN_CRC_LENGTH);
  }
  else
#endif /* CANTSYN_TX_CRC_USED == STD_ON */
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00127,1 */
    CanTSynTxDataPtr[CANTSYN_B0_MSG_TYPE] = CANTSYN_OFNS_WITHOUT_CRC; /* Type */ /* No CRC support */
    CanTSynTxDataPtr[CANTSYN_B1_MSG] = CanTSyn_OffsetMaster[CanTSynPduIdx].UserByte2; /* User Byte 2, default: 0 */
  }

}
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_TransmitOfs
(
  P2VAR(uint8 ,AUTOMATIC, CANTSYN_APPL_DATA) SduData,
  uint8 CanTSynPduIndex,
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  uint8 sduDataLength,
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
  boolean CanTSynIsImmediateOFSTransmission,
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)*/
  uint8 CanTSynTxStatus
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  PduInfoType CanIfTxInfo;
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[CanTSynPduIndex + CANTSYN_NUMBER_OF_SYNC_MASTERS];
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[CanTSynPduIndex];
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[CanTSyn_OffsetMasterPtr->IcvIndex];
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeMasterDomainPtr->IsExtendedMessage)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVNotSupported,1 */
    CanIfTxInfo.SduLength = CANTSYN_EXTENDED_MSG_SIZE;
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVSupported,1 */
      CanIfTxInfo.SduLength = sduDataLength;
    }
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  }
  else
#endif /* (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON) */
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.NormalMessage,1 */
    /* size of the message is 8 Bytes */
    CanIfTxInfo.SduLength = CANTSYN_MSG_SIZE;
  }

  CanIfTxInfo.SduDataPtr = SduData;

  if(CanTSynTxStatus == CANTSYN_OFSMSG_SEND_WAIT)
  {
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfsSENDWAIT-OfsWAITTXCONF,1 */
    /* wait for the OFS Confirmation */
    CanTSyn_OffsetMasterPtr->TxStatus = CANTSYN_OFSMSG_WAIT_TXCONF;
  }
#if(CANTSYN_OFNS_FRAME_USED == STD_ON)
  else
  {
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfnsSENDWAIT-OfnsWAITTXCONF,1 */
    /* wait for the OFNS Confirmation */
    CanTSyn_OffsetMasterPtr->TxStatus = CANTSYN_OFNSMSG_WAIT_TXCONF;
  }
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

  /* load the Confirmation Timeout */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00042,1 */
  CanTSyn_OffsetMasterPtr->ConfirmationTimeout = CanTSyn_TimeMasterDomainPtr->ConfirmationTimeout;

#if(CANTSYN_OFNS_FRAME_USED == STD_ON)
  /* OFNS message */
  if(CanTSynTxStatus == CANTSYN_OFNSMSG_SEND_WAIT)
  {
    RetVal = CanIf_Transmit(CanTSyn_TimeMasterDomainPtr->TxPduId, &CanIfTxInfo);
  }
  else /* OFS message */
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
  {
    /* handle retry mechanism only for OFS messages */
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
    /* Transmit SYNC Message */
    /* !LINKSTO CanTSyn.EB.CanIf_Transmit_E_NOT_OK,2 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00136,1 */
    RetVal = CanIf_Transmit(CanTSyn_TimeMasterDomainPtr->TxPduId, &CanIfTxInfo);
    if((E_OK == RetVal) || (CanTSyn_OffsetMasterPtr->OfsTransRetriesCounter >= (uint8)CANTSYN_MAX_NUMBER_OF_TRANSMIT_RETRIES))
#else
    (void)CanIf_Transmit(CanTSyn_TimeMasterDomainPtr->TxPduId, &CanIfTxInfo);
    RetVal =  E_OK;
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)*/
    {
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
        if(FALSE != CanTSynIsImmediateOFSTransmission)
        {
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00119,1 */
          CanTSyn_OffsetMasterPtr->CyclicMsgResumeTime = CanTSyn_TimeMasterDomainPtr->CyclicMsgResumeTime;
        }
        else
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)*/
        {
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00038,1 */
          CanTSyn_OffsetMasterPtr->TimeTxPeriod = CanTSyn_TimeMasterDomainPtr->TxPeriodTimeout;
        }
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
      /*Reset tramsmit retries counter */
      CanTSyn_OffsetMasterPtr->OfsTransRetriesCounter = 0U;
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)*/
    }
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
    else
    {
      /* !LINKSTO CanTSyn.EB.CanIf_Transmit_E_NOT_OK,2 */
      CanTSyn_OffsetMasterPtr->OfsTransRetriesCounter++;
    }
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)*/

  }

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  if(CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
  {
    /* reset the ICV generation state after a message transmission */
    /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Received_NotRequested,1 */
    CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_NOT_REQUESTED;
  }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

  return RetVal;
}

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SendOfsMessage
(
  uint8 CanTSynPduIndex,
  uint8 CanTSynTxStatus,
  boolean CanTSynIsImmediateOFSTransmission
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  boolean MessageAccepted = FALSE;
  StbM_TimeStampType StbMTimeStamp;
  StbM_UserDataType UserData;

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  uint8 SduData[CANTSYN_SECURED_MSG_LEN] = {0};
#else
  uint8 SduData[CANTSYN_TX_MAX_MSG_LEN] = {0};
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[CanTSynPduIndex + CANTSYN_NUMBER_OF_SYNC_MASTERS];
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[CanTSynPduIndex];
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  boolean skipMessageFill = FALSE;
  uint8 sduDataLength = 0;
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[CanTSyn_OffsetMasterPtr->IcvIndex];
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
  /* assemble the message */
  if(CANTSYN_OFNSMSG_SEND_WAIT == CanTSynTxStatus)
  {
    /* fill the OFNS message */
    CanTSyn_FillTxOfnsFrame(&SduData[0], CanTSynPduIndex);

    MessageAccepted = TRUE;
  }
  else
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
  {
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      /* if ICV generation is ongoing don't fill the frame again */
      if(CanTSyn_IcvMasterPtr->IcvGenerationState != CANTSYN_ICV_STATE_NOT_REQUESTED)
      {
        skipMessageFill = TRUE;
      }
    }
    if(skipMessageFill == FALSE)
    {
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00046,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00056,1 */
      /* get the the second portion and nanosecond of offset time base */
      /* !LINKSTO CanTSyn.EB.StbM_GetOffset_E_NOT_OK,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
      if(E_OK == StbM_GetOffset(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId, &StbMTimeStamp, &UserData))
      {
        /* save the nanosecond portion for the OFNS message */
        CanTSyn_OffsetMasterPtr->OfsTimeNSec = StbMTimeStamp.nanoseconds;

        /* check the Time Base Status for offset frames */
        if((StbMTimeStamp.timeBaseStatus & CANTSYN_SYNC_TO_GATEWAY_MASK) != 0U)
        {
          CanTSyn_OffsetMasterPtr->OfsSGWBit = CANTSYN_SYNCTOSUBDOMAIN;
        }
        else
        {
          CanTSyn_OffsetMasterPtr->OfsSGWBit = CANTSYN_SYNCTOGTM;
        }

        /* save the user Data */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00011,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00013,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00014,1 */
        CanTSyn_OffsetMasterPtr->UserByte0 = CANTSYN_GET_USERBYTE0(UserData);
        CanTSyn_OffsetMasterPtr->UserByte1 = CANTSYN_GET_USERBYTE1(UserData);
        CanTSyn_OffsetMasterPtr->UserByte2 = CANTSYN_GET_USERBYTE2(UserData);

        /* fill the OFS message */
        CanTSyn_FillTxOfsFrame(&StbMTimeStamp, &SduData[0], CanTSynPduIndex);

        /* restart the Sequence Counter when reached the limit */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00048,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00049_OFNS_SCUnchanged,1 */
        CanTSyn_OffsetMasterPtr->SeqCount = CANTSYN_SET_SEQ_COUNTER(CanTSyn_OffsetMasterPtr->SeqCount);

        MessageAccepted = TRUE;
      }
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    }

    if(CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      (void)CanTSyn_CheckIcvGenerationState(SduData, CanTSynPduIndex, &MessageAccepted, &RetVal, &sduDataLength);
    }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  }


  if(MessageAccepted == TRUE)
  {
    RetVal = CanTSyn_TransmitOfs(SduData,
                                CanTSynPduIndex,
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
                                sduDataLength,
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
                                CanTSynIsImmediateOFSTransmission,
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)*/
                                CanTSynTxStatus
    );
  }
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_OFF)
  TS_PARAM_UNUSED(CanTSynIsImmediateOFSTransmission);
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_OFF) */


  return RetVal;
}


STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsTxOFSMessageAwaited
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) NewTimeBaseCounter,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) IsImmediateTransmissionPtr,
  uint8 PduId
)
{
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
    CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[PduId];
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
    CanTSyn_TimeMasterDomainPtr =
      &CanTSyn_TimeMasterConfig[PduId + CANTSYN_NUMBER_OF_SYNC_MASTERS];
  Std_ReturnType retVal = E_NOT_OK;
  boolean isImmediateOFSTransmission = FALSE;

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00123,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00032,1 */
  if(CanTSyn_OffsetMasterPtr->DebounceTime != 0U)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
    /* wait until timer will expire */
    CanTSyn_OffsetMasterPtr->DebounceTime--;
  }

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00125,1 */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_OFF)
  if((CanTSyn_OffsetMasterPtr->TimeTxPeriod == 0U) &&
     (CanTSyn_OffsetMasterPtr->DebounceTime == 0U))
#else
  if(((CanTSyn_TimeMasterDomainPtr->IsImmediateTimeSync == TRUE) ||
      (CanTSyn_OffsetMasterPtr->TimeTxPeriod == 0U)) &&
     (CanTSyn_OffsetMasterPtr->DebounceTime == 0U))
#endif
  {
    StbM_TimeBaseStatusType syncTimeBaseStatus = 0U;
    StbM_TimeBaseStatusType offsetTimeBaseStatus = 0U;

    /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
    (void)StbM_GetTimeBaseStatus(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId,
        &syncTimeBaseStatus, &offsetTimeBaseStatus
    );

    if((offsetTimeBaseStatus & CANTSYN_GLOBAL_TIME_BASE_MASK) != 0U)
    {
      /* If CanTSynImmediateTimeSync is set to TRUE, check if immediate transmission is possible */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00118,1 */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
      uint8 newOfsTimeBaseCounter = 0U;

      if(CanTSyn_TimeMasterDomainPtr->IsImmediateTimeSync == TRUE)
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
        newOfsTimeBaseCounter =
            StbM_GetTimeBaseUpdateCounter(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId);

        /* !LINKSTO CanTSyn.SWS_CanTSyn_00117,1 */
        if(newOfsTimeBaseCounter != CanTSyn_OffsetMasterPtr->OfsTimeBaseCounter)
        {
          CanTSyn_OffsetMasterPtr->TimeTxPeriod = 0U;
          *NewTimeBaseCounter = newOfsTimeBaseCounter;
          /* If all the preconditions are fulfilled the immediate transmission is validated */
          isImmediateOFSTransmission = TRUE;
        }
      }

      /* !LINKSTO CanTSyn.SWS_CanTSyn_00038,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00119,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00121.OFS,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00120.OFS,1 */
      if((CanTSyn_OffsetMasterPtr->CyclicMsgResumeTime == 0U) ||
         (TRUE == isImmediateOFSTransmission))
#else
        TS_PARAM_UNUSED(NewTimeBaseCounter);
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
      {
        /* Transmit immediate OFS message if the immediate transmission is enabled and validated,
         * transmit cyclic OFS message if the immediate transmission is not enabled in configuration
         * and if the immediate transmission is enabled in configuration but not validated because
         * not all the preconditions are fulfilled */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00038,1 */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
        if((isImmediateOFSTransmission == TRUE) ||
           ((CanTSyn_TimeMasterDomainPtr->TxPeriodTimeout != 0U) && (CanTSyn_OffsetMasterPtr->TimeTxPeriod == 0U)))
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
        {
          *IsImmediateTransmissionPtr = isImmediateOFSTransmission;
          retVal = E_OK;
        }
      }
    }
  }

  return retVal;
}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxProcessOfsMsg
(
  uint8 ConfirmationHandleId
)
{
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
    CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[ConfirmationHandleId];
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
    CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[CanTSyn_OffsetMasterPtr->IcvIndex];
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
    CanTSyn_TimeMasterDomainPtr =
      &CanTSyn_TimeMasterConfig[ConfirmationHandleId + CANTSYN_NUMBER_OF_SYNC_MASTERS];
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
  if(CanTSyn_OffsetMasterPtr->CyclicMsgResumeTime != 0U)
  {
    /* Wait until CyclicMsgResumeTime will expire */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00120.OFS,1 */
    CanTSyn_OffsetMasterPtr->CyclicMsgResumeTime--;
  }
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */

  if(CanTSyn_OffsetMasterPtr->ConfirmationTimeout != 0U)
  {
    /* wait until timer will expire */
    CanTSyn_OffsetMasterPtr->ConfirmationTimeout--;
  }

  if(CanTSyn_OffsetMasterPtr->TimeTxPeriod != 0U)
  {
    /* wait until timer will expire */
    CanTSyn_OffsetMasterPtr->TimeTxPeriod--;
  }

  /* check the status of the Master Domain */
  switch(CanTSyn_OffsetMasterPtr->TxStatus)
  {
  case CANTSYN_OFSMSG_SEND_WAIT:
  {
    boolean isImmediateOFSTransmission = FALSE;
    uint8 newOfsTimeBaseCounter = 0U;

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    boolean pendingIcv = FALSE;

    if(CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {

      SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

      /* check if ICV generation indication is awaited */
      if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_PENDING)
      {
        CanTSyn_IcvMasterPtr->IcvGenerationTimeout--;
        if(CanTSyn_IcvMasterPtr->IcvGenerationTimeout == 0U)
        {
          /* Icv generation timeout expired before indication was received from Csm */
          CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_FAILED;
        }
      }

      SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

      if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_PENDING)
      {
        /* Icv generation is ongoing; don't try to send the message again */
        pendingIcv = TRUE;
      }
    }

    if(pendingIcv == FALSE)
    {
#endif /* CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON */
      if(E_OK == CanTSyn_IsTxOFSMessageAwaited(&newOfsTimeBaseCounter, &isImmediateOFSTransmission, ConfirmationHandleId))
      {

        /* Transmit OFS Message */
        if(E_OK == CanTSyn_SendOfsMessage(ConfirmationHandleId, CANTSYN_OFSMSG_SEND_WAIT, isImmediateOFSTransmission))
        {
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
          if(isImmediateOFSTransmission == TRUE)
          {
            /* save the new OffsetTimeBaseCounter */
            CanTSyn_OffsetMasterPtr->OfsTimeBaseCounter = newOfsTimeBaseCounter;
          }
#else
          TS_PARAM_UNUSED(newOfsTimeBaseCounter);
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
        }
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
        else
        {
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00036,1 */
          /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfsSENDWAIT-OfsSENDWAIT,1 */
          /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfnsSENDWAIT_OfsSENDWAIT,1 */
          /* reset state machine due to timeout */
          CanTSyn_TxOffsetReset(ConfirmationHandleId);
        }
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */
      }
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    }
#endif /* CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON */
  }
  break;

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
  case CANTSYN_OFNSMSG_SEND_WAIT:
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00040,1 */
    /* wait until timer will expire */
    CanTSyn_OffsetMasterPtr->DebounceTime--;

    /* !LINKSTO CanTSyn.SWS_CanTSyn_00123,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00125,1 */
    if(CanTSyn_OffsetMasterPtr->DebounceTime == 0U)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00039.SameTimeDomain,1 */
      if(E_OK != CanTSyn_SendOfsMessage(ConfirmationHandleId, CANTSYN_OFNSMSG_SEND_WAIT, FALSE))
      {
        /* reset state machine if OFNS transmission failed */
        /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfnsSENDWAIT_OfsSENDWAIT,1 */
        CanTSyn_TxOffsetReset(ConfirmationHandleId);
      }
    }
  }
  break;
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
  /* CANTSYN_OFSMSG_WAIT_TXCONF */
  /* CANTSYN_OFNSMSG_WAIT_TXCONF */
  default:
  {
#if(CANTSYN_RELIABLE_TXCONF == STD_OFF)
    /* !LINKSTO CanTSyn.EB.OFSTxConfTimeout_RevokeTransmission,1 */
    if(CanTSyn_OffsetMasterPtr->ConfirmationTimeout == 0U)
    {
      /* reset state machine due to timeout */
      /* !LINKSTO CanTSyn.EB.OFSTxConfTimeout_ResetSM,1 */
      /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfsWAITTXCONF_OfsSENDWAIT,1 */
      CanTSyn_TxOffsetReset(ConfirmationHandleId);
    }
#endif /* CANTSYN_RELIABLE_TXCONF == STD_OFF */
  }
  break;
  }

}
#endif /* CANTSYN_TX_OFFSET_USED == STD_ON */

#if (CANTSYN_TX_SYNC_USED == STD_ON)
STATIC FUNC(StbM_TimeStampType, CANTSYN_CODE) CanTSyn_SubtractVLT
(
    P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, CANTSYN_VAR) virtualLocalTimeMinuendPtr,
    P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, CANTSYN_VAR) virtualLocalTimeSubtrahendPtr
)
{
  StbM_TimeStampType CalcTimeStamp = {0U, 0U, 0U, 0U};

  /* when virtualLocalTimeSubtrahendPtr->nanosecondsLo is greater than
   * virtualLocalTimeMinuendPtr->nanosecondsLo then
   * virtualLocalTimeMinuendPtr->nanosecondsHi is greater than 0.
   */
  if(virtualLocalTimeSubtrahendPtr->nanosecondsLo > virtualLocalTimeMinuendPtr->nanosecondsLo)
  {
    /* do not consider nanosecondsHi, a difference greater than 0xFFFFFFFF is too much
     * to be considered */
    CalcTimeStamp.nanoseconds = 0xFFFFFFFFU - virtualLocalTimeSubtrahendPtr->nanosecondsLo + virtualLocalTimeMinuendPtr->nanosecondsLo;
    /* + 1U because {0x01 0x00} - {0x00 0xFFFFFFFF} = 1 */
    /* Deviation TASKING-2 */
    CalcTimeStamp.nanoseconds += 1U;
  }
  else
  {
    CalcTimeStamp.nanoseconds = virtualLocalTimeMinuendPtr->nanosecondsLo - virtualLocalTimeSubtrahendPtr->nanosecondsLo;
  }

  return CalcTimeStamp;
}
#endif /* (CANTSYN_TX_SYNC_USED == STD_ON) */

#if(CANTSYN_TX_SYNC_USED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SendSyncMessage
(
  uint8 ConfirmationHandleId,
  boolean IsImmediateSYNCTransmission
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  StbM_TimeStampType StbMTimeStamp;
  StbM_VirtualLocalTimeType T0VLT;
  StbM_UserDataType UserData;
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[ConfirmationHandleId];

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00149,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00056,1 */
  /* get the current time stamp that is valid at this time and */
  /* the User Data of the Time Base */

  /* !LINKSTO CanTSyn.EB.StbM_BusGetCurrentTime_E_NOT_OK,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
  if(E_OK == StbM_BusGetCurrentTime(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId, &StbMTimeStamp, &T0VLT, &UserData))
  {
    PduInfoType CanIfTxInfo;
    uint8 SduData[CANTSYN_TX_MAX_MSG_LEN];
    P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_MasterPtr = &CanTSyn_SyncMaster[ConfirmationHandleId];

    /* save the seconds portion of T0 */
    CanTSyn_MasterPtr->SyncTimeT0.seconds = StbMTimeStamp.seconds;

    /* save the nanoseconds portion of T0 */
    CanTSyn_MasterPtr->SyncTimeT0.nanoseconds = StbMTimeStamp.nanoseconds;

    /* Save virtual local time */
    CanTSyn_MasterPtr->T0VLT = T0VLT;

    /* check the Time Base Status */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00030.SyncToSubDomain.SGW,1 */
    if((StbMTimeStamp.timeBaseStatus & CANTSYN_SYNC_TO_GATEWAY_MASK) != 0U)
    {
      CanTSyn_MasterPtr->SyncSGWBit = CANTSYN_SYNCTOSUBDOMAIN;
    }
    else
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00030.SyncToGTM.SGW,1 */
      CanTSyn_MasterPtr->SyncSGWBit = CANTSYN_SYNCTOGTM;
    }

    /* save the user Data */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00011,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00013,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00014,1 */
    CanTSyn_MasterPtr->UserByte0 = CANTSYN_GET_USERBYTE0(UserData);
    CanTSyn_MasterPtr->UserByte1 = CANTSYN_GET_USERBYTE1(UserData);
    CanTSyn_MasterPtr->UserByte2 = CANTSYN_GET_USERBYTE2(UserData);

#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
    if(CanTSyn_TimeMasterDomainPtr->IsExtendedMessage)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVNotSupported,1 */
      CanIfTxInfo.SduLength = CANTSYN_EXTENDED_MSG_SIZE;
    }
    else
#endif
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.NormalMessage,1 */
      /* size of the message is 8 Bytes */
      CanIfTxInfo.SduLength = CANTSYN_MSG_SIZE;
    }

    CanIfTxInfo.SduDataPtr = SduData;

    /* assemble the message */
    CanTSyn_FillTxSyncFrame(CanIfTxInfo.SduDataPtr, ConfirmationHandleId);

    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_SyncSENDWAIT-SyncWAITTXCONF,1 */
    /* wait for Confirmation */
    CanTSyn_MasterPtr->TxStatus = CANTSYN_SYNCMSG_WAIT_TXCONF;

    /* restart the Sequence Counter when reached the limit */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00048,1 */
    CanTSyn_MasterPtr->SeqCount = CANTSYN_SET_SEQ_COUNTER(CanTSyn_MasterPtr->SeqCount);
    /* load the Confirmation Timeout */
    CanTSyn_MasterPtr->ConfirmationTimeout =
    CanTSyn_TimeMasterDomainPtr->ConfirmationTimeout;

#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
    /* Transmit SYNC Message */
    /* !LINKSTO CanTSyn.EB.CanIf_Transmit_E_NOT_OK,2 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00136,1 */
    RetVal = CanIf_Transmit(CanTSyn_TimeMasterDomainPtr->TxPduId, &CanIfTxInfo);
    if((E_OK == RetVal) || (CanTSyn_MasterPtr->SyncTransRetriesCounter >= (uint8)CANTSYN_MAX_NUMBER_OF_TRANSMIT_RETRIES))
#else
    (void)CanIf_Transmit(CanTSyn_TimeMasterDomainPtr->TxPduId, &CanIfTxInfo);
    RetVal = E_OK;
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */
    {
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00119,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00120.SYNC,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00122,1 */
      if(IsImmediateSYNCTransmission == TRUE)
      {
        CanTSyn_MasterPtr->CyclicMsgResumeTime = CanTSyn_TimeMasterDomainPtr->CyclicMsgResumeTime;
      }
      else
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00028,1 */
        CanTSyn_MasterPtr->TimeTxPeriod = CanTSyn_TimeMasterDomainPtr->TxPeriodTimeout;
      }
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
      /*Reset tramsmit retries counter */
      CanTSyn_MasterPtr->SyncTransRetriesCounter = 0U;
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */
    }
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
    else
    {
      /* !LINKSTO CanTSyn.EB.CanIf_Transmit_E_NOT_OK,2 */
      CanTSyn_MasterPtr->SyncTransRetriesCounter++;
    }
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */
  }

#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_OFF)
  TS_PARAM_UNUSED(IsImmediateSYNCTransmission);
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_OFF)*/


  return RetVal;
}

#if (CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON)
STATIC FUNC(StbM_TimeStampType, CANTSYN_CODE) CanTSyn_AddTimestamp_TimeValidation
(
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAugendPtr,
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAddendPtr
)
{
  StbM_TimeStampType CalcTimeStamp = {0U, 0U, 0U, 0U};

  /* ignore overflow, since each nanosecond element should not reach 10^9 */
  uint32 NsSum = timeStampAugendPtr->nanoseconds + timeStampAddendPtr->nanoseconds;
  /* calculate seconds sum, overflow detection happens later */
  uint32 SecSum = timeStampAugendPtr->seconds + timeStampAddendPtr->seconds;
  /* store carry to add it to the seconds later */
  uint8 NsCarry = (NsSum / CANTSYN_NS_PER_SEC);

  /* write back nanosecond part */
  CalcTimeStamp.nanoseconds = (NsSum % CANTSYN_NS_PER_SEC);
  /* write back (low-)second part considering the Nanosecond carry */
  CalcTimeStamp.seconds = SecSum + NsCarry;

  return CalcTimeStamp;
}
#endif /* (CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON) */

STATIC FUNC(StbM_TimeStampType, CANTSYN_CODE) CanTSyn_AddTimestamp
(
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAugendPtr,
    P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_VAR) timeStampAddendPtr
)
{
  StbM_TimeStampType CalcTimeStamp = {0U, 0U, 0U, 0U};

  /* ignore overflow, since each nanosecond element should not reach 10^9 */
  uint32 NsSum = timeStampAugendPtr->nanoseconds + timeStampAddendPtr->nanoseconds;
  /* calculate seconds sum, overflow detection happens later */
  uint32 SecSum = timeStampAugendPtr->seconds + timeStampAddendPtr->seconds;
  /* store carry to add it to the seconds later */
  uint8 NsCarry = ((NsSum / CANTSYN_NS_PER_SEC) > 0U) ? 1U : 0U;

  /* write back nanosecond part */
  CalcTimeStamp.nanoseconds = NsSum;
  /* write back (low-)second part considering the Nanosecond carry */
  CalcTimeStamp.seconds = SecSum + NsCarry;

  return CalcTimeStamp;
}

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SendFupMessage
(
  uint8 ConfirmationHandleId
)
{
  PduInfoType CanIfTxInfo;
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  boolean transmitNow = TRUE;
  boolean skipMessageFill = FALSE;
  uint8 dataLength = 0U;
  uint8 SduData[CANTSYN_SECURED_MSG_LEN] = {0};
#else /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  uint8 SduData[CANTSYN_TX_MAX_MSG_LEN] = {0};
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 OvsBit = 0U;
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[ConfirmationHandleId];
  P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_MasterPtr = &CanTSyn_SyncMaster[ConfirmationHandleId];
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[CanTSyn_MasterPtr->IcvIndex];
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  if(CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
  {
    /* if ICV generation is ongoing don't fill the frame again */
    if(CanTSyn_IcvMasterPtr->IcvGenerationState != CANTSYN_ICV_STATE_NOT_REQUESTED)
    {
      skipMessageFill = TRUE;
    }
  }
  if(skipMessageFill == FALSE)
#endif
  {
    /* if T4 >= 1s */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00154,1 */ /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00056,1 */
    /* save the seconds portion of Fup T4 into OVS */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00047,1 */
    OvsBit = (uint8)(CanTSyn_MasterPtr->FupTimeT4.nanoseconds/(CANTSYN_NANOSEC_MAX + 1U));

    /* save the nanoseconds portion from Fup T4 */
    CanTSyn_MasterPtr->FupTimeT4.nanoseconds = CanTSyn_MasterPtr->FupTimeT4.nanoseconds%(CANTSYN_NANOSEC_MAX + 1U);
  }
#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeMasterDomainPtr->IsExtendedMessage)
  {

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVSupported,1 */
      CanIfTxInfo.SduLength = CANTSYN_SECURED_MSG_LEN;
    }
    else
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVNotSupported,1 */
      CanIfTxInfo.SduLength = CANTSYN_EXTENDED_MSG_SIZE;
    }
#else /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.ExtendedMessageICVNotSupported,1 */
    CanIfTxInfo.SduLength = CANTSYN_EXTENDED_MSG_SIZE;
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  }
  else
#endif /* (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON) */
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00010.DLC.NormalMessage,1 */
    /* size of the message is 8 Bytes */
    CanIfTxInfo.SduLength = CANTSYN_MSG_SIZE;
  }

  CanIfTxInfo.SduDataPtr = SduData;

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  if(skipMessageFill == FALSE)
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
  {
    /* assemble the message */
    CanTSyn_FillTxFupFrame(CanIfTxInfo.SduDataPtr, ConfirmationHandleId, OvsBit);
  }
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)

  if(CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
  {
    if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_PENDING)
    {
      /* do not transmit the frame while ICV generation is still ongoing */
      transmitNow = FALSE;
    }
    else if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_FAILED)
    {
      /* Icv generation failed; restore frame contents and transmit without Icv */
      /* restore content of FUP frame from global array*/
      TS_MemCpy(CanIfTxInfo.SduDataPtr,
                &CanTSyn_IcvData[CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvDataStartIndex + CANTSYN_SYNC_PAYLOAD_LENGTH],
                CANTSYN_FUP_ICV_PAYLOAD_LENGTH
      );
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00175.StopICVGeneration,1 */
      CanIfTxInfo.SduDataPtr[CANTSYN_B8_FVL] = 0U;
      CanIfTxInfo.SduDataPtr[CANTSYN_B9_ICVL] = 0U;

#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
  #ifdef CANTSYN_SEV_ICV_GENERATION_FAILED
      /* Icv generation failed; report event to IdsM */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00175.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
      IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_ICV_GENERATION_FAILED, &CanTSyn_TimeMasterConfig[ConfirmationHandleId].TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_ICV_GENERATION_FAILED */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)  */
    }
    else if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_RECEIVED)
    {
      /* Icv generation is successful ; add ICV to frame and transmit FUP message */
      /* restore content of FUP frame from global array*/
      TS_MemCpy(CanIfTxInfo.SduDataPtr,
                &CanTSyn_IcvData[CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvDataStartIndex + CANTSYN_SYNC_PAYLOAD_LENGTH],
                CANTSYN_FUP_ICV_PAYLOAD_LENGTH
      );

      /* add ICV to frame */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00161.ICVinFUP,1 */
      CanTSyn_AddFvAndIcvToFrame(CanIfTxInfo.SduDataPtr,
                                 ConfirmationHandleId,
                                 CanTSyn_MasterPtr->IcvIndex,
#if(CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
                                 CANTSYN_SYNC_PAYLOAD_LENGTH,
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
                               CANTSYN_FUP_ICV_PAYLOAD_LENGTH);
    }
    else
    {
      /* CANTSYN_ICV_STATE_NOT_REQUESTED */
      /* do nothing */
    }
    dataLength = CANTSYN_FUP_ICV_PAYLOAD_LENGTH + (CANTSYN_COMPUTE_FVL_IN_BYTES(CanIfTxInfo.SduDataPtr[CANTSYN_B8_FVL])) + CanIfTxInfo.SduDataPtr[CANTSYN_B9_ICVL];
    CanIfTxInfo.SduLength =  dataLength;
  }


  if(transmitNow == TRUE)
  {
    if(CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Failed_NotRequested,1 */
      /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Received_NotRequested,1 */
      CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_NOT_REQUESTED;
    }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_FupSENDWAIT-FupWAITTXCONF,1 */
    /* wait for Confirmation */
    CanTSyn_MasterPtr->TxStatus = CANTSYN_FUPMSG_WAIT_TXCONF;
    /* load the Confirmation Timeout */
    CanTSyn_MasterPtr->ConfirmationTimeout =
        CanTSyn_TimeMasterDomainPtr->ConfirmationTimeout;
    /* Transmit FUP Message */
    /* !LINKSTO CanTSyn.EB.CanIf_Transmit_E_NOT_OK,2 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00136,1 */
    retVal = CanIf_Transmit(CanTSyn_TimeMasterDomainPtr->TxPduId, &CanIfTxInfo);
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  }
  else
  {
    retVal = E_OK;
  }
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

  return retVal;
}

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsTxSYNCMessageAwaited
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) NewTimeBaseCounter,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) IsImmediateTransmissionPtr,
  uint8 PduId
)
{
  P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
    CanTSyn_SyncMasterPtr = &CanTSyn_SyncMaster[PduId];
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
    CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[PduId];
  Std_ReturnType retVal = E_NOT_OK;
  boolean isImmediateSYNCTransmission = FALSE;
  StbM_TimeBaseStatusType syncTimeBaseStatus = 0U;
  StbM_TimeBaseStatusType offsetTimeBaseStatus = 0U;

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00123,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00032,1 */
  if(CanTSyn_SyncMasterPtr->DebounceTime != 0U)
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
    /* wait until timer will expire */
    CanTSyn_SyncMasterPtr->DebounceTime--;
  }

#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_OFF)
  if((CanTSyn_SyncMasterPtr->TimeTxPeriod == 0U) &&
     (CanTSyn_SyncMasterPtr->DebounceTime == 0U))
#else
  if(((CanTSyn_TimeMasterDomainPtr->IsImmediateTimeSync == TRUE) ||
      (CanTSyn_SyncMasterPtr->TimeTxPeriod == 0U)) &&
     (CanTSyn_SyncMasterPtr->DebounceTime == 0U))
#endif
  {
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
    (void)StbM_GetTimeBaseStatus(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId,
        &syncTimeBaseStatus, &offsetTimeBaseStatus
    );

    if((syncTimeBaseStatus & CANTSYN_GLOBAL_TIME_BASE_MASK) != 0U)
    {
      /* If CanTSynImmediateTimeSync is set to TRUE, check if immediate transmission
       * is possible */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00118,1 */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
      uint8 newSyncTimeBaseCounter = 0U;

      if(CanTSyn_TimeMasterDomainPtr->IsImmediateTimeSync == TRUE)
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
        newSyncTimeBaseCounter =
            StbM_GetTimeBaseUpdateCounter(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId);

        if(newSyncTimeBaseCounter != CanTSyn_SyncMasterPtr->syncTimeBaseCounter)
        {
          CanTSyn_SyncMasterPtr->TimeTxPeriod = 0U;
          *NewTimeBaseCounter = newSyncTimeBaseCounter;
          /* If all the preconditions are fulfilled the immediate transmission is validated */
          isImmediateSYNCTransmission = TRUE;
        }
      }

      /* Resume cyclic message transmission if CyclicMsgResumeTime has reached a value equal or
       * less than zero */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00121.SYNC,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00122,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00028,1 */
      if((CanTSyn_SyncMasterPtr->CyclicMsgResumeTime == 0U) ||
         (TRUE == isImmediateSYNCTransmission))
#else
      TS_PARAM_UNUSED(NewTimeBaseCounter);
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
      {
        /* Transmit immediate SYNC message if the immediate transmission is enabled and validated,
         * transmit cyclic SYNC message if the immediate transmission is not enabled in
         * configuration and if the immediate transmission is enabled in configuration but not
         * validated because not all the preconditions are fulfilled */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00028,1 */
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
        if((isImmediateSYNCTransmission == TRUE) ||
            ((CanTSyn_TimeMasterDomainPtr->TxPeriodTimeout != 0U) && (CanTSyn_SyncMasterPtr->TimeTxPeriod == 0U)))
#endif
        {
          *IsImmediateTransmissionPtr = isImmediateSYNCTransmission;
          retVal = E_OK;
        }
      }
    }
  }

  return retVal;
}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_TxProcessSyncMsg
(
  uint8 ConfirmationHandleId
)
{
  P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
    CanTSyn_SyncMasterPtr = &CanTSyn_SyncMaster[ConfirmationHandleId];
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
    CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[CanTSyn_SyncMasterPtr->IcvIndex];
  boolean decreaseDebounce = TRUE;
#endif /* (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
  if(CanTSyn_SyncMasterPtr->CyclicMsgResumeTime != 0U)
  {
    /* Wait until CyclicMsgResumeTime will expire */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00120.SYNC,1 */
    CanTSyn_SyncMasterPtr->CyclicMsgResumeTime--;
  }
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */

  if(CanTSyn_SyncMasterPtr->TimeTxPeriod != 0U)
  {
    /* wait until timer will expire */
    CanTSyn_SyncMasterPtr->TimeTxPeriod--;
  }

  if(CanTSyn_SyncMasterPtr->ConfirmationTimeout != 0U)
  {
    /* wait until timer will expire */
    CanTSyn_SyncMasterPtr->ConfirmationTimeout--;
  }

  /* check the status of the Master Domain */
  switch(CanTSyn_SyncMasterPtr->TxStatus)
  {
  case CANTSYN_SYNCMSG_SEND_WAIT:
  {
    boolean isImmediateSYNCTransmission = FALSE;
    uint8 newSyncTimeBaseCounter = 0U;

    if(E_OK == CanTSyn_IsTxSYNCMessageAwaited(&newSyncTimeBaseCounter, &isImmediateSYNCTransmission, ConfirmationHandleId))
    {
      /* Transmit immediate or synchronous SYNC Message */
      if(E_OK == CanTSyn_SendSyncMessage(ConfirmationHandleId, isImmediateSYNCTransmission))
      {
#if(CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON)
        if(isImmediateSYNCTransmission == TRUE)
        {
          /* save the new SyncTimeBaseCounter */
          CanTSyn_SyncMasterPtr->syncTimeBaseCounter = newSyncTimeBaseCounter;
        }
#else
        TS_PARAM_UNUSED(newSyncTimeBaseCounter);
#endif /* (CANTSYN_TX_IMMEDIATE_TRANSMISSION == STD_ON) */
      }
#if(CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON)
      else
      {
        /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_SyncSENDWAIT-SyncSENDWAIT,1 */
        /* reset state machine due to timeout */
        CanTSyn_TxSyncReset(ConfirmationHandleId);
      }
#endif /* (CANTSYN_MAX_TRANSMIT_RETRIES == STD_ON) */
    }
  }
  break;

  case CANTSYN_FUPMSG_SEND_WAIT:
  {
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {

      SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

      /* check if ICV generation indication is awaited */
      if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_PENDING)
      {
        CanTSyn_IcvMasterPtr->IcvGenerationTimeout--;
        if(CanTSyn_IcvMasterPtr->IcvGenerationTimeout == 0U)
        {
          /* Icv generation timeout expired before indication was received from Csm */
          /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Pending_Failed_TimeoutExpired,1 */
          CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_FAILED;
        }
      }

      SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
    }
#endif /* CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON */

    /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
    /* wait until timer will expire */
#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)
    if(CanTSyn_TimeMasterConfig[ConfirmationHandleId].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
    {
      if(CanTSyn_IcvMasterPtr->IcvGenerationState != CANTSYN_ICV_STATE_NOT_REQUESTED)
      {
        decreaseDebounce = FALSE;
      }
    }
    if(decreaseDebounce == TRUE)
#endif
    {
      CanTSyn_SyncMasterPtr->DebounceTime--;
    }
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00123,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00125,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00032,1 */
    if(CanTSyn_SyncMasterPtr->DebounceTime == 0U)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00029.SameTimeDomain,1 */
      if(E_OK != CanTSyn_SendFupMessage(ConfirmationHandleId))
      {
        /* reset state machine due to timeout */
        /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_FupSENDWAIT-SyncSENDWAIT,1 */
        CanTSyn_TxSyncReset(ConfirmationHandleId);
      }

      /* !LINKSTO CanTSyn.SWS_CanTSyn_00049.FUP.SCUnchanged,1 */
      /* Sequence counter remains unchanged on every transmission request of a FUP message.*/
    }
  }
  break;

  /* CANTSYN_FUPMSG_WAIT_TXCONF */
  /* CANTSYN_SYNCMSG_WAIT_TXCONF */
  default:
  {
#if(CANTSYN_RELIABLE_TXCONF == STD_OFF)
    /* !LINKSTO CanTSyn.EB.SyncTxConfTimeout_RevokeTransmission,1 */
    /* observe Confirmation Timeout */
    if(CanTSyn_SyncMasterPtr->ConfirmationTimeout == 0U)
    {
      /* reset state machine due to timeout */
      /* !LINKSTO CanTSyn.EB.SyncTxConfTimeout_ResetSM,1 */
      /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_SyncWAITTXCONF_SyncSENDWAIT,1 */
      /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_FupWAITTXCONF_SyncSENDWAIT,1 */
      CanTSyn_TxSyncReset(ConfirmationHandleId);
    }
#endif /* CANTSYN_RELIABLE_TXCONF == STD_OFF */
  }
  break;
  }

}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ConfirmSyncMsg
(
  uint8 CanTSyn_PduActiveIndex
)
{
  P2VAR(CanTSyn_SyncMasterType, AUTOMATIC, CANTSYN_VAR) CanTSyn_MasterPtr = &CanTSyn_SyncMaster[CanTSyn_PduActiveIndex];
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[CanTSyn_PduActiveIndex];

  switch(CanTSyn_MasterPtr->TxStatus)
  {
    case CANTSYN_SYNCMSG_WAIT_TXCONF:
    {
      boolean ProcessConfirmation = FALSE;
      StbM_VirtualLocalTimeType T1VLT;

      /* !LINKSTO CanTSyn.SWS_CanTSyn_00150.SwTimeStamp,1 */
      SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_1();

      /* !LINKSTO CanTSyn.EB.StbM_GetCurrentVirtualLocalTime_E_NOT_OK,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
      if(E_OK == StbM_GetCurrentVirtualLocalTime(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId, &T1VLT))
      {
        ProcessConfirmation = TRUE;
      }

      SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_1();

      if(ProcessConfirmation)
      {
         StbM_TimeStampType T1_T0VLT;
         StbM_VirtualLocalTimeType T0VLT = CanTSyn_MasterPtr->T0VLT;
         StbM_TimeStampType T0SyncNs = {0U, 0U, 0U, 0U};

         T0SyncNs.nanoseconds = CanTSyn_MasterPtr->SyncTimeT0.nanoseconds;

         T1_T0VLT = CanTSyn_SubtractVLT(&T1VLT, &T0VLT);
         CanTSyn_MasterPtr->FupTimeT4 = CanTSyn_AddTimestamp(&T0SyncNs, &T1_T0VLT);

        /* load Tx Follow Up Offset Timeout */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00032,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
        CanTSyn_MasterPtr->DebounceTime = CanTSyn_TimeMasterDomainPtr->DebounceTime;

        /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_SyncWAITTXCONF-FupSENDWAIT,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00026,1 */
        /* FUP message will be sent next */
        CanTSyn_MasterPtr->TxStatus = CANTSYN_FUPMSG_SEND_WAIT;
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00137,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00138,1 */
#if (CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON)
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00141,1 */
        if(TRUE == CanTSyn_TimeMasterDomainPtr->IsTimeValidationUsed)
        {
          StbM_CanTimeMasterMeasurementType MasterMeasureData = {0U, {0U, 0U}, {0U, 0U}, 0U};
          uint8 sequenceCounterVal = CANTSYN_GET_SEQ_COUNTER(CanTSyn_SyncMaster[CanTSyn_PduActiveIndex].SeqCount);
          StbM_TimeStampType FullPreciseOriginTimestamp = CanTSyn_AddTimestamp_TimeValidation(&(CanTSyn_MasterPtr->SyncTimeT0), &T1_T0VLT);
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00142.SequenceCounter,1 */
          MasterMeasureData.sequenceCounter = (uint16)sequenceCounterVal;
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00142.syncEgressTimestamp,1 */
          MasterMeasureData.syncEgressTimestamp = T1VLT;
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00142.preciseOriginTimestamp,1 */
          MasterMeasureData.preciseOriginTimestamp.nanoseconds = FullPreciseOriginTimestamp.nanoseconds;
          MasterMeasureData.preciseOriginTimestamp.seconds = FullPreciseOriginTimestamp.seconds;
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00142.segmentId,1 */
          MasterMeasureData.segmentId=CanTSyn_TimeMasterDomainPtr->NetworkSegmentId;

         /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
          (void)StbM_CanSetMasterTimingData(CanTSyn_TimeMasterDomainPtr->SyncTimeBaseId, &MasterMeasureData);
        }
#endif /* CANTSYN_MASTER_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON */
      }
    }
    break;

    case CANTSYN_FUPMSG_WAIT_TXCONF:
    {
      /* load the Debounce Timeout */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
      CanTSyn_MasterPtr->DebounceTime = CanTSyn_TimeMasterDomainPtr->DebounceTime;
      /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynTxStatus_FupWAITTXCONF_SyncSENDWAIT,1 */
      /* SYNC message will be sent next */
      CanTSyn_MasterPtr->TxStatus = CANTSYN_SYNCMSG_SEND_WAIT;

#if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) && (CANTSYN_ICV_GENERATION_FV_USED == STD_ON))
      if((CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED) && (CanTSyn_TimeMasterDomainPtr->IsFvUsed == TRUE))
      {
        /* Notify FvM of successful transmission of authenticated messages */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00177,1 */
        StbM_SPduTxConfirmation(CanTSyn_TimeMasterDomainPtr->IcvGenerationFvId);
      }
#endif /* ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) && (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)) */
    }
    break;

    default:
       /* Tx Confirmation not awaited */
    break;
  }
}
#endif /* CANTSYN_TX_SYNC_USED == STD_ON */


#if(CANTSYN_TX_OFFSET_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ConfirmOfsMsg
(
  uint8 CanTSyn_PduActiveIndex
)
{
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_VAR) CanTSyn_MasterPtr = &CanTSyn_OffsetMaster[CanTSyn_PduActiveIndex];
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSyn_TimeMasterDomainPtr =
      &CanTSyn_TimeMasterConfig[CanTSyn_PduActiveIndex + CANTSYN_NUMBER_OF_SYNC_MASTERS];

  switch(CanTSyn_MasterPtr->TxStatus)
  {
    case CANTSYN_OFSMSG_WAIT_TXCONF:
    {
      /* load Tx Follow Up Offset Timeout */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00040,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
      CanTSyn_MasterPtr->DebounceTime = CanTSyn_TimeMasterDomainPtr->DebounceTime;
#if (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON)
      if(CanTSyn_TimeMasterDomainPtr->IsExtendedMessage)
      {
        /* !LINKSTO CanTSyn.Dsn.OfsExtended.CanTSynTxStatus_OfsWAITTXCONF_OfsSENDWAIT,1 */
        /* !LINKSTO CanTSyn.EB.ExtendedOFS,1 */
        /* OFS message will be sent next */
        CanTSyn_MasterPtr->TxStatus = CANTSYN_OFSMSG_SEND_WAIT;

#if ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) && (CANTSYN_ICV_GENERATION_FV_USED == STD_ON))
        if((CanTSyn_TimeMasterDomainPtr->IcvGenerationSupport == CANTSYN_ICV_SUPPORTED) && (CanTSyn_TimeMasterDomainPtr->IsFvUsed == TRUE))
        {
          /* Notify FvM of successful transmission of authenticated messages */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00177,1 */
          StbM_SPduTxConfirmation(CanTSyn_TimeMasterDomainPtr->IcvGenerationFvId);
        }
#endif /* ((CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) && (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)) */
      }
      else
#endif /* (CANTSYN_TX_USE_EXTENDED_MSG == STD_ON) */
      {
#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
        /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfsWAITTXCONF-OfnsSENDWAIT,1 */
        /* OFNS message will be sent next */
        CanTSyn_MasterPtr->TxStatus = CANTSYN_OFNSMSG_SEND_WAIT;
#else /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

        /* should not happen */
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
        CANTSYN_UNREACHABLE_CODE_ASSERT(CANTSYN_SID_TXCONFIRMATION);
#endif /* (CANTSYN_DEV_ERROR_DETECT == STD_ON) */

#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
      }
    }
    break;

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
    case CANTSYN_OFNSMSG_WAIT_TXCONF:
    {
      /* load the Debounce Timeout */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00124,1 */
      CanTSyn_MasterPtr->DebounceTime = CanTSyn_TimeMasterDomainPtr->DebounceTime;
      /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynTxStatus_OfnsWAITTXCONF_OfsSENDWAIT,1 */
      /* OFS message will be sent next */
      CanTSyn_MasterPtr->TxStatus = CANTSYN_OFSMSG_SEND_WAIT;
    }
    break;
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

    default:
       /* Tx Confirmation not awaited */
    break;
  }

}
#endif /* CANTSYN_TX_OFFSET_USED == STD_ON */


#if(CANTSYN_TX_CRC_USED == STD_ON)

STATIC FUNC(uint8, CANTSYN_CODE) CanTSyn_CalculateCRC
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) TxDataPtr,
  CanTSyn_DataIDListType DataId,
  uint8 CrcLength
)
{
  uint8 computedCRC;
  uint8 CRCData[CANTSYN_TX_MAX_MSG_LEN - 1U];
  uint8 DataIdPos = CrcLength - 1U;

  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  /* copy bytes 2 to CrcLength - 1U */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00055.CRC.ExtendedMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00055.CRC.NormalMessage,1 */
  TS_MemCpy(&CRCData[0], &TxDataPtr[0], (uint8)(CrcLength - 1U));

  /* add the DataID Value based on the current sequence counter */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00054,1 */
  CRCData[DataIdPos] = DataId;

  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  /* get the CRC value */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00050,1 */
  computedCRC = Crc_CalculateCRC8H2F(&CRCData[0], CrcLength, CANTSYN_START_VALUE_8H2F, TRUE);

  return computedCRC;
}
#endif /* CANTSYN_TX_CRC_USED == STD_ON */

#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_GetRxStatus
(
  uint8 SlavePduId,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) RxStatusPtr
)
{
#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
  if(SlavePduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
  {
    *RxStatusPtr = CanTSyn_SyncSlave[SlavePduId].RxStatus;
  }
  else
  {
    *RxStatusPtr = CanTSyn_OffsetSlave[SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES].RxStatus;
  }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
  *RxStatusPtr = CanTSyn_SyncSlave[SlavePduId].RxStatus;
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
  *RxStatusPtr = CanTSyn_OffsetSlave[SlavePduId].RxStatus;
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */

}

#if(CANTSYN_RX_SYNC_USED == STD_ON)
#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsAuthFUPType
(
  uint8 SlavePduId,
  uint8 Type,
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType,
#endif
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

#if (CANTSYN_RX_CRC_USED == STD_OFF)
  /* check for message type 0x78 if CRC not validated */
  /* check for message type 0x78 anf 0x88 if CRC is ignored */
  if(
      (CANTSYN_IS_CRC_NOT_VAL_FUP_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_FUP_ICV_AUTH(SlavePduId, Type) == TRUE)
    )
#else /*  (CANTSYN_RX_CRC_USED == STD_ON) */
  /* check for message type 0x78 if CRC is not validated  */
  /* check for message type 0x78 or 0x88 if CRC is ignored or optional  */
  if(
      (CANTSYN_IS_CRC_NOT_VAL_FUP_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_FUP_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_OPTIONAL_FUP_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }

#if (CANTSYN_RX_CRC_USED == STD_ON)
  /* check for message type 0x78 or 0x88 if CRC is optional  */
  /* check for message type 0x88 if CRC is validated  */
  if(((CANTSYN_IS_CRC_OPTIONAL_FUP_ICV_AUTH(SlavePduId, Type) == TRUE) &&
       (CANTSYN_IS_FUP_CRC_TYPE_ICV_AUTH(Type) == TRUE)) ||
      (isCrcType))
  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }

    return RetVal;
}
#endif /* if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */


STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsFUPType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00110.ValidFUPMessage.NoCRC,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00110.ValidFUPMessage.CRC,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00110.InvalidType.FUPMessage,1 */
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType = CANTSYN_IS_CRC_VAL_FUP(SlavePduId, Type);
#endif

#if (CANTSYN_RX_CRC_USED == STD_OFF)
  if(
      (CANTSYN_IS_CRC_NOT_VAL_FUP(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_FUP(SlavePduId, Type) == TRUE)
    )
#else /*  (CANTSYN_RX_CRC_USED == STD_ON) */
  if(
      (CANTSYN_IS_CRC_NOT_VAL_FUP(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_FUP(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_OPTIONAL_FUP(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }


#if (CANTSYN_RX_CRC_USED == STD_ON)
  if(
      ((CANTSYN_IS_CRC_OPTIONAL_FUP(SlavePduId, Type) == TRUE) &&
       (CANTSYN_IS_FUP_CRC_TYPE(Type) == TRUE)) ||
      (isCrcType)
    )

  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }

#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
  if(RetVal != E_OK)
  {
    RetVal = CanTSyn_IsAuthFUPType(SlavePduId,
                                  Type,
#if (CANTSYN_RX_CRC_USED == STD_ON)
                                  isCrcType,
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
                                  CrcValidation
    );
  }
#endif /* if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

  return RetVal;
}


STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsSYNCType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* check the received message type */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00058.SYNC.ValidType,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00059.SYNC.ValidType,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00109.ValidSYNCMessage.NoCRC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00109.ValidSYNCMessage.CRC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00109.InvalidType.SYNCMessage,1 */
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType = CANTSYN_IS_CRC_VAL_SYNC(SlavePduId, Type);
#endif

#if (CANTSYN_RX_CRC_USED == STD_OFF)
  if(
      (CANTSYN_IS_CRC_NOT_VAL_SYNC(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_SYNC(SlavePduId, Type) == TRUE)
    )
#else /* (CANTSYN_RX_CRC_USED == STD_ON) */
  if(
      (CANTSYN_IS_CRC_NOT_VAL_SYNC(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_SYNC(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_OPTIONAL_SYNC(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }
#if (CANTSYN_RX_CRC_USED == STD_ON)
  if(
      ((CANTSYN_IS_CRC_OPTIONAL_SYNC(SlavePduId, Type) == TRUE) &&
       (CANTSYN_IS_SYNC_CRC_TYPE(Type) == TRUE)) ||
      (isCrcType)
    )
  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }
  return RetVal;
}
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
#if(CANTSYN_OFNS_FRAME_USED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFNSType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

    /* !LINKSTO CanTSyn.SWS_CanTSyn_00114.ValidOFNSMessage.NoCRC,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00114.ValidOFNSMessage.CRC,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00114.InvalidType.OFNSMessage,1 */
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType = CANTSYN_IS_CRC_VAL_OFNS(SlavePduId, Type);
#endif

/* !LINKSTO CanTSyn.SWS_CanTSyn_00070.ValidOFNSMessage,1 */
#if (CANTSYN_RX_CRC_USED == STD_OFF)
  if(
      (CANTSYN_IS_CRC_NOT_VAL_OFNS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_OFNS(SlavePduId, Type) == TRUE)
    )
#else /* (CANTSYN_RX_CRC_USED == STD_ON) */
  if(
      (CANTSYN_IS_CRC_NOT_VAL_OFNS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_OFNS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_OPTIONAL_OFNS(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }
#if (CANTSYN_RX_CRC_USED == STD_ON)
  if(
      ((CANTSYN_IS_CRC_OPTIONAL_OFNS(SlavePduId, Type) == TRUE) &&
       (CANTSYN_IS_OFNS_CRC_TYPE(Type) == TRUE)) ||
      (isCrcType)
    )
  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }
  return RetVal;
}
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFSType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeSlaveConfig[SlavePduId].IsExtendedMessage)
  {
    RetVal = CanTSyn_IsOFSExtenedType(SlavePduId, Type, CrcValidation);
  }
  else
#endif /* CANTSYN_RX_USE_EXTENDED_MSG == STD_ON */
  {
    RetVal = CanTSyn_IsOFSNormalType(SlavePduId, Type, CrcValidation);
  }
  return RetVal;
}


#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsAuthOFSExtenedType
(
  uint8 SlavePduId,
  uint8 Type,
#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType,
#endif
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

#if(CANTSYN_RX_CRC_USED == STD_OFF)
  /* check for message type 0x94 if CRC is not validated  */
  /* check for message type 0x94 or 0xA4 if CRC is ignored */
  if(
      (CANTSYN_IS_EXT_CRC_NOT_VAL_OFS_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_EXT_CRC_IGNORED_OFS_ICV_AUTH(SlavePduId, Type) == TRUE)
    )
#else /* (CANTSYN_RX_CRC_USED == STD_ON) */
  /* check for message type 0x94 if CRC is not validated  */
  /* check for message type 0x94 or 0xA4 if CRC is ignored or optional */
  if(
      (CANTSYN_IS_EXT_CRC_NOT_VAL_OFS_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_EXT_CRC_IGNORED_OFS_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_EXT_CRC_OPTIONAL_OFS_ICV_AUTH(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }

#if (CANTSYN_RX_CRC_USED == STD_ON)
  /* check for message type 0x94 or 0xA4 if CRC is optional */
  /* check for message type 0xA4 if CRC is validated */
  if(
    ((CANTSYN_IS_EXT_CRC_OPTIONAL_OFS_ICV_AUTH(SlavePduId, Type) == TRUE) &&
     (CANTSYN_IS_OFS_EXT_CRC_TYPE_ICV_AUTH(Type) == TRUE)) ||
    (isCrcType)
  )
  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }
  return RetVal;
}
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */


STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFSExtenedType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType = CANTSYN_IS_EXT_CRC_VAL_OFS(SlavePduId, Type);
#endif

  /* check the received message type */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00066.Valid.NormalOFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00067.Valid.OFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00065.Valid.NormalOFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00113.ValidOFSMessage.NoCRC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00113.ValidOFSMessage.CRC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00113.InvalidType.OFSMessage,1 */
#if (CANTSYN_RX_CRC_USED == STD_OFF)
  if(
      (CANTSYN_IS_EXT_CRC_NOT_VAL_OFS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_EXT_CRC_IGNORED_OFS(SlavePduId, Type) == TRUE)
    )
#else /* (CANTSYN_RX_CRC_USED == STD_ON) */
  if(
      (CANTSYN_IS_EXT_CRC_NOT_VAL_OFS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_EXT_CRC_IGNORED_OFS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_EXT_CRC_OPTIONAL_OFS(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }
#if (CANTSYN_RX_CRC_USED == STD_ON)
  if(
    ((CANTSYN_IS_EXT_CRC_OPTIONAL_OFS(SlavePduId, Type) == TRUE) &&
     (CANTSYN_IS_OFS_EXT_CRC_TYPE(Type) == TRUE)) ||
    (isCrcType)
  )
  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }
#if(CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
  if(RetVal != E_OK)
  {
    RetVal = CanTSyn_IsAuthOFSExtenedType(SlavePduId,
                                          Type,
#if (CANTSYN_RX_CRC_USED == STD_ON)
                                          isCrcType,
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
                                          CrcValidation
    );
  }
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)  */

  return RetVal;
}
#endif /* CANTSYN_RX_USE_EXTENDED_MSG == STD_ON */

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_IsOFSNormalType
(
  uint8 SlavePduId,
  uint8 Type,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;

#if(CANTSYN_RX_CRC_USED == STD_ON)
  boolean isCrcType = CANTSYN_IS_CRC_VAL_OFS(SlavePduId, Type);
#endif

  /* check the received message type */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00066.Valid.NormalOFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00067.Valid.OFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00065.Valid.NormalOFSMessage,1 */
#if (CANTSYN_RX_CRC_USED == STD_OFF)
  if(
      (CANTSYN_IS_CRC_NOT_VAL_OFS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_OFS(SlavePduId, Type) == TRUE)
    )
#else /* (CANTSYN_RX_CRC_USED == STD_ON) */
 if(
      (CANTSYN_IS_CRC_NOT_VAL_OFS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_IGNORED_OFS(SlavePduId, Type) == TRUE) ||
      (CANTSYN_IS_CRC_OPTIONAL_OFS(SlavePduId, Type) == TRUE) ||
      (isCrcType)
    )
#endif /* (CANTSYN_RX_CRC_USED == STD_OFF) */
  {
    RetVal = E_OK;
  }
#if (CANTSYN_RX_CRC_USED == STD_ON)
  if(
      ((CANTSYN_IS_CRC_OPTIONAL_OFS(SlavePduId, Type) == TRUE) &&
       (CANTSYN_IS_OFS_CRC_TYPE(Type) == TRUE)) ||
      (isCrcType)
    )
  {
    *CrcValidation = TRUE;
  }
  else
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */
  {
    *CrcValidation = FALSE;
  }
  return RetVal;
}
#endif /* CANTSYN_RX_OFFSET_USED == STD_ON */

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckMsgType
(
  uint8 SlavePduId,
  uint8 RxStatus,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  P2VAR(boolean, AUTOMATIC, CANTSYN_APPL_DATA) CrcValidation
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  const uint8 Type = DataPtr[0];

  switch(RxStatus)
  {
#if(CANTSYN_RX_SYNC_USED == STD_ON)
    /* Fall through */
    case CANTSYN_FUPMSG_RX_WAIT:
    case CANTSYN_FUPMSG_RX_WAIT_TIMEOUT:
    {
      RetVal = CanTSyn_IsFUPType(SlavePduId, Type, CrcValidation);
#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING)
  #ifdef CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR
      if(RetVal == E_NOT_OK)
      {
        /* message received with wrong sequence counter; report event to IdsM */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00182,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00204,1 */
        IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR, &CanTSyn_TimeSlaveConfig[SlavePduId].TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
      }
  #endif /* CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING) */
      break;
    }

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    case CANTSYN_SYNCMSG_RX_WAIT:
#else
    default:
    /* CANTSYN_SYNCMSG_RX_WAIT */
#endif
    {
      RetVal = CanTSyn_IsSYNCType(SlavePduId, Type, CrcValidation);
      break;
    }
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */

#if(CANTSYN_RX_OFFSET_USED == STD_ON)

    /* Fall through */
    case CANTSYN_OFNSMSG_RX_WAIT:
    case CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT:
    {
#if(CANTSYN_OFNS_FRAME_USED == STD_ON)
      RetVal = CanTSyn_IsOFNSType(SlavePduId, Type, CrcValidation);
#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING)
  #ifdef CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR
      if(RetVal == E_NOT_OK)
      {
        /* message received with wrong sequence counter; report event to IdsM */
        /* !LINKSTO CanTSyn.EB.CanTSynGlobalTimeFollowUpTimeout.OfsOfnsPair,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00204,1 */
        IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR, &CanTSyn_TimeSlaveConfig[SlavePduId].TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
      }
  #endif /* def CANTSYN_SEV_SYNC_FUP_SEQUENCE_ERROR */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING) */
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
      break;
    }

    default:
    /* CANTSYN_OFSMSG_RX_WAIT */
    {
      RetVal = CanTSyn_IsOFSType(SlavePduId, Type, CrcValidation);
      break;
    }
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
  }
  return RetVal;
}

#if(CANTSYN_RX_CRC_USED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckMsgCRC
(
  uint8 SlavePduId,
  uint8 RxStatus,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  switch(RxStatus)
  {
#if(CANTSYN_RX_SYNC_USED == STD_ON)
    /* Fall through */
    case CANTSYN_FUPMSG_RX_WAIT:
    case CANTSYN_FUPMSG_RX_WAIT_TIMEOUT:
    {
      RetVal = CanTSyn_FupMsg_Rx_CRC_Check(SlavePduId, DataPtr);
      break;
    }

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    case CANTSYN_SYNCMSG_RX_WAIT:
#else
    default:
    /* CANTSYN_SYNCMSG_RX_WAIT */
#endif
    {
      RetVal = CanTSyn_SyncMsg_Rx_CRC_Check(SlavePduId, DataPtr);
      break;
    }
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */

#if(CANTSYN_RX_OFFSET_USED == STD_ON)

    /* Fall through */
    case CANTSYN_OFNSMSG_RX_WAIT:
    case CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT:
    {
#if(CANTSYN_OFNS_FRAME_USED == STD_ON)
      RetVal = CanTSyn_OfnsMsg_Rx_CRC_Check(SlavePduId, DataPtr);
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
      break;
    }

    default:
    /* CANTSYN_OFSMSG_RX_WAIT */
    {
      RetVal = CanTSyn_OfsMsg_Rx_CRC_Check(SlavePduId, DataPtr);
      break;
    }
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
  }

  return RetVal;
}
#endif /* CANTSYN_RX_CRC_USED == STD_ON */

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckSequenceCounter
(
  uint8 RxPduId,
  uint8 ReceivedSC,
  boolean IsSync
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(CanTSyn_TimeSlaveDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_TimeSlaveConfigPtr = &CanTSyn_TimeSlaveConfig[RxPduId];
  uint8 SeqCount = 0U;
  uint8 DeltaSeqCount = 0U;

  /* get the sequence counter of the Time Domain */
  if(TRUE == IsSync)
  {
#if(CANTSYN_RX_SYNC_USED == STD_ON)
    SeqCount = CanTSyn_SyncSlave[RxPduId].SeqCount;
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */
  }
  else
  {
#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    SeqCount = CanTSyn_OffsetSlave[RxPduId - CANTSYN_NUMBER_OF_SYNC_SLAVES].SeqCount;
#endif /* CANTSYN_RX_OFFSET_USED == STD_ON */
  }


  /* !LINKSTO CanTSyn.SWS_CanTSyn_00079.Startup.NoSCCheck.SYNC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00079.Startup.NoSCCheck.OFS,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00078.TS.IgnoreMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00078.TS.IgnoreMessage0DeltaSC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00078.SYNC.TimeSequenceCounterJumpWidthLimit,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00078.OFS.TimeSequenceCounterJumpWidthLimit,1 */
  /* Omit SC check for the 1'st received message (SeqCount == CANTSYN_SC_STARTUP_TIMEOUT)
     Check if the SC of the 2'nd received message is a valid one (less or equal than Sequence Counter Jump Width) */
  if(SeqCount == CANTSYN_SC_STARTUP_TIMEOUT)
  {
    RetVal = E_OK;
  }
  else
  {
    uint8 timeBaseStatus;
    StbM_TimeBaseStatusType syncTimeBaseStatus = 0U;
    StbM_TimeBaseStatusType offsetTimeBaseStatus = 0U;

    /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
    (void)StbM_GetTimeBaseStatus(CanTSyn_TimeSlaveConfigPtr->SyncTimeBaseId,
                                     &syncTimeBaseStatus, &offsetTimeBaseStatus);
    if(TRUE == IsSync)
    {
      timeBaseStatus = syncTimeBaseStatus;
    }
    else
    {
      timeBaseStatus = offsetTimeBaseStatus;
    }

    DeltaSeqCount = CANTSYN_DELTA_SC(ReceivedSC, SeqCount);

    /* the SC difference between two consecutive SYNC/OFS messages must be greater than zero */
    if(DeltaSeqCount > 0U)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00079.DeltaSC.GreaterThan0.TBUpdate.NoSCCheck.SYNC,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00079.DeltaSC.GreaterThan0.TBUpdate.NoSCCheck.OFS,1 */
      /* if a timeout was reported at StbM level and the difference between the SCs of
         two consecutive SYNC messages is greater than 0, omit the SC check */
      if((timeBaseStatus & CANTSYN_STBM_TIMEOUT) != 0U)
      {
#if(CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON)
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00143,1 */
        /* apply hysteresis only when configured on Time Domain */
        if(CanTSyn_TimeSlaveConfigPtr->TimeScHysteresis != 0U)
        {
          /* The SC successfully validated during timeout only when:
             - CanTSynGlobalTimeSequenceCounterJumpWidth is zero or
             - delta between two consecutive SYNC/OFS frames is greater than CanTSynGlobalTimeSequenceCounterJumpWidth or
             - received message is the first message during timeout */
          if(((CanTSyn_TimeSlaveConfigPtr->ScJumpWidth == 0U) ||
              (DeltaSeqCount <= CanTSyn_TimeSlaveConfigPtr->ScJumpWidth)) ||
              (CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfigPtr->HysteresisIndex] == CanTSyn_TimeSlaveConfigPtr->TimeScHysteresis)
            )
          {
            if(CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfigPtr->HysteresisIndex] != 0U)
            {
              /* decrease the hysteresis counter each time a valid SC was received */
              CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfigPtr->HysteresisIndex]--;
            }
            else
            {
              /* Reset the SC hysteresis if SC Jump Width is not considered */
              CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfigPtr->HysteresisIndex] = CanTSyn_TimeSlaveConfigPtr->TimeScHysteresis - 1U;
            }
          }
          else
          {
            /* Reset the SC hysteresis if SC Jump Width is not considered */
            CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfigPtr->HysteresisIndex] = CanTSyn_TimeSlaveConfigPtr->TimeScHysteresis - 1U;
          }
        }
#endif /* (CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON) */

        RetVal = E_OK;
      }
      else
      {
        /* Skip Sequence Counter Jump Width checks if the configured Sequence Counter Jump Width is equal to zero
           and no STBM timeout was reported */
        if((CanTSyn_TimeSlaveConfigPtr->ScJumpWidth == 0U) || (DeltaSeqCount <= CanTSyn_TimeSlaveConfigPtr->ScJumpWidth))
        {
          RetVal = E_OK;
        }
      }
    }
    else
    {
#if(CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON)
      /* reload the hysteresis counter during timeout, if an invalid SC was received */
      if(((timeBaseStatus & CANTSYN_STBM_TIMEOUT) != 0U) && (CanTSyn_TimeSlaveConfigPtr->TimeScHysteresis != 0U))
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00143,1 */
        CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfigPtr->HysteresisIndex] = CanTSyn_TimeSlaveConfigPtr->TimeScHysteresis;

        RetVal = E_OK;
      }
      else
#endif /* (CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON) */
      {
        if(CanTSyn_TimeSlaveConfigPtr->ScJumpWidth == 0U)
        {
          RetVal = E_OK;
        }
      }
    }
  }

  return RetVal;
}

#if(CANTSYN_RX_SYNC_USED == STD_ON)

#if(CANTSYN_RX_CRC_USED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_SyncMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 seqCounter = DataPtr[2] & CANTSYN_SC_MASK;

/* !LINKSTO CanTSyn.SWS_CanTSyn_00130,1 */
/* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00131,1 */
#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeSlaveConfig[SlavePduId].IsExtendedMessage)
  {
    RetVal = CanTSyn_CheckCRC
        (CanTSyn_TimeSlaveConfig[SlavePduId].SyncOfsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_EXT_LENGTH);
  }
  else
#endif
  {
    /* call CanTSyn_CheckCRC() with a DataID Value based on the current sequence counter (SC) */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00084,1 */
    RetVal = CanTSyn_CheckCRC
        (CanTSyn_TimeSlaveConfig[SlavePduId].SyncOfsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_LENGTH);
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_FupMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 seqCounter = DataPtr[2] & CANTSYN_SC_MASK;

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00130,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00131,1 */
#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeSlaveConfig[SlavePduId].IsExtendedMessage)
  {
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
    if(DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITH_CRC_ICV_AUTH)
    {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00055.CRC.AuthenticatedExtendedMessage,1 */
      RetVal = CanTSyn_CheckCRC
          (CanTSyn_TimeSlaveConfig[SlavePduId].FupOfnsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_LENGTH);
    }
    else
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
    {
      RetVal = CanTSyn_CheckCRC
          (CanTSyn_TimeSlaveConfig[SlavePduId].FupOfnsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_EXT_LENGTH);
    }
  }
  else
#endif /* (CANTSYN_RX_USE_EXTENDED_MSG == STD_ON) */
  {
    /* call CanTSyn_CheckCRC() with a DataID Value based on the current sequence counter (SC) */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00084,1 */
    RetVal = CanTSyn_CheckCRC
        (CanTSyn_TimeSlaveConfig[SlavePduId].FupOfnsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_LENGTH);
  }

  return RetVal;
}
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */

#endif /* CANTSYN_RX_SYNC_USED == STD_ON */


#if(CANTSYN_RX_OFFSET_USED == STD_ON)

#if(CANTSYN_RX_CRC_USED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_OfsMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 seqCounter = DataPtr[2] & CANTSYN_SC_MASK;

/* !LINKSTO CanTSyn.SWS_CanTSyn_00130,1 */
/* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00131,1 */
/* !LINKSTO CanTSyn.SWS_CanTSyn_00065.Valid.NormalOFSMessage,1 */
#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
  if(CanTSyn_TimeSlaveConfig[SlavePduId].IsExtendedMessage)
  {
    RetVal = CanTSyn_CheckCRC
        (CanTSyn_TimeSlaveConfig[SlavePduId].SyncOfsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_EXT_LENGTH);
  }
  else
#endif /* (CANTSYN_RX_USE_EXTENDED_MSG == STD_ON) */
  {
    /* call CanTSyn_CheckCRC() with a DataID Value based on the current sequence counter (SC) */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00084,1 */
    RetVal = CanTSyn_CheckCRC
        (CanTSyn_TimeSlaveConfig[SlavePduId].SyncOfsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_LENGTH);
  }

  return RetVal;
}

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_OfnsMsg_Rx_CRC_Check
(
  uint8 SlavePduId,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 seqCounter = DataPtr[2] & CANTSYN_SC_MASK;

  /* call CanTSyn_CheckCRC() with a DataID Value based on the current sequence counter (SC) */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00084,1 */
  RetVal = CanTSyn_CheckCRC
      (CanTSyn_TimeSlaveConfig[SlavePduId].FupOfnsDataIdListPtr[seqCounter], DataPtr, CANTSYN_CRC_LENGTH);

  return RetVal;
}
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */

#endif /* CANTSYN_RX_OFFSET_USED == STD_ON */


#if(CANTSYN_RX_CRC_USED == STD_ON)

STATIC FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckCRC
(
  uint8 DataID,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 CrcLength
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  uint8 CRCData[CANTSYN_RX_MAX_MSG_LEN - 1U];
  uint8 DataIdPos = CrcLength - 1U;

  /* copy bytes*/

  TS_MemCpy(&CRCData[0], &DataPtr[2], (uint8)(CrcLength - 1U));

  /* add the DataID Value based on the current sequence counter */
  CRCData[DataIdPos] = DataID;

  /* check if the CRC value is valid */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00080,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00057.SYNC.ValidTypeAndCRC,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00060.ValidFUPMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00068.ValidOFNSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00069.ValidOFNSMessage,1 */
  if(DataPtr[1] == Crc_CalculateCRC8H2F(&CRCData[0], CrcLength, CANTSYN_START_VALUE_8H2F, TRUE))
  {
    RetVal = E_OK;
  }

  return RetVal;
}
#endif /* (CANTSYN_RX_CRC_USED == STD_ON) */

#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON) */


#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_IcvCheckState
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId,
  uint8 IcvIndex,
  boolean isFup
)
{
  boolean isIcvAuthMessageType = FALSE;
  uint8 BYTE_FVL = 0U;
  uint8 BYTE_ICVL = 0U;
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
  uint8 BYTE_START_FVL = 0U;
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
  boolean processFrame = FALSE;

  if((CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_NOT_REQUESTED) ||
    (CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_RECOV_ERROR))
  {
    /* newly received message or new attempt at authenticating the message */

    if(isFup == FALSE)
    {
      /* OFS message */
      isIcvAuthMessageType = (((DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH) ||
                             (DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH)) ? TRUE : FALSE);
      BYTE_FVL = CANTSYN_B16_FVL;
      BYTE_ICVL = CANTSYN_B17_ICVL;
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
      BYTE_START_FVL = CANTSYN_B18_FV;
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
    }
    else
    {
      /* FUP message */
      isIcvAuthMessageType = (((DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH) ||
                              (DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITH_CRC_ICV_AUTH)) ? TRUE : FALSE);
      BYTE_FVL = CANTSYN_B8_FVL;
      BYTE_ICVL = CANTSYN_B9_ICVL;
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
      BYTE_START_FVL = CANTSYN_B10_FV;
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
    }

    switch(CanTSyn_TimeSlaveConfig[PduId].IcvVerificationType)
    {
      case CANTSYN_ICV_IGNORED:
      {
        /* do not perform ICV verification; ignore ICV*/
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00180,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00186,1 */
        processFrame = TRUE;
        break;
      }
      case CANTSYN_ICV_NOT_VERIFIED:
      {
        if(isIcvAuthMessageType == TRUE)
        {
          /* ICV verification failed */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00179.FailedVerification,1 */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00185.FailedVerification,1 */

          /* ignore message */
          processFrame = FALSE;
        }
        else
        {
          processFrame = TRUE;
        }
        /* else do nothing */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00179.ICVNotVerified,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00185.ICVNotVerified,1 */
        break;
      }
      case CANTSYN_ICV_OPTIONAL:
      {
        processFrame = TRUE;
        if(isIcvAuthMessageType == TRUE)
        {
          /* verify ICV */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00181.ICVOptional,1 */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00187.ICVOptional,1 */
          CanTSyn_VerifyIcv(DataPtr,
                            PduId,
                            IcvIndex,
                            BYTE_FVL,
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
                            BYTE_START_FVL,
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
                            BYTE_ICVL);
        }
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00181.FUPNoICV,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00187.OFSNoICV,1 */
        break;
      }
      case CANTSYN_ICV_VERIFIED:
      {
        if(isIcvAuthMessageType == TRUE)
        {
          /* verify ICV */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00178.ICVVerified,1 */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00184.ICVVerified,1 */
          CanTSyn_VerifyIcv(DataPtr,
                            PduId,
                            IcvIndex,
                            BYTE_FVL,
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
                            BYTE_START_FVL,
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
                            BYTE_ICVL);

          processFrame = TRUE;
        }
        else
        {
          /* message does not contain ICV; verification is considered as failed; update state */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00178.FailedVerification,1 */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00184.ExtendedOFSNoICV,1 */
          CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_FAILED;

          processFrame = FALSE;
        }
        break;
      }
      /* CHECK: NOPARSE */
      default:
        /* should not happen */
#if(CANTSYN_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
        CANTSYN_UNREACHABLE_CODE_ASSERT(CANTSYN_SID_RXINDICATION);
#endif /* (CANTSYN_UNREACHABLE_CODE_ASSERT_ENABLED) */
        break;
      /* CHECK: PARSE */
    }
  }

  return processFrame;
}
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

STATIC FUNC(void, CANTSYN_CODE) CanTSyn_RxReset
(
  uint8 SlavePduId
)
{

#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
  if(SlavePduId < CANTSYN_NUMBER_OF_SYNC_SLAVES)
  {
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidCRC_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidCRC_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00109.InvalidCRC.SYNCMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00057.SYNC.InvalidCRC,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00110.InvalidCRC.FUPMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00060.InvalidCRC.FUPMessage,1 */
    /* ignore the invalid FUP message (wrong CRC) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */

    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidLENGTH_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidTYPE_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidLENGTH_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidTYPE_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00057.SYNC.InvalidType,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00058.SYNC.InvalidType,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00059.SYNC.InvalidType,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00060.InvalidType.FUPMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00061.InvalidType.FUPMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00062.InvalidType.FUPMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00061.InvalidType.FUPMessage,1 */
    /* ignore the invalid FUP message (wrong type or length) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */

    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidDOMAINID_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidDOMAINID_SyncRXWAIT,1 */
    /* ignore the invalid FUP message (wrong time domain id) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */
    CanTSyn_RxSyncReset(SlavePduId);
  }
  else
  {
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidCRC_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidCRC_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00113.InvalidCRC.OFSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00114.InvalidCRC.OFNSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00065.InvalidCRC.NormalOFSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00068.InvalidCRC.OFNSMessage,1 */
    /* ignore the invalid OFNS message (wrong CRC) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */

    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidLENGTH_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidTYPE_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidLENGTH_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidTYPE_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00065.InvalidType.NormalOFSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00066.InvalidType.NormalOFSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00067.InvalidType.OFSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00068.InvalidType.OFNSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00069.InvalidType.OFNSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00067.InvalidType.OFSMessage,1 */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00070.InvalidType.OFNSMessage,1 */
    /* ignore the invalid OFNS message (wrong type or length) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */

    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidDOMAINID_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidDOMAINID_OfsRXWAIT,1 */
    /* ignore the invalid OFNS message (wrong time domain id) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */
    CanTSyn_RxOffsetReset(SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES);
  }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidCRC_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidCRC_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00109.InvalidCRC.SYNCMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00057.SYNC.InvalidCRC,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00110.InvalidCRC.FUPMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00060.InvalidCRC.FUPMessage,1 */
  /* ignore the invalid FUP message (wrong CRC) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */

  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidLENGTH_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidTYPE_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidLENGTH_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidTYPE_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00057.SYNC.InvalidType,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00058.SYNC.InvalidType,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00059.SYNC.InvalidType,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00060.InvalidType.FUPMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00061.InvalidType.FUPMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00062.InvalidType.FUPMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00061.InvalidType.FUPMessage,1 */
  /* ignore the invalid FUP message (wrong type or length) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */

  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidDOMAINID_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidDOMAINID_SyncRXWAIT,1 */
  /* ignore the invalid FUP message (wrong time domain id) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */
    CanTSyn_RxSyncReset(SlavePduId);

#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidCRC_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidCRC_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00113.InvalidCRC.OFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00114.InvalidCRC.OFNSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00065.InvalidCRC.NormalOFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00068.InvalidCRC.OFNSMessage,1 */
  /* ignore the invalid OFNS message (wrong CRC) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */

  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidLENGTH_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidTYPE_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidLENGTH_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidTYPE_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00065.InvalidType.NormalOFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00066.InvalidType.NormalOFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00067.InvalidType.OFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00068.InvalidType.OFNSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00069.InvalidType.OFNSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00067.InvalidType.OFSMessage,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00070.InvalidType.OFNSMessage,1 */
  /* ignore the invalid OFNS message (wrong type or length) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */

  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidDOMAINID_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidDOMAINID_OfsRXWAIT,1 */
  /* ignore the invalid OFNS message (wrong time domain id) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */
  CanTSyn_RxOffsetReset(SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES);
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */

}
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON)) */



#if(CANTSYN_RX_SYNC_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxSyncFrame
(
  StbM_VirtualLocalTimeType T2VLT,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
)
{
  P2VAR(CanTSyn_SyncSlaveType, AUTOMATIC, CANTSYN_APPL_DATA)
  CanTSyn_SyncSlavePtr = &CanTSyn_SyncSlave[PduId];

  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00144.SetT2VLT,1 */

  /* save T2VLT */
  CanTSyn_SyncSlavePtr->T2VLT = T2VLT;

  /* save the Sequence counter for the FUP message */
  CanTSyn_SyncSlavePtr->SeqCount = CANTSYN_GET_SC_SLAVE(DataPtr[CANTSYN_B2_MSG_DOMAIN]);

  /* save the seconds part of T0 */
  /* disassemble Bytes 4-7 (Big Endian format) */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00144.RetrieveT0,1 */
  CanTSyn_SyncSlavePtr->T0Sec = CANTSYN_GET_TIME_VAL(DataPtr);

  /* save User Data Byte 0 */
  CanTSyn_SyncSlavePtr->UserByte0 = DataPtr[CANTSYN_B3_MSG];

  /* if no CRC used */
  if(DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_SYNC_WITHOUT_CRC)
  {
    /* save User Data Byte 1 */
    CanTSyn_SyncSlavePtr->UserByte1 = DataPtr[CANTSYN_B1_MSG];
  }

  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_SyncRXWAIT-FupRXWAIT,1 */
  /* next message received shall be the FUP message */
  CanTSyn_SyncSlavePtr->RxStatus = CANTSYN_FUPMSG_RX_WAIT;

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
  if((CanTSyn_TimeSlaveConfig[PduId].IcvVerificationType == CANTSYN_ICV_VERIFIED) || (CanTSyn_TimeSlaveConfig[PduId].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
  {
#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_PRECONDITION_ASSERT((CanTSyn_TimeSlaveConfig[PduId].IcvDataStartIndex + CANTSYN_SYNC_PAYLOAD_LENGTH) < CANTSYN_ICV_DATA_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */
    /* copy content of SYNC frame to IcvData array for Icv verification */
    TS_MemCpy(&CanTSyn_IcvData[CanTSyn_TimeSlaveConfig[PduId].IcvDataStartIndex], DataPtr, CANTSYN_SYNC_PAYLOAD_LENGTH);
  }
#endif

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
    SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
    /* reset the timer to the configured timeout */
    CanTSyn_SyncSlave[PduId].SyncPairTimer = CanTSyn_TimeSlaveConfig[PduId].ReceiveSyncPairTimeout;
    SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
#endif

}

STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxFupFrame
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
)
{
  StbM_UserDataType userData;
  StbM_MeasurementType measureData;
  const StbM_SynchronizedTimeBaseType TimeBaseId = CanTSyn_TimeSlaveConfig[PduId].SyncTimeBaseId;
  StbM_TimeStampType globalTime = {0U, 0U, 0U, 0U};
  uint32 T4Nanoseconds = 0U;
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
  uint8 IcvIndex = CanTSyn_SyncSlave[PduId].IcvIndex;
  boolean processContents = FALSE;
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00151,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00115,1 */
  measureData.pathDelay = 0U;

  /* get the nanoseconds portion from the message */
  /* disassemble Bytes 4-7 (Big Endian format) */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00148.RetrieveData,1 */
  T4Nanoseconds = CANTSYN_GET_TIME_VAL(DataPtr);

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)

  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
  processContents = CanTSyn_IcvCheckState(DataPtr, PduId, IcvIndex, TRUE);

  if((CanTSyn_TimeSlaveConfig[PduId].IcvVerificationType == CANTSYN_ICV_OPTIONAL) ||
    (CanTSyn_TimeSlaveConfig[PduId].IcvVerificationType == CANTSYN_ICV_VERIFIED))
  {
    if((CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_VERIFIED) || (CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_NOT_REQUESTED))
    {
      /* frame contents shall only be processed if the message is authenticated successfully or if it is not an authenticated message at all */
      processContents = TRUE;
    }
    else if(CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_FAILED)
    {
      /* message authentication failed or the message contains a wrong ICV */
      processContents = FALSE;

#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
  #ifdef CANTSYN_SEV_ICV_VERIFICATION_FAILED
      /* authentication failure must be reported to IdsM */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00193.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00200.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
      IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_ICV_VERIFICATION_FAILED, &CanTSyn_TimeSlaveConfig[PduId].TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_ICV_VERIFICATION_FAILED */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON) */

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      /* drop frame */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00206,1 */
      CanTSyn_SyncFupDropped(PduId, CANTSYN_SID_RXINDICATION);
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
      /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Failed_NotRequested,1 */
      /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_FailedIcvAuth_SyncRXWAIT,1 */
      CanTSyn_RxSyncReset(PduId);
    }
    else
    {
      processContents = FALSE;
      /* recoverable error or asynchronous verification */
    }
  }
  /* check ICV support type */


  if(processContents == TRUE)
#endif
  {
    /* SWS_CanTSyn_00086 - 5 : check if the nanoseconds part matches the defined range.
     * See the bug fix ticket [ASCCANTSYN-86]. */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
    if(T4Nanoseconds <= CANTSYN_NANOSEC_MAX)
    {
#if(CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON)
      if(0U == CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfig[PduId].HysteresisIndex])
      {
#else
      {
#endif /* (CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON) */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00148.RetrieveData,1 */
        uint8 SecondsOVS = DataPtr[CANTSYN_B3_MSG] & CANTSYN_OVS_MASK;
        StbM_VirtualLocalTimeType T2VLT = CanTSyn_SyncSlave[PduId].T2VLT;
        /* T3diff + SyncTimeNSec */

        globalTime.nanoseconds = T4Nanoseconds;
        /* set the user data */
        userData.userByte0 = CanTSyn_SyncSlave[PduId].UserByte0;

        /* if no CRC used */
        if((DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITHOUT_CRC) || (DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH))
        {
          /* save User Data Byte 1 and User Data Byte 2 */
          userData.userByte1 = CanTSyn_SyncSlave[PduId].UserByte1;
          userData.userByte2 = DataPtr[CANTSYN_B1_MSG];
          /* no CRC configured for SYNC and FUP messages */
          userData.userDataLength = 3U;
        }
        else
        {
          /* only userByte0 available */
          userData.userDataLength = 1U;
        }

        /* store the received T0 seconds value */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00148.CalculateTLSYNC,1 */
        globalTime.seconds = CanTSyn_SyncSlave[PduId].T0Sec;

        /* !LINKSTO CanTSyn.SWS_CanTSyn_00075,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00148.ComputeT4,1 */
        /* T0 + OVS + SyncTimeSec */
        /* Check if the received seconds portion is in range */
        if((CANTSYN_MAX_32BIT_VALUE - globalTime.seconds) < SecondsOVS)
        {
          /* Adjust seconds to prevent an overflow and increment secondsHi in order to mark
           * the adjustment */
          globalTime.seconds = globalTime.seconds - (CANTSYN_MAX_32BIT_VALUE - SecondsOVS) - 1U;
          globalTime.secondsHi++;
        }
        else
        {
          globalTime.seconds = globalTime.seconds + SecondsOVS;
        }

        /* check if the SGW bit */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00133.SyncToSubDomain.SGW,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00133.SyncToGTM.SGW,1 */
        if((DataPtr[CANTSYN_B3_MSG] & CANTSYN_SGW_MASK) != 0U)
        {
          globalTime.timeBaseStatus |= CANTSYN_SYNC_TO_GATEWAY_MASK;
        }

        /* set the global time */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00064,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.ForwardGlobalTime,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00148.ForwardRxTimeTuple,1 */
        (void)StbM_BusSetGlobalTime(TimeBaseId, &globalTime, &userData, &measureData, &T2VLT);
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00137,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00138,1 */
#if (CANTSYN_SLAVE_TIME_DOMAIN_VALIDATION_SUPPORT == STD_ON)
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00139,1 */
        if(TRUE == CanTSyn_TimeSlaveConfig[PduId].IsTimeValidationUsed)
        {
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00140.UnusedData,1 */
          StbM_CanTimeSlaveMeasurementType SlaveMeasureData = {0U, {0U ,0U}, {0U, 0U}, {0U, 0U}, {0U, 0U}, 0U};
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00140.SequenceCounter,1 */
          SlaveMeasureData.sequenceCounter = (uint16)CanTSyn_SyncSlave[PduId].SeqCount;
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00140.syncIngressTimestamp,1 */
          SlaveMeasureData.syncIngressTimestamp = T2VLT;
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00140.preciseOriginTimestamp,1 */
          SlaveMeasureData.preciseOriginTimestamp.nanoseconds = T4Nanoseconds;
          SlaveMeasureData.preciseOriginTimestamp.seconds = (CanTSyn_SyncSlave[PduId].T0Sec) + SecondsOVS;
          /* !LINKSTO CanTSyn.SWS_CanTSyn_00140.segmentId,1 */
          SlaveMeasureData.segmentId=CanTSyn_TimeSlaveConfig[PduId].NetworkSegmentId;

          /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
          (void)StbM_CanSetSlaveTimingData(TimeBaseId, &SlaveMeasureData);
        }
#endif /* CANTSYN_SLAVE_TIME_DOMAIN_VALIDATION_SUPPORT */

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
        SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
        /* reset the timer to the configured timeout */
        CanTSyn_SyncSlave[PduId].SyncPairTimer = CanTSyn_TimeSlaveConfig[PduId].ReceiveSyncPairTimeout;
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
        /* reset the number of failed frames */
        CanTSyn_SyncSlave[PduId].SyncPairsDroppedCnt = 0U;
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET) */
        SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
        if (CANTSYN_E_DEM_SYNC_FAILED(PduId) < 0xFFFFU)
        {
          /* !LINKSTO CanTSyn.EB.Diagnostic_SyncOK_DEM,1 */
          /* report to DEM a successful frame for healing */
          Dem_ReportErrorStatus
          (
              CANTSYN_E_DEM_SYNC_FAILED(PduId),
              DEM_EVENT_STATUS_PREPASSED
           );
        }
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM) */
      }
    }
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE == STD_ON)
    else
    {
      /* nanosecond part failed, report frame to DEM/DET */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_ExceededNanosecondsRange,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_ExceededNanosecondsRange,1 */
      CanTSyn_SyncFupDropped(PduId, CANTSYN_SID_RXINDICATION);
    }
#endif /* (CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

    /* ignore the invalid FUP message (nanoseconds above the defined range) and reset the SYNC RxStatus and clear all variables for a new SYNC-FUP reception
       or reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception, after a successful reception of a SYNC-FUP sequence */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_NsAboveDefinedRange_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_NsAboveDefinedRange_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_FailedIcvAuth_SyncRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Verified_NotRequested,1 */
    CanTSyn_RxSyncReset(PduId);
  }

}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_RxSyncReset
(
  uint8 CanTSyn_SlavePduActiveIndex
)
{
  P2VAR(CanTSyn_SyncSlaveType, AUTOMATIC, CANTSYN_APPL_DATA)
          CanTSyn_SyncSlavePtr = &CanTSyn_SyncSlave[CanTSyn_SlavePduActiveIndex];

  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_Init,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_SyncRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_SyncRXWAIT,1 */
  /* first message awaited to be received is the SYNC message */
  CanTSyn_SyncSlavePtr->RxStatus = CANTSYN_SYNCMSG_RX_WAIT;

  /* Clear the Follow Up Offset Timeout */
  CanTSyn_SyncSlavePtr->TimeRxFollowUpOffset = 0U;

  CanTSyn_SyncSlavePtr->T0Sec = 0U;

  /* clear user data */
  CanTSyn_SyncSlavePtr->UserByte0 = 0U;
  CanTSyn_SyncSlavePtr->UserByte1 = 0U;

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED)
  if((CanTSyn_TimeSlaveConfig[CanTSyn_SlavePduActiveIndex].IcvVerificationType == CANTSYN_ICV_VERIFIED) || (CanTSyn_TimeSlaveConfig[CanTSyn_SlavePduActiveIndex].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
  {
    /* reset the ICV authentication state machine */
    CanTSyn_IcvSlave[CanTSyn_SyncSlavePtr->IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_NOT_REQUESTED;

    CanTSyn_IcvSlave[CanTSyn_SyncSlavePtr->IcvIndex].IcvVerificationAttempts = 0U;
  }
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED) */
}
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */


#if(CANTSYN_RX_OFFSET_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_RxOffsetReset
(
  uint8 CanTSyn_SlavePduActiveIndex
)
{
  P2VAR(CanTSyn_OffsetSlaveType, AUTOMATIC, CANTSYN_APPL_DATA)
          CanTSyn_OffsetSlavePtr = &CanTSyn_OffsetSlave[CanTSyn_SlavePduActiveIndex];

  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_Init,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsExtended.CanTSynRxStatus_OfsRXWAIT_OfsRXWAIT,1 */
  /* first message awaited to be received is the SYNC message */
  CanTSyn_OffsetSlavePtr->RxStatus = CANTSYN_OFSMSG_RX_WAIT;

  /* Clear the Follow Up Offset Timeout */
  CanTSyn_OffsetSlavePtr->TimeRxFollowUpOffset = 0U;

  /* Clear the Seconds portion */
  CanTSyn_OffsetSlavePtr->OfsSecLo = 0U;

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED)
  if((CanTSyn_TimeSlaveConfig[CanTSyn_SlavePduActiveIndex].IcvVerificationType == CANTSYN_ICV_VERIFIED) ||
     (CanTSyn_TimeSlaveConfig[CanTSyn_SlavePduActiveIndex].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
  {
    /* reset the ICV authentication state machine */
    CanTSyn_IcvSlave[CanTSyn_OffsetSlavePtr->IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_NOT_REQUESTED;

    CanTSyn_IcvSlave[CanTSyn_OffsetSlavePtr->IcvIndex].IcvVerificationAttempts = 0U;
  }
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED) */

}

#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessExtRxOfsFrame
(
  StbM_VirtualLocalTimeType T_VLT,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
)
{
  StbM_TimeStampType timeStamp = {0U, 0U, 0U, 0U};
  StbM_UserDataType userData;
  StbM_MeasurementType measureData;

  P2VAR(CanTSyn_OffsetSlaveType, AUTOMATIC, CANTSYN_APPL_DATA)
          CanTSyn_OffsetSlavePtr = &CanTSyn_OffsetSlave[PduId];
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
  uint8 IcvIndex = CanTSyn_OffsetSlave[PduId].IcvIndex;
  boolean processContents = FALSE;
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
  /* check ICV support type */

  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
  processContents = CanTSyn_IcvCheckState(DataPtr, PduId + CANTSYN_NUMBER_OF_SYNC_SLAVES, IcvIndex, FALSE);

  if((CanTSyn_TimeSlaveConfig[PduId + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_OPTIONAL) ||
    (CanTSyn_TimeSlaveConfig[PduId + CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvVerificationType == CANTSYN_ICV_VERIFIED))
  {
    if((CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_VERIFIED) || (CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_NOT_REQUESTED))
    {
      /* frame contents shall only be processed if the message is authenticated successfully or if it is not an authenticated message at all */
      processContents = TRUE;
    }
    else if(CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_FAILED)
    {
      /* message authentication failed or the message contains a wrong ICV */
      processContents = FALSE;


#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
  #ifdef CANTSYN_SEV_ICV_VERIFICATION_FAILED
      /* authentication failure must be reported to IdsM */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00193.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00200.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
      IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_ICV_VERIFICATION_FAILED, &CanTSyn_TimeSlaveConfig[PduId + CANTSYN_NUMBER_OF_SYNC_SLAVES].TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_ICV_VERIFICATION_FAILED */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON) */

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      /* drop frame */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00206,1 */
      CanTSyn_OfsOfnsDropped(PduId, CANTSYN_SID_RXINDICATION);
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
      /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Failed_NotRequested,1 */
      /* !LINKSTO CanTSyn.Dsn.OfsExtended.CanTSynRxStatus_OfsRXWAIT_FailedIcvAuth_OfsRXWAIT,1 */
      CanTSyn_RxOffsetReset(PduId);
    }
    else
    {
      /* recoverable error or asynchronous verification */
      CanTSyn_IcvSlave[PduId].T5VLT = T_VLT;
      processContents = FALSE;
    }
  }

  if(processContents == TRUE)
#endif
  {
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00116,1 */
    measureData.pathDelay = 0U;

    /* get the nanoseconds portion from the message */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00074,1 */
    /* disassemble Bytes 4-7 (Big Endian format) */
    /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
    timeStamp.nanoseconds = CANTSYN_GET_EXT_NANO_TIME_VAL(DataPtr);

    /* save the Sequence counter for the FUP message */
    CanTSyn_OffsetSlavePtr->SeqCount = CANTSYN_GET_SC_SLAVE(DataPtr[CANTSYN_B2_MSG_DOMAIN]);

    /* SWS_CanTSyn_00086 - 5 : check if the nanoseconds part matches the defined range */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
    if(timeStamp.nanoseconds <= CANTSYN_NANOSEC_MAX)
    {
      timeStamp.seconds = CANTSYN_GET_EXT_TIME_VAL(DataPtr);

      /* if no CRC used */
      if((DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_EXT_MSG_WITHOUT_CRC) || (DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH))
      {
        /* save userByte2 from Byte1 */
        userData.userByte2 = DataPtr[1];
        userData.userDataLength = 3U;
      }
      else
      {
        userData.userDataLength = 2U;
      }

      userData.userByte0 = DataPtr[4];
      userData.userByte1 = DataPtr[5];

      if((DataPtr[CANTSYN_B3_MSG] & CANTSYN_SGW_MASK) != 0U)
      {
        timeStamp.timeBaseStatus |= CANTSYN_SYNC_TO_GATEWAY_MASK;
      }

      /* set the global time */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00072.StbM.ExtendedMessage,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00116,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.ForwardGlobalTime,1 */
      (void)StbM_BusSetGlobalTime(CanTSyn_TimeSlaveConfig[PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES].SyncTimeBaseId, &timeStamp, &userData, &measureData, &T_VLT);

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
      /* reset the timer to the configured timeout */
      CanTSyn_OffsetSlave[PduId].OfsPairTimer = CanTSyn_TimeSlaveConfig[PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES].ReceiveSyncPairTimeout;
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
      /* reset the number of failed frames */
      CanTSyn_OffsetSlave[PduId].OfsPairsDroppedCnt = 0U;
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET) */
      SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
      if (CANTSYN_E_DEM_SYNC_FAILED(PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES) < 0xFFFFU)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsOK_DEM,1 */
        /* report to DEM a successful frame for healing */
        Dem_ReportErrorStatus
        (
            CANTSYN_E_DEM_SYNC_FAILED(PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES),
            DEM_EVENT_STATUS_PREPASSED
         );
      }
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM) */
    }
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE == STD_ON)
    else
    {
      /* nanosecond part failed, report frame to DEM/DET */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_ExceededNanosecondsRange,1 */
      /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_ExceededNanosecondsRange,1 */
      CanTSyn_OfsOfnsDropped(PduId, CANTSYN_SID_RXINDICATION);
    }
#endif /* (CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

    /* ignore the invalid Extended OFS message (nanoseconds above the defined range) and reset the OFS RxStatus and clear all variables for a new Extended OFS reception
       or reset the OFS RxStatus and clear all the variables for a new Extended OFS reception, after a successful reception of an Extended OFS */
    /* !LINKSTO CanTSyn.Dsn.OfsExtended.CanTSynRxStatus_OfsRXWAIT_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsExtended.CanTSynRxStatus_OfsRXWAIT_NsAboveDefinedRange_OfsRXWAIT,1 */
    /* !LINKSTO CanTSyn.Dsn.OfsExtended.CanTSynRxStatus_OfsRXWAIT_FailedIcvAuth_OfsRXWAIT,1 */
    CanTSyn_RxOffsetReset(PduId);
  }

}
#endif /* (CANTSYN_RX_USE_EXTENDED_MSG == STD_ON) */


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxOfsFrame
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
)
{
  P2VAR(CanTSyn_OffsetSlaveType, AUTOMATIC, CANTSYN_APPL_DATA)
          CanTSyn_OffsetSlavePtr = &CanTSyn_OffsetSlave[PduId];

  /* save the Sequence counter for the FUP message */
  CanTSyn_OffsetSlavePtr->SeqCount = CANTSYN_GET_SC_SLAVE(DataPtr[CANTSYN_B2_MSG_DOMAIN]);

  /* save the seconds part */
  /* disassemble Bytes 4-7 (Big Endian format) */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00074,1 */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  CanTSyn_OffsetSlavePtr->OfsSecLo = CANTSYN_GET_TIME_VAL(DataPtr);

  /* if no CRC used */
  if(DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_WITHOUT_CRC)
  {
    /* save userByte1 from Byte1 and userByte0 from Byte3 */
    CanTSyn_OffsetSlavePtr->UserByte1 = DataPtr[1];
    CanTSyn_OffsetSlavePtr->UserByte0 = DataPtr[3];
  }
  else
  {
    /* save userByte0 from Byte3 */
    CanTSyn_OffsetSlavePtr->UserByte0 = DataPtr[3];
  }

  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfsRXWAIT-OfnsRXWAIT,1 */
  /* next message received shall be the OFNS message */
  CanTSyn_OffsetSlavePtr->RxStatus = CANTSYN_OFNSMSG_RX_WAIT;

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
    SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
    /* reset the timer to the configured timeout */
    CanTSyn_OffsetSlave[PduId].OfsPairTimer = CanTSyn_TimeSlaveConfig[PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES].ReceiveSyncPairTimeout;
    SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
#endif

}

#if (CANTSYN_OFNS_FRAME_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxOfnsFrame
(
  StbM_VirtualLocalTimeType T_VLT,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId
)
{
  StbM_TimeStampType timeStamp = {0U, 0U, 0U, 0U};
  StbM_UserDataType userData;
  StbM_MeasurementType measureData;

  /* !LINKSTO CanTSyn.SWS_CanTSyn_00116,1 */
  measureData.pathDelay = 0U;

  /* get the nanoseconds portion from the message */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00074,1 */
  /* disassemble Bytes 4-7 (Big Endian format) */
  /* !LINKSTO CanTSyn.SWS_CanTSyn_00008,1 */
  timeStamp.nanoseconds = CANTSYN_GET_TIME_VAL(DataPtr);

  /* SWS_CanTSyn_00086 - 5 : check if the nanoseconds part matches the defined range */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
  if(timeStamp.nanoseconds <= CANTSYN_NANOSEC_MAX)
  {
#if(CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON)
    if(0U == CanTSyn_HysteresisArray[CanTSyn_TimeSlaveConfig[PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES].HysteresisIndex])
    {
#else
    {
#endif /* (CANTSYN_RX_SC_HYSTERESIS_USED == STD_ON) */
      timeStamp.seconds = CanTSyn_OffsetSlave[PduId].OfsSecLo;

      /* set the User Data Byte 0 from received OFS frame */
      userData.userByte0 = CanTSyn_OffsetSlave[PduId].UserByte0;

      /* if no CRC used */
      if(DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFNS_WITHOUT_CRC)
      {
        /* save User Data Byte 1 and User Data Byte 2 from OFNS frame */
        userData.userByte1 = CanTSyn_OffsetSlave[PduId].UserByte1;
        userData.userByte2 = DataPtr[CANTSYN_B1_MSG];
        /* no CRC configured for SYNC and FUP messages */
        userData.userDataLength = 3U;
      }
      else
      {
        /* only userByte0 is available */
        userData.userDataLength = 1U;
      }

      /* check if the SGW bit is set */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00133.SyncToSubDomain.SGW,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00133.SyncToGTM.SGW,1 */
      if((DataPtr[CANTSYN_B3_MSG] & CANTSYN_SGW_MASK) != 0U)
      {
        timeStamp.timeBaseStatus |= CANTSYN_SYNC_TO_GATEWAY_MASK;
      }

      /* set the global time */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00072.StbM.NormalMessage,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00116,1 */
      /* !LINKSTO CanTSyn.SWS_CanTSyn_00135,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.ForwardGlobalTime,1 */
      (void)StbM_BusSetGlobalTime(CanTSyn_TimeSlaveConfig[PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES].SyncTimeBaseId, &timeStamp, &userData, &measureData, &T_VLT);

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
      /* reset the timer to the configured timeout */
      CanTSyn_OffsetSlave[PduId].OfsPairTimer = CanTSyn_TimeSlaveConfig[PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES].ReceiveSyncPairTimeout;
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
      /* reset the number of failed frames */
      CanTSyn_OffsetSlave[PduId].OfsPairsDroppedCnt = 0U;
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET) */
      SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
      if (CANTSYN_E_DEM_SYNC_FAILED(PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES) < 0xFFFFU)
      {
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsOK_DEM,1 */
        /* report to DEM a successful frame for healing */
        Dem_ReportErrorStatus
        (
            CANTSYN_E_DEM_SYNC_FAILED(PduId+CANTSYN_NUMBER_OF_SYNC_SLAVES),
            DEM_EVENT_STATUS_PREPASSED
         );
      }
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM) */
    }
  }
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE == STD_ON)
  else
  {
    /* nanosecond part failed, report frame to DEM/DET */
    /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_ExceededNanosecondsRange,1 */
    /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_ExceededNanosecondsRange,1 */
    CanTSyn_OfsOfnsDropped(PduId, CANTSYN_SID_RXINDICATION);
  }
#endif /* (CANTSYN_REPORT_EXCEEDED_NANOSECONDS_RANGE == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */

  /* ignore the invalid OFNS message (nanoseconds above the defined range) and reset the OFS RxStatus and clear all variables for a new OFS-OFNS reception
   or reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception, after a successful reception of a OFS-OFNS sequence */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_NsAboveDefinedRange_OfsRXWAIT,1 */
  /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_NsAboveDefinedRange_OfsRXWAIT,1 */
  CanTSyn_RxOffsetReset(PduId);
}
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */



#if((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON))
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_ProcessRxFrame
(
  uint8 SlavePduId,
  uint8 RxStatus,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  StbM_VirtualLocalTimeType T_VLT,
  PduLengthType messageLength
)
{
  const uint8 receivedSequenceCounter = DataPtr[2U] & CANTSYN_SC_MASK;
#if(CANTSYN_RX_OFFSET_USED == STD_ON)
  uint8 OffsetRxPduId = SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES;
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
#if (CANTSYN_RX_SYNC_USED == STD_ON)
  boolean processFrame = TRUE;
#endif /* (CANTSYN_RX_SYNC_USED == STD_ON) */
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

#if((CANTSYN_RX_USE_EXTENDED_MSG == STD_OFF) || (CANTSYN_RX_OFFSET_USED == STD_OFF))
   TS_PARAM_UNUSED(messageLength);
#endif

  switch(RxStatus)
  {
#if(CANTSYN_RX_SYNC_USED == STD_ON)
    case CANTSYN_FUPMSG_RX_WAIT:
    case CANTSYN_FUPMSG_RX_WAIT_TIMEOUT:
    {
      CanTSyn_SyncSlave[SlavePduId].RxStatus = CANTSYN_FUPMSG_RX_WAIT_TIMEOUT;

      /* check if the Sequence Counter is received with the same value like for the SYNC message */
      if(receivedSequenceCounter == CanTSyn_SyncSlave[SlavePduId].SeqCount)
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00061.ValidFUPMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00076.SYNCMatchFUP.SC,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00062.ValidFUPMessage,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.DissasembleMessage,1 */
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
        if((CanTSyn_TimeSlaveConfig[SlavePduId].IcvVerificationType == CANTSYN_ICV_VERIFIED) || (CanTSyn_TimeSlaveConfig[SlavePduId].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
        {
          /* if IcvVerificationState is not CANTSYN_ICV_STATE_NOT_REQUESTED it means that
             Fup message was already received and Icv verification is in progress */
          if(CanTSyn_IcvSlave[CanTSyn_SyncSlave[SlavePduId].IcvIndex].IcvVerificationState != CANTSYN_ICV_STATE_NOT_REQUESTED)
          {
            processFrame = FALSE;
          }
        }
        if(processFrame == TRUE)
#endif /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
        {
          CanTSyn_ProcessRxFupFrame(DataPtr, SlavePduId);
        }
      }
      else
      {
        /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAIT_InvalidSC_SyncRXWAIT,1 */
        /* !LINKSTO CanTSyn.Dsn.SyncFup.CanTSynRxStatus_FupRXWAITTIMEOUT_InvalidSC_SyncRXWAIT,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00110.InvalidSC.FUPMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00060.InvalidSC.FUPMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00061.InvalidSC.FUPMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00062.InvalidSC.FUPMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00076.NoMatchSYNC_FUP.SC,1 */
        /* ignore the invalid FUP message (wrong SC) and reset the SYNC RxStatus and clear all the variables for a new SYNC-FUP reception */
        CanTSyn_RxSyncReset(SlavePduId);

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_SC == STD_ON)
        /* sequence counter failed, report frame to DEM/DET */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongSC,1 */
        CanTSyn_SyncFupDropped(SlavePduId, CANTSYN_SID_RXINDICATION);
#endif /* (CANTSYN_REPORT_WRONG_SC == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
      }
    }
    break;

#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    case CANTSYN_SYNCMSG_RX_WAIT:
#else
    default:
     /* CANTSYN_SYNCMSG_RX_WAIT */
#endif /* CANTSYN_RX_OFFSET_USED == STD_ON */
    {
      /* check if the received Sequence Counter shall be accepted */
      if (E_OK == CanTSyn_CheckSequenceCounter(SlavePduId, receivedSequenceCounter, TRUE))
      {
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.DissasembleMessage,1 */
        CanTSyn_ProcessRxSyncFrame(T_VLT, DataPtr, SlavePduId);
      }
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_SC == STD_ON)
      else
      {
        /* sequence counter failed, report frame to DEM/DET */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DEM_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_SyncFailed_DET_WrongSC,1 */
        CanTSyn_SyncFupDropped(SlavePduId, CANTSYN_SID_RXINDICATION);
      }
#endif /* (CANTSYN_REPORT_WRONG_SC == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
    }
    break;
#endif /* CANTSYN_RX_SYNC_USED == STD_ON */



#if(CANTSYN_RX_OFFSET_USED == STD_ON)
    case CANTSYN_OFNSMSG_RX_WAIT:
    case CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT:
    {
#if(CANTSYN_OFNS_FRAME_USED == STD_ON)
      CanTSyn_OffsetSlave[OffsetRxPduId].RxStatus = CANTSYN_OFNSMSG_RX_WAIT_TIMEOUT;

      /* check if the Sequence Counter is received with the same value like for the OFS message */
      if(receivedSequenceCounter == CanTSyn_OffsetSlave[OffsetRxPduId].SeqCount)
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00077.OFSMatchOFNS.SC,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.DissasembleMessage,1 */
        CanTSyn_ProcessRxOfnsFrame(T_VLT, DataPtr, OffsetRxPduId);
      }
      else
      {
        /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAIT_InvalidSC_OfsRXWAIT,1 */
        /* !LINKSTO CanTSyn.Dsn.OfsOfns.CanTSynRxStatus_OfnsRXWAITTIMEOUT_InvalidSC_OfsRXWAIT,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00077.NoMatchOFS_OFNS.SC,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00114.InvalidSC.OFNSMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00068.InvalidSC.OFNSMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00069.InvalidSC.OFNSMessage,1 */
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00070.InvalidSC.OFNSMessage,1 */
        /* ignore the invalid OFNS message (wrong SC) and reset the OFS RxStatus and clear all the variables for a new OFS-OFNS reception */
          CanTSyn_RxOffsetReset(SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES);

#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_SC == STD_ON)
        /* sequence counter failed, report frame to DEM/DET */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongSC,1 */
        CanTSyn_OfsOfnsDropped((SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
#endif /* (CANTSYN_REPORT_WRONG_SC == STD_ON) */
#endif
      }
#endif /* (CANTSYN_OFNS_FRAME_USED == STD_ON) */
    }
    break;

    default:
      /* CANTSYN_OFSMSG_RX_WAIT */
    {
      /* check if the received Sequence Counter shall be accepted */
      if(E_OK == CanTSyn_CheckSequenceCounter(SlavePduId, receivedSequenceCounter, FALSE))
      {
        /* !LINKSTO CanTSyn.SWS_CanTSyn_00130,1 */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00131,1 */
#if(CANTSYN_RX_USE_EXTENDED_MSG == STD_ON)
#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
        if(messageLength >= CANTSYN_EXTENDED_MSG_SIZE)
#else /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
        if(messageLength == CANTSYN_EXTENDED_MSG_SIZE)
#endif  /* (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */
        {
          CanTSyn_ProcessExtRxOfsFrame(T_VLT, DataPtr, OffsetRxPduId);
        }
        else
#endif /* (CANTSYN_RX_USE_EXTENDED_MSG == STD_ON) */
        {
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00086,1 */
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00087.DissasembleMessage,1 */
          CanTSyn_ProcessRxOfsFrame(DataPtr, OffsetRxPduId);
        }
      }
#if (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
#if(CANTSYN_REPORT_WRONG_SC == STD_ON)
      else
      {
        /* sequence counter failed, report frame to DEM/DET */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DEM_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_OfsFailed_DET_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DEM_WrongSC,1 */
        /* !LINKSTO CanTSyn.EB.Diagnostic_ExtOfsFailed_DET_WrongSC,1 */
        CanTSyn_OfsOfnsDropped((SlavePduId - CANTSYN_NUMBER_OF_SYNC_SLAVES), CANTSYN_SID_RXINDICATION);
      }
#endif /* (CANTSYN_REPORT_WRONG_SC == STD_ON) */
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
    }
    break;
#endif /* (CANTSYN_RX_OFFSET_USED == STD_ON) */
  }

}
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) || (CANTSYN_RX_OFFSET_USED == STD_ON)) */


#if((CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (CANTSYN_RX_SYNC_USED == STD_ON))
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_SyncFupDropped
(
  uint8 rxPduId,
  uint8 apiId
)
{
  P2CONST(CanTSyn_TimeSlaveDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) SlaveConfigPtr = &CanTSyn_TimeSlaveConfig[rxPduId];
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
  boolean callDet = FALSE;
#endif

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
  if (CANTSYN_E_DEM_SYNC_FAILED(rxPduId) < 0xFFFFU)
  {
    SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
    /* Reload the value of accepted waiting timeout */
    CanTSyn_SyncSlave[rxPduId].SyncPairTimer = SlaveConfigPtr->ReceiveSyncPairTimeout;
    SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

    Dem_ReportErrorStatus
    (
      CANTSYN_E_DEM_SYNC_FAILED(rxPduId),
      DEM_EVENT_STATUS_PREFAILED
     );
  }
  TS_PARAM_UNUSED(apiId);
#elif(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
  /* Reload the value of accepted waiting timeout */
  CanTSyn_SyncSlave[rxPduId].SyncPairTimer = SlaveConfigPtr->ReceiveSyncPairTimeout;

  /* increase the number of failed frames and check if the max number is reached */
  CanTSyn_SyncSlave[rxPduId].SyncPairsDroppedCnt++;
  if(CanTSyn_SyncSlave[rxPduId].SyncPairsDroppedCnt >= CANTSYN_MAX_DROPPED_SYNC_PAIRS)
  {
    CanTSyn_SyncSlave[rxPduId].SyncPairsDroppedCnt = CANTSYN_MAX_DROPPED_SYNC_PAIRS;
    callDet = TRUE;
  }
  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  /* increase the number of failed frames and check if the max number is reached */
  if(callDet == TRUE)
  {
    CANTSYN_DET_REPORT_ERROR
    (
        apiId,
        CANTSYN_E_DET_SYNC_FAILED
    );
  }
#endif /* (CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM) */
}

STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_ProcessSyncTimeout
(
  CanTSyn_SyncSlaveType * syncPtr
)
{
  uint16 syncPairTimerLcl;
  boolean timerExpired = FALSE;

  syncPairTimerLcl = syncPtr->SyncPairTimer;

  /* check if timer is greater than 0 (it was set during reception of a frame to replace the initial value of 0) */
  if (syncPairTimerLcl > 0U)
  {
    /* decrement the timer and check if it reaches 0 */
    syncPairTimerLcl--;
    if (syncPairTimerLcl == 0U)
    {
      timerExpired = TRUE;
    }
    else
    {
      syncPtr->SyncPairTimer = syncPairTimerLcl;
    }
  }
  return timerExpired;
}
#endif /* ((CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (CANTSYN_RX_SYNC_USED == STD_ON)) */

#if((CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (CANTSYN_RX_OFFSET_USED == STD_ON))
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_OfsOfnsDropped
(
  uint8 rxPduId,
  uint8 apiId
)
{
  P2CONST(CanTSyn_TimeSlaveDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) SlaveConfigPtr = &CanTSyn_TimeSlaveConfig[rxPduId+CANTSYN_NUMBER_OF_SYNC_SLAVES];
#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
  boolean callDet = FALSE;
#endif

#if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
  if (CANTSYN_E_DEM_SYNC_FAILED(rxPduId+CANTSYN_NUMBER_OF_SYNC_SLAVES) < 0xFFFFU)
  {
    SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
    /* Reload the value of accepted waiting timeout */
    CanTSyn_OffsetSlave[rxPduId].OfsPairTimer = SlaveConfigPtr->ReceiveSyncPairTimeout;
    SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

    Dem_ReportErrorStatus
    (
      CANTSYN_E_DEM_SYNC_FAILED(rxPduId+CANTSYN_NUMBER_OF_SYNC_SLAVES),
      DEM_EVENT_STATUS_PREFAILED
     );
  }
  TS_PARAM_UNUSED(apiId);
#elif(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
  SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();
  /* Reload the value of accepted waiting timeout */
  CanTSyn_OffsetSlave[rxPduId].OfsPairTimer = SlaveConfigPtr->ReceiveSyncPairTimeout;

  /* increase the number of failed frames and check if the max number is reached */
  CanTSyn_OffsetSlave[rxPduId].OfsPairsDroppedCnt++;
  if(CanTSyn_OffsetSlave[rxPduId].OfsPairsDroppedCnt >= CANTSYN_MAX_DROPPED_SYNC_PAIRS)
  {
    CanTSyn_OffsetSlave[rxPduId].OfsPairsDroppedCnt = CANTSYN_MAX_DROPPED_SYNC_PAIRS;
    callDet = TRUE;
  }
  SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

  if(callDet == TRUE)
  {
    CANTSYN_DET_REPORT_ERROR
    (
        apiId,
        CANTSYN_E_DET_SYNC_FAILED
    );
  }
#endif /* #if(CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM) */
}

STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_ProcessOfsTimeout
(
  CanTSyn_OffsetSlaveType * ofsPtr
)
{
  uint16 ofsPairTimerLcl;
  boolean timerExpired = FALSE;

  ofsPairTimerLcl = ofsPtr->OfsPairTimer;

  /* check if timer is greater than 0 (it was set during reception of a frame to replace the initial value of 0) */
  if (ofsPairTimerLcl > 0U)
  {
    /* decrement the timer and check if it reaches 0 */
    ofsPairTimerLcl--;
    if (ofsPairTimerLcl == 0U)
    {
      timerExpired = TRUE;
    }
    else
    {
      ofsPtr->OfsPairTimer = ofsPairTimerLcl;
    }
  }
  return timerExpired;
}
#endif /* ((CANTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */

#if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON)

/* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_91002.Signature,1 */
/* Deviation MISRAC2012-3 */

/* Tresos 8 API */
FUNC(void, CANTSYN_CODE) CanTSyn_IcvGenerationIndication
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  Std_ReturnType result
)
{
  uint8 PduIdx;
  uint8 IcvIndex;
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  boolean validId = FALSE;
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvMasterPtr;

  if(job == NULL_PTR)
  {
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
    validId = TRUE; /* to prevent CANTSYN_E_PARAM reporting */
    /* !LINKSTO CanTSyn.EB.Check.Tx.IcvGenerationIndication.JobId.NullPtr,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_ICVGENERATIONINDICATION, CANTSYN_E_NULL_POINTER);
#endif /* (CANTSYN_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
    /* Deviation TASKING-1 */
    for(PduIdx = 0U;
        PduIdx < CANTSYN_NUMBER_OF_MASTERS;
        PduIdx++ )
    {
      if(CanTSyn_TimeMasterConfig[PduIdx].IcvGenerationSupport == CANTSYN_ICV_SUPPORTED)
      {

        /* check if indication targets this time domain */
        if(job->jobId == CanTSyn_TimeMasterConfig[PduIdx].IcvGenerationJobId)
        {
          SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

#if((CANTSYN_TX_SYNC_USED == STD_ON) && (CANTSYN_TX_OFFSET_USED == STD_ON))
          if(PduIdx < CANTSYN_NUMBER_OF_SYNC_MASTERS)
          {
            /* sync master */
            IcvIndex = CanTSyn_SyncMaster[PduIdx].IcvIndex;
          }
          else
          {
            /* offset master */
            IcvIndex = CanTSyn_OffsetMaster[PduIdx - CANTSYN_NUMBER_OF_SYNC_MASTERS].IcvIndex;
          }
#elif(CANTSYN_TX_SYNC_USED == STD_ON)
          /* sync master */
          IcvIndex = CanTSyn_SyncMaster[PduIdx].IcvIndex;
#elif(CANTSYN_TX_OFFSET_USED == STD_ON)
          /* offset master */
          IcvIndex = CanTSyn_OffsetMaster[PduIdx - CANTSYN_NUMBER_OF_SYNC_MASTERS].IcvIndex;
#endif /* ((CANTSYN_TX_SYNC_USED == STD_ON) && (CANTSYN_TX_OFFSET_USED == STD_ON)) */
          CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[IcvIndex];

          /* check if indication is awaited */
          if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_PENDING)
          {
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
            validId = TRUE;
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */
            /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00174,1 */
            CanTSyn_IcvMasterPtr->IcvGenerationTimeout = 0U;
            if(result == E_OK)
            {
              /* Csm handled the request succesfully */
              /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Pending_Received,1 */
              CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_RECEIVED;
            }
            else
            {
              /* unrecoverable error */
              /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_Pending_Failed_GenNotOk,1 */
              CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_FAILED;
            }
          }

          SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

          break;
        }
      }
    }
  }

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00202,1 */
  if(validId == FALSE)
  {
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_ICVGENERATIONINDICATION, CANTSYN_E_PARAM);
  }
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */

}


STATIC FUNC(void, CANTSYN_CODE) CanTSyn_AddFvAndIcvToFrame
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) SduDataPtr,
  uint8 PduIdx,
  uint8 IcvIndex,
#if(CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 Offset,
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
  uint8 FrameLength
)
{
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 FvIndex;
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
  uint8 IcvByteIndex;
  uint8 FvLength = 0U;
  uint8 IcvOffset;

  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[PduIdx];
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[IcvIndex];

#if(CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
  /* defensive programming */
  CANTSYN_POSTCONDITION_ASSERT((CanTSyn_TimeMasterDomainPtr->ComputedIcvStartIndex + CanTSyn_IcvMasterPtr->ComputedIcvLength) <= CANTSYN_ICV_COMPUTED_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON */
#if(CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  /* add FV or Trunc FV to the frame */
  if(CanTSyn_TimeMasterDomainPtr->IsFvUsed == TRUE)
  {
    if(CanTSyn_TimeMasterDomainPtr->IcvGenerationFvLength > CanTSyn_TimeMasterDomainPtr->IcvGenerationFvTruncLength)
    {
      /* add Trunc FV to frame */
      FvLength = (CANTSYN_COMPUTE_FVL_IN_BYTES(CanTSyn_IcvMasterPtr->IcvGenerationFvTruncLength));
      for(FvIndex = 0U; FvIndex < FvLength; FvIndex++)
      {
        SduDataPtr[FrameLength + FvIndex] = CanTSyn_IcvMasterPtr->TruncatedFv[FvIndex];
      }
    }
    else
    {
      /* take full FV from the IcvData array and add to the frame */
      FvLength = (CANTSYN_COMPUTE_FVL_IN_BYTES(CanTSyn_IcvMasterPtr->IcvGenerationFvLength));
      TS_MemCpy(&SduDataPtr[FrameLength],
          &CanTSyn_IcvData[CanTSyn_TimeMasterDomainPtr->IcvDataStartIndex + Offset + FrameLength],
          FvLength
      );
    }
  }
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */

  /* add ICV to frame */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00161.ICVinFUP,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00162.ICVinOFS,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00176,1 */
  IcvOffset = FrameLength + FvLength;
  for(IcvByteIndex = 0U; IcvByteIndex < CanTSyn_IcvMasterPtr->ComputedIcvLength; IcvByteIndex++)
  {
    SduDataPtr[IcvOffset + IcvByteIndex] = CanTSyn_ComputedIcv[CanTSyn_TimeMasterDomainPtr->ComputedIcvStartIndex + IcvByteIndex];
  }

}

STATIC FUNC(void, CANTSYN_CODE) CanTSyn_CopyFrameAndFvToIcvData
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 PduIdx,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) FV,
#endif /* #if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
  uint32 Offset,
  uint8 FrameLength
)
{
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 FvLengthInBytes = 0;
  uint8 FvIndex;
#endif /* #if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */

#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_PRECONDITION_ASSERT((Offset + FrameLength) < CANTSYN_ICV_DATA_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */
  /* load message payload for Icv generation */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00161.Payload,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00162.Payload,1 */
  TS_MemCpy(&CanTSyn_IcvData[Offset],
                  TxDataPtr,
                  FrameLength);

#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  if(CanTSyn_TimeMasterConfig[PduIdx].IsFvUsed == TRUE)
  {
    /* Use full FV in ICV generation */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00166.FullFVinICV,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00167.UseFullFV,1 */
    FvLengthInBytes = (CANTSYN_COMPUTE_FVL_IN_BYTES(CanTSyn_TimeMasterConfig[PduIdx].IcvGenerationFvLength));

#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_PRECONDITION_ASSERT((Offset + FrameLength + FvLengthInBytes) < CANTSYN_ICV_DATA_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */

    for(FvIndex = 0U;
        FvIndex < FvLengthInBytes;
        FvIndex++
    )
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00161.Payload,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00162.Payload,1 */
      CanTSyn_IcvData[Offset + FrameLength + FvIndex] = FV[FvIndex];
    }
  }
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
}

#if(CANTSYN_TX_OFFSET_USED == STD_ON)
STATIC FUNC(void, CANTSYN_CODE) CanTSyn_CheckIcvGenerationState
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) SduDataPtr,
  uint8 CanTSynPduIndex,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) MessageAccepted,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) RetVal,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) sduDataLength

)
{
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_TimeMasterDomainPtr = &CanTSyn_TimeMasterConfig[CanTSynPduIndex + CANTSYN_NUMBER_OF_SYNC_MASTERS];
  P2VAR(CanTSyn_OffsetMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_OffsetMasterPtr = &CanTSyn_OffsetMaster[CanTSynPduIndex];
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[CanTSyn_OffsetMasterPtr->IcvIndex];

  if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_FAILED)
  {
    /* restore content of FUP frame from global array*/
    TS_MemCpy(SduDataPtr,
              &CanTSyn_IcvData[CanTSyn_TimeMasterDomainPtr->IcvDataStartIndex],
              CANTSYN_OFS_ICV_PAYLOAD_LENGTH
    );
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00175.StopICVGeneration,1 */
    SduDataPtr[CANTSYN_B16_FVL] = 0U;
    SduDataPtr[CANTSYN_B17_ICVL] = 0U;
#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
  #ifdef CANTSYN_SEV_ICV_GENERATION_FAILED
    /* ICV generation failed; report event to IdsM */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00175.CallIdsM,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
    IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_ICV_GENERATION_FAILED, &(CanTSyn_TimeMasterDomainPtr->TimeDomainId), CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_ICV_GENERATION_FAILED */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)  */
  }
  else if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_RECEIVED)
  {
    /* restore content of FUP frame from global array*/
    TS_MemCpy(SduDataPtr,
              &CanTSyn_IcvData[CanTSyn_TimeMasterDomainPtr->IcvDataStartIndex],
              CANTSYN_OFS_ICV_PAYLOAD_LENGTH
    );

    /* add ICV to frame */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00162.ICVinOFS,1 */
    CanTSyn_AddFvAndIcvToFrame(SduDataPtr,
                               CanTSynPduIndex + CANTSYN_NUMBER_OF_SYNC_MASTERS,
                               CanTSyn_OffsetMasterPtr->IcvIndex,
#if(CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
                               0U,
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
                             CANTSYN_OFS_ICV_PAYLOAD_LENGTH);
  }
  else
  {
    /* do nothing */
  }

  /* check if ICV generation indication is still awaited */
  if(CanTSyn_IcvMasterPtr->IcvGenerationState == CANTSYN_ICV_STATE_PENDING)
  {
    *MessageAccepted = FALSE;
    *RetVal = E_OK;
  }
  else
  {
    *MessageAccepted = TRUE;
    *sduDataLength = CANTSYN_OFS_ICV_PAYLOAD_LENGTH + (CANTSYN_COMPUTE_FVL_IN_BYTES(SduDataPtr[CANTSYN_B16_FVL])) + SduDataPtr[CANTSYN_B17_ICVL];
  }
}
#endif /* (CANTSYN_TX_OFFSET_USED == STD_ON) */

STATIC FUNC(void, CANTSYN_CODE) CanTSyn_GenerateIcv
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  uint8 PduIdx,
  uint8 IcvIndex,
  uint8 BYTE_FVL,
  uint8 BYTE_ICVL,
  uint8 BYTE_START_FVL
)
{
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_ConfigPtr = &CanTSyn_TimeMasterConfig[PduIdx];
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[IcvIndex];

  boolean FvError = FALSE;
  boolean isOFS = FALSE;
  Std_ReturnType IcvRetVal = E_NOT_OK;
  uint8 IcvByteIndex = 0U;
  uint32 UsedFVLength = 0U;
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  uint8 FV[CANTSYN_FV_MAX_LENGTH] = {0};
#endif /* if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */

  /* check if frame is OFS */
  if((TxDataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_EXT_MSG_WITHOUT_CRC_ICV_AUTH) || (TxDataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_OFS_EXT_MSG_WITH_CRC_ICV_AUTH))
  {
    isOFS = TRUE;
  }
  /* else is FUP */

  TxDataPtr[BYTE_ICVL] = (CANTSYN_SET_ICVL(CanTSyn_ConfigPtr->IcvTxLength));
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
  FvError = CanTSyn_GenerateFreshnessValue(TxDataPtr,
                                           &FV[0],
                                           PduIdx,
                                           IcvIndex,
                                           BYTE_FVL,
                                           BYTE_ICVL,
                                           BYTE_START_FVL,
                                           &UsedFVLength);
#else /* if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00165,1 */
  TxDataPtr[BYTE_FVL] = 0U;
#endif /* if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */

  /* Generate ICV*/
  if(FvError == FALSE)
  {
    if(isOFS == FALSE)
    {
      /* is FUP frame */
      CanTSyn_CopyFrameAndFvToIcvData(TxDataPtr,
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
                                      PduIdx,
                                      &FV[0],
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
                                      CanTSyn_ConfigPtr->IcvDataStartIndex + CANTSYN_SYNC_PAYLOAD_LENGTH,
                                      CANTSYN_FUP_ICV_PAYLOAD_LENGTH);
    }
    else
    {
      CanTSyn_CopyFrameAndFvToIcvData(TxDataPtr,
#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
                                      PduIdx,
                                      &FV[0],
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
                                      CanTSyn_ConfigPtr->IcvDataStartIndex,
                                      CANTSYN_OFS_ICV_PAYLOAD_LENGTH);
    }

    /* Load the ICV length */
    CanTSyn_IcvMasterPtr->ComputedIcvLength = CanTSyn_ConfigPtr->IcvTxLength;

    /* Call Csm Api to generate ICV*/
#if(CANTSYN_ICV_MAC_GENERATE_USAGE == STD_ON)
    if(CanTSyn_ConfigPtr->IcvGenerationBase == CANTSYN_ICV_MAC)
    {
      /* call to Csm_MacGenerate triggers ICV generation using MAC authentication */
      /* result will be stored in the CanTSyn_ComputedIcv array */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00169,1 */
      IcvRetVal = Csm_MacGenerate(CanTSyn_ConfigPtr->IcvGenerationJobId,
                      CRYPTO_OPERATIONMODE_SINGLECALL,
                      &CanTSyn_IcvData[CanTSyn_ConfigPtr->IcvDataStartIndex],
                      CanTSyn_ConfigPtr->IcvDataLength,
                      &CanTSyn_ComputedIcv[CanTSyn_ConfigPtr->ComputedIcvStartIndex],
                      &(CanTSyn_IcvMasterPtr->ComputedIcvLength)
                      );
    }
#endif /* (CANTSYN_ICV_MAC_GENERATE_USAGE == STD_ON) */
#if(CANTSYN_ICV_SIGNATURE_GENERATE_USAGE == STD_ON)
    if(CanTSyn_ConfigPtr->IcvGenerationBase == CANTSYN_ICV_SIGNATURE)
    {
      /* call to Csm_SignatureGenerate triggers ICV generation using signature authentication */
      /* result will be stored in the CanTSyn_ComputedIcv array */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00170,1 */
      IcvRetVal = Csm_SignatureGenerate(CanTSyn_ConfigPtr->IcvGenerationJobId,
                            CRYPTO_OPERATIONMODE_SINGLECALL,
                            &CanTSyn_IcvData[CanTSyn_ConfigPtr->IcvDataStartIndex],
                            CanTSyn_ConfigPtr->IcvDataLength,
                            &CanTSyn_ComputedIcv[CanTSyn_ConfigPtr->ComputedIcvStartIndex],
                            &(CanTSyn_IcvMasterPtr->ComputedIcvLength)
                            );
    }
#endif /* (CANTSYN_ICV_SIGNATURE_GENERATE_USAGE == STD_ON) */
    if(IcvRetVal != E_OK)
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00175.StopICVGeneration,1 */
      TxDataPtr[BYTE_FVL] = 0U;
      TxDataPtr[BYTE_ICVL] = 0U;
#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
  #ifdef CANTSYN_SEV_ICV_GENERATION_FAILED
      /* Csm API could not handle the request; ICV generation failed; report event to IdsM */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00175.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
      IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_ICV_GENERATION_FAILED , &CanTSyn_ConfigPtr->TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_ICV_GENERATION_FAILED */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)  */
    }
    /* Synchronous ICV generation */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00172,1 */
    else if((CanTSyn_ConfigPtr->IcvGenerationCsmProcessing == CANTSYN_ICV_CSM_SYNCHRONOUS) ||
            (CanTSyn_ConfigPtr->IcvGenerationTimeout == 0U))
    {
#if(CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
      /* defensive programming */
      CANTSYN_POSTCONDITION_ASSERT((CanTSyn_ConfigPtr->ComputedIcvStartIndex + CanTSyn_IcvMasterPtr->ComputedIcvLength) <= CANTSYN_ICV_COMPUTED_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON */

      /* add ICV to frame */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00161.ICVinFUP,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00162.ICVinOFS,1 */
      for(IcvByteIndex = 0U; IcvByteIndex < CanTSyn_IcvMasterPtr->ComputedIcvLength; IcvByteIndex++)
      {
        TxDataPtr[BYTE_START_FVL + UsedFVLength + IcvByteIndex] = CanTSyn_ComputedIcv[CanTSyn_ConfigPtr->ComputedIcvStartIndex + IcvByteIndex];
      }
      /* timeout is disabled */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00171,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_CONSTR_00001,1 */
      CanTSyn_IcvMasterPtr->IcvGenerationTimeout = 0;
    }
    /* Asynchronous ICV generation */
    else
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00173,1 */
      CanTSyn_IcvMasterPtr->IcvGenerationTimeout = CanTSyn_ConfigPtr->IcvGenerationTimeout;
      /* !LINKSTO CanTSyn.Dsn.CanTSynTxIcvStatus_NotRequested_Pending,1 */
      CanTSyn_IcvMasterPtr->IcvGenerationState = CANTSYN_ICV_STATE_PENDING;
    }

  }
}

#if (CANTSYN_ICV_GENERATION_FV_USED == STD_ON)
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_GenerateFreshnessValue
(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) TxDataPtr,
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_DATA) FV,
  uint8 PduIdx,
  uint8 IcvIndex,
  uint8 BYTE_FVL,
  uint8 BYTE_ICVL,
  uint8 BYTE_START_FVL,
  P2VAR(uint32, AUTOMATIC, CANTSYN_APPL_DATA) UsedFVL
)
{
  P2CONST(CanTSyn_TimeMasterDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST)
          CanTSyn_ConfigPtr = &CanTSyn_TimeMasterConfig[PduIdx];
  P2VAR(CanTSyn_IcvMasterType, AUTOMATIC, CANTSYN_APPL_DATA)
        CanTSyn_IcvMasterPtr = &CanTSyn_IcvMaster[IcvIndex];
  boolean FvError = FALSE;
  Std_ReturnType FvRetVal = E_NOT_OK;
#if (CANTSYN_TRUNCATED_FV_USED == STD_ON)
  uint8 TruncFV[CANTSYN_TRUNC_FV_MAX_LENGTH] = {0};
  boolean UseTruncFV = FALSE;
#endif /* (CANTSYN_TRUNCATED_FV_USED == STD_ON) */
  uint8 FvIndex;
  uint32 UsedFVLength = 0U;

  if(CanTSyn_ConfigPtr->IsFvUsed)
  {
    /* use variable struct ; cannot pass const parameters cu API call*/
    CanTSyn_IcvMasterPtr->IcvGenerationFvLength = CanTSyn_ConfigPtr->IcvGenerationFvLength;
#if (CANTSYN_TRUNCATED_FV_USED == STD_ON)
    CanTSyn_IcvMasterPtr->IcvGenerationFvTruncLength = CanTSyn_ConfigPtr->IcvGenerationFvTruncLength;

    /* retrieve freshness value from FvM via StbM */
    if(CanTSyn_IcvMasterPtr->IcvGenerationFvTruncLength < CanTSyn_IcvMasterPtr->IcvGenerationFvLength)
    {
      /* This interface is used by the StbM to obtain the current freshness value. The interface function
         provides also the truncated freshness transmitted in the secured PDU. */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00164,1 */
      FvRetVal = StbM_GetTxFreshnessTruncData(
        CanTSyn_ConfigPtr->IcvGenerationFvId,
        &CanTSyn_IcvMasterPtr->IcvGenerationFvLength,
        &CanTSyn_IcvMasterPtr->IcvGenerationFvTruncLength,
        &FV[0],
        &TruncFV[0]
      );

#if(CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
      /* defensive programming */
      CANTSYN_POSTCONDITION_ASSERT(CanTSyn_IcvMasterPtr->IcvGenerationFvTruncLength < (CANTSYN_TRUNC_FV_MAX_LENGTH*8U), DET_INTERNAL_API_ID);
      /* Deviation TASKING-1 */
      CANTSYN_POSTCONDITION_ASSERT(TruncFV != NULL_PTR, DET_INTERNAL_API_ID);
#endif /* CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON */

      UsedFVLength = CanTSyn_IcvMasterPtr->IcvGenerationFvTruncLength;
      UseTruncFV = TRUE;
    }
    else /* FvTruncLength == FvLength */
#endif /* (CANTSYN_TRUNCATED_FV_USED == STD_ON) */
    {
      /* This API returns the freshness value from the Most Significant Bits
         in the first byte, of the Freshness array, in big endian format. */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00163,1 */
      FvRetVal = StbM_GetTxFreshness(
        CanTSyn_ConfigPtr->IcvGenerationFvId,
        &CanTSyn_IcvMasterPtr->IcvGenerationFvLength,
        &FV[0]
      );

#if(CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
      /* defensive programming */
      CANTSYN_POSTCONDITION_ASSERT(CanTSyn_IcvMasterPtr->IcvGenerationFvLength <= (CANTSYN_FV_MAX_LENGTH*8U), DET_INTERNAL_API_ID);
      /* Deviation TASKING-1 */
      CANTSYN_POSTCONDITION_ASSERT(FV != NULL_PTR, DET_INTERNAL_API_ID);
#endif /* CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON */

      UsedFVLength = CanTSyn_IcvMasterPtr->IcvGenerationFvLength;
    }

    if(FvRetVal == E_OK)
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00166.SetFVL,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00167.SetFVL,1 */
      TxDataPtr[BYTE_FVL] = (uint8)UsedFVLength;
      UsedFVLength = CANTSYN_SET_FVL(CANTSYN_COMPUTE_FVL_IN_BYTES(UsedFVLength));
#if (CANTSYN_TRUNCATED_FV_USED == STD_ON)
      TS_MemCpy(CanTSyn_IcvMasterPtr->TruncatedFv, TruncFV, UsedFVLength);
#endif /* if (CANTSYN_TRUNCATED_FV_USED == STD_ON)  */

      /* add freshness value to frame */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
      for(FvIndex = 0U; FvIndex < UsedFVLength ; FvIndex++)
      {
#if (CANTSYN_TRUNCATED_FV_USED == STD_ON)
        if(UseTruncFV == TRUE)
        {
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00167.TruncatedFV,1 */
          TxDataPtr[FvIndex + BYTE_START_FVL] = TruncFV[FvIndex];
        }
        else
#endif /* if (CANTSYN_TRUNCATED_FV_USED == STD_ON) */
        {
          /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00166.FullFV,1 */
          TxDataPtr[FvIndex + BYTE_START_FVL] = FV[FvIndex];
        }
      }
    }
    else /* GetTxFreshness returned E_NOT_OK or STBM_E_BUSY */
    {
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00168.StopICVGeneration,1 */
      TxDataPtr[BYTE_FVL] = 0U;
      TxDataPtr[BYTE_ICVL] = 0U;
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_91001,1 */
#if (CANTSYN_DET_RUNTIME_CHECK == STD_ON)
       /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00168.CallDet,1 */
      (void)Det_ReportRuntimeError(CANTSYN_MODULE_ID,
                            CANTSYN_INSTANCE_ID,
                            CANTSYN_SID_MAINFUNCTION,
                            CANTSYN_E_FRESHNESSFAILURE);
#endif /* (CANTSYN_DET_RUNTIME_CHECK == STD_ON) */
#if (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
  #ifdef CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE
      /* failed to retrieve freshness value from FvM; Icv generation failed; report event to IdsM */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00168.CallIdsM,1 */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00201,1 */
      IdsM_SetSecurityEventWithContextData(CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE, &CanTSyn_ConfigPtr->TimeDomainId, CANTSYN_CONTEXT_DATA_SIZE_ONE_BYTE);
  #endif /* def CANTSYN_SEV_FRESHNESS_NOT_AVAILABLE */
#endif /* (CANTSYN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)  */
      FvError = TRUE;
    }
  }
  else /* FV is not used */
  {
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00155,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00156,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00157,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00158,1 */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00165,1 */
    TxDataPtr[BYTE_FVL] = 0U;
  }
  (*UsedFVL) = UsedFVLength;
  return FvError;
}
#endif /* (CANTSYN_ICV_GENERATION_FV_USED == STD_ON) */
#endif /* if (CANTSYN_ICV_GENERATION_SUPPORTED == STD_ON) */

#if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON)
/* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_91003.Signature,1 */
/* Deviation MISRAC2012-3 */

/* Tresos 8 API */
FUNC(void, CANTSYN_CODE) CanTSyn_IcvVerificationIndication
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  Std_ReturnType result
)
{
  uint8 PduIdx;
  uint8 IcvIndex;
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  boolean validId = FALSE;
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */

  if(job == NULL_PTR)
  {
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
    validId = TRUE; /* to prevent CANTSYN_E_PARAM reporting */
    /* !LINKSTO CanTSyn.EB.Check.Rx.IcvVerificationIndication.JobId.NullPtr,1 */
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_ICVVERIFICATIONINDICATION, CANTSYN_E_NULL_POINTER);
#endif /* (CANTSYN_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
    for(PduIdx = 0U;
        /* Deviation TASKING-1 */
        PduIdx < CANTSYN_NUMBER_OF_SLAVES;
        PduIdx++ )
    {
      if((CanTSyn_TimeSlaveConfig[PduIdx].IcvVerificationType == CANTSYN_ICV_VERIFIED) || (CanTSyn_TimeSlaveConfig[PduIdx].IcvVerificationType == CANTSYN_ICV_OPTIONAL))
      {
        if(job->jobId == CanTSyn_TimeSlaveConfig[PduIdx].IcvVerificationJobId)
        {
#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
          validId = TRUE;
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */

          SchM_Enter_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

#if((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON))
          if(PduIdx < CANTSYN_NUMBER_OF_SYNC_SLAVES)
          {
            /* sync slave */
            IcvIndex = CanTSyn_SyncSlave[PduIdx].IcvIndex;
          }
          else
          {
            /* offset slave */
            IcvIndex = CanTSyn_OffsetSlave[PduIdx - CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvIndex;
          }
#elif(CANTSYN_RX_SYNC_USED == STD_ON)
          /* sync slave */
          IcvIndex = CanTSyn_SyncSlave[PduIdx].IcvIndex;
#elif(CANTSYN_RX_OFFSET_USED == STD_ON)
          /* offset slave */
          IcvIndex = CanTSyn_OffsetSlave[PduIdx - CANTSYN_NUMBER_OF_SYNC_SLAVES].IcvIndex;
#endif /* ((CANTSYN_RX_SYNC_USED == STD_ON) && (CANTSYN_RX_OFFSET_USED == STD_ON)) */
          /* check if indication was awaited */
          if(CanTSyn_IcvSlave[IcvIndex].IcvVerificationState == CANTSYN_ICV_STATE_PENDING)
          {
            /* check that Csm API handled the request */
            /* the actual result of the verification is stored in variable IcvVerificationResult */
            if(result == E_OK)
            {
              /* check verification result */
              if(CanTSyn_IcvSlave[IcvIndex].IcvVerificationResult == CRYPTO_E_VER_OK)
              {
                /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Pending_Verified,1 */
                CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_VERIFIED;
              }
              else
              {
                /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Pending_Failed_VerifNotOk,1 */
                CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
              }
              /* stop verification timeout */
              /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00198,1 */
              CanTSyn_IcvSlave[IcvIndex].IcvVerificationTimeout = 0U;
            }
            else if((result == CRYPTO_E_BUSY) || (result == CRYPTO_E_QUEUE_FULL))
            {
              /* recoverable error */
              /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00199,1 */
              /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_Pending_RecovError,1 */
              CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_RECOV_ERROR;
              CanTSyn_IcvSlave[IcvIndex].IcvVerificationAttempts++;
            }
            else
            {
              /* unrecoverable error; verification is considered as failed */
              /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00200.StopICVVerification,1 */
              CanTSyn_IcvSlave[IcvIndex].IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
              /* stop verification timeout */
              /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00198,1 */
              CanTSyn_IcvSlave[IcvIndex].IcvVerificationTimeout = 0U;
            }
          }

          SchM_Exit_CanTSyn_SCHM_CANTSYN_EXCLUSIVE_AREA_0();

          break;
        }
      }
    }
  }

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00203,1 */
  if(validId == FALSE)
  {
    CANTSYN_DET_REPORT_ERROR(CANTSYN_SID_ICVVERIFICATIONINDICATION, CANTSYN_E_PARAM);
  }
#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */

}


#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
STATIC FUNC(boolean, CANTSYN_CODE) CanTSyn_FetchFreshnessValue
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId,
  uint8 IcvIndex,
  uint8 offset,
  uint8 frameLength,
  uint8 BYTE_FVL,
  uint8 BYTE_START_FVL
)
{
  P2CONST(CanTSyn_TimeSlaveDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) SlaveConfigPtr = &CanTSyn_TimeSlaveConfig[PduId];
  P2VAR(CanTSyn_IcvSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvSlavePtr = &CanTSyn_IcvSlave[IcvIndex];
  boolean FvError = FALSE;
  uint8 TruncFV[CANTSYN_TRUNC_FV_MAX_LENGTH] = {0};
  Std_ReturnType FvRetVal = E_NOT_OK;
  uint8 FV[CANTSYN_FV_MAX_LENGTH] = {0};
  uint8 FvLength = 0U;
  uint8 FvIndex;
  uint32 FVL_IN_BITS = 0U;
  uint32 FVL = DataPtr[BYTE_FVL]; /* bit 8 is reserved */

  FVL = (CANTSYN_GET_FVL(FVL)); /* bit 8 is reserved */
  FVL_IN_BITS = FVL;
  FVL = (CANTSYN_COMPUTE_FVL_IN_BYTES(FVL));

  /* copy the freshness from the frame to local array */
  TS_MemCpy(TruncFV, &DataPtr[BYTE_START_FVL], FVL);

  /* get freshness from FvM via StbM */
  /* This interface is used by the StbM to query the current freshness value. */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00188,1 */
  FvRetVal = StbM_GetRxFreshness( CanTSyn_TimeSlaveConfig[PduId].IcvVerificationFvId,  /* StbMFreshnessValueId */
                            &TruncFV[0],        /* StbMTruncatedFreshnessValue */
                            FVL_IN_BITS,                /*  StbMTruncatedFreshnessValueLength */
                            CanTSyn_IcvSlavePtr->IcvVerificationAttempts,   /* StbMAuthVerifyAttempts */
                            &CanTSyn_IcvSlavePtr->IcvVerificationFvLength,  /* StbMFreshnessValueLength */
                            &FV[0]  /* StbMFreshnessValue */
  );
  if(FvRetVal != E_OK)
  {
    /* failed attempt */

    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00192.IncrementAttemptCounter,1 */
    CanTSyn_IcvSlavePtr->IcvVerificationAttempts++;

    /* recoverable error; retry during the next main function call; update state */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00192.StbMCallRetry,1 */
    /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_NotRequested_RecovError,1 */
    CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_RECOV_ERROR;

    CanTSyn_IcvSlavePtr->IcvFvRecovError = TRUE;

    FvError = TRUE;
  }
  else
  {
#if(CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_POSTCONDITION_ASSERT(CanTSyn_IcvSlavePtr->IcvVerificationFvLength < (CANTSYN_FV_MAX_LENGTH*8U), DET_INTERNAL_API_ID);
    CANTSYN_POSTCONDITION_ASSERT(FV != NULL_PTR, DET_INTERNAL_API_ID);
#endif /* CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON */

    CanTSyn_IcvSlavePtr->IcvFvRecovError = FALSE;
    /* add freshness to Icv data array */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00191,1 */
    FvLength = (CANTSYN_COMPUTE_FVL_IN_BYTES(CanTSyn_IcvSlavePtr->IcvVerificationFvLength));
    for(FvIndex = 0U; FvIndex < FvLength; FvIndex++)
    {
      CanTSyn_IcvData[SlaveConfigPtr->IcvDataStartIndex + offset + frameLength + FvIndex] = FV[FvIndex];
    }
  }

  return FvError;
}
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */

STATIC FUNC(void, CANTSYN_CODE) CanTSyn_VerifyIcv
(
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_CONST) DataPtr,
  uint8 PduId,
  uint8 IcvIndex,
  uint8 BYTE_FVL,
#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
  uint8 BYTE_START_FVL,
#endif /* (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON) */
  uint8 BYTE_ICVL
)
{
  Std_ReturnType ret = E_NOT_OK;
  boolean FvError = FALSE;
  uint8 ICVL = DataPtr[BYTE_ICVL];
  uint8 offset = 0U;
  uint8 frameLength = 0U;
  uint8 IcvDataLength = 0U;
  P2CONST(CanTSyn_TimeSlaveDomainConfigType, AUTOMATIC, CANTSYN_APPL_CONST) SlaveConfigPtr = &CanTSyn_TimeSlaveConfig[PduId];
  P2VAR(CanTSyn_IcvSlaveType, AUTOMATIC, CANTSYN_APPL_DATA) CanTSyn_IcvSlavePtr = &CanTSyn_IcvSlave[IcvIndex];


  uint32 FVL = DataPtr[BYTE_FVL]; /* bit 8 is reserved */
  FVL = (CANTSYN_GET_FVL(FVL)); /* bit 8 is reserved */
  FVL = (CANTSYN_COMPUTE_FVL_IN_BYTES(FVL));
  ICVL = CANTSYN_SET_ICVL(ICVL); /* bit 7, 6 reserved */

  IcvDataLength = (uint8)SlaveConfigPtr->IcvDataLength;

  if((DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITH_CRC_ICV_AUTH) || (DataPtr[CANTSYN_B0_MSG_TYPE] == CANTSYN_FUP_WITHOUT_CRC_ICV_AUTH))
  {
    /* FUP frame */
    offset = CANTSYN_SYNC_PAYLOAD_LENGTH;
    frameLength = CANTSYN_FUP_ICV_PAYLOAD_LENGTH;
  }
  else
  {
    /* OFS length */
    offset = 0;
    frameLength = CANTSYN_OFS_ICV_PAYLOAD_LENGTH;
  }

  if(CanTSyn_IcvSlavePtr->IcvVerificationAttempts == 0U)
  {
#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_PRECONDITION_ASSERT((SlaveConfigPtr->IcvDataStartIndex + offset + frameLength + FVL) < CANTSYN_ICV_DATA_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */

    /* save frame content in IcvData array */
    TS_MemCpy(&CanTSyn_IcvData[SlaveConfigPtr->IcvDataStartIndex + offset],
              DataPtr,
              frameLength + FVL);

#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
    /* defensive programming */
    CANTSYN_PRECONDITION_ASSERT((SlaveConfigPtr->ComputedIcvStartIndex + ICVL) <= CANTSYN_ICV_COMPUTED_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */

    /* save received ICV from the frame into the CopmutedIcv array */
    TS_MemCpy(&CanTSyn_ComputedIcv[SlaveConfigPtr->ComputedIcvStartIndex],
              &DataPtr[frameLength + FVL],
              ICVL);
  }

#if (CANTSYN_ICV_VERIFICATION_FV_USED == STD_ON)
  /* check FV usage */
  if(CanTSyn_TimeSlaveConfig[PduId].IsFvUsed == TRUE)
  {
    /* check if FV was already retrieved in a previous attempt; skip this step if so */
    if((CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_NOT_REQUESTED) ||
    ((CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_RECOV_ERROR) && (CanTSyn_IcvSlavePtr->IcvFvRecovError == TRUE)))
    {
      CanTSyn_IcvSlavePtr->IcvVerificationFvLength = SlaveConfigPtr->IcvVerificationFvLength;
      if(FVL > 0U)
      {
        FvError = CanTSyn_FetchFreshnessValue(DataPtr, PduId, IcvIndex, offset, frameLength, BYTE_FVL, BYTE_START_FVL);
      }
      else
      {
        IcvDataLength = offset + frameLength;
      }
      /* FV not included in verification */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00189,1 */
    }
    else
    {
      /* do nothing */
      /* this step has already been fulfilled */
      /* needed data is present in the CanTSyn_IcvData array */
    }
  }
  else
  {
    if(FVL > 0U)
    {
      /* verification failed */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00190,1 */
      CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
      FvError = TRUE;
    }
  }
#endif
  /* ICV verification */
  if((CanTSyn_IcvSlavePtr->IcvVerificationState != CANTSYN_ICV_STATE_NOT_REQUESTED) && (CanTSyn_IcvSlavePtr->IcvVerificationState != CANTSYN_ICV_STATE_RECOV_ERROR))
  {
    /* do nothing */
    /* Csm APIs shall only be called during the RxIndication or in case of a retry (recoverable error). */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00192.StbMCallRetry,1 */
  }
  else if(FvError == FALSE)
  {
    if(CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_NOT_REQUESTED)
      /* else: this was already fulfilled during the RxIndication */
    {
#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* defensive programming */
      CANTSYN_PRECONDITION_ASSERT((SlaveConfigPtr->IcvDataStartIndex + offset + frameLength) < CANTSYN_ICV_DATA_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      /* load frame content into IcvData array */
      TS_MemCpy(&CanTSyn_IcvData[SlaveConfigPtr->IcvDataStartIndex + offset],
                DataPtr,
                frameLength);

#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* defensive programming */
      CANTSYN_PRECONDITION_ASSERT((SlaveConfigPtr->ComputedIcvStartIndex + ICVL) <= CANTSYN_ICV_COMPUTED_ARRAY_SIZE, DET_INTERNAL_API_ID);
#endif /* (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      /* load received ICV from the frame into the CopmutedIcv array */
      TS_MemCpy(&CanTSyn_ComputedIcv[SlaveConfigPtr->ComputedIcvStartIndex],
                &DataPtr[frameLength + FVL],
                ICVL);
    }
#if(CANTSYN_ICV_MAC_VERIFY_USAGE == STD_ON)
    if(SlaveConfigPtr->IcvVerificationBase == CANTSYN_ICV_MAC)
    {
      /* call to Csm_MacVerify triggers ICV verification using MAC authentication */
      /* result will be stored in the IcvVerificationResult field of CanTSyn_IcvSlave data structure */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00194,1 */
      ret = Csm_MacVerify(
        SlaveConfigPtr->IcvVerificationJobId, /* Csm Job ID */
        CRYPTO_OPERATIONMODE_SINGLECALL,      /* mode */
        &CanTSyn_IcvData[SlaveConfigPtr->IcvDataStartIndex], /* dataPtr */
        IcvDataLength,        /* dataLength */
        &CanTSyn_ComputedIcv[SlaveConfigPtr->ComputedIcvStartIndex],  /* macPtr */
        ((uint32)ICVL * 8U), /* Icv length in bits */
        &CanTSyn_IcvSlavePtr->IcvVerificationResult  /* verifyPtr */
      );
    }
#endif /* (CANTSYN_ICV_MAC_VERIFY_USAGE == STD_ON) */
#if(CANTSYN_ICV_SIGNATURE_VERIFY_USAGE == STD_ON)
    if(SlaveConfigPtr->IcvVerificationBase == CANTSYN_ICV_SIGNATURE)
    {
      /* call to Csm_SignatureVerify triggers ICV verification using signature authentication */
      /* result will be stored in the IcvVerificationResult field of CanTSyn_IcvSlave data structure */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00195,1 */
      ret = Csm_SignatureVerify(
        SlaveConfigPtr->IcvVerificationJobId,  /* Csm Job ID */
        CRYPTO_OPERATIONMODE_SINGLECALL,       /* mode */
        &CanTSyn_IcvData[SlaveConfigPtr->IcvDataStartIndex],   /* dataPtr */
        IcvDataLength,          /* dataLength */
        &CanTSyn_ComputedIcv[SlaveConfigPtr->ComputedIcvStartIndex],  /* macPtr */
        ((uint32)ICVL), /* Icv length in bytes */
        &CanTSyn_IcvSlavePtr->IcvVerificationResult  /* verifyPtr */
      );
    }
#endif /*  */

    if(ret == E_OK)
    {
      /* synchronous verification */
      /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00196,1 */
      if((SlaveConfigPtr->IcvVerificationCsmProcessing == CANTSYN_ICV_CSM_SYNCHRONOUS) ||
         (SlaveConfigPtr->IcvVerificationTimeout == 0U))
      {
          /* verification successful */
        if(CanTSyn_IcvSlavePtr->IcvVerificationResult == CRYPTO_E_VER_OK)
        {
          /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_RecovError_Verified,1 */
          CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_VERIFIED;
        }
        else
        {
          /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_RecovError_Failed_VerifNotOk,1 */
          CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
        }
      }
      /* asynchronous verification */
      else
      {
        /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_RecovError_Pending,1 */
        /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_NotRequested_Pending,1 */
        CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_PENDING;
        /* start verification timeout */
        /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00197,1 */
        CanTSyn_IcvSlavePtr->IcvVerificationTimeout = SlaveConfigPtr->IcvVerificationTimeout;
      }
    }
    else if((ret ==  CRYPTO_E_BUSY) || (ret == CRYPTO_E_QUEUE_FULL))
    {
      /* recoverable error; retry during next main function call */
       /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00199,1 */
      CanTSyn_IcvSlavePtr->IcvVerificationAttempts++;
      CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_RECOV_ERROR;
    }
    else
    {
      /* unrecoverable error */
      /* verification failed */
      CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
    }
  }
  else
  {
    /* fall through */
  }

  /* check if number of maximum attempts has already been reached */
  /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00200.StopICVVerification,1 */
  if((CanTSyn_IcvSlavePtr->IcvVerificationAttempts == SlaveConfigPtr->IcvVerificationAttempts) && (CanTSyn_IcvSlavePtr->IcvVerificationState == CANTSYN_ICV_STATE_RECOV_ERROR))
  {
    /* verification failed */
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00193.StopICVVerification,1 */
    /* !LINKSTO CanTSyn.Dsn.CanTSynRxIcvStatus_RecovError_Failed_MaxAttemptReached,1 */
    CanTSyn_IcvSlavePtr->IcvVerificationResult = CRYPTO_E_VER_NOT_OK;
    CanTSyn_IcvSlavePtr->IcvVerificationState = CANTSYN_ICV_STATE_FAILED;
#if (CANTSYN_DET_RUNTIME_CHECK == STD_ON)
    /* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00193.CallDet,1 */
    (void)Det_ReportRuntimeError(CANTSYN_MODULE_ID,
                          CANTSYN_INSTANCE_ID,
                          CANTSYN_SID_MAINFUNCTION,
                          CANTSYN_E_FRESHNESSFAILURE);
#endif /* (CANTSYN_DET_RUNTIME_CHECK == STD_ON) */
    /* reset attempt counter */
    CanTSyn_IcvSlavePtr->IcvVerificationAttempts = 0;
  }
}
#endif /* if (CANTSYN_ICV_VERIFICATION_SUPPORTED == STD_ON) */

#define CANTSYN_STOP_SEC_CODE
#include <CanTSyn_MemMap.h>


