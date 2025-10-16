
#ifndef BLPDUR_TRACE_H
#define BLPDUR_TRACE_H
/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                              BlPduR layer                                     */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Trace.h                  */
/*%%  |                             |  %%  \brief BlPduR trace debug mode        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3 */
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
#ifndef DBG_BLPDUR_INIT_ENTRY
/** \brief Entry point of function BlPduR_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_INIT_EXIT
/** \brief Exit point of function BlPduR_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_INIT1_ENTRY
/** \brief Entry point of function BlPduR_Init1()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_INIT1_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_INIT1_EXIT
/** \brief Exit point of function BlPduR_Init1()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_INIT1_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_INIT2_ENTRY
/** \brief Entry point of function BlPduR_Init2()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_INIT2_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_INIT2_EXIT
/** \brief Exit point of function BlPduR_Init2()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_INIT2_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_MANAGE_ENTRY
/** \brief Entry point of function BlPduR_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_MANAGE_EXIT
/** \brief Exit point of function BlPduR_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_TPRXMSGMANAGE_ENTRY
/** \brief Entry point of function BlPduR_TpRxMsgManage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_TPRXMSGMANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_TPRXMSGMANAGE_EXIT
/** \brief Exit point of function BlPduR_TpRxMsgManage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_TPRXMSGMANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SAVETESTERADDRESS_ENTRY
/** \brief Entry point of function BlPduR_SaveTesterAddress()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SAVETESTERADDRESS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SAVETESTERADDRESS_EXIT
/** \brief Exit point of function BlPduR_SaveTesterAddress()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_SAVETESTERADDRESS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_STARTOFRECEPTION_ENTRY
/** \brief Entry point of function BlPduR_StartOfReception()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_STARTOFRECEPTION_ENTRY(RxPduId,TpSduLength,BufferSizePtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_STARTOFRECEPTION_EXIT
/** \brief Exit point of function BlPduR_StartOfReception()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_STARTOFRECEPTION_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_COPYRXDATA_ENTRY
/** \brief Entry point of function BlPduR_CopyRxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_COPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_COPYRXDATA_EXIT
/** \brief Exit point of function BlPduR_CopyRxData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_COPYRXDATA_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_TPRXINDICATION_ENTRY
/** \brief Entry point of function BlPduR_TpRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_TPRXINDICATION_ENTRY(RxPduId,Result)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_TPRXINDICATION_EXIT
/** \brief Exit point of function BlPduR_TpRxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_TPRXINDICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SENDMSGDATA_ENTRY
/** \brief Entry point of function BlPduR_SendMsgData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SENDMSGDATA_ENTRY(PduId,ulLen,paubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SENDMSGDATA_EXIT
/** \brief Exit point of function BlPduR_SendMsgData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_SENDMSGDATA_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_COPYTXDATA_ENTRY
/** \brief Entry point of function BlPduR_CopyTxData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_COPYTXDATA_ENTRY(TxPduId,PduInfoPtr,RetryInfoPtr,AvailableDataPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_COPYTXDATA_EXIT
/** \brief Exit point of function BlPduR_CopyTxData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_COPYTXDATA_EXIT(retVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_TPTXCONFIRMATION_ENTRY
/** \brief Entry point of function BlPduR_TpTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_TPTXCONFIRMATION_ENTRY(TxPduId,Result)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_TPTXCONFIRMATION_EXIT
/** \brief Exit point of function BlPduR_TpTxConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_TPTXCONFIRMATION_EXIT()
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
#define DBG_UDS_SESSIONSTATUSIND_ENTRY(eUdsNewSessType,eUdsOldSessType,eUdsChangingCause)
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
#ifndef DBG_BLPDUR_COM_DEACTIVATE_ENTRY
/** \brief Entry point of function BlPduR_Com_Deactivate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_COM_DEACTIVATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_COM_DEACTIVATE_EXIT
/** \brief Exit point of function BlPduR_Com_Deactivate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_COM_DEACTIVATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SETTESTERADDRESS_ENTRY
/** \brief Entry point of function BlPduR_SetTesterAddress()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SETTESTERADDRESS_ENTRY(ubTesterAddress)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SETTESTERADDRESS_EXIT
/** \brief Exit point of function BlPduR_SetTesterAddress()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SETTESTERADDRESS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_STORECONNECTIONINFO_ENTRY
/** \brief Entry point of function BlPduR_StoreConnectionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_STORECONNECTIONINFO_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_STORECONNECTIONINFO_EXIT
/** \brief Exit point of function BlPduR_StoreConnectionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_STORECONNECTIONINFO_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_RETRIEVECONNECTIONINFO_ENTRY
/** \brief Entry point of function BlPduR_RetrieveConnectionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_RETRIEVECONNECTIONINFO_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_RETRIEVECONNECTIONINFO_EXIT
/** \brief Exit point of function BlPduR_RetrieveConnectionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_RETRIEVECONNECTIONINFO_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SEND_TPFRAME_ENTRY
/** \brief Entry point of function BlPduR_Send_TPFrame()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SEND_TPFRAME_ENTRY(ulLen,paubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SEND_TPFRAME_EXIT
/** \brief Exit point of function BlPduR_Send_TPFrame()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SEND_TPFRAME_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SIMULATERXREQUEST_ENTRY
/** \brief Entry point of function BlPduR_SimulateRxRequest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SIMULATERXREQUEST_ENTRY(ulLen,paubUdsData,ulUdsDataSize,ubWithResp)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SIMULATERXREQUEST_EXIT
/** \brief Exit point of function BlPduR_SimulateRxRequest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SIMULATERXREQUEST_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_LOCKBUFFER_ENTRY
/** \brief Entry point of function BlPduR_LockBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_LOCKBUFFER_ENTRY(pubIsLastBuffer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_LOCKBUFFER_EXIT
/** \brief Exit point of function BlPduR_LockBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_LOCKBUFFER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_UNLOCKBUFFER_ENTRY
/** \brief Entry point of function BlPduR_UnlockBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_UNLOCKBUFFER_ENTRY(ubBufferType)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_UNLOCKBUFFER_EXIT
/** \brief Exit point of function BlPduR_UnlockBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_UNLOCKBUFFER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_RXINDICATION_ENTRY
/** \brief Entry point of function BlPduR_RxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_RXINDICATION_ENTRY(RxPduId,PduInfoPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_RXINDICATION_EXIT
/** \brief Exit point of function BlPduR_RxIndication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_RXINDICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_GETNEXTBUFFER_ENTRY
/** \brief Entry point of function BlPduR_GetNextBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_GETNEXTBUFFER_ENTRY(pulLen,paubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_GETNEXTBUFFER_EXIT
/** \brief Exit point of function BlPduR_GetNextBuffer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_GETNEXTBUFFER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SELECTGROUPID_ENTRY
/** \brief Entry point of function BlPduR_SelectGroupID()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SELECTGROUPID_ENTRY(ubGroupID)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_SELECTGROUPID_EXIT
/** \brief Exit point of function BlPduR_SelectGroupID()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_SELECTGROUPID_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_GROUPIDFRAMEFILTER_ENTRY
/** \brief Entry point of function BlPduR_GroupIdFrameFilter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_GROUPIDFRAMEFILTER_ENTRY(Hrh,CanId,CanDlc,CanSduPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_GROUPIDFRAMEFILTER_EXIT
/** \brief Exit point of function BlPduR_GroupIdFrameFilter()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_GROUPIDFRAMEFILTER_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_ENTRY
/** \brief Entry point of function BlPduR_IsTcpConnectionReestablished()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_EXIT
/** \brief Exit point of function BlPduR_IsTcpConnectionReestablished()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_EXIT(RetVal)
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

#endif      /* BLPDUR_TRACE_H */
/*==================[end of file]===========================================*/

