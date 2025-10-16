/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                BlPduR configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Cfg.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]
[!NOCODE!]
[!/* Verify <layer>_MANAGE_PERIOD is multiple of BLPDUR_MANAGE_PERIOD */!]
[!/* Else an error is generated*/!]

[!/* PROG */!]
[!IF "node:exists(as:modconf('Prog'))"!]
    [!IF " (num:i(as:modconf('Prog')/General/MANAGE_PERIOD) mod num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD)) != 0"!]
        [!ERROR "PROG_MANAGE_PERIOD is not multiple of BLPDUR_MANAGE_PERIOD"!]
    [!ENDIF!]
[!ENDIF!]

[!/* UDS */!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!IF " (num:i(as:modconf('Uds')/General/UDS_MANAGE_PERIOD) mod num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD)) != 0"!]
        [!ERROR "UDS_MANAGE_PERIOD is not multiple of BLPDUR_MANAGE_PERIOD"!]
    [!ENDIF!]
[!ENDIF!]

[!VAR "UPDATE_TP_PARAM_USED" = "0"!]
[!IF "node:exists(as:modconf('PduR'))"!]
    [!IF " as:modconf('PduR')/PduRBswModules/BlPduR/PduRChangeParameterRequestApi = 'true'"!]
        [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
    [!ENDIF!]
[!ENDIF!]

[!/* SA */!]
[!IF "node:exists(as:modconf('SA'))"!]
    [!IF " (num:i(as:modconf('SA')/General/MANAGE_PERIOD) mod num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD)) != 0"!]
        [!ERROR "SA_MANAGE_PERIOD is not multiple of BLPDUR_MANAGE_PERIOD"!]
    [!ENDIF!]
[!ENDIF!]

[!VAR "RxPduCount" = "0"!]
[!VAR "RxConnectionCount" = "0"!]
[!LOOP "PduConnection/*"!]
    [!LOOP "RxPdu/*"!]
        [!VAR "RxPduCount" = "$RxPduCount + 1"!]
    [!ENDLOOP!]
    [!VAR "RxConnectionCount" = "$RxConnectionCount + 1"!]
[!ENDLOOP!]

[!VAR "SharedPduCount" = "0"!]
[!VAR "RxConnectionCount" = "0"!]
[!LOOP "PduConnection/*"!]
            [!IF "ShareFunctionalId = 'true'"!]
                [!VAR "SharedPduCount" = "$SharedPduCount + 1"!]
            [!ENDIF!]
    [!VAR "RxConnectionCount" = "$RxConnectionCount + 1"!]
[!ENDLOOP!]

[!MACRO "GetIDFromPDU", "PduInfo"!]    [!/*
    Parse all the CanIfRxPduCfg configured
    */!][!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!][!/*
        Check if the PDU is the same as the one retrieve from CanTp
        */!][!IF "$PduInfo = CanIfRxPduRef"!][!/*
            if found retrieve the CanId linked to it
            */!][!WS "4"!][!"num:inttohex(CanIfRxPduCanId)"!]U
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDMACRO!]

[!/* End of verify <layer>_MANAGE_PERIOD is multiple of BLPDUR_MANAGE_PERIOD */!]
[!ENDNOCODE!]
[!CODE!]
#ifndef BLPDUR_CFG_H
#define BLPDUR_CFG_H

#define BLPDUR_FALSE      0U
#define BLPDUR_TRUE       1U

/* BlPduR Manage period */
#define BLPDUR_MANAGE_PERIOD               [!"num:i(General/MANAGE_PERIOD)"!]U

/* Define if the UDS module shall have a scheduling counter or not (only necessary if module have a different schedule than BlPduR) */
[!IF "node:exists(as:modconf('Lin')) and (num:i(as:modconf('Lin')/LinGeneral/LinManagePeriod) != num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD))"!]
#define BLPDUR_USE_LIN_MANAGE_CNT         STD_ON
[!ELSE!]
#define BLPDUR_USE_LIN_MANAGE_CNT         STD_OFF
[!ENDIF!]

/* Define if the UDS module shall have a scheduling counter or not (only necessary if module have a different schedule than BlPduR) */
[!IF "node:exists(as:modconf('Ltp')) and (num:i(as:modconf('Ltp')/LtpGeneral/LtpManagePeriod) != num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD))"!]
#define BLPDUR_USE_LTP_MANAGE_CNT         STD_ON
[!ELSE!]
#define BLPDUR_USE_LTP_MANAGE_CNT         STD_OFF
[!ENDIF!]

