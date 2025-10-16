/**
 * \file
 *
 * \brief AUTOSAR Dlt
 *
 * This file contains the implementation of the AUTOSAR
 * module Dlt.
 *
 * \version 1.9.2
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef DLT_INT_CFG_H
#define DLT_INT_CFG_H

/* This file contains the all module internal configuration declarations for
 * the AUTOSAR module Dlt that are target independent. */
/* !LINKSTO Dlt.swdd.DltConfig.Template.Dlt_Int_Cfg_h,1 */

[!INCLUDE "Dlt_Vars.m"!][!//
[!AUTOSPACING!]
/*==================[includes]==============================================*/

#include <Dlt_BSW_Types.h>
#include <Dlt_Types.h>
[!IF "DltGeneral/DltRteUsage = 'true' or DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!]
#include <Rte_Type.h>
[!ENDIF!]

#include <Os.h>

/*------------------[callback header file inclusions]-----------------------*/

/*==================[macros]================================================*/

#if (defined DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL)
#error DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL already defined
#endif
/** \brief Switch for DEM to DET reporting for Dlt full VFB buffer */
#define DLT_PROD_ERR_HANDLING_VFB_BUFFER_FULL    [!//
[!IF "ReportToDem/DltVfbBufferFullReportToDem = 'DEM'"!][!//
TS_PROD_ERR_REP_TO_DEM
[!ELSEIF "ReportToDem/DltVfbBufferFullReportToDem = 'DET'"!][!//
TS_PROD_ERR_REP_TO_DET
[!ELSE!][!//
TS_PROD_ERR_DISABLE
[!ENDIF!][!//




/*------------------[Defensive programming]---------------------------------*/
[!SELECT "DltDefensiveProgramming"!][!//

#if (defined DLT_DEFENSIVE_PROGRAMMING_ENABLED)
#error DLT_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define DLT_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(../DltGeneral/DltDevErrorDetect  = 'true') and (DltDefProgEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_PRECONDITION_ASSERT_ENABLED)
#error DLT_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define DLT_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(../DltGeneral/DltDevErrorDetect  = 'true') and (DltDefProgEnabled = 'true') and (DltPrecondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_POSTCONDITION_ASSERT_ENABLED)
#error DLT_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define DLT_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(../DltGeneral/DltDevErrorDetect  = 'true') and (DltDefProgEnabled = 'true') and (DltPostcondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_UNREACHABLE_CODE_ASSERT_ENABLED)
#error DLT_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define DLT_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(../DltGeneral/DltDevErrorDetect  = 'true') and (DltDefProgEnabled = 'true') and (DltUnreachAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_INVARIANT_ASSERT_ENABLED)
#error DLT_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define DLT_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(../DltGeneral/DltDevErrorDetect  = 'true') and (DltDefProgEnabled = 'true') and (DltInvariantAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined DLT_STATIC_ASSERT_ENABLED)
#error DLT_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define DLT_STATIC_ASSERT_ENABLED           [!//
[!IF "(../DltGeneral/DltDevErrorDetect  = 'true') and (DltDefProgEnabled = 'true') and (DltStaticAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


/*==================[type definitions]======================================*/

#ifndef RTE_TYPE_Dlt_CoreIdType
/** \brief Type for CoreId */
typedef VAR(uint8, TYPEDEF) Dlt_CoreIdType;
#endif

#ifndef RTE_TYPE_Dlt_AppToContextIdTableIdxType
/** \brief Type for ContextId index entry */
typedef uint32_least Dlt_AppToContextIdTableIdxType;
#endif

#ifndef RTE_TYPE_Dlt_ContextIdTableIdxType
/** \brief Type for ContextId index entry */
typedef uint32_least Dlt_ContextIdTableIdxType;
#endif

#ifndef RTE_TYPE_Dlt_AppIdTableIdxType
/** \brief Type for Maximum value of ApplicationId index entry */
typedef uint32_least Dlt_AppIdTableIdxType;
#endif

#ifndef RTE_TYPE_Dlt_AppIdTableType
/** \brief Type for ApplicationId table */
typedef struct
{
  Dlt_Internal_ApplicationIDType AppId;
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
  Dlt_SessionIDType SessionId;
  Dlt_AppDescType DltAppDescription;
[!ENDIF!][!//
[!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
  uint8 AppIdLength;
[!ENDIF!][!//
} Dlt_AppIdTableType;
#endif /* #ifndef RTE_TYPE_Dlt_AppIdTableType */

#ifndef RTE_TYPE_Dlt_AppToContextIdTableType
/** \brief Type for Application to ContextId table */
typedef struct
{
  Dlt_ContextIdTableIdxType ContextIdTableIdx[DLT_MAX_COUNT_CONTEXT_IDS_PER_APP_ID];
} Dlt_AppToContextIdTableType;
#endif

/* !LINKSTO Dlt.swdd.DltConfig.Misc.JetTemplates.Dlt_SessionIdTableType,1 */
#ifndef RTE_TYPE_Dlt_SessionIdTableType
[!IF "(num:i($DltServiceAPI) = $AUTOSAR_421) or (num:i($DltServiceAPI) = $AUTOSAR_422)"!][!//
/** \brief Type for Session Id table */
typedef struct
{
  Dlt_SessionIDType SessionId;
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, LogLevelCallback)
    (Dlt_Internal_ApplicationIDType app_id, Dlt_Internal_ContextIDType context_id, Dlt_MessageLogLevelType loglevel);
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, TraceStatusCallback)
    (Dlt_Internal_ApplicationIDType app_id, Dlt_Internal_ContextIDType context_id, boolean new_trace_status);
[!IF "as:modconf('Dlt')/DltGeneral/DltImplementVerboseMode  = 'true'"!][!//
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, VerboseModeCallback)
    (Dlt_Internal_ApplicationIDType app_id, Dlt_Internal_ContextIDType context_id, boolean is_verbose_mode);
[!ENDIF!][!//
} Dlt_SessionIdTableType;
[!ELSE!][!//
/** \brief Type for Session Id table */
typedef struct
{
  Dlt_SessionIDType SessionId;
} Dlt_SessionIdTableType;
[!ENDIF!][!//
#endif /* #ifndef RTE_TYPE_Dlt_SessionIdTableType */

[!IF "as:modconf('Dlt')/DltGeneral/DltRteUsage = 'false'"!][!//
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
#ifndef RTE_TYPE_Dlt_CtxtDescType
/**brief This type is for Context description information
 ** CtxtDesc: Context description
 ** CtxtDescLen: Context description length*/
typedef struct{
  AppCtxDesc CtxtDesc;
  uint8 CtxtDescLen;
}Dlt_CtxtDescType;
#endif /* #ifndef RTE_TYPE_Dlt_CtxtDescType */
[!ENDIF!][!//

#ifndef RTE_TYPE_Dlt_SessionIdTableIdxType
typedef uint32_least Dlt_SessionIdTableIdxType;
#endif /* #ifndef RTE_TYPE_Dlt_SessionIdTableIdxType */

#ifndef RTE_TYPE_Dlt_ContextIdTableType
typedef struct
{
  Dlt_Internal_ContextIDType ContextId;
  Dlt_SessionIdTableIdxType  SessionIdTableIdx;
  Dlt_MessageTraceStatusType TraceStatus;
  Dlt_MessageLogLevelType    LogLevel;
  uint8                      VerboseMode;
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
  Dlt_CtxtDescType           ContextDescription;
  /* !LINKSTO Dlt.LogChannels.MultipleChannels,1 */
  boolean                    ChannelsIdx[DLT_TXPDU_NO];
  [!IF "$MULTICORE_ENABLED"!][!//
  Dlt_CoreIdType             OsCoreId;
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)) and (as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
  uint8 ContextIdLength;
[!ENDIF!][!//
  uint8                      Flags;
} Dlt_ContextIdTableType;
#endif /* #ifndef RTE_TYPE_Dlt_ContextIdTableType */

[!IF "(node:exists(as:modconf('Dlt')/DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and (as:modconf('Dlt')/DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true')"!][!//
#ifndef RTE_TYPE_Dlt_IOCSendMessageType
/** \brief Type to send a Dlt message from a Dlt slave to the Dlt master via IOC */
typedef struct
{
  Dlt_SessionIDType         session_id;
[!IF "(as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
  uint8                     timestamp[DLT_TMSP_HEADER_LENGTH];
[!ELSE!][!//
  uint32                    timestamp;
[!ENDIF!][!//
  Dlt_MessageCommonInfoType msg_info;
  Dlt_MsgLengthType         msg_data_length;
  uint8                     ServiceId;
  [!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
  uint8                     msg_data[[!"num:i($LargestDltLogChannelMaxMessageLength)"!]U]; /** Largest DltLogChannelMaxMessageLength configured */
  /* !LINKSTO Dlt.LogChannels.MultipleChannels,1 */
  boolean                   ChannelsIdx[DLT_TXPDU_NO];
  [!ELSE!][!//
  uint8                     msg_data[DLT_MAX_MESSAGE_LENGTH];
  [!ENDIF!][!//
  [!IF "(as:modconf('Dlt')/DltGeneral/DltProtocolVersion = 2)"!][!//
  Dlt_MessageAttributesType attributes;
  [!ENDIF!][!//
} Dlt_IOCSendMessageType;
#endif /* #ifndef RTE_TYPE_Dlt_IOCSendMessageType */

#ifndef RTE_TYPE_Dlt_IOCRegisterContextMessageType
/** \brief Type to send context registration information from a Dlt slave to
 **        the Dlt master via IOC. */
typedef struct
{
    Dlt_SessionIDType              session_id;
    Dlt_Internal_ApplicationIDType app_id;
    Dlt_Internal_ContextIDType     context_id;
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
    uint32                         contextIdTableIdx;
[!ENDIF!][!//
    Dlt_MessageLogLevelType        LogLevel;
    Dlt_MessageTraceStatusType     TraceStatus;
    uint8                          VerboseMode;
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
    AppCtxDesc                     app_description;
    uint8                          len_app_description;
    AppCtxDesc                     context_description;
    uint8                          len_context_description;
  [!IF "$MULTICORE_ENABLED"!][!//
    Dlt_CoreIdType                 OsCoreId;
  [!ENDIF!][!//
    boolean                        register_or_unregister;
[!ENDIF!][!//
} Dlt_IOCRegisterContextMessageType;
#endif /* #ifndef RTE_TYPE_Dlt_IOCRegisterContextMessageType */

#ifndef RTE_TYPE_Dlt_IOCSyncTableType
/** \brief Type to send log level and trace status settings from the Dlt
 *+        master to a Dlt slave via IOC. */
typedef struct
{
  uint32                         numberOfContextIds;
  Dlt_ContextIdTableType         ContextIdTable[DLT_MAX_COUNT_CONTEXT_IDS];
  Dlt_MessageLogLevelType        defaultLogLevel;
  Dlt_MessageTraceStatusType     defaultTraceStatus;
  Dlt_FilterMessagesType         filterMessageStatus;
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
  Dlt_AppIdTableType             AppIdTable[DLT_MAX_COUNT_APP_IDS];
  Dlt_SessionIdTableType         SessionIdTable[DLT_SWC_REGISTERED_NO];
  Dlt_AppToContextIdTableType    AppToContextIdTable[DLT_MAX_COUNT_APP_IDS];
  Dlt_AppToContextIdTableIdxType AppToContextIdTableIdx[DLT_MAX_COUNT_APP_IDS];
[!ENDIF!][!//
  Dlt_AppIdTableIdxType          MaxRegisteredAppldTableEntry;
} Dlt_IOCSyncTableType;
#endif /* #ifndef RTE_TYPE_Dlt_IOCSyncTableType */
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "(num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)"!][!//
/** \brief This type describes the callbacks needed for LogTraceSessionControl interface. */
typedef struct{
  Dlt_SessionIDType SessionId;
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, LogLevelChangedCallback) (P2CONST(uint8, AUTOMATIC, DLT_APPL_DATA) appId,
                                                                  P2CONST(uint8, AUTOMATIC, DLT_APPL_DATA) contextId,
                                                                  Dlt_MessageLogLevelType logLevel);
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, TraceStatusChangedCallback) (P2CONST(uint8, AUTOMATIC, DLT_APPL_DATA) appId,
                                                                     P2CONST(uint8, AUTOMATIC, DLT_APPL_DATA) contextId,
                                                                     boolean newTraceStatus);
}Dlt_LogTraceSessionControlCallbacksType;
[!ELSEIF "num:i($DltServiceAPI) = $AUTOSAR_22_11"!][!//
/** \brief This type describes the callbacks needed for LogTraceSessionControl interface. */
typedef struct{
  Dlt_SessionIDType SessionId;
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, LogLevelChangedCallback) (Dlt_ApplicationIDType appId,
                                                                  Dlt_ContextIDType contextId,
                                                                  Dlt_MessageLogLevelType logLevel);
  P2FUNC(Std_ReturnType, DLT_APPL_CODE, TraceStatusChangedCallback) (Dlt_ApplicationIDType appId,
                                                                     Dlt_ContextIDType contextId,
                                                                     boolean newTraceStatus);
}Dlt_LogTraceSessionControlCallbacksType;
[!ENDIF!][!//

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/** \brief Wrapper functions for entering and exiting exclusive areas
 ** on the currently active satellite Dlt instance.
 **/
[!IF "(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!][!//
[!FOR "Index" = "0" TO "node:value(as:modconf('Os')/OsOS/OsNumberOfCores) - 1"!]
    [!IF "node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltSatelliteCore/*[node:ref(DltSatelliteCoreId)/OsCoreId = number($Index)])"!]
#define DLT_1_Core_[!"num:i($Index)"!]_START_SEC_CODE
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

extern FUNC(void, DLT_1_Core_[!"num:i($Index)"!]_CODE) Dlt_EnterExclusiveAreaSatelliteCoreId[!"num:i($Index)"!] (void);

extern FUNC(void, DLT_1_Core_[!"num:i($Index)"!]_CODE) Dlt_ExitExclusiveAreaSatelliteCoreId[!"num:i($Index)"!] (void);

#define DLT_1_Core_[!"num:i($Index)"!]_STOP_SEC_CODE
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]

/*==================[external constants]====================================*/

[!IF "num:i($DltNumSwcsToNotify) > 0"!][!//
#define DLT_START_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>

extern CONST(Dlt_LogTraceSessionControlCallbacksType, DLT_CONST) Dlt_LogTraceSessionControlCallbacks[DLT_NUM_SWCS_TO_NOTIFY];

#define DLT_STOP_SEC_CONST_UNSPECIFIED
#include <Dlt_MemMap.h>
[!ENDIF!][!//

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/
[!IF "(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) and DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'true'"!][!//
  [!FOR "Index" = "0" TO "node:value(as:modconf('Os')/OsOS/OsNumberOfCores) - 1"!][!//
    [!IF "node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltSatelliteCore/*[node:ref(DltSatelliteCoreId)/OsCoreId = number($Index)])"!][!//

/** \brief These tables contain the log level and trace status settings of DltSatelliteCoreId[!"num:i($Index)"!]. */
#define DLT_1_Core_[!"num:i($Index)"!]_START_SEC_VAR_CLEARED_32
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

extern VAR(uint32, DLT_VAR) Dlt_NumberOfContextIds_Core_[!"num:i($Index)"!];
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
extern VAR(Dlt_AppIdTableIdxType, DLT_VAR) Dlt_MaxRegisteredAppldTableEntry_Core_[!"num:i($Index)"!];
extern VAR(Dlt_AppToContextIdTableIdxType, DLT_VAR) Dlt_AppToContextIdTableIdx_Core_[!"num:i($Index)"!][DLT_MAX_COUNT_APP_IDS];
[!ENDIF!][!//

#define DLT_1_Core_[!"num:i($Index)"!]_STOP_SEC_VAR_CLEARED_32
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

#define DLT_1_Core_[!"num:i($Index)"!]_START_SEC_VAR_INIT_8
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

extern VAR(uint8, DLT_VAR) Dlt_InitStateSlave_Core_[!"num:i($Index)"!];
extern VAR(Dlt_MessageLogLevelType, DLT_VAR) Dlt_DefaultLogLevel_Core_[!"num:i($Index)"!];
extern VAR(Dlt_MessageTraceStatusType, DLT_VAR) Dlt_DefaultTraceStatus_Core_[!"num:i($Index)"!];
extern VAR(Dlt_FilterMessagesType, DLT_VAR) Dlt_FilterMessageStatus_Core_[!"num:i($Index)"!];

#define DLT_1_Core_[!"num:i($Index)"!]_STOP_SEC_VAR_INIT_8
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

#define DLT_1_Core_[!"num:i($Index)"!]_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>

extern VAR(Dlt_ContextIdTableType, DLT_VAR) Dlt_ContextIdTable_Core_[!"num:i($Index)"!][DLT_MAX_COUNT_CONTEXT_IDS];
[!IF "num:i($DltServiceAPI) >= $AUTOSAR_431"!][!//
extern VAR(Dlt_AppIdTableType, DLT_VAR) Dlt_AppIdTable_Core_[!"num:i($Index)"!][DLT_MAX_COUNT_APP_IDS];
extern VAR(Dlt_AppToContextIdTableType, DLT_VAR) Dlt_AppToContextIdTable_Core_[!"num:i($Index)"!][DLT_MAX_COUNT_APP_IDS];
extern VAR(Dlt_SessionIdTableType, DLT_VAR) Dlt_SessionIdTable_Core_[!"num:i($Index)"!][DLT_SWC_REGISTERED_NO];
[!ENDIF!][!//

#define DLT_1_Core_[!"num:i($Index)"!]_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dlt_1_Core_[!"num:i($Index)"!]_MemMap.h>
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDIF!][!//

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef DLT_INT_CFG_H */
/*==================[end of file]===========================================*/
