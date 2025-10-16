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
/*%%   _____________________________   %%  \file BM_Prj.h                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2020 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]

[!NOCODE!]
[!IF "not(as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager")"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!CODE!]
#ifndef BLPDUR_PRJ_H
#define BLPDUR_PRJ_H

#include "ncs.h"

#include <TSAutosar.h> /* EB specific standard types */

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
[!IF "node:exists(as:modconf('Flash'))"!]
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
/*-------------------------------------------------------------------------------*/
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
[!IF "node:exists(as:modconf('Flash'))"!]
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


/* HW */
[!IF "node:exists(as:modconf('Flash'))"!]
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
[!IF "node:exists(as:modconf('Flash'))"!]
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

#endif      /* BM_PRJ_H */
[!ENDCODE!]