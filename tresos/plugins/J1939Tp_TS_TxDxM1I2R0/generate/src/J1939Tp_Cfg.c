/**
 * \file
 *
 * \brief AUTOSAR J1939Tp
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Tp.
 *
 * \version 1.2.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* This file generated from the configuration of J1939Tp module. */
[!CODE!]
[!INCLUDE "include/J1939Tp_Vars.m"!]
[!AUTOSPACING!]
/*==================[inclusions]============================================*/

#include <J1939Tp.h>      /* Module public API */
#include <J1939Tp_Api.h>
#include <J1939Tp_Int.h>
#include <CanIf.h>        /* CanIf types */
#include <PduR_J1939Tp.h> /* PduR types */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/
[!VAR "ConfigIndex" = "'0'"!]
[!SELECT "util:distinct(node:order(J1939TpConfiguration/eb-list::*))"!][!//
#define  J1939TP_START_SEC_VAR_CLEARED_8
#include <J1939Tp_MemMap.h>
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]

static VAR(boolean, J1939TP_VAR) [!"node:name(../..)"!]_[!"node:name(.)"!]_J1939TpTxDirectNPduAvailable[[!"num:i(count(J1939TpTxPg/eb-list::*))"!]];

[!ENDLOOP!]
#define  J1939TP_STOP_SEC_VAR_CLEARED_8
#include <J1939Tp_MemMap.h>

#define J1939TP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Tp_MemMap.h>
/* !LINKSTO J1939Tp.dsn.PrecompileTimeConfig,1 */
/* Definition of RAM Structure for monitoring the NSDU parameters for Reception */
/* RxNSdu RAM structure configuration of [!"node:name(.)"!] */
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]

/* RxNSdu RAM structure configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
  [!LOOP "util:distinct(node:order(J1939TpRxPg/eb-list::*))"!]
/* RxNSdu RAM structure configuration of [!"node:name(.)"!] of [!"node:name(..)"!] of [!"node:name(../..)"!] */
    [!LOOP "util:distinct(node:order(J1939TpRxNSdu/eb-list::*))"!]
static VAR(J1939Tp_NSduCtrlType, J1939TP_VAR) [!"node:name(../../../../../..)"!]_[!"node:name(../../../../.)"!]_[!"node:name(../../.)"!]_[!"node:name(.)"!]_rx_nsdu_ctrl[1];
    [!ENDLOOP!]
  [!ENDLOOP!]
static VAR(J1939Tp_ChannelAbortType, J1939TP_VAR) [!"node:name(../..)"!]_[!"node:name(.)"!]_RxChannelAbort;
[!ENDLOOP!]
#define J1939TP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Tp_MemMap.h>

#define J1939TP_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Tp_MemMap.h>
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]

/* RxNSdu RAM structure configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
static VAR(J1939Tp_ChannelInfoType, J1939TP_VAR) [!"node:name(../..)"!]_[!"node:name(.)"!]_RxChannelInfo = {0xFF, 0xFF, FALSE, TRUE, TRUE, TRUE};
[!ENDLOOP!]
#define J1939TP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Tp_MemMap.h>

#define J1939TP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Tp_MemMap.h>

/* Definition of RAM Structure for monitoring the NSDU parameters for Transmission */
/* TxNSdu RAM structure configuration of [!"node:name(.)"!] */
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]

/* TxNSdu RAM structure configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
  [!LOOP "util:distinct(node:order(J1939TpTxPg/eb-list::*))"!]
/* TxNSdu RAM structure configuration of [!"node:name(.)"!] of [!"node:name(..)"!] of [!"node:name(../..)"!] */
    [!LOOP "util:distinct(node:order(J1939TpTxNSdu/eb-list::*))"!]
static VAR(J1939Tp_NSduCtrlType, J1939TP_VAR) [!"node:name(../../../../../..)"!]_[!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_tx_nsdu_ctrl[1];
    [!ENDLOOP!]
  [!ENDLOOP!]
static VAR(J1939Tp_ChannelInfoType, J1939TP_VAR) [!"node:name(../..)"!]_[!"node:name(.)"!]_TxChannelInfo;
[!ENDLOOP!]

#define J1939TP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Tp_MemMap.h>

#define J1939TP_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Tp_MemMap.h>

[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]
  [!IF "((node:exists(J1939TpTxProtocolType)) and (J1939TpTxProtocolType = 'J1939TP_PROTOCOL_CMDT'))"!]
    [!IF "((node:exists(J1939TpTxRetrySupport)) and (node:existsAndTrue(J1939TpTxRetrySupport)))"!]
static VAR(RetryInfoType, J1939TP_VAR) [!"node:name(../..)"!]_[!"node:name(.)"!]_RetryInfo =
{
  TP_DATACONF,
  0U
};
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]

#define J1939TP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Tp_MemMap.h>

#define J1939TP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Tp_MemMap.h>

/*==================[external constants]====================================*/
/* Definition of transmit SDUs*/

/* TxNSdu configuration of [!"node:name(.)"!] */
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]

