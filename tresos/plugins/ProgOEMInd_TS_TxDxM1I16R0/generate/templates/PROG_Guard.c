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
/*%%   _____________________________   %%  \file PROG_Guard.c                      */
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

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include "PROG_Guard.h"

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
tProgStatus PROG_Custom_Guard_CheckMemory_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_CompareKey(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_CheckMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RD_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RD_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RD_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RD_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RTE_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RTE_CheckMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RTE_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_TD_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_TD_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_TD_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_FingerPrint_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_FingerPrint_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_FingerPrint_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_TD_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckMemory_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_ProgSession_EraseMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_ProgSession_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}
tProgStatus PROG_Custom_Guard_FingerPrint_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}
