/**
 * \file
 *
 * \brief AUTOSAR J1939Rm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Rm.
 *
 * \version 1.1.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* This file contains the generated J1939Rm module configuration. */

[!CODE!]

[!INCLUDE "include/J1939Rm_Vars.m"!]

#ifndef J1939RM_CFG_H
#define J1939RM_CFG_H

/*==================[includes]===============================================*/
#include <J1939Rm_Types.h>
#include <J1939Rm_Types_Int.h>
#include <PduR.h>

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00111,1 */
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportRequestIndication)"!]
[!IF "$J1939Nm_RxIndication > 0"!]
#include <J1939Nm.h>
#include <J1939Nm_Cbk.h>
[!ENDIF!]
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00112,1 */
[!IF "$J1939Dcm_RxIndication > 0"!]
#include <J1939Dcm_Cbk.h>
[!ENDIF!]
[!ENDIF!]
[!IF "$Com_count > 0"!]
#include <Com.h>
[!ENDIF!]
/*==================[macros]=================================================*/
#if (defined J1939RM_CFG_SIGNATURE)
#error J1939RM_CFG_SIGNATURE is already defined
#endif

#define J1939RM_CFG_SIGNATURE [!"asc:getConfigSignature(as:modconf('J1939Rm')[1]//eb-list::*[not(child::*) and (node:configclass() = 'PreCompile') ])"!]U /* Compile time verification value */

#if (defined J1939RM_PUBLIC_INFO_SIGNATURE)
#error J1939RM_PUBLIC_INFO_SIGNATURE is already defined
#endif

#define J1939RM_PUBLIC_INFO_SIGNATURE [!"asc:getConfigSignature(node:difference(as:modconf('J1939Rm')[1]/CommonPublishedInformation//eb-list::*[not(child::*) and (node:configclass() = 'PublishedInformation') ], as:modconf('J1939Rm')[1]/CommonPublishedInformation/Release))"!]U /* PublicInfoSignature */

#if (defined J1939RM_PBCFGM_SUPPORT_ENABLED)
#error J1939RM_PBCFGM_SUPPORT_ENABLED is already defined
#endif
#define J1939RM_PBCFGM_SUPPORT_ENABLED [!IF "node:existsAndTrue(node:contains(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef), as:modconf('J1939Rm')))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ----- Pre-processor switch to enable/disable relocateable postbuild config ----- */
#if (defined J1939RM_RELOCATABLE_CFG_ENABLE)
#error J1939RM_RELOCATABLE_CFG_ENABLE is already defined
#endif

#if (J1939RM_PBCFGM_SUPPORT_ENABLED == STD_ON)
#define J1939RM_RELOCATABLE_CFG_ENABLE [!IF "node:existsAndTrue(as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#else
#define J1939RM_RELOCATABLE_CFG_ENABLE [!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmRelocatablePbcfgEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#endif

#if (defined J1939RM_INVALID_PDU)
#error J1939RM_INVALID_PDU already defined
#endif
/** \brief Switch, indicating whether J1939RmDevErrorDetect functionality is available */
#define J1939RM_INVALID_PDU   65535U

#define J1939Rm_Nr_Of_Configured_Variants  [!"num:i(count(variant:all()))"!]U

[!VAR "MainFunctionPeriod" = "as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmMainFunctionPeriod"!]
[!VAR "temp" = "0.05"!]
[!VAR "FIFTY_MS_TIME_OUT" = "$temp div $MainFunctionPeriod"!]
#define FIFTY_MS_TIME_OUT (uint8)[!"num:i($FIFTY_MS_TIME_OUT)"!]


