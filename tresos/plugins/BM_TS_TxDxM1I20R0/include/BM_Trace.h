
#ifndef BM_TRACE_H
#define BM_TRACE_H
/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Trace.h                      */
/*%%  |                             |  %%  \brief BM trace debug mode            */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*==================[inclusions]============================================*/

#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif

/*==================[macros]================================================*/
#if (BM_BOOT_MANAGER_VARIANT == BM_INITIAL_BOOT_MANAGER)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BM_INITIALBOOTSTARTUP_ENTRY
/** \brief Entry point of function BM_InitialBootStartUp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BM_INITIALBOOTSTARTUP_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BM_INITIALBOOTSTARTUP_EXIT
/** \brief Exit point of function BM_InitialBootStartUp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BM_INITIALBOOTSTARTUP_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#else
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BM_STARTUP_ENTRY
/** \brief Entry point of function BM_StartUp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BM_STARTUP_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BM_STARTUP_EXIT
/** \brief Exit point of function BM_StartUp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BM_STARTUP_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BM_MANAGE_ENTRY
/** \brief Entry point of function BM_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BM_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BM_MANAGE_EXIT
/** \brief Exit point of function BM_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BM_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif      /* BM_TRACE_H */
/*==================[end of file]===========================================*/

