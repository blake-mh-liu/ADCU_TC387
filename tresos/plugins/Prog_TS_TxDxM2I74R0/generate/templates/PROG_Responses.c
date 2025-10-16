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
/*%%   _____________________________   %%  \file PROG_Responses.c                */
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
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
[!AUTOSPACING!]
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
/** \brief API that allows to change the response sent in the case of success of Erase
 **
 ** Callback is called: when Erase succeeded and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 **
 **/
void PROG_Custom_EraseRoutine_Succeed(u8 * Data, PduLengthType * DataLength)
{
    /* No change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
}

/** \brief API that allows to change the response sent in the case of failure of Erase
 **
 ** Callback is called: when Erase failed and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response and UDS status
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 ** \param[in,out] eUdsStatus The result of the Erase.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 **/
void PROG_Custom_EraseRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
    OSC_PARAM_UNUSED(eUdsStatus);
}

/** \brief API that allows to change the response sent in the case of success of Check Memory
 **
 ** Callback is called: when Check Memory succeeded and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 **
 **/
void PROG_Custom_CheckMemoryRoutine_Succeed(u8 * Data, PduLengthType * DataLength)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
}

/** \brief API that allows to change the response sent in the case of failure of Check Memory
 **
 ** Callback is called: when Check Memory failed and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response and UDS status
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 ** \param[in,out] eUdsStatus The result of the Check Memory.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 **/
void PROG_Custom_CheckMemoryRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
    OSC_PARAM_UNUSED(eUdsStatus);
}

/** \brief API that allows to change the response sent in the case of success of Check Precondition
 **
 ** Callback is called: when Check Precondition succeeded and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 **
 **/
[!IF "General/Check_Programming_PreConditions = 'true'"!]
void PROG_Custom_PreCondCheckRoutine_Succeed(u8 * Data, PduLengthType * DataLength)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
}

/** \brief API that allows to change the response sent in the case of failure of Check Precondition
 **
 ** Callback is called: when Check Precondition failed and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response and UDS status
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 ** \param[in,out] eUdsStatus The result of the Check Precondition.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 **/
void PROG_Custom_PreCondCheckRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
    OSC_PARAM_UNUSED(eUdsStatus);
}
[!ENDIF!]

/** \brief API that allows to change the response sent in the case of success of Check Prog Dependency
 **
 ** Callback is called: when Check Prog Dependency succeeded and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 **
 **/
void PROG_Custom_CheckProgDepRoutine_Succeed(u8 * Data, PduLengthType * DataLength)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
}

/** \brief API that allows to change the response sent in the case of failure of Check Prog Dependency
 **
 ** Callback is called: when Check Prog Dependency failed and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response and UDS status
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 ** \param[in,out] eUdsStatus The result of the Check Prog Dependency.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 **/
void PROG_Custom_CheckProgDepRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
    OSC_PARAM_UNUSED(eUdsStatus);
}

[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG'))"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/** \brief API that allows to change the response sent in the case of success of Check Precondition
 **
 ** Callback is called: when Check Precondition succeeded and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 **
 **/
void PROG_Custom_PreCondCheckRoutine_Succeed(u8 * Data, PduLengthType * DataLength)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
}

/** \brief API that allows to change the response sent in the case of failure of Check Precondition
 **
 ** Callback is called: when Check Precondition failed and before sending the response
 **
 ** Callback shall implement: The expected Data to send, the length of the response and UDS status
 **
 ** \param[in,out] Data received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in,out] DataLength received data length
 ** \param[in,out] eUdsStatus The result of the Check Precondition.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 **/
void PROG_Custom_PreCondCheckRoutine_Failed(u8 * Data, PduLengthType * DataLength, tUdsStatus * eUdsStatus)
{
    /* No Change */
    OSC_PARAM_UNUSED(Data);
    OSC_PARAM_UNUSED(DataLength);
    OSC_PARAM_UNUSED(eUdsStatus);
}
[!ENDIF!]
[!ENDIF!]