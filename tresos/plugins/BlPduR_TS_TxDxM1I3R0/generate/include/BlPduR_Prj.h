/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                     BlPduR                                       */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Prj.h                       */
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
[!IF "node:exists(as:modconf('Lin')) and as:modconf('Lin')/LinGeneral/LinNodeType != 'Slave'"!]
    [!ERROR "BlPduR module doesn't support Lin Master"!]
[!ENDIF!]

[!CODE!]
#ifndef BLPDUR_PRJ_H
#define BLPDUR_PRJ_H

/* Stack type is bootloader */
#define BOOTLOADER

#include "ncs.h"
#include "ComStack_Types.h"

[!IF "node:exists(as:modconf('PduR'))"!]
#include <PduR.h>
#include "PduR_BlPduR.h"
[!ENDIF!]

/* TYPES */
[!IF "node:exists(as:modconf('Can'))"!]
    [!IF "as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true'"!]
/* - Header Files: CAN                                                           */
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "CanSM.h"
#include <CanSM_ComM.h>
    [!ENDIF!]
[!ENDIF!]
[!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ETH                                                           */
#include "Eth.h"
#include "EthIf.h"
#include "EthSM.h"
#include "TcpIp.h"
#include "SoAd.h"
#include "DoIP.h"
#include "EthIf_Cbk.h"
#include "EthSM_Cbk.h"
#include "SoAd_Cbk.h"
#include "TcpIp_Cbk.h"
#include "DoIP_Cbk.h"
#include "EthTrcv.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Lin'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LIN                                                           */
#include "LIN_Types.h"
#include "LIL_Types.h"
[!ENDIF!]

[!IF "node:exists(as:modconf('Ltp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LTP                                                           */
#include "LTP_Types.h"
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
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                        */
#include "ReProgMemM_Types.h"
[!ELSEIF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                        */
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
/* - Header Files: BlPduR                                                            */
#include "BlPduR_Types.h"
/* - Header Files: APP                                                           */
#include "APP_Types.h"


/* PUB */
[!IF "node:exists(as:modconf('Lin'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LIN                                                           */
#include "LIN_Pub.h"
#include "LIL_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Ltp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LTP                                                           */
#include "LTP_Pub.h"
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
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                         */
#include "ReProgMemM.h"
[!ELSEIF "node:exists(as:modconf('Flash'))"!]
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
/* - Header Files: BlPduR                                                            */
#include "BlPduR_Pub.h"
/*-------------------------------------------------------------------------------*/
/* - Header Files: APP                                                           */
#include "APP_Pub.h"
#include "APP_Boot.h"

/* CFG */
[!IF "node:exists(as:modconf('Lin'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LIN                                                           */
#include "LIN_Cfg.h"
#include "LIL_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Ltp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LTP                                                           */
#include "LTP_Cfg.h"
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
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                        */
#include "ReProgMemM_Cfg.h"
[!ELSEIF "node:exists(as:modconf('Flash'))"!]
/*------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                        */
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
/* - Header Files: BlPduR                                                            */
#include "BlPduR_Cfg.h"
/* HW */
[!IF "(node:exists(as:modconf('Flash')) and not(node:exists(as:modconf('ReProgMemM')))) "!]
/*------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                        */
#include "FLASH_Hw.h"
[!ENDIF!]

/* CBK */
[!IF "node:exists(as:modconf('Lin'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LIN                                                           */
#include "LIN_Cbk.h"
#include "LIL_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('Ltp'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: LTP                                                           */
#include "LTP_Cbk.h"
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
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                        */
#include "ReProgMemM_Interfaces.h"
[!ELSEIF "node:exists(as:modconf('Flash'))"!]
/*------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                        */
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
/* - Header Files: BlPduR                                                          */
#include "BlPduR_Cbk.h"
/* - Header Files: APP                                                           */
#include "APP_Cbk.h"

#endif      /* BLPDUR_PRJ_H */
[!ENDCODE!]