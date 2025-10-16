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

[!INCLUDE "../include/Dcm_common.m"!][!//

/* !LINKSTO Dcm.Dsn.File.RoutineControlOperations.ConfigC,1 */
[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]

 /* MISRA-C:2004 Deviation List
  *
  * MISRA-1) Deviated Rule: 11.4 (advisory)
  *     A cast should not be performed between a pointer to object type and a
  *     different pointer to object type.
  *
  *     Reason:
  *     A cast to unsigned is necessary here to copy data bit by bit and
  *     there is no alignment issues.
  *
  */

 /* MISRA-C:2012 Deviation List
  *
  *  MISRAC2012-1) Deviated Rule: 11.3 (required)
  *     "A cast should not be performed between a pointer to object type and a different pointer to
  *     object type."
  *
  *     Reason:
  *     A cast to UINT8 is necessary here to copy data bit by bit and to be flexible for all
  *     the types, being no alignment issues.
  *     There is no side effects.
  *
  *  MISRAC2012-2) Deviated Rule: 8.9 (advisory)
  *     "An object should be defined at block scope if its identifier only
  *     appears in a single function."
  *
  *     Reason:
  *     The object is defined in this way because the values that are stored
  *     in them are required for the next call of this function and should be
  *     hold in the data segment memory.
  *
  */

[!ENDIF!][!//
[!//
[!AUTOSPACING!][!//
[!//
[!VAR "BytesSwapNeededU16" = "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror))) and ((node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Start')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'UINT16')]/eb-list::*) or (node:existsAndTrue(DcmDspStopRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Stop')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'UINT16')]/eb-list::*)) or (node:existsAndTrue(DcmDspRequestResultsRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(node:name(.), 'RequestRes')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'UINT16')]/eb-list::*)))])"!]
[!VAR "BytesSwapNeededS16" = "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror))) and ((node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Start')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'SINT16')]/eb-list::*) or (node:existsAndTrue(DcmDspStopRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Stop')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'SINT16')]/eb-list::*)) or (node:existsAndTrue(DcmDspRequestResultsRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(node:name(.), 'RequestRes')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'SINT16')]/eb-list::*)))])"!]
[!VAR "BytesSwapNeededU32" = "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror))) and ((node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Start')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'UINT32')]/eb-list::*) or (node:existsAndTrue(DcmDspStopRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Stop')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'UINT32')]/eb-list::*)) or (node:existsAndTrue(DcmDspRequestResultsRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(node:name(.), 'RequestRes')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'UINT32')]/eb-list::*)))])"!]
[!VAR "BytesSwapNeededS32" = "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror))) and ((node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Start')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'SINT32')]/eb-list::*) or (node:existsAndTrue(DcmDspStopRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.), 'Stop')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'SINT32')]/eb-list::*)) or (node:existsAndTrue(DcmDspRequestResultsRoutineSupported) and (node:ref(DcmDspRoutineInfoRef)/eb-list::*[contains(node:name(.), 'RequestRes')]/eb-list::*/eb-list::*[contains(./DcmDspRoutineSignalType,'SINT32')]/eb-list::*)))])"!]
[!VAR "resetOfSignalArray" = "'false'"!][!//
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*"!][!//
  [!IF "node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror)))"!][!//
    [!IF "(node:exists(node:ref(./DcmDspRoutineInfoRef)/DcmDspStartRoutineIn/DcmDspStartRoutineInSignal/eb-list::*[./DcmDspRoutineSignalType != 'VARIABLE_LENGTH'])) or (node:exists(node:ref(./DcmDspRoutineInfoRef)/DcmDspStartRoutineOut/DcmDspStartRoutineOutSignal/eb-list::*[./DcmDspRoutineSignalType != 'VARIABLE_LENGTH']))"!]
      [!VAR "resetOfSignalArray" = "'true'"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
    [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
      [!IF "(node:exists(node:ref(./DcmDspRoutineInfoRef)/DcmDspRoutineStopIn/DcmDspRoutineStopInSignal/eb-list::*[./DcmDspRoutineSignalType != 'VARIABLE_LENGTH'])) or (node:exists(node:ref(./DcmDspRoutineInfoRef)/DcmDspRoutineStopOut/DcmDspRoutineStopOutSignal/eb-list::*[./DcmDspRoutineSignalType != 'VARIABLE_LENGTH']))"!]
        [!VAR "resetOfSignalArray" = "'true'"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!][!//
      [!IF "(node:exists(node:ref(./DcmDspRoutineInfoRef)/DcmDspRoutineRequestResIn/DcmDspRoutineRequestResInSignal/eb-list::*[./DcmDspRoutineSignalType != 'VARIABLE_LENGTH'])) or (node:exists(node:ref(./DcmDspRoutineInfoRef)/DcmDspRoutineRequestResOut/DcmDspRoutineRequestResOutSignal/eb-list::*[./DcmDspRoutineSignalType != 'VARIABLE_LENGTH']))"!]
        [!VAR "resetOfSignalArray" = "'true'"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!/*--- Generation macro for RoutineControl operation ---*/!][!//
[!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.RoutineMacroGeneration,1 */!][!//
[!MACRO "ROUTINECONTROL_GENERATE", "operation", "type"!]
[!IF "$operation = 'Start'"!][!//
  [!VAR "routineInput" = "'DcmDspStartRoutineIn'"!][!//
  [!VAR "routineOutput" = "'DcmDspStartRoutineOut'"!][!//
  [!VAR "inputSignal" = "'DcmDspStartRoutineInSignal'"!][!//
  [!VAR "outputSignal" = "'DcmDspStartRoutineOutSignal'"!][!//
  [!VAR "SVCID" = "'DCM_SVCID_ROUTINECONTROLSTART'"!]
[!ELSEIF "$operation = 'Stop'"!][!//
  [!VAR "routineInput" = "'DcmDspRoutineStopIn'"!][!//
  [!VAR "routineOutput" = "'DcmDspRoutineStopOut'"!][!//
  [!VAR "inputSignal" = "'DcmDspRoutineStopInSignal'"!][!//
  [!VAR "outputSignal" = "'DcmDspRoutineStopOutSignal'"!][!//
  [!VAR "SVCID" = "'DCM_SVCID_ROUTINECONTROLSTOP'"!]
[!ELSEIF "$operation = 'RequestResults'"!][!//
  [!VAR "routineInput" = "'DcmDspRoutineRequestResIn'"!][!//
  [!VAR "routineOutput" = "'DcmDspRoutineRequestResOut'"!][!//
  [!VAR "inputSignal" = "'DcmDspRoutineRequestResInSignal'"!][!//
  [!VAR "outputSignal" = "'DcmDspRoutineRequestResOutSignal'"!][!//
  [!VAR "SVCID" = "'DCM_SVCID_ROUTINECONTROLROUTINERESULTS'"!]
[!ELSE!][!//
  [!ERROR "Macro ROUTINECONTROL_GENERATE called with invalid 'operation' argument"!][!//
[!ENDIF!][!//
[!IF "$type = 'OBD'"!][!//
  [!VAR "prefixType" = "'OBD_'"!][!//
[!ELSEIF "$type = 'UDS'"!][!//
  [!VAR "prefixType" = "'UDS_'"!][!//
[!ELSE!][!//
  [!ERROR "Macro ROUTINECONTROL_GENERATE called with invalid 'type' argument"!][!//
[!ENDIF!][!//
[!//
[!VAR "inputSignalNr" = "count(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineInput]/eb-list::*[node:name(.) = $inputSignal]/eb-list::*)"!][!//
[!VAR "outputSignalNr" = "count(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineOutput]/eb-list::*[node:name(.) = $outputSignal]/eb-list::*)"!][!//
[!VAR "inputVarSignalNr" = "count(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineInput]/eb-list::*[node:name(.) = $inputSignal]/eb-list::*[(DcmDspRoutineSignalType = 'VARIABLE_LENGTH')])"!][!//
[!VAR "outputVarSignalNr" = "count(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineOutput]/eb-list::*[node:name(.) = $outputSignal]/eb-list::*[(DcmDspRoutineSignalType = 'VARIABLE_LENGTH')])"!][!//
[!VAR "DcmRoutineVarLenInBytes" = "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineVariableLengthInBytes"!][!//
[!//
[!CR!]
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC(Std_ReturnType, DCM_CODE) Dcm_[!"node:name(.)"!]_[!"$operation"!](
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
{
  [!INDENT "2"!][!//
    [!VAR "RoutineFixedLength" = "'false'"!][!//
    [!VAR "RoutineVariableInSignals" = "'false'"!][!//
    [!VAR "RoutineVariableOutSignals" = "'false'"!][!//
    [!VAR "ResponseLengthWithoutCurrentDataLength" = "'false'"!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.DcmDspRoutineFixedLength,1 */!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.AUTOSAR40.Interface,1 */!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.AUTOSAR42.Interface,1 */!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.Default40.Interface,1 */!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.Default42.Interface,1 */!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.Disabled40.Interface,1 */!][!//
    [!/* !LINKSTO Dcm.EB.RoutineControl.Disabled42.Interface,1 */!][!//
    [!IF " (node:exists(DcmDspRoutineUsePortASRVersion) and
            ((DcmDspRoutineUsePortASRVersion = 'AUTOSAR_42') or
              ((DcmDspRoutineUsePortASRVersion = 'Default') and
              (as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmServiceAPI/DcmDefaultASRServiceAPI = 'AUTOSAR_42')
              )
            )
          )
          or
          (
            not(node:exists(DcmDspRoutineUsePortASRVersion))
            and (as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmServiceAPI/DcmDefaultASRServiceAPI = 'AUTOSAR_42')
          )"!][!//
      [!VAR "RoutineFixedLength" = "'true'"!][!//
      [!IF "((node:refvalid(DcmDspRoutineInfoRef)) and ($inputVarSignalNr > 0))"!][!//
        [!VAR "RoutineFixedLength" = "'false'"!][!//
        [!VAR "RoutineVariableInSignals" = "'true'"!][!//
      [!ENDIF!][!//
      [!IF "((node:refvalid(DcmDspRoutineInfoRef)) and ($outputVarSignalNr > 0))"!][!//
        [!VAR "RoutineFixedLength" = "'false'"!][!//
        [!VAR "RoutineVariableOutSignals" = "'true'"!][!//
      [!ENDIF!][!//
      [!IF "($RoutineVariableInSignals = 'true') and ($RoutineVariableOutSignals = 'false')"!][!//
        [!VAR "ResponseLengthWithoutCurrentDataLength" = "'true'"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!IF "node:existsAndTrue(DcmDspRoutineFixedLength)"!][!//
        [!VAR "RoutineFixedLength" = "'true'"!][!//
        [!VAR "RoutineVariableInSignals" = "'false'"!][!//
        [!VAR "RoutineVariableOutSignals" = "'false'"!][!//
      [!ELSE!][!//
        [!VAR "RoutineFixedLength" = "'false'"!][!//
        [!VAR "RoutineVariableInSignals" = "'true'"!][!//
        [!VAR "RoutineVariableOutSignals" = "'true'"!][!//
        [!IF "($outputVarSignalNr = 0)"!][!//
          [!VAR "ResponseLengthWithoutCurrentDataLength" = "'true'"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!]
  [!//
  [!/* !LINKSTO SWS_Dcm_00641,1 */!][!//
  [!VAR "endiannessconversionrequired"="0"!][!//
  [!IF "($inputSignalNr > 0 or $outputSignalNr > 0)"!][!//
    [!IF "($inputSignalNr > 0)"!][!//
      [!LOOP "node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineInput]/eb-list::*[node:name(.) = $inputSignal]/eb-list::*"!][!//
        [!IF "contains(DcmDspRoutineSignalType, '16') or contains(DcmDspRoutineSignalType, '32')"!][!//
          [!VAR "endiannessconversionrequired"="1"!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!//
    [!IF "$endiannessconversionrequired != 1"!][!//
      [!IF "($outputSignalNr > 0)"!][!//
      [!LOOP "node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineOutput]/eb-list::*[node:name(.) = $outputSignal]/eb-list::*"!][!//
        [!IF "contains(DcmDspRoutineSignalType, '16') or contains(DcmDspRoutineSignalType, '32')"!][!//
            [!VAR "endiannessconversionrequired"="1"!][!//
            [!BREAK!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!//
    Std_ReturnType ServiceProcessStatus = DCM_E_NOT_OK;
  [!IF "($RoutineFixedLength = 'false')"!][!//
    /* Variable length input/output signal length */
    uint16 CurrentDataLength = 0U;
  [!ENDIF!][!//
  [!IF "($inputSignalNr > 0 or $outputSignalNr > 0)"!][!//
    [!IF "$endiannessconversionrequired = 1"!][!//
    [!CR!]
    [!INDENT "0"!]
#if (DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)
#if (DCM_NUM_PROTOCOL > 1U)
    [!ENDINDENT!]
      /* Get current protocol id */
      uint8 ProtocolInstanceIndex = Dcm_Dsl_Supervisor_GetProcessingProtocolIndex(
      [!WS "24"!]DCM_RX_CONNECTION_ID_FROM_RXPDUID(pMsgContext->dcmRxPduId), DCM_EXTERNAL);
      [!CR!]
      /* Get protocol configuration for current HSM instance */
      CONSTP2CONST(Dcm_ProtocolConfigType, AUTOMATIC, DCM_CONST) CurProtocolConfig =
      [!WS "54"!]&DCM_PROTOCOL_CONFIG(ProtocolInstanceIndex);
      [!CR!]
      [!INDENT "0"!]
#else
      [!ENDINDENT!]
      [!CR!]
      /* Get protocol configuration for current HSM instance */
      CONSTP2CONST(Dcm_ProtocolConfigType, AUTOMATIC, DCM_CONST) CurProtocolConfig =
      [!WS "54"!]&DCM_PROTOCOL_CONFIG(0U);
      [!CR!]
      [!INDENT "0"!]
#endif /* #if (DCM_NUM_PROTOCOL > 1) */
#endif /*(DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)*/
    [!ENDINDENT!]
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!//
  [!VAR "BooleanArrayCount"="0"!][!//
  [!VAR "Sint16ArrayCount"="0"!][!//
  [!VAR "Sint32ArrayCount"="0"!][!//
  [!VAR "Sint8ArrayCount"="0"!][!//
  [!VAR "Uint16ArrayCount"="0"!][!//
  [!VAR "Uint32ArrayCount"="0"!][!//
  [!VAR "Uint8ArrayCount"="0"!][!//
    /* Parameter to store the length of input data (2U indicates the 2-byte RoutineID) received */
    Dcm_MsgLenType InDataLength = pMsgContext->reqDataLen - 2U;
  [!CR!]
  [!/* --- Build a list with the configured input signals which will be later used to extract the input parameters for the routine function calls  --- */!][!//
  [!VAR "inTotalDataLength"="0"!][!//
  [!VAR "inFixedDataLength"="0"!][!//
  [!VAR "inParamList"="''"!][!//
  [!VAR "ArrayTypeSignalsList"="''"!][!//
  [!VAR "NumberOfArrayTypeSignals"="0"!][!//
  [!VAR "InVarSignalShiftPos"="0"!][!//
  [!//
  [!IF "($inputSignalNr > 0)"!][!//
    [!LOOP "util:distinct(node:order(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineInput]/eb-list::*[node:name(.) = $inputSignal]/eb-list::*, 'DcmDspRoutineSignalPos'))"!][!//
      [!VAR "inTotalDataLength"="DcmDspRoutineSignalPos"!][!//
      [!VAR "inFixedDataLength"="$inTotalDataLength "!][!//
      [!IF "DcmDspRoutineSignalType = 'BOOLEAN'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'BooleanArray['), num:i($BooleanArrayCount), '], ')"!][!//
        [!VAR "BooleanArrayCount"="$BooleanArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'SINT16'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Sint16Array['), num:i($Sint16ArrayCount), '], ')"!][!//
        [!VAR "Sint16ArrayCount"="$Sint16ArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'SINT32'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Sint32Array['), num:i($Sint32ArrayCount), '], ')"!][!//
        [!VAR "Sint32ArrayCount"="$Sint32ArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'SINT8'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Sint8Array['), num:i($Sint8ArrayCount), '], ')"!][!//
        [!VAR "Sint8ArrayCount"="$Sint8ArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'UINT16'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Uint16Array['), num:i($Uint16ArrayCount), '], ')"!][!//
        [!VAR "Uint16ArrayCount"="$Uint16ArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'UINT32'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Uint32Array['), num:i($Uint32ArrayCount), '], ')"!][!//
        [!VAR "Uint32ArrayCount"="$Uint32ArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'UINT8'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Uint8Array['), num:i($Uint8ArrayCount), '], ')"!][!//
        [!VAR "Uint8ArrayCount"="$Uint8ArrayCount + 1"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'SINT16_N'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('&Dcm_RoutineControlOperations_' , $prefixType, 'Sint16Array['), num:i($Sint16ArrayCount), '], ')"!][!//
        [!VAR "Sint16ArrayCount"="$Sint16ArrayCount + (./DcmDspRoutineSignalLength div 16)"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'SINT32_N'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('&Dcm_RoutineControlOperations_' , $prefixType, 'Sint32Array['), num:i($Sint32ArrayCount), '], ')"!][!//
        [!VAR "Sint32ArrayCount"="$Sint32ArrayCount + (./DcmDspRoutineSignalLength div 32)"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'SINT8_N'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('&Dcm_RoutineControlOperations_' , $prefixType, 'Sint8Array['), num:i($Sint8ArrayCount), '], ')"!][!//
        [!VAR "Sint8ArrayCount"="$Sint8ArrayCount + (./DcmDspRoutineSignalLength div 8)"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'UINT16_N'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('&Dcm_RoutineControlOperations_' , $prefixType, 'Uint16Array['), num:i($Uint16ArrayCount), '], ')"!][!//
        [!VAR "Uint16ArrayCount"="$Uint16ArrayCount + (./DcmDspRoutineSignalLength div 16)"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'UINT32_N'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('&Dcm_RoutineControlOperations_' , $prefixType, 'Uint32Array['), num:i($Uint32ArrayCount), '], ')"!][!//
        [!VAR "Uint32ArrayCount"="$Uint32ArrayCount + (./DcmDspRoutineSignalLength div 32)"!][!//
      [!ELSEIF "DcmDspRoutineSignalType = 'UINT8_N'"!][!//
        [!VAR "inParamList"="concat($inParamList, concat('&Dcm_RoutineControlOperations_' , $prefixType, 'Uint8Array['), num:i($Uint8ArrayCount), '], ')"!][!//
        [!VAR "Uint8ArrayCount"="$Uint8ArrayCount + (./DcmDspRoutineSignalLength div 8)"!][!//
      [!ELSE!]
        [!IF "((DcmDspRoutineSignalPos mod 8) = 0)"!][!//
          [!/* --- If Variable length signal is byte aligned --- */!][!//
          [!VAR "inParamList"="concat($inParamList, '&(pMsgContext->reqData[', num:i(2 + ($inTotalDataLength div 8)), ']), ')"!][!//
        [!ELSE!][!//
          [!/* --- If Variable length signal is not byte aligned --- */!][!//
          [!VAR "inParamList"="concat($inParamList, '&(pMsgContext->reqData[', num:i(2 + (($inTotalDataLength) div 8)+ 1), ']), ')"!][!//
          [!VAR "InVarSignalShiftPos"="$inFixedDataLength"!][!//
        [!ENDIF!][!//
        [!VAR "inTotalDataLength"="$inTotalDataLength + DcmDspRoutineSignalLength"!][!//
      [!ENDIF!][!//
      [!/* --- Adding length of last signal , if it is not variable length --- */!][!//
      [!IF "DcmDspRoutineSignalPos = num:max(../eb-list::*/DcmDspRoutineSignalPos)"!][!//
        [!IF "not(DcmDspRoutineSignalType = 'VARIABLE_LENGTH')"!][!//
          [!VAR "inTotalDataLength"="$inTotalDataLength + DcmDspRoutineSignalLength"!][!//
          [!/* --- inFixedDataLength will be equal to the total data length --- */!][!//
          [!VAR "inFixedDataLength"="$inTotalDataLength "!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!/* --- Build a list with the configured output signals which will be later used to extract the output parameters for the routine function calls  --- */!][!//
  [!VAR "outFixedDataLength"="0"!][!//
  [!VAR "outVarCount"="0"!][!//
  [!VAR "outParamList"="''"!][!//
  [!VAR "outParamListAddress"="''"!][!//
  [!VAR "outVariableDataLength"="0"!][!//
  [!//
  [!IF "($outputSignalNr > 0)"!][!//
    [!LOOP "util:distinct(node:order(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineOutput]/eb-list::*[node:name(.) = $outputSignal]/*
                          , 'DcmDspRoutineSignalPos'))"!][!//
      [!VAR "outFixedDataLength"="DcmDspRoutineSignalPos"!][!//
      [!IF "DcmDspRoutineSignalType = 'BOOLEAN'"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'BooleanArray['), num:i($BooleanArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'BooleanArray['), num:i($BooleanArrayCount), '], ')"!][!//
        [!VAR "BooleanArrayCount"="$BooleanArrayCount + 1"!][!//
      [!ELSEIF "contains(DcmDspRoutineSignalType, 'SINT16')"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Sint16Array['), num:i($Sint16ArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'Sint16Array['), num:i($Sint16ArrayCount), '], ')"!][!//
        [!IF "DcmDspRoutineSignalType = 'SINT16'"!][!//
          [!VAR "Sint16ArrayCount"="$Sint16ArrayCount + 1"!][!//
        [!ELSE!][!//
          [!VAR "Sint16ArrayCount"="$Sint16ArrayCount + (./DcmDspRoutineSignalLength div 16)"!][!//
        [!ENDIF!][!//
      [!ELSEIF "contains(DcmDspRoutineSignalType, 'SINT32')"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Sint32Array['), num:i($Sint32ArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'Sint32Array['), num:i($Sint32ArrayCount), '], ')"!][!//
        [!IF "DcmDspRoutineSignalType = 'SINT32'"!][!//
        [!VAR "Sint32ArrayCount"="$Sint32ArrayCount + 1"!][!//
        [!ELSE!][!//
          [!VAR "Sint32ArrayCount"="$Sint32ArrayCount + (./DcmDspRoutineSignalLength div 32)"!][!//
        [!ENDIF!][!//
      [!ELSEIF "contains(DcmDspRoutineSignalType, 'SINT8')"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Sint8Array['), num:i($Sint8ArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'Sint8Array['), num:i($Sint8ArrayCount), '], ')"!][!//
        [!IF "DcmDspRoutineSignalType = 'SINT8'"!][!//
          [!VAR "Sint8ArrayCount"="$Sint8ArrayCount + 1"!][!//
        [!ELSE!][!//
          [!VAR "Sint8ArrayCount"="$Sint8ArrayCount + (./DcmDspRoutineSignalLength div 8)"!][!//
        [!ENDIF!][!//
      [!ELSEIF "contains(DcmDspRoutineSignalType, 'UINT16')"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Uint16Array['), num:i($Uint16ArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'Uint16Array['), num:i($Uint16ArrayCount), '], ')"!][!//
        [!IF "DcmDspRoutineSignalType = 'UINT16'"!][!//
          [!VAR "Uint16ArrayCount"="$Uint16ArrayCount + 1"!][!//
        [!ELSE!][!//
          [!VAR "Uint16ArrayCount"="$Uint16ArrayCount + (./DcmDspRoutineSignalLength div 16)"!][!//
        [!ENDIF!][!//
      [!ELSEIF "contains(DcmDspRoutineSignalType, 'UINT32')"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Uint32Array['), num:i($Uint32ArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'Uint32Array['), num:i($Uint32ArrayCount), '], ')"!][!//
        [!IF "DcmDspRoutineSignalType = 'UINT32'"!][!//
          [!VAR "Uint32ArrayCount"="$Uint32ArrayCount + 1"!][!//
        [!ELSE!][!//
          [!VAR "Uint32ArrayCount"="$Uint32ArrayCount + (./DcmDspRoutineSignalLength div 32)"!][!//
        [!ENDIF!][!//
      [!ELSEIF "contains(DcmDspRoutineSignalType, 'UINT8')"!][!//
        [!VAR "outParamList"="concat($outParamList, concat('Dcm_RoutineControlOperations_', $prefixType, 'Uint8Array['), num:i($Uint8ArrayCount), '], ')"!][!//
        [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&Dcm_RoutineControlOperations_', $prefixType, 'Uint8Array['), num:i($Uint8ArrayCount), '], ')"!][!//
        [!IF "DcmDspRoutineSignalType = 'UINT8'"!][!//
          [!VAR "Uint8ArrayCount"="$Uint8ArrayCount + 1"!][!//
        [!ELSE!][!//
          [!VAR "Uint8ArrayCount"="$Uint8ArrayCount + (./DcmDspRoutineSignalLength div 8)"!][!//
        [!ENDIF!][!//
      [!ELSE!]
        [!VAR "outVariableDataLength"="DcmDspRoutineSignalLength"!][!//
        [!IF "$CommonBufferCount = 0"!][!//
          [!/* Rx and Tx buffer are different */!][!//
          [!IF "((DcmDspRoutineSignalPos mod 8) = 0)"!][!//
            [!/* Variable length signal is byte aligned */!][!//
            [!VAR "outParamListAddress"="concat($outParamListAddress, '&(pMsgContext->resData[', num:i(3 + ($outFixedDataLength div 8)), ']), ')"!][!//
          [!ELSE!][!//
            [!/* Variable length signal is not byte aligned */!][!//
            [!VAR "outParamListAddress"="concat($outParamListAddress, '&(pMsgContext->resData[', num:i(3 + ($outFixedDataLength div 8) + 1 ), ']), ')"!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!/* Rx and Tx buffer are same, using a separate buffer */!][!//
          [!VAR "outParamListAddress"="concat($outParamListAddress, concat('&(Dcm_RoutineControlOperations_', $prefixType, 'RoutineControlBuffer['), num:i(0), ']), ')"!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
      [!IF "not(DcmDspRoutineSignalType = 'VARIABLE_LENGTH')"!][!//
        [!/* --- Adding length of last signal --- */!][!//
        [!IF "DcmDspRoutineSignalPos = num:max(../eb-list::*/DcmDspRoutineSignalPos)"!][!//
        [!VAR "outFixedDataLength"="$outFixedDataLength + DcmDspRoutineSignalLength"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "outVarCount"="$outVarCount + 1"!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!//
  [!IF "($RoutineFixedLength = 'false') and ($inputVarSignalNr > 0)"!][!//
    [!IF "$DcmRoutineVarLenInBytes = 'false'"!][!//
      /* Total received length for the variable length input signal minus the fixed data length,
      [!WS "1"!]* in bits. */
      [!IF "($inFixedDataLength = 0)"!][!//
        CurrentDataLength = (uint16)(((pMsgContext->reqDataLen) - 2U) * 8U);
      [!ELSE!][!//
        CurrentDataLength = (uint16)((((pMsgContext->reqDataLen) - 2U) * 8U) - [!"num:i($inFixedDataLength)"!]U);
      [!ENDIF!][!//
    [!ELSE!][!//
      /* Total received length for the variable length input signal minus the fixed data length,
      [!WS "1"!]* in bytes */
      [!IF "($inFixedDataLength = 0)"!][!//
        CurrentDataLength = (uint16)((pMsgContext->reqDataLen) - 2U);
      [!ELSE!][!//
        CurrentDataLength = (uint16)(((pMsgContext->reqDataLen) - 2U) - [!"num:i($inFixedDataLength div 8)"!]U);
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!CR!][!//
  [!ENDIF!][!//
  if (DCM_INITIAL == OpStatus)
  {
  [!INDENT "4"!][!//
  /* Total input data length check */
  [!VAR "inTotalDataLengthBytes"="num:i(($inTotalDataLength + 7) div 8)"!][!//
  [!VAR "inFixedDataLengthBytes"="num:i(($inFixedDataLength + 7) div 8)"!][!//
  [!IF "($inputSignalNr > 0)"!][!//
    [!IF "($inFixedDataLength > 0) and ($inTotalDataLength > $inFixedDataLength)"!][!//
    [!/* --- Both fixed and variable length signals are configured --- */!][!//
    if ((InDataLength >= [!"num:i($inFixedDataLengthBytes)"!]U) && (InDataLength <= [!"num:i($inTotalDataLengthBytes)"!]U))
    [!ELSEIF "($inFixedDataLength > 0)"!][!//
    [!/* --- Only fixed length signals are configured --- */!][!//
    if (InDataLength == [!"num:i($inFixedDataLengthBytes)"!]U)
    [!ELSEIF "($inTotalDataLength > 0)"!][!//
    [!/* --- Only variable length signals are configured --- */!][!//
    if (InDataLength <= [!"num:i($inTotalDataLengthBytes)"!]U)
    [!ENDIF!][!//
  [!ELSE!][!//
    [!/* --- No input signals are configured --- */!][!//
    if (InDataLength == 0U)
  [!ENDIF!][!//
    {
  [!CR!]
  [!ENDINDENT!][!//
  [!IF "($outFixedDataLength + $outVariableDataLength > 0)"!][!//
    [!INDENT "6"!][!//
    if (DCM_GET_BYTES([!"num:i($outFixedDataLength + $outVariableDataLength)"!]U) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH > pMsgContext->resMaxDataLen)
    {
    [!ENDINDENT!][!//
    [!INDENT "8"!][!//
      /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.ResponseTooLong.TransmitNRC0x14,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.ResponseTooLong.TransmitNRC0x14,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.ResponseTooLong.TransmitNRC0x14,1 */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_RESPONSETOOLONG);
      ServiceProcessStatus = DCM_E_NOT_OK;
    [!ENDINDENT!][!//
    [!INDENT "6"!][!//
    }
    else
    {
    [!ENDINDENT!][!//
  [!ELSE!][!//
    [!INDENT "6"!][!//
    {
    [!ENDINDENT!][!//
  [!ENDIF!][!//
  [!INDENT "8"!][!//
  [!IF "$resetOfSignalArray = 'true'"!][!//
    Dcm_Dsp_RoutineControl_ClearInternalArrays();
  [!CR!]
  [!ENDIF!][!//
  [!VAR "inVarCount"="0"!][!//
  [!VAR "Sint16ArrayElementsIn"="0"!][!//
  [!VAR "Sint32ArrayElementsIn"="0"!][!//
  [!VAR "Uint16ArrayElementsIn"="0"!][!//
  [!VAR "Uint32ArrayElementsIn"="0"!][!//
  [!IF "($inputSignalNr > 0)"!][!//
    [!LOOP "util:distinct(node:order(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineInput]/eb-list::*[node:name(.) = $inputSignal]/eb-list::*, 'DcmDspRoutineSignalPos'))"!][!//
      [!IF "DcmDspRoutineSignalType != 'VARIABLE_LENGTH'"!][!//
        [!/* --- Search for fixed signals and copy them to their buffers --- */!][!//
        [!VAR "SignalBaseBitSize" = "0"!][!//
        [!VAR "BaseTypeSignal"="''"!][!//
        [!IF "not(contains(DcmDspRoutineSignalType,'_N'))"!][!//
          [!VAR "BaseTypeSignal"="concat('&',text:split($inParamList, ', ')[position() = ($inVarCount + 1)])"!][!//
          [!IF "DcmDspRoutineSignalType = 'BOOLEAN'"!][!//
            [!VAR "SignalBaseBitSize" = "1"!][!//
          [!ELSE!][!//
            [!VAR "SignalBaseBitSize" = "num:integer(substring-after(DcmDspRoutineSignalType, 'INT'))"!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!VAR "SignalBaseBitSize" = "num:integer(substring-before(substring-after(DcmDspRoutineSignalType, 'INT'),'_' ))"!][!//
          [!VAR "BaseTypeSignal"="text:split($inParamList, ', ')[position() = ($inVarCount + 1)]"!][!//
        [!ENDIF!][!//
        /* Deviation MISRAC2012-1 <+2> */
        /* Deviation MISRA-1 <+2> */
        [!/* !LINKSTO Dcm.EB.RoutineControl.RoutineControlOptionRecord,1 */!][!//
        Dcm_DspInternal_CopySignalData((P2VAR(uint8, AUTOMATIC, DCM_VAR))&(pMsgContext->reqData[2]),
                            [!WS "31"!](P2VAR(uint8, AUTOMATIC, DCM_VAR))[!"$BaseTypeSignal"!],
                            [!WS "31"!][!"DcmDspRoutineSignalPos"!]U,
                            [!WS "31"!]0U,
                            [!WS "31"!][!"DcmDspRoutineSignalLength"!]U,
                            [!WS "31"!]DCM_COPY_FROM_INBUFFER_OPAQUE,
                            [!WS "31"!]DCM_BYTE_DIRECTION_INCREMENT);
        [!CR!]
      [!ELSE!][!//
        [!IF "not((DcmDspRoutineSignalPos mod 8) = 0)"!][!//
          [!WS "2"!]/* Shifting bits of the variable length signal to the right until the next byte boundary */
          [!WS "2"!]Dcm_DspInternal_ShiftBitsInBuffer((P2VAR(uint8, AUTOMATIC, DCM_VAR))&(pMsgContext->reqData[2]),
                            [!WS "36"!][!"num:i($InVarSignalShiftPos)"!]U,
                            [!WS "36"!][!"num:i($InVarSignalShiftPos + (8 -($InVarSignalShiftPos mod 8)))"!]U,
                            [!WS "36"!][!"DcmDspRoutineSignalLength"!]U,
                            [!WS "36"!]FALSE);
          [!CR!]
      [!ENDIF!][!//
      [!ENDIF!][!//
      [!/*--- Calculate how many input signals are in the 16 and 32 bit arrays. These will be used for the endianness conversion ---*/!][!//
      [!IF "(DcmDspRoutineSignalType = 'SINT16')"!][!//
        [!VAR "Sint16ArrayElementsIn"="$Sint16ArrayElementsIn + 1"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'SINT16_N')"!][!//
        [!VAR "Sint16ArrayElementsIn"="$Sint16ArrayElementsIn + (DcmDspRoutineSignalLength div 16)"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'UINT16')"!][!//
        [!VAR "Uint16ArrayElementsIn"="$Uint16ArrayElementsIn + 1"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'UINT16_N')"!][!//
        [!VAR "Uint16ArrayElementsIn"="$Uint16ArrayElementsIn + (DcmDspRoutineSignalLength div 16)"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'SINT32')"!][!//
        [!VAR "Sint32ArrayElementsIn"="$Sint32ArrayElementsIn + 1"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'SINT32_N')"!][!//
        [!VAR "Sint32ArrayElementsIn"="$Sint32ArrayElementsIn + (DcmDspRoutineSignalLength div 32)"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'UINT32')"!][!//
        [!VAR "Uint32ArrayElementsIn"="$Uint32ArrayElementsIn + 1"!][!//
      [!ELSEIF "(DcmDspRoutineSignalType = 'UINT32_N')"!][!//
        [!VAR "Uint32ArrayElementsIn"="$Uint32ArrayElementsIn + (DcmDspRoutineSignalLength div 32)"!][!//
      [!ENDIF!][!//
      [!VAR "inVarCount"="$inVarCount + 1"!][!//
    [!ENDLOOP!][!//
    [!/*--- If there are IN elements in the 16/32 bit arrays, perform endianness if needed ---*/!][!//
    [!IF "($Uint16ArrayElementsIn > 0) or ($Sint16ArrayElementsIn > 0) or ($Uint32ArrayElementsIn > 0) or ($Sint32ArrayElementsIn > 0)"!][!//
        [!INDENT "0"!][!//
        #if (DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)
        [!ENDINDENT!][!//
        /* !LINKSTO Dcm.EB.RoutineControl.EndiannessEnabled,1 */
        if(CurProtocolConfig->EndiannessConversion == TRUE)
        {
      [!IF "($Uint16ArrayElementsIn > 0)"!][!//
        [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_U16(&Dcm_RoutineControlOperations_[!"$prefixType"!]Uint16Array[0], [!"num:i($Uint16ArrayElementsIn)"!]U);[!//
        [!CR!]
      [!ENDIF!][!//
      [!IF "($Sint16ArrayElementsIn > 0)"!][!//
        [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_S16(&Dcm_RoutineControlOperations_[!"$prefixType"!]Sint16Array[0], [!"num:i($Sint16ArrayElementsIn)"!]U);[!//
        [!CR!]
      [!ENDIF!][!//
      [!IF "($Uint32ArrayElementsIn > 0)"!][!//
        [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_U32(&Dcm_RoutineControlOperations_[!"$prefixType"!]Uint32Array[0], [!"num:i($Uint32ArrayElementsIn)"!]U);[!//
        [!CR!]
      [!ENDIF!][!//
      [!IF "($Sint32ArrayElementsIn > 0)"!][!//
        [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_S32(&Dcm_RoutineControlOperations_[!"$prefixType"!]Sint32Array[0], [!"num:i($Sint32ArrayElementsIn)"!]U);[!//
        [!CR!]
      [!ENDIF!][!//
        }
        [!INDENT "0"!][!//
        #endif /*(DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)*/
        [!ENDINDENT!][!//
        [!CR!]
      [!ENDIF!][!//
  [!//
  [!ENDIF!][!//
  [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.FunctionCallGeneration,1 */!][!//
  [!/* !LINKSTO Dcm.EB.RoutineControl.CallSWCFunction,1 */!][!//
  [!IF "node:existsAndTrue(DcmDspRoutineUsePort)"!][!//
    [!IF "($RoutineFixedLength = 'false')"!][!//
      [!IF "$RoutineVariableOutSignals = 'true'"!][!//
        [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.CSVariableOut,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.CS.VariableInFixedOut.ASR40,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,1 */!][!//
        ServiceProcessStatus = Rte_Call_RoutineServices_[!"node:name(.)"!]_[!"$operation"!]([!"$inParamList"!]DCM_INITIAL, [!"$outParamListAddress"!]&CurrentDataLength, ErrorCode);
      [!ELSE!][!//
        [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.CS.VariableInFixedOut.ASR42,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.Callout.VariableInFixedOut.ASR42,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,1 */!][!//
        ServiceProcessStatus = Rte_Call_RoutineServices_[!"node:name(.)"!]_[!"$operation"!]([!"$inParamList"!]DCM_INITIAL, [!"$outParamListAddress"!]CurrentDataLength, ErrorCode);
      [!ENDIF!][!//
    [!ELSE!][!//
      [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.CS.FixedInFixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.CS.AUTOSAR42.FixedInFixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.CS.AUTOSAR42.FixedInFixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.CS.AUTOSAR42.FixedInFixedOut,1 */!][!//
      ServiceProcessStatus = Rte_Call_RoutineServices_[!"node:name(.)"!]_[!"$operation"!]([!"$inParamList"!]DCM_INITIAL, [!"$outParamListAddress"!]ErrorCode);
    [!ENDIF!][!//
  [!ELSE!][!//
    [!IF "$RoutineFixedLength = 'false'"!][!//
      [!IF "$RoutineVariableOutSignals = 'true'"!][!//
        [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.Callout.VariableOut,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.VarInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,1 */!][!//
        ServiceProcessStatus = [!"node:ref(concat('DcmDsp',$operation,'RoutineFnc'))"!]([!"$inParamList"!]DCM_INITIAL, [!"$outParamListAddress"!]&CurrentDataLength, ErrorCode);
      [!ELSE!][!//
        [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.Callout.VariableInFixedOut.ASR40,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,1 */!][!//
        [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,1 */!][!//
        ServiceProcessStatus = [!"node:ref(concat('DcmDsp',$operation,'RoutineFnc'))"!]([!"$inParamList"!]DCM_INITIAL, [!"$outParamListAddress"!]CurrentDataLength, ErrorCode);
      [!ENDIF!][!//
    [!ELSE!][!//
      [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InOperation.Callout.FixedInFixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartIn.Callout.AUTOSAR42.FixedInFixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopIn.Callout.AUTOSAR42.FixedInFixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsIn.Callout.AUTOSAR42.FixedInFixedOut,1 */!][!//
      ServiceProcessStatus = [!"node:ref(concat('DcmDsp',$operation,'RoutineFnc'))"!]([!"$inParamList"!]DCM_INITIAL, [!"$outParamListAddress"!]ErrorCode);
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!CR!]
  [!ENDINDENT!][!//
  [!INDENT "6"!][!//
  }
  [!ENDINDENT!][!//
  [!INDENT "4"!][!//
  }
  else
  {
    [!INDENT "6"!][!//
    [!/* !LINKSTO SWS_Dcm_01140,1 */!][!//
    /* Invalid total data length */
    *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    ServiceProcessStatus = DCM_E_NOT_OK;
    [!ENDINDENT!][!//
  }
  [!ENDINDENT!][!//
  }
  else
  {
  [!INDENT "4"!][!//
  [!/* !LINKSTO Dcm.EB.RoutineControl.CallSWCFunction,1 */!][!//
  [!IF "node:existsAndTrue(DcmDspRoutineUsePort)"!][!//
    [!IF "($RoutineFixedLength = 'false')"!][!//
      [!IF "$RoutineVariableOutSignals = 'true'"!][!//
        ServiceProcessStatus = Rte_Call_RoutineServices_[!"node:name(.)"!]_[!"$operation"!]([!"$inParamList"!]OpStatus, [!"$outParamListAddress"!]&CurrentDataLength, ErrorCode);
      [!ELSE!][!//
        ServiceProcessStatus = Rte_Call_RoutineServices_[!"node:name(.)"!]_[!"$operation"!]([!"$inParamList"!]OpStatus, [!"$outParamListAddress"!]CurrentDataLength, ErrorCode);
      [!ENDIF!][!//
    [!ELSE!][!//
      ServiceProcessStatus = Rte_Call_RoutineServices_[!"node:name(.)"!]_[!"$operation"!]([!"$inParamList"!]OpStatus, [!"$outParamListAddress"!]ErrorCode);
    [!ENDIF!][!//
  [!ELSE!][!//
      [!IF "$RoutineFixedLength = 'false'"!][!//
        [!IF "$RoutineVariableOutSignals = 'true'"!][!//
          ServiceProcessStatus = [!"node:ref(concat('DcmDsp',$operation,'RoutineFnc'))"!]([!"$inParamList"!]OpStatus, [!"$outParamListAddress"!]&CurrentDataLength, ErrorCode);
        [!ELSE!][!//
          ServiceProcessStatus = [!"node:ref(concat('DcmDsp',$operation,'RoutineFnc'))"!]([!"$inParamList"!]OpStatus, [!"$outParamListAddress"!]CurrentDataLength, ErrorCode);
        [!ENDIF!][!//
      [!ELSE!][!//
        ServiceProcessStatus = [!"node:ref(concat('DcmDsp',$operation,'RoutineFnc'))"!]([!"$inParamList"!]OpStatus, [!"$outParamListAddress"!]ErrorCode);
      [!ENDIF!][!//
  [!ENDIF!][!//
  [!ENDINDENT!][!//
  }
  [!CR!]
  if (ServiceProcessStatus == E_OK)
  {
  [!INDENT "4"!][!//
  [!IF "($RoutineFixedLength = 'false')"!][!//
    [!IF "num:i($outFixedDataLength) > 0"!][!//
      [!IF "$DcmRoutineVarLenInBytes = 'false'"!][!//
        [!IF "$ResponseLengthWithoutCurrentDataLength = 'true'"!][!//
          [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBits.FixedOut,1 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          pMsgContext->resDataLen = DCM_GET_BYTES([!"num:i($outFixedDataLength)"!]U) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
        [!ELSE!][!//
          [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBits.VariableOut,1 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          pMsgContext->resDataLen = DCM_GET_BYTES([!"num:i($outFixedDataLength)"!]U + (Dcm_MsgLenType)CurrentDataLength) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
        [!ENDIF!][!//
      [!ELSE!][!//
        if((CurrentDataLength * 8U) > [!"num:i($outVariableDataLength)"!]U)
        {
          [!INDENT "6"!][!//
          /* In case the application returns a length for variable signal bigger than is configured
          * this will be ignored and the length from configuration will be used. */
          pMsgContext->resDataLen = (Dcm_MsgLenType)DCM_GET_BYTES([!"num:i($outFixedDataLength)"!]U + [!"num:i($outVariableDataLength)"!]U) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!IF "($outVariableDataLength)>0"!][!//
            [!INDENT "0"!][!//
            #if (DCM_DEV_ERROR_DETECT == STD_ON)
            [!/* !LINKSTO Dcm.EB.RoutineControl.Start.ReturnLargerData.DET,1 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.Stop.ReturnLargerData.DET,1 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.RequestResults.ReturnLargerData.DET,1 */!][!//
            [!WS "6"!]DCM_DET_REPORT_ERROR([!"$SVCID"!], DCM_E_INTERFACE_RETURN_VALUE);
            #endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
            [!ENDINDENT!][!//
          [!ENDIF!][!//
          [!ENDINDENT!][!//
        }
        else
        {
          [!INDENT "6"!][!//
          [!IF "$ResponseLengthWithoutCurrentDataLength = 'true'"!][!//
            [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBytes.FixedOut,1 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!///
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
            pMsgContext->resDataLen = DCM_GET_BYTES([!"num:i($outFixedDataLength)"!]U) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
          [!ELSE!][!//
            [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBytes.VariableOut,1 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
            pMsgContext->resDataLen = DCM_GET_BYTES([!"num:i($outFixedDataLength)"!]U) + (Dcm_MsgLenType)CurrentDataLength + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
          [!ENDIF!][!//
          [!ENDINDENT!][!//
        }
      [!ENDIF!][!//
    [!ELSE!][!//
      [!IF "$DcmRoutineVarLenInBytes = 'false'"!]
        [!IF "$ResponseLengthWithoutCurrentDataLength = 'true'"!][!//
          [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBits.FixedOut,1 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
          pMsgContext->resDataLen = DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
        [!ELSE!][!//
          [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBits.VariableOut,1 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInVarOut.LengthInBits,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInVarOut.LengthInBits,2 */!][!//
          pMsgContext->resDataLen = DCM_GET_BYTES((Dcm_MsgLenType)CurrentDataLength) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
        [!ENDIF!][!//
      [!ELSE!][!//
        if((CurrentDataLength * 8U) > [!"num:i($outVariableDataLength)"!]U)
        {
          [!INDENT "6"!][!//
          pMsgContext->resDataLen = (Dcm_MsgLenType)DCM_GET_BYTES([!"num:i($outVariableDataLength)"!]U) + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!IF "($outVariableDataLength)>0"!][!//
            [!INDENT "0"!][!//
            #if (DCM_DEV_ERROR_DETECT == STD_ON)
            [!/* !LINKSTO Dcm.EB.RoutineControl.Start.ReturnLargerData.DET,1 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.Stop.ReturnLargerData.DET,1 */!][!//
            [!/* !LINKSTO Dcm.EB.RoutineControl.RequestResults.ReturnLargerData.DET,1 */!][!//
            [!WS "6"!]DCM_DET_REPORT_ERROR([!"$SVCID"!], DCM_E_INTERFACE_RETURN_VALUE);
            #endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
            [!ENDINDENT!][!//
          [!ENDIF!][!//
          [!ENDINDENT!][!//
        }
        else
        {
        [!INDENT "6"!][!//
        [!IF "$ResponseLengthWithoutCurrentDataLength = 'true'"!][!//
          [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBytes.FixedOut,1 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
          pMsgContext->resDataLen = DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
        [!ELSE!][!//
          [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.LengthInBytes.VariableOut,1 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInVarOut.LengthInBytes,2 */!][!//
          [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInVarOut.LengthInBytes,2 */!][!//
          pMsgContext->resDataLen = (Dcm_MsgLenType)CurrentDataLength + DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH;
        [!ENDIF!][!//
        [!ENDINDENT!][!//
        }
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
      [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OutOperation.FixedOut,1 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStartOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxStopOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.FixedInFixedOut,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenFalse,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.FixedInFixedOut.FixedLenTrue,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.FixedInFixedOut,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.Callout.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR40.VarInFixedOut.LengthInBytes,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInFixedOut.LengthInBits,2 */!][!//
      [!/* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResultsOut.CS.AUTOSAR42.VarInFixedOut.LengthInBytes,2 */!][!//
      pMsgContext->resDataLen = [!"num:i((($outFixedDataLength + 7) div 8) + 3)"!]U;
  [!ENDIF!][!//
  [!VAR "outVarCount"="0"!][!//
    [!IF "($outputSignalNr > 0)"!][!//
      [!IF "node:exists(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineOutput]/eb-list::*[node:name(.) = $outputSignal]/eb-list::*[(contains(DcmDspRoutineSignalType,'16') or contains(DcmDspRoutineSignalType,'32'))]/eb-list::*)"!]
        [!VAR "Uint16ArrayElementsOut"="$Uint16ArrayCount - $Uint16ArrayElementsIn"!][!//
        [!VAR "Sint16ArrayElementsOut"="$Sint16ArrayCount - $Sint16ArrayElementsIn"!][!//
        [!VAR "Uint32ArrayElementsOut"="$Uint32ArrayCount - $Uint32ArrayElementsIn"!][!//
        [!VAR "Sint32ArrayElementsOut"="$Sint32ArrayCount - $Sint32ArrayElementsIn"!][!//
        [!INDENT "0"!][!//
        #if (DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)
        [!ENDINDENT!][!//
        /* !LINKSTO Dcm.EB.RoutineControl.EndiannessEnabled,1 */
        if(CurProtocolConfig->EndiannessConversion == TRUE)
        {
        [!/*--- The out signals are positioned after the last IN signal so start the conversion afterwards ---*/!][!//
        [!IF "($Uint16ArrayElementsOut > 0)"!][!//
          [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_U16(&Dcm_RoutineControlOperations_[!"$prefixType"!]Uint16Array[[!"num:i($Uint16ArrayElementsIn)"!]], [!"num:i($Uint16ArrayElementsOut)"!]U);[!//
          [!CR!]
        [!ENDIF!][!//
        [!IF "($Sint16ArrayElementsOut > 0)"!][!//
          [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_S16(&Dcm_RoutineControlOperations_[!"$prefixType"!]Sint16Array[[!"num:i($Sint16ArrayElementsIn)"!]], [!"num:i($Sint16ArrayElementsOut)"!]U);[!//
          [!CR!]
        [!ENDIF!][!//
        [!IF "($Uint32ArrayElementsOut > 0)"!][!//
          [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_U32(&Dcm_RoutineControlOperations_[!"$prefixType"!]Uint32Array[[!"num:i($Uint32ArrayElementsIn)"!]], [!"num:i($Uint32ArrayElementsOut)"!]U);[!//
          [!CR!]
        [!ENDIF!][!//
        [!IF "($Sint32ArrayElementsOut > 0)"!][!//
          [!WS "2"!]Dcm_Dsp_RoutineControl_SwapBytes_S32(&Dcm_RoutineControlOperations_[!"$prefixType"!]Sint32Array[[!"num:i($Sint32ArrayElementsIn)"!]], [!"num:i($Sint32ArrayElementsOut)"!]U);[!//
          [!CR!]
        [!ENDIF!][!//
          }
        [!INDENT "0"!][!//
        #endif /*(DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)*/
        [!ENDINDENT!][!//
        [!CR!]
      [!ENDIF!][!//
      [!LOOP "util:distinct(node:order(node:ref(DcmDspRoutineInfoRef)/eb-list::*[node:name(.) = $routineOutput]/eb-list::*[node:name(.) = $outputSignal]/eb-list::*, 'DcmDspRoutineSignalPos'))"!][!//
        [!IF "(DcmDspRoutineSignalType = 'VARIABLE_LENGTH')"!][!//
          [!IF "$CommonBufferCount = 0"!][!//
            [!/* Rx and Tx buffer are different */!][!//
            [!IF "not((DcmDspRoutineSignalPos mod 8) = '0') "!][!//
              [!CR!]
              [!/* Variable length signal is not byte aligned */!][!//
              [!IF "($DcmRoutineVarLenInBytes='false')"!][!//
                Dcm_DspInternal_ShiftBitsInBuffer((P2VAR(uint8, AUTOMATIC, DCM_VAR))&(pMsgContext->resData[3]),
                  [!WS "34"!][!"num:i($outFixedDataLength + (8- ($outFixedDataLength mod 8)))"!]U,
                  [!WS "34"!][!"num:i($outFixedDataLength)"!]U,
                  [!WS "34"!]CurrentDataLength,
                  [!WS "34"!]TRUE);
              [!ELSE!][!//
                Dcm_DspInternal_ShiftBitsInBuffer((P2VAR(uint8, AUTOMATIC, DCM_VAR))&(pMsgContext->resData[3]),
                  [!WS "34"!][!"num:i($outFixedDataLength + (8 - ($outFixedDataLength mod 8)))"!]U,
                  [!WS "34"!][!"num:i($outFixedDataLength)"!]U,
                  [!WS "34"!](uint32)((uint32)CurrentDataLength * 8U),
                  [!WS "34"!]TRUE);
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            [!CR!]
            [!/* Rx and Tx buffers are the same, an auxiliary buffer needs to be used  */!][!//
            Dcm_DspInternal_CopySignalData((P2VAR(uint8, AUTOMATIC, DCM_VAR))&Dcm_RoutineControlOperations_[!"$prefixType"!]RoutineControlBuffer,
                                [!WS "31"!](P2VAR(uint8, AUTOMATIC, DCM_VAR))&(pMsgContext->resData[3]),
                                [!WS "31"!]0U,
                                [!WS "31"!][!"DcmDspRoutineSignalPos"!]U,
                                [!WS "31"!][!"DcmDspRoutineSignalLength"!]U,
                                [!WS "31"!]DCM_COPY_TO_OUTBUFFER_OPAQUE,
                                [!WS "31"!]DCM_BYTE_DIRECTION_INCREMENT);
          [!ENDIF!][!//
        [!ELSE!][!//
          /* Deviation MISRAC2012-1 <+2> */
          /* Deviation MISRA-1 <+2> */
          Dcm_DspInternal_CopySignalData((P2VAR(uint8, AUTOMATIC, DCM_VAR))&[!"text:split($outParamList, ', ')[position() = ($outVarCount + 1)]"!],
                              [!WS "31"!](P2VAR(uint8, AUTOMATIC, DCM_VAR))&(pMsgContext->resData[3]),
                              [!WS "31"!]0U,
                              [!WS "31"!][!"DcmDspRoutineSignalPos"!]U,
                              [!WS "31"!][!"DcmDspRoutineSignalLength"!]U,
                              [!WS "31"!]DCM_COPY_TO_OUTBUFFER_OPAQUE,
                              [!WS "31"!]DCM_BYTE_DIRECTION_INCREMENT);
          [!VAR "outVarCount"="$outVarCount + 1"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!CR!]
    ServiceProcessStatus = DCM_E_OK;
    [!ENDINDENT!][!//
    }
    else if(ServiceProcessStatus == E_NOT_OK)
    {
      [!WS "2"!]ServiceProcessStatus = DCM_E_NOT_OK;
    }
    else
    {
      [!WS "2"!]/* ServiceProcessStatus is DCM_E_PENDING, DCM_E_FORCE_RCRRP or unknown and these
      [!WS "3"!]* cases are processed in service handler */
    }
  [!CR!]
  return ServiceProcessStatus;
  [!ENDINDENT!][!//
}
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
[!ENDMACRO!][!//
[!//
/*==================[inclusions]=================================================================*/

[!AUTOSPACING!][!//
#include <Dcm_RoutineControl_Cfg.h>                             /*  RoutineControl Configuration */
#include <Dcm_API_Cfg.h>                                  /*  Configurable function declarations */
#include <Dcm_DspExternal.h>                           /* Callbacks provided by Central Diag SwC */
#include <Dcm_Dsl_Supervisor.h>                        /* Dcm Dsl Supervisor header file */
#include <TSMem.h>
/*==================[macros]=====================================================================*/

/* The minimum length of a positive response (without the SID which is already added in the Dsd) is:
 * byte Subservice ID + 2 bytes RoutineId. */
#define DCM_SUBSERVICEID_AND_ROUTINEID_LENGTH 3U

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/
[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]

[!IF "$resetOfSignalArray = 'true' or $BytesSwapNeededU16 = 'true' or $BytesSwapNeededS16 = 'true' or $BytesSwapNeededU32 = 'true' or $BytesSwapNeededS32 = 'true'"!][!//

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

[!IF "$resetOfSignalArray = 'true'"!][!//
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_ClearInternalArrays(void);
[!ENDIF!]

#if (DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)
[!IF "$BytesSwapNeededU16 = 'true'"!][!//
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_U16(uint16* SignalData, uint32 SignalLength);
[!ENDIF!]

[!IF "$BytesSwapNeededS16 = 'true'"!][!//
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_S16(sint16* SignalData, uint32 SignalLength);
[!ENDIF!]

[!IF "$BytesSwapNeededU32 = 'true'"!][!//
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_U32(uint32* SignalData, uint32 SignalLength);
[!ENDIF!]

[!IF "$BytesSwapNeededS32 = 'true'"!][!//
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_S32(sint32* SignalData, uint32 SignalLength);
[!ENDIF!]
#endif

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
[!ENDIF!]
[!ENDIF!]

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/
[!//
[!VAR "CommonBufferCount"="count(DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/eb-list::*[DcmDslProtocolTxBufferID =  DcmDslConnection/eb-list::*/DcmDslProtocolRx/eb-list::*/DcmDslProtocolRxBufferID])"!]
[!IF "(node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed) and ((node:existsAndTrue(../../DcmDspEnableObdMirror) and not(node:exists(DcmDspRoutineTidRef))) or node:existsAndFalse(../../DcmDspEnableObdMirror)) and (node:exists(node:ref(DcmDspRoutineInfoRef)/eb-list::*[./eb-list::*/eb-list::*/DcmDspRoutineSignalType = 'VARIABLE_LENGTH']))]))"!]
    [!VAR "VariableLength" = "'true'"!]
  [!ELSE!]
    [!VAR "VariableLength" = "'false'"!]
[!ENDIF!]

[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]
  [!INDENT "0"!][!//
    [!/*--- UDS datatype max length variables  ---*/!][!//
    [!VAR "UDS_BooleanArrayMaxLength"="0"!][!//
    [!VAR "UDS_Sint16ArrayMaxLength"="0"!][!//
    [!VAR "UDS_Sint32ArrayMaxLength"="0"!][!//
    [!VAR "UDS_Sint8ArrayMaxLength"="0"!][!//
    [!VAR "UDS_Uint16ArrayMaxLength"="0"!][!//
    [!VAR "UDS_Uint32ArrayMaxLength"="0"!][!//
    [!VAR "UDS_Uint8ArrayMaxLength"="0"!][!//
    [!VAR "UDS_VariableSignalLength" = "0"!]
    [!IF "($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON')"!]
      [!/*--- OBD datatype max length variables  ---*/!][!//
      [!VAR "OBD_BooleanArrayMaxLength"="0"!][!//
      [!VAR "OBD_Sint16ArrayMaxLength"="0"!][!//
      [!VAR "OBD_Sint32ArrayMaxLength"="0"!][!//
      [!VAR "OBD_Sint8ArrayMaxLength"="0"!][!//
      [!VAR "OBD_Uint16ArrayMaxLength"="0"!][!//
      [!VAR "OBD_Uint32ArrayMaxLength"="0"!][!//
      [!VAR "OBD_Uint8ArrayMaxLength"="0"!][!//
      [!VAR "OBD_VariableSignalLength" = "0"!]
    [!ENDIF!]
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*"!]
    [!/*--- OBD max size for variableLength buffer calculation ---*/!][!//
      [!IF "node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror)))"!]
        [!IF "(($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON') and (DcmDspRoutineIdentifier >= num:hextoint('0xE000')) and (DcmDspRoutineIdentifier <= num:hextoint('0xE1FF')))"!]
          [!IF "(($CommonBufferCount > 0) and ($VariableLength = 'true'))"!]
            [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*/eb-list::*[node:name(.) = 'DcmDspStartRoutineOutSignal' or node:name(.) = 'DcmDspRoutineStopOutSignal' or node:name(.) = 'DcmDspRoutineRequestResOutSignal']/eb-list::*[DcmDspRoutineSignalType = 'VARIABLE_LENGTH']"!]
              [!IF "number(DcmDspRoutineSignalLength) > $OBD_VariableSignalLength"!]
                [!VAR "OBD_VariableSignalLength" = "DcmDspRoutineSignalLength"!]
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
          [!/*--- OBD datatype max length array calculation for Start operation ---*/!][!//
          [!VAR "OBD_StartBooleanArrayLength"="0"!][!//
          [!VAR "OBD_StartSint16ArrayLength"="0"!][!//
          [!VAR "OBD_StartSint32ArrayLength"="0"!][!//
          [!VAR "OBD_StartSint8ArrayLength"="0"!][!//
          [!VAR "OBD_StartUint16ArrayLength"="0"!][!//
          [!VAR "OBD_StartUint32ArrayLength"="0"!][!//
          [!VAR "OBD_StartUint8ArrayLength"="0"!][!//
          [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.),'Start')]/eb-list::*/eb-list::*"!]
            [!IF "(./DcmDspRoutineSignalType = 'BOOLEAN')"!]
              [!VAR "OBD_StartBooleanArrayLength"="$OBD_StartBooleanArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16')"!]
              [!VAR "OBD_StartSint16ArrayLength"="$OBD_StartSint16ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32')"!]
              [!VAR "OBD_StartSint32ArrayLength"="$OBD_StartSint32ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8')"!]
              [!VAR "OBD_StartSint8ArrayLength"="$OBD_StartSint8ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16')"!]
              [!VAR "OBD_StartUint16ArrayLength"="$OBD_StartUint16ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32')"!]
              [!VAR "OBD_StartUint32ArrayLength"="$OBD_StartUint32ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8')"!]
              [!VAR "OBD_StartUint8ArrayLength"="$OBD_StartUint8ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16_N')"!]
              [!VAR "OBD_StartSint16ArrayLength"="$OBD_StartSint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32_N')"!]
              [!VAR "OBD_StartSint32ArrayLength"="$OBD_StartSint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8_N')"!]
              [!VAR "OBD_StartSint8ArrayLength"="$OBD_StartSint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16_N')"!]
              [!VAR "OBD_StartUint16ArrayLength"="$OBD_StartUint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32_N')"!]
              [!VAR "OBD_StartUint32ArrayLength"="$OBD_StartUint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8_N')"!]
              [!VAR "OBD_StartUint8ArrayLength"="$OBD_StartUint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
            [!ENDIF!]
          [!ENDLOOP!]
          [!/*--- OBD datatype max length array calculation for Stop operation ---*/!][!//
          [!VAR "OBD_StopBooleanArrayLength"="0"!][!//
          [!VAR "OBD_StopSint16ArrayLength"="0"!][!//
          [!VAR "OBD_StopSint32ArrayLength"="0"!][!//
          [!VAR "OBD_StopSint8ArrayLength"="0"!][!//
          [!VAR "OBD_StopUint16ArrayLength"="0"!][!//
          [!VAR "OBD_StopUint32ArrayLength"="0"!][!//
          [!VAR "OBD_StopUint8ArrayLength"="0"!][!//
          [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
            [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.),'Stop')]/eb-list::*/eb-list::*"!]
              [!IF "(./DcmDspRoutineSignalType = 'BOOLEAN')"!]
                [!VAR "OBD_StopBooleanArrayLength"="$OBD_StopBooleanArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16')"!]
                [!VAR "OBD_StopSint16ArrayLength"="$OBD_StopSint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32')"!]
                [!VAR "OBD_StopSint32ArrayLength"="$OBD_StopSint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8')"!]
                [!VAR "OBD_StopSint8ArrayLength"="$OBD_StopSint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16')"!]
                [!VAR "OBD_StopUint16ArrayLength"="$OBD_StopUint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32')"!]
                [!VAR "OBD_StopUint32ArrayLength"="$OBD_StopUint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8')"!]
                [!VAR "OBD_StopUint8ArrayLength"="$OBD_StopUint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16_N')"!]
                [!VAR "OBD_StopSint16ArrayLength"="$OBD_StopSint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32_N')"!]
                [!VAR "OBD_StopSint32ArrayLength"="$OBD_StopSint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8_N')"!]
                [!VAR "OBD_StopSint8ArrayLength"="$OBD_StopSint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16_N')"!]
                [!VAR "OBD_StopUint16ArrayLength"="$OBD_StopUint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32_N')"!]
                [!VAR "OBD_StopUint32ArrayLength"="$OBD_StopUint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8_N')"!]
                [!VAR "OBD_StopUint8ArrayLength"="$OBD_StopUint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
          [!/*--- OBD datatype max length array calculation for RequestResults operation ---*/!][!//
          [!VAR "OBD_RequestResBooleanArrayLength"="0"!][!//
          [!VAR "OBD_RequestResSint16ArrayLength"="0"!][!//
          [!VAR "OBD_RequestResSint32ArrayLength"="0"!][!//
          [!VAR "OBD_RequestResSint8ArrayLength"="0"!][!//
          [!VAR "OBD_RequestResUint16ArrayLength"="0"!][!//
          [!VAR "OBD_RequestResUint32ArrayLength"="0"!][!//
          [!VAR "OBD_RequestResUint8ArrayLength"="0"!][!//
          [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!]
            [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.),'Request')]/eb-list::*/eb-list::*"!]
              [!IF "(./DcmDspRoutineSignalType = 'BOOLEAN')"!]
                [!VAR "OBD_RequestResBooleanArrayLength"="$OBD_RequestResBooleanArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16')"!]
                [!VAR "OBD_RequestResSint16ArrayLength"="$OBD_RequestResSint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32')"!]
                [!VAR "OBD_RequestResSint32ArrayLength"="$OBD_RequestResSint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8')"!]
                [!VAR "OBD_RequestResSint8ArrayLength"="$OBD_RequestResSint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16')"!]
                [!VAR "OBD_RequestResUint16ArrayLength"="$OBD_RequestResUint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32')"!]
                [!VAR "OBD_RequestResUint32ArrayLength"="$OBD_RequestResUint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8')"!]
                [!VAR "OBD_RequestResUint8ArrayLength"="$OBD_RequestResUint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16_N')"!]
                [!VAR "OBD_RequestResSint16ArrayLength"="$OBD_RequestResSint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32_N')"!]
                [!VAR "OBD_RequestResSint32ArrayLength"="$OBD_RequestResSint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8_N')"!]
                [!VAR "OBD_RequestResSint8ArrayLength"="$OBD_RequestResSint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16_N')"!]
                [!VAR "OBD_RequestResUint16ArrayLength"="$OBD_RequestResUint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32_N')"!]
                [!VAR "OBD_RequestResUint32ArrayLength"="$OBD_RequestResUint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8_N')"!]
                [!VAR "OBD_RequestResUint8ArrayLength"="$OBD_RequestResUint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ENDIF!]
            [!ENDLOOP!]
              [!ENDIF!]
          [!IF "($OBD_StartBooleanArrayLength > $OBD_BooleanArrayMaxLength)"!]
            [!VAR "OBD_BooleanArrayMaxLength" = "$OBD_StartBooleanArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopBooleanArrayLength > $OBD_BooleanArrayMaxLength)"!][!//
            [!VAR "OBD_BooleanArrayMaxLength" = "$OBD_StopBooleanArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResBooleanArrayLength > $OBD_BooleanArrayMaxLength)"!]
            [!VAR "OBD_BooleanArrayMaxLength" = "$OBD_RequestResBooleanArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StartSint16ArrayLength > $OBD_Sint16ArrayMaxLength)"!]
            [!VAR "OBD_Sint16ArrayMaxLength" = "$OBD_StartSint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopSint16ArrayLength > $OBD_Sint16ArrayMaxLength)"!][!//
            [!VAR "OBD_Sint16ArrayMaxLength" = "$OBD_StopSint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResSint16ArrayLength > $OBD_Sint16ArrayMaxLength)"!]
            [!VAR "OBD_Sint16ArrayMaxLength" = "$OBD_RequestResSint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StartSint32ArrayLength > $OBD_Sint32ArrayMaxLength)"!]
            [!VAR "OBD_Sint32ArrayMaxLength" = "$OBD_StartSint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopSint32ArrayLength > $OBD_Sint32ArrayMaxLength)"!][!//
            [!VAR "OBD_Sint32ArrayMaxLength" = "$OBD_StopSint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResSint32ArrayLength > $OBD_Sint32ArrayMaxLength)"!]
            [!VAR "OBD_Sint32ArrayMaxLength" = "$OBD_RequestResSint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StartSint8ArrayLength > $OBD_Sint8ArrayMaxLength)"!]
            [!VAR "OBD_Sint8ArrayMaxLength" = "$OBD_StartSint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopSint8ArrayLength > $OBD_Sint8ArrayMaxLength)"!][!//
            [!VAR "OBD_Sint8ArrayMaxLength" = "$OBD_StopSint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResSint8ArrayLength > $OBD_Sint8ArrayMaxLength)"!]
            [!VAR "OBD_Sint8ArrayMaxLength" = "$OBD_RequestResSint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StartUint16ArrayLength > $OBD_Uint16ArrayMaxLength)"!]
            [!VAR "OBD_Uint16ArrayMaxLength" = "$OBD_StartUint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopUint16ArrayLength > $OBD_Uint16ArrayMaxLength)"!][!//
            [!VAR "OBD_Uint16ArrayMaxLength" = "$OBD_StopUint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResUint16ArrayLength > $OBD_Uint16ArrayMaxLength)"!]
            [!VAR "OBD_Uint16ArrayMaxLength" = "$OBD_RequestResUint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StartUint32ArrayLength > $OBD_Uint32ArrayMaxLength)"!]
            [!VAR "OBD_Uint32ArrayMaxLength" = "$OBD_StartUint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopUint32ArrayLength > $OBD_Uint32ArrayMaxLength)"!][!//
            [!VAR "OBD_Uint32ArrayMaxLength" = "$OBD_StopUint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResUint32ArrayLength > $OBD_Uint32ArrayMaxLength)"!]
            [!VAR "OBD_Uint32ArrayMaxLength" = "$OBD_RequestResUint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StartUint8ArrayLength > $OBD_Uint8ArrayMaxLength)"!]
            [!VAR "OBD_Uint8ArrayMaxLength" = "$OBD_StartUint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_StopUint8ArrayLength > $OBD_Uint8ArrayMaxLength)"!][!//
            [!VAR "OBD_Uint8ArrayMaxLength" = "$OBD_StopUint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($OBD_RequestResUint8ArrayLength > $OBD_Uint8ArrayMaxLength)"!]
            [!VAR "OBD_Uint8ArrayMaxLength" = "$OBD_RequestResUint8ArrayLength"!]
          [!ENDIF!]
        [!ELSE!]
        [!/*--- UDS max size for variableLength buffer calculation ---*/!][!//
          [!IF "(($CommonBufferCount > 0) and ($VariableLength = 'true'))"!]
            [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*/eb-list::*[node:name(.) = 'DcmDspStartRoutineOutSignal' or node:name(.) = 'DcmDspRoutineStopOutSignal' or node:name(.) = 'DcmDspRoutineRequestResOutSignal']/eb-list::*[DcmDspRoutineSignalType = 'VARIABLE_LENGTH']"!]
              [!IF "number(DcmDspRoutineSignalLength) > $UDS_VariableSignalLength"!]
                [!VAR "UDS_VariableSignalLength" = "(DcmDspRoutineSignalLength)"!]
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
          [!/*--- UDS datatype max length array calculation for Start operation ---*/!][!//
          [!VAR "UDS_StartBooleanArrayLength"="0"!][!//
          [!VAR "UDS_StartSint16ArrayLength"="0"!][!//
          [!VAR "UDS_StartSint32ArrayLength"="0"!][!//
          [!VAR "UDS_StartSint8ArrayLength"="0"!][!//
          [!VAR "UDS_StartUint16ArrayLength"="0"!][!//
          [!VAR "UDS_StartUint32ArrayLength"="0"!][!//
          [!VAR "UDS_StartUint8ArrayLength"="0"!][!//
          [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.),'Start')]/eb-list::*/eb-list::*"!]
            [!IF "(./DcmDspRoutineSignalType = 'BOOLEAN')"!]
              [!VAR "UDS_StartBooleanArrayLength"="$UDS_StartBooleanArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16')"!]
              [!VAR "UDS_StartSint16ArrayLength"="$UDS_StartSint16ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32')"!]
              [!VAR "UDS_StartSint32ArrayLength"="$UDS_StartSint32ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8')"!]
              [!VAR "UDS_StartSint8ArrayLength"="$UDS_StartSint8ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16')"!]
              [!VAR "UDS_StartUint16ArrayLength"="$UDS_StartUint16ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32')"!]
              [!VAR "UDS_StartUint32ArrayLength"="$UDS_StartUint32ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8')"!]
              [!VAR "UDS_StartUint8ArrayLength"="$UDS_StartUint8ArrayLength + 1"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16_N')"!]
              [!VAR "UDS_StartSint16ArrayLength"="$UDS_StartSint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32_N')"!]
              [!VAR "UDS_StartSint32ArrayLength"="$UDS_StartSint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8_N')"!]
              [!VAR "UDS_StartSint8ArrayLength"="$UDS_StartSint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16_N')"!]
              [!VAR "UDS_StartUint16ArrayLength"="$UDS_StartUint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32_N')"!]
              [!VAR "UDS_StartUint32ArrayLength"="$UDS_StartUint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
            [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8_N')"!]
              [!VAR "UDS_StartUint8ArrayLength"="$UDS_StartUint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
            [!ENDIF!]
          [!ENDLOOP!]
          [!/*--- UDS datatype max length array calculation for Stop operation ---*/!][!//
          [!VAR "UDS_StopBooleanArrayLength"="0"!][!//
          [!VAR "UDS_StopSint16ArrayLength"="0"!][!//
          [!VAR "UDS_StopSint32ArrayLength"="0"!][!//
          [!VAR "UDS_StopSint8ArrayLength"="0"!][!//
          [!VAR "UDS_StopUint16ArrayLength"="0"!][!//
          [!VAR "UDS_StopUint32ArrayLength"="0"!][!//
          [!VAR "UDS_StopUint8ArrayLength"="0"!][!//
          [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
            [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.),'Stop')]/eb-list::*/eb-list::*"!]
              [!IF "(./DcmDspRoutineSignalType = 'BOOLEAN')"!]
                [!VAR "UDS_StopBooleanArrayLength"="$UDS_StopBooleanArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16')"!]
                [!VAR "UDS_StopSint16ArrayLength"="$UDS_StopSint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32')"!]
                [!VAR "UDS_StopSint32ArrayLength"="$UDS_StopSint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8')"!]
                [!VAR "UDS_StopSint8ArrayLength"="$UDS_StopSint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16')"!]
                [!VAR "UDS_StopUint16ArrayLength"="$UDS_StopUint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32')"!]
                [!VAR "UDS_StopUint32ArrayLength"="$UDS_StopUint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8')"!]
                [!VAR "UDS_StopUint8ArrayLength"="$UDS_StopUint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16_N')"!]
                [!VAR "UDS_StopSint16ArrayLength"="$UDS_StopSint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32_N')"!]
                [!VAR "UDS_StopSint32ArrayLength"="$UDS_StopSint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8_N')"!]
                [!VAR "UDS_StopSint8ArrayLength"="$UDS_StopSint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16_N')"!]
                [!VAR "UDS_StopUint16ArrayLength"="$UDS_StopUint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32_N')"!]
                [!VAR "UDS_StopUint32ArrayLength"="$UDS_StopUint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8_N')"!]
                [!VAR "UDS_StopUint8ArrayLength"="$UDS_StopUint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
          [!/*--- UDS datatype max length array calculation for RequestResults operation ---*/!][!//
          [!VAR "UDS_RequestResBooleanArrayLength"="0"!][!//
          [!VAR "UDS_RequestResSint16ArrayLength"="0"!][!//
          [!VAR "UDS_RequestResSint32ArrayLength"="0"!][!//
          [!VAR "UDS_RequestResSint8ArrayLength"="0"!][!//
          [!VAR "UDS_RequestResUint16ArrayLength"="0"!][!//
          [!VAR "UDS_RequestResUint32ArrayLength"="0"!][!//
          [!VAR "UDS_RequestResUint8ArrayLength"="0"!][!//
          [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!]
            [!LOOP "node:ref(./DcmDspRoutineInfoRef)/eb-list::*[contains(as:name(.),'Request')]/eb-list::*/eb-list::*"!]
              [!IF "(./DcmDspRoutineSignalType = 'BOOLEAN')"!]
                [!VAR "UDS_RequestResBooleanArrayLength"="$UDS_RequestResBooleanArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16')"!]
                [!VAR "UDS_RequestResSint16ArrayLength"="$UDS_RequestResSint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32')"!]
                [!VAR "UDS_RequestResSint32ArrayLength"="$UDS_RequestResSint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8')"!]
                [!VAR "UDS_RequestResSint8ArrayLength"="$UDS_RequestResSint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16')"!]
                [!VAR "UDS_RequestResUint16ArrayLength"="$UDS_RequestResUint16ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32')"!]
                [!VAR "UDS_RequestResUint32ArrayLength"="$UDS_RequestResUint32ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8')"!]
                [!VAR "UDS_RequestResUint8ArrayLength"="$UDS_RequestResUint8ArrayLength + 1"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT16_N')"!]
                [!VAR "UDS_RequestResSint16ArrayLength"="$UDS_RequestResSint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT32_N')"!]
                [!VAR "UDS_RequestResSint32ArrayLength"="$UDS_RequestResSint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'SINT8_N')"!]
                [!VAR "UDS_RequestResSint8ArrayLength"="$UDS_RequestResSint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT16_N')"!]
                [!VAR "UDS_RequestResUint16ArrayLength"="$UDS_RequestResUint16ArrayLength + (./DcmDspRoutineSignalLength div 16)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT32_N')"!]
                [!VAR "UDS_RequestResUint32ArrayLength"="$UDS_RequestResUint32ArrayLength + (./DcmDspRoutineSignalLength div 32)"!][!//
              [!ELSEIF "(./DcmDspRoutineSignalType = 'UINT8_N')"!]
                [!VAR "UDS_RequestResUint8ArrayLength"="$UDS_RequestResUint8ArrayLength + (./DcmDspRoutineSignalLength div 8)"!][!//
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDIF!]
          [!IF "($UDS_StartBooleanArrayLength > $UDS_BooleanArrayMaxLength)"!]
            [!VAR "UDS_BooleanArrayMaxLength" = "$UDS_StartBooleanArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopBooleanArrayLength > $UDS_BooleanArrayMaxLength)"!][!//
            [!VAR "UDS_BooleanArrayMaxLength" = "$UDS_StopBooleanArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResBooleanArrayLength > $UDS_BooleanArrayMaxLength)"!]
            [!VAR "UDS_BooleanArrayMaxLength" = "$UDS_RequestResBooleanArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StartSint16ArrayLength > $UDS_Sint16ArrayMaxLength)"!]
            [!VAR "UDS_Sint16ArrayMaxLength" = "$UDS_StartSint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopSint16ArrayLength > $UDS_Sint16ArrayMaxLength)"!][!//
            [!VAR "UDS_Sint16ArrayMaxLength" = "$UDS_StopSint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResSint16ArrayLength > $UDS_Sint16ArrayMaxLength)"!]
            [!VAR "UDS_Sint16ArrayMaxLength" = "$UDS_RequestResSint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StartSint32ArrayLength > $UDS_Sint32ArrayMaxLength)"!]
            [!VAR "UDS_Sint32ArrayMaxLength" = "$UDS_StartSint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopSint32ArrayLength > $UDS_Sint32ArrayMaxLength)"!][!//
            [!VAR "UDS_Sint32ArrayMaxLength" = "$UDS_StopSint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResSint32ArrayLength > $UDS_Sint32ArrayMaxLength)"!]
            [!VAR "UDS_Sint32ArrayMaxLength" = "$UDS_RequestResSint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StartSint8ArrayLength > $UDS_Sint8ArrayMaxLength)"!]
            [!VAR "UDS_Sint8ArrayMaxLength" = "$UDS_StartSint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopSint8ArrayLength > $UDS_Sint8ArrayMaxLength)"!][!//
            [!VAR "UDS_Sint8ArrayMaxLength" = "$UDS_StopSint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResSint8ArrayLength > $UDS_Sint8ArrayMaxLength)"!]
            [!VAR "UDS_Sint8ArrayMaxLength" = "$UDS_RequestResSint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StartUint16ArrayLength > $UDS_Uint16ArrayMaxLength)"!]
            [!VAR "UDS_Uint16ArrayMaxLength" = "$UDS_StartUint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopUint16ArrayLength > $UDS_Uint16ArrayMaxLength)"!][!//
            [!VAR "UDS_Uint16ArrayMaxLength" = "$UDS_StopUint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResUint16ArrayLength > $UDS_Uint16ArrayMaxLength)"!]
            [!VAR "UDS_Uint16ArrayMaxLength" = "$UDS_RequestResUint16ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StartUint32ArrayLength > $UDS_Uint32ArrayMaxLength)"!]
            [!VAR "UDS_Uint32ArrayMaxLength" = "$UDS_StartUint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopUint32ArrayLength > $UDS_Uint32ArrayMaxLength)"!][!//
            [!VAR "UDS_Uint32ArrayMaxLength" = "$UDS_StopUint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResUint32ArrayLength > $UDS_Uint32ArrayMaxLength)"!]
            [!VAR "UDS_Uint32ArrayMaxLength" = "$UDS_RequestResUint32ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StartUint8ArrayLength > $UDS_Uint8ArrayMaxLength)"!]
            [!VAR "UDS_Uint8ArrayMaxLength" = "$UDS_StartUint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_StopUint8ArrayLength > $UDS_Uint8ArrayMaxLength)"!][!//
            [!VAR "UDS_Uint8ArrayMaxLength" = "$UDS_StopUint8ArrayLength"!]
          [!ENDIF!]
          [!IF "($UDS_RequestResUint8ArrayLength > $UDS_Uint8ArrayMaxLength)"!]
            [!VAR "UDS_Uint8ArrayMaxLength" = "$UDS_RequestResUint8ArrayLength"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDINDENT!][!//
[!//
  [!IF "(($UDS_VariableSignalLength > 0) or ($UDS_BooleanArrayMaxLength > 0) or ($UDS_Uint8ArrayMaxLength > 0) or ($UDS_Sint8ArrayMaxLength > 0) or (($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON') and (($OBD_BooleanArrayMaxLength > 0) or ($OBD_Uint8ArrayMaxLength > 0) or ($OBD_Sint8ArrayMaxLength > 0) or ($OBD_VariableSignalLength > 0))))"!]
    [!INDENT "0"!][!//
    #define DCM_START_SEC_VAR_CLEARED_8
    #include <Dcm_MemMap.h>
    [!IF "number($UDS_VariableSignalLength) > 0"!]
      [!CR!]
      /* Defining UDS global buffer for Routine control service */
      /* Deviation MISRAC2012-2 */
      STATIC VAR(uint8, DCM_VAR) Dcm_RoutineControlOperations_UDS_RoutineControlBuffer[[!"num:i(($UDS_VariableSignalLength + 7) div 8)"!]];
    [!ENDIF!]
    [!IF "($UDS_BooleanArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global boolean buffer for API parameters used by Routine Control service */
      STATIC VAR(boolean, DCM_VAR) Dcm_RoutineControlOperations_UDS_BooleanArray[[!"num:i($UDS_BooleanArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($UDS_Uint8ArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global uint8 buffer for API parameters used by Routine Control service */
      STATIC VAR(uint8, DCM_VAR) Dcm_RoutineControlOperations_UDS_Uint8Array[[!"num:i($UDS_Uint8ArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($UDS_Sint8ArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global sint8 buffer for API parameters used by Routine Control service */
      STATIC VAR(sint8, DCM_VAR) Dcm_RoutineControlOperations_UDS_Sint8Array[[!"num:i($UDS_Sint8ArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON')"!]
      [!IF "number($OBD_VariableSignalLength) > 0"!]
        [!CR!]
        /* Defining OBD global buffer for Routine control service */
        /* Deviation MISRAC2012-2 */
        STATIC VAR(uint8, DCM_VAR) Dcm_RoutineControlOperations_OBD_RoutineControlBuffer[[!"num:i(($OBD_VariableSignalLength + 7) div 8)"!]];
      [!ENDIF!]
      [!IF "($OBD_BooleanArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global boolean buffer for API parameters used by Routine Control service */
        STATIC VAR(boolean, DCM_VAR) Dcm_RoutineControlOperations_OBD_BooleanArray[[!"num:i($OBD_BooleanArrayMaxLength)"!]];
      [!ENDIF!]
      [!IF "($OBD_Uint8ArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global uint8 buffer for API parameters used by Routine Control service */
        STATIC VAR(uint8, DCM_VAR) Dcm_RoutineControlOperations_OBD_Uint8Array[[!"num:i($OBD_Uint8ArrayMaxLength)"!]];
      [!ENDIF!]
      [!IF "($OBD_Sint8ArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global sint8 buffer for API parameters used by Routine Control service */
        STATIC VAR(sint8, DCM_VAR) Dcm_RoutineControlOperations_OBD_Sint8Array[[!"num:i($OBD_Sint8ArrayMaxLength)"!]];
      [!ENDIF!]
    [!ENDIF!]
    [!CR!]
    #define DCM_STOP_SEC_VAR_CLEARED_8
    #include <Dcm_MemMap.h>
    [!CR!]
    [!ENDINDENT!]
  [!ENDIF!]
[!//
  [!IF "(($UDS_Uint16ArrayMaxLength > 0) or ($UDS_Sint16ArrayMaxLength > 0) or (($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON') and (($OBD_Uint16ArrayMaxLength > 0) or ($OBD_Sint16ArrayMaxLength > 0))))"!]
    [!INDENT "0"!][!//
    #define DCM_START_SEC_VAR_CLEARED_16
    #include <Dcm_MemMap.h>
    [!IF "($UDS_Uint16ArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global uint16 buffer for API parameters used by Routine Control service */
      STATIC VAR(uint16, DCM_VAR) Dcm_RoutineControlOperations_UDS_Uint16Array[[!"num:i($UDS_Uint16ArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($UDS_Sint16ArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global sint16 buffer for API parameters used by Routine Control service */
      STATIC VAR(sint16, DCM_VAR) Dcm_RoutineControlOperations_UDS_Sint16Array[[!"num:i($UDS_Sint16ArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON')"!]
      [!IF "($OBD_Uint16ArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global uint16 buffer for API parameters used by Routine Control service */
        STATIC VAR(uint16, DCM_VAR) Dcm_RoutineControlOperations_OBD_Uint16Array[[!"num:i($OBD_Uint16ArrayMaxLength)"!]];
      [!ENDIF!]
      [!IF "($OBD_Sint16ArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global sint16 buffer for API parameters used by Routine Control service */
        STATIC VAR(sint16, DCM_VAR) Dcm_RoutineControlOperations_OBD_Sint16Array[[!"num:i($OBD_Sint16ArrayMaxLength)"!]];
      [!ENDIF!]
    [!ENDIF!]
    [!CR!]
    #define DCM_STOP_SEC_VAR_CLEARED_16
    #include <Dcm_MemMap.h>
    [!CR!]
    [!ENDINDENT!]
  [!ENDIF!]
[!//
  [!IF "(($UDS_Uint32ArrayMaxLength > 0) or ($UDS_Sint32ArrayMaxLength > 0) or (($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON') and (($OBD_Uint32ArrayMaxLength > 0) or ($OBD_Sint32ArrayMaxLength > 0))))"!]
    [!INDENT "0"!][!//
    #define DCM_START_SEC_VAR_CLEARED_32
    #include <Dcm_MemMap.h>
    [!IF "($UDS_Uint32ArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global uint32 buffer for API parameters used by Routine Control service */
      STATIC VAR(uint32, DCM_VAR) Dcm_RoutineControlOperations_UDS_Uint32Array[[!"num:i($UDS_Uint32ArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($UDS_Sint32ArrayMaxLength > 0)"!]
      [!CR!]
      /* Defining UDS global sint32 buffer for API parameters used by Routine Control service */
      STATIC VAR(sint32, DCM_VAR) Dcm_RoutineControlOperations_UDS_Sint32Array[[!"num:i($UDS_Sint32ArrayMaxLength)"!]];
    [!ENDIF!]
    [!IF "($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON')"!]
      [!IF "($OBD_Uint32ArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global uint32 buffer for API parameters used by Routine Control service */
        STATIC VAR(uint32, DCM_VAR) Dcm_RoutineControlOperations_OBD_Uint32Array[[!"num:i($OBD_Uint32ArrayMaxLength)"!]];
      [!ENDIF!]
      [!IF "($OBD_Sint32ArrayMaxLength > 0)"!]
        [!CR!]
        /* Defining OBD global sint32 buffer for API parameters used by Routine Control service */
        STATIC VAR(sint32, DCM_VAR) Dcm_RoutineControlOperations_OBD_Sint32Array[[!"num:i($OBD_Sint32ArrayMaxLength)"!]];
      [!ENDIF!]
    [!ENDIF!]
    [!CR!]
    #define DCM_STOP_SEC_VAR_CLEARED_32
    #include <Dcm_MemMap.h>
    [!CR!]
    [!ENDINDENT!]
  [!ENDIF!]
[!ENDIF!]
/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/
[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]
  [!VAR "routineOperationMemorySectionIncluded" = "'false'"!][!//
  [!INDENT "0"!]
  [!/* !LINKSTO Dcm.Dsn.IB.RoutineControl.RoutineOperationGeneration,1 */!][!//
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*"!]
    [!/* !LINKSTO SWS_Dcm_00569,1 */!][!//
    [!IF "node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror)))"!][!//
      [!IF "$routineOperationMemorySectionIncluded = 'false'"!]
        [!VAR "routineOperationMemorySectionIncluded" = "'true'"!][!//
      [!ENDIF!]
      [!IF "(($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON') and (DcmDspRoutineIdentifier >= num:hextoint('0xE000')) and (DcmDspRoutineIdentifier <= num:hextoint('0xE1FF')))"!]
        [!CALL "ROUTINECONTROL_GENERATE", "operation" = "'Start'", "type" = "'OBD'"!]
        [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
          [!CALL "ROUTINECONTROL_GENERATE", "operation" = "'Stop'", "type" = "'OBD'"!]
        [!ENDIF!]
        [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!]
          [!CALL "ROUTINECONTROL_GENERATE", "operation" = "'RequestResults'", "type" = "'OBD'"!]
        [!ENDIF!]
      [!ELSE!]
        [!CALL "ROUTINECONTROL_GENERATE", "operation" = "'Start'", "type" = "'UDS'"!]
        [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
          [!CALL "ROUTINECONTROL_GENERATE", "operation" = "'Stop'", "type" = "'UDS'"!]
        [!ENDIF!]
        [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!]
          [!CALL "ROUTINECONTROL_GENERATE", "operation" = "'RequestResults'", "type" = "'UDS'"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ELSEIF "$resetOfSignalArray = 'true' or $BytesSwapNeededU16 = 'true' or $BytesSwapNeededS16 = 'true' or $BytesSwapNeededU32 = 'true' or $BytesSwapNeededS32 = 'true'"!][!//
      [!IF "$routineOperationMemorySectionIncluded = 'false'"!]
        [!VAR "routineOperationMemorySectionIncluded" = "'true'"!][!//
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!CR!]
  /*==================[internal function definitions]==============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
  [!IF "$resetOfSignalArray = 'true'"!][!//
  [!CR!]
    STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_ClearInternalArrays(void)
    {
      [!CR!]
      [!INDENT "2"!]
        [!IF "($UDS_BooleanArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_BooleanArray,0U,sizeof(Dcm_RoutineControlOperations_UDS_BooleanArray));
          [!CR!]
        [!ENDIF!]
        [!IF "($UDS_Uint8ArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_Uint8Array,0U,sizeof(Dcm_RoutineControlOperations_UDS_Uint8Array));
          [!CR!]
        [!ENDIF!]
        [!IF "($UDS_Sint8ArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_Sint8Array,0U,sizeof(Dcm_RoutineControlOperations_UDS_Sint8Array));
          [!CR!]
        [!ENDIF!]
        [!IF "($UDS_Uint16ArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_Uint16Array,0U,sizeof(Dcm_RoutineControlOperations_UDS_Uint16Array));
          [!CR!]
        [!ENDIF!]
        [!IF "($UDS_Sint16ArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_Sint16Array,0U,sizeof(Dcm_RoutineControlOperations_UDS_Sint16Array));
          [!CR!]
        [!ENDIF!]
        [!IF "($UDS_Uint32ArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_Uint32Array,0U,sizeof(Dcm_RoutineControlOperations_UDS_Uint32Array));
          [!CR!]
        [!ENDIF!]
        [!IF "($UDS_Sint32ArrayMaxLength > 0)"!]
          TS_MemSet(Dcm_RoutineControlOperations_UDS_Sint32Array,0U,sizeof(Dcm_RoutineControlOperations_UDS_Sint32Array));
          [!CR!]
        [!ENDIF!]
        [!IF "($DCM_ROUTINE_PARALLEL_PROCESSING = 'STD_ON')"!]
          [!IF "($OBD_BooleanArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_BooleanArray,0U,sizeof(Dcm_RoutineControlOperations_OBD_BooleanArray));
            [!CR!]
          [!ENDIF!]
          [!IF "($OBD_Uint8ArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_Uint8Array,0U,sizeof(Dcm_RoutineControlOperations_OBD_Uint8Array));
            [!CR!]
          [!ENDIF!]
          [!IF "($OBD_Sint8ArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_Sint8Array,0U,sizeof(Dcm_RoutineControlOperations_OBD_Sint8Array));
            [!CR!]
          [!ENDIF!]
          [!IF "($OBD_Uint16ArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_Uint16Array,0U,sizeof(Dcm_RoutineControlOperations_OBD_Uint16Array));
            [!CR!]
          [!ENDIF!]
          [!IF "($OBD_Sint16ArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_Sint16Array,0U,sizeof(Dcm_RoutineControlOperations_OBD_Sint16Array));
            [!CR!]
          [!ENDIF!]
          [!IF "($OBD_Uint32ArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_Uint32Array,0U,sizeof(Dcm_RoutineControlOperations_OBD_Uint32Array));
            [!CR!]
          [!ENDIF!]
          [!IF "($OBD_Sint32ArrayMaxLength > 0)"!]
            TS_MemSet(Dcm_RoutineControlOperations_OBD_Sint32Array,0U,sizeof(Dcm_RoutineControlOperations_OBD_Sint32Array));
            [!CR!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDINDENT!]
    }
  [!ENDIF!]
  [!IF "$routineOperationMemorySectionIncluded = 'true'"!][!//
    #if (DCM_ROUTINE_ENDIANNESS_CONVERSION == STD_ON)
  [!ENDIF!]
  [!IF "$BytesSwapNeededU16 = 'true'"!][!//
  [!CR!]
    STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_U16(uint16* SignalData, uint32 SignalLength)
    {
      [!INDENT "2"!]
      uint16_least ArrayIndex;
      for(ArrayIndex = 0U; ArrayIndex < SignalLength; ArrayIndex++)
      {
      [!ENDINDENT!]
      [!INDENT "4"!]
        const uint16 TempParameter = ((uint16)(SignalData[ArrayIndex] >> 8U) | (uint16)(SignalData[ArrayIndex] << 8U));
        SignalData[ArrayIndex] = TempParameter;
      [!ENDINDENT!]
      [!INDENT "2"!]
      }
      [!ENDINDENT!]
    }
  [!ENDIF!]

  [!IF "$BytesSwapNeededS16 = 'true'"!][!//
  [!CR!]
    STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_S16(sint16* SignalData, uint32 SignalLength)
    {
      [!INDENT "2"!]
      uint16_least ArrayIndex;
      for(ArrayIndex = 0U; ArrayIndex < SignalLength; ArrayIndex++)
      {
      [!ENDINDENT!]
      [!INDENT "4"!]
        const uint16 TempParameter = (uint16)((uint16)SignalData[ArrayIndex] >> 8U) |
                                   (uint16)((uint16)SignalData[ArrayIndex] << 8U);
        SignalData[ArrayIndex] = (sint16)TempParameter;
      [!ENDINDENT!]
      [!INDENT "2"!]
      }
      [!ENDINDENT!]
    }
  [!ENDIF!]

  [!IF "$BytesSwapNeededU32 = 'true'"!][!//
  [!CR!]
    STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_U32(uint32* SignalData, uint32 SignalLength)
    {
      [!INDENT "2"!]
      uint16_least ArrayIndex;
      for(ArrayIndex = 0U; ArrayIndex < SignalLength; ArrayIndex++)
      {
      [!ENDINDENT!]
      [!INDENT "4"!]
        const uint32 TempParameter = ((SignalData[ArrayIndex]) >> 24U) |
                                   (((SignalData[ArrayIndex]) << 8U) & 0x00ff0000U) |
                                   (((SignalData[ArrayIndex]) >> 8U) & 0x0000ff00U) |
                                   ((SignalData[ArrayIndex]) << 24U);
        SignalData[ArrayIndex] = TempParameter;
      [!ENDINDENT!]
      [!INDENT "2"!]
      }
      [!ENDINDENT!]
    }
  [!ENDIF!]

  [!IF "$BytesSwapNeededS32 = 'true'"!][!//
  [!CR!]
    STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SwapBytes_S32(sint32* SignalData, uint32 SignalLength)
    {
      [!INDENT "2"!]
      uint16_least ArrayIndex;
      for(ArrayIndex = 0U; ArrayIndex < SignalLength; ArrayIndex++)
      {
      [!ENDINDENT!]
      [!INDENT "4"!]
        const uint32 TempParameter = (((uint32)SignalData[ArrayIndex]) >> 24U) |
                                   ((((uint32)SignalData[ArrayIndex]) << 8U) & 0x00ff0000U) |
                                   ((((uint32)SignalData[ArrayIndex]) >> 8U) & 0x0000ff00U) |
                                   (((uint32)SignalData[ArrayIndex]) << 24U);
        SignalData[ArrayIndex] = (sint32)TempParameter;
        SignalData[ArrayIndex] = (sint32)TempParameter;
      [!ENDINDENT!]
      [!INDENT "2"!]
      }
      [!ENDINDENT!]
    }
  [!ENDIF!]
  [!ENDINDENT!]
  [!IF "$routineOperationMemorySectionIncluded = 'true'"!][!//
    [!INDENT "0"!][!//
    #endif
    [!ENDINDENT!]
  [!ENDIF!]
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
[!ENDIF!]
/*==================[end of file]================================================================*/
