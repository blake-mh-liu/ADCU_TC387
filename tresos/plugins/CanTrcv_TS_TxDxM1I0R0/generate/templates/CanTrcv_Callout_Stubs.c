/**
 * \file
 *
 * \brief Simulated wakeup and shutdown by software
 *
 * This file contains the implementation of a simulated wakeup and shutdown
 * by Nm frame in software. Normally this is done by external hardware and its drivers.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==[Includes]================================================================*/

#include <Std_Types.h>                  /* AUTOSAR standard types        */
#include <TSAutosar.h>                  /* EB specific standard types    */
#include <CanTrcv_Callout_Stubs.h>

#include <Mcu.h>
#include <CanIf.h>
#include <CanNm.h>
#include <Nm.h>
#include <BswM.h>
#include <EcuM.h>
#include <EcuM_Int.h> /* for EcuM_SchM_Deinit() */
#include <ComM.h>
#include <ComM_BSW_Cfg.h>

/*==[Macros]=================================================================*/
#define ECUM_MODE_IGNORED 0u

/*==[Definition of functions with external linkage]===========================*/

/** \brief Simulates shutdown in software.
 *
 * Instead of real shutdown for wakeup by bus this function simulates the shutdown
 * and resets ecu on next Nm frame.
 * If Can rx interrupt is enabled function has to be called before OsShutdown,
 * e.g. instead of EcuM_GoDown. Otherwise Can_RxMainfunction has to be added in loop.
 */
FUNC(void, ECUM_APPL_CODE) CanTrcv_Callout_SimulatedShutDown(void)
{
    CanIf_ControllerModeType ControllerMode;
    CanIf_PduModeType PduMode;

    /* do same as EcuM_GoDown, except calling OsShutdown. */
    EcuM_OnGoOffOne();
    BswM_Deinit();
    EcuM_SchM_Deinit();

    /* Let CanIf receive Pdus again */
    CanIf_GetPduMode(0, &PduMode);
    if (PduMode == CANIF_OFFLINE)
    {
        CanIf_SetPduMode(0, CANIF_TX_OFFLINE);
    }

    /* enable Can controller again */
    CanIf_GetControllerMode(0, &ControllerMode);
    if ((ControllerMode == CANIF_CS_SLEEP))
    {
        CanIf_SetControllerMode(0, CANIF_CS_STOPPED);
        CanIf_SetControllerMode(0, CANIF_CS_STARTED);
    }

    /* loop MainFunctions until ComM channel state is not NO_COM anymore. Det errors may be reported if 
     * Nm frame is received due to channel state is disabled in this modules. */
    do
    {
        CanNm_MainFunction();
        Nm_MainFunction();
        ComM_MainFunction_0();
    } while(ComM_ChanState[0] == 0); 

    /* do reset for wakeup */
    for(;;)
    {
        /* instruct the EcuM to perform a reset, when EcuM_Shutdown() is called */
        EcuM_SelectShutdownTarget(ECUM_STATE_RESET, ECUM_MODE_IGNORED);
        /* shutdown the Os, the system will be shut down via EcuM_Shutdown() being called from ShutdownHook() */
        ShutdownOS(E_OK);
    }
}

/** \brief Simulates wakeup by bus in software.
 *
 * Instead of real wakeup by bus this function simulates the wakeup.
 * Replace the EcuMWakeupSource with your EcuMWakeupSource name with activated ComM
 * channel reference by your needs.
 * Call this function after ComM_Init(). Calling it before may fail depending on
 * the configuration and stack mainfunction scheduling.
 */
FUNC(void, ECUM_APPL_CODE) CanTrcv_Callout_SimulatedWakeup(void)
{
    /* Set wakeup event as real external hardware driver for wakeup by bus */
    EcuM_SetWakeupEvent(1U << EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_CAN);
}
