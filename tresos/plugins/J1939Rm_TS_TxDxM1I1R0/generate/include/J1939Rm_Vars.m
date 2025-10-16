[!/**
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
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('J1939RM_VARS_M'))"!][!/*
*/!][!VAR "J1939RM_VARS_M"="'true'"!][!/*

*** Total number of Rm Channels ***
*/!][!VAR "TotalNumberOfJ1939RmChannels" = "num:i(count(J1939RmConfigSet/eb-list::*[1]/J1939RmChannel/eb-list::*))"!][!/*

*** Total number of Rm Nodes ***
*/!][!VAR "TotalNumberOfJ1939RmNodes" = "num:i(count(J1939RmConfigSet/eb-list::*[1]/J1939RmNode/eb-list::*))"!][!/*

*** Confirmation Timeout Value ***
*/!][!VAR "J1939RmTxConfirmationTimeoutValue" = "num:i((J1939RmGeneral/J1939RmTxConfirmationTimeout) div (J1939RmGeneral/J1939RmMainFunctionPeriod))"!][!/*

*** Supervision Timeout Value ***
*/!][!VAR "J1939RmTimeoutSupervisionValue" = "num:i(1.25 div (J1939RmGeneral/J1939RmMainFunctionPeriod))"!][!/*

*** Count the J1939RmUsers configured as COM, J1939Nm, J1939Dcm, Cdd and RTE in the J1939RM-configuration ***
*/!][!VAR "Com_count" = "'0'"!][!/*
*/!][!VAR "ComIpduRqstQueueSize" = "'0'"!][!/*
*/!][!VAR "J1939Nm_count" = "'0'"!][!/*
*/!][!VAR "J1939Dcm_count" = "'0'"!][!/*
*/!][!VAR "J1939Nm_RxIndication" = "'0'"!][!/*
*/!][!VAR "J1939Dcm_RxIndication" = "'0'"!][!/*
*/!][!VAR "Cdd_count" = "'0'"!][!/*
*/!][!VAR "Rte_count" = "'0'"!][!/*
*/!][!VAR "UserSendRequest_count" = "'0'"!][!/*
*/!][!VAR "UserSendAck_count" = "'0'"!][!/*
*/!][!VAR "UserTimeoutSupervision_count" = "'0'"!][!/*
*/!][!VAR "UserRequestIndication_count" = "'0'"!][!/*
*/!][!VAR "UserAckIndication_count" = "'0'"!][!/*
*/!][!VAR "TotalNumberOfJ1939RmUser" = "'0'"!][!/*
*/!][!VAR "J1939RmUserComIPduRequestTotal" = "'0'"!][!/*
*/!][!VAR "Tp_User" = "'0'"!][!/*
*/!][!VAR "RTE_SendAck" = "'0'"!][!/*
*/!][!VAR "RTE_AckIndication" = "'0'"!][!/*

*/!][!LOOP "(util:distinct(node:order(J1939RmConfigSet/eb-list::*[1]/J1939RmNode/eb-list::*)))"!][!/*
  */!][!LOOP "(util:distinct(node:order(J1939RmUser/eb-list::*)))"!][!/*
  */!][!IF "((node:existsAndTrue(J1939RmUserRequestIndication)) and (node:value(J1939RmUserType) = 'J1939RM_USER_J1939DCM'))"!][!/*
    */!][!VAR "J1939Dcm_RxIndication" = "$J1939Dcm_RxIndication + 1"!][!/*
  */!][!ELSEIF "((node:existsAndTrue(J1939RmUserRequestIndication)) and (node:value(J1939RmUserType) = 'J1939RM_USER_J1939NM'))"!][!/*
    */!][!VAR "J1939Nm_RxIndication" = "$J1939Nm_RxIndication + 1"!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "(node:existsAndTrue(J1939RmUserAckIndication))"!][!/*
     */!][!VAR "UserAckIndication_count" = "$UserAckIndication_count + 1"!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "(node:existsAndTrue(J1939RmUserRequestIndication))"!][!/*
     */!][!VAR "UserRequestIndication_count" = "$UserRequestIndication_count + 1"!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "(node:existsAndTrue(J1939RmUserSendRequest))"!][!/*
     */!][!VAR "UserSendRequest_count" = "$UserSendRequest_count + 1"!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "(node:existsAndTrue(J1939RmUserSendAck))"!][!/*
     */!][!VAR "UserSendAck_count" = "$UserSendAck_count + 1"!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "(node:existsAndTrue(J1939RmUserTimeoutSupervision))"!][!/*
     */!][!VAR "UserTimeoutSupervision_count" = "$UserTimeoutSupervision_count + 1"!][!/*
  */!][!ENDIF!][!/*
  */!][!VAR "TotalNumberOfJ1939RmUser" = "$TotalNumberOfJ1939RmUser + 1"!][!/*
    */!][!IF "(node:value(J1939RmUserType) = 'J1939RM_USER_CDD')"!][!/*
      */!][!VAR "Cdd_count" = "$Cdd_count + 1"!][!/*
    */!][!ELSEIF "(node:value(J1939RmUserType) = 'J1939RM_USER_COM')"!][!/*
      */!][!VAR "Com_count" = "$Com_count + 1"!][!/*
      */!][!VAR "ComIpduRqstQueueSize" = "$ComIpduRqstQueueSize + J1939RmUserComIPduRequestQueueSize"!][!/*
      */!][!LOOP "(util:distinct(node:order(J1939RmComIPdu/eb-list::*)))"!][!/*
      */!][!VAR "J1939RmUserComIPduRequestTotal" = "$J1939RmUserComIPduRequestTotal + 1"!][!/*
      */!][!IF "(node:value(ComIPduType) = 'ComIPdu_TP')"!][!/*
        */!][!VAR "Tp_User" = "$Tp_User + 1"!][!/*
      */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ELSEIF "(node:value(J1939RmUserType) = 'J1939RM_USER_J1939DCM')"!][!/*
      */!][!VAR "J1939Dcm_count" = "$J1939Dcm_count + 1"!][!/*
    */!][!ELSEIF "(node:value(J1939RmUserType) = 'J1939RM_USER_J1939NM')"!][!/*
      */!][!VAR "J1939Nm_count" = "$J1939Nm_count + 1"!][!/*
    */!][!ELSE!][!/*
      */!][!VAR "Rte_count" = "$Rte_count + 1"!][!/*
	  */!][!IF "node:existsAndTrue(J1939RmUserSendAck)"!][!/*
	    */!][!VAR "RTE_SendAck" = "$RTE_SendAck + 1"!][!/*
      */!][!ENDIF!][!/*
	  */!][!IF "node:existsAndTrue(J1939RmUserAckIndication)"!][!/*
	    */!][!VAR "RTE_AckIndication" = "$RTE_AckIndication + 1"!][!/*
      */!][!ENDIF!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*

*** Macro used for determining the size of runtime memory allocation area ***
*/!][!VAR "J1939RmAckQueueSizeTotal" = "'0'"!][!/*
*/!][!VAR "J1939RmRequestQueueSizeTotal" = "'0'"!][!/*
*/!][!VAR "J1939RmRequestTimeoutMonitorsTotal" = "'0'"!][!/*

*/!][!LOOP "(util:distinct(node:order(J1939RmConfigSet/eb-list::*)))"!][!/*
  */!][!LOOP "(util:distinct(node:order(J1939RmChannel/eb-list::*)))"!][!/*
    */!][!VAR "J1939RmAckQueueSizeTotal" = "$J1939RmAckQueueSizeTotal + J1939RmAckQueueSize"!][!/*
    */!][!VAR "J1939RmRequestQueueSizeTotal" = "$J1939RmRequestQueueSizeTotal + J1939RmRequestQueueSize"!][!/*
    */!][!VAR "J1939RmRequestTimeoutMonitorsTotal" = "$J1939RmRequestTimeoutMonitorsTotal + J1939RmRequestTimeoutMonitors"!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//