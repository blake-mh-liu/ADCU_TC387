/**
 * \file
 *
 * \brief AUTOSAR ApplTemplates
 *
 * This file contains the implementation of the AUTOSAR
 * module ApplTemplates.
 *
 * \version 6.8.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/
#include <Os.h>
#include <BswM.h>
#include <Eb_Intgr_BswM_UserCallouts.h>
#include <Fvt_Intgr_BswM_OsApp_1_UserCallouts.h>
#include <EcuM.h>

/*==================[OS resource declarations]===============================*/
DeclareTask(Init_Task);
DeclareTask(Init_Task_Core1);


/*==================[OS resource definitions]================================*/
TASK(Init_Task)
{
  EcuM_StartupTwo();  /* Task "Init_Task" has to invoke function "EcuM_StartupTwo". */

  Eb_Intgr_BswM_DriverInitTwo(); /*Driver Initialization moved to InitTask from BswM Action to comply with
                                 SwAD-ARCH-0004
                                 */
  BswM_RequestMode(EB_INTGR_BSWM_BSWM_SM, EB_INTGR_BSWM_STARTUP_TWO_A);  /* Parameter 1 refers to
                                             * BswM parameter "BswMModeRequesterId",
                                             * which belongs to mode request port "EcuM_AL_ReqPort". */
                                            /* TBD: This invocation needs to be done due
                                             * to current BswM implementation - at the moment
                                             * rules will just be evaluated within the main function
                                             * if a mode request has been initiated before.
                                             * This does not comply to the AUTOSAR specification.
                                             * Therefore an EB specific parameter will probably be
                                             * introduced that controls this behaviour.
                                             * Remove this code line and the accompayning header file
                                             * inclusion when the EB specific parameter has been
                                             * implemented. */

  (void) TerminateTask();
}


TASK(Init_Task_Core1)
{
  EcuM_StartupTwo();

  BswM_RequestMode(BSWM_OS_APP_1_BSWM_SM, EB_INTGR_BSWM_CORE1_STARTUP_TWO_A);

  (void) TerminateTask();
}

/*==================[end of file]============================================*/
