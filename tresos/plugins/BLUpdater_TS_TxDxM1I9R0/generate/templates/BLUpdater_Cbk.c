/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater layer                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Cbk.c                 */
/*%%  |                             |  %%  \brief BLUpdater plugin file          */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.9.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files                                                                */

#include "EB_Prj.h"
/*                                                                               */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
/** \brief Callback to set validity marker for New Bootloader
 **
 ** The validity of the New Bootloader shall be saved here
 **
 ** \param[in] eNewBootValidity status to write
 **
 ** \return Result application validation
 ** \retval BLU_TRUE finish successfully
 ** \retval BLU_FALSE Error happened during treatment (ErrorCode shall be filled in this case)
 **/
tBLUBoolean BLU_CustomSetValidityNewBootloader(tBLUBoolean eNewBootValidity)
{
    OSC_PARAM_UNUSED(eNewBootValidity);
    return BLU_TRUE;
}
/** \brief Callback to set validity marker pf the Bootloader Updater
 **
 ** The validity of the Bootloader Updater shall be saved here
 **
 ** \param[in] eBLUValidity status to write
 **
 ** \return Result application invalidation
 ** \retval BLU_TRUE Treatment finish successfully
 ** \retval BLU_FALSE Error happened during treatment 
 **/
tBLUBoolean BLU_CustomSetValidityBLUpdater(tBLUBoolean eBLUValidity)
{
    OSC_PARAM_UNUSED(eBLUValidity);
    return BLU_TRUE;
}
/** \brief Callback to get Pdu ID
 ** Get the Rx Pdu Identifier on which the response after reset shall be sent
 **
 ** \param[out] pubRxPduId Rx Pdu Identifier pointer
 **
 **/
void BLU_CustomGetPduID(u16* pubRxPduId)
{
    OSC_PARAM_UNUSED(pubRxPduId);
}
/** \brief Callback to trigger the Watchdog
 ** Watchdog can be triggered directly by using this callback.
 **
 **/
void BLU_CustomTriggerWatchdog(void)
{

}

/** \brief Initialization of modules of communication stack
 **
 **/
void BLU_Custom_Com_Init(void)
{

}

[!IF "(Security/SecureBoot/SECURE_BOOT = 'true')"!]
/** \brief Callback to update the checksum of the Bootloader
 **
 ** \param[in] ulBootStartAddress : Start of the Boot to be verified by the SecureBoot
 ** \param[in] ulBootSize : Size of the Boot to be verified by the SecureBoot
 ** 
 ** \retval BLU_E_OK Treatment finish successfully
 ** \retval BLU_E_NOT_OK Error happened during treatment 
 ** \retval BLU_E_BUSY Treatment in progress
 **/
tBLUStatus BLU_CustomBootChecksumUpdate(u32 ulBootStartAddress, u32 ulBootSize)
{
    OSC_PARAM_UNUSED(ulBootStartAddress);
    OSC_PARAM_UNUSED(ulBootSize);
    return BLU_E_OK;
}
[!ENDIF!]