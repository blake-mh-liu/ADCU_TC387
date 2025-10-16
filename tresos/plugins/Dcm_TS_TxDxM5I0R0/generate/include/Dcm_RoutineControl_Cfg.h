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
[!AUTOSPACING!]

/* !LINKSTO Dcm.Dsn.File.RoutineControl.ConfigH,1 */

#ifndef DCM_ROUTINECONTROL_CFG_H
#define DCM_ROUTINECONTROL_CFG_H

/*==================[inclusions]=================================================================*/

#include <Dcm_Int.h>
[!INCLUDE "Dcm_common.m"!]

/*==================[macros]=====================================================================*/

[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]
#if (defined DCM_ROUTINE_DEFAULT_INTERFACES)
  #error "DCM_ROUTINE_DEFAULT_INTERFACES is already defined"
#endif
/** \brief Indicates the Generic End of Line handling for unsupported routines
 **  If is set as STD_ON, for every routine which is not supported (not configured or not used),
 **  Dcm shall call the Application Default Interfaces (Dcm_DefaultRoutineStart, Dcm_DefaultRoutineStop
 **  or Dcm_DefaultRoutineRequestRoutineResults).
 **  If is set as STD_OFF, for every routine which is not supported (not configured or not used),
 **  Dcm shall reject the request with DCM_E_REQUESTOUTOFRANGE Nrc*/
#define DCM_ROUTINE_DEFAULT_INTERFACES   [!//
[!IF "node:existsAndTrue(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineEnableDefaultInterfaces)"!]
  [!WS "3"!]STD_ON
  [!ELSE!]
  [!WS "3"!]STD_OFF
[!ENDIF!]
[!ENDIF!]

[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]
#if (defined DCM_NUM_ROUTINES) /* To prevent double declaration */
#error DCM_NUM_ROUTINES already defined
#endif /* if (defined DCM_NUM_ROUTINES) */
/** \brief Number of Routines configured */
#define DCM_NUM_ROUTINES [!WS "20"!][!"num:i($DCM_NUM_ROUTINES)"!]U

