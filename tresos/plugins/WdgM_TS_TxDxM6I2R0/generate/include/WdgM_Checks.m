[!/**
 * \file
 *
 * \brief AUTOSAR WdgM
 *
 * This file contains the implementation of the AUTOSAR
 * module WdgM.
 *
 * \version 6.2.7
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!NOCODE!][!//
[!/* *** multiple inclusion protection ***
*/!][!IF "not(var:defined('WDGM_CHECKS_M'))"!][!/*
*/!][!VAR "WDGM_CHECKS_M"="'true'"!][!/*
*/!][!INCLUDE "include/WdgM_Macros.m"!][!/*

****************************************************************************
* Least common multiple of all reference cycle values of a
* mode exceeds the maximum value representable by a 32-bit variable.
****************************************************************************
*/!][!/*
*/!][!LOOP "util:distinct(node:order(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!/*
  */!][!VAR "modeLCM"!][!/*
    */!][!CALL "getModeSpecificLCM", "modeRef" = "as:path(.)"!][!/*
  */!][!ENDVAR!][!/*
  */!][!ASSERT "num:i($modeLCM) <= num:i(4294967295)"!][!/*
    */!]The Supervision Reference Cycles for the configured Alive Supervisions in WdgM mode '[!"as:name(.)"!]' have a least common multiple of [!"$modeLCM"!] which cannot be represented via the internal 32-bit supervision counter.[!/*
  */!][!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*

****************************************************************************
* At least one Supervised Entity mapped to a satellite core and one to the
* master core
****************************************************************************
*/!][!IF "node:exists(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores) and as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMNumberOfCores > 1"!][!/*
*/!][!VAR "NumberOfMasterCoreSEs" = "0"!][!/*
*/!][!LOOP "as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*"!][!/*
  */!][!VAR "NumberOfSEs" = "num:i(count(as:modconf('WdgM')[1]/WdgMGeneral/WdgMSupervisedEntity/eb-list::*))"!][!/*
  */!][!IF "num:i(node:value(WdgMSupervisedEntityCoreId)) = num:i(node:value(as:modconf('WdgM')[1]/WdgMGeneral/WdgMGeneralMulticore/WdgMMasterCoreId))"!][!/*
    */!][!VAR "NumberOfMasterCoreSEs" = "num:i($NumberOfMasterCoreSEs + 1)"!][!/*
    */!][!IF "$NumberOfSEs = $NumberOfMasterCoreSEs"!][!/*
      */!][!ERROR "If the MultiCore feature is enabled, at least one Supervised Entity shall be mapped to the WdgMMasterCoreId and at least one Supervised Entity shall be mapped to a satellite core."!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!ENDIF!][!/*

****************************************************************************
* At least one Supervised Entity must be configured
****************************************************************************
*/!][!/*
*/!][!ASSERT "$NumberOfSupervisedEntities >= num:i(1)"!][!/*
  */!]There must be at least one Supervised Entity configured.[!/*
*/!][!ENDASSERT!][!/*

<!-- !LINKSTO WDGM.EB.ExternalSupervision2,1 -->
****************************************************************************
* Check if there is one connected graph per WdgMExternalLogicalSupervision instance:
*
* For each pair of used initial checkpoints, the following must be valid:
*   The intersection set of the final checkpoints reachable from the
*   two initial checkpoints must not be empty
****************************************************************************
*/!][!/*
*/!][!LOOP "util:distinct(node:order(WdgMConfigSet/eb-list::*[1]/WdgMMode/eb-list::*, 'WdgMModeId'))"!][!/*
*/!][!VAR "modeName" = "as:name(.)"!][!/*
*/!][!VAR "modeId" = "WdgMModeId"!][!/*
  */!][!LOOP "WdgMExternalLogicalSupervision/eb-list::*"!][!/*
    */!][!VAR "extSupervName" = "as:name(.)"!][!/*
    */!][!VAR "extLogSupervIndex" = "node:pos(.)"!][!/*
    */!][!LOOP "util:distinct(node:order(WdgMExternalCheckpointInitialRef/eb-list::*, 'num:i(node:pos(.))'))"!][!/*
      */!][!VAR "initCPRef1"="node:value(.)"!][!/*
      */!][!VAR "initCPIndex1"="num:i(node:pos(.))"!][!/*
      */!][!VAR "initCP1Name" = "as:name(node:ref($initCPRef1))"!][!/*
      */!][!LOOP "util:distinct(node:order(../../WdgMExternalCheckpointInitialRef/eb-list::*, 'num:i(node:pos(.))'))"!][!/*
        */!][!VAR "initCPRef2"="node:value(.)"!][!/*
        */!][!VAR "initCPIndex2"="num:i(node:pos(.))"!][!/*
        */!][!VAR "initCP2Name" = "as:name(node:ref($initCPRef2))"!][!/*
        */!][!IF "$initCPIndex2 > $initCPIndex1"!][!/*
          */!][!VAR "finalCPs1"!][!/*
            */!][!CALL "getFinalCPsFromInitialCP", "sourceCPRef" = "$initCPRef1", "modeId" = "$modeId", "extLogSupervIndex" = "$extLogSupervIndex", "visited" = "''"!][!/*
          */!][!ENDVAR!][!/*
          */!][!VAR "finalCPs2"!][!/*
            */!][!CALL "getFinalCPsFromInitialCP", "sourceCPRef" = "$initCPRef2", "modeId" = "$modeId", "extLogSupervIndex" = "$extLogSupervIndex", "visited" = "''"!][!/*
          */!][!ENDVAR!][!/*
          */!][!IF "(count(text:split($finalCPs1)) > 0) and (count(text:split($finalCPs2)) > 0)"!][!/*
            */!][!VAR "nIntersectingCPs"="num:i(0)"!][!/*
            */!][!LOOP "text:split($finalCPs1)"!][!/*
              */!][!VAR "finalCP1"="."!][!/*
              */!][!LOOP "text:split($finalCPs2)"!][!/*
                */!][!VAR "finalCP2"="."!][!/*
                */!][!IF "$finalCP1 = $finalCP2"!][!/*
                  */!][!VAR "nIntersectingCPs"="num:i(num:i($nIntersectingCPs) + num:i(1))"!][!/*
                */!][!ENDIF!][!/*
              */!][!ENDLOOP!][!/*
            */!][!ENDLOOP!][!/*
            */!][!ASSERT "num:i($nIntersectingCPs) > num:i(0)"!][!/*
              */!]The External Logical Supervision configuration with name '[!"$extSupervName"!]' in WdgM mode '[!"$modeName"!]' contains at least two independent graphs starting with Initial Checkpoints '[!"$initCP1Name"!]' and '[!"$initCP2Name"!]', but only one connected graph is allowed per instance of the WdgMExternalLogicalSupervision container.[!/*
            */!][!ENDASSERT!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDLOOP!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*

 */!][!/*
 **********************************************************************
 */!][!ENDIF!][!/*
 */!][!//
[!ENDNOCODE!][!//