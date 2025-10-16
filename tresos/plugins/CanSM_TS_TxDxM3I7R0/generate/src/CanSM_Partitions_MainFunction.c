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

[!CODE!][!//
[!INCLUDE "../../generate_macros/CanSM_Macros.m"!][!//

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 */

/*==================[inclusions]============================================*/

#include <CanSM_Trace.h>
#include <ComStack_Types.h>         /* AUTOSAR communication stack types */

#include <CanSM_Int_Stc.h>          /* Module internal static header */
#include <CanSM_Cfg.h>              /* Module configuration */
#include <CanSM_Partitions_MainFunction.h>
#include <CanSM_Internal.h>         /* Module private API */
[!IF "$multiCoreSupport = 'true'"!][!//
#include <SchM_CanSM.h>
[!ENDIF!][!//

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/
  /* !LINKSTO CanSM.EB.CanSMDistributedChannels_MainFunctions_Processing,1 */
[!IF "($ChannelsDistributionSupport = 'true')"!][!//
  [!VAR "CANSM_EcuC_Partition"="'false'"!][!//
  [!LOOP "(util:distinct(node:order(as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*)))"!][!//
    [!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!//
      [!VAR "CANSM_EcuC_Partition"="'true'"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "($CANSM_EcuC_Partition = 'true')"!][!//
    [!LOOP "as:modconf('EcuC')[1]/EcucPartitionCollection/EcucPartition/*"!][!//
      [!VAR "EcuC_Partition_Referenced"="'false'"!][!//
      [!VAR "PartitionName" = "as:name(.)"!][!//
      [!LOOP "as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*"!][!//
        [!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!//
          [!IF "($PartitionName = as:name(as:ref(as:ref(CanSMComMNetworkHandleRef)/ComMChannelPartitionRef))) and ($EcuC_Partition_Referenced = 'false')"!][!//
            [!VAR "EcuC_Partition_Referenced"="'true'"!][!//
#define CANSM_1_[!"$PartitionName"!]_START_SEC_CODE
#include <CanSM_1_[!"$PartitionName"!]_MemMap.h>

FUNC(void, CANSM_CODE) CanSM_1_[!"$PartitionName"!]_MainFunction_[!"$PartitionName"!] (
  void
)
{
  CanSM_NetworkIndexType nw;

  DBG_CANSM_MAINFUNCTION_ENTRY();

  if (CanSM_GlobalInit == CANSM_GLOBAL_INIT)
  {
    /* Deviation TASKING-1 */
    for ( nw=0U; nw<CANSM_NETWORKS_NUM; nw++ )
    {
      if (CANSM_NW_INFO_PARTITIONID(nw) == [!"text:toupper($PartitionName)"!]_ID)
      {
        CanSM_MainFunctionInternal(nw);
      }
    } /* loop over networks */
  } /* else of ( CanSM_GlobalInit == CANSM_GLOBAL_UNINIT ) */

  DBG_CANSM_MAINFUNCTION_EXIT();
}

#define CANSM_1_[!"$PartitionName"!]_STOP_SEC_CODE
#include <CanSM_1_[!"$PartitionName"!]_MemMap.h>

[!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDLOOP!][!/*Partitions loop
  */!][!ENDIF!][!/*
*/!][!ENDIF!][!//


/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
[!ENDCODE!]

