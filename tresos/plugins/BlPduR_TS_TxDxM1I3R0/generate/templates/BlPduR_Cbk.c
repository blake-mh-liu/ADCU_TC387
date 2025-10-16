/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                           BlPduR callbacks                                    */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Cbk.c                       */
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
/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: BlPduR                                                           */
#include "BlPduR_Prj.h"
/*                                                                               */
/*********************************************************************************/

/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
/*                                                                               */
/*********************************************************************************/
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*********************************************************************************/

/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*-------------------------------------------------------------------------------*/
/* - Public Callbacks                                                            */

/*                                                                               */
/*********************************************************************************/
[!IF "node:exists(as:modconf('CanIf'))"!]
[!IF "MultipleIdentifier/MultipleIdentifierGroup = 'EXTERNAL_NOTIFICATION'"!]
/** \brief This service is at system initialization by BlPduR module to retrieve Group Id use in the ECU
 **
 ** The Group ID shall be retrieve depending on the system architecture (e.g. from NVM, from a specific I/O,..)
 ** It shall then be returned.
 **
 ** \return value of the Group ID that shall be used in by the bootloader to run
 **/
u8 BlPduR_GetGroupIdVal (void)
{
    /* Here the group ID shall be retrieve and returned */
    return 0U;
}
[!ENDIF!]
[!ENDIF!]

/** \brief Get the Rx Pdu Identifier on which the response after reset shall be sent
 **
 ** \param[out] pubRxPduId Rx Pdu Identifier pointer
 **
 **/
void BlPduR_GetRxPduId(u8* pubRxPduId)
{
    OSC_PARAM_UNUSED(pubRxPduId);
}

/** \brief Store the Rx Pdu Identifier on which the request shall be responded after reset has been received
 **
 ** \param[in] pubRxPduId Rx Pdu Identifier
 **
 **/
void BlPduR_StoreRxPduId(u8 ubRxPduId)
{
    OSC_PARAM_UNUSED(ubRxPduId);
}


/** \brief Initialization of modules of communication stack and initialization of the stored PDUID of the active connection
 **
 **/
void BlPduR_Custom_Com_Init(void)
{
#ifndef PLATFORMS_STUBS_ENABLED
    if (PLATFORMS_SW_RESET != BoardGetResetType())
    {
        /* If it is not a Software reset then initialize the stored PDU ID to invalid to start a new connection later*/
        BlPduR_StoreRxPduId(BLPDUR_INVALID_PDU);
    }
#endif
}

/** \brief Deactivate the Communication
 **
 **/
void BlPduR_Custom_Com_Deactivate(void)
{

}
