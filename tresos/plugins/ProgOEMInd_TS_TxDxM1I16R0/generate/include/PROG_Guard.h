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
/*%%   _____________________________   %%  \file PROG_Guard.h                    */
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

#ifndef PROG_GUARD_H
#define PROG_GUARD_H

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

extern tProgStatus PROG_Custom_Guard_RD_Check_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_RD_Check_CompareKey(void);

extern tProgStatus PROG_Custom_Guard_RD_Check_RD(void);

extern tProgStatus PROG_Custom_Guard_RD_Check_CheckMemory(void);

extern tProgStatus PROG_Custom_Guard_RD_Check_TD(void);

extern tProgStatus PROG_Custom_Guard_RD_Check_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_Fingerprint(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_CheckMemory_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_CheckProgDep_CompareKey(void);

extern tProgStatus PROG_Custom_Guard_CheckProgDep_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_CheckProgDep_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_CheckProgDep_CheckMemory(void);

extern tProgStatus PROG_Custom_Guard_CheckProgDep_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_CompareKey_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_CompareKey_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_CompareKey_RD(void);

extern tProgStatus PROG_Custom_Guard_CompareKey_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_EraseMemory_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_EraseMemory_RD(void);

extern tProgStatus PROG_Custom_Guard_EraseMemory_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_EraseMemory_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_RD_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_RD_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_RD_RD(void);

extern tProgStatus PROG_Custom_Guard_RD_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_RTE_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_RTE_CheckMemory(void);

extern tProgStatus PROG_Custom_Guard_RTE_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_TD_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_TD_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_TD_RD(void);

extern tProgStatus PROG_Custom_Guard_FingerPrint_RD(void);

extern tProgStatus PROG_Custom_Guard_FingerPrint_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_FingerPrint_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_TD_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_CheckMemory_RD(void);

extern tProgStatus PROG_Custom_Guard_CheckProgDep_RD(void);

extern tProgStatus PROG_Custom_Guard_ProgSession_EraseMemory(void);

extern tProgStatus PROG_Custom_Guard_ProgSession_FingerPrint(void);

extern tProgStatus PROG_Custom_Guard_FingerPrint_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_RD_Check_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_CheckProgDep(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_CompareKey(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_ProgSession(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_TD(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_RD(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_RTE(void);

extern tProgStatus PROG_Custom_Guard_Erase_Check_CheckMemory(void);

#endif /* PROG_GUARD_H */
