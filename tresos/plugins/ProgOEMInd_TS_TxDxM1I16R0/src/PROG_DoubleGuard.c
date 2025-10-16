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
/*%%   _____________________________   %%  \file PROG_DoubleGuard.c              */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.16.0 BL3 */
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
/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.40
 * Do not create incompatible declarations of the same function or object
 *
 * Reason:
 * Two functions are declared to  provide two different functionalities though.
 * they are almost similar in declarations they wont be functional impact.
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include "PROG_Guard.h"

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
tProgStatus PROG_Custom_Guard_RD_Check_FingerPrint(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_FingerPrint_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_RD_Check_CompareKey(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_CompareKey_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_RD_Check_RD(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_RD_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_RD_Check_CheckMemory(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_CheckMemory_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_RD_Check_CheckProgDep(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_CheckProgDep_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_RD_Check_TD(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_TD_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_RD_Check_EraseMemory(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_RD_Check())
    {
        if (PROG_Custom_Guard_EraseMemory_RD()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_Erase_Check_Fingerprint(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_FingerPrint_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_Erase_Check_EraseMemory(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_EraseMemory_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_Erase_Check_CheckProgDep(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_CheckProgDep_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_Erase_Check_CompareKey(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_CompareKey_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_Erase_Check_ProgSession(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_ProgSession_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}

tProgStatus PROG_Custom_Guard_Erase_Check_TD(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_TD_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_Erase_Check_RD(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        if (PROG_Custom_Guard_RD_EraseMemory()==PROG_E_OK)
        {
            eStatus = PROG_E_OK;
        }
        else
        {
            eStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_Erase_Check_RTE(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        eStatus = PROG_E_OK;
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
/* Deviation CERTC-1 */
tProgStatus PROG_Custom_Guard_Erase_Check_CheckMemory(void)
{
    tProgStatus eStatus;
    if (PROG_E_OK==PROG_Erase_Guard())
    {
        eStatus = PROG_E_OK;
    }
    else
    {
        eStatus = PROG_E_NOT_OK;
    }
    return eStatus;
}
