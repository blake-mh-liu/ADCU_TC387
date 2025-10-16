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
/*%%   _____________________________   %%  \file EB_Types.h                      */
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
[!CODE!]
[!AUTOSPACING!]
#ifndef EB_TYPES_H
#define EB_TYPES_H

[!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
[!IF "(as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true' and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR') or as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!][!AUTOSPACING!]
/* Can Identifier Type */
#define STANDARD_ID 0U
#define EXTENDED_ID 1U
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
typedef struct
{
    tTpMsgIdx   TpIdx;
    u16          TesterAddress;
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    u32         CanId;
    u8          CanIdType;
[!ENDIF!]
} tTpTesterAddrRef; 
[!ENDIF!]

#endif      /* EB_TYPES_H */
[!ENDCODE!]

