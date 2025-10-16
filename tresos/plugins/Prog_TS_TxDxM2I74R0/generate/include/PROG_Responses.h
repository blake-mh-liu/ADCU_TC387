/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Responses.h                */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
[!NOCODE!]
[!/* Activate generation of the file*/!]
[!IF "not((node:exists(as:modconf('ProgOEMInd'))) or (node:exists(as:modconf('ProgVAG'))))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

#ifndef PROG_RESPONSES_H
#define PROG_RESPONSES_H

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

[!AUTOSPACING!]
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
[!IF "node:exists(as:modconf('ProgOEMInd'))"!]

extern void PROG_Custom_EraseRoutine_Succeed(u8 * Data, PduLengthType * DataLength);

extern void PROG_Custom_EraseRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus);


extern void PROG_Custom_CheckMemoryRoutine_Succeed(u8 * Data, PduLengthType  * DataLength);

extern void PROG_Custom_CheckMemoryRoutine_Failed(u8 * Data, PduLengthType  * DataLength, tUdsStatus * eUdsStatus);

[!IF "General/Check_Programming_PreConditions = 'true'"!]
extern void PROG_Custom_PreCondCheckRoutine_Succeed(u8 * Data, PduLengthType  * DataLength);

extern void PROG_Custom_PreCondCheckRoutine_Failed(u8 * Data, PduLengthType  * DataLength, tUdsStatus * eUdsStatus);
[!ENDIF!]

extern void PROG_Custom_CheckProgDepRoutine_Succeed(u8 * Data, PduLengthType * DataLength);

extern void PROG_Custom_CheckProgDepRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus);

[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG'))"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
extern void PROG_Custom_PreCondCheckRoutine_Succeed(u8 * Data, PduLengthType * DataLength);

extern void PROG_Custom_PreCondCheckRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus);
[!ENDIF!]
[!ENDIF!]

#endif /* PROG_RESPONSES_H */
