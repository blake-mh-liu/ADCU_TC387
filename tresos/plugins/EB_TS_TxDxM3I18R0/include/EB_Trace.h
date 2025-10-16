
#ifndef EB_TRACE_H
#define EB_TRACE_H
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
/*%%   _____________________________   %%  \file EB_Trace.h                      */
/*%%  |                             |  %%  \brief EB trace debug mode            */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.18.0 BL3 */
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
#ifndef DBG_EB_INIT_ENTRY
/** \brief Entry point of function EB_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INIT_EXIT
/** \brief Exit point of function EB_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INIT1_ENTRY
/** \brief Entry point of function EB_Init1()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INIT1_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INIT1_EXIT
/** \brief Exit point of function EB_Init1()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INIT1_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INIT2_ENTRY
/** \brief Entry point of function EB_Init2()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INIT2_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INIT2_EXIT
/** \brief Exit point of function EB_Init2()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INIT2_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_EBRXFRAMEAUTOSAR_ENTRY
/** \brief Entry point of function Com_EBRxFrameAutosar()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_EBRXFRAMEAUTOSAR_ENTRY(Hrh,CanId,CanDlc,CanSduPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_EBRXFRAMEAUTOSAR_EXIT
/** \brief Exit point of function Com_EBRxFrameAutosar()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_COM_EBRXFRAMEAUTOSAR_EXIT(ubCheckResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_EBRXFRAME_ENTRY
/** \brief Entry point of function Com_EBRxFrame()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_EBRXFRAME_ENTRY(ubFrameIndex)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_EBRXFRAME_EXIT
/** \brief Exit point of function Com_EBRxFrame()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_COM_EBRXFRAME_EXIT(ubCheckResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_NASIND_ENTRY
/** \brief Entry point of function COM_NAsInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_NASIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_NASIND_EXIT
/** \brief Exit point of function COM_NAsInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_NASIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXTIMEOUTIND_ENTRY
/** \brief Entry point of function COM_TxTimeoutInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_TXTIMEOUTIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXTIMEOUTIND_EXIT
/** \brief Exit point of function COM_TxTimeoutInd()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_COM_TXTIMEOUTIND_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXTIMEOUTIND_ENTRY
/** \brief Entry point of function COM_TxTimeoutInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_TXTIMEOUTIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXTIMEOUTIND_EXIT
/** \brief Exit point of function COM_TxTimeoutInd()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_COM_TXTIMEOUTIND_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXCONF_ENTRY
/** \brief Entry point of function COM_TxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_TXCONF_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXCONF_EXIT
/** \brief Exit point of function COM_TxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_TXCONF_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_COMBACKIND_ENTRY
/** \brief Entry point of function COM_ComBackInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_COMBACKIND_ENTRY(uNodeIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_COMBACKIND_EXIT
/** \brief Exit point of function COM_ComBackInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_COMBACKIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_COMLOSSIND_ENTRY
/** \brief Entry point of function COM_ComLossInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_COMLOSSIND_ENTRY(uNodeIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_COMLOSSIND_EXIT
/** \brief Exit point of function COM_ComLossInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_COMLOSSIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_MODEMODIFYEXTENSION_ENTRY
/** \brief Entry point of function COM_ModeModifyExtension()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_MODEMODIFYEXTENSION_ENTRY(eCurMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_MODEMODIFYEXTENSION_EXIT
/** \brief Exit point of function COM_ModeModifyExtension()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_MODEMODIFYEXTENSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXFRAMEIND_ENTRY
/** \brief Entry point of function COM_TxFrameInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_TXFRAMEIND_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_TXFRAMEIND_EXIT
/** \brief Exit point of function COM_TxFrameInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_TXFRAMEIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_MONNODESTATUSIND_ENTRY
/** \brief Entry point of function COM_MonNodeStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_MONNODESTATUSIND_ENTRY(uNodeIdx, eFrameStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_MONNODESTATUSIND_EXIT
/** \brief Exit point of function COM_MonNodeStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_MONNODESTATUSIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_CBKRXTPSEGUNDERIT_ENTRY
/** \brief Entry point of function COM_CbkRxTpSegUnderIT()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_CBKRXTPSEGUNDERIT_ENTRY(uFrameIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_COM_CBKRXTPSEGUNDERIT_EXIT
/** \brief Exit point of function COM_CbkRxTpSegUnderIT()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_COM_CBKRXTPSEGUNDERIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_WAKEUPIND_ENTRY
/** \brief Entry point of function CAN_WakeUpInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_WAKEUPIND_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_WAKEUPIND_EXIT
/** \brief Exit point of function CAN_WakeUpInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_WAKEUPIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_CTRLMODEERRORIND_ENTRY
/** \brief Entry point of function CAN_CtrlModeErrorInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_CTRLMODEERRORIND_ENTRY(uErrorID)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CAN_CTRLMODEERRORIND_EXIT
/** \brief Exit point of function CAN_CtrlModeErrorInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CAN_CTRLMODEERRORIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_MANAGE_ENTRY
/** \brief Entry point of function EB_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_MANAGE_EXIT
/** \brief Exit point of function EB_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_DATABUFFEREMPTYIND_ENTRY
/** \brief Entry point of function TP_DataBufferEmptyInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_DATABUFFEREMPTYIND_ENTRY(uMsgIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_DATABUFFEREMPTYIND_EXIT
/** \brief Exit point of function TP_DataBufferEmptyInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_DATABUFFEREMPTYIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_TXCONF_ENTRY
/** \brief Entry point of function TP_TxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_TXCONF_ENTRY(uMsgIdx, ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_TXCONF_EXIT
/** \brief Exit point of function TP_TxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_TXCONF_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXIND_ENTRY
/** \brief Entry point of function TP_RxInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXIND_ENTRY(uMsgIdx,ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXIND_EXIT
/** \brief Exit point of function TP_RxInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXIND_EXIT(uMsgIdx,ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXENABLEIND_ENTRY
/** \brief Entry point of function TP_RxEnableInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXENABLEIND_ENTRY(uMsgIdx, uRxEnable)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXENABLEIND_EXIT
/** \brief Exit point of function TP_RxEnableInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXENABLEIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_STREAMINGFRAMERECEIVED_ENTRY
/** \brief Entry point of function TP_StreamingFrameReceived()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_STREAMINGFRAMERECEIVED_ENTRY(ulReceivedDataLength, aubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_STREAMINGFRAMERECEIVED_EXIT
/** \brief Exit point of function TP_StreamingFrameReceived()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_STREAMINGFRAMERECEIVED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SETSTREAMINGSTATUS_ENTRY
/** \brief Entry point of function EB_SetStreamingStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SETSTREAMINGSTATUS_ENTRY(ubStreamingState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SETSTREAMINGSTATUS_EXIT
/** \brief Exit point of function EB_SetStreamingStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SETSTREAMINGSTATUS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_SESSIONSTATUSIND_ENTRY
/** \brief Entry point of function UDS_SessionStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_SESSIONSTATUSIND_ENTRY(eUdsNewSessType, eUdsOldSessType,eUdsChangingCause)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_SESSIONSTATUSIND_EXIT
/** \brief Exit point of function UDS_SessionStatusInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_SESSIONSTATUSIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_LONGREQUESTRESPONSEIND_ENTRY
/** \brief Entry point of function UDS_LongRequestResponseInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_UDS_LONGREQUESTRESPONSEIND_ENTRY(uwLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_UDS_LONGREQUESTRESPONSEIND_EXIT
/** \brief Exit point of function UDS_LongRequestResponseInd()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_UDS_LONGREQUESTRESPONSEIND_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_ISNETWORKSYNCHRONIZED_ENTRY
/** \brief Entry point of function EB_IsNetworkSynchronized()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_ISNETWORKSYNCHRONIZED_ENTRY(frCycle)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_ISNETWORKSYNCHRONIZED_EXIT
/** \brief Exit point of function EB_IsNetworkSynchronized()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_EB_ISNETWORKSYNCHRONIZED_EXIT(SynchroStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_COM_DEACTIVATE_ENTRY
/** \brief Entry point of function EB_Com_Deactivate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_COM_DEACTIVATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_COM_DEACTIVATE_EXIT
/** \brief Exit point of function EB_Com_Deactivate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_COM_DEACTIVATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SETTESTERADDRESS_ENTRY
/** \brief Entry point of function EB_SetTesterAddress()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SETTESTERADDRESS_ENTRY(ubTesterAddress)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SETTESTERADDRESS_EXIT
/** \brief Exit point of function EB_SetTesterAddress()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SETTESTERADDRESS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SEND_TPFRAME_ENTRY
/** \brief Entry point of function EB_Send_TPFrame()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SEND_TPFRAME_ENTRY(uwLen,paubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SEND_TPFRAME_EXIT
/** \brief Exit point of function EB_Send_TPFrame()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SEND_TPFRAME_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SIMULATERXREQUEST_ENTRY
/** \brief Entry point of function EB_SimulateRxRequest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SIMULATERXREQUEST_ENTRY(uwLen,paubUdsData,ulUdsDataSize,ubWithResp)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SIMULATERXREQUEST_EXIT
/** \brief Exit point of function EB_SimulateRxRequest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SIMULATERXREQUEST_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_STOPSESSIONTIMER_ENTRY
/** \brief Entry point of function EB_StopSessionTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_STOPSESSIONTIMER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_STOPSESSIONTIMER_EXIT
/** \brief Exit point of function EB_StopSessionTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_STOPSESSIONTIMER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INITFULLDUPLEX_ENTRY
/** \brief Entry point of function EB_InitFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INITFULLDUPLEX_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_INITFULLDUPLEX_EXIT
/** \brief Exit point of function EB_InitFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_INITFULLDUPLEX_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TPRXMSGMANAGEFULLDUPLEX_ENTRY
/** \brief Entry point of function EB_TpRxMsgManageFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TPRXMSGMANAGEFULLDUPLEX_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TPRXMSGMANAGEFULLDUPLEX_EXIT
/** \brief Exit point of function EB_TpRxMsgManageFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TPRXMSGMANAGEFULLDUPLEX_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_TXCONFFULLDUPLEX_ENTRY
/** \brief Entry point of function TP_TxConfFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_TXCONFFULLDUPLEX_ENTRY(uMsgIdx,ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_TXCONFFULLDUPLEX_EXIT
/** \brief Exit point of function TP_TxConfFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_TXCONFFULLDUPLEX_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXINDFULLDUPLEX_ENTRY
/** \brief Entry point of function TP_RxIndFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXINDFULLDUPLEX_ENTRY(uMsgIdx,ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXINDFULLDUPLEX_EXIT
/** \brief Exit point of function TP_RxIndFullDuplex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXINDFULLDUPLEX_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXENABLE_ENTRY
/** \brief Entry point of function TP_RxEnable()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_RXENABLE_ENTRY(uMsgIdx,uRxEnable)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_RXENABLE_EXIT
/** \brief Exit point of function TP_RxEnable()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_TP_RXENABLE_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_SETMSGDATA_ENTRY
/** \brief Entry point of function TP_SetMsgData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_SETMSGDATA_ENTRY(uMsgIdx,uwLen,paubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_SETMSGDATA_EXIT
/** \brief Exit point of function TP_SetMsgData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_TP_SETMSGDATA_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_SETMSGDATACOPY_ENTRY
/** \brief Entry point of function TP_SetMsgDataCopy()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_SETMSGDATACOPY_ENTRY(uMsgIdx,uwLen,paubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_SETMSGDATACOPY_EXIT
/** \brief Exit point of function TP_SetMsgDataCopy()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_TP_SETMSGDATACOPY_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_GETMSGDATA_ENTRY
/** \brief Entry point of function TP_GetMsgData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_GETMSGDATA_ENTRY(uMsgIdx,puwLen,paubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_GETMSGDATA_EXIT
/** \brief Exit point of function TP_GetMsgData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_TP_GETMSGDATA_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_STARTOFRECEPTION_ENTRY
/** \brief Entry point of function EB_StartOfReception()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_STARTOFRECEPTION_ENTRY(RxPduId,TpSduLength,BufferSizePtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_STARTOFRECEPTION_EXIT
/** \brief Exit point of function EB_StartOfReception()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_EB_STARTOFRECEPTION_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_COPYRXDATA_ENTRY
/** \brief Entry point of function EB_CopyRxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_COPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_COPYRXDATA_EXIT
/** \brief Exit point of function EB_CopyRxData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_EB_COPYRXDATA_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TPRXINDICATION_ENTRY
/** \brief Entry point of function EB_TpRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TPRXINDICATION_ENTRY(RxPduId,Result)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TPRXINDICATION_EXIT
/** \brief Exit point of function EB_TpRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TPRXINDICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_COPYTXDATA_ENTRY
/** \brief Entry point of function EB_CopyTxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_COPYTXDATA_ENTRY(TxPduId,PduInfoPtr,RetryInfoPtr,AvailableDataPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_COPYTXDATA_EXIT
/** \brief Exit point of function EB_CopyTxData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_EB_COPYTXDATA_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TPTXCONFIRMATION_ENTRY
/** \brief Entry point of function EB_TpTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TPTXCONFIRMATION_ENTRY(TxPduId,Result)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TPTXCONFIRMATION_EXIT
/** \brief Exit point of function EB_TpTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TPTXCONFIRMATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_UDS_RELEASEBUFFERS_ENTRY
/** \brief Entry point of function TP_UDS_ReleaseBuffers()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_UDS_RELEASEBUFFERS_ENTRY(uMsgIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_UDS_RELEASEBUFFERS_EXIT
/** \brief Exit point of function TP_UDS_ReleaseBuffers()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_UDS_RELEASEBUFFERS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_SWAPBUFFER_ENTRY
/** \brief Entry point of function TP_SwapBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_TP_SWAPBUFFER_ENTRY(uMsgIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_TP_SWAPBUFFER_EXIT
/** \brief Exit point of function TP_SwapBuffer()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_TP_SWAPBUFFER_EXIT(eTpStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PDUR_APP_WRAPPER_RXINDICATION_ENTRY
/** \brief Entry point of function PDUR_APP_Wrapper_RxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PDUR_APP_WRAPPER_RXINDICATION_ENTRY(RxPduId,PduInfoPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PDUR_APP_WRAPPER_RXINDICATION_EXIT
/** \brief Exit point of function PDUR_APP_Wrapper_RxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PDUR_APP_WRAPPER_RXINDICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_GETCURRENTRXPDU_ENTRY
/** \brief Entry point of function EB_GetCurrentRxPdu()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_GETCURRENTRXPDU_ENTRY(ubCurrentRxPduId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_GETCURRENTRXPDU_EXIT
/** \brief Exit point of function EB_GetCurrentRxPdu()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_GETCURRENTRXPDU_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SETCURRENTRXPDU_ENTRY
/** \brief Entry point of function EB_SetCurrentRxPdu()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SETCURRENTRXPDU_ENTRY(ubCurrentRxPduId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_SETCURRENTRXPDU_EXIT
/** \brief Exit point of function EB_SetCurrentRxPdu()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_SETCURRENTRXPDU_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TXCONF_ENTRY
/** \brief Entry point of function EB_TxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TXCONF_ENTRY(uMsgIdx)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_EB_TXCONF_EXIT
/** \brief Exit point of function EB_TxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_EB_TXCONF_EXIT()
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

#endif      /* EB_TRACE_H */
/*==================[end of file]===========================================*/

