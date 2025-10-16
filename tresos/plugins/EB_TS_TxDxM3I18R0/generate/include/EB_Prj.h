/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                     EB                                        */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_Prj.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.18.0 BL3                */
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
[!VAR "FullDuplexUses" = "0"!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
         [!IF "as:modconf('Tp')/Message/*[position()=$MsgNB]/Mode = 'Full_Duplex'"!]
            [!VAR "FullDuplexUses" = "1"!]
        [!ENDIF!]
    [!ENDFOR!]
[!ENDIF!]
[!ENDNOCODE!]

[!CODE!]
#ifndef EB_PRJ_H
#define EB_PRJ_H

/* Stack type is bootloader */
#define BOOTLOADER

#include "ncs.h"

/* TYPES */
[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN'"!]
    [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
        [!IF "node:exists(as:modconf('Can'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
#include "CAN_Types.h"
        [!ENDIF!]
    [!ENDIF!]
    [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
        [!IF "node:exists(as:modconf('Can'))"!]
#include "CAN.h"
        [!ENDIF!]
        [!IF "node:exists(as:modconf('CanIf'))"!]
#include "CANIf.h"
        [!ENDIF!]
        [!IF "node:exists(as:modconf('CanTp'))"!]
#include "CANTp.h"
        [!ENDIF!]
        [!IF "node:exists(as:modconf('CanSM'))"!]
#include "CanSM.h"
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]
[!IF "as:modconf('EB')/General/Protocol_Type = 'FLEXRAY'"!]
    [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLEXRAY                                                       */
        [!IF "node:exists(as:modconf('Fr'))"!]
#include "Fr.h"
        [!ENDIF!]
        [!IF "node:exists(as:modconf('FrIf'))"!]
#include "FrIf.h"
        [!ENDIF!]
        [!IF "node:exists(as:modconf('FrTp'))"!]
#include "FrTp.h"
        [!ENDIF!]
        [!IF "node:exists(as:modconf('FrSM'))"!]
#include "FrSM.h"
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]
[!IF "as:modconf('EB')/General/Protocol_Type = 'ETHERNET' and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ETH                                                           */
    [!IF "node:exists(as:modconf('EthTrcv'))"!]
#include "EthTrcv.h"
#include "EthTrcv_1_T01_PBcfg.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('Eth'))"!]
#include "Eth.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('EthIf'))"!]
#include "EthIf.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('EthSM'))"!]
#include "EthSM.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('TcpIp'))"!]
#include "TcpIp.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('SoAd'))"!]
#include "SoAd.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('DoIP'))"!]
#include "DoIP.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Com'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: COM                                                           */
#include "COM_Types.h"
    [!IF "as:modconf('Com')/General/IL_included  = 'true'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: IL                                                            */
#include "IL_Types.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: TP                                                            */
#include "TP_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Prog'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: PROG                                                          */
#include "PROG_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('BM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */
#include "BM_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('FlashExt'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH_Ext                                                     */
#include "FLASH_Ext_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: SA                                                            */
#include "SA_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: DIAG                                                          */
#include "UDS_Types.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Types.h"
[!IF "$FullDuplexUses = 1"!]
#include "EB_FullDuplex.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: APP                                                           */
#include "APP_Types.h"
[!IF "node:exists(as:modconf('PduR'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: PduR                                                          */
#include "PduR.h"
#include "PduR_EB.h"
[!ENDIF!]


/* PUB */
[!IF "node:exists(as:modconf('Can'))"!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
#include "CAN_Pub.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Com'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: COM                                                           */
#include "COM_Pub.h"
    [!IF "as:modconf('Com')/General/IL_included  = 'true'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: IL                                                            */
#include "IL_Pub.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: TP                                                            */
#include "TP_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Prog'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: PROG                                                          */
#include "PROG_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('BM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */
#include "BM_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('FlashExt'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH_Ext                                                     */
#include "FLASH_Ext_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: SA                                                            */
#include "SA_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: DIAG                                                          */
#include "UDS_Pub.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Pub.h"
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
#include "EB_Boot_PduR.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: APP                                                           */
#include "APP_Pub.h"
#include "APP_Boot.h"


/* CFG */
[!IF "node:exists(as:modconf('Can'))"!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
#include "CAN_Cfg.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Eth'))"!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'ETHERNET' and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ETH                                                           */
#include "Eth_Cfg.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Com'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: COM                                                           */
#include "COM_Cfg.h"
    [!IF "as:modconf('Com')/General/IL_included  = 'true'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: IL                                                            */
#include "IL_Cfg.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: TP                                                            */
#include "TP_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Prog'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: PROG                                                          */
#include "PROG_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('BM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */
#include "BM_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('FlashExt'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH_Ext                                                     */
#include "FLASH_Ext_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: SA                                                            */
#include "SA_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: DIAG                                                          */
#include "UDS_Cfg.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Cfg.h"

/* HW */
[!IF "node:exists(as:modconf('Can'))"!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
#include "CAN_Hw.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Hw.h"
[!ENDIF!]


/* CBK */
[!IF "node:exists(as:modconf('Can'))"!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
#include "CAN_Cbk.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "as:modconf('EB')/General/Protocol_Type = 'ETHERNET' and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ETH                                                           */
    [!IF "node:exists(as:modconf('EthIf'))"!]
#include "EthIf_Cbk.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('EthSM'))"!]
#include "EthSM_Cbk.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('SoAd'))"!]
#include "SoAd_Cbk.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('TcpIp'))"!]
#include "TcpIp_Cbk.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Com'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: COM                                                           */
#include "COM_Cbk.h"
    [!IF "as:modconf('Com')/General/IL_included  = 'true'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: IL                                                            */
#include "IL_Cbk.h"
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Om'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: OM                                                            */
#include "OM_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: TP                                                            */
#include "TP_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Prog'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: PROG                                                          */
#include "PROG_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('BM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */
#include "BM_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('FlashExt'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH_Ext                                                     */
#include "FLASH_Ext_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: SA                                                            */
#include "SA_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: DIAG                                                          */
#include "UDS_Cbk.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Cbk.h"
/*-------------------------------------------------------------------------------*/
/* - Header Files: APP                                                           */
#include "APP_Cbk.h"

#endif      /* EB_PRJ_H */
[!ENDCODE!]