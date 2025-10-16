/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               UDS configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Cfg.c                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.22.0 BL3 */
/*%%  |   &       &    &            |  %%  Variant: ISO                  */
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




/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: UDS                                                           */
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
[!AUTOSPACING!]
[!LOOP "Service/*"!][!AUTOSPACING!]
[!/* We check if each service is defined at least in one session */!][!AUTOSPACING!]
    [!IF "(Default = 'false' and Programming = 'false' and Extended = 'false' and Supplier = 'false' and Other_1 = 'false' and Other_2 = 'false' and Other_3 = 'false' and Other_4 = 'false')"!][!AUTOSPACING!]
        [!ERROR!]The service "[!"name(.)"!]" is not defined in any session.[!ENDERROR!][!AUTOSPACING!]
    [!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!AUTOSPACING!]
[!LOOP "Service_DID/*"!][!AUTOSPACING!]
[!/* We check if each DID is defined at least in one session */!][!AUTOSPACING!]
    [!IF "(Default = 'false' and Programming = 'false' and Extended = 'false' and Supplier = 'false'and Other_1 = 'false' and Other_2 = 'false' and Other_3 = 'false' and Other_4 = 'false')"!][!AUTOSPACING!]
        [!ERROR!]The DID "[!"name(.)"!]" is not defined in any session.[!ENDERROR!][!AUTOSPACING!]
    [!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!AUTOSPACING!]
[!LOOP "Service_LID/*"!][!AUTOSPACING!]
[!/* We check if each LID is defined at least in one session */!][!AUTOSPACING!]
    [!IF "(Default = 'false' and Programming = 'false' and Extended = 'false')"!][!AUTOSPACING!]
        [!ERROR!]The LID "[!"name(.)"!]" is not defined in any session.[!ENDERROR!][!AUTOSPACING!]
    [!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!AUTOSPACING!]
[!LOOP "Routine_Control/*"!][!AUTOSPACING!]
[!/* We check if each routine control is defined at least in one session */!][!AUTOSPACING!]
    [!IF "(Default = 'false' and Programming = 'false' and Extended = 'false' and Other_1 = 'false' and Other_2 = 'false' and Other_3 = 'false' and Other_4 = 'false')"!][!AUTOSPACING!]
            [!IF "(Supplier = 'false')"!][!AUTOSPACING!]
                [!ERROR!]The routine control "[!"name(.)"!]" is not defined in any session.[!ENDERROR!][!AUTOSPACING!]
            [!ENDIF!][!AUTOSPACING!]
    [!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!AUTOSPACING!]

