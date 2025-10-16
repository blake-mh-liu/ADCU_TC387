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

#include "Rte_SWC_CyclicCounter.h"

#include <BswM.h>                       /* BswM API */
#include <Eb_Intgr_BswM_UserCallouts.h>          /* Callout function declarations */
#include <Base_Modules.h>               /* Module enable defines and
                                           standard config pointer names */
#include <WdgM.h>                       /* AUTOSAR WdgM                             */

#ifdef _X86_
#include <stdio.h>
#include <Os.h>
#endif

#define RTE_START_SEC_APPL_CODE
#include "MemMap.h"

FUNC(void, RTE_APPL_CODE) SWC_CyclicCounter_Init(void)
{
  uint8 counterValue = 0U;

  /* Read counter value from per-instance memory
     which is configured as RAM mirror for an
     NvM block */
  counterValue = *Rte_Pim_PimCounterValue();

  /* Write counter value to inter-runnable variable */
  Rte_IrvWrite_Cyclic_CurrentCounterValue(counterValue);
}

FUNC(void, RTE_APPL_CODE) SWC_CyclicCounter_Shutdown(void)
{
  uint8 counterValue = 0U;

  /* update the RAM mirror */
  counterValue = Rte_IrvRead_Cyclic_CurrentCounterValue();
  (*Rte_Pim_PimCounterValue()) = counterValue;

  /* and mark block as modified */
  (void) Rte_Call_PS_PersistentCounterValue_SetRamBlockStatus(TRUE);

}

FUNC(void, RTE_APPL_CODE) SWC_CyclicCounter_Cyclic(void)
{
  uint8 counterValue = 0U;
  uint8 specialReceiveCommands[10] = { 0U };
  uint8 i = 0U;
  boolean specialReceiveCommand = FALSE;

  WdgM_CheckpointReached
  (
      WdgMConf_WdgMSupervisedEntity_WdgMSupervisedLogical,
      WdgMConf_WdgMCheckpoint_WdgMCheckpoint_0_SWC_CyclicCounter_Cyclic
  );
  
  /* get all special commands received since last run */
  while(Rte_Receive_R_SpecialHandling_EventMessage(&specialReceiveCommands[0]) == E_OK)
  {
    /* save all requests in an temp array, can be used for later processing */
    if(i >= sizeof(specialReceiveCommands)) break;
    specialReceiveCommands[sizeof(specialReceiveCommands) - i - 1U]=specialReceiveCommands[0];


    if (specialReceiveCommands[i] == 0xf1)
    {
#ifdef _X86_
    {
        os_intstatus_t intValue = OS_WINDOWSGoingToUseWindowsService();
        /* Print counter value to standard out */
        printf("Received trigger Det command 0xF1\n");
        OS_WINDOWSFinishedUsingWindowsService(intValue);
    }
#endif
      /* special command for generating pseudo det error */
      (void) Rte_Call_R_CyclicCounterDet_ReportError(1U,2U,3U);
      specialReceiveCommand = TRUE;
    }
    i++;
  }

  /* don't handle counter values which are special commands */
  if (!specialReceiveCommand)
  {
    /* Read counter value from inter-runnable variable */
     counterValue = Rte_IrvRead_Cyclic_CurrentCounterValue();

    /* toggle LED */
    if ((counterValue % 2U) == 0U)
    {
      (void) Rte_Call_R_MyLED_SetDiscreteValue(1U);
    }
    else
    {
      (void) Rte_Call_R_MyLED_SetDiscreteValue(0U);
    }

    /* Write incremented counter value to inter-runnable variable */
    Rte_IrvWrite_Cyclic_CurrentCounterValue(counterValue + 1U);

#ifdef _X86_
    {
        os_intstatus_t intValue = OS_WINDOWSGoingToUseWindowsService();
        /* Print counter value to standard out */
        printf("Counter: %d\n", counterValue);
        OS_WINDOWSFinishedUsingWindowsService(intValue);
    }
#endif

    /* Write current counter value */
    (void) Rte_Write_P_CounterOut_CounterValue(counterValue);
  }
}


FUNC(void, RTE_APPL_CODE) SWC_CyclicCounter_SetCounter
(
uint8 newCounterValue,
P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) returnSum
)
{
    uint8 currentCounter = 0U;

    /* read actual cyclic counter value */
    currentCounter = Rte_IrvRead_SetCounter_CurrentCounterValue();

    /* replace the current counter value with new */
    Rte_IrvWrite_SetCounter_CurrentCounterValue(newCounterValue);

    /* return the sum */
    *returnSum = currentCounter + newCounterValue;
}

FUNC(void, RTE_APPL_CODE) SWC_CyclicCounter_SetCounter_FD
(
uint8 newCounterValue,
P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) returnSum
)
{
    uint8 currentCounter = 0U;

    /* read actual cyclic counter value */
    currentCounter = Rte_IrvRead_SetCounter_FD_CurrentCounterValue_FD();

    /* replace the current counter value with new */
    Rte_IrvWrite_SetCounter_FD_CurrentCounterValue_FD(newCounterValue);

    /* return the sum */
    *returnSum = currentCounter + newCounterValue;
}

FUNC(void, RTE_APPL_CODE) SWC_CyclicCounter_Cyclic_FD(void)
{
  uint8 counterValue = 0U;


    /* Read counter value from inter-runnable variable */
     counterValue = Rte_IrvRead_Cyclic_FD_CurrentCounterValue_FD();


    /* Write incremented counter value to inter-runnable variable */
    Rte_IrvWrite_Cyclic_FD_CurrentCounterValue_FD(counterValue + 1U);


    /* Write current counter value */
    (void) Rte_Write_P_CounterOut_FD_CounterValue_FD(counterValue);

}



#define RTE_STOP_SEC_APPL_CODE
#include "MemMap.h"