[!VAR "routineInfoCount" = "0"!][!//
[!VAR "routineInfoRefList"="'#'"!][!//
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*"!][!//
  [!IF "node:existsAndTrue(DcmDspRoutineUsed)"!]
  [!IF "not(contains($routineInfoRefList, concat('#', as:name(node:ref(DcmDspRoutineInfoRef)), '#')))"!]
    [!VAR "routineInfoCount" = "$routineInfoCount + 1"!][!//
    [!VAR "routineInfoRefList" = "concat($routineInfoRefList, as:name(node:ref(DcmDspRoutineInfoRef)), '#')"!]
  [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!][!//
[!//
#if (defined DCM_NUM_ROUTINE_INFO) /* To prevent double declaration */
#error DCM_NUM_ROUTINE_INFO already defined
#endif /* if (defined DCM_NUM_ROUTINE_INFO) */
/** \brief Number of DcmDspRoutineInfos referenced by DcmDspRoutines */
#define DCM_NUM_ROUTINE_INFO [!WS "16"!][!"num:integer( $routineInfoCount)"!]U

#if (defined DCM_ROUTINE_ENDIANNESS_CONVERSION) /* To prevent double declaration */
#error DCM_ROUTINE_ENDIANNESS_CONVERSION already defined
#endif /* if (defined DCM_ROUTINE_ENDIANNESS_CONVERSION) */
/** \brief Indicates if endianness conversion for routines is enabled */
#define DCM_ROUTINE_ENDIANNESS_CONVERSION [!//
[!IF "(node:existsAndTrue(DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmDslProtocolRoutineEndiannessConvEnabled))"!]
  [!WS "2"!]STD_ON
  [!ELSE!]
  [!WS "2"!]STD_OFF
[!ENDIF!]

#if (defined DCM_RTE_TABLE_ROUTINE_SERVICES_SIZE) /* To prevent double declaration */
#error DCM_RTE_TABLE_ROUTINE_SERVICES_SIZE already defined
#endif
/** \brief Routine Services count */
#define DCM_RTE_TABLE_ROUTINE_SERVICES_SIZE [!"num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*))"!]U

#if (defined DCM_ROUTINE_INACTIVE) /* To prevent double declaration */
#error DCM_ROUTINE_INACTIVE already defined
#endif/* #if (defined DCM_ROUTINE_INACTIVE) */
/** \brief Specifies the status of a routine  */
#define DCM_ROUTINE_INACTIVE                0x00U

#if (defined DCM_ROUTINE_STARTED) /* To prevent double declaration */
#error DCM_ROUTINE_STARTED already defined
#endif/* #if (defined DCM_ROUTINE_STARTED) */
/** \brief Specifies the status of a routine  */
#define DCM_ROUTINE_STARTED                 0x01U

#if (defined DCM_ROUTINE_STOPPED) /* To prevent double declaration */
#error DCM_ROUTINE_STOPPED already defined
#endif/* #if (defined DCM_ROUTINE_STOPPED) */
/** \brief Specifies the status of a routine  */
#define DCM_ROUTINE_STOPPED                 0x02U

#if (defined DCM_ROUTINECONTROL_USE_RTE) /* To prevent double declaration */
#error DCM_ROUTINECONTROL_USE_RTE already defined
#endif /* if (defined DCM_ROUTINECONTROL_USE_RTE) */
/** \brief Number of Routines that use Rte */
#define DCM_ROUTINECONTROL_USE_RTE [!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsePort)])"!]
  [!WS "9"!]STD_ON
  [!ELSE!]
  [!WS "9"!]STD_OFF
[!ENDIF!]

#if (defined DCM_ROUTINE_ROUTINEINFOBYTE) /* To prevent double declaration */
  #error "DCM_ROUTINE_ROUTINEINFOBYTE is already defined"
#endif /* #if (defined DCM_ROUTINE_ROUTINEINFOBYTE) */
/** \brief Define to activate or deactivate the functionality to add one more information byte
 **        to the response of the routine request.
 **        If is set as STD_ON, for every routine which returns E_OK, Dcm shall call the
 **        Application Interface Dcm_AddRoutineInfoByte.
 **        If is set as STD_OFF, the original routine response will be kept. */
#define DCM_ROUTINE_ROUTINEINFOBYTE   [!//
[!IF "node:existsAndTrue(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutineEnableRoutineInfoByte)"!]
  [!WS "3"!]STD_ON
  [!ELSE!]
  [!WS "3"!]STD_OFF
[!ENDIF!]
[!CR!]
[!ENDIF!][!//

#if (defined DCM_ROUTINE_PARALLEL_PROCESSING) /* To prevent double declaration */
  #error "DCM_ROUTINE_PARALLEL_PROCESSING is already defined"
#endif /* #if (defined DCM_ROUTINE_PARALLEL_PROCESSING) */
/** \brief Define to activate or deactivate the functionality of processing routines in parallel */
#define DCM_ROUTINE_PARALLEL_PROCESSING   [!"$DCM_ROUTINE_PARALLEL_PROCESSING"!]

/*==================[type definitions]===========================================================*/

[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]
/** \brief Type of service function for internally handling the routine
 ** control service calls for start, stop and requestResults sub-functions */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RoutineFncHandlerType) (
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief This type contains the configuration information for each Routine Services of the Dcm
 ** module. */
typedef struct
{
  /** \brief Reference to DcmDspSecurityRow Security levels allowed to control this RID */
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) SecurityLevelRef;

  /** \brief Reference to DcmDspSessionRow Sessions allowed to control this RID */
  P2CONST(Dcm_SesCtrlType, TYPEDEF, DCM_CONST) SessionRef;

  /** \brief Number of Security levels allowed to control this RID */
  uint8 NumSesLevels;

  /** \brief Number of Sessions allowed to control this RID */
  uint8 NumSecLevels;
}
Dcm_DspRoutineServicesInfoType;

/** \brief Pointer to const Dcm_DspRoutineServicesInfoType */
typedef P2CONST(Dcm_DspRoutineServicesInfoType, TYPEDEF, DCM_CONST)
  Dcm_DspRoutineServicesInfoPtrType;

/** \brief This type contains the configuration for each Routine Services of the Dcm
 ** module. */
typedef struct
{
  /** \brief Function name handler for request to application the results of a routine */
  Dcm_RoutineFncHandlerType RequestResultsFncHandler;

  /** \brief Function name handler for request to application to start a routine */
  Dcm_RoutineFncHandlerType StartFncHandler;

  /** \brief Function name handler for request to application to stop a routine */
  Dcm_RoutineFncHandlerType StopFncHandler;

  /** \brief Reference to DcmDspRoutineInfo containing information on this routine */
  P2CONST(Dcm_DspRoutineServicesInfoType, TYPEDEF, DCM_CONST) RoutineInfoRef;

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
  /** \brief Pointer to Mode rule function */
  Dcm_ModeRuleFunctionType ModeRuleRoutineFunction;
#endif /* DCM_MODEDECLARATION_SUPPORT */

  /** \brief 2 bytes Identifier of the RID */
  uint16 Identifier;

#if (DCM_DSP_ENABLE_OBD_MIRROR == STD_ON)
  /** \brief Define the interface that will be used for an OBD Routine
   ** TRUE:
   **   - the RID is in the OBD range and a valid reference for DcmDspRoutineTidRef
   **     is configured and configuration parameter DcmDspEnableObdMirror is set to TRUE.
   **
   ** FALSE:
   **   - configuration parameter DcmDspEnableObdMirror is set to FALSE or
   **     the RID is not in OBD range or
   **     the RID is in OBD range and does not have a reference for DcmDspRoutineTidRef
  */
  boolean UseOBDInterface;
#endif /* #if (DCM_DSP_ENABLE_OBD_MIRROR == STD_ON) */
}
Dcm_DspRoutineServicesType;

[!ENDIF!][!//
/*==================[external function declarations]=============================================*/

[!IF "($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!]
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

[!INDENT "0"!][!//
[!//
[!/*----------- External declarations of user functions for the service 0x31 ---------------*/!][!//
[!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*"!]
  [!IF "node:existsAndTrue(DcmDspRoutineUsed) and (((node:existsAndTrue(../../DcmDspEnableObdMirror)) and not(node:exists(DcmDspRoutineTidRef))) or (node:existsAndFalse(../../DcmDspEnableObdMirror)))"!]
    extern FUNC(Std_ReturnType, DCM_CODE) Dcm_[!"node:name(.)"!]_Start(
    [!INDENT "2"!]
    Dcm_OpStatusType OpStatus,
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);
    [!ENDINDENT!]

      [!IF "node:existsAndTrue(DcmDspStopRoutineSupported)"!]
        extern FUNC(Std_ReturnType, DCM_CODE) Dcm_[!"node:name(.)"!]_Stop(
        [!INDENT "2"!]
        Dcm_OpStatusType OpStatus,
        P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
        P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);
        [!ENDINDENT!]
      [!ENDIF!]

[!//
      [!IF "node:existsAndTrue(DcmDspRequestResultsRoutineSupported)"!]
        extern FUNC(Std_ReturnType, DCM_CODE) Dcm_[!"node:name(.)"!]_RequestResults(
        [!INDENT "2"!]
        Dcm_OpStatusType OpStatus,
        P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
        P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);
        [!ENDINDENT!]
      [!ENDIF!]

  [!ENDIF!]
[!ENDLOOP!]
[!ENDINDENT!]
[!//
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

[!ENDIF!]
/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspRoutine/eb-list::*[node:existsAndTrue(DcmDspRoutineUsed)]) and ($DCM_DSP_USE_SERVICE_0X31 = 'STD_ON')"!][!//
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

/** \brief Global array holding the configuration for each routines */
extern CONST(Dcm_DspRoutineServicesType, DCM_CONST) Dcm_DspRoutineConfig[DCM_NUM_ROUTINES];

/** \brief Global array holding the configuration information for each routines */
extern CONST(Dcm_DspRoutineServicesInfoType, DCM_CONST)
  Dcm_DspRoutineInfoConfig[DCM_NUM_ROUTINE_INFO];

[!IF "$DCM_RID_AVAILABILITY_CALCULATION = 'STD_ON'"!]

/** Optimization mechanism for finding the configured OBDonUDS routines (0xE000 - 0xE1FF)
 ** Mechanism created in order to avoid looping through all configured routines.
 ** Optimization procedure:
 ** During generation time all configured routines are sorted by the routine identifier.
 ** In the populating phase of the Dcm_DspRoutineConfig array,
 ** when the first OBDonUDS routine identifier is reached, its index is stored within
 ** $routineOBDOnUDSIndexStart, same applies for the last OBDonUDS routine identifier when reached,
 ** its index is stored within $routineOBDOnUDSIndexEnd.
 ** Within Dcm_Dsp_RoutineControl_CheckAvailabilityOBDRID() function, the variables defined below
 ** are used by the for loop in order to check which OBDonUDS routines are configured, checking only
 ** routines configured in the OBDonUDS range (0xE000 - 0xE1FF).
 */

/** \brief Global variable used to store the starting index of the OBDonUDS routineIds */
extern CONST(uint16, DCM_CONST) Dcm_Dsp_RoutineControl_OBDOnUDS_RoutineIndexStart;

/** \brief Global variable used to store the ending index of the OBDonUDS routineIds */
extern CONST(uint16, DCM_CONST) Dcm_Dsp_RoutineControl_OBDOnUDS_RoutineIndexEnd;

[!ENDIF!]

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

[!ENDIF!]
/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* ifndef DCM_ROUTINECONTROL_CFG_H */
/*==================[end of file]================================================================*/