/* TxNSdu configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
  [!LOOP "util:distinct(node:order(J1939TpTxPg/eb-list::*))"!]

/* TxNSdu configuration of [!"node:name(.)"!] of [!"node:name(..)"!] of [!"node:name(../..)"!] */
static CONST(J1939Tp_TxNSduType, J1939TP_CONST) [!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_tx_nsdu[[!"num:i(count(J1939TpTxNSdu/eb-list::*))"!]] =
{
    [!LOOP "util:distinct(node:order(J1939TpTxNSdu/eb-list::*))"!]
    {
      &[!"node:name(../../../../../..)"!]_[!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_tx_nsdu_ctrl[0],    /* structure, RAM structure for monitoring the NSDU parameters */
      J1939TpConf_J1939TpTxNSdu_[!"as:name(.)"!], /* uint16, Own ID for PduR for transmit request and cancel transmit. */
      [!VAR "J1939TpTxNSduRefVerify" = "as:name(as:ref(J1939TpTxNSduRef))"!]
      [!VAR "RefFound" = "'false'"!]
        [!LOOP "(util:distinct(node:order(../../../../../../../../../../../PduR/ELEMENTS/PduR/PduRRoutingTables/eb-list::*)))"!]
          [!IF "$RefFound = 'true'"!]
            [!BREAK!]
          [!ELSE!]
            [!LOOP "(util:distinct(node:order(PduRRoutingTable/eb-list::*)))"!]
              [!IF "$RefFound = 'true'"!]
                [!BREAK!]
              [!ELSE!]
                [!LOOP "(util:distinct(node:order(PduRRoutingPath/eb-list::*)))"!]
                  [!IF "$RefFound = 'true'"!]
                    [!BREAK!]
                  [!ELSE!]
                    [!LOOP "(util:distinct(node:order(PduRDestPdu/eb-list::*)))"!]
                      [!IF "$J1939TpTxNSduRefVerify = as:name(as:ref(PduRDestPduRef))"!]
                        [!IF "node:exists(PduRDestPduHandleId)"!]
      [!"(PduRDestPduHandleId)"!]U,  /*uint16, The I-PDU identifier (PduRDest) used for TxConfirmation to COM from J1939Tp. */
                          [!VAR "RefFound" = "'true'"!]
                          [!BREAK!]
                        [!ELSE!]
                          [!ERROR!]In PduR the PduRDestPduHandleId is not configured for the PduRDestPdu ([!"as:name(.)"!]).[!ENDERROR!]
                        [!ENDIF!]
                      [!ENDIF!]
                    [!ENDLOOP!]
                  [!ENDIF!]
                [!ENDLOOP!]
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$RefFound = 'false'"!]
          [!ERROR!]The J1939TpTxNSduRef reference [!"$J1939TpTxNSduRefVerify"!]  is not matching with PduRDestPduRef configuration.[!ENDERROR!]
        [!ENDIF!]
      [!IF "not(node:empty(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef))"!]
        [!VAR "MetaDataItemLength"= "'0'"!]
        [!IF "node:refvalid(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)"!]
          [!IF "node:exists(node:ref(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'PRIORITY_8'])"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'TARGET_ADDRESS_16'])"!]
              [!IF "node:exists(node:ref(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'SOURCE_ADDRESS_16'])"!]
                [!VAR "MetaDataItemLength"= "'4'"!]
              [!ELSE!]
                [!ERROR!]MetaDataItem "SOURCE_ADDRESS_16" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxNSduRef))"!]" of J1939TpTxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
              [!ENDIF!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "TARGET_ADDRESS_16" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxNSduRef))"!]" of J1939TpTxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
            [!ENDIF!]
          [!ELSEIF "node:exists(node:ref(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'TARGET_ADDRESS_16'])"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'SOURCE_ADDRESS_16'])"!]
              [!VAR "MetaDataItemLength"= "'2'"!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "SOURCE_ADDRESS_16" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxNSduRef))"!]" of J1939TpTxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
            [!ENDIF!]
          [!ELSEIF "node:exists(node:ref(node:ref(J1939TpTxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'SOURCE_ADDRESS_16'])"!]
            [!VAR "MetaDataItemLength"= "'1'"!]
          [!ELSE!]
            [!ERROR!]MetaDataItem is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxNSduRef))"!]" of J1939TpTxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
          [!ENDIF!]
        [!ELSE!]
          [!ERROR!]No proper MetaDataTypeRef "[!"node:ref(J1939TpTxNSduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxNSduRef))"!]" of J1939TpTxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
        [!ENDIF!]
      [!"$MetaDataItemLength"!]U, /* uint8,  Get the MetaDataLength for the NSdu in the Tx side (value may be 0 or 1 or 2 or 4) */
      [!ELSE!]
        0U, /* uint8, Get the MetaDataLength for the NSdu in the Tx side (value may be 0 or 1 or 2 or 4) */
      [!ENDIF!]
      [!IF "(num:i($CanFDTxChannelCounter) > num:i(0)) or (num:i($CanFDRxChannelCounter) > num:i(0))"!]
      [!IF "node:exists(J1939TpTxAssuranceDataType)"!]
        [!"J1939TpTxAssuranceDataType"!], /* Assurance data type */
      [!ELSE!]
      J1939TP_NO_ASSURANCE_DATA, /* The Tx NSdu doesn't support CanFD Transmission, No assurance data */
      [!ENDIF!]
      [!IF "node:exists(J1939TpTxAssuranceDataLength)"!]
        [!"J1939TpTxAssuranceDataLength"!] /* The length of the assurance data */
      [!ELSE!]
      0U /* Assurance data isn't used for this NSdu */
      [!ENDIF!]
      [!ENDIF!]
    },
    [!ENDLOOP!]
};
  [!ENDLOOP!]
[!ENDLOOP!]

/* Definition of receive SDUs */
/* J1939Tp RxNSdu configuration */

/* RxNSdu configuration of [!"node:name(.)"!] */
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]

