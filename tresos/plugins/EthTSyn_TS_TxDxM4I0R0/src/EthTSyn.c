/**
 * \file
 *
 * \brief AUTOSAR EthTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module EthTSyn.
 *
 * \version 4.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  Misra-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 8.13 (Advisory)
 *    A pointer should point to a const-qualified type whenever possible.
 *
 *    Reason:
 *    - The API parameter is specified to be pointer to variable by AUTOSAR specification.
 *    - The API parameter is required to be pointer to variable for at least one possible
 *      configuration.
 *
 *  MISRAC2012-2) Deviated Rule: 8.9 (Advisory)
 *    An object should be defined at block scope if its identifier only appears in a single
 *    function.
 *
 *    Reason:
 *    - The AUTOSAR memory mapping requires that functions are mapped in SEC_CODE memory sections.
 *    - Objects at block scope require a different memory mapping, e.g. to a SEC_VAR section,
 *    which leads to nested memory sections, which is not supported by some compilers.
 *
 *  MISRAC2012-3) Deviated Rule 8.4 (Required)
 *    A compatible declaration shall be visible when an object or function
 *    with external linkage is defined.
 *
 *    Reason:
 *    - The symbol isn't meant to be normally exposed. It's used only during
 *      testing.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W529
 * W529: overflow in constant expression of type "unsigned int"
 *
 * Reason:
 * False-positive from the compilers Tasking 62r2p2 and Tasking 63r1p2 (see justification in ASCETHTSYN-652).
 *
 * TASKING-2) Deviated Rule: W529
 * W529: overflow in constant expression of type "unsigned long int"
 *
 * Reason:
 * False-positive from the compilers Tasking 62r2p2 and Tasking 63r1p2 (see justification in ASCETHTSYN-652).
 *
 * TASKING-3) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False-positive from the compilers Tasking 63r1p2 (see justification in ASCETHTSYN-969).
 */


/*==================[inclusions]============================================*/

#include <TSAutosar.h> /* Specific standard types */
#include <ComStack_Types.h> /* Communication stack types */
#include <EthTSyn.h> /* Module public API */
#include <EthTSyn_Cfg.h> /* Module configuration */
#include <EthTSyn_Int.h> /* Module internal header file */
#include <EthTSyn_Int01_Lib.h> /* Module internal header file */
#include <EthTSyn_Types.h> /* Module specific types */
#include <EthTSyn_Trace.h> /* Debug and trace */
#include <EthIf.h> /* Module public API */
#include <StbM.h> /* Module public API */
#include <TSMem.h> /* TS_MemCpy, ... */
#include <TSAtomic_Assign.h> /* Atomic assignment macros */

/* !LINKSTO EthTSyn.EB.SwitchConfigured, 1 */
#if(ETHTSYN_SWITCH_USED == STD_ON)
#include <EthSwt.h> /* Module public API */
#endif

#if (ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#include <IdsM.h> /* Module public API */
#endif

#include <SchM_EthTSyn.h> /* SchM interface header */

/* if any DEM event is switched on, include Dem.h */
#if ((ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM) || \
     (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DEM) || \
     (ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DEM))
#include <Dem.h>
#endif

#if((ETHTSYN_DEV_ERROR_DETECT == STD_ON) || (ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON))
#include <Det.h> /* DET support */
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
#include <Crc.h> /* CRC support */
#endif/* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
#include <DevAuth.h>
#endif

#if(ETHTSYN_TIME_RECORDING == STD_ON)
#include <StbM_EthTSyn.h> /* Module public API */
#endif

#if(ETHTSYN_ICV_USED == STD_ON)
#include <Csm.h> /* Csm public types */
#endif

/*==================[macros]================================================*/

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
#if (defined ETHTSYN_DET_REPORT_ERROR)
#error ETHTSYN_DET_REPORT_ERROR is already defined
#endif
#define ETHTSYN_DET_REPORT_ERROR(ApiId, ErrorId) \
  (void) Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId), (ErrorId))
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */

#if(ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON)
#if (defined ETHTSYN_DET_RUNTIME_REPORT_ERROR)
#error ETHTSYN_DET_RUNTIME_REPORT_ERROR is already defined
#endif
#define ETHTSYN_DET_RUNTIME_REPORT_ERROR(ApiId, ErrorId) \
  (void) Det_ReportRuntimeError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, (ApiId), (ErrorId))
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */

#if (defined ETHTSYN_PTP_FRAMETYPE)
#error ETHTSYN_PTP_FRAMETYPE is already defined
#endif
/* All EthTSyn frames use the PTP frame type (See 802.1AS-2011 Ch 11.3.5). */
#define ETHTSYN_PTP_FRAMETYPE (Eth_FrameType) 0x88F7U

#if (defined ETHTSYN_MAC_ADD_SIZE)
#error ETHTSYN_MAC_ADD_SIZE is already defined
#endif
#define ETHTSYN_MAC_ADD_SIZE 6U /* Size of MAC address in bytes. */

#if (defined ETHTSYN_TIME_STAMP_SIZE)
#error ETHTSYN_TIME_STAMP_SIZE is already defined
#endif
#define ETHTSYN_TIME_STAMP_SIZE 10U /* Size of time stamp in bytes. */

#if (defined ETHTSYN_SEQ_NUM_MAX)
#error ETHTSYN_SEQ_NUM_MAX is already defined
#endif
#define ETHTSYN_SEQ_NUM_MAX 0xFFFFU /* Maximum of the 16 bit sequence number. */

#if (defined ETHTSYN_INV_BUFIDX)
#error ETHTSYN_INV_BUFIDX is already defined
#endif
/* Invalid buffer index */
/* BufIdx is Eth_BufIdxType -> used uint32 with maximum for invalid value. */
#define ETHTSYN_INV_BUFIDX 0xFFFFFFFFU

#if (defined ETHTSYN_UNINIT)
#error ETHTSYN_UNINIT is already defined
#endif
/* Check if module is initialized properly */
#define ETHTSYN_UNINIT (EthTSyn_RootCfgPtr == NULL_PTR)

#if (defined ETHTSYN_INV_DEBOUNCE_VALUE)
#error ETHTSYN_INV_DEBOUNCE_VALUE is already defined
#endif
/* Invalid debounce value */
/* DebounceTime is uint32 with maximum for invalid value. */
#define ETHTSYN_INV_DEBOUNCE_VALUE 0xFFFFFFFFU

#if (defined ETHTSYN_SC_MAXLIMIT)
#error ETHTSYN_SC_MAXLIMIT is already defined
#endif
/* GlobalTimeSequenceCounterJumpWidth is limited by uint16 max value. */
#define ETHTSYN_SC_MAXLIMIT 0xFFFFU

#if (defined ETHTSYN_STBM_TIMEOUT) /* to prevent double declaration */
#error ETHTSYN_STBM_TIMEOUT is already defined
#endif /* if (defined ETHTSYN_STBM_TIMEOUT) */
#define ETHTSYN_STBM_TIMEOUT  (1U)

#if (defined ETHTSYN_DELAY_ASYMMETRY)
#error ETHTSYN_DELAY_ASYMMETRY is already defined
#endif
/* Delay asym is not used in the current implementation. */
/* Added for further development. */
#define ETHTSYN_DELAY_ASYMMETRY 0U

/*====== Pdelay calculation ======*/

#if (defined ETHTSYN_PTP_HEADER_SIZE)
#error ETHTSYN_PTP_HEADER_SIZE is already defined
#endif
#define ETHTSYN_PTP_HEADER_SIZE 34U /* PTP header size is 34 bytes. */

#if (defined ETHTSYN_FUP_TLV_SIZE)
#error ETHTSYN_FUP_TLV_SIZE is already defined
#endif
#define ETHTSYN_FUP_TLV_SIZE 32U /* Follow up TLV size is 32 bytes. */

#if (defined ETHTSYN_RESERVED_10BYTES)
#error ETHTSYN_RESERVED_10BYTES is already defined
#endif
#define ETHTSYN_RESERVED_10BYTES 10U /* 10 bytes reserved space. */

/* ====== PTP header values ====== */
#if (defined ETHTSYN_PTP_HEADER_TRANS_SPEC_UN)
#error ETHTSYN_PTP_HEADER_TRANS_SPEC_UN is already defined
#endif
/* Transport specific upper nibble value (for or conjunction) (See 802.1AS-2011 Ch 10.5.2.2.1) */
#define ETHTSYN_PTP_HEADER_TRANS_SPEC_UN 0x10U

/* Message type (See 802.1AS-2011 Ch 11.4.2.1) */
/* !LINKSTO EthTSyn.PRS_TS_00028, 1 */
#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_SYNC)
#error ETHTSYN_PTP_HEADER_MSGTYPE_SYNC is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_SYNC 0x00U

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ)
#error ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ 0x02U

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ)
#error ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ 0x01U

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP)
#error ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP 0x03U

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP)
#error ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP 0x09U

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_FUP)
#error ETHTSYN_PTP_HEADER_MSGTYPE_FUP is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_FUP 0x08U

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP)
#error ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP 0x0AU

#if (defined ETHTSYN_PTP_HEADER_MSGTYPE_ANNOUNCE)
#error ETHTSYN_PTP_HEADER_MSGTYPE_ANNOUNCE is already defined
#endif
#define ETHTSYN_PTP_HEADER_MSGTYPE_ANNOUNCE 0x0BU

#if (defined ETHTSYN_PTP_HEADER_VERSION)
#error ETHTSYN_PTP_HEADER_VERSION is already defined
#endif
#define ETHTSYN_PTP_HEADER_VERSION 0x02U /* PTP version (See 802.1AS-2011 Ch 10.5.2.2.3) */

#if (defined ETHTSYN_PTP1588_HEADER_VERSION)
#error ETHTSYN_PTP1588_HEADER_VERSION is already defined
#endif
#define ETHTSYN_PTP1588_HEADER_VERSION 0x12U /* PTP IEEE1588_V2 version */

#if (defined ETHTSYN_PTP1588_SYNC_FUP_PAYLOADSIZE)
#error ETHTSYN_PTP1588_SYNC_FUP_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP1588_SYNC_FUP_PAYLOADSIZE 10U /* PTP IEEE1588_V2 Payload Length */

#if (defined ETHTSYN_PTP1588_CLEAR_TIMESCALE_BIT)
#error ETHTSYN_PTP1588_CLEAR_TIMESCALE_BIT is already defined
#endif
#define ETHTSYN_PTP1588_CLEAR_TIMESCALE_BIT 0xF7U /* PTP IEEE1588_V2 Timescale bit  */

#if (defined ETHTSYN_PTP_HEADER_DOMAIN)
#error ETHTSYN_PTP_HEADER_DOMAIN is already defined
#endif
#define ETHTSYN_PTP_HEADER_DOMAIN 0x00U /* Domain number (See 802.1AS-2011 Ch 8.1) */

#if (defined ETHTSYN_PTP_HEADER_RESERVED)
#error ETHTSYN_PTP_HEADER_RESERVED is already defined
#endif
#define ETHTSYN_PTP_HEADER_RESERVED 0x00U

#if (defined ETHTSYN_PTP_HEADER_FLAG_ONESTEP)
#error ETHTSYN_PTP_HEADER_FLAG_ONESTEP is already defined
#endif
#define ETHTSYN_PTP_HEADER_FLAG_ONESTEP 0x0001U /* Bit 1 is FALSE (See 802.1AS-2011 Ch 11.4.2.3) */

#if (defined ETHTSYN_PTP_HEADER_FLAG_TWOSTEP)
#error ETHTSYN_PTP_HEADER_FLAG_TWOSTEP is already defined
#endif
#define ETHTSYN_PTP_HEADER_FLAG_TWOSTEP 0x0002U /* Set bit 1 (See 802.1AS-2011 Ch 11.4.2.3) */

#if (defined ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE)
#error ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE is already defined
#endif
#define ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE 0x0800U /* Set bit (See 802.1AS-2011 Ch 10.5.2.2.6) */

#if (defined ETHTSYN_PTP_HEADER_NOFLAGS)
#error ETHTSYN_PTP_HEADER_NOFLAGS is already defined
#endif
#define ETHTSYN_PTP_HEADER_NOFLAGS 0x0000U

/* EUI-48 defined bytes of the source clock identity. */
#if (defined ETHTSYN_PTP_HEADER_EUI48_IDX3_SRCPORTIDENTITY)
#error ETHTSYN_PTP_HEADER_EUI48_IDX3_SRCPORTIDENTITY is already defined
#endif
#define ETHTSYN_PTP_HEADER_EUI48_IDX3_SRCPORTIDENTITY 0xFFU

#if (defined ETHTSYN_PTP_HEADER_EUI48_IDX4_SRCPORTIDENTITY)
#error ETHTSYN_PTP_HEADER_EUI48_IDX4_SRCPORTIDENTITY is already defined
#endif
#define ETHTSYN_PTP_HEADER_EUI48_IDX4_SRCPORTIDENTITY 0xFEU

#if (defined ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED)
#error ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED is already defined
#endif
/* Log message interval reserved value for Pdelay_Resp and Pdelay_Resp_Follow_Up
   (See 802.1AS-2011 Ch 11.4.2.8) */
#define ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED 0x7FU

/* Control field (See 802.1AS-2011 Ch 11.4.2.7) */
#if (defined ETHTSYN_PTP_HEADER_CONTROL_SYNC)
#error ETHTSYN_PTP_HEADER_CONTROL_SYNC is already defined
#endif
#define ETHTSYN_PTP_HEADER_CONTROL_SYNC 0x00U

#if (defined ETHTSYN_PTP_HEADER_CONTROL_FUP)
#error ETHTSYN_PTP_HEADER_CONTROL_FUP is already defined
#endif
#define ETHTSYN_PTP_HEADER_CONTROL_FUP 0x02U

#if (defined ETHTSYN_PTP_HEADER_CONTROL_PDELAY)
#error ETHTSYN_PTP_HEADER_CONTROL_PDELAY is already defined
#endif
#define ETHTSYN_PTP_HEADER_CONTROL_PDELAY 0x05U /* All Pdealy frames */

#if (defined ETHTSYN_PTP_HEADER_CONTROL_DELAYREQ)
#error ETHTSYN_PTP_HEADER_CONTROL_DELAYREQ is already defined
#endif
#define ETHTSYN_PTP_HEADER_CONTROL_DELAYREQ 0x01U /* (See IEEE1588_V2 Ch 13.3.2.13) */

#if (defined ETHTSYN_PTP_HEADER_CONTROL_DELAYRESP)
#error ETHTSYN_PTP_HEADER_CONTROL_DELAYRESP is already defined
#endif
#define ETHTSYN_PTP_HEADER_CONTROL_DELAYRESP 0x03U /* (See IEEE1588_V2 Ch 13.3.2.13) */

#if (defined ETHTSYN_PTP_HEADER_CONTROL_ANNOUNCE)
#error ETHTSYN_PTP_HEADER_CONTROL_ANNOUNCE is already defined
#endif
#define ETHTSYN_PTP_HEADER_CONTROL_ANNOUNCE 0x05U /* (See 802.1AS-2011 Ch 10.5.2.2.10) */


/* ====== Follow Up TLV values ====== */

#if (defined ETHTSYN_FUP_TLV_TYPE_1)
#error ETHTSYN_FUP_TLV_TYPE_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_TYPE_1 0x00U /* TLV type (See 802.1AS-2011 Ch 11.4.4.3.2) */

#if (defined ETHTSYN_FUP_TLV_TYPE_0)
#error ETHTSYN_FUP_TLV_TYPE_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_TYPE_0 0x03U

#if (defined ETHTSYN_FUP_TLV_LENGTH_1)
#error ETHTSYN_FUP_TLV_LENGTH_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_LENGTH_1 0U /* Length (See 802.1AS-2011 Ch 11.4.4.3.3) */

#if (defined ETHTSYN_FUP_TLV_LENGTH_0)
#error ETHTSYN_FUP_TLV_LENGTH_0 is already defined
#endif
/* Value is strange since TLV is 32 bytes. Maybe the bytes after length field are counted. */
#define ETHTSYN_FUP_TLV_LENGTH_0 28U

#if (defined ETHTSYN_FUP_TLV_ORGID_2)
#error ETHTSYN_FUP_TLV_ORGID_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_ORGID_2 0x00U /* Organization ID (See 802.1AS-2011 Ch 11.4.4.3.4) */

#if (defined ETHTSYN_FUP_TLV_ORGID_1)
#error ETHTSYN_FUP_TLV_ORGID_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_ORGID_1 0x80U

#if (defined ETHTSYN_FUP_TLV_ORGID_0)
#error ETHTSYN_FUP_TLV_ORGID_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_ORGID_0 0xC2U

/* Organization sub type (See 802.1AS-2011 Ch 11.4.4.3.5) */
#if (defined ETHTSYN_FUP_TLV_ORG_SUBTYPE_2)
#error ETHTSYN_FUP_TLV_ORG_SUBTYPE_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_ORG_SUBTYPE_2 0U

#if (defined ETHTSYN_FUP_TLV_ORG_SUBTYPE_1)
#error ETHTSYN_FUP_TLV_ORG_SUBTYPE_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_ORG_SUBTYPE_1 0U

#if (defined ETHTSYN_FUP_TLV_ORG_SUBTYPE_0)
#error ETHTSYN_FUP_TLV_ORG_SUBTYPE_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_ORG_SUBTYPE_0 1U

/* Grand master time base indicator */
#if (defined ETHTSYN_FUP_TLV_GM_TIMEBASE_IND_1)
#error ETHTSYN_FUP_TLV_GM_TIMEBASE_IND_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_GM_TIMEBASE_IND_1 0U

#if (defined ETHTSYN_FUP_TLV_GM_TIMEBASE_IND_0)
#error ETHTSYN_FUP_TLV_GM_TIMEBASE_IND_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_GM_TIMEBASE_IND_0 0U /* Wireshark from Extreme Switch */

/* Byte masks */
#if (defined ETHTSYN_32BIT_MASK0_LSB)
#error ETHTSYN_32BIT_MASK0_LSB is already defined
#endif
#define ETHTSYN_32BIT_MASK0_LSB (uint32) 0x000000FFU

#if (defined ETHTSYN_32BIT_MASK1)
#error ETHTSYN_32BIT_MASK1 is already defined
#endif
#define ETHTSYN_32BIT_MASK1 (uint32) 0x0000FF00U

#if (defined ETHTSYN_32BIT_MASK2)
#error ETHTSYN_32BIT_MASK2 is already defined
#endif
#define ETHTSYN_32BIT_MASK2 (uint32) 0x00FF0000U

#if (defined ETHTSYN_32BIT_MASK3_MSB)
#error ETHTSYN_32BIT_MASK3_MSB is already defined
#endif
#define ETHTSYN_32BIT_MASK3_MSB (uint32) 0xFF000000U

#if (defined ETHTSYN_16BIT_MASK_LSB)
#error ETHTSYN_16BIT_MASK_LSB is already defined
#endif
#define ETHTSYN_16BIT_MASK_LSB (uint16) 0x00FFU

#if (defined ETHTSYN_16BIT_MASK_MSB)
#error ETHTSYN_16BIT_MASK_MSB is already defined
#endif
#define ETHTSYN_16BIT_MASK_MSB (uint16) 0xFF00U

#if (defined ETHTSYN_8BIT_MASK_LN)
#error ETHTSYN_8BIT_MASK_LN is already defined
#endif
#define ETHTSYN_8BIT_MASK_LN (uint8) 0x0FU /* Mask for lower nibble. */

#if (defined ETHTSYN_8BIT_MASK_UN)
#error ETHTSYN_8BIT_MASK_UN is already defined
#endif
#define ETHTSYN_8BIT_MASK_UN (uint8) 0xF0U /* Mask for upper nibble. */

/* Bit masks */
#if (defined ETHTSYN_32BIT_MASK_BIT31)
#error ETHTSYN_32BIT_MASK_BIT31 is already defined
#endif
#define ETHTSYN_32BIT_MASK_BIT31 (uint32) 0x80000000U /* Mask to get bit 31 (MSB) of 32 bit var.*/

#if (defined ETHTSYN_16BIT_MASK_BIT15)
#error ETHTSYN_16BIT_MASK_BIT15 is already defined
#endif
#define ETHTSYN_16BIT_MASK_BIT15 (uint16) 0x8000U /* Mask to get bit 15 (MSB) of 16 bit var.*/

/* ====== PTP frame payload sizes ====== */
#if (defined ETHTSYN_PTP_SYNC_PAYLOADSIZE)
#error ETHTSYN_PTP_SYNC_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_SYNC_PAYLOADSIZE 10U /* (See 802.1AS-2011 Ch 11.4.3) */

#if (defined ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE)
#error ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE 42U /* (See 802.1AS-2011 Ch 11.4.4.1) */

#if (defined ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE)
#error ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE 20U /* (See 802.1AS-2011 Ch 11.4.5) */

#if (defined ETHTSYN_PTP_DELAY_REQ_PAYLOADSIZE)
#error ETHTSYN_PTP_DELAY_REQ_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_DELAY_REQ_PAYLOADSIZE 10U /* (See IEEE1588_V2 Ch 13.6.1) */

#if (defined ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE)
#error ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE 20U /* (See 802.1AS-2011 Ch 11.4.6.1) */

#if (defined ETHTSYN_PTP_DELAY_RESP_PAYLOADSIZE)
#error ETHTSYN_PTP_DELAY_RESP_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_DELAY_RESP_PAYLOADSIZE 20U /* (See IEEE1588_V2 Ch 13.8.1) */

#if (defined ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE)
#error ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE 20U /* (See 802.1AS-2011 Ch 11.4.7.1) */

#if (defined ETHTSYN_PTP_ANNOUNCE_PAYLOADSIZE)
#error ETHTSYN_PTP_ANNOUNCE_PAYLOADSIZE is already defined
#endif
#define ETHTSYN_PTP_ANNOUNCE_PAYLOADSIZE 42U /* (See 802.1AS-2011 Ch 10.5.3.1) (N = 1) */

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_SIZE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_SIZE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_SIZE 14U

/* ====== AUTH_CHALLENGE Tlv byte numbers ====== */
#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B0_TYPE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B0_TYPE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B0_TYPE 0U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B1_TYPE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B1_TYPE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B1_TYPE 1U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B2_LENGTH)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B2_LENGTH is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B2_LENGTH 2U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B3_LENGTH)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B3_LENGTH is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B3_LENGTH 3U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B4_CHLTYPE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B4_CHLTYPE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B4_CHLTYPE 4U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B5_RESERVED)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B5_RESERVED is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B5_RESERVED 5U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B6_REQNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B6_REQNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B6_REQNONCE 6U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B7_REQNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B7_REQNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B7_REQNONCE 7U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B8_REQNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B8_REQNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B8_REQNONCE 8U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B9_REQNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B9_REQNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B9_REQNONCE 9U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B10_RESPNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B10_RESPNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B10_RESPNONCE 10U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B11_RESPNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B11_RESPNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B11_RESPNONCE 11U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B12_RESPNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B12_RESPNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B12_RESPNONCE 12U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_B13_RESPNONCE)
#error ETHTSYN_AUTH_CHALLENGE_TLV_B9_REQNONCE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_B13_RESPNONCE 13U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_0)
#error ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_0 is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_0 0x20U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_1)
#error ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_1 is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_1 0x01U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_0)
#error ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_0 is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_0 0x00U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_1)
#error ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_1 is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_1 0x0EU

#if (defined ETHTSYN_AUTH_CHALLENGE_RESPONSE_TYPE)
#error ETHTSYN_AUTH_CHALLENGE_RESPONSE_TYPE is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_RESPONSE_TYPE 0x02U

#if (defined ETHTSYN_AUTH_CHALLENGE_TLV_RESERVED)
#error ETHTSYN_AUTH_CHALLENGE_TLV_RESERVED is already defined
#endif
#define ETHTSYN_AUTH_CHALLENGE_TLV_RESERVED 0x00U

/* ====== PTP header byte numbers ====== */
#if (defined ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE)
#error ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE is already defined
#endif
#define ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE 0U /* Message type (lower nibble) */

#if (defined ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC)
#error ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC is already defined
#endif
#define ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC 0U /* Transport specific (upper nibble) */

#if (defined ETHTSYN_PTP_HEADER_B1_PTPVERSION)
#error ETHTSYN_PTP_HEADER_B1_PTPVERSION is already defined
#endif
#define ETHTSYN_PTP_HEADER_B1_PTPVERSION 1U /* PTP version */

#if (defined ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1)
#error ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1 2U /* 16 bit message length */

#if (defined ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0)
#error ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0 3U

#if (defined ETHTSYN_PTP_HEADER_B4_DOMAIN)
#error ETHTSYN_PTP_HEADER_B4_DOMAIN is already defined
#endif
#define ETHTSYN_PTP_HEADER_B4_DOMAIN 4U /* Domain number */

#if (defined ETHTSYN_PTP_HEADER_B5_RESERVED)
#error ETHTSYN_PTP_HEADER_B5_RESERVED is already defined
#endif
#define ETHTSYN_PTP_HEADER_B5_RESERVED 5U

#if (defined ETHTSYN_PTP_HEADER_B6_FLAGS_0)
#error ETHTSYN_PTP_HEADER_B6_FLAGS_0 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B6_FLAGS_0 6U /* 16 bit flags */

#if (defined ETHTSYN_PTP_HEADER_B7_FLAGS_1)
#error ETHTSYN_PTP_HEADER_B7_FLAGS_1 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B7_FLAGS_1 7U

#if (defined ETHTSYN_PTP_HEADER_B8_CORRFIELD_0)
#error ETHTSYN_PTP_HEADER_B8_CORRFIELD_0 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B8_CORRFIELD_0 8U /* 8 byte correction field */

#if (defined ETHTSYN_PTP_HEADER_B9_CORRFIELD_1)
#error ETHTSYN_PTP_HEADER_B9_CORRFIELD_1 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B9_CORRFIELD_1 9U

#if (defined ETHTSYN_PTP_HEADER_B10_CORRFIELD_2)
#error ETHTSYN_PTP_HEADER_B10_CORRFIELD_2 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B10_CORRFIELD_2 10U

#if (defined ETHTSYN_PTP_HEADER_B11_CORRFIELD_3)
#error ETHTSYN_PTP_HEADER_B11_CORRFIELD_3 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B11_CORRFIELD_3 11U

#if (defined ETHTSYN_PTP_HEADER_B12_CORRFIELD_4)
#error ETHTSYN_PTP_HEADER_B12_CORRFIELD_4 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B12_CORRFIELD_4 12U

#if (defined ETHTSYN_PTP_HEADER_B13_CORRFIELD_5)
#error ETHTSYN_PTP_HEADER_B13_CORRFIELD_5 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B13_CORRFIELD_5 13U

#if (defined ETHTSYN_PTP_HEADER_B14_CORRFIELD_6)
#error ETHTSYN_PTP_HEADER_B14_CORRFIELD_6 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B14_CORRFIELD_6 14U

#if (defined ETHTSYN_PTP_HEADER_B15_CORRFIELD_7)
#error ETHTSYN_PTP_HEADER_B15_CORRFIELD_7 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B15_CORRFIELD_7 15U

#if (defined ETHTSYN_PTP_HEADER_B16_RESERVED_0)
#error ETHTSYN_PTP_HEADER_B16_RESERVED_0 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B16_RESERVED_0 16U

#if (defined ETHTSYN_PTP_HEADER_B17_RESERVED_1)
#error ETHTSYN_PTP_HEADER_B17_RESERVED_1 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B17_RESERVED_1 17U

#if (defined ETHTSYN_PTP_HEADER_B18_RESERVED_2)
#error ETHTSYN_PTP_HEADER_B18_RESERVED_2 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B18_RESERVED_2 18U

#if (defined ETHTSYN_PTP_HEADER_B19_RESERVED_3)
#error ETHTSYN_PTP_HEADER_B19_RESERVED_3 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B19_RESERVED_3 19U

#if (defined ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0)
#error ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0 20U /* 10 byte source port identity */

#if (defined ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1)
#error ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1 21U

#if (defined ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2)
#error ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2 22U

#if (defined ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3)
#error ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3 23U

#if (defined ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4)
#error ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4 24U

#if (defined ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5)
#error ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5 25U

#if (defined ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6)
#error ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6 26U

#if (defined ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7)
#error ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7 27U

#if (defined ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8)
#error ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8 28U

#if (defined ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9)
#error ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9 29U

#if (defined ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1)
#error ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1 30U /* 16 bit sequence number */

#if (defined ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0)
#error ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0 is already defined
#endif
#define ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0 31U

#if (defined ETHTSYN_PTP_HEADER_B32_CONTROL)
#error ETHTSYN_PTP_HEADER_B32_CONTROL is already defined
#endif
#define ETHTSYN_PTP_HEADER_B32_CONTROL 32U /* Control field. */

#if (defined ETHTSYN_PTP_HEADER_B33_LOGMSGINTERVAL)
#error ETHTSYN_PTP_HEADER_B33_LOGMSGINTERVAL is already defined
#endif
#define ETHTSYN_PTP_HEADER_B33_LOGMSGINTERVAL 33U /* Log message interval (till next Tx frame) */

/* ====== Follow up TLV ====== */
#if (defined ETHTSYN_FUP_TLV_B0_TYPE_1)
#error ETHTSYN_FUP_TLV_B0_TYPE_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B0_TYPE_1 0U /* 16 bit TLV Type */

#if (defined ETHTSYN_FUP_TLV_B1_TYPE_0)
#error ETHTSYN_FUP_TLV_B1_TYPE_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B1_TYPE_0 1U /* PTP version */

#if (defined ETHTSYN_FUP_TLV_B2_LENGTH_1)
#error ETHTSYN_FUP_TLV_B2_LENGTH_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B2_LENGTH_1 2U /* 16 bit TLV length */

#if (defined ETHTSYN_FUP_TLV_B3_LENGTH_0)
#error ETHTSYN_FUP_TLV_B3_LENGTH_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B3_LENGTH_0 3U

#if (defined ETHTSYN_FUP_TLV_B4_ORGID_2)
#error ETHTSYN_FUP_TLV_B4_ORGID_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_B4_ORGID_2 4U /* 3 bytes organization ID */

#if (defined ETHTSYN_FUP_TLV_B5_ORGID_1)
#error ETHTSYN_FUP_TLV_B5_ORGID_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B5_ORGID_1 5U

#if (defined ETHTSYN_FUP_TLV_B6_ORGID_0)
#error ETHTSYN_FUP_TLV_B6_ORGID_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B6_ORGID_0 6U

#if (defined ETHTSYN_FUP_TLV_B7_ORG_SUBTYPE_2)
#error ETHTSYN_FUP_TLV_B7_ORG_SUBTYPE_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_B7_ORG_SUBTYPE_2 7U /* 24 bit organization sub type. */

#if (defined ETHTSYN_FUP_TLV_B8_ORG_SUBTYPE_1)
#error ETHTSYN_FUP_TLV_B8_ORG_SUBTYPE_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B8_ORG_SUBTYPE_1 8U

#if (defined ETHTSYN_FUP_TLV_B9_ORG_SUBTYPE_0)
#error ETHTSYN_FUP_TLV_B9_ORG_SUBTYPE_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B9_ORG_SUBTYPE_0 9U

#if (defined ETHTSYN_FUP_TLV_B10_CSRO_3)
#error ETHTSYN_FUP_TLV_B10_CSRO_3 is already defined
#endif
#define ETHTSYN_FUP_TLV_B10_CSRO_3 10U /* 32 bit cumulativeScaledRateOffset */

#if (defined ETHTSYN_FUP_TLV_B11_CSRO_2)
#error ETHTSYN_FUP_TLV_B11_CSRO_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_B11_CSRO_2 11U

#if (defined ETHTSYN_FUP_TLV_B12_CSRO_1)
#error ETHTSYN_FUP_TLV_B12_CSRO_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B12_CSRO_1 12U

#if (defined ETHTSYN_FUP_TLV_B13_CSRO_0)
#error ETHTSYN_FUP_TLV_B13_CSRO_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B13_CSRO_0 13U

#if (defined ETHTSYN_FUP_TLV_B14_GM_TIMEBASEIND_1)
#error ETHTSYN_FUP_TLV_B14_GM_TIMEBASEIND_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B14_GM_TIMEBASEIND_1 14U /* 16 bit grand master time base indicator */

#if (defined ETHTSYN_FUP_TLV_B15_GM_TIMEBASEIND_0)
#error ETHTSYN_FUP_TLV_B15_GM_TIMEBASEIND_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B15_GM_TIMEBASEIND_0 15U

#if (defined ETHTSYN_FUP_TLV_B16_GM_PH_CHG_0)
#error ETHTSYN_FUP_TLV_B16_GM_PH_CHG_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B16_GM_PH_CHG_0 16U /* 12 bytes  last grand master phase change */

#if (defined ETHTSYN_FUP_TLV_B17_GM_PH_CHG_1)
#error ETHTSYN_FUP_TLV_B17_GM_PH_CHG_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B17_GM_PH_CHG_1 17U

#if (defined ETHTSYN_FUP_TLV_B18_GM_PH_CHG_2)
#error ETHTSYN_FUP_TLV_B18_GM_PH_CHG_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_B18_GM_PH_CHG_2 18U

#if (defined ETHTSYN_FUP_TLV_B19_GM_PH_CHG_3)
#error ETHTSYN_FUP_TLV_B19_GM_PH_CHG_3 is already defined
#endif
#define ETHTSYN_FUP_TLV_B19_GM_PH_CHG_3 19U

#if (defined ETHTSYN_FUP_TLV_B20_GM_PH_CHG_4)
#error ETHTSYN_FUP_TLV_B20_GM_PH_CHG_4 is already defined
#endif
#define ETHTSYN_FUP_TLV_B20_GM_PH_CHG_4 20U

#if (defined ETHTSYN_FUP_TLV_B21_GM_PH_CHG_5)
#error ETHTSYN_FUP_TLV_B21_GM_PH_CHG_5 is already defined
#endif
#define ETHTSYN_FUP_TLV_B21_GM_PH_CHG_5 21U

#if (defined ETHTSYN_FUP_TLV_B22_GM_PH_CHG_6)
#error ETHTSYN_FUP_TLV_B22_GM_PH_CHG_6 is already defined
#endif
#define ETHTSYN_FUP_TLV_B22_GM_PH_CHG_6 22U

#if (defined ETHTSYN_FUP_TLV_B23_GM_PH_CHG_7)
#error ETHTSYN_FUP_TLV_B23_GM_PH_CHG_7 is already defined
#endif
#define ETHTSYN_FUP_TLV_B23_GM_PH_CHG_7 23U

#if (defined ETHTSYN_FUP_TLV_B24_GM_PH_CHG_8)
#error ETHTSYN_FUP_TLV_B24_GM_PH_CHG_8 is already defined
#endif
#define ETHTSYN_FUP_TLV_B24_GM_PH_CHG_8 24U

#if (defined ETHTSYN_FUP_TLV_B25_GM_PH_CHG_9)
#error ETHTSYN_FUP_TLV_B25_GM_PH_CHG_9 is already defined
#endif
#define ETHTSYN_FUP_TLV_B25_GM_PH_CHG_9 25U

#if (defined ETHTSYN_FUP_TLV_B26_GM_PH_CHG_10)
#error ETHTSYN_FUP_TLV_B26_GM_PH_CHG_10 is already defined
#endif
#define ETHTSYN_FUP_TLV_B26_GM_PH_CHG_10 26U

#if (defined ETHTSYN_FUP_TLV_B27_GM_PH_CHG_11)
#error ETHTSYN_FUP_TLV_B27_GM_PH_CHG_11 is already defined
#endif
#define ETHTSYN_FUP_TLV_B27_GM_PH_CHG_11 27U

#if (defined ETHTSYN_FUP_TLV_B28_GM_FREQ_CHG_3)
#error ETHTSYN_FUP_TLV_B28_GM_FREQ_CHG_3 is already defined
#endif
#define ETHTSYN_FUP_TLV_B28_GM_FREQ_CHG_3 28U /* 32 scaled last grand master frequency change */

#if (defined ETHTSYN_FUP_TLV_B29_GM_FREQ_CHG_2)
#error ETHTSYN_FUP_TLV_B29_GM_FREQ_CHG_2 is already defined
#endif
#define ETHTSYN_FUP_TLV_B29_GM_FREQ_CHG_2 29U

#if (defined ETHTSYN_FUP_TLV_B30_GM_FREQ_CHG_1)
#error ETHTSYN_FUP_TLV_B30_GM_FREQ_CHG_1 is already defined
#endif
#define ETHTSYN_FUP_TLV_B30_GM_FREQ_CHG_1 30U

#if (defined ETHTSYN_FUP_TLV_B31_GM_FREQ_CHG_0)
#error ETHTSYN_FUP_TLV_B31_GM_FREQ_CHG_0 is already defined
#endif
#define ETHTSYN_FUP_TLV_B31_GM_FREQ_CHG_0 31U

/* ====== AUTOSAR TLV header data ====== */
#if (defined ETHTSYN_FUP_EXT_TLV_LENGTH_0)
#error ETHTSYN_FUP_EXT_TLV_LENGTH_0 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_LENGTH_0 6U

#if (defined ETHTSYN_FUP_EXT_TLV_LENGTH_1)
#error ETHTSYN_FUP_EXT_TLV_LENGTH_1 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_LENGTH_1 0U

#if (defined ETHTSYN_FUP_EXT_TLV_ORGID_2)
#error ETHTSYN_FUP_EXT_TLV_ORGID_2 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_ORGID_2 0x1AU

#if (defined ETHTSYN_FUP_EXT_TLV_ORGID_1)
#error ETHTSYN_FUP_EXT_TLV_ORGID_1 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_ORGID_1 0x75U

#if (defined ETHTSYN_FUP_EXT_TLV_ORGID_0)
#error ETHTSYN_FUP_EXT_TLV_ORGID_0 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_ORGID_0 0xFBU

#if (defined ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_2)
#error ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_2 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_2 0x60U

#if (defined ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_1)
#error ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_1 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_1 0x56U

#if (defined ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_0)
#error ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_0 is already defined
#endif
#define ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_0 0x76U

/* ====== AUTOSAR follow up sub TLV ====== */
#if (defined ETHTSYN_FUP_SUBTLV_TIME_SIZE)
#error ETHTSYN_FUP_SUBTLV_TIME_SIZE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_SIZE 5U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_B0_TYPE)
#error ETHTSYN_FUP_SUBTLV_TIME_B0_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_B0_TYPE 0U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_B1_LENGTH)
#error ETHTSYN_FUP_SUBTLV_TIME_B1_LENGTH] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_B1_LENGTH 1U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS)
#error ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS 2U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_B3_CRC_TIME_0)
#error ETHTSYN_FUP_SUBTLV_TIME_B3_CRC_TIME_0 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_B3_CRC_TIME_0 3U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1)
#error ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1 4U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_TYPE)
#error ETHTSYN_FUP_SUBTLV_TIME_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_TYPE 0x28U

#if (defined ETHTSYN_FUP_SUBTLV_TIME_LENGTH)
#error ETHTSYN_FUP_SUBTLV_TIME_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIME_LENGTH 3U

#if (defined ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH)
#error ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH is already defined
#endif
#define ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH 10U

#if (defined ETHTSYN_FUP_SUBTLV_HEADER_SIZE)
#error ETHTSYN_FUP_SUBTLV_HEADER_SIZE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_HEADER_SIZE 2U

#if (defined ETHTSYN_FUP_AUTOSAR_TLV_HEADER_START_ADDR)
#error ETHTSYN_FUP_AUTOSAR_TLV_HEADER_START_ADDR is already defined
#endif
#define ETHTSYN_FUP_AUTOSAR_TLV_HEADER_START_ADDR 76U

#if (defined ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR)
#error ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR is already defined
#endif
#define ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR 86U

#if (defined ETHTSYN_MESSAGE_LENGTH_BIT_MASK)
#error ETHTSYN_MESSAGE_LENGTH_BIT_MASK is already defined
#endif
#define ETHTSYN_MESSAGE_LENGTH_BIT_MASK 0x01U

#if (defined ETHTSYN_DOMAIN_NUMBER_BIT_MASK)
#error ETHTSYN_DOMAIN_NUMBER_BIT_MASK is already defined
#endif
#define ETHTSYN_DOMAIN_NUMBER_BIT_MASK 0x02U

#if (defined ETHTSYN_CORRECTION_FIELD_BIT_MASK)
#error ETHTSYN_CORRECTION_FIELD_BIT_MASK is already defined
#endif
#define ETHTSYN_CORRECTION_FIELD_BIT_MASK 0x04U

#if (defined ETHTSYN_SOURCE_PORT_IDENTITY_BIT_MASK)
#error ETHTSYN_SOURCE_PORT_IDENTITY_BIT_MASK is already defined
#endif
#define ETHTSYN_SOURCE_PORT_IDENTITY_BIT_MASK 0x08U

#if (defined ETHTSYN_SEQUENCE_ID_BIT_MASK)
#error ETHTSYN_SEQUENCE_ID_BIT_MASK is already defined
#endif
#define ETHTSYN_SEQUENCE_ID_BIT_MASK 0x10U

#if (defined ETHTSYN_PRECISE_ORIGIN_TIMESTAMP_BIT_MASK)
#error ETHTSYN_PRECISE_ORIGIN_TIMESTAMP_BIT_MASK is already defined
#endif
#define ETHTSYN_PRECISE_ORIGIN_TIMESTAMP_BIT_MASK 0x20U

/* ====== AUTOSAR follow-up STATUS sub TLV ====== */
#if (defined ETHTSYN_FUP_SUBTLV_STATUS_SIZE)
#error ETHTSYN_FUP_SUBTLV_STATUS_SIZE] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_SIZE 4U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_B0_TYPE)
#error ETHTSYN_FUP_SUBTLV_STATUS_B0_TYPE] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_B0_TYPE 0U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_B1_LENGTH)
#error ETHTSYN_FUP_SUBTLV_STATUS_B1_LENGTH] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_B1_LENGTH 1U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS)
#error ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS 2U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_B3_CRC_STATUS)
#error ETHTSYN_FUP_SUBTLV_STATUS_B3_CRC_STATUS is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_B3_CRC_STATUS 3U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_NOT_SECURED_TYPE)
#error ETHTSYN_FUP_SUBTLV_STATUS_NOT_SECURED_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_NOT_SECURED_TYPE 0x51U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_SECURED_TYPE)
#error ETHTSYN_FUP_SUBTLV_STATUS_SECURED_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_SECURED_TYPE 0x50U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_LENGTH)
#error ETHTSYN_FUP_SUBTLV_STATUS_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_LENGTH 2U

#if (defined ETHTSYN_FUP_SUBTLV_STATUS_CRC_STATUS)
#error ETHTSYN_FUP_SUBTLV_STATUS_CRC_STATUS is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_STATUS_CRC_STATUS 0U

#if (defined ETHTSYN_SYNC_TO_SUBDOMAIN)
#error ETHTSYN_SYNC_TO_SUBDOMAIN is already defined
#endif
#define ETHTSYN_SYNC_TO_SUBDOMAIN 1U

#if (defined ETHTSYN_SYNC_TO_GTM)
#error ETHTSYN_SYNC_TO_GTM is already defined
#endif
#define ETHTSYN_SYNC_TO_GTM 0U

#if (defined ETHTSYN_GLOBAL_TIME_BASE_MASK)
#error ETHTSYN_GLOBAL_TIME_BASE_MASK is already defined
#endif
#define ETHTSYN_GLOBAL_TIME_BASE_MASK  8U /* Global time base mask */

#if (defined ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM)
#error ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM is already defined
#endif
#define ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM  0x04U /* Sync to gateway mask */

#if (defined ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV)
#error ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV is already defined
#endif
#define ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV  0x01U /* Sync to gateway mask */

/* ====== AUTOSAR follow-up UserData sub TLV ====== */
#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_SIZE)
#error ETHTSYN_FUP_SUBTLV_USERDATA_SIZE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_SIZE 7U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH)
#error ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH 5U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_SECURED_TYPE)
#error ETHTSYN_FUP_SUBTLV_USERDATA_SECURED_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_SECURED_TYPE 0x60U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_NOT_SECURED_TYPE)
#error ETHTSYN_FUP_SUBTLV_USERDATA_NOT_SECURED_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_NOT_SECURED_TYPE 0x61U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B0_TYPE)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B0_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B0_TYPE 0U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B1_LENGTH)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B1_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B1_LENGTH 1U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH 2U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0 3U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1 4U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2 5U

#if (defined ETHTSYN_FUP_SUBTLV_USERDATA_B6_CRC_USERDATA)
#error ETHTSYN_FUP_SUBTLV_USERDATA_B6_CRC_USERDATA is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_USERDATA_B6_CRC_USERDATA 6U

/* ====== AUTOSAR follow-up OFS sub TLV ====== */
#if (defined ETHTSYN_FUP_SUBTLV_OFS_SIZE)
#error ETHTSYN_FUP_SUBTLV_OFS_SIZE] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_SIZE 19U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B0_TYPE)
#error ETHTSYN_FUP_SUBTLV_OFS_B0_TYPE] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B0_TYPE 0U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B1_LENGTH)
#error ETHTSYN_FUP_SUBTLV_OFS_B1_LENGTH] is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B1_LENGTH 1U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B2_TIMEDOMAIN)
#error ETHTSYN_FUP_SUBTLV_OFS_B2_TIMEDOMAIN is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B2_TIMEDOMAIN 2U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B3_TIMESEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B3_TIMESEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B3_TIMESEC 3U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B4_TIMESEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B4_TIMESEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B4_TIMESEC 4U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B5_TIMESEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B5_TIMESEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B5_TIMESEC 5U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B6_TIMESEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B6_TIMESEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B6_TIMESEC 6U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B7_TIMESEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B7_TIMESEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B7_TIMESEC 7U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B8_TIMESEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B8_TIMESEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B8_TIMESEC 8U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B9_TIMENSEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B9_TIMENSEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B9_TIMENSEC 9U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B10_TIMENSEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B10_TIMENSEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B10_TIMENSEC 10U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B11_TIMENSEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B11_TIMENSEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B11_TIMENSEC 11U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B12_TIMENSEC)
#error ETHTSYN_FUP_SUBTLV_OFS_B12_TIMENSEC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B12_TIMENSEC 12U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B13_STATUS)
#error ETHTSYN_FUP_SUBTLV_OFS_B13_STATUS is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B13_STATUS 13U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B14_USER_DATA_LENGTH)
#error ETHTSYN_FUP_SUBTLV_OFS_B14_USER_DATA_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B14_USER_DATA_LENGTH 14U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B15_USER_DATA_BYTE_0)
#error ETHTSYN_FUP_SUBTLV_OFS_B15_USER_DATA_BYTE_0 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B15_USER_DATA_BYTE_0 15U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B16_USER_DATA_BYTE_1)
#error ETHTSYN_FUP_SUBTLV_OFS_B16_USER_DATA_BYTE_1 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B16_USER_DATA_BYTE_1 16U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B17_USER_DATA_BYTE_2)
#error ETHTSYN_FUP_SUBTLV_OFS_B17_USER_DATA_BYTE_2 is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B17_USER_DATA_BYTE_2 17U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_B18_CRC)
#error ETHTSYN_FUP_SUBTLV_OFS_B18_CRC is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_B18_CRC 18U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_NOT_SECURED_TYPE)
#error ETHTSYN_FUP_SUBTLV_OFS_NOT_SECURED_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_NOT_SECURED_TYPE 0x34U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_SECURED_TYPE)
#error ETHTSYN_FUP_SUBTLV_OFS_SECURED_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_SECURED_TYPE 0x44U

#if (defined ETHTSYN_FUP_SUBTLV_OFS_LENGTH)
#error ETHTSYN_FUP_SUBTLV_OFS_LENGTH is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_OFS_LENGTH 17U


/* ====== AUTOSAR follow-up Icv sub TLV ====== */

#if (defined ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH)
#error ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH is already defined
#endif
#define ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH 4U

#if (defined ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_WITH_FV)
#error ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_WITH_FV is already defined
#endif
#define ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_WITH_FV 5U

#if (defined ETHTSYN_FUP_MAXLEN_SUBTLV_TIMEAUTH)
#error ETHTSYN_FUP_MAXLEN_SUBTLV_TIMEAUTH is already defined
#endif
#define ETHTSYN_FUP_MAXLEN_SUBTLV_TIMEAUTH 216U

#if (defined ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI)
#error ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI is already defined
#endif
#define ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI 2U

#if (defined ETHTSYN_FUP_LEN_FVL)
#error ETHTSYN_FUP_LEN_FVL is already defined
#endif
#define ETHTSYN_FUP_LEN_FVL 1U

#if (defined ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE)
#error ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE is already defined
#endif
#define ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE 0x70U

#if (defined ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI)
#error ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI is already defined
#endif
#define ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI 2U

#if (defined ETHTSYN_ICV_WITH_FV)
#error ETHTSYN_ICV_WITH_FV is already defined
#endif
#define ETHTSYN_ICV_WITH_FV 1U

#if (defined ETHTSYN_ICV_GENERATION_FAILED)
#error ETHTSYN_ICV_GENERATION_FAILED is already defined
#endif
#define ETHTSYN_ICV_GENERATION_FAILED 2U

#if (defined ETHTSYN_ICV_IN_MULTIPLE_SUBTLV)
#error ETHTSYN_ICV_IN_MULTIPLE_SUBTLV is already defined
#endif
#define ETHTSYN_ICV_IN_MULTIPLE_SUBTLV 4U

#if (defined ETHTSYN_TIMEAUTH_TLV_B0_TYPE)
#error ETHTSYN_TIMEAUTH_TLV_B0_TYPE is already defined
#endif
#define ETHTSYN_TIMEAUTH_TLV_B0_TYPE 0U

#if (defined ETHTSYN_TIMEAUTH_TLV_B1_LENGTH)
#error ETHTSYN_TIMEAUTH_TLV_B1_LENGTH is already defined
#endif
#define ETHTSYN_TIMEAUTH_TLV_B1_LENGTH 1U

#if (defined ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS)
#error ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS is already defined
#endif
#define ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS 2U

#if (defined ETHTSYN_TIMEAUTH_TLV_B3_SEQNR)
#error ETHTSYN_TIMEAUTH_TLV_B3_SEQNR is already defined
#endif
#define ETHTSYN_TIMEAUTH_TLV_B3_SEQNR 3U

#if (defined ETHTSYN_TIMEAUTH_TLV_B4_FVL)
#error ETHTSYN_TIMEAUTH_TLV_B4_FVL is already defined
#endif
#define ETHTSYN_TIMEAUTH_TLV_B4_FVL 4U

#if (defined ETHTSYN_TIMEAUTH_TLV_B5_FV)
#error ETHTSYN_TIMEAUTH_TLV_B5_FV is already defined
#endif
#define ETHTSYN_TIMEAUTH_TLV_B5_FV 5U

#if (defined ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITH_FVL)
#error ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITH_FVL is already defined
#endif
#define ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITH_FVL(freshness) (ETHTSYN_FUP_MAXLEN_SUBTLV_TIMEAUTH - ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI - ETHTSYN_FUP_LEN_FVL - (uint16)freshness)

#if (defined ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL)
#error ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL is already defined
#endif
#define ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL (ETHTSYN_FUP_MAXLEN_SUBTLV_TIMEAUTH - ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI)

#if (defined ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG)
#error ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG is already defined
#endif
#define ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(freshness) ((freshness != 0U)?(ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITH_FVL(freshness)):(ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL))

/* ====== Announce frame values ====== */

/* Time sync grand master priority (See 802.1AS-2011 Ch 10.5.3.2.2) */
#if (defined ETHTSYN_GM_PRIORITY1)
#error ETHTSYN_GM_PRIORITY1 is already defined
#endif
#define ETHTSYN_GM_PRIORITY1 246U

#if (defined ETHTSYN_GM_PRIORITY2)
#error ETHTSYN_GM_PRIORITY2 is already defined
#endif
#define ETHTSYN_GM_PRIORITY2 246U

#if (defined ETHTSYN_GM_CLOCK_CLASS)
#error ETHTSYN_GM_CLOCK_CLASS is already defined
#endif
/* Time sync grand master clockClass (See 802.1AS-2011 Ch 8.6.2.2) */
#define ETHTSYN_GM_CLOCK_CLASS 248U

#if (defined ETHTSYN_GM_CLOCK_ACCURANCY)
#error ETHTSYN_GM_CLOCK_ACCURANCY is already defined
#endif
/* Time sync grand master clockClass (See 802.1AS-2011 Ch 8.6.2.3) */
#define ETHTSYN_GM_CLOCK_ACCURANCY 254U

/* Time sync grand master offset scaled log variance (See 802.1AS-2011 Ch 8.6.2.4) */
#if (defined ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_1)
#error ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_1 is already defined
#endif
#define ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_1 0x41U /* 16 bit */

#if (defined ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_0)
#error ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_0 is already defined
#endif
#define ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_0 0x00U

#if(ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON)
#if (defined ETHTSYN_ANNOUNCE_TLV_TYPE_1)
#error ETHTSYN_ANNOUNCE_TLV_TYPE_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_TLV_TYPE_1 0x00U /* TLV type (See 802.1AS-2011 Ch 10.5.3.3.2) */

#if (defined ETHTSYN_ANNOUNCE_TLV_TYPE_0)
#error ETHTSYN_ANNOUNCE_TLV_TYPE_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_TLV_TYPE_0 0x08U

#if (defined ETHTSYN_ANNOUNCE_TLV_LENGTH_1)
#error ETHTSYN_ANNOUNCE_TLV_LENGTH_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_TLV_LENGTH_1 0U /* Length (See 802.1AS-2011 Ch 10.5.3.3.3) */

#if (defined ETHTSYN_ANNOUNCE_TLV_LENGTH_0)
#error ETHTSYN_ANNOUNCE_TLV_LENGTH_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_TLV_LENGTH_0 8U

/* ====== Announce frame Payload ====== */
#if (defined ETHTSYN_ANNOUNCE_PL_B09_RESERVED)
#error ETHTSYN_ANNOUNCE_PL_B09_RESERVED is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B09_RESERVED 9U

#if (defined ETHTSYN_ANNOUNCE_PL_B10_CUR_UTC_OFFSET_1)
#error ETHTSYN_ANNOUNCE_PL_B10_CUR_UTC_OFFSET_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B10_CUR_UTC_OFFSET_1 10U /* 16 bit */

#if (defined ETHTSYN_ANNOUNCE_PL_B11_CUR_UTC_OFFSET_0)
#error ETHTSYN_ANNOUNCE_PL_B11_CUR_UTC_OFFSET_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B11_CUR_UTC_OFFSET_0 11U

#if (defined ETHTSYN_ANNOUNCE_PL_B12_RESERVED)
#error ETHTSYN_ANNOUNCE_PL_B12_RESERVED is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B12_RESERVED 12U

#if (defined ETHTSYN_ANNOUNCE_PL_B13_GM_PRIO1)
#error ETHTSYN_ANNOUNCE_PL_B13_GM_PRIO1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B13_GM_PRIO1 13U

#if (defined ETHTSYN_ANNOUNCE_PL_B14_GM_CLK_QUAL_3)
#error ETHTSYN_ANNOUNCE_PL_B14_GM_CLK_QUAL_3 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B14_GM_CLK_QUAL_3 14U /* Type ClockQuality 4 byte */

#if (defined ETHTSYN_ANNOUNCE_PL_B15_GM_CLK_QUAL_2)
#error ETHTSYN_ANNOUNCE_PL_B15_GM_CLK_QUAL_2 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B15_GM_CLK_QUAL_2 15U

#if (defined ETHTSYN_ANNOUNCE_PL_B16_GM_CLK_QUAL_1)
#error ETHTSYN_ANNOUNCE_PL_B16_GM_CLK_QUAL_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B16_GM_CLK_QUAL_1 16U

#if (defined ETHTSYN_ANNOUNCE_PL_B17_GM_CLK_QUAL_0)
#error ETHTSYN_ANNOUNCE_PL_B17_GM_CLK_QUAL_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B17_GM_CLK_QUAL_0 17U

#if (defined ETHTSYN_ANNOUNCE_PL_B18_GM_PRIO2)
#error ETHTSYN_ANNOUNCE_PL_B18_GM_PRIO2 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B18_GM_PRIO2 18U

#if (defined ETHTSYN_ANNOUNCE_PL_B19_GM_IDENTITY_0)
#error ETHTSYN_ANNOUNCE_PL_B19_GM_IDENTITY_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B19_GM_IDENTITY_0 19U

#if (defined ETHTSYN_ANNOUNCE_PL_B20_GM_IDENTITY_1)
#error ETHTSYN_ANNOUNCE_PL_B20_GM_IDENTITY_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B20_GM_IDENTITY_1 20U

#if (defined ETHTSYN_ANNOUNCE_PL_B21_GM_IDENTITY_2)
#error ETHTSYN_ANNOUNCE_PL_B21_GM_IDENTITY_2 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B21_GM_IDENTITY_2 21U

#if (defined ETHTSYN_ANNOUNCE_PL_B22_GM_IDENTITY_3)
#error ETHTSYN_ANNOUNCE_PL_B22_GM_IDENTITY_3 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B22_GM_IDENTITY_3 22U

#if (defined ETHTSYN_ANNOUNCE_PL_B23_GM_IDENTITY_4)
#error ETHTSYN_ANNOUNCE_PL_B23_GM_IDENTITY_4 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B23_GM_IDENTITY_4 23U

#if (defined ETHTSYN_ANNOUNCE_PL_B24_GM_IDENTITY_5)
#error ETHTSYN_ANNOUNCE_PL_B24_GM_IDENTITY_5 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B24_GM_IDENTITY_5 24U

#if (defined ETHTSYN_ANNOUNCE_PL_B25_GM_IDENTITY_6)
#error ETHTSYN_ANNOUNCE_PL_B25_GM_IDENTITY_6 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B25_GM_IDENTITY_6 25U

#if (defined ETHTSYN_ANNOUNCE_PL_B26_GM_IDENTITY_7)
#error ETHTSYN_ANNOUNCE_PL_B26_GM_IDENTITY_7 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B26_GM_IDENTITY_7 26U

#if (defined ETHTSYN_ANNOUNCE_PL_B27_STEP_REM_1)
#error ETHTSYN_ANNOUNCE_PL_B27_STEP_REM_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B27_STEP_REM_1 27U /* 16 bit */

#if (defined ETHTSYN_ANNOUNCE_PL_B28_STEP_REM_0)
#error ETHTSYN_ANNOUNCE_PL_B28_STEP_REM_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B28_STEP_REM_0 28U

#if (defined ETHTSYN_ANNOUNCE_PL_B29_TIME_SOURCE)
#error ETHTSYN_ANNOUNCE_PL_B29_TIME_SOURCE is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B29_TIME_SOURCE 29U

#if (defined ETHTSYN_ANNOUNCE_PL_B30_PATH_TRACE_TLV_TYPE_1)
#error ETHTSYN_ANNOUNCE_PL_B30_PATH_TRACE_TLV_TYPE_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B30_PATH_TRACE_TLV_TYPE_1 30U

#if (defined ETHTSYN_ANNOUNCE_PL_B31_PATH_TRACE_TLV_TYPE_0)
#error ETHTSYN_ANNOUNCE_PL_B31_PATH_TRACE_TLV_TYPE_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B31_PATH_TRACE_TLV_TYPE_0 31U

#if (defined ETHTSYN_ANNOUNCE_PL_B32_PATH_TRACE_TLV_LEN_0)
#error ETHTSYN_ANNOUNCE_PL_B32_PATH_TRACE_TLV_LEN_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B32_PATH_TRACE_TLV_LEN_0 32U

#if (defined ETHTSYN_ANNOUNCE_PL_B33_PATH_TRACE_TLV_LEN_1)
#error ETHTSYN_ANNOUNCE_PL_B33_PATH_TRACE_TLV_LEN_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B33_PATH_TRACE_TLV_LEN_1 33U

#if (defined ETHTSYN_ANNOUNCE_PL_B34_PATH_TRACE_TLV_SEQ_0)
#error ETHTSYN_ANNOUNCE_PL_B34_PATH_TRACE_TLV_SEQ_0 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B34_PATH_TRACE_TLV_SEQ_0 34U

#if (defined ETHTSYN_ANNOUNCE_PL_B35_PATH_TRACE_TLV_SEQ_1)
#error ETHTSYN_ANNOUNCE_PL_B35_PATH_TRACE_TLV_SEQ_1 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B35_PATH_TRACE_TLV_SEQ_1 35U

#if (defined ETHTSYN_ANNOUNCE_PL_B36_PATH_TRACE_TLV_SEQ_2)
#error ETHTSYN_ANNOUNCE_PL_B36_PATH_TRACE_TLV_SEQ_2 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B36_PATH_TRACE_TLV_SEQ_2 36U

#if (defined ETHTSYN_ANNOUNCE_PL_B37_PATH_TRACE_TLV_SEQ_3)
#error ETHTSYN_ANNOUNCE_PL_B37_PATH_TRACE_TLV_SEQ_3 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B37_PATH_TRACE_TLV_SEQ_3 37U

#if (defined ETHTSYN_ANNOUNCE_PL_B38_PATH_TRACE_TLV_SEQ_4)
#error ETHTSYN_ANNOUNCE_PL_B38_PATH_TRACE_TLV_SEQ_4 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B38_PATH_TRACE_TLV_SEQ_4 38U

#if (defined ETHTSYN_ANNOUNCE_PL_B39_PATH_TRACE_TLV_SEQ_5)
#error ETHTSYN_ANNOUNCE_PL_B39_PATH_TRACE_TLV_SEQ_5 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B39_PATH_TRACE_TLV_SEQ_5 39U

#if (defined ETHTSYN_ANNOUNCE_PL_B40_PATH_TRACE_TLV_SEQ_6)
#error ETHTSYN_ANNOUNCE_PL_B40_PATH_TRACE_TLV_SEQ_6 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B40_PATH_TRACE_TLV_SEQ_6 40U

#if (defined ETHTSYN_ANNOUNCE_PL_B41_PATH_TRACE_TLV_SEQ_7)
#error ETHTSYN_ANNOUNCE_PL_B41_PATH_TRACE_TLV_SEQ_7 is already defined
#endif
#define ETHTSYN_ANNOUNCE_PL_B41_PATH_TRACE_TLV_SEQ_7 41U
#endif /* ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON) */

#if (defined ETHTSYN_8_BITS)
#error ETHTSYN_8_BITS is already defined
#endif
#define ETHTSYN_8_BITS 8U

#define ETHTSYN_GET16(headerPtr, constByteOffset) \
  (((uint16)(((uint16)(((headerPtr))[(constByteOffset)]))<<8u)) | \
   ((uint16) ((uint8) (((headerPtr))[(constByteOffset)+1U]))) )

#define ETHTSYN_SET_TXFLAG(Flag, BitNr, StateOfGlobalTxFlag)      \
 do{                                                              \
   TS_AtomicSetBit_8(Flag, BitNr);                                \
   TS_AtomicAssign8(EthTSyn_Frame2Transmit, StateOfGlobalTxFlag); \
 }while(0)

#if (defined ETHTSYN_DELTA_SC)
#error ETHTSYN_DELTA_SC is already defined
#endif /* if (defined ETHTSYN_DELTA_SC) */
#define ETHTSYN_DELTA_SC(receivedSeqCount, seqCount)  (((receivedSeqCount) >= (seqCount))?(uint16)((receivedSeqCount) - (seqCount)) : \
                                                             (uint16)(((receivedSeqCount) + ETHTSYN_SC_MAXLIMIT + 1U) - (seqCount)))

#define ETH_TIMESTAMP_DIFF_INIT(x)  \
   do{                              \
      x.diff.secondsHi = 0U;        \
      x.diff.seconds = 0U;          \
      x.diff.nanoseconds = 0U;       \
      x.sign = FALSE;               \
   }while(0)

#if (defined ETHTSYN_ROOTCFG)
#error ETHTSYN_ROOTCFG is already defined
#endif /* if (defined ETHTSYN_ROOTCFG) */
#define ETHTSYN_ROOTCFG(idx) EthTSyn_RootCfgPtr->EthTSynCtrl[(idx)]

/*==================[type definitions]======================================*/

/** \brief Type definition of PTP header fields which are not common for all frames. */
typedef struct
{
  uint16 MsgLength;
  uint16 Flags;
  uint16 SequNumber;
  uint8 MsgType;
  uint8 Control;
  uint8 LogMsgInterval;
}EthTSyn_PTPHeaderType;

/** \brief Type definition of received Offset timedomains informations. */
typedef struct
{
  StbM_TimeStampType StbMOffsetTimeStamp;
  StbM_UserDataType StbMOffsetUserData;
  uint8 StbMOffsetTimeDomId;
}EthTSyn_OfsInfoType;

/*==================[internal function declarations]========================*/
#define ETHTSYN_START_SEC_CODE
#include <EthTSyn_MemMap.h>

/**
 * \brief Service to translate EthIfCtrlIdx to EthTSynCtrlIdx.
 *
 * \param[in] EthIfCtrlIdx - Index of the EthIf controller.
 * \param[out] EthTSynCtrlIdxPtr - Pointer containing the corresponding EthTSyn controller index.
 *
 * \return E_OK: EthTSyn controller index found.
 *         E_NOT_OK: No EthTSyn controller index found for this EthIfCtrlIdx.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TranslateEthIfCtrlIdx
(
  uint8 EthIfCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) EthTSynCtrlIdxPtr
);

/**
 * \brief Service to transmit a Sync frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitSyncFrame
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to transmit a Sync follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitSyncFUpFrame
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to calculate origin time stamp with HW timestamping.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] TimeStampPtr - Pointer to the Egress time stamp.
 * \return E_OK: Success
 *         E_NOT_OK: Calculation failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CalculateOriginTimeStamp
(
  uint8 EthTSynCtrlIdx,
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#else
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#endif
);
#if((ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (ETHTSYN_MAX_SLAVE != 0U))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SyncFupDropped
(
  uint8 EthTSynCtrlIdx
);
#endif
#if(ETHTSYN_MAX_SLAVE != 0U)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_PerformSync
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  Eth_TimeStampType OriginTimeStamp
);
#endif

#if((ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (ETHTSYN_MAX_SLAVE != 0U))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleDemSync
(
  uint8 EthTSynCtrlIdx
);
#endif

#if((ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE) && (ETHTSYN_MAX_SLAVE != 0U))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_PDelayFrameDropped
(
  uint8 EthTSynCtrlIdx
);
#endif

#if (ETHTSYN_MAX_SLAVE != 0U)
/**
 * \brief Initialize all slave variables.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_SlaveVar
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Initialize all slave variables used for error cases.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
#if((ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DET) || \
    (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) || \
    ((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_SlaveVarErr
(
  uint8 EthTSynCtrlIdx
);
#endif
/**
 * \brief Initialize all slave variables used fo calculation of the pdelay.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ResetSlavePdelayData
(
  uint8 EthTSynCtrlIdx
);
#if(ETHTSYN_ICV_USED == STD_ON)
/**
 * \brief Initialize all relevant time auth slave variables.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_IcvSubTlvData
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Handles VerificationTimeout and VerificationAttempts.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleICV
(
  uint8 EthTSynCtrlIdx
);
#endif /* ETHTSYN_ICV_USED == STD_ON */
#endif

/**
 * \brief Initialize all Master and common variables.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_CtrlVar
(
  uint8 EthTSynCtrlIdx
);

#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
/**
 * \brief Initialize all slave variables.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_TimeRecordingVar
(
  uint8 EthTSynCtrlIdx
);
#endif

/**
 * \brief Find the next minimum of all ports of a controller.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Index of the EthTSyn ports.
 *
 */
STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_NextMinDebounceOffset
(
  P2VAR(uint32, AUTOMATIC, ETHTSYN_APPL_DATA) CommonOffset,
  uint32 SpecificOffset
);



#if(ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON)
/**
 * \brief Service to transmit an announce frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TransmitAnnounceFrame
(
  uint8 EthTSynCtrlIdx
);
#endif /* ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON) */

/**
 * \brief Service to transmit a Pdelay request frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitPdelayReqFrame
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to transmit a Pdelay response frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] RxDataPtr - Pointer to the received Pdelay request payload.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitPdelayRespFrame
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to transmit a Pdelay response follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitPdelayRespFUpFrame
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to get Tx buffer and fill the PTP header
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PayloadLength - Length of the frame payload.
 * \param[out] BufIdxPtr - Pointer to the buffer index of the requested Tx frame buffer.
 * \param[out] BufPtr - Pointer to return the pointer of the Ethernet Tx frame buffer.
 *
 * \return E_OK: Tx buffer available and big enough.
 *         E_NOT_OK: No suitable Tx buffer available.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetTxBuffer
(
  uint8 EthTSynCtrlIdx,
  uint16 PayloadLength,
  P2VAR(Eth_BufIdxType, AUTOMATIC, ETHTSYN_APPL_DATA) BufIdxPtr,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

/**
 * \brief Service to fill the PTP header for all outgoing EthTSyn frames.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PTPHeader - PTP header containing all bytes which do not have common values.
 * \param[out] BufPtr - Pointer to store the created 34 byte PTP header.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillPTPHeader
(
  uint8 EthTSynCtrlIdx,
  P2CONST(EthTSyn_PTPHeaderType, AUTOMATIC, ETHTSYN_APPL_DATA) PTPHeader,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

/**
 * \brief Service to fill the TLV information of the follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

#if(ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON)
/**
 * \brief Service to fill announce frame payload.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[out] BufPtr - Pointer to store the created announce frame payload.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillAnnouncePayload
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);
#endif /* ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON) */

/**
 * \brief Service to send the PTP frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] BufIdx - Buffer index of used Tx frame buffer.
 * \param[in] PayloadLength - Length of the frame payload.
 * \param[in] ActivateTimeStamp - Activates egress time stamping.
 *
 * \return E_OK: Transmit performed.
 *         E_NOT_OK: Error detected.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitFrame
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
  uint16 PayloadLength,
  boolean ActivateTimeStamp
);

/**
 * \brief Service to convert the time stamp to a byte array ready to send via frame.
 *
 * \param[in] TimeStampPtr - Pointer to time stamp which requires conversion.
 * \param[out] BufPtr - Pointer to store the converted time stamp.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TimeStampToArray
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
/**
 * \brief Service to add the difference between OTS and SyncEgress to the correctionField.
 *
 * \param[in] OriginTimeStampPtr - Pointer to time stamp which contains the calculated originTS.
 * \param[in] EgressTimeStampPtr - Pointer to time stamp which contains egressTS.
 * \param[out] BufPtr - Pointer to store the converted time stamp.
 *
 * \return E_OK: Valid correction value.
 *         E_NOT_OK: Invalid correction value.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CorrField2PTPHeader
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) OriginTimeStampPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) EgressTimeStampPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

/**
 * \brief Service to process incoming Sync frames.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] LenByte - Length in bytes.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessReceivedSyncFrame
(
  uint8 EthTSynCtrlIdx,
  uint16 LenByte,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
);
#if (ETHTSYN_MAX_SLAVE != 0U)
/**
 * \brief Service to convert a byte array to a time stamp.
 *
 * \param[out] TimeStampPtr - Pointer to store the converted time stamp.
 * \param[in] BufPtr - Pointer provide the time stamp in byte array.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ArrayToTimeStamp
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

/**
 * \brief Service to process incoming Sync frames.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxSyncFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
);

/**
 * \brief Service to process incoming Sync follow up frames.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] Length - Length of the FUp frame.
 *
 * \return Sequence number which is stored in the PTP header.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxSynFUpFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length
);

/**
 * \brief Service to process incoming Pdelay response frames.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 *
 * \return Sequence number which is stored in the PTP header.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxPdelayRespFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
);

/**
 * \brief Service to process incoming Pdelay response follow up frames.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 *
 * \return Sequence number which is stored in the PTP header.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxPdelayRespFUpFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
);

/**
 * \brief Service to check whether an EthIf controller is a slave.
 *
 * This service checks whether an EthIf controller is a slave.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthIf controller
 *
 * \return TRUE if EthTSynCtrlIdx is a slave
 *         FALSE if EthTSynCtrlIdx is not a slave
 */
STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsSlave
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to convert and add correction field array to time stamp.
 *
 * This converts the 8 byte correction field array into a time stamp value and adds it to
 * the given time stamp.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] CorrectionFieldArray - 8 byte correction field array in ns.
 * \param[in/out] TimeStampPtr - Pointer returning the sum of this time stamp and the converted
 *                               time stamp.
 *
 * \return E_OK: Correction field is valid.
 *         E_NOT_OK: Correction field is invalid.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_AddCorrField
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) CorrectionFieldArray,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
);

/**
 * \brief Service to handle the confirmation of the transmitted delay frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleTxConfPDelayReq
(
  uint8 EthTSynCtrlIdx
);

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
/**
 * \brief Service to convert and add correction field array to time stamp.
 *
 * This converts the 8 byte correction field array into a time stamp value and adds it to
 * the given time stamp.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] CorrectionFieldArray - 8 byte correction field array in ns.
 * \param[out] TimeStampPtr - Pointer returning the correction value in time stamp.
 *
 * \return E_OK: Correction field is valid.
 *         E_NOT_OK: Correction field is invalid.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SavePTPCorrField
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) CorrectionFieldArray,
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
);

/**
 * \brief Service to handle the corrections values.
 *
 * This function handles the correction values received in the frames. Is used to substract or add
 * this values to the calculated Delay.
 *
 * \param[in/out] DelayValue - Pointer to the calculated Delay.
 * \param[in] CorrectionValue - Pointer to the Correction value.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleCorrections
(
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) DelayValue,
  P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) CorrectionValue
);

/**
 * \brief Service to save the relevant data for the calculation of meanPathDelay.
 *  This function will save also backup values.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] OriginTimeStampPtr - Pointer to time stamp which contains the received value of originTS.
 * \param[in] FupCorrectionPtr - Pointer to time stamp which contains correction received in the Fup frame.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_UpdateDelayValues
(
  uint8 EthTSynCtrlIdx,
  Eth_TimeStampType OriginTimeStamp,
  Eth_TimeIntDiffType FupCorrection
);

/**
 * \brief Service to initialiaze relevant variables for PTP feature.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_PTPIEEE1588_BckpVars
(
  uint8 EthTSynCtrlIdx
);
/**
 * \brief Service to substract corrections from the OTS.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] TimeStampCorrDiff - Pointer to time stamp which contains correction received in the Fup frame.
 * \param[in\out] OriginTimeStampPtr - Pointer to time stamp which contains the calculated value of originTS.
 *
 * \return E_OK: Global time will be passed to StbM.
 *         E_NOT_OK: StbM will not be called.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SubCorrE2EMechanism
(
  uint8 EthTSynCtrlIdx,
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampCorrDiff,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) OriginTimeStampPtr
);

/** \brief Computes the product of two numbers
 **
 ** This function computes the product of two numbers
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 **
 ** \return Product result
 */
STATIC FUNC(uint64, STBM_CODE) EthTSyn_Umul32_64
(
  uint32 a,
  uint32 b
);

/** \brief Computes the high part of a product
 **
 ** This function computes the high part of the product a*b number (bits <63:32>)
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 ** \param[out] rhi - bits <63:32> of the product a * b
 **
 */
STATIC FUNC(uint32, STBM_CODE) EthTSyn_Umul32_hi
(
  uint32 a,
  uint32 b
);

/** \brief Computes product of two unsigned 32-bit integers
 **
 ** This function computes the full 64-bit product of two unsigned 32-bit integers
 **
 ** \param[in] a - first member of the product
 ** \param[in] b - second member of the product
 ** \param[out] rhi - bits <63:32> of the product a * b
 ** \param[out] rlo - bits <31:0> of the product a * b
 **
 */
STATIC FUNC(void, STBM_CODE) EthTSyn_Umul32_Wide
(
  uint32 a,
  uint32 b,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rhi,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rlo
);
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
/**
 * \brief Service to calculate the Pdelay.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_CalculatePdelay
(
  uint8 EthTSynCtrlIdx
);

#endif /* ETHTSYN_MAX_SLAVE != 0U */

#if((ETHTSYN_MAX_SLAVE != 0U) || (ETHTSYN_SWITCH_USED == STD_ON) || (ETHTSYN_IEEE1588_CONFIGURED == STD_ON))
/**
 * \brief Service to subtract two time stamps.
 *
 * This service subtracts two time stamps and returns the result in the first time stamp
 * parameter if successful. In case that subtraction was not successful (negative result) the
 * parameters are not changed.
 *
 * Note: A result can either be positive or negative. If service returns E_NOT_OK the call
 *       with swapped parameters will always return E_OK.
 *
 * \param[in] TimeStamp_MinuendPtr - Minuend pointer to a time stamp for subtraction.
 * \param[in] TimeStamp_SubtrahendPtr - Subtrahend pointer to a time stamp for subtraction.
 * \param[in/out] TimeStamp_ResultPtr - Result pointer provides a variable for the result of the
 *                                      subtraction.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SubTimeStamps
(
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp_MinuendPtr,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp_SubtrahendPtr,
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp_ResultPtr
);

/**
 * \brief Service to compare two time stamps.
 *
 * This service compares two time stamps to detect which one is bigger.
 *
 * \param[in] TimeStamp1Ptr - First pointer to a time stamp.
 * \param[in] TimeStamp2Ptr - Second pointer to a time stamp.
 *
 * \return TRUE if TimeStamp1Ptr >= TimeStamp2Ptr
 *         FALSE if TimeStamp1Ptr < TimeStamp2Ptr
 */

STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_TimeStamp_IsGreaterOrEqual
(
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp1Ptr,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp2Ptr
);
#endif/* (ETHTSYN_MAX_SLAVE != 0U) || (ETHTSYN_SWITCH_USED == STD_ON) || (ETHTSYN_IEEE1588_CONFIGURED == STD_ON) */
/**
 * \brief Service to get the ingress time stamp.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] RxDataPtr - Pointer to the received frame.
 * \param[out] TimeStampPtr - Pointer to return the actual time stamp.
 *
 * \return E_OK: Transmit performed.
 *         E_NOT_OK: Error detected.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetIngressTimeStamp
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) RxDataPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
);

/**
 * \brief Service to get the egress time stamp.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] BufIdx - Buffer index of used Tx frame buffer.
 * \param[out] TimeStampPtr - Pointer to return the actual time stamp.
 *
 * \return E_OK: Transmit performed.
 *         E_NOT_OK: Error detected.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetEgressTimeStamp
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#else
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#endif
);

/**
 * \brief Service to return serial number from PTP header.
 *
 * \param[in] PTPHeaderPtr - Pointer PTP header.
 *
 * \return Sequence number which is stored in the PTP header.
 */
STATIC FUNC(uint16, ETHTSYN_CODE) EthTSyn_GetPTPHeaderSequNumber
(
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPHeaderPtr
);

/**
 * \brief Service to Transmit a frame and retry if fails(EthTSynMaxNumberOfTransmitRetries > 0U).
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] BufIdx - Buf Id to be transmitted.
 * \param[in] FrameLength - Length of the frame.
 *
 * * \return E_OK: Transmited succesfully.
 *           E_NOT_OK: Transmision failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitAndRetry
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
  EthTSyn_IntPortIdxType PortIdx,
  uint16 FrameLength
);

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**
 * \brief Service to check the AUTOSAR TLV information of the received follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(uint16, ETHTSYN_CODE) EthTSyn_CheckForAUTOSARSubTLV
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to fill the AUTOSAR TLV information of the follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpAutosarTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

/**
 * \brief Service to fill the not secured AUTOSAR TLV information of the follow up frame.
 *
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVStatus_NotSecured
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset
);

/**
 * \brief Service to fill the secured AUTOSAR TLV information of the follow up frame.
 *
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLV_UserData_NotSecured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset
);

/**
 * \brief Service to fill the OFS AUTOSAR TLV information of the follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] SubTlvOffset - Offset to the next free space where to add the ofs sub-tlv.
 * \param[in] OfsIdx - Offset index.
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 * * \return E_OK: Received data from StbM_GetOffset() was valid.
 *           E_NOT_OK: Received data from StbM_GetOffset() was invalid.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVOfs
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset,
  uint8 OfsIdx
);

/**
 * \brief Service to fill in the the status field of the SubTLV.
 *
 * \param[in] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FUpSubTLVStatus
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

#if(ETHTSYN_ICV_USED == STD_ON)
#if(ETHTSYN_TOTAL_ICVTXLENGTH > 0U)
/**
 * \brief Service to check the Icv AUTOSAR TLV information.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in\out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessFupTxSubTlvIcv
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

/**
 * \brief Service to check the Icv AUTOSAR TLV information.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] SubTlvOffset - The Sub-TLV offset.
 * \param[in] FreshnessValueLength - Freshness value length.
 * \param[in] FreshnessPtr - Pointer to the freshness value.
 * \param[in\out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVIcv
(
  uint8 EthTSynCtrlIdx,
  uint16 SubTlvOffset,
  uint8 FreshnessValueLength,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) FreshnessPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

/**
 * \brief Service to check the Icv AUTOSAR TLV information.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in\out] BufPtr - Pointer to data to be transmitted.
 * \param[out] FrameWasTransmitted - Contains the information if any further actions are needed.
 *
 * * \return E_OK: Transmited succesfully.
 *           E_NOT_OK: Transmision failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CheckPendingTimeAuthTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  EthTSyn_IntPortIdxType PortIdx,
  uint16 PayloadLength,
  P2VAR(boolean, AUTOMATIC, ETHTSYN_APPL_DATA) FrameWasTransmitted
);

/**
 * \brief Service to fill the buffer with the right data if Icv generation fails.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in\out] BufPtr - Pointer to data to be transmitted.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillBufIcvGenFailed
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);

#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
/**
 * \brief Service to fill the buffer with the right data if Icv generation fails.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] IdsMSev - Security event to be reported to IdsM(if configured).
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ReportToIdsM
(
  uint8 EthTSynCtrlIdx,
  uint16 IdsMSev
);
#endif
/**
 * \brief Service to fill the segments of a bigger ICV(than max allowed value in one subtlv).
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] LengthFV - Length of the calculated freshness value.
 * \param[in] FrameOffset - Frame offset.
 * \param[in\out] BufPtr - Pointer to data to be transmitted.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillSegmentsIcv
(
  uint8 EthTSynCtrlIdx,
  uint8 LengthFV,
  uint16 FrameOffset,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);
#endif /* #if(ETHTSYN_TOTAL_ICVTXLENGTH > 0U) */
#if (ETHTSYN_MAX_SLAVE != 0U)
/**
 * \brief Service to extract the segments of a received timeauth Sub-TLV
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] BufPtr - Pointer to the received data.
 * \param[in] Length - Length in bytes.
 * \param[in] Offset - Frame offset.
 *
 * \return E_OK: Valid frame.
 *         E_NOT_OK: Invalid frame.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CheckTimeAuthSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);

/**
 * \brief Service to extract the segments of a received timeauth Sub-TLV
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] BufPtr - Pointer to the received data.
 * \param[in] Length - Length in bytes.
 * \param[in] Offset - Frame offset.
 * \param[out] VerifFailed - Status of verification.
 *
 * \return E_OK: Valid frame.
 *         E_NOT_OK: Invalid frame.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_ProcessICVSegments
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset,
  P2VAR(boolean, AUTOMATIC, ETHTSYN_APPL_DATA) VerifFailed
);

/**
 * \brief Service to extract the segments of a received timeauth Sub-TLV
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] BufPtr - Pointer to the received data.
 * \param[in] Length - Length in bytes.
 * \param[in] Offset - Frame offset.
 * \param[in] OffsetTimeAuth - TimeAuth TLV offset.
 * \param[out] NrOfFvBytes - Number of FV bytes.
 * \param[out] VerifFailed - Status of verification.
 *
 * \return E_OK: Valid frame.
 *         E_NOT_OK: Invalid frame.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_ExtractFreshness
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset,
  uint16 OffsetTimeAuth,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) NrOfFvBytes,
  P2VAR(boolean, AUTOMATIC, ETHTSYN_APPL_DATA) VerifFailed
);

/**
 * \brief Service to verify the received Icv.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 * \return E_OK: Valid frame.
 *         E_NOT_OK: Invalid frame.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyIcv
(
  uint8 EthTSynCtrlIdx
);


/**
 * \brief Service to update controller states in case of a verification fail.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_VerificationFailed
(
  uint8 EthTSynCtrlIdx
);
#if(ETHTSYN_SLAVE_FV_USED == STD_ON)
/**
 * \brief Service to retrieve the Fv from StbM.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 * \return E_OK: Valid frame.
 *         E_NOT_OK: Invalid frame.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetRxFreshnessValue
(
  uint8 EthTSynCtrlIdx
);
#endif /* ETHTSYN_SLAVE_FV_USED != 0U */
#endif /* ETHTSYN_MAX_SLAVE != 0U */
#endif /* ETHTSYN_ICV_USED == STD_ON */

#if(ETHTSYN_TX_CRC_USED == STD_ON)

/**
 * \brief Service to fill the secured AUTOSAR TLV information of the follow up frame.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[out] BufPtr - Pointer to store the TLV information.
 * \param[in] SubTlvOffset - Offset where the Time Sub Tlv is found in the frame.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVTime_Secured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset
);


/**
 * \brief Service to fill the secured AUTOSAR TLV information of the follow up frame.
 *
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVStatus_Secured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset
);

/**
 * \brief Service to fill the secured AUTOSAR TLV information of the follow up frame.
 *
 * \param[out] BufPtr - Pointer to store the TLV information.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLV_UserData_Secured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset
);

#endif /* (ETHTSYN_TX_CRC_USED == STD_ON) */

/**
 * \brief Service to calculate the slave CRC.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Crc_0 - Pointer to store the calculated Crc_0.
 * \param[in] Crc_1 - Pointer to store the calculated Crc_1.
 *
 * \return E_OK: Header data is valid.
 *         E_NOT_OK: Header data is invalid.
 *
 */
#if((ETHTSYN_RX_CRC_USED == STD_ON) || (ETHTSYN_TX_CRC_USED == STD_ON))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_CalculateCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_0,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_1
);

/**
 * \brief Service to calculate the CRC userdata in case of master, and to calculate and compare
 *        in case of slave.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] SubTlvOffset - Offset where we find the respective Sub Tlv.
 * \param[out]Crc_UserData - Pointer to store the calculated Crc (only for master, set to NULL_PTR
 *            otherwise).
 */

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CalcComp_UserDataCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_UserData
);
#endif

/**
 * \brief Service to calculate the OFS CRC in case of master, and to calculate and compare
 *        in case of slave.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] SubTlvOffset - Offset where we find the respective Sub Tlv.
 * \param[out]Crc_UserData - Pointer to store the calculated Crc (only for master, set to NULL_PTR
 *            otherwise).
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CalcComp_OfsCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_Ofs
);

/**
 * \brief Service to calculate the slave CRC for Time Secured Sub-Tlv.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] SubTlvOffset - Offset where we find the respective Sub Tlv.
 *
 */
#if(ETHTSYN_RX_CRC_USED == STD_ON)
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CompareCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 SubTlvOffset
);

/**
 * \brief Service to calculate the slave CRC for Status Secured Sub-Tlv
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] SubTlvOffset - Offset where we find the respective Sub Tlv.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CompareCrc_Status
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 SubTlvOffset
);
#endif
#endif

#if (ETHTSYN_MAX_SLAVE != 0U)
/**
 * \brief Service to verify the AUTOSAR Sub-TLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame
 *
 * \return E_OK: AUTOSAR TLV is valid.
 *         E_NOT_OK: AUTOSAR SubTLV is invalid.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyAutosarTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length
);

/**
 * \brief Service to verify the TLV header data.
 *
 * \param[in] DataPtr - Pointer to store the received FUp information.
 *
 * \return E_OK: Header data is valid.
 *         E_NOT_OK: Header data is invalid.
 *
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyTLVHeader
(
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
);

/**
 * \brief Service to verify the SubTLV data.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: SubTLV data is invalid.
 */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifySubTLVData
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length
);

/**
 * \brief Service to verify the TimeSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Received and calculated Crc are not equal.
                     Slave is configured to CRC_NOT_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyTimeSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);
/**
 * \brief Service to verify the StatusSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Received and calculated Crc are not equal.
                     Slave is configured to CRC_NOT_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyStatusSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);
/**
 * \brief Service to verify the Status NotSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Slave is configured to CRC_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyStatusNotSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);

/**
 * \brief Service to verify the UserDataSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Received and calculated Crc are not equal.
                     Slave is configured to CRC_NOT_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyUserDataSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);

/**
 * \brief Service to verify the UserData NotSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Slave is configured to CRC_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyUserDataNotSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);
#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)
/**
 * \brief Service to verify the Ofs NotSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Slave is configured to CRC_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyOfsNotSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);

/**
 * \brief Service to verify the OfsSecured SubTLV.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Length - Length of the received frame.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: Received and calculated Crc are not equal.
                     Slave is configured to CRC_NOT_VALIDATED.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyOfsSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
);

/**
 * \brief Service to save the received OfsSubTLV data .
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[in] Offset - Offset to where the respective SubTlv starts.
 *
 * \return E_OK: SubTLV data is valid.
 *         E_NOT_OK: SubTLV data is invalid.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SaveOfsData
(
 uint8 EthTSynCtrlIdx,
 P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
 uint16 Offset
);
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */
#endif /* ETHTSYN_MAX_SLAVE != 0U */
#endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */
/**
 * \brief Service to reset sync state machine.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ResetSynTxStateMachine
(
  uint8 EthTSynCtrlIdx
);

#if(ETHTSYN_SWITCH_USED == STD_ON)
/**
 * \brief Service to update debounce value for controller(debounce value is enabled
    for the configured timedomain).
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTransmitDebouncePerCtrl
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to update next debounce value for configured ports(debounce value is enabled per ports).
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTransmitDebouncePerPort
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief API used to retrieve the timestamps from EthSwt.
 *
 * \return void
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index.
 * \param[in] MgmtInfo - Pointer that holds the switch info: SwitchIdx and SwitchPortIdx
 * \param[in] UniqueId - Unique Id provided by EthSwt used to identify the right TimeStamps for certain frames.
 * \param[in] PortTimeStampPtr - Pointer that holds the TimeStamp provided by EthSwt for a certain port.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_EthSwtPtpTimeStampIndicationSub
(
  uint8 EthTSynCtrlIdx,
  EthSwt_MgmtInfoType MgmtInfo,
  uint32 UniqueId,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) PortTimeStampPtr
);
#endif /* ETHTSYN_SWITCH_USED == STD_ON */

/**
 * \brief Service to perform TSyn master main function tasks
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunctionTimeSynMaster
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Trigger an immediate transmission of Time Synchronization messages belonging to this Time Base
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TriggImmediateTimeSyncMsg
(
  uint8 EthTSynCtrlIdx
);

#if(ETHTSYN_MAX_SLAVE != 0U)
/**
 * \brief Service to perform TSyn slave main function tasks
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunctionTimeSynSlave
(
  uint8 EthTSynCtrlIdx
);
#endif

/**
 * \brief Service of the mainfunction
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessFrame2Transmit(void);

/**
 * \brief Service of the mainfunction
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TriggerPeriodicFrames(void);

/**
 * \brief Service to perform transmit frame after debounce was perfomed
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitFrameWithDebounce
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Function used to process the received frame.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] DataPtr - Address of the received payload.
 * \param[in] PhysAddrPtr - Pointer to physical source address.
 * \param[in] LenByte - Length of the payload contained in the received Rx buffer.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxMsg
(
 uint8 EthTSynCtrlIdx,
 P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
 P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PhysAddrPtr,
 uint16 LenByte
);

/**
 * \brief Function used to process the received frame based of the FrameType.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] DataPtr - Address of the received payload.
 * \param[in] LenByte - Length of the payload contained in the received Rx buffer.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessFrameType
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 LenByte
);

/**
 * \brief Service to process incoming Pdelay request frames.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] LenByte - Length of the payload contained in the received Rx buffer.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxPdelayReqFrame
(
 uint8 EthTSynCtrlIdx,
 P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
 uint16 LenByte
);

#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
/**
 * \brief Service to verify the Authentication Challenge TLV for Device Authentication.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] DataPtr - Address of the received payload.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayDevAuth
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
);

/**
 * \brief  Service to fill the Authentication Challenge TLV information
 *         of the pdelayresp/pdelayresp_fup frames.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] DataPtr - Address of the buffer to be filled.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillAuthChallengeTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
);
#endif

/**
 * \brief  Service to reset relevant data in case a transmission failed.
 *
 * \param[in] EthIfCtrlIdx - Index of the EthIf controller.
 * \param[in] BufIdx - Index of the buffer resource.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TxFailedResetValues
(
  uint8 EthIfCtrlIdx,
  Eth_BufIdxType BufIdx
);

/* ================================================================================ */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
/**
 * \brief Service to process incoming Sync frames from EthSwt.
 *
 * \param[in] IngressTimeStampPtr - Ingress timestamp, provided by the EthSwt module.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 *
 * \return TRUE: Timestamp is required for T5(egressTS from the hostport).
 *         FALSE: No timestamp is required.
 */

STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxSyncSwtMsg
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint32 UniqueId
);

/**
 * \brief Service to process incoming Sync frames from EthSwt.
 *
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] Len - Length of the payload.
 *
 *
 * \return
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxFupSyncSwtMsg
(
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint16 Len
);

/**
 * \brief Service to synchronize the time base
 *
 * \param[in] OtsPdelayCorrPtr - Time used for the simple bridge synchronization.
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_SynchronizeBridge
(
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) OtsPdelayCorrPtr,
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to add valid OTS and correctionField values.
 *
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_AddOtsCorr
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to process received sync frame.
 *
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxSyncFrame
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx
);

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**
 * \brief Service to verify the SubTLV data when using a simple bridge configuration.
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] DataPtr - Pointer to store the received FUp information.
 * \param[inout] Crc_Time_1 - Pointer to store the calculated Crc_Time_1.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_BridgeCalculateCrcTime1
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_Time_1
);

#endif /* ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF */
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */

#if(ETHTSYN_SWITCH_USED == STD_ON)


/**
 * \brief Service to transmit a Sync frame to a specific port of a switch
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Index of the PortIdx of the switch.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtSyncFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
);

/**
 * \brief Service to transmit a FuP frame to a specific port of a switch
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Index of the PortIdx of the switch.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSyncSwtFUpFramePerPort
(
  uint8 EthTSynCtrlIdx,
  EthTSyn_IntPortIdxType PortIdx
);

/**
 * \brief Service to transmit a Sync frame to a specific port of a switch
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtOnHostPortSyncFrame
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to transmit a Pdelay_req frame to a specific port of a switch
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Index of the PortIdx of the switch.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtPdelayReqFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
);

/**
 * \brief Service to transmit a Pdelay_resp frame to a specific port of a switch
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Index of the PortIdx of the switch.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtPdelayRespFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
);

/**
 * \brief Service to transmit a Pdelay_resp_fup frame to a specific port of a switch
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Index of the PortIdx of the switch.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtPdelayRespFupFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
);


/**
 * \brief Service to get Swt Tx buffer and fill the PTP header
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PayloadLength - Length of the frame payload.
 * \param[in] IntPortIdx - Internal unique port Idx.
 * \param[out] BufIdxPtr - Pointer to the buffer index of the requested Tx frame buffer.
 * \param[out] BufPtr - Pointer to return the pointer of the Ethernet Tx frame buffer.
 *
 * \return E_OK: Tx buffer available and big enough.
 *         E_NOT_OK: No suitable Tx buffer available.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_GetSwtTxBuffer
(
  uint8 EthTSynCtrlIdx,
  uint16 PayloadLength,
  EthTSyn_IntPortIdxType IntPortIdx,
  P2VAR(Eth_BufIdxType, AUTOMATIC, ETHTSYN_APPL_DATA) BufIdxPtr,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHIF_APPL_DATA) BufPtr
);

/**
 * \brief Service to transmit a frame over switch ports.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] BufIdx - Buffer index of the requested Tx frame buffer.
 * \param[in] RequestTimeStamp - Boolean to request switch time stamp
 * \param[in] IntPortIdx - Internal unique port Idx.
 * \param[in] ActivateTimeStamp - Activates egress time stamping.
 * \param[in] LenByte - Length of the frame to be transmitted.
 * \param[in] IsPdelayResp - Identify if the transmitted frame is a pdelay_resp
 *
 * \return E_OK: Tx was successful
 *         E_NOT_OK: Tx was not successful
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtFrame
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
  boolean RequestTimeStamp,
  EthTSyn_IntPortIdxType IntPortIdx,
  boolean ActivateTimeStamp,
  uint16 LenByte,
  boolean IsPdelayResp
);

/**
 * \brief Service to calculate the correction and update the field in PTPHeader.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Swt Port Idx.
 * \param[out] CalculatedCorrection - Value of the calculated correction.
 *
 * \return E_OK: Valid correction value.
 *         E_NOT_OK: Invalid correction value.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_SwtCorrField
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx,
  P2VAR(uint32, AUTOMATIC, ETHTSYN_VAR) CalculatedCorrection
);

/**
 * \brief Service handle syn Tx state machine
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_SwtSynStateHandling
(
  uint8 EthTSynCtrlIdx
);

/**
 * \brief Service to perform transmit swt frame after debounce was perfomed
 *
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] PortIdx - Port index the frame belongs to.
 *
 * \return E_OK: Tranmission success.
 *         E_NOT_OK: Tranmission failed.
 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtFrameWithDebounce
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
);

/**
 * \brief Service to reset pdelay state machine of a port.
 *
 * \param[in] PortIdx - Port index the frame belongs to.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ResetPortPdelayVars
(
  uint8 PortIdx
);

/**
 * \brief Function used to process the received frame from EthSwt.
 *
 * \param[in] MgmtInfoPtr - Switch and Port ID.
 * \param[in] IngressTimeStampPtr - Ingress timestamp provided by the EthSwt.
 * \param[in] DataPtr - Address of the received payload.
 * \param[in] Len - Length of the payload contained in the received Rx buffer.
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] UniqueId - UniqueId provided by EthSwt used for identification.
 * \return true: TimeStamp is expected.
 *         false: TimeStamp is not expected.
 */
STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxSwtMsg
(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHTSYN_APPL_DATA) MgmtInfoPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint16 Len,
  uint32 UniqueId
);
/**
 * \brief Service to process incoming PdelayReq frames from EthSwt.
 *
 * \param[in] MgmtInfoPtr - Port information.
 * \param[in] IngressTimeStampPtr - Ingress timestamp, provided by the EthSwt module.
 * \param[in] DataPtr - Pointer to the payload of the frame.
 * \param[in] EthTSynCtrlIdx - EthTSyn controller index the frame belongs to.
 * \param[in] Len - Length of the payload.
 *
 */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxPdelayReqSwtMsg
(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHTSYN_APPL_DATA) MgmtInfoPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint16 Len
);

/**
 * \brief Service to fill the PTP header for all outgoing EthTSyn frames.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 * \param[in] PortIdx - Port index the frame belongs to.
 * \param[in] SubTlvLength - If configured, contains the total length of the sub-tlvs.
 * \param[in] CorrectionValue - Calculated correction value.
 * \param[out] BufPtr - Pointer to store the payload.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_PrepareSwtFUpForTx
(
  uint8 EthTSynCtrlIdx,
  EthTSyn_IntPortIdxType PortIdx,
  uint16 SubTlvLength,
  uint32 CorrectionValue,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  Eth_BufIdxType BufIdx
);
#endif/* ETHTSYN_SWITCH_USED == STD_ON */
/* ================================================================================ */

#define ETHTSYN_STOP_SEC_CODE
#include <EthTSyn_MemMap.h>
/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
#include <EthTSyn_MemMap.h>

#if (ETHTSYN_MAX_SLAVE != 0U)
/** \brief Ns Array to time stamp conversion table
 *
 *  This table contains the converted value in seconds and nanoseconds (< 1s) of:
 *  Index 0: 2^32ns
 *  Index 1: 2^33ns
 *  ...
 *  Index 15: 2^47ns
 *
 *  Type sorted by nanoseconds, seconds, secondsHi.
 */
 /* Deviation MISRAC2012-2 */
STATIC CONST(Eth_TimeStampType, ETHTSYN_CONST) EthTSyn_NsArrayConversionTable[16U] =
{
  {294967296U, 4U, 0U},
  {589934592U, 8U, 0U},
  {179869184U, 17U, 0U},
  {359738368U, 34U, 0U},
  {719476736U, 68U, 0U},
  {438953472U, 137U, 0U},
  {877906944U, 274U, 0U},
  {755813888U, 549U, 0U},
  {511627776U, 1099U, 0U},
  {23255552U, 2199U, 0U},
  {46511104U, 4398U, 0U},
  {93022208U, 8796U, 0U},
  {186044416U, 17592U, 0U},
  {372088832U, 35184U, 0U},
  {744177664U, 70368U, 0U},
  {488355328U, 140737U, 0U}
};
#endif

#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
#include <EthTSyn_MemMap.h>
/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define ETHTSYN_START_SEC_VAR_INIT_UNSPECIFIED
#include <EthTSyn_MemMap.h>

/** \brief Pointer to access the configuration structure. */
STATIC P2CONST(EthTSyn_ConfigType, ETHTSYN_VAR, ETHTSYN_APPL_CONST) EthTSyn_RootCfgPtr = NULL_PTR;

#define ETHTSYN_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <EthTSyn_MemMap.h>

#define ETHTSYN_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <EthTSyn_MemMap.h>

/** \brief Master/slave common controller variables. */
STATIC VAR(EthTSyn_ControllerType, ETHTSYN_VAR) EthTSyn_Ctrl[ETHTSYN_MAX_CTRL];

#if (ETHTSYN_MAX_SLAVE != 0U)
/** \brief Slave controller variables. */
STATIC VAR(EthTSyn_ControllerSlaveType, ETHTSYN_VAR) EthTSyn_Slave[ETHTSYN_MAX_SLAVE];
#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)

STATIC VAR(EthTSyn_OfsInfoType, ETHTSYN_VAR) EthTSyn_OffsetTbInfo[ETHTSYN_OFSTIMEBASES_CONFIGURED];
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */

#endif /* ETHTSYN_MAX_SLAVE != 0U */

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)

/** \brief Global time base status */
STATIC VAR(EthTSyn_ControllerType, ETHTSYN_VAR) EthTSyn_MasterTimeBaseStatus;

#endif

#if(ETHTSYN_SWITCH_USED == STD_ON)
STATIC EthTSyn_ControllerSwtPortType EthTSyn_SwitchPorts[ETHTSYN_SWITCH_PORTS_CONFIGURED];
#endif

#define ETHTSYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <EthTSyn_MemMap.h>

#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
#include <EthTSyn_MemMap.h>

/* Deviation MISRAC2012-3 <+10>*/
#if (defined ETHTSYN_TST_RUNTIME_DATA_EXPOSE_PTR)
#if (ETHTSYN_TST_RUNTIME_DATA_EXPOSE_PTR != 0)
#if(ETHTSYN_SWITCH_USED == STD_ON)
CONSTP2VAR(EthTSyn_ControllerSwtPortType, ETHTSYN_CONST, ETHTSYN_APPL_DATA) EthTSyn_TS_SwitchPorts = EthTSyn_SwitchPorts;
#endif
CONSTP2VAR(EthTSyn_ControllerType, ETHTSYN_CONST, ETHTSYN_APPL_DATA) EthTSyn_TS_Ctrl = EthTSyn_Ctrl;
#if (ETHTSYN_MAX_SLAVE != 0U)
CONSTP2VAR(EthTSyn_ControllerSlaveType, ETHTSYN_CONST, ETHTSYN_APPL_DATA) EthTSyn_TS_Slave = EthTSyn_Slave;
#endif
#endif /* TS_ETHTSYN_RUNTIME_DATA_EXPOSE_PTR != 0 */
#endif /* ifdef TS_ETHTSYN_RUNTIME_DATA_EXPOSE_PTR */

#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
#include <EthTSyn_MemMap.h>

#define ETHTSYN_START_SEC_VAR_CLEARED_8
#include <EthTSyn_MemMap.h>

#if (ETHTSYN_MAX_SLAVE != 0U)

/** \brief Stores the extracted SYNC_TO_GATEWAY  bit */
/* Deviation MISRAC2012-2 */
STATIC VAR(uint8, ETHTSYN_VAR) EthTSyn_SyncToGatewayBit;

#endif /* ETHTSYN_MAX_SLAVE != 0U */

STATIC VAR(boolean, ETHTSYN_VAR) EthTSyn_Frame2Transmit;

#if(ETHTSYN_TOTAL_ICVTXLENGTH > 0U)
/** \brief Holds all generated Icvs for all EthTSynCtrl */
STATIC VAR(uint8, ETHTSYN_APPL_CONST) EthTSyn_IcvTxFrame[ETHTSYN_TOTAL_ICVTXLENGTH];
#endif

#define ETHTSYN_STOP_SEC_VAR_CLEARED_8
#include <EthTSyn_MemMap.h>


#define ETHTSYN_START_SEC_VAR_CLEARED_32
#include <EthTSyn_MemMap.h>

/** \brief Stores the number of mainfunction() calls */
VAR(uint32, ETHTSYN_VAR) EthTSyn_GeneralCounter;

/** \brief Stores the minimum debounceoffset */
STATIC VAR(uint32, ETHTSYN_VAR) GlobalMinDebounceTimeOffset;

#define ETHTSYN_STOP_SEC_VAR_CLEARED_32
#include <EthTSyn_MemMap.h>

/*==================[external function definitions]=========================*/
#define ETHTSYN_START_SEC_CODE
#include <EthTSyn_MemMap.h>

#if(ETHTSYN_VERSION_INFO_API == STD_ON)
/* !LINKSTO EthTSyn.SWS_EthTSyn_00036, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETHTSYN_APPL_DATA) VersionInfo
)
{
  DBG_ETHTSYN_GETVERSIONINFO_ENTRY(VersionInfo);

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(VersionInfo == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.EB.GetVersionInfo.NullPtr, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_GETVERSIONINFO, ETHTSYN_E_PARAM_POINTER);
  }
  else
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    /* Return version information */
    /* !LINKSTO EthTSyn.EB.GetVersionInfo, 1 */
    VersionInfo->vendorID = ETHTSYN_VENDOR_ID;
    VersionInfo->moduleID = ETHTSYN_MODULE_ID;
    VersionInfo->sw_major_version = ETHTSYN_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = ETHTSYN_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = ETHTSYN_SW_PATCH_VERSION;
  }

  DBG_ETHTSYN_GETVERSIONINFO_EXIT(VersionInfo);
}
#endif /* ETHTSYN_VERSION_INFO_API */

/* !LINKSTO EthTSyn.SWS_EthTSyn_00035, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Init
(
  P2CONST(EthTSyn_ConfigType, AUTOMATIC, ETHTSYN_APPL_CONST) CfgPtr
)
{
  uint8 EthTSynCtrlIdx;

  DBG_ETHTSYN_INIT_ENTRY(CfgPtr);

  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

  EthTSyn_RootCfgPtr = CfgPtr;

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00006, 1 */
  /* !LINKSTO EthTSyn.EB.EthTSyn_00008, 1 */

  if(CfgPtr == NULL_PTR)
  {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00030_ValueCheck_INIT_FAILED, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_INIT, ETHTSYN_E_INIT_FAILED);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
#if (ETHTSYN_MAX_SLAVE != 0U)
    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynSlaveIdx;
         EthTSynCtrlIdx++
       )
    {
      EthTSyn_Init_SlaveVar(EthTSynCtrlIdx);
    }
#endif /* ETHTSYN_MAX_SLAVE != 0U */
    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
         EthTSynCtrlIdx++
       )
    {
      EthTSyn_Init_CtrlVar(EthTSynCtrlIdx);
      /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_Init, 1 */
      /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_INIT-IDLE, 1 */
      EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
    }

    /* Init global counter */
    EthTSyn_GeneralCounter = 0U;

    /* Maximum */
    GlobalMinDebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE;
  }

  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

  DBG_ETHTSYN_INIT_EXIT(CfgPtr);
}

/* !LINKSTO EthTSyn.SWS_EthTSyn_00044, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunction(void)
{
  DBG_ETHTSYN_MAINFUNCTION_ENTRY();

  /* !LINKSTO EthTSyn.EB.MainFunction.Uninit, 1 */
  if(!ETHTSYN_UNINIT)
  {
    uint8 EthTSynCtrlIdx;
    EthTSyn_GeneralCounter++;
    /*check for smallest */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00130, 1 */
    if(GlobalMinDebounceTimeOffset == EthTSyn_GeneralCounter)
    {
      GlobalMinDebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE;

      for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
         EthTSynCtrlIdx++
       )
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00133, 1 */
        /* !LINKSTO EthTSyn.EB.TransparentClock_DebounceValueElapse, 1 */
        if(EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset == EthTSyn_GeneralCounter)
        {
          EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE;
#if(ETHTSYN_SWITCH_USED == STD_ON)
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SwtDebouncingPerPort == TRUE)
          {
            EthTSyn_IntPortIdxType Idx = 0U;
           /* find the next minimum of all ports of a controller */
            for(
                 Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
                 Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                 EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
                 Idx++
               )
            {
              if(EthTSyn_GeneralCounter == EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset)
              {
                EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE;
              }
              else
              {
                boolean Updated = FALSE;

                Updated = EthTSyn_NextMinDebounceOffset
                          (&EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset,
                           EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset
                          );
                if(Updated == TRUE)
                {
                  (void)EthTSyn_NextMinDebounceOffset
                        (&GlobalMinDebounceTimeOffset,
                         EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
                        );
                }
              }
            }
          }
#endif
        }
        else
        {
          (void)EthTSyn_NextMinDebounceOffset
                (&GlobalMinDebounceTimeOffset,
                 EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
                );
        }
      }
    }

    EthTSyn_TriggerPeriodicFrames();

    if(EthTSyn_Frame2Transmit)
    {
      TS_AtomicAssign8(EthTSyn_Frame2Transmit, FALSE);
      EthTSyn_ProcessFrame2Transmit();
    }
  }
  DBG_ETHTSYN_MAINFUNCTION_EXIT();
}

/* !LINKSTO EthTSyn.SWS_EthTSyn_00040, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_RxIndication
(
  uint8 CtrlIdx,
  Eth_FrameType FrameType,
  boolean IsBroadcast,
  /* Deviation MISRAC2012-1 */
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PhysAddrPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 LenByte
)
{
  DBG_ETHTSYN_RXINDICATION_ENTRY(CtrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, LenByte);

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO EthTSyn.EB.RxIndication.Uninit, 1 */
  if(ETHTSYN_UNINIT)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_UNINIT);
  }
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00041_PARAMPTR, 1 */
  else if(PhysAddrPtr == NULL_PTR)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_PARAM_POINTER);
  }
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00041_PARAMPTR, 1 */
  else if(DataPtr == NULL_PTR)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_PARAM_POINTER);
  }
  /* !LINKSTO EthTSyn.EB.RxIndication.InvalidHeaderSize, 1 */
  else if(ETHTSYN_PTP_HEADER_SIZE > LenByte)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_PARAM);
  }
  else
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    /* !LINKSTO EthTSyn.EB.RxIndication.InvalidFrameType_DetOFF, 1 */
    if(ETHTSYN_PTP_FRAMETYPE == FrameType)
    {
      uint8 EthTSynCtrlIdx;
      Std_ReturnType RetVal;
      uint8 TmpTimeDomainId;
      const uint8 MsgType = DataPtr[ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE] & ETHTSYN_8BIT_MASK_LN;
      TS_PARAM_UNUSED(IsBroadcast);

      EthTSynCtrlIdx = 0U; /* Initialize to get rid of warning. */
      RetVal = EthTSyn_TranslateEthIfCtrlIdx(CtrlIdx, &EthTSynCtrlIdx);

      if(E_OK == RetVal)
      {
        if(
           (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ) ||
           (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP) ||
           (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP)
          )
        {
          /* TimeDomainId for Pdelay frames shall be 0U according to IEEE802.1AS-2020 chapter 11.4.2.4 */
          /* !LINKSTO EthTSyn.EB.CheckPdelayDomainNr, 1 */
          TmpTimeDomainId = 0U;
        }
        else
        {
          /* If any other frame is received a check against the configured timedomain shall be performed. */
          TmpTimeDomainId = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncGlobalTimeDomainId;
        }

        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_TimeDomain, 1 */
        if(DataPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN] == TmpTimeDomainId)
        {
          /* The major version must be 2.*/
          /* !LINKSTO EthTSyn.EB.checkMajorVersionPTP, 1 */
          if((DataPtr[ETHTSYN_PTP_HEADER_B1_PTPVERSION] & ETHTSYN_8BIT_MASK_LN) == ETHTSYN_PTP_HEADER_VERSION)
          {
            /* If the version of the synchronization mechanism match, continue to process the message */
            EthTSyn_ProcessRxMsg(EthTSynCtrlIdx, DataPtr, PhysAddrPtr, LenByte);
          }
          /* !LINKSTO EthTSyn.EB.VersionPTP_NOK, 1 */
        }
      }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
      else
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00041_CTRLIDX, 1 */
        /* Throw a DET error if the input parameter "CtrlIdx" is not valid */
        ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_CTRL_IDX);
      }
#endif
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* !LINKSTO EthTSyn.EB.RxIndication.InvalidFrameType_DetON, 1 */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_PARAM);
    }
#endif
  }

  DBG_ETHTSYN_RXINDICATION_EXIT(CtrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, LenByte);
}

/* !LINKSTO EthTSyn.SWS_EthTSyn_00042, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TxConfirmation
(
  uint8 CtrlIdx,
  Eth_BufIdxType BufIdx
#if(ETHTSYN_RELIABLE_TXCONF == STD_ON)
  ,Std_ReturnType Result
#endif /* ETHTSYN_RELIABLE_TXCONF == STD_ON */
)
{
  Std_ReturnType TmpRet;
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampType TmpTimeStamp;

  TmpTimeStamp.nanoseconds = 0U;
  TmpTimeStamp.seconds = 0U;
  TmpTimeStamp.secondsHi = 0U;
#else
  StbM_VirtualLocalTimeType TmpTimeStamp;

  TmpTimeStamp.nanosecondsLo = 0U;
  TmpTimeStamp.nanosecondsHi = 0U;
#endif
#if(ETHTSYN_RELIABLE_TXCONF == STD_OFF)
  DBG_ETHTSYN_TXCONFIRMATION_ENTRY(CtrlIdx, BufIdx);
#else
  DBG_ETHTSYN_TXCONFIRMATION_ENTRY(CtrlIdx, BufIdx, Result);
#endif /* ETHTSYN_RELIABLE_TXCONF == STD_OFF */

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO EthTSyn.EB.TxConfirmation.Uninit, 1 */
  if(ETHTSYN_UNINIT)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_TXCONFIRMATION, ETHTSYN_E_UNINIT);
  }
  else
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00175, 1 */
  /* No DET shall be reported if EthTSyn_TxConfirmation() is called with invalid controller ID */
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
#if(ETHTSYN_RELIABLE_TXCONF == STD_ON)
    if(Result == E_OK)
    {
#endif /* ETHTSYN_RELIABLE_TXCONF == STD_ON */
      uint8 EthTSynCtrlIdx;

      for(
           EthTSynCtrlIdx = 0U;
           EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
           EthTSynCtrlIdx++
         )
      {
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx == CtrlIdx)
        {
          if(EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx == BufIdx)
          {

            EthTSyn_CtrlSyncTxStateType SyncTxState;

            /* Get sync frame egress time stamp. */
            /* !LINKSTO EthTSyn.EB.Master.SendSyncFU, 1 */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00127, 1 */
            TmpRet = EthTSyn_GetEgressTimeStamp
            (
              EthTSynCtrlIdx,
              (Eth_BufIdxType)EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx, /* BufIdx */
              &TmpTimeStamp /* TimeStampPtr */
            );
            TS_AtomicAssign8
            (
              SyncTxState,
              EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState
            );

            if(TmpRet == E_OK)
            {
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
              if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
              {
                /* !LINKSTO EthTSyn.EB.PTPE2EsaveSyncEgress, 1 */
                /* Save the sync egress timestamp */
                EthTSyn_Ctrl[EthTSynCtrlIdx].SyncEgressTimeStamp = TmpTimeStamp;
              }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
              /* !LINKSTO EthTSyn.SWS_EthTSyn_00127, 1 */
              TmpRet = EthTSyn_CalculateOriginTimeStamp(EthTSynCtrlIdx, &TmpTimeStamp);
            }

            if((TmpRet == E_OK) && (ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_ETH_EGRESS_TS == SyncTxState))
            {
              if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
              {
                TS_AtomicAssign8
                (
                  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
                  ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_FUP
                );
              }
#if(ETHTSYN_SWITCH_USED == STD_ON)
              else
              {
                /* !LINKSTO EthTSyn.EB.BoundaryClock_TransmitSyncOnMasterPorts, 1 */
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
                /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_WAIT_EGRESS-READY_SYN_TO_PORT, 1 */
                TS_AtomicAssign8
                (
                  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
                  ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_SYN_TO_PORT
                );
#else
                /* If EthSwt will handle the distribution of sync frames to non host ports
                   (EthTSynSendSyncFrameOnlyOnHostPort set to true) EthTSyn will take no action until
                   a valid ingress timestamp for the host port. */
                /* !LINKSTO EthTSyn.EB.EthTSynSendSyncFrameOnlyOnHostPort, 1 */
                TS_AtomicAssign8
                (
                  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
                  ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_SWT_INGRESS_TS
                );
#endif /* ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF */
              }
#endif /* ETHTSYN_SWITCH_USED == STD_ON */
            }
            else
            {
              EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
            }
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00214, 1 */
            /* If time measurement with switches is not used, we can inform StbM, else EthTSyn will pass the master
               information on the transmission of each fup frame, because only at that moment the correctionField
               will be available. */
            if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
            {
              (void)StbM_EthSetMasterTimingData
                (
                    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                    /* !LINKSTO EthTSyn.SWS_EthTSyn_00215, 1 */
                    &EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording
                );
            }
#endif
            EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx = ETHTSYN_INV_BUFIDX;
          }
          else if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx == BufIdx)
          {
            /* !LINKSTO EthTSyn.EB.Master.SendPdelayResponseFU, 1 */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00159, 1 */
            /* !LINKSTO EthTSyn.EB.InvTimeQuality.PdelayReqEgress, 1 */
            TmpRet = EthTSyn_GetEgressTimeStamp
            (
              EthTSynCtrlIdx,
              (Eth_BufIdxType)EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx, /* BufIdx */
              &TmpTimeStamp /* TimeStampPtr */
            );

             /* Set the flag */
             if(E_OK == TmpRet)
             {
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
                EthTSyn_Ctrl[EthTSynCtrlIdx].EgressTimeStamp_PdelayT3 = TmpTimeStamp;
#else /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
                /* !LINKSTO EthTSyn.SWS_EthTSyn_00122, 1 */
                EthTSyn_Int01_ConvertVirtualTimeToEthTime(&TmpTimeStamp,
                                             &EthTSyn_Ctrl[EthTSynCtrlIdx].EgressTimeStamp_PdelayT3);
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
                if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv == TRUE)
                {
                  /* !LINKSTO EthTSyn.EB.DevAuth_PdelayRespTxConf, 1 */
                  TmpRet = DevAuth_PDelayResIndication
                      (
                          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx,
                          &EthTSyn_Ctrl[EthTSynCtrlIdx].EgressTimeStamp_PdelayT3,
                          EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce
                      );
                  if(E_OK != TmpRet)
                  {
                    /* !LINKSTO EthTSyn.EB.DevAuth_PDelayResIndication_NOK, 1 */
                    /* The authentication challenge TLV will not be sent in the pdelay_resp_fup frame */
                    TS_AtomicAssign8(
                                      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv,
                                      FALSE
                                    );
                  }
                }
#endif/* ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON */
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
                if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
                {
                  /* If E2E mechanism is used for calculation of the delay, no Fup will be sent.
                     E2E is a one step mechanism. If the timevalidation is enabled for the master
                     relevant data can be passed now to the StbM.*/
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
                  /* The confirmation for a Delay_resp frame is expected only when the
                     timevalidation is enabled for the timedomain. */
                  /* Set the recorded timing measurement data for a pdelay of the
                   * corresponding Synchronized Time Base on Time Master */
                  /* !LINKSTO EthTSyn.SWS_EthTSyn_00219, 1 */
                  (void)StbM_EthSetPdelayResponderData
                    (
                      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                      /* !LINKSTO EthTSyn.SWS_EthTSyn_00220, 1 */
                      &EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording
                    );
#endif /* (ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE) */
                }
                else
                {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
                    /* Transmit the pdelayrespFup frame. */
                    ETHTSYN_SET_TXFLAG
                     (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_PDELAYRESP_FUP, TRUE);
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
                }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
             }
          }
          else if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx == BufIdx)
          {
#if (ETHTSYN_MAX_SLAVE != 0U)
            EthTSyn_HandleTxConfPDelayReq(EthTSynCtrlIdx);
#endif /* ETHTSYN_MAX_SLAVE != 0U */
          }
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
          else if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFup_BufIdx == BufIdx)
          {
            /* The confirmation for a pdelay_resp_fup frame is expected only when the
               timevalidation is enabled for the timedomain. */
            /* Set the recorded timing measurement data for a pdelay of the
             * corresponding Synchronized Time Base on Time Master */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00219, 1 */
            (void)StbM_EthSetPdelayResponderData
                (
                    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                    /* !LINKSTO EthTSyn.SWS_EthTSyn_00220, 1 */
                    &EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording
                );
             EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFup_BufIdx = ETHTSYN_INV_BUFIDX;
          }
#endif
#if(ETHTSYN_ICV_USED == STD_ON)
          else if(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx == BufIdx)
          {
            if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId != ETHTSYN_FV_NOT_CONFIGURED)
            {
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
               /* Time Master shall notify the successful transmission of the Follow_Up
                  message to FVM by calling StbM_SPduTxConfirmation */
               /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00258, 1 */
               (void)StbM_SPduTxConfirmation
               (
                 ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId
               );
#endif
            }
             EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = ETHTSYN_INV_BUFIDX;
          }
#endif /* ETHTSYN_ICV_USED == STD_ON */
          else
          {
            /* Sync_Follow_Up, Pdelay_Resp_Follow_Up */
            /* Nothing to do for these frames. */
          }
        }
      }
#if(ETHTSYN_RELIABLE_TXCONF == STD_ON)
    }
    else
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00176, 1 */
      /* If parameter Result != E_OK, the process of collection of synchronized time distribution shall be
         aborted and all intermediate result variables shall be reset to default value.*/
      EthTSyn_TxFailedResetValues(CtrlIdx, BufIdx);
    }
#endif /* ETHTSYN_RELIABLE_TXCONF == STD_ON */
  }

#if(ETHTSYN_RELIABLE_TXCONF == STD_OFF)
  DBG_ETHTSYN_TXCONFIRMATION_EXIT(CtrlIdx, BufIdx);
#else
  DBG_ETHTSYN_TXCONFIRMATION_EXIT(CtrlIdx, BufIdx, Result);
#endif /* ETHTSYN_RELIABLE_TXCONF == STD_OFF */

}

/* !LINKSTO EthTSyn.SWS_EthTSyn_00043, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TrcvLinkStateChg
(
  uint8 CtrlIdx,
  EthTrcv_LinkStateType LinkState
)
{
  DBG_ETHTSYN_TRCVLINKSTATECHG_ENTRY(CtrlIdx, LinkState);

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO EthTSyn.EB.TrcvLinkStateChg.Uninit, 1 */
  if(ETHTSYN_UNINIT)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_TRCVLINKSTATECHG, ETHTSYN_E_UNINIT);
  }
  else
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00174, 1 */
  /* No DET shall be reported if EthTSyn_TrcvLinkStateChg() is called with invalid controller ID */
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 EthTSynCtrlIdx;
    boolean UpdatePhysAddr = FALSE;
    uint8 DestMacAddr[ETHTSYN_MAC_ADD_SIZE];

    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
         EthTSynCtrlIdx++
       )
    {
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx == CtrlIdx)
      {
        TS_AtomicAssign8(EthTSyn_Ctrl[EthTSynCtrlIdx].LinkState, LinkState);

        TS_MemCpy(DestMacAddr, EthTSyn_DestMacAddr, ETHTSYN_MAC_ADD_SIZE);

        UpdatePhysAddr = TRUE;
        if(ETHTRCV_LINK_STATE_ACTIVE != LinkState)
        {
#if(ETHTSYN_SWITCH_USED == STD_ON)
          EthTSyn_IntPortIdxType Idx;
#endif
          EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
          /* Set timeout to 0 to trigger sync frame as soon as link is up again. */
          EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout = 0U;
          TS_AtomicAssign8(EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, 0U);
#if(ETHTSYN_SWITCH_USED == STD_ON)
          for
          (
            Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
            Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
            Idx++
          )
          {
            TS_AtomicAssign8(EthTSyn_SwitchPorts[Idx].Frame2Transmit, 0U);
          }
#endif
        }
      }
    }

    if(UpdatePhysAddr == TRUE)
    {
      if(ETHTRCV_LINK_STATE_ACTIVE == LinkState)
      {
        /* !LINKSTO EthTSyn.EB.UpdatePhysAddrFilter_AddToFilter, 1 */
        (void)EthIf_UpdatePhysAddrFilter
        (
           CtrlIdx, /* EthIf CtrlIdx */
           DestMacAddr,
           ETH_ADD_TO_FILTER
        );
      }
      else
      {
        /* !LINKSTO EthTSyn.EB.UpdatePhysAddrFilter_RemoveFromFilter, 1 */
        (void)EthIf_UpdatePhysAddrFilter
        (
           CtrlIdx, /* EthIf CtrlIdx */
           DestMacAddr,
           ETH_REMOVE_FROM_FILTER
        );
      }
    }
  }

  DBG_ETHTSYN_TRCVLINKSTATECHG_EXIT(CtrlIdx, LinkState);
}

/* !LINKSTO EthTSyn.SWS_EthTSyn_00039, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SetTransmissionMode
(
  uint8 CtrlIdx,
  EthTSyn_TransmissionModeType Mode
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_ETHTSYN_SETTRANSMISSIONMODE_ENTRY(CtrlIdx, Mode);

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO EthTSyn.EB.SetTransmissionMode.Uninit, 1 */
  if(ETHTSYN_UNINIT)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_SETTRANSMISSIONMODE, ETHTSYN_E_UNINIT);
  }
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00172_Mode, 1 */
  else if((Mode != ETHTSYN_TX_ON) && (Mode != ETHTSYN_TX_OFF))
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_SETTRANSMISSIONMODE, ETHTSYN_E_PARAM);
  }
  else
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 EthTSynCtrlIdx;

    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
         EthTSynCtrlIdx++
       )
    {
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx == CtrlIdx)
      {
        if(EthTSyn_Ctrl[EthTSynCtrlIdx].TxMode != Mode)
        {
#if(ETHTSYN_SWITCH_USED == STD_ON)
          EthTSyn_IntPortIdxType Idx;
#endif
          TS_AtomicAssign8(EthTSyn_Ctrl[EthTSynCtrlIdx].TxMode, Mode);
          TS_AtomicAssign8(EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, 0U);
#if(ETHTSYN_SWITCH_USED == STD_ON)
          for(
           Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
           Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
           EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
           Idx++
         )
         {
            TS_AtomicAssign8(EthTSyn_SwitchPorts[Idx].Frame2Transmit, 0U);
         }
#endif
        }
        RetVal = E_OK;
      }
    }
    if(RetVal == E_NOT_OK)
    {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
       /* Throw a DET error if the input parameter "CtrlIdx" is not valid */
       /* !LINKSTO EthTSyn.SWS_EthTSyn_00172_CtrlIdx, 1 */
       ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_SETTRANSMISSIONMODE, ETHTSYN_E_CTRL_IDX);
#endif
    }
  }

  DBG_ETHTSYN_SETTRANSMISSIONMODE_EXIT(CtrlIdx, Mode);
}

#if(ETHTSYN_SWITCH_USED == STD_ON)
FUNC(void, ETHTSYN_CODE) EthTSyn_EthSwtPtpTimeStampIndication
(
  uint8 EthIfCtrlIdx,
  EthSwt_MgmtInfoType MgmtInfo,
  uint32 UniqueId,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) PortTimeStampPtr
)
{
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(ETHTSYN_UNINIT)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpTimeStampIndication.Uninit, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPTIMESTAMPINDICATION, ETHTSYN_E_UNINIT);
  }
  else if(PortTimeStampPtr == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpTimeStampIndication.NULL_PTR, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPTIMESTAMPINDICATION, ETHTSYN_E_PARAM_POINTER);
  }
  else
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 EthTSynCtrlIdx = 0U;
    Std_ReturnType RetVal;

    RetVal = EthTSyn_TranslateEthIfCtrlIdx(EthIfCtrlIdx, &EthTSynCtrlIdx);

    if(E_OK == RetVal)
    {
      EthTSyn_EthSwtPtpTimeStampIndicationSub
      (
        EthTSynCtrlIdx,
        MgmtInfo,
        UniqueId,
        PortTimeStampPtr
       );
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* !LINKSTO EthTSyn.EB.EthSwtPtpTimeStampIndication_InvalidControllerId, 1 */
      /* Throw a DET error if the input parameter "CtrlIdx" is not valid */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPTIMESTAMPINDICATION,
                               ETHTSYN_E_PARAM);
    }
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  }
}

FUNC(boolean, ETHTSYN_CODE) EthTSyn_EthSwtPtpRxIndication
(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHTSYN_APPL_DATA) MgmtInfoPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthIfCtrlIdx,
  uint16 Len,
  uint32 UniqueId
)
{
  boolean TimeStampRequired = FALSE;
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(ETHTSYN_UNINIT)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpRxIndication.Uninit, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_UNINIT);
  }
  else if(MgmtInfoPtr == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpRxIndication.NULL_PTR, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_PARAM_POINTER);
  }
  else if(DataPtr == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpRxIndication.NULL_PTR, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_PARAM_POINTER);
  }
  else if(IngressTimeStampPtr == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpRxIndication.NULL_PTR, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_PARAM_POINTER);
  }
  /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpRxIndication.InvalidHeaderSize, 1 */
  else if(ETHTSYN_PTP_HEADER_SIZE > Len)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_PARAM);
  }
  else
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 EthTSynCtrlIdx = 0U;
    Std_ReturnType RetVal;

    RetVal = EthTSyn_TranslateEthIfCtrlIdx(EthIfCtrlIdx, &EthTSynCtrlIdx);
    if(E_OK == RetVal)
    {
      /* !LINKSTO EthTSyn.EB.EthTSyn_EthSwtPtpRxIndication.InvalidDomainNumber, 1 */
      if(DataPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN] == EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncGlobalTimeDomainId)
      {
        /* Process received message */
        TimeStampRequired = EthTSyn_Inc02_ProcessRxSwtMsg(MgmtInfoPtr, IngressTimeStampPtr, DataPtr, EthTSynCtrlIdx, Len, UniqueId);
      }
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* !LINKSTO EthTSyn.EB.EthSwtPtpRxIndication_InvalidControllerId, 1 */
      /* Throw a DET error if the input parameter "CtrlIdx" is not valid */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_PARAM);
    }
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
  }

  return TimeStampRequired;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTransmitDebouncePerPort
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* Debouncing is done per port. */
  EthTSyn_IntPortIdxType Idx = 0U;
  uint8 ClearSwtFlag = 0U;
  /* if swt used */
  for(
       Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
       Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
       EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
       Idx++
     )
  {
    if(EthTSyn_SwitchPorts[Idx].Frame2Transmit != 0U)
    {
     if(EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
     {
       RetVal = EthTSyn_Inc02_TransmitSwtFrameWithDebounce(EthTSynCtrlIdx,Idx);
       if(
           (EthTSyn_RootCfgPtr->SwitchConfig[Idx].EthTSynPortDebounceTime != 0U) &&
           (RetVal == E_OK)
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON)
           /* The debounce values are already calculated for the non host port */
           /* If ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON the debounce for host port is ignored because
            * the sync frames are not transmitted by EthTSyn module and for the host port no
            * fup frame will be sent. */
           && (Idx != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt)
#endif
        )
        {
          boolean Updated = FALSE;
          /* set the debounce time */
          EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset =
             EthTSyn_RootCfgPtr->SwitchConfig[Idx].EthTSynPortDebounceTime +
             EthTSyn_GeneralCounter;
          if(EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
          {
            /* !LINKSTO EthTSyn.EB.DebounceCalculation_MaxValue, 1 */
            /* If calculated DebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE the frame transmission
              shall be lost. Decreasing the DebounceTimeOffset with 1 shall transmit the
              frame 1 EthTSyn_MainFunction() earlier, but the frame won't be lost. */
            EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset--;
          }

          /* call the controller min function*/
          Updated = EthTSyn_NextMinDebounceOffset
                    (&EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset,
                     EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset
                    );
          if(Updated == TRUE)
          {
           (void)EthTSyn_NextMinDebounceOffset
                 (&GlobalMinDebounceTimeOffset,
                  EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
                 );
          }
        }
      }
    }
  }
  for(
     Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
     Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
     EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
     Idx++
   )
  {
    if(EthTSyn_SwitchPorts[Idx].Frame2Transmit != 0U)
    {
      ClearSwtFlag++;
    }
  }
  if(ClearSwtFlag == 0U)
  {/* clear the flag */
    TS_AtomicClearBit_8
    (
     &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
     ETHTSYN_BITPOS_TX_SWT
    );
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTransmitDebouncePerCtrl
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  EthTSyn_IntPortIdxType Idx = 0U;
  /* if swt used */
  if(EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset ==
                                                ETHTSYN_INV_DEBOUNCE_VALUE)
  {
    uint8 ClearSwtFlag = 0U;
    for(
         Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
         Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
         EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
         Idx++
       )
    {
      if(EthTSyn_SwitchPorts[Idx].Frame2Transmit != 0U)
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00131, 1 */
        RetVal = EthTSyn_Inc02_TransmitSwtFrameWithDebounce(EthTSynCtrlIdx, Idx);
        if(EthTSyn_SwitchPorts[Idx].Frame2Transmit != 0U)
        {
          /* If still another frame must be transmitted don't clear the transmission flag */
          ClearSwtFlag++;
        }
        /* Debounce value is not calculated for the HostPort since it would add a
         * debounce counter between Sync frames on different ports. */
        if(
            (Idx != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt) &&
            (RetVal == E_OK)
          )
        {
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeDebounceTime != 0U)
          {
            /* !LINKSTO EthTSyn.EB.TransparentClock_DebounceValueSet, 1 */
            EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset =
                EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeDebounceTime +
                EthTSyn_GeneralCounter;

            if(EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
            {
              /* !LINKSTO EthTSyn.EB.DebounceCalculation_MaxValue, 1 */
              /* If calculated DebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE the frame transmission
                shall be lost. Decreasing the DebounceTimeOffset with 1 shall transmit the
                frame 1 EthTSyn_MainFunction() earlier, but the frame won't be lost. */
              EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset--;
            }

            /* needs to be set always when debounce is set to a new value != invalid */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00132, 1 */
            (void)EthTSyn_NextMinDebounceOffset
                  (&GlobalMinDebounceTimeOffset,
                   EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
                  );
          }
        }
      }
    }
    if(ClearSwtFlag == 0U)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_SWT
      );
    }
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_EthSwtPtpTimeStampIndicationSub
(
  uint8 EthTSynCtrlIdx,
  EthSwt_MgmtInfoType MgmtInfo,
  uint32 UniqueId,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) PortTimeStampPtr
)
{
  EthTSyn_IntPortIdxType Idx;
  boolean Found = FALSE;
  for
  (
     Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
    ((Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart))
        && (FALSE == Found));
     Idx++
  )
  {
    EthTSyn_PortSyncTxStateType PortSynTxState;
    EthTSyn_PortSyncTxStateType PortPdelayTxState;
    TS_AtomicAssign8
    (
      PortSynTxState,
      EthTSyn_SwitchPorts[Idx].SyncTxState
    );

    TS_AtomicAssign8
    (
      PortPdelayTxState,
      EthTSyn_SwitchPorts[Idx].PdelayState
    );

    if(
        (MgmtInfo.SwitchIdx == EthTSyn_RootCfgPtr->SwitchConfig[Idx].EthSwtIdx)
      &&
         /* Check if the received timestamp is valid. */
         /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
        (
          PortTimeStampPtr->nanoseconds <= ETHTSYN_NANOSEC_MAX
        )
      )
    {
      if(MgmtInfo.SwitchPortIdx == EthTSyn_RootCfgPtr->SwitchConfig[Idx].EthSwtPortIdx)
      {
        if(EthTSyn_SwitchPorts[Idx].UniqueId == UniqueId)
        {
          /* !LINKSTO EthTSyn.EB.EthSwt_GetTimeStamps, 1 */
          switch(PortSynTxState)
          {
            case ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS:
            {
              EthTSyn_SwitchPorts[Idx].SyncTimeStamp.nanoseconds = PortTimeStampPtr->nanoseconds;
              EthTSyn_SwitchPorts[Idx].SyncTimeStamp.seconds = PortTimeStampPtr->seconds;
              EthTSyn_SwitchPorts[Idx].SyncTimeStamp.secondsHi = PortTimeStampPtr->secondsHi;
#if(ETHTSYN_TIME_RECORDING == STD_ON)
              if(EthTSyn_RootCfgPtr->SwitchConfig[Idx].TimeValidationEnabled == TRUE)
              {
                /* Save the egress timestamp to be passed to the StbM. */
                /* Convert the egress timestamp. */
                (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime(&EthTSyn_SwitchPorts[Idx].SyncTimeStamp,
                   &EthTSyn_SwitchPorts[Idx].SyncMasterTimeRecording.syncEgressTimestamp);
              }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
              if(Idx == EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt)
              {
                /* For the host port, the only time when an egress timestamp is expected, is when the
                   GTM is not the MGM cpu. */
                /* T5 - T4 */
                /* !LINKSTO EthTSyn.EB.TransparentClock_SynchronizeT5T4_Invalid, 1 */
                EthTSyn_SubTimeStamps(
                               &EthTSyn_SwitchPorts[Idx].SyncTimeStamp, /* Egress on the host port */
                               &EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].SyncTimeStamp, /* Ingress timestamp in the switch */
                               &EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress /* (T5 - T4 ) */
                             );
                if(EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.sign == TRUE)
                {
                  TS_AtomicAssign8
                  (
                      EthTSyn_SwitchPorts[Idx].SyncTxState,
                      ETHTSYN_PORT_READY_FOR_TIME_SYNC
                  );
                }
              }
              else
              {
#endif
                /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_CTRL_READY_FUP-PORT_READY_FUP, 1 */
                /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_CTRL_READY-PORT_READY, 1 */
                /* !LINKSTO EthTSyn.Dsn.PortSynTxState_WAIT_EGRESS-READY_FUP, 1 */
                TS_AtomicAssign8
                (
                    EthTSyn_SwitchPorts[Idx].SyncTxState,
                    ETHTSYN_PORT_SYN_TX_STATE_READY_FOR_FUP
                );
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
              }
#endif
              Found = TRUE;
              break;
            }
            case ETHTSYN_PORT_SYN_TX_STATE_WAIT_INGRESS_TS:
            {

              EthTSyn_SwitchPorts[Idx].SyncTimeStamp.nanoseconds = PortTimeStampPtr->nanoseconds;
              EthTSyn_SwitchPorts[Idx].SyncTimeStamp.seconds = PortTimeStampPtr->seconds;
              EthTSyn_SwitchPorts[Idx].SyncTimeStamp.secondsHi = PortTimeStampPtr->secondsHi;
              /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_WAIT_SWT_INGRESS-VALID_INGRESS, 1 */
              /* !LINKSTO EthTSyn.Dsn.HostPortSynTxState_WAIT_INGRESS-VALID_INGRESS, 1 */
              /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_WAIT_INGRESS-VALID_INGRESS, 1 */
              TS_AtomicAssign8
              (
                  EthTSyn_SwitchPorts[Idx].SyncTxState,
                  ETHTSYN_PORT_SYN_TX_STATE_VALID_INGRESS_TS
              );
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON)
              {
                uint8 PortIndex;
                for(
                    PortIndex = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 1U;
                    PortIndex < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
                   PortIndex++
                 )
                {
                 /* If EthTSynSendSyncFrameOnlyOnHostPort set to true and a valid ingress
                    timestamp was received set all the non host ports to
                    ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS. */
                  TS_AtomicAssign8
                  (
                      EthTSyn_SwitchPorts[PortIndex].SyncTxState,
                      ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS
                  );
                }
              }
#endif /* (ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON) */
              Found = TRUE;
              break;
            }
            /* CHECK: NOPARSE */
            default:
            {
              /* This branch can not be reached since UniqueId will not match for other states. */
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
              ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
              break; /* Caution: this 'break' is required by MISRA-C:2012 */
            }
            /* CHECK: PARSE */
          }
          EthTSyn_SwitchPorts[Idx].UniqueId = ETHTSYN_UNIQUE_ID_INVALID;
        }
        else
        {
          if(EthTSyn_SwitchPorts[Idx].PdelayUniqueId == UniqueId)
          {
            /* !LINKSTO EthTSyn.EB.EthSwt_GetTimeStamps, 1 */
            switch(PortPdelayTxState)
            {
              case ETHTSYN_PORT_PDELAY_WAIT_EGRESS_TS:
              {
                /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayResp_SaveEgressTS, 1 */
                EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp.nanoseconds = PortTimeStampPtr->nanoseconds;
                EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp.seconds = PortTimeStampPtr->seconds;
                EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp.secondsHi = PortTimeStampPtr->secondsHi;
                /* Make sure that the transmit flag is set to true
                 * (this can be already set if a sync cycle is in progress) */
                /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayRespFup_Transmit, 1 */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
                if(Idx == EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave)
                {
                  /* Save T1 */
                  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1 = EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp;
                  /* If the egress timestamp was received on the slave port, it means that a pdelay calculation was started */
                  TS_AtomicSetBit_8
                  (
                    &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
                    ETHTSYN_BITPOS_PDELAYREQ_EGRESSCONF
                  );
                  /* If a slave started the calculation of the pdelay(by sending the Pdelay_Req) there is no need to transmit
                   * any other message */
                  TS_AtomicAssign8
                  (
                    EthTSyn_SwitchPorts[Idx].PdelayState,
                    ETHTSYN_PORT_PDELAY_STATE_IDLE
                  );
#if(ETHTSYN_TIME_RECORDING == STD_ON)
                  if(EthTSyn_RootCfgPtr->SwitchConfig[Idx].TimeValidationEnabled == TRUE)
                  {
                    /* Converted value of the responseReceiptTimestamp */
                    (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
                        (
                            &EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1,
                            &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestOriginTimestamp
                        );
                  }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */

                }
                else
#endif
                {
                  ETHTSYN_SET_TXFLAG
                    (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);
                  /* In the next mainfunction the pdelayrespFUp frame can be transmitted. */
                  /* !LINKSTO EthTSyn.EB.TimeAwareBridge_MasterTransmitPdelayRespFUp, 1 */
                  TS_AtomicSetBit_8
                  (
                    &EthTSyn_SwitchPorts[Idx].Frame2Transmit,
                    ETHTSYN_BITPOS_PDELAYRESP_FUP
                  );
                }
                Found = TRUE;
                break;
              }
              /* CHECK: NOPARSE */
              case ETHTSYN_PORT_PDELAY_WAIT_INGRESS_TS:
              {
                /* Not used */
                break;
              }
              default:
              {
                /* This branch can not be reached since UniqueId will not match for other states. */
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
                ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
                break; /* Caution: this 'break' is required by MISRA-C:2012 */
              }
              /* CHECK: PARSE */
            }
            EthTSyn_SwitchPorts[Idx].PdelayUniqueId = ETHTSYN_UNIQUE_ID_INVALID;
          }
        }
      }
      /* !LINKSTO EthTSyn.EB.Master.InvalidUniqueId, 1 */
      /* else ignore */
    }
    /* !LINKSTO EthTSyn.EB.Master.InvalidSwitchId, 1 */
    /* else ignore */
  }
}
#endif /* ETHTSYN_SWITCH_USED == STD_ON */

/* !LINKSTO EthTSyn.SWS_EthTSyn_00330, 1 */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SetProtocolParam
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_ProtocolParamType, AUTOMATIC, ETHTSYN_APPL_DATA) protocolParam
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 EthTSynCtrlIdx;
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  boolean TimeBaseFound = FALSE;
#endif

  DBG_ETHTSYN_SETPROTOCOLPARAM_ENTRY(timeBaseId, protocolParam);

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO EthTSyn.EB.SetProtocolParam.Uninit, 1 */
  if(ETHTSYN_UNINIT)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_SETPROTOCOLPARAM, ETHTSYN_E_UNINIT);
  }
  else if(protocolParam == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00228, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_SETPROTOCOLPARAM, ETHTSYN_E_PARAM_POINTER);
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Loop over all Master TimeDomains and update the ProtocolParam for each Domain that has
     * the referenced StbM TimeBaseId the same as the timeBaseId parameter.*/
    for(
         EthTSynCtrlIdx = ETHTSYN_MAX_SLAVE;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
         EthTSynCtrlIdx++
       )
    {
      if(timeBaseId == EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId)
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00226, 1 */
        SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();

        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.cumulativeScaledRateOffset = protocolParam->cumulativeScaledRateOffset;
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator = protocolParam->gmTimeBaseIndicator;
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.lastGmPhaseChange = protocolParam->lastGmPhaseChange;
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange = protocolParam->scaledLastGmFreqChange;

        SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        /* If no StbM TimeBases have the correct TimeBaseId a DET shall be reported. */
        TimeBaseFound = TRUE;
#endif
        RetVal = E_OK;
      }
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(TimeBaseFound == FALSE)
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00228, 1 */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_SETPROTOCOLPARAM, ETHTSYN_E_PARAM);
    }
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_ETHTSYN_SETPROTOCOLPARAM_EXIT(RetVal, timeBaseId, protocolParam);

  return RetVal;
}

FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetProtocolParam
(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_ProtocolParamType, AUTOMATIC, ETHTSYN_APPL_DATA) protocolParam
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  boolean TimeBaseFound = FALSE;
  uint8 EthTSynCtrlIdx;
  DBG_ETHTSYN_GETPROTOCOLPARAM_ENTRY(timeBaseId, protocolParam);

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO EthTSyn.EB.GetProtocolParam.Uninit, 1 */
  if(ETHTSYN_UNINIT)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_GETPROTOCOLPARAM, ETHTSYN_E_UNINIT);
  }
  else if(protocolParam == NULL_PTR)
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00229, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_GETPROTOCOLPARAM, ETHTSYN_E_PARAM_POINTER);
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Loop over all Slave TimeDomains and update the ProtocolParam to store the
     * Ieee TLV data in the last received SyncFUp frame and stop after first Slave is found. */

    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynSlaveIdx;
         EthTSynCtrlIdx++
       )
    {
      if((timeBaseId == EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId) && (TimeBaseFound == FALSE))
      {
        SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00227, 1 */
        protocolParam->cumulativeScaledRateOffset = EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.cumulativeScaledRateOffset;
        protocolParam->gmTimeBaseIndicator = EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator;
        protocolParam->lastGmPhaseChange = EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.lastGmPhaseChange;
        protocolParam->scaledLastGmFreqChange = EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange;
        protocolParam->protocolType = STBM_TIMESYNC_ETHERNET;

        SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();

        TimeBaseFound = TRUE;

        RetVal = E_OK;
      }
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(TimeBaseFound == FALSE)
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00229, 1 */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_GETPROTOCOLPARAM, ETHTSYN_E_PARAM);
    }
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_ETHTSYN_GETPROTOCOLPARAM_EXIT(RetVal, timeBaseId, protocolParam);

  return RetVal;
}
#if(ETHTSYN_ICV_USED == STD_ON)
#if(ETHTSYN_TOTAL_ICVTXLENGTH > 0U)
/* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_91001, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_IcvGenerationIndication
(

  P2CONST(Crypto_JobType, AUTOMATIC, ETHTSYN_APPL_DATA) job,
  Std_ReturnType result

)
{
  boolean JobIdFound = FALSE;
  uint8 EthTSynCtrlIdx;

  DBG_ETHTSYN_ICVGENERATIONINDICATION_ENTRY(jobId, result);
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(ETHTSYN_UNINIT)
  {
  /* !LINKSTO EthTSyn.EB.EthTSyn_IcvGenerationIndication.Uninit, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ICVGENERATIONINDICATION, ETHTSYN_E_UNINIT);
  }

  /* !LINKSTO EthTSyn.EB.EthTSyn_IcvGenerationIndication.NULL_PTR, 1 */
  else if(job == NULL_PTR)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ICVGENERATIONINDICATION, ETHTSYN_E_PARAM_POINTER);
  }

  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    const uint32 jobId = job->jobId;
    /* Loop over all Master TimeDomains and search if the jobId is configured. */
    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
         EthTSynCtrlIdx++
       )
    {
      if((jobId == ETHTSYN_ROOTCFG(EthTSynCtrlIdx).CsmJobId) && (JobIdFound == FALSE))
      {
        JobIdFound = TRUE;
        /* Check if an indication is pending. */
        if((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_WAIT_FOR_INDICATION_MASK) != FALSE)
        {
          if(result == CRYPTO_E_VER_OK)
          {
            /* If the generation of Icv was succesfully generated, frame can be updated accordingly
               and transmitted on the next mainfunction()*/
            TS_AtomicSetBit_8
             (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_INDICATION_RECEIVED_TX_FUP);
          }
          else
          {
            /* If the generation of Icv fails, frame can be updated accordingly
               and transmitted on the next mainfunction()*/
            TS_AtomicSetBit_8
             (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_GENERATION_FAILED);
          }
          ETHTSYN_SET_TXFLAG
            (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_FUP, TRUE);
          /* Indication was received. */
          TS_AtomicClearBit_8
          (
            &EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv,
             ETHTSYN_AUTH_WAIT_FOR_INDICATION
          );
          /* stop the running ICV generation timeout timer */
          /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00255, 1 */
          EthTSyn_Ctrl[EthTSynCtrlIdx].IcvIndication_Timeout = 0xFFFFFFFFU;
        }
      }
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(JobIdFound == FALSE)
    {
      /* If the indication is received for a JobId not configured, the error shall be
         reported to Det. */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00259, 1 */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ICVGENERATIONINDICATION, ETHTSYN_E_PARAM);
    }
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  }
  DBG_ETHTSYN_ICVGENERATIONINDICATION_EXIT(jobId, result);
}
#endif
#if(ETHTSYN_MAX_SLAVE != 0U)
/* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_91002, 1 */
FUNC(void, ETHTSYN_CODE) EthTSyn_IcvVerificationIndication
(

  P2CONST(Crypto_JobType, AUTOMATIC, ETHTSYN_APPL_DATA) job,
  Std_ReturnType result

)
{
  boolean JobIdFound = FALSE;
  uint8 EthTSynCtrlIdx;

  DBG_ETHTSYN_ICVVERIFICATIONINDICATION_ENTRY(jobId, result);
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(ETHTSYN_UNINIT)
  {
    /* !LINKSTO EthTSyn.EB.EthTSyn_IcvVerificationIndication.Uninit, 1 */
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ICVVERIFICATIONINDICATION, ETHTSYN_E_UNINIT);
  }

  /* !LINKSTO EthTSyn.EB.EthTSyn_IcvVerificationIndication.NULL_PTR, 1 */
  else if(job == NULL_PTR)
  {
    ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ICVVERIFICATIONINDICATION, ETHTSYN_E_PARAM_POINTER);
  }

  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    const uint32 jobId = job->jobId;
    /* Loop over all Slave TimeDomains and search if the jobId is configured. */
    for(
         EthTSynCtrlIdx = 0U;
         EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynSlaveIdx;
         EthTSynCtrlIdx++
       )
    {
      if((jobId == ETHTSYN_ROOTCFG(EthTSynCtrlIdx).CsmJobId) && (JobIdFound == FALSE))
      {
        JobIdFound = TRUE;
        /* Check if an indication is pending. */
        if((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_WAIT_INDICATION_MASK) != FALSE)
        {
          if(result == CRYPTO_E_VER_OK)
          {
            /* If the verification of Icv was succesfully verified, time can be passed to
               StbM on the next mainfunction()*/
            /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00244, 1 */
            TS_AtomicSetBit_8
             (&EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction, ETHTSYN_AUTH_VERIFICATION_PASSED);
            /* Clear any pending retry, the verification passed. */
            TS_AtomicClearBit_8
            (
              &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
              ETHTSYN_AUTH_VERIFICATION_ICV_RETRY
            );
          }
          else
          {
            /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00245, 1 */
            /* If the generation of Icv fails, frame can be updated accordingly
               and transmitted on the next mainfunction()*/
            TS_AtomicSetBit_8
             (&EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction, ETHTSYN_AUTH_VERIFICATION_FAILED);
          }

          /* Indication was received. */
          TS_AtomicClearBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
             ETHTSYN_AUTH_VERIFICATION_WAIT_INDICATION
          );
          /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00242, 1 */
          /* stop the running ICV verification timeout timer */
          EthTSyn_Slave[EthTSynCtrlIdx].IcvVerificationTimeout = 0xFFFFFFFFU;
        }
      }
    }
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(JobIdFound == FALSE)
    {
      /* If the indication is received for a JobId not configured, the error shall be
         reported to Det. */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00260, 1 */
      ETHTSYN_DET_REPORT_ERROR(ETHTSYN_SID_ICVVERIFICATIONINDICATION, ETHTSYN_E_PARAM);
    }
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  }
  DBG_ETHTSYN_ICVVERIFICATIONINDICATION_EXIT(jobId, result);
}
#endif /* #if(ETHTSYN_MAX_SLAVE != 0U) */
#endif /* #if(ETHTSYN_ICV_USED == STD_ON) */
/*==================[internal function definitions]=========================*/

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TranslateEthIfCtrlIdx
(
  uint8 EthIfCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) EthTSynCtrlIdxPtr
)
{
  uint8 EthTSynCtrlIdx;
  Std_ReturnType RetVal = E_NOT_OK;

  for(
       EthTSynCtrlIdx = 0U;
       EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
       EthTSynCtrlIdx++
     )
  {
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx == EthIfCtrlIdx)
    {
      *EthTSynCtrlIdxPtr = EthTSynCtrlIdx;
      RetVal = E_OK;
      break;
    }
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitSyncFrame
(
  uint8 EthTSynCtrlIdx
)
{
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00061, 2 */
  Std_ReturnType RetVal;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;

  /* Prepare time sync frame PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_TWOSTEP;
  PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_SYNC;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_SYNC;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00189, 1 */
  TS_AtomicAssign16(PTPHeader.SequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

  PTPHeader.LogMsgInterval = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxMsgLogInterval;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_PAYLOADSIZE;

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
  RetVal = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
  if(E_OK == RetVal)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
    {
      /* PTP mechanism is used */
      /* transportSpecific field is set to 0U */
      /* !LINKSTO EthTSyn.EB.ManyPtpProfiles, 1 */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC] = ETHTSYN_PTP_HEADER_MSGTYPE_SYNC;
      /* !LINKSTO EthTSyn.EB.FillE2EversionPTP, 1 */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B1_PTPVERSION] = ETHTSYN_PTP1588_HEADER_VERSION;
      /* Timescale bit is cleared */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B7_FLAGS_1] &= ETHTSYN_PTP1588_CLEAR_TIMESCALE_BIT;
    }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
  {
    /* Save SyncSequNumber to be reported to StbM for time recording */
    TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sequenceId,
                                                      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity =
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
         (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber =
         (uint16)(((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber |=
         (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
  }
#endif
    /* Set PTP payload */
    /* All bytes are reserved. */
    TS_MemBZero(&PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE], ETHTSYN_PTP_SYNC_PAYLOADSIZE);

    EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx = BufIdx;

    /* Send frame */
    RetVal = EthTSyn_TransmitFrame(EthTSynCtrlIdx, BufIdx, PTPHeader.MsgLength, TRUE);

    /* !LINKSTO EthTSyn.EB.EthIf_Transmit_NotOk, 1 */
    if(RetVal == E_OK)
    {
      TS_AtomicAssign8
      (
        EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
        ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_ETH_EGRESS_TS
      );

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_SYNC
      );

      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
    }
    else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_SYNC
      );

      EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
    }
  }


  return RetVal;
}


STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitSyncFUpFrame
(
  uint8 EthTSynCtrlIdx
)
{
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00061, 2 */
  Std_ReturnType TmpRet = E_NOT_OK;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  uint16 SubTlvSize = 0U;
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
  boolean FrameWasTransmitted = FALSE;
#endif /* ETHTSYN_ICV_USED == STD_ON */

  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_FUP;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_FUP;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00190, 1 */
  TS_AtomicAssign16(PTPHeader.SequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

  /* Same value as sync frame (See 802.1AS-2011 Ch 11.4.2.8) */
  PTPHeader.LogMsgInterval = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxMsgLogInterval;

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
  SubTlvSize = EthTSyn_CheckForAUTOSARSubTLV(EthTSynCtrlIdx);
#endif

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == FALSE)
  {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE + SubTlvSize;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  }
  else
  {
    /* IEEE1588_V2 is used */
    /* Timescale bit is cleared */
    PTPHeader.Flags = 0U;
    PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP1588_SYNC_FUP_PAYLOADSIZE;
  }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
  /* If Icv SubTLV is enabled, update the buffer */
  if((ETHTSYN_ROOTCFG(EthTSynCtrlIdx).TLVFollowUpICVSubTLV == TRUE) && (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout > 0U))
  {
    TmpRet = EthTSyn_CheckPendingTimeAuthTLV(EthTSynCtrlIdx, &PTPPayloadPtr, 0xFFU, 0xFFFFU, &FrameWasTransmitted);
  }
  else
#endif
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00203, 1 */
    TmpRet = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &PTPPayloadPtr);
  }
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
  if(FrameWasTransmitted == FALSE)
  {
#endif
    if(E_OK == TmpRet)
    {
      uint8 PayloadIdx = 0U;
      Eth_TimeStampType TempOriginTimestamp = {0U, 0U, 0U};

      /* Fill PTP header */
      EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[PayloadIdx]);
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == FALSE)
      {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
        /* gPTP mechanism is used */
        TempOriginTimestamp = EthTSyn_Ctrl[EthTSynCtrlIdx].OriginTimeStamp;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      }
      else
      {
        /* PTP mechanism is used */
        /* transportSpecific field is set to 0U */
        /* !LINKSTO EthTSyn.EB.ManyPtpProfiles, 1 */
        PTPPayloadPtr[ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC] = ETHTSYN_PTP_HEADER_MSGTYPE_FUP;
        /* !LINKSTO EthTSyn.EB.FillE2EversionPTP, 1 */
        PTPPayloadPtr[ETHTSYN_PTP_HEADER_B1_PTPVERSION] = ETHTSYN_PTP1588_HEADER_VERSION;
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
        EthTSyn_Int01_ConvertVirtualTimeToEthTime(&EthTSyn_Ctrl[EthTSynCtrlIdx].SyncEgressTimeStamp,
                                 &TempOriginTimestamp);
#else
        TempOriginTimestamp = EthTSyn_Ctrl[EthTSynCtrlIdx].SyncEgressTimeStamp;
#endif
        /* Correction field shall contain the difference between
         calculated origintimestamp and sync egress timestamp */
        TmpRet = EthTSyn_CorrField2PTPHeader
          (
            &EthTSyn_Ctrl[EthTSynCtrlIdx].OriginTimeStamp,
            &TempOriginTimestamp,
            &PTPPayloadPtr[PayloadIdx]
            );
      }
      /* !LINKSTO EthTSyn.EB.PTPE2EInvalidCorrectionTx, 1 */
      if(E_OK == TmpRet)
      {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
        PayloadIdx += ETHTSYN_PTP_HEADER_SIZE; /* Set payload index to next free space. */
        /* Set PTP payload */
        /* !LINKSTO EthTSyn.PRS_TS_00018, 1 */
        EthTSyn_TimeStampToArray
          (
            &TempOriginTimestamp, &PTPPayloadPtr[PayloadIdx]
          );
        PayloadIdx += ETHTSYN_TIME_STAMP_SIZE; /* Set payload index to next free space. */

        /* Add IEEE TLV information. */
        EthTSyn_FillFUpTLV(EthTSynCtrlIdx, &PTPPayloadPtr[PayloadIdx]);

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
        if(SubTlvSize > 0U)
        {
          /* The AUTOSAR TLV is used */
          EthTSyn_FillFUpAutosarTLV(EthTSynCtrlIdx, &PTPPayloadPtr[0U]);
          /* If OFS SubTLV is enabled, update(if needed) the value of the length field */
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpOFSSubTLV == TRUE)
          {
            if(EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfValidOfs != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TotalOfsTimebase)
            {
              uint8 FailedOfs = 0U;
              /* Calculate the number of failed StbM_GetOffset() */
              FailedOfs = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TotalOfsTimebase - EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfValidOfs;

               SubTlvSize -= ((uint16)FailedOfs) * ETHTSYN_FUP_SUBTLV_OFS_SIZE;

              if(SubTlvSize > ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH)
              {
                PTPHeader.MsgLength -= ((uint16)FailedOfs) * ETHTSYN_FUP_SUBTLV_OFS_SIZE;
              }
              else
              {
                /* If no tlv will be sent, we need to update also the msglength */
                PTPHeader.MsgLength -= ((((uint16)FailedOfs) * ETHTSYN_FUP_SUBTLV_OFS_SIZE) + ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH);
              }
              /* Update the tlv length */
              PTPPayloadPtr[ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1]
                = (uint8)((uint16)(PTPHeader.MsgLength & ETHTSYN_16BIT_MASK_MSB) >> 8U);
              PTPPayloadPtr[ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0]
               = (uint8)(PTPHeader.MsgLength & ETHTSYN_16BIT_MASK_LSB);
            }
            EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfValidOfs = 0U;
          }
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
          /* If Icv SubTLV is enabled, update the buffer */

          /* !LINKSTO EthTSyn.R22-11.PRS_TS_00223, 1 */
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpICVSubTLV == TRUE)
          {
            /* Confirmation of transmission needed to be passed to FVM */
            EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = BufIdx;
            EthTSyn_ProcessFupTxSubTlvIcv(EthTSynCtrlIdx, &PTPPayloadPtr[0U]);
            /* update the transmitted data */
            PTPHeader.MsgLength = (uint16)((uint16)PTPPayloadPtr[ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1] << 8U);
            PTPHeader.MsgLength |= (uint16)(PTPPayloadPtr[ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0]);
          }
#endif /* ETHTSYN_ICV_USED == STD_ON */
        }
#endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_ON) */
#if(ETHTSYN_ICV_USED == STD_ON)
        if(((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_GENERATION_FAILED_MASK) != FALSE) &&
           (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout > 0U))
        {
          P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) TmpPTPPayloadPtr;
          /* If generation fails, buffer needs to be requested */
          TmpRet = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &TmpPTPPayloadPtr);
          if(TmpRet == E_OK)
          {
            /* Copy the data to be transmitted */
            TS_MemCpy(TmpPTPPayloadPtr, PTPPayloadPtr, PTPHeader.MsgLength);
          }
          /* Set to IDLE. */
          TS_AtomicAssign8
          (
            EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv,
            ETHTSYN_AUTH_GENERATION_IDLE
          );
          /* Confirmation of transmission needed to be passed to FVM */
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = BufIdx;
        }
        if((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_WAIT_FOR_INDICATION_MASK) == FALSE)
        {
          /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
          if(E_OK == TmpRet)
          {
#endif /* ETHTSYN_ICV_USED == STD_ON */
            /* PortIdx not used */
            TmpRet = EthTSyn_TransmitAndRetry(EthTSynCtrlIdx, BufIdx, ETHTSYN_UNUSED_PORTIDX, PTPHeader.MsgLength);
#if(ETHTSYN_ICV_USED == STD_ON)
          }
        }
        else
        {
           /* clear the flag, indication is pending. */
           TS_AtomicClearBit_8
           (
             &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
             ETHTSYN_BITPOS_TX_FUP
           );
        }
#endif /* ETHTSYN_ICV_USED == STD_ON */
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    }
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
  }
#endif /* ETHTSYN_ICV_USED == STD_ON */
  return TmpRet;
}

#if(ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TransmitAnnounceFrame
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;

  /* Prepare time sync frame PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_ANNOUNCE;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_ANNOUNCE;

  /* Set sequence number. */
  TS_AtomicAssign16(PTPHeader.SequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

  PTPHeader.LogMsgInterval = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxMsgLogInterval;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_ANNOUNCE_PAYLOADSIZE;

  RetVal = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
  if(E_OK == RetVal)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);

    /* Set PTP payload */
    EthTSyn_FillAnnouncePayload(EthTSynCtrlIdx, &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE]);

    /* Send frame: Ignore return value. No error handling will be done. */
    (void) EthTSyn_TransmitFrame(EthTSynCtrlIdx, BufIdx, PTPHeader.MsgLength, FALSE);
  }
}
#endif /* ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON) */

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitPdelayReqFrame
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType TmpRet = E_NOT_OK;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  uint16 PdelayReqSequNumber;
  Eth_BufIdxType BufIdx = 0U;

  TS_AtomicAssign16(PdelayReqSequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber);
  /* Increment sequence number. The Sequence Counter shall wrap around at 65535 to 0 again. */
  /* !LINKSTO EthTSyn.PRS_TS_00188, 1 */
  if(ETHTSYN_SEQ_NUM_MAX == PdelayReqSequNumber)
  {
    /* The first transmission of the Pdelay_Req frame shall contain seqId 0.*/
    /* !LINKSTO EthTSyn.PRS_TS_00187_PdelayReq, 1 */
    PdelayReqSequNumber = 0U;
  }
  else
  {
    PdelayReqSequNumber++;
  }

  TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber, PdelayReqSequNumber);

  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_NOFLAGS;

  /* Set sequence number. */
  PTPHeader.SequNumber = PdelayReqSequNumber;

  PTPHeader.LogMsgInterval
    = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayTxMsgLogInterval;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
  {
    /* !LINKSTO EthTSyn.EB.PTPE2EEthTSynDelayReqFrameTx, 1 */
    /* If E2E mechanism is used for calculation of the delay, msgType and length must be updated
       accordingly. */
    PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ;
    PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_DELAY_REQ_PAYLOADSIZE;
    PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_DELAYREQ;
  }
  else
  {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ;
    PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE;
    PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_PDELAY;
    PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00200, 1 */
  TmpRet = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
  if(E_OK == TmpRet)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);
    /* TimeDomainId for Pdelay frames shall be 0U according to IEEE802.1AS-2020 chapter 11.4.2.4 */
    PTPPayloadPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN] = 0U;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
    {
      /* PTP mechanism is used */
      /* transportSpecific field is set to 0U */
      /* !LINKSTO EthTSyn.EB.ManyPtpProfiles, 1 */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC] = ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ;
      /* !LINKSTO EthTSyn.EB.FillE2EversionPTP, 1 */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B1_PTPVERSION] = ETHTSYN_PTP1588_HEADER_VERSION;
    }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    /* Set PTP payload */
    /* All bytes are reserved. */
    TS_MemBZero(&PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE], ((uint32)PTPHeader.MsgLength - ETHTSYN_PTP_HEADER_SIZE));

#if(ETHTSYN_MAX_SLAVE != 0U)
    if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx))
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
        StbM_TimeStampType StbMTimeStamp;
        StbM_UserDataType UserData;
        /* Save the value of the Virtual Local Time of the reference Global Time Tuple
         *  - referenceLocalTimestamp*/
        /* Save the value of the local instance of the Global Time of the reference
         *  Global Time Tuple referenceGlobalTimestamp */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00223, 1 */
        (void)StbM_BusGetCurrentTime
        (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
            &StbMTimeStamp,
            &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceLocalTimestamp,
            &UserData
        );
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceGlobalTimestamp.
          nanoseconds = StbMTimeStamp.nanoseconds;
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceGlobalTimestamp.
          seconds     = StbMTimeStamp.seconds;
        /* Save the Sequence Id of sent Pdelay_Req frame */
       TS_AtomicAssign8
        (
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.sequenceId,
        PdelayReqSequNumber
        );

       /* Save the sourcePortId of sent Pdelay_Req frame*/
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity =
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
           (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.portNumber =
           (uint16)(((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
       EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.portNumber |=
           (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
      }
#endif/* ETHTSYN_TIME_RECORDING == STD_ON */
    }
#endif/* ETHTSYN_MAX_SLAVE != 0U */

    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx = BufIdx;

    /* Send frame */
    TmpRet = EthTSyn_TransmitFrame(EthTSynCtrlIdx, BufIdx, PTPHeader.MsgLength, TRUE);

    if(E_OK == TmpRet)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYREQ
      );

      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* Set source port identity to find corresponding Pdelay response and Pdelay response follow
         up frames. */
      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
      TS_MemCpy(
                 &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Tx_SrcPortIdentity[0U],
                 &PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
                 ETHTSYN_SOURCEPORTIDENTITY_SIZE
               );
      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

      /* Set wait timeout for frame to transmit. */
      /* !LINKSTO EthTSyn.EB.EthTSynInitialGlobalTimeTxPdelayReqPeriod_Subsequent, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
        = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval;
#if(ETHTSYN_MAX_SLAVE != 0U)
      if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx))
      {
        /* A pdelay calculation is started */
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
          ETHTSYN_BITPOS_PDELAYREQ_SENT
        );
      }
#endif /* (ETHTSYN_MAX_SLAVE != 0U) */
#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
      /* Set wait timeout for receiving PdelayResp/PdelayResp_Fup frames. */
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFupPairTimeoutInit = TRUE;
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespPairTimeout
        = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespFupPairsPeriod;
#endif
    }
    else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
    {
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx = ETHTSYN_INV_BUFIDX;
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYREQ
      );

      EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);

      /* Set wait timeout for frame to transmit. */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
        = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval;
    }
  }

  return TmpRet;
}

/* !LINKSTO EthTSyn.SWS_EthTSyn_00201, 1 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitPdelayRespFrame
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType TmpRet;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00191_PdelayResp, 1 */
  TS_AtomicAssign16(
                     PTPHeader.SequNumber,
                     EthTSyn_Ctrl[EthTSynCtrlIdx].Ingress_PdelayReqSequNumber
                   );


  /* Reserved value (See 802.1AS-2011 Ch 11.4.2.8) */
  PTPHeader.LogMsgInterval = ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE;

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
  {
    /* If E2E mechanism is used for calculation of the delay, flags, msgType and control must be updated
       accordingly. */
    /* Prepare PTP header. */
    /* !LINKSTO EthTSyn.EB.PTPE2EEthTSynDelayRespFrameTx, 1 */
    PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_ONESTEP;
    PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP;
    PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_DELAYRESP;
  }
  else
  {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    /* Prepare PTP header. */
    PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_TWOSTEP;
    PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
    PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP;
    PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_PDELAY;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
  if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv == TRUE)
  {
    /* !LINKSTO EthTSyn.EB.DevAuth_PdelayResp, 1 */
    PTPHeader.MsgLength += ETHTSYN_AUTH_CHALLENGE_TLV_SIZE;
  }
#endif

  /* !LINKSTO EthTSyn.PRS_TS_00012, 1 */
  TmpRet = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
  if(E_OK == TmpRet)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);
    /* TimeDomainId for Pdelay frames shall be 0U according to IEEE802.1AS-2020 chapter 11.4.2.4 */
    PTPPayloadPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN] = 0U;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
    {
      /* PTP mechanism is used */
      /* transportSpecific field is set to 0U */
      /* !LINKSTO EthTSyn.EB.ManyPtpProfiles, 1 */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC] = ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP;
      /* !LINKSTO EthTSyn.EB.FillE2EversionPTP, 1 */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B1_PTPVERSION] = ETHTSYN_PTP1588_HEADER_VERSION;
    }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    TS_MemCpy(
               &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE],
               &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Rx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
        StbM_UserDataType UserData;
        StbM_TimeStampType StbMTimeStamp;
        StbM_VirtualLocalTimeType StbMVirtualLocalTime;

        StbMVirtualLocalTime.nanosecondsLo = 0U;
        StbMVirtualLocalTime.nanosecondsHi = 0U;
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00218, 1 */
        (void)StbM_BusGetCurrentTime
          (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
            &StbMTimeStamp, /* timeStampPtr */
            &StbMVirtualLocalTime, /* localTimePtr */
            &UserData /* userDataPtr */
          );

        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceLocalTimestamp.
            nanosecondsLo = StbMVirtualLocalTime.nanosecondsLo;
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceLocalTimestamp.
            nanosecondsHi = StbMVirtualLocalTime.nanosecondsHi;
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceGlobalTimestamp.
            nanoseconds = StbMTimeStamp.nanoseconds;
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceGlobalTimestamp.
            seconds = StbMTimeStamp.seconds;

        /* Save the sourcePortId of received Pdelay_Req frame*/
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity =
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.portNumber =
             (uint16)(((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.portNumber |=
             (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
      }
#endif

    /* Set PTP payload */
    EthTSyn_TimeStampToArray(&EthTSyn_Ctrl[EthTSynCtrlIdx].IngressTimeStamp,
                             &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE]);

#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
    if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv == TRUE)
    {
      /* !LINKSTO EthTSyn.EB.DevAuth_TLV, 1 */
      EthTSyn_FillAuthChallengeTLV(EthTSynCtrlIdx,
        &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE]);
    }
#endif

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
      {
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
        {
          /* Save the buffer id */
          EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx = BufIdx;
        }
        else
        {
          /* No need to save the the buffer id, no TxConfirmation is expected */
          EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx = ETHTSYN_INV_BUFIDX;
        }
#endif /* (ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE) */
      }
      else
      {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx = BufIdx;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

    /* !LINKSTO EthTSyn.PRS_TS_00012, 1 */
    TmpRet = EthTSyn_TransmitFrame(EthTSynCtrlIdx, BufIdx, PTPHeader.MsgLength, TRUE);

    if(TmpRet == E_OK)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYRESP
      );

      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
    }
    else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
    {
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx = ETHTSYN_INV_BUFIDX;
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYRESP
      );

      EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
    }
  }

  return TmpRet;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitPdelayRespFUpFrame
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType TmpRet;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  Eth_BufIdxType BufIdx = 0U;

  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_NOFLAGS;
  PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_PDELAY;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00191_PdelayRespFup, 1 */
  TS_AtomicAssign16(
                     PTPHeader.SequNumber,
                     EthTSyn_Ctrl[EthTSynCtrlIdx].Ingress_PdelayReqSequNumber
                   );

  /* Reserved value (See 802.1AS-2011 Ch 11.4.2.8) */
  PTPHeader.LogMsgInterval = ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE;

#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
  if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv == TRUE)
  {
    /* !LINKSTO EthTSyn.EB.DevAuth_PdelayRespFUp, 1 */
    PTPHeader.MsgLength += ETHTSYN_AUTH_CHALLENGE_TLV_SIZE;
  }
#endif

  /* !LINKSTO EthTSyn.EB.Master.SendPdelayResponseFU, 1 */
  TmpRet = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, PTPHeader.MsgLength, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
  if(E_OK == TmpRet)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);
    /* TimeDomainId for Pdelay frames shall be 0U according to IEEE802.1AS-2020 chapter 11.4.2.4 */
    PTPPayloadPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN] = 0U;
    TS_MemCpy(
               &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE],
               &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Rx_SrcPortIdentity[0U],
                ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
        /* Save the buffer id */
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFup_BufIdx = BufIdx;
      }
#endif
      /* Set PTP payload */
      EthTSyn_TimeStampToArray(&EthTSyn_Ctrl[EthTSynCtrlIdx].EgressTimeStamp_PdelayT3, &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE]);
#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
      if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv == TRUE)
      {
        /* !LINKSTO EthTSyn.EB.DevAuth_TLV, 1 */
        EthTSyn_FillAuthChallengeTLV(EthTSynCtrlIdx,
            &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE]);
        /* Clear the flag */
        TS_AtomicAssign8(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv, FALSE);
      }
#endif
    /* Send frame: Ignore return value since no retry possible. */
    /* !LINKSTO EthTSyn.EB.Master.SendPdelayResponseFU, 1 */
    TmpRet = EthTSyn_TransmitFrame(EthTSynCtrlIdx, BufIdx, PTPHeader.MsgLength, FALSE);
  }
  if(TmpRet == E_OK)
  {
    /* Reset variables */
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx = ETHTSYN_INV_BUFIDX;

    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
      ETHTSYN_BITPOS_PDELAYRESP_FUP
    );

    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
  }
  else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
  }
  else
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
      ETHTSYN_BITPOS_PDELAYRESP_FUP
    );

    EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
  }

  return TmpRet;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetTxBuffer
(
  uint8 EthTSynCtrlIdx,
  uint16 PayloadLength,
  P2VAR(Eth_BufIdxType, AUTOMATIC, ETHTSYN_APPL_DATA) BufIdxPtr,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  uint16 BufferSize = PayloadLength;
  Std_ReturnType RetVal = E_NOT_OK;
  BufReq_ReturnType RetVal_BufReq;


  /* Get Tx buffer. */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00162, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00163, 1 */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00148, 1 */
  /* !LINKSTO EthTSyn.EB.Master.FrameType, 1 */
  RetVal_BufReq = EthIf_ProvideTxBuffer
  (
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, /* EthIf CtrlIdx */
    ETHTSYN_PTP_FRAMETYPE, /* FrameType */
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].FramePriority, /* Priority */
    BufIdxPtr, /* BufIdxPtr */
    BufPtr, /* BufPtr */
    &BufferSize /* LenBytePtr */
  );

  if((PayloadLength <= BufferSize) && (BUFREQ_OK == RetVal_BufReq))
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/* !LINKSTO EthTSyn.R22-11.PRS_TS_00063, 1 */
/* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_FUp, 1 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillPTPHeader
(
  uint8 EthTSynCtrlIdx,
  P2CONST(EthTSyn_PTPHeaderType, AUTOMATIC, ETHTSYN_APPL_DATA) PTPHeader,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  uint8 SrcMacAddr[ETHTSYN_MAC_ADD_SIZE];

  BufPtr[ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE] = PTPHeader->MsgType & ETHTSYN_8BIT_MASK_LN;
  BufPtr[ETHTSYN_PTP_HEADER_B0_UN_TRANS_SPEC] |= ETHTSYN_PTP_HEADER_TRANS_SPEC_UN;
  BufPtr[ETHTSYN_PTP_HEADER_B1_PTPVERSION] = ETHTSYN_PTP_HEADER_VERSION;

  BufPtr[ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1]
    = (uint8)((uint16)(PTPHeader->MsgLength & ETHTSYN_16BIT_MASK_MSB) >> 8U);
  BufPtr[ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0]
   = (uint8)(PTPHeader->MsgLength & ETHTSYN_16BIT_MASK_LSB);

  BufPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN] =
      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncGlobalTimeDomainId;

  BufPtr[ETHTSYN_PTP_HEADER_B5_RESERVED] = ETHTSYN_PTP_HEADER_RESERVED;

  BufPtr[ETHTSYN_PTP_HEADER_B6_FLAGS_0] = (uint8)(PTPHeader->Flags & ETHTSYN_16BIT_MASK_LSB);
  BufPtr[ETHTSYN_PTP_HEADER_B7_FLAGS_1]
    = (uint8)((uint16)(PTPHeader->Flags & ETHTSYN_16BIT_MASK_MSB) >> 8U);

  BufPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B9_CORRFIELD_1] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B10_CORRFIELD_2] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B11_CORRFIELD_3] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B12_CORRFIELD_4] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B13_CORRFIELD_5] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B14_CORRFIELD_6] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B15_CORRFIELD_7] = 0x00U;

  BufPtr[ETHTSYN_PTP_HEADER_B16_RESERVED_0] = ETHTSYN_PTP_HEADER_RESERVED;
  BufPtr[ETHTSYN_PTP_HEADER_B17_RESERVED_1] = ETHTSYN_PTP_HEADER_RESERVED;
  BufPtr[ETHTSYN_PTP_HEADER_B18_RESERVED_2] = ETHTSYN_PTP_HEADER_RESERVED;
  BufPtr[ETHTSYN_PTP_HEADER_B19_RESERVED_3] = ETHTSYN_PTP_HEADER_RESERVED;

  /* Get source MAC address */
  EthIf_GetPhysAddr(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, &SrcMacAddr[0]);

  BufPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0] = SrcMacAddr[0U]; /* Source MAC upper 3 bytes */
  BufPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1] = SrcMacAddr[1U];
  BufPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2] = SrcMacAddr[2U];
  BufPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3] = ETHTSYN_PTP_HEADER_EUI48_IDX3_SRCPORTIDENTITY;
  BufPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4] = ETHTSYN_PTP_HEADER_EUI48_IDX4_SRCPORTIDENTITY;
  BufPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5] = SrcMacAddr[3U]; /* Source MAC lower 3 bytes */
  BufPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6] = SrcMacAddr[4U];
  BufPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7] = SrcMacAddr[5U];
  BufPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8] = 0x00U; /* 16 bit port number */
  BufPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9] = 0x01U;

  BufPtr[ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1]
    = (uint8)((uint16)(PTPHeader->SequNumber & ETHTSYN_16BIT_MASK_MSB) >> 8U);
  BufPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]
    = (uint8)(PTPHeader->SequNumber & ETHTSYN_16BIT_MASK_LSB);
  BufPtr[ETHTSYN_PTP_HEADER_B32_CONTROL] = PTPHeader->Control;
  BufPtr[ETHTSYN_PTP_HEADER_B33_LOGMSGINTERVAL] = PTPHeader->LogMsgInterval;

}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  uint32 ProtocolParamTemp;

  BufPtr[ETHTSYN_FUP_TLV_B0_TYPE_1] = ETHTSYN_FUP_TLV_TYPE_1;
  BufPtr[ETHTSYN_FUP_TLV_B1_TYPE_0] = ETHTSYN_FUP_TLV_TYPE_0;
  BufPtr[ETHTSYN_FUP_TLV_B2_LENGTH_1] = ETHTSYN_FUP_TLV_LENGTH_1;
  BufPtr[ETHTSYN_FUP_TLV_B3_LENGTH_0] = ETHTSYN_FUP_TLV_LENGTH_0;
  BufPtr[ETHTSYN_FUP_TLV_B4_ORGID_2] = ETHTSYN_FUP_TLV_ORGID_2;
  BufPtr[ETHTSYN_FUP_TLV_B5_ORGID_1] = ETHTSYN_FUP_TLV_ORGID_1;
  BufPtr[ETHTSYN_FUP_TLV_B6_ORGID_0] = ETHTSYN_FUP_TLV_ORGID_0;
  BufPtr[ETHTSYN_FUP_TLV_B7_ORG_SUBTYPE_2] = ETHTSYN_FUP_TLV_ORG_SUBTYPE_2;
  BufPtr[ETHTSYN_FUP_TLV_B8_ORG_SUBTYPE_1] = ETHTSYN_FUP_TLV_ORG_SUBTYPE_1;
  BufPtr[ETHTSYN_FUP_TLV_B9_ORG_SUBTYPE_0] = ETHTSYN_FUP_TLV_ORG_SUBTYPE_0;

  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();

  ProtocolParamTemp = (uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.cumulativeScaledRateOffset);

  BufPtr[ETHTSYN_FUP_TLV_B10_CSRO_3] = (uint8)((ProtocolParamTemp & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[ETHTSYN_FUP_TLV_B11_CSRO_2] = (uint8)((ProtocolParamTemp & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[ETHTSYN_FUP_TLV_B12_CSRO_1] = (uint8)((ProtocolParamTemp & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[ETHTSYN_FUP_TLV_B13_CSRO_0] = (uint8)(ProtocolParamTemp & ETHTSYN_32BIT_MASK0_LSB);

  BufPtr[ETHTSYN_FUP_TLV_B14_GM_TIMEBASEIND_1] = (uint8)((uint16)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[ETHTSYN_FUP_TLV_B15_GM_TIMEBASEIND_0] = (uint8)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator  & ETHTSYN_32BIT_MASK0_LSB);

  ProtocolParamTemp = (uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.lastGmPhaseChange);

  BufPtr[ETHTSYN_FUP_TLV_B16_GM_PH_CHG_0] = (uint8)((ProtocolParamTemp & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[ETHTSYN_FUP_TLV_B17_GM_PH_CHG_1] = (uint8)((ProtocolParamTemp & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[ETHTSYN_FUP_TLV_B18_GM_PH_CHG_2] = (uint8)((ProtocolParamTemp & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[ETHTSYN_FUP_TLV_B19_GM_PH_CHG_3] = (uint8)(ProtocolParamTemp & ETHTSYN_32BIT_MASK0_LSB);
  BufPtr[ETHTSYN_FUP_TLV_B20_GM_PH_CHG_4] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B21_GM_PH_CHG_5] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B22_GM_PH_CHG_6] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B23_GM_PH_CHG_7] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B24_GM_PH_CHG_8] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B25_GM_PH_CHG_9] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B26_GM_PH_CHG_10] = 0x00U;
  BufPtr[ETHTSYN_FUP_TLV_B27_GM_PH_CHG_11] = 0x00U;

  BufPtr[ETHTSYN_FUP_TLV_B28_GM_FREQ_CHG_3] = (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[ETHTSYN_FUP_TLV_B29_GM_FREQ_CHG_2] = (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[ETHTSYN_FUP_TLV_B30_GM_FREQ_CHG_1] = (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[ETHTSYN_FUP_TLV_B31_GM_FREQ_CHG_0] = (uint8)(EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange & ETHTSYN_32BIT_MASK0_LSB);

  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();

}

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_AutosarTLVHeader, 1 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpAutosarTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_TimeNotSecured, 1 */
  /* A time secured SubTlv will not be supported if
     EthTSynGlobalTimeTxCrcSecured is CRC_NOT_SUPPORTED */
  uint16 Length;
  uint8 AutosarTlvOffset = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE;

  uint8 SubTlvOffset = ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR;

  /* AUTOSAR TLV Header */
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B0_TYPE_1] = ETHTSYN_FUP_TLV_TYPE_1;
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B1_TYPE_0] = ETHTSYN_FUP_TLV_TYPE_0;

  /* Length without Sub-TLVs is 6U */
  Length = ETHTSYN_FUP_EXT_TLV_LENGTH_0;

  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B4_ORGID_2] = ETHTSYN_FUP_EXT_TLV_ORGID_2;
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B5_ORGID_1] = ETHTSYN_FUP_EXT_TLV_ORGID_1;
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B6_ORGID_0] = ETHTSYN_FUP_EXT_TLV_ORGID_0;
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B7_ORG_SUBTYPE_2] = ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_2;
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B8_ORG_SUBTYPE_1] = ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_1;
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B9_ORG_SUBTYPE_0] = ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_0;

  /* !LINKSTO EthTSyn.PRS_TS_00070, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00068, 1 */

#if(ETHTSYN_TX_CRC_USED == STD_ON)
  /* If the Master -> EthTSynTLVFollowUpTimeSubTLV is set */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_TimeSecured, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00074, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpTimeSubTLV == TRUE) &&
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].IsTxCrcSecuredUsed == ETHTSYN_CRC_SUPPORTED)
    )
  {
    /* Length is length plus the size in bytes of FUpSubTLVTime secured */
    Length += ETHTSYN_FUP_SUBTLV_TIME_SIZE;
    EthTSyn_FillFUpSubTLVTime_Secured
    (
      EthTSynCtrlIdx,
      &BufPtr[0U],
      SubTlvOffset
    );

    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
    SubTlvOffset += ETHTSYN_FUP_SUBTLV_TIME_SIZE;
  }

  /* If the Master -> EthTSynTLVFollowUpStatusSubTLV is set and CRC_SUPPORTED */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_StatusSecured, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpStatusSubTLV == TRUE) &&
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].IsTxCrcSecuredUsed == ETHTSYN_CRC_SUPPORTED)
    )
  {
    /* Length is length plus the size in bytes of FUpSubTLVStatus secured */
    Length += ETHTSYN_FUP_SUBTLV_STATUS_SIZE;
    /* !LINKSTO EthTSyn.PRS_TS_00077, 1 */
    EthTSyn_FillFUpSubTLVStatus_Secured
    (
      EthTSynCtrlIdx,
      &BufPtr[0U],
      SubTlvOffset
    );

    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
    SubTlvOffset += ETHTSYN_FUP_SUBTLV_STATUS_SIZE;
  }

  /* If the Master -> TLVFollowUpUserDataSubTLV is set and CRC_SUPPORTED */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_UserDataSecured, 1 */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_UserDataSecured, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpUserDataSubTLV == TRUE) &&
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].IsTxCrcSecuredUsed == ETHTSYN_CRC_SUPPORTED)
    )
  {
    /* SWS_EthTSyn_00153: If UserDataLength equals 0, UserDataSubTlv is excluded */
    if(EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength != 0U)
    {
      /* Length is length plus the size in bytes of FUpSubTLVUserData secured */
      Length += ETHTSYN_FUP_SUBTLV_USERDATA_SIZE;

      /* !LINKSTO EthTSyn.PRS_TS_00078, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00079, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00082, 1 */
      EthTSyn_FillFUpSubTLV_UserData_Secured
      (
        EthTSynCtrlIdx,
        &BufPtr[0U],
        SubTlvOffset
      );

      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
      SubTlvOffset += ETHTSYN_FUP_SUBTLV_USERDATA_SIZE;
    }
  }
#else
  TS_PARAM_UNUSED(EthTSynCtrlIdx);
#endif /* (ETHTSYN_TX_CRC_USED == STD_ON) */

  /* If the Master -> EthTSynTLVFollowUpStatusSubTLV is set and CRC_NOT_SUPPORTED */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_StatusNotSecured, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpStatusSubTLV == TRUE) &&
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].IsTxCrcSecuredUsed ==
        ETHTSYN_CRC_NOT_SUPPORTED
      )
    )
  {
    /* Length is length plus the size in bytes of FUpSubTLVStatus not secured */
    Length += ETHTSYN_FUP_SUBTLV_STATUS_SIZE;
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
    EthTSyn_FillFUpSubTLVStatus_NotSecured
    (
      &BufPtr[0U],
      SubTlvOffset
    );

    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
    SubTlvOffset += ETHTSYN_FUP_SUBTLV_STATUS_SIZE;
  }

  /* If the Master -> TLVFollowUpUserDataSubTLV is set and CRC_NOT_SUPPORTED */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_UserDataNotSecured, 1 */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_UserDataNotSecured, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpUserDataSubTLV == TRUE) &&
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].IsTxCrcSecuredUsed ==
        ETHTSYN_CRC_NOT_SUPPORTED
      )
    )
  {
    /* If UserDataLength equals 0, UserDataSubTlv is excluded */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00153, 1 */
    if(EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength != 0U)
    {
      /* Length is length plus the size in bytes of FUpSubTLVUserData not secured */
      Length += ETHTSYN_FUP_SUBTLV_USERDATA_SIZE;

      /* !LINKSTO EthTSyn.PRS_TS_00078, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00079, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00082, 1 */
      EthTSyn_FillFUpSubTLV_UserData_NotSecured
      (
        EthTSynCtrlIdx,
        &BufPtr[0U],
        SubTlvOffset
      );

      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
      SubTlvOffset += ETHTSYN_FUP_SUBTLV_USERDATA_SIZE;
    }
  }

  /* If the Master -> EthTSynTLVFollowUpOFSSubTLV is set */
  /* !LINKSTO EthTSyn.PRS_TS_00086, 1 */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_OFSSecured, 1 */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpOFSSubTLV == TRUE)
  {
    Std_ReturnType RetVal = E_NOT_OK;
    uint8 OfsIdx = 0U;

    for(OfsIdx = 0U; OfsIdx < EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TotalOfsTimebase; OfsIdx++)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
      RetVal = EthTSyn_FillFUpSubTLVOfs
      (
        EthTSynCtrlIdx,
        &BufPtr[0U],
        SubTlvOffset,
        OfsIdx
      );

      if(E_OK == RetVal)
      {
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00071, 1 */
        /* Length is length plus the size in bytes of FUpSubTLVOfs not secured */
        Length += ETHTSYN_FUP_SUBTLV_OFS_SIZE;
        /* If multiple OFS timedomains are used, we need to update where to add
         * the next OFS Sub-TLV */
        SubTlvOffset += ETHTSYN_FUP_SUBTLV_OFS_SIZE;
      }
      /* If something is wrong, e.g. StbM_GetOffset() is returning E_NOT_OK, nothing to do,
       * only valid OFS will be added to the Fup message. */
    }
  }
#if(ETHTSYN_ICV_USED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpICVSubTLV == TRUE)
  {
    /* start of the time auth sub-TLV */
    EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv = SubTlvOffset;
    Length += EthTSyn_Ctrl[EthTSynCtrlIdx].TimeAuthTotalLength;
  }
#endif /* ETHTSYN_ICV_USED == STD_ON */

  /* !LINKSTO EthTSyn.PRS_TS_00067, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00069, 1 */
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B2_LENGTH_1] = (uint8)((Length >>  8U) & 0xFFU);
  BufPtr[AutosarTlvOffset + ETHTSYN_FUP_TLV_B3_LENGTH_0] = (uint8)((Length       ) & 0xFFU);

}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVStatus_NotSecured
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset
)
{
  /* AUTOSAR TLV Sub-TLV: Status Not Secured */
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B0_TYPE] =
    ETHTSYN_FUP_SUBTLV_STATUS_NOT_SECURED_TYPE;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B1_LENGTH] =
    ETHTSYN_FUP_SUBTLV_STATUS_LENGTH;
  EthTSyn_FUpSubTLVStatus(&BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS]);
  /* Not used */
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B3_CRC_STATUS] =
    ETHTSYN_FUP_SUBTLV_STATUS_CRC_STATUS;
}


STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLV_UserData_NotSecured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset
)
{
  /* AUTOSAR TLV Sub-TLV: UserData Secured */
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B0_TYPE] =
    ETHTSYN_FUP_SUBTLV_USERDATA_NOT_SECURED_TYPE;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B1_LENGTH] =
    ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B6_CRC_USERDATA] = 0U;
}


STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVOfs
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset,
  uint8 OfsIdx
)
{
  uint8 Crc_Ofs = 0U;
  StbM_TimeStampType timeStamp;
  StbM_UserDataType userData;
  Std_ReturnType Retval = E_NOT_OK;

  /* !LINKSTO EthTSyn.PRS_TS_00095, 1 */
  /* !LINKSTO EthTSyn.EB.OffsetSubTlv_GetOffset_NOK, 2 */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00199, 1 */
  Retval = StbM_GetOffset
  (
      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsInfo[OfsIdx].OffsetTimeBaseId, &timeStamp, &userData
  );

  if(E_OK == Retval)
  {
    /* In case StbM_GetOffset () returns a value different of E_OK ,
       we need to update the length field in AUTOSAR Tlv header. */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfValidOfs++;
    /* Length */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B1_LENGTH] = ETHTSYN_FUP_SUBTLV_OFS_LENGTH;

    /* OfsTimeDomain */
    /* !LINKSTO EthTSyn.PRS_TS_00085, 1 */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B2_TIMEDOMAIN] =
                                   EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsInfo[OfsIdx].OfsGlobalTimeDomainId;

    /* OfsTimeSec - SecondsHi */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B3_TIMESEC] =
                                (uint8)((uint16)(timeStamp.secondsHi & ETHTSYN_32BIT_MASK1) >> 8U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B4_TIMESEC] =
                                (uint8)(timeStamp.secondsHi  & ETHTSYN_32BIT_MASK0_LSB);
    /* OfsTimeSec - Seconds */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B5_TIMESEC] =
                             (uint8)((uint32)(timeStamp.seconds & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B6_TIMESEC] =
                             (uint8)((uint32)(timeStamp.seconds & ETHTSYN_32BIT_MASK2) >> 16U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B7_TIMESEC] =
                             (uint8)((uint32)(timeStamp.seconds & ETHTSYN_32BIT_MASK1) >> 8U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B8_TIMESEC] =
                             (uint8)(timeStamp.seconds  & ETHTSYN_32BIT_MASK0_LSB);

    /* OfsTimeNSec */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B9_TIMENSEC] =
                         (uint8)((uint32)(timeStamp.nanoseconds & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B10_TIMENSEC] =
                         (uint8)((uint32)(timeStamp.nanoseconds & ETHTSYN_32BIT_MASK2) >> 16U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B11_TIMENSEC] =
                         (uint8)((uint32)(timeStamp.nanoseconds & ETHTSYN_32BIT_MASK1) >> 8U);
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B12_TIMENSEC] =
                         (uint8)(timeStamp.nanoseconds & ETHTSYN_32BIT_MASK0_LSB);

    /* Status */
    /* !LINKSTO EthTSyn.PRS_TS_00094, 1 */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B13_STATUS] = timeStamp.timeBaseStatus;

    /* userDataLength */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00087, 1 */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B14_USER_DATA_LENGTH] =  userData.userDataLength;

    /* userBytes */
    /* !LINKSTO EthTSyn.PRS_TS_00089, 1 */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B15_USER_DATA_BYTE_0] =  userData.userByte0;
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B16_USER_DATA_BYTE_1] =  userData.userByte1;
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B17_USER_DATA_BYTE_2] =  userData.userByte2;

    /* !LINKSTO EthTSyn.PRS_TS_00084, 1 */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].IsTxCrcSecuredUsed == ETHTSYN_CRC_SUPPORTED)
    {
      /* AUTOSAR TLV Sub-TLV: OFS Secured */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_OFSSecured, 1 */
      BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B0_TYPE] = ETHTSYN_FUP_SUBTLV_OFS_SECURED_TYPE;
      /* !LINKSTO EthTSyn.PRS_TS_00103, 1 */
      (void)EthTSyn_CalcComp_OfsCrc(EthTSynCtrlIdx, &BufPtr[0U], SubTlvOffset, &Crc_Ofs);
    }
    else
    {
      /* AUTOSAR TLV Sub-TLV: OFS Not Secured */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_OFSNotSecured, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_OFSnotSecured, 1 */
      BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B0_TYPE] =
                                                            ETHTSYN_FUP_SUBTLV_OFS_NOT_SECURED_TYPE;
    }

    /* CRC_OFS */
    BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B18_CRC] = Crc_Ofs;
  }

  return Retval;
}
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FUpSubTLVStatus
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  BufPtr[0U] = 0U;

  /* Set status from master SYNC_TO_GATEWAY bit */
  if((EthTSyn_MasterTimeBaseStatus.GlobalTimebaseStatus & ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM) > 0U)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00094_SyncToGatewaySet, 1 */
    BufPtr[0U] |= ETHTSYN_SYNC_TO_SUBDOMAIN; /* the offset is 0 */
  }
  else
  {
    /* !LINKSTO EthTSyn.PRS_TS_00094_SyncToGatewayNOTSet, 1 */
    BufPtr[0U] |= ETHTSYN_SYNC_TO_GTM;
  }
}

#if(ETHTSYN_ICV_USED == STD_ON)

#if(ETHTSYN_TOTAL_ICVTXLENGTH > 0U)

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessFupTxSubTlvIcv
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00224, 1 */
#if(ETHTSYN_TRUNC_FV_USED == STD_ON)
  uint32 tmpFreshnesslength = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueLength;
#endif
  uint32 tmpTruncFreshnesslength = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength;
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00225, 1 */
  uint32 macLength = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength;
  uint16 frameOffset = EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv;
  uint8 tmpArray_freshnesstrunc[8U] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
  uint8 byteLengthTruncFVL = 0U;

#if(ETHTSYN_TRUNC_FV_USED == STD_ON)
  uint8 tmpArray_freshness[8U]  = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
  uint8 byteLengthFVL = 0U;
  boolean tmpTruncEnabled = FALSE;
#endif
  uint16 bufLength = 0U;

#if(ETHTSYN_MASTER_FV_USED == STD_ON)
  /* Check If freshnesscounter is referenced. */
  if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId != ETHTSYN_FV_NOT_CONFIGURED)
  {
#if(ETHTSYN_TRUNC_FV_USED == STD_ON)
    if(tmpFreshnesslength > tmpTruncFreshnesslength)
    {
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00247, 1 */
      /* When the configured truncated FV length (StbMFreshnessValueTruncLength)
         is less than FV length (StbMFreshnessValueLength) in StbM,
         the Time Master shall call the StbM_GetTxFreshnessTruncData Api in order to
         obtain the full FV and the truncated FV. */
      RetVal = StbM_GetTxFreshnessTruncData
        (
          ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId,
          &tmpFreshnesslength,
          &tmpTruncFreshnesslength,
          &tmpArray_freshness[0U],
          &tmpArray_freshnesstrunc[0U]
         );
      tmpTruncEnabled = TRUE;
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00234, 1 */
      if((tmpFreshnesslength % ETHTSYN_8_BITS) != 0U)
      {
        /* use length in bytes */
        byteLengthFVL = ((uint8)tmpFreshnesslength / ETHTSYN_8_BITS) + 1U;
      }
      else
      {
        byteLengthFVL = (uint8)tmpFreshnesslength / ETHTSYN_8_BITS;
      }
    }
    else
#endif /* if(ETHTSYN_TRUNC_FV_USED == STD_ON) */
    {
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00246, 1 */
      /* When the FV is referenced (refer EthTSynIcvGenerationFvIdRef)
         and the configured truncated FV length (StbMFreshnessValueTruncLength)
         is equal to FV length (StbMFreshnessValueLength) in StbM,
         the Time Master shall call the StbM_GetTxFreshness.
         Config limitation:
         StbMFreshnessValueTruncLength can't be bigger than StbMFreshnessValueLength.*/
      RetVal = StbM_GetTxFreshness
      (
          ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId,
          &tmpTruncFreshnesslength,
          &tmpArray_freshnesstrunc[0U]
       );
    }
    if((tmpTruncFreshnesslength % ETHTSYN_8_BITS) != 0U)
    {
      /* use length in bytes */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00234, 1 */
      byteLengthTruncFVL = ((uint8)tmpTruncFreshnesslength / ETHTSYN_8_BITS) + 1U;
    }
    else
    {
      byteLengthTruncFVL = (uint8)tmpTruncFreshnesslength / ETHTSYN_8_BITS;
    }
  }
  else
  {
    /* No freshness configured, proceed with filling the timeauth sub-tlv. */
    RetVal = E_OK;
  }
#endif /* #if(ETHTSYN_MASTER_FV_USED == STD_ON) */

#if(ETHTSYN_MASTER_FV_USED == STD_ON)
  if(RetVal == E_OK)
  {
#endif /* #if(ETHTSYN_MASTER_FV_USED == STD_ON) */
    bufLength = (frameOffset + ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH);
    /* Construct the ICV sub-tlv. */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00248, 1 */
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00063_TimeAuthNotSecured, 1 */
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_TimeAutenticated_CrcSupported, 1 */
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_000104_MsgComplianceOFF_TimeAuth, 1 */
    EthTSyn_FillFUpSubTLVIcv(EthTSynCtrlIdx, frameOffset, byteLengthTruncFVL, &tmpArray_freshnesstrunc[0U], BufPtr);

    /* Copy the Fup frame in a tempBuffer*/
    TS_MemCpy(&EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U], BufPtr, bufLength);
    /* Check If freshnesscounter is referenced. */
    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId != ETHTSYN_FV_NOT_CONFIGURED)
    {
#if(ETHTSYN_TRUNC_FV_USED == STD_ON)
      if(tmpTruncEnabled == TRUE)
      {
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00249, 1 */
        /* Move the index as FVL was updated. */
        bufLength++;
        /* update the buffer in order to generate the ICV with full FV */
        TS_MemCpy(&EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[frameOffset + ETHTSYN_TIMEAUTH_TLV_B5_FV], &tmpArray_freshness[0U], byteLengthFVL);
        /* update the length of the frame */
        bufLength += byteLengthFVL;
      }
      else
#endif
      {
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00248, 1 */
        EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[frameOffset + ETHTSYN_TIMEAUTH_TLV_B4_FVL] = (uint8)tmpTruncFreshnesslength;
        /* Move the index as FVL was updated. */
        bufLength++;
        /* update the buffer in order to generate the ICV with full FV */
        TS_MemCpy(&EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[frameOffset + ETHTSYN_TIMEAUTH_TLV_B5_FV], &tmpArray_freshnesstrunc[0U], byteLengthTruncFVL);
        /* update the length of the frame */
        bufLength += byteLengthTruncFVL;
      }
    }

    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationBase == TRUE)
    {
      /* Symmetric cryptography selection for the ICV generation. */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00251, 1 */
      /* EthTSynIcvGenerationBase for the Time Domain is configured to ICV_MAC */
#if(ETHTSYN_ICV_BASE_MAC == STD_ON)
      RetVal = Csm_MacGenerate
               (
                ETHTSYN_ROOTCFG(EthTSynCtrlIdx).CsmJobId,
                CRYPTO_OPERATIONMODE_SINGLECALL,
                &EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U],
                bufLength,
                &EthTSyn_IcvTxFrame[ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxOffset],
                &macLength
               );
#endif
    }
    else
    {
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00252, 1 */
      /* Asymmetric cryptography selection for the ICV generation. */
      /* EthTSynIcvGenerationBase for the Time Domain is configured to ICV_SIGNATURE */
#if(ETHTSYN_ICV_BASE_SIGNATURE == STD_ON)
      RetVal = Csm_SignatureGenerate
               (
                ETHTSYN_ROOTCFG(EthTSynCtrlIdx).CsmJobId,
                CRYPTO_OPERATIONMODE_SINGLECALL,
                &EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U],
                bufLength,
                &EthTSyn_IcvTxFrame[ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxOffset],
                &macLength
               );
#endif
    }
    if(RetVal == E_OK)
    {
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00238, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00238, 1 */
      if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout == 0U)
      {
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00253, 1 */
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00227, 1 */
        /* Synchronous job is configured */
        if(EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments > 0U)
        {
          /* If the ICV length is bigger than the max supported value,
          multiple time auth sub-tlvs will be transmitted. */
          EthTSyn_FillSegmentsIcv(EthTSynCtrlIdx, (uint8)tmpTruncFreshnesslength, frameOffset, &BufPtr);
        }
        else
        {
          /* Fill the buffer with data to be transmitted. */
          frameOffset += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
#if(ETHTSYN_MASTER_FV_USED == STD_ON)
          if(byteLengthTruncFVL != 0U)
          {
            BufPtr[frameOffset++] = (uint8)tmpTruncFreshnesslength;
            TS_MemCpy(&BufPtr[frameOffset], &tmpArray_freshnesstrunc[0U], byteLengthTruncFVL);
            frameOffset += (uint16)byteLengthTruncFVL;
          }
#endif
          /* Copy the Icv to the fup frame */
          TS_MemCpy(&BufPtr[frameOffset], &EthTSyn_IcvTxFrame[ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxOffset], macLength);
        }
        TS_AtomicSetBit_8
               (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_TRANSMIT_FRAME);
      }
      else
      {
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00254_MacGenerate, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00254_SignatureGenerate, 1 */
        /* Asynchronous job is configured */
        frameOffset = frameOffset + ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
#if(ETHTSYN_MASTER_FV_USED == STD_ON)
        if(byteLengthTruncFVL != 0U)
        {
          BufPtr[frameOffset++] = (uint8)tmpTruncFreshnesslength;
          TS_MemCpy(&BufPtr[frameOffset], &tmpArray_freshnesstrunc[0U], byteLengthTruncFVL);
          frameOffset += (uint16)byteLengthTruncFVL;
        }
#endif
        /* load the timer and wait for indication */
        EthTSyn_Ctrl[EthTSynCtrlIdx].IcvIndication_Timeout = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout;
        TS_AtomicSetBit_8
               (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_WAIT_FOR_INDICATION);
        /* Save the offset from where ICV should be added. */
        EthTSyn_Ctrl[EthTSynCtrlIdx].IcvAuthTlvOffset = frameOffset;
      }
    }
    else
    {
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00256_MacGenerate_StopIcv, 1 */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00256_SignatureGenerate_StopIcv, 1 */
      EthTSyn_FillBufIcvGenFailed(EthTSynCtrlIdx, BufPtr);
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
      EthTSyn_ReportToIdsM(EthTSynCtrlIdx, ETHTSYN_SEV_ICV_GENERATION_FAILED);
#endif
      TS_AtomicSetBit_8
                 (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_GENERATION_FAILED);
    }
#if(ETHTSYN_MASTER_FV_USED == STD_ON)
  }
  else
  {
#if(ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON)
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00250_GetTxFreshness_CallDet, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00250_GetTxFreshnessTruncData_CallDet, 1 */
    ETHTSYN_DET_RUNTIME_REPORT_ERROR(ETHTSYN_SID_MAINFUNCTION, ETHTSYN_E_FRESHNESSFAILURE);
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */

    EthTSyn_FillBufIcvGenFailed(EthTSynCtrlIdx, BufPtr);
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
      EthTSyn_ReportToIdsM(EthTSynCtrlIdx, ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE);
#endif

    TS_AtomicSetBit_8
               (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_GENERATION_FAILED);
  }
#endif /* #if(ETHTSYN_MASTER_FV_USED == STD_ON) */

}

/* !LINKSTO EthTSyn.R22-11.PRS_TS_00093_TimeAutenticated_CrcNotSupported, 1 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVIcv
(
  uint8 EthTSynCtrlIdx,
  uint16 SubTlvOffset,
  uint8 FreshnessValueLength,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) FreshnessPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  uint8 Idx = 0U;
  uint8 tmpFreshnessValue = 0U;
  uint16 lengthSubTlv = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength;
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00236, 1 */
  if(FreshnessValueLength > 0U)
  {
    /* ICV_Flags */
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00235, 1 */
    BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] |= ETHTSYN_ICV_WITH_FV;
    /* FreshnessValueLength */
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00235, 1 */
    BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B4_FVL] = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength;
    for(Idx = 0U; Idx < FreshnessValueLength; Idx++)
    {
      /* Add the freshness value.*/
      BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B5_FV + Idx] = FreshnessPtr[Idx];
    }
    tmpFreshnessValue = (FreshnessValueLength + ETHTSYN_FUP_LEN_FVL);
  }
  else
  {
    /* ICV_Flags */
    BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] = 0U;
  }
  if(lengthSubTlv > ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITH_FVL(FreshnessValueLength))
  {
    /* ICV_Flags */
    BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] |= ETHTSYN_ICV_IN_MULTIPLE_SUBTLV;
  }
  else
  {
    lengthSubTlv += ((uint16)tmpFreshnessValue + ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI);
  }

  /* ICV type */
  BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B0_TYPE] = ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE;
  /* Length of the frame */
  BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] = (uint8)lengthSubTlv;
  /* Sequence number */
  BufPtr[SubTlvOffset + ETHTSYN_TIMEAUTH_TLV_B3_SEQNR] = 0U;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CheckPendingTimeAuthTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  EthTSyn_IntPortIdxType PortIdx,
  uint16 PayloadLength,
  P2VAR(boolean, AUTOMATIC, ETHTSYN_APPL_DATA) FrameWasTransmitted
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_BufIdxType BufIdx = 0U;
  uint16 FrameLength = EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv;
  if(EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv == ETHTSYN_AUTH_GENERATION_IDLE)
  {
    /* If no generation of the ICV is pending, proceed with creating the Fup frame to be
       transmitted. */
    *BufPtr = &EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U];
    RetVal = E_OK;
    *FrameWasTransmitted = FALSE;
  }
  else if((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_GENERATION_FAILED_MASK) != FALSE)
  {
    FrameLength += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
    EthTSyn_FillBufIcvGenFailed(EthTSynCtrlIdx, &EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U]);
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
      EthTSyn_ReportToIdsM(EthTSynCtrlIdx, ETHTSYN_SEV_ICV_GENERATION_FAILED);
#endif
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
    {
      RetVal = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, FrameLength, &BufIdx, BufPtr);
    }
#if(ETHTSYN_SWITCH_USED == STD_ON)
    else
    {
      RetVal = EthTSyn_Inc02_GetSwtTxBuffer
      (EthTSynCtrlIdx, PayloadLength, PortIdx, &BufIdx, BufPtr);
    }
#endif
    /* Prepare the buffer to transmit */
    /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
    if(E_OK == RetVal)
    {
      TS_MemCpy(&((*BufPtr)[0]), &EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U], FrameLength);
      *FrameWasTransmitted = TRUE;
      /* Confirmation of transmission needed to be passed to FVM */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = BufIdx;
    }
  }
  /* CHECK: NOPARSE */
  /* - GetTxBuffer RetVal and IcvSegments branches are already covered in tests.
     - Empty else branch is unreachable because this functin will be called only when NextIcvAction is GENERATION_IDLE,
     GENERATION_FAILED or INDICATION_RECEIVED states. */
  else if((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_INDICATION_RECEIVED_TX_FUP_MASK) != FALSE)
  {
    FrameLength += EthTSyn_Ctrl[EthTSynCtrlIdx].TimeAuthTotalLength;
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00257, 1 */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
    {
      RetVal = EthTSyn_GetTxBuffer(EthTSynCtrlIdx, FrameLength, &BufIdx, BufPtr);
    }
#if(ETHTSYN_SWITCH_USED == STD_ON)
    else
    {
      RetVal = EthTSyn_Inc02_GetSwtTxBuffer
      (EthTSynCtrlIdx, PayloadLength, PortIdx, &BufIdx, BufPtr);
    }
#endif
    /* Icv succesfully generated, frame can be sent. */
    /* Prepare the buffer to transmit */
    /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
    if(E_OK == RetVal)
    {
      TS_MemCpy(&((*BufPtr)[0]), &EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U], EthTSyn_Ctrl[EthTSynCtrlIdx].IcvAuthTlvOffset);
      if(EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments > 0U)
      {
        EthTSyn_FillSegmentsIcv(EthTSynCtrlIdx, ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength, EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv, &(*BufPtr));
      }
      else
      {
        /* Copy the Icv to the fup frame */
        TS_MemCpy(&((*BufPtr)[EthTSyn_Ctrl[EthTSynCtrlIdx].IcvAuthTlvOffset]),
                &EthTSyn_IcvTxFrame[ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxOffset],
                ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength);
      }
      *FrameWasTransmitted = TRUE;
      /* Confirmation of transmission needed to be passed to FVM */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = BufIdx;
    }
  }
  else
  {
     /* still waiting for indication */
  }
  /* CHECK: PARSE */

  if((*FrameWasTransmitted == TRUE) && (E_OK == RetVal))
  {
    /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
    RetVal = EthTSyn_TransmitAndRetry(EthTSynCtrlIdx, BufIdx, PortIdx, FrameLength);
  }
#if(ETHTSYN_SWITCH_USED == STD_OFF)
  TS_PARAM_UNUSED(PayloadLength);
#endif
  return RetVal;
}
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillBufIcvGenFailed
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00250_GetTxFreshness_StopIcv, 1 */
  /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00250_GetTxFreshnessTruncData_StopIcv, 1 */
  uint16 FrameLength = EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv;
  uint16 tmpSubTlvLength = (FrameLength - ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR) + (ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH + ETHTSYN_FUP_EXT_TLV_LENGTH_0);
  FrameLength += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
  BufPtr[EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv + ETHTSYN_TIMEAUTH_TLV_B0_TYPE] = ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE;
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00239, 1 */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00237, 1 */
  BufPtr[EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] |= ETHTSYN_ICV_GENERATION_FAILED;
  BufPtr[EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] &= (~ETHTSYN_ICV_WITH_FV);
  BufPtr[EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] &= (~ETHTSYN_ICV_IN_MULTIPLE_SUBTLV);
  BufPtr[EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] = ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI;

  BufPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE + ETHTSYN_FUP_TLV_B2_LENGTH_1] = ETHTSYN_FUP_EXT_TLV_LENGTH_1;
  BufPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE + ETHTSYN_FUP_TLV_B3_LENGTH_0] = (uint8)(tmpSubTlvLength & 0xFFU);
  BufPtr[ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1] = (uint8)((FrameLength >>  8U) & 0xFFU);
  BufPtr[ETHTSYN_PTP_HEADER_B3_MSGLENGTH_0] = (uint8)((FrameLength       ) & 0xFFU);
}
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ReportToIdsM
(
  uint8 EthTSynCtrlIdx,
  uint16 IdsMSev
)
{
  if(IdsMSev == ETHTSYN_SEV_ICV_GENERATION_FAILED)
  {
#if(ETHTSYN_SEV_ICV_GENERATION_FAILED != ETHTSYN_INVALID_SEV_REF)
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_GENERATION_FAILED, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00262, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00256_SignatureGenerate_CallIdsM, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00256_MacGenerate_CallIdsM, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00256_GenerationTimeout_CallIdsM, 1 */
    IdsM_SetSecurityEventWithContextData
    (
      ETHTSYN_SEV_ICV_GENERATION_FAILED,
      &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
      ETHTSYN_CONTEXT_DATA_SIZE
    );
#endif /* ETHTSYN_SEV_ICV_GENERATION_FAILED != ETHTSYN_INVALID_SEV_REF */
  }
  else
  {
#if(ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE != ETHTSYN_INVALID_SEV_REF)
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_FRESHNESS_NOT_AVAILABLE, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00262, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00250_GetTxFreshnessTruncData_CallIdsM, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00250_GetTxFreshness_CallIdsM, 1 */
    IdsM_SetSecurityEventWithContextData
    (
      ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE,
      &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
      ETHTSYN_CONTEXT_DATA_SIZE
    );
#endif /* ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE != ETHTSYN_INVALID_SEV_REF */
  }
}
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */


STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillSegmentsIcv
(
  uint8 EthTSynCtrlIdx,
  uint8 LengthFV,
  uint16 FrameOffset,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00226, 1 */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00240, 1 */
  uint16 timeAuthOffset = FrameOffset;
  uint16 tmpIcvOffset = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxOffset;
  uint16 tmpIcvTotalLength = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength;
  uint8 tmpFv = 0U;
  uint8 Idx;
  if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId != ETHTSYN_FV_NOT_CONFIGURED)
  {
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00234, 1 */
    if((LengthFV % ETHTSYN_8_BITS) != 0U)
    {
      /* use length in bytes */
      tmpFv = (LengthFV / ETHTSYN_8_BITS) + 1U;
    }
    else
    {
      tmpFv = LengthFV / ETHTSYN_8_BITS;
    }
  }
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00227, 1 */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00229, 1 */
  for(Idx = 0U; Idx <= EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments; Idx++)
  {
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00228, 1 */
    if(Idx == 0U)
    {
      uint8 bytes2Copy = ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(tmpFv);
      /* For the first segment update as specified. */
      /* This seqment will contain also the FV. */
      (*BufPtr)[timeAuthOffset] = ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] = ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(tmpFv);
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00230, 1 */
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] |= ETHTSYN_ICV_IN_MULTIPLE_SUBTLV;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B3_SEQNR] = Idx;

      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00231_Seq0, 1 */
      if(tmpFv != 0U)
      {
        (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B4_FVL] = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength;
        timeAuthOffset += ((uint16)tmpFv + ETHTSYN_FUP_LEN_FVL);
      }
      timeAuthOffset += (uint16)ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
      /* Copy the Icv to the fup frame */
      TS_MemCpy(&((*BufPtr)[timeAuthOffset]), &EthTSyn_IcvTxFrame[tmpIcvOffset], bytes2Copy);
      tmpIcvOffset += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(tmpFv);
      timeAuthOffset += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(tmpFv);
      tmpIcvTotalLength -= ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(tmpFv);
    }
    else if(Idx == EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00231_SeqNot0, 1 */
      /* The last frame will contain no flags.*/
      (*BufPtr)[timeAuthOffset] = ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] = (uint8)tmpIcvTotalLength;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] = 0U;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B3_SEQNR] = Idx;
      timeAuthOffset += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
      /* Copy the Icv to the fup frame */
      TS_MemCpy(&((*BufPtr)[timeAuthOffset]), &EthTSyn_IcvTxFrame[tmpIcvOffset], tmpIcvTotalLength);
    }
    else
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00231_SeqNot0, 1 */
      (*BufPtr)[timeAuthOffset] = ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] = ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00230, 1 */
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] = ETHTSYN_ICV_IN_MULTIPLE_SUBTLV;
      (*BufPtr)[timeAuthOffset + ETHTSYN_TIMEAUTH_TLV_B3_SEQNR] = Idx;
      timeAuthOffset += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
      /* Copy the Icv to the fup frame */
      TS_MemCpy(&((*BufPtr)[timeAuthOffset]), &EthTSyn_IcvTxFrame[tmpIcvOffset], ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL);
      tmpIcvOffset += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
      timeAuthOffset += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
      tmpIcvTotalLength -= ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
    }
  }
}
#endif /* ETHTSYN_TOTAL_ICVTXLENGTH > 0U */

#if (ETHTSYN_MAX_SLAVE != 0U)

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CheckTimeAuthSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  /* extract */
  Std_ReturnType RetVal = E_NOT_OK;
  boolean VerifFailed = FALSE;

  /* Clear all states */
  EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction = 0U;
  /* Save the fup message + the header of the timeauth */
  EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv = Offset + ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;

  if(EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv <= Length)
  {
    /* Save the current fup frame, without time auth TLV */
    TS_MemCpy(&EthTSyn_Slave[EthTSynCtrlIdx].BufferSubTlv[0U], &DataPtr[0U], EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv);

    RetVal = EthTSyn_ProcessICVSegments(EthTSynCtrlIdx, &DataPtr[0U], Length, Offset, &VerifFailed);
  }

  if(VerifFailed == TRUE)
  {
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00251, 1 */
    TS_AtomicSetBit_8
    (
      &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
      ETHTSYN_AUTH_VERIFICATION_FAILED
    );
    RetVal = E_NOT_OK;
    /* Reset saved values. */
    EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
  }

  if(RetVal == E_OK)
  {
    /* Call the Csm verification apis */
    RetVal = EthTSyn_VerifyIcv(EthTSynCtrlIdx);
  }
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_ProcessICVSegments
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset,
  P2VAR(boolean, AUTOMATIC, ETHTSYN_APPL_DATA) VerifFailed
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 OffsetTimeAuth = Offset;
  uint8 FvOffset = 0U;
  uint8 SegmentId = 0U;
  uint8 NrOfFvBytes = 0U;
  boolean ExitLoop = FALSE;

  /* Save the received ICV */
  for(SegmentId = 0U; ((SegmentId < 4U) && (ExitLoop == FALSE) && (*VerifFailed == FALSE) && (OffsetTimeAuth < Length)); SegmentId++)
  {
    if(DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B0_TYPE] == ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE)
    {
      if(DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] > ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI)
      {
        if(DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B3_SEQNR] == SegmentId)
        {
          uint8 SegmentLength = DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH];
          if(SegmentId == 0U)
          {
            /* Check in the first flags, and take proper actions based on this */
            /* !LINKSTO EthTSyn.R22-11.PRS_TS_00249, 1 */
            if(
                ((DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] & ETHTSYN_ICV_WITH_FV) == TRUE) &&
                 (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId != ETHTSYN_FV_NOT_CONFIGURED)
              )
            {
              EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength = DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B4_FVL];

              if((EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength > 0U) &&
                 (EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength <= ETHTSYN_SYNCFUP_MAX_SIZE_FV_BITS)
                )
              {
                /* Extract FV */
                RetVal = EthTSyn_ExtractFreshness(EthTSynCtrlIdx, &DataPtr[0U], Length, Offset, OffsetTimeAuth, &NrOfFvBytes, VerifFailed);
                /* Prepare offset to point to the first byte of ICV */
                FvOffset = NrOfFvBytes + ETHTSYN_FUP_LEN_FVL;
              } /* EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength > 0U */
              else
              {
                /* !LINKSTO EthTSyn.R22-11.PRS_TS_00250, 1 */
                TS_AtomicSetBit_8
                (
                  &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
                  ETHTSYN_AUTH_VERIFICATION_FAILED
                );
#if(ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON)
                ETHTSYN_DET_RUNTIME_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_FRESHNESSFAILURE);
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#if(ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE != ETHTSYN_INVALID_SEV_REF)
                /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallIdsM, 1 */
                IdsM_SetSecurityEventWithContextData
                (
                  ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE,
                  &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
                  ETHTSYN_CONTEXT_DATA_SIZE
                );
#endif /* ETHTSYN_SEV_ICV_GENERATION_FAILED != ETHTSYN_INVALID_SEV_REF */
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
                /* No need to do further processing, verification failed */
                *VerifFailed = TRUE;
              } /* EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength = 0U */
            } /* FV configured and received in the message */
            else
            {
              /* Sub-TLV does not contain FV */
              RetVal = E_OK;
            }
            /* Save the Icv value */
            if(*VerifFailed != TRUE)
            {
              if((DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] & ETHTSYN_ICV_IN_MULTIPLE_SUBTLV) != FALSE)
              {
                EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength = ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(NrOfFvBytes);
                /* Copy the Icv to the fup frame */
                OffsetTimeAuth += ((uint16)FvOffset + ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH);

                if(
                    ((uint16)(sizeof(EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv)) >= (EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength)) &&
                    (Length >= (EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength + OffsetTimeAuth))
                  )
                  {
                    TS_MemCpy(&EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[0U], &DataPtr[OffsetTimeAuth], EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength);
                  }
                  else
                  {
                    *VerifFailed = TRUE;
                  }
                /* Offset to the next segment */
                OffsetTimeAuth += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(NrOfFvBytes);
              }
              else
              {
                /* No need to do further processing, only one segment was received */
                EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength = DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH];
                EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength -= ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI;
                if(EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength > ((uint16)NrOfFvBytes + ETHTSYN_FUP_LEN_FVL))
                {
                  if(NrOfFvBytes > 0U)
                  {
                    /* substract the fv from the received length */
                    EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength -=((uint16)NrOfFvBytes + ETHTSYN_FUP_LEN_FVL);
                  }
                  OffsetTimeAuth += ((uint16)FvOffset + ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH);
                  /* Copy the Icv to the fup frame */
                  if((OffsetTimeAuth + EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength <= Length) &&
                     ((uint16)(sizeof(EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv)) >=
                       (EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength)
                     )
                    )
                  {
                    TS_MemCpy(&EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[0U], &DataPtr[OffsetTimeAuth], EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength);
                    ExitLoop = TRUE;
                  }
                  else
                  {
                    *VerifFailed = TRUE;
                  }
                  
                }
                else
                {
                  *VerifFailed = TRUE;
                } /* EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength > ((uint16)NrOfFvBytes + ETHTSYN_FUP_LEN_FVL) */
              }
            }
          } /* SegmentId 0 */
          else
          {
            /* Save the Icv value */
            if((DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B2_ICV_FLAGS] & ETHTSYN_ICV_IN_MULTIPLE_SUBTLV) != FALSE)
            {
              OffsetTimeAuth += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
              /* Copy the Icv to the fup frame */
              if((OffsetTimeAuth + ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL <= Length) &&
                  ((uint16)(sizeof(EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv)) >=
                    (EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength + ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL)
                  )
                )
              {
                TS_MemCpy(&EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength], &DataPtr[OffsetTimeAuth], ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL);
                EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
                OffsetTimeAuth += ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
              }
              else
              {
                *VerifFailed = TRUE;
              }
            }
            else
            {
              OffsetTimeAuth += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
              if((OffsetTimeAuth + (uint8)(SegmentLength - ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI) <= Length) &&
                  ((uint16)(sizeof(EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv)) >=
                    (EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength + (uint8)(SegmentLength - ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI))
                  )
                )
              {
                /* Copy the Icv to the fup frame */
                TS_MemCpy(&EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength], &DataPtr[OffsetTimeAuth], (uint8)(SegmentLength - ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI));
                /* No need to do further processing, only one segment was received */
                EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength += ((uint16)SegmentLength - ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH_PCI);
                ExitLoop = TRUE;
              }
              else
              {
                *VerifFailed = TRUE;
              }
            }
          }
        }
        else
        {
          *VerifFailed = TRUE;
        } /* DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B3_SEQNR] == SegmentId */
      }
      else
      {
        *VerifFailed = TRUE;
      } /* DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B1_LENGTH] > ETHTSYN_LEN_SUBTLV_TIMEAUTH_PCI */
    }
    else
    {
      *VerifFailed = TRUE;
    } /* DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B0_TYPE] == ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE */
  } /* For */
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_ExtractFreshness
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset,
  uint16 OffsetTimeAuth,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) NrOfFvBytes,
  P2VAR(boolean, AUTOMATIC, ETHTSYN_APPL_DATA) VerifFailed
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00248, 1 */
  uint8 receivedFvLength = DataPtr[OffsetTimeAuth + ETHTSYN_TIMEAUTH_TLV_B4_FVL];

  if((receivedFvLength % ETHTSYN_8_BITS) != 0U)
  {
    /* use length in bytes */
    *NrOfFvBytes = (receivedFvLength / ETHTSYN_8_BITS) + 1U;
  }
  else
  {
    *NrOfFvBytes = receivedFvLength / ETHTSYN_8_BITS;
  }

  if(Offset + ETHTSYN_TIMEAUTH_TLV_B5_FV + *NrOfFvBytes <= Length)
  {
    /* save the received FV to be passed to StbM */
    TS_MemCpy(
     &EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueReceived[0U],
     &DataPtr[Offset + ETHTSYN_TIMEAUTH_TLV_B5_FV],
     *NrOfFvBytes
    );
#if(ETHTSYN_SLAVE_FV_USED == STD_ON)
    /* Get Rx FV */
    RetVal = EthTSyn_GetRxFreshnessValue(EthTSynCtrlIdx);
#else
    RetVal = E_OK;
#endif
  }
  else
  {
    *VerifFailed = TRUE;
  }
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyIcv
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvRxLength == EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength)
  {
    /* set state in order to use the */
    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationBase == TRUE)
    {
#if(ETHTSYN_ICV_BASE_MAC == STD_ON)
      uint32 IcvLengthBit = (uint32)((uint32)EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength * 8U);
      /* Symmetric cryptography selection for the ICV generation. */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00237, 1 */
      /* EthTSynIcvGenerationBase for the Time Domain is configured to ICV_MAC */

      RetVal = Csm_MacVerify
               (
                ETHTSYN_ROOTCFG(EthTSynCtrlIdx).CsmJobId, /* jobId */
                CRYPTO_OPERATIONMODE_SINGLECALL,
                &EthTSyn_Slave[EthTSynCtrlIdx].BufferSubTlv[0U], /* DataPtr */
                EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv, /* length of the data */
                &EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[0U], /* Fv */
                IcvLengthBit, /* received Icv length in bits */
                &EthTSyn_Slave[EthTSynCtrlIdx].VerificationResult
               );
#endif
    }
    else
    {
      /* Asymmetric cryptography selection for the ICV generation. */
      /* EthTSynIcvGenerationBase for the Time Domain is configured to ICV_SIGNATURE */
#if(ETHTSYN_ICV_BASE_SIGNATURE == STD_ON)
      RetVal = Csm_SignatureVerify
               (
                ETHTSYN_ROOTCFG(EthTSynCtrlIdx).CsmJobId, /* jobId */
                CRYPTO_OPERATIONMODE_SINGLECALL,
                &EthTSyn_Slave[EthTSynCtrlIdx].BufferSubTlv[0U], /* DataPtr */
                EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv, /* length of the data */
                &EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[0U], /* Fv */
                EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength, /* received Icv length */
                &EthTSyn_Slave[EthTSynCtrlIdx].VerificationResult
               );
#endif
    }
  }
  if(RetVal == E_OK)
  {
    /* RetVal returned E_OK */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00239, 1 */
    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationTimeout == 0U)
    {
      if(EthTSyn_Slave[EthTSynCtrlIdx].VerificationResult == CRYPTO_E_VER_OK)
      {
        /* Fup message was accepted */
        RetVal = E_OK;
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
          ETHTSYN_AUTH_VERIFICATION_PASSED
        );
      }
      else
      {
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00252, 1 */
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
          ETHTSYN_AUTH_VERIFICATION_FAILED
        );
        /* drop the frame */
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00240_MacVerify, 1 */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00240_SignatureVerify, 1 */
      TS_AtomicSetBit_8
      (
        &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
        ETHTSYN_AUTH_VERIFICATION_WAIT_INDICATION
      );
      /* Load Verification Timeout */
      EthTSyn_Slave[EthTSynCtrlIdx].IcvVerificationTimeout = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationTimeout;
    }
  }
  else if(RetVal == CRYPTO_E_BUSY)
  {
    /* Check on the next mainfunction if authverificationattempts is configured */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00241_MacVerify, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00241_SignatureVerify, 1 */
    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationAttempts != 0U)
    {
      /* If retry is in progress */
      if(EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts != ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationAttempts)
      {
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
          ETHTSYN_AUTH_VERIFICATION_ICV_RETRY
        );
      }
      else
      {
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_VerificationAttempts_StopIcv, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_VerificationTimeoutExp_StopIcv, 1 */
        /* If retry pending, clear the corresponding bit. */
        TS_AtomicClearBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
          ETHTSYN_AUTH_VERIFICATION_ICV_RETRY
        );

        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallIdsM, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_VerificationAttempts_CallIdsM, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_VerificationTimeoutExp_CallIdsM, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_VERIFICATION_FAILED, 1 */
        EthTSyn_VerificationFailed(EthTSynCtrlIdx);
      }
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.Csm_BUSY_0_Attempts, 1 */
      EthTSyn_VerificationFailed(EthTSynCtrlIdx);
    }
  }
  else
  {
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_NOK_StopIcv, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_KEY_FAILURE_StopIcv, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallIdsM, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_NOK_CallIdsM, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_KEY_FAILURE_CallIdsM, 1 */
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_VERIFICATION_FAILED, 1 */
    EthTSyn_VerificationFailed(EthTSynCtrlIdx);
  }
  return RetVal;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_VerificationFailed
(
  uint8 EthTSynCtrlIdx
)
{
  TS_AtomicSetBit_8
  (
    &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
    ETHTSYN_AUTH_VERIFICATION_FAILED
  );
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#if(ETHTSYN_SEV_ICV_VERIFICATION_FAILED != ETHTSYN_INVALID_SEV_REF)
  IdsM_SetSecurityEventWithContextData
  (
    ETHTSYN_SEV_ICV_VERIFICATION_FAILED,
    &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
    ETHTSYN_CONTEXT_DATA_SIZE
  );
#endif /* ETHTSYN_SEV_ICV_VERIFICATION_FAILED != ETHTSYN_INVALID_SEV_REF */
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
  /* Reset saved values. */
  EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
}

#if(ETHTSYN_SLAVE_FV_USED == STD_ON)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetRxFreshnessValue
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueLength = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueLength;
  /* call StbM in order to retrieve the freshness value */
  /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00233, 1 */
  RetVal = StbM_GetRxFreshness
          (
            ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId,
            &EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueReceived[0U],
            EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength,
            EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts,
            &EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueLength,
            &EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueStbM[0U]
          );
  if(RetVal != E_OK)
  {
    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationAttempts != 0U)
    {
      if((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_FV_RETRY_MASK) != FALSE)
      {
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00235_RetryGetRxFreshness, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00235_IncrementIcvVerificationAttempt, 1 */
        /* If retry is in progress */
        if(EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts != ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationAttempts)
        {
          TS_AtomicSetBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
            ETHTSYN_AUTH_VERIFICATION_FV_RETRY
          );
        }
        else
        {
          /* If retry pending, clear the corresponding bit. */
          TS_AtomicClearBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
            ETHTSYN_AUTH_VERIFICATION_FV_RETRY
          );
          /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_StopIcv, 1 */
          TS_AtomicSetBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
            ETHTSYN_AUTH_VERIFICATION_FAILED
          );
#if(ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON)
          /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallDet, 1 */
          ETHTSYN_DET_RUNTIME_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_FRESHNESSFAILURE);
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#if(ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE != ETHTSYN_INVALID_SEV_REF)
          /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallIdsM, 1 */
          IdsM_SetSecurityEventWithContextData
          (
            ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE,
            &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
            ETHTSYN_CONTEXT_DATA_SIZE
          );
#endif /* ETHTSYN_SEV_ICV_GENERATION_FAILED != ETHTSYN_INVALID_SEV_REF */
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
          /* Reset saved values. */
          EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
        }
      }
      else
      {
        /* Retry on the next mainfunction */
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
          ETHTSYN_AUTH_VERIFICATION_FV_RETRY
        );
      }
    }
    else
    {
      TS_AtomicSetBit_8
      (
        &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
        ETHTSYN_AUTH_VERIFICATION_FAILED
      );
#if(ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON)
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00146, 2 */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallDet, 1 */
      ETHTSYN_DET_RUNTIME_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_FRESHNESSFAILURE);
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#if(ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE != ETHTSYN_INVALID_SEV_REF)
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallIdsM, 1 */
      IdsM_SetSecurityEventWithContextData
      (
        ETHTSYN_SEV_FRESHNESS_NOT_AVAILABLE,
        &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
        ETHTSYN_CONTEXT_DATA_SIZE
      );
#endif /* ETHTSYN_SEV_ICV_GENERATION_FAILED != ETHTSYN_INVALID_SEV_REF */
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
      /* Reset saved values. */
      EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
    } /* EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts != ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationAttempts */
  } /* RetVal != E_OK */
  else
  {
    /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00234, 1 */
    /* copy the FV in order to be used in verification of ICV */
    uint8 FvLength = 0U;
    if((EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueLength % ETHTSYN_8_BITS) != 0U)
    {
      /* use length in bytes */
      FvLength = (uint8)((EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueLength / ETHTSYN_8_BITS) + 1U);
    }
    else
    {
      FvLength = (uint8)(EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueLength / ETHTSYN_8_BITS);
    }

    EthTSyn_Slave[EthTSynCtrlIdx].BufferSubTlv[EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv] = EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength;
    EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv++;
      /* Save the current fup frame, without time atuh TLV */
    TS_MemCpy(&EthTSyn_Slave[EthTSynCtrlIdx].BufferSubTlv[EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv], &EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueStbM[0U], FvLength);
    EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv += FvLength;
    /* clear FV retry bit */
    TS_AtomicClearBit_8
    (
      &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
      ETHTSYN_AUTH_VERIFICATION_FV_RETRY
    );
  }
  return RetVal;
}
#endif /* ETHTSYN_SLAVE_FV_USED == STD_ON */
#endif /* ETHTSYN_MAX_SLAVE != 0U */
#endif /* ETHTSYN_ICV_USED == STD_ON */

#if(ETHTSYN_TX_CRC_USED == STD_ON)

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVTime_Secured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset
)
{
  uint8 Crc_0;
  uint8 Crc_1;

  /* AUTOSAR TLV Sub-TLV: Time Secured */
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B0_TYPE]  = ETHTSYN_FUP_SUBTLV_TIME_TYPE;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B1_LENGTH] = ETHTSYN_FUP_SUBTLV_TIME_LENGTH;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags;

  /* !LINKSTO EthTSyn.PRS_TS_00182, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00184, 1 */
  EthTSyn_CalculateCrc(EthTSynCtrlIdx, &BufPtr[0U], &Crc_0, &Crc_1);

  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B3_CRC_TIME_0] = Crc_0;

  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1] = Crc_1;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLVStatus_Secured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint8 SubTlvOffset
)
{
  uint8 Crc_Status;
  uint8 SeqNr = (BufPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]) % 16U;

  /* AUTOSAR TLV Sub-TLV: Status Secured */
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B0_TYPE] =
    ETHTSYN_FUP_SUBTLV_STATUS_SECURED_TYPE;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B1_LENGTH] = ETHTSYN_FUP_SUBTLV_STATUS_LENGTH;
  EthTSyn_FUpSubTLVStatus(&BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS]);

  Crc_Status = Crc_CalculateCRC8H2F
      (&BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS], 1U, 0U, TRUE);

  Crc_Status = Crc_CalculateCRC8H2F
      (&EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr], 1U, Crc_Status, FALSE);

  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B3_CRC_STATUS] = Crc_Status;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillFUpSubTLV_UserData_Secured
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset
)
{
  uint8 Crc_UserData = 0U;

  /* AUTOSAR TLV Sub-TLV: UserData Secured */
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B0_TYPE] =
    ETHTSYN_FUP_SUBTLV_USERDATA_SECURED_TYPE;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B1_LENGTH] =
    ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength ;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1;
  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2] =
      EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2;

  (void)EthTSyn_CalcComp_UserDataCrc(EthTSynCtrlIdx, &BufPtr[0U], SubTlvOffset, &Crc_UserData);

  BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B6_CRC_USERDATA] = Crc_UserData;
}

#endif /*(ETHTSYN_TX_CRC_USED == STD_ON) */

STATIC FUNC(uint16, ETHTSYN_CODE) EthTSyn_CheckForAUTOSARSubTLV
(
  uint8 EthTSynCtrlIdx
)
{
  uint16 SubTlvSize = 0U;
  /* Increment the frame size with 10 bytes */
  SubTlvSize += ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH;

  /* If Time SubTLV is enabled, increment the frame size with 5 bytes */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpTimeSubTLV == TRUE)
  {
   SubTlvSize += ETHTSYN_FUP_SUBTLV_TIME_SIZE;
  }
  /* If Status SubTLV is enabled, increment the frame size with 4 bytes */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpStatusSubTLV == TRUE)
  {
   SubTlvSize += ETHTSYN_FUP_SUBTLV_STATUS_SIZE;
  }
  /* If UserData SubTLV is enabled, increment the frame size with 7 bytes */
  if(
     (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpUserDataSubTLV == TRUE) &&
     (EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength  != 0U)
  )
  {
   SubTlvSize += ETHTSYN_FUP_SUBTLV_USERDATA_SIZE;
  }

  /* If OFS SubTLV is enabled, increment the frame size with 19 bytes */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpOFSSubTLV == TRUE)
  {
    /* Check how many time Ofs are configured and multiply the needed size. */
    SubTlvSize += ((uint16)EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TotalOfsTimebase) * ETHTSYN_FUP_SUBTLV_OFS_SIZE;
  }
#if(ETHTSYN_ICV_USED == STD_ON)
  /* If Icv SubTLV is enabled, update the buffer */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpICVSubTLV == TRUE)
  {
    uint8 byteLengthFVL = 0U;
    uint16 tmpOffset = SubTlvSize;
    SubTlvSize += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH + ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength;
    EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments = 0U;
    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueId != ETHTSYN_FV_NOT_CONFIGURED)
    {
      /* The FVL byte is added */
      SubTlvSize++;
      /* Freshness is used in order to generate the ICV */
      if((ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength % ETHTSYN_8_BITS) != 0U)
      {
        /* use length in bytes */
        byteLengthFVL = (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength / ETHTSYN_8_BITS) + 1U;
      }
      else
      {
        byteLengthFVL = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).FreshnessValueTruncLength / ETHTSYN_8_BITS;
      }
      SubTlvSize += byteLengthFVL;
    }

    if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength > ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(byteLengthFVL))
    {
      uint16 tmpICVlength = ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvTxLength - ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG(byteLengthFVL);
      while(tmpICVlength > ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL)
      {
        tmpICVlength -= ETHTSYN_TIMEAUTH_MAX_LENGTH_FIRST_SEG_WITHOUT_FVL;
        /* add the header of the segment */
        SubTlvSize += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
        EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments++;
      }
      /* add the header of the segment */
      SubTlvSize += ETHTSYN_FUP_LEN_SUBTLV_TIMEAUTH;
      EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments++;
    }
    /* save the calculated TimeAuth tlv length.*/
    EthTSyn_Ctrl[EthTSynCtrlIdx].TimeAuthTotalLength = SubTlvSize - tmpOffset;
  }
#endif /* ETHTSYN_ICV_USED == STD_ON */
  if(SubTlvSize == ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH)
  {
   SubTlvSize = 0U;
  }
  return SubTlvSize;
}
#endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

#if(ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillAnnouncePayload
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  uint8 Idx;
  uint8 SrcMacAddr[ETHTSYN_MAC_ADD_SIZE];

  for(Idx = 0U; Idx <ETHTSYN_RESERVED_10BYTES; Idx++)
  {
    BufPtr[Idx] = 0U;
  }

  BufPtr[ETHTSYN_ANNOUNCE_PL_B10_CUR_UTC_OFFSET_1] = 0U;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B11_CUR_UTC_OFFSET_0] = 0U;

  BufPtr[ETHTSYN_ANNOUNCE_PL_B12_RESERVED] = 0U;

  BufPtr[ETHTSYN_ANNOUNCE_PL_B13_GM_PRIO1] = ETHTSYN_GM_PRIORITY1;

  BufPtr[ETHTSYN_ANNOUNCE_PL_B14_GM_CLK_QUAL_3] = ETHTSYN_GM_CLOCK_CLASS;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B15_GM_CLK_QUAL_2] = ETHTSYN_GM_CLOCK_ACCURANCY;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B16_GM_CLK_QUAL_1] = ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_1;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B17_GM_CLK_QUAL_0] = ETHTSYN_GM_OFFSET_SCALEDLOG_VARIANCE_0;

  BufPtr[ETHTSYN_ANNOUNCE_PL_B18_GM_PRIO2] = ETHTSYN_GM_PRIORITY2;

  /* Get source MAC address */
  EthIf_GetPhysAddr(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, &SrcMacAddr[0]);

  BufPtr[ETHTSYN_ANNOUNCE_PL_B19_GM_IDENTITY_0] = SrcMacAddr[0U]; /* Source MAC upper 3 bytes */
  BufPtr[ETHTSYN_ANNOUNCE_PL_B20_GM_IDENTITY_1] = SrcMacAddr[1U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B21_GM_IDENTITY_2] = SrcMacAddr[2U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B22_GM_IDENTITY_3] = ETHTSYN_PTP_HEADER_EUI48_IDX3_SRCPORTIDENTITY;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B23_GM_IDENTITY_4] = ETHTSYN_PTP_HEADER_EUI48_IDX4_SRCPORTIDENTITY;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B24_GM_IDENTITY_5] = SrcMacAddr[3U]; /* Source MAC lower 3 bytes */
  BufPtr[ETHTSYN_ANNOUNCE_PL_B25_GM_IDENTITY_6] = SrcMacAddr[4U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B26_GM_IDENTITY_7] = SrcMacAddr[5U];

  BufPtr[ETHTSYN_ANNOUNCE_PL_B27_STEP_REM_1] = 0U;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B28_STEP_REM_0] = 0U;

  BufPtr[ETHTSYN_ANNOUNCE_PL_B29_TIME_SOURCE] = 0xA0U; /* internal oscillator */

  BufPtr[ETHTSYN_ANNOUNCE_PL_B30_PATH_TRACE_TLV_TYPE_1] = ETHTSYN_ANNOUNCE_TLV_TYPE_1;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B31_PATH_TRACE_TLV_TYPE_0] = ETHTSYN_ANNOUNCE_TLV_TYPE_0;

  BufPtr[ETHTSYN_ANNOUNCE_PL_B32_PATH_TRACE_TLV_LEN_0] = ETHTSYN_ANNOUNCE_TLV_LENGTH_1;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B33_PATH_TRACE_TLV_LEN_1] = ETHTSYN_ANNOUNCE_TLV_LENGTH_0;

  /* Source MAC upper 3 bytes */
  BufPtr[ETHTSYN_ANNOUNCE_PL_B34_PATH_TRACE_TLV_SEQ_0] = SrcMacAddr[0U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B35_PATH_TRACE_TLV_SEQ_1] = SrcMacAddr[1U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B36_PATH_TRACE_TLV_SEQ_2] = SrcMacAddr[2U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B37_PATH_TRACE_TLV_SEQ_3]
    = ETHTSYN_PTP_HEADER_EUI48_IDX3_SRCPORTIDENTITY;
  BufPtr[ETHTSYN_ANNOUNCE_PL_B38_PATH_TRACE_TLV_SEQ_4]
    = ETHTSYN_PTP_HEADER_EUI48_IDX4_SRCPORTIDENTITY;
  /* Source MAC lower 3 bytes */
  BufPtr[ETHTSYN_ANNOUNCE_PL_B39_PATH_TRACE_TLV_SEQ_5] = SrcMacAddr[3U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B40_PATH_TRACE_TLV_SEQ_6] = SrcMacAddr[4U];
  BufPtr[ETHTSYN_ANNOUNCE_PL_B41_PATH_TRACE_TLV_SEQ_7] = SrcMacAddr[5U];

}
#endif /* ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON) */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessReceivedSyncFrame
(
  uint8 EthTSynCtrlIdx,
  uint16 LenByte,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  /* !LINKSTO EthTSyn.EB.Sync_IncorrectLength, 2 */
  if(LenByte >= ETHTSYN_SYNC_FRAME_SIZE)
  {
#if(ETHTSYN_MAX_SLAVE != 0U)
    if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
    {
#if((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON))
      Std_ReturnType TmpRet = E_NOT_OK;
      if(EthTSyn_Slave[EthTSynCtrlIdx].SaveSrcPortId == TRUE)
      {
        /* When the first sync frame is received, save the sourceportid, in order to be able to detect
           parallel masters. */
        TS_MemCpy(
           &EthTSyn_Slave[EthTSynCtrlIdx].Sync_Rx_SrcPortIdentity[0U],
           &DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
           ETHTSYN_SOURCEPORTIDENTITY_SIZE
         );
         EthTSyn_Slave[EthTSynCtrlIdx].SaveSrcPortId = FALSE;
      }

      /* Check source port identity */
      TmpRet = TS_MemCmp(
                &EthTSyn_Slave[EthTSynCtrlIdx].Sync_Rx_SrcPortIdentity[0U],
                &DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
                ETHTSYN_SOURCEPORTIDENTITY_SIZE
              );
      if(TmpRet == E_OK)
      {
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        /* !LINKSTO EthTSyn.EB.Master.RxIndication, 1 */
        /* !LINKSTO EthTSyn.PRS_TS_00120, 1 */
        EthTSyn_ProcessRxSyncFrame(EthTSynCtrlIdx, DataPtr);
#if((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON))
      }
      else
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00146, 2 */
        ETHTSYN_DET_RUNTIME_REPORT_ERROR(ETHTSYN_SID_RXINDICATION, ETHTSYN_E_TSCONFLICT);
      }
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */
    }
    else
#else /* ETHTSYN_MAX_SLAVE == 0U */
    TS_PARAM_UNUSED(EthTSynCtrlIdx);
    TS_PARAM_UNUSED(DataPtr);
#endif /* ETHTSYN_MAX_SLAVE != 0U */
    {
#if(ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DEM)
      /* !LINKSTO EthTSyn.EB.Diagnostic_UnexpectedSync_DEM, 1 */
      Dem_ReportErrorStatus
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdUnexpectedSync,
        DEM_EVENT_STATUS_FAILED
      );
#else /* ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC != TS_PROD_ERR_REP_TO_DEM */
      TS_PARAM_UNUSED(EthTSynCtrlIdx);
#endif/* ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DEM */

#if(ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON)

#if(ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00145, 2 */
      ETHTSYN_DET_RUNTIME_REPORT_ERROR
      (
        ETHTSYN_SID_RXINDICATION,
        ETHTSYN_E_TMCONFLICT
      );
#endif
#endif /* ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON */

#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
#if(ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DET)
      /* !LINKSTO EthTSyn.EB.Diagnostic_UnexpectedSync_DET, 1 */
      ETHTSYN_DET_REPORT_ERROR
      (
        ETHTSYN_SID_RXINDICATION,
        ETHTSYN_E_TMCONFLICT_CONFIGURED
      );
#endif

#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
    }
  }
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitFrame
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
  uint16 PayloadLength,
  boolean ActivateTimeStamp
)
{
  uint8 DestMacAddr[ETHTSYN_MAC_ADD_SIZE];
  Std_ReturnType RetVal;


  /* !LINKSTO EthTSyn.ECUC_EthTSyn_00058_Conf, 1 */
  TS_MemCpy(DestMacAddr, EthTSyn_DestMacAddr, ETHTSYN_MAC_ADD_SIZE);

#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  if(ActivateTimeStamp == TRUE)
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00200, 1 */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
    EthIf_EnableEgressTimeStamp
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx,
        BufIdx
      );
  }
#else
  TS_PARAM_UNUSED(ActivateTimeStamp);
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00200, 1 */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
  /* !LINKSTO EthTSyn.EB.Master.FrameType, 1 */
  RetVal = EthIf_Transmit
  (
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, /* EthIf CtrlIdx */
    BufIdx, /* BufIdx */
    ETHTSYN_PTP_FRAMETYPE, /* FrameType */
    TRUE, /* TxConfirmation */
    PayloadLength, /* LenByte */
    &DestMacAddr[0U] /* PhysAddrPtr */
  );

  return RetVal;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TimeStampToArray
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  /* !LINKSTO EthTSyn.PRS_TS_00181, 1 */
  BufPtr[0U] = (uint8)((uint16)(TimeStampPtr->secondsHi & ETHTSYN_16BIT_MASK_MSB) >> 8U);
  BufPtr[1U] = (uint8)(TimeStampPtr->secondsHi & ETHTSYN_16BIT_MASK_LSB);
  BufPtr[2U] = (uint8)((uint32)(TimeStampPtr->seconds & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[3U] = (uint8)((uint32)(TimeStampPtr->seconds & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[4U] = (uint8)((uint32)(TimeStampPtr->seconds & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[5U] = (uint8)(TimeStampPtr->seconds & ETHTSYN_32BIT_MASK0_LSB);
  BufPtr[6U] = (uint8)((uint32)(TimeStampPtr->nanoseconds & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[7U] = (uint8)((uint32)(TimeStampPtr->nanoseconds & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[8U] = (uint8)((uint32)(TimeStampPtr->nanoseconds & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[9U] = (uint8)(TimeStampPtr->nanoseconds & ETHTSYN_32BIT_MASK0_LSB);

}

#if (ETHTSYN_MAX_SLAVE != 0U)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleTxConfPDelayReq
(
  uint8 EthTSynCtrlIdx
)
{
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampType TmpTimeStamp;

  TmpTimeStamp.nanoseconds = 0U;
  TmpTimeStamp.seconds = 0U;
  TmpTimeStamp.secondsHi = 0U;
#else
  StbM_VirtualLocalTimeType TmpTimeStamp;

  TmpTimeStamp.nanosecondsLo = 0U;
  TmpTimeStamp.nanosecondsHi = 0U;
#endif
  if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
  {
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
    Std_ReturnType TmpRet = E_NOT_OK;
    /* Store t1 (See 802.1AS-2011 Ch 11.1.2). */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00013, 1 */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00123, 1 */
    TmpRet = EthTSyn_GetEgressTimeStamp
    (
      EthTSynCtrlIdx,
      (Eth_BufIdxType)EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx, /* BufIdx */
      &TmpTimeStamp /* TimeStampPtr */
    );

    /* !LINKSTO EthTSyn.EB.Slave.StbMSync.GetCurrentTime.NotOk, 1 */
    if(E_OK == TmpRet)
    {
      Eth_TimeStampType ConvertedValue = {0U, 0U, 0U};
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      ConvertedValue = TmpTimeStamp;
#else /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
      EthTSyn_Int01_ConvertVirtualTimeToEthTime(&TmpTimeStamp,
                                      &ConvertedValue);
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
      {
        SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
        /* If E2E mechanism is used for calculation of the delay, the egress time of the delay_req
           is saved as T3. */
        /* !LINKSTO EthTSyn.EB.PTPE2EDelayReqpSaveT3, 1 */
        EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3 = ConvertedValue;
        SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
      }
      else
      {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
        /* If gPTP mechanism is used for calculation of the delay, the egress time of the Pdelay_req
           is saved as T1. */
        EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1 = ConvertedValue;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
        /* TxConfirmation was received */
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
          ETHTSYN_BITPOS_PDELAYREQ_EGRESSCONF
        );
    }
    else
    {
      /* Something is wrong, abort the pdelay calculation */
      /* !LINKSTO EthTSyn.EB.Slave.NoConfirmationForPdelayReq, 1 */
      EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
    }
    /* The Pdelay_Req was transmitted, wait for the egress timestamp */
#else /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
    TS_PARAM_UNUSED(TmpTimeStamp);
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF */
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx = ETHTSYN_INV_BUFIDX;
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ArrayToTimeStamp
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{

  TimeStampPtr->secondsHi = (uint16)((uint16)BufPtr[0U] << 8U)
                            + BufPtr[1U];
  TimeStampPtr->seconds = ((uint32)BufPtr[2U] << 24U)
                          + (uint32)((uint32)BufPtr[3U] << 16U)
                          + (uint32)((uint32)BufPtr[4U] << 8U)
                          + BufPtr[5U];
  TimeStampPtr->nanoseconds = ((uint32)BufPtr[6U] << 24U)
                              + (uint32)((uint32)BufPtr[7U] << 16U)
                              + (uint32)((uint32)BufPtr[8U] << 8U)
                              + BufPtr[9U];

}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxSyncFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  Std_ReturnType TmpRet = E_NOT_OK;
  Eth_TimeStampType Sync_IngressTimeStamp;
  uint16 FrameLen = ETHTSYN_GET16(DataPtr, 2U);

  Sync_IngressTimeStamp.nanoseconds = 0U;
  Sync_IngressTimeStamp.seconds = 0U;
  Sync_IngressTimeStamp.secondsHi = 0U;


  /* !LINKSTO EthTSyn.PRS_TS_00199_CheckSC, 1 */
  /* !LINKSTO EthTSyn.EB.SyncFrame_IncorrectLenBytes, 1 */
  /* Drop frame if SequenceCounter is not ok, or if LengthByte do not contain the sync frame size(44) */
  if((E_OK == EthTSyn_CheckSC(EthTSynCtrlIdx, DataPtr)) && (FrameLen == ETHTSYN_SYNC_FRAME_SIZE))
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00128, 1 */
    TmpRet = EthTSyn_GetIngressTimeStamp(EthTSynCtrlIdx, DataPtr, &Sync_IngressTimeStamp);
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    if((EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE) && (TmpRet == E_OK))
    {
      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
      /* !LINKSTO EthTSyn.EB.PTPE2EcorrectedSyncCorrectionField, 1 */
      TmpRet = EthTSyn_SavePTPCorrField
      (
        EthTSynCtrlIdx,
        &DataPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0],
        &EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection
      );
      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
      /* Update the value of the corrected sync correction. */
      /* Delay asymmetry is 0 in the current implementation. */
      EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.diff.nanoseconds += ETHTSYN_DELAY_ASYMMETRY;
    }
#endif/* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
  }
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  if((EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived == TRUE) || (E_OK != TmpRet))
  {
    /* Fup frame is missing or there where an issue on processing the sync frame */
    EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
  }
#endif

  /* !LINKSTO EthTSyn.EB.Slave.LostSyncFUPFrame, 1 */
  if(E_OK == TmpRet)
  {
    SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
    EthTSyn_Slave[EthTSynCtrlIdx].Sync_ActualIngressTimeStamp = Sync_IngressTimeStamp;
    EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived = TRUE;
    SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

    /* Timeout value of the Follow_Up message (of the subsequent Sync message).
       A value of 0 deactivates this timeout observation.*/
    EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout =
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout;
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
    {

      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity =
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)((uint64) DataPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.portNumber =
           (uint16)(((uint16) DataPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.portNumber |=
           (uint16)((uint16) DataPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sequenceId =
                                                EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber;

    }
#endif
  }
  else
  {
    /* Reset the state of the received sync frame*/
    TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, FALSE);
  }
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
  {
    /* A new sync was received, reset the flag.*/
    TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncFupReceived, FALSE);
  }
#endif

}

FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CheckSC
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  Std_ReturnType TmpRet = E_NOT_OK;
  uint16 DeltaSeqCount = 0U;
  uint16 ReceivedSeqCounter = 0U;
  StbM_TimeBaseStatusType syncTimeBaseStatus = 0U;
  StbM_TimeBaseStatusType offsetTimeBaseStatus = 0U;
  boolean StatusChecked = FALSE;

  /* Store serial number to find corresponding follow up frame. */
  ReceivedSeqCounter = EthTSyn_GetPTPHeaderSequNumber(DataPtr);

  /* EthTSyn checkes for TIMEOUT from StbM only if SequenceCounterHysteresis is configured
     or if SequenceCounter needs to be validated against SequenceCounterJumpWidth. */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SequenceCounterHysteresis > 0U)
  {
    (void)StbM_GetTimeBaseStatus(
                                  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                                  &syncTimeBaseStatus, &offsetTimeBaseStatus
                                );
    StatusChecked = TRUE;
  }

  /* !LINKSTO EthTSyn.PRS_TS_00199_SkipCheckSCounterAfterInit, 1 */
  /* !LINKSTO EthTSyn.EB.NoSCCheck_SyncTimeout, 1 */
  if(EthTSyn_Slave[EthTSynCtrlIdx].CheckSeqCounter == FALSE)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00199_SkipCheckSCounterIfWidthIs0, 1 */
    /* A time Slave shall not check the SequenceCounter if
       GlobalTimeSequenceCounterJumpWidth is configured to 0. */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SequenceCounterJumpWidth != 0U)
    {
      /* On the next received sync frame the sequence counter can be checked against the jump width. */
      TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].CheckSeqCounter, TRUE);
    }
    TmpRet = E_OK;
  }
  else
  {
    DeltaSeqCount = ETHTSYN_DELTA_SC(ReceivedSeqCounter, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

    if(
        (DeltaSeqCount > 0U) &&
        (DeltaSeqCount <= EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SequenceCounterJumpWidth)
      )
    {
      /* Valid Sequence counter*/
      /* !LINKSTO EthTSyn.PRS_TS_00198_JumpWidthMaxValue, 1 */
      TmpRet = E_OK;
    }
    else
    {
      if(StatusChecked == FALSE)
      {
        (void)StbM_GetTimeBaseStatus(
                                      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                                      &syncTimeBaseStatus, &offsetTimeBaseStatus
                                    );
      }

      if(((syncTimeBaseStatus & ETHTSYN_STBM_TIMEOUT) != 0U) && (DeltaSeqCount > 0U))
      {
        /* !LINKSTO EthTSyn.EB.NoSCCheck_SyncTimeout, 1 */
        /* Timeout occured - No need to check SC for the next received Sync frame. */
        TmpRet = E_OK;
      }

      /* Invalid Sequence counter*/
      /* !LINKSTO EthTSyn.PRS_TS_00198_JumpWidthGreaterThanConfiguredCounterJumpWidth, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00198_JumpWidthIsZero, 1 */
    }

  }
  /* Save the seqId for the next received sync frame. */
  TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber, ReceivedSeqCounter);

  /* Reset ValidSyncSyncFUpPairs in case invalid Sync frame was received */
  if(((syncTimeBaseStatus & ETHTSYN_STBM_TIMEOUT) != 0U) && (TmpRet == E_NOT_OK))
  {
    EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs = 0U;
  }

  TS_PARAM_UNUSED(offsetTimeBaseStatus);


  return TmpRet;
}
#endif /* ETHTSYN_MAX_SLAVE != 0U */

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
#if (ETHTSYN_MAX_SLAVE != 0U)

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyAutosarTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  uint8 Crc_Time_1;
#endif
  /* The length of the IEEE TLV plus the length of the AUTOSAR TLV header: 76 + 10.
   * If the Length is higher than this size there is at least 1 SubTLV. */
  /* !LINKSTO EthTSyn.EB.RxIndication.InvalidFrameLength, 1 */
  if(Length > (ETHTSYN_FUP_AUTOSAR_TLV_HEADER_START_ADDR + ETHTSYN_FUP_AUTOSAR_TLV_HEADER_LENGTH))
  {
    RetVal = EthTSyn_VerifyTLVHeader(&DataPtr[ETHTSYN_FUP_AUTOSAR_TLV_HEADER_START_ADDR]);

    if(RetVal != E_NOT_OK)
    {
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
      /* !LINKSTO EthTSyn.EB.RxIndication.ProcessSubTlvLength, 1 */
      RetVal = EthTSyn_VerifySubTLVData(EthTSynCtrlIdx, &DataPtr[0U], Length);
#else
      /* !LINKSTO EthTSyn.EB.EthSwtRx_SyncFUpSubTLV_IncorrectLength, 1 */
      if((DataPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR] == ETHTSYN_FUP_SUBTLV_TIME_TYPE) &&
         (Length > (ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS)) &&
         ((DataPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS] &
           ETHTSYN_CORRECTION_FIELD_BIT_MASK) != 0U
         )
        )
        {
          /* !LINKSTO EthTSyn.PRS_TS_00207, 1 */
          EthTSyn_Inc02_BridgeCalculateCrcTime1(EthTSynCtrlIdx, &DataPtr[0U], &Crc_Time_1);
          if((Length > (ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1)) &&
             (Crc_Time_1 == DataPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1])
            )
          {
            RetVal = E_OK;
          }
          else
          {
            RetVal = E_NOT_OK;
          }
        }
        else
        {
          /* SyncFUp doesn't contain a TimeSecured Sub-TLV, or the TimeSecured Sub-TLV doesn't need validation */
          RetVal = E_OK;
        }
#endif
    }
  }

  return RetVal;
}

/* !LINKSTO EthTSyn.PRS_TS_00106, 1 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyTLVHeader
(
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 Tlv_Length;

  Tlv_Length = ETHTSYN_GET16(DataPtr, 2U);

  /* Verify header: */
  if(
      /* TLV type */
      (DataPtr[ETHTSYN_FUP_TLV_B0_TYPE_1] == 0U) &&
      (DataPtr[ETHTSYN_FUP_TLV_B1_TYPE_0] == 3U) &&
      /* length field */
      (Tlv_Length > ETHTSYN_FUP_EXT_TLV_LENGTH_0) &&

      /* organizationId */
      (DataPtr[ETHTSYN_FUP_TLV_B4_ORGID_2] == ETHTSYN_FUP_EXT_TLV_ORGID_2) &&
      (DataPtr[ETHTSYN_FUP_TLV_B5_ORGID_1] == ETHTSYN_FUP_EXT_TLV_ORGID_1) &&
      (DataPtr[ETHTSYN_FUP_TLV_B6_ORGID_0] == ETHTSYN_FUP_EXT_TLV_ORGID_0) &&
      /* organizationSubType */
      (DataPtr[ETHTSYN_FUP_TLV_B7_ORG_SUBTYPE_2] == ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_2) &&
      (DataPtr[ETHTSYN_FUP_TLV_B8_ORG_SUBTYPE_1] == ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_1) &&
      (DataPtr[ETHTSYN_FUP_TLV_B9_ORG_SUBTYPE_0] == ETHTSYN_FUP_EXT_TLV_ORG_SUBTYPE_0)
    )
  {
    RetVal = E_OK;
  }

  return RetVal;
}

#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifySubTLVData
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 Idx = ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR;
  uint16 Tlv_Received_Length = 0U;
  uint16 Tlv_Processed_Length = ETHTSYN_FUP_EXT_TLV_LENGTH_0;
  boolean ExitLoop = FALSE;

  Tlv_Received_Length = ETHTSYN_GET16(DataPtr, ETHTSYN_FUP_AUTOSAR_TLV_HEADER_START_ADDR + 2U);

  while
  (
    ((Idx + ETHTSYN_FUP_SUBTLV_HEADER_SIZE) <= Length) &&
    (ExitLoop != TRUE) &&
    (Tlv_Processed_Length < Tlv_Received_Length)
  )
  {
    /* Verify the type of the existing SubTLV */
    switch(DataPtr[Idx])
    {
      case ETHTSYN_FUP_SUBTLV_TIME_TYPE:
      {
        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_TIME_LENGTH)
        {
          RetVal = EthTSyn_VerifyTimeSecuredSubTlv(EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }
        break;
      }
      case ETHTSYN_FUP_SUBTLV_STATUS_NOT_SECURED_TYPE:
      {
        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_STATUS_LENGTH)
        {
          RetVal = EthTSyn_VerifyStatusNotSecuredSubTlv(EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }
        break;
      }
      case ETHTSYN_FUP_SUBTLV_STATUS_SECURED_TYPE:
      {

        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_STATUS_LENGTH)
        {
          RetVal = EthTSyn_VerifyStatusSecuredSubTlv(EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }

        break;
      }
      case ETHTSYN_FUP_SUBTLV_USERDATA_NOT_SECURED_TYPE:
      {
        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH)
        {
          /* !LINKSTO EthTSyn.PRS_TS_00081, 1 */
          RetVal = EthTSyn_VerifyUserDataNotSecuredSubTlv
                      (EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }

        break;
      }
      case ETHTSYN_FUP_SUBTLV_USERDATA_SECURED_TYPE:
      {
        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH)
        {
          /* !LINKSTO EthTSyn.PRS_TS_00081, 1 */
          RetVal = EthTSyn_VerifyUserDataSecuredSubTlv(EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }

        break;
      }
#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)
      case ETHTSYN_FUP_SUBTLV_OFS_NOT_SECURED_TYPE:
      {
        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_OFS_LENGTH)
        {
          /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_Sub_TlvType, 1 */
          RetVal = EthTSyn_VerifyOfsNotSecuredSubTlv
                      (EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }

        break;
      }

      case ETHTSYN_FUP_SUBTLV_OFS_SECURED_TYPE:
      {
        /* If Sub-TLV length is incorrect, following data shall be corrupt - drop whole message */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.IncorrectLength, 1 */
        /* DataPtr[Idx + 1U] holds the second byte in a SubTLV - Length Byte */
        if(DataPtr[Idx + 1U] == ETHTSYN_FUP_SUBTLV_OFS_LENGTH)
        {
          /* !LINKSTO EthTSyn.PRS_TS_00081, 1 */
          /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_Sub_TlvType, 1 */
          RetVal = EthTSyn_VerifyOfsSecuredSubTlv(EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
        }
        else
        {
          RetVal = E_NOT_OK;
        }

        break;
      }
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */
#if (ETHTSYN_ICV_USED == STD_ON)
      case ETHTSYN_FUP_SUBTLV_TIMEAUTH_TYPE:
      {
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_IcvVerified, 1 */
        switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxIcvValidated)
        {
          case ETHTSYN_ICV_OPTIONAL: /* Fall through */
          case ETHTSYN_ICV_VERIFIED: /* Fall through */
          {
            /* Check if timeauth is configured for this slave */
            if(ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvRxLength != ETHTSYN_ICV_NOT_CONFIGURED)
            {
              /* !LINKSTO EthTSyn.R22-11.PRS_TS_00243, 1 */
              /* !LINKSTO EthTSyn.R22-11.PRS_TS_00244, 1 */
              /* !LINKSTO EthTSyn.R22-11.PRS_TS_00245, 1 */
              /* !LINKSTO EthTSyn.R22-11.PRS_TS_00246, 1 */
              RetVal = EthTSyn_CheckTimeAuthSubTlv(EthTSynCtrlIdx, &DataPtr[0U], Length, Idx);
              /* Timeauth is the last TLV. */
              ExitLoop = TRUE;
            }
            break;
          }
          /* !LINKSTO EthTSyn.R22-11.PRS_TS_00243, 1 */
          case ETHTSYN_ICV_IGNORED:
          {
            RetVal = E_OK;
            break;
          }
          case ETHTSYN_ICV_NOT_VERIFIED:
          {
            /* !LINKSTO EthTSyn.R22-11.PRS_TS_00247, 1 */
            RetVal = E_NOT_OK;
            break;
          }
          /* CHECK: NOPARSE */
          default:
          {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
              ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
            RetVal = E_NOT_OK;
            break; /* Caution: this 'break' is required by MISRA-C:2012 */
          }
          /* CHECK: PARSE */
        }
        break;
      }
#endif /* ETHTSYN_ICV_USED == STD_ON */
      /* Sub-TLV with unknown Sub-TLV type shall be ignored and the next
        Sub-TLV shall be processed. */
      /* !LINKSTO EthTSyn.PRS_TS_00118, 1 */
      /* !LINKSTO EthTSyn.EB.AutosarSubTLV.UnknownSubTLVType, 1 */
      default:
      {
        RetVal = E_OK;
        break;
      }
    }
    if(RetVal == E_OK)
    {
      Tlv_Processed_Length += (uint16)(DataPtr[Idx + 1U]) + ETHTSYN_FUP_SUBTLV_HEADER_SIZE;
    }
    else
    {
      ExitLoop = TRUE;
    }

    /* Move DataPtr offset to hold the SubTLV type byte  */
    Idx += (uint16)(DataPtr[Idx + 1U]) + ETHTSYN_FUP_SUBTLV_HEADER_SIZE;
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyTimeSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_TIME_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_TimeSecuredValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_TimeSecured_Optional, 1 */
      case ETHTSYN_CRC_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
#if(ETHTSYN_RX_CRC_USED == STD_ON)
        RetVal = EthTSyn_CompareCrc
        (
          EthTSynCtrlIdx,
          &DataPtr[0U],
          Offset
        );
#endif
        break;
      }
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_TimeSecured_Ignored, 1 */
      case ETHTSYN_CRC_IGNORED:
      {
        RetVal = E_OK;
        break;
      }
      case ETHTSYN_CRC_NOT_VALIDATED:
      {
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_TimeNotValidated, 1 */
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_NOT_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }
#if(ETHTSYN_RX_CRC_USED == STD_OFF)
  TS_PARAM_UNUSED(DataPtr);
#endif
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyStatusSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_STATUS_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_StatusValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_StatusSecured_Optional, 1 */
      case ETHTSYN_CRC_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
#if(ETHTSYN_RX_CRC_USED == STD_ON)
        RetVal = EthTSyn_CompareCrc_Status
        (
          EthTSynCtrlIdx,
          &DataPtr[0U],
          Offset
        );
        if(RetVal == E_OK)
#endif /* ETHTSYN_RX_CRC_USED == STD_ON */
        {
          /* Verify that SubTLVPtr byte offset 2 is the status */
          /* !LINKSTO EthTSyn.PRS_TS_00156_SgwIsNOTSyncToSubDomain, 1 */
          if(
              (
                DataPtr[Offset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS] &
                ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV
              ) > 0U
            )
          {
            /* !LINKSTO EthTSyn.PRS_TS_00156_SgwIsSyncToSubDomain, 1 */
            /* Extract the SYNC_TO_GATEWAY bit if it is set */
            EthTSyn_SyncToGatewayBit = ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM;
          }
        }
        break;
      }
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_StatusSecured_Ignored, 1 */
      case ETHTSYN_CRC_IGNORED:
      {
        /* Verify that SubTLVPtr byte offset 2 is the status */
        if(
            (
              DataPtr[Offset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS] &
              ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV
            ) > 0U
          )
        {
          /* Extract the SYNC_TO_GATEWAY bit if it is set */
          EthTSyn_SyncToGatewayBit = ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM;
        }
        RetVal = E_OK;
        break;
      }
      case ETHTSYN_CRC_NOT_VALIDATED:
      {
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_NOT_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyStatusNotSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_STATUS_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_StatusNotValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_StatusNotSecured_Ignored, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_StatusNotSecured_Optional, 1 */
      case ETHTSYN_CRC_IGNORED: /* Fall through */
      case ETHTSYN_CRC_NOT_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
        {
          /* Verify that SubTLVPtr byte offset 2 is the status */
          /* !LINKSTO EthTSyn.PRS_TS_00156_SgwIsNOTSyncToSubDomain, 1 */
          if(
              (
                DataPtr[Offset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS] &
                ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV
              ) > 0U
            )
          {
            /* Extract the SYNC_TO_GATEWAY bit if it is set */
            /* !LINKSTO EthTSyn.PRS_TS_00156_SgwIsSyncToSubDomain, 1 */
            EthTSyn_SyncToGatewayBit = ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM;
          }
          /* All the SubTLV data is set */
          RetVal = E_OK;
        }
        break;
      }
      case ETHTSYN_CRC_VALIDATED:
      {
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyUserDataSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_UsrDataValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_UserDataSecured_Optional, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00116_Validated, 1 */
      case ETHTSYN_CRC_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
#if(ETHTSYN_RX_CRC_USED == STD_ON)
        RetVal = EthTSyn_CalcComp_UserDataCrc
        (
          EthTSynCtrlIdx,
          &DataPtr[0U],
          Offset,
          NULL_PTR
        );

        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength  =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2];

#endif /* ETHTSYN_RX_CRC_USED == STD_ON */
        break;
      }
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_UserDataSecured_Ignored, 1 */
      case ETHTSYN_CRC_IGNORED:
      {
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength  =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2];

        RetVal = E_OK;
        break;
      }
      case ETHTSYN_CRC_NOT_VALIDATED:
      {
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_NOT_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }
#if(ETHTSYN_RX_CRC_USED == STD_OFF)
  TS_PARAM_UNUSED(DataPtr);
#endif
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyUserDataNotSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_USERDATA_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_UsrDataNotValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_UserDataNotSecured_Ignored, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_UserDataNotSecured_Optional, 1 */
      case ETHTSYN_CRC_IGNORED: /* Fall through */
      case ETHTSYN_CRC_NOT_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength  =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B3_USER_BYTE_0];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B4_USER_BYTE_1];
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2 =
                      DataPtr[Offset + ETHTSYN_FUP_SUBTLV_USERDATA_B5_USER_BYTE_2];

        RetVal = E_OK;
        break;
      }
      case ETHTSYN_CRC_VALIDATED:
      {
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }

  return RetVal;
}
#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyOfsNotSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_OFS_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_OFSNotValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_OFSNotSecured_Ignored, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_OFSNotSecured_Optional, 1 */
      case ETHTSYN_CRC_IGNORED: /* Fall through */
      case ETHTSYN_CRC_NOT_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
        RetVal = EthTSyn_SaveOfsData(EthTSynCtrlIdx, &DataPtr[0U], Offset);
        break;
      }
      case ETHTSYN_CRC_VALIDATED:
      {
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_VerifyOfsSecuredSubTlv
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length,
  uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if((Offset + ETHTSYN_FUP_SUBTLV_HEADER_SIZE + ETHTSYN_FUP_SUBTLV_OFS_LENGTH) <= Length)
  {
    switch(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].RxCrcValidated)
    {
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00107_OFSValidated, 1 */
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00109_OFSSecured_Optional, 1 */
      case ETHTSYN_CRC_VALIDATED: /* Fall through */
      case ETHTSYN_CRC_OPTIONAL:
      {
        /* !LINKSTO EthTSyn.PRS_TS_00117_Validated, 1 */
        /* !LINKSTO EthTSyn.PRS_TS_00117_Optional, 1 */
        RetVal = EthTSyn_CalcComp_OfsCrc
        (
          EthTSynCtrlIdx,
          &DataPtr[0U],
          Offset,
          NULL_PTR
        );

        if(RetVal == E_OK)
        {
          RetVal = EthTSyn_SaveOfsData(EthTSynCtrlIdx, &DataPtr[0U], Offset);
        }
        break;
      }
      /* !LINKSTO EthTSyn.R22-11.PRS_TS_00108_OFSSecured_Ignored, 1 */
      case ETHTSYN_CRC_IGNORED:
      {
        RetVal = EthTSyn_SaveOfsData(EthTSynCtrlIdx, &DataPtr[0U], Offset);
        break;
      }
      case ETHTSYN_CRC_NOT_VALIDATED:
      {
        /* !LINKSTO EthTSyn.EB.AutosarSubTLV.CRC_NOT_VALIDATED, 1 */
        RetVal = E_NOT_OK;
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        RetVal = E_NOT_OK;
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }
#if(ETHTSYN_RX_CRC_USED == STD_OFF)
  TS_PARAM_UNUSED(DataPtr);
#endif
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SaveOfsData
(
 uint8 EthTSynCtrlIdx,
 P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
 uint16 Offset
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 OfsTd = 0xFFU;
  uint8 Idx = 0U;

  /* !LINKSTO EthTSyn.PRS_TS_00110, 1 */
  /* OfsTimeDomain */
  /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_OfsTimeDomain, 1 */
  OfsTd = DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B2_TIMEDOMAIN];

  /* Check if the received ofsId is configured in EthTSyn.*/
  for(
        Idx = 0U;
        Idx < EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TotalOfsTimebase;
        Idx++
      )
  {
    /* The received time domain matches to the defined OfsTimeDomain */
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_TimeDomain, 1 */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsInfo[Idx].OfsGlobalTimeDomainId == OfsTd)
    {
      uint8 ArrayIndex = EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex;
      /* Extract the relevant StbM Offset TimeBase Id. */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeDomId =
           EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsInfo[Idx].OffsetTimeBaseId;

      /* Extract the offset relevant data*/
      /* Calculate and save received TimeSecHi */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.secondsHi =
                          (uint16)((uint16)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B3_TIMESEC] << 8U)
                                          + DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B4_TIMESEC];
      /* Calculate and save received TimeSec */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.seconds =
                         ((uint32)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B5_TIMESEC] << 24U)
                       + (uint32)((uint32)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B6_TIMESEC] << 16U)
                       + (uint32)((uint32)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B7_TIMESEC] << 8U)
                       + DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B8_TIMESEC];

      /* Calculate and save received TimeNSec */
      /* !LINKSTO EthTSyn.EB.PRS_TS_00119_OfsTimeNSec, 1 */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.nanoseconds =
                       ((uint32)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B9_TIMENSEC] << 24U)
                     + (uint32)((uint32)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B10_TIMENSEC] << 16U)
                     + (uint32)((uint32)DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B11_TIMENSEC] << 8U)
                     + DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B12_TIMENSEC];

      /* Status */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.timeBaseStatus =
                                  DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B13_STATUS];

      /* userDataLength */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetUserData.userDataLength =
                                  DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B14_USER_DATA_LENGTH];
      /* userBytes */
      /* !LINKSTO EthTSyn.PRS_TS_00088, 1 */
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetUserData.userByte0 =
                                  DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B15_USER_DATA_BYTE_0];
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetUserData.userByte1 =
                                  DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B16_USER_DATA_BYTE_1];
      EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetUserData.userByte2 =
                                  DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B17_USER_DATA_BYTE_2];


      /* !LINKSTO EthTSyn.EB.PRS_TS_00119_OfsTimeNSec, 1 */
      if(ETHTSYN_NANOSEC_MAX < EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.nanoseconds)
      {
        RetVal = E_NOT_OK;
      }
      else
      {
        /* Verify the status */
        if(
            (
              DataPtr[Offset + ETHTSYN_FUP_SUBTLV_OFS_B13_STATUS] &
              ETHTSYN_SYNC_TO_GATEWAY_MASK_SUBTLV
            ) > 0U
          )
        {
          /* Extract the SYNC_TO_GATEWAY bit if it is set */
          /* !LINKSTO EthTSyn.PRS_TS_00213, 1 */
          EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.timeBaseStatus = ETHTSYN_SYNC_TO_GATEWAY_MASK_STBM;
        }
        else
        {
          EthTSyn_OffsetTbInfo[ArrayIndex].StbMOffsetTimeStamp.timeBaseStatus = 0U;
        }
        /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
        RetVal = E_OK;
        /* Increase the index value */
        /* CHECK: NOPARSE */
        if(
            EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex <
            (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsIndex +
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TotalOfsTimebase)
          )
        {
          EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex++;
        }
        /* CHECK: PARSE */
        /* unreachable: else we reached the maximum number of the configured tlv */
      }
    }
  }


  return RetVal;
}
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */
#endif /* ETHTSYN_MAX_SLAVE != 0U */

#if((ETHTSYN_RX_CRC_USED == STD_ON) || (ETHTSYN_TX_CRC_USED == STD_ON))
/* !LINKSTO EthTSyn.SWS_EthTSyn_00111, 1 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_CalculateCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_0,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_1
)
{
  uint8 Crc_Temp_0;
  uint8 Crc_Temp_1;
  uint8 SeqNr = (BufPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]) % 16U;

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00096, 1 */
  Crc_Temp_0 = Crc_CalculateCRC8H2F(&EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags, 1U, 0U, TRUE);
  Crc_Temp_1 = Crc_Temp_0;

  /* !LINKSTO EthTSyn.PRS_TS_00099, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00113, 1 */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcDomainNumber == TRUE)
  {
    Crc_Temp_0 = Crc_CalculateCRC8H2F
            (&BufPtr[ETHTSYN_PTP_HEADER_B4_DOMAIN], 1U, Crc_Temp_0, FALSE);
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcSourcePortIdentity == TRUE)
  {
    Crc_Temp_0 = Crc_CalculateCRC8H2F
            (&BufPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0], 10U, Crc_Temp_0, FALSE);
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcPreciseOriginTimestamp == TRUE)
  {
    Crc_Temp_0 = Crc_CalculateCRC8H2F
            (
              &BufPtr[ETHTSYN_PTP_HEADER_SIZE], ETHTSYN_TIME_STAMP_SIZE, Crc_Temp_0, FALSE
            );
  }
  Crc_Temp_0 = Crc_CalculateCRC8H2F
            (
              &EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr],
              1U, Crc_Temp_0, FALSE
            );

  /* !LINKSTO EthTSyn.PRS_TS_00100, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00114, 1 */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcMessageLength == TRUE)
  {
    Crc_Temp_1 =
        Crc_CalculateCRC8H2F(&BufPtr[ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1], 2U, Crc_Temp_1, FALSE);
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcCorrectionField == TRUE)
  {
    Crc_Temp_1 = Crc_CalculateCRC8H2F
            (&BufPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0], 8U, Crc_Temp_1, FALSE);
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcSequenceId == TRUE)
  {
    Crc_Temp_1 =
        Crc_CalculateCRC8H2F(&BufPtr[ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1], 2U, Crc_Temp_1, FALSE);
  }
  Crc_Temp_1 = Crc_CalculateCRC8H2F
            (
              &EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr],
              1U, Crc_Temp_1, FALSE
            );

  *Crc_0 = Crc_Temp_0;
  *Crc_1 = Crc_Temp_1;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CalcComp_UserDataCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_UserData
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Crc_UserDataTemp = 0U;
  uint8 SeqNr = (BufPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]) % 16U;

  /* !LINKSTO EthTSyn.PRS_TS_00102, 1 */
  /* Calculate Crc_UserData by considering: UserDataLength, UserByte_0, UserByte_1, UserByte_2 and
   * DataID */
  Crc_UserDataTemp = Crc_CalculateCRC8H2F
      (&BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B2_USER_DATA_LENGTH], 4U, 0U, TRUE);

  Crc_UserDataTemp = Crc_CalculateCRC8H2F
      (&EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr], 1U, Crc_UserDataTemp,
                                                                                            FALSE);

#if(ETHTSYN_MAX_SLAVE != 0U)
  if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
  {
    /* Compare calculated Crc with received Crc */
    if(
        Crc_UserDataTemp == BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_USERDATA_B6_CRC_USERDATA]
      )
    {
      RetVal = E_OK;
    }
  }
  else
#endif/* ETHTSYN_MAX_SLAVE != 0U */
  {
    *Crc_UserData = Crc_UserDataTemp;
    RetVal = E_OK;
  }

  return RetVal;
}
#endif /* ((ETHTSYN_RX_CRC_USED == STD_ON) || (ETHTSYN_TX_CRC_USED == STD_ON)) */

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CalcComp_OfsCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  uint16 SubTlvOffset,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_Ofs
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Crc_OfsTemp = 0U;
  uint8 SeqNr = (BufPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]) % 16U;

  /* calculate the CRC for CRC_OFS by considering the contents
   * of OfsTimeDomain, OfsTimeSec, OfsTimeNSec, Status, UserDataLength,
   * UserByte_0, UserByte_1, UserByte_2 and DataID (in this order).*/

  Crc_OfsTemp = Crc_CalculateCRC8H2F
      (&BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B2_TIMEDOMAIN], 16U, 0U, TRUE);

  Crc_OfsTemp = Crc_CalculateCRC8H2F
      (&EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr], 1U, Crc_OfsTemp, FALSE);

#if(ETHTSYN_MAX_SLAVE != 0U)
  if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
  {
    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00119_SuccessfulValidation, 1 */
    /* Compare calculated Crc with received Crc */
    if(
        Crc_OfsTemp == BufPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_OFS_B18_CRC]
      )
    {
      RetVal = E_OK;
    }
  }
  else
#endif/* ETHTSYN_MAX_SLAVE != 0U */
  {
    *Crc_Ofs = Crc_OfsTemp;
    RetVal = E_OK;
  }

  return RetVal;
}

#if(ETHTSYN_RX_CRC_USED == STD_ON)
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
/* !LINKSTO EthTSyn.PRS_TS_00113, 1 */
/* !LINKSTO EthTSyn.PRS_TS_00114, 1 */
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CompareCrc
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 SubTlvOffset
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Crc_0;
  uint8 Crc_1;

  /* !LINKSTO EthTSyn.PRS_TS_00183, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00185, 1 */
  EthTSyn_CalculateCrc(EthTSynCtrlIdx, &DataPtr[0U], &Crc_0, &Crc_1);

  if(
      (Crc_0 == DataPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B3_CRC_TIME_0]) &&
      (Crc_1 == DataPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1])
    )
  {
    RetVal = E_OK;
  }
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CompareCrc_Status
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 SubTlvOffset
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Crc_Status;

  uint8 SeqNr = (DataPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]) % 16U;

  /* !LINKSTO EthTSyn.PRS_TS_00101, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00115, 1 */
  Crc_Status = Crc_CalculateCRC8H2F
      (&DataPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B2_STATUS], 1U, 0U, TRUE);

  Crc_Status = Crc_CalculateCRC8H2F
      (&EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr], 1U, Crc_Status, FALSE);

  /* Compare calculated Crc with received Crc */
  if(
      Crc_Status == DataPtr[SubTlvOffset + ETHTSYN_FUP_SUBTLV_STATUS_B3_CRC_STATUS]
    )
  {
    RetVal = E_OK;
  }
  return RetVal;
}
#endif

#endif/* (ETHTSYN_RX_CRC_USED == STD_ON) */
#endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

#if (ETHTSYN_MAX_SLAVE != 0U)
/* !LINKSTO EthTSyn.EB.Slave.LostPdelayRespFUP, 1 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxSynFUpFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 Length
)
{
  const uint16 RxSequNumber = EthTSyn_GetPTPHeaderSequNumber(DataPtr);
  Std_ReturnType RetVal = E_NOT_OK;
  StbM_TimeBaseStatusType syncTimeBaseStatus = 0U;
  StbM_TimeBaseStatusType offsetTimeBaseStatus = 0U;

  /* Default value for the SYNC_TO_GATEWAY bit in timeBaseStatus */
  /* !LINKSTO EthTSyn.PRS_TS_00211, 1 */
  /* If MessageCompliance is set to TRUE the SYNC_TO_GATEWAY bit
     within timeBaseStatus shall be set to zero.*/
  /* !LINKSTO EthTSyn.PRS_TS_00212, 1 */
  EthTSyn_SyncToGatewayBit = 0U;


  /* EthTSyn checkes for TIMEOUT from StbM only if SequenceCounterHysteresis is configured. */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SequenceCounterHysteresis > 0U)
  {
    (void)StbM_GetTimeBaseStatus(
                                  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                                  &syncTimeBaseStatus, &offsetTimeBaseStatus
                                );
  }
  TS_PARAM_UNUSED(offsetTimeBaseStatus);

  /* !LINKSTO EthTSyn.PRS_TS_00196, 1 */
  /* !LINKSTO EthTSyn.PRS_TS_00200, 1 */
  if(RxSequNumber == EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber)
  {
    if((syncTimeBaseStatus & ETHTSYN_STBM_TIMEOUT) != 0U)
    {
      /* Valid pair of Sync/SyncFUp frames was received */
      EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs++;
    }
#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)

    RetVal = EthTSyn_VerifyAutosarTlv(EthTSynCtrlIdx, &DataPtr[0U], Length);
#else
    {
      TS_PARAM_UNUSED(Length);
    }
#endif

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
    if(RetVal == E_OK)
    {
#endif
      if(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived)
      {
        Eth_TimeStampType OriginTimeStamp;

        OriginTimeStamp.nanoseconds = 0U;
        OriginTimeStamp.seconds = 0U;
        OriginTimeStamp.secondsHi = 0U;

        /* !LINKSTO EthTSyn.EB.Slave.LostSyncFUPFrame, 1 */
        TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, FALSE);

        /* Get origin time stamp of the master from follow up frame payload. */
        EthTSyn_ArrayToTimeStamp(&OriginTimeStamp, &DataPtr[ETHTSYN_PTP_HEADER_SIZE]);

        if(ETHTSYN_NANOSEC_MAX < OriginTimeStamp.nanoseconds)
        {
          /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
          RetVal = E_NOT_OK;
        }
        else
        {
          /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
          RetVal = E_OK;
        }

        if(E_OK == RetVal)
        {
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
          RetVal = EthTSyn_PerformSync(EthTSynCtrlIdx, &DataPtr[0U], OriginTimeStamp);
#else
          (void)EthTSyn_PerformSync(EthTSynCtrlIdx, &DataPtr[0U], OriginTimeStamp);
#endif /* (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) */
        }
      }
#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
    }
#endif
  }
  else
  {
    if((syncTimeBaseStatus & ETHTSYN_STBM_TIMEOUT) != 0U)
    {
      EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs = 0U;
    }
  }
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  if(E_OK != RetVal)
  {
    /* Sync frame is missing or there where an issue on processing the Fup frame */
    EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
  }
#endif
}

/* !LINKSTO EthTSyn.EB.Slave.LostPdelayResp, 1 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxPdelayRespFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  Std_ReturnType TmpRet;
  uint16 PdelayReqSequNumber;
  EthTSyn_PdelayCalculationType PdelayCalculationStarted;
  const uint16 RxSequNumber = EthTSyn_GetPTPHeaderSequNumber(DataPtr);


  TS_AtomicAssign16(PdelayReqSequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber);
  TS_AtomicAssign8(PdelayCalculationStarted, EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay);

  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
  /* Check source port identity */
  TmpRet = TS_MemCmp(
                      &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Tx_SrcPortIdentity[0U],
                      &DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE],
                      ETHTSYN_SOURCEPORTIDENTITY_SIZE
                    );
  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

  if(RxSequNumber != PdelayReqSequNumber)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00192, 1 */
    TmpRet = E_NOT_OK;
  }
  else if((ETHTSYN_PDELAYCALC_PDELAYREQ_SENT_MASK & PdelayCalculationStarted) != ETHTSYN_PDELAYCALC_PDELAYREQ_SENT_MASK)
  {
    TmpRet = E_NOT_OK;
  }
  else
  {
    /* Keep TmpRet from TS_MemCmp(). */
  }

  if(E_OK == TmpRet)
  {
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
    Eth_TimeStampType IngressTimeStamp_Resp={0U, 0U, 0U};
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF */
    /* Received Pdelay response correspond to previously sent Pdelay request. */
    /* See 802.1AS-2011 Ch 11.1.2: Propagation delay calculation:
     D = ((t4 - t1) - (t3 - t2)) / 2 */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
#if((ETHTSYN_IEEE1588_CONFIGURED == STD_ON) && (ETHTSYN_TIME_RECORDING == STD_ON))
    boolean GetIngress = FALSE;
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
    {
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
        /* Try to retrive the ingress of the delay_resp only if the timevalidation is enabled
           for this timedomain. */
        GetIngress = TRUE;
      }
      else
      {
        /* Skip the GetIngress timestamp. */
        GetIngress = FALSE;
      }
    }
    else
    {
      /* If PTP is not set to TRUE, the peer to peer mechanism is used, consequently the ingress timestamp
         is needed */
      GetIngress = TRUE;
    }
    if(GetIngress == TRUE)
    {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON) && (ETHTSYN_TIME_RECORDING == STD_ON) */
      /* Get t4 */
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00049, 1 */
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00161, 1 */
      TmpRet = EthTSyn_GetIngressTimeStamp(EthTSynCtrlIdx, DataPtr, &IngressTimeStamp_Resp);
#if((ETHTSYN_IEEE1588_CONFIGURED == STD_ON) && (ETHTSYN_TIME_RECORDING == STD_ON))
    }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON) && (ETHTSYN_TIME_RECORDING == STD_ON) */
    if(E_OK == TmpRet)
    {
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF */
      Eth_TimeStampType ReceivedTimeStamp;
      /* Get t2 */
      EthTSyn_ArrayToTimeStamp(
                                &ReceivedTimeStamp,
                                &DataPtr[ETHTSYN_PTP_HEADER_SIZE]
                              );

      if(ETHTSYN_NANOSEC_MAX >= ReceivedTimeStamp.nanoseconds)
      {
        /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
        {
          /* requestReceiptTimeStamp as received in pdelay_Response message */
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
              seconds = ReceivedTimeStamp.seconds;
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
              nanoseconds = ReceivedTimeStamp.nanoseconds;

          /* Save the sourcePortId of the received Pdelay_Resp frame*/
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                 = (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                |= (uint64)((uint64) DataPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.portNumber =
               (uint16)(((uint16) DataPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.portNumber |=
               (uint16)((uint16) DataPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);

        }
#endif

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
        {
          /* Save the time received in the Delay_resp frame. */
          /* !LINKSTO EthTSyn.EB.PTPE2EDelayRespSaveT4, 1 */
          SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

          EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4 = ReceivedTimeStamp;
          /* If the frame is succesfully processed, save the correction.
             Is needed in calculation of the delay path.*/
          /* !LINKSTO EthTSyn.EB.PTPE2EDelayRespCorrectionField, 1 */
          TmpRet = EthTSyn_SavePTPCorrField
          (
            EthTSynCtrlIdx,
            &DataPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0],
            &EthTSyn_Slave[EthTSynCtrlIdx].CorrectionDelayRespCorrection
          );

          SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

          /* The calculation of the pdelay can be started on the next mainfunction. */
          TS_AtomicSetBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
            ETHTSYN_BITPOS_PDELAYRESP_RECEIVED
          );
          /* E2E is one step mechanism, so no fup will be expected. */
          /* !LINKSTO EthTSyn.EB.PTPE2ECalculateMeanDelay, 1 */
          TS_AtomicSetBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
            ETHTSYN_BITPOS_PDELAYRESP_FUP_RECEIVED
          );
        }
        else
        {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
          EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4 = IngressTimeStamp_Resp;
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF */
          EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2 = ReceivedTimeStamp;
          TS_AtomicSetBit_8
          (
            &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
            ETHTSYN_BITPOS_PDELAYRESP_RECEIVED
          );
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
        }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
      }
      else
      {
        /* Something is wrong, abort the pdelay calculation */
        TmpRet = E_NOT_OK;
      }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
    }
#endif/* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF */
  }
  if(TmpRet == E_NOT_OK)
  {
#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
    EthTSyn_PDelayFrameDropped(EthTSynCtrlIdx);
#endif
    /* Something is wrong, abort the pdelay calculation */
    EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
  }

}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxPdelayRespFUpFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  Std_ReturnType TmpRet;
  uint16 PdelayReqSequNumber;
  EthTSyn_PdelayCalculationType PdelayCalculationStarted;
  const uint16 RxSequNumber = EthTSyn_GetPTPHeaderSequNumber(DataPtr);


  TS_AtomicAssign16(PdelayReqSequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber);
  TS_AtomicAssign8(PdelayCalculationStarted, EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay);

  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
  /* Check source port identity */
  TmpRet = TS_MemCmp(
                      &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Tx_SrcPortIdentity[0U],
                      &DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE],
                      ETHTSYN_SOURCEPORTIDENTITY_SIZE
                    );
  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

  if(RxSequNumber != PdelayReqSequNumber)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00194, 1 */
    TmpRet = E_NOT_OK;
  }
  else if((ETHTSYN_PDELAYCALC_PDELAYRESP_RECEIVED_MASK & PdelayCalculationStarted) != ETHTSYN_PDELAYCALC_PDELAYRESP_RECEIVED_MASK)
  {
    TmpRet = E_NOT_OK;
  }
  else
  {
    /* Keep TmpRet from TS_MemCmp(). */
  }

  if(E_OK == TmpRet)
  {
    /* Received Pdelay response follow up correspond to previously sent Pdelay request. */
    /* Get t3 */
    EthTSyn_ArrayToTimeStamp(&EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3, &DataPtr[ETHTSYN_PTP_HEADER_SIZE]);

    if(ETHTSYN_NANOSEC_MAX >= EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.nanoseconds)
    {
      /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
         /* responseOriginTimeStamp as received in pdelay_Response_Follow_Up */
         EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseOriginTimestamp.seconds
              =  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.seconds;
         EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseOriginTimestamp.
              nanoseconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.nanoseconds;
      }
#endif

      TS_AtomicSetBit_8
      (
        &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
        ETHTSYN_BITPOS_PDELAYRESP_FUP_RECEIVED
      );

#if(ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DEM)
      /* Heal dem event */
      /* !LINKSTO EthTSyn.EB.Diagnostic_PdelayOK_DEM, 1 */
      Dem_ReportErrorStatus
      (
         EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdPdelayFailed,
         DEM_EVENT_STATUS_PREPASSED
      );
#elif(ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DET)
      /* PdelayResp/Fup pair was received, reset the counter */
      EthTSyn_Slave[EthTSynCtrlIdx].PdelayRespFupDroppedPairsCt = 0U;
#endif
#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
      /* Reset the supervision of timeout */
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFupPairTimeoutInit = FALSE;
#endif
    }
    else
    {
      /* Something is wrong, abort the pdelay calculation */
      TmpRet = E_NOT_OK;
    }
  }

  if(E_OK != TmpRet)
  {
#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
    EthTSyn_PDelayFrameDropped(EthTSynCtrlIdx);
#endif
    /* Something is wrong, abort the pdelay calculation */
    EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
  }

}
#endif /* ETHTSYN_MAX_SLAVE != 0U */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxPdelayReqFrame
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 LenByte
)
{
  Std_ReturnType TmpRet;


  /* Store serial number to be used for Pdelay_resp and Pdelay_resp_FUp. */
  TS_AtomicAssign16(
                     EthTSyn_Ctrl[EthTSynCtrlIdx].Ingress_PdelayReqSequNumber,
                     EthTSyn_GetPTPHeaderSequNumber(DataPtr)
                   );
  TS_MemCpy(
       &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Rx_SrcPortIdentity[0U],
       &DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
       ETHTSYN_SOURCEPORTIDENTITY_SIZE
     );
  /* Get ingress time stamp of Pdelay request. */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00160, 1 */
  TmpRet = EthTSyn_GetIngressTimeStamp
          (EthTSynCtrlIdx, DataPtr, &EthTSyn_Ctrl[EthTSynCtrlIdx].IngressTimeStamp);
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
  {
    /* Store serial number as received from slave. */
    TS_AtomicAssign16(
                   EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.sequenceId,
                   EthTSyn_Ctrl[EthTSynCtrlIdx].Ingress_PdelayReqSequNumber
                 );

    /* Save the sourcePortId of received Pdelay_Req frame*/
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity =
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
     (uint64)((uint64) DataPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.portNumber =
     (uint16)(((uint16) DataPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
    EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.portNumber |=
     (uint16)((uint16) DataPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
  }
#endif
  if(TmpRet == E_OK)
  {
#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
    /* !LINKSTO EthTSyn.EB.DevAuth_RxPdelayReqWithTLV, 1 */
    if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE + ETHTSYN_AUTH_CHALLENGE_TLV_SIZE) <= LenByte)
    {
       EthTSyn_PdelayDevAuth(EthTSynCtrlIdx,
          &DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE]);
    }
#else
    TS_PARAM_UNUSED(LenByte);
#endif
     /* !LINKSTO EthTSyn.PRS_TS_00120, 1 */
     /* set the transmission flag for pdelayresp, to be sent in the next mainfunction */
     ETHTSYN_SET_TXFLAG
      (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_PDELAYRESP, TRUE);
  }

}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetIngressTimeStamp
(
  uint8 EthTSynCtrlIdx,
  /* Deviation MISRAC2012-1 */
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) RxDataPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
)
{
  Std_ReturnType RetVal;
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampQualType TimeQuality;
#endif
#if((ETHTSYN_TIME_RECORDING == STD_ON) || ((ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) && (ETHTSYN_MAX_SLAVE != 0U)))
  /* Extract message type from PTP header. */
  const uint8 MsgType = RxDataPtr[ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE] & ETHTSYN_8BIT_MASK_LN;
#endif


#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00128, 1 */
    (void)EthIf_GetIngressTimeStamp
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, /* EthIf CtrlIdx */
        RxDataPtr,
        &TimeQuality,
        TimeStampPtr /* TimeStampPtr */
      );

    /* !LINKSTO EthTSyn.EB.InvTimeQuality.PdelayRespIngress, 1 */
    /* !LINKSTO EthTSyn.EB.InvTimeQuality.Slave.SyncIngress, 1 */
    /* !LINKSTO EthTSyn.EB.InvTimeQuality.PdelayReqIngress, 1 */
    if(ETH_VALID == TimeQuality)
    {
      RetVal = E_OK;
    }
    else
    {
      RetVal = E_NOT_OK;
    }

    /* !LINKSTO EthTSyn.SWS_EthTSyn_00124, 1 */
    /* !LINKSTO EthTSyn.EB.InvTimeStamp.PdelayReqIngress, 1 */
    if(ETHTSYN_NANOSEC_MAX < TimeStampPtr->nanoseconds)
    {
      /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
      RetVal = E_NOT_OK; /* Nanoseconds >= 1s is not allowed. */
    }
    /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
  }
#if(ETHTSYN_MAX_SLAVE != 0U)
  /* Getting TimeStamps needed to calculate the sync reception delay.
     Proceed only if a Sync frame was received on a Slave and IngressTimeStamp is valid. */
  if(
      (TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) &&
      (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_SYNC) &&
      (RetVal == E_OK)
    )
  {
    RetVal = EthTSyn_Int01_ConvertEthTimeToVirtualTime
      (
        TimeStampPtr,
        &EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt
      );

    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].VltStbMIsEthFreerunningCounter == FALSE)
    {
      Eth_TimeStampType EthTimeStamp;
      StbM_VirtualLocalTimeType VirtualLocalTimeT3;

      EthTimeStamp.nanoseconds = 0U;
      EthTimeStamp.seconds = 0U;
      EthTimeStamp.secondsHi = 0U;

      /* !LINKSTO EthTSyn.SWS_EthTSyn_00190_Protection, 1 */
      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();

      /* !LINKSTO EthTSyn.SWS_EthTSyn_00190_GetCurrentTime, 1 */
      RetVal = EthIf_GetCurrentTime(
                                   EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx,
                                   &TimeQuality,
                                   &EthTimeStamp
                                 );

      /* !LINKSTO EthTSyn.EB.Slave.InvHWTimpStamp.GatewaySync, 1 */
      /* !LINKSTO EthTSyn.EB.TransparentClock_InvalidTimeStamp, 2 */
      if((E_OK == RetVal) && (ETH_VALID == TimeQuality))
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00190_GetCurrentVirtual, 1 */
        RetVal = StbM_GetCurrentVirtualLocalTime
        (
          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
          &EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt
        );

        RetVal |= EthTSyn_Int01_ConvertEthTimeToVirtualTime
        (
          &EthTimeStamp,
          &VirtualLocalTimeT3
        );

        /* !LINKSTO EthTSyn.SWS_EthTSyn_00190_SRD, 1 */
        RetVal |= EthTSyn_Int01_SubVirtualLocalTimes
                    (
                       &VirtualLocalTimeT3,
                       &EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt,
                       &EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay
                    );
      }
      else
      {
        /* If EthIf_GetCurrentTime() returns E_NOT_OK, or a TimeQuality that is not VALID,
         * syncronization shall not take place. */
        RetVal = E_NOT_OK;
      }
      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
    }
    else
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00138, 1 */
      EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt = EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt;
      EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay.nanosecondsLo = 0U;
      EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay.nanosecondsHi = 0U;
    }
  }
#endif/* ETHTSYN_MAX_SLAVE != 0U */
#else /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */

#if(ETHTSYN_TIME_RECORDING == STD_OFF)
  TS_PARAM_UNUSED(RxDataPtr); /* Not needed for StbM time stamp. */
#endif/* ETHTSYN_TIME_RECORDING == STD_OFF */

  RetVal = EthTSyn_Ctrl[EthTSynCtrlIdx].GetCurrentVirtualLocalTimeRetVal;
  EthTSyn_Int01_ConvertVirtualTimeToEthTime(&EthTSyn_Ctrl[EthTSynCtrlIdx].RxIngressVirtualTime, TimeStampPtr);

#if(ETHTSYN_MAX_SLAVE != 0U)
  if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx))
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00180_SRD, 1 */
    EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt = EthTSyn_Ctrl[EthTSynCtrlIdx].RxIngressVirtualTime;
    EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt = EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt;
    EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay.nanosecondsLo = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay.nanosecondsHi = 0U;
  }
#endif

#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
  {
    switch(MsgType)
    {
      case ETHTSYN_PTP_HEADER_MSGTYPE_SYNC:
      {
#if(ETHTSYN_MAX_SLAVE != 0U)
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
        (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
            (
                TimeStampPtr,
                &EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.syncIngressTimestamp
            );
#else
          EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.syncIngressTimestamp =
                                                EthTSyn_Ctrl[EthTSynCtrlIdx].RxIngressVirtualTime;
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#endif /* ETHTSYN_MAX_SLAVE != 0U */
        break;
      }
      case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ:
      case ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ:
      {
#if(ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE)
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
        (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
            (
                TimeStampPtr,
                &EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestReceiptTimestamp
            );
#else
          /* Get Ingress timestamp for pdelay_req on master side */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00224, 1 */
        EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestReceiptTimestamp =
                                                EthTSyn_Ctrl[EthTSynCtrlIdx].RxIngressVirtualTime;
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#endif /* ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE*/
        break;
      }
      case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP:
      case ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP:
      {
#if(ETHTSYN_MAX_SLAVE != 0U)
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
        (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
            (
               TimeStampPtr,
               &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseReceiptTimestamp
            );
#else
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseReceiptTimestamp =
                                                EthTSyn_Ctrl[EthTSynCtrlIdx].RxIngressVirtualTime;
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#endif /* ETHTSYN_MAX_SLAVE != 0U */
        break;
      }
      /* CHECK: NOPARSE */
      default:
      {
        /* Unknown message type: Ignore */
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
        break; /* Caution: this 'break' is required by MISRA-C:2012 */
      }
      /* CHECK: PARSE */
    }
  }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */


  return RetVal;
}


STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_GetEgressTimeStamp
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#else
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#endif
)
{
  Std_ReturnType RetVal;


#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  {
    Eth_TimeStampQualType TimeQuality;

    RetVal = EthIf_GetEgressTimeStamp
    (
      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, /* EthIf CtrlIdx */
      BufIdx, /* BufIdx */
      &TimeQuality,
      TimeStampPtr /* TimeStampPtr */
    );

    /* !LINKSTO EthTSyn.EB.InvTimeQuality.Master.SyncEgress, 1 */
    /* !LINKSTO EthTSyn.EB.InvTimeQuality.PdelayRespEgress, 1 */
    if((RetVal == E_OK) && (ETH_VALID == TimeQuality))
    {
      RetVal = E_OK;
    }
    else
    {
      RetVal = E_NOT_OK;
    }

    if(ETHTSYN_NANOSEC_MAX < TimeStampPtr->nanoseconds)
    {
      /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
      RetVal = E_NOT_OK; /* Nanoseconds >= 1s is not allowed. */
    }
    /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
  }
#else /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
  RetVal = StbM_GetCurrentVirtualLocalTime
      (
          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
          TimeStampPtr
      );
  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
  {
    if(BufIdx == EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx)
    {
#if(ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE)
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
        (
            TimeStampPtr,
            &EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.syncEgressTimestamp
        );
#else
      /* Save T2Vlt to be reported to StbM for time recording */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.syncEgressTimestamp = *TimeStampPtr;
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#endif /* ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE */
    }
    else if(BufIdx == EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx)
    {
      /* Save Pdelay_Resp egress timestamp for slave */
#if(ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE)
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
        (
            TimeStampPtr,
            &EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responseOriginTimestamp
        );
#else
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responseOriginTimestamp =
                                                                                    *TimeStampPtr;
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
#endif /* ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE */
    }
    /* EthTSyn_GetEgressTimeStamp() is called only for Sync, Pdelay_fup and Pdelay_req frames,
       and false condition will never be reached, therefore check no parse is needed. */
    /* CHECK: NOPARSE */
    else if(BufIdx == EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx)
    {
#if(ETHTSYN_MAX_SLAVE != 0U)
      if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
      {
        /* Save Pdelay_Req egress timestamp for slave */
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
        (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
          (
              TimeStampPtr,
              &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestOriginTimestamp
          );
#else
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestOriginTimestamp =
                                                                                     *TimeStampPtr;
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */
      }
      else
      {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
        /* Since only a slave initiates the pdelay calculation(transmits the PdelayReq frame),
          EthTSyn_TxConfirmation() will never be called with EthTSynCtrlIdx belonging to a master port. */
        ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif
      }
#endif/* ETHTSYN_MAX_SLAVE != 0U */
    }
    /* CHECK: PARSE */
    /* CHECK: NOPARSE */
    else
    {
      /* This branch can not be reached since BufIdx will not match for other frames. */
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
      ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif /* ETHTSYN_DEV_ERROR_DETECT == STD_ON */
    }
    /* CHECK: PARSE */
  }
#else
  TS_PARAM_UNUSED(BufIdx);
#endif/* ETHTSYN_TIME_RECORDING == STD_ON */


  return RetVal;
}

STATIC FUNC(uint16, ETHTSYN_CODE) EthTSyn_GetPTPHeaderSequNumber
(
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPHeaderPtr
)
{
  const uint16 SequNumber
    = (uint16)(((uint16)PTPHeaderPtr[ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1]) << 8U)
      + (uint16)(PTPHeaderPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]);

  return SequNumber;
}

#if((ETHTSYN_MAX_SLAVE != 0U) || (ETHTSYN_SWITCH_USED == STD_ON) || (ETHTSYN_IEEE1588_CONFIGURED == STD_ON))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SubTimeStamps
(
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp_MinuendPtr,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp_SubtrahendPtr,
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp_ResultPtr
)
{
  boolean Borrow;
  boolean Sign;

  Eth_TimeStampType TimeStamp_Minuend = *TimeStamp_MinuendPtr;
  Eth_TimeStampType TimeStamp_Subtrahend = *TimeStamp_SubtrahendPtr;


  Sign = EthTSyn_TimeStamp_IsGreaterOrEqual(&TimeStamp_Minuend, &TimeStamp_Subtrahend);

  if(Sign == FALSE)
  {
    /* Negative */
    Eth_TimeStampType TmpTimeStamp = TimeStamp_Minuend;
    TimeStamp_Minuend = TimeStamp_Subtrahend;
    TimeStamp_Subtrahend = TmpTimeStamp;
  }

  if(TimeStamp_Minuend.nanoseconds >= TimeStamp_Subtrahend.nanoseconds)
  {
    TimeStamp_Minuend.nanoseconds -= TimeStamp_Subtrahend.nanoseconds;
    Borrow = FALSE;
  }
  else
  {
    uint32 DiffNanoSeconds = TimeStamp_Subtrahend.nanoseconds - TimeStamp_Minuend.nanoseconds;
    TimeStamp_Minuend.nanoseconds = (ETHTSYN_NANOSEC_MAX + 1U) - DiffNanoSeconds;
    Borrow = TRUE;
  }

  if(Borrow)
  {
    if(TimeStamp_Minuend.seconds > 0U)
    {
      TimeStamp_Minuend.seconds--;
      Borrow = FALSE;
    }
    else
    {
      TimeStamp_Minuend.seconds = ETHTSYN_32BIT_MAX; /* Set to maximum of 32 bit */
      Borrow = TRUE;
    }
  }

  if(TimeStamp_Minuend.seconds >= TimeStamp_Subtrahend.seconds)
  {
    TimeStamp_Minuend.seconds -= TimeStamp_Subtrahend.seconds;
  }
  else
  {
    uint32 DiffSeconds = TimeStamp_Subtrahend.seconds - TimeStamp_Minuend.seconds;
    TimeStamp_Minuend.seconds = ETHTSYN_32BIT_MAX - DiffSeconds;
    /* Borrow 1 secondHi which equals ETHTSYN_32BIT_MAX + 1.
     * It was necessary to separate +1 in order to avoid type overflow. */
    /* Deviation TASKING-1 */
    /* Deviation TASKING-2 */
    TimeStamp_Minuend.seconds++;
    Borrow = TRUE;
  }

  if(Borrow)
  {
    TimeStamp_Minuend.secondsHi--;
  }

  /* TimeStamp_Minuend.secondsHi is always >= TimeStamp_Subtrahend.secondsHi */
  TimeStamp_Minuend.secondsHi -= TimeStamp_Subtrahend.secondsHi;

  /* Write result. */
  TimeStamp_ResultPtr->sign = Sign;
  TimeStamp_ResultPtr->diff.secondsHi = TimeStamp_Minuend.secondsHi;
  TimeStamp_ResultPtr->diff.seconds = TimeStamp_Minuend.seconds;
  TimeStamp_ResultPtr->diff.nanoseconds = TimeStamp_Minuend.nanoseconds;

}

STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_TimeStamp_IsGreaterOrEqual
(
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp1Ptr,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp2Ptr
)
{
  boolean Sign;


  if(TimeStamp1Ptr->secondsHi > TimeStamp2Ptr->secondsHi)
  {
    Sign = TRUE;
  }
  else if(TimeStamp1Ptr->secondsHi < TimeStamp2Ptr->secondsHi)
  {
    Sign = FALSE;
  }
  /* TimeStamp1Ptr->secondsHi == TimeStamp2Ptr->secondsHi */
  else if(TimeStamp1Ptr->seconds > TimeStamp2Ptr->seconds)
  {
    Sign = TRUE;
  }
  else if(TimeStamp1Ptr->seconds < TimeStamp2Ptr->seconds)
  {
    Sign = FALSE;
  }
  /* TimeStamp1Ptr->secondsHi == TimeStamp2Ptr->secondsHi */
  /* TimeStamp1Ptr->seconds == TimeStamp2Ptr->seconds */
  else if(TimeStamp1Ptr->nanoseconds >= TimeStamp2Ptr->nanoseconds)
  {
    Sign = TRUE; /* TimeStamp1Ptr >= TimeStamp2Ptr */
  }
  else
  {
    Sign = FALSE; /* TimeStamp1Ptr < TimeStamp2Ptr */
  }


  return Sign;
}
#endif /* ((ETHTSYN_MAX_SLAVE != 0U) || (ETHTSYN_SWITCH_USED == STD_ON) || (ETHTSYN_IEEE1588_CONFIGURED == STD_ON)) */

FUNC(void, ETHTSYN_CODE) EthTSyn_AddTimeStamps
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp1Ptr,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStamp2Ptr
)
{
  uint8 Idx;
  uint32 Overflow = 0U;
  uint32 LocalNanosec = TimeStamp2Ptr->nanoseconds;

  for(Idx = 0U; Idx < 4U; Idx++)
  {
    if(TimeStamp1Ptr->nanoseconds > ETHTSYN_NANOSEC_MAX)
    {
      TimeStamp1Ptr->nanoseconds -= ETHTSYN_NANOSEC_MAX + 1U; /* - 1s */
      Overflow++;
    }
    if(LocalNanosec > ETHTSYN_NANOSEC_MAX)
    {
      LocalNanosec -= ETHTSYN_NANOSEC_MAX + 1U; /* - 1s */
      Overflow++;
    }
  }
  /* ANSI C90: A computation involving unsigned operands can
               never overflow, because a result that cannot be represented by the
               resulting unsigned integer type is reduced modulo the number that is
               one greater than the largest value that can be represented by the
               resulting unsigned integer type. */
  TimeStamp1Ptr->nanoseconds += LocalNanosec;

  if(TimeStamp1Ptr->nanoseconds > ETHTSYN_NANOSEC_MAX)
  {
    TimeStamp1Ptr->nanoseconds -= ETHTSYN_NANOSEC_MAX + 1U; /* - 1s */
    TimeStamp1Ptr->seconds++;
  }

  TimeStamp1Ptr->seconds += TimeStamp2Ptr->seconds;

  /* !LINKSTO EthTSyn.EB.Slave_OverflowDetection, 1 */
  if(TimeStamp1Ptr->seconds < TimeStamp2Ptr->seconds) /* Overflow occured */
  {
    TimeStamp1Ptr->secondsHi++;
  }

  TimeStamp1Ptr->seconds += Overflow;
    /* !LINKSTO EthTSyn.EB.Slave_OverflowDetection, 1 */
  if(TimeStamp1Ptr->seconds < Overflow) /* Overflow occured */
  {
    TimeStamp1Ptr->secondsHi++;
  }

  TimeStamp1Ptr->secondsHi += TimeStamp2Ptr->secondsHi;

}

#if (ETHTSYN_MAX_SLAVE != 0U)
STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsSlave
(
  uint8 EthTSynCtrlIdx
)
{
  boolean RetVal;

  if(EthTSynCtrlIdx < ETHTSYN_MAX_SLAVE)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_AddCorrField
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) CorrectionFieldArray,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
)
{
  uint16 Idx;
  uint16 CorrFieldHi_ns;
  Eth_TimeStampType NsTimeStamp;
  uint16 RemainingCorrFieldHi_ns;
  Eth_TimeStampType CorrFieldHi_TS;
  Std_ReturnType RetVal = E_NOT_OK;

  CorrFieldHi_ns = (uint16)(((uint16) CorrectionFieldArray[0U]) << 8U);
  CorrFieldHi_ns += CorrectionFieldArray[1U];

  NsTimeStamp.nanoseconds = (uint32)(((uint32) CorrectionFieldArray[2U]) << 24U);
  NsTimeStamp.nanoseconds |= (uint32)(((uint32) CorrectionFieldArray[3U]) << 16U);
  NsTimeStamp.nanoseconds |= (uint32)(((uint32) CorrectionFieldArray[4U]) << 8U);
  NsTimeStamp.nanoseconds |= CorrectionFieldArray[5U];
  NsTimeStamp.seconds = 0U;
  NsTimeStamp.secondsHi = 0U;
  /* Save CorrectionField to be reported to StbM for time recording */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  {
    uint64 CorrValue = 0U;

    CorrValue =  (uint64)(((uint64) CorrectionFieldArray[0U]) << 56U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[1U]) << 48U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[2U]) << 40U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[3U]) << 32U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[4U]) << 24U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[5U]) << 16U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[6U]) << 8U);
    CorrValue |= (uint64)((uint64) CorrectionFieldArray[7U]);

    EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.correctionField = (sint64)CorrValue;
  }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
  /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_NegativeCorrectionField, 1 */
  if((CorrFieldHi_ns > ETHTSYN_16BIT_MASK_BIT15) || /* Check if Correction Field is negative. */
      (
        /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_MaxValues_NsTimeStamp_CorrFieldHi, 1 */
        /* Invalid value detected (See 802.1AS-2011 Ch 11.4.2.4) */
        (ETHTSYN_16BIT_SIGNED_MAX == CorrFieldHi_ns) &&
        (ETHTSYN_32BIT_MAX == NsTimeStamp.nanoseconds)
      )
    )
  {
    RetVal = E_NOT_OK;
  }
  else
  {
    if(CorrFieldHi_ns >= EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_ns)
    {
      /* Speed optimization: Add last converted values and only convert delta. */
      CorrFieldHi_TS = EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_TS;

      RemainingCorrFieldHi_ns = CorrFieldHi_ns - EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_ns;
    }
    else
    {
      RemainingCorrFieldHi_ns = CorrFieldHi_ns;

      CorrFieldHi_TS.nanoseconds = 0U;
      CorrFieldHi_TS.seconds = 0U;
      CorrFieldHi_TS.secondsHi = 0U;
    }

    /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_RemainingCorrFieldHi_Ns_NotZero, 1 */
    /* Convert the remaining higher 15 bits (signed) of 48bit ns into  time stamp. */
    for(Idx = 0U; Idx < 15U; Idx++)
    {
      if(RemainingCorrFieldHi_ns == 0U)
      {
        /* Calculation finished for this CorrFieldHi_ns */
        break;
      }
      if((RemainingCorrFieldHi_ns & 0x0001U) == 1U)
      {
        EthTSyn_AddTimeStamps(&CorrFieldHi_TS, &EthTSyn_NsArrayConversionTable[Idx]);
      }

      RemainingCorrFieldHi_ns >>= 1U;
    }

    EthTSyn_AddTimeStamps(TimeStampPtr, &CorrFieldHi_TS);

    /* Store CorrFieldHi_ns for next function call. */
    EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_ns = CorrFieldHi_ns;
    /* Store calculated time stamp value corresponding to CorrFieldHi_ns. */
    EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_TS = CorrFieldHi_TS;

    /* Add ns part of correction field */
    /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_NsPart_Of_CorrField, 1 */
    /* !LINKSTO EthTSyn.EB.Nanoseconds.CorrectionTime, 1 */
    if(NsTimeStamp.nanoseconds > ETHTSYN_NANOSEC_MAX)
    {
      NsTimeStamp.seconds += NsTimeStamp.nanoseconds / (ETHTSYN_NANOSEC_MAX + 1U);
      NsTimeStamp.nanoseconds %= (ETHTSYN_NANOSEC_MAX + 1U);
    }

    EthTSyn_AddTimeStamps(TimeStampPtr, &NsTimeStamp);

    RetVal = E_OK;
  }

  return RetVal;
}
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SavePTPCorrField
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) CorrectionFieldArray,
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
)
{
  uint16 Idx;
  uint16 CorrFieldHi_ns;
  Eth_TimeStampType NsTimeStamp;
  uint16 RemainingCorrFieldHi_ns;
  Eth_TimeStampType CorrFieldHi_TS;
  Std_ReturnType RetVal = E_NOT_OK;

  TimeStampPtr->diff.nanoseconds = 0U;
  TimeStampPtr->diff.seconds = 0U;
  TimeStampPtr->diff.secondsHi = 0U;
  TimeStampPtr->sign = FALSE;

  CorrFieldHi_ns = (uint16)(((uint16) CorrectionFieldArray[0U]) << 8U);
  CorrFieldHi_ns += CorrectionFieldArray[1U];

  NsTimeStamp.nanoseconds = (uint32)(((uint32) CorrectionFieldArray[2U]) << 24U);
  NsTimeStamp.nanoseconds |= (uint32)(((uint32) CorrectionFieldArray[3U]) << 16U);
  NsTimeStamp.nanoseconds |= (uint32)(((uint32) CorrectionFieldArray[4U]) << 8U);
  NsTimeStamp.nanoseconds |= CorrectionFieldArray[5U];
  NsTimeStamp.seconds = 0U;
  NsTimeStamp.secondsHi = 0U;
  /* Save CorrectionField to be reported to StbM for time recording */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  {
    uint64 CorrValue = 0U;

    CorrValue =  (uint64)(((uint64) CorrectionFieldArray[0U]) << 56U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[1U]) << 48U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[2U]) << 40U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[3U]) << 32U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[4U]) << 24U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[5U]) << 16U);
    CorrValue |= (uint64)(((uint64) CorrectionFieldArray[6U]) << 8U);
    CorrValue |= (uint64)((uint64) CorrectionFieldArray[7U]);

    EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.correctionField = (sint64)CorrValue;
  }
#else
  TS_PARAM_UNUSED(EthTSynCtrlIdx);
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
  if(
      /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_MaxValues_NsTimeStamp_CorrFieldHi, 1 */
      /* Invalid value detected (See IEEE1588_V2 Ch 13.3.2.9) */
      (ETHTSYN_16BIT_SIGNED_MAX == CorrFieldHi_ns) &&
      (ETHTSYN_32BIT_MAX == NsTimeStamp.nanoseconds)
    )
  {
    RetVal = E_NOT_OK;
  }
  else
  {
    /* Extract the correction sign. */
    boolean Sign = ((CorrFieldHi_ns & ETHTSYN_16BIT_MASK_BIT15) >> 15U);
    RemainingCorrFieldHi_ns = CorrFieldHi_ns;

    CorrFieldHi_TS.nanoseconds = 0U;
    CorrFieldHi_TS.seconds = 0U;
    CorrFieldHi_TS.secondsHi = 0U;


    /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_RemainingCorrFieldHi_Ns_NotZero, 1 */
    /* Convert the remaining higher 15 bits (signed) of 48bit ns into  time stamp. */
    for(Idx = 0U; Idx < 15U; Idx++)
    {
      if(RemainingCorrFieldHi_ns == 0U)
      {
        /* Calculation finished for this CorrFieldHi_ns */
        break;
      }
      if((RemainingCorrFieldHi_ns & 0x0001U) == 1U)
      {
        EthTSyn_AddTimeStamps(&CorrFieldHi_TS, &EthTSyn_NsArrayConversionTable[Idx]);
      }

      RemainingCorrFieldHi_ns >>= 1U;
    }

    EthTSyn_AddTimeStamps(&(TimeStampPtr->diff), &CorrFieldHi_TS);

    /* Add ns part of correction field */
    /* !LINKSTO EthTSyn.EB.Slave.AddCorrField_NsPart_Of_CorrField, 1 */
    /* !LINKSTO EthTSyn.EB.Nanoseconds.CorrectionTime, 1 */
    if(NsTimeStamp.nanoseconds > ETHTSYN_NANOSEC_MAX)
    {
      NsTimeStamp.seconds += NsTimeStamp.nanoseconds / (ETHTSYN_NANOSEC_MAX + 1U);
      NsTimeStamp.nanoseconds %= (ETHTSYN_NANOSEC_MAX + 1U);
    }

    EthTSyn_AddTimeStamps(&(TimeStampPtr->diff), &NsTimeStamp);
    /* !LINKSTO EthTSyn.EB.Slave.NegativeCorrectionField, 1 */
    if(Sign == 0U)
    {
      /* If the sign bit is 0, a positive correction is received.*/
      TimeStampPtr->sign = TRUE;
    }
    else
    {
      /* If the sign bit is 1, a negative correction is received.*/
      TimeStampPtr->sign = FALSE;
    }


    RetVal = E_OK;
  }

  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CorrField2PTPHeader
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) OriginTimeStampPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) EgressTimeStampPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_TimeIntDiffType TimeCorrection;

  /* Correction field shall contain the difference between
   calculated origintimestamp and sync egress time stamp */
  EthTSyn_SubTimeStamps(
                         OriginTimeStampPtr,
                         EgressTimeStampPtr,
                         &TimeCorrection /* (OTS - Egress) */
                       );

  /* If secHi is bigger than 0 the correctionfield will exceed the max allowed
     value ETHTSYN_MAX_SIGNED_CORRECTIONFIELD. */
  if(
      (TimeCorrection.diff.secondsHi == 0U) &&
      (
        (
          (TimeCorrection.diff.nanoseconds <= ETHTSYN_MAX_NANOSECONDS_CORRECTIONFIELD_VALUE ) &&
          (TimeCorrection.diff.seconds == ETHTSYN_MAX_SECONDS_CORRECTIONFIELD_VALUE)
        ) ||
        (
          (TimeCorrection.diff.nanoseconds <= ETHTSYN_NANOSEC_MAX) &&
          (TimeCorrection.diff.seconds < ETHTSYN_MAX_SECONDS_CORRECTIONFIELD_VALUE)
        )
      )
    )
  {
    uint64 NsValue = 0U;
    NsValue = EthTSyn_Umul32_64(TimeCorrection.diff.seconds, (ETHTSYN_NANOSEC_MAX + 1U));
    NsValue += TimeCorrection.diff.nanoseconds;
    /* !LINKSTO EthTSyn.EB.PTPE2EcalculateCorrection, 1 */
    BufPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0] = (uint8)((NsValue >> 48U) & 0xFFU);
    BufPtr[ETHTSYN_PTP_HEADER_B9_CORRFIELD_1] = (uint8)((NsValue >> 32U) & 0xFFU);
    /* ns integer part */
    BufPtr[ETHTSYN_PTP_HEADER_B10_CORRFIELD_2] = (uint8)((NsValue >> 24U) & 0xFFU);
    BufPtr[ETHTSYN_PTP_HEADER_B11_CORRFIELD_3] = (uint8)((NsValue >> 16U) & 0xFFU);
    BufPtr[ETHTSYN_PTP_HEADER_B12_CORRFIELD_4] = (uint8)((NsValue >>  8U) & 0xFFU);
    BufPtr[ETHTSYN_PTP_HEADER_B13_CORRFIELD_5] = (uint8)((NsValue       ) & 0xFFU);
    if(TimeCorrection.sign == FALSE)
    {
       /* !LINKSTO EthTSyn.EB.PTPE2EnegativeCorrection, 1 */
      /* If the value is negative we need to update the sign bit */
      BufPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0] |= 0x80U;
    }
    RetVal = E_OK;
  }
  return RetVal;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleCorrections
(
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) DelayValue,
  P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) CorrectionValue
)
{
  Eth_TimeStampType TimeStamp_Delay = DelayValue->diff;
  Eth_TimeIntDiffType TimeStamp_Correction = *CorrectionValue;
  Eth_TimeIntDiffType ResultedTimestamp;

  if(TimeStamp_Correction.sign == FALSE)
  {
    /* Value must be added */
    EthTSyn_AddTimeStamps(&TimeStamp_Delay, &TimeStamp_Correction.diff);
    ResultedTimestamp.diff = TimeStamp_Delay;
    /* Adding two positive numbers will always result in a positive sign. */
    ResultedTimestamp.sign = TRUE;
  }
  else
  {
    /* If TimeStamp2 is positive, check if is lower than the calculated Delay.
       If TRUE the substraction can be done.*/
    /* Delay - CorrectionValue */
    EthTSyn_SubTimeStamps(
                   &TimeStamp_Delay,
                   &TimeStamp_Correction.diff,
                   &ResultedTimestamp
                 );
  }
  /* Write result. */
  DelayValue->sign = ResultedTimestamp.sign;
  DelayValue->diff.secondsHi = ResultedTimestamp.diff.secondsHi;
  DelayValue->diff.seconds = ResultedTimestamp.diff.seconds;
  DelayValue->diff.nanoseconds = ResultedTimestamp.diff.nanoseconds;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_UpdateDelayValues
(
  uint8 EthTSynCtrlIdx,
  Eth_TimeStampType OriginTimeStamp,
  Eth_TimeIntDiffType FupCorrection
)
{
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectedSyncCorrection = EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectionSyncFupCorrection = EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t1 = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t2 = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2;
  /* !LINKSTO EthTSyn.EB.PTPE2EDelaySyncFupSaveT1T2, 1 */
  /* If PTP with E2E delay calculation is enabled for this timedomain, we need to save the T1 and T2 timestamps. */
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1 = OriginTimeStamp;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2 = EthTSyn_Slave[EthTSynCtrlIdx].Sync_ActualIngressTimeStamp;
  /* The correction of the Sync is needed on the calculation of the delay. */
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection = EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection;
  /* The correction of the Fup is needed on the calculation of the delay. */
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection = FupCorrection;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SubCorrE2EMechanism
(
  uint8 EthTSynCtrlIdx,
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampCorrDiff,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) OriginTimeStampPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_TimeIntDiffType TimeStampDiff;
  Eth_TimeStampType CalculatedTimestamp = *OriginTimeStampPtr;
  Eth_TimeIntDiffType PTPFupCorrection = *TimeStampCorrDiff;

  ETH_TIMESTAMP_DIFF_INIT(TimeStampDiff);
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
  {
    /* correctedMasterEventTimestamp = preciseOriginTimestamp + meanDelay + correctedSyncCorrectionField
       + correctionField of Follow_Up message. */
    if(EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.sign == FALSE)
    {
      /* OriginTimeStamp - synccorrectionField + Pdelay */
      EthTSyn_SubTimeStamps(
                     &CalculatedTimestamp, /* OriginTimeStamp + MeanDelay + (T2 - T1) */
                     &EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.diff, /* received sync correction */
                     &TimeStampDiff
                   );
      if(TimeStampDiff.sign == FALSE)
      {
        /* If the difference is negative the time shall not be passed to the StbM. */
        RetVal = E_NOT_OK;
      }
      else
      {
        /* Save the calculated value. */
        CalculatedTimestamp = TimeStampDiff.diff;
        RetVal = E_OK;
      }

    }
    else
    {
     /* OriginTimeStamp + SynccorrectionField + MeanDelay + (T2 - T1) */
      EthTSyn_AddTimeStamps(
                 &CalculatedTimestamp,  /* OriginTimeStamp + MeanDelay + (T2 - T1) */
                 &EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.diff /* received sync correction */
               );
      RetVal = E_OK;
    }

    if(RetVal == E_OK)
    {
      if(PTPFupCorrection.sign == FALSE)
      {
        /* OriginTimeStamp - correctionField + MeanDelay */
        EthTSyn_SubTimeStamps(
                       &CalculatedTimestamp, /* OriginTimeStamp + correctedSyncCorrectionField + MeanDelay + (T2 - T1) */
                       &PTPFupCorrection.diff, /* received Fup correction */
                       &TimeStampDiff
                     );
        if(TimeStampDiff.sign == FALSE)
        {
          /* If the difference is negative the time shall not be passed to the StbM. */
          RetVal = E_NOT_OK;
        }
        else
        {
          /* Save the calculated value. */
          CalculatedTimestamp = TimeStampDiff.diff;
          RetVal = E_OK;
        }
      }
      else
      {
        /* OriginTimeStamp + correctedSyncCorrectionField + MeanDelay + (T2 - T1) + correctionField */
        EthTSyn_AddTimeStamps(
                   &CalculatedTimestamp,  /* OriginTimeStamp + correctedSyncCorrectionField + MeanDelay + (T2 - T1) */
                   &PTPFupCorrection.diff /* received correction */
                 );
        RetVal = E_OK;
      }
    }

    if(RetVal == E_OK)
    {
      /* Update the origintimestamp. */
      OriginTimeStampPtr->nanoseconds = CalculatedTimestamp.nanoseconds;
      OriginTimeStampPtr->seconds     = CalculatedTimestamp.seconds;
      OriginTimeStampPtr->secondsHi   = CalculatedTimestamp.secondsHi;
    }
  }
  else
  {
    /* If PTP with E2E mechanism is not enabled for this TD, no need to do any calculation.*/
    RetVal = E_OK;
  }
  return RetVal;
}

STATIC FUNC(uint32, STBM_CODE) EthTSyn_Umul32_hi
(
  uint32 a,
  uint32 b
)
{
  /* split operands into halves */
  uint32 al = (uint16)a;
  uint32 ah = a >> 16;
  uint32 bl = (uint16)b;
  uint32 bh = b >> 16;
  /* compute partial products */
  uint32 p0 = al * bl;
  uint32 p1 = al * bh;
  uint32 p2 = ah * bl;
  uint32 p3 = ah * bh;
  /* sum partial products */
  uint32 cy = ((p0 >> 16) + (uint16)p1 + (uint16)p2) >> 16;
  uint32 rhi = p3 + (p2 >> 16) + (p1 >> 16) + cy;

  return rhi;
}

STATIC FUNC(void, STBM_CODE) EthTSyn_Umul32_Wide
(
  uint32 a,
  uint32 b,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rhi,
  P2VAR(uint32, AUTOMATIC, STBM_VAR) rlo
)
{

  /* bits <31:0> of the product a * b */
  *rlo = a * b;
  /* bits <63:32> of the product a * b */
  *rhi = EthTSyn_Umul32_hi (a, b);

}

STATIC FUNC(uint64, STBM_CODE) EthTSyn_Umul32_64
(
  uint32 a,
  uint32 b
)
{
  uint32 hi, lo;
  uint64 product;


  EthTSyn_Umul32_Wide(a, b, &hi, &lo);

  product = (uint64)(((uint64)hi << 32) | lo);

  return product;
}
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_CalculatePdelay
(
  uint8 EthTSynCtrlIdx
)
{
  /* !LINKSTO EthTSyn.PRS_TS_00059, 1 */
  uint32 ActualPdelay = 0U;
  boolean UpdatePdelay = FALSE;
  Eth_TimeStampType TimeStamp_t1;
  Eth_TimeStampType TimeStamp_t2;
  Eth_TimeStampType TimeStamp_t3;
  Eth_TimeStampType TimeStamp_t4;
  Eth_TimeIntDiffType TimeStampDiffT4T1;
  Eth_TimeIntDiffType TimeStampDiffT3T2;
  Eth_TimeIntDiffType PdelayDiff;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  Eth_TimeIntDiffType SyncFrameCorrection;
  Eth_TimeIntDiffType FupFrameCorrection;
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
  /* Init Variables */
  ETH_TIMESTAMP_DIFF_INIT(TimeStampDiffT4T1);
  ETH_TIMESTAMP_DIFF_INIT(TimeStampDiffT3T2);
  ETH_TIMESTAMP_DIFF_INIT(PdelayDiff);
  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

  TimeStamp_t1 = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1;
  TimeStamp_t2 = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2;
  TimeStamp_t3 = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3;
  TimeStamp_t4 = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  SyncFrameCorrection = EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection;
  FupFrameCorrection = EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection;
#endif

  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
  {
    boolean SignT1gtT4 = FALSE;
    boolean SignT2gtT3 = FALSE;
    /* If PTP with E2E mechanism is used, check that valid timestamps are received.
       If the sign is TRUE, it means that the Sync was received after the Delay_Req was transmitted.*/
    SignT1gtT4 = EthTSyn_TimeStamp_IsGreaterOrEqual(&TimeStamp_t1,
                                               &TimeStamp_t4);
    /* If PTP with E2E mechanism is used, check that valid timestamps are received. */
    SignT2gtT3 = EthTSyn_TimeStamp_IsGreaterOrEqual(&TimeStamp_t2,
                                               &TimeStamp_t3);
    if((SignT1gtT4 == TRUE) || (SignT2gtT3 == TRUE))
    {
      /* !LINKSTO EthTSyn.EB.UseBackupValues, 1 */
      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

      /* Use the backup values for calculation of the delay.*/
      TimeStamp_t1 = EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t1;
      TimeStamp_t2 = EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t2;
      SyncFrameCorrection = EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectedSyncCorrection;
      FupFrameCorrection = EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectionSyncFupCorrection;

      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
    }
  }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
  EthTSyn_SubTimeStamps(
                         &TimeStamp_t4,
                         &TimeStamp_t1,
                         &TimeStampDiffT4T1 /* (t4 - t1) */
                       );

  EthTSyn_SubTimeStamps(
                         &TimeStamp_t3,
                         &TimeStamp_t2,
                         &TimeStampDiffT3T2 /* (t3 - t2) */
                       );

  /* !LINKSTO EthTSyn.EB.PdelayResp_NegativeTimeOffset, 1 */
  if((FALSE == TimeStampDiffT4T1.sign) || (FALSE == TimeStampDiffT3T2.sign))
  {
    UpdatePdelay = FALSE;
  }
  /* !LINKSTO EthTSyn.EB.TimeDiff_InvalidTime, 1 */
  else if((0U != TimeStampDiffT4T1.diff.secondsHi) || (0U != TimeStampDiffT3T2.diff.secondsHi))
  {
    UpdatePdelay = FALSE;
  }
  /* !LINKSTO EthTSyn.EB.TimeDiff_InvalidTime, 1 */
  else if((0U != TimeStampDiffT4T1.diff.seconds) || (0U != TimeStampDiffT3T2.diff.seconds))
  {
    UpdatePdelay = FALSE;
  }
  /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
  else
  {
    EthTSyn_SubTimeStamps(
                           &TimeStampDiffT4T1.diff, /* T4 - T1 */
                           &TimeStampDiffT3T2.diff, /* T3 - T2 */
                           &PdelayDiff /* (T4 - T1) - (T3 - T2) */
                         );
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    if((EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE) && (TRUE == PdelayDiff.sign))
    {
      /* If E2E mechanism is used, additional operations must be performed.*/
      Eth_TimeIntDiffType TempDelay = PdelayDiff;
      /* (T4 - T1) - (T3 - T2) - correctedSyncCorrectionField*/
      EthTSyn_HandleCorrections
      (
        &TempDelay,
        &SyncFrameCorrection
      );

      if(TempDelay.sign == TRUE)
      {
        /* (T4 - T1) - (T3 - T2) - correctedSyncCorrectionField - correctionField of Follow_Up message */
        EthTSyn_HandleCorrections
        (
          &TempDelay,
          &FupFrameCorrection
        );
        if(TempDelay.sign == TRUE)
        {
          /* (T4 - T1) - (T3 - T2) - correctedSyncCorrectionField - correctionField of Follow_Up message -
              correctionField of Delay_Resp message*/
          EthTSyn_HandleCorrections
          (
            &TempDelay,
            &EthTSyn_Slave[EthTSynCtrlIdx].CorrectionDelayRespCorrection
          );
        }
      }
      /* Update the calculated Pdelay. */
      PdelayDiff = TempDelay;
    }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    /* !LINKSTO EthTSyn.EB.TransparentClock_PdelayCalculation, 1 */
    ActualPdelay = PdelayDiff.diff.nanoseconds / 2U;
    /* !LINKSTO EthTSyn.PRS_TS_00154, 1 */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayLatencyThreshold >= ActualPdelay)
    {
      /* Check if Pdelay measurement is within expected range and valid. */
      /* !LINKSTO EthTSyn.EB.PdelayRespFU_NegativeTimeOffset, 1 */
      if(FALSE == PdelayDiff.sign) /* Pdelay must be positive. */
      {
        UpdatePdelay = FALSE;
      }
      else if(0U == EthTSyn_Slave[EthTSynCtrlIdx].Pdelay)
      {
        EthTSyn_Slave[EthTSynCtrlIdx].Pdelay = ActualPdelay; /* Init Pdelay */
        UpdatePdelay = FALSE; /* No need to update */
      }
      else
      {
        UpdatePdelay = TRUE;
      }
    }
  }

  /* Pdelay calculation: Add a fraction of delta to actual Pdelay. */
  if(UpdatePdelay)
  {
    uint32 Delta;
    const uint8 DeltaShift = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].FilterDeltaShift;

    if(ActualPdelay > EthTSyn_Slave[EthTSynCtrlIdx].Pdelay)
    {
      /* !LINKSTO EthTSyn.EB.Slave.PdelayFilter.Disabled, 1 */
      Delta = ActualPdelay - EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
      EthTSyn_Slave[EthTSynCtrlIdx].Pdelay += (uint32) (Delta >> DeltaShift);
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.Slave.PdelayFilter.Enabled, 1 */
      Delta = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay - ActualPdelay;
      EthTSyn_Slave[EthTSynCtrlIdx].Pdelay -= (uint32) (Delta >> DeltaShift);
    }
  }

#if(ETHTSYN_TIME_RECORDING == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
  {
    EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.pdelay = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
    /* Set the recorded timing measurement data for a pdelay of the
     *  corresponding Synchronized Time Base on Time Master */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00221, 1 */
    (void)StbM_EthSetPdelayInitiatorData
        (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00222, 1 */
            &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording
        );
  }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  /* If a TAB is configured, check if the timevalidation is enabled for the slave port. */
  else if (EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].TimeValidationEnabled == TRUE)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00060, 1 */
    EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.pdelay = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
    /* requestReceiptTimeStamp as received in pdelay_Response message */
    EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
        seconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.seconds;
    EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
        nanoseconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.nanoseconds;
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */

    /* responseOriginTimeStamp as received in pdelay_Response_Follow_Up */
    EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseOriginTimestamp.seconds
        =  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.seconds;
    EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseOriginTimestamp.
        nanoseconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.nanoseconds;

    /* Set the recorded timing measurement data for a pdelay of the
     *  corresponding Synchronized Time Base on Time Master */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00221, 1 */
    (void)StbM_EthSetPdelayInitiatorData
        (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00222, 1 */
            &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording
        );
  }
  else
  {
    /* Nothing to do */
  }
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
#endif
}
#endif /* ETHTSYN_MAX_SLAVE != 0U */

#if (ETHTSYN_MAX_SLAVE != 0U)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_SlaveVar
(
  uint8 EthTSynCtrlIdx
)
{
#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)
  uint8 Idx = 0U;
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRefTimbaseId != 0xFFU)
  {
    uint8 Index;
    /* CHECK: NOPARSE */
    /* Search from which timedomain the Pdelay will be used. */
    /* False condition is unreachable because the 'break' will always happen before reaching
       the case when Index > MaxEthTSynSlaveIdx. Both 'if' cases inside for loop are covered by tests. */
    for(Index = 0U; Index < EthTSyn_RootCfgPtr->MaxEthTSynSlaveIdx; Index++)
    {
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRefTimbaseId ==
                        EthTSyn_RootCfgPtr->EthTSynCtrl[Index].TimeBaseId)
      {
        EthTSyn_Slave[EthTSynCtrlIdx].RemotePDelay = &EthTSyn_Slave[Index].Pdelay;
        break;
      }
    }
    /* CHECK: PARSE */
  }
  else
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00006, 1 */
    /* !LINKSTO EthTSyn.EB.EthTSyn_00008, 1 */
    /* !LINKSTO EthTSyn.PRS_TS_00140, 1 */
    /* !LINKSTO EthTSyn.EB.EthTSyn_00010, 1 */
    /* !LINKSTO EthTSyn.PRS_TS_00142, 1 */
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay =
      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DefaultPdelayNs;
    EthTSyn_Slave[EthTSynCtrlIdx].RemotePDelay = NULL_PTR;
  }
  /* LastCorrFieldHi_ns = maximum will be treated as invalid in the calculation. */
  EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_ns = ETHTSYN_16BIT_MAX;
  EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_TS.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_TS.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].LastCorrFieldHi_TS.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived = FALSE;
  /* !LINKSTO EthTSyn.PRS_TS_00199_SkipCheckSCounterAfterInit, 1 */
  EthTSyn_Slave[EthTSynCtrlIdx].CheckSeqCounter = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs = 0U;
  EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);

  EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt.nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].T1Vlt.nanosecondsHi = 0U;

  EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt.nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt.nanosecondsHi = 0U;

  /* SyncReceptionDelay */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay.nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay.nanosecondsHi = 0U;
#if((ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DET) || \
    (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) || \
    ((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)))

  EthTSyn_Init_SlaveVarErr(EthTSynCtrlIdx);

#endif
#if (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  /* !LINKSTO EthTSyn.EB.Diagnostic_EthTSynReceiveSyncFupPairsPeriod, 1 */
  EthTSyn_Slave[EthTSynCtrlIdx].BridgeLastSyncSentTime = 0U;
#endif
  /* If EthTSynTimeRecording is set to True */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  /* Detailed data for time validation of the Time Slave on Ethernet */
  /* Sequence Id of received Sync frame */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sequenceId = 0U;
  /* SourcePortId from received Sync frame */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.portNumber = 0U;
  /* Ingress timestamp of Sync frame converted to Virtual Local Time */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.syncIngressTimestamp.nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.syncIngressTimestamp.nanosecondsHi = 0U;
  /* PreciseOriginTimestamp taken from the received Follow_Up frame */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.preciseOriginTimestamp.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.preciseOriginTimestamp.seconds = 0U;
  /* CorrectionField taken from the received Follow_Up frame */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.correctionField = 0;
  /* Currently valid pDelay value */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.pDelay = 0U;
  /* SyncLocal Time Tuple (Virtual Local Time part) */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.referenceLocalTimestamp.nanosecondsLo
                                                                                            = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.referenceLocalTimestamp.nanosecondsHi
                                                                                            = 0U;
  /* SyncLocal Time Tuple (Global Time part) */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.referenceGlobalTimestamp.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.referenceGlobalTimestamp.seconds = 0U;

  /* Detailed timing data for the pDelay Initiator */
  /* Sequence Id of sent Pdelay_Req frame */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.sequenceId = 0U;
  /* SourcePortId of sent Pdelay_Req frame */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.portNumber = 0U;
  /* SourcePortId of sent Pdelay_Resp frame */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.portNumber = 0U;
  /* Egress timestamp of Pdelay_Req in Virtual Local Time */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestOriginTimestamp.
                                                                              nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestOriginTimestamp.
                                                                              nanosecondsHi = 0U;
  /* Ingress timestamp of Pdelay_Resp in Virtual Local Time */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseReceiptTimestamp.
                                                                              nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseReceiptTimestamp.
                                                                              nanosecondsHi = 0U;

  /* Ingress timestamp of Pdelay_Req in Global Time taken from the received Pdelay_Resp */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
                                                                               nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
                                                                               seconds = 0U;

  /* Egress timestamp of Pdelay_Resp in Global Time taken from the
     received Pdelay_Resp_Follow_Up */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseOriginTimestamp.
                                                                               nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseOriginTimestamp.
                                                                               seconds = 0U;
  /* Value of the Virtual Local Time of the reference Global Time Tuple */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceLocalTimestamp.
                                                                              nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceLocalTimestamp.
                                                                              nanosecondsHi = 0U;
  /* Value of the local instance of the Global Time of the reference Global Time Tuple */
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceGlobalTimestamp.
                                                                               nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceGlobalTimestamp.
                                                                               seconds = 0U;
#endif

#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.sign = FALSE;
  /* Boundary clock transmit sync frames . */
  EthTSyn_Slave[EthTSynCtrlIdx].TriggerTxOnBridge = FALSE;
#endif
#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)
  EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsIndex;
  for(Idx = 0U;Idx < ETHTSYN_OFSTIMEBASES_CONFIGURED; Idx++)
  {
    /* Reset the offset values.*/
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeDomId = 0xFFU;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.secondsHi = 0U;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.seconds = 0U;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.nanoseconds = 0;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.timeBaseStatus = 0xFFU;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userByte0 = 0xFFU;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userByte1 = 0xFFU;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userByte2 = 0xFFU;
    EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userDataLength = 0xFFU;
  }
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  /* In order to avoid a violation of Code-Metric Rule HIS_VOCF,
     split the initialization of the PTP variables. */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].SyncCorrection.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectedSyncCorrection.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionSyncFupCorrection.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionDelayRespCorrection.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionDelayRespCorrection.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionDelayRespCorrection.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].CorrectionDelayRespCorrection.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncFupReceived = FALSE;
  EthTSyn_Init_PTPIEEE1588_BckpVars(EthTSynCtrlIdx);
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
#if(ETHTSYN_ICV_USED == STD_ON)
  EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
#endif /* ETHTSYN_ICV_USED == STD_ON */
}

#if((ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DET) || \
    (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) || \
    ((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_SlaveVarErr
(
  uint8 EthTSynCtrlIdx
)
{
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
  EthTSyn_Slave[EthTSynCtrlIdx].SyncFupDroppedPairsCt = 0U;
#endif
#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DET)
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayRespFupDroppedPairsCt = 0U;
#endif
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  /* !LINKSTO EthTSyn.EB.Diagnostic_EthTSynReceiveSyncFupPairsPeriod, 1 */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout =
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].ReceiveSyncFupPairTimeout;
#endif

#if((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON))
  TS_MemBZero(
               &EthTSyn_Slave[EthTSynCtrlIdx].Sync_Rx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
  EthTSyn_Slave[EthTSynCtrlIdx].SaveSrcPortId = TRUE;
#endif /* (ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */
}
#endif
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_PTPIEEE1588_BckpVars
(
  uint8 EthTSynCtrlIdx
)
{
  /* Used if E2E mechanism is enabled. */
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectedSyncCorrection.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectedSyncCorrection.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectedSyncCorrection.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectedSyncCorrection.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectionSyncFupCorrection.diff.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectionSyncFupCorrection.diff.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectionSyncFupCorrection.diff.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].BackupCorrectionSyncFupCorrection.sign = FALSE;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t1.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t1.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t1.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t2.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t2.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Backup_Delay_TimeStamp_t2.secondsHi = 0U;
}
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ResetSlavePdelayData
(
  uint8 EthTSynCtrlIdx
)
{
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == FALSE)
  {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    /* If IEEE1588_V2 is used, this values should be reset only if gPTP mechanism is used.*/
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1.nanoseconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1.seconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t1.secondsHi = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.nanoseconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.seconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.secondsHi = 0U;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t3.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].PdelayFollowUpTimeout = 0xFFFFFFFFU;
  TS_AtomicAssign8
  (
      EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
      ETHTSYN_PDELAY_CALCULATION_IDLE
  );
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  EthTSyn_Inc02_ResetPortPdelayVars(EthTSynCtrlIdx);
#endif
}

#if(ETHTSYN_ICV_USED == STD_ON)
/**
 * \brief Initialize all relevant time auth slave variables.
 *
 * \param[in] EthTSynCtrlIdx - Index of the EthTSyn controller.
 *
 */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_IcvSubTlvData
(
  uint8 EthTSynCtrlIdx
)
{

  EthTSyn_Slave[EthTSynCtrlIdx].VirtualTimeToBePassed2StbM.nanosecondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].VirtualTimeToBePassed2StbM.nanosecondsLo = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].TimeToBePassed2StbM.nanoseconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].TimeToBePassed2StbM.seconds = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].TimeToBePassed2StbM.secondsHi = 0U;


  EthTSyn_Slave[EthTSynCtrlIdx].MeasureDataToBePassed2StbM.pathDelay = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.secondsHi = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].UserDataToBePassed2StbM.userDataLength = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].UserDataToBePassed2StbM.userByte0 = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].UserDataToBePassed2StbM.userByte1 = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].UserDataToBePassed2StbM.userByte2 = 0U;

  EthTSyn_Slave[EthTSynCtrlIdx].IcvVerificationTimeout = 0xFFFFFFFFU;
  EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueLength = 0U;
  /* !LINKSTO EthTSyn.EB.EthTSyn_VerifyAttempts_StbM, 1 */
  EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].ReceivedIcvLength = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].ReceivedFvLength = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].StartOfTimeAuthTlv = 0U;
  EthTSyn_Slave[EthTSynCtrlIdx].VerificationResult = CRYPTO_E_VER_NOT_OK;
  EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction = 0U;
  TS_AtomicSetBit_8
  (
    &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
    ETHTSYN_AUTH_VERIFICATION_IDLE
  );
  TS_MemBZero(&EthTSyn_Slave[EthTSynCtrlIdx].BufferSubTlv[0U], ETHTSYN_SYNCFUP_RECEIVE_FRAME_MAX_SIZE_ALL_TLVS);
  TS_MemBZero(&EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueReceived[0U], ETHTSYN_SYNCFUP_MAX_SIZE_FV);
  TS_MemBZero(&EthTSyn_Slave[EthTSynCtrlIdx].FreshnessValueStbM[0U], ETHTSYN_SYNCFUP_MAX_SIZE_FV);
  TS_MemBZero(&EthTSyn_Slave[EthTSynCtrlIdx].BufferReceivedIcv[0U], ETHTSYN_MAX_TIMEAUTH_ICV_LENGTH);
}


STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleICV
(
  uint8 EthTSynCtrlIdx
)
{
  if(
      (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationTimeout > 0U) &&
      ((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_WAIT_INDICATION_MASK) != FALSE)
    )
  {
    if(0U == EthTSyn_Slave[EthTSynCtrlIdx].IcvVerificationTimeout)
    {
      /* Drop fup message */
      EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction = 0U;
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00245, 1 */
      /* If the generation of Icv fails, frame can be updated accordingly
         and transmitted on the next mainfunction()*/
      TS_AtomicSetBit_8
       (&EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction, ETHTSYN_AUTH_VERIFICATION_FAILED);
    }
    else
    {
      EthTSyn_Slave[EthTSynCtrlIdx].IcvVerificationTimeout--;
    }
  }
  /* If retry is needed */
  if(EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts != ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvVerificationAttempts)
  {
#if(ETHTSYN_SLAVE_FV_USED == STD_ON)
    if((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_FV_RETRY_MASK) != FALSE)
    {
      Std_ReturnType RetVal = E_NOT_OK;
      EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts++;
      RetVal = EthTSyn_GetRxFreshnessValue(EthTSynCtrlIdx);
      if(RetVal == E_OK)
      {
        /* ready for ICV verification */
        TS_AtomicSetBit_8
        (
          &EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction,
          ETHTSYN_AUTH_VERIFICATION_ICV_RETRY
        );
      }
    }
#endif
    if((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_ICV_RETRY_MASK) != FALSE)
    {
       EthTSyn_Slave[EthTSynCtrlIdx].TimeAuthVerificationAttempts++;

      (void)EthTSyn_VerifyIcv(EthTSynCtrlIdx);
    }
  }
  if((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_PASSED_MASK) != FALSE)
  {
    /* Pass the time to StbM */
    (void) StbM_BusSetGlobalTime
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
        &EthTSyn_Slave[EthTSynCtrlIdx].TimeToBePassed2StbM, /* timeStampPtr */
        &EthTSyn_Slave[EthTSynCtrlIdx].UserDataToBePassed2StbM, /* userDataPtr */
        &EthTSyn_Slave[EthTSynCtrlIdx].MeasureDataToBePassed2StbM, /* measureDataPtr */
        &EthTSyn_Slave[EthTSynCtrlIdx].VirtualTimeToBePassed2StbM /* localTimePtr */
      );
    /* Reset saved values. */
    EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
  }
  else
  {
    if((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_FAILED_MASK) != FALSE)
    {
      /* Fail this frame */
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      /* Sync frame is missing or there where an issue on processing the Fup frame */
      EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
#endif
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#if(ETHTSYN_SEV_ICV_VERIFICATION_FAILED != ETHTSYN_INVALID_SEV_REF)
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00236_CallIdsM, 1 */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_NOK_CallIdsM, 1 */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00243_KEY_FAILURE_CallIdsM, 1 */
      /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_VERIFICATION_FAILED, 1 */
      IdsM_SetSecurityEventWithContextData
      (
        ETHTSYN_SEV_ICV_VERIFICATION_FAILED,
        &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
        ETHTSYN_CONTEXT_DATA_SIZE
      );
#endif /* ETHTSYN_SEV_ICV_VERIFICATION_FAILED != ETHTSYN_INVALID_SEV_REF */
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
      /* Reset saved values. */
      EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);
    }
  }
}

#endif /* ETHTSYN_ICV_USED == STD_ON */

#endif

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_CtrlVar
(
  uint8 EthTSynCtrlIdx
)
{
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber = 0xFFFFU; /* Maximum */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber = 0xFFFFU; /* Maximum */
  EthTSyn_Ctrl[EthTSynCtrlIdx].Ingress_PdelayReqSequNumber = 0U;
  /* This must be aligned to StbM, timeBaseUpdateCounter initial value:
   * requirement SWS_StbM_00344 , initial value must be 0U */
  EthTSyn_Ctrl[EthTSynCtrlIdx].LastTimeBaseUpdateCounter = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].LinkState = ETHTRCV_LINK_STATE_DOWN;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResp_BufIdx = ETHTSYN_INV_BUFIDX;
  EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx = ETHTSYN_INV_BUFIDX;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx = ETHTSYN_INV_BUFIDX;
  EthTSyn_Ctrl[EthTSynCtrlIdx].TxMode = ETHTSYN_TX_OFF;
  EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE;
  EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.nanoseconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.seconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.secondsHi = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.timeBaseStatus = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].IngressTimeStamp.nanoseconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].IngressTimeStamp.seconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].IngressTimeStamp.secondsHi = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0 = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1 = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2 = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime.nanosecondsLo = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime.nanosecondsHi = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].ImmediateTransIsLocked = FALSE;
  EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  TS_MemBZero(&EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrame[0], ETHTSYN_SYNCFUP_FRAME_MAX_SIZE);
  EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrameLength = 0U;
#endif
  EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.cumulativeScaledRateOffset = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.lastGmPhaseChange = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange = 0U;


#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFupPairTimeoutInit = FALSE;
#endif
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
  EthTSyn_Init_TimeRecordingVar(EthTSynCtrlIdx);
#endif
#if(ETHTSYN_SWITCH_USED == STD_ON)
  {
    EthTSyn_IntPortIdxType Idx = 0U;
    for(
         Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
         Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
         EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
         Idx++
       )
    {
      EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp.nanoseconds = 0U;
      EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp.seconds = 0U;
      EthTSyn_SwitchPorts[Idx].EgressPdelayFrameTimeStamp.secondsHi = 0U;
      EthTSyn_SwitchPorts[Idx].Frame2Transmit = 0U;
      EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp.nanoseconds = 0U;
      EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp.seconds = 0U;
      EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp.secondsHi = 0U;
      EthTSyn_SwitchPorts[Idx].Ingress_PdelayReqSequNumber = 0U;
      /* !LINKSTO EthTSyn.Dsn.PortPdelayState_Init, 1 */
      EthTSyn_SwitchPorts[Idx].PdelayState = ETHTSYN_PORT_PDELAY_STATE_IDLE;
      EthTSyn_SwitchPorts[Idx].PdelayUniqueId = ETHTSYN_UNIQUE_ID_INVALID;
      EthTSyn_SwitchPorts[Idx].SyncTimeStamp.nanoseconds = 0U;
      EthTSyn_SwitchPorts[Idx].SyncTimeStamp.seconds = 0U;
      EthTSyn_SwitchPorts[Idx].SyncTimeStamp.secondsHi = 0U;
      /* !LINKSTO EthTSyn.Dsn.HostPortSynTxState_INIT, 1 */
      /* !LINKSTO EthTSyn.Dsn.PortSynTxState_INIT, 1 */
      EthTSyn_SwitchPorts[Idx].SyncTxState = ETHTSYN_PORT_SYN_TX_STATE_IDLE;
      EthTSyn_SwitchPorts[Idx].UniqueId = ETHTSYN_UNIQUE_ID_INVALID;
      EthTSyn_SwitchPorts[Idx].GlobalTimeDebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE;
      EthTSyn_SwitchPorts[Idx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
      TS_MemBZero(
                   &EthTSyn_SwitchPorts[Idx].Pdelay_Rx_SrcPortIdentity[0U],
                   ETHTSYN_SOURCEPORTIDENTITY_SIZE
                 );
    }
  }
#endif

  TS_MemBZero(
               &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Tx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
  TS_MemBZero(
               &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Rx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
  /* Send next frame immediately. */
  EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout = 0U;

  /* Set Pdelay send timeout initial value different to the sync send timeout to reduce
     traffic on bus. */

#if(ETHTSYN_INITIAL_PDELAY_TIMER == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].InitialPdelayReqTxInterval != 0U)
  {
    /* !LINKSTO EthTSyn.EB.EthTSynInitialGlobalTimeTxPdelayReqPeriod_First, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
      = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].InitialPdelayReqTxInterval;
  }
  else
#endif
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
      = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval;
  }

  /* Initialize the time flags */
  EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags = 0U;
  /* Contains the number of the valid Ofs Tlvs */
  EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfValidOfs = 0U;

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcMessageLength == TRUE)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags |= ETHTSYN_MESSAGE_LENGTH_BIT_MASK;
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcDomainNumber == TRUE)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags |= ETHTSYN_DOMAIN_NUMBER_BIT_MASK;
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcCorrectionField == TRUE)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags |= ETHTSYN_CORRECTION_FIELD_BIT_MASK;
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcSourcePortIdentity == TRUE)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags |= ETHTSYN_SOURCE_PORT_IDENTITY_BIT_MASK;
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcSequenceId == TRUE)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags |= ETHTSYN_SEQUENCE_ID_BIT_MASK;
  }
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CrcPreciseOriginTimestamp == TRUE)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags |= ETHTSYN_PRECISE_ORIGIN_TIMESTAMP_BIT_MASK;
  }
#if(ETHTSYN_ICV_USED == STD_ON)
  /* Init relevant data for usage of the time auth sub-tlv. */
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = ETHTSYN_INV_BUFIDX;
  EthTSyn_Ctrl[EthTSynCtrlIdx].IcvIndication_Timeout = 0xFFFFFFFFU;
  EthTSyn_Ctrl[EthTSynCtrlIdx].TimeAuthTotalLength = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].NrOfIcvSegments = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].StartOfTimeAuthTlv = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv = ETHTSYN_AUTH_GENERATION_IDLE;
  TS_MemBZero(&EthTSyn_Ctrl[EthTSynCtrlIdx].BufferSubTlv[0U], ETHTSYN_SYNCFUP_FRAME_MAX_SIZE_ALL_TLVS);
#endif /* ETHTSYN_ICV_USED == STD_ON */
}

#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Init_TimeRecordingVar
(
  uint8 EthTSynCtrlIdx
)
{
  /* Detailed data for time validation of the Time Master on Ethernet */
  /* SequenceId of sent Ethernet frame */
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sequenceId = 0U;
  /* SourcePortId of sending Ethernet port */
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber = 0U;
  /* Egress timestamp of Sync frame */
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.syncEgressTimestamp.nanosecondsLo = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.syncEgressTimestamp.nanosecondsHi = 0U;
  /* Egress timestamp of Sync frame in Global Time */
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.seconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.nanoseconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.correctionField = 0U;

  /* Timing data for the pDelay Responder */
  /* SequenceId of received Pdelay_Req frame */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.sequenceId = 0U;
  /* SourcePortId of received Pdelay_Req frame */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.clockIdentity = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestPortId.portNumber = 0U;
  /* SourcePortId of sent Pdelay_Resp frame */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responsePortId.portNumber = 0U;
  /* Ingress timestamp of Pdelay_Req converted to Virtual Local Time */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestReceiptTimestamp.
                                                                              nanosecondsLo = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.requestReceiptTimestamp.
                                                                              nanosecondsHi = 0U;
  /* Egress timestamp of Pdelay_Resp converted to Virtual Local Time */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responseOriginTimestamp.
                                                                              nanosecondsLo = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.responseOriginTimestamp.
                                                                              nanosecondsHi = 0U;
  /* Value of the Virtual Local Time of the reference Global Time Tuple used to convert
     requestReceiptTimestamp and responseOriginTimestamp into Global Time*/
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceLocalTimestamp.
                                                                              nanosecondsLo = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceLocalTimestamp.
                                                                              nanosecondsHi = 0U;
  /* Value of the local instance of the Global Time of the reference Global Time Tuple used to
     convert requestReceiptTimestamp and responseOriginTimestamp into Global Time*/
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceGlobalTimestamp.
                                                                              nanoseconds = 0U;
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayResponderTimeRecording.referenceGlobalTimestamp.
                                                                              seconds = 0U;

  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFup_BufIdx = ETHTSYN_INV_BUFIDX;

}
#endif

STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_NextMinDebounceOffset
(
  P2VAR(uint32, AUTOMATIC, ETHTSYN_APPL_DATA) CommonOffset,
  uint32 SpecificOffset
)
{
  boolean SpecificOffsetUpdated = FALSE;

  if(*CommonOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
  {
    *CommonOffset = SpecificOffset;
    SpecificOffsetUpdated = TRUE;
  }
  else if((EthTSyn_GeneralCounter <= *CommonOffset) && (EthTSyn_GeneralCounter <= SpecificOffset))
  {
    /* both GlobalMinDebounceTimeOffset and EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
       have no wrap around */
    if(*CommonOffset > SpecificOffset)
    {
      *CommonOffset = SpecificOffset;
      SpecificOffsetUpdated = TRUE;
    }
    /* else do nothing */
  }
  else if((EthTSyn_GeneralCounter <= *CommonOffset) && (EthTSyn_GeneralCounter > SpecificOffset))
  {
    /* nothing to do GlobalMinDebounceTimeOffset has no wrap around while EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset has. */
  }
  else if((EthTSyn_GeneralCounter > *CommonOffset) && (EthTSyn_GeneralCounter <= SpecificOffset))
  {
    *CommonOffset = SpecificOffset;
    SpecificOffsetUpdated = TRUE;
  }
  /* CHECK: NOPARSE */
  /* False condition is unreachable, but NOPARSE needs to be added before "else if" branch.
   * Remaining branches inside "else if" are already covered by tests. */
  else if((EthTSyn_GeneralCounter > *CommonOffset) && (EthTSyn_GeneralCounter > SpecificOffset))
  {
    if(*CommonOffset > SpecificOffset)
    {
      *CommonOffset = SpecificOffset;
      SpecificOffsetUpdated = TRUE;
    }
  }
  else
  {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif
  }
  /* CHECK: PARSE */

  return SpecificOffsetUpdated;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ResetSynTxStateMachine
(
  uint8 EthTSynCtrlIdx
)
{
#if(ETHTSYN_SWITCH_USED == STD_ON)
  EthTSyn_IntPortIdxType Idx;

  /* cleanup */
  for(
        Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
        Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
        Idx++
     )
  {
    TS_AtomicAssign8
    (
      EthTSyn_SwitchPorts[Idx].SyncTxState,
      ETHTSYN_PORT_SYN_TX_STATE_IDLE
    );
    EthTSyn_SwitchPorts[Idx].SyncTimeStamp.nanoseconds = 0U;
    EthTSyn_SwitchPorts[Idx].SyncTimeStamp.seconds = 0U;
    EthTSyn_SwitchPorts[Idx].SyncTimeStamp.secondsHi = 0U;
    EthTSyn_SwitchPorts[Idx].UniqueId = ETHTSYN_UNIQUE_ID_INVALID;
  }
#endif /* ETHTSYN_SWITCH_USED == STD_ON */

  TS_AtomicAssign8
  (
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
    ETHTSYN_CTRL_SYN_TX_STATE_IDLE
  );
}
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunctionTimeSynMaster
(
  uint8 EthTSynCtrlIdx
)
{
  const StbM_SynchronizedTimeBaseType TimeBaseId
    = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId;
  Std_ReturnType RetVal;

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00135, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].ImmediateTimeSync) &&
      (!EthTSyn_Ctrl[EthTSynCtrlIdx].ImmediateTransIsLocked)
    )
  {
    EthTSyn_TriggImmediateTimeSyncMsg(EthTSynCtrlIdx);
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxInterval != 0U)
  {
    if(0U < EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout)
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00137.2, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout--;
    }

    /* !LINKSTO EthTSyn.SWS_EthTSyn_00139, 1 */
    if(0U == EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout)
    {
      StbM_TimeBaseStatusType syncTimeBaseStatus;
      StbM_TimeBaseStatusType offsetTimeBaseStatus;

      /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].ImmediateTransIsLocked = FALSE;
      RetVal = StbM_GetTimeBaseStatus(TimeBaseId, &syncTimeBaseStatus, &offsetTimeBaseStatus);
      TS_PARAM_UNUSED(offsetTimeBaseStatus);
      /* !LINKSTO EthTSyn.EB.Slave.GetTimeBaseStatus.NotOk, 1 */
      if(RetVal == E_OK)
      {
#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
        /* Store the time base status */
        EthTSyn_MasterTimeBaseStatus.GlobalTimebaseStatus = syncTimeBaseStatus;
#endif
        /* !LINKSTO EthTSyn.PRS_TS_00016_TxPeriodZero, 1 */
        /* !LINKSTO EthTSyn.PRS_TS_00016, 1 */
        if((syncTimeBaseStatus & ETHTSYN_GLOBAL_TIME_BASE_MASK) != 0U)
        {
          uint16 SyncSequNumber;
          StbM_UserDataType UserData;
          StbM_TimeStampType StbMTimeStamp;
          StbM_VirtualLocalTimeType StbMVirtualLocalTime;

          StbMVirtualLocalTime.nanosecondsLo = 0U;
          StbMVirtualLocalTime.nanosecondsHi = 0U;

          TS_AtomicAssign16(SyncSequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);
          /* Increment sequence number. The Sequence Counter shall wrap around at 65535 to 0 again. */
          /* !LINKSTO EthTSyn.PRS_TS_00189, 1 */
          if(ETHTSYN_SEQ_NUM_MAX == SyncSequNumber)
          {
            /* The first transmission of the Sync frame shall contain seqId 0.*/
            /* !LINKSTO EthTSyn.PRS_TS_00187_Sync, 1 */
            SyncSequNumber = 0U;
          }
          else
          {
            SyncSequNumber++;
          }

          TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber, SyncSequNumber);
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
          RetVal = StbM_BusGetCurrentTime
            (
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
              &StbMTimeStamp, /* timeStampPtr */
              &StbMVirtualLocalTime, /* localTimePtr */
              &UserData /* userDataPtr */
            );

          /* !LINKSTO EthTSyn.EB.BusGetCurrentTime_NOK, 1 */
          if(RetVal == E_OK)
          {
            EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength = UserData.userDataLength;
            EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0 = UserData.userByte0;
            EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1 = UserData.userByte1;
            EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2 = UserData.userByte2;

            EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp = StbMTimeStamp;
            EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime = StbMVirtualLocalTime;

            /* !LINKSTO EthTSyn.EB.Master.DisableAnnounce, 1 */
#if(ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON)
            /* !LINKSTO EthTSyn.EB.Master.SendPeriodicAnnounce, 1 */
            EthTSyn_TransmitAnnounceFrame(EthTSynCtrlIdx);
#endif /* ETHTSYN_SEND_ANNOUNCEFRAMES == STD_ON) */
            /* Master: Send sync frame. */
            /* !LINKSTO EthTSyn.EB.Master.SendPeriodicSync, 1 */
            if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
            {
              ETHTSYN_SET_TXFLAG
                (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SYNC, TRUE);
            }
#if(ETHTSYN_SWITCH_USED == STD_ON)
            else
            {
              ETHTSYN_SET_TXFLAG
                (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);
              TS_AtomicSetBit_8
              (
                &EthTSyn_SwitchPorts
                   [EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].Frame2Transmit,
                ETHTSYN_BITPOS_TX_SYNC_ON_HOST
              );

            }
#endif
            /* Set timeout for next Sync frame. */
            EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout
              = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxInterval;
          }
        }
      }
    }
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
  {
    if(
        EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState
        == ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_FUP
      )
    {
      ETHTSYN_SET_TXFLAG
        (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_FUP, TRUE);
      /* cleanup */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState = ETHTSYN_CTRL_SYN_TX_STATE_IDLE;
    }
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TriggImmediateTimeSyncMsg
(
  uint8 EthTSynCtrlIdx
)
{
  const StbM_SynchronizedTimeBaseType TimeBaseId
    = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId;
  uint8 TimeBaseUpdateCounter;
  Std_ReturnType RetVal;

  TimeBaseUpdateCounter = StbM_GetTimeBaseUpdateCounter(TimeBaseId);
  if (TimeBaseUpdateCounter != EthTSyn_Ctrl[EthTSynCtrlIdx].LastTimeBaseUpdateCounter)
  {
    StbM_TimeBaseStatusType SyncTimeBaseStatus;
    StbM_TimeBaseStatusType OffsetTimeBaseStatus;
    EthTSyn_Ctrl[EthTSynCtrlIdx].LastTimeBaseUpdateCounter = TimeBaseUpdateCounter;

    RetVal = StbM_GetTimeBaseStatus(TimeBaseId, &SyncTimeBaseStatus,
                                    &OffsetTimeBaseStatus
                                   );
    if(
        ((SyncTimeBaseStatus & ETHTSYN_GLOBAL_TIME_BASE_MASK) != 0U) &&
        (RetVal == E_OK)
      )
    {
      uint16 SyncSequNumberImm;
      StbM_UserDataType UserDataImm;
      StbM_TimeStampType StbMTimeStampImm;
      StbM_VirtualLocalTimeType StbMVirtualLocalTimeImm;
      StbMVirtualLocalTimeImm.nanosecondsLo = 0U;
      StbMVirtualLocalTimeImm.nanosecondsHi = 0U;

      TS_AtomicAssign16(SyncSequNumberImm, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);
      /* Increment sequence number. The Sequence Counter shall wrap around at 65535 to 0 again. */
      /* !LINKSTO EthTSyn.PRS_TS_00189, 1 */
      if(ETHTSYN_SEQ_NUM_MAX == SyncSequNumberImm)
      {
        /* The first transmission of the Sync frame shall contain seqId 0.*/
        /* !LINKSTO EthTSyn.PRS_TS_00187_Sync, 1 */
        SyncSequNumberImm = 0U;
      }
      else
      {
        SyncSequNumberImm++;
      }

      TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber, SyncSequNumberImm);
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
      RetVal = StbM_BusGetCurrentTime
        (
          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
          &StbMTimeStampImm, /* timeStampPtr */
          &StbMVirtualLocalTimeImm, /* localTimePtr */
          &UserDataImm /* userDataPtr */
        );

      /* !LINKSTO EthTSyn.EB.BusGetCurrentTime_NOK, 1 */
      if(RetVal == E_OK)
      {
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength = UserDataImm.userDataLength;
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0 = UserDataImm.userByte0;
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1 = UserDataImm.userByte1;
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2 = UserDataImm.userByte2;

        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp = StbMTimeStampImm;
        EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime = StbMVirtualLocalTimeImm;

        /* !LINKSTO EthTSyn.SWS_EthTSyn_00135, 1 */
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
        {
           ETHTSYN_SET_TXFLAG
            (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SYNC, TRUE);
        }
#if(ETHTSYN_SWITCH_USED == STD_ON)
        else
        {
          ETHTSYN_SET_TXFLAG
            (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);
          TS_AtomicSetBit_8
          (
            &EthTSyn_SwitchPorts
               [EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].Frame2Transmit,
            ETHTSYN_BITPOS_TX_SYNC_ON_HOST
          );
        }
#endif
        EthTSyn_Ctrl[EthTSynCtrlIdx].ImmediateTransIsLocked = TRUE;
        /* Set timeout for next Sync frame. */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00136, 1 */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00137.1, 1 */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00137.2, 1 */
        EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout
          = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].CyclicMsgResumeTime;
      }
    }
  }
}

#if(ETHTSYN_MAX_SLAVE != 0U)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunctionTimeSynSlave
(
  uint8 EthTSynCtrlIdx
)
{
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  /* CHECK: NOPARSE */
  if(0U < EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout)
  {
     EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout--;
  }
  else
  {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif
  }
  /* CHECK: PARSE */

  if(0U == EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout)
  {
    /* !LINKSTO EthTSyn.EB.Diagnostic_EthTSynReceiveSyncFupPairsPeriod_Expire, 1 */
    /* Sync/Fup frames are missing , increase the value of SyncFupDroppedPairsCt and
     * eventually report to Dem\Det */
    EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
  }

#endif

#if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
  if(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespFupPairTimeoutInit == TRUE)
  {
    /* CHECK: NOPARSE */
    if(0U < EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespPairTimeout)
    {
      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespPairTimeout--;
    }
    else
    {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
      ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif
    }
    /* CHECK: PARSE */
    /* !LINKSTO EthTSyn.EB.Diagnostic_EthTSynReceivePdelayRespFupPairsPeriod, 1 */
    /* !LINKSTO EthTSyn.EB.Diagnostic_EthTSynReceivePdelayRespFupPairsPeriod_Expire, 1 */
    if(0U == EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespPairTimeout)
    {
      /* PdelayResp/PdelayRespFup frames are missing , increase the value of
         PdelayRespFupDroppedPairsCt and eventually report to Dem\Det */
      EthTSyn_PDelayFrameDropped(EthTSynCtrlIdx);
      /* Abort the pdelay calculation */
      EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
    }
  }
#endif
  /* If the followup timeout is configured and the sync frame was received, begin the timeout observation. */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout > 0U) &&
      (EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived)
    )
  {
    if(EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout == 0U)
    {
      /* Timeout expired, reset the state */
      /* !LINKSTO EthTSyn.PRS_TS_00025, 2 */
      /* !LINKSTO EthTSyn.PRS_TS_00197, 1 */
      TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, FALSE);
    }
    else
    {
      EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout--;
    }
  }

  if(EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime > 0U)
  {
    /* debounce is configured between reception of sync/fup frame */
    EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime--;
  }
  if((EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay) == ETHTSYN_READY_FOR_PDELAY_CALCULATION)
  {
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
     if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
     {
        if(EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncFupReceived == TRUE)
        {
          EthTSyn_CalculatePdelay(EthTSynCtrlIdx);
        }
     }
     else
     {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
       EthTSyn_CalculatePdelay(EthTSynCtrlIdx);
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
     }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    /* Pdelay calculation done, reset the variables */
    EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
  }

  /* !LINKSTO EthTSyn.PRS_TS_00164.TimeoutDeactivated, 1 */
  if(
      (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespAndRespFollowUpTimeout > 0U) &&
      /* Handle the timeout only if a pdelay calculation was started */
      (EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay != ETHTSYN_PDELAY_CALCULATION_IDLE)
    )
  {
    if(0U == EthTSyn_Slave[EthTSynCtrlIdx].PdelayFollowUpTimeout)
    {
      /* If a reception timeout occurs (refer to [PRS_TS_00164]), any received
         Pdelay_Resp resp Pdelay_Resp_Follow_Up shall be ignored, until a new
         Pdelay_Req has been sent. */
      /* !LINKSTO EthTSyn.PRS_TS_00210, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00004, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00193, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00195, 1 */
      EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
    }
    else
    {
      EthTSyn_Slave[EthTSynCtrlIdx].PdelayFollowUpTimeout--;
    }
  }
#if(ETHTSYN_ICV_USED == STD_ON)
  EthTSyn_HandleICV(EthTSynCtrlIdx);
#endif
}
#endif

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TriggerPeriodicFrames(void)
{

  uint8 EthTSynCtrlIdx;

  for(
       EthTSynCtrlIdx = 0U;
       EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
       EthTSynCtrlIdx++
     )
  {
    uint8 TxMode;
    TS_AtomicAssign8(TxMode, EthTSyn_Ctrl[EthTSynCtrlIdx].TxMode);

    /* Send frame only if active link available. */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00021, 1 */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00022, 1 */
    if(ETHTSYN_TX_ON == TxMode)
    {
      uint8 LinkState;

      TS_AtomicAssign8(LinkState, EthTSyn_Ctrl[EthTSynCtrlIdx].LinkState);

      /* !LINKSTO EthTSyn.SWS_EthTSyn_00020, 1 */
      if(ETHTRCV_LINK_STATE_ACTIVE == LinkState)
      {
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00134, 1 */
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeSyncMaster)
          {
            EthTSyn_MainFunctionTimeSynMaster(EthTSynCtrlIdx);
#if(ETHTSYN_ICV_USED == STD_ON)
            if((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_WAIT_FOR_INDICATION_MASK) != FALSE)
            {
              if(0U < EthTSyn_Ctrl[EthTSynCtrlIdx].IcvIndication_Timeout)
              {
                EthTSyn_Ctrl[EthTSynCtrlIdx].IcvIndication_Timeout--;
              }
              else
              {
                /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00256_GenerationTimeout_StopIcv, 1 */
                TS_AtomicSetBit_8
                 (&EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv, ETHTSYN_AUTH_GENERATION_FAILED);
                ETHTSYN_SET_TXFLAG
                  (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_FUP, TRUE);
                /* Timer expired, clear the wait state. */
                TS_AtomicClearBit_8
                (
                  &EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv,
                   ETHTSYN_AUTH_WAIT_FOR_INDICATION
                );
              }
            }
#endif /* ETHTSYN_ICV_USED == STD_ON */
          }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
          else if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
          {
            /* Check if the sync period expired and no sync was received.*/
            /* Save the time of the last transmitted frame */
            if((EthTSyn_GeneralCounter - EthTSyn_Slave[EthTSynCtrlIdx].BridgeLastSyncSentTime) >=
                                    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].BridgeTxPeriod)
            {
              /* ready to transmit, on the next mainfunction, the sync to the connected slaves */
              /* Boundary clock transmit sync frames . */
              EthTSyn_Slave[EthTSynCtrlIdx].TriggerTxOnBridge = TRUE;
            }

            if(EthTSyn_Slave[EthTSynCtrlIdx].TriggerTxOnBridge == TRUE)
            {
              /* Begin transmission */
              EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout = 0U;
              EthTSyn_MainFunctionTimeSynMaster(EthTSynCtrlIdx);
              /* Save the time of the last transmitted frame */
              EthTSyn_Slave[EthTSynCtrlIdx].BridgeLastSyncSentTime = EthTSyn_GeneralCounter;
              /* Reset relevant boundary variables */
              EthTSyn_Slave[EthTSynCtrlIdx].TriggerTxOnBridge = FALSE;
              EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextSyncFrame_Timeout = 0xFFFFFFFFU;
            }
          }
          else
          {
            /* Nothing to do */
          }
#endif
          /* !LINKSTO EthTSyn.PRS_TS_00011, 1 */
          /* !LINKSTO EthTSyn.PRS_TS_00141, 1 */
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval != 0U)
          {
            /* Master/Slave: Send Pdelay_Req frame. */
            /* !LINKSTO EthTSyn.EB.Master_TransmitPdelayRequestFrame, 1 */
            if(0U < EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout)
            {
              EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout--;
            }
            /* Else branch - do nothing - retry the transmission in the next EthTSyn_MainFunction() */
            /* !LINKSTO EthTSyn.EB.PdelayReqTransmit_Retry, 1 */
            if(0U == EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout)
            {
              /* !LINKSTO EthTSyn.SWS_EthTSyn_00135, 1 */
              if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
              {
                 ETHTSYN_SET_TXFLAG
               (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_PDELAYREQ, TRUE);
              }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
              else
              {
                /* !LINKSTO EthTSyn.EB.TransparentClock_PdelayReqTransmission, 1 */
                ETHTSYN_SET_TXFLAG
                  (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);
                TS_AtomicSetBit_8
                (
                  &EthTSyn_SwitchPorts
                     [EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].Frame2Transmit,
                  ETHTSYN_BITPOS_PDELAYREQ
                );
              }
#endif
#if (ETHTSYN_MAX_SLAVE != 0U)
              if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
              {
                 /* !LINKSTO EthTSyn.PRS_TS_00005, 1 */
                 EthTSyn_ResetSlavePdelayData(EthTSynCtrlIdx);
                 /* Load the configured timeout: Time Master and Time Slave shall observe the Pdelay timeout
                 as given by PdelayRespAndRespFollowUpTimeout , if a Pdelay_Req has been
                 transmitted (waiting for Pdelay_Resp). */
                 /* !LINKSTO EthTSyn.PRS_TS_00164.PdelayReqTimeout, 1 */
                 EthTSyn_Slave[EthTSynCtrlIdx].PdelayFollowUpTimeout
                   = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespAndRespFollowUpTimeout;
               }
#endif/* (ETHTSYN_MAX_SLAVE != 0U) */
            }
          }

      }
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00019, 1 */
      else
      {
        /* Set Pdelay send timeout initial value different to the sync send timeout to reduce
           traffic on bus. */
        EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
          = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval;
      }
    }
#if(ETHTSYN_MAX_SLAVE != 0U)
    if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx))
    {
      EthTSyn_MainFunctionTimeSynSlave(EthTSynCtrlIdx);
    }
#endif/* (ETHTSYN_MAX_SLAVE != 0U) */
#if(ETHTSYN_SWITCH_USED == STD_ON)
    EthTSyn_Inc02_SwtSynStateHandling(EthTSynCtrlIdx);
#endif /* (ETHTSYN_SWITCH_USED == STD_ON) */
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessFrame2Transmit(void)
{
  uint8 EthTSynCtrlIdx;
  Std_ReturnType RetVal = E_NOT_OK;
  for(
       EthTSynCtrlIdx = 0U;
       EthTSynCtrlIdx < EthTSyn_RootCfgPtr->MaxEthTSynCtrlIdx;
       EthTSynCtrlIdx++
     )
  {
    uint8 TxMode;
    TS_AtomicAssign8(TxMode, EthTSyn_Ctrl[EthTSynCtrlIdx].TxMode);

    /* Send frame only if active link available. */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00021, 1 */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00022, 1 */
    if(ETHTSYN_TX_ON == TxMode)
    {
      if(EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit != 0U)
      {
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
        {
          /* if offset reached transmit frame and load the debounceoffset */
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00133, 1 */
          if(EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
          {
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00131, 1 */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00133, 1 */
            RetVal = EthTSyn_TransmitFrameWithDebounce(EthTSynCtrlIdx);
            /* set the debounce time only when the frame was succesfully transmitted */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00130, 1 */
            if(
                (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeDebounceTime != 0U) &&
                (RetVal == E_OK)
              )
            {
              EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset =
                  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeDebounceTime +
                  EthTSyn_GeneralCounter;
              if(EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
              {
                /* !LINKSTO EthTSyn.EB.DebounceCalculation_MaxValue, 1 */
                /* If calculated DebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE the frame transmission
                  shall be lost. Decreasing the DebounceTimeOffset with 1 shall transmit the
                  frame 1 EthTSyn_MainFunction() earlier, but the frame won't be lost. */
                EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset--;
              }
              /* needs to be set always when debounce is set to a new value != invalid */
              /* !LINKSTO EthTSyn.SWS_EthTSyn_00132, 1 */
              (void)EthTSyn_NextMinDebounceOffset
                    (&GlobalMinDebounceTimeOffset,
                     EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
                    );
            }
          }
        }
#if(ETHTSYN_SWITCH_USED == STD_ON)
        else
        {
          if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SwtDebouncingPerPort == FALSE)
          {
            /* Debouncing is done per Ctrl. */
            EthTSyn_SwtTransmitDebouncePerCtrl(EthTSynCtrlIdx);
          }
          else
          {
            /* Debouncing is done per port. */
            EthTSyn_SwtTransmitDebouncePerPort(EthTSynCtrlIdx);
          }
        }
#endif
      }
    }
    if(EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit != 0U)
    {
      TS_AtomicAssign8(EthTSyn_Frame2Transmit, TRUE);
    }
  }
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitFrameWithDebounce
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* !LINKSTO EthTSyn.PRS_TS_00186, 1 */
  if((EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_TX_SYNC_MASK) != 0U)
  {
    RetVal = EthTSyn_TransmitSyncFrame(EthTSynCtrlIdx);
  }
  else if((EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_TX_FUP_MASK) != 0U)
  {
    RetVal = EthTSyn_TransmitSyncFUpFrame(EthTSynCtrlIdx);
  }
  else if((EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_PDELAYREQ_MASK) != 0U)
  {
    RetVal = EthTSyn_TransmitPdelayReqFrame(EthTSynCtrlIdx);
  }
  else if((EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_PDELAYRESP_MASK) != 0U)
  {
    RetVal = EthTSyn_TransmitPdelayRespFrame(EthTSynCtrlIdx);
  }
  /* CHECK: NOPARSE */
  else if((EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_PDELAYRESP_FUP_MASK) !=
                                                                                                0U)
  {
    RetVal = EthTSyn_TransmitPdelayRespFUpFrame(EthTSynCtrlIdx);
  }
  else
  {
    /* nothing to do */
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif
  }
  /* CHECK: PARSE */
  return RetVal;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessRxMsg
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  /* Deviation MISRAC2012-1 */
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PhysAddrPtr,
  uint16 LenByte
)
{
  /* Extract message type from PTP header. */
  const uint8 MsgType = DataPtr[ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE] & ETHTSYN_8BIT_MASK_LN;

  TS_PARAM_UNUSED(PhysAddrPtr);

#if(ETHTSYN_HW_TIMESTAMP_SUPPORT != STD_ON)

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00180_Protection, 1 */
  SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
  if((MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_SYNC) ||
     (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ) ||
     (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP) ||
     (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ) ||
     /* This will be needed if timevalidation feature is enabled. */
     (MsgType == ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP)
    )
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00180_GetCurrentVirtual, 1 */
    /* !LINKSTO EthTSyn.EB.GetVirtualProtection_PdelayReq, 1 */
    /* !LINKSTO EthTSyn.EB.GetVirtualProtection_PdelayResp, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].GetCurrentVirtualLocalTimeRetVal =
    StbM_GetCurrentVirtualLocalTime
    (
      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
      &EthTSyn_Ctrl[EthTSynCtrlIdx].RxIngressVirtualTime
    );
  }

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00180_Protection, 1 */
  SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
#else
  TS_PARAM_UNUSED(MsgType);
#endif

  /* !LINKSTO EthTSyn.PRS_TS_00120, 1 */
  EthTSyn_ProcessFrameType(EthTSynCtrlIdx, DataPtr, LenByte);
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_ProcessFrameType
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint16 LenByte
)
{
  /* Extract message type from PTP header. */
  const uint8 MsgType = DataPtr[ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE] & ETHTSYN_8BIT_MASK_LN;

  switch(MsgType)
  {
    case ETHTSYN_PTP_HEADER_MSGTYPE_SYNC:
    {
#if (ETHTSYN_MAX_SLAVE != 0U)
      if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx))
      {
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00241, 1 */
        /* !LINKSTO EthTSyn.R22-11.PRS_TS_00242, 1 */
        if(EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime == 0U)
        {
          /* If debounce is equal to 0, frame can be processed. */
          /* Load the configured debounce value. */
          EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime =
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeRxDebounceTime;
          EthTSyn_ProcessReceivedSyncFrame(EthTSynCtrlIdx, LenByte, DataPtr);
        }
        else
        {
          /* Fail this frame */
  #if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
          EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
  #endif
          /* debounce is greater than 0, frame is not processed. */
  #if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
  #if(ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR != ETHTSYN_INVALID_SEV_REF)
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_SYNC_FOLLOWUP_SEQUENCE_ERROR, 1 */
        /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00232, 1 */
        IdsM_SetSecurityEventWithContextData
        (
          ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR,
          &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
          ETHTSYN_CONTEXT_DATA_SIZE
        );
  #endif /* ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR != ETHTSYN_INVALID_SEV_REF */
  #endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
        }
      }
      else
#endif
      {
        EthTSyn_ProcessReceivedSyncFrame(EthTSynCtrlIdx, LenByte, DataPtr);
      }

      break;
    }
    case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ:
    {
      /* !LINKSTO EthTSyn.EB.PdelayReq_IncorrectLength, 1 */
      if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE) <= LenByte)
      {
        /* !LINKSTO EthTSyn.PRS_TS_00143, 1 */
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespEnable == TRUE)
        {
          EthTSyn_ProcessRxPdelayReqFrame(EthTSynCtrlIdx, DataPtr, LenByte);
        }
      }
      break;
    }
    case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP:
    {
      if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE) <= LenByte)
      {
#if (ETHTSYN_MAX_SLAVE != 0U)
        if(
            (TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) &&
            (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval != 0U)
          ) /* Slave */
          {
            /* !LINKSTO EthTSyn.EB.Master.RxIndication, 1 */
            /* !LINKSTO EthTSyn.PRS_TS_00120, 1 */
            /* !LINKSTO EthTSyn.EB.Slave.LostSyncFUPFrame, 1 */
            EthTSyn_ProcessRxPdelayRespFrame(EthTSynCtrlIdx, DataPtr);
            /* Update PdelayRespAndRespFollowUpTimeout(waiting for Pdelay_Resp) */
            /* !LINKSTO EthTSyn.PRS_TS_00164.PdelayRespTimeout, 1 */
            EthTSyn_Slave[EthTSynCtrlIdx].PdelayFollowUpTimeout
              = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespAndRespFollowUpTimeout;
          }
#endif /* ETHTSYN_MAX_SLAVE != 0U */
      }
      break;
    }
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    case ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_REQ:
    {
      /* !LINKSTO EthTSyn.EB.IncorrectdelayReqFrameLength, 1 */
      if(
          ((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_DELAY_REQ_PAYLOADSIZE) <= LenByte) &&
           (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE) &&
           (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespEnable == TRUE)
         )
      {
        /* !LINKSTO EthTSyn.PRS_TS_00143, 1 */
        EthTSyn_ProcessRxPdelayReqFrame(EthTSynCtrlIdx, DataPtr, LenByte);
      }
      break;
    }
    case ETHTSYN_PTP_HEADER_MSGTYPE_DELAY_RESP:
    {
      if(
          ((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_DELAY_RESP_PAYLOADSIZE) <= LenByte) &&
          (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
        )
      {
#if (ETHTSYN_MAX_SLAVE != 0U)
        if(
            (TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) &&
            ((EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval != 0U) ||
            (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TransmitDelayReqAfterFup == TRUE))
          ) /* Slave */
          {
            /* !LINKSTO EthTSyn.EB.Master.RxIndication, 1 */
            /* !LINKSTO EthTSyn.PRS_TS_00120, 1 */
            /* !LINKSTO EthTSyn.EB.Slave.LostSyncFUPFrame, 1 */
            EthTSyn_ProcessRxPdelayRespFrame(EthTSynCtrlIdx, DataPtr);
          }
#endif /* ETHTSYN_MAX_SLAVE != 0U */
      }
      break;
    }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    case ETHTSYN_PTP_HEADER_MSGTYPE_FUP:
    {
      uint16 TmpLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
      {
        /* PTP IEEE1588_V2 mechanism is used */
        /* !LINKSTO EthTSyn.EB.IEEE1588FupLength, 1 */
        TmpLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP1588_SYNC_FUP_PAYLOADSIZE;
      }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
      if(TmpLength <= LenByte)
      {
#if (ETHTSYN_MAX_SLAVE != 0U)
        if(TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) /* Slave */
        {
          if(EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime == 0U)
          {
            /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00242, 1 */
            /* If debounce is equal to 0, frame can be processed. */
            /* Load the configured debounce value. */
            EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeRxDebounceTime =
                EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeRxDebounceTime;

            /* !LINKSTO EthTSyn.EB.Master.RxIndication, 1 */
            /* !LINKSTO EthTSyn.PRS_TS_00120, 1 */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00052, 1 */
            EthTSyn_ProcessRxSynFUpFrame(EthTSynCtrlIdx, DataPtr, LenByte);
          }
          else
          {
             /* Fail this frame */
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
             EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
#endif
             /* debounce is greater than 0, frame is not processed. */
#if(ETHTSYN_SECURITYEVENT_REPORTING == STD_ON)
#if(ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR != ETHTSYN_INVALID_SEV_REF)
            /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00261_SYNC_FOLLOWUP_SEQUENCE_ERROR, 1 */
            /* !LINKSTO EthTSyn.R22-11.SWS_EthTSyn_00232, 1 */
            IdsM_SetSecurityEventWithContextData
            (
              ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR,
              &ETHTSYN_ROOTCFG(EthTSynCtrlIdx).SyncGlobalTimeDomainId,
              ETHTSYN_CONTEXT_DATA_SIZE
            );
#endif /* ETHTSYN_SEV_SYNC_FOLLOWUP_SEQUENCE_ERROR != ETHTSYN_INVALID_SEV_REF */
#endif /* ETHTSYN_SECURITYEVENT_REPORTING == STD_ON */
          }
        }
#endif /* ETHTSYN_MAX_SLAVE != 0U */
      }

      break;
    }
    case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP:
    {
      if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE) <= LenByte)
      {
#if (ETHTSYN_MAX_SLAVE != 0U)
        if(
            (TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) &&
            (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval != 0U)
          ) /* Slave */
        {
          /* !LINKSTO EthTSyn.EB.Master.RxIndication, 1 */
          EthTSyn_ProcessRxPdelayRespFUpFrame(EthTSynCtrlIdx, DataPtr);
        }
#endif /* ETHTSYN_MAX_SLAVE != 0U */
      }
      break;
    }
    default:
    {
      /* !LINKSTO EthTSyn.EB.UnexpectedFrames, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00005, 1 */
      /* !LINKSTO EthTSyn.PRS_TS_00206, 1 */
      /* Unknown message type: Ignore */
      break;
    }
  }
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_CalculateOriginTimeStamp
(
  uint8 EthTSynCtrlIdx,
#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#else
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, ETHTSYN_APPL_DATA) TimeStampPtr
#endif
)
{
  StbM_VirtualLocalTimeType VirtualLocalTime;
  Std_ReturnType TmpRet;
  Eth_TimeStampType StbMTimeStamp2EthTimeStamp;
  Eth_TimeStampType EthTimeValueDiffT4Vlt_T1Vlt;


  EthTimeValueDiffT4Vlt_T1Vlt.nanoseconds = 0U;
  EthTimeValueDiffT4Vlt_T1Vlt.seconds = 0U;
  EthTimeValueDiffT4Vlt_T1Vlt.secondsHi = 0U;

  VirtualLocalTime.nanosecondsLo = 0U;
  VirtualLocalTime.nanosecondsHi = 0U;

  /* convert StbM_TimeStamp to Eth_TimeStamp */
  StbMTimeStamp2EthTimeStamp.nanoseconds = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.nanoseconds;
  StbMTimeStamp2EthTimeStamp.seconds = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.seconds;
  StbMTimeStamp2EthTimeStamp.secondsHi = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMTimeStamp.secondsHi;

#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)

  TS_PARAM_UNUSED(EthTimeValueDiffT4Vlt_T1Vlt);

  TmpRet = EthTSyn_Int01_ConvertEthTimeToVirtualTime
  (
      TimeStampPtr,
      &VirtualLocalTime
  );

  if(E_OK == TmpRet)
  {
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].VltStbMIsEthFreerunningCounter == TRUE)
    {
      StbM_VirtualLocalTimeType VirtualLocalTimeDiff_t2_t0;
      VirtualLocalTimeDiff_t2_t0.nanosecondsLo = 0U;
      VirtualLocalTimeDiff_t2_t0.nanosecondsHi = 0U;

      TmpRet = EthTSyn_Int01_SubVirtualLocalTimes
                  (
                     &VirtualLocalTime,
                     &EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime,
                     &VirtualLocalTimeDiff_t2_t0
                  );
      if(TmpRet == E_OK)
      {
        Eth_TimeStampType EthTimeStampDiffT2_T0;
        EthTimeStampDiffT2_T0.nanoseconds = 0U;
        EthTimeStampDiffT2_T0.seconds = 0U;
        EthTimeStampDiffT2_T0.secondsHi = 0U;

        EthTSyn_Int01_ConvertVirtualTimeToEthTime(&VirtualLocalTimeDiff_t2_t0,
                                                                           &EthTimeStampDiffT2_T0);

        /* Torigin = T0 + (T2vlt-T0vlt) */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00188, 1 */
        EthTSyn_AddTimeStamps(&StbMTimeStamp2EthTimeStamp, &EthTimeStampDiffT2_T0);
      }
    }
    else
    {
      Eth_TimeStampQualType TimeQuality;
      Eth_TimeStampType EthTimeStamp;
      StbM_VirtualLocalTimeType VirtualLocalTimeT3;
      StbM_VirtualLocalTimeType VirtualLocalTimeT4;
      StbM_VirtualLocalTimeType VirtualLocalTimeDiff_t4_t0;
      StbM_VirtualLocalTimeType VirtualLocalTimeDiff_t3_t2;
      StbM_VirtualLocalTimeType VirtualLocalTimeDiff;

      EthTimeStamp.nanoseconds = 0U;
      EthTimeStamp.seconds = 0U;
      EthTimeStamp.secondsHi = 0U;

      VirtualLocalTimeDiff.nanosecondsLo = 0U;
      VirtualLocalTimeDiff.nanosecondsHi = 0U;

      VirtualLocalTimeDiff_t4_t0.nanosecondsLo = 0U;
      VirtualLocalTimeDiff_t4_t0.nanosecondsHi = 0U;

      VirtualLocalTimeDiff_t3_t2.nanosecondsLo = 0U;
      VirtualLocalTimeDiff_t3_t2.nanosecondsHi = 0U;

      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
      /* !LINKSTO EthTSyn.EB.InvTimeQuality.Master.GetCurrentTime, 1 */
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00017, 1 */
      TmpRet = EthIf_GetCurrentTime(
                                     EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx,
                                     &TimeQuality,
                                     &EthTimeStamp
                                   );
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00017, 1 */
      TmpRet |= StbM_GetCurrentVirtualLocalTime
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
        &VirtualLocalTimeT4
      );
      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_1();
      if(TimeQuality != ETH_VALID)
      {
        TmpRet = E_NOT_OK;
      }

      if(E_OK == TmpRet)
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00017, 1 */
        TmpRet = EthTSyn_Int01_ConvertEthTimeToVirtualTime
        (
            &EthTimeStamp,
            &VirtualLocalTimeT3
        );
      }

      /* !LINKSTO EthTSyn.SWS_EthTSyn_00017, 1 */
      if(TmpRet == E_OK)
      {
        TmpRet = EthTSyn_Int01_SubVirtualLocalTimes
                    (
                       &VirtualLocalTimeT4,
                       &EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime,
                       &VirtualLocalTimeDiff_t4_t0
                    );
        TmpRet |= EthTSyn_Int01_SubVirtualLocalTimes
                    (
                       &VirtualLocalTimeT3,
                       &VirtualLocalTime,
                       &VirtualLocalTimeDiff_t3_t2
                    );
        TmpRet |= EthTSyn_Int01_SubVirtualLocalTimes
                     (
                       &VirtualLocalTimeDiff_t4_t0,
                       &VirtualLocalTimeDiff_t3_t2,
                       &VirtualLocalTimeDiff
                     );
      }
      if(TmpRet == E_OK)
      {
        Eth_TimeStampType EthTimeStampDiff;

        EthTimeStampDiff.nanoseconds = 0U;
        EthTimeStampDiff.seconds = 0U;
        EthTimeStampDiff.secondsHi = 0U;

        EthTSyn_Int01_ConvertVirtualTimeToEthTime(&VirtualLocalTimeDiff, &EthTimeStampDiff);

        /* Torigin= T0 + (T4vlt-T0vlt) -(T3vlt-T2vlt); */
        EthTSyn_AddTimeStamps(&StbMTimeStamp2EthTimeStamp, &EthTimeStampDiff);

      }
    }
  }
#else

  TmpRet = EthTSyn_Int01_SubVirtualLocalTimes
      (
         TimeStampPtr,
         &EthTSyn_Ctrl[EthTSynCtrlIdx].StbMVirtualLocalTime,
         &VirtualLocalTime
      );

  EthTSyn_Int01_ConvertVirtualTimeToEthTime(&VirtualLocalTime, &EthTimeValueDiffT4Vlt_T1Vlt);
  /* T0 + t0(virtuallocaltime) */
  EthTSyn_AddTimeStamps(&StbMTimeStamp2EthTimeStamp, &EthTimeValueDiffT4Vlt_T1Vlt);

#endif

  if(TmpRet == E_OK)
  {
    EthTSyn_Ctrl[EthTSynCtrlIdx].OriginTimeStamp = StbMTimeStamp2EthTimeStamp;
  }

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_MAX_CTRL != ETHTSYN_MAX_SLAVE))
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
  {
    /* Save preciseOriginTimeStamp to be reported to StbM for time recording */
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.nanoseconds =
                                                            StbMTimeStamp2EthTimeStamp.nanoseconds;
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.seconds =
                                                            StbMTimeStamp2EthTimeStamp.seconds;
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.correctionField  = 0U;
  }
#endif


  return TmpRet;
}
#if((ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (ETHTSYN_MAX_SLAVE != 0U))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_SyncFupDropped
(
  uint8 EthTSynCtrlIdx
)
{
  /* Reload the value of accepted waiting timeout */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout =
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].ReceiveSyncFupPairTimeout;

   /* Clear the flag, a sync/fup was dropped */
  TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, FALSE);
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
       /* !LINKSTO EthTSyn.EB.Diagnostic_SyncFailed_DEM, 1 */
       /* !LINKSTO EthTSyn.EB.TimeAwareBridge_DEM_FailedSync, 1 */
       /* !LINKSTO EthTSyn.EB.TimeAwareBridge_DEM_FailedSync_Ingress, 1 */
        Dem_ReportErrorStatus
        (
           EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdSyncFailed,
           DEM_EVENT_STATUS_PREFAILED
         );
#elif((ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET) && \
      (ETHTSYN_DEV_ERROR_DETECT == STD_ON) \
     )
        EthTSyn_Slave[EthTSynCtrlIdx].SyncFupDroppedPairsCt++;
        if(EthTSyn_Slave[EthTSynCtrlIdx].SyncFupDroppedPairsCt >=
                                                                 ETHTSYN_MAX_DROPPED_SYNCFUP_PAIRS)
        {
          EthTSyn_Slave[EthTSynCtrlIdx].SyncFupDroppedPairsCt = ETHTSYN_MAX_DROPPED_SYNCFUP_PAIRS;
          /* !LINKSTO EthTSyn.EB.Diagnostic_SyncFailed_DET, 1 */
          ETHTSYN_DET_REPORT_ERROR
          (
              ETHTSYN_SID_RXINDICATION,
              ETHTSYN_E_DET_SYNC_FAILED
          );
        }
#endif
}
#endif

#if(ETHTSYN_MAX_SLAVE != 0U)
STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_PerformSync
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  Eth_TimeStampType OriginTimeStamp
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* Measure Data */
  StbM_MeasurementType MeasureData;
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  StbM_EthTimeSlaveMeasurementType RecordData;
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
  Eth_TimeStampType TmpTimeStamp;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  Eth_TimeIntDiffType PTPFupCorrection;
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRefTimbaseId != 0xFFU)
  {
    /* !LINKSTO EthTSyn.EB.RemotePdelay,1 */
    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay = *(EthTSyn_Slave[EthTSynCtrlIdx].RemotePDelay);
  }
  /* Calculate time offset between master and slave. */
  /* Pdelay + OriginTimeStampSync[FUP] */
  TmpTimeStamp.secondsHi = 0U;
  TmpTimeStamp.seconds = 0U;
  TmpTimeStamp.nanoseconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
  /* !LINKSTO EthTSyn.EB.PTPE2ECalculatedMeanDelay,1 */
  /* !LINKSTO EthTSyn.SWS_EthTSyn_00150,1 */
  MeasureData.pathDelay = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
  {
    /* !LINKSTO EthTSyn.EB.PTPE2EFupCorrectionField,1 */
    RetVal = EthTSyn_SavePTPCorrField
    (
      EthTSynCtrlIdx,
      &DataPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0],
      &PTPFupCorrection
    );
  }
  else
  {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
    RetVal = EthTSyn_AddCorrField
    (
      EthTSynCtrlIdx,
      &DataPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0],
      &TmpTimeStamp
    );
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
  }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
  if(E_OK == RetVal) /* Only perform a correction if no wrong time stamp detected. */
  {
    StbM_UserDataType UserData;
    Eth_TimeStampType SyncReceptionDelay = {0U, 0U, 0U};
    StbM_TimeStampType StbMTimeStamp;
    uint32 ProtocolParamTemp;

    StbM_VirtualLocalTimeType VirtualLocalTimeT2 = EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt;

    /* correctionField + Pdelay + OriginTimeStamp */
    EthTSyn_AddTimeStamps(&TmpTimeStamp, &OriginTimeStamp);

    /* Convert virtual time to ethtime */
    EthTSyn_Int01_ConvertVirtualTimeToEthTime(&EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay, &SyncReceptionDelay);

    /* !LINKSTO EthTSyn.SWS_EthTSyn_00080, 1 */
    UserData.userDataLength = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength;
    UserData.userByte0 = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0;
    UserData.userByte1 = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1;
    UserData.userByte2 = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2;

    /* OriginTimeStamp + correctionField + Pdelay + SRD */
    EthTSyn_AddTimeStamps(
                 &TmpTimeStamp, /* OriginTimeStamp + correctionField + Pdelay */
                 &SyncReceptionDelay /* Sync Reception Delay */
               );
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
    RetVal = EthTSyn_SubCorrE2EMechanism(EthTSynCtrlIdx, &PTPFupCorrection, &TmpTimeStamp);

    /* !LINKSTO EthTSyn.EB.PTPE2EInvalidCorrectionRx, 1 */
    if(RetVal == E_OK)
    {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
      StbMTimeStamp.nanoseconds = TmpTimeStamp.nanoseconds;
      StbMTimeStamp.seconds = TmpTimeStamp.seconds;
      StbMTimeStamp.secondsHi = TmpTimeStamp.secondsHi;
      StbMTimeStamp.timeBaseStatus = EthTSyn_SyncToGatewayBit;
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
        /* Save PreciseOriginTimestamp as received in the Followup Message from master */
        EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.preciseOriginTimestamp.
                                                 nanoseconds = OriginTimeStamp.nanoseconds;
        EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.preciseOriginTimestamp.
                                                 seconds = OriginTimeStamp.seconds;
        EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.pDelay =
                                                      MeasureData.pathDelay;
        RecordData = EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording;
      }
#endif

      /* Forward the TimeStamp to StbM only if no StbM TIMEOUT took place, or, if a TIMEOUT
         happened, only if there are enough valid Sync/SyncFUp pairs received. */
      /* !LINKSTO EthTSyn.PRS_TS_00200, 1 */
      /* Deviation TASKING-3 */
      if((EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs == 0U) ||
         ((EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs > 0U) &&
          (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SequenceCounterHysteresis ==
            EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs)
         )
        )
      {
#if(ETHTSYN_ICV_USED == STD_ON)
        if(
           ((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_IDLE_MASK) != FALSE) ||
           ((EthTSyn_Slave[EthTSynCtrlIdx].VerifIcvAction & ETHTSYN_AUTH_VERIFICATION_PASSED_MASK) != FALSE)
           )
        {
#endif /* ETHTSYN_ICV_USED == STD_ON */
          /* Return value ignored: No further action possible if E_NOT_OK returned. */
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00129, 1 */
          /* !LINKSTO EthTSyn.EB.Slave.HWTimpStamp.GatewaySync, 1 */
          /* !LINKSTO EthTSyn.EB.Slave.StbMSync, 1 */
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00052, 1 */
          (void) StbM_BusSetGlobalTime
            (
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
              &StbMTimeStamp, /* timeStampPtr */
              &UserData, /* userDataPtr */
              &MeasureData, /* measureDataPtr */
              &VirtualLocalTimeT2 /* localTimePtr */
            );

#if(ETHTSYN_ICV_USED == STD_ON)
          /* Reset saved values. */
          EthTSyn_Init_IcvSubTlvData(EthTSynCtrlIdx);

        }
        else
        {
          /* Retry mechanism for verification of the ICV is ongoing . Save the relevant data.*/
          EthTSyn_Slave[EthTSynCtrlIdx].TimeToBePassed2StbM = StbMTimeStamp;
          EthTSyn_Slave[EthTSynCtrlIdx].VirtualTimeToBePassed2StbM = VirtualLocalTimeT2;
          EthTSyn_Slave[EthTSynCtrlIdx].MeasureDataToBePassed2StbM = MeasureData;
          EthTSyn_Slave[EthTSynCtrlIdx].UserDataToBePassed2StbM = UserData;
        }
#endif /* ETHTSYN_ICV_USED == STD_ON */
        /* Reset valid pairs counter */
        EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs = 0U;
      }

#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == FALSE)
      {
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */
        SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();
        /* Save ProtocolParam from succesfully received SyncFUp frame.
         * Shall be returned when EthTSyn_GetProtocolParam() is called */
        ProtocolParamTemp = (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B10_CSRO_3]) << 24U;
        ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B11_CSRO_2]) << 16U;
        ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B12_CSRO_1]) << 8U;
        ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B13_CSRO_0]);

        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.cumulativeScaledRateOffset = (sint32)(ProtocolParamTemp);

        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator =
            (uint16)((uint16)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B14_GM_TIMEBASEIND_1]) << 8U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator |=
            (uint16)((uint16)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B15_GM_TIMEBASEIND_0]));

        ProtocolParamTemp = (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B16_GM_PH_CHG_0]) << 24U;
        ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B17_GM_PH_CHG_1]) << 16U;
        ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B18_GM_PH_CHG_2]) << 8U;
        ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B19_GM_PH_CHG_3]);

        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.lastGmPhaseChange = (sint32)(ProtocolParamTemp);

        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange =
            (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B28_GM_FREQ_CHG_3]) << 24U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange |=
            (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B29_GM_FREQ_CHG_2]) << 16U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange |=
            (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B30_GM_FREQ_CHG_1]) << 8U);
        EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange |=
            (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                      ETHTSYN_FUP_TLV_B31_GM_FREQ_CHG_0]));

        SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      }
#endif /* ETHTSYN_IEEE1588_CONFIGURED == STD_ON */

#if(ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U)
      if
      ((EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex > EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsIndex) &&
        ((EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs == 0U) ||
        /* Deviation TASKING-3 */
        ((EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs > 0U) &&
          (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SequenceCounterHysteresis ==
           EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncSyncFUpPairs)
        )
        )
      )
      {
        uint8 Idx;
        for(
              Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsIndex;
              Idx < EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex;
              Idx++
            )
        {
           /* !LINKSTO EthTSyn.SWS_EthTSyn_00198, 1 */
          (void) StbM_BusSetGlobalTime
            (
              EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeDomId , /* StbMOffsetTimeDomId */
              &EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp, /* timeStampPtr */
              &EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData, /* userDataPtr */
              &MeasureData, /* measureDataPtr */
              &VirtualLocalTimeT2 /* localTimePtr */
            );
          /* Reset the offset values.*/
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeDomId = 0xFFU;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.secondsHi = 0U;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.seconds = 0U;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.nanoseconds = 0;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetTimeStamp.timeBaseStatus = 0xFFU;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userByte0 = 0xFFU;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userByte1 = 0xFFU;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userByte2 = 0xFFU;
          EthTSyn_OffsetTbInfo[Idx].StbMOffsetUserData.userDataLength = 0xFFU;
        }
        EthTSyn_Slave[EthTSynCtrlIdx].OffsetIndex = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].OfsIndex;
      }
#endif /* ETHTSYN_OFSTIMEBASES_CONFIGURED > 0U */
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeValidationEnabled == TRUE)
      {
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00216, 1 */
        (void) StbM_EthSetSlaveTimingData
          (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00217, 1 */
            &RecordData /* measureDataPtr */
          );
      }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */

#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      EthTSyn_HandleDemSync(EthTSynCtrlIdx);
#endif
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PTPMechanismEnabled == TRUE)
      {
        SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
        /* Save the previous values and update the relevant data. */
        /* !LINKSTO EthTSyn.EB.SaveBackupValues, 1 */
        EthTSyn_UpdateDelayValues(EthTSynCtrlIdx, OriginTimeStamp, PTPFupCorrection);
        /* The Delay can be calculated.*/
        /* !LINKSTO EthTSyn.EB.MeanDelayAfterValidFrames, 1 */
        EthTSyn_Slave[EthTSynCtrlIdx].ValidSyncFupReceived = TRUE;

        SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TransmitDelayReqAfterFup == TRUE)
        {
          /* Send the delay_req frame on the next mainfunction */
          /* !LINKSTO EthTSyn.EB.PTPE2EEthTSynDelayReqAfterFupTRUE, 1 */
          ETHTSYN_SET_TXFLAG
             (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_PDELAYREQ, TRUE);
        }
        /* !LINKSTO EthTSyn.EB.PTPE2EEthTSynDelayReqAfterFupFALSE, 1 */
      }
    }
#endif

  }
  return RetVal;
}
#endif

#if((ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE) && (ETHTSYN_MAX_SLAVE != 0U))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_HandleDemSync
(
  uint8 EthTSynCtrlIdx
)
{
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
  /* Heal dem event */
  /* !LINKSTO EthTSyn.EB.Diagnostic_SyncOK_DEM, 1 */
  Dem_ReportErrorStatus
  (
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdSyncFailed,
    DEM_EVENT_STATUS_PREPASSED
  );
#elif (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
  /* Sync/Fup pair was received, reset the counter */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncFupDroppedPairsCt = 0U;
#endif
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  /* Reload the value of timeout */
  EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout =
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].ReceiveSyncFupPairTimeout;
#endif
}
#endif

#if((ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE) && (ETHTSYN_MAX_SLAVE != 0U))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_PDelayFrameDropped
(
  uint8 EthTSynCtrlIdx
)
{

  /* Reload the value of accepted waiting timeout */
  EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayRespPairTimeout =
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespFupPairsPeriod;

#if(ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DEM)
        /* !LINKSTO EthTSyn.EB.Diagnostic_PdelayFailed_DEM, 1 */
        Dem_ReportErrorStatus
        (
           EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdPdelayFailed,
           DEM_EVENT_STATUS_PREFAILED
         );
#elif((ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED == TS_PROD_ERR_REP_TO_DET) && \
      (ETHTSYN_DEV_ERROR_DETECT == STD_ON))
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayRespFupDroppedPairsCt++;
        if(EthTSyn_Slave[EthTSynCtrlIdx].PdelayRespFupDroppedPairsCt >=
                                                     ETHTSYN_MAX_DROPPED_PDELAYRESPPDELAYFUP_PAIRS)
        {
          EthTSyn_Slave[EthTSynCtrlIdx].PdelayRespFupDroppedPairsCt =
                                                     ETHTSYN_MAX_DROPPED_PDELAYRESPPDELAYFUP_PAIRS;
          /* !LINKSTO EthTSyn.EB.Diagnostic_PdelayFailed_DET, 1 */
          ETHTSYN_DET_REPORT_ERROR
          (
              ETHTSYN_SID_RXINDICATION,
              ETHTSYN_E_DET_PDELAY_FAILED
          );
        }
#endif
}
#endif
#if(ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON)
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayDevAuth
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 Tlv_Length;
  Tlv_Length = ETHTSYN_GET16(DataPtr, 2U);
  /* !LINKSTO EthTSyn.EB.DevAuth_PdelayReqInvalidTLV, 1 */
  if(
      /* TLV type */
      (DataPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B0_TYPE] == ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_0) &&
      (DataPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B1_TYPE] == ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_1) &&
      /* length field */
      (Tlv_Length == ETHTSYN_AUTH_CHALLENGE_TLV_SIZE)
    )
  {
    /* !LINKSTO EthTSyn.EB.DevAuth_PdelayReqValidAuthTLV, 1 */
    /* Save RequestNonce from received PdelayReq frame */
    EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce =
                       ((uint32)DataPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B6_REQNONCE] << 24U)
                        + (uint32)((uint32)DataPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B7_REQNONCE] << 16U)
                        + (uint32)((uint32)DataPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B8_REQNONCE] << 8U)
                        + DataPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B9_REQNONCE];
    /* !LINKSTO EthTSyn.EB.DevAuth_PdelayReqIndication_NOK, 1 */
    RetVal = DevAuth_PDelayReqIndication
    (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx,
        &EthTSyn_Ctrl[EthTSynCtrlIdx].IngressTimeStamp,
        EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce,
        &EthTSyn_Ctrl[EthTSynCtrlIdx].ResponseNonce
     );

    if(RetVal == E_OK)
    {
      TS_AtomicAssign8(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqReceivedWithAuthChallTlv, TRUE);
    }

  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_FillAuthChallengeTLV
(
  uint8 EthTSynCtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr
)
{
  /* tlvType = AUTHENTICATION_CHALLENGE */
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B0_TYPE] = ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_0;
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B1_TYPE] = ETHTSYN_AUTH_CHALLENGE_TLV_TYPE_1;

  /* lengthField */
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B2_LENGTH] = ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_0;
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B3_LENGTH] = ETHTSYN_AUTH_CHALLENGE_TLV_LENGTH_1;

  /* challengeType */
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B4_CHLTYPE] = ETHTSYN_AUTH_CHALLENGE_RESPONSE_TYPE;
  /* reserved */
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B5_RESERVED] = ETHTSYN_AUTH_CHALLENGE_TLV_RESERVED;

  /* RequestNonce */
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B6_REQNONCE] =
      (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B7_REQNONCE] =
      (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B8_REQNONCE] =
      (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B9_REQNONCE] =
      (uint8)(EthTSyn_Ctrl[EthTSynCtrlIdx].RequestNonce & ETHTSYN_32BIT_MASK0_LSB);

  /* ResponseNonce */
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B10_RESPNONCE] =
      (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].ResponseNonce & ETHTSYN_32BIT_MASK3_MSB) >> 24U);
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B11_RESPNONCE] =
      (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].ResponseNonce & ETHTSYN_32BIT_MASK2) >> 16U);
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B12_RESPNONCE] =
      (uint8)((uint32)(EthTSyn_Ctrl[EthTSynCtrlIdx].ResponseNonce & ETHTSYN_32BIT_MASK1) >> 8U);
  BufPtr[ETHTSYN_AUTH_CHALLENGE_TLV_B13_RESPNONCE] =
      (uint8)(EthTSyn_Ctrl[EthTSynCtrlIdx].ResponseNonce & ETHTSYN_32BIT_MASK0_LSB);

}
#endif /* ETHTSYN_DEVICE_AUTHENTICATION_SUPPORT == STD_ON */
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_TxFailedResetValues
(
  uint8 EthIfCtrlIdx,
  Eth_BufIdxType BufIdx
)
{
  uint8 TSynCtrlIdx;
  Std_ReturnType EthTSynCtrlFound = E_NOT_OK;
  EthTSynCtrlFound = EthTSyn_TranslateEthIfCtrlIdx(EthIfCtrlIdx, &TSynCtrlIdx);
  if(EthTSynCtrlFound == E_OK)
  {
    if(EthTSyn_Ctrl[TSynCtrlIdx].Sync_BufIdx == BufIdx)
    {
      EthTSyn_ResetSynTxStateMachine(TSynCtrlIdx);
      EthTSyn_Ctrl[TSynCtrlIdx].Sync_BufIdx = ETHTSYN_INV_BUFIDX;
    }
    else if(EthTSyn_Ctrl[TSynCtrlIdx].PdelayResp_BufIdx == BufIdx)
    {
      EthTSyn_Ctrl[TSynCtrlIdx].PdelayResp_BufIdx = ETHTSYN_INV_BUFIDX;
    }
    else if(EthTSyn_Ctrl[TSynCtrlIdx].PdelayReq_BufIdx == BufIdx)
    {
#if(ETHTSYN_MAX_SLAVE != 0U)
      /* Reset the pdelay data. */
      if (EthTSyn_IsSlave(TSynCtrlIdx))
      {
        EthTSyn_ResetSlavePdelayData(TSynCtrlIdx);
      }
#endif /* ETHTSYN_MAX_SLAVE != 0U */
      EthTSyn_Ctrl[TSynCtrlIdx].PdelayReq_BufIdx  = ETHTSYN_INV_BUFIDX;
    }
#if(ETHTSYN_ICV_USED == STD_ON)
    else if(EthTSyn_Ctrl[TSynCtrlIdx].SyncFUp_BufIdx == BufIdx)
    {
      /* Reset relevant data for usage of the time auth sub-tlv. */
      EthTSyn_Ctrl[TSynCtrlIdx].SyncFUp_BufIdx = ETHTSYN_INV_BUFIDX;
      EthTSyn_Ctrl[TSynCtrlIdx].IcvIndication_Timeout = 0xFFFFFFFFU;
      EthTSyn_Ctrl[TSynCtrlIdx].TimeAuthTotalLength = 0U;
      EthTSyn_Ctrl[TSynCtrlIdx].NrOfIcvSegments = 0U;
      EthTSyn_Ctrl[TSynCtrlIdx].StartOfTimeAuthTlv = 0U;
      EthTSyn_Ctrl[TSynCtrlIdx].NextActionIcv = ETHTSYN_AUTH_GENERATION_IDLE;
      TS_MemBZero(&EthTSyn_Ctrl[TSynCtrlIdx].BufferSubTlv[0U], ETHTSYN_SYNCFUP_FRAME_MAX_SIZE_ALL_TLVS);
      EthTSyn_Ctrl[TSynCtrlIdx].SyncFUp_BufIdx = ETHTSYN_INV_BUFIDX;
    }
#endif /* ETHTSYN_ICV_USED == STD_ON */
    else
    {
      /* Wrong BufIdx */
    }
  }
}


/* ============================================================================= */
#if(ETHTSYN_SWITCH_USED == STD_ON)

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtOnHostPortSyncFrame
(
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  EthTSyn_CtrlSyncTxStateType SyncTxState;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  uint8 Tmp_buffer[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_PAYLOADSIZE];

  const EthTSyn_IntPortIdxType IntHostPortIdx
    = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt;


  TS_AtomicAssign8
  (
    SyncTxState,
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState
  );
  if(ETHTSYN_CTRL_SYN_TX_STATE_IDLE != SyncTxState)
  {
    EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
  }

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_PAYLOADSIZE;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
  {
#endif
    /* Prepare time sync frame PTP header. */
    PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_TWOSTEP;
    PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
    PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_SYNC;
    PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_SYNC;

    /* Set sequence number. */
    /* !LINKSTO EthTSyn.PRS_TS_00189, 1 */
    TS_AtomicAssign16(PTPHeader.SequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

    PTPHeader.LogMsgInterval = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxMsgLogInterval;

    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &Tmp_buffer[0U]);
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  }
  else
  {
    /* If a TAB with GTM not as Mgm CPU is configured and EthTSyn is configured to handle the fowrding of the frames, copy the
     * received frame. */
    TS_MemCpy(&Tmp_buffer, &EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedSyncFrame, PTPHeader.MsgLength);
  }
#endif

#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SwtPortIdxInCorrField)
  {
    /* !LINKSTO EthTSyn.EB.SwitchPortIdx.StoredInCorrectionField, 1 */
    Tmp_buffer[ETHTSYN_PTP_HEADER_B14_CORRFIELD_6] =
        (uint8)EthTSyn_RootCfgPtr->SwitchConfig[IntHostPortIdx].EthSwtIdx;
    Tmp_buffer[ETHTSYN_PTP_HEADER_B15_CORRFIELD_7] =
        (uint8)EthTSyn_RootCfgPtr->SwitchConfig[IntHostPortIdx].EthSwtPortIdx;
  }
#endif /*(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)*/

  /* Set PTP payload */
  /* All bytes are reserved. */
  TS_MemBZero(&Tmp_buffer[ETHTSYN_PTP_HEADER_SIZE], ETHTSYN_PTP_SYNC_PAYLOADSIZE);

  /* !LINKSTO EthTSyn.EB.EthSwt_TransmitSyncFrameOnHostPort, 1 */
  RetVal = EthTSyn_Inc02_GetSwtTxBuffer
     (EthTSynCtrlIdx, PTPHeader.MsgLength, IntHostPortIdx, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
  if(RetVal == E_OK)
  {
    TS_MemCpy(PTPPayloadPtr, Tmp_buffer, PTPHeader.MsgLength);

    EthTSyn_Ctrl[EthTSynCtrlIdx].Sync_BufIdx = BufIdx;
#if((ETHTSYN_TIME_RECORDING == STD_ON) && (ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON))
    {
      /* If EthTSynSendSyncFrameOnlyOnHostPort is TRUE and time recording enabled, EthTSyn
         has to save the sequenceId, sourcePortId */
      uint8 Idx = 0U;
      boolean Found = FALSE;
      uint8 StartPort = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 1U;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
      /* check only the master ports */
      StartPort = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 2U;
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
      for
      (
         Idx = StartPort;
        ((Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                 EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart
                )
         )
            && (FALSE == Found)
        );
         Idx++
      )
      {
        if(EthTSyn_RootCfgPtr->SwitchConfig[Idx].TimeValidationEnabled == TRUE)
        {
          /* Save SyncSequNumber to be reported to StbM for time recording */
          TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sequenceId,
                                                            EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity =
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
               (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber =
               (uint16)(((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber |=
               (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
          /* Is enough to check that at least one port from the current timedomain has the timevalidation enabled */
          Found = TRUE;
        }
      }
    }
#endif
    RetVal = EthTSyn_Inc02_TransmitSwtFrame(EthTSynCtrlIdx, BufIdx, TRUE, IntHostPortIdx, TRUE, PTPHeader.MsgLength, FALSE);
  }

  /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
  if(RetVal == E_OK)
  {
    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_SwitchPorts[IntHostPortIdx].Frame2Transmit,
      ETHTSYN_BITPOS_TX_SYNC_ON_HOST
    );

    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
    EthTSyn_SwitchPorts[IntHostPortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
    {
      /* !LINKSTO EthTSyn.Dsn.HostPortSynTxState_INIT-WAIT_INGRESS, 1 */
      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[IntHostPortIdx].SyncTxState,
        ETHTSYN_PORT_SYN_TX_STATE_WAIT_INGRESS_TS
      );
      /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_IDLE-WAIT_EGRESS, 1 */
      TS_AtomicAssign8
      (
        EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
        ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_ETH_EGRESS_TS
      );
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON)
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SwtDebouncingPerPort == TRUE)
      {
        /* !LINKSTO EthTSyn.EB.DebouncePerPort_Enabled, 1 */
        EthTSyn_IntPortIdxType PortIndex = 0U;
        for(
            PortIndex = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
            PortIndex < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                   EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
            PortIndex++
           )
        {
          if((EthTSyn_RootCfgPtr->SwitchConfig[PortIndex].EthTSynPortDebounceTime != 0U) &&
                     (PortIndex != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt))
          {
            boolean Updated = FALSE;
            /* set the debounce time */
            EthTSyn_SwitchPorts[PortIndex].GlobalTimeDebounceTimeOffset =
                EthTSyn_RootCfgPtr->SwitchConfig[PortIndex].EthTSynPortDebounceTime +
                EthTSyn_GeneralCounter;

            if(EthTSyn_SwitchPorts[PortIndex].GlobalTimeDebounceTimeOffset == ETHTSYN_INV_DEBOUNCE_VALUE)
            {
              /* !LINKSTO EthTSyn.EB.DebounceCalculation_MaxValue, 1 */
              /* If calculated DebounceTimeOffset = ETHTSYN_INV_DEBOUNCE_VALUE the frame transmission
                shall be lost. Decreasing the DebounceTimeOffset with 1 shall transmit the
                frame 1 EthTSyn_MainFunction() earlier, but the frame won't be lost. */
              EthTSyn_SwitchPorts[PortIndex].GlobalTimeDebounceTimeOffset--;
            }

            /* call the controller min function*/
            Updated = EthTSyn_NextMinDebounceOffset
                       (&EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset,
                        EthTSyn_SwitchPorts[PortIndex].GlobalTimeDebounceTimeOffset
                       );
            if(Updated == TRUE)
            {
              (void)EthTSyn_NextMinDebounceOffset
                    (&GlobalMinDebounceTimeOffset,
                     EthTSyn_Ctrl[EthTSynCtrlIdx].DebounceTimeOffset
                    );
            }
          }
        }
      }
#endif /* (ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_ON) */
    }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
    else
    {
      uint8 Idx;
      /* Prepare the master ports for receiving the egressTS. */
      for(
          Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 2U;
          Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
          Idx++
         )
      {
        TS_AtomicAssign8
        (
            EthTSyn_SwitchPorts[Idx].SyncTxState,
            ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS
        );
      }
    }
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
  }
  else if(EthTSyn_SwitchPorts[IntHostPortIdx].EthTSynMaxNumberOfRetries > 0U)
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
    EthTSyn_SwitchPorts[IntHostPortIdx].EthTSynMaxNumberOfRetries--;
  }
  else
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
    EthTSyn_SwitchPorts[IntHostPortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_SwitchPorts[IntHostPortIdx].Frame2Transmit,
      ETHTSYN_BITPOS_TX_SYNC_ON_HOST
    );

    EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
  }

  return RetVal;
}


STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtSyncFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr ;
  EthTSyn_PTPHeaderType PTPHeader;
  uint8 Tmp_buffer[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_PAYLOADSIZE];
  EthTSyn_IntPortIdxType PortIdleCounter = 0U;
  EthTSyn_IntPortIdxType Idx;
  EthTSyn_PortSyncTxStateType PortSynTxState;


  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_PAYLOADSIZE;

#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
  {
#endif
    /* Prepare time sync frame PTP header. */
    PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_TWOSTEP;
    PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
    PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_SYNC;
    PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_SYNC;

    /* Set sequence number. */
    /* !LINKSTO EthTSyn.PRS_TS_00189, 1 */
    TS_AtomicAssign16(PTPHeader.SequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

    PTPHeader.LogMsgInterval = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxMsgLogInterval;

    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &Tmp_buffer[0U]);

    /* Set PTP payload */
    /* All bytes are reserved. */
    TS_MemBZero(&Tmp_buffer[ETHTSYN_PTP_HEADER_SIZE], ETHTSYN_PTP_SYNC_PAYLOADSIZE);
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  }
  else
  {
    /* If a TAB with GTM not as Mgm CPU is configured and EthTSyn is configured to handle the fowrding of the frames, copy the
     * received frame. */
    TS_MemCpy(&Tmp_buffer, &EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedSyncFrame, PTPHeader.MsgLength);
  }
#endif

  /* !LINKSTO EthTSyn.EB.EthSwt_TransmitSyncFrameOnPorts, 1 */
  /* !LINKSTO EthTSyn.EB.TransparentClock_EthTSynSendSync_FailedFw, 1 */
  RetVal = EthTSyn_Inc02_GetSwtTxBuffer
      (EthTSynCtrlIdx, PTPHeader.MsgLength, PortIdx, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
  if(E_OK == RetVal)
  {
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SwtPortIdxInCorrField)
    {
      Tmp_buffer[ETHTSYN_PTP_HEADER_B14_CORRFIELD_6] =
          (uint8)EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthSwtIdx;
      Tmp_buffer[ETHTSYN_PTP_HEADER_B15_CORRFIELD_7] =
          (uint8)EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthSwtPortIdx;
    }

    /* If the EthTSyn portid is configured update the portid bytes form the sourceportid field. */
    if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId != 0xFFFFU)
    {
      /* 16 bit port number */
      Tmp_buffer[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8] =
        (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_MSB) >> 8U);
      Tmp_buffer[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9] =
        (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_LSB));
    }
#endif

    TS_MemCpy(PTPPayloadPtr, &Tmp_buffer, PTPHeader.MsgLength);

#if(ETHTSYN_TIME_RECORDING == STD_ON)
    if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].TimeValidationEnabled == TRUE)
    {
      /* Save SyncSequNumber to be reported to StbM for time recording */
      /* The seqId is the same for all ports. */
      TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sequenceId,
                                                        EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity =
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.portNumber =
           (uint16)((uint16) (PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
      EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId.portNumber |=
           (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
    }
#endif
    /* !LINKSTO EthTSyn.EB.EthSwt_TransmitSyncFrameOnPorts, 1 */
    RetVal = EthTSyn_Inc02_TransmitSwtFrame(EthTSynCtrlIdx, BufIdx, TRUE, PortIdx, TRUE, PTPHeader.MsgLength, FALSE);

    /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
    if(E_OK == RetVal)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_SYNC
      );

      /* !LINKSTO EthTSyn.Dsn.PortSynTxState_IDLE-WAIT_EGRESS, 1 */
      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[PortIdx].SyncTxState,
        ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS
      );

      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
      EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
    }
    else if(EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries > 0U)
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
      EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries--;
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
      EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_SYNC
      );
      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[PortIdx].SyncTxState,
        ETHTSYN_PORT_SYN_TX_STATE_IDLE
      );
    }
    for(
       Idx =  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
       Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount
           +  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
       Idx++
     )
    {
      TS_AtomicAssign8
      (
          PortSynTxState,
          EthTSyn_SwitchPorts[Idx].SyncTxState
      );

      if(ETHTSYN_PORT_SYN_TX_STATE_IDLE == PortSynTxState)
      {
        PortIdleCounter++;
      }
    }

    if((EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount - 1U) == PortIdleCounter)
    {
      /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_PORT_READY_FUP-IDLE, 1 */
      /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_PORT_READY-IDLE, 1 */
      EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
    }

  }
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSyncSwtFUpFramePerPort
(
  uint8 EthTSynCtrlIdx,
  EthTSyn_IntPortIdxType PortIdx
)
{
  EthTSyn_IntPortIdxType Idx;
  EthTSyn_IntPortIdxType PortIdleCounter = 0U;
  EthTSyn_PortSyncTxStateType PortSynTxState;
  uint16 SubTlvSize = 0U;
  Std_ReturnType RetVal = E_NOT_OK;
  Std_ReturnType CorrectionStatus = E_NOT_OK;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  uint32 NsLow = 0U;
#if(ETHTSYN_ICV_USED == STD_ON)
  boolean FrameWasTransmitted = FALSE;
#endif /* ETHTSYN_ICV_USED == STD_ON */


  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_FUP;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_FUP;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00190, 1 */
  TS_AtomicAssign16(PTPHeader.SequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber);

  /* Same value as sync frame (See 802.1AS-2011 Ch 11.4.2.8) */
  PTPHeader.LogMsgInterval = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SyncTxMsgLogInterval;

#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
  SubTlvSize = EthTSyn_CheckForAUTOSARSubTLV(EthTSynCtrlIdx);
#endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_ON) */

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE + SubTlvSize;

#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == TRUE)
  {
    PTPHeader.MsgLength = EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrameLength;
  }
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */

  /* Check that a valid correction value is updated in the correction field
   * If the value is invalid the fup will not pe sent on this port */
  CorrectionStatus = EthTSyn_Inc02_SwtCorrField(EthTSynCtrlIdx, PortIdx ,&NsLow);
  /* !LINKSTO EthTSyn.EB.Swt_InvalidCorrection_Calculated, 1 */
  if(CorrectionStatus == E_OK)
  {
#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
    /* If Icv SubTLV is enabled, update the buffer */
    if((ETHTSYN_ROOTCFG(EthTSynCtrlIdx).TLVFollowUpICVSubTLV == TRUE) && (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout > 0U))
    {
      RetVal = EthTSyn_CheckPendingTimeAuthTLV(EthTSynCtrlIdx, &PTPPayloadPtr, PortIdx, PTPHeader.MsgLength, &FrameWasTransmitted);
    }
    else
#endif
    {
      /* !LINKSTO EthTSyn.EB.EthSwt_TransmitSyncFupFrameOnPorts, 1 */
      RetVal = EthTSyn_Inc02_GetSwtTxBuffer
        (EthTSynCtrlIdx, PTPHeader.MsgLength, PortIdx, &BufIdx, &PTPPayloadPtr);
    }
#if(ETHTSYN_ICV_USED == STD_ON)
    if(FrameWasTransmitted == FALSE)
    {
#endif
      /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
      /* !LINKSTO EthTSyn.EB.BridgeWithGTMnotMgmCPU_FailedSyncFUp, 1 */
      if(RetVal == E_OK)
      {
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
        {
#endif
          /* Fill PTP header */
          EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
        }
        else
        {
          /* If a transparent clock is used copy the received frame */
          TS_MemCpy(PTPPayloadPtr, &EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrame, EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrameLength);
        }
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */
        /* Prepare frame for transmission */

        EthTSyn_Inc02_PrepareSwtFUpForTx(EthTSynCtrlIdx, PortIdx, SubTlvSize, NsLow, &PTPPayloadPtr[0U], BufIdx);
#if(ETHTSYN_ICV_USED == STD_ON)
        if(((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_GENERATION_FAILED_MASK) != FALSE) &&
           (ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout > 0U))
        {
          P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) TmpPTPPayloadPtr;
          /* If generation fails, buffer needs to be requested */
          RetVal = EthTSyn_Inc02_GetSwtTxBuffer
          (EthTSynCtrlIdx, PTPHeader.MsgLength, PortIdx, &BufIdx, &TmpPTPPayloadPtr);
          if(RetVal == E_OK)
          {
            /* Copy the data to be transmitted */
            TS_MemCpy(TmpPTPPayloadPtr, PTPPayloadPtr, PTPHeader.MsgLength);
          }
          /* Set to IDLE. */
          TS_AtomicAssign8
          (
            EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv,
            ETHTSYN_AUTH_GENERATION_IDLE
          );
          /* Confirmation of transmission needed to be passed to FVM */
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = BufIdx;
        }
        if((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_WAIT_FOR_INDICATION_MASK) == FALSE)
        {
          /* !LINKSTO EthTSyn.EB.EthIf_Return_NotOk, 2 */
          if(E_OK == RetVal)
          {
#endif /* ETHTSYN_ICV_USED == STD_ON */
          /* !LINKSTO EthTSyn.EB.EthSwt_TransmitSyncFupFrameOnPorts, 1 */
          /* !LINKSTO EthTSyn.EB.SwtTransmit_SyncFUP_ICV, 1 */
          RetVal = EthTSyn_Inc02_TransmitSwtFrame
                    (EthTSynCtrlIdx, BufIdx, FALSE, PortIdx, FALSE, PTPHeader.MsgLength, FALSE);
          /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
          if(E_OK == RetVal)
          {
            /* !LINKSTO EthTSyn.Dsn.PortSynTxState_READY_FUP-IDLE, 1 */
            TS_AtomicAssign8
            (
              EthTSyn_SwitchPorts[PortIdx].SyncTxState,
              ETHTSYN_PORT_SYN_TX_STATE_IDLE
            );

            /* clear the flag */
            TS_AtomicClearBit_8
            (
              &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
              ETHTSYN_BITPOS_TX_FUP
            );

            EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
          }
          else if(EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries > 0U)
          {
            /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
            EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries--;
          }
          else
          {
            /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
            /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
            EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

            /* !LINKSTO EthTSyn.Dsn.PortSynTxState_READY_FUP-IDLE, 1 */
            TS_AtomicAssign8
            (
              EthTSyn_SwitchPorts[PortIdx].SyncTxState,
              ETHTSYN_PORT_SYN_TX_STATE_IDLE
            );

            /* clear the flag */
            TS_AtomicClearBit_8
            (
              &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
              ETHTSYN_BITPOS_TX_FUP
            );
          }
#if(ETHTSYN_ICV_USED == STD_ON)
          }
        }
        else
        {
           /* clear the flag, indication is pending. */
          TS_AtomicClearBit_8
          (
            &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
            ETHTSYN_BITPOS_TX_FUP
          );
        }
#endif /* ETHTSYN_ICV_USED == STD_ON */
      }
      for(
           Idx =  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
           Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount
               +  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
           Idx++
         )
      {
        TS_AtomicAssign8
        (
            PortSynTxState,
            EthTSyn_SwitchPorts[Idx].SyncTxState
        );

        if(ETHTSYN_PORT_SYN_TX_STATE_IDLE == PortSynTxState)
        {
          PortIdleCounter++;
        }
      }

      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == PortIdleCounter)
      {
        /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_PORT_READY_FUP-IDLE, 1 */
        /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_PORT_READY-IDLE, 1 */
        EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
      }
#if(ETHTSYN_ICV_USED == STD_ON)
    }
#endif
  }
  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtPdelayReqFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
)
{
  Std_ReturnType TmpRet;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  uint16 PdelayReqSequNumber;
  EthTSyn_PortSyncTxStateType PortPdelayTxState;
  EthTSyn_IntPortIdxType PortIdleCounter = 0U;
  EthTSyn_IntPortIdxType Idx;


  TS_AtomicAssign16(PdelayReqSequNumber, EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber);
  /* Increment sequence number. The Sequence Counter shall wrap around at 65535 to 0 again. */
  /* !LINKSTO EthTSyn.PRS_TS_00188, 1 */
  if(ETHTSYN_SEQ_NUM_MAX == PdelayReqSequNumber)
  {
    /* The first transmission of the Pdelay_Req frame shall contain seqId 0.*/
    /* !LINKSTO EthTSyn.PRS_TS_00187_PdelayReq, 1 */
    PdelayReqSequNumber = 0U;
  }
  else
  {
    PdelayReqSequNumber++;
  }
  TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReqSequNumber, PdelayReqSequNumber);

  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_NOFLAGS;
  PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_PDELAY;

  /* Set sequence number. */
  PTPHeader.SequNumber = PdelayReqSequNumber;

  PTPHeader.LogMsgInterval
    = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayTxMsgLogInterval;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE;

  /* !LINKSTO EthTSyn.EB.TransparentClock_PdelayReqTransmission_FailedBuffer, 1 */
  TmpRet = EthTSyn_Inc02_GetSwtTxBuffer
      (EthTSynCtrlIdx, PTPHeader.MsgLength, PortIdx, &BufIdx, &PTPPayloadPtr);

  if(E_OK == TmpRet)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);

    /* Set PTP payload */
    /* All bytes are reserved. */
    TS_MemBZero(&PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE], ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE);
#if(ETHTSYN_MAX_SLAVE != 0U)
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(
        (TRUE == EthTSyn_IsSlave(EthTSynCtrlIdx)) &&
        (EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].TimeValidationEnabled == TRUE)
        )
      {
        StbM_TimeStampType StbMTimeStamp;
        StbM_UserDataType UserData;
        /* Save the value of the Virtual Local Time of the reference Global Time Tuple
         *  - referenceLocalTimestamp*/
        /* Save the value of the local instance of the Global Time of the reference
         *  Global Time Tuple referenceGlobalTimestamp */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00223, 1 */
        (void)StbM_BusGetCurrentTime
        (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
            &StbMTimeStamp,
            &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceLocalTimestamp,
            &UserData
        );
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceGlobalTimestamp.
          nanoseconds = StbMTimeStamp.nanoseconds;
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.referenceGlobalTimestamp.
          seconds     = StbMTimeStamp.seconds;
        /* Save the Sequence Id of sent Pdelay_Req frame */
       TS_AtomicAssign8
        (
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.sequenceId,
        PdelayReqSequNumber
        );

        /* Save the sourcePortId of sent Pdelay_Req frame*/
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity =
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.clockIdentity |=
          (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.portNumber =
          (uint16)(((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
        EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestPortId.portNumber |=
          (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
      }
#endif/* ETHTSYN_TIME_RECORDING == STD_ON */
#endif/* ETHTSYN_MAX_SLAVE != 0U */
    TmpRet = EthTSyn_Inc02_TransmitSwtFrame(EthTSynCtrlIdx, BufIdx, TRUE, PortIdx, TRUE, PTPHeader.MsgLength, TRUE);

    if(E_OK == TmpRet)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYREQ
      );
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
      EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* Set source port identity to find corresponding Pdelay response and Pdelay response follow
         up frames. */
      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();
      TS_MemCpy(
                 &EthTSyn_Ctrl[EthTSynCtrlIdx].Pdelay_Tx_SrcPortIdentity[0U],
                 &PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
                 ETHTSYN_SOURCEPORTIDENTITY_SIZE
               );
      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_0();

      EthTSyn_Ctrl[EthTSynCtrlIdx].PdelayReq_BufIdx = BufIdx;

      /* Set wait timeout for frame to transmit. */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
        = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval;
#if(ETHTSYN_MAX_SLAVE != 0U)
      /* A pdelay calculation is started */
      TS_AtomicSetBit_8
      (
        &EthTSyn_Slave[EthTSynCtrlIdx].CalculatePdelay,
        ETHTSYN_BITPOS_PDELAYREQ_SENT
      );
#endif /* (ETHTSYN_MAX_SLAVE != 0U) */

      /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayResp_WaitEgress, 1 */
      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[PortIdx].PdelayState,
        ETHTSYN_PORT_PDELAY_WAIT_EGRESS_TS
      );
    }
    else if(EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries > 0U)
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
      EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries--;
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
      EthTSyn_SwitchPorts[PortIdx].EthTSynMaxNumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYREQ
      );

      EthTSyn_Inc02_ResetPortPdelayVars(PortIdx);
    }
  }
  else
  {
    /* Reset the state machine if something happened with swt driver (TmpRet != E_OK)*/
    /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
    EthTSyn_Inc02_ResetPortPdelayVars(PortIdx);
    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
      ETHTSYN_BITPOS_PDELAYREQ
    );
  }

  for(
     Idx =  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
     Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount
         +  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
     Idx++
   )
  {
    TS_AtomicAssign8
    (
      PortPdelayTxState,
      EthTSyn_SwitchPorts[Idx].PdelayState
    );

    if(ETHTSYN_PORT_PDELAY_STATE_IDLE == PortPdelayTxState)
    {
      PortIdleCounter++;
    }
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == PortIdleCounter)
  {
    /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_PORT_READY_FUP-IDLE, 1 */
    /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_PORT_READY-IDLE, 1 */
    EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);

    /* Set wait timeout for frame to transmit. */
    EthTSyn_Ctrl[EthTSynCtrlIdx].SendNextPdelayReqFrame_Timeout
      = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval;
  }

  return TmpRet;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtPdelayRespFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
)
{
  Std_ReturnType TmpRet;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  EthTSyn_PortSyncTxStateType PortPdelayTxState;
  EthTSyn_IntPortIdxType PortIdleCounter = 0U;
  EthTSyn_IntPortIdxType Idx;


  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_FLAG_TWOSTEP;
  PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_PDELAY;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00191_PdelayResp, 1 */
  TS_AtomicAssign16(
                     PTPHeader.SequNumber,
                     EthTSyn_SwitchPorts[PortIdx].Ingress_PdelayReqSequNumber
                   );
  /* Reserved value (See 802.1AS-2011 Ch 11.4.2.8) */
  PTPHeader.LogMsgInterval = ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE;

  /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayResp_Transmit, 1 */
  TmpRet = EthTSyn_Inc02_GetSwtTxBuffer
      (EthTSynCtrlIdx, PTPHeader.MsgLength, PortIdx, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
  if(E_OK == TmpRet)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);

#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
    /* If the EthTSyn portid is configured update the portid bytes form the sourceportid field. */
    if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId != 0xFFFFU)
    {
      /* 16 bit port number */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8] =
        (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_MSB) >> 8U);
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9] =
        (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_LSB));
    }
#endif
    /* Set PTP payload */
    EthTSyn_TimeStampToArray(
                              &EthTSyn_SwitchPorts[PortIdx].IngPdelayFrameTimeStamp,
                              &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE]
                            );

    TS_MemCpy(
               &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE],
               &EthTSyn_SwitchPorts[PortIdx].Pdelay_Rx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
#if(ETHTSYN_TIME_RECORDING == STD_ON)
    if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].TimeValidationEnabled == TRUE)
    {
        StbM_UserDataType UserData;
        StbM_TimeStampType StbMTimeStamp;

        (void)StbM_BusGetCurrentTime
          (
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
            &StbMTimeStamp, /* timeStampPtr */
            &EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.referenceLocalTimestamp, /* localTimePtr */
            &UserData /* userDataPtr */
          );

        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.referenceGlobalTimestamp.
            nanoseconds = StbMTimeStamp.nanoseconds;
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.referenceGlobalTimestamp.
            seconds = StbMTimeStamp.seconds;
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity =
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)(((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.clockIdentity |=
             (uint64)((uint64) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.portNumber =
             (uint16)(((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
        EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responsePortId.portNumber |=
             (uint16)((uint16) PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
    }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
    /* !LINKSTO EthTSyn.PRS_TS_00012, 1 */
    TmpRet = EthTSyn_Inc02_TransmitSwtFrame(EthTSynCtrlIdx, BufIdx, TRUE, PortIdx, TRUE, PTPHeader.MsgLength, TRUE);
  }
  if(E_OK == TmpRet)
  {
    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
      ETHTSYN_BITPOS_PDELAYRESP
    );

    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

    /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayResp_WaitEgress, 1 */
    /* !LINKSTO EthTSyn.Dsn.PortPdelayState_IDLE-WAIT_EGRESS, 1 */
    TS_AtomicAssign8
    (
      EthTSyn_SwitchPorts[PortIdx].PdelayState,
      ETHTSYN_PORT_PDELAY_WAIT_EGRESS_TS
    );
  }
  else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
  }
  else
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */

    /* clear the flag */
    TS_AtomicClearBit_8
    (
      &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
      ETHTSYN_BITPOS_PDELAYRESP
    );

    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

    /* Reset the state machine if something happened with swt driver (TmpRet != E_OK)*/
    /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
    EthTSyn_Inc02_ResetPortPdelayVars(PortIdx);
  }

  for(
   Idx =  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
   Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount
       +  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
   Idx++
  )
  {
    TS_AtomicAssign8
    (
      PortPdelayTxState,
      EthTSyn_SwitchPorts[Idx].PdelayState
    );

    if(ETHTSYN_PORT_PDELAY_STATE_IDLE == PortPdelayTxState)
    {
      PortIdleCounter++;
    }
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == PortIdleCounter)
  {
    /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_PORT_READY_FUP-IDLE, 1 */
    /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_PORT_READY-IDLE, 1 */
    EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
  }

  return TmpRet;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtPdelayRespFupFramePerPort
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
)
{
  Std_ReturnType TmpRet;
  Eth_BufIdxType BufIdx = 0U;
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) PTPPayloadPtr;
  EthTSyn_PTPHeaderType PTPHeader;
  EthTSyn_PortSyncTxStateType PortPdelayTxState;
  EthTSyn_IntPortIdxType PortIdleCounter = 0U;
  EthTSyn_IntPortIdxType Idx;


  /* Prepare PTP header. */
  PTPHeader.Flags = ETHTSYN_PTP_HEADER_NOFLAGS;
  PTPHeader.Flags |= ETHTSYN_PTP_HEADER_FLAG_PTPTIMESCALE;
  PTPHeader.MsgType = ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP;
  PTPHeader.Control = ETHTSYN_PTP_HEADER_CONTROL_PDELAY;

  /* Set sequence number. */
  /* !LINKSTO EthTSyn.PRS_TS_00191_PdelayRespFup, 1 */
  TS_AtomicAssign16(
                     PTPHeader.SequNumber,
                     EthTSyn_SwitchPorts[PortIdx].Ingress_PdelayReqSequNumber
                   );
  /* Reserved value (See 802.1AS-2011 Ch 11.4.2.8) */
  PTPHeader.LogMsgInterval = ETHTSYN_PTP_HEADER_LOGMSGINTERVAL_RESERVED;

  PTPHeader.MsgLength = ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE;

  /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayRespFup_Transmit, 1 */
  TmpRet = EthTSyn_Inc02_GetSwtTxBuffer
      (EthTSynCtrlIdx, PTPHeader.MsgLength, PortIdx, &BufIdx, &PTPPayloadPtr);

  /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
  if(E_OK == TmpRet)
  {
    /* Fill PTP header */
    EthTSyn_FillPTPHeader(EthTSynCtrlIdx, &PTPHeader, &PTPPayloadPtr[0U]);

#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
    /* If the EthTSyn portid is configured update the portid bytes form the sourceportid field. */
    if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId != 0xFFFFU)
    {
      /* 16 bit port number */
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8] =
        (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_MSB) >> 8U);
      PTPPayloadPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9] =
        (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_LSB));
    }
#endif

    /* Set PTP payload */
    EthTSyn_TimeStampToArray(
                              &EthTSyn_SwitchPorts[PortIdx].EgressPdelayFrameTimeStamp,
                              &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE]
                            );

    TS_MemCpy(
               &PTPPayloadPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE],
               &EthTSyn_SwitchPorts[PortIdx].Pdelay_Rx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );

    /* !LINKSTO EthTSyn.PRS_TS_00012, 1 */
    TmpRet = EthTSyn_Inc02_TransmitSwtFrame(EthTSynCtrlIdx, BufIdx, TRUE, PortIdx, FALSE, PTPHeader.MsgLength, FALSE);

    /* !LINKSTO EthTSyn.EB.EthSwt_Return_NotOk, 1 */
    if(E_OK == TmpRet)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYRESP_FUP
      );
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* Pass the responder data to the StbM. */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].TimeValidationEnabled == TRUE)
      {
        /* Convert the egress timestamp. */
        /* !LINKSTO EthTSyn.SWS_EthTSyn_00225, 1 */
        (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime(&EthTSyn_SwitchPorts[PortIdx].EgressPdelayFrameTimeStamp,
           &EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording.responseOriginTimestamp);

        (void)StbM_EthSetPdelayResponderData
            (
                EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
                /* !LINKSTO EthTSyn.SWS_EthTSyn_00220, 1 */
                &EthTSyn_SwitchPorts[PortIdx].PdelayResponderTimeRecording
            );
      }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */

      /* Reset port pdelay variables */
      /* !LINKSTO EthTSyn.Dsn.PortPdelayState_WAIT_EGRESS-IDLE, 1 */
      EthTSyn_Inc02_ResetPortPdelayVars(PortIdx);
    }
    else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
    }
    else
    {
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
      /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
      EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_PDELAYRESP_FUP
      );

      /* Reset port pdelay variables */
      /* !LINKSTO EthTSyn.Dsn.PortPdelayState_WAIT_EGRESS-IDLE, 1 */
      EthTSyn_Inc02_ResetPortPdelayVars(PortIdx);
    }
  }

  for(
   Idx =  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
   Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount
       +  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
   Idx++
  )
  {
    TS_AtomicAssign8
    (
      PortPdelayTxState,
      EthTSyn_SwitchPorts[Idx].PdelayState
    );

    if(ETHTSYN_PORT_PDELAY_STATE_IDLE == PortPdelayTxState)
    {
      PortIdleCounter++;
    }
  }

  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == PortIdleCounter)
  {
    /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_PORT_READY_FUP-IDLE, 1 */
    /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_PORT_READY-IDLE, 1 */
    EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
  }

  return TmpRet;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_GetSwtTxBuffer
(
  uint8 EthTSynCtrlIdx,
  uint16 PayloadLength,
  EthTSyn_IntPortIdxType IntPortIdx,
  P2VAR(Eth_BufIdxType, AUTOMATIC, ETHTSYN_APPL_DATA) BufIdxPtr,
  P2VAR(EthTSyn_PtrUint8, AUTOMATIC, ETHIF_APPL_DATA) BufPtr
)
{
  uint16 BufferSize = PayloadLength;
  Std_ReturnType RetVal = E_NOT_OK;
  BufReq_ReturnType RetVal_BufReq;
  EthSwt_MgmtInfoType MgmtInfo;


  MgmtInfo.SwitchIdx = (uint8)EthTSyn_RootCfgPtr->SwitchConfig[IntPortIdx].EthSwtIdx;
  MgmtInfo.SwitchPortIdx = (uint8)EthTSyn_RootCfgPtr->SwitchConfig[IntPortIdx].EthSwtPortIdx;

  /* !LINKSTO EthTSyn.EB.Master.FrameType, 1 */
  RetVal_BufReq = EthSwt_ProvideTxBuffer
  (
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, /* EthIf CtrlIdx */
    ETHTSYN_PTP_FRAMETYPE, /* FrameType */
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].FramePriority, /* Priority */
    &MgmtInfo, /* EthSwt_MgmtInfoType */
    BufIdxPtr, /* BufIdxPtr */
    BufPtr, /* BufPtr */
    &BufferSize /* LenBytePtr */
  );

  /* !LINKSTO EthTSyn.EB.EthSwt_ProvideTxBuffer.NULL_PTR, 1 */
  if((BUFREQ_OK == RetVal_BufReq) && (*BufPtr != NULL_PTR))
  {
    RetVal = E_OK;
  }


  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtFrame
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
  boolean RequestTimeStamp,
  EthTSyn_IntPortIdxType IntPortIdx,
  boolean ActivateTimeStamp,
  uint16 LenByte,
  boolean IsPdelayResp
)
{
  uint8 DestMacAddr[ETHTSYN_MAC_ADD_SIZE];
  Std_ReturnType RetVal;
  uint32 UniqueId;
  EthSwt_MgmtInfoType MgmtInfo;


  /* !LINKSTO EthTSyn.ECUC_EthTSyn_00058_Conf, 1 */
  TS_MemCpy(DestMacAddr, EthTSyn_DestMacAddr, ETHTSYN_MAC_ADD_SIZE);

#if(ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  if(ActivateTimeStamp == TRUE)
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00202, 1 */
    EthIf_EnableEgressTimeStamp
    (
      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx,
      BufIdx
    );
  }
#else
  TS_PARAM_UNUSED(ActivateTimeStamp);
#endif /* ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON */

  MgmtInfo.SwitchIdx = (uint8)EthTSyn_RootCfgPtr->SwitchConfig[IntPortIdx].EthSwtIdx;
  MgmtInfo.SwitchPortIdx = (uint8)EthTSyn_RootCfgPtr->SwitchConfig[IntPortIdx].EthSwtPortIdx;

  /* !LINKSTO EthTSyn.EB.Master.FrameType, 1 */
  RetVal = EthSwt_PtpTransmit
  (
    EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, /* EthIf CtrlIdx */
    BufIdx, /* BufIdx */
    &MgmtInfo,
    &UniqueId,
    RequestTimeStamp, /* RequestTimeStamp */
    ETHTSYN_PTP_FRAMETYPE, /* FrameType */
    &DestMacAddr[0U], /* PhysAddrPtr */
    LenByte /* Length of frame in bytes */
  );

  if((E_OK == RetVal) && (RequestTimeStamp == TRUE))
  {
    if(IsPdelayResp == FALSE)
    {
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
      EthTSyn_SwitchPorts[IntPortIdx].UniqueId = UniqueId;
#else
      uint8 Idx;
      for(
          Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
          Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
          Idx++
         )
      {
        /* If EthTSynSendSyncFrameOnlyOnHostPort set to true the uniqueid returned
           from transmission of sync frame on host port will be added to all other
           non host ports. */
         EthTSyn_SwitchPorts[Idx].UniqueId = UniqueId;
      }
#endif/* (ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF) */
    }
    else
    {
      /* Save the uniqueId to identify the egress timestamp */
      /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayResp_SaveUniqueId, 1 */
      EthTSyn_SwitchPorts[IntPortIdx].PdelayUniqueId = UniqueId;
    }
  }


  return RetVal;
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_SwtCorrField
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx,
  P2VAR(uint32, AUTOMATIC, ETHTSYN_VAR) CalculatedCorrection
)
{
  Std_ReturnType ValidCorrValue = E_NOT_OK;
  Eth_TimeIntDiffType TimeCorrection;

  EthTSyn_SubTimeStamps
  (
    &EthTSyn_SwitchPorts[PortIdx].SyncTimeStamp,
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
    &EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTimeStamp,
#else
    &EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].SyncTimeStamp,
#endif
    &TimeCorrection
  );
  if(
      (TimeCorrection.diff.nanoseconds <= ETHTSYN_NANOSEC_MAX) &&
      (TimeCorrection.diff.secondsHi == 0U) &&
      (TimeCorrection.sign == TRUE) &&
      (TimeCorrection.diff.seconds < 4U)
    )
  {
    *CalculatedCorrection = ((ETHTSYN_NANOSEC_MAX + 1U) * TimeCorrection.diff.seconds) + TimeCorrection.diff.nanoseconds;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
    /* If a transparent clock is used, add the pathdelay to the correction field. */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == TRUE)
    {
      /* add to the correction field tha calculated pathDelay between the GTM and the switch. */
       *CalculatedCorrection += EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
    }
#endif
    ValidCorrValue = E_OK;
  }
  else
  {
    ValidCorrValue = E_NOT_OK;
  }
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].TimeValidationEnabled == TRUE)
  {
    /* If timevalidation enabled, save the correction */
    EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.correctionField = *CalculatedCorrection;
  }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
  return ValidCorrValue;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_SwtSynStateHandling
(
  uint8 EthTSynCtrlIdx
)
{
  EthTSyn_CtrlSyncTxStateType SyncTxState;
  TS_AtomicAssign8
  (
    SyncTxState,
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState
  );

  switch(SyncTxState)
  {
    case ETHTSYN_CTRL_SYN_TX_STATE_IDLE:
    case ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_ETH_EGRESS_TS:
    {
      /* Nothing to do in main function. */
      break;
    }
    case ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_SYN_TO_PORT:
    {
      uint8 Idx;
      ETHTSYN_SET_TXFLAG
       (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);

      for(
            Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
            Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
            Idx++
         )
      {
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
        if((Idx != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt) &&
           (Idx != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave)
          )
#else
        if(Idx != EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt)
#endif
        {
          TS_AtomicSetBit_8
          (
            &EthTSyn_SwitchPorts[Idx].Frame2Transmit,
             ETHTSYN_BITPOS_TX_SYNC
          );
        }
      }

      /* No retry performed if sync Tx is not okay for a single port. */
      /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_READY_SYN_TO_PORT-WAIT_SWT_INGRESS, 1 */
      /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_READY-WAIT_INGRESS, 1 */
      TS_AtomicAssign8
      (
        EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
        ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_SWT_INGRESS_TS
      );
      break;
    }
    case ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_SWT_INGRESS_TS:
    {
      EthTSyn_PortSyncTxStateType PortSynTxState;

      TS_AtomicAssign8
      (
        PortSynTxState,
        EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState
      );

      if(ETHTSYN_PORT_SYN_TX_STATE_VALID_INGRESS_TS == PortSynTxState)
      {
        /* !LINKSTO EthTSyn.Dsn.HostPortSynTxState_VALID_INGRESS-IDLE, 1 */
        TS_AtomicAssign8
        (
          EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState,
          ETHTSYN_PORT_SYN_TX_STATE_IDLE
        );
        /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_VALID_INGRESS-READY_FUP, 1 */
        /* !LINKSTO EthTSyn.Dsn.HostPortSynTxState_VALID_INGRESS-IDLE, 1 */
        /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_VALID_INGRESS-READY_FUP, 1 */
        TS_AtomicAssign8
        (
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
          ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_FUP
        );
      }
      break;
    }
    case ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_FUP:
    {
      EthTSyn_PortSyncTxStateType Idx;
      EthTSyn_PortSyncTxStateType PortSynTxState;
#if(ETHTSYN_ICV_USED == STD_ON)
      if((ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout == 0U) ||
        /* Deviation TASKING-3 */
        ((ETHTSYN_ROOTCFG(EthTSynCtrlIdx).EthTSynIcvGenerationTimeout > 0U) && ((EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv & ETHTSYN_AUTH_WAIT_FOR_INDICATION_MASK) == FALSE))
        )
      {
        {
  #endif
          for(
                Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 1U;
                Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                      EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
                Idx++
             )
          {
            TS_AtomicAssign8
            (
              PortSynTxState,
              EthTSyn_SwitchPorts[Idx].SyncTxState
            );
            /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_CTRL_READY_FUP-PORT_READY_FUP, 1 */
            /* !LINKSTO EthTSyn.EB.BoundaryClock_TransmitSyncFUpOnMasterPorts, 1 */
            if(PortSynTxState == ETHTSYN_PORT_SYN_TX_STATE_READY_FOR_FUP)
            {
              ETHTSYN_SET_TXFLAG
                (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);
              TS_AtomicSetBit_8
              (
                &EthTSyn_SwitchPorts[Idx].Frame2Transmit,
                ETHTSYN_BITPOS_TX_FUP
              );
            }
          }
  #if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
          /* If the egress timestamp on the host port was received, we can proceed with the synchronization */
          if(EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState == ETHTSYN_PORT_READY_FOR_TIME_SYNC)
          {
            uint8 PortIdx;
            uint8 PortIdleCounter = 0U;

            /* Sync the slave */
            /* !LINKSTO EthTSyn.EB.TransparentClock_Synchronize_EgressHostPortAfterSyncFUp, 1 */
            /* !LINKSTO EthTSyn.EB.TransparentClock_Synchronize_EgressHostPortAfterSyncFUpFW, 1 */
            EthTSyn_Inc02_SynchronizeBridge(&EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr, EthTSynCtrlIdx);

            /* Sync performed, don't retry on the mainfunction, reset the state for the host port */
            TS_AtomicAssign8
            (
                EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState,
                ETHTSYN_PORT_SYN_TX_STATE_IDLE
            );

            /* If the timestamp for the host port was provided after the transmission of the fup frame, the ctrl SM must be reset */
            for(
                 PortIdx =  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
                 PortIdx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount
                     +  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
                 PortIdx++
               )
            {
              TS_AtomicAssign8
              (
                  PortSynTxState,
                  EthTSyn_SwitchPorts[PortIdx].SyncTxState
              );

              if(ETHTSYN_PORT_SYN_TX_STATE_IDLE == PortSynTxState)
              {
                PortIdleCounter++;
              }
            }

            if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == PortIdleCounter)
            {
              /* !LINKSTO EthTSyn.Dsn.CtrlSynTxState_PORT_READY_FUP-IDLE, 1 */
              /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_PORT_READY-IDLE, 1 */
              EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
            }
          }
  #endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
  #if(ETHTSYN_ICV_USED == STD_ON)
        }
      }
#endif
      break;
    }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
    case ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_BRIDGE_SYNC:
    {
      /* If the egress timestamp on the host port was received, we can proceed with the synchronization */
      if(EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState == ETHTSYN_PORT_READY_FOR_TIME_SYNC)
      {
        /* Sync the slave */
        EthTSyn_Inc02_SynchronizeBridge(&EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr, EthTSynCtrlIdx);
        EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
      }
      break;
    }
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
    /* CHECK: NOPARSE */
    default:
    {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
      ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
#endif
      break;
    }
  /* CHECK: PARSE */
  }
}

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Inc02_TransmitSwtFrameWithDebounce
(
  uint8 EthTSynCtrlIdx,
  uint8 PortIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  if((EthTSyn_SwitchPorts[PortIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_SWT_TX_ON_HOST_MASK) != 0U)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00186, 1 */
    RetVal = EthTSyn_Inc02_TransmitSwtOnHostPortSyncFrame(EthTSynCtrlIdx);
  }
  else if((EthTSyn_SwitchPorts[PortIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_TX_SYNC_MASK) != 0U)
  {
    RetVal = EthTSyn_Inc02_TransmitSwtSyncFramePerPort(EthTSynCtrlIdx, PortIdx);
  }
  /* CHECK: NOPARSE */
  else if((EthTSyn_SwitchPorts[PortIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_TX_FUP_MASK) != 0U)
  {
    RetVal = EthTSyn_Inc02_TransmitSyncSwtFUpFramePerPort(EthTSynCtrlIdx, PortIdx);
  }
  else if((EthTSyn_SwitchPorts[PortIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_PDELAYREQ_MASK) != 0U)
  {
    RetVal = EthTSyn_Inc02_TransmitSwtPdelayReqFramePerPort(EthTSynCtrlIdx, PortIdx);
  }
  else if((EthTSyn_SwitchPorts[PortIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_PDELAYRESP_MASK) != 0U)
  {
    RetVal = EthTSyn_Inc02_TransmitSwtPdelayRespFramePerPort(EthTSynCtrlIdx, PortIdx);
  }
  else if((EthTSyn_SwitchPorts[PortIdx].Frame2Transmit & ETHTSYN_DEBOUNCE_PDELAYRESP_FUP_MASK) != 0U)
  {
    RetVal = EthTSyn_Inc02_TransmitSwtPdelayRespFupFramePerPort(EthTSynCtrlIdx, PortIdx);
  }
  else
  {
#if(ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    ETHTSYN_UNREACHABLE_CODE_ASSERT(ETHTSYN_INTERNAL_SVCID);
    /* nothing to do */
#endif
  }
  /* CHECK: PARSE */
  return RetVal;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ResetPortPdelayVars
(
  uint8 PortIdx
)
{

  TS_AtomicAssign8
  (
    EthTSyn_SwitchPorts[PortIdx].PdelayState,
    ETHTSYN_PORT_PDELAY_STATE_IDLE
  );
  EthTSyn_SwitchPorts[PortIdx].EgressPdelayFrameTimeStamp.nanoseconds = 0U;
  EthTSyn_SwitchPorts[PortIdx].EgressPdelayFrameTimeStamp.seconds = 0U;
  EthTSyn_SwitchPorts[PortIdx].EgressPdelayFrameTimeStamp.secondsHi = 0U;

  EthTSyn_SwitchPorts[PortIdx].IngPdelayFrameTimeStamp.nanoseconds = 0U;
  EthTSyn_SwitchPorts[PortIdx].IngPdelayFrameTimeStamp.seconds = 0U;
  EthTSyn_SwitchPorts[PortIdx].IngPdelayFrameTimeStamp.secondsHi = 0U;
  EthTSyn_SwitchPorts[PortIdx].Ingress_PdelayReqSequNumber = 0U;
  EthTSyn_SwitchPorts[PortIdx].PdelayUniqueId = ETHTSYN_UNIQUE_ID_INVALID;
  TS_MemBZero(
               &EthTSyn_SwitchPorts[PortIdx].Pdelay_Rx_SrcPortIdentity[0U],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
}

#if((ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON))
STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_BridgeCalculateCrcTime1
(
  uint8 EthTSynCtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) Crc_Time_1
)
{
  uint8 Crc_1;
  uint8 SeqNr = (DataPtr[ETHTSYN_PTP_HEADER_B31_SEQUNUMBER_0]) % 16U;

  /* Calculate CRC_Time_1 based using the value of CRC_Time_Flags */
  Crc_1 = Crc_CalculateCRC8H2F(&EthTSyn_Ctrl[EthTSynCtrlIdx].Crc_Time_Flags, 1U, 0U, TRUE);

  /* Calculate CRC_Time_1 based using the length of the message if CRC_Time_Flags has Bitmask 0x01 */
  if((DataPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS] & ETHTSYN_MESSAGE_LENGTH_BIT_MASK) != 0U)
  {
    Crc_1 = Crc_CalculateCRC8H2F(&DataPtr[ETHTSYN_PTP_HEADER_B2_MSGLENGTH_1], 2U, Crc_1, FALSE);
  }

  /* Calculate CRC_Time_1 based using the correctionField */
  Crc_1 = Crc_CalculateCRC8H2F(&DataPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0], 8U, Crc_1, FALSE);

  /* Calculate CRC_Time_1 based using the CRCsequenceId if CRC_Time_Flags has Bitmask 0x10 */
  if((DataPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS] & ETHTSYN_SEQUENCE_ID_BIT_MASK) != 0U)
  {
    Crc_1 = Crc_CalculateCRC8H2F(&DataPtr[ETHTSYN_PTP_HEADER_B30_SEQUNUMBER_1], 2U, Crc_1, FALSE);
  }

  /* Calculate CRC_Time_1 based using the DataId */
  Crc_1 = Crc_CalculateCRC8H2F
            (
              &EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].DataIdList[SeqNr],
              1U, Crc_1, FALSE
            );

  *Crc_Time_1 = Crc_1;
}

#endif /* ((ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)) */
STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxSwtMsg
(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHTSYN_APPL_DATA) MgmtInfoPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint16 Len,
  uint32 UniqueId
)
{
  boolean TimeStampRequired = FALSE;

  /* Extract message type from PTP header. */
  const uint8 MsgType = DataPtr[ETHTSYN_PTP_HEADER_B0_LN_MSGTYPE] & ETHTSYN_8BIT_MASK_LN;
  switch(MsgType)
  {
    case ETHTSYN_PTP_HEADER_MSGTYPE_SYNC:
    {
      /* !LINKSTO EthTSyn.EB.EthSwt_ReceiveSyncFrameOnSlavePort, 1 */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
      uint16 FrameLen = ETHTSYN_GET16(DataPtr, 2U);
      /* !LINKSTO EthTSyn.EB.EthSwtRx_Sync_IncorrectLength, 2 */
      /* !LINKSTO EthTSyn.EB.SyncFrame_IncorrectLenBytes, 1 */
      if((Len >= ETHTSYN_SYNC_FRAME_SIZE) && (FrameLen == 44U))
      {
        /* !LINKSTO EthTSyn.EB.EthSwtPtpRxIndication_Incorrect_MgmtInfo, 1 */
        /* Sync frame can be received only on the slave port */
        if(
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtIdx == MgmtInfoPtr->SwitchIdx
            )
          &&
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtPortIdx == MgmtInfoPtr->SwitchPortIdx
            )
          &&
             /* Check if the received timestamp is valid. */
             /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
            (
              IngressTimeStampPtr->nanoseconds <= ETHTSYN_NANOSEC_MAX
            )
         )
         {
#if((ETHTSYN_DEV_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON))
          Std_ReturnType TmpRet = E_NOT_OK;
          /* The validation is done if the simple bridge is configured to validate the sync frame or
             if a boundary clock is used. */
          if((EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridgeValidateSync == TRUE) ||
            (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE))
          {
            if(EthTSyn_Slave[EthTSynCtrlIdx].SaveSrcPortId == TRUE)
            {
              /* When the first sync frame is received, save the sourceportid, in order to be able to detect
                 parallel masters. */
              TS_MemCpy(
                 &EthTSyn_Slave[EthTSynCtrlIdx].Sync_Rx_SrcPortIdentity[0U],
                 &DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
                 ETHTSYN_SOURCEPORTIDENTITY_SIZE
               );
               EthTSyn_Slave[EthTSynCtrlIdx].SaveSrcPortId = FALSE;
            }

            /* Check source port identity */
            TmpRet = TS_MemCmp(
                      &EthTSyn_Slave[EthTSynCtrlIdx].Sync_Rx_SrcPortIdentity[0U],
                      &DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
                      ETHTSYN_SOURCEPORTIDENTITY_SIZE
                    );
          }
          else
          {
            TmpRet = E_OK;
          }
          if(TmpRet == E_OK)
          {
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */
             /* If a new sync frame is received, reset the state and the previous values.*/
             EthTSyn_ResetSynTxStateMachine(EthTSynCtrlIdx);
             /* If a sync frame is received on the slave port we can proceed with processing the frame */
             TimeStampRequired = EthTSyn_Inc02_ProcessRxSyncSwtMsg(IngressTimeStampPtr, DataPtr, EthTSynCtrlIdx, UniqueId);
#if((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON))
          }
          else
          {
            /* !LINKSTO EthTSyn.SWS_EthTSyn_00146, 2 */
            /* !LINKSTO EthTSyn.EB.TransparentClock_ValidateSync_ScrPortId, 1 */
            ETHTSYN_DET_RUNTIME_REPORT_ERROR(ETHTSYN_SID_ETHSWTPTPRXINDICATION, ETHTSYN_E_TSCONFLICT);
          }
#endif /* (ETHTSYN_DET_RUNTIME_REPORT_ERROR == STD_ON) && (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */
         }
      }
      /* If a sync message is received on the TAB with GTM as Mgm CPU, report an error if configured */
#elif(ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DEM)
      /* !LINKSTO EthTSyn.EB.Diagnostic_UnexpectedSync_DEM, 1 */
      Dem_ReportErrorStatus
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdUnexpectedSync,
        DEM_EVENT_STATUS_FAILED
      );
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */

#if((ETHTSYN_DEV_RUNTIME_ERROR_DETECT == STD_ON) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF))
     /* Report errors (if configured) if a sync frame is received on a time aware with GTM as MGM cpu */
#if(ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00145, 2 */
      ETHTSYN_DET_RUNTIME_REPORT_ERROR
      (
        ETHTSYN_SID_ETHSWTPTPRXINDICATION,
        ETHTSYN_E_TMCONFLICT
      );
#endif /* (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */
#endif /* (ETHTSYN_DET_RUNTIME_REPORT_ERROR == STD_ON) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON) */

#if((ETHTSYN_DEV_ERROR_DETECT == STD_ON) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF))
#if(ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DET)
      /* !LINKSTO EthTSyn.EB.Diagnostic_UnexpectedSync_DET, 1 */
      ETHTSYN_DET_REPORT_ERROR
      (
        ETHTSYN_SID_ETHSWTPTPRXINDICATION,
        ETHTSYN_E_TMCONFLICT_CONFIGURED
      );
#endif /* (ETHTSYN_PROD_ERR_HANDLING_UNEXPECTED_SYNC == TS_PROD_ERR_REP_TO_DET) */

#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON) */
      break;
    }
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
    case ETHTSYN_PTP_HEADER_MSGTYPE_FUP:
    {
      /* !LINKSTO EthTSyn.EB.EthSwtRx_SyncFUp_IncorrectLength, 1 */
      if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE) <= Len)
      {
        /* !LINKSTO EthTSyn.EB.EthSwtPtpRxIndication_Incorrect_MgmtInfo, 1 */
        /* SyncFup frame can be received only on the slave port */
        if(
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtIdx == MgmtInfoPtr->SwitchIdx
            )
          &&
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtPortIdx == MgmtInfoPtr->SwitchPortIdx
            )
         )
         {
            /* If a Fup frame is received on the slave port we can proceed with processing the frame */
            EthTSyn_Inc02_ProcessRxFupSyncSwtMsg(DataPtr, EthTSynCtrlIdx, Len);
            /* No timestamp is required for the Fup frame. */
            TimeStampRequired = FALSE;
         }
        }
      break;
    }

    case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_RESP:
    {
      /* !LINKSTO EthTSyn.EB.EthSwtRx_PdelayResp_IncorrectLength, 1 */
      if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_PAYLOADSIZE) <= Len)
      {
        /* !LINKSTO EthTSyn.EB.TransparentClock_InvalidPdelayRespMgmtInfo, 1 */
        if(
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtIdx == MgmtInfoPtr->SwitchIdx
            )
          &&
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtPortIdx == MgmtInfoPtr->SwitchPortIdx
            )
          &&
            (
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval != 0U
            )
          &&
             /* Check if the received timestamp is valid. */
             /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
            (
              IngressTimeStampPtr->nanoseconds <= ETHTSYN_NANOSEC_MAX
            )
         )
          {
            EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.nanoseconds =  IngressTimeStampPtr->nanoseconds;
            EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.seconds =  IngressTimeStampPtr->seconds;
            EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4.secondsHi =  IngressTimeStampPtr->secondsHi;
            EthTSyn_ProcessRxPdelayRespFrame(EthTSynCtrlIdx, DataPtr);
#if(ETHTSYN_TIME_RECORDING == STD_ON)
            if(EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].TimeValidationEnabled == TRUE)
            {
              /* requestReceiptTimeStamp as received in pdelay_Response message */
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
                  seconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.seconds;
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.requestReceiptTimestamp.
                  nanoseconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t2.nanoseconds;

              /* Converted value of the responseReceiptTimestamp */
              (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
                  (
                      &EthTSyn_Slave[EthTSynCtrlIdx].Pdelay_TimeStamp_t4,
                      &EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responseReceiptTimestamp
                  );

              /* Save the sourcePortId of sent Pdelay_Req frame*/
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                     = (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.clockIdentity
                    |= (uint64)((uint64) DataPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.portNumber =
                   (uint16)(((uint16) DataPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
              EthTSyn_Slave[EthTSynCtrlIdx].PdelayInitiatorTimeRecording.responsePortId.portNumber |=
                   (uint16)((uint16) DataPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);

            }
#endif
            /* Update PdelayRespAndRespFollowUpTimeout(waiting for Pdelay_Resp) */
            /* !LINKSTO EthTSyn.PRS_TS_00164.PdelayRespTimeout, 1 */
            EthTSyn_Slave[EthTSynCtrlIdx].PdelayFollowUpTimeout
              = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayRespAndRespFollowUpTimeout;
          }
      }
      break;
    }
    case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_FUP:
    {
      /* !LINKSTO EthTSyn.EB.EthSwtRx_PdelayRespFUp_IncorrectLength, 1 */
      if((ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_RESP_FUP_PAYLOADSIZE) <= Len)
      {
        /* !LINKSTO EthTSyn.EB.TransparentClock_InvalidPdelayRespFUpMgmtInfo, 1 */
        if(
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtIdx == MgmtInfoPtr->SwitchIdx
            )
          &&
            (
              EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
              EthSwtPortIdx == MgmtInfoPtr->SwitchPortIdx
            )
          &&
            (
              EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PdelayReqTxInterval != 0U
            )
         )
        {
          /* !LINKSTO EthTSyn.EB.Master.RxIndication, 1 */
          EthTSyn_ProcessRxPdelayRespFUpFrame(EthTSynCtrlIdx, DataPtr);
        }
      }
      break;
    }
#endif/* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */
    case ETHTSYN_PTP_HEADER_MSGTYPE_PDELAY_REQ:
    {
      /* !LINKSTO EthTSyn.EB.EthSwtRx_PdelayReq_IncorrectLength, 1 */
      if(
          (
            (ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_PDELAY_REQ_PAYLOADSIZE) <= Len
          )
         &&
           /* Check if the received timestamp is valid. */
           /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
          (
            IngressTimeStampPtr->nanoseconds <= ETHTSYN_NANOSEC_MAX
          )
        )
      {
        EthTSyn_Inc02_ProcessRxPdelayReqSwtMsg(MgmtInfoPtr, IngressTimeStampPtr, DataPtr, EthTSynCtrlIdx, Len);
        TS_PARAM_UNUSED(UniqueId);
        TimeStampRequired = FALSE;
      }
      break;
    }

    default:
    {
      /* !LINKSTO EthTSyn.EB.EthSwtPtpRxIndication_UnknownFrameType, 1 */
      /* Unknown message type: Ignore */
      break;
    }
  }
  return TimeStampRequired;
}
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
STATIC FUNC(boolean, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxSyncSwtMsg
(
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint32 UniqueId
)
{
  uint8 Idx = 0U;
  boolean TimeStampRequired = FALSE;
  /* Save the ingress timestamp for the slave port */
  /* Save the ingress timestamp in order to calculate the origintimestamp. */
  EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
                     SyncTimeStamp.nanoseconds = IngressTimeStampPtr->nanoseconds;
  EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
                     SyncTimeStamp.seconds = IngressTimeStampPtr->seconds;
  EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].
                     SyncTimeStamp.secondsHi = IngressTimeStampPtr->secondsHi;

  /* Process received sync frame */
  EthTSyn_Inc02_ProcessRxSyncFrame(DataPtr, EthTSynCtrlIdx);
  /* The sync message was successfully processed*/
  if(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived == TRUE)
  {
    /* If a transparent clock is used, and the sync message was successfully processed */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == TRUE)
    {
      /* EthSwt will handle the fowarding of the frames */
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridgeTSynSendSync == FALSE)
      {
        /* Save the uniqueid for all master ports for the current timedomain. */
        for(
            Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 2U;
            Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
            Idx++
           )
        {
          /* Use the uniqueid to identify the egress timestamps for the master ports. */
          EthTSyn_SwitchPorts[Idx].UniqueId = UniqueId;
          /* If the sync was received, the EthSwt already transmitted the sync to the
             master ports, therefore we can wait for the egress timestamps.*/
          TS_AtomicAssign8
          (
              EthTSyn_SwitchPorts[Idx].SyncTxState,
              ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS
          );
        }
        /* Wait for the egress timestamps. */
        /* !LINKSTO EthTSyn.Dsn.CtrlSynBridge_IDLE-READY, 1 */
        TS_AtomicAssign8
        (
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
          ETHTSYN_CTRL_SYN_TX_STATE_WAIT_FOR_ETH_EGRESS_TS
        );
      }
      else
      {
        /* !LINKSTO EthTSyn.EB.TransparentClock_EthTSynSendSync, 1 */
        TS_MemCpy(&EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedSyncFrame[0], &DataPtr[0], ETHTSYN_SYNC_FRAME_SIZE);
        if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeDebounceTime != 0U)
        {

#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
          uint8 PortIdx;
         /* Transmit sync frames to the connected slaves on the mainfunction */
          for(
              PortIdx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 2U;
              PortIdx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
              PortIdx++
             )
          {
            TS_AtomicSetBit_8
            (
              &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
              ETHTSYN_BITPOS_TX_SYNC
            );
          }

#else
          /* !LINKSTO EthTSyn.EB.TransparentClock_SyncOnHost, 1 */
          TS_AtomicSetBit_8
          (
            &EthTSyn_SwitchPorts
               [EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].Frame2Transmit,
            ETHTSYN_BITPOS_TX_SYNC_ON_HOST
          );
#endif/* ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF */
         /* The transmission will be done on the mainfunction */
         ETHTSYN_SET_TXFLAG
            (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);
        }
        else
        {
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
          /* If the debounce is 0 transmit the sync */
          for(
              Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 2U;
              Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
                  EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart);
              Idx++
             )
          {
            /* Transmit the sync to the connected slave ports */
            (void)EthTSyn_Inc02_TransmitSwtSyncFramePerPort(EthTSynCtrlIdx, Idx);
          }
#else
          (void)EthTSyn_Inc02_TransmitSwtOnHostPortSyncFrame(EthTSynCtrlIdx);
#endif/* ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF */
        }
      }
      /* If the sync is needed and the sync frame was processed successfully proceed with the sync */
      if(
          (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SynchronizeSimpleBridge == TRUE) &&
          (EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState == ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS)
        )
      {
        /* Use the uniqueid to identify the egress timestamps for the host port. */
        EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].UniqueId = UniqueId;
        /* If synchronization of the simplebridge is configured, the egress
           timestamp T5(figure 5.7, PRS 1.5.1) is needed.*/
        TimeStampRequired = TRUE;
      }
    }
    else
    {
      /* Boundary clock */
      /* Ready to wait the egress timestamp from the host port. */
      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState,
        ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS
      );
      /* Use the uniqueid to identify the egress timestamps for the host port. */
      EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].UniqueId = UniqueId;
      TimeStampRequired = TRUE;
    }
  }
  return TimeStampRequired;
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxFupSyncSwtMsg
(
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint16 Len
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  const uint16 RxSequNumber = EthTSyn_GetPTPHeaderSequNumber(DataPtr);
  uint32 ProtocolParamTemp;
  /* !LINKSTO EthTSyn.PRS_TS_00196, 1 */
  if(
      (RxSequNumber == EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber) &&
      (EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived)
     )
  {
#if(ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)

    /* If an EthTSynTimeDomain is configured as a transparent clock, CRC configuration won't be used
      (data from received message shall be used when validating the SyncFUp message) -
      - If received SyncFUp message length is greater than 76, the message contains AUTOSAR Sub-TLV. */
    if(Len > (ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_PTP_SYNC_FUP_PAYLOADSIZE))
    {
      /* !LINKSTO EthTSyn.PRS_TS_00208, 1 */
      RetVal = EthTSyn_VerifyAutosarTlv(EthTSynCtrlIdx, &DataPtr[0U], Len);
    }
    else
    {
      RetVal = E_OK;
    }

    if(RetVal == E_OK)
#endif
    {
      SchM_Enter_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();

      /* Save ProtocolParam from succesfully received SyncFUp frame.
       * Shall be returned when EthTSyn_GetProtocolParam() is called */
      ProtocolParamTemp = (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B10_CSRO_3]) << 24U;
      ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B11_CSRO_2]) << 16U;
      ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B12_CSRO_1]) << 8U;
      ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B13_CSRO_0]);

      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.cumulativeScaledRateOffset = (sint32)(ProtocolParamTemp);

      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator =
          (uint16)((uint16)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B14_GM_TIMEBASEIND_1]) << 8U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.gmTimeBaseIndicator |=
          (uint16)((uint16)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B15_GM_TIMEBASEIND_0]));

      ProtocolParamTemp = (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B16_GM_PH_CHG_0]) << 24U;
      ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B17_GM_PH_CHG_1]) << 16U;
      ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B18_GM_PH_CHG_2]) << 8U;
      ProtocolParamTemp |= (uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B19_GM_PH_CHG_3]);

      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.lastGmPhaseChange = (sint32)(ProtocolParamTemp);

      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange =
          (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B28_GM_FREQ_CHG_3]) << 24U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange |=
          (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B29_GM_FREQ_CHG_2]) << 16U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange |=
          (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B30_GM_FREQ_CHG_1]) << 8U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].protocolParam.scaledLastGmFreqChange |=
          (uint32)((uint32)(DataPtr[ETHTSYN_PTP_HEADER_SIZE + ETHTSYN_TIME_STAMP_SIZE +
                                    ETHTSYN_FUP_TLV_B31_GM_FREQ_CHG_0]));

      SchM_Exit_EthTSyn_SCHM_ETHTSYN_EXCLUSIVE_AREA_2();

      /* !LINKSTO EthTSyn.EB.Slave.LostSyncFUPFrame, 1 */
      TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, FALSE);
      /* If a transparent clock is used */
      if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == TRUE)
      {
        /* !LINKSTO EthTSyn.EB.EthSwtRx_SyncFUp_MaxLength, 1 */
        if(Len > ETHTSYN_SYNCFUP_FRAME_MAX_SIZE)
        {
          Len = ETHTSYN_SYNCFUP_FRAME_MAX_SIZE;
        }
        /* !LINKSTO EthTSyn.EB.EthSwt_ReceiveSyncFupFrameOnSlavePort, 1 */
        TS_MemCpy(&EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrame[0], &DataPtr[0], Len);
        EthTSyn_Ctrl[EthTSynCtrlIdx].ReceivedFupFrameLength = Len;

        /* !LINKSTO EthTSyn.EB.EthSwt_PassFupFrameToMasterPorts, 1 */
        /* Trigger the transmission of syncFup on all master ports. */
        /* !LINKSTO EthTSyn.PRS_TS_00209, 1 */
        TS_AtomicAssign8
        (
          EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
          ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_FUP
        );
      }
      if(
          (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SynchronizeSimpleBridge == TRUE) ||
          (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
        )
      {
        /* Extract and calculate OTS + Correction */
        EthTSyn_Inc02_AddOtsCorr(DataPtr, EthTSynCtrlIdx);
        /* If the egress timestamp on the host port was received, we can proceed with the synchronization */
        if(EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState == ETHTSYN_PORT_READY_FOR_TIME_SYNC)
        {
          /* Sync the slave */
          EthTSyn_Inc02_SynchronizeBridge(&EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr, EthTSynCtrlIdx);

          /* Sync performed, don't retry on the mainfunction, reset the state for the host port */
          TS_AtomicAssign8
          (
              EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState,
              ETHTSYN_PORT_SYN_TX_STATE_IDLE
          );
        }
        else if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
        {
            /* The sync frame and the fup are received and processed. */
            TS_AtomicAssign8
            (
              EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
              ETHTSYN_CTRL_SYN_TX_STATE_READY_FOR_BRIDGE_SYNC
            );
        }
        else
        {
          /* nothing to do */
        }
      }
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DEM)
      /* Heal dem event */
      /* !LINKSTO EthTSyn.EB.Diagnostic_SyncOK_DEM, 1 */
      Dem_ReportErrorStatus
      (
          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EventIdSyncFailed,
          DEM_EVENT_STATUS_PREPASSED
      );
#elif (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED == TS_PROD_ERR_REP_TO_DET)
      /* Sync/Fup pair was received, reset the counter */
      EthTSyn_Slave[EthTSynCtrlIdx].SyncFupDroppedPairsCt = 0U;
#endif
#if(ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
      /* Reload the value of timeout */
      EthTSyn_Slave[EthTSynCtrlIdx].SyncFupPairTimeout =
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].ReceiveSyncFupPairTimeout;
      /* Fup frame was successfully processed */
      RetVal = E_OK;
#endif
    }
#if((ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE))
    else
    {
      /* Sub-TLV validation failed */
      RetVal = E_NOT_OK;
    }
#endif
  }
#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  else
  {
    /* SeqCounter not equal or sync frame was not received */
    RetVal = E_NOT_OK;
  }
  if(E_OK != RetVal)
  {
    /* Sync frame is missing or there where an issue on processing the Fup frame */
    EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
  }
#else
    TS_PARAM_UNUSED(RetVal);
#endif
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_SynchronizeBridge
(
  P2VAR(Eth_TimeIntDiffType, AUTOMATIC, ETHTSYN_APPL_DATA) OtsPdelayCorrPtr,
  uint8 EthTSynCtrlIdx
)
{
  /* Measure Data */
  StbM_MeasurementType MeasureData;
  Eth_TimeStampType TmpTimeStamp;

  /* Default value for the SYNC_TO_GATEWAY bit in timeBaseStatus */
  EthTSyn_SyncToGatewayBit = 0U;

  TmpTimeStamp.nanoseconds = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
  TmpTimeStamp.seconds = 0U;
  TmpTimeStamp.secondsHi = 0U;

  /* !LINKSTO EthTSyn.SWS_EthTSyn_00150,1 */
  MeasureData.pathDelay = EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;

  if(OtsPdelayCorrPtr->sign == TRUE) /* Proceed with sync, only if no wrong time stamp detected. */
  {
    StbM_UserDataType UserData;
    StbM_TimeStampType StbMTimeStamp;
    Eth_TimeStampType SyncReceptionDelay = {0U, 0U, 0U};
    StbM_VirtualLocalTimeType VirtualLocalTimeT2 = EthTSyn_Slave[EthTSynCtrlIdx].T2Vlt;

    /* Convert virtual time to ethtime */
    EthTSyn_Int01_ConvertVirtualTimeToEthTime(&EthTSyn_Slave[EthTSynCtrlIdx].SyncReceptionDelay, &SyncReceptionDelay);

    /* !LINKSTO EthTSyn.SWS_EthTSyn_00080, 1 */
    UserData.userDataLength = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userDataLength;
    UserData.userByte0 = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte0;
    UserData.userByte1 = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte1;
    UserData.userByte2 = EthTSyn_Ctrl[EthTSynCtrlIdx].StbMUserData.userByte2;

    /* OriginTimeStamp + correctionField + Pdelay */
    EthTSyn_AddTimeStamps(
               &TmpTimeStamp,
               &OtsPdelayCorrPtr->diff /* OriginTimeStamp + correctionField  */
             );
    /* OriginTimeStamp + correctionField + Pdelay + SRD */
    EthTSyn_AddTimeStamps(
                 &TmpTimeStamp, /* OriginTimeStamp + correctionField + Pdelay */
                 &SyncReceptionDelay /* Sync Reception Delay */
               );
    /* OriginTimeStamp + correctionField + Pdelay + SRD + (T5 - T4)*/
    EthTSyn_AddTimeStamps(
                 &TmpTimeStamp, /* OriginTimeStamp + correctionField + Pdelay + SRD */
                 &EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff /* T5 - T4  */
               );
    StbMTimeStamp.nanoseconds = TmpTimeStamp.nanoseconds;
    StbMTimeStamp.seconds = TmpTimeStamp.seconds;
    StbMTimeStamp.secondsHi = TmpTimeStamp.secondsHi;
    StbMTimeStamp.timeBaseStatus = EthTSyn_SyncToGatewayBit;

    /* Return value ignored: No further action possible if E_NOT_OK returned. */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00129, 1 */
    /* !LINKSTO EthTSyn.EB.Slave.HWTimpStamp.GatewaySync, 1 */
    /* !LINKSTO EthTSyn.EB.Slave.StbMSync, 1 */
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00052, 1 */
    /* !LINKSTO EthTSyn.EB.TransparentClock_Synchronize, 1 */
    (void) StbM_BusSetGlobalTime
      (
        EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
        &StbMTimeStamp, /* timeStampPtr */
        &UserData, /* userDataPtr */
        &MeasureData, /* measureDataPtr */
        &VirtualLocalTimeT2 /* localTimePtr */
      );

    /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
    if(EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].TimeValidationEnabled == TRUE)
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.pDelay =
                                                    EthTSyn_Slave[EthTSynCtrlIdx].Pdelay;
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00216, 1 */
      (void) StbM_EthSetSlaveTimingData
        (
          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId, /* timeBaseId */
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00217, 1 */
          &EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording /* measureDataPtr */
        );
    }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */

    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
    {
      uint32 ConfiguredTxPeriod = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].BridgeTxPeriod;
      uint32 TransmitSync = 0U;

      if((ConfiguredTxPeriod % 2U) == 0U)
      {
        TransmitSync = ConfiguredTxPeriod / 2U;
      }
      else
      {
        TransmitSync = (ConfiguredTxPeriod / 2U) + 1U;
      }
      if(
          ((EthTSyn_GeneralCounter - EthTSyn_Slave[EthTSynCtrlIdx].BridgeLastSyncSentTime) >= TransmitSync) ||
          (EthTSyn_Slave[EthTSynCtrlIdx].BridgeLastSyncSentTime == 0U)
        )
      {
        /* !LINKSTO EthTSyn.EB.BoundaryClock_TransmitSyncOnHostPort, 1 */
        /* !LINKSTO EthTSyn.EB.BoundaryClock_TransmitSyncOnHostPort_SecondTx_Less, 1 */
        /* !LINKSTO EthTSyn.EB.BoundaryClock_TransmitSyncOnHostPort_SecondTx_More, 1 */
        /* ready to transmit, on the next mainfunction, the sync to the connected slaves */
        /* Boundary clock transmit sync frames . */
        EthTSyn_Slave[EthTSynCtrlIdx].TriggerTxOnBridge = TRUE;
      }

      TS_AtomicAssign8
      (
        EthTSyn_Ctrl[EthTSynCtrlIdx].SyncTxState,
        ETHTSYN_CTRL_SYN_TX_STATE_IDLE
      );
    }
    /* After sync we can reset the variables */
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.nanoseconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.seconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.secondsHi = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.sign = FALSE;
    EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff.nanoseconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff.seconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.diff.secondsHi = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].TimeDiffHostEgressSlaveIngress.sign = FALSE;
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_AddOtsCorr
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_TimeStampType OriginTimeStamp;

  OriginTimeStamp.nanoseconds = 0U;
  OriginTimeStamp.seconds = 0U;
  OriginTimeStamp.secondsHi = 0U;


  /* Get origin time stamp of the master from follow up frame payload. */
  EthTSyn_ArrayToTimeStamp(&OriginTimeStamp, &DataPtr[ETHTSYN_PTP_HEADER_SIZE]);

  if(ETHTSYN_NANOSEC_MAX < OriginTimeStamp.nanoseconds)
  {
    /* !LINKSTO EthTSyn.EB.TransparentClock_SyncFUp_NanoSecMax, 1 */
    /* !LINKSTO EthTSyn.EB.Nanoseconds, 1 */
    RetVal = E_NOT_OK;
  }
  else
  {
    /* !LINKSTO EthTSyn.EB.NanosecondsLimit, 1 */
    RetVal = E_OK;
  }

  if(E_OK == RetVal)
  {
    Eth_TimeStampType TmpTimeStamp;
    /* Calculate time offset between master and slave. */
    /* OriginTimeStampSync[FUP] */
    TmpTimeStamp.secondsHi = 0U;
    TmpTimeStamp.seconds = 0U;
    TmpTimeStamp.nanoseconds = 0U;

    RetVal = EthTSyn_AddCorrField
    (
      EthTSynCtrlIdx,
      &DataPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0],
      &TmpTimeStamp
    );

    if(E_OK == RetVal) /* Only perform a correction if no wrong time stamp detected. */
    {
#if(ETHTSYN_TIME_RECORDING == STD_ON)
      if(EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].TimeValidationEnabled == TRUE)
      {
        /* Save PreciseOriginTimestamp as received in the Followup Message from master */
        EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.preciseOriginTimestamp.
                                                 nanoseconds = OriginTimeStamp.nanoseconds;
        EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.preciseOriginTimestamp.
                                                 seconds = OriginTimeStamp.seconds;

      }
#endif
      EthTSyn_AddTimeStamps(&TmpTimeStamp, &OriginTimeStamp);
      EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.nanoseconds = TmpTimeStamp.nanoseconds;
      EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.seconds = TmpTimeStamp.seconds;
      EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.secondsHi = TmpTimeStamp.secondsHi;
      EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.sign = TRUE;
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
    }
  }
  if(RetVal != E_OK)
  {
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.nanoseconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.seconds = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.diff.secondsHi = 0U;
    EthTSyn_Slave[EthTSynCtrlIdx].OriginTimeStampCorr.sign = FALSE;
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxSyncFrame
(
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx
)
{
  Std_ReturnType TmpRet = E_NOT_OK;
  Eth_TimeStampType Sync_IngressTimeStamp;

  Sync_IngressTimeStamp.nanoseconds = 0U;
  Sync_IngressTimeStamp.seconds = 0U;
  Sync_IngressTimeStamp.secondsHi = 0U;

  /* If a boundary clock is used, take the ingress timestamp*/
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
  {
    /* !LINKSTO EthTSyn.PRS_TS_00199_CheckSC, 1 */
    /* !LINKSTO EthTSyn.EB.TransparentClock_ValidateSync, 1 */
    /* !LINKSTO EthTSyn.EB.TimeAwareBridge_DEM_FailedSync_Ingress_SC, 1 */
    if(E_OK == EthTSyn_CheckSC(EthTSynCtrlIdx, DataPtr))
    {
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00128, 1 */
      TmpRet = EthTSyn_GetIngressTimeStamp(EthTSynCtrlIdx, DataPtr, &Sync_IngressTimeStamp);
      if(TmpRet == E_OK)
      {
        EthTSyn_Slave[EthTSynCtrlIdx].Sync_ActualIngressTimeStamp = Sync_IngressTimeStamp;
      }
    }
  }
  else
  {
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SynchronizeSimpleBridge == TRUE)
    {
      Std_ReturnType RetValChecks = E_NOT_OK;
      /* !LINKSTO EthTSyn.SWS_EthTSyn_00128, 1 */
      /* !LINKSTO EthTSyn.EB.TransparentClock_SynchronizeFailIngress, 1 */
      RetValChecks = EthTSyn_GetIngressTimeStamp(EthTSynCtrlIdx, DataPtr, &Sync_IngressTimeStamp);
      if(RetValChecks == E_OK)
      {
        EthTSyn_Slave[EthTSynCtrlIdx].Sync_ActualIngressTimeStamp = Sync_IngressTimeStamp;
        /* Wait egress timestamp from the host port. */
        TS_AtomicAssign8
        (
          EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState,
          ETHTSYN_PORT_SYN_TX_STATE_WAIT_EGRESS_TS
        );
      }
      else
      {
        /* Something is not ok, Skip the synchronization. */
        TS_AtomicAssign8
        (
          EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].SyncTxState,
          ETHTSYN_PORT_SYN_TX_STATE_IDLE
        );
        EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortMgt].UniqueId = ETHTSYN_UNIQUE_ID_INVALID;
      }
    }
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridgeValidateSync == TRUE)
    {
      if(E_OK != EthTSyn_CheckSC(EthTSynCtrlIdx, DataPtr))
      {
        TmpRet = E_NOT_OK;
      }
      else
      {
        TmpRet = E_OK;
      }
    }
    else
    {
      /* Save the seqId. */
      TS_AtomicAssign16(EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber, EthTSyn_GetPTPHeaderSequNumber(DataPtr));
      /* If transparent clock is used, proceed with processing the sync frame */
      TmpRet = E_OK;
    }
  }

#if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
  if((EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived == TRUE) || (E_OK != TmpRet))
  {
    /* Fup frame is missing or there where an issue on processing the sync frame */
    EthTSyn_SyncFupDropped(EthTSynCtrlIdx);
  }
#endif

  /* !LINKSTO EthTSyn.EB.Slave.LostSyncFUPFrame, 1 */
  if(E_OK == TmpRet)
  {
    TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, TRUE);
    /* Timeout value of the Follow_Up message (of the subsequent Sync message).
       A value of 0 deactivates this timeout observation.*/
    EthTSyn_Slave[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout =
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].GlobalTimeFollowUpTimeout;
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00213, 1 */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
    if(EthTSyn_RootCfgPtr->SwitchConfig[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].TimeValidationEnabled == TRUE)
    {

      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity =
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.clockIdentity |=
           (uint64)((uint64) DataPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.portNumber =
           (uint16)(((uint16) DataPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sourcePortId.portNumber |=
           (uint16)((uint16) DataPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);
      EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.sequenceId =
                                                EthTSyn_Ctrl[EthTSynCtrlIdx].SyncSequNumber;
        /* Save the ingress timestamp to be passed to the StbM. */
        /* Convert the ingress timestamp. */
      (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime(&EthTSyn_SwitchPorts[EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortSlave].SyncTimeStamp,
           &EthTSyn_Slave[EthTSynCtrlIdx].SyncSlaveTimeRecording.syncIngressTimestamp);

    }
#endif
  }
  else
  {
    /* Reset the state of the received sync frame*/
    TS_AtomicAssign8(EthTSyn_Slave[EthTSynCtrlIdx].Sync_SyncFrameReceived, FALSE);
  }

}
#endif /* ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON */

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_ProcessRxPdelayReqSwtMsg
(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHTSYN_APPL_DATA) MgmtInfoPtr,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETHTSYN_APPL_DATA) IngressTimeStampPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHTSYN_APPL_DATA) DataPtr,
  uint8 EthTSynCtrlIdx,
  uint16 Len
)
{
  boolean Found = FALSE;
  EthTSyn_IntPortIdxType Idx;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
  Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart;
#else
  /* The pdelay_req frame is not processed for the slave port. */
  Idx = EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart + 2U;
#endif
  for
  (;((Idx < (EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount +
            EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortStart))
        && (FALSE == Found));
     Idx++
  )
  {
    /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayReqReceived_Incorrect_MgmtInfo, 1 */
    if(MgmtInfoPtr->SwitchIdx == EthTSyn_RootCfgPtr->SwitchConfig[Idx].EthSwtIdx)
    {
      if(MgmtInfoPtr->SwitchPortIdx == EthTSyn_RootCfgPtr->SwitchConfig[Idx].EthSwtPortIdx)
      {
        /* !LINKSTO EthTSyn.PRS_TS_00143, 1 */
        if(EthTSyn_RootCfgPtr->SwitchConfig[Idx].PdelayRespEnable == TRUE)
        {
          Found = TRUE;
          /* Store serial number to be used for Pdelay_resp and Pdelay_resp_FUp. */
          /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayReqReceived_SaveData, 1 */
          TS_AtomicAssign16(
                             EthTSyn_SwitchPorts[Idx].Ingress_PdelayReqSequNumber,
                             EthTSyn_GetPTPHeaderSequNumber(DataPtr)
                           );
          TS_MemCpy(
               &EthTSyn_SwitchPorts[Idx].Pdelay_Rx_SrcPortIdentity[0U],
               &DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0],
               ETHTSYN_SOURCEPORTIDENTITY_SIZE
             );
          /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayReq_SaveIngressTS, 1 */
          EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp.nanoseconds = IngressTimeStampPtr->nanoseconds;
          EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp.seconds = IngressTimeStampPtr->seconds;
          EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp.secondsHi = IngressTimeStampPtr->secondsHi;

          TS_PARAM_UNUSED(Len);
          /* Make sure that the transmit flag is set to true
           * (this can be already set if a sync cycle is in progress) */
          /* !LINKSTO EthTSyn.EB.SwitchPdelay.PdelayResp_Transmit, 1 */
          ETHTSYN_SET_TXFLAG
            (&EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit, ETHTSYN_BITPOS_TX_SWT, TRUE);

          /* In the next mainfunction the pdelayresp frame can be transmitted. */
          /* !LINKSTO EthTSyn.EB.TimeAwareBridge_MasterReceivePdelayReq, 1 */
          TS_AtomicSetBit_8
          (
            &EthTSyn_SwitchPorts[Idx].Frame2Transmit,
            ETHTSYN_BITPOS_PDELAYRESP
          );
#if(ETHTSYN_TIME_RECORDING == STD_ON)
          if(EthTSyn_RootCfgPtr->SwitchConfig[Idx].TimeValidationEnabled == TRUE)
          {

            /* If timevalidation is enabled save the relevant data. */
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.sequenceId =
                               EthTSyn_SwitchPorts[Idx].Ingress_PdelayReqSequNumber;

            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity =
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)(((uint64) DataPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.clockIdentity |=
                 (uint64)((uint64) DataPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.portNumber =
                 (uint16)(((uint16) DataPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
            EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestPortId.portNumber |=
                 (uint16)((uint16) DataPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);

            (void)EthTSyn_Int01_ConvertEthTimeToVirtualTime
                (
                    &EthTSyn_SwitchPorts[Idx].IngPdelayFrameTimeStamp,
                    &EthTSyn_SwitchPorts[Idx].PdelayResponderTimeRecording.requestReceiptTimestamp
                );
          }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
        }
      }
    }
  }
}

STATIC FUNC(void, ETHTSYN_CODE) EthTSyn_Inc02_PrepareSwtFUpForTx
(
  uint8 EthTSynCtrlIdx,
  EthTSyn_IntPortIdxType PortIdx,
  uint16 SubTlvLength,
  uint32 CorrectionValue,
  P2VAR(uint8, AUTOMATIC, ETHTSYN_APPL_DATA) BufPtr,
  Eth_BufIdxType BufIdx
)
{
  uint8 PayloadIdx = 0U;
  uint8 SwitchIdx = 0U;
  uint8 SwitchPortIdx = 0U;
#if((ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON))
  uint8 Crc_Time_1;
#endif

  /* if TimeCorrection.diff.seconds >= 4seconds */
  BufPtr[ETHTSYN_PTP_HEADER_B8_CORRFIELD_0] = 0x00U;
  BufPtr[ETHTSYN_PTP_HEADER_B9_CORRFIELD_1] = 0x00U;
  /* ns integer part */
  BufPtr[ETHTSYN_PTP_HEADER_B10_CORRFIELD_2] = (uint8)((CorrectionValue >> 24U) & 0xFFU);
  BufPtr[ETHTSYN_PTP_HEADER_B11_CORRFIELD_3] = (uint8)((CorrectionValue >> 16U) & 0xFFU);
  BufPtr[ETHTSYN_PTP_HEADER_B12_CORRFIELD_4] = (uint8)((CorrectionValue >>  8U) & 0xFFU);
  BufPtr[ETHTSYN_PTP_HEADER_B13_CORRFIELD_5] = (uint8)((CorrectionValue       ) & 0xFFU);

#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
  /* If the EthTSyn portid is configured update the portid bytes form the sourceportid field. */
  if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId != 0xFFFFU)
  {
    /* 16 bit port number */
    BufPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8] =
      (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_MSB) >> 8U);
    BufPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9] =
      (uint8)((uint16)(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthTSynSourcePortId & ETHTSYN_16BIT_MASK_LSB));
  }
#endif
  /* update correction field PTP header */
  /* !LINKSTO EthTSyn.EB.EthSwt_UpdateCorrectionField, 1 */
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SwtPortIdxInCorrField)
  {
    SwitchIdx       = (uint8)EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthSwtIdx;
    SwitchPortIdx   = (uint8)EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].EthSwtPortIdx;
  }
  /* ns fractional part */
  /* !LINKSTO EthTSyn.EB.SwitchPortIdx.StoredInCorrectionField, 1 */
  BufPtr[ETHTSYN_PTP_HEADER_B14_CORRFIELD_6] = SwitchIdx;
  BufPtr[ETHTSYN_PTP_HEADER_B15_CORRFIELD_7] = SwitchPortIdx;

  PayloadIdx += ETHTSYN_PTP_HEADER_SIZE; /* Set payload index to next free space. */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == FALSE)
  {
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */
    /* Set PTP payload */
    EthTSyn_TimeStampToArray
    (
      &EthTSyn_Ctrl[EthTSynCtrlIdx].OriginTimeStamp, &BufPtr[PayloadIdx]
    );
    PayloadIdx += ETHTSYN_TIME_STAMP_SIZE; /* Set payload index to next free space. */
    /* Add IEEE TLV information. */
    EthTSyn_FillFUpTLV(EthTSynCtrlIdx, &BufPtr[PayloadIdx]);
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  }
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */

#if((ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF))
  if(SubTlvLength > 0U)
  {
    /* The AUTOSAR TLV is used */
    EthTSyn_FillFUpAutosarTLV(EthTSynCtrlIdx, &BufPtr[0U]);

#if((ETHTSYN_ICV_USED == STD_ON) && (ETHTSYN_TOTAL_ICVTXLENGTH > 0U))
    /* If Icv SubTLV is enabled, update the buffer */

    /* !LINKSTO EthTSyn.R22-11.PRS_TS_00223, 1 */
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TLVFollowUpICVSubTLV == TRUE)
    {
      /* Confirmation of transmission needed to be passed to FVM */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncFUp_BufIdx = BufIdx;
      EthTSyn_ProcessFupTxSubTlvIcv(EthTSynCtrlIdx, &BufPtr[0U]);
    }
#else
    TS_PARAM_UNUSED(BufIdx);
#endif /* ETHTSYN_ICV_USED == STD_ON */
 }
#else
  TS_PARAM_UNUSED(SubTlvLength);
  TS_PARAM_UNUSED(BufIdx);
#endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_ON) */
#if((ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON))
 if((BufPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR] == ETHTSYN_FUP_SUBTLV_TIME_TYPE) &&
    ((BufPtr
    [ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR + ETHTSYN_FUP_SUBTLV_TIME_B2_TIME_FLAGS] &
     ETHTSYN_CORRECTION_FIELD_BIT_MASK) != 0U
    )
   )
  {
    /* !LINKSTO EthTSyn.PRS_TS_00209, 1 */
    EthTSyn_Inc02_BridgeCalculateCrcTime1(EthTSynCtrlIdx, &BufPtr[0U], &Crc_Time_1);
    BufPtr[ETHTSYN_FUP_AUTOSAR_SUBTLV_START_ADDR +
                  ETHTSYN_FUP_SUBTLV_TIME_B4_CRC_TIME_1] = Crc_Time_1;
  }
#endif
#if(ETHTSYN_TIME_RECORDING == STD_ON)
  if(EthTSyn_RootCfgPtr->SwitchConfig[PortIdx].TimeValidationEnabled == TRUE)
  {
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
    /* update port specific members */
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId =
        EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.sourcePortId;
#endif
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.correctionField =
        EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.correctionField;
    /* Save preciseOriginTimeStamp to be reported to StbM for time recording */
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.nanoseconds =
                                 EthTSyn_Ctrl[EthTSynCtrlIdx].OriginTimeStamp.nanoseconds;
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.seconds =
                                 EthTSyn_Ctrl[EthTSynCtrlIdx].OriginTimeStamp.seconds;
    EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.syncEgressTimestamp =
                     EthTSyn_SwitchPorts[PortIdx].SyncMasterTimeRecording.syncEgressTimestamp;
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].SimpleBridge == TRUE)
    {
      Eth_TimeStampType OriginTimeStamp;

      OriginTimeStamp.nanoseconds = 0U;
      OriginTimeStamp.seconds = 0U;
      OriginTimeStamp.secondsHi = 0U;
      /* If a transparent clock is used, EthTSyn will extract the data from the received fup and this will be
         passed to the StbM */
      /* Save SyncSequNumber to be reported to StbM for time recording */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sequenceId =
                                                 EthTSyn_GetPTPHeaderSequNumber(BufPtr);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity =
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B20_SRCPORTIDENTITY_0]) << 56U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B21_SRCPORTIDENTITY_1]) << 48U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B22_SRCPORTIDENTITY_2]) << 40U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B23_SRCPORTIDENTITY_3]) << 32U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B24_SRCPORTIDENTITY_4]) << 24U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B25_SRCPORTIDENTITY_5]) << 16U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)(((uint64) BufPtr[ETHTSYN_PTP_HEADER_B26_SRCPORTIDENTITY_6]) << 8U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.clockIdentity |=
           (uint64)((uint64) BufPtr[ETHTSYN_PTP_HEADER_B27_SRCPORTIDENTITY_7]);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber =
           (uint16)(((uint16) BufPtr[ETHTSYN_PTP_HEADER_B28_SRCPORTIDENTITY_8]) << 8U);
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.sourcePortId.portNumber |=
           (uint16)((uint16) BufPtr[ETHTSYN_PTP_HEADER_B29_SRCPORTIDENTITY_9]);

      /* Get origin time stamp of the master from follow up frame payload. */
      EthTSyn_ArrayToTimeStamp(&OriginTimeStamp, &BufPtr[ETHTSYN_PTP_HEADER_SIZE]);
      /* Save preciseOriginTimeStamp to be reported to StbM for time recording */
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.nanoseconds =
                                                                   OriginTimeStamp.nanoseconds;
      EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording.preciseOriginTimestamp.seconds =
                                                                   OriginTimeStamp.seconds;
    }
#endif /* (ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF) */
    (void)StbM_EthSetMasterTimingData
      (
          EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].TimeBaseId,
          /* !LINKSTO EthTSyn.SWS_EthTSyn_00215, 1 */
          &EthTSyn_Ctrl[EthTSynCtrlIdx].SyncMasterTimeRecording
      );
  }
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
}
#endif /* (ETHTSYN_SWITCH_USED == STD_ON) */

STATIC FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TransmitAndRetry
(
  uint8 EthTSynCtrlIdx,
  Eth_BufIdxType BufIdx,
  EthTSyn_IntPortIdxType PortIdx,
  uint16 FrameLength
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount == 0U)
  {
    /* !LINKSTO EthTSyn.SWS_EthTSyn_00203, 1 */
    RetVal = EthTSyn_TransmitFrame(EthTSynCtrlIdx, BufIdx, FrameLength, FALSE);
  }
#if(ETHTSYN_SWITCH_USED == STD_ON)
  else
  {
    RetVal = EthTSyn_Inc02_TransmitSwtFrame(EthTSynCtrlIdx, BufIdx, TRUE, PortIdx, TRUE, FrameLength, FALSE);
  }
#endif

  if(RetVal == E_OK)
  {
    /* clear the flag */
    TS_AtomicClearBit_8
    (
    &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
    ETHTSYN_BITPOS_TX_FUP
    );
#if(ETHTSYN_SWITCH_USED == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount > 0U)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_FUP
      );

      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[PortIdx].SyncTxState,
        ETHTSYN_PORT_SYN_TX_STATE_IDLE
      );
    }
#endif
#if(ETHTSYN_ICV_USED == STD_ON)
    /* Set to IDLE. */
    TS_AtomicAssign8
    (
      EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv,
      ETHTSYN_AUTH_GENERATION_IDLE
    );
#endif /* ETHTSYN_ICV_USED == STD_ON */
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Success, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;
  }
  else if(EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries > 0U)
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Retry, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries--;
  }
  else
  {
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_Fail, 1 */
    /* !LINKSTO EthTSyn.EB.EthTSynMaxNumberOfTransmitRetries_0, 1 */
    EthTSyn_Ctrl[EthTSynCtrlIdx].NumberOfRetries = ETHTSYN_MAXIMUM_NUMBER_OF_RETRIES;

    /* clear the flag */
    TS_AtomicClearBit_8
    (
    &EthTSyn_Ctrl[EthTSynCtrlIdx].Frame2Transmit,
    ETHTSYN_BITPOS_TX_FUP
    );
#if(ETHTSYN_SWITCH_USED == STD_ON)
    if(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].PortCount > 0U)
    {
      /* clear the flag */
      TS_AtomicClearBit_8
      (
        &EthTSyn_SwitchPorts[PortIdx].Frame2Transmit,
        ETHTSYN_BITPOS_TX_FUP
      );

      TS_AtomicAssign8
      (
        EthTSyn_SwitchPorts[PortIdx].SyncTxState,
        ETHTSYN_PORT_SYN_TX_STATE_IDLE
      );
    }
#endif
#if(ETHTSYN_ICV_USED == STD_ON)
    /* Set to IDLE. */
    TS_AtomicAssign8
    (
      EthTSyn_Ctrl[EthTSynCtrlIdx].NextActionIcv,
      ETHTSYN_AUTH_GENERATION_IDLE
    );
#endif /* ETHTSYN_ICV_USED == STD_ON */
    EthTSyn_TxFailedResetValues(EthTSyn_RootCfgPtr->EthTSynCtrl[EthTSynCtrlIdx].EthIfCtrlIdx, BufIdx);
  }
#if(ETHTSYN_SWITCH_USED == STD_OFF)
  TS_PARAM_UNUSED(PortIdx);
#endif
  return RetVal;
}

/* ================================================================================== */
#define ETHTSYN_STOP_SEC_CODE
#include <EthTSyn_MemMap.h>

/*==================[version check]=========================================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef ETHTSYN_VENDOR_ID /* configuration check */
#error ETHTSYN_VENDOR_ID must be defined
#endif

#if (ETHTSYN_VENDOR_ID != 1U) /* vendor check */
#error ETHTSYN_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef ETHTSYN_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error ETHTSYN_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (ETHTSYN_AR_RELEASE_MAJOR_VERSION != 4U)
#error ETHTSYN_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef ETHTSYN_AR_RELEASE_MINOR_VERSION /* configuration check */
#error ETHTSYN_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (ETHTSYN_AR_RELEASE_MINOR_VERSION != 7U )
#error ETHTSYN_AR_RELEASE_MINOR_VERSION wrong (!= 6U)
#endif

#ifndef ETHTSYN_AR_RELEASE_REVISION_VERSION /* configuration check */
#error ETHTSYN_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (ETHTSYN_AR_RELEASE_REVISION_VERSION != 0U )
#error ETHTSYN_AR_RELEASE_REVISION_VERSION wrong (!= 0U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef ETHTSYN_SW_MAJOR_VERSION /* configuration check */
#error ETHTSYN_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (ETHTSYN_SW_MAJOR_VERSION != 4U)
#error ETHTSYN_SW_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef ETHTSYN_SW_MINOR_VERSION /* configuration check */
#error ETHTSYN_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (ETHTSYN_SW_MINOR_VERSION < 0U)
#error ETHTSYN_SW_MINOR_VERSION wrong (< 0U)
#endif

#ifndef ETHTSYN_SW_PATCH_VERSION /* configuration check */
#error ETHTSYN_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (ETHTSYN_SW_PATCH_VERSION < 0U)
#error ETHTSYN_SW_PATCH_VERSION wrong (< 0U)
#endif

/*==================[end of file]===========================================*/
