/**
 * \file
 *
 * \brief AUTOSAR Mirror
 *
 * This file contains the implementation of the AUTOSAR
 * module Mirror.
 *
 * \version 1.1.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!CODE!]
#ifndef MIRROR_CFG_H
#define MIRROR_CFG_H

/*==================[includes]==============================================*/
 
#include <Mirror_Types.h>
[!INCLUDE "../include/Mirror_PrecompileMacros.m"!][!//
[!LOOP "as:modconf('Mirror')[1]/MirrorGeneral/MirrorHeaderFileInclusion/*"!][!//
#include "[!"node:value(.)"!]"      /* Call back header file */
[!ENDLOOP!][!//
/*==================[macros]================================================*/

/** \brief Support for Development error reporting
 ** This macro defines whether the Det_ReportError() is provided or not.
 ** STD_ON    Function is provided
 ** STD_OFF   Function is not provided
*/
/* !LINKSTO Mirror.ASR44.ECUC_Mirror_00003,1 */
#if(defined MIRROR_DEV_ERROR_DETECT)
#error MIRROR_DEV_ERROR_DETECT already defined!
#endif /* #if(defined MIRROR_DEV_ERROR_DETECT)*/
#define MIRROR_DEV_ERROR_DETECT        STD_[!IF "MirrorGeneral/MirrorDevErrorDetect = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Support of Mirror_GetVersionInfo()
 ** This macro defines whether the Mirror_GetVersionInfo is provided or not.
 ** STD_ON    Function is provided
 ** STD_OFF   Function is not provided
*/
#if(defined MIRROR_VERSION_INFO_API)
#error MIRROR_VERSION_INFO_API already defined!
#endif /* #if(defined MIRROR_VERSION_INFO_API)*/
#define MIRROR_VERSION_INFO_API        STD_[!IF "MirrorGeneral/MirrorVersionInfoApi = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief The TimeBaseId the Mirror module will use. */
#if(defined MIRROR_TIMEBASEID)
#error MIRROR_TIMEBASEID already defined!
#endif /* #if(defined MIRROR_TIMEBASEID)*/
#define MIRROR_TIMEBASEID        [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomGetTimeFuncName)"!]0U[!ELSE!][!"node:value(as:ref(as:modconf('Mirror')[1]/MirrorGeneral/MirrorStbRef)/StbMSynchronizedTimeBaseIdentifier)"!]U[!ENDIF!]
[!CALL "InitialDestNetworkIndex"!][!//

/** \brief The initial destination network network the Mirror module will use. */
#if(defined MIRROR_INITIAL_DEST_NETWORK_IDX)
#error MIRROR_INITIAL_DEST_NETWORK_IDX already defined!
#endif /* #if(defined MIRROR_INITIAL_DEST_NETWORK_IDX)*/
#define MIRROR_INITIAL_DEST_NETWORK_IDX        [!"num:i($InitDestIndex)"!]U
[!CALL "NumOfSrcControllers"!][!//

/** \brief Number of source controllers or channels configured for all source networks. */
#if(defined MIRROR_NO_OF_SOURCECONTROLLERS)
#error MIRROR_NO_OF_SOURCECONTROLLERS already defined!
#endif /* #if(defined MIRROR_NO_OF_SOURCECONTROLLERS)*/
#define MIRROR_NO_OF_SOURCECONTROLLERS        [!"num:i($SrcControllerCount)"!]U

/* !LINKSTO Mirror.EB.MirrorGetCurrentTime,1 */
/** \brief The function used to get the current time wheter from StbM or a custom function. */
#if(defined MIRROR_GET_TIME_STAMP)
#error MIRROR_GET_TIME_STAMP already defined!
#endif /* #if(defined MIRROR_GET_TIME_STAMP)*/
#define MIRROR_GET_TIME_STAMP(TimeStamp,UserData)    [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomGetTimeFuncName)"!][!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomGetTimeFuncName)"!](MIRROR_TIMEBASEID, TimeStamp, UserData)[!ELSE!](void)StbM_GetCurrentTime(MIRROR_TIMEBASEID, TimeStamp, UserData)[!ENDIF!]
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinLostFrameCallBack)) and not(node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond))"!][!//

/** \brief The call back function called in case of a lost LIN frame. */
#if(defined MIRROR_LIN_LOST_FRAME_CBK)
#error MIRROR_LIN_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_LIN_LOST_FRAME_CBK)*/
#define MIRROR_LIN_LOST_FRAME_CBK(MirrorNetworkId) [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinLostFrameCallBack)"!](MirrorNetworkId)
[!ENDIF!][!//
[!VAR "CanSrcNWSize" = "num:i(count(as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*[node:name(.) = 'MirrorSourceNetworkCan']))"!][!//
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanLostFrameCallBack)) and $CanSrcNWSize > 0"!][!//

/** \brief The call back function called in case of a lost CAN frame. */
#if(defined MIRROR_CAN_LOST_FRAME_CBK)
#error MIRROR_CAN_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_CAN_LOST_FRAME_CBK)*/
#define MIRROR_CAN_LOST_FRAME_CBK(MirrorNetworkId) [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanLostFrameCallBack)"!](MirrorNetworkId)
[!ENDIF!][!//
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDLostFrameCallBack)) and not(node:empty(as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*/MirrorCanFDFramesPerSecond))"!][!//

/** \brief The call back function called in case of a lost CANFD frame. */
#if(defined MIRROR_CANFD_LOST_FRAME_CBK)
#error MIRROR_CANFD_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_CANFD_LOST_FRAME_CBK)*/
#define MIRROR_CANFD_LOST_FRAME_CBK(MirrorNetworkId) [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDLostFrameCallBack)"!](MirrorNetworkId)
[!ENDIF!][!//
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrLostFrameCallBack)) and not(node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrFramesPerSecond))"!][!//

