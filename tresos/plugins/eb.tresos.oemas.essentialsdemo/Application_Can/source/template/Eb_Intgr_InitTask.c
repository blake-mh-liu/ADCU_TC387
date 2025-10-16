/**
 * \file
 *
 * \brief AUTOSAR ApplTemplates
 *
 * This file contains the implementation of the AUTOSAR
 * module ApplTemplates.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/
#include <Os.h>
#include <BswM.h>
#include <Eb_Intgr_BswM_UserCallouts.h>
#include <EcuM.h>

/*==================[OS resource declarations]===============================*/
DeclareTask(Init_Task);


/*==================[OS resource definitions]================================*/
TASK(Init_Task)
{
  EcuM_StartupTwo();  /* Task "Init_Task" has to invoke function "EcuM_StartupTwo". */

  /* !LINKSTO SwAD-ARCH-0004,1 */
  Eb_Intgr_BswM_DriverInitTwo(); /*Driver Initialization moved to InitTask from BswM Action to comply with
                                 SwAD-ARCH-0004
                                 */

  BswM_RequestMode(EB_INTGR_BSWM_BSWM_SM, EB_INTGR_BSWM_STARTUP_TWO_A);  /* Parameter 1 refers to
                                             * BswM parameter "BswMModeRequesterId",
                                             * which belongs to mode request port "EcuM_AL_ReqPort". */
  (void) TerminateTask();
}


/*==================[end of file]============================================*/
