#ifndef PROG_ROUTINEACTIVATIONCONFIRMATIONCBK_H
#define PROG_ROUTINEACTIVATIONCONFIRMATIONCBK_H

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
/*%%   _____________________________   %%  \file PROG_RoutineActivationConfrmationCbk.h                      */
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
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
[!AUTOSPACING!]

[!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]
[!IF "node:exists(as:modconf('DoIP'))"!]
extern Std_ReturnType PROG_DoIpRoutineActivationRxConfirmationCbk(
    P2VAR(boolean, AUTOMATIC, EBSTUBS_APPL_DATA) Authentified,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationReqData,
    P2VAR(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) AuthenticationResData);
extern Std_ReturnType PROG_DoIpRoutineActivationRxConfirmationCbk_OnBoard(
    P2VAR(boolean, AUTOMATIC, EBSTUBS_APPL_DATA) Authentified,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationReqData,
    P2VAR(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) AuthenticationResData);
[!ENDIF!]
[!ENDIF!]

#endif      /* PROG_ROUTINEACTIVATIONCBK_H */
