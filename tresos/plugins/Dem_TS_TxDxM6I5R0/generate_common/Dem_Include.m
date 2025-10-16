[!/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \version 6.5.8
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!//
[!/* ======== IMPORTANT NOTE! ===============
   * Dem_Include.m in generate_swcd/swcd_calibration
   * is an svn external of Dem_Include.m in generate/include and
   * This is done due to a include limitation for macro files */!][!//
[!//
[!/* === define maximum space needed ===*/!][!//
[!AUTOSPACING!][!//
[!MACRO "Indent", "Length"!][!//
[!INDENT "0"!][!//
  [!FOR "i" = "1" TO "$Length"!][!//
    [!WS!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!SELECT "as:modconf('Dem')[1]"!][!//
[!//
[!/* === original DEM configuration parameters ===*/!][!//
[!VAR "CommonOperationCycleEnabled" = "node:existsAndTrue(DemGeneral/DemCommonOperationCycleSupport)"!][!//
[!VAR "EventCombinationSupport" = "DemGeneral/DemEventCombinationSupport"!][!//
[!VAR "CalibrationSupport" = "node:existsAndTrue(DemGeneral/DemCalibrationSupport)"!][!//
[!VAR "CalibrationWithoutEvCombSupport" = "($CalibrationSupport = 'true') and ($EventCombinationSupport = 'DEM_EVCOMB_DISABLED')"!][!//
[!VAR "CalibrationWithEvCombSupport" = "($CalibrationSupport = 'true') and ($EventCombinationSupport != 'DEM_EVCOMB_DISABLED')"!][!//
[!VAR "ObdUdsDtcSeparationSupport" = "(((node:exists(DemGeneral/DemObdVariant)) and (DemGeneral/DemObdVariant = 'DEM_OBD_VARIANT_OBDONUDS')) or node:exists(DemGeneral/DemCalloutObdVariantFnc)) and node:existsAndTrue(DemGeneral/DemGeneralOBD/DemSupportedObdUdsDtcSeparation)"!][!//
[!VAR "ReadinessEventSlotAvailability" = "node:exists(DemGeneral/DemReadinessGroupCalibration/eb-list::*) and (num:i(sum(DemGeneral/DemReadinessGroupCalibration/eb-list::*)) > 0)"!][!//
[!VAR "ReadinessCalibrationSupport" = "node:exists(DemGeneral/DemMaxNumEventsPerReadinessGroup) or ($ReadinessEventSlotAvailability = 'true')"!][!//
[!VAR "DemRteUsage" = "DemGeneral/DemRteUsage"!][!//
[!VAR "NumMultiEventTriggering" = "num:integer(count(DemGeneral/DemMultiEventTriggering/eb-list::*))"!][!//
[!VAR "DemTaskTime" = "DemGeneral/DemTaskTime"!][!//
[!VAR "OBDonUDSCombination" = "($EventCombinationSupport = 'DEM_EVCOMB_TYPE1') and (node:existsAndTrue(DemGeneral/DemOBDSupport)) and ((DemGeneral/DemObdVariant = 'DEM_OBD_VARIANT_OBDONUDS') or (node:exists(DemGeneral/DemCalloutObdVariantFnc))) "!][!//
[!VAR "MARSupport" = "(node:existsAndTrue(DemGeneral/DemOBDSupport)) and ((DemGeneral/DemObdVariant = 'DEM_OBD_VARIANT_OBDONUDS') or (node:exists(DemGeneral/DemCalloutObdVariantFnc))) and (count(util:distinct(node:refs(util:distinct(node:refs(as:modconf('Dem')[1]/DemConfigSet/eb-list::*[1]/DemEventParameter/eb-list::*/DemExtendedDataClassRef))/DemExtendedDataRecordClassRef/eb-list::*))[DemExtendedDataRecordNumber = '147']) > 0)"!][!//
[!VAR "DemObdDTCSupport" = "node:exists(DemGeneral/DemCalloutObdVariantFnc) or DemGeneral/DemObdVariant = 'DEM_OBD_VARIANT_OBD_CLASSIC' or $ObdUdsDtcSeparationSupport = 'false'"!][!//
[!VAR "DemNumEnCondGroups" = "count(DemGeneral/DemEnableConditionGroup/eb-list::*)"!][!//
[!VAR "DTCClassAvailable" = "node:existsAndTrue(as:modconf('Dem')[1]/DemGeneral/DemWWHOBDDTCClassSupport)"!][!//
[!VAR "DemAgingAllowedSupport" = "node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:existsAndTrue(DemEventClass/DemAgingAllowed)])"!][!//
[!//
[!/* === derived configuration parameters ===*/!][!//
[!VAR "AgingAllowedSeperateFlag" = "(node:existsAndTrue(DemGeneral/DemAgingAllowedSeperateFlag)) and ($CalibrationWithoutEvCombSupport = 'true')"!][!//
[!VAR "NumIndicator" = "num:i(count(DemGeneral/DemIndicator/eb-list::*))"!][!//
[!VAR "NumFFCls" = "count(DemGeneral/DemFreezeFrameClass/eb-list::*)"!][!//
[!VAR "NumberOfConfiguredDemEvents" = "num:integer(count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*))"!][!//
[!//
[!ENDSELECT!][!//
[!/* === String variables used for generating bit-packed structures ===
   * Dem_EventDesc[]       -> EventDescStr
   * Dem_DTCDesc[]         -> DTCDescStr
   * Dem_EventDTCConfIdx[] -> DTCConfIdxStr
   * Dem_OBDDTC[]          -> OBDDTCStr
   * Dem_OBDConfig[]       -> OBDConfigStr  */!][!//
[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED'"!][!//
  [!VAR "EventDescEmptyStr" = "'{ 0U, 0U, 0U },'"!][!//
  [!VAR "EventDescStr"!][!//
    Dem_EventDesc
    #SM# EvConf1 32
      UDS_DTC_VALUE
      DTC_ORIGIN
      DTC_SEVERITY
      ENABLE_PRESTORAGE
      EVENT_KIND
      INDICATOR_USED
      IMMEDIATE_STORAGE
    #SM# EvConf2 32
      EVENT_SIGNIFICANCE
      FFCLASSIDX
      FFRECINFO
      EXTENDED_DATA_CLASS
      OPERATION_CYCLE
      AGING_CTR_THRESHOLD
      DTC_GROUP
      EVENT_CLASS
    #SM# EvConf3 32
      ENABLE_CONDITION_GROUP_IDX
      EVENT_FAILURE_CLASS_IDX
      EVENT_PRIORITY
      DEBOUNCE_ALGORITHM
      FUNCTIONAL_UNIT
      AGING_CYCLE_ID
  [!ENDVAR!][!//
  [!IF "($CalibrationWithoutEvCombSupport = 'false') and ($NumMultiEventTriggering > 0)"!][!//
    [!VAR "EventDescEmptyStr" = "'{ 0U, 0U, 0U, 0U },'"!][!//
    [!VAR "EventDescStr" = "concat($EventDescStr, ' #SM# EvConf4 32 MULTI_EVENT_TRIGGERING_IDX')"!][!//
  [!ENDIF!][!//
  [!//
[!ELSE!][!//
  [!VAR "EventDescEmptyStr" = "'{ 0U },'"!][!//
  [!VAR "EventDescStr"!][!//
    Dem_EventDesc
    #SM# EvConf1 32
      EVENT_KIND
      INDICATOR_USED
      ENABLE_PRESTORAGE
      DEBOUNCE_ALGORITHM
      ENABLE_CONDITION_GROUP_IDX
      EVENT_FAILURE_CLASS_IDX
      OPERATION_CYCLE
      DTC_CONFIG_IDX
  [!ENDVAR!][!//
  [!IF "($CalibrationWithoutEvCombSupport = 'false') and ($NumMultiEventTriggering > 0)"!][!//
    [!VAR "EventDescEmptyStr" = "'{ 0U, 0U },'"!][!//
    [!VAR "EventDescStr" = "concat($EventDescStr, ' #SM# EvConf2 32 MULTI_EVENT_TRIGGERING_IDX')"!][!//
  [!ENDIF!][!//
  [!//
  [!VAR "DTCDescStr"!][!//
    Dem_DTCDesc
    #SM# DTCConf1 32
      UDS_DTC_VALUE
      DTC_ORIGIN
      DTC_SEVERITY
      IMMEDIATE_STORAGE
      EVENT_SIGNIFICANCE
    #SM# DTCConf2 32
      EVENT_PRIORITY
      FFCLASSIDX
      FFRECINFO
      EXTENDED_DATA_CLASS
      AGING_CYCLE_ID
      AGING_CTR_THRESHOLD
      FUNCTIONAL_UNIT
      DTC_GROUP
  [!ENDVAR!][!//
  [!VAR "DTCConfIdxStr"!][!//
    Dem_EventDTCConfIdx
    #SM# #NONE# 16
      DTC_CONFIG_IDX
  [!ENDVAR!][!//
[!ENDIF!][!//
[!//
[!IF "$DemObdDTCSupport = 'true'"!][!//
  [!VAR "OBDDTCStr"!][!//
    Dem_OBDDTC
    #SM# #NONE# 16
      OBD_DTC_VALUE
  [!ENDVAR!][!//
[!ENDIF!][!//
[!//
[!VAR "OBDConfigEmptyStr" = "'0U,'"!][!//
[!IF "$ObdUdsDtcSeparationSupport = 'true'"!][!//
  [!VAR "OBDConfigStr"!][!//
    Dem_OBDConfig
    #SM# #NONE# 32
      3BYTE_OBD_DTC_VALUE
      WWHOBD_DTCCLASS_VALUE
      OBD_READINESS_VALUE
  [!ENDVAR!][!//
[!ELSE!][!//
  [!VAR "OBDConfigStr"!][!//
    Dem_OBDConfig
    #SM# #NONE# 8
      WWHOBD_DTCCLASS_VALUE
      OBD_READINESS_VALUE
  [!ENDVAR!][!//
[!ENDIF!][!//
[!/*
 * === Get DemEventClassString ===
 * This Macro will fill the variable EventClassString
 * with a string of the following structure:
 *
 * MultiEventTriggeringClassIdx         T
 * DemIndicatorClass                    I
 * DemAgingCycleCounterThreshold        A
 * DemOBDAgingCycleCounterThreshold     O
 * DemEventFailureCycleCounterThreshold F
 * DemEventPriority                     P
 * CommonOperationCycle                 !
 * DemAgingAllowed                      ?
 * DemMinRatioEvent                     M
 * DemEnableConditionGroupRef           &
 *
 * The String contains the values from the configuration parameter DemEventParameter separated by a
 * meaningful character.
 */!][!//
[!MACRO "GET_EVENT_CLASS_STRING"!][!//
[!INDENT "0"!][!//
  [!VAR "EventClassString" = "''"!][!//
  [!/* calculate multi event triggering index */!][!//
  [!CALL "GET_MULTI_EVENT_TRIGGERING_INDEX", "EVENT_ID" = "../DemEventId"!][!//
  [!IF "$MultiEventTriggeringClassIdx != $NumMultiEventTriggering"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, num:i($MultiEventTriggeringClassIdx), 'T')"!][!//
  [!ELSE!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '-', 'T')"!][!//
  [!ENDIF!][!//
  [!/* calculate indicator class index */!][!//
  [!CALL "GET_INDICATOR_CLASS_INDEX", "EVENT_ID" = "../DemEventId"!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $IndicatorClassIndex, 'I')"!][!//
  [!/* calculate aging allowed and threshold */!][!//
  [!IF "node:exists(DemAgingAllowed)"!][!//
    [!VAR "AgingAllowed" = "DemAgingAllowed"!][!//
  [!ELSE!][!//
    [!VAR "AgingAllowed" = "'false'"!][!//
  [!ENDIF!][!//
  [!IF "$AgingAllowed = 'true'"!][!//
    [!VAR "AgingCycleCounterThreshold" = "num:i(DemAgingCycleCounterThreshold)"!][!//
  [!ELSE!][!//
    [!/* !LINKSTO Dem.AgingAllowedSeperateEntry.Disabled,1 */!][!//
    [!VAR "AgingCycleCounterThreshold" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!/* calculate aging counter threshold */!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $AgingCycleCounterThreshold, 'A')"!][!//
  [!/* calculate OBD aging counter threshold */!][!//
  [!IF "node:existsAndTrue(DemAgingAllowed) and node:exists(DemOBDAgingCycleCounterThreshold)"!][!//
    [!VAR "OBDAgingCycleCounterThreshold" = "num:i(DemOBDAgingCycleCounterThreshold)"!][!//
  [!ELSE!][!//
    [!VAR "OBDAgingCycleCounterThreshold" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $OBDAgingCycleCounterThreshold, 'O')"!][!//
  [!/* calculate OBD failure cycle threshold */!][!//
  [!IF "node:exists(DemEventFailureCycleCounterThreshold)"!][!//
    [!VAR "EventFailureCycleCounterThreshold" = "num:i(DemEventFailureCycleCounterThreshold)"!][!//
  [!ELSE!][!//
    [!VAR "EventFailureCycleCounterThreshold" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $EventFailureCycleCounterThreshold, 'F')"!][!//
  [!/* calculate priority */!][!//
  [!IF "node:exists(DemEventPriority)"!][!//
    [!VAR "EventPriority" = "num:i(DemEventPriority)"!][!//
  [!ELSE!][!//
    [!VAR "EventPriority" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $EventPriority, 'P')"!][!//
  [!IF "$CommonOperationCycleEnabled = 'true'"!][!//
    [!/* calculate common operation cycle */!][!//
    [!VAR "EventClassString" = "concat($EventClassString, as:name(as:ref(DemOperationCycleRef)), '!')"!][!//
  [!ENDIF!][!//
  [!/* !LINKSTO Dem.AgingAllowedSeperateEntry.Enabled,1 */!][!//
  [!IF "$AgingAllowedSeperateFlag = 'true'"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, text:toupper($AgingAllowed), '?')"!][!//
  [!ENDIF!][!//
  [!/* calculate minimum ratio */!][!//
  [!IF "(node:existsAndTrue(DemMinRatioEvent))"!][!//
    [!VAR "MinRatioEvent" = "num:i(1)"!][!//
  [!ELSE!][!//
    [!VAR "MinRatioEvent" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $MinRatioEvent, 'M')"!][!//
  [!/* enable condition group */!][!//
  [!VAR "EnCondGroupRef" = "''"!][!//
  [!IF "node:exists(DemEnableConditionGroupRef)"!][!//
    [!VAR "EnCondGroupRef" = "node:pos(as:ref(DemEnableConditionGroupRef))"!][!//
  [!ELSE!][!//
    [!VAR "EnCondGroupRef" = "'-'"!][!//
  [!ENDIF!][!//
  [!VAR "EventClassString" = "concat($EventClassString, $EnCondGroupRef, '&')"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*
 * === Create DemEventClassList ===
 * This Macro creates a list of unique EventClassString
 * The EventClassString is created with the macro "GET_EVENT_CLASS_STRING"
 * The EventClassString are separate by '#' and ordered first occurrence in a DemEventParameter
 * ordered by DemEventId
 * At the end are added strings with default values for empty configuration entries
 */!][!//
[!MACRO "CREATE_EVENT_CLASS_LIST"!][!//
[!INDENT "0"!][!//
  [!VAR "EventClassList" = "''"!][!//
  [!CALL "CALC_INDICATOR_CLASSES"!][!//
  [!CALL "CALC_MULTI_EVENT_CLASSES"!][!//
  [!LOOP "util:distinct(node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Dem/ELEMENTS/Dem/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*,'DemEventId'))"!][!//
    [!VAR "IndicatorClassIndex" = "0"!][!//
    [!SELECT "DemEventClass"!][!//
      [!CALL "GET_EVENT_CLASS_STRING"!][!//
    [!ENDSELECT!][!//
    [!IF "not(contains($EventClassList,$EventClassString))"!][!//
      [!VAR "EventClassList" = "concat($EventClassList, $EventClassString, '#')"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!VAR "NumOfEventClasses" = "num:integer(count(text:split($EventClassList, '#')))"!][!//
  [!VAR "MaxNumberEventClasses" = "DemGeneral/DemMaxNumberEventClasses"!][!//
  [!IF "$NumOfEventClasses > $MaxNumberEventClasses"!][!//
    [!VAR "MaxNumberEventClasses" = "$NumOfEventClasses"!][!//
  [!ENDIF!][!//
  [!/* The EventClassList is filled with strings containing default values for empty
     * configurations entries */!][!//
  [!FOR "EmptyEventClassIdx" = "$NumOfEventClasses"  TO "$MaxNumberEventClasses - 1"!][!//
    [!VAR "EventClassString" = "''"!][!//
    [!/* Default values for Multi-event Triggering ('T'), AgingCycleCounterThreshold ('A'),
       * OBDAgingCycleCounterThreshold ('O'), EventFailureCycleCounterThreshold ('F'),
       * EventPriority ('P') and IndicatorClass ('I') */!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '-', 'T')"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '-', 'I')"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '1', 'A')"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '1', 'O')"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '1', 'F')"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '2', 'P')"!][!//
    [!IF "$CommonOperationCycleEnabled = 'true'"!][!//
      [!/* Default value for CommonOperationCycle */!][!//
      [!VAR "EventClassString" = "concat($EventClassString, as:name(as:modconf('Dem')[1]/DemGeneral/DemOperationCycle/eb-list::*[1]), '!')"!][!//
    [!ENDIF!][!//
    [!IF "$AgingAllowedSeperateFlag = 'true'"!][!//
      [!/* Default value for AgingAllowed */!][!//
      [!VAR "EventClassString" = "concat($EventClassString, 'TRUE', '?')"!][!//
    [!ENDIF!][!//
    [!/* Default values for MinRatioEvent and EnableConditionGroupRef */!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '0', 'M')"!][!//
    [!VAR "EventClassString" = "concat($EventClassString, '-', '&')"!][!//
    [!VAR "EventClassList" = "concat($EventClassList, $EventClassString, '#')"!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*
 * === Get SizeOfFreezeFrameClass ===
 * The Macro shall be run in contex of a DemFreezeFrameClass and it computes:
 * - the total size of all DidData assigned to this FreezeFrame and assignes
 * it to SizeOfFreezeFrameClass
 * - the number of Dids assigned to the FreezeFrame and assigns it to
 * SizeOfFreezeFrameClassNumDid.
 */!][!//
[!MACRO "GET_SIZE_OF_FREEEZE_FRAME_CLASS"!][!//
  [!VAR "SizeOfFreezeFrameClass" = "0"!][!//
  [!VAR "SizeOfFreezeFrameClassNumDid" = "0"!][!//
  [!LOOP "./DemDidClassRef/eb-list::*"!][!//
    [!LOOP "node:ref(.)/DemDidDataElementClassRef/eb-list::*"!][!//
      [!CALL "GET_SIZE_OF_DATA_ELEMENT"!][!//
      [!VAR "SizeOfFreezeFrameClass" = "$SizeOfFreezeFrameClass + $SizeOfDataElement"!][!//
    [!ENDLOOP!][!//
    [!VAR "SizeOfFreezeFrameClassNumDid" = "$SizeOfFreezeFrameClassNumDid + 1"!][!//
  [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Get NumFFRecords ===
 * This Macro shall run in context of a DemEventParameter.
 * This Macro outputs NumFFRecords in which is stored the number of freeze
 * frame records.
 */!][!//
[!MACRO "GET_NUM_FF_RECORDS"!][!//
  [!IF "as:modconf('Dem')[1]/DemGeneral/DemTypeOfFreezeFrameRecordNumeration = 'DEM_FF_RECNUM_CALCULATED'"!][!//
    [!VAR "NumFFRecords" = "DemMaxNumberFreezeFrameRecords"!][!//
  [!ELSE!][!//
    [!VAR "NumFFRecords" = "count(as:ref(DemFreezeFrameRecNumClassRef)/DemFreezeFrameRecordNumber/eb-list::*)"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Get SizeOfDataElement ===
 * The Macro shall be run in context of a DemDataElementClass and it computes:
 * - the size of the needed DataElement and assigns it to SizeOfDataElement
 */!][!//
[!MACRO "GET_SIZE_OF_DATA_ELEMENT"!][!//
  [!VAR "SizeOfDataElement" = "0"!][!//
  [!IF "node:existsAndTrue(node:ref(.)/DemDataElementDataSize)"!][!//
    [!VAR "SizeOfDataElement" = "as:ref(.)/DemDataElementDataSize"!][!//
  [!ELSEIF "node:existsAndTrue(node:ref(.)/DemDataElementArraySize)"!][!//
    [!VAR "DataTypes" = "substring-before(node:ref(.)/DemDataElementDataType, '_N')"!][!//
    [!IF "($DataTypes ='UINT16') or ($DataTypes ='SINT16')"!][!//
      [!VAR "SizeOfDataElement" = "num:integer((node:ref(.)/DemDataElementArraySize) * 2)"!][!//
    [!ELSEIF "($DataTypes ='UINT32') or ($DataTypes ='SINT32') or ($DataTypes ='FLOAT32')"!][!//
      [!VAR "SizeOfDataElement" = "num:integer((node:ref(.)/DemDataElementArraySize) * 4)"!][!//
    [!ELSE!][!//
      [!VAR "SizeOfDataElement" = "num:integer(node:ref(.)/DemDataElementArraySize)"!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!IF "node:exists(node:ref(.)/DemDataElementDataType)"!][!//
      [!VAR "DataTypes" = "(node:ref(.)/DemDataElementDataType)"!][!//
      [!IF "($DataTypes ='UINT16') or ($DataTypes ='SINT16')"!][!//
        [!VAR "SizeOfDataElement" = "num:integer(2)"!][!//
      [!ELSEIF "($DataTypes ='UINT32') or ($DataTypes ='SINT32') or ($DataTypes ='FLOAT32')"!][!//
        [!VAR "SizeOfDataElement" = "num:integer(4)"!][!//
      [!ELSE!][!//
        [!VAR "SizeOfDataElement" = "num:integer(1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Is internal data element referenced ===
 * This Macro outputs IsIntDataReferenced which indicates whether selected internal data element is used.
 */!][!//
[!MACRO "IS_INT_DATA_REFERENCED", "InternalDataElement"!][!//
[!VAR "IsIntDataReferenced" = "text:contains(util:distinct(node:refs(util:distinct(node:refs(util:distinct(node:refs(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemExtendedDataClassRef))/DemExtendedDataRecordClassRef/eb-list::*))/DemDataElementClassRef/eb-list::*))/DemInternalDataElement, $InternalDataElement)"!]
[!ENDMACRO!][!//
[!//
[!/*
 * === Get VccOcc5Used ===
 * This Macro outputs VccOcc5Used which indicates whether OCC5 is used.
 */!][!//
[!MACRO "GET_VCC_OCC5_USED"!][!//
[!INDENT "0"!][!//
  [!VAR "VccOcc5Used" = "0"!][!//
     [!/* !LINKSTO dsn.Dem.OBD.OCC5.DemInternalDataElement,1,VCC_DEM_006_Req171v1_Implicit1,1 */!][!//
     [!CALL "IS_INT_DATA_REFERENCED", "InternalDataElement" = "'DEM_OCC5'"!][!//
     [!IF "$IsIntDataReferenced"!][!//
       [!VAR "VccOcc5Used" = "1"!][!//
     [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === GET_WIDTH ===
 * returns the required bits for a variable
 */!][!//
[!MACRO "GET_WIDTH", "PNumber", "context"!][!//
[!INDENT "0"!][!//
  [!IF "$PNumber < 0"!][!//
    [!VAR "NumberOfBits" = "0"!][!//
  [!ELSEIF "$PNumber < 2"!][!//
    [!VAR "NumberOfBits" = "1"!][!//
  [!ELSEIF "$PNumber < 4"!][!//
    [!VAR "NumberOfBits" = "2"!][!//
  [!ELSEIF "$PNumber < 8"!][!//
    [!VAR "NumberOfBits" = "3"!][!//
  [!ELSEIF "$PNumber < 16"!][!//
    [!VAR "NumberOfBits" = "4"!][!//
  [!ELSEIF "$PNumber < 32"!][!//
    [!VAR "NumberOfBits" = "5"!][!//
  [!ELSEIF "$PNumber < 64"!][!//
    [!VAR "NumberOfBits" = "6"!][!//
  [!ELSEIF "$PNumber < 128"!][!//
    [!VAR "NumberOfBits" = "7"!][!//
  [!ELSEIF "$PNumber < 256"!][!//
    [!VAR "NumberOfBits" = "8"!][!//
  [!ELSEIF "$PNumber < 512"!][!//
    [!VAR "NumberOfBits" = "9"!][!//
  [!ELSEIF "$PNumber < 1024"!][!//
    [!VAR "NumberOfBits" = "10"!][!//
  [!ELSEIF "$PNumber < 2048"!][!//
    [!VAR "NumberOfBits" = "11"!][!//
  [!ELSEIF "$PNumber < 4096"!][!//
    [!VAR "NumberOfBits" = "12"!][!//
  [!ELSEIF "$PNumber < 8192"!][!//
    [!VAR "NumberOfBits" = "13"!][!//
  [!ELSEIF "$PNumber < 16384"!][!//
    [!VAR "NumberOfBits" = "14"!][!//
   [!ELSE!][!//
    [!ERROR!]Unexpected condition in Dem 'GET_WIDTH' macro. Given number is too big! Context: [!"$context"!] Number:[!"$PNumber"!][!ENDERROR!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*
 * === LOG ===
 * returns the logarithm to base of 2
 */!][!//
[!MACRO "LOG", "PNumber", "context"!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$PNumber", "context" = "$context"!][!//
  [!"num:i($NumberOfBits)"!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Indicators macros ===
 */!][!//
[!//
[!/*
 * === Indicator Classes ===
 * Returns the indicator class index of given EventId
 */!][!//
[!MACRO "GET_INDICATOR_CLASS_INDEX", "EVENT_ID"!][!//
[!INDENT "0"!][!//
  [!LOOP "text:split($EventIndicatorClassIndexList, '#')"!][!//
    [!IF "contains(., concat('!', num:i($EVENT_ID), ':'))"!][!//
      [!VAR "IndicatorClassIndex" = "text:split(., ':')[position() = 2]"!][!//
      [!IF "$IndicatorClassIndex != '-'"!][!//
        [!VAR "IndicatorClassIndex" = "num:i($IndicatorClassIndex)"!][!//
      [!ENDIF!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Number of Indicator Classes ===
 * Returns the number of indicator classes
 */!][!//
[!MACRO "GET_NUMBER_OF_INDICATOR_CLASSES"!][!//
[!INDENT "0"!][!//
  [!VAR "NumberOfIndicatorClasses" = "count(text:split($IndicatorClassList, '#'))"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Indicator Class For Event ===
 * Calculates the indicator class for an individual event
 *
 * Class entries (DemIndicatorAttributes) are separated by +
 *
 * Note: the current macro is called in a loop that iterates
 *       over all DemIndicatorAttribute nodes
 */!][!//
[!MACRO "ADD_INDICATOR_ATTRIBUTES_TO_INDICATOR_CLASS_FOR_EVENT", "INDICATOR_CLASS"!][!//
[!INDENT "0"!][!//
  [!IF "./DemIndicatorFailureCycleSource = 'DEM_FAILURE_CYCLE_INDICATOR'"!][!//
    [!VAR "FailureThreshold" = "node:value(./DemIndicatorFailureCycleCounterThreshold)"!][!//
    [!VAR "IsIndFailureCycleSrcEvent" = "'FALSE'"!][!//
  [!ELSE!][!//
    [!/* check if event is combined */!][!//
    [!IF "node:exists(../../../DemEvtCmbCommonParamMaster)"!][!//
            [!VAR "FailureThreshold" = "node:value(../../../../eb-list::*[(DemDTCClassRef=node:current()/../../../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemEventFailureCycleCounterThreshold)"!][!//
    [!ELSE!][!//
      [!VAR "FailureThreshold" = "node:value(../../DemEventFailureCycleCounterThreshold)"!][!//
    [!ENDIF!][!//
    [!VAR "IsIndFailureCycleSrcEvent" = "'TRUE'"!][!//
  [!ENDIF!][!//
  [!IF "$CommonOperationCycleEnabled = 'false'"!][!//
    [!IF "./DemIndicatorFailureCycleSource = 'DEM_FAILURE_CYCLE_INDICATOR'"!][!//
      [!VAR "FailureCycle" = "as:name(as:ref(./DemIndicatorFailureCycleRef))"!][!//
    [!ELSE!][!//
      [!/* check if event is combined */!][!//
      [!IF "node:exists(../../../DemEvtCmbCommonParamMaster)"!][!//
              [!VAR "FailureCycle" = "as:name(as:ref(../../../../eb-list::*[(DemDTCClassRef=node:current()/../../../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemEventFailureCycleRef))"!][!//
      [!ELSE!][!//
        [!VAR "FailureCycle" = "as:name(as:ref(../../DemEventFailureCycleRef))"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!VAR "HealingCycle" = "as:name(as:ref(DemIndicatorHealingCycleRef))"!][!//
    [!VAR "IndicatorClass" = "concat($INDICATOR_CLASS, ' ', as:name(as:ref(DemIndicatorRef)), ' ', DemIndicatorBehaviour, ' ', num:i($FailureThreshold), ' ', num:i(DemIndicatorHealingCycleCounterThreshold), ' ',$IsIndFailureCycleSrcEvent, ' ', $FailureCycle, ' ', $HealingCycle, '+')"!][!//
  [!ELSE!][!//
    [!/* Common operation cycle*/!][!//
    [!VAR "IndicatorClass" = "concat($INDICATOR_CLASS, ' ', as:name(as:ref(DemIndicatorRef)), ' ', DemIndicatorBehaviour, ' ', num:i($FailureThreshold), ' ', num:i(DemIndicatorHealingCycleCounterThreshold), ' ',$IsIndFailureCycleSrcEvent, '+')"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Indicator Classes ===
 * Calculates all indicator classes
 *
 * Classes are separated by #
 * Class entries (DemIndicatorAttributes) are separated by +
 */!][!//
[!/* !LINKSTO Dem.IndicatorClass.Combination,1 */!][!//
[!MACRO "CALC_INDICATOR_CLASSES"!][!//
[!INDENT "0"!][!//
  [!VAR "ClassIndex" = "0"!][!//
  [!VAR "IndicatorClassList" = "'#'"!][!//
  [!VAR "EventIndicatorClassIndexList" = "''"!][!//
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
    [!VAR "IndicatorClass" = "''"!][!//
    [!IF "($OBDonUDSCombination = 'true') and node:existsAndFalse(./DemEvtCmbCommonParamMaster)"!][!//
      [!/* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.CommonMILConfiguration,1 */!][!//
      [!/* If OBDonUDS combination is enabled and the current event is a slave event, extend indicator list with the MIL of the master event */!][!//
      [!LOOP "util:distinct(node:order(util:union((./DemEventClass/DemIndicatorAttribute/eb-list::*) , (../eb-list::*[(DemDTCClassRef = node:current()/DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemIndicatorAttribute/eb-list::*[DemIndicatorRef=as:modconf('Dem')[1]/DemGeneral/DemMILIndicatorRef])), 'as:name(as:ref(DemIndicatorRef))'))"!][!//
        [!CALL "ADD_INDICATOR_ATTRIBUTES_TO_INDICATOR_CLASS_FOR_EVENT", "INDICATOR_CLASS" = "$IndicatorClass"!][!//
      [!ENDLOOP!][!//
    [!ELSE!][!//
      [!LOOP "util:distinct(node:order(./DemEventClass/DemIndicatorAttribute/eb-list::*, 'as:name(as:ref(DemIndicatorRef))'))"!][!//
        [!CALL "ADD_INDICATOR_ATTRIBUTES_TO_INDICATOR_CLASS_FOR_EVENT", "INDICATOR_CLASS" = "$IndicatorClass"!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!/* If the event has an indicator class, add it to the list if new, otherwise identify its index in the list */!][!//
    [!IF "$IndicatorClass != ''"!][!//
      [!VAR "Index" = "0"!][!//
      [!IF "not(contains($IndicatorClassList, concat('#', $IndicatorClass, '#')))"!][!//
        [!VAR "IndicatorClassList" = "concat($IndicatorClassList, $IndicatorClass, '#')"!][!//
        [!VAR "Index" = "num:i($ClassIndex)"!][!//
        [!VAR "ClassIndex" = "$ClassIndex + 1"!][!//
      [!ELSE!][!//
        [!VAR "IndexFound" = "'false'"!][!//
        [!LOOP "text:split($IndicatorClassList, '#')"!][!//
          [!IF "string(.) != $IndicatorClass"!][!//
            [!VAR "Index" = "num:i($Index + 1)"!][!//
          [!ELSE!][!//
            [!VAR "IndexFound" = "'true'"!][!//
            [!BREAK!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$IndexFound = 'false'"!][!//
          [!VAR "Index" = "'-'"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "Index" = "'-'"!][!//
    [!ENDIF!][!//
    [!VAR "EventIndicatorClassIndexList" = "concat($EventIndicatorClassIndexList, '!', DemEventId, ':', $Index, '#')"!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Get the MIL Id when OBDonUDS combination is enabled  ===
 * Returns the MIL Indicator Id if it is configured and
 * OBDonUDS combination is enabled. Otherwise it returns 'None'.
 */!][!//
[!MACRO "GET_OBDONUDS_MIL_ID"!][!//
[!INDENT "0"!][!//
  [!VAR "OBDonUDSMILId" = "'None'"!][!//
  [!IF "($OBDonUDSCombination = 'true') and node:exists(as:modconf('Dem')[1]/DemGeneral/DemMILIndicatorRef)"!][!//
    [!VAR "OBDonUDSMILId" = "as:ref(as:modconf('Dem')[1]/DemGeneral/DemMILIndicatorRef)/DemIndicatorID"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Number of slave events referencing the MIL  ===
 * Returns the number of slave events which are referencing the MIL
 * when the OBDonUDS combination is enabled. In this case the MIL
 * is configured only for the master event and generated for all
 * events of the combination.
 */!][!//
[!MACRO "GET_NUMBER_OF_MIL_SLAVE_EVENTS"!][!//
[!INDENT "0"!][!//
  [!VAR "MILSlaveEventsNum" = "0"!][!//
  [!/* For OBDonUDS combination, if master event has MIL configured, the same MIL configuration will be generated also for the slave events */!][!//
  [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
    [!IF "node:existsAndTrue(DemEvtCmbCommonParamMaster) and (count(DemEventClass/DemIndicatorAttribute/eb-list::*[DemIndicatorRef=as:modconf('Dem')[1]/DemGeneral/DemMILIndicatorRef]) > 0)"!][!//
      [!/* Count the slave events for which a MIL link is generated (based on the master event MIL configuration) */!][!//
      [!VAR "MILSlaveEventsNum" = "count(../eb-list::*[DemDTCClassRef = node:current()/DemDTCClassRef])+ $MILSlaveEventsNum - 1"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Number of Indicator classes considering DemMaxNumberIndicatorClasses ===
 * Returns the (maximum) number of indicator classes
 */!][!//
[!MACRO "GET_NUMBER_OF_INDICATOR_CLASSES_WITH_DEMMAXNUMBERINDICATORCLASSES"!][!//
[!INDENT "0"!][!//
  [!CALL "GET_NUMBER_OF_INDICATOR_CLASSES"!][!//
  [!IF "($NumIndicator != 0) and (number($NumberOfIndicatorClasses) < DemGeneral/DemMaxNumberIndicatorClasses)"!]
    [!VAR "NumberOfIndicatorClasses" = "DemGeneral/DemMaxNumberIndicatorClasses"!]
  [!ENDIF!]
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*
 * === Number of Indicator Links ===
 * Returns the (maximum) number of indicator links
 */!][!//
[!MACRO "GET_NUMBER_OF_INDICATOR_LINKS"!][!//
[!INDENT "0"!][!//
  [!IF "$CalibrationSupport = 'true'"!][!//
    [!CALL "CALC_INDICATOR_CLASSES"!][!//
    [!CALL "GET_NUMBER_OF_INDICATOR_CLASSES"!][!//
    [!IF "$NumberOfIndicatorClasses = 0"!][!//
      [!/* If no indicator is configured in the indicator list, then DemMaxNumberIndicatorClasses will be taken into consideration
         * when calibration support is enabled. DemMaxNumberIndicatorClasses specifies how many instances of the class
         * DemIndicatorClass that should be allocated at least */!][!//
      [!VAR "NumIndicatorLinks" = "DemGeneral/DemMaxNumberIndicatorClasses"!][!//
    [!ELSE!][!//
      [!/* Subtracting of one must be done because of the class separator # at the end */!][!//
      [!VAR "NumIndicatorLinks" = "count(text:split($IndicatorClassList, '+')) - 1"!][!//
      [!IF "($NumIndicatorLinks != 0) and (number($NumberOfIndicatorClasses) < DemGeneral/DemMaxNumberIndicatorClasses)"!][!//
        [!/* Add additional requested classes (DemGeneral/DemMaxNumberIndicatorClasses) */!][!//
        [!VAR "NumIndicatorLinks" = "$NumIndicatorLinks + DemGeneral/DemMaxNumberIndicatorClasses - $NumberOfIndicatorClasses"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!VAR "NumIndicatorLinks" = "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemIndicatorAttribute/eb-list::*)"!][!//
    [!IF "($OBDonUDSCombination = 'true') and (node:exists(DemGeneral/DemMILIndicatorRef))"!][!//
      [!/* For OBDonUDS combination, if master event has MIL configured, the same MIL configuration is generated also for the slave events */!][!//
      [!CALL "GET_NUMBER_OF_MIL_SLAVE_EVENTS"!][!//
      [!VAR "NumIndicatorLinks" = "$NumIndicatorLinks + $MILSlaveEventsNum"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Create indicator link ===
 * Generates the indicator link for event
 *
 * Note: the current macro is called in a loop that iterates
 *       over all DemIndicatorAttribute nodes
 */!][!//
[!MACRO "CREATE_INDICATOR_LINK"!][!//
[!INDENT "4"!][!//
DemConf_DemEventParameter_[!"$EventName"!],
[!VAR "IndicatorBehaviour" = "../../../DemEventClass/DemIndicatorAttribute/eb-list::*[number(as:ref(DemIndicatorRef)/DemIndicatorID) = $IndicatorId]/DemIndicatorBehaviour"!][!//
[!IF "$IndicatorBehaviour = 'DEM_INDICATOR_CONTINUOUS'"!][!//
  DEM_INDICATOR_CONTINUOUS,
[!ELSEIF "$IndicatorBehaviour = 'DEM_INDICATOR_BLINKING'"!][!//
  DEM_INDICATOR_BLINKING,
[!ELSEIF "$IndicatorBehaviour = 'DEM_INDICATOR_BLINK_CONT'"!][!//
  DEM_INDICATOR_BLINK_CONT,
[!ELSEIF "$IndicatorBehaviour = 'DEM_INDICATOR_SLOW_FLASH'"!][!//
  DEM_INDICATOR_SLOW_FLASH,
[!ELSE!][!//
  DEM_INDICATOR_FAST_FLASH,
[!ENDIF!][!//
[!IF "$CommonOperationCycleEnabled = 'false'"!][!//
  [!VAR "HealingCycle" = "as:name(as:ref(./DemIndicatorHealingCycleRef))"!][!//
[!ELSE!][!//
  [!VAR "HealingCycle" = "as:name(as:ref(../../DemOperationCycleRef))"!][!//
[!ENDIF!][!//
[!VAR "HealingThreshold" = "node:value(./DemIndicatorHealingCycleCounterThreshold)"!][!//
[!VAR "HealCtr" = "0"!][!//
[!LOOP "text:split($HealList, '#')"!][!//
   [!IF "text:contains(., concat($HealingCycle,'*', $HealingThreshold))"!][!//
     [!"num:integer($HealCtr)"!]U, /* Index of Dem_HealingCycleCounterInfo[] */
     [!BREAK!][!//
   [!ENDIF!][!//
   [!VAR "HealCtr" = "$HealCtr + 1"!][!//
[!ENDLOOP!][!//
[!IF "./DemIndicatorFailureCycleSource = 'DEM_FAILURE_CYCLE_INDICATOR'"!][!//
  [!IF "$CommonOperationCycleEnabled = 'false'"!][!//
    [!VAR "FailureCycle" = "as:name(as:ref(./DemIndicatorFailureCycleRef))"!][!//
  [!ENDIF!][!//
  [!VAR "FailureThreshold" = "node:value(./DemIndicatorFailureCycleCounterThreshold)"!][!//
[!ELSE!][!//
  [!IF "$CommonOperationCycleEnabled = 'false'"!][!//
    [!/* check if event is combined */!][!//
    [!IF "node:exists(../../../DemEvtCmbCommonParamMaster)"!][!//
      [!VAR "FailureCycle" = "as:name(as:ref(../../../../eb-list::*[(DemDTCClassRef=node:current()/../../../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemEventFailureCycleRef))"!][!//
    [!ELSE!][!//
      [!VAR "FailureCycle" = "as:name(as:ref(../../DemEventFailureCycleRef))"!]
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!/* check if event is combined */!][!//
  [!IF "node:exists(../../../DemEvtCmbCommonParamMaster)"!][!//
    [!VAR "FailureThreshold" = "node:value(../../../../eb-list::*[(DemDTCClassRef=node:current()/../../../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemEventFailureCycleCounterThreshold)"!][!//
  [!ELSE!][!//
    [!VAR "FailureThreshold" = "node:value(../../DemEventFailureCycleCounterThreshold)"!]
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$CommonOperationCycleEnabled = 'true'"!][!//
  [!VAR "FailureCycle" = "as:name(as:ref(../../DemOperationCycleRef))"!][!//
[!ENDIF!][!//
[!VAR "FailCtr" = "0"!][!//
[!LOOP "text:split($FailList, '#')"!][!//
   [!IF "text:contains(., concat($FailureCycle,'*', $FailureThreshold))"!][!//
     [!"num:integer($FailCtr)"!]U, /* Index of Dem_FailureCycleCounterInfo[] */
     [!BREAK!][!//
   [!ENDIF!][!//
   [!VAR "FailCtr" = "$FailCtr + 1"!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Create MAR events list ===
 * This macro creates a string list containing the EventIds
 * of the non-combined events which are referencing the EDRN 0x93
 * Additionally, it calculates the number of MAR events and MAR DTCs
 */!][!//
[!MACRO "CREATE_MAR_EVENTS_LIST"!][!//
[!INDENT "0"!][!//
  [!VAR "MARNonCmbEventList" = "'#'"!][!//
  [!VAR "MARNonCmbEventsNum" = "0"!][!//
  [!VAR "MARNonCmbDTCsNum" = "0"!][!//
  [!IF "$EventCombinationSupport = 'DEM_EVCOMB_DISABLED'"!][!//
    [!VAR "MARCmbEventList" = "'#'"!][!//
    [!VAR "MARCmbEventsNum" = "0"!][!//
    [!VAR "MARCmbDTCsNum" = "0"!][!//
  [!ENDIF!][!//
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
    [!VAR "EventId" = "DemEventId"!][!//
    [!VAR "EventName" = "node:name(.)"!][!//
    [!IF "not(node:exists(DemEvtCmbCommonParamMaster)) and node:exists(util:distinct(node:refs(util:distinct(node:refs(DemExtendedDataClassRef))/DemExtendedDataRecordClassRef/eb-list::*))[DemExtendedDataRecordNumber = '147'])"!][!//
      [!VAR "MARNonCmbEventList" = "concat($MARNonCmbEventList, $EventId, ':', $EventName, '#')"!][!//
      [!VAR "MARNonCmbEventsNum" = "$MARNonCmbEventsNum + 1"!][!//
      [!VAR "MARNonCmbDTCsNum" = "$MARNonCmbDTCsNum + 1"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!VAR "MAREventsNum" = "$MARNonCmbEventsNum + $MARCmbEventsNum"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
 * === Packed EventDesc macros ===
 */!][!//
[!/* === Packed EventDesc macro for UDSDTCValue === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_UDS_DTC_VALUE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemUdsDTC)"!][!//
    [!WS "$Indent"!]/* UDS-DTC value */
    [!WS "$Indent"!][!"$Prefix"!][!"translate(num:inttohex(as:ref(DemDTCClassRef)/DemUdsDTC, 6), 'abcdef', 'ABCDEF')"!]U
  [!ELSE!][!/* No DTC class or no UDS-DTC configured */!][!//
    [!WS "$Indent"!]/* No UDS-DTC value */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_NO_DTC) )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for OBDDTCValue === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_OBD_DTC_VALUE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemObdDTC)"!][!//
    [!/* !LINKSTO dsn.Dem.OBD.config.ObdDTC.0002,2 */!][!//
    [!WS "$Indent"!][!"$Prefix"!][!"translate(num:inttohex(as:ref(DemDTCClassRef)/DemObdDTC, 4), 'abcdef', 'ABCDEF')"!]U /* OBD-DTC value */
  [!ELSE!][!/* No DTC class or no OBD-DTC configured */!][!//
    [!/* !LINKSTO dsn.Dem.OBD.config.ObdDTC.0003,2 */!][!//
    [!WS "$Indent"!][!"$Prefix"!](uint16)(DEM_NO_DTC) /* No OBD-DTC value */
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for 3-byte OBDDTCValue === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_3BYTE_OBD_DTC_VALUE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "$ObdUdsDtcSeparationSupport = 'true'"!][!//
    [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemDtcValue3Byte)"!][!//
      [!/* !LINKSTO dsn.Dem.OBD.config.DtcValue3Byte.0002,2 */!][!//
      [!WS "$Indent"!][!"$Prefix"!][!"translate(num:inttohex(as:ref(DemDTCClassRef)/DemDtcValue3Byte, 6), 'abcdef', 'ABCDEF')"!]U /* 3-byte OBD-DTC value */
    [!ELSE!][!/* No DTC class or no OBD-DTC configured */!][!//
      [!/* !LINKSTO dsn.Dem.OBD.config.DtcValue3Byte.0003,2 */!][!//
      [!WS "$Indent"!][!"$Prefix"!](uint32)(DEM_NO_DTC) /* No 3-byte OBD-DTC value */
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_OBD_MEMSEC_VARS"!][!//
[!INDENT "0"!][!//
  [!IF "$ObdUdsDtcSeparationSupport = 'true'"!][!//
    [!VAR "ObdTypeWidth" = "num:i(32)"!][!//
  [!ELSE!][!//
    [!VAR "ObdTypeWidth" = "num:i(8)"!][!//
  [!ENDIF!][!//
[!//
  [!VAR "ObdDTCDataSection" = "'CONST'"!][!//
  [!VAR "ObdDTCMemSection" = "'DEM_CONST'"!][!//
  [!VAR "ObdConfigDataSection" = "'CONST'"!][!//
  [!VAR "ObdConfigMemSection" = "'DEM_CONST'"!][!//
  [!IF "$CalibrationSupport = 'true'"!][!//
    [!VAR "ObdDTCDataSection" = "'CALIB'"!][!//
    [!VAR "ObdDTCMemSection" = "'DEM_CONST_CALIBRATION'"!][!//
    [!IF "($ObdUdsDtcSeparationSupport = 'true') or ($DTCClassAvailable = 'true')"!][!//
      [!VAR "ObdConfigDataSection" = "'CALIB'"!][!//
      [!VAR "ObdConfigMemSection" = "'DEM_CONST_CALIBRATION'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for OBD Readiness value === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_OBD_READINESS_VALUE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "$CalibrationWithoutEvCombSupport = 'false'"!][!//
    [!WS "$Indent"!][!"$Prefix"!]((uint[!"$ObdTypeWidth"!])(DEM_OBD_READINESS_MASK & [!"DemEventClass/DemEventOBDReadinessGroup"!]) <<[!//
    [!WS!]DEM_OBD_READINESS_OFFSET) /* OBD Readiness Group */
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for DTC class value === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_WWHOBD_DTCCLASS_VALUE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemWWHOBDDTCClass)"!][!//
    [!IF "as:ref(DemDTCClassRef)/DemWWHOBDDTCClass = 'DEM_DTC_WWHOBD_CLASS_A'"!][!//
      [!WS "$Indent"!]/* DTC Class: corresponds to DEM_DTC_WWHOBD_CLASS_A */
      [!WS "$Indent"!][!"$Prefix"!]((uint[!"$ObdTypeWidth"!])(DEM_WWHOBD_DTCCLASS_MASK & 2U) <<[!//
      [!WS!]DEM_DTCCLASS_OFFSET) /* OBD DTC class */
    [!ELSEIF "as:ref(DemDTCClassRef)/DemWWHOBDDTCClass = 'DEM_DTC_WWHOBD_CLASS_B1'"!][!//
      [!WS "$Indent"!]/* DTC Class: corresponds to DEM_DTC_WWHOBD_CLASS_B1 */
      [!WS "$Indent"!][!"$Prefix"!]((uint[!"$ObdTypeWidth"!])(DEM_WWHOBD_DTCCLASS_MASK & 3U) <<[!//
      [!WS!]DEM_DTCCLASS_OFFSET) /* OBD DTC class */
    [!ELSEIF "as:ref(DemDTCClassRef)/DemWWHOBDDTCClass = 'DEM_DTC_WWHOBD_CLASS_B2'"!][!//
      [!WS "$Indent"!]/* DTC Class: corresponds to DEM_DTC_WWHOBD_CLASS_B2 */
      [!WS "$Indent"!][!"$Prefix"!]((uint[!"$ObdTypeWidth"!])(DEM_WWHOBD_DTCCLASS_MASK & 4U) <<[!//
      [!WS!]DEM_DTCCLASS_OFFSET) /* OBD DTC class */
    [!ELSEIF "as:ref(DemDTCClassRef)/DemWWHOBDDTCClass = 'DEM_DTC_WWHOBD_CLASS_C'"!][!//
      [!WS "$Indent"!]/* DTC Class: corresponds to DEM_DTC_WWHOBD_CLASS_C */
      [!WS "$Indent"!][!"$Prefix"!]((uint[!"$ObdTypeWidth"!])(DEM_WWHOBD_DTCCLASS_MASK & 5U) <<[!//
      [!WS!]DEM_DTCCLASS_OFFSET) /* OBD DTC class */
    [!ELSE!][!//
      [!WS "$Indent"!]/* DTC Class: corresponds to DEM_DTC_WWHOBD_CLASS_NOCLASS */
      [!WS "$Indent"!][!"$Prefix"!]((uint[!"$ObdTypeWidth"!])(DEM_WWHOBD_DTCCLASS_MASK & 1U) <<[!//
      [!WS!]DEM_DTCCLASS_OFFSET) /* OBD DTC class */
    [!ENDIF!][!//
  [!ELSE!][!//
    [!WS "$Indent"!]/* DTC Class: corresponds to not configured DTC Class */
    [!WS "$Indent"!][!"$Prefix"!](DEM_SEVERITY_WWHOBD_CLASS_UNSUPPORTED) /* OBD DTC class */
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for DTCOrigin === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_DTC_ORIGIN", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!WS "$Indent"!]/* Origin of DTC */
  [!WS "$Indent"!][!"$Prefix"!]( (uint32)[!//
  [!/* exactly one event destination can be selected, ensured in xdm */!][!//
  [!IF "DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_PRIMARY_MEMORY'"!][!//
    [!WS!](DEM_DTCORIGIN_MASK & (DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U))[!//
  [!ENDIF!][!//
  [!IF "DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_SECONDARY_MEMORY'"!][!//
    [!WS!](DEM_DTCORIGIN_MASK & (DEM_DTC_ORIGIN_SECONDARY_MEMORY - 1U))[!//
  [!ENDIF!][!//
  [!IF "DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_MIRROR_MEMORY'"!][!//
    [!WS!](DEM_DTCORIGIN_MASK & (DEM_DTC_ORIGIN_MIRROR_MEMORY - 1U))[!//
  [!ENDIF!][!//
  [!WS!]<< DEM_DTCORIGIN_OFFSET )
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for DTCSeverity === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_DTC_SEVERITY", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemDTCSeverity)"!][!//
    [!IF "as:ref(DemDTCClassRef)/DemDTCSeverity = 'DEM_DTC_SEV_NO_SEVERITY'"!][!//
      [!WS "$Indent"!]/* Severity of DTC: corresponds to DEM_SEVERITY_NO_SEVERITY */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCSEVERITY_MASK & 0U) << DEM_DTCSEVERITY_OFFSET )
    [!ELSEIF "as:ref(DemDTCClassRef)/DemDTCSeverity = 'DEM_DTC_SEV_MAINTENANCE_ONLY'"!][!//
      [!WS "$Indent"!]/* Severity of DTC: corresponds to DEM_SEVERITY_MAINTENANCE_ONLY */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCSEVERITY_MASK & 1U) << DEM_DTCSEVERITY_OFFSET )
    [!ELSEIF "as:ref(DemDTCClassRef)/DemDTCSeverity = 'DEM_DTC_SEV_CHECK_AT_NEXT_HALT'"!][!//
      [!WS "$Indent"!]/* Severity of DTC: corresponds to DEM_SEVERITY_CHECK_AT_NEXT_HALT */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCSEVERITY_MASK & 2U) << DEM_DTCSEVERITY_OFFSET )
    [!ELSEIF "as:ref(DemDTCClassRef)/DemDTCSeverity = 'DEM_DTC_SEV_IMMEDIATELY'"!][!//
      [!WS "$Indent"!]/* Severity of DTC: corresponds to DEM_SEVERITY_CHECK_IMMEDIATELY */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCSEVERITY_MASK & 3U) << DEM_DTCSEVERITY_OFFSET )
[!/* ELSE-case will never appear, ensured by enumeration in xdm */!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!WS "$Indent"!]/* No severity specified for DTC */
    [!/* !LINKSTO Dem.SWS_Dem_01292,1 */!][!//
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCSEVERITY_MASK & 0U) << DEM_DTCSEVERITY_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EnablePrestorage === */!][!//
[!VAR "MaxNumPrestoredFF" = "num:integer(count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:existsAndTrue(DemEventClass/DemFFPrestorageSupported)]))"!]
[!MACRO "EVENT_DESC_BITFIELD_ENABLE_PRESTORAGE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "$MaxNumPrestoredFF = 0"!][!//
    [!WS "$Indent"!]/* Prestorage disabled */
  [!ELSE!][!//
    [!IF "node:existsAndTrue(DemEventClass/DemFFPrestorageSupported)"!][!//
      [!WS "$Indent"!]/* Prestorage enabled */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_ENABLEPRESTORAGE_MASK & 1U) << DEM_ENABLEPRESTORAGE_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]/* Prestorage disabled */
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EventKind === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_EVENT_KIND", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!WS "$Indent"!]/* Event kind is [!"substring-after(DemEventKind, 'DEM_EVENT_KIND_')"!] */
  [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTKIND_MASK & [!"DemEventKind"!]) <<[!//
  [!WS!]DEM_EVENTKIND_OFFSET )
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for IndicatorUsed === */!][!//
[!CALL "GET_NUMBER_OF_INDICATOR_LINKS"!][!//
[!MACRO "EVENT_DESC_BITFIELD_INDICATOR_USED", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "$NumIndicatorLinks = 0"!][!//
    [!WS "$Indent"!]/* No warning indicator used */
  [!ELSE!][!//
    [!IF "node:exists(DemEventClass/DemIndicatorAttribute/eb-list::*)"!][!//
      [!WS "$Indent"!]/* Warning indicator used */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_INDICATORUSED_MASK & 1U) << DEM_INDICATORUSED_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]/* No warning indicator used */
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for ImmediateStorage === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_IMMEDIATE_STORAGE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "(node:exists(DemDTCClassRef) and node:existsAndTrue(as:ref(DemDTCClassRef)/DemImmediateNvStorage)) or (node:existsAndTrue(as:modconf('Dem')[1]/DemGeneral/DemImmediateStorageInternalEvents) and not(node:exists(DemDTCClassRef)))"!][!//
    [!WS "$Indent"!]/* Immediate storage enabled */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_IMMEDIATESTORAGE_MASK & 1U) <<[!//
    [!WS!]DEM_IMMEDIATESTORAGE_OFFSET )
  [!ELSE!][!//
    [!WS "$Indent"!]/* Immediate storage disabled */
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EventSignificance === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_EVENT_SIGNIFICANCE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!WS "$Indent"!]/* DTC Significance */
  [!IF " node:exists(DemEventClass/DemEventSignificance) and DemEventClass/DemEventSignificance = 'DEM_EVENT_SIGNIFICANCE_OCCURRENCE'"!][!//
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTSIGNIFICANCE_MASK & DEM_EVENT_SIGNIFICANCE_OCCURRENCE) <<[!//
    [!WS!]DEM_EVENTSIGNIFICANCE_OFFSET )
  [!ELSEIF "node:exists(DemEventClass/DemEventSignificance) and (DemEventClass/DemEventSignificance = 'DEM_EVENT_SIGNIFICANCE_FAULT')"!][!//
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTSIGNIFICANCE_MASK & DEM_EVENT_SIGNIFICANCE_FAULT) <<[!//
    [!WS!]DEM_EVENTSIGNIFICANCE_OFFSET )
  [!ELSE!][!//
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTSIGNIFICANCE_MASK & DEM_EVENT_SIGNIFICANCE_FAULT) <<[!//
    [!WS!]DEM_EVENTSIGNIFICANCE_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for FFCLASSIDX === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_FFCLASSIDX", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemFreezeFrameClassRef)"!][!//
    [!WS "$Indent"!]/* Freeze frame class */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_FFCLASSIDX_MASK &[!//
    [!WS!]DEM_FFCLS_IDX_[!"as:name(as:ref(DemFreezeFrameClassRef))"!]) << DEM_FFCLASSIDX_OFFSET)
  [!ELSE!][!//
    [!WS "$Indent"!]/* Freeze frame class */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_FFCLASSIDX_MASK & DEM_FFCLS_NULL_IDX) << DEM_FFCLASSIDX_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for FFRECINFO === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_FFRECINFO", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemFreezeFrameClassRef)"!][!//
    [!IF "as:modconf('Dem')[1]/DemGeneral/DemTypeOfFreezeFrameRecordNumeration = 'DEM_FF_RECNUM_CALCULATED'"!][!//
      [!WS "$Indent"!]/* Maximal number of freeze frames */
      [!WS "$Indent"!]| ( (uint32)(DEM_FFRECINFO_MASK & [!"DemMaxNumberFreezeFrameRecords"!]U) << DEM_FFRECINFO_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]/* Index of freeze frame record numeration class */
      [!WS "$Indent"!]| ( (uint32)(DEM_FFRECINFO_MASK & DEM_FFRECNUMCLS_IDX_[!"as:name(as:ref(DemFreezeFrameRecNumClassRef))"!]) <<[!//
      [!WS!]DEM_FFRECINFO_OFFSET )
    [!ENDIF!][!//
  [!ELSEIF "node:exists(as:modconf('Dem')[1]/DemGeneral/DemCommonFFDataClassRef)"!][!//
    [!IF "as:modconf('Dem')[1]/DemGeneral/DemTypeOfFreezeFrameRecordNumeration = 'DEM_FF_RECNUM_CALCULATED'"!][!//
      [!WS "$Indent"!]/* Maximal number of freeze frames */
      [!WS "$Indent"!]| ( (uint32)(DEM_FFRECINFO_MASK & [!"DemMaxNumberFreezeFrameRecords"!]U) << DEM_FFRECINFO_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]/* Index of freeze frame record numeration class */
      [!WS "$Indent"!]| ( (uint32)(DEM_FFRECINFO_MASK & DEM_FFRECNUMCLS_IDX_[!"as:name(as:ref(DemFreezeFrameRecNumClassRef))"!]) <<[!//
      [!WS!]DEM_FFRECINFO_OFFSET )
    [!ENDIF!][!//
  [!ELSE!][!//
    [!WS "$Indent"!]/* No freeze frame records */
    [!IF "as:modconf('Dem')[1]/DemGeneral/DemTypeOfFreezeFrameRecordNumeration = 'DEM_FF_RECNUM_CONFIGURED' and node:exists(as:modconf('Dem')[1]/DemGeneral/DemFreezeFrameRecNumClass/eb-list::*)"!][!//
      [!WS "$Indent"!]| ( (uint32)(DEM_FFRECINFO_MASK & DEM_FFRECNUMCLS_NULL) << DEM_FFRECINFO_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]| ( (uint32)(DEM_FFRECINFO_MASK & 0U) << DEM_FFRECINFO_OFFSET )
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EDClassIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_EXTENDED_DATA_CLASS", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
[!/*  - [EDClassIdx] - */!][!//
  [!IF "node:exists(DemExtendedDataClassRef)"!][!//
    [!WS "$Indent"!]/* Extended data class */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EDCLASSIDX_MASK & DEM_EDCLS_IDX_[!"as:name(as:ref(DemExtendedDataClassRef))"!]) <<[!//
    [!WS!]DEM_EDCLASSIDX_OFFSET )
  [!ELSE!][!//
    [!WS "$Indent"!]/* No extended data class */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EDCLASSIDX_MASK & DEM_EDCLS_NULL_IDX) << DEM_EDCLASSIDX_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for OpCycleIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_OPERATION_CYCLE", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
[!/* !LINKSTO dsn.Dem.CommonOperationCycle.Dem_EventDesc,1 */!][!//
[!IF "($CalibrationWithoutEvCombSupport = 'false') or ($CommonOperationCycleEnabled = 'false')"!][!//
  [!WS "$Indent"!]/* Operation cycle Id */
  [!/* check if current event is slave, while OBDonUDS combination is enabled or the associated master event is storing DEM_FAILED_CYCLES */!][!//
  [!IF "(node:existsAndFalse(../DemEvtCmbCommonParamMaster)) and (($OBDonUDSCombination = 'true') or (count(util:distinct(node:refs(util:distinct(node:refs(util:distinct(node:refs(as:modconf('Dem')[1]/DemConfigSet/eb-list::*[1]/DemEventParameter/eb-list::*[(DemDTCClassRef = node:current()/../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemExtendedDataClassRef))/DemExtendedDataRecordClassRef/eb-list::*))/DemDataElementClassRef/eb-list::*))/eb-list::*[. = 'DEM_FAILED_CYCLES']) > 0))"!][!//
    [!/* get the operation cycle of the master event of the combination */!][!//
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_OPCYCLEIDX_MASK &[!//
    [!"as:name(as:ref(../../eb-list::*[(DemDTCClassRef=node:current()/../DemDTCClassRef) and (node:existsAndTrue(./DemEvtCmbCommonParamMaster))]/DemEventClass/DemOperationCycleRef))"!]) <<[!//
    [!WS!]DEM_OPCYCLEIDX_OFFSET )
  [!ELSE!][!//
  [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_OPCYCLEIDX_MASK & [!"as:name(as:ref(DemEventClass/DemOperationCycleRef))"!]) <<[!//
    [!WS!]DEM_OPCYCLEIDX_OFFSET )
  [!ENDIF!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for DTCConfigIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_DTC_CONFIG_IDX", "Indent", "Prefix"!][!//
[!IF "($CalEventDescArray = 'Dem_EventDTCConfIdx') or ($CalDtcConfigIdxOffset != 0)"!][!//
  [!INDENT "0"!][!//
  [!VAR "DemDTCClassRefName" = "0"!][!//
  [!VAR "DemDTCCounter" = "0"!][!//
  [!IF "node:exists(DemDTCClassRef)"!][!//
    [!VAR "DemDTCClassRefName" = "as:name(as:ref(DemDTCClassRef))"!][!//
    [!LOOP "text:split($DemDTCClassList, '#')"!][!//
      [!IF "string($DemDTCClassRefName) = ."!][!//
        [!WS "$Indent"!]/* Index of DTC Class */
        [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCCONFIDX_MASK & [!"num:i($DemDTCCounter)"!]U) << DEM_DTCCONFIDX_OFFSET )
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "DemDTCCounter" = "$DemDTCCounter + 1"!][!//
    [!ENDLOOP!][!//
  [!ELSE!][!//
    [!VAR "DemDTCClassRefName" = "node:name(.)"!][!//
    [!LOOP "text:split($DemDTCClassList, '#')"!][!//
      [!IF "string($DemDTCClassRefName) = ."!][!//
        [!WS "$Indent"!]/* Index of dummy DTC Class */
        [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCCONFIDX_MASK & [!"num:i($DemDTCCounter)"!]U) << DEM_DTCCONFIDX_OFFSET )
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "DemDTCCounter" = "$DemDTCCounter + 1"!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!ENDINDENT!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for AgingCounterThreshold === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_AGING_CTR_THRESHOLD", "Indent", "Prefix"!][!//
[!IF "$CalibrationWithoutEvCombSupport = 'false'"!][!//
  [!INDENT "0"!][!//
    [!IF "node:existsAndTrue(DemEventClass/DemAgingAllowed)"!][!//
      [!WS "$Indent"!]/* Limit of DTC aging cycles */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_AGINGCTRTHRESHOLD_MASK & [!"DemEventClass/DemAgingCycleCounterThreshold"!]U) <<[!//
      [!WS!]DEM_AGINGCTRTHRESHOLD_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]/* Aging disabled (AgingCycles = 0) */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)0U << DEM_AGINGCTRTHRESHOLD_OFFSET )
    [!ENDIF!][!//
  [!ENDINDENT!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for DTCGroup === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_DTC_GROUP", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
[!/*  find group to which the configured DTC belongs to */!][!//
  [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemUdsDTC)"!][!//
    [!VAR "GroupName" = "'ALL_DTC'"!][!//
    [!IF "(node:exists(as:modconf('Dem')[1]/DemGeneral/DemGroupOfDTC/eb-list::*[(as:name(.) != 'DEM_DTC_GROUP_EMISSION_REL_DTCS') and (DemGroupDTCs < as:ref(node:current()/DemDTCClassRef)/DemUdsDTC)]))"!][!//
      [!VAR "GroupName" = "substring(as:name(util:distinct(node:order(as:modconf('Dem')[1]/DemGeneral/DemGroupOfDTC/eb-list::*[(DemGroupDTCs < as:ref(node:current()/DemDTCClassRef)/DemUdsDTC)], './DemGroupDTCs'))[last()]), 15)"!][!//
    [!ENDIF!][!//
    [!WS "$Indent"!]/* Group of DTC */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCGROUP_MASK & DEM_DTCGRP_IDX_[!"$GroupName"!]) << DEM_DTCGROUP_OFFSET )
  [!ELSE!][!/* No UDS DTC configured */!][!//
    [!WS "$Indent"!]/* No group of DTC */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCGROUP_MASK & DEM_DTCGRP_IDX_NO_DTC) << DEM_DTCGROUP_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EventClass === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_EVENT_CLASS", "Indent", "Prefix"!][!//
[!IF "$CalibrationWithoutEvCombSupport = 'true'"!][!//
  [!INDENT "0"!][!//
  [!/*  - Create current event class string - */!][!//
    [!VAR "EventClassIdx" = "0"!][!//
    [!SELECT "DemEventClass"!][!//
      [!CALL "GET_EVENT_CLASS_STRING"!][!//
    [!ENDSELECT!][!//
    [!LOOP "text:split($EventClassList, '#')"!][!//
      [!IF "string(.) = $EventClassString"!][!//
        [!BREAK!][!//
      [!ELSE!][!//
        [!VAR "EventClassIdx" = "$EventClassIdx + 1"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!WS "$Indent"!]/* Event Class Description Index */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTCLASSDESCIDX_MASK & [!"num:integer($EventClassIdx)"!]U) <<[!//
    [!WS!]DEM_EVENTCLASSDESCIDX_OFFSET )
  [!ENDINDENT!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EnCondGrpIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_ENABLE_CONDITION_GROUP_IDX", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!VAR "EnCondGrpCtrIdx" = "0"!][!//
  [!IF "node:exists(DemEventClass/DemEnableConditionGroupRef)"!][!//
    [!LOOP "DemEventClass/DemEnableConditionGroupRef"!][!//
      [!VAR "EnCondGrpCtrIdx" = "node:pos(as:ref(.))"!][!//
    [!ENDLOOP!][!//
    [!WS "$Indent"!]/* Index of enable condition group */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_ENCONDGRPIDX_MASK & [!"substring(concat(string(num:integer($EnCondGrpCtrIdx)), 'U '), 1, 6)"!]) <<[!//
    [!WS!]DEM_ENCONDGRPIDX_OFFSET )
  [!ELSE!][!//
    [!WS "$Indent"!]/* No enable condition group referenced */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_ENCONDGRPIDX_MASK & DEM_ENCONDITIONGROUP_UNUSED) <<[!//
    [!WS!]DEM_ENCONDGRPIDX_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for MultiEventTriggeringClassIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_MULTI_EVENT_TRIGGERING_IDX", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!CALL "GET_MULTI_EVENT_TRIGGERING_INDEX", "EVENT_ID" = "./DemEventId"!][!//
  [!IF "$MultiEventTriggeringClassIdx != $NumMultiEventTriggering"!][!//
    [!WS "$Indent"!]/* Index of multi event triggering configuration */
    [!WS "$Indent"!][!"$Prefix"!]( (uint16)(DEM_MULTIEVENTTRIGGERINGIDX_MASK & [!"num:i($MultiEventTriggeringClassIdx)"!]U) <<[!//
    [!WS!]DEM_MULTIEVENTTRIGGERINGIDX_OFFSET )
  [!ELSE!][!//
    [!WS "$Indent"!]/* No multi event triggering configuration referenced */
    [!WS "$Indent"!][!"$Prefix"!]( (uint16)(DEM_MULTIEVENTTRIGGERINGIDX_MASK & DEM_MULTIEVENTTRIGGERINGIDX_UNUSED) <<[!//
    [!WS!]DEM_MULTIEVENTTRIGGERINGIDX_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EventFailureClassIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_EVENT_FAILURE_CLASS_IDX", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!VAR "EvFailureFound" = "0"!][!//
[!/* check if event is combined */!][!//
  [!IF "node:exists(DemEvtCmbCommonParamMaster)"!][!//
    [!SELECT "as:modconf('Dem')[1]/DemConfigSet/eb-list::*[1]/DemEventParameter/eb-list::*[DemDTCClassRef = node:current()/DemDTCClassRef and node:existsAndTrue(DemEvtCmbCommonParamMaster)]/DemEventClass"!][!//
      [!IF "node:exists(./DemEventFailureCycleCounterThreshold)"!][!//
        [!VAR "EventFailureCycle" = "as:name(as:ref(./DemEventFailureCycleRef))"!][!//
        [!VAR "EventFailureThreshold" = "node:value(./DemEventFailureCycleCounterThreshold)"!][!//
        [!VAR "EvFailureFound" = "1"!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ELSE!][!//
    [!IF "node:exists(DemEventClass/DemEventFailureCycleCounterThreshold)"!][!//
      [!IF "$CommonOperationCycleEnabled = 'true'"!][!//
        [!VAR "EventFailureCycle" = "as:name(as:ref(DemEventClass/DemOperationCycleRef))"!][!//
      [!ELSE!][!//
        [!VAR "EventFailureCycle" = "as:name(as:ref(DemEventClass/DemEventFailureCycleRef))"!][!//
      [!ENDIF!][!//
      [!VAR "EventFailureThreshold" = "node:value(DemEventClass/DemEventFailureCycleCounterThreshold)"!][!//
      [!VAR "EvFailureFound" = "1"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!IF "$EvFailureFound = 1"!][!//
    [!VAR "FailureClassIdx" = "0"!][!//
[!/* search list of failure cycle configurations for existing combination */!][!//
    [!LOOP "text:split($FailureCycleCfgList, '#')"!][!//
      [!IF ". = concat($EventFailureCycle, '*', $EventFailureThreshold)"!][!//
[!/* failure cycle configuration item found, stop searching */!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "FailureClassIdx" = "num:i($FailureClassIdx) + 1"!][!//
    [!ENDLOOP!][!//
    [!WS "$Indent"!]/* Index of failure class configuration */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTFAILURECLASSIDX_MASK & [!"num:i($FailureClassIdx)"!]U) <<[!//
    [!WS!]DEM_EVENTFAILURECLASSIDX_OFFSET )
  [!ELSE!][!//
    [!WS "$Indent"!]/* Fault confirmation not configured */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_EVENTFAILURECLASSIDX_MASK & DEM_NO_FAULT_CONFIRMATION) <<[!//
    [!WS!]DEM_EVENTFAILURECLASSIDX_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for EventPriority === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_EVENT_PRIORITY", "Indent", "Prefix"!][!//
[!IF "$CalibrationWithoutEvCombSupport = 'false'"!][!//
  [!INDENT "0"!][!//
    [!IF "node:existsAndTrue(as:modconf('Dem')[1]/DemGeneral/DemEventDisplacementSupport)"!][!//
      [!/*    configured priority value [1..255] */!][!//
      [!VAR "PriorityValue" = "DemEventClass/DemEventPriority"!][!//
      [!/*    get index of configured priority from priority list */!][!//
      [!CALL "GET_INTERNAL_PRIORITY_IDX", "Prio" = "$PriorityValue"!][!//
      [!WS "$Indent"!]/* Internal event priority (0 = most important) */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_PRIORITY_MASK & [!"num:integer($PriorityValueIdx)"!]U) <<[!//
      [!WS!]DEM_PRIORITY_OFFSET )
    [!ELSE!][!//
      [!WS "$Indent"!]/* No event priority used as event displacement is disabled */
      [!WS "$Indent"!][!"$Prefix"!]( (uint32)0U << DEM_PRIORITY_OFFSET )
    [!ENDIF!][!//
  [!ENDINDENT!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!VAR "DebounceCtrsInitialized"  = "'false'"!][!//
[!/* === Packed EventDesc macro for DebounceAlgo & DebounceIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_DEBOUNCE_ALGORITHM", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "$DebounceCtrsInitialized = 'false'"!][!//
    [!/* the indexes must be initialized only once and then the macro can be re-called for any number of times */!][!//
    [!/* initialize counting variables */!][!//
    [!VAR "DebounceCtrIdx"  = "0"!][!//
    [!VAR "DebounceTimeIdx" = "0"!][!//
    [!VAR "DebounceFrqIdx"  = "0"!][!//
    [!VAR "DebounceCtrsInitialized"  = "'true'"!][!//
  [!ENDIF!][!//
  [!IF "DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceCounterBased'"!][!//
    [!WS "$Indent"!]/* Counter based event debouncing */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DEBOUNCEALGO_MASK & ((uint32)DEM_DEBOUNCE_COUNTERBASED)) << DEM_DEBOUNCEALGO_OFFSET )
    [!WS "$Indent"!]/* Index of debouncing configuration/status */
    [!WS "$Indent"!]| ( (uint32)(DEM_DEBOUNCEIDX_MASK & [!"num:i($DebounceCtrIdx)"!]U) << DEM_DEBOUNCEIDX_OFFSET )
    [!VAR "DebounceCtrIdx" = "$DebounceCtrIdx + 1"!][!//
  [!ELSEIF "DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase'"!][!//
    [!WS "$Indent"!]/* Time based event debouncing */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DEBOUNCEALGO_MASK & ((uint32)DEM_DEBOUNCE_TIMEBASED)) << DEM_DEBOUNCEALGO_OFFSET )
    [!WS "$Indent"!]/* Index of debouncing configuration/status */
    [!WS "$Indent"!]| ( (uint32)(DEM_DEBOUNCEIDX_MASK & [!"num:i($DebounceTimeIdx)"!]U) << DEM_DEBOUNCEIDX_OFFSET )
    [!VAR "DebounceTimeIdx" = "$DebounceTimeIdx + 1"!][!//
  [!ELSEIF "DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceFrequencyBased'"!][!//
    [!WS "$Indent"!]/* Frequency based event debouncing */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DEBOUNCEALGO_MASK & ((uint32)DEM_DEBOUNCE_FREQUENCYBASED)) << DEM_DEBOUNCEALGO_OFFSET )
    [!WS "$Indent"!]/* Index of debouncing configuration/status */
    [!WS "$Indent"!]| ( (uint32)(DEM_DEBOUNCEIDX_MASK & [!"num:i($DebounceFrqIdx)"!]U) << DEM_DEBOUNCEIDX_OFFSET )
    [!VAR "DebounceFrqIdx" = "$DebounceFrqIdx + 1"!][!//
  [!ELSE!][!/* monitor internal debouncing */!][!//
    [!WS "$Indent"!]/* Monitor internal event debouncing */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DEBOUNCEALGO_MASK & ((uint32)DEM_DEBOUNCE_MONITOR)) << DEM_DEBOUNCEALGO_OFFSET )
    [!WS "$Indent"!]/* Index not used */
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for DTCFuncUnit === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_FUNCTIONAL_UNIT", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(DemDTCClassRef)"!][!//
    [!WS "$Indent"!]/* DTC Functional Unit */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCFUNCTIONALUNIT_MASK & [!"as:ref(DemDTCClassRef)/DemDTCFunctionalUnit"!]U) <<[!//
    [!WS!]DEM_DTCFUNCTIONALUNIT_OFFSET )
  [!ELSE!][!/* No DTC class configured */!][!//
    [!WS "$Indent"!]/* No DTC Functional Unit */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_DTCFUNCTIONALUNIT_MASK & DEM_NO_DTC_FUNCTIONAL_UNIT) << DEM_DTCFUNCTIONALUNIT_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Packed EventDesc macro for AgingCycleIdx === */!][!//
[!MACRO "EVENT_DESC_BITFIELD_AGING_CYCLE_ID", "Indent", "Prefix"!][!//
[!INDENT "0"!][!//
  [!IF "($CommonOperationCycleEnabled = 'false') and node:exists(DemEventClass/DemAgingCycleRef) and ( as:name(as:ref(DemEventClass/DemOperationCycleRef)) != as:name(as:ref(DemEventClass/DemAgingCycleRef)) )"!][!//
    [!WS "$Indent"!]/* Aging cycle Id */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_AGINGCYCLEIDX_MASK & [!"as:name(as:ref(DemEventClass/DemAgingCycleRef))"!]) <<[!//
    [!WS!]DEM_AGINGCYCLEIDX_OFFSET )
  [!ELSE!][!/* No (different/separate) aging cycle reference configured */!][!//
    [!WS "$Indent"!]/* No aging cycle Id */
    [!WS "$Indent"!][!"$Prefix"!]( (uint32)(DEM_AGINGCYCLEIDX_MASK & DEM_NUM_AGINGCYCLES) << DEM_AGINGCYCLEIDX_OFFSET )
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_UDS_DTC_VALUE"!][!//
  [!VAR "CalUdsDtcValueWidth" = "24"!][!//
  [!VAR "CalUdsDtcValueOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalUdsDtcValueConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalUdsDtcValueWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_DTC_ORIGIN"!][!//
  [!VAR "CalDtcOriginWidth" = "2"!][!//
  [!VAR "CalDtcOriginOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalDtcOriginConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalDtcOriginWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_DTC_SEVERITY"!][!//
  [!VAR "CalDtcSeverityWidth" = "2"!][!//
  [!VAR "CalDtcSeverityOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalDtcSeverityConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalDtcSeverityWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_ENABLE_PRESTORAGE"!][!//
  [!VAR "CalEnablePrestorageOffset" = "$CalEventDescOffset"!][!//
  [!IF "$MaxNumPrestoredFF > 0"!][!//
    [!VAR "CalEnablePrestorageWidth" = "1"!][!//
    [!VAR "CalEnablePrestorageConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEnablePrestorageWidth"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_EVENT_KIND"!][!//
  [!VAR "CalEventKindWidth" = "1"!][!//
  [!VAR "CalEventKindOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalEventKindConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEventKindWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_INDICATOR_USED"!][!//
  [!VAR "CalIndicatorUsedOffset" = "$CalEventDescOffset"!][!//
  [!IF "$NumIndicatorLinks > 0"!][!//
    [!VAR "CalIndicatorUsedWidth" = "1"!][!//
    [!VAR "CalIndicatorUsedConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalIndicatorUsedWidth"!][!//
  [!ELSE!][!//
    [!VAR "CalIndicatorUsedWidth" = "0"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_IMMEDIATE_STORAGE"!][!//
  [!/* !LINKSTO Dem.ImmediateStorage.InternalEvents,1 */!][!//
  [!VAR "CalImmediateStorageWidth" = "1"!][!//
  [!VAR "CalImmediateStorageOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalImmediateStorageConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalImmediateStorageWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_EVENT_SIGNIFICANCE"!][!//
  [!VAR "CalEventSignificanceWidth" = "1"!][!//
  [!VAR "CalEventSignificanceOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalEventSignificanceConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEventSignificanceWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_FFCLASSIDX"!][!//
  [!CALL "GET_WIDTH", "PNumber" = "count(DemGeneral/DemFreezeFrameClass/eb-list::*)", "context" = "'FFClassIdx'"!][!//
  [!VAR "CalFFClassIdxWidth" = "$NumberOfBits"!][!//
  [!VAR "CalFFClassIdxOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalFfclassidxConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalFFClassIdxWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_FFRECINFO"!][!//
  [!VAR "CalEvDescFFRecInfo" = "0"!][!//
  [!IF "DemGeneral/DemTypeOfFreezeFrameRecordNumeration = 'DEM_FF_RECNUM_CALCULATED'"!][!//
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
      [!IF "number($CalEvDescFFRecInfo) < DemMaxNumberFreezeFrameRecords"!][!//
        [!VAR "CalEvDescFFRecInfo" = "DemMaxNumberFreezeFrameRecords"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!/* calculate the FFRecInfo to include the NULL class as well */!][!//
    [!VAR "CalEvDescFFRecInfo" = "$CalEvDescFFRecInfo + 1"!][!//
  [!ELSE!][!//
    [!VAR "CalEvDescFFRecInfo" = "count(DemGeneral/DemFreezeFrameRecNumClass/eb-list::*)"!][!//
  [!ENDIF!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescFFRecInfo", "context" = "'CalEvDescFFRecInfo'"!][!//
  [!VAR "CalFfrecinfoWidth" = "$NumberOfBits"!][!//
  [!VAR "CalFfrecinfoOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalFfrecinfoConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalFfrecinfoWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_EXTENDED_DATA_CLASS"!][!//
  [!CALL "GET_WIDTH", "PNumber" = "count(DemGeneral/DemExtendedDataClass/eb-list::*)", "context" = "'DemExtendedDataClass'"!][!//
  [!VAR "CalExtendedDataClassWidth" = "$NumberOfBits"!][!//
  [!VAR "CalExtendedDataClassOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalExtendedDataClassConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalExtendedDataClassWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_OPERATION_CYCLE"!][!//
  [!VAR "CalOperationCycleOffset" = "$CalEventDescOffset"!][!//
  [!IF "($CommonOperationCycleEnabled = 'false') or ($CalibrationWithoutEvCombSupport = 'false')"!][!//
    [!VAR "CalEvDescOpCalEvDescCycNameList" = "'#'"!][!//
    [!VAR "CalEvDescOpCycCtr"  = "count(DemGeneral/DemOperationCycle/eb-list::*)"!][!//
    [!CALL "GET_WIDTH", "PNumber" = "num:integer($CalEvDescOpCycCtr)", "context" = "'CalEvDescOpCycCtr'"!][!//
    [!VAR "CalOperationCycleWidth" = "$NumberOfBits"!][!//
    [!VAR "CalOperationCycleConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalOperationCycleWidth"!][!//
  [!ELSE!][!//
    [!VAR "CalOperationCycleWidth" = "0"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_AGING_CTR_THRESHOLD"!][!//
  [!VAR "CalAgingCtrThresholdOffset" = "$CalEventDescOffset"!][!//
  [!IF "$CalibrationWithoutEvCombSupport = 'false'"!][!//
    [!VAR "CalEvDescMaxAgeCyc" = "0"!][!//
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass[node:existsAndTrue(DemAgingAllowed)]"!][!//
      [!IF "number($CalEvDescMaxAgeCyc) < DemAgingCycleCounterThreshold"!][!//
        [!VAR "CalEvDescMaxAgeCyc" = "DemAgingCycleCounterThreshold"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescMaxAgeCyc", "context" = "'CalEvDescMaxAgeCyc'"!][!//
    [!VAR "CalAgingCtrThresholdWidth" = "$NumberOfBits"!][!//
    [!VAR "CalAgingCtrThresholdConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalAgingCtrThresholdWidth"!][!//
  [!ELSE!][!//
    [!VAR "CalAgingCtrThresholdWidth" = "0"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_DTC_GROUP"!][!//
  [!VAR "CalDtcGroupWidth" = "5"!][!//
  [!VAR "CalDtcGroupOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalDtcGroupConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalDtcGroupWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_EVENT_CLASS"!][!//
  [!IF "$CalibrationWithoutEvCombSupport = 'true'"!][!//
    [!CALL "CREATE_EVENT_CLASS_LIST"!][!//
    [!VAR "CalEvDescNumberOfEventClasses" = "count(text:split($EventClassList, '#'))"!][!//
    [!VAR "CalEvDescMaxNumberEventClasses" = "/AUTOSAR/TOP-LEVEL-PACKAGES/Dem/ELEMENTS/Dem/DemGeneral/DemMaxNumberEventClasses"!][!//
    [!IF "$CalEvDescNumberOfEventClasses < $CalEvDescMaxNumberEventClasses"!][!//
      [!VAR "CalEvDescNumberOfEventClasses" = "$CalEvDescMaxNumberEventClasses"!][!//
    [!ENDIF!][!//
    [!CALL "GET_WIDTH", "PNumber" = "(num:integer($CalEvDescNumberOfEventClasses) - 1)", "context" = "'CalEvDescNumberOfEventClasses'"!][!//
    [!/* Special handling for EVENT_CLASS: */!][!//
    [!VAR "CalEventClassWidth" = "$NumberOfBits"!][!//
    [!IF "$CalEventDescOffset + $CalEventClassWidth <= $CalEventDescSubElemSize"!][!//
      [!/* Only if fits in bitpacking structure.. */!][!//
      [!VAR "CalEventClassOffset" = "$CalEventDescOffset"!][!//
      [!VAR "CalEventClassConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
      [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEventClassWidth"!][!//
    [!ELSE!][!//
      [!/* .. else remove it from */!][!//
      [!VAR "CalEventClassOffset" = "255"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_ENABLE_CONDITION_GROUP_IDX"!][!//
[!VAR "CalEnableConditionGroupIdxOffset" = "$CalEventDescOffset"!][!//
[!IF "$CalibrationWithoutEvCombSupport = 'false'"!][!//
  [!VAR "CalEvDescNumEnCondGrp" = "num:i(count(DemGeneral/DemEnableConditionGroup/eb-list::*))"!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescNumEnCondGrp", "context" = "'CalEvDescNumEnCondGrp'"!][!//
  [!VAR "CalEnableConditionGroupIdxWidth" = "$NumberOfBits"!][!//
  [!VAR "CalEnableConditionGroupIdxConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEnableConditionGroupIdxWidth"!][!//
[!ELSE!][!//
    [!VAR "CalEnableConditionGroupIdxWidth" = "0"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_EVENT_FAILURE_CLASS_IDX"!][!//
  [!CALL "CREATE_FAILURE_COUNTER_CYCLE_LIST"!][!//
  [!VAR "CalEvDescEventFailureClassIdx" = "$EventFailureClassIdx"!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescEventFailureClassIdx", "context" = "'CalEvDescEventFailureClassIdx'"!][!//
  [!VAR "CalEventFailureClassIdxWidth" = "$NumberOfBits"!][!//
  [!VAR "CalEventFailureClassIdxOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalEventFailureClassIdxConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEventFailureClassIdxWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_EVENT_PRIORITY"!][!//
  [!VAR "CalEventPriorityOffset" = "$CalEventDescOffset"!][!//
  [!IF "$CalibrationWithoutEvCombSupport = 'false'"!][!//
    [!VAR "CalEvDescNumPriorities" = "0"!][!//
    [!IF "(node:existsAndTrue(DemGeneral/DemEventDisplacementSupport)) or (node:exists(as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemPidClass/eb-list::*))"!][!//
      [!CALL "GET_NUMBER_OF_EVENT_PRIORITIES"!]
      [!VAR "CalEvDescNumPriorities" = "$NumberOfPriorities"!][!//
    [!ENDIF!][!//
    [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescNumPriorities - 1", "context" = "'CalEvDescNumPriorities'"!][!//
    [!VAR "CalEventPriorityWidth" = "$NumberOfBits"!][!//
    [!VAR "CalEventPriorityConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalEventPriorityWidth"!][!//
  [!ELSE!][!//
    [!VAR "CalEventPriorityWidth" = "0"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_DEBOUNCE_ALGORITHM"!][!//
  [!/* Calculation for TYPE of debouncing algorithm */!][!//
  [!VAR "CalDebounceAlgorithmWidth" ="2"!][!//
  [!VAR "CalDebounceAlgorithmOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalDebounceAlgorithmConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalDebounceAlgorithmWidth"!][!//
  [!/* Calculation for class INDEX of the debouncing algorithm */!][!//
  [!VAR "CalEvDescMaxDebIdx" = "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceCounterBased'])"!][!//
  [!VAR "CalEvDescMaxTimeDebIdx" = "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase'])"!][!//
  [!IF "$CalEvDescMaxDebIdx < $CalEvDescMaxTimeDebIdx"!][!//
    [!VAR "CalEvDescMaxDebIdx" = "$CalEvDescMaxTimeDebIdx"!][!//
  [!ENDIF!][!//
  [!VAR "CalEvDescMaxFreqDebIdx" = "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceFrequencyBased'])"!][!//
  [!IF "$CalEvDescMaxDebIdx < $CalEvDescMaxFreqDebIdx"!][!//
    [!VAR "CalEvDescMaxDebIdx" = "$CalEvDescMaxFreqDebIdx"!][!//
  [!ENDIF!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescMaxDebIdx", "context" = "'CalEvDescMaxDebIdx'"!][!//
  [!VAR "CalDebounceAlgorithmIdxWidth" = "$NumberOfBits"!][!//
  [!VAR "CalDebounceAlgorithmIdxOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalDebounceAlgorithmIdxConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalDebounceAlgorithmIdxWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_FUNCTIONAL_UNIT"!][!//
  [!VAR "CalEvDescMaxDTCFuncUnit" = "0"!][!//
  [!LOOP "DemConfigSet/eb-list::*/DemDTCClass/eb-list::*"!][!//
    [!IF "num:i($CalEvDescMaxDTCFuncUnit) < DemDTCFunctionalUnit"!][!//
      [!VAR "CalEvDescMaxDTCFuncUnit" = "DemDTCFunctionalUnit"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescMaxDTCFuncUnit", "context" = "'CalEvDescMaxDTCFuncUnit'"!][!//
  [!VAR "CalFunctionalUnitWidth" = "$NumberOfBits"!][!//
  [!VAR "CalFunctionalUnitOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalFunctionalUnitConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalFunctionalUnitWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_AGING_CYCLE_ID"!][!//
  [!VAR "CalAgingCycleIdOffset" = "$CalEventDescOffset"!][!//
  [!IF "$CommonOperationCycleEnabled = 'false'"!][!//
    [!VAR "CalEvDescCycNameList" = "'#'"!][!//
    [!/* additional value "not configured" is added */!][!//
    [!VAR "CalEvDescAgeCycCtr" = "count(DemGeneral/DemAgingCycle/eb-list::*) + 1"!][!//
    [!CALL "GET_WIDTH", "PNumber" = "$CalEvDescAgeCycCtr", "context" = "'CalEvDescAgeCycCtr'"!][!//
    [!VAR "CalAgingCycleIdWidth" = "$NumberOfBits"!][!//
    [!VAR "CalAgingCycleIdConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalAgingCycleIdWidth"!][!//
  [!ELSE!][!//
    [!VAR "CalAgingCycleIdWidth" = "0"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_DTC_CONFIG_IDX"!][!//
  [!/* Offset calculation Dem_EventDesc depends on DemNbOfDTCClasses, generated
     * by the CREATE_DTCCLASS_LIST_FROM_EVENTS macro */!][!//
  [!CALL "GET_WIDTH", "PNumber" = "$DemNbOfDTCClasses", "context" = "'CalEvDescDTCConfIdxWidth'"!][!//
  [!VAR "CalDtcConfigIdxWidth" = "$NumberOfBits"!][!//
  [!VAR "CalDtcConfigIdxOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalDtcConfigIdxConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalDtcConfigIdxWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_MULTI_EVENT_TRIGGERING_IDX"!][!//
  [!VAR "CalMultiEventTriggeringIdxWidth" = "16"!][!//
  [!VAR "CalMultiEventTriggeringIdxOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalMultiEventTriggeringIdxConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalMultiEventTriggeringIdxWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_OBD_DTC_VALUE"!][!//
  [!VAR "CalObdDtcValueWidth" = "16"!][!//
  [!VAR "CalObdDtcValueOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalObdDtcValueConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalObdDtcValueWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_3BYTE_OBD_DTC_VALUE"!][!//
  [!VAR "Cal3ByteObdDtcValueWidth" = "24"!][!//
  [!VAR "Cal3ByteObdDtcValueOffset" = "$CalEventDescOffset"!][!//
  [!VAR "Cal3ByteObdDtcValueConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $Cal3ByteObdDtcValueWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_OBD_READINESS_VALUE"!][!//
  [!VAR "CalObdReadinessValueWidth" = "5"!][!//
  [!VAR "CalObdReadinessValueOffset" = "$CalEventDescOffset"!][!//
  [!VAR "CalObdReadinessValueConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
  [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalObdReadinessValueWidth"!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "CALC_EVENT_DESC_WWHOBD_DTCCLASS_VALUE"!][!//
  [!IF "$DTCClassAvailable = 'true'"!][!//
    [!VAR "CalWWHObdDtcClassValueWidth" = "3"!][!//
    [!VAR "CalWWHObdDtcClassValueOffset" = "$CalEventDescOffset"!][!//
    [!VAR "CalWWHObdDtcClassValueConf" = "concat($CalEventDescArray, '[', $CalEventDescIndexPrefix, '(EventId)]', $CalEventDescSubElem)"!][!//
    [!VAR "CalEventDescOffset" = "$CalEventDescOffset + $CalWWHObdDtcClassValueWidth"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!// Macro for the calculation of bitfields
[!MACRO "CALC_DESCRIPTION", "Array", "CalEventDescIndexPrefix" = "''"!][!//
[!INDENT "0"!][!//
  [!VAR "Array" = "normalize-space($Array)"!][!//
  [!VAR "CalEventDescArray" = "substring-before($Array, ' ')"!][!//
  [!VAR "Array" = "substring-after($Array, ' ')"!][!//
  [!VAR "NumStructs" = "num:integer(count(text:split($Array, '#SM#')))"!][!//
  [!FOR "StructIndex" = "1" TO "$NumStructs"!][!//
    [!VAR "StructMember" = "text:split($Array, '#SM#')[position() = $StructIndex]"!][!//
    [!VAR "StructMember" = "normalize-space($StructMember)"!][!//
    [!VAR "CalEventDescSubElem" = "substring-before($StructMember, ' ')"!][!//
    [!IF "$CalEventDescSubElem = '#NONE#'"!][!//
      [!VAR "CalEventDescSubElem" = "''"!][!//
    [!ELSE!][!//
      [!VAR "CalEventDescSubElem" = "concat('.', $CalEventDescSubElem)"!][!//
    [!ENDIF!][!//
    [!VAR "StructMember" = "substring-after($StructMember, ' ')"!][!//
    [!VAR "CalEventDescSubElemSize" = "substring-before($StructMember, ' ')"!][!//
    [!/* ---[[!"$CalEventDescSubElem"!] ([!"$CalEventDescSubElemSize"!] bit)]--- */!][!//
    [!VAR "StructMember" = "substring-after($StructMember, ' ')"!][!//
    [!VAR "CalEventDescOffset" = "num:i(0)"!][!//
    [!VAR "NumSM" = "num:integer(count(text:split($StructMember, ' ')))"!][!//
    [!FOR "SMIndex" = "1" TO "$NumSM"!][!//
      [!VAR "BitValueName" = "text:split($StructMember, ' ')[position() = $SMIndex]"!][!//
      [!VAR "MacroName" = "concat('CALC_EVENT_DESC_', $BitValueName)"!][!//
      [!CALL "?$MacroName"!][!//
      [!/*Special handling for DTC_CONFIG_IDX */!][!//
      [!IF "($BitValueName = 'DTC_CONFIG_IDX') and ($CalEventDescOffset > $CalEventDescSubElemSize)"!][!//
        [!VAR "CalEventDescOffset" = "$CalEventDescOffset - $CalDtcConfigIdxWidth"!][!//
        [!VAR "CalDtcConfigIdxOffset" = "num:i(0)"!][!//
        [!IF "$CalDtcConfigIdxWidth <= 8"!][!//
          [!VAR "CalDtcConfigIdxWidth" = "num:i(8)"!][!//
        [!ELSE!][!//
          [!VAR "CalDtcConfigIdxWidth" = "num:i(16)"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!/* Check overflow after each BitValueName */!][!//
      [!IF "$CalEventDescOffset > $CalEventDescSubElemSize"!][!//
        [!VAR "ErrStr" = "concat('Event-Configuration-Layout ', $CalEventDescArray, $CalEventDescSubElem, '.', $BitValueName, ' needs to much space!')"!][!//
        [!ERROR!][!": $ErrStr"!][!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!// Macro for the generation of bitfields
[!MACRO "BUILD_BITFIELD", "BitfieldArray"!][!//
  [!VAR "NumMacros" = "num:integer(count(text:split($BitfieldArray, ' ')))"!][!//
  [!FOR "MacroIndex" = "1" TO "$NumMacros"!][!//
    [!VAR "MacroName" = "concat('EVENT_DESC_BITFIELD_', text:split($BitfieldArray, ' ')[position() = $MacroIndex])"!][!//
    [!CALL "?$MacroName", "Indent" = "4", "Prefix" = "$Operator"!][!//
    [!VAR "Operator" = "'| '"!][!//
  [!ENDFOR!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "BUILD_DESCRIPTION", "Array"!][!//
[!INDENT "0"!][!//
  [!VAR "Array" = "normalize-space($Array)"!][!//
  [!VAR "CalEventDescArray" = "substring-before($Array, ' ')"!][!//
  [!VAR "Array" = "substring-after($Array, ' ')"!][!//
  [!VAR "NumArrayElem" = "num:integer(count(text:split($Array, '#SM#')))"!][!//
  [!FOR "SubElemIndex" = "1" TO "$NumArrayElem"!][!//
    [!VAR "CurrentSubElem" = "text:split($Array, '#SM#')[position() = $SubElemIndex]"!][!//
    [!VAR "CalEventDescSubElem" = "substring-before(normalize-space($CurrentSubElem), ' ')"!][!//
    [!IF "$CalEventDescSubElem = '#NONE#'"!][!//
      [!VAR "CalEventDescSubElem" = "''"!][!//
    [!ENDIF!][!//
    [!VAR "StructMember" = "substring-after(normalize-space($CurrentSubElem), ' ')"!][!//
    [!VAR "CalEventDescSubElemSize" = "substring-before($StructMember, ' ')"!][!//
    [!WS "4"!]/* -----[[!"$CalEventDescSubElem"!] ([!"$CalEventDescSubElemSize"!] bits)]----- */
    [!VAR "StructMember" = "substring-after($StructMember, ' ')"!][!//
    [!VAR "Operator" = "''"!][!//
    [!CALL "BUILD_BITFIELD", "BitfieldArray" = "$StructMember"!],[!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
   * === GET_OPTIONAL_DTCFORMATS ===
   * Creates a list of optional DTC Formats for the desired MASK selection.
   * Optional DTC formats are: 'J1939', 'OBD' and 'OBD_3BYTE'.
   * Supported Selection values are:
   *   DEM_DEFINED_DTCFORMATS_OBDCLASSIC    Defined DTC format values without OBD/UDS separation.
   *   DEM_DEFINED_DTCFORMATS_OBDONUDS      Defined DTC format values dependent on OBD/UDS DTC
   *                                        separation.
   *   DEM_DEFINED_UDS_DTCFORMATS_OBDONUDS  Defined OBDonUDS DTC format values dependent on
   *                                        OBD/UDS DTC separation.
   *   DEM_CONFIGURED_DTCFORMATS_OBDCLASSIC Applicable configured DTC format values when OBD Classic
   *                                        is activated by application callout.
   *   DEM_CONFIGURED_DTCFORMATS_OBDONUDS   Applicable configured DTC format values when OBDonUDS
   *                                        is activated by application callout.
   *   DEM_CONFIGURED_DTCFORMATS            Configured DTC format values.
   *   DEM_SUPPORTED_DTCFORMATS_OBDCLASSIC  Supported DTC format values when OBD Classic is activated
   *                                        by application callout (does not include 'J1939').
   *   DEM_SUPPORTED_DTCFORMATS_OBDONUDS    Supported DTC format values when OBDonUDS is activated
   *                                        by application callout (does not include 'J1939').
   *   DEM_SUPPORTED_DTCFORMATS             Supported DTC format values (does not include 'J1939').
   */!][!//
[!MACRO "GET_OPTIONAL_DTCFORMATS", "Selection"!][!//
[!INDENT "0"!][!//
[!SELECT "as:modconf('Dem')[1]"!][!//
  [!VAR "OptionalDTCFormats" = "''"!][!//
  [!/* 'J1939' is always included in lists of defined DTC formats */!][!//
  [!IF "(($Selection = 'DEM_DEFINED_DTCFORMATS_OBDCLASSIC') or
         ($Selection = 'DEM_DEFINED_DTCFORMATS_OBDONUDS'))"!][!//
    [!VAR "OptionalDTCFormats" = "concat($OptionalDTCFormats, 'J1939 ')"!][!//
  [!ENDIF!] [!//
  [!IF "(node:existsAndTrue(DemGeneral/DemJ1939Support))"!][!//
    [!IF "(($Selection = 'DEM_CONFIGURED_DTCFORMATS_OBDCLASSIC') or
           ($Selection = 'DEM_CONFIGURED_DTCFORMATS_OBDONUDS') or
           ($Selection = 'DEM_CONFIGURED_DTCFORMATS'))"!][!//
      [!VAR "OptionalDTCFormats" = "concat($OptionalDTCFormats, 'J1939 ')"!][!//
    [!ENDIF!] [!//
  [!ENDIF!][!/* (node:existsAndTrue(DemGeneral/DemJ1939Support)) */!][!//
  [!/* CONFIGURED lists contain all DTC formats of SUPPORTED lists + optional 'J1939'
     * that has already been added above. Therefore, only the SUPPORTED selection
     * is used for the remaining DTC formats */!][!//
  [!IF "($Selection = 'DEM_CONFIGURED_DTCFORMATS_OBDCLASSIC') or
        ($Selection = 'DEM_CONFIGURED_DTCFORMATS_OBDONUDS') or
        ($Selection = 'DEM_CONFIGURED_DTCFORMATS')"!][!//
    [!VAR "Selection" = "text:replace($Selection, 'CONFIGURED', 'SUPPORTED')"!][!//
  [!ENDIF!][!//
  [!//
  [!/* 'OBD' is always DEFINED */!][!//
  [!IF "($Selection = 'DEM_DEFINED_DTCFORMATS_OBDCLASSIC') or
        ($Selection = 'DEM_DEFINED_DTCFORMATS_OBDONUDS')"!][!//
    [!VAR "OptionalDTCFormats" = "concat($OptionalDTCFormats, 'OBD ')"!][!//
  [!ENDIF!][!//
  [!IF "node:existsAndTrue(DemGeneral/DemOBDSupport)"!][!//
    [!/* Conditionally add 'OBD' to SUPPORTED/CONFIGURED list */!][!//
    [!IF "not(node:exists(DemGeneral/DemCalloutObdVariantFnc))"!][!//
      [!IF "(DemGeneral/DemObdVariant = 'DEM_OBD_VARIANT_OBD_CLASSIC')"!][!//
        [!IF "(($Selection = 'DEM_SUPPORTED_DTCFORMATS_OBDCLASSIC') or
               ($Selection = 'DEM_SUPPORTED_DTCFORMATS'))"!][!//
          [!VAR "OptionalDTCFormats" = "concat($OptionalDTCFormats, 'OBD ')"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ELSE!][!/*  "not(node:exists(DemGeneral/DemCalloutObdVariantFnc))" */!][!//
      [!IF "(($Selection = 'DEM_SUPPORTED_DTCFORMATS_OBDCLASSIC') or
             ($Selection = 'DEM_SUPPORTED_DTCFORMATS'))"!][!//
        [!VAR "OptionalDTCFormats" = "concat($OptionalDTCFormats, 'OBD ')"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!/* not(node:exists(DemGeneral/DemCalloutObdVariantFnc)) */!][!//
    [!//
    [!/* Conditionally add 'OBD_3BYTE' to DEFINED/SUPPORTED/CONFIGURED list
       * Since 'OBD_3BYTE' is only added to the DEFINED lists if ObdUdsDtcSeparationSupport
       * is enabled, and the DEFINED lists are used for Det checks, a Det is reported if
       * 'OBD_3BYTE' is used but not "configured". */!][!//
    [!/* !LINKSTO Dem.ASR21-11.SWS_Dem_01373,1 */!][!//
    [!IF "$ObdUdsDtcSeparationSupport"!][!//
      [!IF "(($Selection = 'DEM_DEFINED_DTCFORMATS_OBDONUDS') or
             ($Selection = 'DEM_DEFINED_UDS_DTCFORMATS_OBDONUDS') or
             ($Selection = 'DEM_SUPPORTED_DTCFORMATS_OBDONUDS') or
             ($Selection = 'DEM_SUPPORTED_DTCFORMATS'))"!][!//
        [!VAR "OptionalDTCFormats" = "concat($OptionalDTCFormats, 'OBD_3BYTE ')"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!/* (node:existsAndTrue(DemGeneral/DemOBDSupport)) */!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
*
* CREATE_FAILURE_COUNTER_CYCLE_LIST creates a list of unique failure class cycles and thresholds
*/!][!//
[!MACRO "CREATE_FAILURE_COUNTER_CYCLE_LIST"!][!//
[!INDENT "0"!][!//
  [!/* create unique list of all configured
   * failure cycle counter cycles and thresholds */!][!//
  [!VAR "FailureCycleCfgList" = "'#'"!][!//
  [!VAR "EventFailureClassIdx" = "0"!][!//
  [!VAR "EventFailureCycle" = "''"!][!//
  [!LOOP "(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:exists(./DemEventClass/DemEventFailureCycleCounterThreshold)])"!][!//
    [!IF "$CommonOperationCycleEnabled = 'false'"!][!//
      [!VAR "EventFailureCycle" = "as:name(as:ref(DemEventClass/DemEventFailureCycleRef))"!][!//
    [!ELSE!][!//
      [!VAR "EventFailureCycle" = "as:name(as:ref(DemEventClass/DemOperationCycleRef))"!][!//
    [!ENDIF!][!//
    [!VAR "EventFailureThreshold" = "node:value(DemEventClass/DemEventFailureCycleCounterThreshold)"!][!//
    [!IF "not(contains($FailureCycleCfgList, concat('#', $EventFailureCycle, '*', $EventFailureThreshold, '#')))"!][!//
[!/* add non-existing cycle counter cycle and threshold to the list */!][!//
      [!VAR "FailureCycleCfgList" = "concat($FailureCycleCfgList, $EventFailureCycle, '*', $EventFailureThreshold, '#')"!][!//
[!/* increment counter of unique combinations */!][!//
      [!VAR "EventFailureClassIdx" = "$EventFailureClassIdx + 1"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
*
* CREATE_SEM_CONFIG_LISTS creates a list containing event sync storage callback
* for SEM
*/!][!//
[!MACRO "CREATE_SEM_CONFIG_LISTS"!][!//
[!INDENT "0"!][!//
    [!VAR "DemSevWithCbList" = "'#'"!][!/* list of all event Id with callbacks */!][!//
    [!VAR "DemSevCbNameList" = "'#'"!][!/* list of all callbacks */!][!//
    [!VAR "DemSevConfList" = "'#'"!]  [!/* list of bytes for the Sev config bit array */!][!//
    [!VAR "BitIndex" = "1"!][!// Skip pos 0 which is allocated for invalid event
    [!VAR "ByteVal" = "0"!][!//
    [!VAR "ByteHex" = "0"!][!//
    [!VAR "NumSev" = "0"!]            [!/* number of Sev */!][!//
    [!VAR "NumSevWithCb" = "0"!]      [!/* number of Sev with callbacks */!][!//
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
      [!IF "DemEventKind = 'DEM_EVENT_KIND_SEV'"!][!//
        [!IF "node:exists(./DemCallbackEventSyncStorageProcessed/DemCallbackEventSyncStorageProcessedFnc)"!][!//
          [!VAR "CallbackName" = "(./DemCallbackEventSyncStorageProcessed/DemCallbackEventSyncStorageProcessedFnc)"!][!//
          [!VAR "DemSevCbNameList" = "concat($DemSevCbNameList, $CallbackName, '#')"!][!//
          [!VAR "EventId" = "DemEventId"!][!//
          [!VAR "EventName" = "as:name(.)"!][!//
          [!VAR "DemSevWithCbList" = "concat($DemSevWithCbList, $EventId, '?', $EventName, '#')"!][!//
          [!VAR "NumSevWithCb" = "$NumSevWithCb + 1"!][!//
        [!ENDIF!][!//
        [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!][!//
        [!VAR "NumSev" = "$NumSev + 1"!][!//
      [!ENDIF!][!//
      [!VAR "BitIndex" = "$BitIndex + 1"!][!//
      [!IF "($BitIndex = 8)"!][!//
        [!VAR "ByteHex" = "translate(num:inttohex($ByteVal, 2), 'abcdef', 'ABCDEF')"!][!//
        [!VAR "DemSevConfList" = "concat($DemSevConfList, $ByteHex, '#')"!][!//
        [!VAR "ByteVal" = "0"!][!//
        [!VAR "BitIndex" = "0"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "($BitIndex != 0)"!][!//
      [!VAR "ByteHex" = "translate(num:inttohex($ByteVal, 2), 'abcdef', 'ABCDEF')"!][!//
      [!VAR "DemSevConfList" = "concat($DemSevConfList, $ByteHex, '#')"!][!//
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
   * Returns the MIL group index (1-based) for given MIL group representative
   */!][!//
[!MACRO "GET_MILGROUP_INDEX", "REPRESENTATIVE_ID"!][!//
[!INDENT "0"!][!//
  [!VAR "RepresentativeFound" = "'false'"!][!//
  [!LOOP "text:split($MILGroupRepresentativeList, '#')"!][!//
    [!IF "contains(., concat(num:i($REPRESENTATIVE_ID), ':'))"!][!//
      [!VAR "MILGroupIdx" = "text:split(., ':')[position() = 2]"!][!//
      [!VAR "MILGroupIdx" = "num:i($MILGroupIdx)"!][!//
      [!VAR "RepresentativeFound" = "'true'"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "$RepresentativeFound = 'false'"!][!//
    [!VAR "NumberOfMILGroups" = "num:i($NumberOfMILGroups + 1)"!][!//
    [!VAR "MILGroupIdx" = "num:i($MILGroupIdx + 1)"!][!//
    [!VAR "MILGroupRepresentativeList" = "concat($MILGroupRepresentativeList, $MILGroupRepresentative, ':', $MILGroupIdx, '#')"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
*
* CREATE_MILGROUP_EVENT_LIST creates a list containing the events assigned to
* MIL groups and the corresponding index of the MIL group to which they are assigned
*/!][!//
[!MACRO "CREATE_MILGROUP_EVENT_LIST"!][!//
[!INDENT "0"!][!//
  [!VAR "MILGroupEventList" = "'#'"!][!//
  [!VAR "MILGroupRepresentativeList" = "'#'"!][!//
  [!VAR "MILGroupIdx" = "0"!][!//
  [!VAR "NumberOfMILGroups" = "0"!][!//
  [!VAR "NumberOfEventsInMILGroups" = "0"!][!//
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
    [!IF "node:exists(./DemOBDGroupingAssociativeEventsRef)"!][!//
      [!VAR "NumberOfEventsInMILGroups" = "num:i($NumberOfEventsInMILGroups + 1)"!][!//
      [!VAR "MILGroupRepresentative" = "node:value(as:ref(./DemOBDGroupingAssociativeEventsRef)/DemEventId)"!][!//
      [!CALL "GET_MILGROUP_INDEX", "REPRESENTATIVE_ID" = "$MILGroupRepresentative"!][!//
      [!VAR "MILGroupEventList" = "concat($MILGroupEventList, DemEventId, ':', num:i($MILGroupIdx - 1), '#')"!][!//
    [!ELSE!]
      [!VAR "MILGroupEventList" = "concat($MILGroupEventList, DemEventId, ':', '-', '#')"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!CALL "CREATE_MILGROUP_EVENT_LIST"!][!//
[!/* === Get debounce classes === */!][!//
[!VAR "DebounceCounterConsecutiveCallFlag"  = "'false'"!][!//
[!MACRO "DEBOUNCE_COUNTER_CLASS_CALC"!][!//
[!INDENT "0"!][!//
  [!IF "$DebounceCounterConsecutiveCallFlag = 'false'"!][!//
    [!VAR "DebounceClasses" = "''"!][!//
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceCounterBased'], 'DemEventId'))"!][!//
      [!SELECT "DemEventClass/DemDebounceAlgorithmClass"!][!//
        [!VAR "UnconfirmedThreshold" = "0"!][!//
        [!IF "node:existsAndTrue(DemDebounceCounterUnconfirmedThreshold)"!][!//
          [!VAR "UnconfirmedThreshold" = "DemDebounceCounterUnconfirmedThreshold"!][!//
        [!ENDIF!][!//
        [!VAR "DebounceClass" = "concat('#', DemDebounceCounterDecrementStepSize, ':', DemDebounceCounterIncrementStepSize, ':', DemDebounceCounterPassedThreshold, ':', DemDebounceCounterFailedThreshold, ':', $UnconfirmedThreshold, ':', DemDebounceCounterJumpDownValue, ':', DemDebounceCounterJumpUpValue, ':', DemDebounceBehavior, ':', DemDebounceCounterJumpDown, ':', DemDebounceCounterJumpUp, ':', DemDebounceCounterStorage, '#')"!][!//
        [!IF "not(contains($DebounceClasses, $DebounceClass))"!][!//
          [!VAR "DebounceClasses" = "concat($DebounceClasses, $DebounceClass)"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDLOOP!][!//
    [!VAR "DebounceCounterConsecutiveCallFlag"  = "'true'"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Number of debounce classes ===
   * Macro DEBOUNCE_COUNTER_CLASS_CALC must be called before!
   */!][!//
[!MACRO "DEBOUNCE_COUNTER_GET_CLASS_COUNT"!][!//
[!CALL "DEBOUNCE_COUNTER_CLASS_CALC"!]
[!INDENT "0"!][!//
  [!VAR "DebounceCounterClassCount" = "count(text:split($DebounceClasses, '#'))"!][!//
[!ENDINDENT!][!//
[!IF "node:exists(DemGeneral/DemMaxNumberDebCounterClasses)"!]
  [!IF "number($DebounceCounterClassCount) < DemGeneral/DemMaxNumberDebCounterClasses"!]
    [!VAR "DebounceCounterClassCount" = "DemGeneral/DemMaxNumberDebCounterClasses"!]
  [!ENDIF!]
[!ENDIF!]
[!ENDMACRO!][!//
[!//
[!/* === Get debounce class index ===
   * Macro DEBOUNCE_COUNTER_CLASS_CALC must be called before!
   */!][!//
[!MACRO "DEBOUNCE_COUNTER_GET_CLASS_INDEX", "EventId"!][!//
[!INDENT "0"!][!//
  [!VAR "UnconfirmedThreshold" = "0"!][!//
  [!IF "node:exists(DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterUnconfirmedThreshold)"!][!//
    [!VAR "UnconfirmedThreshold" = "DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterUnconfirmedThreshold"!][!//
  [!ENDIF!][!//
  [!VAR "DebounceCounterClassIndex" = "0"!][!//
  [!VAR "DebounceClass" = "concat(DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterDecrementStepSize, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterIncrementStepSize, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterPassedThreshold, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterFailedThreshold, ':', $UnconfirmedThreshold, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterJumpDownValue, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterJumpUpValue, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceBehavior, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterJumpDown, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterJumpUp, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterStorage)"!][!//
  [!IF "contains($DebounceClasses, $DebounceClass)"!][!//
    [!LOOP "text:split($DebounceClasses, '#')"!][!//
      [!IF "string(.) = $DebounceClass"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "DebounceCounterClassIndex" = "$DebounceCounterClassIndex + 1"!][!//
    [!ENDLOOP!][!//
    [!VAR "DebounceCounterClassIndex" = "concat(num:i($DebounceCounterClassIndex), 'U')"!][!//
  [!ELSE!][!//
    [!VAR "DebounceCounterClassIndex" = "'DEM_DEBOUNCE_CLASS_INVALID'"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!//
[!//
[!/* === Get Time debounce classes === */!][!//
[!VAR "DebounceTimeConsecutiveCallFlag"  = "'false'"!][!//
[!MACRO "DEBOUNCE_TIME_CLASS_CALC"!][!//
[!INDENT "0"!][!//
  [!IF "$DebounceTimeConsecutiveCallFlag = 'false'"!][!//
    [!VAR "TimeDebounceClasses" = "''"!][!//
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase'], 'DemEventId'))"!][!//
      [!SELECT "DemEventClass/DemDebounceAlgorithmClass"!][!//
        [!VAR "TimeDebounceClass" = "concat('#', DemDebounceTimeFailedThreshold, ':', DemDebounceTimePassedThreshold, ':', DemDebounceBehavior, '#')"!][!//
        [!IF "not(contains($TimeDebounceClasses, $TimeDebounceClass))"!][!//
          [!VAR "TimeDebounceClasses" = "concat($TimeDebounceClasses, $TimeDebounceClass)"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDLOOP!][!//
    [!VAR "DebounceTimeConsecutiveCallFlag"  = "'true'"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Number of Time debounce classes ===
   * Macro DEBOUNCE_TIME_CLASS_CALC must be called before!
   */!][!//
[!MACRO "DEBOUNCE_TIME_GET_CLASS_COUNT"!][!//
[!CALL "DEBOUNCE_TIME_CLASS_CALC"!]
[!INDENT "0"!][!//
  [!VAR "DebounceTimeClassCount" = "count(text:split($TimeDebounceClasses, '#'))"!][!//
[!ENDINDENT!][!//
[!IF "node:exists(DemGeneral/DemMaxNumberDebTimeClasses)"!]
  [!IF "number($DebounceTimeClassCount) < DemGeneral/DemMaxNumberDebTimeClasses"!]
    [!VAR "DebounceTimeClassCount" = "DemGeneral/DemMaxNumberDebTimeClasses"!]
  [!ENDIF!]
[!ENDIF!]
[!ENDMACRO!][!//
[!//
[!/* === Get Time debounce class index ===
   * Macro DEBOUNCE_TIME_CLASS_CALC must be called before!
   */!][!//
[!MACRO "DEBOUNCE_TIME_GET_CLASS_INDEX", "EventId"!][!//
[!INDENT "0"!][!//
  [!VAR "DebounceTimeClassIndex" = "0"!][!//
  [!VAR "TimeDebounceClass" = "concat(DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceTimeFailedThreshold, ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceTimePassedThreshold,  ':', DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceBehavior)"!][!//
  [!IF "contains($TimeDebounceClasses, $TimeDebounceClass)"!][!//
    [!LOOP "text:split($TimeDebounceClasses, '#')"!][!//
      [!IF "string(.) = $TimeDebounceClass"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "DebounceTimeClassIndex" = "$DebounceTimeClassIndex + 1"!][!//
    [!ENDLOOP!][!//
    [!VAR "DebounceTimeClassIndex" = "concat(num:i($DebounceTimeClassIndex), 'U')"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!VAR "AvailabilitySupport" = "node:exists(DemGeneral/DemAvailabilitySupport) and (DemGeneral/DemAvailabilitySupport = 'DEM_EVENT_AVAILABILITY')"!]
[!/* === Create J1939 supported node list === */!][!//
[!MACRO "CREATE_J1939_NODE_LIST"!][!//
[!INDENT "0"!][!//
  [!VAR "J1939NodeList" = "'#'"!][!//
  [!VAR "J1939NodeListWithReadiness" = "'#'"!][!//
  [!VAR "J1939NodeValue" = "0"!][!//
  [!VAR "J1939NodeName" = "''"!][!//
  [!VAR "NumJ1939Nodes" = "0"!][!//
  [!VAR "NumReadinessRelevantNodes" = "0"!][!//
  [!VAR "ReadinessJ1939Support" = "(node:existsAndTrue(DemGeneral/DemOBDSupport)) and node:exists(DemGeneral/DemGeneralJ1939/DemJ1939Readiness1Support) and (node:existsAndTrue(DemGeneral/DemGeneralJ1939/DemJ1939Readiness1Support))"!][!//
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
    [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemJ1939DTCValue)"!][!//
      [!VAR "J1939NodeValue" = "node:value(as:ref(as:ref(./DemDTCClassRef)/DemJ1939NodeRef)/J1939NmNodeId)"!][!//
      [!VAR "J1939NodeName" = "text:split(node:value(as:ref(./DemDTCClassRef)/DemJ1939NodeRef),'/')[last()]"!][!//
      [!IF "not(text:contains(text:split($J1939NodeList, "#"), concat($J1939NodeValue, ':', $J1939NodeName)))"!][!//
        [!VAR "J1939NodeList" = "concat($J1939NodeList, $J1939NodeValue, ':', $J1939NodeName, '#')"!][!//
        [!VAR "NumJ1939Nodes" = "$NumJ1939Nodes + 1"!][!//
      [!ENDIF!][!//
      [!IF "$ReadinessJ1939Support = 'true'"!][!//
        [!IF "DemEventClass/DemEventOBDReadinessGroup != 'DEM_OBD_RDY_NONE' and not(text:contains(text:split($J1939NodeListWithReadiness, "#"), concat($J1939NodeValue, ':', $J1939NodeName)))"!][!//
          [!VAR "J1939NodeListWithReadiness" = "concat($J1939NodeListWithReadiness, $J1939NodeValue, ':', $J1939NodeName, '#')"!][!//
          [!VAR "NumReadinessRelevantNodes" = "$NumReadinessRelevantNodes + 1"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!VAR "J1939NodeList" = "text:join(num:order(text:split($J1939NodeList, '#')), '#')"!][!//
  [!VAR "J1939NodeList" = "concat($J1939NodeList, '#')"!][!//
  [!IF "$NumReadinessRelevantNodes > 0"!][!//
    [!VAR "J1939NodeListWithReadiness" = "text:join(num:order(text:split($J1939NodeListWithReadiness, '#')), '#')"!][!//
    [!VAR "J1939NodeListWithReadiness" = "concat($J1939NodeListWithReadiness, '#')"!][!//
  [!ELSE!][!//
    [!VAR "ReadinessJ1939Support" = "'false'"!][!//
  [!ENDIF!][!//
  [!IF "$NumJ1939Nodes > 254"!][!//
    [!ERROR!]Dem does not support more than 254 unique J1939NmNodeId's[!ENDERROR!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Create legacy readiness group list === */!][!//
[!VAR "LegacyReadinessGroupsList" = "''"!][!//
[!VAR "MaxNumEventsInRG" = "0"!][!//
[!MACRO "CREATE_LEGACY_READINESSGROUPS_LIST"!][!//
  [!VAR "RGMaskConfiguredLegacy" = "0"!][!//
  [!VAR "ConditionalReadinessGroupGPF" = "''"!][!//
  [!INDENT "0"!][!//
    [!IF "$LegacyReadinessGroupsList = ''"!][!//
    [!IF "node:exists(as:modconf('Dem')[1]/DemGeneral/DemMaxNumEventsPerReadinessGroup)"!][!//
      [!VAR "MaxNumEventsInRG" = "node:value(as:modconf('Dem')[1]/DemGeneral/DemMaxNumEventsPerReadinessGroup)"!][!//
    [!ENDIF!][!//
      [!IF "node:exists(as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemEventOBDReadinessGroup = 'DEM_OBD_RDY_GPF'])"!][!//
        [!VAR "ConditionalReadinessGroupGPF" = "concat('0x15:GPF:', $MaxNumEventsInRG, '#')"!][!//
      [!ENDIF!][!//
      [!VAR "LegacyReadinessGroupsList" = "concat('0x03:MISF:', $MaxNumEventsInRG, '#', [!//
                                                  '0x06:FLSYS:', $MaxNumEventsInRG, '#', [!//
                                                  '0x0E:CMPRCMPT:', $MaxNumEventsInRG, '#', [!//
                                                  '0x08:EGR:', $MaxNumEventsInRG, '#', [!//
                                                  '0x19:FLSYS_NONCONT:', $MaxNumEventsInRG, '#')"!][!//
      [!IF "node:exists(DemGeneral/DemGeneralOBD/DemOBDEngineType) and (DemGeneral/DemGeneralOBD/DemOBDEngineType = 'DEM_IGNITION_SPARK')"!][!//
        [!VAR "LegacyReadinessGroupsList" = "concat($LegacyReadinessGroupsList, '0x01:CAT:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x02:HTCAT:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x04:EVAP:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x05:SECAIR:', $MaxNumEventsInRG, '#', [!//
                                                                                $ConditionalReadinessGroupGPF, [!//
                                                                                '0x16:O2SENS:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x17:O2SENSHT:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x18:AC:', $MaxNumEventsInRG, '#')"!][!//
      [!ELSE!][!//
        [!VAR "LegacyReadinessGroupsList" = "concat($LegacyReadinessGroupsList, '0x10:HCCAT:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x11:NOXCAT:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x04:UNUSED_1:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x12:BOOSTPR:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x07:EGSENS:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x14:PMFLT:', $MaxNumEventsInRG, '#', [!//
                                                                                '0x18:UNUSED_2:', $MaxNumEventsInRG, '#')"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!VAR "NumberOfGroups" = "num:i(count(text:split($LegacyReadinessGroupsList, '#')))"!][!//
    [!/* === Hard code readiness group mask for OBD variant classic === */!][!//
    [!IF "node:exists(as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemEventOBDReadinessGroup = 'DEM_OBD_RDY_GPF'])"!][!//
      [!VAR "RGMaskConfiguredLegacy" = "num:hextoint('0x1F741FE')"!][!//
    [!ELSE!][!//
      [!VAR "RGMaskConfiguredLegacy" = "num:hextoint('0x1D741FE')"!][!//
    [!ENDIF!][!//
  [!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Complete information of OBDonUDS readiness group === */!][!//
[!VAR "ReadinessInfoList" = "''"!][!//
[!MACRO "CREATE_READINESS_INFO_LIST"!][!//
[!INDENT "0"!][!//
  [!IF "$ReadinessInfoList = ''"!][!//
    [!/* === Readiness group name, RGID, F501(Spark : Compr), F401(Spark : Compr), J1939(Spark : Compr) === */!][!//
    [!VAR "ReadinessInfoList" = "concat('NONE:0x00:0:0:0:0:0:0', '#', [!//
                                        'CAT:0x01:1:0:1:0:1:0', '#', [!//
                                        'HTCAT:0x02:1:0:1:0:1:0', '#', [!//
                                        'MISF:0x03:1:1:1:1:1:1', '#', [!//
                                        'EVAP:0x04:1:0:1:0:1:0', '#', [!//
                                        'SECAIR:0x05:1:0:1:0:1:0', '#', [!//
                                        'FLSYS:0x06:1:1:1:1:1:1', '#', [!//
                                        'EGSENS:0x07:1:1:0:1:0:1', '#', [!//
                                        'EGR:0x08:1:1:1:1:1:1', '#', [!//
                                        'PCV:0x09:1:1:0:0:0:0', '#', [!//
                                        'ECS:0x0A:1:1:0:0:0:0', '#', [!//
                                        'CSER:0x0B:1:1:0:0:1:1', '#', [!//
                                        'VVT:0x0C:1:1:0:0:0:0', '#', [!//
                                        'DOR:0x0D:1:1:0:0:0:0', '#', [!//
                                        'CMPRCMPT:0x0E:1:1:1:1:1:1', '#', [!//
                                        'OTHER:0x0F:1:1:0:0:0:0', '#', [!//
                                        'HCCAT:0x10:0:1:0:1:0:1', '#', [!//
                                        'NOXCAT:0x11:0:1:0:1:0:1', '#', [!//
                                        'BOOSTPR:0x12:0:1:0:1:0:1', '#', [!//
                                        'NOXADSORB:0x13:0:1:0:0:0:0', '#', [!//
                                        'PMFLT:0x14:1:1:0:1:0:1', '#', [!//
                                        'GPF:0x15:0:0:1:0:0:0', '#', [!//
                                        'O2SENS:0x16:0:0:1:0:1:0', '#', [!//
                                        'O2SENSHT:0x17:0:0:1:0:1:0', '#', [!//
                                        'AC:0x18:0:0:0:0:1:0', '#')"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Create readiness group events list === */!][!//
[!MACRO "CREATE_READINESSGROUPS_EVENT_LIST"!][!//
[!INDENT "0"!][!//
  [!VAR "RGMaskConfiguredEvent" = "0"!][!//
  [!VAR "ReadinessGroupsEventList" = "'#'"!][!//
  [!VAR "LegacyRGList" = "''"!][!//
  [!INDENT "2"!][!//
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemEventOBDReadinessGroup != 'DEM_OBD_RDY_NONE']"!][!//
      [!IF "not(node:existsAndFalse(DemEvtCmbCommonParamMaster))"!][!//
        [!VAR "RG" ="substring-after(node:value(DemEventClass/DemEventOBDReadinessGroup), 'DEM_OBD_RDY_')"!][!//
        [!IF "$RG = 'FLSYS_NONCONT'"!][!//
          [!VAR "RGID" = "'0x19'"!][!//
        [!ELSE!][!//
          [!CALL "CREATE_READINESS_INFO_LIST"!][!//
          [!VAR "RGID" = "substring-before(substring-after($ReadinessInfoList, concat($RG,':')), ':')"!][!//
        [!ENDIF!][!//
        [!VAR "RGMaskConfiguredEvent" = "bit:or($RGMaskConfiguredEvent, bit:shl(1,num:hextoint($RGID)))"!][!//
        [!VAR "ReadinessGroupsEventList" = "concat($ReadinessGroupsEventList, $RGID, ':', node:name("."),'#')"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDINDENT!][!//
  [!/* === Sort the ReadinessGroupEventList === */!][!//
  [!IF "(DemGeneral/DemReadinessGroupCalibrationConfigKind = 'DEM_NUMBER_OF_SLOTS_COMMON_CONFIG')"!][!//
    [!CALL "CREATE_LEGACY_READINESSGROUPS_LIST"!][!//
    [!LOOP "text:split($LegacyReadinessGroupsList, '#')"!][!//
      [!VAR "RGIdx" = "text:split(., ":")[position() = '1']"!][!//
      [!LOOP "text:split($ReadinessGroupsEventList, '#')"!][!//
        [!VAR "EvtRGID" = "text:split(., ":")[position() = '1']"!][!//
        [!IF "($RGIdx = $EvtRGID)"!][!//
          [!VAR "LegacyRGList" = "concat($LegacyRGList, ., '#')"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!VAR "ReadinessGroupsEventList" = "$LegacyRGList"!][!//
  [!ELSE!][!//
    [!VAR "ReadinessGroupsEventList" = "text:join(text:order(text:split($ReadinessGroupsEventList, '#')),'#')"!][!//
    [!VAR "ReadinessGroupsEventList" = "concat($ReadinessGroupsEventList, '#')"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Create ReadinessGroupsConfigList and calculate configured readiness group mask === */!][!//
[!MACRO "CREATE_READINESSGROUPS_CONFIG_LIST"!][!//
[!INDENT "0"!][!//
  [!CALL "CREATE_READINESS_INFO_LIST"!][!//
  [!IF "not(node:exists(DemGeneral/DemReadinessGroupCalibration/eb-list::*))"!][!//
    [!CALL "CREATE_LEGACY_READINESSGROUPS_LIST"!][!//
    [!VAR "ReadinessGroupsConfigList" = "$LegacyReadinessGroupsList"!][!//
  [!ELSE!][!//
    [!VAR "ReadinessGroupsConfigList" = "'#'"!][!//
    [!VAR "RGMaskConfiguredEventSlots" = "0"!][!//
    [!LOOP "DemGeneral/DemReadinessGroupCalibration/*"!][!//
    [!IF "(node:value(".") != '0')"!][!//
      [!VAR "RG" ="text:toupper(substring-after(node:name(.), 'DemMaxNumEventsRdy'))"!][!//
      [!VAR "RGID" = "substring-before(substring-after($ReadinessInfoList, concat($RG, ':')), ':')"!][!//
      [!VAR "ReadinessGroupsConfigList" = "concat($ReadinessGroupsConfigList, $RGID, ':', $RG, ':', node:value("."), '#')"!][!//
      [!VAR "RGMaskConfiguredEventSlots" = "bit:or($RGMaskConfiguredEventSlots, bit:shl(1,num:hextoint($RGID)))"!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!/* === Sort the ReadinessGroupsConfigList === */!][!//
    [!VAR "ReadinessGroupsConfigList" = "text:join(text:order(text:split($ReadinessGroupsConfigList, '#')),'#')"!][!//
    [!VAR "ReadinessGroupsConfigList" = "concat($ReadinessGroupsConfigList, '#')"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* Extract the readiness group mask for spark and compression engine type */!][!//
[!MACRO "GET_RGMASK", "Readiness", "Engine"!][!//
[!INDENT "0"!][!//
  [!IF "$Readiness = 'PIDF501'"!][!//
    [!IF "$Engine = 'DEM_IGNITION_SPARK'"!][!//
      [!VAR "position" = "3"!][!//
    [!ELSE!][!//
      [!VAR "position" = "4"!][!//
    [!ENDIF!][!//
  [!ELSEIF "$Readiness = 'PID01_41'"!][!//
    [!IF "$Engine = 'DEM_IGNITION_SPARK'"!][!//
      [!VAR "position" = "5"!][!//
    [!ELSE!][!//
      [!VAR "position" = "6"!][!//
    [!ENDIF!][!//
  [!ELSEIF "$Readiness = 'J1939Readiness1'"!][!//
    [!IF "$Engine = 'DEM_IGNITION_SPARK'"!][!//
      [!VAR "position" = "7"!][!//
    [!ELSE!][!//
      [!VAR "position" = "8"!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!ERROR "Invalid Readiness: $Readiness"!][!//
  [!ENDIF!][!//
  [!VAR "RGMaskBit" = "0"!][!//
  [!LOOP "text:split($ReadinessInfoList, '#')"!][!//
    [!VAR "RGID" = "text:split(., ':')[position() = 2]"!][!//
    [!VAR "RGbit" = "text:split(., ':')[position() = $position]"!][!//
    [!IF "$RGbit = 1"!][!//
      [!VAR "RGMaskBit" = "bit:or($RGMaskBit, bit:shl(1,num:hextoint($RGID)))"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!VAR "RGConfigMask" = "bit:and($RGMaskBit, $RGMaskConfigured)"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!VAR "NumRGREvents" = "-1"!][!//
[!/* === Total number of calibratable event slots === */!][!//
[!MACRO "GET_NUMBER_RG_EVENTS"!][!//
[!INDENT "0"!][!//
  [!IF "$NumRGREvents < 0"!][!//
    [!IF "node:exists(DemGeneral/DemReadinessGroupCalibrationConfigKind) and (DemGeneral/DemReadinessGroupCalibrationConfigKind = 'DEM_NUMBER_OF_SLOTS_COMMON_CONFIG')"!][!//
      [!CALL "CREATE_LEGACY_READINESSGROUPS_LIST"!][!//
      [!VAR "EventIdSlots" = "num:i($NumberOfGroups * $MaxNumEventsInRG)"!][!//
    [!ELSE!][!//
      [!VAR "EventIdSlots" = "num:i(sum(DemGeneral/DemReadinessGroupCalibration/eb-list::*))"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
[!/* === Get the internal priority index === */!][!//
[!MACRO "GET_INTERNAL_PRIORITY_IDX", "Prio"!][!//
[!INDENT "0"!][!//
[!/* internally packed priority value [0..(N-1)] */!][!//
  [!VAR "PriorityValueIdx" = "0"!][!//
  [!LOOP "text:split($PriorityValueList, '#')"!][!//
    [!IF "number(.) = $Prio"!][!//
      [!BREAK!][!//
    [!ELSE!][!//
      [!VAR "PriorityValueIdx" = "$PriorityValueIdx + 1"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Create a filled list of internal priority values === */!][!//
[!MACRO "CREATE_PRIORITY_VALUE_LIST"!][!//
[!INDENT "0"!][!//
  [!VAR "PriorityValueList" = "'#'"!][!//
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:exists(DemEventClass/DemEventPriority)]/DemEventClass, 'DemEventPriority'))"!][!//
    [!IF "not(contains($PriorityValueList, concat('#', DemEventPriority, '#')))"!][!//
      [!/* add non-existing higher priority value at the end of the list */!][!//
      [!VAR "PriorityValueList" = "concat($PriorityValueList, DemEventPriority, '#')"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!MACRO "GET_NUMBER_OF_EVENT_PRIORITIES"!][!//
  [!CALL "CREATE_PRIORITY_VALUE_LIST"!][!//
  [!VAR "NumberOfPriorities" = "num:i(count(text:split($PriorityValueList, '#')))"!][!//
[!ENDMACRO!][!//
[!//
[!/* Creates lists used to generate events and DTC data arrays, for event combination */!][!//
[!MACRO "CREATE_DTCCLASS_LIST_FROM_EVENTS"!][!//
[!INDENT "0"!][!//
[!/* === DemDTCClassList ===
   * This list contains combined DTC values, non-combined DTC values, and events without DTC in this order.
   * The DemDTCClassList is used for generating the Dem_DTCDesc[] config array.
   * If DemEventCombinationSupport is enabled (DEM_EVCOMB_TYPE1), Dem_EventDesc[] entries contain an
   * index to a Dem_DTCDesc[] entry which needs to be generated for events without DTC as well.
   * Note that the SHORT-NAME-path of the DTC and event is unique within the SHORT-NAME parent
   * and therefore DemEventsWithoutDTCList can be appended to DemDTCClassList.
   * The macro generates also an additional list containing the combined DTC classes that have EDRN0x93
   * configured, and info wrt the events assigned to these DTC classes. This list is used for the
   * Monitor Activity Ratio (MAR) functionality.
   */!][!//
  [!VAR "DemDTCClassList" = "'#'"!][!//
  [!VAR "DemNonCombinedDTCList" = "'#'"!][!//
  [!VAR "DemEventsWithoutDTCList" = "'#'"!][!//
  [!VAR "DemCmbDTCEvLnkList" = "'#'"!][!//
  [!VAR "DemIdxInCmbDTCEvents" = "0"!][!//
  [!VAR "DemCmbDTCEventsList" = "'#'"!][!//
[!//
  [!VAR "MARCmbEventList" = "'#'"!][!//
  [!VAR "MARCmbEventsNum" = "0"!][!//
  [!VAR "MARCmbDTCsNum" = "0"!][!//
[!//
  [!VAR "DTCSeverityAvailabilityMask" = "0"!][!//
[!//
  [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemDTCClass/eb-list::*"!][!//
    [!VAR "DTCClassName" = "as:name(.)"!][!//
    [!VAR "NumOfEventsWithTheSameDTC" = "0"!][!//
    [!VAR "DemAuxCmbDTCEvLnkList" = "'#'"!][!//
    [!VAR "EvCombParentEventId" = "0"!][!//
[!//
    [!VAR "MARAuxCmbEventsList" = "'?'"!][!//
    [!VAR "IsMARDTC" = "'false'"!][!//
[!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
    [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:exists(DemDTCClassRef)]"!][!//
[!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
   * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
      [!IF "string($DTCClassName) = text:split(DemDTCClassRef, '/')[last()]"!][!//
        [!VAR "NumOfEventsWithTheSameDTC" = "$NumOfEventsWithTheSameDTC + 1"!][!//
        [!VAR "EventName" = "node:name(.)"!][!//
        [!VAR "EventID" = "node:value(DemEventId)"!][!//
        [!IF "node:exists(DemEvtCmbCommonParamMaster) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
          [!VAR "EvCombParentEventId" = "$EventID"!][!//
          [!/* if the master event is referencing EDRN 0x93, then all events of the combination are MAR events */!][!//
          [!IF "$MARSupport = 'true' and node:exists(util:distinct(node:refs(util:distinct(node:refs(DemExtendedDataClassRef))/DemExtendedDataRecordClassRef/eb-list::*))[DemExtendedDataRecordNumber = '147'])"!][!//
            [!VAR "IsMARDTC" = "'true'"!][!//
            [!VAR "MARCmbDTCsNum" = "$MARCmbDTCsNum + 1"!][!//
          [!ENDIF!][!//
          [!VAR "EvCombParentEventName" = "$EventName"!][!//
        [!ELSE!][!//
          [!VAR "DemAuxCmbDTCEvLnkList" = "concat($DemAuxCmbDTCEvLnkList, $EventID, '#')"!][!//
          [!VAR "MARAuxCmbEventsList" = "concat($MARAuxCmbEventsList, $EventID, ':', $EventName, '?')"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$NumOfEventsWithTheSameDTC > 1"!][!//
      [!VAR "DemDTCClassList" = "concat($DemDTCClassList, $DTCClassName, '#')"!][!//
      [!VAR "DemCmbDTCEvLnkList" = "concat($DemCmbDTCEvLnkList, $DemIdxInCmbDTCEvents, '#')"!][!//
      [!VAR "DemIdxInCmbDTCEvents" = "($DemIdxInCmbDTCEvents + $NumOfEventsWithTheSameDTC)"!][!//
      [!VAR "DemCmbDTCEventsList" = "concat($DemCmbDTCEventsList , $EvCombParentEventId, '#')"!][!//
      [!VAR "DemCmbDTCEventsList" = "concat($DemCmbDTCEventsList , $DemAuxCmbDTCEvLnkList, '#')"!][!//
      [!IF "$IsMARDTC = 'true'"!][!//
        [!/* add master MAR event at the begin of the list of combination's events */!][!//
        [!VAR "MARAuxCmbEventsList" = "concat('?', $EvCombParentEventId, ':', $EvCombParentEventName, '?', $MARAuxCmbEventsList)"!][!//
        [!/* for combined MAR events, the list contains the DTCClass, number of events of the combination, and the events of the combination */!][!//
        [!VAR "MARCmbEventList" = "concat($MARCmbEventList , $DTCClassName, '&', $NumOfEventsWithTheSameDTC, '&', $MARAuxCmbEventsList, '#')"!][!//
        [!/* add number of events in current combination to the total number of MAR combined events */!][!//
        [!VAR "MARCmbEventsNum" = "$MARCmbEventsNum + $NumOfEventsWithTheSameDTC"!][!//
      [!ENDIF!][!//
    [!ELSEIF "$NumOfEventsWithTheSameDTC = 1"!][!//
      [!VAR "DemNonCombinedDTCList" = "concat($DemNonCombinedDTCList, $DTCClassName, '#')"!][!//
    [!ENDIF!][!//
    [!IF "$NumOfEventsWithTheSameDTC >= 1"!][!//
      [!/* for all DTCs referenced by events, check DemDTCSeverity and DemWWHOBDDTCClass parameters
         * to generate DTCSeverityAvailabilityMask */!][!//
      [!/* !LINKSTO Dem.ASR21-11.SWS_Dem_01182,1 */!][!//
      [!IF "node:exists(DemDTCSeverity) and (node:value(DemDTCSeverity) != 'DEM_DTC_SEV_NO_SEVERITY')"!][!//
        [!IF "node:value(DemDTCSeverity) = 'DEM_DTC_SEV_MAINTENANCE_ONLY'"!][!//
          [!VAR "DTCSeverityMask" = "num:hextoint('0x20')"!][!//
        [!ELSEIF "node:value(DemDTCSeverity) = 'DEM_DTC_SEV_CHECK_AT_NEXT_HALT'"!][!//
          [!VAR "DTCSeverityMask" = "num:hextoint('0x40')"!][!//
        [!ELSEIF "node:value(DemDTCSeverity) = 'DEM_DTC_SEV_IMMEDIATELY'"!][!//
          [!VAR "DTCSeverityMask" = "num:hextoint('0x80')"!][!//
        [!ENDIF!][!//
        [!VAR "DTCSeverityAvailabilityMask" = "bit:or($DTCSeverityAvailabilityMask, $DTCSeverityMask)"!][!//
      [!ENDIF!][!//
      [!IF "$DTCClassAvailable = 'true'"!][!//
        [!IF "node:exists(DemWWHOBDDTCClass)"!][!//
          [!IF "node:value(DemWWHOBDDTCClass) = 'DEM_DTC_WWHOBD_CLASS_NOCLASS'"!][!//
            [!VAR "DTCClassMask" = "num:hextoint('0x01')"!][!//
          [!ELSEIF "node:value(DemWWHOBDDTCClass) = 'DEM_DTC_WWHOBD_CLASS_A'"!][!//
            [!VAR "DTCClassMask" = "num:hextoint('0x02')"!][!//
          [!ELSEIF "node:value(DemWWHOBDDTCClass) = 'DEM_DTC_WWHOBD_CLASS_B1'"!][!//
            [!VAR "DTCClassMask" = "num:hextoint('0x04')"!][!//
          [!ELSEIF "node:value(DemWWHOBDDTCClass) = 'DEM_DTC_WWHOBD_CLASS_B2'"!][!//
            [!VAR "DTCClassMask" = "num:hextoint('0x08')"!][!//
          [!ELSEIF "node:value(DemWWHOBDDTCClass) = 'DEM_DTC_WWHOBD_CLASS_C'"!][!//
            [!VAR "DTCClassMask" = "num:hextoint('0x10')"!][!//
          [!ENDIF!][!//
          [!VAR "DTCSeverityAvailabilityMask" = "bit:or($DTCSeverityAvailabilityMask, $DTCClassMask)"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!VAR "DTCSeverityAvailabilityMask" = "translate(num:inttohex($DTCSeverityAvailabilityMask, 2), 'abcdef', 'ABCDEF')"!][!//
[!/* Create the list of events without associated DTC */!][!//
  [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:exists(DemDTCClassRef))]"!][!//
    [!VAR "DemEventsWithoutDTCList" = "concat($DemEventsWithoutDTCList, as:name(.), '#')"!][!//
  [!ENDLOOP!][!//
[!//
[!/* Additional entry is created in order to calculate the number of linked events */!][!//
  [!VAR "DemCmbDTCEvLnkList" = "concat($DemCmbDTCEvLnkList, $DemIdxInCmbDTCEvents, '#')"!][!//
  [!VAR "DemDTCClassList" = "concat($DemDTCClassList, $DemNonCombinedDTCList, '#')"!][!//
  [!VAR "DemDTCClassList" = "concat($DemDTCClassList, $DemEventsWithoutDTCList, '#')"!][!//
  [!VAR "DemNbOfDTCClasses" = "count(text:split($DemDTCClassList, '#'))"!][!//
  [!VAR "DemNbOfCmbDTCs" = "(count(text:split($DemCmbDTCEvLnkList, '#')) - 1)"!][!//
  [!VAR "DemNbOfCmbEvents" = "count(text:split($DemCmbDTCEventsList, '#'))"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Get Intermediate DTC size ===
   * Macro GET_INTERMEDIATE_DTC_SIZE computes the size of StorageOrderIdAndDTCStatus array for each memory origin
   * Macro CREATE_DTCCLASS_LIST_FROM_EVENTS must be called before!
   */!][!//
[!MACRO "GET_INTERMEDIATE_DTC_SIZE"!][!//
[!INDENT "0"!][!//
  [!VAR "IntermediateNvStorage" = "'false'"!][!//
  [!IF "(node:existsAndTrue(DemGeneral/DemIntermediateNvStorageOfDTCStatus))"!][!//
    [!VAR "IntermediateDTCsMaxPriSize" = "0"!][!//
    [!VAR "IntermediateDTCsMaxSecSize" = "0"!][!//
    [!VAR "IntermediateDTCsMaxMirSize" = "0"!][!//
    [!/* Check combined events with immediate storage */!][!//
    [!FOR "Ctr" = "1" TO "$DemNbOfCmbDTCs"!][!//
      [!VAR "CurrNode" = "text:split($DemCmbDTCEvLnkList, '#')[position() = $Ctr]"!][!//
      [!VAR "NextNode" = "text:split($DemCmbDTCEvLnkList, '#')[position() = $Ctr+1]"!][!//
      [!VAR "EventId" = "text:split($DemCmbDTCEventsList, '#')[position() = $CurrNode+1]"!][!//
      [!IF "node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemDTCClassRef) and node:existsAndTrue(as:ref(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemDTCClassRef)/DemImmediateNvStorage)"!][!//
        [!IF "(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_PRIMARY_MEMORY')"!][!//
          [!IF "($IntermediateDTCsMaxPriSize < ($NextNode - $CurrNode))"!][!//
            [!VAR "IntermediateDTCsMaxPriSize" = "$NextNode - $CurrNode"!][!//
          [!ENDIF!][!//
        [!ELSEIF "(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_SECONDARY_MEMORY')"!][!//
          [!IF "($IntermediateDTCsMaxSecSize < ($NextNode - $CurrNode))"!][!//
            [!VAR "IntermediateDTCsMaxSecSize" = "$NextNode - $CurrNode"!][!//
          [!ENDIF!][!//
        [!ELSEIF "(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_MIRROR_MEMORY')"!][!//
          [!IF "($IntermediateDTCsMaxMirSize < ($NextNode - $CurrNode))"!][!//
            [!VAR "IntermediateDTCsMaxMirSize" = "$NextNode - $CurrNode"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
    [!/* Check existence of internal events or non-combined events with immediate storage for a given origin */!][!//
    [!IF "$IntermediateDTCsMaxPriSize = 0"!][!//
      [!IF "(node:existsAndTrue(DemGeneral/DemImmediateStorageInternalEvents) and node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:refexists(DemDTCClassRef)) and DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_PRIMARY_MEMORY'])) or
            node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:refexists(DemDTCClassRef) and node:existsAndTrue(as:ref(DemDTCClassRef)/DemImmediateNvStorage) and DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_PRIMARY_MEMORY'])"!][!//
        [!VAR "IntermediateDTCsMaxPriSize" = "1"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$IntermediateDTCsMaxSecSize = 0"!][!//
      [!IF "((node:existsAndTrue(DemGeneral/DemImmediateStorageInternalEvents)) and node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:refexists(DemDTCClassRef)) and DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_SECONDARY_MEMORY'])) or
            node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:refexists(DemDTCClassRef) and node:existsAndTrue(as:ref(DemDTCClassRef)/DemImmediateNvStorage) and DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_SECONDARY_MEMORY'])"!][!//
        [!VAR "IntermediateDTCsMaxSecSize" = "1"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$IntermediateDTCsMaxMirSize = 0"!][!//
      [!IF "((node:existsAndTrue(DemGeneral/DemImmediateStorageInternalEvents)) and node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:refexists(DemDTCClassRef)) and DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_MIRROR_MEMORY'])) or
            node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:refexists(DemDTCClassRef) and node:existsAndTrue(as:ref(DemDTCClassRef)/DemImmediateNvStorage) and DemEventClass/DemEventDestination = 'DEM_DTC_ORIGIN_MIRROR_MEMORY'])"!][!//
        [!VAR "IntermediateDTCsMaxMirSize" = "1"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* Enable intermediate DTC status storage */!][!//
    [!IF "($IntermediateDTCsMaxPriSize != 0) or ($IntermediateDTCsMaxSecSize != 0) or ($IntermediateDTCsMaxMirSize != 0)"!][!//
      [!VAR "IntermediateNvStorage" = "'true'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/* === Create a macro for preparing the BSW distribution settings ===
   * This macro must be called once at the begining of the file!
   */!][!//
[!MACRO "CALCULATE_MULTICORE_SETTINGS"!][!//
[!INDENT "0"!][!//
  [!VAR "DemBSWDistributionOfEventReports" = "'false'"!][!//
  [!IF "node:existsAndTrue(DemGeneral/DemBSWDistribution/DemDistributedBSWEventReporting)"!][!//
    [!VAR "DemBSWDistributionOfEventReports" = "'true'"!][!//
  [!ENDIF!][!//
[!//
  [!IF "$DemBSWDistributionOfEventReports = 'true'"!][!//
    [!VAR "NumberOfSatteliteCores" = "count(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!][!//
  [!ELSE!][!//
    [!VAR "NumberOfSatteliteCores" = "'0'"!][!//
  [!ENDIF!][!//
[!//
  [!IF "node:exists(DemGeneral/DemBSWDistribution/DemMasterCoreId)"!][!//
    [!VAR "MasterCoreId" = "num:i(DemGeneral/DemBSWDistribution/DemMasterCoreId)"!][!//
  [!ELSE!][!//
    [!VAR "MasterCoreId" = "'0'"!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
* === Multi-event triggering Classes ===
* Calculates all multi-event triggering classes
*
* Classes are separated by #
* Class MultiEventTriggeringClassList entries are separated by ' '
*/!][!//
[!MACRO "CALC_MULTI_EVENT_CLASSES"!][!//
[!INDENT "0"!][!//
  [!/* create unique list of all configured multi-triggering elements */!][!//
  [!VAR "ClassIndex" = "0"!][!//
  [!VAR "MultiEventTriggeringSlaveGroupList" = "'#'"!][!//
  [!VAR "MultiEventTriggeringClassList" = "'#'"!][!//
  [!VAR "MultiEventTriggeringClassIndexList" = "'#'"!][!//
  [!VAR "SlaveIdx" = "0"!][!//
  [!LOOP "util:distinct(node:order(DemGeneral/DemMultiEventTriggering/eb-list::*, 'node:ref(DemMultiEventTriggeringMasterEventRef)/DemEventId'))"!][!//
    [!VAR "Behavior" = "./DemMultiEventTriggeringAlternativeBehavior"!][!//
    [!VAR "MasterId" = "node:ref(DemMultiEventTriggeringMasterEventRef)/DemEventId"!][!//
    [!VAR "SlaveCount" = "0"!][!//
    [!VAR "SlaveEventsGroup" = "concat($Behavior, ';')"!][!//
    [!/* get each class of slave events with their behavior */!][!//
    [!LOOP "util:distinct(node:order(./DemMultiEventTriggeringSlaveEventRef/eb-list::*, 'as:ref(.)/DemEventId'))"!][!//
      [!VAR "SlaveCount" = "$SlaveCount + 1"!][!//
      [!VAR "CurrentSlaveId" = "as:ref(.)/DemEventId"!][!//
      [!VAR "SlaveEventsGroup" = "concat($SlaveEventsGroup, $CurrentSlaveId, ' ')"!][!//
    [!ENDLOOP!][!//
    [!VAR "Index" = "0"!][!//
    [!/* strip end empty space */!][!//
    [!VAR "SlaveEventsGroup" = "normalize-space($SlaveEventsGroup)"!][!//
    [!/* check if class of slave events with their behavior was already found */!][!//
    [!IF "not(contains($MultiEventTriggeringSlaveGroupList, concat($SlaveEventsGroup, '#')))"!][!//
      [!VAR "MultiEventTriggeringClassList" = "concat($MultiEventTriggeringClassList, num:i($SlaveIdx), ' ', num:i($SlaveIdx + $SlaveCount), ' ', $Behavior, '#')"!][!//
      [!VAR "MultiEventTriggeringSlaveGroupList" = "concat($MultiEventTriggeringSlaveGroupList, $SlaveEventsGroup, '#')"!][!//
      [!VAR "SlaveIdx" = "$SlaveIdx + $SlaveCount"!][!//
      [!VAR "Index" = "$ClassIndex"!][!//
      [!VAR "ClassIndex" = "$ClassIndex + 1"!][!//
    [!ELSE!][!//
      [!LOOP "text:split($MultiEventTriggeringSlaveGroupList, '#')"!][!//
        [!IF "string(.) != $SlaveEventsGroup"!][!//
          [!VAR "Index" = "$Index + 1"!][!//
        [!ELSE!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!VAR "MultiEventTriggeringClassIndexList" = "concat($MultiEventTriggeringClassIndexList, $MasterId, ':', num:i($Index), '#')"!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
* === Multi Event Triggering ===
* Returns the multi event triggering index of given EventId
* Macro CALC_MULTI_EVENT_CLASSES must be called before!
*/!][!//
[!MACRO "GET_MULTI_EVENT_TRIGGERING_INDEX", "EVENT_ID"!][!//
[!INDENT "0"!][!//
  [!VAR "MultiEventTriggeringClassIdx" = "$NumMultiEventTriggering"!][!//
  [!LOOP "text:split($MultiEventTriggeringClassIndexList, '#')"!][!//
    [!IF "text:split(.,':')[position() = 1] = num:i($EVENT_ID)"!][!//
      [!VAR "MultiEventTriggeringClassIdx" = "text:split(.,':')[position() = 2]"!][!//
      [!/* multi event trigggering configuration item found, stop searching */!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
* === Number of multi-event classes ===
* Macro CALC_MULTI_EVENT_CLASSES must be called before!
*/!][!//
[!MACRO "GET_MULTI_EVENT_TRIGGERING_CLASS_COUNT"!][!//
[!INDENT "0"!][!//
  [!VAR "NumMultiEventTriggeringClasses" = "count(text:split($MultiEventTriggeringClassList, '#'))"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
* === Number of multi-event slave groups ===
* Macro CALC_MULTI_EVENT_CLASSES must be called before!
*/!][!//
[!MACRO "GET_MULTI_EVENT_TRIGGERING_SLAVE_COUNT"!][!//
[!INDENT "0"!][!//
  [!VAR "NumMultiEventTriggeringSlaves" = "num:i($SlaveIdx)"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!/*
* === Calculate number of NvM block Ids ===
* Macro GET_NVM_BLOCK_ID calculates the block id for configured NvM blocks!
*/!][!//
[!MACRO "GET_NVM_BLOCK_ID"!][!//
[!INDENT "0"!][!//
  [!VAR "DemNvRamBlockId" = "as:name(.)"!]
  [!VAR "DemNvRamBlockIdRefName" = "as:name(as:ref(DemNvRamBlockIdRef))"!]
  #if (defined [!"$DemNvRamBlockId"!])
  #error [!"$DemNvRamBlockId"!] already defined
  #endif
  /** \brief NvM block Id for block [!"$DemNvRamBlockId"!] */
  [!/* Naming shema according AUTOSAR R4.0 Rev 3 and newer*/!][!//
  #if defined (NvMConf_NvMBlockDescriptor_[!"$DemNvRamBlockIdRefName"!])
  #define [!"$DemNvRamBlockId"!] NvMConf_NvMBlockDescriptor_[!"$DemNvRamBlockIdRefName"!]
  [!/* Naming shema according AUTOSAR R3.1 Rev 4 till  R4.0 Rev 2*/!][!//
  #elif defined (NvM_[!"$DemNvRamBlockIdRefName"!])
  #define [!"$DemNvRamBlockId"!] NvM_[!"$DemNvRamBlockIdRefName"!]
  [!/* Naming shema according AUTOSAR R3.1 Rev 3 */!][!//
  #elif defined ([!"$DemNvRamBlockIdRefName"!])
  #define [!"$DemNvRamBlockId"!] [!"$DemNvRamBlockIdRefName"!]
  #else
  #error No symbolic name for NvM block [!"$DemNvRamBlockIdRefName"!] (refered by [!"$DemNvRamBlockId"!]) is generated
  #endif
[!ENDINDENT!][!//
[!ENDMACRO!][!//
