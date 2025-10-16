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
/*%%   _____________________________   %%  \file PROG_Erase.c                    */
/*%%  |                             |  %%  \brief PROG Erase feature             */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

#if (PROG_PRELIM_ERASING_ENABLE == STD_ON)
/*-----------------------{PROG_PrelimErasing}------------------------------------*/
tProgStatus PROG_PrelimErasing(tSegmentType * pstSegment)
{
    tProgStatus eProgStatus;
    u8 ubLoopIndex;

    eProgStatus = PROG_E_OK;

    for(ubLoopIndex = 0U; (ubLoopIndex < (PROG_BLOCK_NB - 1U)) && (PROG_E_OK == eProgStatus); ubLoopIndex++)
    {
        eProgStatus = PROG_CheckProgrammingCounter(ubLoopIndex);
    }

    if(PROG_E_OK == eProgStatus)
    {
        /* Check Address */
        (void) PROG_GetSegmentByBlockId((PROG_BLOCK_NB - 1U), &pstSegment->ubSegmentId, &pstSegment->ubSegmentNbr);

        /* Construct Segment Structure (Address) */
        pstSegment->ulStartAddress = stConfigSegment[pstSegment->ubSegmentId].ulEraseStartAddress;
        pstSegment->ubLogicalBlockId = PROG_MAX_BLOCK_ID;

        /* Construct Segment Structure (Size) */
        pstSegment->ulSize = (stConfigSegment[pstSegment->ubSegmentId].ulEraseEndAddress
                            - stConfigSegment[pstSegment->ubSegmentId].ulEraseStartAddress)
                            + 1U;
    }

    return eProgStatus;
}
/*-----------------------{end PROG_PrelimErasing}--------------------------------*/
#endif
