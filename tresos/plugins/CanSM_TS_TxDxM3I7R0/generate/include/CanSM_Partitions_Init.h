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

#ifndef CANSM_PARTITIONS_INIT_H
#define CANSM_PARTITIONS_INIT_H

/*==================[inclusions]============================================*/

#include <ComStack_Types.h>    /* AUTOSAR communication stack types */

/*==================[macros]================================================*/

[!IF "($ChannelsDistributionSupport = 'true')"!][!/*
  */!][!IF "$ChannelsInitDistributionSupport = 'true'"!][!/*
    */!][!VAR "CANSM_EcuC_Partition"="'false'"!][!/*
    */!][!LOOP "(util:distinct(node:order(as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*)))"!][!/*
      */!][!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!/*
        */!][!VAR "CANSM_EcuC_Partition"="'true'"!][!/*
        */!][!BREAK!][!/*
      */!][!ENDIF!][!/*
    */!][!ENDLOOP!][!/*
    */!][!IF "($CANSM_EcuC_Partition = 'true')"!][!/*
    */!][!LOOP "as:modconf('EcuC')[1]/EcucPartitionCollection/EcucPartition/*"!][!/*
      */!][!VAR "EcuC_Partition_Referenced"="'false'"!][!/*
      */!][!VAR "PartitionName" = "as:name(.)"!][!/*
      */!][!LOOP "as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*"!][!/*
        */!][!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!/*
          */!][!IF "($PartitionName = as:name(as:ref(as:ref(CanSMComMNetworkHandleRef)/ComMChannelPartitionRef))) and ($EcuC_Partition_Referenced = 'false')"!][!/*
            */!][!VAR "EcuC_Partition_Referenced"="'true'"!]
#if (defined CanSM_Init[!"$PartitionName"!])      /* To prevent double declaration */
#error CanSM_Init_[!"$PartitionName"!] already defined!
#endif /* #if (defined CanSM_Init_[!"$PartitionName"!]) */
#define CanSM_Init_[!"$PartitionName"!](x)  CanSM_1_[!"$PartitionName"!]_Init_[!"$PartitionName"!](x)

[!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDLOOP!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDIF!]

/*==================[type definitions]======================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function declarations]========================*/

[!IF "($ChannelsDistributionSupport = 'true')"!][!/*
  */!][!IF "$ChannelsInitDistributionSupport = 'true'"!][!/*
    */!][!VAR "CANSM_EcuC_Partition"="'false'"!][!/*
    */!][!LOOP "(util:distinct(node:order(as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*)))"!][!/*
      */!][!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!/*
        */!][!VAR "CANSM_EcuC_Partition"="'true'"!][!/*
        */!][!BREAK!][!/*
      */!][!ENDIF!][!/*
    */!][!ENDLOOP!][!/*
    */!][!IF "($CANSM_EcuC_Partition = 'true')"!][!/*
      */!][!LOOP "as:modconf('EcuC')[1]/EcucPartitionCollection/EcucPartition/*"!][!/*
        */!][!VAR "EcuC_Partition_Referenced"="'false'"!][!/*
        */!][!VAR "PartitionName" = "as:name(.)"!][!/*
        */!][!LOOP "as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*"!][!/*
          */!][!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!/*
            */!][!IF "($PartitionName = as:name(as:ref(as:ref(CanSMComMNetworkHandleRef)/ComMChannelPartitionRef))) and ($EcuC_Partition_Referenced = 'false')"!][!/*
              */!][!VAR "EcuC_Partition_Referenced"="'true'"!]
#define CANSM_1_[!"$PartitionName"!]_START_SEC_CODE
#include <CanSM_1_[!"$PartitionName"!]_MemMap.h>

/** \brief Initializes the CanSM module.
 **
 ** This function initializes the CanSM module. It is the first
 ** function called in CanSM.
 **
 ** \param[in] ConfigPtr Pointer to init structure for the post-build
 **                      configuration parameters of the CanSM. This parameter
 **                      is ignored because post-build configuration is not
 **                      supported. Please use NULL_PTR as parameter for the
 **                      initialization.
 **
 ** \ServiceID{0}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANSM_CODE) CanSM_1_[!"$PartitionName"!]_Init_[!"$PartitionName"!] (
  P2CONST( CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST ) ConfigPtr
);

#define CANSM_1_[!"$PartitionName"!]_STOP_SEC_CODE
#include <CanSM_1_[!"$PartitionName"!]_MemMap.h>

[!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDLOOP!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDIF!]


#endif
/*==================[end of file]===========================================*/

[!ENDCODE!]