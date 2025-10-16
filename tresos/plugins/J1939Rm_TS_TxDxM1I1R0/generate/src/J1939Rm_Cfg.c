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

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 9.3 (Required)
 *    Arrays shall not be partially initialized.
 *
 *    Reason:
 *    - The J1939Rm_GlobalConfig.J1939Rm50MsSupervision is initialized in J1939Rm_Init.
 *
 *  MISRAC2012-2) Deviated Rule 11.1 (Required)
 *    Conversions shall not be performed between a pointer to a function and any other type.
 *
 *    Reason:
 *    - Casting must be done to avoid the warning because the Rte_user has a different return type for all its callback functions.
 */
[!CODE!]
[!AUTOSPACING!]
[!INCLUDE "include/J1939Rm_Vars.m"!]
[!SELECT "(J1939RmConfigSet/eb-list::*)"!][!//
/*==================[inclusions]============================================*/
#include <J1939Rm.h>
#include <J1939Rm_Api.h>
#include <J1939Rm_Int.h>

[!IF "$Cdd_count > 0"!]
[!LOOP "(util:distinct(node:order(J1939RmNode/eb-list::*)))"!]
  [!LOOP "(util:distinct(node:order(J1939RmUser/eb-list::*)))"!]
    [!IF "(J1939RmUserType = 'J1939RM_USER_CDD')"!]
#include <[!"J1939RmUserCddName"!].h> /* CDD Inclusion */
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
[!ENDIF!]

[!AUTOSPACING!][!//
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

#define J1939RM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Rm_MemMap.h>

/*Runtime memory allocation area for J1939RM*/
static J1939Rm_Channel_Ram_Struct J1939Rm_Cfg_ChannelBss[J1939RM_CFG_CHANNELBSS_SIZE];
static J1939Rm_AckmTxQueueType_Struct J1939Rm_Cfg_AckmTxQueueTypeBss[J1939RM_CFG_ACKMTXQUEUETYPEBSS_SIZE];
static J1939Rm_AckmTxQueueData_Struct J1939Rm_Cfg_AckmTxQueueDataBss[J1939RM_CFG_ACKMTXQUEUEDATABSS_SIZE];
static J1939Rm_RqstTxQueueType_Struct J1939Rm_Cfg_RqstTxQueueTypeBss[J1939RM_CFG_RQSTTXQUEUETYPEBSS_SIZE];
static J1939Rm_RqstTxQueueData_Struct J1939Rm_Cfg_RqstTxQueueDataBss[J1939RM_CFG_RQSTTXQUEUEDATABSS_SIZE];
static J1939Rm_RqstTSQueueType_Struct J1939Rm_Cfg_RqstTsQueueTypeBss[J1939RM_CFG_RQSTTSQUEUETYPEBSS_SIZE];
static J1939Rm_RqstTSQueueData_Struct J1939Rm_Cfg_RqstTsQueueDataBss[J1939RM_CFG_RQSTTSQUEUEDATABSS_SIZE];
static J1939Rm_ComIpduRqstQueueType_Struct J1939Rm_Cfg_ComIpduRqstQueueTypeBss[J1939RM_CFG_COMIPDURQSTQUEUETYPEBSS_SIZE];
[!IF "$Com_count > 0"!]
static J1939Rm_ComIpduRqstQueueData_Struct J1939Rm_Cfg_ComIpduRqstQueueDataBss[J1939RM_CFG_COMIPDURQSTQUEUEDATABSS_SIZE];
[!ENDIF!]

#define J1939RM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Rm_MemMap.h>

/* Public Constant Definitions*/

#define J1939RM_START_SEC_CONST_UNSPECIFIED
#include <J1939Rm_MemMap.h>

/* J1939Rm User Configuration */
/*****************************CONFIGURATION *********************************************/
static CONST(J1939Rm_User_Const_Struct, J1939RM_CONST) J1939Rm_Cfg_Rmuser[[!"num:i($TotalNumberOfJ1939RmUser)"!]] =
{
[!VAR "NodeIndex" = "'0'"!]
[!LOOP "(util:distinct(node:order(J1939RmNode/eb-list::*)))"!]
  [!VAR "UserIndex" = "'0'"!]
  [!LOOP "(util:distinct(node:order(J1939RmUser/eb-list::*)))"!]
  {
        [!VAR "userName" = "as:name(.)"!]
        [!VAR "userName_occurance" = "'0'"!]
      [!LOOP "(as:modconf('J1939Rm')[1]/J1939RmConfigSet/eb-list::*)"!]
          [!LOOP "(util:distinct(node:order(J1939RmNode/eb-list::*)))"!]
              [!LOOP "(util:distinct(node:order(J1939RmUser/eb-list::*)))"!]
              [!VAR "CurrentUserName" = "as:name(.)"!]
                [!IF "$userName = $CurrentUserName"!]
                    [!VAR "userName_occurance" = "num:i($userName_occurance + 1)"!]
                [!ENDIF!]
              [!ENDLOOP!]
          [!ENDLOOP!]
      [!ENDLOOP!]
      [!IF "$userName_occurance > 1"!]
      [!ERROR!]The username should not be repeated[!ENDERROR!]
      [!ENDIF!]
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00086,1 */
    [!IF "(node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportAckIndication)) and (node:existsAndTrue(J1939RmUserAckIndication)) and (J1939RmUserType = 'J1939RM_USER_CDD')"!]
    /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00027,1 */
    &[!"J1939RmUserCddName"!]_AckIndication,     /* J1939RmUserAckIndicationFctPtr */
    [!ELSEIF "(node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportAckIndication)) and (node:existsAndTrue(J1939RmUserAckIndication)) and (J1939RmUserType = 'J1939RM_USER_RTE')"!]
    /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00028,1 */
    /* Deviation MISRAC2012-2 <1> */
    (void (*)(uint8 node, NetworkHandleType channel, uint32 ackPgn, J1939Rm_AckCode ackCode, uint8 ackAddress, uint8 sourceAddress, uint8 priority))Rte_Call_J1939Rm_AckIndication_[!"as:name(.)"!]_AckIndication,
    [!ELSE!]
    NULL_PTR,     /*_AckIndication*/
    [!ENDIF!]
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00085,1 */
    [!IF "(node:existsAndTrue(J1939RmUserRequestIndication)) and (node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportRequestIndication))"!]
      [!IF "J1939RmUserType = 'J1939RM_USER_J1939DCM'"!]
       /* !LINKSTO EB_Ref.SWS_J1939Rm_00002.J1939Dcm,1 */
       /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.J1939Dcm_RequestIndication,1 */
    &J1939Dcm_RequestIndication,       /* J1939RmUserRequestIndicationFctPtr */
      [!ENDIF!]
      [!IF "J1939RmUserType = 'J1939RM_USER_J1939NM'"!]
      /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.J1939Nm_RequestIndication,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Rm_00002.J1939Nm,1 */
    &J1939Nm_RequestIndication,       /* J1939RmUserRequestIndicationFctPtr */
      [!ENDIF!]
      [!IF "J1939RmUserType = 'J1939RM_USER_CDD'"!]
      /* !LINKSTO EB_Ref.SWS_J1939Rm_00002.CDD,1 */
    &[!"J1939RmUserCddName"!]_RequestIndication,
      [!ENDIF!]
      [!IF "J1939RmUserType = 'J1939RM_USER_RTE'"!]  
      /* !LINKSTO J1939Rm.SWS_J1939Rm_00003,1 */
      /* Deviation MISRAC2012-2 <1> */
    (void (*)(uint8 node, NetworkHandleType channel, uint32 requestedPgn, uint8 sourceAddress, uint8 destAddress, uint8 priority))Rte_Call_J1939Rm_RequestIndication_[!"as:name(.)"!]_RequestIndication,
      [!ENDIF!]
    [!ELSE!]
    NULL_PTR,     /*_RequestIndication*/
    [!ENDIF!]
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00087,1 */
    [!IF "(node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportTimeoutSupervision)) and (node:existsAndTrue(J1939RmUserTimeoutSupervision)) and (J1939RmUserType = 'J1939RM_USER_CDD')"!]
    &[!"J1939RmUserCddName"!]_RequestTimeoutIndication,       /* J1939RmUserRequestTimeoutIndicationFctPtr */
    [!ELSEIF "(node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportTimeoutSupervision)) and (node:existsAndTrue(J1939RmUserTimeoutSupervision)) and (J1939RmUserType = 'J1939RM_USER_RTE')"!]
    /* Deviation MISRAC2012-2 <1> */
    (void (*)(uint8 node, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress))Rte_Call_J1939Rm_RequestTimeoutIndication_[!"as:name(.)"!]_RequestTimeoutIndication,
    [!ELSE!]
    NULL_PTR, /*_RequestTimeoutIndication*/
    [!ENDIF!]
    [!IF "(node:existsAndTrue(as:modconf('J1939Rm')[1]/J1939RmGeneral/J1939RmSupportTimeoutSupervision)) and (node:existsAndTrue(J1939RmUserTimeoutSupervision))"!]
      [!IF "((J1939RmUserType = 'J1939RM_USER_CDD') or (J1939RmUserType = 'J1939RM_USER_RTE'))"!]
    &J1939Rm_CancelRequestTimeout,     /* J1939RmCancelRequestTimeoutFctPtr */
      [!ELSE!]
    NULL_PTR,     /* J1939RmCancelRequestTimeoutFctPtr */
      [!ENDIF!]
    [!ELSE!]
    NULL_PTR,     /* J1939RmCancelRequestTimeoutFctPtr */
    [!ENDIF!]
  },
  [!VAR "UserIndex" = "num:i($UserIndex + 1)"!]
  [!ENDLOOP!]
[!VAR "NodeIndex" = "num:i($NodeIndex + 1)"!]
[!ENDLOOP!]
};

#define J1939RM_STOP_SEC_CONST_UNSPECIFIED
#include <J1939Rm_MemMap.h>

[!ENDSELECT!][!//

#define J1939RM_START_SEC_CONST_UNSPECIFIED
#include <J1939Rm_MemMap.h>

/* J1939Rm Configuration */
/* !LINKSTO J1939Rm.dsn.PrecompileTimeConfig,1 */
CONST(J1939Rm_RealStructType, J1939RM_CONST) J1939Rm_Cfg_J1939RmConfig =
{
/*****************************CONFIGURATION *********************************************************/
    &J1939Rm_Cfg_Rmuser[0],       /*J1939RmUserConstStructPtr*/
    &J1939Rm_Cfg_ChannelBss[0],
    &J1939Rm_Cfg_AckmTxQueueTypeBss[0],
    &J1939Rm_Cfg_RqstTxQueueTypeBss[0],
    &J1939Rm_Cfg_RqstTsQueueTypeBss[0],
    &J1939Rm_Cfg_AckmTxQueueDataBss[0],
    &J1939Rm_Cfg_RqstTxQueueDataBss[0],
    &J1939Rm_Cfg_RqstTsQueueDataBss[0],
    &J1939Rm_Cfg_ComIpduRqstQueueTypeBss[0],
    [!IF "$Com_count > 0"!]
    &J1939Rm_Cfg_ComIpduRqstQueueDataBss[0],/* Memory allocation area info - J1939Rm_ComIpduRqstQueueData_Struct_tag structure */
    [!ELSE!]
    NULL_PTR,/* Runtime Memory allocation area info - Icsp_J1939Rm_ComIpduRqstQueueData_Struct_tag structure */
    [!ENDIF!]
  /* Deviation MISRAC2012-1 <1> */
};

#define J1939RM_STOP_SEC_CONST_UNSPECIFIED
#include <J1939Rm_MemMap.h>
/*======================[end of file]============================================*/

[!ENDCODE!]
