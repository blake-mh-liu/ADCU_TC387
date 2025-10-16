
#ifndef APP_TRACE_H
#define APP_TRACE_H
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
/*%%   _____________________________   %%  \file APP_Trace.h                     */
/*%%  |                             |  %%  \brief APP trace debug mode            */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.8.0 BL3 */
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
#ifndef DBG_APP_INIT_ENTRY
/** \brief Entry point of function APP_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_INIT_EXIT
/** \brief Exit point of function APP_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_INTERRUPTENABLE_ENTRY
/** \brief Entry point of function APP_InterruptEnable()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_INTERRUPTENABLE_ENTRY(ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_INTERRUPTENABLE_EXIT
/** \brief Exit point of function APP_InterruptEnable()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_INTERRUPTENABLE_EXIT(ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_INTERRUPTDISABLE_ENTRY
/** \brief Entry point of function APP_InterruptDisable()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_INTERRUPTDISABLE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_INTERRUPTDISABLE_EXIT
/** \brief Exit point of function APP_InterruptDisable()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_APP_INTERRUPTDISABLE_EXIT(eContext)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMNASIND_ENTRY
/** \brief Entry point of function APP_ComNAsInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMNASIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMNASIND_EXIT
/** \brief Exit point of function APP_ComNAsInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMNASIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_MANAGE_ENTRY
/** \brief Entry point of function APP_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_MANAGE_EXIT
/** \brief Exit point of function APP_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMTXTIMEOUTIND_ENTRY
/** \brief Entry point of function APP_ComTxTimeoutInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMTXTIMEOUTIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMTXTIMEOUTIND_EXIT
/** \brief Exit point of function APP_ComTxTimeoutInd()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_APP_COMTXTIMEOUTIND_EXIT(COM_ERR_OK)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMTXCONF_ENTRY
/** \brief Entry point of function APP_ComTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMTXCONF_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMTXCONF_EXIT
/** \brief Exit point of function APP_ComTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMTXCONF_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMMODEMODIFYEXTENSION_ENTRY
/** \brief Entry point of function APP_ComModeModifyExtension()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMMODEMODIFYEXTENSION_ENTRY(eCurMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMMODEMODIFYEXTENSION_EXIT
/** \brief Exit point of function APP_ComModeModifyExtension()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMMODEMODIFYEXTENSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMBACKIND_ENTRY
/** \brief Entry point of function APP_ComBackInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMBACKIND_ENTRY(uNodeIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMBACKIND_EXIT
/** \brief Exit point of function APP_ComBackInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMBACKIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMLOSSIND_ENTRY
/** \brief Entry point of function APP_ComLossInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMLOSSIND_ENTRY(uNodeIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMLOSSIND_EXIT
/** \brief Exit point of function APP_ComLossInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMLOSSIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COM_MONNODESTATUSIND_ENTRY
/** \brief Entry point of function APP_COM_MonNodeStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COM_MONNODESTATUSIND_ENTRY(uNodeIdx, eFrameStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COM_MONNODESTATUSIND_EXIT
/** \brief Exit point of function APP_COM_MonNodeStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COM_MONNODESTATUSIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMTXFRAMEIND_ENTRY
/** \brief Entry point of function APP_ComTxFrameInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMTXFRAMEIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_COMTXFRAMEIND_EXIT
/** \brief Exit point of function APP_ComTxFrameInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_COMTXFRAMEIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_BUSOFFIND_ENTRY
/** \brief Entry point of function CAN_BusOffInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_BUSOFFIND_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_BUSOFFIND_EXIT
/** \brief Exit point of function CAN_BusOffInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_BUSOFFIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_GETBAUDRATEIDX_ENTRY
/** \brief Entry point of function CAN_GetBaudRateIdx()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_GETBAUDRATEIDX_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_GETBAUDRATEIDX_EXIT
/** \brief Exit point of function CAN_GetBaudRateIdx()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CAN_GETBAUDRATEIDX_EXIT(eIndex)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_P2ABOUTTOEXPIREIND_ENTRY
/** \brief Entry point of function UDS_P2AboutToExpireInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_P2ABOUTTOEXPIREIND_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_P2ABOUTTOEXPIREIND_EXIT
/** \brief Exit point of function UDS_P2AboutToExpireInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_P2ABOUTTOEXPIREIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_UDSSESSIONSTATUSIND_ENTRY
/** \brief Entry point of function APP_UdsSessionStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_UDSSESSIONSTATUSIND_ENTRY(eUdsNewSessType, eUdsOldSessType, eUdsChangingCause)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_UDSSESSIONSTATUSIND_EXIT
/** \brief Exit point of function APP_UdsSessionStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_UDSSESSIONSTATUSIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPDATABUFFEREMPTYIND_ENTRY
/** \brief Entry point of function APP_TpDataBufferEmptyInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPDATABUFFEREMPTYIND_ENTRY(uMsgIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPDATABUFFEREMPTYIND_EXIT
/** \brief Exit point of function APP_TpDataBufferEmptyInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPDATABUFFEREMPTYIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPTXCONF_ENTRY
/** \brief Entry point of function APP_TpTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPTXCONF_ENTRY(uMsgIdx, ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPTXCONF_EXIT
/** \brief Exit point of function APP_TpTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPTXCONF_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPRXIND_ENTRY
/** \brief Entry point of function APP_TpRxInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPRXIND_ENTRY(uMsgIdx, ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPRXIND_EXIT
/** \brief Exit point of function APP_TpRxInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPRXIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPRXENABLEIND_ENTRY
/** \brief Entry point of function APP_TpRxEnableInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPRXENABLEIND_ENTRY(uMsgIdx, uRxEnable)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_TPRXENABLEIND_EXIT
/** \brief Exit point of function APP_TpRxEnableInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_TPRXENABLEIND_EXIT(eSessionCode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_GETUDSDATABUFFERIND_ENTRY
/** \brief Entry point of function APP_GetUdsDataBufferInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_GETUDSDATABUFFERIND_ENTRY(uwLen, paubUdsData,uMsgIdx, eStatusRxReq )
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_GETUDSDATABUFFERIND_EXIT
/** \brief Exit point of function APP_GetUdsDataBufferInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_GETUDSDATABUFFERIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_CANCTRLMODEERRORIND_ENTRY
/** \brief Entry point of function APP_CanCtrlModeErrorInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_CANCTRLMODEERRORIND_ENTRY(uErrorID)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_CANCTRLMODEERRORIND_EXIT
/** \brief Exit point of function APP_CanCtrlModeErrorInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_CANCTRLMODEERRORIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_NCS_SDFVARIABLECOHERENCYERROR_ENTRY
/** \brief Entry point of function NCS_SdfVariableCoherencyError()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_NCS_SDFVARIABLECOHERENCYERROR_ENTRY(uwParam)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_NCS_SDFVARIABLECOHERENCYERROR_EXIT
/** \brief Exit point of function NCS_SdfVariableCoherencyError()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_NCS_SDFVARIABLECOHERENCYERROR_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_NCS_SDFVARIABLERANGEERROR_ENTRY
/** \brief Entry point of function NCS_SdfVariableRangeError()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_NCS_SDFVARIABLERANGEERROR_ENTRY(uwParam)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_NCS_SDFVARIABLERANGEERROR_EXIT
/** \brief Exit point of function NCS_SdfVariableRangeError()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_NCS_SDFVARIABLERANGEERROR_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_MEMSTARTERASING_ENTRY
/** \brief Entry point of function APP_MemStartErasing()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_APP_MEMSTARTERASING_ENTRY(ulStartAddress, ulEraseLength,ErrorCode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_APP_MEMSTARTERASING_EXIT
/** \brief Exit point of function APP_MemStartErasing()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_APP_MEMSTARTERASING_EXIT(eStatus)
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

#endif      /* APP_TRACE_H */
/*==================[end of file]===========================================*/