[!/* We check if each service OBD is defined only one time */!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "Service_OBD/*"!][!AUTOSPACING!]
    [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
    [!VAR "TMP_SRV" = "Service"!][!AUTOSPACING!]
    [!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
    [!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
    [!LOOP "../../Service_OBD/*"!][!AUTOSPACING!]
        [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
        [!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
            [!IF "Service = $TMP_SRV"!][!AUTOSPACING!]
            [!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
            [!ENDIF!][!AUTOSPACING!]
        [!ENDIF!][!AUTOSPACING!]
    [!ENDLOOP!]
    [!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
        [!ERROR!][!"Service"!] is defined more than one time[!ENDERROR!][!AUTOSPACING!]
    [!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!AUTOSPACING!]

/***************************** PRIVATE DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
[!/* Macro used to generate code for Cfg1 */!][!AUTOSPACING!]
[!MACRO "Config1_generation"!][!AUTOSPACING!]
[!VAR "TMP_SESSIONFIELD" = "0"!][!AUTOSPACING!]
[!WS "4"!]{UDS_SRV_[!"Service"!], [!AUTOSPACING!]
[!IF "Service = 'RTE' or Service = 'TD' or Service = 'RU' or Service = 'RD' or Service = 'RMBA' or Service = 'WMBA' or Service = 'CDTCI'"!]0x00U[!ELSE!][!"num:inttohex(SubService,2)"!]U[!ENDIF!], [!AUTOSPACING!]
[!/* For each session, if it exists, its bit value is added to session field */!][!AUTOSPACING!]
[!IF "Default"!][!VAR "TMP_SESSIONFIELD" = "1"!][!ENDIF!][!AUTOSPACING!]
[!IF "Programming"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 2"!][!ENDIF!][!AUTOSPACING!]
[!IF "Extended"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 4"!][!ENDIF!][!AUTOSPACING!]
[!IF "Supplier"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 8"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_1"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 16"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_2"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 32"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_3"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 64"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_4"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 128"!][!ENDIF!][!AUTOSPACING!][!"num:inttohex($TMP_SESSIONFIELD)"!]U, [!AUTOSPACING!]
[!"Length"!]U, [!AUTOSPACING!]
[!"SecurityLevel"!]U, [!AUTOSPACING!]
[!IF "Mode = 'Physical'"!]UDS_ADDR_PHYSICAL[!ELSEIF "Mode = 'Functional'"!]UDS_ADDR_FUNCTIONAL[!ELSE!]UDS_ADDR_PHYSICAL_FUNCTIONAL[!ENDIF!], [!AUTOSPACING!]
[!IF "Callback = ''"!]NULL[!ELSE!]&[!"Callback"!][!ENDIF!]},[!AUTOSPACING!]
[!WS "4"!]/* [!AUTOSPACING!]
[!VAR "TMP_FIRSTMASK" = "0"!][!AUTOSPACING!]
[!/* If Default exists, the name of the mask is written and a flag is set*/!][!AUTOSPACING!]
[!IF "Default"!]UDS_SESSION_DEFAULT_MASK[!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!][!AUTOSPACING!]
[!/* Then each following line does the same code: If the session in the current configuration exists and if the flag is set, this code is written: */!][!AUTOSPACING!]
[!/* OR MASK_NAME */!][!AUTOSPACING!]
[!/* Else if the session exists but the flag is not set, this code is written  */!][!AUTOSPACING!]
[!/* MASK_NAME */!][!AUTOSPACING!]
[!IF "Programming"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_PROGRAMMING_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Extended"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_EXTENDED_DIAG_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Supplier"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_SUPPLIER_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_1"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_01_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_2"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_02_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_3"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_03_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_4"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_04_MASK[!ENDIF!][!AUTOSPACING!]
 */[!AUTOSPACING!][!CR!]
[!ENDMACRO!][!AUTOSPACING!]
[!AUTOSPACING!]
[!/* Macro used to check the no redundancy SubService Section */!][!AUTOSPACING!]
[!MACRO "Check_SubService", "Service_info"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!VAR "TMP_SUBSERVICE" = "SubService"!][!AUTOSPACING!]
[!LOOP "../../Service/*[Service=$Service_info]"!][!AUTOSPACING!]
[!IF "SubService = $TMP_SUBSERVICE"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ERROR!][!AUTOSPACING!]
SubService [!"num:inttohex(SubService)"!] is defined more than once for [!"$Service_info"!]
[!ENDERROR!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!ENDMACRO!][!AUTOSPACING!]

[!AUTOSPACING!]
[!/* Macro used to generate code for Cfg2 */!][!AUTOSPACING!]
[!MACRO "Config2_generation"!][!AUTOSPACING!]
[!VAR "TMP_SESSIONFIELD" = "0"!][!AUTOSPACING!]
[!WS "4"!]{UDS_SRV_[!"Service"!], [!"num:inttohex(DID,4)"!]U, [!AUTOSPACING!]
[!/* For each session, if it exists, its bit value is added to session field */!][!AUTOSPACING!]
[!IF "Default"!][!VAR "TMP_SESSIONFIELD" = "1"!][!ENDIF!][!AUTOSPACING!]
[!IF "Programming"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 2"!][!ENDIF!][!AUTOSPACING!]
[!IF "Extended"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 4"!][!ENDIF!][!AUTOSPACING!]
[!IF "Supplier"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 8"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_1"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 16"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_2"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 32"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_3"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 64"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_4"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 128"!][!ENDIF!][!AUTOSPACING!][!"num:inttohex($TMP_SESSIONFIELD)"!]U, [!AUTOSPACING!]
[!"Length"!]U, [!AUTOSPACING!]
[!"SecurityLevel"!]U, [!AUTOSPACING!]
[!IF "Mode = 'Physical'"!]UDS_ADDR_PHYSICAL[!ELSEIF "Mode = 'Functional'"!]UDS_ADDR_FUNCTIONAL[!ELSE!]UDS_ADDR_PHYSICAL_FUNCTIONAL[!ENDIF!], [!AUTOSPACING!]
[!IF "Callback = ''"!]NULL[!ELSE!]&[!"Callback"!][!ENDIF!]},[!AUTOSPACING!]
[!WS "4"!]/* [!AUTOSPACING!]
[!VAR "TMP_FIRSTMASK" = "0"!][!AUTOSPACING!]
[!/* If Default exists, the name of the mask is written and a flag is set*/!][!AUTOSPACING!]
[!IF "Default"!]UDS_SESSION_DEFAULT_MASK[!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!][!AUTOSPACING!]
[!/* Then each following line does the same code: If the session in the current configuration exists and if the flag is set, this code is written: */!][!AUTOSPACING!]
[!/* OR MASK_NAME */!][!AUTOSPACING!]
[!/* Else if the session exists but the flag is not set, this code is written  */!][!AUTOSPACING!]
[!/* MASK_NAME */!][!AUTOSPACING!]
[!IF "Programming"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_PROGRAMMING_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Extended"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_EXTENDED_DIAG_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Supplier"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_SUPPLIER_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_1"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_01_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_2"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_02_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_3"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_03_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_4"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_04_MASK[!ENDIF!][!AUTOSPACING!]
 */[!AUTOSPACING!][!CR!]
[!ENDMACRO!][!AUTOSPACING!]
[!/* Macro used to check the no redundancy DID section */!][!AUTOSPACING!]
[!MACRO "Check_DID", "Service_info"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!VAR "TMP_DID" = "DID"!][!AUTOSPACING!]
[!LOOP "../../Service_DID/*[Service=$Service_info]"!][!AUTOSPACING!]
[!IF "DID = $TMP_DID"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ERROR!][!AUTOSPACING!]
DID [!"num:inttohex(DID)"!] is defined more than once for [!"$Service_info"!]
[!ENDERROR!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!ENDMACRO!][!AUTOSPACING!]
[!AUTOSPACING!]
[!/* Macro used to generate code for Cfg3 (Routine Control) */!][!AUTOSPACING!]
[!MACRO "Config3_generation"!][!AUTOSPACING!]
[!VAR "TMP_SESSIONFIELD" = "0"!][!AUTOSPACING!]
[!WS "4"!]{UDS_SRV_RC, [!"num:inttohex(SubService,2)"!]U, [!AUTOSPACING!]
[!"num:inttohex(Routine_Identifier,4)"!]U, [!AUTOSPACING!]
[!/* For each session, if it exists, its bit value is added to session field */!][!AUTOSPACING!]
[!IF "Default"!][!VAR "TMP_SESSIONFIELD" = "1"!][!ENDIF!][!AUTOSPACING!]
[!IF "Programming"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 2"!][!ENDIF!][!AUTOSPACING!]
[!IF "Extended"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 4"!][!ENDIF!][!AUTOSPACING!]
[!IF "Supplier"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 8"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_1"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 16"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_2"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 32"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_3"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 64"!][!ENDIF!][!AUTOSPACING!]
[!IF "Other_4"!][!VAR "TMP_SESSIONFIELD" = "$TMP_SESSIONFIELD + 128"!][!ENDIF!][!AUTOSPACING!][!"num:inttohex($TMP_SESSIONFIELD)"!]U, [!AUTOSPACING!]
[!"Length"!]U, [!AUTOSPACING!]
[!"SecurityLevel"!]U, [!AUTOSPACING!]
[!IF "Mode = 'Physical'"!]UDS_ADDR_PHYSICAL[!ELSEIF "Mode = 'Functional'"!]UDS_ADDR_FUNCTIONAL[!ELSE!]UDS_ADDR_PHYSICAL_FUNCTIONAL[!ENDIF!], [!AUTOSPACING!]
[!IF "Callback = ''"!]NULL[!ELSE!]&[!"Callback"!][!ENDIF!]},[!AUTOSPACING!]
[!WS "4"!]/* [!AUTOSPACING!]
[!VAR "TMP_FIRSTMASK" = "0"!][!AUTOSPACING!]
[!/* If Default exists, the name of the mask is written and a flag is set*/!][!AUTOSPACING!]
[!IF "Default"!]UDS_SESSION_DEFAULT_MASK[!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!][!AUTOSPACING!]
[!/* Then each following line does the same code: If the session in the current configuration exists and if the flag is set, this code is written: */!][!AUTOSPACING!]
[!/* OR MASK_NAME */!][!AUTOSPACING!]
[!/* Else if the session exists but the flag is not set, this code is written  */!][!AUTOSPACING!]
[!/* MASK_NAME */!][!AUTOSPACING!]
[!IF "Programming"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_PROGRAMMING_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Extended"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_EXTENDED_DIAG_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Supplier"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_SUPPLIER_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_1"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_01_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_2"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_02_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_3"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_03_MASK[!ENDIF!][!AUTOSPACING!]
[!IF "Other_4"!][!AUTOSPACING!][!IF "$TMP_FIRSTMASK = 1"!] | [!ELSE!][!VAR "TMP_FIRSTMASK" = "1"!][!ENDIF!] UDS_SESSION_OTHER_04_MASK[!ENDIF!][!AUTOSPACING!]
 */[!AUTOSPACING!][!CR!]
[!ENDMACRO!][!AUTOSPACING!]
[!AUTOSPACING!]
[!/* Macro used to check the no redundancy RC section */!][!AUTOSPACING!]
[!MACRO "Check_RC", "Service_info"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!VAR "TMP_SUBSERVICE" = "SubService"!][!AUTOSPACING!]
[!LOOP "../../Routine_Control/*[Routine_Identifier=$Service_info]"!][!AUTOSPACING!]
[!IF "SubService = $TMP_SUBSERVICE"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ERROR!][!AUTOSPACING!]
SubService [!"num:inttohex(SubService)"!] is defined more than once for [!"num:inttohex($Service_info)"!]
[!ENDERROR!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!ENDMACRO!][!AUTOSPACING!]
[!AUTOSPACING!]
[!/* Macro used to check the no redundancy DID section */!][!AUTOSPACING!]
[!MACRO "Check_LID", "Service_info"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!VAR "TMP_LID" = "LID"!][!AUTOSPACING!]
[!LOOP "../../Service_LID/*[Service=$Service_info]"!][!AUTOSPACING!]
[!IF "LID = $TMP_LID"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ERROR!][!AUTOSPACING!]
DID [!"num:inttohex(LID)"!] is defined more than once for [!"$Service_info"!]
[!ENDERROR!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!ENDMACRO!][!AUTOSPACING!]
[!AUTOSPACING!]
[!/* Macro used to generate code for Cfg5 */!][!AUTOSPACING!]
[!MACRO "Config5_generation"!][!AUTOSPACING!]
[!WS "4"!]{UDS_SRV_[!"Service"!], [!AUTOSPACING!]
[!"Length"!]U, [!AUTOSPACING!]
[!IF "Mode = 'Physical'"!]UDS_ADDR_PHYSICAL[!ELSEIF "Mode = 'Functional'"!]UDS_ADDR_FUNCTIONAL[!ELSE!]UDS_ADDR_PHYSICAL_FUNCTIONAL[!ENDIF!], [!AUTOSPACING!]
[!IF "Callback = ''"!]NULL[!ELSE!]&[!"Callback"!][!ENDIF!]},[!CR!]
[!ENDMACRO!][!AUTOSPACING!]
[!AUTOSPACING!]


[!AUTOSPACING!]
[!VAR "UDS_SRV_CFG_MAX" = "num:dectoint(count(Service/*))"!]
[!IF "$UDS_SRV_CFG_MAX > '0'"!]
/* Diagnostic services configuration 1, stored in Read-Only memory */
const tUdsSrvCfg1 m_astDiagSrvCfg1[UDS_SRV_CFG1_MAX] =
{
[!LOOP "Service/*[Service='DSC']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'DSC'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='ER']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'ER'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='SA']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'SA'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='TP']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'TP'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='CDTCS']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'CDTCS'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='RMBA']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'RMBA'"*/!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when RMBA service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='WMBA']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'WMBA'"*/!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when WMBA service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='CDTCI']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'CDTCI'"*/!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when CDTCI service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='RDTCI']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'RDTCI'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='RD']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'RD'*/"!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when RD service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='RU']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'RU'"*/!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when RU service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='TD']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'TD'"*/!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when TD service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='RTE']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!/*CALL "Check_SubService", "Service_info"="'RTE'"*/!][!AUTOSPACING!]
[!/*Comment because no subservice to configure when RTE service selected*/!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='LC']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'LC'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='CC']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'CC'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service/*[Service='ARS']"!][!AUTOSPACING!]
[!CALL "Config1_generation"!][!AUTOSPACING!]
[!CALL "Check_SubService", "Service_info"="'ARS'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
};
[!ELSE!]
[!/* If no service is defined an error occurs */!][!AUTOSPACING!]
    [!ERROR!]No service defined.[!ENDERROR!][!AUTOSPACING!]
[!ENDIF!]

[!AUTOSPACING!]
[!VAR "UDS_SRV_CFG_MAX" = "num:dectoint(count(Service_DID/*))"!]
[!IF "$UDS_SRV_CFG_MAX > '0'"!]
/* Diagnostic services configuration 2, stored in Read-Only memory */
const tUdsSrvCfg2 m_astDiagSrvCfg2[UDS_SRV_CFG2_MAX] =
{
[!LOOP "Service_DID/*[Service='RDBI']"!][!AUTOSPACING!]
[!CALL "Config2_generation"!][!AUTOSPACING!]
[!CALL "Check_DID", "Service_info"="'RDBI'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service_DID/*[Service='WDBI']"!][!AUTOSPACING!]
[!CALL "Config2_generation"!][!AUTOSPACING!]
[!CALL "Check_DID", "Service_info"="'WDBI'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service_DID/*[Service='IOCBI']"!][!AUTOSPACING!]
[!CALL "Config2_generation"!][!AUTOSPACING!]
[!CALL "Check_DID", "Service_info"="'IOCBI'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
[!LOOP "Service_DID/*[Service='RSDBI']"!][!AUTOSPACING!]
[!CALL "Config2_generation"!][!AUTOSPACING!]
[!CALL "Check_DID", "Service_info"="'RSDBI'"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

};
[!ENDIF!]


[!AUTOSPACING!]
[!VAR "UDS_SRV_CFG_MAX" = "num:dectoint(count(Routine_Control/*))"!]
[!IF "$UDS_SRV_CFG_MAX > '0'"!][!AUTOSPACING!]
/* Diagnostic services configuration 3, stored in Read-Only memory */
const tUdsSrvCfg3 m_astDiagSrvCfg3[UDS_SRV_CFG3_MAX] =
{
[!LOOP "Routine_Control/*"!][!AUTOSPACING!]
[!CALL "Config3_generation"!][!AUTOSPACING!]
[!CALL "Check_RC", "Service_info"="Routine_Identifier"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
};
[!ENDIF!]


[!AUTOSPACING!]
[!VAR "UDS_SRV_CFG_MAX" = "num:dectoint(count(Service_OBD/*))"!]
[!IF "$UDS_SRV_CFG_MAX > '0'"!][!AUTOSPACING!]
/* Diagnostic services configuration 5, stored in Read-Only memory */
const tUdsSrvCfg5 m_astDiagSrvCfg5[UDS_SRV_CFG5_MAX] =
{
[!LOOP "Service_OBD/*"!][!AUTOSPACING!]
[!CALL "Config5_generation"!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]
};
[!ENDIF!]

/* Structure storing sessions and associated NRC_78 timings (P2 and P2Star) */
const tUdsSessionInfo m_stSessionInfo[UDS_CONFIGURABLE_SESSION_MAX] = 
{
  [!/*Check of the order in case customer use arrows to move up and down sessions*/!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='DEFAULT']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_DEFAULT, UDS_SESSION_PROT_DEFAULT_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='PROGRAMMING']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_PROGRAMMING, UDS_SESSION_PROT_PROGRAMMING_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='EXTENDED']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_EXTENDED_DIAG, UDS_SESSION_PROT_EXTENDED_DIAG_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='SUPPLIER']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_SUPPLIER, UDS_SESSION_PROT_SUPPLIER_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='OTHER_01']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_OTHER_01, UDS_SESSION_PROT_OTHER_01_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='OTHER_02']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_OTHER_02, UDS_SESSION_PROT_OTHER_02_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='OTHER_03']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_OTHER_03, UDS_SESSION_PROT_OTHER_03_MASK},[!ENDLOOP!][!CR!]
  [!WS "2"!][!LOOP "as:modconf('Uds')[1]/Session/*[@name='OTHER_04']"!]{[!"Identifier"!], [!"num:i(num:i(UDS_P2) div num:i(../../General/UDS_MANAGE_PERIOD))"!], [!"num:i(num:i(UDS_P2STAR) div num:i(../../General/UDS_MANAGE_PERIOD))"!], UDS_SESSION_PROT_OTHER_04, UDS_SESSION_PROT_OTHER_04_MASK}[!ENDLOOP!][!CR!]
};

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

