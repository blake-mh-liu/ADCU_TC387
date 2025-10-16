/**
 * \file
 *
 * \brief AUTOSAR Rte
 *
 * This file contains the implementation of the AUTOSAR
 * module Rte.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2018 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/*
 * \addtogroup Rte Runtime Environment
 * @{
 */

/* ==================[Includes]=============================================== */
#include <Rte_SWC_AppStateHandler.h>

/* ==================[Definition of functions with external linkage]========== */
/* ------------------------[runnable entity skeletons]------------------------ */
FUNC(void, RTE_CODE) App_StateHandler (void)
{
  AppStateModeRequestType reqMode;
  uint8 currentMode;

  reqMode = Rte_IRead_Runable_StateHandler_AppStateRequest_If_AppStateRequestMode();
  currentMode = Rte_Mode_AppState_AppStateMode();
  switch(reqMode)
  {
     case EB_INTGR_APP_STARTUP:
        
           (void)Rte_Switch_AppState_AppStateMode(RTE_MODE_AppStateModeGroup_EB_INTGR_APP_STARTUP);
        
        break;
     case EB_INTGR_APP_ACTIVE:
        
			(void)Rte_Switch_AppState_AppStateMode(RTE_MODE_AppStateModeGroup_EB_INTGR_APP_ACTIVE);

        break;
     case EB_INTGR_APP_INACTIVE:
        
           (void)Rte_Switch_AppState_AppStateMode(RTE_MODE_AppStateModeGroup_EB_INTGR_APP_INACTIVE);
        
        break;
     default:
        break;
  }
  
} /* FUNC(void, RTE_CODE) App_StateHandler (void) */

/*
  ------------------------[runnable-independent API]-------------------------

  Copy and paste the following API to those runnable entity functions where
  you want to use them.

  ------------------------[port handle API]----------------------------------
  ------------------------[per instance memory API]--------------------------
 */

/** @} doxygen end group definition  */
/* ==================[end of file]============================================ */