/* Define if the UDS module shall have a scheduling counter or not (only necessary if module have a different schedule than BlPduR) */
[!IF "node:exists(as:modconf('Uds')) and (num:i(as:modconf('Uds')/General/UDS_MANAGE_PERIOD) != num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD))"!]
#define BLPDUR_USE_UDS_MANAGE_CNT         STD_ON
[!ELSE!]
#define BLPDUR_USE_UDS_MANAGE_CNT         STD_OFF
[!ENDIF!]

/* Define if the Prog module shall have a scheduling counter or not (only necessary if module have a different schedule than BlPduR) */
[!IF "node:exists(as:modconf('Prog')) and (num:i(as:modconf('Prog')/General/MANAGE_PERIOD) != num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD))"!]
#define BLPDUR_USE_PROG_MANAGE_CNT        STD_ON
[!ELSE!]
#define BLPDUR_USE_PROG_MANAGE_CNT        STD_OFF
[!ENDIF!]

/* Define if the SA module shall have a scheduling counter or not (only necessary if module have a different schedule than BlPduR) */
[!IF "node:exists(as:modconf('SA')) and (num:i(as:modconf('SA')/General/MANAGE_PERIOD) != num:i(as:modconf('BlPduR')/General/MANAGE_PERIOD))"!]
#define BLPDUR_USE_SA_MANAGE_CNT          STD_ON
[!ELSE!]
#define BLPDUR_USE_SA_MANAGE_CNT          STD_OFF
[!ENDIF!]

