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

 /* MISRA-C:2004 Deviation List
  *
  * MISRA-1) Deviated Rule: 12.4 (required)
  *     The right-hand operand of a logical '&&' or '||' operator
  *     shall not contain side effects.
  *
  *     Reason:
  *     Logical operators '&&' and '||' are used here purposefully. The sub-expression shall not be
  *      evaluated if the first expression of a '&&' operation is FALSE. Similarly the
  *      sub-expression shall not be evaluated if the first expression of a '||' operation is TRUE.
  *      There is no side effects.
  *
  * MISRA-2) Deviated Rule: 11.4 (advisory)
  *     A cast should not be performed between a pointer to object type and a
  *     different pointer to object type.
  *
  *     Reason:
  *     A cast to unsigned is necessary here to copy data bit by bit and
  *     there is no alignment issues.
  *
  * MISRA-3) Deviated Rule: 11.1 (required)
  *     Conversions shall not be performed between a pointer to a function and
  *     any type other than an integral type.
  *
  *     Reason:
  *     In order to save memory, the function pointers necessary for DID operations are generated
  *     as an array of unions (union type which contains all such possible function pointers),
  *     instead of an array of structures containing all possible pointer types.
  *     The array containing the function pointers is initialized using brace-enclosed initializer
  *     list and C90 standard allows only the initialization of the first union member.
  *     The solution is to use a "generic function pointer" and use that type to define the array,
  *     and use explicit casts for each initialized member.
  *     Casting one function pointer type to the general type at initialization and then back again
  *     to the original type is guaranteed to preserve the correct data.
  *
  */

 /* MISRA-C:2012 Deviation List
  *
  *  MISRAC2012-1) Deviated Rule: 11.1 (required)
  *     "Conversions shall not be performed between a pointer to a function and any other type."
  *
  *     Reason:
  *     In order to save memory, the function pointers necessary for DID operations are generated
  *     as an array of unions (union type which contains all such possible function pointers),
  *     instead of an array of structures containing all possible pointer types.
  *     The array containing the function pointers is initialized using brace-enclosed initializer
  *     list and C90 standard allows only the initialization of the first union member.
  *     The solution is to use a "generic function pointer" and use that type to define the array,
  *     and use explicit casts for each initialized member.
  *     Casting one function pointer type to the general type at initialization and then back again
  *     to the original type is guaranteed to preserve the correct data.
  *
  *  MISRAC2012-2) Deviated Rule: 13.5 (required)
  *     "The right hand operand of a logical && or || operator shall not contain persistent
  *     side effects."
  *
  *     Reason:
  *     Logical operators '&&' and '||' are used here purposefully. The sub-expression shall not be
  *     evaluated if the first expression of a '&&' operation is FALSE. Similarly the
  *     sub-expression shall not be evaluated if the first expression of a '||' operation is TRUE.
  *     There is no side effects.
  *
  *  MISRAC2012-3) Deviated Rule: 11.3 (required)
  *     "A cast should not be performed between a pointer to object type and a different pointer to
  *     object type."
  *
  *     Reason:
  *     A cast to UINT8 is necessary here to copy data bit by bit and to be flexible for all
  *     the types, being no alignment issues.
  *     There is no side effects.
  *
  *  MISRAC2012-4) Deviated Rule: 8.9 (advisory)
  *     "An object should be defined at block scope if its identifier only
  *     appears in a single function."
  *
  *     Reason:
  *     The object is defined in this way because the values that are stored
  *     in them are required for the next call of this function and should be
  *     hold in the data segment memory.
  *
  *  MISRAC2012-5) Deviated Rule: 20.7 (required)
  *     Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
  *
  *     Reason:
  *     The macro DCM_CONST_CALIBRATION is used to modify the read-only attribute of a memory section
  *     to which a constant is assigned via the compiler abstraction macro, in order for the compiler
  *     to allow the simulation of the constant calibration. The syntax of the compiler abstraction
  *     macro definition requires DCM_CONST_CALIBRATION macro's definition to not be enclosed in
  *     parentheses.
  */

