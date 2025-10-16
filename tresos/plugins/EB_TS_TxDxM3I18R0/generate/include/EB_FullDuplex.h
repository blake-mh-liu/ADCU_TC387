/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                EB configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_FullDuplex.h                 */
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
[!VAR "FunctionalMsgExist" = "0"!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
         [!IF "as:modconf('Tp')/Message/*[position()=$MsgNB]/Mode = 'Full_Duplex'"!]
            [!VAR "FullDuplexUses" = "1"!] 
        [!ENDIF!]
        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd')  and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
            [!VAR "FunctionalMsgExist" = "1"!] 
        [!ENDIF!]
    [!ENDFOR!]
    [!/* Activate generation of EB_Prg_Queued.c file*/!]
    [!IF "$FullDuplexUses = 0"!]
        [!IF "(as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK')"!]
            [!SKIPFILE!]
        [!ELSE!]
        [!ERROR "There shall be at least one message defined as Full_Duplex in Module TP"!]
        [!ENDIF!]
    [!ENDIF!]
[!ELSE!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!CODE!]
#ifndef EB_FULLDUPLEX_H
#define EB_FULLDUPLEX_H

extern u8 m_ubTpMsgIdxNrc78;

#define EB_STATUS_OK            0x01U
#define EB_STATUS_WAIT          0x02U
#define EB_STATUS_ERROR         0x04U
#define EB_STATUS_QUEUED        0x08U
typedef u8 tEbQueuedStatus;

#define EB_STATUS_NOT_STARTED 0x01U
#define EB_STATUS_IN_PROGRESS 0x02U
typedef u8 tEbStatus;

#define EB_CAN_BUFFERSIZE      4096U

extern void EB_InitFullDuplex(void);
extern void EB_TpRxMsgManageFullDuplex(void);

#endif      /* EB_FULLDUPLEX_H */
[!ENDCODE!]

