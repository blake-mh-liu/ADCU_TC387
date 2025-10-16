/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BLUpdater configuration                       */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Cfg.h                 */
/*%%  |                             |  %%  \brief BLUpdater layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.9.0 BL3                */
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

#ifndef BLUPDATER_CFG_H
#define BLUPDATER_CFG_H

#ifndef NCS_UNITARY_TEST
extern const tCfgSegmentType stConfigBootReprog;
extern const tCfgSegmentType stConfigNewBootImage;
#else
extern tCfgSegmentType stConfigBootReprog;
extern tCfgSegmentType stConfigNewBootImage;
#endif

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

[!IF "(General/Eth_Protocol_Supported = 'true')"!]
/* Number of Rx PDU configured */
#define BLU_MAX_RX_PDU_NUM             [!"num:i($RxPduCount)"!]U

/* Number of Shared PDU configured */
#define BLU_SHARED_RX_PDU_NUM             [!"num:i($SharedPduCount)"!]U

/* Number of connection configured */
#define BLU_MAX_PDU_CONNECTION         [!"num:i($RxConnectionCount)"!]U

extern tRxPdu stRxPdu[BLU_MAX_RX_PDU_NUM+BLU_SHARED_RX_PDU_NUM];
extern tPduConnection stPduConnection[BLU_MAX_PDU_CONNECTION];
[!ENDIF!]

[!AUTOSPACING!]
[!IF "(General/Eth_Protocol_Supported = 'true')"!]
/* Define Pdu for transmition */
[!FOR "PDU_IDX" = "1" TO "count(PduConnection/*)" STEP "1"!]
    [!IF "PduConnection/*[num:i($PDU_IDX)]/LinConnection = 'false'"!]
#define  BLU_[!"name(node:ref(PduConnection/*[num:i($PDU_IDX)]/TxPduRef))"!] [!WS "15"!][!"PduConnection/*[num:i($PDU_IDX)]/TxConfPduId"!]U
    [!ENDIF!]
[!ENDFOR!]
[!ELSE!]
/* Define Pdu for transmition */
[!LOOP "PduConnection/*[LinConnection = 'false']"!]
#define  BLU_[!"name(node:ref(TxPduRef))"!]
[!ENDLOOP!]
[!ENDIF!]

#define BLU_MANAGE_PERIOD        [!WS "30"!][!"num:dectoint(General/BLU_MANAGE_PERIOD)"!]U

[!IF "(General/BLU_Communication_Support = 'true')"!]
#define BLU_NRC78_SENDING_PERIOD [!WS "23"!]([!"num:dectoint(General/NRC78_Sending_Period)"!]U/BLU_MANAGE_PERIOD)
[!ENDIF!]
 
[!IF "(Security/SecureBoot/SECURE_BOOT = 'true')"!]
#define BLU_SECURE_BOOT [!WS "16"!]STD_ON
#define BLU_BOOT_START_ADDR                  ([!"num:inttohex(Security/SecureBoot/BootCksStartAddress)"!]U)
#define BLU_BOOT_LENGTH                      ([!"num:inttohex(Security/SecureBoot/BootCksRangeLength)"!]U)
[!ELSE!]
#define BLU_SECURE_BOOT [!WS "16"!]STD_OFF
[!ENDIF!]

[!IF "(node:exists(as:modconf('ReProgMemM')))"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(as:modconf('ReProgMemM')/MemoryConfig/Memory/*))"!]
#define BLU_REPROGMEMM_ENABLED        STD_ON
#define BLU_FLASHWRAPPER_ENABLED      STD_OFF
[!ELSEIF "node:exists(as:modconf('Flash'))"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
#define BLU_FLASHWRAPPER_ENABLED      STD_ON
#define BLU_REPROGMEMM_ENABLED        STD_OFF
[!ENDIF!]

[!IF "(General/BLU_Communication_Support = 'true')"!]
#define BLU_COMMUNICATION_SUPPORT STD_ON
[!ELSE!]
#define BLU_COMMUNICATION_SUPPORT STD_OFF
[!ENDIF!]

[!IF "(General/Eth_Protocol_Supported = 'true')"!]
#define ETH_PROTOCOL_SUPPORT STD_ON
[!ELSE!]
#define ETH_PROTOCOL_SUPPORT STD_OFF
[!ENDIF!]
#endif /* BLUpdater_CFG_H */
