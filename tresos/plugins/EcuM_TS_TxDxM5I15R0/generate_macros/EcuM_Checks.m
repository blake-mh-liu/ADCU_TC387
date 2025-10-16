[!/**
 * \file
 *
 * \brief AUTOSAR EcuM
 *
 * This file contains the implementation of the AUTOSAR
 * module EcuM.
 *
 * \version 5.15.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//

[!VAR "variantName"="variant:name()"!][!//

[!IF "$variantName = ''"!][!//
[!// ERROR and WARNING evaluate their parameter as an xpath expression thus a dummy concat is used here.
[!VAR "RestartListErr"="concat('Entries in the restart list should be in the same order as in init list zero and one','')"!][!//
[!VAR "RestartListWrn"="concat('There is one entry in the restart list which does not have a counterpart in init list zero or one','')"!][!//
[!ELSE!][!//
[!VAR "RestartListErr"="concat('Entries in the restart list should be in the same order as in init list zero and one for variant ',$variantName)"!][!//
[!VAR "RestartListWrn"="concat('There is one entry in the restart list which does not have a counterpart in init list zero or one for variant ',$variantName)"!][!//
[!ENDIF!][!//

[!NOCODE!][!//
[!//
[!SELECT "EcuMConfiguration/eb-list::*[1]/EcuMCommonConfiguration"!][!//
[!/* Check for correct order of invocations */!][!//
[!VAR "ModuleServiceList"="''"!][!// Let ModuleServiceList be initially empty
[!LOOP "(EcuMDriverInitListZero/EcuMDriverInitItem/eb-list::*)"!][!// Loop through init list zero
    [!VAR "ModuleServiceList"="concat($ModuleServiceList,' ',EcuMModuleID,'_', EcuMModuleService)"!][!//
[!ENDLOOP!][!//
[!LOOP "(EcuMDriverInitListOne/EcuMDriverInitItem/eb-list::*)"!][!// Loop through init list one
  [!IF "EcuMEnableDriver"!][!//
    [!VAR "ModuleServiceList"="concat($ModuleServiceList,' ',EcuMModuleID,'_', EcuMModuleService)"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

[!/* !LINKSTO EcuM.ASR403.EcuM2720,1 */!]
[!VAR "RestartModuleService"="''"!][!// Let RestartModuleService be initially empty
[!VAR "PreviousLocation"="-1"!][!// Let PreviousLocation be initially empty
[!VAR "CurrentLocation"="-1"!][!// Let CurrentLocation be initially empty
[!LOOP "EcuMDriverRestartList/EcuMDriverInitItem/eb-list::*"!][!// Loop through Restart List
  [!IF "EcuMEnableDriver"!][!//
    [!VAR "RestartModuleService"="concat($RestartModuleService,' ',EcuMModuleID,'_', EcuMModuleService)"!][!//
    [!VAR "CurrentLocation"= "text:indexOf( string($ModuleServiceList), string($RestartModuleService) )"!][!//
    [!IF "$CurrentLocation > -1"!][!//
      [!IF "$CurrentLocation <= $PreviousLocation"!][!// if the order is not correct display the error
        [!ERROR "?$RestartListErr"!][!//
      [!ENDIF!][!//
      [!VAR "PreviousLocation" = "$CurrentLocation"!][!// save the current location
    [!ELSE!][!//
      [!WARNING "?$RestartListWrn"!][!//
    [!ENDIF!][!//
    [!VAR "RestartModuleService"="''"!][!// empty the string for future iterations
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//

[!IF "node:existsAndTrue(as:modconf('EcuM')/EcuMGeneral/EcuMEnableMulticore)"!]
[!MACRO "ComMGetUserOsApplication","UserEcuCPartitionRef"!]
[!VAR "UserOsApplication" = "node:name(as:modconf('Os')[1]/OsApplication/eb-list::*[node:exists(OsAppEcucPartitionRef) and (string(OsAppEcucPartitionRef) = $UserEcuCPartitionRef)])"!]
[!ENDMACRO!]

[!MACRO "ComMGetMasterPncOsApplication"!]
[!VAR "MasterPncOsApplication"="''"!]
[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef)"!]
  [!VAR "MasterPncOsApplication" = "node:name(as:modconf('Os')[1]/OsApplication/eb-list::*[node:exists(OsAppEcucPartitionRef) and (OsAppEcucPartitionRef = as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef)])"!]
[!ENDIF!]
[!ENDMACRO!]

[!MACRO "ComMGetUsedUserOsApplications"!]
[!VAR "FoundUserOsApplications"="''"!]
[!LOOP "as:modconf('ComM')[1]/ComMConfigSet/eb-list::*[1]/ComMUser/eb-list::*"!]
  [!IF "node:exists(ComMUserEcucPartitionRef)"!]
    [!CALL "ComMGetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
    [!VAR "OsApplicationAssignmentFound" = "'false'"!]
    [!FOR "Idx" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]
      [!IF "(string(text:split($FoundUserOsApplications,' ')[position() = $Idx]) = $UserOsApplication)"!]
        [!VAR "OsApplicationAssignmentFound" = "'true'"!]
      [!ENDIF!]
    [!ENDFOR!]
    [!IF "$OsApplicationAssignmentFound = 'false'"!]
      [!IF "count(text:split($FoundUserOsApplications,' ')) = 0"!]
        [!VAR "FoundUserOsApplications" = "$UserOsApplication"!]
      [!ELSE!]
        [!VAR "FoundUserOsApplications" = "concat($FoundUserOsApplications,' ')"!]
        [!VAR "FoundUserOsApplications" = "concat($FoundUserOsApplications,$UserOsApplication)"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]
[!ENDMACRO!]

[!MACRO "ComMGetUsedInhibitionOsApplication"!]
[!VAR "FoundInhibitionOsApplication"="''"!]
[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMInhibitionEcuCPartitionRef)"!]
  [!VAR "FoundInhibitionOsApplication" = "node:name(as:modconf('Os')[1]/OsApplication/eb-list::*[node:exists(OsAppEcucPartitionRef) and (OsAppEcucPartitionRef = as:modconf('ComM')[1]/ComMGeneral/ComMInhibitionEcuCPartitionRef)])"!]
[!ENDIF!] [!/*[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMInhibitionEcuCPartitionRef))"!]*/!]
[!ENDMACRO!]

[!MACRO "ComMGetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
[!CALL "ComMGetMasterPncOsApplication"!]
[!CALL "ComMGetUsedUserOsApplications"!]
[!CALL "ComMGetUsedInhibitionOsApplication"!]
[!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications"="$MasterPncOsApplication"!]
[!VAR "OsApplicationAssignmentFound" = "'false'"!]
[!FOR "Idx1" = "1" TO "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' '))"!]
  [!IF "($FoundInhibitionOsApplication) = string(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')[position() = $Idx1])"!]
    [!VAR "OsApplicationAssignmentFound" = "'true'"!]
    [!BREAK!]
  [!ENDIF!]
[!ENDFOR!] [!/* [!FOR "Idx1" = "1" TO "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' '))"!] */!]
[!IF "$OsApplicationAssignmentFound = 'false'"!]
  [!IF "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) = 0"!]
    [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "$FoundInhibitionOsApplication"!]
  [!ELSE!]
   [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "concat($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')"!]
   [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "concat($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,$FoundInhibitionOsApplication)"!]
  [!ENDIF!]
[!ENDIF!] 
[!FOR "Idx1" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]
  [!VAR "OsApplicationAssignmentFound" = "'false'"!]
  [!FOR "Idx2" = "1" TO "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' '))"!]
    [!IF "(string(text:split($FoundUserOsApplications,' ')[position() = $Idx1]) = string(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')[position() = $Idx2]))"!]
      [!VAR "OsApplicationAssignmentFound" = "'true'"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDFOR!] [!/* [!FOR "Idx1" = "1" TO "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' '))"!] */!]
  [!IF "$OsApplicationAssignmentFound = 'false'"!]
    [!IF "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) = 0"!]
      [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "string(text:split($FoundUserOsApplications,' ')[position() = $Idx1])"!]
    [!ELSE!]
     [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "concat($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')"!]
     [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "concat($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,string(text:split($FoundUserOsApplications,' ')[position() = $Idx1]))"!]
    [!ENDIF!]
  [!ENDIF!] 
[!ENDFOR!] [!/*[!FOR "Idx1" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]*/!]
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/eb-list::*[1]/ComMChannel/eb-list::*, 'ComMChannelId'))"!]
  [!IF "node:exists(ComMChannelPartitionRef)"!]
    [!VAR "PartitionRef" = "ComMChannelPartitionRef"!]
    [!LOOP "as:modconf('Os')[1]/OsApplication/eb-list::*[node:exists(OsAppEcucPartitionRef) and (string(OsAppEcucPartitionRef) = $PartitionRef)]"!]
      [!VAR "OsApplicationAssignmentFound" = "'false'"!]
      [!FOR "Idx" = "1" TO "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' '))"!]
        [!IF "(string(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')[position() = $Idx]) = node:name(.))"!]
          [!VAR "OsApplicationAssignmentFound" = "'true'"!]
        [!ENDIF!]
      [!ENDFOR!]
      [!IF "$OsApplicationAssignmentFound = 'false'"!]
        [!IF "count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) = 0"!]
          [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "node:name(.)"!]
        [!ELSE!]
         [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "concat($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')"!]
         [!VAR "FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications" = "concat($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,node:name(.))"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDLOOP!]
[!ENDMACRO!]

[!CALL "ComMGetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
[!IF "(node:existsAndTrue(as:modconf('EcuM')/EcuMGeneral/EcuMCrossCoreComMWakeup)) and (node:existsAndFalse(as:modconf('ComM')/ComMGeneral/ComMMultiCoreSupport))"!]
[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) < 1)"!]
[!ERROR "If EcuMCrossCoreComMWakeup is enabled, ComM shall also be multicore capable by either enabling ComMMultiCoreSupport OR by referencing ComM channels and ComM users to EcuC partitions"!][!//
[!ENDIF!]
[!ENDIF!]

[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (node:existsAndFalse(as:modconf('EcuM')/EcuMGeneral/EcuMCrossCoreComMWakeup))"!]
[!ERROR "If EcuC partitions (User, Channel, Pnc, Inhibition) are enabled in ComM and EcuMEnableMulticore is set to true EcuMCrossCoreComMWakeup shall also be set to true"!][!//
[!ENDIF!]

[!ENDIF!][!//

[!ENDNOCODE!][!//
