[!AUTOSPACING!]
#ifndef STBM_CFG_H
#define STBM_CFG_H

/**
 * \file
 *
 * \brief AUTOSAR StbM
 *
 * This file contains the implementation of the AUTOSAR
 * module StbM.
 *
 * \version 5.0.9
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/** \addtogroup Synchronized Time Base Manager
 ** @{ */

/*==[Includes]================================================================*/

#include <StbM_Gen_Common.h>

[!INCLUDE "StbM_Vars.m"!]
/* include Rte_StbM_Type.h file before the StbM_Types.h file inclusion,
   in order to assure that re-definitions of StbM types in case Non-EB Rte is used, will not happen */
#if (STBM_RTE_USED == STD_ON)
[!LOOP "text:split($ListOfEcucPartitionNames, ';')"!]
[!VAR "EcuCPartitionName" = "."!]
[!IF "$EcuCPartitionName = '_NoPartition'"!]
  [!VAR "EcuCPartitionName" = "''"!]
[!ENDIF!]
#include <Rte_StbM[!"$EcuCPartitionName"!]_Type.h>
[!ENDLOOP!]
#endif /* STBM_RTE_USED == STD_ON */

/*==[Macros]==================================================================*/

#if (defined STBM_VERSION_INFO_API)
#error STBM_VERSION_INFO_API is already defined.
#endif
/** \brief Enables/Disables the StbM_GetVersionInfo API. */
#define STBM_VERSION_INFO_API                     STD_[!IF "StbMGeneral/StbMVersionInfoApi = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Definitions of symbolic names for all the synchronized (time base id < 16) and offset
 ** (time base id >= 16) time base identifiers */
[!LOOP "util:distinct(node:order(as:modconf('StbM')[1]/StbMSynchronizedTimeBase/*, './StbMSynchronizedTimeBaseIdentifier'))"!]
  [!VAR "prefix" = "string('StbMConf_StbMSynchronizedTimeBase_')"!]
  [!VAR "timeBaseId" = "num:i(node:value(StbMSynchronizedTimeBaseIdentifier))"!]
  [!VAR "timeBaseName" = "as:name(.)"!]
  [!VAR "define1" = "concat($prefix, $timeBaseName)"!]
  [!VAR "define2" = "concat($define1, string('  '))"!]
  [!VAR "define3" = "concat($define2, $timeBaseId)"!]
#define [!"$define3"!]U
[!ENDLOOP!]

/** \brief Definitions of symbolic names for all the Notification Customers */
[!LOOP "as:modconf('StbM')[1]/StbMSynchronizedTimeBase/*/StbMNotificationCustomer/*"!]
  [!VAR "prefix" = "string('StbMConf_StbMNotificationCustomer_')"!]
  [!VAR "customerId" = "num:i(node:value(StbMNotificationCustomerId))"!]
  [!VAR "customerName" = "as:name(.)"!]
  [!VAR "define1" = "concat($prefix, $customerName)"!]
  [!VAR "define2" = "concat($define1, string('  '))"!]
  [!VAR "define3" = "concat($define2, $customerId)"!]
#define [!"$define3"!]U
[!ENDLOOP!]


/** \brief Definitions of symbolic names for all the StbM freshness values */
[!LOOP "util:distinct(node:order(as:modconf('StbM')[1]/StbMFreshnessValueInformation/StbMFreshnessValue/*))"!]
  [!VAR "prefix" = "string('StbMConf_StbMFreshnessValue_')"!]
  [!VAR "freshnessValueId" = "num:i(node:value(StbMFreshnessValueId))"!]
  [!VAR "freshnessValueName" = "as:name(.)"!]
  [!VAR "define1" = "concat($prefix, $freshnessValueName)"!]
  [!VAR "define2" = "concat($define1, string('  '))"!]
  [!VAR "define3" = "concat($define2, $freshnessValueId)"!]
#define [!"$define3"!]U
[!ENDLOOP!]


/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/** @} doxygen end group definition */
/*==================[end of file]===========================================*/


#endif /* ifndef STBM_CFG_H */
