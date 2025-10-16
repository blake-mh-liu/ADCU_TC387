/**
 * \file
 *
 * \brief AUTOSAR Workflows
 *
 * This file contains the implementation of the AUTOSAR
 * module Workflows.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#include "Rte_SWC_IoHwAbs.h"

#ifdef _X86_
#include <stdio.h>
#include <Os.h>
#define DioConf_DioChannel_MY_LED_CYCLIC 0U
#define Dio_ChannelType uint32
#else
#include "Dio.h"
#include <WdgM.h>                       /* AUTOSAR WdgM                             */
#endif


#define RTE_START_SEC_VAR_UNSPECIFIED
#include <MemMap.h>

STATIC Dio_ChannelType SetPortArgToChannel[1] = {DioConf_DioChannel_MY_LED_CYCLIC};

#define RTE_STOP_SEC_VAR_UNSPECIFIED
#include <MemMap.h>


#define RTE_START_SEC_APPL_CODE
#include "MemMap.h"

FUNC(void, RTE_APPL_CODE) SWC_IoHwAbs_SetDiscreteValue (uint32 val0, uint32 value)
{
#ifdef _X86_
  {
      os_intstatus_t intValue = OS_WINDOWSGoingToUseWindowsService();
      /* Print Dio channel */
      printf("Dio channel %d: %d\n",SetPortArgToChannel[val0], value);
      OS_WINDOWSFinishedUsingWindowsService(intValue);
  }
#else
  WdgM_CheckpointReached
  (
      WdgMConf_WdgMSupervisedEntity_WdgMSupervisedLogical,
      WdgMConf_WdgMCheckpoint_WdgMCheckpoint_1_SWC_IoHwAbs_SetDiscreteValue
  );
  
 
  /* write to Dio channel */
  Dio_WriteChannel(SetPortArgToChannel[val0], (Dio_LevelType) value);
#endif
}

#define RTE_STOP_SEC_APPL_CODE
#include "MemMap.h"