/* RxNSdu configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
  [!LOOP "util:distinct(node:order(J1939TpRxPg/eb-list::*))"!]

/* RxNSdu configuration of [!"node:name(.)"!] of [!"node:name(..)"!] of [!"node:name(../..)"!] */
static CONST(J1939Tp_RxNSduType, J1939TP_CONST) [!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_rx_nsdu[[!"num:i(count(J1939TpRxNSdu/eb-list::*))"!]] =
{
    [!LOOP "util:distinct(node:order(J1939TpRxNSdu/eb-list::*))"!]
    {
      &[!"node:name(../../../../../..)"!]_[!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_rx_nsdu_ctrl[0],    /* structure, RAM structure for monitoring the NSDU parameters */
      J1939TpConf_J1939TpRxNSdu_[!"as:name(.)"!], /* uint16, Own ID for CancelReceive used by PduR */
      [!VAR "J1939TpRxNSduRefVerify" = "as:name(as:ref(J1939TpRxNSduRef))"!]
      [!VAR "RefFound" = "'false'"!]
      [!LOOP "(util:distinct(node:order(../../../../../../../../../../../PduR/ELEMENTS/PduR/PduRRoutingTables/eb-list::*)))"!]
        [!IF "$RefFound = 'true'"!]
          [!BREAK!]
        [!ELSE!]
          [!LOOP "(util:distinct(node:order(PduRRoutingTable/eb-list::*)))"!]
            [!IF "$RefFound = 'true'"!]
              [!BREAK!]
            [!ELSE!]
              [!LOOP "(util:distinct(node:order(PduRRoutingPath/eb-list::*)))"!]
                [!IF "$J1939TpRxNSduRefVerify = as:name(as:ref(PduRSrcPdu/PduRSrcPduRef))"!]
      [!"(PduRSrcPdu/PduRSourcePduHandleId)"!]U,  /*uint16, The I-PDU identifier (PduRSrc) used for TxConfirmation to J1939Rm from CanIf or J1939Tp. */
                  [!VAR "RefFound" = "'true'"!]
                  [!BREAK!]
                [!ENDIF!]
              [!ENDLOOP!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$RefFound = 'false'"!]
        [!ERROR!]The [!"$J1939TpRxNSduRefVerify"!] reference is not matching with PduRSrcPduRef configuration.[!ENDERROR!]
      [!ENDIF!]
      [!IF "not(node:empty(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef))"!]
        [!VAR "MetaDataItemLength"= "'0'"!]
        [!IF "node:refvalid(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)"!]
          [!IF "node:exists(node:ref(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'PRIORITY_8'])"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'TARGET_ADDRESS_16'])"!]
              [!IF "node:exists(node:ref(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'SOURCE_ADDRESS_16'])"!]
                [!VAR "MetaDataItemLength"= "'4'"!]
              [!ELSE!]
                [!ERROR!]MetaDataItem "SOURCE_ADDRESS_16" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxNSduRef))"!]" of J1939TpRxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
              [!ENDIF!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "TARGET_ADDRESS_16" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxNSduRef))"!]" of J1939TpRxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
            [!ENDIF!]
          [!ELSEIF "node:exists(node:ref(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'TARGET_ADDRESS_16'])"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'SOURCE_ADDRESS_16'])"!]
              [!VAR "MetaDataItemLength"= "'2'"!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "SOURCE_ADDRESS_16" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxNSduRef))"!]" of J1939TpRxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
            [!ENDIF!]
          [!ELSEIF "node:exists(node:ref(node:ref(J1939TpRxNSduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'SOURCE_ADDRESS_16'])"!]
            [!VAR "MetaDataItemLength"= "'1'"!]
           [!ENDIF!]
        [!ELSE!]
          [!ERROR!]No proper MetaDataTypeRef "[!"node:ref(J1939TpRxNSduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxNSduRef))"!]" of J1939TpRxNSdu "[!"as:name(.)"!]".[!ENDERROR!]
        [!ENDIF!]
      [!"$MetaDataItemLength"!]U, /* uint8, MetaDataLength for the configured NSDU in the receiver side */
      [!ELSE!]
      0U,
      [!ENDIF!]
      [!IF "(num:i($CanFDTxChannelCounter) > num:i(0)) or (num:i($CanFDRxChannelCounter) > num:i(0))"!]
      [!IF "node:exists(J1939TpRxAssuranceDataType)"!]
      [!"J1939TpRxAssuranceDataType"!], /* Assurance data type */
        [!IF "J1939TpRxAssuranceDataType != 'J1939TP_NO_ASSURANCE_DATA'"!]
          [!IF "node:exists(J1939TpRxAssuranceDataLength)"!]
      [!"J1939TpRxAssuranceDataLength"!] /* The length of the assurance data */
          [!ELSE!]
      J1939TP_DYNAMIC_ASSURANCE_DATA_LENGTH /* Assurance data is dynamic */
          [!ENDIF!]
        [!ELSE!]
      0U /* Assurance data isn't used for this NSdu */
        [!ENDIF!]
      [!ELSE!]
      J1939TP_NO_ASSURANCE_DATA, /* The Tx NSdu doesn't support CanFD Transmission, No assurance data */
      0U /* Assurance data isn't used for this NSdu */
      [!ENDIF!]
      [!ENDIF!]

    },
    [!ENDLOOP!]
};
  [!ENDLOOP!]
[!ENDLOOP!]

/* TxPg configuration of [!"node:name(.)"!] */
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]

