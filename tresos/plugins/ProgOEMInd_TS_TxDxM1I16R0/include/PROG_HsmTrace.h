#ifndef PROG_HSMTRACE_H
#define PROG_HSMTRACE_H
/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG_Hsm layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_HsmTrace.h                    */
/*%%  |                             |  %%  \brief Prog_Hsm trace                     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.16.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

#define DBG_PROG_GENERIC_GRP(startChartId, instIdx, oldState, stateId) \
    {TS_PARAM_UNUSED(oldState);}

#define DBG_PROG_HSMINIT_ENTRY(sc)

#define DBG_PROG_HSMINIT_EXIT(sc)

#define DBG_PROG_HSMINITINST_ENTRY(sc, instIdx)

#define DBG_PROG_HSMINITINST_EXIT(sc, instIdx)

#define DBG_PROG_HSMEMIT_ENTRY(sc, event)

#define DBG_PROG_HSMEMIT_EXIT(sc, event)

#define DBG_PROG_HSMEMITINST_ENTRY(sc, instIdx, event)

#define DBG_PROG_HSMEMITINST_EXIT(sc, instIdx, event)

#define DBG_PROG_HSMEMITTOSELFINST_ENTRY(sc, instIdx, event)

#define DBG_PROG_HSMEMITTOSELFINST_EXIT(sc, instIdx, event)

#define DBG_PROG_HSMMAININST_ENTRY(sc, instIdx)

#define DBG_PROG_HSMMAININST_EXIT(transitionFired, sc, instIdx)

#define DBG_PROG_HSMSETTRACING_ENTRY(newValue)

#define DBG_PROG_HSMSETTRACING_EXIT(newValue)

#define DBG_PROG_HSM_DEL_FROM_QUEUE_ENTRY(sc, instIdx, queueEntryNo)

#define DBG_PROG_HSM_DEL_FROM_QUEUE_EXIT(sc, instIdx, queueEntryNo)

#define DBG_PROG_HSM_TRAN_ENTRY(sc, instIdx, tran)

#define DBG_PROG_HSM_TRAN_EXIT(sc, instIdx, tran)

#define DBG_PROG_HSM_INIT_SUBSTATES_ENTRY(sc, instIdx)

#define DBG_PROG_HSM_INIT_SUBSTATES_EXIT(sc, instIdx)

#define DBG_PROG_HSM_FIND_EV_TO_DISPATCH_ENTRY(sc, instIdx, event, queueEntryNo)

#define DBG_PROG_HSM_FIND_EV_TO_DISPATCH_EXIT(foundEventToDispatch, sc, instIdx, event, queueEntryNo)

#define DBG_PROG_HSM_DISPATCH_EVENT_ENTRY(sc, instIdx, event)

#define DBG_PROG_HSM_DISPATCH_EVENT_EXIT(transitionFired, sc, instIdx, event)


/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

#endif

