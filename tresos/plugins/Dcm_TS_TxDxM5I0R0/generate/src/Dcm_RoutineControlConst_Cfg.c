/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Dcm.Dsn.File.RoutineControlConst.ConfigC,1 */

[!/*=== Verification that Routine Control signals are not overlapping ===*/!][!//
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineInfo/eb-list::*"!][!//
  [!LOOP "util:distinct(node:order(DcmDspRoutineRequestResOut/DcmDspRoutineRequestResOutSignal/eb-list::* , 'DcmDspRoutineSignalPos'))"!][!//
    [!VAR "POSN" = "DcmDspRoutineSignalPos"!][!//
    [!VAR "LENGTH" = "DcmDspRoutineSignalLength"!][!//
    [!VAR "nodeposn" = "node:pos(.) + 1"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../eb-list::*[position() != $nodeposn]"!][!//
      [!IF "(($POSN >= number(DcmDspRoutineSignalPos)) and ($POSN <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1))) or ((($POSN + $LENGTH -1) >= number(DcmDspRoutineSignalPos)) and (($POSN + $LENGTH -1) <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1)))"!][!//
        [!ERROR!][!//
          signal [!"node:name(.)"!] overlaps with signal [!"$Name"!]
          Routine Information : '[!"node:name(../../..)"!]'
          Configuration       : '[!"node:name(../..)"!]'
         [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!//
  [!LOOP "util:distinct(node:order(DcmDspRoutineRequestResIn/DcmDspRoutineRequestResInSignal/eb-list::* , 'DcmDspRoutineSignalPos'))"!][!//
    [!VAR "POSN" = "DcmDspRoutineSignalPos"!][!//
    [!VAR "LENGTH" = "DcmDspRoutineSignalLength"!][!//
    [!VAR "nodeposn" = "node:pos(.) + 1"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../eb-list::*[position() != $nodeposn]"!][!//
      [!IF "(($POSN >= number(DcmDspRoutineSignalPos)) and ($POSN <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1))) or ((($POSN + $LENGTH -1) >= number(DcmDspRoutineSignalPos)) and (($POSN + $LENGTH -1) <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1)))"!][!//
        [!ERROR!][!//
          signal [!"node:name(.)"!] overlaps with signal [!"$Name"!]
          Routine Information : '[!"node:name(../../..)"!]'
          Configuration       : '[!"node:name(../..)"!]'
         [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!//
  [!LOOP "util:distinct(node:order(DcmDspRoutineStopIn/DcmDspRoutineStopInSignal/eb-list::* , 'DcmDspRoutineSignalPos'))"!][!//
    [!VAR "POSN" = "DcmDspRoutineSignalPos"!][!//
    [!VAR "LENGTH" = "DcmDspRoutineSignalLength"!][!//
    [!VAR "nodeposn" = "node:pos(.) + 1"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../eb-list::*[position() != $nodeposn]"!][!//
      [!IF "(($POSN >= number(DcmDspRoutineSignalPos)) and ($POSN <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1))) or ((($POSN + $LENGTH -1) >= number(DcmDspRoutineSignalPos)) and (($POSN + $LENGTH -1) <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1)))"!][!//
        [!ERROR!][!//
          signal [!"node:name(.)"!] overlaps with signal [!"$Name"!]
          Routine Information : '[!"node:name(../../..)"!]'
          Configuration       : '[!"node:name(../..)"!]'
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!//
  [!LOOP "util:distinct(node:order(DcmDspRoutineStopOut/DcmDspRoutineStopOutSignal/eb-list::* , 'DcmDspRoutineSignalPos'))"!][!//
    [!VAR "POSN" = "DcmDspRoutineSignalPos"!][!//
    [!VAR "LENGTH" = "DcmDspRoutineSignalLength"!][!//
    [!VAR "nodeposn" = "node:pos(.) + 1"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../eb-list::*[position() != $nodeposn]"!][!//
      [!IF "(($POSN >= number(DcmDspRoutineSignalPos)) and ($POSN <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1))) or ((($POSN + $LENGTH -1) >= number(DcmDspRoutineSignalPos)) and (($POSN + $LENGTH -1) <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1)))"!][!//
        [!ERROR!][!//
          signal [!"node:name(.)"!] overlaps with signal [!"$Name"!]
          Routine Information : '[!"node:name(../../..)"!]'
          Configuration       : '[!"node:name(../..)"!]'
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!//
  [!LOOP "util:distinct(node:order(DcmDspStartRoutineIn/DcmDspStartRoutineInSignal/eb-list::* , 'DcmDspRoutineSignalPos'))"!][!//
    [!VAR "POSN" = "DcmDspRoutineSignalPos"!][!//
    [!VAR "LENGTH" = "DcmDspRoutineSignalLength"!][!//
    [!VAR "nodeposn" = "node:pos(.) + 1"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../eb-list::*[position() != $nodeposn]"!][!//
      [!IF "(($POSN >= number(DcmDspRoutineSignalPos)) and ($POSN <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1))) or ((($POSN + $LENGTH -1) >= number(DcmDspRoutineSignalPos)) and (($POSN + $LENGTH -1) <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1)))"!][!//
        [!ERROR!][!//
          signal [!"node:name(.)"!] overlaps with signal [!"$Name"!]
          Routine Information : '[!"node:name(../../..)"!]'
          Configuration       : '[!"node:name(../..)"!]'
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!//
  [!LOOP "util:distinct(node:order(DcmDspStartRoutineOut/DcmDspStartRoutineOutSignal/eb-list::* , 'DcmDspRoutineSignalPos'))"!][!//
    [!VAR "POSN" = "DcmDspRoutineSignalPos"!][!//
    [!VAR "LENGTH" = "DcmDspRoutineSignalLength"!][!//
    [!VAR "nodeposn" = "node:pos(.) + 1"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../eb-list::*[position() != $nodeposn]"!][!//
      [!IF "(($POSN >= number(DcmDspRoutineSignalPos)) and ($POSN <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1))) or ((($POSN + $LENGTH -1) >= number(DcmDspRoutineSignalPos)) and (($POSN + $LENGTH -1) <= number(DcmDspRoutineSignalPos + DcmDspRoutineSignalLength -1)))"!][!//
        [!ERROR!][!//
          signal [!"node:name(.)"!] overlaps with signal [!"$Name"!]
          Routine Information : '[!"node:name(../../..)"!]'
          Configuration       : '[!"node:name(../..)"!]'
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!//
/*==================[inclusions]=================================================================*/

[!AUTOSPACING!]
#include <Dcm_RoutineControl_Cfg.h>                             /*  RoutineControl Configuration */

[!INCLUDE "../include/Dcm_common.m"!][!//
/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

[!VAR "RoutineCount" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)]))"!]
[!//
[!IF "$RoutineCount > 0 and ($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!][!//
[!//
[!IF "node:exists(util:distinct(node:refs(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*/DcmDspRoutineInfoRef))/DcmDspRoutineAuthorization/DcmDspRoutineSessionRef/eb-list::*) or node:exists(util:distinct(node:refs(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*/DcmDspRoutineInfoRef))/DcmDspRoutineAuthorization/DcmDspRoutineSecurityLevelRef/eb-list::*)"!][!//
#define DCM_START_SEC_CONST_8
#include <Dcm_MemMap.h>
[!//
[!VAR "sessioncount" = "0"!][!//
[!VAR "RoutineInfoList"="'#'"!][!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
    [!IF "not(contains($RoutineInfoList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
    [!VAR "sessioncount" = "$sessioncount + count(node:ref(DcmDspRoutineInfoRef)/DcmDspRoutineAuthorization/DcmDspRoutineSessionRef/eb-list::*)"!][!//
      [!VAR "RoutineInfoList" = "concat($RoutineInfoList, as:name(node:ref(DcmDspRoutineInfoRef)), '#')"!]
  [!ENDIF!]
[!ENDLOOP!][!//
[!//
[!IF "node:exists(util:distinct(node:refs(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*/DcmDspRoutineInfoRef))/DcmDspRoutineAuthorization/DcmDspRoutineSessionRef/eb-list::*)"!]
[!VAR "RoutineInfoList"="'#'"!][!//

/* Array of session types for all routines */
STATIC CONST(Dcm_SesCtrlType, DCM_CONST) Dcm_RoutineControl_SessionTypes[[!"num:i($sessioncount)"!]] =
{
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
      [!IF "not(contains($RoutineInfoList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
      [!SELECT "node:ref(DcmDspRoutineInfoRef)"!][!//
        [!LOOP "DcmDspRoutineAuthorization/DcmDspRoutineSessionRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U,
        [!ENDLOOP!][!//
      [!ENDSELECT!][!//
        [!VAR "RoutineInfoList" = "concat($RoutineInfoList, as:name(node:ref(DcmDspRoutineInfoRef)), '#')"!]
    [!ENDIF!]
  [!ENDLOOP!][!//
};
[!ENDIF!]
[!//
[!VAR "seclevelList"="'#'"!][!//
[!VAR "seclevelcount" = "0"!][!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
    [!IF "not(contains($seclevelList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
    [!VAR "seclevelcount" = "$seclevelcount + count(node:ref(DcmDspRoutineInfoRef)/DcmDspRoutineAuthorization/DcmDspRoutineSecurityLevelRef/eb-list::*)"!][!//
      [!VAR "seclevelList" = "concat($seclevelList, as:name(node:ref(DcmDspRoutineInfoRef)), '#')"!]
  [!ENDIF!]
[!ENDLOOP!][!//
[!//
[!IF "node:exists(util:distinct(node:refs(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*/DcmDspRoutineInfoRef))/DcmDspRoutineAuthorization/DcmDspRoutineSecurityLevelRef/eb-list::*)"!]
[!VAR "seclevelList"="'#'"!][!//

/* Array of security types for all routines */
STATIC CONST(Dcm_SecLevelType,DCM_CONST) Dcm_RoutineControl_SecurityLevel[[!"num:i($seclevelcount)"!]] =
{
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
      [!IF "not(contains($seclevelList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
      [!VAR "seclevelcount" = "$seclevelcount + 1"!][!//
      [!SELECT "node:ref(DcmDspRoutineInfoRef)"!][!//
        [!LOOP "DcmDspRoutineAuthorization/DcmDspRoutineSecurityLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,
        [!ENDLOOP!][!//
      [!ENDSELECT!][!//
        [!VAR "seclevelList" = "concat($seclevelList, as:name(node:ref(DcmDspRoutineInfoRef)), '#')"!]
    [!ENDIF!]
  [!ENDLOOP!][!//
};
[!ENDIF!]
[!//

#define DCM_STOP_SEC_CONST_8
#include <Dcm_MemMap.h>

[!ENDIF!][!//
[!//
/*==================[external constants]=========================================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!IF "$DCM_RID_AVAILABILITY_CALCULATION = 'STD_ON'"!]
  [!VAR "routineIndex" = "0"!]
  [!VAR "firstOBDOnUDSRoutine" = "'false'"!]
  [!VAR "routineOBDOnUDSIndexStart" = "num:hextoint('0xFFFF')"!]
  [!VAR "routineOBDOnUDSIndexEnd" = "0"!]
[!ENDIF!]

/* Contains the configuration (parameters) for Routine's Info */
[!VAR "routineinfocount" = "0"!][!//
[!VAR "routineInfoRefList"="'#'"!][!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
    [!IF "not(contains($routineInfoRefList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
    [!VAR "routineinfocount" = "$routineinfocount + 1"!][!//
      [!VAR "routineInfoRefList" = "concat($routineInfoRefList, as:name(node:ref(DcmDspRoutineInfoRef)), '#')"!]
  [!ENDIF!]
[!ENDLOOP!][!//
[!//
[!VAR "routineInfoRefCounter" = "0"!][!//
[!VAR "routineInfoRefList"="'#'"!][!//
[!VAR "SesLevelPos" = "0"!][!//
[!VAR "SecLevelPos" = "0"!][!//
CONST(Dcm_DspRoutineServicesInfoType, DCM_CONST) Dcm_DspRoutineInfoConfig[[!"num:integer( $routineinfocount)"!]] =
{
  [!INDENT "2"!]
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
      [!IF "not(contains($routineInfoRefList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
      [!SELECT "node:ref(DcmDspRoutineInfoRef)"!][!//
        {
        [!INDENT "4"!]
        [!VAR "NumSecLevels" = "num:integer(count(DcmDspRoutineAuthorization/DcmDspRoutineSecurityLevelRef/eb-list::*))"!][!//
        [!VAR "NumSesLevels" = "num:integer(count(DcmDspRoutineAuthorization/DcmDspRoutineSessionRef/eb-list::*))"!][!//
          /* Pointer to security levels */
          [!IF "$NumSecLevels > 0"!][!//
            &(Dcm_RoutineControl_SecurityLevel[[!"num:integer( $SecLevelPos)"!]]),
          [!ELSE!][!//
            NULL_PTR,
          [!ENDIF!]
          /* Pointer to sessions */
          [!IF "$NumSesLevels > 0"!][!//
            &(Dcm_RoutineControl_SessionTypes[[!"num:integer( $SesLevelPos)"!]]),
          [!ELSE!][!//
            NULL_PTR,
          [!ENDIF!]
          /* Number of sessions */
          [!"$NumSesLevels"!]U,
          /* Number of security levels */
          [!"$NumSecLevels"!]U
        [!VAR "SesLevelPos" = "$SesLevelPos + $NumSesLevels"!][!//
        [!VAR "SecLevelPos" = "$SecLevelPos + $NumSecLevels"!][!//
        [!ENDINDENT!]
        },
      [!ENDSELECT!][!//
      [!VAR "routineInfoRefList" = "concat($routineInfoRefList, as:name(node:ref(DcmDspRoutineInfoRef)), '#', num:i($routineInfoRefCounter), '#')"!]
      [!VAR "routineInfoRefCounter" = "$routineInfoRefCounter + 1"!]
    [!ENDIF!]
  [!ENDLOOP!][!//
  [!ENDINDENT!]
};

/* Configuration parameters for 'Routine Control' service */
CONST(Dcm_DspRoutineServicesType, DCM_CONST) Dcm_DspRoutineConfig[DCM_NUM_ROUTINES] =
{
[!INDENT "2"!]
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(./DcmDspRoutineUsed)], 'DcmDspRoutineIdentifier'))"!][!//
  {
  [!INDENT "4"!]
    /* Pointer to request service handler function */
    [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!][!//
      &Dcm_[!"node:name(.)"!]_RequestResults,
    [!ELSE!][!//
      NULL_PTR,
    [!ENDIF!][!//
    /* Pointer to start service handler function */
    [!IF "(((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror)))"!]
      &Dcm_[!"node:name(.)"!]_Start,
    [!ELSE!][!//
      NULL_PTR,
    [!ENDIF!][!//
    /* Pointer to stop service handler function */
    [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
      &Dcm_[!"node:name(.)"!]_Stop,
    [!ELSE!][!//
      NULL_PTR,
    [!ENDIF!][!//
    [!VAR "currentconfig" = "concat('#', as:name(as:ref(DcmDspRoutineInfoRef)), '#')"!][!//
    [!VAR "routineinfoindex" = "num:i(substring-before(substring-after($routineInfoRefList, $currentconfig), '#'))"!][!//
    /* Pointer to assigned RoutineInfo configuration */
    &Dcm_DspRoutineInfoConfig[[!"num:integer($routineinfoindex)"!]],
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
    /* Routine mode rule */
    [!IF "node:exists(node:ref(DcmDspRoutineInfoRef)/DcmDspRoutineAuthorization/DcmDspRoutineModeRuleRef)"!]
      &Dcm_ModeRule_[!"as:name(node:ref(node:ref(DcmDspRoutineInfoRef)/DcmDspRoutineAuthorization/DcmDspRoutineModeRuleRef))"!]_Result,
    [!ELSE!]
      NULL_PTR,
    [!ENDIF!]
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
    /* RID Identifier */
    [!"num:inttohex(DcmDspRoutineIdentifier)"!]U,
    [!//
    [!IF "(node:existsAndTrue(../../DcmDspEnableObdMirror))"!]
      /* Define the interface that will be used for this Routine: TRUE = OBD, FALSE = UDS */
      [!IF "((DcmDspRoutineIdentifier >= num:hextoint('0xE000')) and (DcmDspRoutineIdentifier <= num:hextoint('0xE0FF')) and (node:refvalid(DcmDspRoutineTidRef)))"!]
        TRUE
      [!ELSE!][!//
        FALSE
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDINDENT!]
  }, /* index: [!"node:pos(.)"!] */
  [!IF "$DCM_RID_AVAILABILITY_CALCULATION = 'STD_ON'"!]
    [!IF "(DcmDspRoutineIdentifier >= num:hextoint('0xE000')) and (DcmDspRoutineIdentifier <= num:hextoint('0xE1FF'))"!]
      [!IF "($firstOBDOnUDSRoutine = 'false')"!]
        [!VAR "routineOBDOnUDSIndexStart"="$routineIndex"!]
        [!VAR "firstOBDOnUDSRoutine"="'true'"!]
      [!ENDIF!]
      [!VAR "routineOBDOnUDSIndexEnd"="$routineIndex"!]
    [!ENDIF!]
    [!VAR "routineIndex"="$routineIndex + 1"!]
  [!ENDIF!]
[!ENDLOOP!][!//
[!ENDINDENT!]
};

[!IF "$DCM_RID_AVAILABILITY_CALCULATION = 'STD_ON'"!]
  CONST(uint16, DCM_CONST) Dcm_Dsp_RoutineControl_OBDOnUDS_RoutineIndexStart = [!"num:i($routineOBDOnUDSIndexStart)"!]U;
  CONST(uint16, DCM_CONST) Dcm_Dsp_RoutineControl_OBDOnUDS_RoutineIndexEnd = [!"num:i($routineOBDOnUDSIndexEnd)"!]U;
[!ENDIF!]

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!//
[!ENDIF!]
/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

/*==================[end of file]================================================================*/