/* TxPg configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
static CONST(J1939Tp_TxPgType, J1939TP_CONST) [!"node:name(../..)"!]_[!"node:name(.)"!]_tx_pg[[!"num:i(count(J1939TpTxPg/eb-list::*))"!]] =
{
  [!LOOP "util:distinct(node:order(J1939TpTxPg/eb-list::*))"!]
  {
    &[!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_tx_nsdu[0], /* structure, J1939TpTxNSdu container */
    [!"node:value(J1939TpTxPgPGN)"!]U, /* uint32,PGN of the referenced N-SDUs. */
    [!IF "((node:existsAndTrue(J1939TpTxPgDynLength)) and (node:exists(J1939TpTxDirectNPdu)))"!]
    J1939TpConf_J1939TpTxDirectNPdu_[!"as:name(J1939TpTxDirectNPdu)"!],  /* uint16, Own ID for TxConfirmation from CanIf */
    [!VAR "J1939TpTxDirectNPduRefVerify" = "as:name(as:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef))"!]
    [!VAR "RefFound" = "'false'"!]
    [!IF "node:existsAndTrue(../../J1939TpTxCanFDSupport)"!]
      [!LOOP "(util:distinct(node:order(../../../../../../../../../PduR/ELEMENTS/PduR/PduRRoutingTables/eb-list::*)))"!]
        [!IF "$RefFound = 'true'"!]
          [!BREAK!]
        [!ELSE!]
          [!LOOP "(util:distinct(node:order(PduRRoutingTable/eb-list::*)))"!]
            [!IF "$RefFound = 'true'"!]
              [!BREAK!]
            [!ELSE!]
              [!LOOP "(util:distinct(node:order(PduRRoutingPath/eb-list::*)))"!]
                [!IF "$J1939TpTxDirectNPduRefVerify = as:name(as:ref(PduRSrcPdu/PduRSrcPduRef))"!]
    [!"(PduRSrcPdu/PduRSourcePduHandleId)"!]U,  /*uint16, The I-PDU identifier (PduRTx) used for Transmit the Direct PG. */
                  [!VAR "RefFound" = "'true'"!]
                  [!BREAK!]
                [!ENDIF!]
              [!ENDLOOP!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ELSE!]
      [!LOOP "(util:distinct(node:order(../../../../../../../../../CanIf/ELEMENTS/CanIf/CanIfInitCfg/eb-list::*)))"!]
        [!IF "$RefFound = 'true'"!]
          [!BREAK!]
        [!ELSE!]
          [!LOOP "(util:distinct(node:order(CanIfTxPduCfg/eb-list::*)))"!]
            [!IF "$J1939TpTxDirectNPduRefVerify = as:name(as:ref(CanIfTxPduRef))"!]
    [!"CanIfTxPduId"!]U, /* uint16, The I-PDU identifier (CanIfTx) used for Transmit the Direct PG */
              [!VAR "RefFound" = "'true'"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDIF!]
    [!IF "$RefFound = 'false'"!]
    J1939TP_INVALID_IPDU,
    [!ENDIF!]
      [!IF "not(node:empty(node:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef)/MetaDataTypeRef))"!]
        [!VAR "MetaDataItemLength"= "'0'"!]
        [!IF "node:refvalid(node:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef)/MetaDataTypeRef)"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
            [!VAR "MetaDataItemLength"= "'4'"!]
             [!ELSE!]
              [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef))"!]" of J1939TpTxDirectNPdu "[!"as:name(J1939TpTxDirectNPdu)"!]".[!ENDERROR!]
            [!ENDIF!]
          [!ELSE!]
          [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef))"!]" of J1939TpTxDirectNPdu "[!"as:name(J1939TpTxDirectNPdu)"!]".[!ENDWARNING!]
        [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* uint8, MetaDataLength of Direct Pdu from EcuC */
      [!ELSE!]
    0U,
      [!ENDIF!]
    [!ELSE!]
    J1939TP_INVALID_IPDU,
    J1939TP_INVALID_IPDU,
    0U,
    [!ENDIF!]
    [!"num:i(count(J1939TpTxNSdu/eb-list::*))"!]U,  /* uint16, Number of configured transmit NSdus.*/
    [!IF "node:existsAndTrue(J1939TpTxPgDynLength)"!]
    TRUE /* TRUE: when the N-SDU refers to a PGN with variable length. */
    [!ELSE!]
    FALSE /* FALSE: when the N-SDU refers to a PGN with fixed length. */
    [!ENDIF!]
  },
  [!ENDLOOP!]
};
[!ENDLOOP!]

/* RxPg configuration of [!"node:name(.)"!] */
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]