#if (defined J193RM_J1939DCM_SUPPORT)
#error J193RM_J1939DCM_SUPPORT already defined
#endif
#define J193RM_J1939DCM_SUPPORT     [!//
[!IF "$J1939Dcm_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J1939RM_COM_SUPPORT)
#error J1939RM_COM_SUPPORT already defined
#endif
#define J1939RM_COM_SUPPORT     [!//
[!IF "$Com_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined J1939RM_J1939TP_SUPPORT)
#error J1939RM_J1939TP_SUPPORT already defined
#endif
#define J1939RM_J1939TP_SUPPORT     [!//
[!IF "$Tp_User > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J1939RM_SENDREQUEST_SUPPORT)
#error J1939RM_SENDREQUEST_SUPPORT already defined
#endif
#define J1939RM_SENDREQUEST_SUPPORT     [!//
[!IF "$UserSendRequest_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J1939RM_SENDACK_SUPPORT)
#error J1939RM_SENDACK_SUPPORT already defined
#endif
#define J1939RM_SENDACK_SUPPORT     [!//
[!IF "$UserSendAck_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J1939RM_TIMEOUTSUPERVISION_SUPPORT)
#error J1939RM_TIMEOUTSUPERVISION_SUPPORT already defined
#endif
#define J1939RM_TIMEOUTSUPERVISION_SUPPORT     [!//
[!IF "$UserTimeoutSupervision_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J1939RM_REQUESTINDICATION_SUPPORT)
#error J1939RM_REQUESTINDICATION_SUPPORT already defined
#endif
#define J1939RM_REQUESTINDICATION_SUPPORT     [!//
[!IF "$UserRequestIndication_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J1939RM_ACKINDICATION_SUPPORT)
#error J1939RM_ACKINDICATION_SUPPORT already defined
#endif
#define J1939RM_ACKINDICATION_SUPPORT     [!//
[!IF "$UserAckIndication_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J193RM_J1939NM_SUPPORT)
#error J193RM_J1939NM_SUPPORT already defined
#endif
#define J193RM_J1939NM_SUPPORT      [!//
[!IF "$J1939Nm_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined J193RM_RTE_SUPPORT)
#error J193RM_RTE_SUPPORT already defined
#endif
#define J193RM_RTE_SUPPORT      [!//
[!IF "$Rte_count > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/*
#if (defined J1939RM_DEV_ERROR_DETECT)
#error J1939RM_DEV_ERROR_DETECT already defined
#endif
*/
/** \brief Switch, indicating whether J1939RmDevErrorDetect functionality is available */
/*#define J1939RM_DEV_ERROR_DETECT       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
*/

#if (defined J1939RM_SUPPORT_ACKINDICATION)
#error J1939RM_SUPPORT_ACKINDICATION already defined
#endif
/** \brief Switch, indicating whether support of acknowledgement indications is available */
#define J1939RM_SUPPORT_ACKINDICATION       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmSupportAckIndication)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined J1939RM_SUPPORT_ACKTRANSMISSION)
#error J1939RM_SUPPORT_ACKTRANSMISSION already defined
#endif
/** \brief Switch, indicating whether support of acknowledgement transmission is available */
#define J1939RM_SUPPORT_ACKTRANSMISSION       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmSupportAckTransmission)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined J1939RM_SUPPORT_REQUESTINDICATION)
#error J1939RM_SUPPORT_REQUESTINDICATION already defined
#endif
/** \brief Switch, indicating whether support of request indications is available */
#define J1939RM_SUPPORT_REQUESTINDICATION       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmSupportRequestIndication)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined J1939RM_SUPPORT_REQUESTTRANSMISSION)
#error J1939RM_SUPPORT_REQUESTTRANSMISSION already defined
#endif
/** \brief Switch, indicating whether support of request transmission is available */
#define J1939RM_SUPPORT_REQUESTTRANSMISSION       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmSupportRequestTransmission)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined J1939RM_SUPPORT_TIMEOUTSUPERVISION)
#error J1939RM_SUPPORT_TIMEOUTSUPERVISION already defined
#endif
/** \brief Switch, indicating whether support of request timeout supervision is available */
#define J1939RM_SUPPORT_TIMEOUTSUPERVISION       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmSupportTimeoutSupervision)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined J1939RM_VERSIONINFO_API)
#error J1939RM_VERSIONINFO_API already defined
#endif
/** \brief Switch, indicating whether support of version info API is available */
#define J1939RM_VERSIONINFO_API       [!//
[!IF "node:existsAndTrue(J1939RmGeneral/J1939RmVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!SELECT "(util:distinct(node:order(J1939RmConfigSet/eb-list::*)))"!][!//

/* The value depends on the size of J1939Rm_Channel_Ram_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_CHANNELBSS_SIZE)
#error J1939RM_CFG_CHANNELBSS_SIZE already defined
#endif
#define J1939RM_CFG_CHANNELBSS_SIZE     [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_NrOfChannels_Max[!ELSE!][!"num:i(($TotalNumberOfJ1939RmChannels))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_AckmTxQueueType_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_ACKMTXQUEUETYPEBSS_SIZE)
#error J1939RM_CFG_ACKMTXQUEUETYPEBSS_SIZE already defined
#endif
#define J1939RM_CFG_ACKMTXQUEUETYPEBSS_SIZE     [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_NrOfChannels_Max[!ELSE!][!"num:i(($TotalNumberOfJ1939RmChannels))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_AckmTxQueueData_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_ACKMTXQUEUEDATABSS_SIZE)
#error J1939RM_CFG_ACKMTXQUEUEDATABSS_SIZE already defined
#endif
#define J1939RM_CFG_ACKMTXQUEUEDATABSS_SIZE     [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_AckQueueSizeTotal_Max[!ELSE!][!"num:i(($J1939RmAckQueueSizeTotal))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_RqstTxQueueType_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_RQSTTXQUEUETYPEBSS_SIZE)
#error J1939RM_CFG_RQSTTXQUEUETYPEBSS_SIZE already defined
#endif
#define J1939RM_CFG_RQSTTXQUEUETYPEBSS_SIZE      [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_NrOfChannels_Max[!ELSE!][!"num:i(($TotalNumberOfJ1939RmChannels))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_RqstTxQueueData_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_RQSTTXQUEUEDATABSS_SIZE)
#error J1939RM_CFG_RQSTTXQUEUEDATABSS_SIZE already defined
#endif
#define J1939RM_CFG_RQSTTXQUEUEDATABSS_SIZE      [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_RequestQueueSizeTotal_Max[!ELSE!][!"num:i(($J1939RmRequestQueueSizeTotal))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_RqstTsQueueType_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_RQSTTSQUEUETYPEBSS_SIZE)
#error J1939RM_CFG_RQSTTSQUEUETYPEBSS_SIZE already defined
#endif
#define J1939RM_CFG_RQSTTSQUEUETYPEBSS_SIZE      [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_NrOfChannels_Max[!ELSE!][!"num:i(($TotalNumberOfJ1939RmChannels))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_RqstTsQueueData_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_RQSTTSQUEUEDATABSS_SIZE)
#error J1939RM_CFG_RQSTTSQUEUEDATABSS_SIZE already defined
#endif
#define J1939RM_CFG_RQSTTSQUEUEDATABSS_SIZE       [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_RequestTimeoutMonitorsTotal_Max[!ELSE!][!"num:i(($J1939RmRequestTimeoutMonitorsTotal))"!]U[!ENDIF!]

/* The value depends on the size of J1939Rm_ComIpduRqstQueueType_Struct structure in J1939Rm_Types.h file */
#if (defined J1939RM_CFG_COMIPDURQSTQUEUETYPEBSS_SIZE)
#error J1939RM_CFG_COMIPDURQSTQUEUETYPEBSS_SIZE already defined
#endif
#define J1939RM_CFG_COMIPDURQSTQUEUETYPEBSS_SIZE    [!//
[!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/POST_BUILD_VARIANT_USED) and (num:i(count(variant:all()))>0)"!]J1939RM_NrOfUsers_Max[!ELSE!][!"num:i(($TotalNumberOfJ1939RmUser))"!]U[!ENDIF!]

/* J1939RmUserComIPduRequestQueueSize this parameter not exist */
[!IF "$Com_count > 0"!]
/*The value depends on the size of J1939Rm_RqstTsQueueData_Struct structure in J1939Rm_Types.h file*/
#if (defined J1939RM_CFG_COMIPDURQSTQUEUEDATABSS_SIZE)
#error J1939RM_CFG_COMIPDURQSTQUEUEDATABSS_SIZE already defined
#endif
#define J1939RM_CFG_COMIPDURQSTQUEUEDATABSS_SIZE    [!"num:i($ComIpduRqstQueueSize)"!]U
[!ENDIF!]

/*------------------[symbolic name values]----------------------------------*/
/* J1939RmChannelIDs in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmChannel/eb-list::*))"!]
[!VAR "ComMChannelIdValue" = "(as:ref(J1939RmComMNetworkHandleRef)/ComMChannelId)"!]

#if (defined J1939RM_J1939RMCHANNEL_CFG_[!"text:toupper(as:name(.))"!])
#error J1939RM_J1939RMCHANNEL_CFG_[!"text:toupper(as:name(.))"!] already defined
#endif
#define J1939RM_J1939RMCHANNEL_CFG_[!"text:toupper(as:name(.))"!]    [!"$ComMChannelIdValue"!]U  /* Reference to [!"as:name(.)"!] ID */
[!ENDLOOP!]

/* J1939RmUserIDs in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmNode/eb-list::*))"!]
  [!LOOP "util:distinct(node:order(J1939RmUser/eb-list::*))"!]
    [!IF "node:exists(J1939RmUserId)"!]
    [!VAR "J1939RmUserIdValue"= "node:value(J1939RmUserId)"!]

#if (defined J1939RM_J1939RMUSER_CFG_[!"text:toupper(as:name(.))"!])
#error J1939RM_J1939RMUSER_CFG_[!"text:toupper(as:name(.))"!] already defined
#endif
#define J1939RM_J1939RMUSER_CFG_[!"text:toupper(as:name(.))"!]    [!"$J1939RmUserIdValue"!]U  /* Reference to  [!"as:name(.)"!] */
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]

/* J1939RmNmNodeIDs in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmNode/eb-list::*))"!]
  [!VAR "J1939RmNmNodeIdValue" = "node:ref(J1939RmNmNodeRef)/J1939NmNodeId"!]
  [!VAR "J1939RmNmNodeAddress" = "node:ref(J1939RmNmNodeRef)/J1939NmNodePreferredAddress"!]

#if (defined J1939RM_J1939RMNODE_CFG_[!"text:toupper(as:name(.))"!])
#error J1939RM_J1939RMNODE_CFG_[!"text:toupper(as:name(.))"!] already defined
#endif
#define J1939RM_J1939RMNODE_CFG_[!"text:toupper(as:name(.))"!]    [!"$J1939RmNmNodeIdValue"!]U  /* Reference to  [!"as:name(.)"!] */

#if (defined J1939RM_J1939RMNODE_CFG_[!"text:toupper(as:name(.))"!]_NODEADDRESS)
#error J1939RM_J1939RMNODE_CFG_[!"text:toupper(as:name(.))"!]_NODEADDRESS already defined
#endif
#define J1939RM_J1939RMNODE_CFG_[!"text:toupper(as:name(.))"!]_NODEADDRESS    [!"$J1939RmNmNodeAddress"!]U  /* Reference to  [!"as:name(.)"!] */
[!ENDLOOP!]

/* J1939RmAckmRxPdus in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmChannel/eb-list::*))"!]
  [!IF "node:exists(J1939RmAckmRxPdu)"!]
  [!VAR "J1939RmAckmRxPduIdValue"= "(J1939RmAckmRxPdu/J1939RmAckmRxPduId)"!]

#if (defined J1939RmConf_J1939RmAckmRxPdu_[!"as:name(J1939RmAckmRxPdu)"!])
#error J1939RmConf_J1939RmAckmRxPdu_[!"as:name(J1939RmAckmRxPdu)"!] already defined
#endif
#define J1939RmConf_J1939RmAckmRxPdu_[!"as:name(J1939RmAckmRxPdu)"!]    [!"$J1939RmAckmRxPduIdValue"!]U  /* Reference to [!"as:name(J1939RmAckmRxPdu)"!] ID */
  [!ENDIF!]
[!ENDLOOP!]

/* J1939RmAckmTxPdus in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmChannel/eb-list::*))"!]
  [!IF "node:exists(J1939RmAckmTxPdu)"!]
  [!VAR "J1939RmAckmTxPduIdValue" = "(J1939RmAckmTxPdu/J1939RmAckmTxPduId)"!]

#if (defined J1939RmConf_J1939RmAckmTxPdu_[!"as:name(J1939RmAckmTxPdu)"!])
#error J1939RmConf_J1939RmAckmTxPdu_[!"as:name(J1939RmAckmTxPdu)"!] already defined
#endif
#define J1939RmConf_J1939RmAckmTxPdu_[!"as:name(J1939RmAckmTxPdu)"!]    [!"$J1939RmAckmTxPduIdValue"!]U  /* Reference to [!"as:name(J1939RmAckmTxPdu)"!] ID */
  [!ENDIF!]
[!ENDLOOP!]

/* J1939RmRqstRxPdu in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmChannel/eb-list::*))"!]
  [!IF "node:exists(J1939RmRqstRxPdu)"!]
  [!VAR "J1939RmRqstRxPduIdValue"= "(J1939RmRqstRxPdu/J1939RmRqstRxPduId)"!]

#if (defined J1939RmConf_J1939RmRqstRxPdu_[!"as:name(J1939RmRqstRxPdu)"!])
#error J1939RmConf_J1939RmRqstRxPdu_[!"as:name(J1939RmRqstRxPdu)"!] already defined
#endif
#define J1939RmConf_J1939RmRqstRxPdu_[!"as:name(J1939RmRqstRxPdu)"!]    [!"$J1939RmRqstRxPduIdValue"!]U  /* Reference to [!"as:name(J1939RmRqstRxPdu)"!] ID */
  [!ENDIF!]
[!ENDLOOP!]

/* J1939RmRqstTxPdu in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmChannel/eb-list::*))"!]
  [!IF "node:exists(J1939RmRqstTxPdu)"!]
  [!VAR "J1939RmRqstTxPduIdValue"= "(J1939RmRqstTxPdu/J1939RmRqstTxPduId)"!]

#if (defined J1939RmConf_J1939RmRqstTxPdu_[!"as:name(J1939RmRqstTxPdu)"!])
#error J1939RmConf_J1939RmRqstTxPdu_[!"as:name(J1939RmRqstTxPdu)"!] already defined
#endif
#define J1939RmConf_J1939RmRqstTxPdu_[!"as:name(J1939RmRqstTxPdu)"!]    [!"$J1939RmRqstTxPduIdValue"!]U  /* Reference to [!"as:name(J1939RmRqstTxPdu)"!] ID */
  [!ENDIF!]
[!ENDLOOP!]

/* J1939RmUpperComIPduIds in ConfigSet  */
/* J1939RmLowerComIPduIds in ConfigSet  */
[!LOOP "util:distinct(node:order(J1939RmNode/eb-list::*))"!]
  [!LOOP "util:distinct(node:order(J1939RmUser/eb-list::*))"!]
    [!IF "J1939RmUserType = 'J1939RM_USER_COM'"!]
      [!LOOP "(util:distinct(node:order(J1939RmComIPdu/eb-list::*)))"!]
      [!VAR "J1939RmUpperComIPduIdValue"= "(J1939RmUpperComIPdu/J1939RmUpperComIPduId)"!]
      [!VAR "J1939RmLowerComIPduIdValue"= "(J1939RmLowerComIPdu/J1939RmLowerComIPduId)"!]

#if (defined J1939RmConf_J1939RmUpperComIPdu_[!"as:name(J1939RmUpperComIPdu)"!])
#error J1939RmConf_J1939RmUpperComIPdu_[!"as:name(J1939RmUpperComIPdu)"!] already defined
#endif
#define J1939RmConf_J1939RmUpperComIPdu_[!"as:name(J1939RmUpperComIPdu)"!]    [!"$J1939RmUpperComIPduIdValue"!]U  /* Reference to [!"as:name(J1939RmUpperComIPdu)"!] ID */

#if (defined J1939RmConf_J1939RmLowerComIPdu_Cfg_[!"as:name(J1939RmLowerComIPdu)"!])
#error J1939RmConf_J1939RmLowerComIPdu_[!"as:name(J1939RmLowerComIPdu)"!] already defined
#endif
#define J1939RmConf_J1939RmLowerComIPdu_[!"as:name(J1939RmLowerComIPdu)"!]    [!"$J1939RmLowerComIPduIdValue"!]U  /* Reference to [!"as:name(J1939RmLowerComIPdu)"!] ID */
      [!ENDLOOP!]
    [!ELSEIF "J1939RmUserType = 'J1939RM_USER_RTE'"!]
      [!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportAckTransmission)"!]
        [!IF "(node:existsAndTrue(J1939RmUserSendAck))"!]
          #ifndef J1939RM_RTE_SEND_ACK
          #define J1939RM_RTE_SEND_ACK
          #endif
        [!ENDIF!]
      [!ENDIF!]
      [!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportRequestTransmission)"!]
        [!IF "(node:existsAndTrue(J1939RmUserSendRequest))"!]
          #ifndef J1939RM_RTE_SEND_REQUEST
          #define J1939RM_RTE_SEND_REQUEST
          #endif
        [!ENDIF!]
      [!ENDIF!]
      [!IF "node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportTimeoutSupervision)"!]
        [!IF "(node:existsAndTrue(J1939RmUserTimeoutSupervision))"!]
          #ifndef J1939RM_RTE_CANCEL_REQUEST_TIMEOUT
          #define J1939RM_RTE_CANCEL_REQUEST_TIMEOUT
          #endif
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
[!ENDSELECT!][!//
/*==================[external constants]=====================================*/

#define J1939RM_START_SEC_CONST_UNSPECIFIED
#include <J1939Rm_MemMap.h>

/** \brief Configuration placeholder for J1939Rm_Init() call. */
extern CONST( J1939Rm_RealStructType, J1939RM_CONST ) J1939Rm_Cfg_J1939RmConfig;

#define J1939RM_STOP_SEC_CONST_UNSPECIFIED
#include <J1939Rm_MemMap.h>

#endif /* J1939RM_CFG_H */
/*======================[end of file]============================================*/
[!ENDCODE!]
