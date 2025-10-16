/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                     BLUpdater                                 */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Prj.h                 */
/*%%  |                             |  %%                                        */
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
[!AUTOSPACING!]

[!CODE!]
#ifndef BLUPDATER_PRJ_H
#define BLUPDATER_PRJ_H

/* Stack type is bootloader */

#include "ncs.h"
#include "ComStack_Types.h"

#include "APP_Types.h"

[!IF "node:exists(as:modconf('PduR'))"!]
#include <PduR.h>
#include "PduR_BLUpdater.h"
[!ENDIF!]

/* TYPES */
[!IF "as:modconf('BLUpdater')/General/Can_Protocol_Supported = 'true'"!]
    [!IF "node:exists(as:modconf('Can'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN                                                           */
#include "Can.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('CanIf'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN Interface                                                 */
#include "CanIf.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('CanSM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: CAN State Manager                                             */
#include "CanSM.h"
#include <CanSM_ComM.h>
    [!ENDIF!]
[!ENDIF!]
[!IF "as:modconf('BLUpdater')/General/Eth_Protocol_Supported = 'true'"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ETH                                                           */
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
    [!IF "node:exists(as:modconf('DoIP'))"!]
#include "DoIP_Cbk.h"
    [!ENDIF!]
    [!IF "node:exists(as:modconf('EthTrcv'))"!]
#include "EthTrcv.h"
    [!ENDIF!]
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
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Types.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                         */
#include "ReProgMemM_Types.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BLUpdater                                                     */
#include "BLUpdater_Types.h"



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
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Pub.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                         */
#include "ReProgMemM.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BLUpdater                                                     */
#include "BLUpdater_Pub.h"
/*-------------------------------------------------------------------------------*/


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
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Cfg.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                         */
#include "ReProgMemM_Cfg.h"
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: BLUpdater                                                     */
#include "BLUpdater_Cfg.h"


/* HW */
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
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
[!IF "node:exists(as:modconf('Flash'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: FLASH                                                         */
#include "FLASH_Cbk.h"
[!ENDIF!]
[!IF "node:exists(as:modconf('ReProgMemM'))"!]
/*-------------------------------------------------------------------------------*/
/* - Header Files: ReProgMemM                                                         */
#include "ReProgMemM_Interfaces.h"
[!ENDIF!]
/* - Header Files: BLUpdater                                                     */
#include "BLUpdater_Cbk.h"

#endif      /* BLUPDATER_PRJ_H */
[!ENDCODE!]