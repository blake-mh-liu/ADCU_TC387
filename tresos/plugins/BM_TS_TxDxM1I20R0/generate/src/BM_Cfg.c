/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BM configuration                              */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cfg.c                        */
/*%%  |                             |  %%  \brief BM layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3              */
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
[!NOCODE!]
[!/* Activate generation of BM_Cfg.c file */!]
[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT ='OFF')
       or (as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager")"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

#include "EB_Prj.h"

[!IF "node:exists(as:modconf('Csm'))"!]
#include "Csm.h"
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF')
       and (node:exists(as:modconf('ProgDAG'))
       or  (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
       or  (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode = 'LogicalBlock'))"!]
  [!VAR "BLOCK_MAX"="num:dectoint(count(as:modconf('Prog')/Blocks/*))"!]
/* Table of information for each Block needed for Authenticated/Secure Boot */
const tProg_BlockSecureBootInfo stCfgBMBlockSecureBootInfo[PROG_BLOCK_NB] =
{
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
      [!VAR "START_ADDRESS"="num:inttohex(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Start_Address_Secure_Boot_Verification)"!]
      [!VAR "LENGTH"="num:inttohex(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Length_Secure_Boot_Verification)"!]
      [!VAR "BLOCK_IDENT"="num:inttohex(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
    {
      [!WS "8"!][!"$START_ADDRESS"!]U,[!WS "17"!]/* Start Address for the Secure Boot Verification */
      [!WS "8"!][!"$LENGTH"!]U,[!WS "17"!]/* Length of the block for the Secure Boot Verification */
      [!"$BLOCK_IDENT"!]U,[!WS "21"!]/* Block Identifier */
      [!WS "8"!][!IF "as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Verified_For_Secure_Boot='Block will be verified'"!]BM_TRUE,[!WS "18"!][!ELSE!]BM_FALSE,[!WS "17"!][!ENDIF!]/* Block will be verified by the Secure Boot */
      [!WS "8"!][!IF "as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Blocker_for_Software_execution='Will block software execution'"!]BM_TRUE,[!WS "18"!][!ELSE!]BM_FALSE,[!WS "17"!][!ENDIF!]/* Block will prevent the execution of software if Secure Boot verification is failed */
    },
    [!ENDFOR!]
};
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT != 'OFF')
       and (node:exists(as:modconf('ProgJLR')) or node:exists(as:modconf('ProgFord'))
       or  (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')
       or  (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'LogicalBlock'))"!]
  [!VAR "SEGMENT_MAX"="num:dectoint(count(as:modconf('Prog')/Segments/*))"!]
const tProg_BlockSecureBootInfo    stCfgBMBlockSecureBootInfo[[!"$SEGMENT_MAX"!]] =
{
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
      [!VAR "START_ADDRESS"="num:inttohex(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/SecureBoot/Start_Address_Secure_Boot_Verification)"!]
      [!VAR "LENGTH"="num:inttohex(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/SecureBoot/Length_Secure_Boot_Verification)"!]
    {
      [!WS "8"!][!"$START_ADDRESS"!]U,[!WS "17"!]/* Start Address for the Secure Boot Verification */
      [!WS "8"!][!"$LENGTH"!]U,[!WS "17"!]/* Memory size for the Secure Boot Verification */
      [!"num:inttohex($SEGMENT_IDX - 1)"!]U,[!WS "23"!]/* Segment Identifier */
      [!WS "8"!][!IF "as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/SecureBoot/Verified_For_Secure_Boot='Block will be verified'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* if TRUE Segment will be verified by the Secure Boot else this will be excluded from the secure boot verification */
      [!WS "8"!][!IF "as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/SecureBoot/Blocker_for_Software_execution='Will block software execution'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* if set to TRUE then on the failure of Secure Boot verification for this segment, execution of the software is halted*/
    },
    [!ENDFOR!]
};
[!ENDIF!]
