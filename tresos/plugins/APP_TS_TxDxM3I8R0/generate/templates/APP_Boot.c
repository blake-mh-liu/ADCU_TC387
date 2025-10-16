/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                APP BOOT VCC                                   */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Boot.c                     */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.8.0 BL3  */
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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.7 (advisory)
 *   A pointer parameter in a function prototype should be declared as pointer to const
 *   if the pointer is not used to modify the addressed object.
 *
 *   Reason:
 *   This pointer will is generated from a common template and can't be set to const.
 *
 *  MISRA-2) Deviated Rule: 11.3 (advisory)
 *   A cast should not be performed between a pointer type and an integral type.
 *
 *   Reason:
 *   This cast is unavoidable since we addressed a defined software memory area
 */
/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
#include "EB_Prj.h"
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

/***************************** PRIVATE DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

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
/* - Public Functions                                                            */

/*-------------------------------------------------------------------------------*/


[!IF "node:exists(as:modconf('ProgVCC'))"!]
[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'"!]
/*----------------------------{APP_MemStartErasing}-----------------------------*/

tProgStatus APP_MemStartErasing(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode)
{
    tProgStatus eStatus = PROG_E_OK;

    DBG_APP_MEMSTARTERASING_ENTRY(ulStartAddress,ulEraseLength,ErrorCode);

    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulEraseLength);
    OSC_PARAM_UNUSED(ErrorCode);

    DBG_APP_MEMSTARTERASING_EXIT(eStatus);

    return eStatus;
}
/*----------------------------{end APP_MemStartErasing}-------------------------*/
[!ENDIF!]
[!ENDIF!]
