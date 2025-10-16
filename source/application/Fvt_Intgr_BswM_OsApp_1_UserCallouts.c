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
 * Copyright 2005 - 2023 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                  /* AUTOSAR standard types        */
#include <TSAutosar.h>                  /* EB specific standard types    */
#include <Fvt_Intgr_BswM_OsApp_1_UserCallouts.h> /* Callout function declarations */


#include <Platforms_Modules.h>          /* platform-specific config pointer
                                           names */
#include <Base_Modules.h>               /* Module enable defines and
                                           standard config pointer names */
#include <Eb_Intgr_BswM_Modules.h>      /* Init function call defines    */
#include <Eb_Intgr_Det.h>               /* Det definitions */

/*==================[macros]================================================*/
#if defined(BASE_ECUM_ENABLED)
#if (BASE_ECUM_ENABLED==STD_ON)
#ifndef ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
#define ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
#endif
#include <EcuM.h>
#endif
#endif

#if defined(BASE_BSWM_ENABLED)
#if (BASE_BSWM_ENABLED==STD_ON)
#ifndef BSWM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
#define BSWM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
#endif
#include <BswM.h>
#endif
#endif

#if defined(BASE_RTE_ENABLED)
#if (BASE_RTE_ENABLED==STD_ON)
#ifndef RTE_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
#define RTE_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
#endif
#include <Rte_Main.h>
#endif
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/*------------------[User callouts]------------------------------------------*/
FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnStartupTwoA(void)
{
  BswM_RequestMode(BSWM_OS_APP_1_BSWM_SM, EB_INTGR_BSWM_CORE1_STARTUP_TWO_B);
}

FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnStartupTwoB(void)
{
  BswM_RequestMode(BSWM_OS_APP_1_BSWM_SM, EB_INTGR_BSWM_CORE1_RUN_TWO);
}

FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnRunTwo(void)
{
#if defined(BASE_RTE_ENABLED)
#if (BASE_RTE_ENABLED==STD_ON)
#if 1
/* When compile the final demo application, remove enclosing "#if 1", "#endif"
 * preprocessor statements.
 *
 * Reason:
 * Within the basicTemplate itself the RteGeneratorOutput is set to BSW_SCHEDULER_ONLY
 * and hence no Rte_Start(), Rte_Stop() are generated/provided.
 *
 * But during demo application configuration the RteGeneratorOutput is set to FULL mode
 * and Rte_Start(), Rte_Stop() are generated/provided and have to be called by the application.
*/
  /* ComM_RequestComMode( 0, COMM_FULL_COMMUNICATION );
  ComM_CommunicationAllowed(0,TRUE); */
  if ( Rte_Start() != E_OK )
  {
    /* Rte start failed */
  }
#endif /* 0 */
#endif
#endif
}

FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnPrpShutdown(void)
{
  /* Do all activities here which shall be done right before the shutdown */

  EcuM_StateType shutdownTarget;
  uint8 sleepMode;

  EcuM_GetShutdownTarget(&shutdownTarget, &sleepMode);

  if (ECUM_STATE_OFF == shutdownTarget)
  {
    BswM_RequestMode(BSWM_OS_APP_1_BSWM_SM, EB_INTGR_BSWM_CORE1_GO_OFF_ONE_A);
  }
  else if (ECUM_STATE_SLEEP == shutdownTarget)
  {
    EcuM_GoPoll();
  }
  else if (ECUM_STATE_RESET == shutdownTarget)
  {
    /* Insert your code here. */
  }
  else
  {
    /* Insert your code here. */
  }
}

FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnGoOffOneA(void)
{
#if 1
/* When compile the final demo application, remove enclosing "#if 1", "#endif"
 * preprocessor statements.
 *
 * Reason:
 * Within the basicTemplate itself the RteGeneratorOutput is set to BSW_SCHEDULER_ONLY
 * and hence no Rte_Start(), Rte_Stop() are generated/provided.
 *
 * But during demo application configuration the RteGeneratorOutput is set to FULL mode
 * and Rte_Start(), Rte_Stop() are generated/provided and have to be called by the application.
*/
#if defined(BASE_RTE_ENABLED)
#if (BASE_RTE_ENABLED==STD_ON)
  if ( Rte_Stop() != E_OK )
  {
    /* failed to stop the Rte */
  }
#endif
#endif
#endif /* 0 */

  /* directly request BSWM_GO_OFF_ONE_B */
  BswM_RequestMode(BSWM_OS_APP_1_BSWM_SM, EB_INTGR_BSWM_CORE1_GO_OFF_ONE_B);
}

FUNC(void, BSWM_APPL_CODE) BswM_OsApp_1_OnGoOffOneB(void)
{
  (void) EcuM_GoDown(BSWM_MODULE_ID);
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>


/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
