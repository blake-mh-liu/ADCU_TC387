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
/*%%   _____________________________   %%  \file EB_Cfg.h                        */
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
[!/* Verify <layer>_MANAGE_PERIOD is multiple of EB_MANAGE_PERIOD */!]
[!/* Else an error is generated*/!]

[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!/* COM */!]
    [!IF "node:exists(as:modconf('Com'))"!]
        [!IF " (num:i(as:modconf('Com')/General/MANAGE_PERIOD) mod num:i(as:modconf('EB')/General/MANAGE_PERIOD)) != 0"!]
            [!ERROR "COM_MANAGE_PERIOD is not multiple of EB_MANAGE_PERIOD"!]
        [!ENDIF!]
    [!ENDIF!]

    [!/* TP */!]
    [!IF "node:exists(as:modconf('Tp'))"!]
        [!IF " (num:i(as:modconf('Tp')/TpGeneral/TpManagePeriod) mod num:i(as:modconf('EB')/General/MANAGE_PERIOD)) != 0"!]
            [!ERROR "TpManagePeriod is not multiple of EB_MANAGE_PERIOD"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]

[!/* PROG */!]
[!IF "node:exists(as:modconf('Prog'))"!]
    [!IF " (num:i(as:modconf('Prog')/General/MANAGE_PERIOD) mod num:i(as:modconf('EB')/General/MANAGE_PERIOD)) != 0"!]
        [!ERROR "PROG_MANAGE_PERIOD is not multiple of EB_MANAGE_PERIOD"!]
    [!ENDIF!]
[!ENDIF!]


[!/* UDS */!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!IF " (num:i(as:modconf('Uds')/General/UDS_MANAGE_PERIOD) mod num:i(as:modconf('EB')/General/MANAGE_PERIOD)) != 0"!]
        [!ERROR "UDS_MANAGE_PERIOD is not multiple of EB_MANAGE_PERIOD"!]
    [!ENDIF!]
[!ENDIF!]

[!/* SA */!]
[!IF "node:exists(as:modconf('SA'))"!]
    [!IF " (num:i(as:modconf('SA')/General/MANAGE_PERIOD) mod num:i(as:modconf('EB')/General/MANAGE_PERIOD)) != 0"!]
        [!ERROR "SA_MANAGE_PERIOD is not multiple of EB_MANAGE_PERIOD"!]
    [!ENDIF!]
[!ENDIF!]
[!/* End of verify <layer>_MANAGE_PERIOD is multiple of EB_MANAGE_PERIOD */!]
[!ENDNOCODE!]
[!CODE!]
#ifndef EB_CFG_H
#define EB_CFG_H

/* EB Manage period */
#define EB_MANAGE_PERIOD               [!"num:i(General/MANAGE_PERIOD)"!]U

/* Number of Physical TP message */
[!/* For Osek Stack */!]
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
#define EB_TP_PHYS_MESS_NBR [!"num:i(count(as:modconf('Tp')/Message/*[(Adressing_Mode = 'Physical')]))"!]U
[!/* For Autosar Stack */!]
[!ELSE!]
#define EB_TP_PHYS_MESS_NBR [!"num:i(count(as:modconf('EB')/Communication/TxPdus/*))"!]U
[!ENDIF!]

/* TP messages index definition (TP_Cfg.h)[!AUTOSPACING!] */
[!VAR "MSG_IDX" = "0"!][!AUTOSPACING!]
[!LOOP "Communication/TxPdus/*"!][!AUTOSPACING!]
    [!CR!]#define TP_MSG_IDX_[!"name(.)"!][!WS "4"!][!"num:i($MSG_IDX)"!]U[!AUTOSPACING!]
    [!VAR "MSG_IDX" = "$MSG_IDX + 1"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

#endif      /* EB_CFG_H */
[!ENDCODE!]
