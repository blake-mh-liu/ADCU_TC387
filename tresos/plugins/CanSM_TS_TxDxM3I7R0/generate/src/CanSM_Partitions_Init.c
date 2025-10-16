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
#include <TSAutosar.h>              /* EB specific standard types */
#include <ComStack_Types.h>         /* AUTOSAR communication stack types */
#include <CanSM_PBcfg.h>            /* Module post-build generated configuration */
#include <CanSM_Api_Static.h>       /* Module public API */
#include <CanSM_Cfg.h>              /* Module generated configuration */
#include <CanSM_Internal.h>         /* Module internal */
#include <ComM.h>                   /* ComM_ModeType */
[!IF "($ChannelsDistributionSupport = 'true')"!][!/*
*/!][!IF "$ChannelsInitDistributionSupport = 'true'"!]
#include <CanSM_Partitions_Init.h>
[!ENDIF!][!/*
*/!][!ENDIF!]
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/
  /* !LINKSTO CanSM.EB.CanSMDistributedChannelInit_InitFunctions,1 */
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

FUNC(void, CANSM_CODE) CanSM_1_[!"$PartitionName"!]_Init_[!"$PartitionName"!] (
  P2CONST( CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST ) ConfigPtr
)
{
  CanSM_NetworkIndexType nw;

  P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST) LocalConfigPtr = ConfigPtr;

  DBG_CANSM_INIT_ENTRY(ConfigPtr);

#if (CANSM_DEV_ERROR_DETECT == STD_ON)
  /* check whether parameter LocalConfigPtr is a NULL_PTR */
  if (LocalConfigPtr == NULL_PTR)
  {
    /* found a NULL_PTR, report to DET */
    CANSM_DET( CANSM_SID_INIT,
               CANSM_E_PARAM_POINTER
             );
  }
  else
#endif /* CANIF_DEV_ERROR_DETECT */
  {
    CANSM_INIT_SPIN_LOCKED_WAIT(CanSM_InitInProgress,(Atomic_value_t)0x1U);
    if(CanSM_MultiCoreInitCount == 0U)
    {
      /* !LINKSTO CanSM.EB.CanSMDistributedChannels_InitFunctions_Initialization,1 */
      /* set global configuration pointer */
      CanSM_ConfigPtr = LocalConfigPtr;

      /* Deviation TASKING-1 */
      for ( nw=0U; nw<CANSM_NETWORKS_NUM; nw++)
      {
        CANSM_NW_INFO_STATE(nw) = CANSM_UNINITED;
        CANSM_NW_INFO_INTERNALSTATE(nw) = CANSM_S_NOIN;
        CANSM_NW_INFO_REQCOMMODE(nw) = COMM_NO_COMMUNICATION;
        CANSM_NW_INFO_TRANSITION_ONGOING(nw) = FALSE;
        CANSM_NW_INFO_PARTITIONID(nw) = CanSM_PartitionID[nw];
      }

      CanSM_GlobalInit = CANSM_GLOBAL_INIT;
    } /* CanSM_MultiCoreInitCount == 0U */

    CanSM_MultiCoreInitCount++;
    if(CanSM_MultiCoreInitCount >= CANSM_MULTI_INIT_COUNT)
    {
      /* !LINKSTO CanSM.EB.CanSMDistributedChannels_InitFunctions_Re_Init,1 */
      CanSM_MultiCoreInitCount = 0;
    }
    Atomics_ClearFlag(&CanSM_InitInProgress,(Atomic_value_t)0x1U);

    /* Deviation TASKING-1 */
    for ( nw=0U; nw<CANSM_NETWORKS_NUM; nw++)
    {
      /* !LINKSTO CanSM.EB.CanSMDistributedChannels_InitFunctions_StateTransition,1 */
      if(CANSM_NW_INFO_PARTITIONID(nw) == [!"text:toupper($PartitionName)"!]_ID)
      {
        CanSM_DoTransitionSequence(nw, CANSM_T_RNOCO_INITIAL, FALSE);
      }
      else
      {
        /* Nothing to do, this nw will be handled in another Init function at another partition */
      }
    }
  }

  DBG_CANSM_INIT_EXIT(ConfigPtr);

}

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

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
[!ENDCODE!]

