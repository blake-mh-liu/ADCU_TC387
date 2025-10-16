/**
 * \file
 *
 * \brief AUTOSAR CanSM
 *
 * This file contains the implementation of the AUTOSAR
 * module CanSM.
 *
 * \version 3.7.21
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!CODE!]
[!INCLUDE "../../generate_macros/CanSM_Macros.m"!][!//
[!AUTOSPACING!]

#ifndef CANSM_PARTITIONS_MINFUNCTION_H
#define CANSM_PARTITIONS_MINFUNCTION_H

 /* mgcc62 Deviation List
 *
 * MGCC62-1) Deviated Rule: redundant-decls
 * warning: redundant redeclaration of 'CanSM_MainFunction' [-Wredundant-decls]
 *
 * Reason:
 * MainFunction needs to be exported through <module>_SchM.h for Rte usage.
 * Rte also exports the function in SchM_<module>.h, redeclaring the function.
 */

/*==================[inclusions]============================================*/

#include <ComStack_Types.h>    /* AUTOSAR communication stack types */

/*==================[macros]================================================*/
/* !LINKSTO CanSM.EB.CanSMDistributedChannels_MainFunctions,1 */
[!IF "($ChannelsDistributionSupport = 'true')"!]

  [!VAR "CANSM_EcuC_Partition"="'false'"!]
  [!LOOP "(util:distinct(node:order(as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*)))"!]
    [!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!]
      [!VAR "CANSM_EcuC_Partition"="'true'"!]
      [!BREAK!]
    [!ENDIF!]  
  [!ENDLOOP!]

  [!IF "($CANSM_EcuC_Partition = 'true')"!]
    [!LOOP "as:modconf('EcuC')[1]/EcucPartitionCollection/EcucPartition/*"!]
    [!VAR "EcuC_Partition_Referenced"="'false'"!]
      [!VAR "PartitionName" = "as:name(.)"!]
      [!LOOP "as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*"!]
        [!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!]
          [!IF "($PartitionName = as:name(as:ref(as:ref(CanSMComMNetworkHandleRef)/ComMChannelPartitionRef))) and ($EcuC_Partition_Referenced = 'false')"!]
            [!VAR "EcuC_Partition_Referenced"="'true'"!]
#define CanSM_MainFunction_[!"$PartitionName"!]() CanSM_1_[!"$PartitionName"!]_MainFunction_[!"$PartitionName"!]()
          [!ENDIF!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!][!//Partitions loop
  [!ENDIF!]
[!ENDIF!]

/*==================[type definitions]======================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function declarations]========================*/

[!IF "($ChannelsDistributionSupport = 'true')"!]

  [!VAR "CANSM_EcuC_Partition"="'false'"!]
  [!LOOP "(util:distinct(node:order(as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*)))"!]
    [!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!]
      [!VAR "CANSM_EcuC_Partition"="'true'"!]
      [!BREAK!]
    [!ENDIF!]  
  [!ENDLOOP!]

  [!IF "($CANSM_EcuC_Partition = 'true')"!]
    [!LOOP "as:modconf('EcuC')[1]/EcucPartitionCollection/EcucPartition/*"!]
    [!VAR "EcuC_Partition_Referenced"="'false'"!]
      [!VAR "PartitionName" = "as:name(.)"!]
      [!LOOP "as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*"!]
        [!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!]
          [!IF "($PartitionName = as:name(as:ref(as:ref(CanSMComMNetworkHandleRef)/ComMChannelPartitionRef))) and ($EcuC_Partition_Referenced = 'false')"!]
            [!VAR "EcuC_Partition_Referenced"="'true'"!]
#define CANSM_1_[!"$PartitionName"!]_START_SEC_CODE
#include <CanSM_1_[!"$PartitionName"!]_MemMap.h>
/** \brief This function handles asynchronous events, such as mode changes.
**
** This is the CanSM_MainFunction_[!"$PartitionName"!].
** It handles asynchronous events, such as mode changes. It is called cyclically with a fixed period
** from the BSW Scheduler, it handles the main function related processing for the channels that have [!"$PartitionName"!] configured
**
*/
/* Deviation MGCC62-1 */
extern FUNC(void, CANSM_CODE) CanSM_1_[!"$PartitionName"!]_MainFunction_[!"$PartitionName"!] (
  void
);
#define CANSM_1_[!"$PartitionName"!]_STOP_SEC_CODE
#include <CanSM_1_[!"$PartitionName"!]_MemMap.h>
          [!ENDIF!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!][!//Partitions loop
  [!ENDIF!]
[!ENDIF!]


#endif
/*==================[end of file]===========================================*/

[!ENDCODE!]