/* RxPg configuration of [!"node:name(.)"!] of [!"node:name(..)"!] */
static  CONST(J1939Tp_RxPgType, J1939TP_CONST) [!"node:name(../..)"!]_[!"node:name(.)"!]_rx_pg[[!"num:i(count(J1939TpRxPg/eb-list::*))"!]] =
{
  [!LOOP "util:distinct(node:order(J1939TpRxPg/eb-list::*))"!]
  {
    &[!"node:name(../../../..)"!]_[!"node:name(../..)"!]_[!"node:name(.)"!]_rx_nsdu[0],    /* structure, J1939TpRxNSdu container */
    [!"node:value(J1939TpRxPgPGN)"!]U, /* uint32, PGN of the referenced N-SDUs. */
    [!IF "((node:existsAndTrue(J1939TpRxPgDynLength)) and (node:existsAndTrue(node:exists(J1939TpRxDirectNPdu))))"!]
    J1939TpConf_J1939TpRxDirectNPdu_[!"as:name(J1939TpRxDirectNPdu)"!], /* uint16, Own ID for RxIndication for Direct Pdu. */
      [!IF "not(node:empty(node:ref(J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef)/MetaDataTypeRef))"!]
        [!VAR "MetaDataItemLength"= "'0'"!]
        [!IF "node:refvalid(node:ref(J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef)/MetaDataTypeRef)"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
            [!VAR "MetaDataItemLength"= "'4'"!]
            [!ELSE!]
            [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef))"!]" of J1939TpRxDirectNPdu "[!"as:name(J1939TpRxDirectNPdu)"!]".[!ENDERROR!]
            [!ENDIF!]
       [!ELSE!]
          [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef))"!]" of J1939TpRxDirectNPdu "[!"as:name(J1939TpRxDirectNPdu)"!]".[!ENDWARNING!]
        [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* uint8, MetaDataLength of DirectNpdu configured in EcuC */
      [!ELSE!]
    0U,
      [!ENDIF!]
    [!ELSE!]
    J1939TP_INVALID_IPDU,
    0U,
    [!ENDIF!]
    [!"num:i(count(J1939TpRxNSdu/eb-list::*))"!]U, /* uint16, Number of configured receive NSdus. */
    [!IF "node:existsAndTrue(J1939TpRxPgDynLength)"!]
    TRUE /* TRUE: when the N-SDU refers to a PGN with variable length. */
    [!ELSE!]
    FALSE /* FALSE: when the N-SDU refers to a PGN with fixed length. */
    [!ENDIF!]
  },
  [!ENDLOOP!]
};
[!ENDLOOP!]
[!IF "num:i(count(J1939TpTxChannel/eb-list::*)) > 0"!]
/* TxChannel configuration of [!"node:name(.)"!] */
static CONST(J1939Tp_TxChannelType, J1939TP_CONST) [!"node:name(.)"!]_tx_channel[[!"num:i(count(J1939TpTxChannel/eb-list::*))"!]] =
{
  [!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]
  {
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_tx_pg[0],    /* structure, J1939TpTxPg container */
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_TxChannelInfo,    /* Structure to hold tx Channel Status */
    [!IF "((node:exists(J1939TpTxProtocolType))  and (node:exists(J1939TpTxRetrySupport)))"!]
        [!IF "(node:value(J1939TpTxProtocolType) = 'J1939TP_PROTOCOL_CMDT') and node:existsAndTrue(J1939TpTxRetrySupport)"!]
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_RetryInfo,  /* structure, Pointer to RetryInfoType variable of this channel. */
        [!ELSE!]
    NULL_PTR, /* structure, Pointer to RetryInfoType variable of this channel. */
        [!ENDIF!]
    [!ELSE!]
    NULL_PTR, /* structure, Pointer to RetryInfoType variable of this channel. */
    [!ENDIF!]
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_J1939TpTxDirectNPduAvailable[0],  /* structure, poointer to flag that dictates wether directpg npdu is available. */
    [!IF "(node:exists(J1939TpTxProtocolType))"!]
    [!"node:value(J1939TpTxProtocolType)"!],  /* Enum, Protocol type used by this channel. This parameter is only required for channels with fixed destination address. */
    [!ELSE!]
    J1939TP_PROTOCOL_CMDT,  /*Generic Channel uses metadata to detect protocol type, CMDT is used as default value and it will be ignored as protocol selection will be based on metadata DA. */
    [!ENDIF!]    
    J1939TpConf_J1939TpTxCmNPdu_[!"as:name(J1939TpTxCmNPdu)"!], /* Own ID for TP.CM/BAM or RTS frame transmit Confirmation ID used by CanIf. */
    [!VAR "J1939TpTxCmNPduRefVerify" = "as:name(as:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef))"!]
    [!VAR "RefFound" = "'false'"!]
      [!LOOP "(util:distinct(node:order(../../../../../../../CanIf/ELEMENTS/CanIf/CanIfInitCfg/eb-list::*)))"!]
        [!IF "$RefFound = 'true'"!]
          [!BREAK!]
        [!ELSE!]
          [!LOOP "(util:distinct(node:order(CanIfTxPduCfg/eb-list::*)))"!]
            [!IF "$J1939TpTxCmNPduRefVerify = as:name(as:ref(CanIfTxPduRef))"!]
    [!"CanIfTxPduId"!]U, /* Lower layer I-PDU identifier (CanIfTx) used for Transmit RTS or BAM. */
              [!VAR "RefFound" = "'true'"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$RefFound = 'false'"!]
        [!ERROR!]The J1939TpTxCmNPduRef reference [!"$J1939TpTxCmNPduRefVerify"!] is not matching with CanIfTxPduRef reference.[!ENDERROR!]
      [!ENDIF!]
    J1939TpConf_J1939TpTxDtNPdu_[!"as:name(J1939TpTxDtNPdu)"!], /* Own ID-For Dt Tx confirmation used by CanIf to J1939Tp. */
    [!VAR "J1939TpTxDtNPduRefVerify" = "as:name(as:ref(J1939TpTxDtNPdu/J1939TpTxDtNPduRef))"!]
    [!VAR "RefFound" = "'false'"!]
      [!LOOP "(util:distinct(node:order(../../../../../../../CanIf/ELEMENTS/CanIf/CanIfInitCfg/eb-list::*)))"!]
        [!IF "$RefFound = 'true'"!]
          [!BREAK!]
        [!ELSE!]
          [!LOOP "(util:distinct(node:order(CanIfTxPduCfg/eb-list::*)))"!]
            [!IF "$J1939TpTxDtNPduRefVerify = as:name(as:ref(CanIfTxPduRef))"!]
    [!"CanIfTxPduId"!]U, /* Lower layer I-PDU identifier (CanIfTx) used for transmit for DT Frame. */
              [!VAR "RefFound" = "'true'"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$RefFound = 'false'"!]
        [!ERROR!]The J1939TpTxDtNPduRef reference [!"$J1939TpTxDtNPduRefVerify"!] is not matching with CanIfTxPduRef reference.[!ENDERROR!]
      [!ENDIF!]
    [!IF "node:exists(J1939TpRxFcNPdu)"!]
    J1939TpConf_J1939TpRxFcNPdu_[!"as:name(J1939TpRxFcNPdu)"!], /* Own ID- N-PDU identifier used by CanIf for transmit CTS. */
    [!ELSE!]
    J1939TP_INVALID_FC,
    [!ENDIF!]
    [!"node:value(J1939TpTxMaxPacketsPerBlock)"!]U,  /* Maximum number of TP.DT frames the transmitting J1939Tp module is ready to send before waiting for another TP.CM_CTS. This parameter is transmitted in the TP.CM_RTS frame, and is thus only relevant for transmission of messages via CMDT. When J1939TpTxDynamicBlockCalculation is enabled, this parameter specifies a maximum for the calculated value. */
    [!"num:i(count(J1939TpTxPg/eb-list::*))"!]U, /* Number of configured Tx Pgs. */
    [!IF "(node:exists(J1939TpRxFcNPdu)) and (not(node:empty(node:ref(J1939TpRxFcNPdu/J1939TpRxFcNPduRef)/MetaDataTypeRef)))"!]
    [!VAR "MetaDataItemLength"= "'0'"!]
    [!IF "node:refvalid(node:ref(J1939TpRxFcNPdu/J1939TpRxFcNPduRef)/MetaDataTypeRef)"!]
          [!IF "node:exists(node:ref(node:ref(J1939TpRxFcNPdu/J1939TpRxFcNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
            [!VAR "MetaDataItemLength"= "'4'"!]
          [!ELSE!]
            [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxFcNPdu/J1939TpRxFcNPduRef))"!]" of J1939TpRxFcNPdu "[!"as:name(J1939TpRxFcNPdu)"!]".[!ENDERROR!]
          [!ENDIF!]
    [!ELSE!]
      [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpRxFcNPdu/J1939TpRxFcNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxFcNPdu/J1939TpRxFcNPduRef))"!]" of J1939TpRxFcNPdu "[!"as:name(J1939TpRxFcNPdu)"!]".[!ENDWARNING!]
    [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* MetaDataLength of J1939TpRxFcNPdu. */
    [!ELSE!]
    0U,
    [!ENDIF!]
    [!IF "not(node:empty(node:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef)/MetaDataTypeRef))"!]
      [!VAR "MetaDataItemLength"= "'0'"!]
      [!IF "node:refvalid(node:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef)/MetaDataTypeRef)"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
            [!VAR "MetaDataItemLength"= "'4'"!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef))"!]" of J1939TpTxCmNPdu "[!"as:name(J1939TpTxCmNPdu)"!]".[!ENDERROR!]
            [!ENDIF!]
    [!ELSE!]
    [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef))"!]" of J1939TpTxCmNPdu "[!"as:name(J1939TpTxCmNPdu)"!]".[!ENDWARNING!]
    [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* MetaDataLength of J1939TpTxCmNPdu. */
    [!ELSE!]
    0U,
    [!ENDIF!]
    [!IF "not(node:empty(node:ref(J1939TpTxDtNPdu/J1939TpTxDtNPduRef)/MetaDataTypeRef))"!]
      [!VAR "MetaDataItemLength"= "'0'"!]
        [!IF "node:refvalid(node:ref(J1939TpTxCmNPdu/J1939TpTxCmNPduRef)/MetaDataTypeRef)"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpTxDtNPdu/J1939TpTxDtNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
              [!VAR "MetaDataItemLength"= "'4'"!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxDtNPdu/J1939TpTxDtNPduRef))"!]" of J1939TpTxDtNPdu "[!"as:name(J1939TpTxDtNPdu)"!]".[!ENDERROR!]
            [!ENDIF!]
      [!ELSE!]
        [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpTxDtNPdu/J1939TpTxDtNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxDtNPdu/J1939TpTxDtNPduRef))"!]" of J1939TpTxDtNPdu "[!"as:name(J1939TpTxDtNPdu)"!]".[!ENDWARNING!]
      [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* MetaDataLength of J1939TpTxDtNPdu. */
    [!ELSE!]
    0U,
    [!ENDIF!]
    [!IF "((node:exists(J1939TpTxRetrySupport)) and (node:existsAndTrue(J1939TpTxRetrySupport)))"!]
    TRUE, /* Enable support for repetition of failed transmission using TP.CM_CTS with a packet number that has already been sent. */
    [!ELSE!]
    FALSE, /* Disable support for repetition of failed transmission. */
    [!ENDIF!]
    [!IF "((node:exists(J1939TpTxDynamicBlockCalculation)) and (node:existsAndTrue(J1939TpTxDynamicBlockCalculation)))"!]
    TRUE, /* Enable dynamic calculation of "maximum number of packets that can be sent" value in TP.CM_RTS */
    [!ELSE!]
    FALSE, /* Disable dynamic calculation of "maximum number of packets that can be sent" value in TP.CM_RTS */
    [!ENDIF!]
    [!IF "((node:exists(J1939TpTxDynamicBlockCalculation)) and (node:existsAndTrue(J1939TpTxCancellationSupport)))"!]
    TRUE, /* Enable transmit cancellation using the API J1939Tp_CancelTransmit() for this channel */
    [!ELSE!]
    FALSE, /* Disable transmit cancellation for this channel */
    [!ENDIF!]
    [!IF "(node:existsAndTrue(J1939TpTxCanFDSupport))"!]
    TRUE  /* Enable CanFD Transmission for this channel */
    [!ELSE!]
    FALSE /* Disable CanFD Transmission for this channel */
    [!ENDIF!]
  },
  [!ENDLOOP!]
};
[!ENDIF!]
#define J1939TP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Tp_MemMap.h>


#define J1939TP_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Tp_MemMap.h>

[!IF "num:i(count(J1939TpRxChannel/eb-list::*)) > 0"!]
/* RxChannel configuration of [!"node:name(.)"!] */
static VAR(J1939Tp_RxChannelType, J1939TP_VAR) [!"node:name(.)"!]_rx_channel[[!"num:i(count(J1939TpRxChannel/eb-list::*))"!]] =
{
  [!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]
  {
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_rx_pg[0],    /* structure, J1939TpRxPg container */
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_RxChannelInfo,   /* Structure to hold Rx Channel Status */
    &[!"node:name(../..)"!]_[!"node:name(.)"!]_RxChannelAbort,       /* Structure to hold Rx Channel Abort type */
    [!IF "(node:exists(J1939TpRxProtocolType))"!]
    [!"node:value(J1939TpRxProtocolType)"!],  /* Enum, Protocol type used by this channel. This parameter is only required for channels with fixed destination address. */
    [!ELSE!]
    J1939TP_PROTOCOL_ACCEPT_ANY,  /*Generic Channel uses metadata to detect protocol type, CMDT is used as default value and it will be ignored as protocol selection will be based on metadata DA. */
    [!ENDIF!]     
    J1939TpConf_J1939TpRxCmNPdu_[!"as:name(J1939TpRxCmNPdu)"!], /* uint16, TP Own ID-RX N-PDU ID for TP.CM and abort in CMDT: CanIf -> J1939Tp */
    J1939TpConf_J1939TpRxDtNPdu_[!"as:name(J1939TpRxDtNPdu)"!], /* uint16, TP Own ID-RX N-PDU ID for TP.DT: Canif -> J1939Tp */
    [!IF "((node:exists(J1939TpRxProtocolType)) and (J1939TpRxProtocolType = 'J1939TP_PROTOCOL_CMDT')) or (not(node:exists(J1939TpRxProtocolType)))"!]
      [!VAR "J1939TpTxFcNPduRefVerify" = "as:name(as:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef))"!]
      [!VAR "RefFound" = "'false'"!]
        [!LOOP "(util:distinct(node:order(../../../../../../../CanIf/ELEMENTS/CanIf/CanIfInitCfg/eb-list::*)))"!]
          [!IF "$RefFound = 'true'"!]
            [!BREAK!]
          [!ELSE!]
            [!LOOP "(util:distinct(node:order(CanIfTxPduCfg/eb-list::*)))"!]
              [!IF "$J1939TpTxFcNPduRefVerify = as:name(as:ref(CanIfTxPduRef))"!]
    [!"CanIfTxPduId"!]U, /* uint16, The I-PDU identifier (CanIfTx) used  for transmitting CTS used by J1939Tp. */
                [!VAR "RefFound" = "'true'"!]
                [!BREAK!]
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$RefFound = 'false'"!]
          [!ERROR!]The J1939TpTxFcNPduRef reference [!"$J1939TpTxFcNPduRefVerify"!] is not matching with CanIfTxPduRef reference.[!ENDERROR!]
        [!ENDIF!]
    J1939TpConf_J1939TpTxFcNPdu_[!"as:name(J1939TpTxFcNPdu)"!],  /* uint16, Tx N-PDU ID of J1939Tp used by CanIf to provide the confirmation of CTS */
    [!ELSE!]
    J1939TP_INVALID_IPDU, /* uint16, Tx N-PDU ID of CanIf for transmitting CTS used by J1939Tp */
    J1939TP_INVALID_IPDU, /* uint16, Tx N-PDU ID of J1939Tp used by CanIf to provide the confirmation of CTS */
    [!ENDIF!]
    [!IF "node:exists(J1939TpRxDynamicBufferRatio) "!]
    [!"node:value(J1939TpRxDynamicBufferRatio)"!]U, /* uint8, Percentage of available buffer that shall be used for retry. */
    [!ELSE!]
    0U, /* uint8, Percentage of available buffer that shall be used for retry. */
    [!ENDIF!]
    [!"node:value(J1939TpRxPacketsPerBlock)"!]U,  /* uint8, Number of TP.DT frames the receiving J1939Tp module allows the sender to send before waiting for another TP.CM_CTS. */
    [!"num:i(count(J1939TpRxPg/eb-list::*))"!]U, /* uint16, Number of configured Rx Pgs. */
    [!IF "not(node:empty(node:ref(J1939TpRxCmNPdu/J1939TpRxCmNPduRef)/MetaDataTypeRef))"!]
      [!VAR "MetaDataItemLength"= "'0'"!]
      [!IF "node:refvalid(node:ref(J1939TpRxCmNPdu/J1939TpRxCmNPduRef)/MetaDataTypeRef)"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpRxCmNPdu/J1939TpRxCmNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
              [!VAR "MetaDataItemLength"= "'4'"!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxCmNPdu/J1939TpRxCmNPduRef))"!]" of J1939TpRxCmNPdu "[!"as:name(J1939TpRxCmNPdu)"!]".[!ENDERROR!]
            [!ENDIF!]
      [!ELSE!]
        [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpRxCmNPdu/J1939TpRxCmNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxCmNPdu/J1939TpRxCmNPduRef))"!]" of J1939TpRxCmNPdu "[!"as:name(J1939TpRxCmNPdu)"!]".[!ENDWARNING!]
      [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* uint8. Get the MetaDataLength for the RTS/BAM pdur value may be 0 or 1 or 2 or 4. */
    [!ELSE!]
    0U,
    [!ENDIF!]
    [!IF "not(node:empty(node:ref(J1939TpRxDtNPdu/J1939TpRxDtNPduRef)/MetaDataTypeRef))"!]
      [!VAR "MetaDataItemLength"= "'0'"!]
      [!IF "node:refvalid(node:ref(J1939TpRxDtNPdu/J1939TpRxDtNPduRef)/MetaDataTypeRef)"!]
            [!IF "node:exists(node:ref(node:ref(J1939TpRxDtNPdu/J1939TpRxDtNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
              [!VAR "MetaDataItemLength"= "'4'"!]
            [!ELSE!]
              [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxDtNPdu/J1939TpRxDtNPduRef))"!]" of J1939TpRxDtNPdu "[!"as:name(J1939TpRxDtNPdu)"!]".[!ENDERROR!]
            [!ENDIF!]
      [!ELSE!]
        [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpRxDtNPdu/J1939TpRxDtNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpRxDtNPdu/J1939TpRxDtNPduRef))"!]" of J1939TpRxDtNPdu "[!"as:name(J1939TpRxDtNPdu)"!]".[!ENDWARNING!]
      [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* uint8. Get the MetaDataLength of RxDtNPdu for data transmission to CanIf. */
    [!ELSE!]
    0U,
    [!ENDIF!]
    [!IF "node:exists(J1939TpTxFcNPdu)"!]
      [!IF "not(node:empty(node:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef)/MetaDataTypeRef))"!]
        [!VAR "MetaDataItemLength"= "'0'"!]
        [!IF "node:refvalid(node:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef)/MetaDataTypeRef)"!]
              [!IF "node:exists(node:ref(node:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef)/MetaDataTypeRef)/MetaDataItem/eb-list::*[MetaDataItemType = 'CAN_ID_32'])"!]
                [!VAR "MetaDataItemLength"= "'4'"!]
              [!ELSE!]
                [!ERROR!]MetaDataItem "CAN_ID_32" is not configured for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef))"!]" of J1939TpTxFcNPdu "[!"as:name(J1939TpTxFcNPdu)"!]".[!ENDERROR!]
              [!ENDIF!]
        [!ELSE!]
          [!WARNING!]No proper MetaDataTypeRef "[!"node:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef)/MetaDataTypeRef"!]" exist for the reference EcuC Pdu "[!"node:name(as:ref(J1939TpTxFcNPdu/J1939TpTxFcNPduRef))"!]" of J1939TpTxFcNPdu "[!"as:name(J1939TpTxFcNPdu)"!]".[!ENDWARNING!]
        [!ENDIF!]
    [!"$MetaDataItemLength"!]U, /* uint8. Get the MetaDataLength of TxFcNPdu for CTS/EOMAck/Abort Frame transmission to CanIf. */
      [!ELSE!]
      0U,
      [!ENDIF!]
    [!ELSE!]
    J1939TP_INVALID_FC,
    [!ENDIF!]
    [!IF "((node:exists(J1939TpRxRetrySupport)) and (node:existsAndTrue(J1939TpRxRetrySupport)))"!]
    TRUE, /* boolean, Enable support for triggering repetition of failed transmission using TP.CM_CTS with a packet number that has already been sent. */
    [!ELSE!]
    FALSE, /* boolean, Disable support for triggering repetition of failed transmission using TP.CM_CTS with a packet number that has already been sent. */
    [!ENDIF!]
    [!IF "((node:exists(J1939TpRxDynamicBlockCalculation)) and (node:existsAndTrue(J1939TpRxDynamicBlockCalculation)))"!]
    TRUE, /* boolean, Enable dynamic calculation of "number of packets that can be sent" value in TP.CM_CTS. */
    [!ELSE!]
    FALSE, /* boolean, Disable dynamic calculation of "number of packets that can be sent" value in TP.CM_CTS. */
    [!ENDIF!]
    [!IF "((node:exists(J1939TpRxCancellationSupport)) and (node:existsAndTrue(J1939TpRxCancellationSupport)))"!]
    TRUE, /* boolean, Enable receive cancellation using the API J1939Tp_CancelReceive() for this channel. */
    [!ELSE!]
    FALSE, /* boolean, Disable receive cancellation using the API J1939Tp_CancelReceive() for this channel. */
    [!ENDIF!]
    [!IF "(node:existsAndTrue(J1939TpRxCanFDSupport))"!]
    TRUE  /* Enable CanFD Reception for this channel */
    [!ELSE!]
    FALSE /* Disable CanFD Reception for this channel */
    [!ENDIF!]
  } ,
  [!ENDLOOP!]
};
[!ENDIF!]
#define J1939TP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Tp_MemMap.h>

