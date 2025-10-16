
#ifndef UDS_TRACE_H
#define UDS_TRACE_H
/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Trace.h                     */
/*%%  |                             |  %%  \brief UDS trace debug mode            */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.22.0 BL3 */
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

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_INIT_ENTRY
/** \brief Entry point of function UDS_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_INIT_EXIT
/** \brief Exit point of function UDS_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RXREQUEST_ENTRY
/** \brief Entry point of function UDS_RxRequest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_RXREQUEST_ENTRY(pulLen,aubUdsData,ulUdsDataSize)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RXREQUEST_EXIT
/** \brief Exit point of function UDS_RxRequest()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_UDS_RXREQUEST_EXIT(eUdsBoolean)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RXREQUESTWITHADDRMODE_ENTRY
/** \brief Entry point of function UDS_RxRequestWithAddrMode()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_RXREQUESTWITHADDRMODE_ENTRY(pulLen,aubUdsData,ulUdsDataSize,UdsAddrMode,eUdsAddrType)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RXREQUESTWITHADDRMODE_EXIT
/** \brief Exit point of function UDS_RxRequestWithAddrMode()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_UDS_RXREQUESTWITHADDRMODE_EXIT(eUdsBoolean)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_LONGREQUESTEND_ENTRY
/** \brief Entry point of function UDS_LongRequestEnd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_LONGREQUESTEND_ENTRY(ulLen,aubUdsData,eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_LONGREQUESTEND_EXIT
/** \brief Exit point of function UDS_LongRequestEnd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_LONGREQUESTEND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_ISPENDING_ENTRY
/** \brief Entry point of function UDS_IsPending()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_ISPENDING_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_ISPENDING_EXIT
/** \brief Exit point of function UDS_IsPending()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_UDS_ISPENDING_EXIT(tUdsStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_MANAGE_ENTRY
/** \brief Entry point of function UDS_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_MANAGE_EXIT
/** \brief Exit point of function UDS_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RESPONSEPENDING_MANAGE_ENTRY
/** \brief Entry point of function UDS_ResponsePending_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_RESPONSEPENDING_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RESPONSEPENDING_MANAGE_EXIT
/** \brief Exit point of function UDS_ResponsePending_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_RESPONSEPENDING_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RELOADTSTOPDIAG_ENTRY
/** \brief Entry point of function UDS_ReloadTStopDiag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_RELOADTSTOPDIAG_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_RELOADTSTOPDIAG_EXIT
/** \brief Exit point of function UDS_ReloadTStopDiag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_RELOADTSTOPDIAG_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_STOPSESSIONTIMER_ENTRY
/** \brief Entry point of function UDS_StopSessionTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_STOPSESSIONTIMER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_STOPSESSIONTIMER_EXIT
/** \brief Exit point of function UDS_StopSessionTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_STOPSESSIONTIMER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_LONGREQUESTRESPTXCONF_ENTRY
/** \brief Entry point of function UDS_LongRequestRespTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_LONGREQUESTRESPTXCONF_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_LONGREQUESTRESPTXCONF_EXIT
/** \brief Exit point of function UDS_LongRequestRespTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_LONGREQUESTRESPTXCONF_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_STOPNRC78TIMER_ENTRY
/** \brief Entry point of function UDS_StopNRC78Timer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_STOPNRC78TIMER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_STOPNRC78TIMER_EXIT
/** \brief Exit point of function UDS_StopNRC78Timer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_STOPNRC78TIMER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_ISOBDSERVICE_ENTRY
/** \brief Entry point of function UDS_IsOBDService()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_ISOBDSERVICE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_ISOBDSERVICE_EXIT
/** \brief Exit point of function UDS_IsOBDService()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_UDS_ISOBDSERVICE_EXIT(m_eUdsObdService)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_GETCURRENTSESSION_ENTRY
/** \brief Entry point of function UDS_GetCurrentSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_GETCURRENTSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_GETCURRENTSESSION_EXIT
/** \brief Exit point of function UDS_GetCurrentSession()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_UDS_GETCURRENTSESSION_EXIT(eSessionCode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif      /* UDS_TRACE_H */
/*==================[end of file]===========================================*/