/*==================[inclusions]=================================================================*/
[!//
[!AUTOSPACING!]
[!INDENT "0"!]
#include <ComStack_Types.h>                                            /* AUTOSAR standard types */
#include <Dcm_Cfg.h>                                           /* Generated configuration header */
#include <Dcm_API_Cfg.h>                                  /*  Configurable function declarations */
#include <Dcm_Hsm.h>                                                        /* Dcm State Machine */
#include <Dcm_Int.h>                                       /* Module internal header static part */
#include <Dcm_DspExternal.h>                          /* Callbacks provided by Central Diag SwC  */
#include <Dcm_Dsl_Supervisor.h>                                       /* Module internal header static part */

/* PID Services */
#if(DCM_DSP_USE_PIDSERVICES == STD_ON) || \
   (DCM_DSP_USE_SERVICE_0X02 == STD_ON)
#include <Dcm_Dsp_PidServices.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X06 == STD_ON)
#include <Dcm_Dsp_SvcH_RequestOnboardMonitoringTestResults.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X08 == STD_ON)
#include <Dcm_Dsp_SvcH_RequestControlOfOnBoardSysTstComp.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X09 == STD_ON)
/* OBD Service 0x09 */
#include <Dcm_Dsp_SvcH_RequestVehicleInformation.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X14 == STD_ON)
#include <Dcm_Dsp_SvcH_ClearDiagnosticInformation.h>
#endif

#if ( (DCM_DSP_USE_SERVICE_0X19 == STD_ON) || (DCM_DSP_USE_SERVICE_0XAF == STD_ON) )
#include <Dcm_Dsp_SvcH_ReadDTCInformation.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON)
#include <Dcm_Dsp_SvcH_ReadDataByIdentifier.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X23 == STD_ON)
#include <Dcm_Dsp_SvcH_ReadMemoryByAddress.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X24 == STD_ON)
#include <Dcm_Dsp_SvcH_ReadScalingDataByIdentifier.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X2E == STD_ON)
#include <Dcm_Dsp_SvcH_WriteDataByIdentifier.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X34 == STD_ON)
#include <Dcm_Dsp_SvcH_RequestDownload.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X35 == STD_ON)
#include <Dcm_Dsp_SvcH_RequestUpload.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X36 == STD_ON)
#include <Dcm_Dsp_SvcH_TransferData.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X37 == STD_ON)
#include <Dcm_Dsp_SvcH_RequestTransferExit.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X3D == STD_ON)
#include <Dcm_Dsp_SvcH_WriteMemoryByAddress.h>
#endif

#if (DCM_DSP_USE_DIDSERVICES == STD_ON)
/* Include DidServices SW unit header for IO control */
#include <Dcm_Dsp_DidServices.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X85 == STD_ON)
#include <Dcm_Dsp_SvcH_ControlDTCSetting.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X86 == STD_ON)
#include <Dcm_Dsp_SvcH_ResponseOnEvent.h>
#endif

#if (DCM_DSP_USE_ROESERVICES == STD_ON)
#include <Dcm_Dsl_RoeServices.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X2C == STD_ON)
#include <Dcm_Dsp_SvcH_DynamicallyDefineDataIdentifier.h>
#endif

#if(DCM_DSP_USE_SERVICE_0X28 == STD_ON)
#include <Dcm_Dsp_SvcH_CommunicationControl.h>
#endif

#if(DCM_DSP_USE_SERVICE_0X29 == STD_ON)
#include <Dcm_Dsp_SvcH_Authentication.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X87 == STD_ON)
#include <Dcm_Dsp_SvcH_LinkControl.h>
#endif

#if(DCM_DSP_USE_SERVICE_0X27 == STD_ON)
#include <Dcm_Dsp_SvcH_SecurityAccess.h>
#endif

#if(DCM_DSP_USE_MEMORYSERVICES == STD_ON)
#include <Dcm_Dsp_MemoryServices.h>
#endif

#if(DCM_DSP_USE_SERVICE_0X3E == STD_ON)
#include <Dcm_Dsp_SvcH_TesterPresent.h>
#endif

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
#include <Dcm_Dsp_SvcH_InputOutputControlByIdentifier.h>
#endif

#if(DCM_DSP_USE_SERVICE_0X31 == STD_ON)
#include <Dcm_Dsp_SvcH_RoutineControl.h>
#endif

[!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmHeaderFileInclusion/eb-list::*"!]
[!/* !LINKSTO Dcm.Dsn.File.MemoryServices.CustomHeader,1 */!][!//
[!/* !LINKSTO Dcm.EB.CustomMemoryLabelsHeaderFile,1 */!][!//
/* Custom header files */
#include <[!"."!]>
[!ENDLOOP!]

#if ((DCM_DSP_USE_DIDSERVICES == STD_ON) && (DCM_DSP_USE_SENDERRECEIVER_INTERFACES == STD_ON))
#include <Dcm_Dsp_EndiannessInterpretation.h>
#endif

[!IF "node:exists(DcmConfigSet/eb-list::*/DcmProcessingConditions/DcmModeCondition/eb-list::*[node:exists(DcmBswModeRef)]) or (node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmModeDeclarationSupport))"!][!//
#include <SchM_Dcm.h>
[!ENDIF!][!//
[!INCLUDE "Dcm.m"!][!//
[!INCLUDE "../include/Dcm_common.m"!]
/*==================[macros]=====================================================================*/

[!/*
EcuC References of Dcm Rx PDUs
*/!][!VAR "DcmRxPduCount" = "num:integer( count( DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/eb-list::*/DcmDslConnection/eb-list::*/DcmDslProtocolRx/eb-list::*/DcmDslProtocolRxPduRef))"!][!/*

EcuC References of Dcm Tx PDUs
*/!][!VAR "DcmTxPduCount" = "num:integer( count( DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/eb-list::*))"!]  [!/* Default Tx connection */!][!/*

Activation period of main function
*/!][!VAR "DcmTaskTime" = "DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmTaskTime"!][!//
/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

[!//
[!LOOP "DcmConfigSet/eb-list::*/DcmProcessingConditions/DcmModeCondition/eb-list::*"!]
/** \brief Mode condition function declaration for [!"as:name(.)"!] */
STATIC FUNC(boolean, DCM_CODE) Dcm_ModeCondition_[!"as:name(.)"!]_Result(void);

[!ENDLOOP!]
[!//
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*==================[internal constants]=========================================================*/
[!IF "DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmServiceAPI/DcmDefaultASRServiceAPI = 'AUTOSAR_42'"!][!//
  [!VAR "DefaultASRVersion" = "'DCM_USE_AUTOSAR_42'"!][!//
[!ELSE!][!//
  [!VAR "DefaultASRVersion" = "'DCM_USE_AUTOSAR_40'"!][!//
[!ENDIF!][!//

#define DCM_START_SEC_CONST_8
#include <Dcm_MemMap.h>

[!VAR "SUB_SID_TAB_SES_LEVELS_COUNT" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*/DcmDsdSubService/eb-list::*/DcmDsdSubServiceSessionLevelRef/eb-list::*))"!]
[!VAR "SUB_SID_TAB_SEC_LEVELS_COUNT" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*/DcmDsdSubService/eb-list::*/DcmDsdSubServiceSecurityLevelRef/eb-list::*))"!]
[!//
[!IF "$SUB_SID_TAB_SES_LEVELS_COUNT > 0"!]
  /* Array of session types for all Subservices */
  STATIC CONST(Dcm_SesCtrlType,DCM_CONST) Dcm_SubSidTabSesLevels[[!"$SUB_SID_TAB_SES_LEVELS_COUNT"!]] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
      [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
        [!LOOP "util:distinct(node:order(DcmDsdSubService/eb-list::*, 'DcmDsdSubServiceId'))"!][!//
          [!LOOP "DcmDsdSubServiceSessionLevelRef/eb-list::*"!][!//
            [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U, /* [!"as:name(node:ref(.))"!] of [!"as:name(../../../..)"!] referred by its subservice [!"as:name(../..)"!] */
          [!ENDLOOP!][!//
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };

[!ENDIF!]
[!//
[!IF "$SUB_SID_TAB_SEC_LEVELS_COUNT > 0"!]
  /* Array of security types for all Subservices */
  STATIC CONST(Dcm_SecLevelType,DCM_CONST) Dcm_SubSidTabSecLevels[[!"$SUB_SID_TAB_SEC_LEVELS_COUNT"!]] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
      [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
        [!LOOP "util:distinct(node:order(DcmDsdSubService/eb-list::*, 'DcmDsdSubServiceId'))"!][!//
          [!LOOP "DcmDsdSubServiceSecurityLevelRef/eb-list::*"!][!//
            [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U, /* [!"as:name(node:ref(.))"!] of [!"as:name(../../../..)"!] referred by its subservice [!"as:name(../..)"!] */
          [!ENDLOOP!][!//
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };

[!ENDIF!]
[!//
[!VAR "SID_TAB_SES_LEVELS_COUNT" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*/DcmDsdSidTabSessionLevelRef/eb-list::*))"!]
[!VAR "SID_TAB_SEC_LEVELS_COUNT" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*/DcmDsdSidTabSecurityLevelRef/eb-list::*))"!]
[!//
[!IF "$SID_TAB_SES_LEVELS_COUNT > 0"!]
  /* Array of session types for all services */
  STATIC CONST(Dcm_SesCtrlType,DCM_CONST) Dcm_SidTabSesLevels[[!"$SID_TAB_SES_LEVELS_COUNT"!]] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
      [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
        [!LOOP "DcmDsdSidTabSessionLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U, /* [!"as:name(node:ref(.))"!] referred to by [!"as:name(../..)"!] */
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };

[!ENDIF!]
[!//
[!IF "$SID_TAB_SEC_LEVELS_COUNT > 0"!]
  /* Array of security types for all services */
  STATIC CONST(Dcm_SecLevelType, DCM_CONST) Dcm_SidTabSecLevels[[!"$SID_TAB_SEC_LEVELS_COUNT"!]] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
      [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
        [!LOOP "DcmDsdSidTabSecurityLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U, /* [!"as:name(node:ref(.))"!] referred to by [!"as:name(../..)"!] */
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };

[!ENDIF!]
[!//
#define DCM_STOP_SEC_CONST_8
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
  [!/* -------- create entry for role element in service/subservice configuration ----------- */!][!//
  [!MACRO "GET_AUTHENTICATION_ROLE", "NodePath", "NodeName"!]
    [!VAR "RoleValue" = "''"!]
    [!IF "node:refexists(concat($NodePath, '/', $NodeName))"!]
      [!VAR "Role" = "node:ref(concat($NodePath, '/', $NodeName))"!]
    [!ELSE!]
      [!VAR "Role" = "0"!]
    [!ENDIF!]
    [!FOR "i" = "0" TO "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationRoleSize - 1"!]
      [!VAR "RoleValue"!]
        [!"num:inttohex($Role mod 256, 2)"!]U, [!//
        [!VAR "Role" = "$Role div 256"!]
        [!"$RoleValue"!][!//
      [!ENDVAR!]
    [!ENDFOR!]
    { [!"$RoleValue"!]} [!//
  [!ENDMACRO!]
[!ENDIF!]
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!VAR "SubSesLevelPos" = "0"!][!//
[!VAR "SubSecLevelPos" = "0"!][!//
[!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
  [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
  [!//
    [!IF "node:exists(./DcmDsdSubService/eb-list::*) and (node:existsAndTrue(./DcmDsdSidTabSubfuncAvail))"!]
      /* Array of Subservices for Service '[!"as:name(.)"!]' */
      [!VAR "SizeOfArray" = "( count(./DcmDsdSubService/eb-list::*))"!][!//
      [!IF "(DcmDsdSidTabServiceId = 62) and not(node:exists(DcmDsdSubService/eb-list::*[DcmDsdSubServiceId = 0]))"!]
        [!VAR "SizeOfArray" = "$SizeOfArray + 1"!][!//
      [!ENDIF!]
      STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig[!"../../DcmDsdSidTabId"!]_SubSidTabEntryConfig[!"DcmDsdSidTabServiceId"!][[!"num:integer($SizeOfArray)"!]] =
      {
        [!IF "(DcmDsdSidTabServiceId = 62) and not(node:exists(DcmDsdSubService/eb-list::*[DcmDsdSubServiceId = 0]))"!]
          [!VAR "NumSubSesLevels" = "num:integer( count( DcmDsdSubServiceSessionLevelRef/eb-list::*))"!][!//
          [!VAR "NumSubSecLevels" = "num:integer( count( DcmDsdSubServiceSecurityLevelRef/eb-list::*))"!][!//
          [!WS "2"!]{
          [!INDENT "4"!]
            NULL_PTR, /* Pointer to subservice sessions */
            NULL_PTR, /* Pointer to subservice security levels */
            NULL_PTR, /* Pointer to External Subservice function */
            &Dcm_Dsp_TesterPresent_ZeroSubFunction_SSvcH, /* Pointer to Internal Subservice function */
            NULL_PTR, /* Pointer to Mode rule function */
            [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
              [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdSubServiceRole'"!], /* Role */
            [!ENDIF!]
            0x00U, /* SubServiceId */
            [!"$NumSubSesLevels"!]U, /* Number of sub service session levels */
            [!"$NumSubSecLevels"!]U, /* Number of sub service security levels */
          [!ENDINDENT!]
          [!WS "2"!]},
          [!VAR "SubSesLevelPos" = "$SubSesLevelPos + $NumSubSesLevels"!][!//
          [!VAR "SubSecLevelPos" = "$SubSecLevelPos + $NumSubSecLevels"!][!//
        [!ENDIF!]
        [!LOOP "util:distinct(node:order(DcmDsdSubService/eb-list::*, 'DcmDsdSubServiceId'))"!][!//
          [!VAR "NumSubSesLevels" = "num:integer( count( DcmDsdSubServiceSessionLevelRef/eb-list::*))"!][!//
          [!VAR "NumSubSecLevels" = "num:integer( count( DcmDsdSubServiceSecurityLevelRef/eb-list::*))"!][!//
          [!WS "2"!]{
          [!INDENT "4"!]
            [!IF "$NumSubSesLevels > 0"!]
              &( Dcm_SubSidTabSesLevels[[!"num:integer( $SubSesLevelPos)"!]]), /* Pointer to subservice sessions */
            [!ELSE!]
              NULL_PTR, /* Pointer to subservice sessions */
            [!ENDIF!]
            [!IF "$NumSubSecLevels > 0"!]
              &(Dcm_SubSidTabSecLevels[[!"num:integer( $SubSecLevelPos)"!]]), /* Pointer to subservice security levels */
            [!ELSE!]
              NULL_PTR, /* Pointer to subservice security levels */
            [!ENDIF!]
            [!IF "node:exists(DcmDsdSubServiceFnc)"!]
              &[!"DcmDsdSubServiceFnc"!], /* Pointer to External Subservice function */
              NULL_PTR, /* Pointer to Internal Subservice function */
            [!ELSE!][!//
              NULL_PTR, /* Pointer to External Subservice function */
              [!IF "../../DcmDsdSidTabServiceId != 39"!] [!/* Avoid to generate a subservice handler name for service SecurityAccess (0x27), as the sub-service identifier only represents a security level */!][!//
                &[!CALL "DCM_SUB_SERVICE_HANDLER_NAME"!], /* Pointer to Internal Subservice function */
              [!ELSE!][!//
                NULL_PTR, /* Pointer to Internal Subservice function */
              [!ENDIF!]
            [!ENDIF!]
            [!IF "node:exists(DcmDsdSubServiceModeRuleRef)"!]
              &Dcm_ModeRule_[!"as:name(as:ref(DcmDsdSubServiceModeRuleRef))"!]_Result, /*  Pointer to Mode rule function */
            [!ELSE!]
              NULL_PTR, /* Pointer to Mode rule function */
            [!ENDIF!]
            [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
              [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdSubServiceRole'"!], /* Role */
            [!ENDIF!]
            [!"num:inttohex( DcmDsdSubServiceId, 2)"!]U, /* SubServiceId */
            [!"$NumSubSesLevels"!]U, /* Number of sub service session levels */
            [!"$NumSubSecLevels"!]U, /* Number of sub service security levels */
          [!ENDINDENT!]
          [!WS "2"!]},
          [!VAR "SubSesLevelPos" = "$SubSesLevelPos + $NumSubSesLevels"!][!//
          [!VAR "SubSecLevelPos" = "$SubSecLevelPos + $NumSubSecLevels"!][!//
        [!ENDLOOP!]
      };

    [!ELSEIF "(DcmDsdSidTabServiceId = 62) and (not(node:exists(DcmDsdSidTabFnc)) or (node:exists(DcmDsdSidTabFnc) and node:existsAndFalse(DcmDsdDisableGenericServiceImplementation)))"!]
      /* Array of Subservices for Service '[!"as:name(.)"!]' */
      STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig[!"../../DcmDsdSidTabId"!]_SubSidTabEntryConfig[!"DcmDsdSidTabServiceId"!][1] =
      {
        [!VAR "NumSubSesLevels" = "num:integer( count( DcmDsdSubServiceSessionLevelRef/eb-list::*))"!][!//
        [!VAR "NumSubSecLevels" = "num:integer( count( DcmDsdSubServiceSecurityLevelRef/eb-list::*))"!][!//
        [!WS "2"!]{
        [!INDENT "4"!]
          NULL_PTR, /* Pointer to subservice sessions */
          NULL_PTR, /* Pointer to subservice security levels */
          NULL_PTR, /* Pointer to External Subservice function */
          &Dcm_Dsp_TesterPresent_ZeroSubFunction_SSvcH, /* Pointer to Internal Subservice function */
          NULL_PTR, /* Pointer to Mode rule function */
          [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
            [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdSubServiceRole'"!], /* Role */
          [!ENDIF!]
          0x00U, /* SubServiceId */
          [!"$NumSubSesLevels"!]U, /* Number of sub service session levels */
          [!"$NumSubSecLevels"!]U, /* Number of sub service security levels */
        [!ENDINDENT!]
        [!WS "2"!]},
        [!VAR "SubSesLevelPos" = "$SubSesLevelPos + $NumSubSesLevels"!][!//
        [!VAR "SubSecLevelPos" = "$SubSecLevelPos + $NumSubSecLevels"!][!//
      };
    [!ELSEIF "((DcmDsdSidTabServiceId = 49) and ((count(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed)]) > 0) or (node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineEnableDefaultInterfaces)))) and ((not(node:exists(DcmDsdSidTabFnc))) or ((node:exists(DcmDsdSidTabFnc)) and (node:existsAndFalse(DcmDsdDisableGenericServiceImplementation))))"!]
          /* Array of Subservices for Service '[!"as:name(.)"!]' */
      STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig[!"../../DcmDsdSidTabId"!]_SubSidTabEntryConfig[!"DcmDsdSidTabServiceId"!][3] =
      {
        [!WS "2"!]{
        [!INDENT "4"!]
          NULL_PTR, /* Pointer to subservice sessions */
          NULL_PTR, /* Pointer to subservice security levels */
          NULL_PTR, /* Pointer to External Subservice function */
          &Dcm_Dsp_RoutineControl_StartRoutine_SSvcH, /* Pointer to Internal Subservice function */
          NULL_PTR, /* Pointer to Mode rule function */
          [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
            [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdSubServiceRole'"!], /* Role */
          [!ENDIF!]
          0x01U, /* SubServiceId */
          0x00U, /* Number of sub service session levels */
          0x00U, /* Number of sub service security levels */
        [!ENDINDENT!]
        [!WS "2"!]},

        [!WS "2"!]{
        [!INDENT "4"!]
          NULL_PTR, /* Pointer to subservice sessions */
          NULL_PTR, /* Pointer to subservice security levels */
          NULL_PTR, /* Pointer to External Subservice function */
          &Dcm_Dsp_RoutineControl_StopRoutine_SSvcH, /* Pointer to Internal Subservice function */
          NULL_PTR, /* Pointer to Mode rule function */
          [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
            [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdSubServiceRole'"!], /* Role */
          [!ENDIF!]
          0x02U, /* SubServiceId */
          0x00U, /* Number of sub service session levels */
          0x00U, /* Number of sub service security levels */
        [!ENDINDENT!]
        [!WS "2"!]},

        [!WS "2"!]{
        [!INDENT "4"!]
          NULL_PTR, /* Pointer to subservice sessions */
          NULL_PTR, /* Pointer to subservice security levels */
          NULL_PTR, /* Pointer to External Subservice function */
          &Dcm_Dsp_RoutineControl_RequestResults_SSvcH, /* Pointer to Internal Subservice function */
          NULL_PTR, /* Pointer to Mode rule function */
          [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
            [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdSubServiceRole'"!], /* Role */
          [!ENDIF!]
          0x03U, /* SubServiceId */
          0x00U, /* Number of sub service session levels */
          0x00U, /* Number of sub service security levels */
        [!ENDINDENT!]
        [!WS "2"!]}
      };
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
[!//
[!IF "$SUB_SID_TAB_SES_LEVELS_COUNT != num:i($SubSesLevelPos)"!]
[!ERROR!]Error calculating SubSesLevelPos ([!"$SUB_SID_TAB_SES_LEVELS_COUNT"!] != [!"$SubSesLevelPos"!])[!ENDERROR!]
[!ENDIF!]
[!IF "$SUB_SID_TAB_SEC_LEVELS_COUNT != num:i($SubSecLevelPos)"!]
[!ERROR!]Error calculating SubSecLevelPos ([!"$SUB_SID_TAB_SEC_LEVELS_COUNT"!] != [!"$SubSecLevelPos"!])[!ENDERROR!]
[!ENDIF!]
[!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!VAR "SesLevelPos" = "0"!][!//
[!VAR "SecLevelPos" = "0"!][!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
[!//
  /* Array of services for Service table '[!"as:name( .)"!]' (id [!"DcmDsdSidTabId"!]) */
  STATIC CONST(Dcm_SidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig[!"DcmDsdSidTabId"!][[!"num:integer( count(DcmDsdService/eb-list::*))"!]] =
    {
      [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
        [!VAR "NumSesLevels" = "num:integer( count( DcmDsdSidTabSessionLevelRef/eb-list::*))"!][!//
        [!VAR "NumSecLevels" = "num:integer( count( DcmDsdSidTabSecurityLevelRef/eb-list::*))"!][!//
        [!WS "2"!]{
        [!INDENT "4"!]
          [!IF "$NumSesLevels > 0"!]
            &( Dcm_SidTabSesLevels[[!"num:integer( $SesLevelPos)"!]]), /* Pointer to sessions */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!]
          [!IF "$NumSecLevels > 0"!]
            &( Dcm_SidTabSecLevels[[!"num:integer( $SecLevelPos)"!]]),/* Pointer to security levels */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!]
          [!IF "(node:exists(./DcmDsdSubService/eb-list::*) and (node:existsAndTrue(./DcmDsdSidTabSubfuncAvail))) or ((DcmDsdSidTabServiceId = 62) and (not(node:exists(DcmDsdSidTabFnc)) or (node:exists(DcmDsdSidTabFnc) and node:existsAndFalse(DcmDsdDisableGenericServiceImplementation)))) or (((DcmDsdSidTabServiceId = 49) and ((count(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed)]) > 0) or (node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineEnableDefaultInterfaces)))) and ((not(node:exists(DcmDsdSidTabFnc))) or ((node:exists(DcmDsdSidTabFnc)) and (node:existsAndFalse(DcmDsdDisableGenericServiceImplementation)))))"!]
            (Dcm_SidTabEntryConfig[!"../../DcmDsdSidTabId"!]_SubSidTabEntryConfig[!"DcmDsdSidTabServiceId"!]), /*Pointer to subservices array. */
          [!ELSE!]
            NULL_PTR, /*Pointer to subservices array. */
          [!ENDIF!]
          [!IF "not(node:exists(DcmDsdSidTabFnc))"!]
            [!IF "(DcmDsdSidTabServiceId != 1) and (DcmDsdSidTabServiceId != 2) and (DcmDsdSidTabServiceId != 3) and (DcmDsdSidTabServiceId != 4) and (DcmDsdSidTabServiceId != 6) and (DcmDsdSidTabServiceId != 7) and (DcmDsdSidTabServiceId != 8)
              and (DcmDsdSidTabServiceId != 9) and (DcmDsdSidTabServiceId != 10) and (DcmDsdSidTabServiceId != 16) and (DcmDsdSidTabServiceId != 20)
              and (DcmDsdSidTabServiceId != 25) and (DcmDsdSidTabServiceId != 35) and (DcmDsdSidTabServiceId != 36) and (DcmDsdSidTabServiceId != 39) and (DcmDsdSidTabServiceId != 47) and (DcmDsdSidTabServiceId != 61) and
              (DcmDsdSidTabServiceId != 49) and (DcmDsdSidTabServiceId != 62) and (DcmDsdSidTabServiceId != 34) and (DcmDsdSidTabServiceId != 42) and (DcmDsdSidTabServiceId != 46) and  (DcmDsdSidTabServiceId != 17) and (DcmDsdSidTabServiceId != 52) and (DcmDsdSidTabServiceId != 53) and (DcmDsdSidTabServiceId != 54) and (DcmDsdSidTabServiceId != 40) and (DcmDsdSidTabServiceId != 41) and (DcmDsdSidTabServiceId != 44) and (DcmDsdSidTabServiceId != 55) and (DcmDsdSidTabServiceId != 133) and (DcmDsdSidTabServiceId != 135) and (DcmDsdSidTabServiceId != 134) and (DcmDsdSidTabServiceId != 175) "!][!//
            [!ERROR "This service is not implemented in Dsp."!][!//
            [!ELSE!][!//
              NULL_PTR,
              &[!CALL "DCM_SERVICE_HANDLER_NAME"!],  /* Pointer to internal service function */
            [!ENDIF!]
          [!ELSE!][!//
            [!IF "node:existsAndTrue(DcmDsdDisableGenericServiceImplementation)"!]
              &[!"DcmDsdSidTabFnc"!], /* Pointer to external service function */
              NULL_PTR,
            [!ELSE!]
              &[!"DcmDsdSidTabFnc"!], /* Pointer to external service function */
              &[!CALL "DCM_SERVICE_HANDLER_NAME"!],  /* Pointer to internal service function */
            [!ENDIF!]
          [!ENDIF!][!//
          [!IF "node:exists(DcmDsdSidTabModeRuleRef)"!]
            &Dcm_ModeRule_[!"as:name(as:ref(DcmDsdSidTabModeRuleRef))"!]_Result, /* Service Mode rule */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!][!//
          [!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
            [!CALL "GET_AUTHENTICATION_ROLE", "NodePath" = "node:path(.)", "NodeName" = "'DcmDsdServiceRole'"!], /* Role */
          [!ENDIF!]
          [!"num:inttohex( DcmDsdSidTabServiceId, 2)"!]U, /* ServiceId */
          [!"$NumSesLevels"!]U, /* Number of sessions */
          [!"$NumSecLevels"!]U, /* Number of security levels */
          [!IF "(DcmDsdSidTabServiceId = 62)"!]
            [!IF "node:exists(./DcmDsdSubService/eb-list::*)"!]
              [!IF "node:exists(./DcmDsdSubService/eb-list::*[DcmDsdSubServiceId = 0])"!]
                [!"num:integer( count(./DcmDsdSubService/eb-list::*))"!]U, /* Number of subservices */
              [!ELSE!]
                [!"num:integer( count(./DcmDsdSubService/eb-list::*) + 1)"!]U, /* Number of subservices */
              [!ENDIF!]
            [!ELSE!]
              1U, /* Number of subservices */
            [!ENDIF!]
            TRUE, /* Subfunction available */
          [!ELSEIF "((DcmDsdSidTabServiceId = 49) and ((count(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed)]) > 0) or (node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineEnableDefaultInterfaces))))"!]
            3U, /* Number of subservices */
            TRUE, /* Subfunction available */
          [!ELSE!]
            [!"num:integer( count(./DcmDsdSubService/eb-list::*))"!]U, /* Number of subservices */
            [!"text:toupper( DcmDsdSidTabSubfuncAvail)"!], /* Subfunction available */
          [!ENDIF!][!//
          [!"text:toupper(DcmAsyncServiceExecution)"!] /* AsyncServiceExecution available */
        [!ENDINDENT!]
        [!WS "2"!]},
        [!VAR "SesLevelPos" = "$SesLevelPos + $NumSesLevels"!][!//
        [!VAR "SecLevelPos" = "$SecLevelPos + $NumSecLevels"!][!//
      [!ENDLOOP!][!//
    };

[!ENDLOOP!]
[!//
[!IF "$SID_TAB_SES_LEVELS_COUNT != num:i($SesLevelPos)"!]
[!ERROR!]Error calculating SesLevelPos ([!"$SID_TAB_SES_LEVELS_COUNT"!] != [!"$SesLevelPos"!])[!ENDERROR!]
[!ENDIF!]
[!IF "$SID_TAB_SEC_LEVELS_COUNT != num:i($SecLevelPos)"!]
[!ERROR!]Error calculating SecLevelPos ([!"$SID_TAB_SEC_LEVELS_COUNT"!] != [!"$SecLevelPos"!])[!ENDERROR!]
[!ENDIF!]
[!//
[!/*---------------Security Access Levels configured for read access to memory locations------------*/!][!//
[!VAR "readMemSeccountAddr" = "count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspReadMemoryRangeInfo/eb-list::*/DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*)"!][!//
[!VAR "readMemSeccountLabel" = "count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspReadMemoryRangeByLabelInfo/eb-list::*/DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*)"!][!//
[!//
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_8
#include <Dcm_MemMap.h>

[!IF "(num:i($readMemSeccountAddr)+num:i($readMemSeccountLabel)) > 0 and $DCM_DSP_USE_MEMORYSERVICES = 'STD_ON'"!]
  STATIC CONST(Dcm_SecLevelType,DCM_CONST) Dcm_ReadMemSecLevels[[!"num:i((num:i($readMemSeccountAddr)+num:i($readMemSeccountLabel)))"!]] =
  {
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*"!][!//
        [!LOOP "./DcmDspReadMemoryRangeInfo/eb-list::*/DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,
        [!ENDLOOP!][!//
        [!LOOP "./DcmDspReadMemoryRangeByLabelInfo/eb-list::*/DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };
[!ENDIF!]

[!/*-------------Security Access Levels configured for Write access to memory locations--*/!][!//
[!VAR "writeMemSeccountAddr" = "count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspWriteMemoryRangeInfo/eb-list::*/DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*)"!][!//
[!VAR "writeMemSeccountLabel" = "count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspWriteMemoryRangeByLabelInfo/eb-list::*/DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*)"!][!//
[!//
[!IF "(num:i($writeMemSeccountAddr)+num:i($writeMemSeccountLabel)) > 0 and $DCM_DSP_USE_MEMORYSERVICES = 'STD_ON'"!]
  STATIC CONST(Dcm_SecLevelType,DCM_CONST) Dcm_WriteMemSecLevels[[!"num:i((num:i($writeMemSeccountAddr)+num:i($writeMemSeccountLabel)))"!]] =
  {
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*"!][!//
        [!LOOP "./DcmDspWriteMemoryRangeInfo/eb-list::*/DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,
        [!ENDLOOP!][!//
        [!LOOP "./DcmDspWriteMemoryRangeByLabelInfo/eb-list::*/DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*"!][!//
          [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };
[!ENDIF!]
#define DCM_STOP_SEC_CONST_8
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[node:existsAndTrue(DcmDspDidUsed)]/DcmDspDidSignal/eb-list::*)"!][!//
#if (DCM_DSP_USE_DIDSERVICES == STD_ON)
  /* Array of signals configured Did services */
  /* !LINKSTO Dcm.Dsn.DidSignals.ConfigurationData.DidSignals,1 */
  CONST(Dcm_DidSignalType,DCM_CONST) Dcm_DidSignals[DCM_DID_SIGNALS_COUNT] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[node:existsAndTrue(DcmDspDidUsed)], 'DcmDspDidIdentifier'))"!][!//
      [!VAR "signaloverlap" = "0"!][!//
      [!VAR "did" = "node:name(.)"!]
      [!VAR "DataPos" = "0"!][!//
      [!LOOP "util:distinct(node:order(DcmDspDidSignal/eb-list::* , 'DcmDspDidDataPos'))"!][!//
        [!VAR "DataPos" = "num:i(DcmDspDidDataPos)"!][!//
        [!WS "2"!]{ [!"num:i($DataPos)"!]U, [!"node:pos(as:ref(DcmDspDidDataRef))"!]U }, /* signal [!"node:pos(.)"!] of Did [!"$did"!] */
        [!VAR "signaloverlap" = "num:i($DataPos) + node:ref(DcmDspDidDataRef)/DcmDspDataSize"!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  };
#endif /* #if (DCM_DSP_USE_DIDSERVICES == STD_ON) */
[!ENDIF!][!//
[!//
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- Create DID related data structures ------------------------- */!][!//
[!/* --------------------------------------------------------------------- */!][!//
[!VAR "didReadAccessSecLevelCount" = "0"!]
[!VAR "didReadAccessSessCount" = "0"!]
[!VAR "didWriteAccessSecLevelCount" = "0"!]
[!VAR "didWriteAccessSessCount" = "0"!]
[!VAR "didControlAccessSecLevelCount" = "0"!]
[!VAR "didControlAccessSessCount" = "0"!]
[!VAR "didReadScalingAccessSecLevelCount" = "0"!]
[!VAR "didReadScalingAccessSessCount" = "0"!]
[!//
[!VAR "did_read_access_sec_array" = "''"!]
[!VAR "did_read_access_sess_array" = "''"!]
[!VAR "did_write_access_sec_array" = "''"!]
[!VAR "did_write_access_sess_array" = "''"!]
[!VAR "did_control_access_sec_array" = "''"!]
[!VAR "did_control_access_sess_array" = "''"!]
[!VAR "did_read_scaling_access_sec_array" = "''"!]
[!VAR "did_read_scaling_access_sess_array" = "''"!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- create one Dcm_DidReadAccessInfo array element ------------- */!][!//
[!MACRO "HANDLE_DID_READ_ACCESS"!]
[!INDENT "2"!]
  [!VAR "secLevelCount" = "num:integer(count(DcmDspDidReadSecurityLevelRef/eb-list::*))"!]
  [!VAR "sessCount" = "num:integer(count(DcmDspDidReadSessionRef/eb-list::*))"!][!//
  {
  [!INDENT "4"!]
  {
    [!INDENT "6"!]
    [!IF "$secLevelCount > 0"!]
      &(Dcm_ReadDidSecTypes[[!"num:integer($didReadAccessSecLevelCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_read_access_sec_array"!]
        [!"$did_read_access_sec_array"!][!//
        [!IF "string-length($did_read_access_sec_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidReadSecurityLevelRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SecLevels */
    [!IF "$sessCount > 0"!]
      &(Dcm_ReadDidSesTypes[[!"num:integer($didReadAccessSessCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_read_access_sess_array"!]
        [!"$did_read_access_sess_array"!][!//
        [!IF "string-length($did_read_access_sess_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidReadSessionRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SesCtrls */
    [!IF "node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmModeDeclarationSupport)"!]
      [!IF "node:exists(DcmDspDidReadModeRuleRef)"!]
        &Dcm_ModeRule_[!"as:name(node:ref(DcmDspDidReadModeRuleRef))"!]_Result[!//
      [!ELSE!]
        NULL_PTR[!//
      [!ENDIF!]
      , /* ModeRuleDidFunction */
    [!ENDIF!]
    [!"$secLevelCount"!], /* NumSecLevels */
    [!"$sessCount"!], /* NumSesCtrls */
    [!ENDINDENT!]
  } /* AccessInfoBase */
  [!ENDINDENT!]
  },
  [!VAR "didReadAccessSecLevelCount" = "$didReadAccessSecLevelCount + $secLevelCount"!]
  [!VAR "didReadAccessSessCount" = "$didReadAccessSessCount + $sessCount"!]
[!ENDINDENT!]
[!ENDMACRO!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- create one Dcm_DidWriteAccessInfo array element ------------ */!][!//
[!MACRO "HANDLE_DID_WRITE_ACCESS"!]
[!INDENT "2"!]
  [!VAR "secLevelCount" = "num:integer(count(DcmDspDidWriteSecurityLevelRef/eb-list::*))"!]
  [!VAR "sessCount" = "num:integer(count(DcmDspDidWriteSessionRef/eb-list::*))"!][!//
  {
  [!INDENT "4"!]
  {
    [!INDENT "6"!]
    [!IF "$secLevelCount > 0"!]
      &(Dcm_WriteDidSecTypes[[!"num:integer($didWriteAccessSecLevelCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_write_access_sec_array"!]
        [!"$did_write_access_sec_array"!][!//
        [!IF "string-length($did_write_access_sec_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidWriteSecurityLevelRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SecLevels */
    [!IF "$sessCount > 0"!]
      &(Dcm_WriteDidSesTypes[[!"num:integer($didWriteAccessSessCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_write_access_sess_array"!]
        [!"$did_write_access_sess_array"!][!//
        [!IF "string-length($did_write_access_sess_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidWriteSessionRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SesCtrls */
    [!IF "node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmModeDeclarationSupport)"!]
      [!IF "node:exists(DcmDspDidWriteModeRuleRef)"!]
        &Dcm_ModeRule_[!"as:name(node:ref(DcmDspDidWriteModeRuleRef))"!]_Result[!//
      [!ELSE!]
        NULL_PTR[!//
      [!ENDIF!]
      , /* ModeRuleDidFunction */
    [!ENDIF!]
    [!"$secLevelCount"!], /* NumSecLevels */
    [!"$sessCount"!], /* NumSesCtrls */
    [!ENDINDENT!]
  } /* AccessInfoBase */
  [!ENDINDENT!]
  },
  [!VAR "didWriteAccessSecLevelCount" = "$didWriteAccessSecLevelCount + $secLevelCount"!]
  [!VAR "didWriteAccessSessCount" = "$didWriteAccessSessCount + $sessCount"!]
[!ENDINDENT!]
[!ENDMACRO!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- create one Dcm_DidIoctlAccessInfo array element ------------ */!][!//
[!MACRO "HANDLE_DID_CONTROL_ACCESS"!]
[!INDENT "2"!]
  [!VAR "secLevelCount" = "num:integer(count(DcmDspDidControlSecurityLevelRef/eb-list::*))"!]
  [!VAR "sessCount" = "num:integer(count(DcmDspDidControlSessionRef/eb-list::*))"!][!//
  {
  [!INDENT "4"!]
  {
    [!INDENT "6"!]
    [!IF "$secLevelCount > 0"!]
      &(Dcm_ControlDidSecLevels[[!"num:integer($didControlAccessSecLevelCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_control_access_sec_array"!]
        [!"$did_control_access_sec_array"!][!//
        [!IF "string-length($did_control_access_sec_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidControlSecurityLevelRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SecLevels */
    [!IF "$sessCount > 0"!]
      &(Dcm_ControlDidSesLevels[[!"num:integer($didControlAccessSessCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_control_access_sess_array"!]
        [!"$did_control_access_sess_array"!][!//
        [!IF "string-length($did_control_access_sess_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidControlSessionRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SesCtrls */
    [!IF "node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmModeDeclarationSupport)"!]
      [!IF "node:exists(DcmDspDidControlModeRuleRef)"!]
        &Dcm_ModeRule_[!"as:name(node:ref(DcmDspDidControlModeRuleRef))"!]_Result[!//
      [!ELSE!]
        NULL_PTR[!//
      [!ENDIF!]
      , /* ModeRuleDidFunction */
    [!ENDIF!]
    [!"$secLevelCount"!], /* NumSecLevels */
    [!"$sessCount"!], /* NumSesCtrls */
    [!ENDINDENT!]
    }, /* AccessInfoBase */
    {
    [!INDENT "6"!]
    [!IF "node:existsAndTrue(DcmDspDidFreezeCurrentState)"!]
      TRUE[!//
    [!ELSE!]
      FALSE[!//
    [!ENDIF!]
    , /* FreezeCurrentStateEnable */
    [!IF "node:existsAndTrue(DcmDspDidResetToDefault)"!]
      TRUE[!//
    [!ELSE!]
      FALSE[!//
    [!ENDIF!]
    , /* ResetToDefaulEnable*/
    [!IF "node:existsAndTrue(DcmDspDidShortTermAdjustment)"!]
      TRUE[!//
    [!ELSE!]
      FALSE[!//
    [!ENDIF!]
    , /* ShortTermAdjustmentEnable */
    [!IF "node:existsAndTrue(DcmDspDidReturnControlToEcu)"!]
      TRUE[!//
    [!ELSE!]
      FALSE[!//
    [!ENDIF!]
    , /* ReturnControlToEcuEnable */
[!IF "$didMaskExternalExists = 'TRUE'"!]
    [!IF "node:exists(DcmDspDidControlMask)"!][!//
    [!"(DcmDspDidControlMask)"!],     /* DcmDspDidControlMask */
    [!"(DcmDspDidControlMaskSize)"!], /* DcmDspDidControlMaskSize */
    [!ELSE!][!//
    DCM_CONTROLMASK_NOT_DEFINED, /* DcmDspDidControlMask */
    0U,                          /* DcmDspDidControlMaskSize */
    [!ENDIF!][!//
[!ENDIF!][!//
    [!WS!]
    [!ENDINDENT!]
  } /* AccessInfoExt */
  [!ENDINDENT!]
  },
  [!VAR "didControlAccessSecLevelCount" = "$didControlAccessSecLevelCount + $secLevelCount"!]
  [!VAR "didControlAccessSessCount" = "$didControlAccessSessCount + $sessCount"!]
[!ENDINDENT!]
[!ENDMACRO!]
[!/* ---------------------------------------------------------------------------- */!][!//
[!/* -------- create one Dcm_DidReadScalingAccessInfo array element ------------- */!][!//
[!MACRO "HANDLE_DID_READSCALING_ACCESS"!]
[!INDENT "2"!]
  [!VAR "secLevelCount" = "num:integer(count(DcmDspDidReadScalingDataSecurityLevelRef/eb-list::*))"!]
  [!VAR "sessCount" = "num:integer(count(DcmDspDidReadScalingDataSessionRef/eb-list::*))"!][!//
  {
  [!INDENT "4"!]
  {
    [!INDENT "6"!]
    [!IF "$secLevelCount > 0"!]
      &(Dcm_ReadScalingDidSecTypes[[!"num:integer($didReadScalingAccessSecLevelCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_read_scaling_access_sec_array"!]
        [!"$did_read_scaling_access_sec_array"!][!//
        [!IF "string-length($did_read_scaling_access_sec_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidReadScalingDataSecurityLevelRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSecurityLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SecLevels */
    [!IF "$sessCount > 0"!]
      &(Dcm_ReadScalingDidSesTypes[[!"num:integer($didReadScalingAccessSessCount)"!]])[!//
[!INDENT "2"!]
      [!VAR "did_read_scaling_access_sess_array"!]
        [!"$did_read_scaling_access_sess_array"!][!//
        [!IF "string-length($did_read_scaling_access_sess_array) != 0"!][!CR!][!ENDIF!][!//
        [!LOOP "DcmDspDidReadScalingDataSessionRef/eb-list::*"!]
          [!"num:inttohex(node:ref(.)/DcmDspSessionLevel, 2)"!]U,[!//
        [!ENDLOOP!]
      [!ENDVAR!]
[!ENDINDENT!]
    [!ELSE!]
      NULL_PTR[!//
    [!ENDIF!]
    , /* SesCtrls */
    [!IF "node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmModeDeclarationSupport)"!]
      [!/*  No modeDeclarationSupport is defined for DcmDspDidReadScalingData */!][!//
      NULL_PTR[!//
      , /* ModeRuleDidFunction */
    [!ENDIF!]
    [!"$secLevelCount"!], /* NumSecLevels */
    [!"$sessCount"!], /* NumSesCtrls */
    [!ENDINDENT!]
  } /* AccessInfoBase */
  [!ENDINDENT!]
  },
  [!VAR "didReadScalingAccessSecLevelCount" = "$didReadScalingAccessSecLevelCount + $secLevelCount"!]
  [!VAR "didReadScalingAccessSessCount" = "$didReadScalingAccessSessCount + $sessCount"!]
[!ENDINDENT!]
[!ENDMACRO!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- initialize access arrays and their element counters -------- */!][!//
[!VAR "did_read_access_array" = "''"!][!//
[!VAR "did_write_access_array" = "''"!][!//
[!VAR "did_control_access_array" = "''"!][!//
[!VAR "did_readscaling_access_array" = "''"!][!//
[!//
[!VAR "didControlAccessCount" = "0"!][!//
[!VAR "didReadAccessCount" = "0"!][!//
[!VAR "didWriteAccessCount" = "0"!][!//
[!VAR "didReadScalingAccessCount" = "0"!][!//
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- variable to store the created element indexes -------------- */!][!//
[!VAR "processedDidInfoIdx" = "'#'"!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- create one Dcm_DidInfo array element ----------------------- */!][!//
[!MACRO "HANDLE_DID_INFO"!]
  [!IF "not(contains($processedDidInfoIdx, concat('#', node:pos(.), '#')))"!]
    [!INDENT "2"!]
    {
      [!INDENT "4"!]
      [!IF "node:exists(DcmDspDidAccess/DcmDspDidRead)"!]
        [!"num:i($didReadAccessCount)"!], /* ReadAccessInfoIdx */
        [!SELECT "DcmDspDidAccess/DcmDspDidRead"!]
          [!VAR "did_read_access_array"!][!//
            [!"$did_read_access_array"!][!CALL "HANDLE_DID_READ_ACCESS"!]
          [!ENDVAR!]
        [!ENDSELECT!]
        [!VAR "didReadAccessCount" = "$didReadAccessCount + 1"!][!//
      [!ELSE!]
        DCM_DIDREADACCESSINFOIDX_INVALID, /* ReadAccessInfoIdx */
      [!ENDIF!]
      [!IF "node:exists(DcmDspDidAccess/DcmDspDidWrite)"!]
        [!"num:i($didWriteAccessCount)"!], /* WriteAccessInfoIdx */
        [!SELECT "DcmDspDidAccess/DcmDspDidWrite"!]
          [!VAR "did_write_access_array"!]
            [!"$did_write_access_array"!][!CALL "HANDLE_DID_WRITE_ACCESS"!]
          [!ENDVAR!]
        [!ENDSELECT!]
        [!VAR "didWriteAccessCount" = "$didWriteAccessCount + 1"!][!//
      [!ELSE!]
        DCM_DIDWRITEACCESSINFOIDX_INVALID, /* WriteAccessInfoIdx */
      [!ENDIF!]
      [!IF "node:exists(DcmDspDidAccess/DcmDspDidControl)"!]
        [!SELECT "DcmDspDidAccess/DcmDspDidControl"!]
          [!VAR "did_control_access_array"!]
            [!"$did_control_access_array"!][!CALL "HANDLE_DID_CONTROL_ACCESS"!]
          [!ENDVAR!]
        [!ENDSELECT!]
        [!"num:i($didControlAccessCount)"!], /* IoctlAccessInfoIdx */
        [!VAR "didControlAccessCount" = "$didControlAccessCount + 1"!][!//
      [!ELSE!]
        DCM_DIDIOCTLACCESSINFOIDX_INVALID, /* IoctlAccessInfoIdx */
      [!ENDIF!]
      [!IF "$DCM_DSP_USE_SERVICE_0X24 = 'STD_ON'"!]
        [!IF "node:exists(DcmDspDidAccess/DcmDspDidReadScalingData)"!]
          [!"num:i($didReadScalingAccessCount)"!], /* ReadScalingAccessInfoIdx */
          [!SELECT "DcmDspDidAccess/DcmDspDidReadScalingData"!]
            [!VAR "did_readscaling_access_array"!][!//
              [!"$did_readscaling_access_array"!][!CALL "HANDLE_DID_READSCALING_ACCESS"!]
            [!ENDVAR!]
          [!ENDSELECT!]
          [!VAR "didReadScalingAccessCount" = "$didReadScalingAccessCount + 1"!][!//
        [!ELSE!]
          DCM_DIDREADSCALINGACCESSINFOIDX_INVALID, /* ReadScalingAccessInfoIdx */
        [!ENDIF!]
      [!ENDIF!]
      [!IF "$DCM_DSP_USE_SERVICE_0X2C = 'STD_ON'"!]
        [!IF "node:existsAndTrue(DcmDspDidDynamicallyDefined) and node:exists(DcmDspDDDIDMaxElements)"!]
          [!"num:i(DcmDspDDDIDMaxElements)"!]U, /* DDDidMaxNumSrcElements */
        [!ELSE!]
          0U, /* DDDidMaxNumSrcElements */
        [!ENDIF!]
      [!ENDIF!]
      [!ENDINDENT!]
    },
    [!ENDINDENT!]
    [!VAR "processedDidInfoIdx" = "concat($processedDidInfoIdx, node:pos(.), '#')"!]
  [!ENDIF!]
[!ENDMACRO!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- calculate the real position based on the stored index ------ */!][!//
[!MACRO "GET_DID_INFO_REF_IDX", "idx"!]
  [!INDENT "4"!]
  [!VAR "str" = "substring-before($processedDidInfoIdx, concat('#', $idx, '#'))"!]
  [!"num:i(string-length($str) - string-length(translate($str,'#','')))"!]U[!//
  [!ENDINDENT!]
[!ENDMACRO!]
[!/* --------------------------------------------------------------------- */!][!//
[!/* -------- create one Dcm_DidRangeConfig array element ---------------- */!][!//
[!MACRO "HANDLE_DID_RANGE"!]
  [!INDENT "2"!]
    {
    [!INDENT "4"!]
      [!IF "node:existsAndTrue(DcmDspDidRangeHasGaps)"!]
        [!IF "node:existsAndFalse(DcmDspDidRangeUsePort)"!]
          &[!"DcmDspDidRangeIsDidAvailableFnc"!], /* IsDidAvailableFnc */
        [!ELSE!]
          &Rte_Call_DataServices_DIDRange_[!"node:name(.)"!]_IsDidAvailable, /* IsDidAvailableFnc */
        [!ENDIF!]
      [!ELSE!]
        NULL_PTR, /* IsDidAvailableFnc */
      [!ENDIF!][!//
      [!IF "node:exists(node:ref(DcmDspDidRangeInfoRef)/DcmDspDidAccess/DcmDspDidRead)"!]
        [!IF "node:existsAndFalse(DcmDspDidRangeUsePort)"!]
          &[!"DcmDspDidRangeReadDidFnc"!], /* ReadDidDataFnc */
        [!ELSE!]
          &Rte_Call_DataServices_DIDRange_[!"node:name(.)"!]_ReadDidData, /* ReadDidDataFnc */
        [!ENDIF!]
      [!ELSE!]
        NULL_PTR, /* ReadDidDataFnc */
      [!ENDIF!][!//
      [!IF "node:exists(node:ref(DcmDspDidRangeInfoRef)/DcmDspDidAccess/DcmDspDidWrite)"!]
        [!IF "node:existsAndFalse(DcmDspDidRangeUsePort)"!]
          &[!"DcmDspDidRangeWriteDidFnc"!], /* WriteDidDataFnc */
        [!ELSE!]
          &Rte_Call_DataServices_DIDRange_[!"node:name(.)"!]_WriteDidData, /* WriteDidDataFnc */
        [!ENDIF!]
      [!ELSE!]
        NULL_PTR, /* WriteDidDataFnc */
      [!ENDIF!][!//
      [!"num:inttohex(DcmDspDidRangeIdentifierLowerLimit)"!]U, /* LowerLimit */
      [!"num:inttohex(DcmDspDidRangeIdentifierUpperLimit)"!]U, /* UpperLimit */
      [!CALL "GET_DID_INFO_REF_IDX", "idx" = "node:pos(node:ref(DcmDspDidRangeInfoRef))"!][!WS!], /* DidInfoIdx */
      [!"DcmDspDidRangeMaxDataLength"!], /* MaxDataLength */
      [!"text:toupper(DcmDspDidRangeHasGaps)"!] /* HasGaps */
    [!ENDINDENT!]
    }, /* index: [!"node:pos(.)"!] */
  [!ENDINDENT!]
[!ENDMACRO!]
[!//
[!VAR "DidRefCount" = "0"!][!//
[!VAR "DidSignalCount" = "0"!][!//
[!VAR "dynamicDidSrcTableCount" = "0"!][!//
[!VAR "DidConfigIndex" = "0"!][!//
[!VAR "FirstObdDidConfigIndex" = "'DCM_DIDCONFIGIDX_INVALID'"!][!//
[!VAR "FirstMonitorDidConfigIndex" = "'DCM_DIDCONFIGIDX_INVALID'"!][!//
[!VAR "FirstInfoTypeDidConfigIndex" = "'DCM_DIDCONFIGIDX_INVALID'"!][!//
[!/* -------- create one Dcm_DidConfig array element --------------------- */!][!//
[!MACRO "HANDLE_DID_CONFIG"!]
  [!VAR "RefCount" = "num:i(count(DcmDspDidRef/eb-list::*))"!]
  [!VAR "SignalCount" = "num:i(count(DcmDspDidSignal/eb-list::*))"!]
  [!IF "$FirstObdDidConfigIndex = 'DCM_DIDCONFIGIDX_INVALID' and (bit:shr(DcmDspDidIdentifier, 8) = 244 or bit:shr(DcmDspDidIdentifier, 8) = 245 or bit:shr(DcmDspDidIdentifier, 8) = 247)"!]
    [!VAR "FirstObdDidConfigIndex" = "$DidConfigIndex"!]
  [!ENDIF!]
  [!IF "$FirstMonitorDidConfigIndex = 'DCM_DIDCONFIGIDX_INVALID' and bit:shr(DcmDspDidIdentifier, 8) = 246"!]
    [!VAR "FirstMonitorDidConfigIndex" = "$DidConfigIndex"!]
  [!ENDIF!]
  [!IF "$FirstInfoTypeDidConfigIndex = 'DCM_DIDCONFIGIDX_INVALID' and bit:shr(DcmDspDidIdentifier, 8) = 248"!]
    [!VAR "FirstInfoTypeDidConfigIndex" = "$DidConfigIndex"!]
  [!ENDIF!]
  [!INDENT "2"!]
  {
    [!INDENT "4"!]
    [!"num:inttohex(DcmDspDidIdentifier)"!]U, /* Did */
    [!"$SignalCount"!]U, /* NumSignals */
    [!CALL "GET_DID_INFO_REF_IDX", "idx" = "node:pos(node:ref(DcmDspDidInfoRef))"!], /* DidInfoIdx */
    [!IF "$RefCount > 0"!]
      [!"num:i($DidRefCount)"!]U[!//
      [!VAR "DidRefCount" = "$DidRefCount + $RefCount"!]
    [!ELSE!]
      DCM_DIDREFERSIDX_INVALID[!//
    [!ENDIF!]
    , /* DidRefersIdx */
    [!IF "$SignalCount > 0"!]
      [!"num:integer($DidSignalCount)"!]U[!//
      [!VAR "DidSignalCount" = "$DidSignalCount + $SignalCount"!]
    [!ELSE!]
      DCM_DIDSIGNALSIDX_INVALID[!//
    [!ENDIF!]
    , /* DidSignalsIdx */
    [!"$RefCount"!]U, /* NumRefDids */
    [!IF "$DCM_DSP_USE_SERVICE_0X2C = 'STD_ON'"!]
      [!IF "node:existsAndTrue(node:ref(DcmDspDidInfoRef)/DcmDspDidDynamicallyDefined)"!]
        [!"num:integer($dynamicDidSrcTableCount)"!]U, /* DDDidSrcTableIdx */
        [!VAR "dynamicDidSrcTableCount" = "$dynamicDidSrcTableCount + num:i(node:ref(DcmDspDidInfoRef)/DcmDspDDDIDMaxElements)"!][!//
      [!ELSE!]
        DCM_DDDIDSRCTABLEIDX_INVALID, /* DDDidSrcTableIdx */
      [!ENDIF!]
    [!ENDIF!]
    [!IF "node:exists(DcmDspDidSignal/eb-list::*[not(starts-with(node:ref(DcmDspDidDataRef)/DcmDspDataUsePort,'USE_DATA_S'))])"!][!//
    [!// Synchronous DID signals are: USE_DATA_SENDER_RECEIVER, USE_DATA_SENDER_RECEIVER_AS_SERVICE, USE_DATA_SYNCH_CLIENT_SERVER, USE_DATA_SYNCH_FNC
      FALSE, /* IsDidSync */
    [!ELSE!]
      TRUE, /* IsDidSync */
    [!ENDIF!]
    [!ENDINDENT!]
  }, /* index: [!"node:pos(.)"!] */
  [!ENDINDENT!]
  [!VAR "DidConfigIndex" = "$DidConfigIndex + 1"!]
[!ENDMACRO!]
[!//
[!VAR "did_range_array" = "''"!]
[!VAR "did_config_array" = "''"!]
[!VAR "did_info_array" = "''"!]
[!VAR "didMaskExternalExists" = "'FALSE'"!]
[!IF "count(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDidInfo/eb-list::*[DcmDspDidAccess/DcmDspDidControl/DcmDspDidControlMask = 'DCM_CONTROLMASK_EXTERNAL']) !=0"!]
  [!VAR "didMaskExternalExists" = "'TRUE'"!]
[!ENDIF!]
[!/* Iterate over the referenced DidInfos from DID or DID ranges,
     construct the DID range, DID info, AccessInfo, security and session level arrays
     If no services are using Data Identifiers, skip this part                             */!][!//
[!IF "$DCM_DSP_USE_DIDSERVICES = 'STD_ON'"!]
  [!VAR "did_info_array"!]
  [!/*---- Loop through the enabled DIDs ----*/!][!//
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[node:existsAndTrue(DcmDspDidUsed)], 'DcmDspDidIdentifier'))"!]
    [!SELECT "node:ref(DcmDspDidInfoRef)"!]
      [!CALL "HANDLE_DID_INFO"!]
    [!ENDSELECT!]
    [!VAR "did_config_array"!]
      [!"$did_config_array"!][!CALL "HANDLE_DID_CONFIG"!]
    [!ENDVAR!]
  [!ENDLOOP!]
  [!/*---- Loop through the DID ranges ----*/!][!//
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDidRange/eb-list::*, 'DcmDspDidRangeIdentifierLowerLimit'))"!]
    [!SELECT "node:ref(DcmDspDidRangeInfoRef)"!]
      [!CALL "HANDLE_DID_INFO"!]
    [!ENDSELECT!]
    [!VAR "did_range_array"!]
      [!"$did_range_array"!][!CALL "HANDLE_DID_RANGE"!]
    [!ENDVAR!]
  [!ENDLOOP!]
  [!ENDVAR!]
[!ENDIF!]

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_8
#include <Dcm_MemMap.h>

[!/*-------------- Dcm_ReadDidSecTypes ------------------------------------*/!][!//
[!IF "string-length($did_read_access_sec_array) != 0"!]
/** \brief Array that holds the configured security levels for read access of the didinfo
           entries */
STATIC CONST(Dcm_SecLevelType, DCM_CONST) Dcm_ReadDidSecTypes[] =
{
  [!WS "2"!][!"$did_read_access_sec_array"!]
};

[!ENDIF!]
[!/*-------------- Dcm_ReadDidSesTypes ------------------------------------*/!][!//
[!IF "string-length($did_read_access_sess_array) != 0"!]
/** \brief Array that holds the configured sessions for read access of the didinfo entries */
STATIC CONST(Dcm_SesCtrlType, DCM_CONST) Dcm_ReadDidSesTypes[] =
{
  [!WS "2"!][!"$did_read_access_sess_array"!]
};

[!ENDIF!]
[!/*-------------- Dcm_WriteDidSecTypes -----------------------------------*/!][!//
[!IF "string-length($did_write_access_sec_array) != 0"!]
/** \brief Array that holds the configured security levels for write access of the didinfo
           entries */
STATIC CONST(Dcm_SecLevelType, DCM_CONST) Dcm_WriteDidSecTypes[] =
{
  [!WS "2"!][!"$did_write_access_sec_array"!]
};

[!ENDIF!]
[!/*-------------- Dcm_WriteDidSesTypes -----------------------------------*/!][!//
[!IF "string-length($did_write_access_sess_array) != 0"!]
/** \brief Array that holds the configured sessions for write access of the didinfo entries */
STATIC CONST(Dcm_SesCtrlType, DCM_CONST) Dcm_WriteDidSesTypes[] =
{
  [!WS "2"!][!"$did_write_access_sess_array"!]
};

[!ENDIF!]
[!/*-------------- Dcm_ControlDidSecLevels --------------------------------*/!][!//
[!IF "string-length($did_control_access_sec_array) != 0"!]
/** \brief Array that holds the configured security levels for control access of the didinfo
           entries */
STATIC CONST(Dcm_SecLevelType,DCM_CONST) Dcm_ControlDidSecLevels[] =
{
  [!WS "2"!][!"$did_control_access_sec_array"!]
};

[!ENDIF!]
[!/*-------------- Dcm_ControlDidSesLevels --------------------------------*/!][!//
[!IF "string-length($did_control_access_sess_array) != 0"!]
/** \brief Array that holds the configured sessions for control access of the didinfo entries */
STATIC CONST(Dcm_SesCtrlType, DCM_CONST) Dcm_ControlDidSesLevels[] =
{
  [!WS "2"!][!"$did_control_access_sess_array"!]
};

[!ENDIF!]

[!/*-------------- Dcm_ReadScalingDidSecTypes ------------------------------------*/!][!//
[!IF "string-length($did_read_scaling_access_sec_array) != 0"!]
/** \brief Array that holds the configured security levels for read scaling access of the didinfo
           entries */
STATIC CONST(Dcm_SecLevelType, DCM_CONST) Dcm_ReadScalingDidSecTypes[] =
{
  [!WS "2"!][!"$did_read_scaling_access_sec_array"!]
};

[!ENDIF!]
[!/*-------------- Dcm_ReadScalingDidSesTypes ------------------------------------*/!][!//
[!IF "string-length($did_read_scaling_access_sess_array) != 0"!]
/** \brief Array that holds the configured sessions for read scaling access of the didinfo
           entries */
STATIC CONST(Dcm_SesCtrlType, DCM_CONST) Dcm_ReadScalingDidSesTypes[] =
{
  [!WS "2"!][!"$did_read_scaling_access_sess_array"!]
};

[!ENDIF!]
#define DCM_STOP_SEC_CONST_8
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!/*-------------- Dcm_DidReadAccessInfo ----------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidReadAccessInfo,1 */
[!IF "string-length($did_read_access_array) != 0"!]
/** \brief Array that holds the configured read access information of the didinfo entries */
CONST(Dcm_DidReadAccessInfoType, DCM_CONST) Dcm_DidReadAccessInfo[] =
{
  [!WS "2"!][!"$did_read_access_array"!][!//
};

[!ENDIF!]
[!/*-------------- Dcm_DidWriteAccessInfo ---------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidWriteAccessInfo,1 */
[!IF "string-length($did_write_access_array) != 0"!]
/** \brief Array that holds the configured write access information of the didinfo entries */
CONST(Dcm_DidWriteAccessInfoType, DCM_CONST) Dcm_DidWriteAccessInfo[] =
{
  [!WS "2"!][!"$did_write_access_array"!][!//
};

[!ENDIF!]
[!/*-------------- Dcm_DidIoctlAccessInfo ---------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidIoctlAccessInfo,1 */
[!IF "string-length($did_control_access_array) != 0"!]
/** \brief Array that holds the configured control access information of the didinfo entries */
CONST(Dcm_DidIoctlAccessInfoType, DCM_CONST) Dcm_DidIoctlAccessInfo[] =
{
  [!WS "2"!][!"$did_control_access_array"!][!//
};

[!ENDIF!]
[!/*-------------- Dcm_DidReadScalingAccessInfo ---------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidReadScalingAccessInfo,1 */
[!IF "string-length($did_readscaling_access_array) != 0"!]
/** \brief Array that holds the configured control access information of the didinfo entries */
CONST(Dcm_DidReadScalingAccessInfoType, DCM_CONST) Dcm_DidReadScalingAccessInfo[] =
{
  [!WS "2"!][!"$did_readscaling_access_array"!][!//
};

[!ENDIF!]
[!/*-------------- Dcm_DidInfo --------------------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidInfo,1 */
[!IF "string-length($did_info_array) != 0"!]
/** \brief Array that holds the configured didinfo entries that are enabled */
CONST(Dcm_DidInfoType, DCM_CONST) Dcm_DidInfo[] =
{
  [!WS "2"!][!"$did_info_array"!][!//
};

[!ENDIF!]
[!/*-------------- Dcm_DidRangeConfig -------------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidRangeConfig,1 */
[!IF "string-length($did_range_array) != 0"!]
/** \brief Array that holds the configured DID ranges */
CONST(Dcm_DidRangeConfigType, DCM_CONST) Dcm_DidRangeConfig[] =
{
  [!WS "2"!][!"$did_range_array"!][!//
};
[!ENDIF!]

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

#if ((DCM_DSP_USE_DIDSERVICES == STD_ON) && (DCM_DID_REF_COUNT > 0))
#define DCM_START_SEC_CONST_16
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidRefers,1 */
/* Array for Dids which is referred from other Dids. */
CONST(uint16,DCM_CONST) Dcm_DidRefers[DCM_DID_REF_COUNT] =
{
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[node:existsAndTrue(DcmDspDidUsed)], 'DcmDspDidIdentifier'))/DcmDspDidRef/eb-list::*"!][!//
    [!WS "2"!][!"num:inttohex(node:ref(.)/DcmDspDidIdentifier)"!]U,
  [!ENDLOOP!][!//
};

#define DCM_STOP_SEC_CONST_16
#include <Dcm_MemMap.h>
#endif /* #if ((DCM_DSP_USE_DIDSERVICES == STD_ON) && (DCM_DID_REF_COUNT > 0)) */
/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!/*-------------- Dcm_DidConfig ------------------------------------------*/!][!//
/* !LINKSTO Dcm.Dsn.DidServices.ConfigurationData.DidConfig,1 */
[!IF "string-length($did_config_array) != 0"!]
CONST(Dcm_DidConfigType, DCM_CONST) Dcm_DidConfig[] =
{
  [!WS "2"!][!"$did_config_array"!][!//
};

[!IF "node:existsAndTrue(DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmDspDidAvailabilityCalculation)"!][!//
CONST(Dcm_DidConfigIdxType, DCM_CONST) Dcm_FirstObdDidConfigIndex = [!//
  [!IF "$FirstObdDidConfigIndex = 'DCM_DIDCONFIGIDX_INVALID'"!][!//
    DCM_DIDCONFIGIDX_INVALID;
  [!ELSE!][!//
    [!"num:i($FirstObdDidConfigIndex)"!]U;
  [!ENDIF!][!//

CONST(Dcm_DidConfigIdxType, DCM_CONST) Dcm_FirstMonitorDidConfigIndex = [!//
  [!IF "$FirstMonitorDidConfigIndex = 'DCM_DIDCONFIGIDX_INVALID'"!][!//
    DCM_DIDCONFIGIDX_INVALID;
  [!ELSE!][!//
    [!"num:i($FirstMonitorDidConfigIndex)"!]U;
  [!ENDIF!][!//

CONST(Dcm_DidConfigIdxType, DCM_CONST) Dcm_FirstInfoTypeDidConfigIndex = [!//
  [!IF "$FirstInfoTypeDidConfigIndex = 'DCM_DIDCONFIGIDX_INVALID'"!][!//
    DCM_DIDCONFIGIDX_INVALID;
  [!ELSE!][!//
    [!"num:i($FirstInfoTypeDidConfigIndex)"!]U;
  [!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
/* Constant holding the pointer to the configured mode rule to be used when re-enabling DTC */
CONST(Dcm_ModeRuleFunctionType, DCM_CONST) Dcm_DspModeRuleDTCFunction =
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspControlDTCSetting/DcmDspControlDTCSettingReEnableModeRuleRef)"!][!//
  [!WS "2"!]&Dcm_ModeRule_[!"as:name(node:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspControlDTCSetting/DcmDspControlDTCSettingReEnableModeRuleRef))"!]_Result; /* re-enable DTC mode rule */
[!ELSE!][!//
  [!WS "2"!]NULL_PTR;
[!ENDIF!][!//
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
[!//

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_8
#include <Dcm_MemMap.h>

/** \brief Configuration structure */
CONST(Dcm_ConfigType, DCM_CONST) [!"as:name(DcmConfigSet/eb-list::*[1])"!] = { 0U };
[!//
[!/*------------------------------------------------------------------*/!][!//

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspAddressAndLengthFormatIdentifier)"!][!//

  /* Array of configuration information of all Supported AddressAndLengthFormatIdentifiers */
  CONST(uint8, DCM_CONST) Dcm_SupportedAddAndLenFormatIds[DCM_NUM_ADDR_LENGTH_FORMAT_IDENTIFIER] =
  {
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspAddressAndLengthFormatIdentifier/DcmDspSupportedAddressAndLengthFormatIdentifier/eb-list::*"!][!//
      [!WS "2"!][!"num:inttohex(.)"!]U,
    [!ENDLOOP!][!//
  };

[!ENDIF!]

#define DCM_STOP_SEC_CONST_8
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

/* Array of configuration information for diagnostic sessions */
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspSession/eb-list::*"!]
  [!IF "node:contains(util:distinct(node:refs(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/eb-list::*/DcmDslProtocolSessionRef)), .)"!]
    STATIC CONST(Dcm_SesTabEntryConfigType, DCM_CONST) Dcm_SesTabEntryConfig[!"node:pos(.)"!][[!"num:integer( count(./DcmDspSessionRow/eb-list::*))"!]] =
    {
    [!LOOP "./DcmDspSessionRow/eb-list::*"!][!//
      [!WS "2"!]{
        [!INDENT "4"!]
          [!"num:integer(round((DcmDspSessionP2StarServerMax) div $DcmTaskTime))"!]U,/*P2StarMaxTime*/
          [!"num:integer(round(DcmDspSessionP2ServerMax div $DcmTaskTime))"!]U, /*P2MaxTime*/
          [!IF "node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspSession/eb-list::*/DcmDspSessionRow/eb-list::*/DcmDspDiagSesRespMaxNumRespPend)"!]
            [!IF "node:exists(DcmDspDiagSesRespMaxNumRespPend)"!]
              [!"num:integer(DcmDspDiagSesRespMaxNumRespPend)"!]U,/* Maximum number of ResponsePending messages */
            [!ELSE!]
              [!"num:i(../../../../../DcmDsl/DcmDslDiagResp/DcmDslDiagRespMaxNumRespPend)"!]U,/* Maximum number of ResponsePending messages takes default value */
            [!ENDIF!]
          [!ENDIF!]
          [!"DcmDspSessionForBoot"!],/*specifies whether this session allows
                                       to jump to Bootloader */
          [!"DcmDspSessionLevel"!]U,/* Session type */
          [!IF "node:existsAndTrue(../../../../../DcmGeneral/DcmModeDeclarationSupport)"!]
            RTE_MODE_DcmDiagnosticSessionControl_[!"as:name(.)"!] /* Session type generate by Rte */
          [!ENDIF!]
        [!ENDINDENT!]
      [!WS "2"!]},
    [!ENDLOOP!][!//
    };
  [!ENDIF!]

[!ENDLOOP!]
[!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
/* Holds configuration information for diagnostic sessions */
CONST(Dcm_SesTabConfigType, DCM_CONST) Dcm_SesTabConfig[DCM_NUM_PROTOCOL] =
{
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/eb-list::*"!]
    [!WS "2"!]{
      [!INDENT "4"!]
        Dcm_SesTabEntryConfig[!"node:pos(as:ref(DcmDslProtocolSessionRef))"!], /* Pointer to session configurations */
        [!"num:integer( count(as:ref(DcmDslProtocolSessionRef)/eb-list::*/eb-list::*))"!]U, /* Number of configured sessions */
        [!VAR "Indx" = "(node:pos(as:ref(DcmDslProtocolSessionRef)))"!]
        [!LOOP "../../../../DcmDsp/DcmDspSession/eb-list::*/DcmDspSessionRow/eb-list::*"!]
          [!IF "(./DcmDspSessionLevel = 1) and (number(node:pos(../..)) = number($Indx))"!]
            [!"node:pos(.)"!]U /* Index of default session */
          [!ENDIF!]
        [!ENDLOOP!]
      [!ENDINDENT!]
    [!WS "2"!]},
  [!ENDLOOP!]
};

[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!//
/* Initialize global array holding the configuration for the service Id table */
CONST(Dcm_SidTabConfigType, DCM_CONST) Dcm_SidTabConfig[[!"num:integer( count( DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*))"!]] =
{
  [!FOR "SidTabId"="0" TO "count( DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*) - 1"!][!//
    [!SELECT "DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*[number(DcmDsdSidTabId) = number($SidTabId)]"!][!//
    [!WS "2"!]{
      [!WS "4"!]Dcm_SidTabEntryConfig[!"$SidTabId"!], /* Pointer to array of service table entries */
      [!WS "4"!][!"num:integer(count(DcmDsdService/eb-list::*))"!]U /* Number of service entries within this table */
    [!WS "2"!]},
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
};

[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslCallbackDCMRequestService/eb-list::*)"!]
CONST(Dcm_CallbackRequestServicesType, DCM_CONST) Dcm_CallbackRequests[DCM_CALLBACK_REQUEST_SIZE] =
{
[!INDENT "2"!]
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslCallbackDCMRequestService/eb-list::*"!]
  {
[!INDENT "4"!]
    &Rte_Call_Dcm_CallBackDCMRequestServices_[!"node:name(.)"!]_StartProtocol, /* StartProtocol */
    &Rte_Call_Dcm_CallBackDCMRequestServices_[!"node:name(.)"!]_StopProtocol, /* StopProtocol */
[!ENDINDENT!]
  },
[!ENDLOOP!]
[!ENDINDENT!]
};

[!ENDIF!][!//
[!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!//
[!LOOP "DcmConfigSet/eb-list::*/DcmDsp/DcmDspDid/eb-list::*"!]
[!/*-1) Check for the service 0x2E .If a DataConfigured as USE_DATA_SYNCH_FNC or
   USE_DATA_ASYNCH_FNC, its writedata functions must be configured provided if it is linked to a
   signal with write access.
   -2) If the fixed lenth is false only one signal can be configured for a Did which has write
    access ---*/!][!//
  [!IF "node:exists(node:ref(DcmDspDidInfoRef)/DcmDspDidAccess/DcmDspDidWrite)"!]
    [!VAR "numsignals" = "count(DcmDspDidSignal/eb-list::*)"!][!//
    [!LOOP "DcmDspDidSignal/eb-list::*"!]
      [!SELECT "node:ref(DcmDspDidDataRef)"!][!//
        [!IF "(DcmDspDataUsePort = 'USE_DATA_SYNCH_FNC' or DcmDspDataUsePort = 'USE_DATA_ASYNCH_FNC') and (not(node:exists(DcmDspDataWriteFnc)))"!]
        [!ERROR!]
            Configure WriteData operation for Data configuration [!"node:name(.)"!]
            This Data is configured as '[!"node:value(DcmDspDataUsePort)"!]' and is mapped to
            a signal which has write access.
          [!ENDERROR!]
        [!ENDIF!]
      [!ENDSELECT!]
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDLOOP!][!//
[!//

[!/*------------------------------------------------------------------*/!][!//
[!IF "(node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspReadMemoryRangeInfo/eb-list::*) or node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspReadMemoryRangeByLabelInfo/eb-list::*)) and $DCM_DSP_USE_MEMORYSERVICES = 'STD_ON'"!]
[!/* !LINKSTO SWS_Dcm_01158_RangeByAddress_GenError_condition,1 */!][!//
  [!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspReadMemoryRangeInfo/eb-list::*)"!]
    [!SELECT "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory"!][!//
      [!LOOP "util:distinct(node:order(./DcmDspMemoryIdInfo/eb-list::*/DcmDspReadMemoryRangeInfo/eb-list::* ,'DcmDspReadMemoryRangeLow', 'DcmDspReadMemoryRangeHigh'))"!][!//
      [!VAR "CurrentHighLimit" = "-1"!][!//
      [!VAR "CurrentLowLimit" = "-1"!][!//
      [!VAR "PreviousHighLimit" = "-1"!][!//
        [!VAR "CurrentHighLimit" = "num:i(DcmDspReadMemoryRangeHigh)"!][!//
        [!VAR "CurrentLowLimit" = "num:i(DcmDspReadMemoryRangeLow)"!][!//
            [!IF "$PreviousHighLimit > $CurrentLowLimit"!]
              [!ERROR!]
                 Read memory ranges for configuration parameter [!"node:name(./../..)"!]/[!"node:name(.)"!] are overlapped.
              [!ENDERROR!]
            [!ENDIF!]
        [!VAR "PreviousHighLimit" = "$CurrentHighLimit"!][!//
      [!ENDLOOP!]
    [!ENDSELECT!][!//
  [!ENDIF!]
  [!VAR "ReadMemSecPos" = "0"!][!//
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*"!]
    [!IF "node:exists(./DcmDspReadMemoryRangeInfo/eb-list::*) or node:exists(./DcmDspReadMemoryRangeByLabelInfo/eb-list::*) "!]
    /** \brief Provides the range of memory address allowed for reading */
    STATIC CONST(Dcm_MemoryRangeInfoType,DCM_CONST) Dcm_ReadMemoryRangeInfoTable[!"node:pos(.)"!][[!"num:i(num:i(count(DcmDspReadMemoryRangeInfo/eb-list::*))+num:i(count(DcmDspReadMemoryRangeByLabelInfo/eb-list::*)))"!]] =
    {
    [!LOOP "DcmDspReadMemoryRangeInfo/eb-list::*"!]
      [!VAR "ReadMemSecLevels" = "num:integer(count(DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*))"!][!//
      [!WS "2"!]{
        [!INDENT "4"!]
          [!/*---MemoryRangeLow configured by Address------*/!][!//
          [!"num:inttohex(DcmDspReadMemoryRangeLow)"!]U,
          [!/*---MemoryRangeHigh configured by Address------*/!][!//
          [!"num:inttohex(DcmDspReadMemoryRangeHigh)"!]U,
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
          [!/*---DcmDspReadMemoryRangeModeRuleRef------*/!][!//
          [!IF "node:exists(DcmDspReadMemoryRangeModeRuleRef)"!]
            &Dcm_ModeRule_[!"as:name(node:ref(DcmDspReadMemoryRangeModeRuleRef))"!]_Result, /* mem read mode rule */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!]
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
          [!/* Configurations for Read Memory access*/!][!//
          [!IF "node:exists(util:distinct(node:refs(DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*)))"!]
              [!IF "$ReadMemSecLevels > 0"!]
                &(Dcm_ReadMemSecLevels[[!"num:integer( $ReadMemSecPos)"!]]),
              [!ELSE!]
                NULL_PTR,
              [!ENDIF!]
                [!"$ReadMemSecLevels"!]U,
          [!ELSE!]
            NULL_PTR,
            0U,
          [!ENDIF!]
        [!ENDINDENT!]
      [!WS "2"!]},
      [!VAR "ReadMemSecPos" = "$ReadMemSecPos + $ReadMemSecLevels"!][!//
    [!ENDLOOP!]

    [!LOOP "DcmDspReadMemoryRangeByLabelInfo/eb-list::*"!]
      [!VAR "ReadMemSecLevelsByLabel" = "num:integer(count(DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*))"!][!//
      [!WS "2"!]{
        [!INDENT "4"!]
          [!/*---MemoryRangeLow configured by Label------*/!][!//
          (uint32)([!"node:value(DcmDspReadMemoryRangeByLabelLow)"!]),
          [!/*---MemoryRangeHigh configured by Label------*/!][!//
          (uint32)([!"node:value(DcmDspReadMemoryRangeByLabelHigh)"!]),
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
          [!/*---DcmDspReadMemoryRangeModeRuleRef------*/!][!//
          [!IF "node:exists(DcmDspReadMemoryRangeModeRuleRef)"!]
            &Dcm_ModeRule_[!"as:name(node:ref(DcmDspReadMemoryRangeModeRuleRef))"!]_Result, /* mem read mode rule */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!]
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
          [!/* Configurations for Read Memory access*/!][!//
          [!IF "node:exists(util:distinct(node:refs(DcmDspReadMemoryRangeSecurityLevelRef/eb-list::*)))"!]
              [!IF "$ReadMemSecLevelsByLabel > 0"!]
                &(Dcm_ReadMemSecLevels[[!"num:integer( $ReadMemSecPos)"!]]),
              [!ELSE!]
                NULL_PTR,
              [!ENDIF!]
                [!"$ReadMemSecLevelsByLabel"!]U,
          [!ELSE!]
            NULL_PTR,
            0U,
          [!ENDIF!]
        [!ENDINDENT!]
      [!WS "2"!]},
      [!VAR "ReadMemSecPos" = "$ReadMemSecPos + $ReadMemSecLevelsByLabel"!][!//
    [!ENDLOOP!]
    };

    [!ENDIF!]
  [!ENDLOOP!]
[!ENDIF!]

[!//
[!IF "(node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspWriteMemoryRangeInfo/eb-list::*) or node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspWriteMemoryRangeByLabelInfo/eb-list::*)) and $DCM_DSP_USE_MEMORYSERVICES = 'STD_ON'"!]
[!/* !LINKSTO SWS_Dcm_01056_RangeByAddress_GenError_condition,1 */!][!//
  [!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*/DcmDspWriteMemoryRangeInfo/eb-list::*)"!]
    [!SELECT "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory"!][!//
        [!LOOP "util:distinct(node:order(./DcmDspMemoryIdInfo/eb-list::*/DcmDspWriteMemoryRangeInfo/eb-list::* ,'DcmDspWriteMemoryRangeLow', 'DcmDspWriteMemoryRangeHigh'))"!][!//
        [!VAR "CurrentHighLimit" = "-1"!][!//
        [!VAR "CurrentLowLimit" = "-1"!][!//
        [!VAR "PreviousHighLimit" = "-1"!][!//
          [!VAR "CurrentHighLimit" = "num:i(DcmDspWriteMemoryRangeHigh)"!][!//
          [!VAR "CurrentLowLimit" = "num:i(DcmDspWriteMemoryRangeLow)"!][!//
              [!IF "$PreviousHighLimit > $CurrentLowLimit"!]
                [!ERROR!]
                   Write memory ranges for configuration parameter [!"node:name(./../..)"!]/[!"node:name(.)"!] are overlapped.
                [!ENDERROR!]
              [!ENDIF!]
          [!VAR "PreviousHighLimit" = "$CurrentHighLimit"!][!//
        [!ENDLOOP!]
    [!ENDSELECT!][!//
  [!ENDIF!]
  [!VAR "WriteMemSecPos" = "0"!][!//
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*"!]
    [!IF "node:exists(./DcmDspWriteMemoryRangeInfo/eb-list::*) or node:exists(./DcmDspWriteMemoryRangeByLabelInfo/eb-list::*)"!]
    /** \brief Provides the range of memory address allowed for writing */
    STATIC CONST(Dcm_MemoryRangeInfoType,DCM_CONST) Dcm_WriteMemoryRangeInfoTable[!"node:pos(.)"!][[!"num:i(num:i(count(DcmDspWriteMemoryRangeInfo/eb-list::*))+num:i(count(DcmDspWriteMemoryRangeByLabelInfo/eb-list::*)))"!]] =
    {
    [!LOOP "DcmDspWriteMemoryRangeInfo/eb-list::*"!]
      [!VAR "NumSecLevels" = "num:integer(count(DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*))"!][!//
      [!WS "2"!]{
        [!INDENT "4"!]
          [!/*---MemoryRangeLow configured by Address------*/!][!//
          [!"num:inttohex(DcmDspWriteMemoryRangeLow)"!]U,
          [!/*---MemoryRangeHigh configured by Address------*/!][!//
          [!"num:inttohex(DcmDspWriteMemoryRangeHigh)"!]U,
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
          [!/*---DcmDspWriteMemoryRangeModeRuleRef------*/!][!//
          [!IF "node:exists(DcmDspWriteMemoryRangeModeRuleRef)"!]
            &Dcm_ModeRule_[!"as:name(node:ref(DcmDspWriteMemoryRangeModeRuleRef))"!]_Result, /* mem write mode rule */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!]
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
          /* Configurations for Write Memory access*/
          [!IF "node:exists(util:distinct(node:refs(DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*)))"!]
            [!IF "$NumSecLevels > 0"!]
              &(Dcm_WriteMemSecLevels[[!"num:integer( $WriteMemSecPos)"!]]),
            [!ELSE!]
              NULL_PTR,
            [!ENDIF!]
              [!"$NumSecLevels"!]U,
          [!ELSE!]
            NULL_PTR,
            0,
          [!ENDIF!]
        [!ENDINDENT!]
      [!WS "2"!]},
      [!VAR "WriteMemSecPos" = "$WriteMemSecPos + $NumSecLevels"!][!//
    [!ENDLOOP!]

    [!LOOP "DcmDspWriteMemoryRangeByLabelInfo/eb-list::*"!]
      [!VAR "NumSecLevelsByLabel" = "num:integer(count(DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*))"!][!//
      [!WS "2"!]{
        [!INDENT "4"!]
          [!/*---MemoryRangeLow configured by Label------*/!][!//
          (uint32)([!"node:value(DcmDspWriteMemoryRangeByLabelLow)"!]),
          [!/*---MemoryRangeHigh configured by Label------*/!][!//
          (uint32)([!"node:value(DcmDspWriteMemoryRangeByLabelHigh)"!]),
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
          [!/*---DcmDspWriteMemoryRangeModeRuleRef------*/!][!//
          [!IF "node:exists(DcmDspWriteMemoryRangeModeRuleRef)"!]
            &Dcm_ModeRule_[!"as:name(node:ref(DcmDspWriteMemoryRangeModeRuleRef))"!]_Result, /* mem write mode rule */
          [!ELSE!]
            NULL_PTR,
          [!ENDIF!]
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
          /* Configurations for Write Memory access*/
          [!IF "node:exists(util:distinct(node:refs(DcmDspWriteMemoryRangeSecurityLevelRef/eb-list::*)))"!]
            [!IF "$NumSecLevelsByLabel > 0"!]
              &(Dcm_WriteMemSecLevels[[!"num:integer($WriteMemSecPos)"!]]),
            [!ELSE!]
              NULL_PTR,
            [!ENDIF!]
              [!"$NumSecLevelsByLabel"!]U,
          [!ELSE!]
            NULL_PTR,
            0U,
          [!ENDIF!]
        [!ENDINDENT!]
      [!WS "2"!]},
      [!VAR "WriteMemSecPos" = "$WriteMemSecPos + $NumSecLevelsByLabel"!][!//
    [!ENDLOOP!]
    };

    [!ENDIF!]
  [!ENDLOOP!]
[!ENDIF!]
[!//
[!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*) and $DCM_DSP_USE_MEMORYSERVICES = 'STD_ON'"!]
  /** \brief Provides the configuration of memory access requested through diagnostic services: WriteMemoryByAddress and readMemoryByAddress*/
CONST(Dcm_MemoryIdInfoType, DCM_CONST) Dcm_MemoryIdInfoAndIdValueTable[DCM_NUM_MEMORY_IDINFO] =
{
  [!INDENT "2"!]
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspMemory/DcmDspMemoryIdInfo/eb-list::*"!]
  {
    [!INDENT "4"!]
      /* Pointer to Write memory range info configurations */
      [!IF "(node:exists(./DcmDspWriteMemoryRangeInfo/eb-list::*) or node:exists(./DcmDspWriteMemoryRangeByLabelInfo/eb-list::*))"!]
        Dcm_WriteMemoryRangeInfoTable[!"node:pos(.)"!],
      [!ELSE!]
        NULL_PTR,
      [!ENDIF!]
      /* Pointer to Read memory range info configurations */
      [!IF "(node:exists(./DcmDspReadMemoryRangeInfo/eb-list::*) or node:exists(./DcmDspReadMemoryRangeByLabelInfo/eb-list::*))"!]
        Dcm_ReadMemoryRangeInfoTable[!"node:pos(.)"!],
      [!ELSE!]
        NULL_PTR,
      [!ENDIF!]
      /* Number of ranges of memory addresses available for writing */
      [!"num:i(num:i(count(./DcmDspWriteMemoryRangeInfo/eb-list::*)) + num:i(count(./DcmDspWriteMemoryRangeByLabelInfo/eb-list::*)))"!]U,
      /* Number of range of memory addresses available for reading */
      [!"num:i(num:i(count(./DcmDspReadMemoryRangeInfo/eb-list::*)) + num:i(count(./DcmDspReadMemoryRangeByLabelInfo/eb-list::*)))"!]U,
      [!/*---MemoryIdValue------*/!][!//
      /* MemoryID Value */
      [!IF "node:existsAndTrue(../../DcmDspUseMemoryId)"!]
        /* !LINKSTO Dcm.EB.Config.DcmDspUseMemoryId.Enabled,1 */
        [!"DcmDspMemoryIdValue"!]U
      [!ELSE!]
        /* !LINKSTO Dcm.EB.Config.DcmDspUseMemoryId.Disabled,1 */
        0U
      [!ENDIF!]
    [!ENDINDENT!]
  },
  [!ENDLOOP!]
  [!ENDINDENT!]
};

[!ENDIF!]
[!//
[!VAR "DidDataPosition" = "0"!]
[!VAR "DidDataArray" = "''"!]
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspData/eb-list::*) and $DCM_DSP_USE_DIDSERVICES = 'STD_ON'"!]
  [!VAR "DidDataArray"!]
  [!/*---- Loop through all DID Data ----*/!][!//
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspData/eb-list::*"!][!//
      [!CALL "HANDLE_DID_DATA", "GenerateFunctions" = "'TRUE'", "DidDataPosition" = "$DidDataPosition""!]
    [!ENDLOOP!]
  [!ENDVAR!]
[!ENDIF!]
[!//
#if ((DCM_DID_DATA_TABLE_SIZE > 0U) && (DCM_DID_SIGNALS_COUNT > 0))
/* !LINKSTO Dcm.Dsn.DidSignals.ConfigurationData.DidDataTable,1 */
CONST(Dcm_VariableFunctionPointerRecordType, DCM_CONST) Dcm_DidDataTable[DCM_DID_DATA_TABLE_SIZE] =
{
  [!WS "2"!]/* Deviation MISRAC2012-1 <START> */ /* Deviation MISRA-3  <START> */
  [!WS "2"!][!"$DidDataArray"!]
  [!WS "2"!]/* Deviation MISRA-3  <STOP> */ /* Deviation MISRAC2012-1 <STOP> */
};
#endif

[!VAR "DidDataArrayIndex" = "''"!]
[!/* Iterate over all DcmDspData */!][!//
[!IF "$DCM_DID_SIGNALS_COUNT > 0 and $DCM_DSP_USE_DIDSERVICES = 'STD_ON'"!]
  [!VAR "DidDataArrayIndex"!]
  [!/*---- Loop through all DID Data ----*/!][!//
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspData/eb-list::*"!][!//
      [!CALL "HANDLE_DID_DATA", "GenerateFunctions" = "'FALSE'", "DidDataPosition" = "$DidDataPosition""!]
  [!ENDLOOP!][!//
  [!ENDVAR!]
[!ENDIF!]
[!//
[!IF "string-length($DidDataArrayIndex) != 0"!]
/* !LINKSTO Dcm.Dsn.DidSignals.ConfigurationData.DidDataIndexingArray,1 */
CONST(Dcm_DidDataIndexingArrayEntryType, DCM_CONST) Dcm_DidDataIndexingArray[DCM_NUM_DID_DATA] =
{
  [!WS "2"!][!"$DidDataArrayIndex"!][!//
};
[!ENDIF!]

[!IF "$DCM_DID_SIGNALS_COUNT > 0 and $DCM_DSP_USE_DIDSERVICES = 'STD_ON'"!]

/* !LINKSTO Dcm.Dsn.DidSignals.ConfigurationData.DidScalingDataSignalsIndexingArray,1 */
#if (DCM_DSP_USE_SERVICE_0X24 == STD_ON)
#if (DCM_NUM_READSCALING_DID_DATA > 0)
CONST(Dcm_DidScalingDataSignalsIndexingArrayEntryType, DCM_CONST) Dcm_DidScalingDataSignalsIndexingArray[DCM_NUM_READSCALING_DID_DATA] =
{
[!VAR "DidSignalPosition" = "0"!]
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspData/eb-list::*"!]
[!//
  [!IF "(node:exists(node:ref(DcmDspDataInfoRef)/DcmDspDataScalingInfoSize))"!]
[!//
    [!WS "2"!]{
    [!WS "4"!]/* Did Data signal position index in DcmDspData table  */
    [!WS "4"!][!"num:i($DidSignalPosition)"!]U,
    [!WS "4"!]/* Scaling info size */
    [!WS "4"!][!"(node:ref(DcmDspDataInfoRef)/DcmDspDataScalingInfoSize)"!]U,
[!//
    [!WS "2"!]},
  [!ENDIF!]
[!//
  [!VAR "DidSignalPosition" = "$DidSignalPosition + 1"!][!//
[!ENDLOOP!][!//
};
#endif /* #if (DCM_NUM_READSCALING_DID_DATA > 0) */
#endif /* #if (DCM_DSP_USE_SERVICE_0X24 == STD_ON) */
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_16
#include <Dcm_MemMap.h>
/* !LINKSTO Dcm.Dsn.DidSignals.ConfigurationData.DidDataSizeArray,1 */
CONST(uint16, DCM_CONST) Dcm_DidDataSizeArray[DCM_NUM_DID_DATA] =
{
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspData/eb-list::*"!]
    [!WS "2"!][!"DcmDspDataSize"!],
  [!ENDLOOP!]
};

#define DCM_STOP_SEC_CONST_16
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!ENDIF!][!//
[!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslServiceRequestManufacturerNotification/eb-list::*) and (node:existsAndTrue(DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmRteUsage))"!]
  /** \brief RTE function pointer table for Manufacturer Notification */
  CONST(Dcm_RteRequestNotificationType, DCM_CONST)
  [!WS "2"!]Dcm_RteManufacturerNotificationTable[DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE] =
  {
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslServiceRequestManufacturerNotification/eb-list::*"!]
      [!WS "2"!]{
        [!WS "4"!][!"concat('&Rte_Call_ServiceRequestManufacturerNotification_', as:name(.), '_Indication')"!],
        [!WS "4"!][!"concat('&Rte_Call_ServiceRequestManufacturerNotification_', as:name(.), '_Confirmation')"!]
      [!WS "2"!]},
    [!ENDLOOP!]
  };

[!ENDIF!]
[!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslServiceRequestSupplierNotification/eb-list::*) and (node:existsAndTrue(DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmRteUsage))"!]
  /** \brief RTE function pointer table for Supplier Notification */
  CONST(Dcm_RteRequestNotificationType, DCM_CONST)
  [!WS "2"!]Dcm_RteSupplierNotificationTable[DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE] =
  {
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsl/DcmDslServiceRequestSupplierNotification/eb-list::*"!]
      {[!WS "2"!]
        [!WS "4"!][!"concat('&Rte_Call_ServiceRequestSupplierNotification_', as:name(.), '_Indication')"!],
        [!WS "4"!][!"concat('&Rte_Call_ServiceRequestSupplierNotification_', as:name(.), '_Confirmation')"!]
      [!WS "2"!]},
    [!ENDLOOP!]
  };

[!ENDIF!]
[!//
[!/*------------------------------------------------------------------*/!][!//
[!/*------------------- ROE 4.2 START --------------------------------*/!][!//
[!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoe)"!]
CONST(Dcm_RoeEventPreconfListType, DCM_CONST) Dcm_RoeEventPreconfList[DCM_ROE_NUM_PRECONF_EVENT] =
{
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoe/DcmDspRoeEvent/eb-list::*, 'DcmDspRoeEventId'))"!]
[!INDENT "2"!]
  {
    [!INDENT "4"!]
    /* DidRef */
    [!IF "DcmDspRoeEventProperties = 'DcmDspRoeOnChangeOfDataIdentifier'"!]
    [!"num:inttohex(node:ref(DcmDspRoeEventProperties/eb-choice::*[1]/DcmDspRoeDidRef)/DcmDspDidIdentifier)"!],
    [!ELSE!]
    0,
    [!ENDIF!]
    [!"DcmDspRoeInitialEventStatus"!], /* InitialEventStatus */
    [!IF "DcmDspRoeEventProperties = 'DcmDspRoeOnChangeOfDataIdentifier'"!]
    DCM_ROE_EVENT_DID, /* EventType */
    0, /* DTCStatusMask */
    [!ELSE!]
    DCM_ROE_EVENT_DTC, /* EventType */
    [!"num:inttohex(DcmDspRoeEventProperties/eb-choice::*[1]/DcmDspRoeEventPreconfiguredDTCMask)"!] /* DTCStatusMask */
    [!ENDIF!]
    [!ENDINDENT!]
  }, /* index: [!"node:pos(.)"!] */
[!ENDINDENT!]
[!ENDLOOP!]
};

CONST(Dcm_RoeEventWindowTimePreconfType, DCM_CONST)
  [!WS "2"!]Dcm_RoeEventWindowTimePreconfList[DCM_ROE_NUM_PRECONF_EVENT_WINDOW_TIMES] =
{
[!LOOP "./DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoe/DcmDspRoeEventWindowTime/eb-list::*"!]
[!INDENT "2"!]
  {
    [!INDENT "4"!]
    [!"DcmDspRoeEventWindowTime"!], /* EventWindowTime */
    [!"text:toupper(DcmDspRoeStorageState)"!] /* StorageState */
    [!ENDINDENT!]
  }, /* index: [!"node:pos(.)"!] */
[!ENDINDENT!]
[!ENDLOOP!]
};

[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
CONST(Dcm_RoeSchMSwitchFunctionType, DCM_CONST)  Dcm_RoeSchMSwitchFunctionList[] =
{
[!INDENT "2"!]
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoe/DcmDspRoeEvent/eb-list::*, 'DcmDspRoeEventId'))"!]
  &SchM_Switch_Dcm_DcmResponseOnEvent_[!"DcmDspRoeEventId"!],
[!ENDLOOP!]
[!ENDINDENT!]
};

[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
[!ENDIF!]
[!//
[!/*------------------- ROE 4.2 END ----------------------------------*/!][!//
[!/*------------------------------------------------------------------*/!][!//
[!//
[!/* !LINKSTO Dcm.dsn.Dsp.PidData.config.0001,2 */!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*/DcmDspPidData/eb-list::*)"!]
CONST(Dcm_DspPidDataConfigType,DCM_CONST) Dcm_DspPidDataConfig[DCM_DSP_PID_DATA_NUM] =
{
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::* , 'DcmDspPidIdentifier'))"!]
    [!VAR "DcmDspPidService" = "DcmDspPidService"!]
    [!LOOP "util:distinct(node:order(DcmDspPidData/eb-list::*, 'DcmDspPidDataPos'))"!]
      [!WS "2"!]/* PID [!"as:name(../..)"!] - PidData [!"as:name(.)"!] */
      [!WS "2"!]{
      [!INDENT "4"!]
        [!/* !LINKSTO Dcm.dsn.Dsp.PidData.config.004,2 */!][!//
        [!IF "$DcmDspPidService = 'DCM_SERVICE_02'"!]
          NULL_PTR, /* Service 01 not supported */
        [!ELSE!]
          [!IF "node:exists(DcmDspPidService01)"!]
            [!IF "DcmDspPidService01/DcmDspPidDataUsePort='USE_DATA_SYNCH_FNC'"!]
              [!IF "node:exists(DcmDspPidService01/DcmDspPidDataReadFnc) and DcmDspPidService01/DcmDspPidDataReadFnc!=''"!]
                &[!"DcmDspPidService01/DcmDspPidDataReadFnc"!], /*ReadData Fnc Pointer*/
              [!ENDIF!]
            [!ELSEIF "DcmDspPidService01/DcmDspPidDataUsePort='USE_DATA_SYNCH_CLIENT_SERVER'"!]
              &Rte_Call_DataServices_[!"as:name(.)"!]_ReadData, /* Rte ReadData operation pointer */
            [!ELSEIF "DcmDspPidService01/DcmDspPidDataUsePort='USE_DATA_SENDER_RECEIVER'"!]
              &Rte_Read_DataServices_[!"as:name(.)"!]_data, /* Rte Read function pointer */
            [!ELSE!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDIF!]
        [!/* !LINKSTO Dcm.dsn.Dsp.PidData.config.0002,2 */!][!//
        [!"num:i(DcmDspPidDataPos)"!]U, /*DataPos*/
        [!/* !LINKSTO Dcm.dsn.Dsp.PidData.config.003,2 */!][!//
        [!"num:i(DcmDspPidDataSize)"!]U, /*DataSize*/
      [!ENDINDENT!]
      [!WS "2"!]},
    [!ENDLOOP!]
  [!ENDLOOP!]
};

[!ENDIF!]
[!//

[!/* !LINKSTO Dcm.dsn.Dsp.PidSupInfo.config.0001,1 */!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*/DcmDspPidSupportInfo/eb-list::*)"!][!//
  CONST(Dcm_DspPidSupInfoConfigType,DCM_CONST)
  [!WS "2"!]Dcm_DspPidSupInfoConfig[DCM_DSP_PID_SUPINFO_CONFIG_NUM] =
  {
    [!VAR "SupInfoDataStartIndex" = "0"!]
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*"!]
      [!LOOP "util:distinct(node:order(DcmDspPidSupportInfo/eb-list::* , 'DcmDspPidSupportInfoPos'))"!]
        [!WS "2"!]/* PID [!"as:name(../..)"!] - SupInfoConfig [!"as:name(.)"!] */
        [!WS "2"!]{
          [!INDENT "4"!]
            [!"num:i($SupInfoDataStartIndex)"!]U, /*index of first SupInfoData*/
            [!"num:i(DcmDspPidSupportInfoLen)"!]U, /*PidSupportInfoLen*/
            [!"num:i(DcmDspPidSupportInfoPos)"!]U, /*PidSupportInfoPos*/
          [!ENDINDENT!]
        },
        [!VAR "SupInfoDataStartIndex" = "$SupInfoDataStartIndex + DcmDspPidSupportInfoLen"!]
      [!ENDLOOP!]
    [!ENDLOOP!]
  };

[!ENDIF!][!//
[!//
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!/* !LINKSTO Dcm.dsn.Dsp.PidSupInfoData.config.0001,1 */!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*/DcmDspPidSupportInfo/eb-list::*)"!][!//

#define DCM_START_SEC_CONST_8
#include <Dcm_MemMap.h>

[!VAR "SetMask" = "0"!][!//
[!VAR "ByteIndex" = "0"!][!//
  CONST(uint8,DCM_CONST) Dcm_DspPidSupInfoData[DCM_DSP_PID_SUPINFO_DATA_NUM] =
  {
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*"!]
      [!LOOP "util:distinct(node:order(DcmDspPidSupportInfo/eb-list::* , 'DcmDspPidSupportInfoPos'))"!]
      [!WS "2"!]/* PID [!"as:name(../..)"!] - SupInfoData [!"as:name(.)"!] */
      [!VAR "SupInfoName"="as:name(.)"!]
      [!VAR "ByteIndex" = "0"!]
        [!FOR "i" = "1" TO "num:i(DcmDspPidSupportInfoLen)"!]
          [!VAR "ByteVal" = "0"!]
          [!VAR "SetMask" = "0"!]
          [!VAR "BitIndex" = "0"!]
          [!LOOP "../../DcmDspPidData/eb-list::*"!]
            [!IF "node:exists(DcmDspPidDataSupportInfo)"!]
             [!/* !LINKSTO Dcm622,2 */!][!//
            [!IF "(as:name(node:ref(DcmDspPidDataSupportInfo/DcmDspPidDataSupportInfoRef)) = $SupInfoName) and (num:i((DcmDspPidDataSupportInfo/DcmDspPidDataSupportInfoBit div 8)) = $ByteIndex)"!]
              [!VAR "BitIndex" = "DcmDspPidDataSupportInfo/DcmDspPidDataSupportInfoBit mod 8"!]
              [!VAR "SetMask" = "bit:shl(1,$BitIndex)"!]
              [!VAR "ByteVal" = "bit:or($ByteVal,$SetMask)"!]
            [!ENDIF!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!WS "2"!][!"num:i($ByteVal)"!]U,
          [!VAR "ByteIndex" = "$ByteIndex + 1"!]
        [!ENDFOR!]
      [!ENDLOOP!]
    [!ENDLOOP!]
  };
#define DCM_STOP_SEC_CONST_8
#include <Dcm_MemMap.h>
[!ENDIF!]
[!//
[!/*------------ generate structure of OBDMIDs from configuration ----------------*/!][!//
[!IF "($DCM_DSP_USE_MIDSERVICES = 'STD_ON') and (node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*))"!][!//

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>
  [!INDENT "0"!]
    CONST(Dcm_DspOBDMIDConfigType, DCM_CONST) Dcm_DspOBDMIDConfig[DCM_NUM_OBDMID_CFG] =
    {
    [!VAR "indexTIDsOfOBDMID" = "0"!]
    [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*"!]
      [!IF "node:value(./eb-list::*) != 0"!]
        [!WS "2"!]{Dcm_DspTestResultTidUsed_[!"num:inttohex(node:value(./eb-list::*), 2)"!], [!//
        [!"num:i($indexTIDsOfOBDMID)"!]U, [!//
        [!"num:inttohex(node:value(./eb-list::*), 2)"!]U, [!//
        [!"num:i(count(./DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*))"!]U},[!//
        [!VAR "indexTIDsOfOBDMID" = "$indexTIDsOfOBDMID + num:i(count(./DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*))"!]
      [!ENDIF!][!CR!]
    [!ENDLOOP!]
    [!//
    };

    CONST(Dcm_DspOBDMIDTidConfigType, DCM_CONST) Dcm_DspOBDMIDTidConfig[DCM_NUM_OBDMIDTID_CFG] =
    {
    [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*/DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*"!]
      [!WS "2"!]{[!"num:inttohex(node:value(./../../DcmDspTestResultObdmidTidUaSid), 2)"!]U, [!//
      [!"num:inttohex(as:ref(./eb-list::*)/DcmDspTestResultTestId, 2)"!]U, [!//
      [!IF "node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmRteUsage)"!][!//
        Rte_Call_DTRServices_[!"as:name(./../../../..)"!]_[!"as:name(as:ref(./eb-list::*))"!]_GetDTRValue[!//
        [!ELSE!][!//
        NULL_PTR[!//
        [!ENDIF!][!//
    },
    [!ENDLOOP!]
    };
  [!ENDINDENT!]

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>
[!ENDIF!]
[!//

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!IF "(node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId = num:i(8)])) or ((node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId = num:i(49)])) and ((node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspEnableObdMirror))))"!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRequestControl/eb-list::*)"!]
/* Initialize global array holding the configuration for OBD Service $08,
 * that are also are used by UDS service 0x31 in case OBD mirroring is enable. */
CONST(Dcm_DspRequestControlType, DCM_CONST) Dcm_DspRequestControlConfig[DCM_DSP_NUM_REQUESTCONTROL_CFG] =
{
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRequestControl/eb-list::*"!]
  [!WS "2"!]{
    [!INDENT "4"!]
      [!IF "DcmDspRequestControlUsePort = 'USE_REQUESTCONTROL_SYNCH_FNC'"!][!//
        [!IF "node:exists(DcmDspRequestControlFnc)"!][!//
          &[!"DcmDspRequestControlFnc"!],
        [!ELSE!][!//
          NULL_PTR,
        [!ENDIF!][!//
      [!ELSEIF "DcmDspRequestControlUsePort = 'USE_REQUESTCONTROL_SYNCH_CLIENT_SERVER'"!][!//
          &Rte_Call_RequestControlServices_[!"node:name(.)"!]_RequestControl,
      [!ELSE!][!//
          NULL_PTR,
      [!ENDIF!]
      [!"num:i(DcmDspRequestControlInBufferSize)"!]U,
      [!"num:i(DcmDspRequestControlOutBufferSize)"!]U,
      [!"num:i(DcmDspRequestControlTestId)"!]U
    [!ENDINDENT!]
  [!WS "2"!]},
  [!ENDLOOP!]
};

[!ENDIF!]
[!ENDIF!]
[!//

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>


[!/*------------------------------------ Calibration ------------------------------------*/!][!//
#define DCM_START_SEC_CALIB_8
#include <Dcm_MemMap.h>

#if (DCM_DSP_SUBSERVICE_USED_BUF_SIZE > 0)
/* Initialize global array holding the configuration for the subservice usage */
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*)"!]

[!VAR "MaxValue" = "0"!][!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
  [!IF "DcmDsdSidTabServiceId = 62"!]
    [!VAR "Count" = "num:integer(count(DcmDsdSubService/eb-list::*)) + 1"!]
  [!ELSE!]
    [!VAR "Count" = "num:integer(count(DcmDsdSubService/eb-list::*))"!]
  [!ENDIF!]
  [!IF "$Count > $MaxValue"!][!//
    [!VAR "MaxValue" = "$Count"!]
  [!ENDIF!]
[!ENDLOOP!]
[!//
/* Deviation MISRAC2012-5 */
CONST(uint8, DCM_CONST_CALIBRATION) Dcm_DsdSubServiceUsed[DCM_DSP_NUMBER_OF_SRV_TABLES_USED][DCM_DSP_NUMBER_OF_SERVICE_USED][DCM_DSP_SUBSERVICE_USED_BUF_SIZE] =
{
  [!INDENT "2"!]
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
  {
    [!INDENT "4"!]
    [!VAR "ServiceIndex" = "0"!]
    [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
      [!IF "DcmDsdSidTabServiceId = 62"!]
        [!VAR "BitIndex" = "1"!]
      [!ELSE!]
        [!VAR "BitIndex" = "0"!]
      [!ENDIF!]
      [!VAR "idx" = "0"!][!//
      [!VAR "ByteVal" = "0"!][!//
      [!VAR "ByteFilled" = "0"!][!//
      [!VAR "ByteIndex" = "0"!][!//
      [!VAR "PidRemaining" = "num:integer(count(DcmDsdSubService/eb-list::*))"!][!//
      /* [!"node:name(.)"!] subservice used */
      {
        [!INDENT "6"!]
        [!LOOP "util:distinct(node:order(DcmDsdSubService/eb-list::*, 'DcmDsdSubServiceId'))"!][!//
          [!IF "$PidRemaining > 0"!]
            [!VAR "PidRemaining" = "$PidRemaining - 1"!]
          [!ENDIF!]
          [!IF "node:existsAndTrue(DcmDsdSubServiceUsed)"!]
            [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
          [!ENDIF!]
          [!VAR "BitIndex" = "$BitIndex + 1"!]
          [!IF "($BitIndex mod 8) = 0"!]
            [!VAR "ByteFilled" = "1"!]
            [!VAR "BitIndex" = "0"!]
          [!ENDIF!]
          [!IF "($ByteFilled = 1) or ($PidRemaining = 0)"!]
            [!"num:i($ByteVal)"!]U,
            [!VAR "ByteFilled" = "0"!]
            [!VAR "ByteVal" = "0"!]
            [!VAR "ByteIndex" = "$ByteIndex + 1"!]
          [!ENDIF!]
        [!ENDLOOP!]
        [!FOR "idx" = "num:i($ByteIndex + 1)" TO "num:integer(($MaxValue + 7) div 8)"!][!//
          0U,
        [!ENDFOR!]
        [!ENDINDENT!]
      },
      [!VAR "ServiceIndex" = "$ServiceIndex + 1"!]
    [!ENDLOOP!]
    [!IF "num:i($ServiceIndex) < $DCM_DSP_NUMBER_OF_SERVICE_USED"!]
      [!FOR "FillArrayIdx" = "$ServiceIndex + 1" TO "$DCM_DSP_NUMBER_OF_SERVICE_USED"!]
        /* Initialize with '0' the unused values */
        {
          [!FOR "Idx" = "1" TO "num:integer(($MaxValue + 7) div 8)"!]
            [!WS "2"!]0U,
          [!ENDFOR!]
        },
      [!ENDFOR!]
    [!ENDIF!]
    [!ENDINDENT!]
  },
  [!ENDLOOP!]
  [!ENDINDENT!]
};
[!ENDIF!][!//
#endif

/* Initialize global array holding the configuration for the service usage */
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*)"!]

[!VAR "MaxValue" = "0"!][!//
[!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
  [!VAR "Count" = "num:integer(count(DcmDsdService/eb-list::*))"!][!//
  [!IF "$Count > $MaxValue"!][!//
    [!VAR "MaxValue" = "$Count"!]
  [!ENDIF!]
[!ENDLOOP!]
[!//
/* Deviation MISRAC2012-5 */
CONST(uint8, DCM_CONST_CALIBRATION) Dcm_DsdServiceUsed[DCM_DSP_NUMBER_OF_SRV_TABLES_USED][DCM_DSP_SERVICE_USED_BUF_SIZE] =
{
  [!INDENT "2"!]
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*, 'DcmDsdSidTabId'))"!][!//
    [!VAR "BitIndex" = "0"!][!//
    [!VAR "idx" = "0"!][!//
    [!VAR "ByteVal" = "0"!][!//
    [!VAR "ByteFilled" = "0"!][!//
    [!VAR "ByteIndex" = "0"!][!//
    [!VAR "PidRemaining" = "num:integer(count(DcmDsdService/eb-list::*))"!][!//
    {
      [!INDENT "4"!]
      [!LOOP "util:distinct(node:order(DcmDsdService/eb-list::*, 'DcmDsdSidTabServiceId'))"!][!//
        [!IF "$PidRemaining > 0"!]
          [!VAR "PidRemaining" = "$PidRemaining - 1"!]
        [!ENDIF!]
        [!IF "node:existsAndTrue(DcmDsdServiceUsed)"!]
          [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
        [!ENDIF!]
        [!VAR "BitIndex" = "$BitIndex + 1"!]
        [!IF "($BitIndex mod 8) = 0"!]
          [!VAR "ByteFilled" = "1"!]
          [!VAR "BitIndex" = "0"!]
        [!ENDIF!]
        [!IF "($ByteFilled = 1) or ($PidRemaining = 0)"!]
          [!"num:i($ByteVal)"!]U,
          [!VAR "ByteFilled" = "0"!]
          [!VAR "ByteVal" = "0"!]
          [!VAR "ByteIndex" = "$ByteIndex + 1"!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!FOR "idx" = "num:i($ByteIndex + 1)" TO "num:integer(($MaxValue + 7) div 8)"!][!//
        0U,
      [!ENDFOR!]
      [!ENDINDENT!]
    },
  [!ENDLOOP!]
  [!ENDINDENT!]
};
[!ENDIF!][!//

#if (DCM_DSP_USE_DIDSERVICES == STD_ON)
#if (DCM_DSP_DIDSERVICES_NUM_DIDS > 0)
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*)"!]
[!VAR "BitIndex" = "0"!][!//
[!VAR "ByteVal" = "0"!][!//
[!VAR "ByteFilled" = "0"!][!//
[!VAR "DidRemaining" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[node:existsAndTrue(./DcmDspDidUsed)]))"!][!//
  /* Deviation MISRAC2012-5 */
  CONST(Dcm_DspDidUsedType,DCM_CONST_CALIBRATION) Dcm_DspDidUsed[DCM_DSP_DID_USED_BUF_SIZE] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[node:existsAndTrue(./DcmDspDidUsed)], 'DcmDspDidIdentifier'))"!]
      [!IF "$DidRemaining > 0"!]
        [!VAR "DidRemaining" = "$DidRemaining - 1"!]
      [!ENDIF!]
      [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
      [!VAR "BitIndex" = "$BitIndex + 1"!]
      [!IF "($BitIndex mod 8) = 0"!]
        [!VAR "ByteFilled" = "1"!]
        [!VAR "BitIndex" = "0"!]
      [!ENDIF!]
      [!IF "($ByteFilled = 1) or ($DidRemaining = 0)"!]
        [!WS "2"!][!"num:i($ByteVal)"!]U,
        [!VAR "ByteFilled" = "0"!]
        [!VAR "ByteVal" = "0"!]
      [!ENDIF!]
    [!ENDLOOP!]
  };
[!ENDIF!][!//
#endif /* #if (DCM_DSP_DIDSERVICES_NUM_DIDS > 0) */
#endif /* #if (DCM_DSP_USE_DIDSERVICES == STD_ON) */

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*)"!]
[!VAR "BitIndex" = "0"!][!//
[!VAR "ByteVal" = "0"!][!//
[!VAR "ByteFilled" = "0"!][!//
[!VAR "PidRemaining" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*))"!][!//
[!/* !LINKSTO Dcm.dsn.Dsp.DspPidUsed.config.0001,1 */!][!//
  /* Deviation MISRAC2012-5 */
  CONST(uint8,DCM_CONST_CALIBRATION) Dcm_DspPidUsed[DCM_DSP_PID_USED_BUF_SIZE] =
  {
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::* , 'DcmDspPidIdentifier'))"!]
      [!IF "$PidRemaining > 0"!]
        [!VAR "PidRemaining" = "$PidRemaining - 1"!]
      [!ENDIF!]
      [!IF "node:existsAndTrue(DcmDspPidUsed)"!]
        [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
      [!ENDIF!]
      [!VAR "BitIndex" = "$BitIndex + 1"!]
      [!IF "($BitIndex mod 8) = 0"!]
        [!VAR "ByteFilled" = "1"!]
        [!VAR "BitIndex" = "0"!]
      [!ENDIF!]
      [!IF "($ByteFilled = 1) or ($PidRemaining = 0)"!]
        [!WS "2"!][!"num:i($ByteVal)"!]U,
        [!VAR "ByteFilled" = "0"!]
        [!VAR "ByteVal" = "0"!]
      [!ENDIF!]
    [!ENDLOOP!]
  };
[!ENDIF!][!//
[!//

[!/*------------ generate structure of OBDMIDs from configuration ----------------*/!][!//
[!IF "($DCM_DSP_USE_MIDSERVICES = 'STD_ON') and (node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*))"!][!//
  [!INDENT "0"!][!//
    /* !LINKSTO Dcm.ReadDataById.ReadOBDMIDs.ConfigurationSpecification.DcmDspTestResultObdmidTidRef,1 */
    [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*"!]
    /* Deviation MISRAC2012-5 */
    CONST(Dcm_DspUsedType, DCM_CONST_CALIBRATION) Dcm_DspTestResultTidUsed_[!"num:inttohex(node:value(./eb-list::*), 2)"!][!//
    [[!"num:i((count(./DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*/DcmDspTestResultObdmidTidRef)+7)div 8)"!]U] =
    {
      [!VAR "indexTIDRef" = "0"!][!//
      [!LOOP "./DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*"!][!//
        [!IF "($indexTIDRef mod 8) = 0"!][!//
          [!WS "2"!][!//
          [!VAR "enabledTIDRef" = "0"!][!//
        [!ENDIF!][!//
        [!VAR "enabledTIDRef" = "bit:shr($enabledTIDRef, 1)"!]
        [!IF "node:existsAndTrue(./DcmDspTestResultTidUsed)"!][!//
          [!VAR "enabledTIDRef" = "bit:or($enabledTIDRef, 128)"!][!//
        [!ENDIF!]
        [!VAR "indexTIDRef" = "$indexTIDRef + 1"!]
        [!IF "($indexTIDRef mod 8) = 0"!][!//
          [!"num:inttohex($enabledTIDRef, 2)"!]U,[!CR!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
      [!IF "(count(./DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*)mod 8) >0"!][!//
        [!VAR "indexTIDRef" = "8-(count(./DcmDspTestResultObdmidTids/eb-list::*/DcmDspTestResultObdmidTidRefs/eb-list::*)mod 8)"!]
        [!VAR "enabledTIDRef" = "bit:shr($enabledTIDRef, $indexTIDRef)"!]
        [!"num:inttohex($enabledTIDRef, 2)"!]U
      [!ENDIF!][!//
    [!//
    };[!CR!]
    [!ENDLOOP!]
  [!ENDINDENT!]
[!ENDIF!]
[!//

[!/*------------ generate structure of OBDMIDs from configuration ----------------*/!][!//
[!IF "($DCM_DSP_USE_MIDSERVICES = 'STD_ON') and (node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*))"!][!//
  [!INDENT "0"!][!//
    /* !LINKSTO Dcm.EB.Config.DcmDspTestResultObdmidUsed,1 */
    /* Deviation MISRAC2012-5 */
    CONST(Dcm_DspUsedType, DCM_CONST_CALIBRATION) Dcm_DspOBDMIDUsed[DCM_NUM_OBDMIDUSED_CFG] =
{
    [!VAR "indexOBDMID" = "0"!]
    [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*"!][!//
      [!IF "($indexOBDMID mod 8) = 0"!][!//
        [!WS "2"!][!//
        [!VAR "enabledOBDMID" = "0"!][!//
      [!ENDIF!][!//
      [!VAR "enabledOBDMID" = "bit:shr($enabledOBDMID, 1)"!]
      [!IF "node:existsAndTrue(./DcmDspTestResultObdmidUsed)"!][!//
        [!VAR "enabledOBDMID" = "bit:or($enabledOBDMID, 128)"!][!//
      [!ENDIF!]
      [!VAR "indexOBDMID" = "$indexOBDMID + 1"!]
      [!IF "($indexOBDMID mod 8) = 0"!][!//
        [!"num:inttohex($enabledOBDMID, 2)"!]U,[!CR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "(count(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*)mod 8) >0"!][!//
      [!VAR "indexOBDMID" = "8-(count(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspTestResultByObdmid/DcmDspTestResultObdmidTid/eb-list::*)mod 8)"!]
      [!VAR "enabledOBDMID" = "bit:shr($enabledOBDMID, $indexOBDMID)"!]
      [!"num:inttohex($enabledOBDMID, 2)"!]U
    [!ENDIF!][!//
    };
  [!ENDINDENT!]
[!ENDIF!]
[!//

[!IF "(node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId = num:i(8)])) or ((node:exists(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId = num:i(49)])) and ((node:existsAndTrue(as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspEnableObdMirror))))"!][!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRequestControl/eb-list::*)"!]
/* Initialize global array holding the information on the used entries in the Dcm_DspRequestControlConfig array */
/* Deviation MISRAC2012-5 */
CONST(Dcm_DspRequestControlUsedType, DCM_CONST_CALIBRATION) Dcm_DspRequestControlUsedConfig[DCM_DSP_NUM_REQUESTCONTROL_CFG] =
{
  [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRequestControl/eb-list::*"!]
    [!INDENT "2"!]
      [!"text:toupper(DcmDspRequestControlUsed)"!],
    [!ENDINDENT!]
  [!ENDLOOP!]
};

[!ENDIF!]
[!ENDIF!]
[!//
#define DCM_STOP_SEC_CALIB_8
#include <Dcm_MemMap.h>

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::*)"!]
#define DCM_START_SEC_CALIB_UNSPECIFIED
#include <Dcm_MemMap.h>

  /* Deviation MISRAC2012-5 */
  CONST(Dcm_DspPidConfigType,DCM_CONST_CALIBRATION) Dcm_DspPidConfig[DCM_NUM_PID_CFG] =
  {
    [!INDENT "2"!]
    [!VAR "DataStartIndex" = "0"!]
    [!VAR "SupInfoStartIndex" = "0"!]
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspPid/eb-list::* , 'DcmDspPidIdentifier'))"!]
    {
      [!INDENT "4"!]
        [!"num:i($DataStartIndex)"!]U, /*index of first PidDataConfig*/
        [!VAR "DataCnt" = "num:integer(count(DcmDspPidData/eb-list::*))"!]
        [!"num:i($DataCnt)"!]U, /*count of PidDataConfig*/
        [!"num:i($SupInfoStartIndex)"!]U, /*index of first SupInfoConfig*/
        [!VAR "SupInfoCnt" = "num:integer(count(DcmDspPidSupportInfo/eb-list::*))"!]
        [!"num:i($SupInfoCnt)"!]U, /*count of SupInfoConfig*/
        [!"num:inttohex(num:i(DcmDspPidIdentifier), 2)"!]U, /*PidIdentifier*/
        [!"num:i(DcmDspPidSize)"!]U, /*DcmDspPidSize*/
        [!IF "DcmDspPidService = 'DCM_SERVICE_01'"!]
          1U, /*Service01 is enabled*/
        [!ELSEIF "DcmDspPidService = 'DCM_SERVICE_02'"!]
          2U, /*Service02 is enabled*/
        [!ELSEIF "DcmDspPidService = 'DCM_SERVICE_01_02'"!]
          3U, /*Services 01 and 02 are enabled*/
        [!ELSE!]
        [!ENDIF!]
      [!ENDINDENT!]
    },
    [!VAR "DataStartIndex" = "$DataStartIndex + $DataCnt"!]
    [!VAR "SupInfoStartIndex" = "$SupInfoStartIndex + $SupInfoCnt"!]
    [!ENDLOOP!]
    [!ENDINDENT!]
  };

#define DCM_STOP_SEC_CALIB_UNSPECIFIED
#include <Dcm_MemMap.h>
[!ENDIF!]
[!//
/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

[!IF "(node:existsAndFalse(DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmModeDeclarationSupport))"!]
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspSession/eb-list::*/DcmDspSessionRow/eb-list::*"!][!//
  [!VAR "StrName"="''"!]
  [!VAR "StrTemp"="substring-after(as:name(.),'DCM_')"!]
  [!IF "$StrTemp = ''"!][!VAR "StrTemp"="as:name(.)"!][!ENDIF!]
  [!LOOP "text:split($StrTemp, '_')"!]
    [!VAR "StrName"="concat($StrName, concat(substring(., 1,1), text:tolower(substring(., 2))))"!]
  [!ENDLOOP!]
[!//
  [!IF "not(contains($StrName,'AllSessionLevel'))"!]
    FUNC(Std_ReturnType, DCM_CODE) Dcm_[!"$StrName"!]ModeEntry(void)
    {
[!INDENT "2"!]
      Dcm_Dsp_DiagnosticSessionControl_ConfirmSession(DcmConf_[!"as:name(../../.)"!]_[!"as:name(.)"!]);
      return E_OK;
[!ENDINDENT!]
    }

  [!ENDIF!]
[!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!IF "((count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')])) = 1) and
       (node:exists(node:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')]/DcmDspDidInfoRef)/DcmDspDidAccess/DcmDspDidRead)) and
       (count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')]/DcmDspDidSignal/eb-list::*) = 1) and
       (node:existsAndTrue(node:ref(node:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')]/DcmDspDidSignal/eb-list::*[1]/DcmDspDidDataRef)/DcmDspDataInfoRef)/DcmDspDataFixedLength)) and
       (node:value(node:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')]/DcmDspDidSignal/eb-list::*[1]/DcmDspDidDataRef)/DcmDspDataUsePort) = 'USE_DATA_SYNCH_FNC') and
       (node:exists(node:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')]/DcmDspDidSignal/eb-list::*[1]/DcmDspDidDataRef)/DcmDspDataReadFnc)) and
       (node:value(node:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspDid/eb-list::*[DcmDspDidIdentifier = num:hextoint('0xf186')]/DcmDspDidSignal/eb-list::*[1]/DcmDspDidDataRef)/DcmDspDataReadFnc) = 'Dcm_Internalf186Readout')"!]
/*------------ Definition of user function for the service 0xF186 --------------*/
/* !LINKSTO Dcm.EB.ActiveDiagnosticSessionDataIdentifier,1 */
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Internalf186Readout(
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Data)
{
  Std_ReturnType retVal = E_NOT_OK;

  retVal = Dcm_GetSesCtrlTypeExt(Data);

  return retVal;
}

[!ENDIF!]
[!//
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*==================[internal function definitions]==============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

[!VAR "BswModeDecGpList" = "'#'"!]
[!VAR "SwcModeDecGpList" = "'#'"!]
[!LOOP "DcmConfigSet/eb-list::*/DcmProcessingConditions/DcmModeCondition/eb-list::*"!]
/** \brief Mode condition function for [!"as:name(.)"!] */
STATIC FUNC(boolean, DCM_CODE) Dcm_ModeCondition_[!"as:name(.)"!]_Result(void)
{
  [!INDENT "2"!]
    boolean result = FALSE;
    [!IF "DcmConditionType = 'DCM_EQUALS' "!]
      [!VAR "condition" = "'=='"!]
      [!VAR "check" = "'matches'"!]
    [!ELSE!]
      [!VAR "condition" = "'!='"!]
      [!VAR "check" = "'does not match'"!]
    [!ENDIF!]
    [!IF "node:exists(DcmBswModeRef)"!]
      [!VAR "ModeDecGp" = "text:split(./DcmBswModeRef, '/')[last()-1]"!]
      /* Bsw mode (provided by Dcm or any other mode manager) */
      uint16 mode = [!//
        RTE_MODE_[!"$ModeDecGp"!]_[!"text:split(./DcmBswModeRef, '/')[last()]"!];

      [!IF "not(contains($BswModeDecGpList, concat('#', $ModeDecGp, '#')))"!]
        /* check if mode returned by the Bsw module [!"$check"!] with that configured in DcmBswModeRef */
        if(SchM_Mode_Dcm_DcmModeRuleRequiredMode_[!"node:pos(.)"!]_[!"$ModeDecGp"!]() [!"$condition"!]
        [!VAR "BswModeDecGpList" = "concat($BswModeDecGpList, $ModeDecGp, '#')"!]
      [!ELSE!]
        [!/* loop to find the index of mode condition having the same Bsw mode declaration */!]
        [!LOOP "../eb-list::*"!]
          [!IF "string($ModeDecGp) = text:split(./DcmBswModeRef, '/')[last()-1]"!]
            [!VAR "idx" = "node:pos(.)"!]
            [!BREAK!]
          [!ENDIF!]
        [!ENDLOOP!]
        /* check if mode returned by the Bsw module [!"$check"!] with that configured in DcmBswModeRef */
        if(SchM_Mode_Dcm_DcmModeRuleRequiredMode_[!"num:i($idx)"!]_[!"$ModeDecGp"!]() [!"$condition"!]
      [!ENDIF!]
      [!WS "4"!]mode)
    [!ELSEIF "node:exists(DcmSwcModeRef)"!]
      [!VAR "SwcModeDecGp" = "text:split(./DcmSwcModeRef, '/')[last()-1]"!]
      /* Swc mode (provided by Swc which is the mode manager) */
      uint16 mode = [!//
        RTE_MODE_[!"$SwcModeDecGp"!]_[!"text:split(./DcmSwcModeRef, '/')[last()]"!];
      [!IF "not(contains($SwcModeDecGpList, concat('#', $SwcModeDecGp, '#')))"!]
        /* check if mode returned by the Swc [!"$check"!] with that configured in DcmSwcModeRef */
        if(Rte_Mode_Dcm_R_SwcMode_[!"node:pos(.)"!]_[!"$SwcModeDecGp"!]_DcmModeRuleRequiredModeGp_[!"$SwcModeDecGp"!]() [!"$condition"!]
        [!VAR "SwcModeDecGpList" = "concat($SwcModeDecGpList, $SwcModeDecGp, '#')"!]
      [!ELSE!]
        [!/* loop to find the index of mode condition having the same Swc mode declaration */!]
        [!LOOP "../eb-list::*"!]
          [!IF "string($SwcModeDecGp) = text:split(./DcmSwcModeRef, '/')[last()-1]"!]
            [!VAR "Swcidx" = "node:pos(.)"!]
            [!BREAK!]
          [!ENDIF!]
        [!ENDLOOP!]
        /* check if mode returned by the Swc [!"$check"!] with that configured in DcmSwcModeRef */
        if(Rte_Mode_Dcm_R_SwcMode_[!"num:i($Swcidx)"!]_[!"$SwcModeDecGp"!]_DcmModeRuleRequiredModeGp_[!"$SwcModeDecGp"!]() [!"$condition"!]
      [!ENDIF!]
      [!WS "4"!]mode)
    [!ENDIF!]
      {
      [!WS "2"!]result = TRUE;
      }

    return result;
  [!ENDINDENT!]
}

[!ENDLOOP!]
[!//
[!LOOP "DcmConfigSet/eb-list::*/DcmProcessingConditions/DcmModeRule/eb-list::*"!]
/** \brief Mode rule function for [!"as:name(.)"!] */
FUNC(boolean, DCM_CODE) Dcm_ModeRule_[!"as:name(.)"!]_Result(P2VAR(uint8, AUTOMATIC, DCM_VAR) Nrc)
{
  [!INDENT "2"!]
    [!VAR "EnableIfConditionEvaluation" = "'OFF'"!][!//
    [!VAR "DcmArgumentRefCount" = "0"!][!//
    [!LOOP "DcmArgumentRef/eb-list::*"!][!//
      [!VAR "DcmArgumentRefCount" = "$DcmArgumentRefCount + 1"!][!//
      [!IF "'DcmModeRule' = node:name(as:ref(.)/..)"!][!//
        [!VAR "EnableIfConditionEvaluation" = "'ON'"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$EnableIfConditionEvaluation = 'ON'"!][!//
      uint8 calcNrc = 0U;
    [!ENDIF!][!//
      boolean result = FALSE;
    [!IF "DcmLogicalOperator = 'DCM_AND'"!]
      [!VAR "operator" = "'&&'"!]
    [!ENDIF!]
    [!IF "DcmLogicalOperator = 'DCM_OR'"!]
      [!VAR "operator" = "'||'"!]
    [!ENDIF!]
    /* Get result of all referenced MRs/MCs */
    /* Deviation MISRAC2012-2 <START> */
    /* Deviation MISRA-1  <START> */
    result =
    [!LOOP "DcmArgumentRef/eb-list::*"!]
      [!IF "'DcmModeCondition' = node:name(as:ref(.)/..)"!]
        (Dcm_ModeCondition_[!"as:name(as:ref(.))"!]_Result()) [!//
        [!IF "$DcmArgumentRefCount != 1"!]
          [!"$operator"!]
        [!ENDIF!][!//
      [!ELSE!][!//
        (Dcm_ModeRule_[!"as:name(as:ref(.))"!]_Result(&calcNrc)) [!//
        [!IF "$DcmArgumentRefCount != 1"!]
          [!"$operator"!]
         [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "DcmArgumentRefCount" = "$DcmArgumentRefCount - 1"!][!//
    [!ENDLOOP!][!//
    ;
  /* Deviation MISRA-1  <STOP> */
  /* Deviation MISRAC2012-2 <STOP> */

  if (result == FALSE)
  {
  [!INDENT "4"!]
    [!IF "$EnableIfConditionEvaluation = 'ON'"!][!//
     /* result is a failure */
     if( calcNrc != 0U )
     {
       [!WS "2"!]/* referenced MR which failed has an NRC */
       [!WS "2"!]*Nrc = calcNrc;
     }
     else
    [!ENDIF!][!//
    {
    [!IF "node:exists(DcmModeRuleNrcValue)"!]
      [!WS "2"!]/* referenced MR which failed does NOT have an NRC or an MC failed so use
      [!WS "3"!]   configured NRC for the master MR */
      [!WS "2"!]*Nrc = [!"DcmModeRuleNrcValue"!]U;
    [!ELSE!]
      [!WS "2"!]/* referenced MR which failed does NOT have an NRC or an MC failed and also
       [!WS "3"!]  no configured NRC for the master MR so use DCM_E_CONDITIONSNOTCORRECT as the NRC */
      [!WS "2"!]*Nrc = 0x22U;
    [!ENDIF!]
    }
    [!ENDINDENT!]
  }
  else
  {
  [!WS "2"!]/* result is TRUE so no NRC to be sent */
  [!WS "2"!]*Nrc = 0U;
  }

  return result;
  [!ENDINDENT!]
}

[!ENDLOOP!]
[!//
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

[!ENDINDENT!]
[!//
/*==================[end of file]================================================================*/