[!VAR "ConfigIndex" = "num:i($ConfigIndex + 1)"!]
[!ENDSELECT!][!//

#define J1939TP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Tp_MemMap.h>

static CONST(J1939Tp_GeneralType, J1939TP_CONST) j1939tp_general =
{
  [!IF "node:existsAndTrue(J1939TpGeneral/J1939TpCancellationSupport)"!]
  &J1939Tp_CancelTransmit, /* Function pointer, Enable transmit cancellation. The API J1939Tp_CancelTransmit() is available when J1939TpCancellationSupport is TRUE. */
  &J1939Tp_CancelReceive, /* Function pointer, Enable receive cancellation. The API J1939Tp_CancelReceive() is available when J1939TpCancellationSupport is TRUE. */
  [!ELSE!]
  NULL_PTR, /* Function pointer, Enable transmit cancellation. The API J1939Tp_CancelTransmit() is available when J1939TpCancellationSupport is TRUE. */
  NULL_PTR, /* Function pointer, Enable receive cancellation. The API J1939Tp_CancelReceive() is available when J1939TpCancellationSupport is TRUE. */
  [!ENDIF!]
  [!IF "node:existsAndTrue(J1939TpGeneral/J1939TpVersionInfoApi)"!]
  &J1939Tp_GetVersionInfo, /* Function pointer, The function J1939Tp_GetVersionInfo is configurable (On/Off) by this configuration parameter. */
  [!ELSE!]
  NULL_PTR, /* Function pointer, The function J1939Tp_GetVersionInfo is configurable (On/Off) by this configuration parameter. */
  [!ENDIF!]
  [!"num:i((($T1) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =750ms/(main function period in ms) Timeout occurred on receiver side Timeout between two data packets. */
  [!"num:i((($T2) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =1250ms/(main function period in ms) Timeout occurred on receiver side Timeout between RTS/CTS and next data. */
  [!"num:i((($T3) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =1250ms/(main function period in ms) Timeout occurred on transmitter side Timeout between data and next CTS. */
  [!"num:i((($T4) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =1050ms/(main function period in ms) Timeout occurred on transmitter side Timeout after CTS with 0 packets. */
  [!"num:i((($T5) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =3000ms/(main function period in ms) Timeout occurred on transmitter side after transmission of FD.TP.CM_EOMS frame.*/
  [!IF "num:i((($Tr) div ($J1939TpMainFunctionPeriodValue))) < 1"!]
    1U,     /* ( Tr ) Timeout occurred on transmitter or receiver side while trying to send the next TP.DT or TP.CM frame. */
  [!ELSE!]
  [!"num:i((($Tr) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =200ms/(main function period in ms) Timeout occurred on transmitter or receiver side while trying to send the next TP.DT or TP.CM frame. */
  [!ENDIF!]
  [!IF "num:i((($Tbammin) div ($J1939TpMainFunctionPeriodValue))) < 2"!]
  0U,    /* Tbammin BAM minimal time between two messages. */
  [!ELSE!]
  [!"num:i((($Tbammin) div ($J1939TpMainFunctionPeriodValue))-2)"!]U,    /* uint16, =50ms/(main function period in ms) BAM minimal time between two messages. */
  [!ENDIF!]
  [!"num:i((($Th) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =500ms/(main function period in ms) Timeout occurred on receiver side while trying to send the next TP.CM/CTS frame after a TP.CM/CTS(0) frame. */
  [!IF "num:i((($Tbammax) div ($J1939TpMainFunctionPeriodValue))) < 1"!]
  1U,    /* Tbammax BAM maximal time between two messages. */
  [!ELSE!]
  [!"num:i((($Tbammax) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* uint16, =200ms/(main function period in ms) BAM maximal time between two messages. */
  [!ENDIF!]
  [!"num:i((($TxConfirmationTimeOut) div ($J1939TpMainFunctionPeriodValue))-1)"!]U,    /* TxConfirmation Timeout */
  [!IF "node:existsAndTrue(J1939TpGeneral/J1939TpDevErrorDetect)"!]
  TRUE, /* boolean, Switches the Development Error Detection and Notification. */
  [!ELSE!]
  FALSE, /* boolean, Switches the Development Error Detection and Notification */
  [!ENDIF!]
};

[!LOOP "util:distinct(node:order(J1939TpConfiguration/eb-list::*))"!]

/*  Configuration for J1939TpConfiguration_0_config */
CONST(J1939Tp_GeneralConfigType, J1939TP_CONST) J1939TpConfiguration_0_config=
{
    [!IF "num:i(count(J1939TpTxChannel/eb-list::*)) > 0"!]
  &[!"node:name(.)"!]_tx_channel[0],    /* structure, J1939TpTxChannel Container. */
    [!ELSE!]
        NULL_PTR, /* NO J1939TpTxChannels configured */
    [!ENDIF!]
    [!IF "num:i(count(J1939TpRxChannel/eb-list::*)) > 0"!]
  &[!"node:name(.)"!]_rx_channel[0],    /* structure, J1939TpRxChannel Container. */
    [!ELSE!]
        NULL_PTR, /* NO J1939TpRxChannels configured */
    [!ENDIF!]
  &j1939tp_general,    /* structure, J1939Tp General configurations. */
  [!"num:i(count(J1939TpTxChannel/eb-list::*))"!]U,    /* uint16, Number of configured J1939Tp Tx channels. */
  [!"num:i(count(J1939TpRxChannel/eb-list::*))"!]U    /* uint16, Number of configured J1939Tp Rx channels. */
};
[!ENDLOOP!]

#define J1939TP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Tp_MemMap.h>

/*==================[end of file]============================================*/
[!ENDCODE!]