/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define BLPDUR_UPDATE_TP_PARAM_ENABLE                     [!WS "20"!][!IF "$UPDATE_TP_PARAM_USED = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Network use definition */
#define BLPDUR_NETWORK_CAN_SUPPORTED      [!WS "6"!][!IF "as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BLPDUR_NETWORK_FLEXRAY_SUPPORTED  [!WS "2"!][!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BLPDUR_NETWORK_ETH_SUPPORTED      [!WS "6"!][!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BLPDUR_NETWORK_LIN_SUPPORTED      [!WS "6"!][!IF "as:modconf('BlPduR')/General/Lin_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/**** LIN Stack ****/
/* Define if the Lin module is present in the project configuration */
#define BLPDUR_USE_LIN [!WS "5"!][!IF "node:exists(as:modconf('Lin'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the Ltp module is present in the project configuration */
#define BLPDUR_USE_LTP [!WS "5"!][!IF "node:exists(as:modconf('Ltp'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/**** Bootloader Stack ****/
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/* Define if the ReProgMemM module is present in the project configuration */
#define BLPDUR_USE_REPROGMEMM [!WS "3"!][!IF "node:exists(as:modconf('ReProgMemM'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BLPDUR_USE_FLASH  STD_OFF
[!ELSEIF "node:exists(as:modconf('Flash'))"!]
/* Define if the Flash module is present in the project configuration */
#define BLPDUR_USE_FLASH [!WS "3"!][!IF "node:exists(as:modconf('Flash'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BLPDUR_USE_REPROGMEMM STD_OFF
[!ELSE!]
#define BLPDUR_USE_REPROGMEMM STD_OFF
#define BLPDUR_USE_FLASH  STD_OFF
[!ENDIF!]
/* Define if the Prog module is present in the project configuration */
#define BLPDUR_USE_PROG [!WS "4"!][!IF "node:exists(as:modconf('Prog'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the SA module is present in the project configuration */
#define BLPDUR_USE_SA [!WS "6"!][!IF "node:exists(as:modconf('SA'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the UDS module is present in the project configuration */
#define BLPDUR_USE_UDS [!WS "5"!][!IF "node:exists(as:modconf('Uds'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/**** ASR Stack ****/
/* Define if the PduR module is present in the project configuration */
#define BLPDUR_USE_PDUR [!WS "4"!][!IF "node:exists(as:modconf('PduR'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/**** Can Stack ****/
/* Define if the Can module is present in the project configuration */
#define BLPDUR_USE_CAN [!WS "5"!][!IF "node:exists(as:modconf('Can'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the CanIf module is present in the project configuration */
#define BLPDUR_USE_CANIF [!WS "3"!][!IF "node:exists(as:modconf('CanIf'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the CanTp module is present in the project configuration */
#define BLPDUR_USE_CANTP [!WS "3"!][!IF "node:exists(as:modconf('CanTp'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the CanSM module is present in the project configuration */
#define BLPDUR_USE_CANSM [!WS "3"!][!IF "node:exists(as:modconf('CanSM'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/**** Fr Stack ****/
/* Define if the Fr module is present in the project configuration */
#define BLPDUR_USE_FR [!WS "6"!][!IF "node:exists(as:modconf('Fr'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the FrIf module is present in the project configuration */
#define BLPDUR_USE_FRIF [!WS "4"!][!IF "node:exists(as:modconf('FrIf'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the FrTp module is present in the project configuration */
#define BLPDUR_USE_FRTP [!WS "4"!][!IF "node:exists(as:modconf('FrTp'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the FrSM module is present in the project configuration */
#define BLPDUR_USE_FRSM [!WS "4"!][!IF "node:exists(as:modconf('FrSM'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/**** Eth Stack ****/
/* Define if the Eth module is present in the project configuration */
#define BLPDUR_USE_ETH [!WS "5"!][!IF "node:exists(as:modconf('Eth'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the EthIf module is present in the project configuration */
#define BLPDUR_USE_ETHIF [!WS "3"!][!IF "node:exists(as:modconf('EthIf'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the EthSM module is present in the project configuration */
#define BLPDUR_USE_ETHSM [!WS "3"!][!IF "node:exists(as:modconf('EthSM'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the TcpIp module is present in the project configuration */
#define BLPDUR_USE_TCPIP [!WS "3"!][!IF "node:exists(as:modconf('TcpIp'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the SoAd module is present in the project configuration */
#define BLPDUR_USE_SOAD [!WS "4"!][!IF "node:exists(as:modconf('SoAd'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the DoIP module is present in the project configuration */
#define BLPDUR_USE_DOIP [!WS "4"!][!IF "node:exists(as:modconf('DoIP'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
/* Define if the EthTrcv module is present in the project configuration */
#define BLPDUR_USE_ETHTRCV [!WS "1"!][!IF "node:exists(as:modconf('EthTrcv'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
#define BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE          STD_ON
[!ELSE!]
#define BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE          STD_OFF
[!ENDIF!]

#define BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION         0U
#define BLPDUR_MULTIPLE_ID_EXTERNAL_NOTIFICATION    1U
#define BLPDUR_MULTIPLE_ID_OFF                      2U
#define BLPDUR_MULTIPLE_ID_NO_SEL                   0xFFU

[!IF "node:exists(as:modconf('CanIf'))"!]
    [!IF "MultipleIdentifier/MultipleIdentifierGroup != 'OFF'"!]
#define BLPDUR_MULTIPLE_ID_ENABLE        STD_ON
#define BLPDUR_MULTIPLE_ID_TYPE          BLPDUR_MULTIPLE_ID_[!"MultipleIdentifier/MultipleIdentifierGroup"!]
#define BLPDUR_MULTIPLE_ID_CONF_MAX      [!"num:i(count(IDGroup/*))"!]
        [!IF "MultipleIdentifier/MultipleIdentifierGroup = 'CAN_NOTIFICATION'"!]
#define BLPDUR_MULTIPLE_ID_CAN_NOTIF_PDU [!"num:i(count(IDGroup/*))"!]
#define BLPDUR_MULTIPLE_ID_TIMEOUT       [!"num:i(MultipleIdentifier/MultipleIdentifierSelectTimeout)"!]U
#define BLPDUR_MULTIPLE_ID_BYTE_IDX_IN_DATA [!"num:i(MultipleIdentifier/IDGroupByteNum)"!]U
#define BLPDUR_MULTIPLE_ID_CAN_SELECT_IDENT [!CALL "GetIDFromPDU", "PduInfo"="MultipleIdentifier/IDGroupPDURef"!]
#define BLPDUR_MULTIPLE_ID_PDU_ID           [!"num:inttohex((MultipleIdentifier)/RxPduId)"!]U
        [!ENDIF!]
    [!ELSE!]
#define BLPDUR_MULTIPLE_ID_TYPE          BLPDUR_MULTIPLE_ID_OFF
#define BLPDUR_MULTIPLE_ID_ENABLE        STD_OFF
    [!ENDIF!]
[!ELSE!]
#define BLPDUR_MULTIPLE_ID_TYPE          BLPDUR_MULTIPLE_ID_OFF
#define BLPDUR_MULTIPLE_ID_ENABLE        STD_OFF
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')) and (node:exists(as:modconf('Prog'))) and (as:modconf('Prog')/General/Sleep_Management_NM_Message ='true'))"!]
/* Sleep Management Feature for NM message */
#define BLPDUR_NM_MESSAGE_ENABLE         STD_ON
    [!IF "(as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup != 'OFF') and (SleepManagement/Grouping_NM_Message = 'true')"!]
#define BLPDUR_NM_MESSAGE_GROUP_ENABLE   STD_ON
    [!ELSE!]
#define BLPDUR_NM_MESSAGE_GROUP_ENABLE   STD_OFF
    [!ENDIF!]
#define BLPDUR_NM_MESSAGE_PDU_ID         [!"num:inttohex((SleepManagement)/RxPduId)"!]U
    [!IF "node:exists(as:modconf('CanIf'))"!]
#define BLPDUR_NM_MESSAGE_ID_CAN          [!CALL "GetIDFromPDU", "PduInfo"="SleepManagement/IDGroupPDURef"!]
    [!ENDIF!]
[!ELSE!]
#define BLPDUR_NM_MESSAGE_ENABLE         STD_OFF
#define BLPDUR_NM_MESSAGE_GROUP_ENABLE   STD_OFF
[!ENDIF!]


[!IF "General/Enable_DownloadData_Streaming = 'true'"!]
 /* Streaming Feature is Enabled */
#define BLPDUR_USE_STREAMING              STD_ON
[!ELSE!]
/* Streaming Feature is Disabled */
#define BLPDUR_USE_STREAMING              STD_OFF
[!ENDIF!]

/* All tester address are allowed */
#define BLPDUR_ALL_TESTER_ADDRESS         0xFFU

#define BLPDUR_NO_ACTIVE_CONNECTION       0xFFU
#define BLPDUR_INVALID_PDU                0xFFU
/* Define the number of physical buffer configured (from 1 to 4) */
#define BLPDUR_RX_PHY_BUFFER_NUM          [!"num:i(General/RxBufferNum)"!]U
[!IF "General/MultipleRxBuffer = 'true'"!]
#define BLPDUR_MULTIPLE_BUFFERS_ENABLE    STD_ON
[!ELSE!]
#define BLPDUR_MULTIPLE_BUFFERS_ENABLE    STD_OFF
[!ENDIF!]
[!IF "node:exists(as:modconf('BlPduR')/General/QueuedManagement)"!]
[!IF "General/QueuedManagement = 'true'"!]
#define BLPDUR_QUEUED_MANAGEMENT_ENABLE   STD_ON
#define BLPDUR_UDS_SRV_RCONTROL           0x31U
#define BLPDUR_UDS_CHECK_MEMORY_RID_0     0x02U
#define BLPDUR_UDS_CHECK_MEMORY_RID_1     0x12U
[!IF "node:exists(as:modconf('Prog')) and as:modconf('Prog')/DownloadVerification/Allow2MaxSuccessiveCheckMemoryRequests='true'"!]
#define BLPDUR_PROG_2_SUCCESSIVE_CHECKMEMORY_ALLOWED           STD_ON
[!ELSE!]
#define BLPDUR_PROG_2_SUCCESSIVE_CHECKMEMORY_ALLOWED           STD_OFF
[!ENDIF!]
[!ELSE!]
#define BLPDUR_QUEUED_MANAGEMENT_ENABLE    STD_OFF
[!ENDIF!]
[!IF "General/QueuedManagement = 'false' and General/MultipleRxBuffer = 'false'"!]
[!ENDIF!]
[!ELSEIF "General/MultipleRxBuffer = 'false'"!]
#define BLPDUR_QUEUED_MANAGEMENT_ENABLE    STD_OFF
[!ELSE!]
#define BLPDUR_QUEUED_MANAGEMENT_ENABLE    STD_OFF
[!ENDIF!]
/* Define Pdu for transmition */
[!FOR "PDU_IDX" = "1" TO "count(PduConnection/*)" STEP "1"!]
    [!IF "PduConnection/*[num:i($PDU_IDX)]/LinConnection = 'false'"!]
#define  BLPDUR_[!"name(node:ref(PduConnection/*[num:i($PDU_IDX)]/TxPduRef))"!] [!WS "15"!][!"PduConnection/*[num:i($PDU_IDX)]/TxConfPduId"!]U
    [!ENDIF!]
[!ENDFOR!]

[!IF "as:modconf('BlPduR')/General/Lin_Protocol_Supported = 'true'"!]
/* Define for Lin specific pdu value */
#define BLPDUR_LIN_TX_PDU                 0xFF
[!LOOP "PduConnection/*"!]
    [!IF "LinConnection = 'true'"!]
        [!VAR "RxIdx" = "RxPdu/*['0']/Id"!]
    [!ENDIF!]
[!ENDLOOP!]
/* Define the connection number that is used for the LIN */
#define BLPDUR_RX_LIN                     [!"$RxIdx"!]U
#define BLPDUR_LIN_BIT_RESPONSE_ENABLE    [!WS "4"!][!IF "as:modconf('Lin')/LinRspErrorBitCallbackName/LinRspErrorBitDetect = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BLPDUR_LIN_FRAME_IDX_TX           LIN_FRAME_IDX_[!"name(node:ref(as:modconf('Ltp')/LtpGeneral/LinTxFrameRef))"!]
[!IF "as:modconf('Lin')/LinRspErrorBitCallbackName/LinRspErrorBitDetect = 'true'"!]
/** \brief  Defines Lin response bit error frame reference */
#define BLPDUR_LIN_FRAME_IDX_BIT_RESP_ERROR   LIN_FRAME_IDX_[!"name(node:ref(as:modconf('Lin')/LinRspErrorBitCallbackName/LinRspErrorBitFrameRef))"!]
[!ENDIF!]
#define BLPDUR_LIN_SIGNAL_BIT_RESP_ERROR      LIN_SIGNAL_BIT_RESP_ERROR
[!ENDIF!]


#define BLPDUR_RX_SMALL_BUFFERSIZE          64U
/* Physical buffer size (same for all physical if multiple buffer enable) */
#define BLPDUR_RX_PHYS_BUFFERSIZE         [!"num:i(General/RxPhysicalBufferSize)"!]U

/* Number of Rx PDU configured + 1 see RQD_BLPDUR_CFG_073 */
#define BLPDUR_MAX_RX_PDU_NUM             ([!"num:i($RxPduCount)"!]U + 1U)

/* Number of Shared PDU configured */
#define BLPDUR_SHARED_RX_PDU_NUM             [!"num:i($SharedPduCount)"!]U

/* Number of connection configured */
#define BLPDUR_MAX_PDU_CONNECTION         [!"num:i($RxConnectionCount)"!]U

#define BLPDUR_OLD_BUFFER                 0x1U
#define BLPDUR_ALL_BUFFER                 0xFFU

[!VAR "PduDefault" = "0"!]
[!FOR "GROUP_IDX" = "1" TO "count(IDGroup/*)" STEP "1"!]
    [!IF "IDGroup/*[num:i($GROUP_IDX)]/Default = 'true'"!]
        [!VAR "PduDefault" = "$GROUP_IDX - 1"!]
    [!ENDIF!]
    [!VAR "PduCount" = "0"!]
    [!FOR "CONNECT_IDX" = "1" TO "count(IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*)" STEP "1"!]
        [!SELECT "node:ref(IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*[$CONNECT_IDX]/ConnectionRef)"!]
            [!LOOP "RxPdu/*"!]
                [!VAR "PduCount" = "$PduCount + 1"!]
            [!ENDLOOP!]
            [!IF "ShareFunctionalId = 'true'"!]
                [!VAR "PduCount" = "$PduCount + 1"!]
            [!ENDIF!]
        [!ENDSELECT!]
        [!IF "( (as:modconf('BlPduR')/SleepManagement/Grouping_NM_Message = 'true') and ((IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*[num:i($CONNECT_IDX)]/ConnectionRef) = (as:modconf('BlPduR')/SleepManagement/PduConnectionGroupRef)) )"!]
            [!VAR "PduCount" = "$PduCount + 1"!]
        [!ENDIF!]
    [!ENDFOR!]
/* Number of CAN ID allowed in the ID group [!"num:i($GROUP_IDX - 1)"!] */
#define BLPDUR_CONNECTION_NUM_ID_GR_[!"num:i($GROUP_IDX - 1)"!]     [!"num:i($PduCount)"!]U
[!ENDFOR!]
/* Number of ID group configured */
#define BLPDUR_ID_GROUP_NUM               [!"num:i(count(IDGroup/*))"!]U
/* ID of the default group */
#define BLPDUR_ID_GROUP_DEFAULT           [!"num:i($PduDefault)"!]U


 [!IF "node:exists(as:modconf('CanTp'))"!]
[!MACRO "calcSTmin", "value"!][!/*
 */!][!IF "$value*1000 > 0.9"!][!/*
    */!][!"num:i($value*1000 + 0.99999)"!][!/*
 */!][!ELSEIF "$value*10000 >= 0.00001"!][!/*
    */!][!"num:i($value*10000 + 0.99999 + 240)"!][!/*
 */!][!ELSE!][!/*
    */!]0[!/*
 */!][!ENDIF!][!/*
*/!][!ENDMACRO!]

[!VAR "DefaultFound" = "0"!]
[!LOOP "as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*"!]
[!LOOP "CanTpRxNSdu/*"!]
          [!IF "'CANTP_PHYSICAL' = CanTpRxTaType"!]
          [!IF "$DefaultFound = 0"!]
#define BLPDUR_BS_DEFAULT     [!WS "8"!][!"CanTpBs"!]
#define BLPDUR_STMIN_DEFAULT  [!WS "4"!][!CALL "calcSTmin", "value"="CanTpSTmin"!]
          [!VAR "DefaultFound" = "1"!]
          [!ENDIF!]
          [!ENDIF!]
[!ENDLOOP!]
[!ENDLOOP!]
[!ENDIF!]


/* declaration of configuration */
extern tRxPdu stRxPdu[BLPDUR_MAX_RX_PDU_NUM+BLPDUR_SHARED_RX_PDU_NUM];
extern tPduConnection stPduConnection[BLPDUR_MAX_PDU_CONNECTION];
extern uint8 BlPduRRxPhysBuffer[BLPDUR_RX_PHY_BUFFER_NUM][BLPDUR_RX_PHYS_BUFFERSIZE];
extern tBufferInfoType stRxPhysBufferInfo[BLPDUR_RX_PHY_BUFFER_NUM];
extern tBufferConfigType stRxPhysBufferConfig[BLPDUR_RX_PHY_BUFFER_NUM];

extern uint8 BlPduRRxSmallBuffer[BLPDUR_MAX_RX_PDU_NUM][BLPDUR_RX_SMALL_BUFFERSIZE];
extern tBufferInfoType stRxSmallBufferInfo[BLPDUR_MAX_RX_PDU_NUM];
extern tBufferConfigType stRxSmallBufferConfig[BLPDUR_MAX_RX_PDU_NUM];


[!IF "node:exists(as:modconf('CanIf'))"!]
[!IF "MultipleIdentifier/MultipleIdentifierGroup != 'OFF'"!]
extern const tMultipleIdConfig stMultipleIdConfig[BLPDUR_ID_GROUP_NUM];
[!ENDIF!]
[!ENDIF!]



[!IF "node:exists(as:modconf('CanIf'))"!]
[!IF "MultipleIdentifier/MultipleIdentifierGroup != 'OFF'"!][!/*
Get all the ID for all the ID group configured
*/!][!FOR "GROUP_IDX" = "1" TO "count(IDGroup/*)" STEP "1"!]
/* Tab for all CanId configured in a connection */
extern Can_IdType auCanId_[!"num:i($GROUP_IDX - 1)"!][BLPDUR_CONNECTION_NUM_ID_GR_[!"num:i($GROUP_IDX - 1)"!]];
[!ENDFOR!]
[!ENDIF!]
[!ENDIF!]

 [!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]
 [!IF "(as:modconf('FrSM')/FrSMGeneral/FrSMKeySlotOnlyModeEnable = 'true')"!]
 #define BLPDUR_FRSM_ENABLEALLSLOTS STD_ON
 [!ELSE!]
 #define BLPDUR_FRSM_ENABLEALLSLOTS STD_OFF
 [!ENDIF!]
 [!ELSE!]
 #define BLPDUR_FRSM_ENABLEALLSLOTS STD_OFF
 [!ENDIF!]
#endif      /* BLPDUR_CFG_H */
[!ENDCODE!]