/** \brief The call back function called in case of a lost FlexRay frame. */
#if(defined MIRROR_FLEXRAY_LOST_FRAME_CBK)
#error MIRROR_FLEXRAY_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_FLEXRAY_LOST_FRAME_CBK)*/
#define MIRROR_FLEXRAY_LOST_FRAME_CBK(MirrorNetworkId) [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrLostFrameCallBack)"!](MirrorNetworkId)
[!ENDIF!][!//
[!CALL "MaxQueueAndBuffSize"!][!//

/** \brief The maximum number of queue buffer size configured for all destination networks. */
#if(defined MIRROR_MAX_QUEUE_SIZE)
#error MIRROR_MAX_QUEUE_SIZE already defined!
#endif /* #if(defined MIRROR_MAX_QUEUE_SIZE)*/
#define MIRROR_MAX_QUEUE_SIZE        [!"num:i($MaxQueueSize)"!]U

/** \brief The maximum buffer size that any destination network would use. */
#if(defined MIRROR_MAX_BUFFER_SIZE)
#error MIRROR_MAX_BUFFER_SIZE already defined!
#endif /* #if(defined MIRROR_MAX_BUFFER_SIZE)*/
#define MIRROR_MAX_BUFFER_SIZE        [!"num:i($MaxBuffSize)"!]U

/** \brief The number of Lin frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_LIN_ELEMENTCOUNTER)
#error MIRROR_LIN_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_LIN_ELEMENTCOUNTER)*/
#define MIRROR_LIN_ELEMENTCOUNTER          [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!]MIRROR_ZERO_ELEMENTS[!ELSE!][!"num:i((((as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)) * $MainFuncPeriod) +1)"!]U[!ENDIF!]

[!VAR "CanElementNumber" = "0"!][!//
[!LOOP "as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*"!][!//
[!IF "node:name(.) = 'MirrorSourceNetworkCan'"!][!//
[!VAR "CanElementNumber" = "$CanElementNumber + (num:i((node:value(./MirrorCanFramesPerSecond) * $MainFuncPeriod) +1))"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/** \brief The number of CAN frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_CAN_ELEMENTCOUNTER)
#error MIRROR_CAN_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_CAN_ELEMENTCOUNTER)*/
#define MIRROR_CAN_ELEMENTCOUNTER        [!"num:i($CanElementNumber)"!]U

[!VAR "CanFDElementNumber" = "0"!][!//
[!LOOP "as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*"!][!//
[!IF "node:name(.) = 'MirrorSourceNetworkCan'"!][!//
[!IF "node:exists(./MirrorCanFDFramesPerSecond)"!][!//
[!VAR "CanFDElementNumber" = "$CanFDElementNumber + (num:i((node:value(./MirrorCanFDFramesPerSecond) * $MainFuncPeriod) +1))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/** \brief The number of CANFD frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_CANFD_ELEMENTCOUNTER)
#error MIRROR_CANFD_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_CANFD_ELEMENTCOUNTER)*/
#define MIRROR_CANFD_ELEMENTCOUNTER        [!"num:i($CanFDElementNumber)"!]U

/** \brief The number of FlexRay frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_FLEXRAY_ELEMENTCOUNTER)
#error MIRROR_FLEXRAY_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_FLEXRAY_ELEMENTCOUNTER)*/
#define MIRROR_FLEXRAY_ELEMENTCOUNTER          [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrFramesPerSecond)"!]MIRROR_ZERO_ELEMENTS[!ELSE!][!"num:i((((as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrFramesPerSecond)) * $MainFuncPeriod) +1)"!]U[!ENDIF!]
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!][!//

[!VAR "LinIndex" = "0"!][!//
[!LOOP "as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*"!][!//
[!IF "node:name(.) = 'MirrorSourceNetworkLin'"!][!//
[!BREAK!][!//
[!ELSE!][!//
[!VAR "LinIndex" = "($LinIndex + 1)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/** \brief Indicates index of the first configured LIN network. */
#if(defined MIRROR_LIN_FIRSTNETWORKINDEX)
#error MIRROR_LIN_FIRSTNETWORKINDEX already defined!
#endif /* #if(defined MIRROR_LIN_FIRSTNETWORKINDEX)*/
#define MIRROR_LIN_FIRSTNETWORKINDEX          [!"num:i($LinIndex)"!]U
[!ENDIF!][!//
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrFramesPerSecond)"!][!//

[!VAR "FrIndex" = "0"!][!//
[!LOOP "as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*"!][!//
[!IF "node:name(.) = 'MirrorSourceNetworkFlexRay'"!][!//
[!BREAK!][!//
[!ELSE!][!//
[!VAR "FrIndex" = "($FrIndex + 1)"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/** \brief Indicates index of the first configured FlexRay network. */
#if(defined MIRROR_FLEXRAY_FIRSTNETWORKINDEX)
#error MIRROR_FLEXRAY_FIRSTNETWORKINDEX already defined!
#endif /* #if(defined MIRROR_FLEXRAY_FIRSTNETWORKINDEX)*/
#define MIRROR_FLEXRAY_FIRSTNETWORKINDEX          [!"num:i($FrIndex)"!]U
[!ENDIF!][!//

/** \brief Indicating if a LIN source network is configured. */
#if(defined MIRROR_LIN_SOURCENETWORK)
#error MIRROR_LIN_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_LIN_SOURCENETWORK)*/
#define MIRROR_LIN_SOURCENETWORK          STD_[!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!]OFF[!ELSE!]ON[!ENDIF!]

/** \brief Indicating if a CAN source network is configured. */
#if(defined MIRROR_CAN_SOURCENETWORK)
#error MIRROR_CAN_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_CAN_SOURCENETWORK)*/
#define MIRROR_CAN_SOURCENETWORK           STD_[!IF "$CanSrcNWSize > 0"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if a CANFD source network is configured. */
#if(defined MIRROR_CANFD_SOURCENETWORK)
#error MIRROR_CANFD_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_CANFD_SOURCENETWORK)*/
#define MIRROR_CANFD_SOURCENETWORK           STD_[!IF "node:exists(as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*/MirrorCanFDFramesPerSecond)"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if a FlexRay source network is configured. */
#if(defined MIRROR_FLEXRAY_SOURCENETWORK)
#error MIRROR_FLEXRAY_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_FLEXRAY_SOURCENETWORK)*/
#define MIRROR_FLEXRAY_SOURCENETWORK          STD_[!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrFramesPerSecond)"!]OFF[!ELSE!]ON[!ENDIF!]
[!CALL "SrcNetworkCtrlTrcvCheck"!][!//

/** \brief Indicating if any configured can source network has transceiver support. */
#if(defined MIRROR_CANTRCV)
#error MIRROR_CANTRCV already defined!
#endif /* #if(defined MIRROR_CANTRCV)*/
#define MIRROR_CANTRCV          STD_[!IF "$CanTrcvCfg = 1"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if any configured lin source network has transceiver support. */
#if(defined MIRROR_LINTRCV)
#error MIRROR_LINTRCV already defined!
#endif /* #if(defined MIRROR_LINTRCV)*/
#define MIRROR_LINTRCV          STD_[!IF "$LinTrcvCfg = 1"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if the communication between the Mirror and the CanIf uses IPC. */
#if(defined MIRROR_CANIPCSUPPORT)
#error MIRROR_CANIPCSUPPORT already defined!
#endif /* #if(defined MIRROR_CANIPCSUPPORT)*/
#define MIRROR_CANIPCSUPPORT          STD_[!IF "as:modconf('Mirror')[1]/MirrorGeneral/MirrorUseCanIfIPC = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if the communication between the Mirror and the LinIf uses IPC. */
#if(defined MIRROR_LINIPCSUPPORT)
#error MIRROR_LINIPCSUPPORT already defined!
#endif /* #if(defined MIRROR_LINIPCSUPPORT)*/
#define MIRROR_LINIPCSUPPORT          STD_[!IF "as:modconf('Mirror')[1]/MirrorGeneral/MirrorUseLinIfIPC = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if the communication between the Mirror and the FrIf uses IPC. */
#if(defined MIRROR_FRIPCSUPPORT)
#error MIRROR_FRIPCSUPPORT already defined!
#endif /* #if(defined MIRROR_FRIPCSUPPORT)*/
#define MIRROR_FRIPCSUPPORT          STD_[!IF "as:modconf('Mirror')[1]/MirrorGeneral/MirrorUseFrIfIPC = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating the type of network to be CAN */
#if(defined MIRROR_CAN_NETWORK_TYPE)
#error MIRROR_CAN_NETWORK_TYPE already defined!
#endif /* #if(defined MIRROR_CAN_NETWORK_TYPE)*/
#define MIRROR_CAN_NETWORK_TYPE         0U

/** \brief Indicating the type of network to be CANFD */
#if(defined MIRROR_CANFD_NETWORK_TYPE)
#error MIRROR_CANFD_NETWORK_TYPE already defined!
#endif /* #if(defined MIRROR_CANFD_NETWORK_TYPE)*/
#define MIRROR_CANFD_NETWORK_TYPE         1U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/
#define MIRROR_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <Mirror_MemMap.h>

extern CONST(Mirror_DestNetworkType, MIRROR_APPL_CONST) Mirror_DestNetworks[MIRROR_NO_OF_DESTNETWORKS];

extern CONST(Mirror_SourceNetworkType, MIRROR_APPL_CONST) Mirror_SourceNetworks[MIRROR_NO_OF_SOURCENETWORKS];

#define MIRROR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_CONFIG_DATA_8
#include <Mirror_MemMap.h>

extern CONST(uint8, MIRROR_APPL_CONST) Mirror_SourceNetworkControllers[MIRROR_NO_OF_SOURCECONTROLLERS];

#define MIRROR_STOP_SEC_CONFIG_DATA_8
#include <Mirror_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!][!//
#define MIRROR_START_SEC_VAR_CLEARED_GLOBAL_LIN_UNSPECIFIED
#include <Mirror_MemMap.h>

extern VAR(Mirror_LinElementType, MIRROR_VAR) Mirror_LinElement[MIRROR_LIN_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_LinTimeStamp[MIRROR_LIN_ELEMENTCOUNTER];

#define MIRROR_STOP_SEC_VAR_CLEARED_GLOBAL_LIN_UNSPECIFIED
#include <Mirror_MemMap.h>
[!ENDIF!][!//

[!IF "$CanSrcNWSize > 0"!][!//
#define MIRROR_START_SEC_VAR_CLEARED_GLOBAL_CAN_UNSPECIFIED
#include <Mirror_MemMap.h>

extern VAR(Mirror_CanElementType, MIRROR_VAR) Mirror_CanElement[MIRROR_CAN_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_CanTimeStamp[MIRROR_CAN_ELEMENTCOUNTER];

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorConfigSet/MirrorSourceNetwork/*/MirrorCanFDFramesPerSecond)"!][!//
extern VAR(Mirror_CanFDElementType, MIRROR_VAR) Mirror_CanFDElement[MIRROR_CANFD_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_CanFDTimeStamp[MIRROR_CANFD_ELEMENTCOUNTER];

[!ENDIF!][!//
#define MIRROR_STOP_SEC_VAR_CLEARED_GLOBAL_CAN_UNSPECIFIED
#include <Mirror_MemMap.h>
[!ENDIF!][!//

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorFrFramesPerSecond)"!][!//
#define MIRROR_START_SEC_VAR_CLEARED_GLOBAL_FR_UNSPECIFIED
#include <Mirror_MemMap.h>

extern VAR(Mirror_FlexRayElementType, MIRROR_VAR) Mirror_FlexRayElement[MIRROR_FLEXRAY_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_FlexRayTimeStamp[MIRROR_FLEXRAY_ELEMENTCOUNTER];

extern VAR(Mirror_FlexRaySrcAggStatusType, MIRROR_VAR) Mirror_FlexRaySrcAggStatus[MIRROR_NO_OF_FLEXRAYSOURCENETWORKS];

#define MIRROR_STOP_SEC_VAR_CLEARED_GLOBAL_FR_UNSPECIFIED
#include <Mirror_MemMap.h>
[!ENDIF!][!//

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef MIRROR_CFG_H */
/*==================[end of file]===========================================*/
[!ENDCODE!]