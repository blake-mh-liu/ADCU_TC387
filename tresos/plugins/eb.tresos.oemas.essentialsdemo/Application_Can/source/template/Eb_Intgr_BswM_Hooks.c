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
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                  /* AUTOSAR standard types        */
#include <TSAutosar.h>                  /* EB specific standard types    */
#include <Eb_Intgr_BswM_Hooks.h>        /* Callout function declarations */


/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define BSWM_START_SEC_CODE
#include <MemMap.h>

/*------------------[User callouts]------------------------------------------*/

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnStartupTwoA(void)
{

}

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnStartupTwoB(void)
{

}

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnPrpShutdown(void)
{

}

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnGoOffOneA(void)
{

}

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnGoOffOneB(void)
{

}

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnRunTwo(void)
{

}

FUNC(void, BSWM_APPL_CODE) Eb_Intgr_BswM_Hook_OnPostRun(void)
{

}

#define BSWM_STOP_SEC_CODE
#include <MemMap.h>


/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
