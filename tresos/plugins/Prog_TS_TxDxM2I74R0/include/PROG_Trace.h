
#ifndef PROG_TRACE_H
#define PROG_TRACE_H
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
/*%%   _____________________________   %%  \file PROG_Trace.h                      */
/*%%  |                             |  %%  \brief PROG trace debug mode            */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
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
#include "EB_Prj.h"
/*==================[macros]================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_INIT_ENTRY
/** \brief Entry point of function PROG_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_INIT_EXIT
/** \brief Exit point of function PROG_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TPTXCONF_ENTRY
/** \brief Entry point of function PROG_TpTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TPTXCONF_ENTRY(uMsgIdx,ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TPTXCONF_EXIT
/** \brief Exit point of function PROG_TpTxConf()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TPTXCONF_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TPRXIND_ENTRY
/** \brief Entry point of function PROG_TpRxInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TPRXIND_ENTRY(uMsgIdx,ebStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TPRXIND_EXIT
/** \brief Exit point of function PROG_TpRxInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TPRXIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TPSTARTOFRECEPTIONIND_ENTRY
/** \brief Entry point of function PROG_TpStartOfReceptionInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TPSTARTOFRECEPTIONIND_ENTRY(ubStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TPSTARTOFRECEPTIONIND_EXIT
/** \brief Exit point of function PROG_TpStartOfReceptionInd()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TPSTARTOFRECEPTIONIND_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKHASH_ENTRY
/** \brief Entry point of function PROG_Entry_CheckHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKHASH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKHASH_EXIT
/** \brief Exit point of function PROG_Entry_CheckHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKHASH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQUESTSEED_ENTRY
/** \brief Entry point of function PROG_RequestSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_REQUESTSEED_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQUESTSEED_EXIT
/** \brief Exit point of function PROG_RequestSeed()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_REQUESTSEED_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDKEY_ENTRY
/** \brief Entry point of function PROG_SendKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDKEY_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDKEY_EXIT
/** \brief Exit point of function PROG_SendKey()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_SENDKEY_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQUESTDOWNLOAD_ENTRY
/** \brief Entry point of function PROG_RequestDownload()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_REQUESTDOWNLOAD_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQUESTDOWNLOAD_EXIT
/** \brief Exit point of function PROG_RequestDownload()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_REQUESTDOWNLOAD_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TRANSFERDATA_ENTRY
/** \brief Entry point of function PROG_TransferData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TRANSFERDATA_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TRANSFERDATA_EXIT
/** \brief Exit point of function PROG_TransferData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_TRANSFERDATA_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQUESTTRANSFEREXIT_ENTRY
/** \brief Entry point of function PROG_RequestTransferExit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_REQUESTTRANSFEREXIT_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQUESTTRANSFEREXIT_EXIT
/** \brief Exit point of function PROG_RequestTransferExit()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_REQUESTTRANSFEREXIT_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASEMEMORY_ENTRY
/** \brief Entry point of function PROG_EraseMemory()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ERASEMEMORY_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASEMEMORY_EXIT
/** \brief Exit point of function PROG_EraseMemory()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ERASEMEMORY_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_INVALIDATESECTION_ENTRY
/** \brief Entry point of function PROG_InvalidateSection()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_INVALIDATESECTION_ENTRY(ubPartitionId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_INVALIDATESECTION_EXIT
/** \brief Exit point of function PROG_InvalidateSection()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_INVALIDATESECTION_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITEFINGERPRINT_ENTRY
/** \brief Entry point of function PROG_WriteFingerprint()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITEFINGERPRINT_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITEFINGERPRINT_EXIT
/** \brief Exit point of function PROG_WriteFingerprint()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_WRITEFINGERPRINT_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQCHECKPROGPRECONDITION_ENTRY
/** \brief Entry point of function PROG_ReqCheckProgPreCondition()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_REQCHECKPROGPRECONDITION_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_REQCHECKPROGPRECONDITION_EXIT
/** \brief Exit point of function PROG_ReqCheckProgPreCondition()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_REQCHECKPROGPRECONDITION_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPROGRAMMINGPRECONDITION_ENTRY
/** \brief Entry point of function PROG_CheckProgrammingPreCondition()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKPROGRAMMINGPRECONDITION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPROGRAMMINGPRECONDITION_EXIT
/** \brief Exit point of function PROG_CheckProgrammingPreCondition()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKPROGRAMMINGPRECONDITION_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_LOGICALBLOCKHASH_ENTRY
/** \brief Entry point of function PROG_LogicalBlockHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_LOGICALBLOCKHASH_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_LOGICALBLOCKHASH_EXIT
/** \brief Exit point of function PROG_LogicalBlockHash()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_LOGICALBLOCKHASH_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETPROGRAMMINGSTATUS_ENTRY
/** \brief Entry point of function PROG_SetProgrammingStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETPROGRAMMINGSTATUS_ENTRY(ulProgrammingStatusMask, ubStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETPROGRAMMINGSTATUS_EXIT
/** \brief Exit point of function PROG_SetProgrammingStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETPROGRAMMINGSTATUS_EXIT()
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
#ifndef DBG_PROG_SETSTREAMINGSTATUS_ENTRY
/** \brief Entry point of function PROG_SetStreamingStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETSTREAMINGSTATUS_ENTRY(ubStreamingState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETSTREAMINGSTATUS_EXIT
/** \brief Exit point of function PROG_SetStreamingStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETSTREAMINGSTATUS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ECURESET_ENTRY
/** \brief Entry point of function PROG_EcuReset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ECURESET_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ECURESET_EXIT
/** \brief Exit point of function PROG_EcuReset()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ECURESET_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_AUTOCONTROL_ENTRY
/** \brief Entry point of function PROG_AutoControl()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_AUTOCONTROL_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_AUTOCONTROL_EXIT
/** \brief Exit point of function PROG_AutoControl()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_AUTOCONTROL_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ACTIVESBL_ENTRY
/** \brief Entry point of function PROG_ActiveSBL()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ACTIVESBL_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ACTIVESBL_EXIT
/** \brief Exit point of function PROG_ActiveSBL()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ACTIVESBL_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDAPPLICATION_ENTRY
/** \brief Entry point of function PROG_CheckValidApplication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKVALIDAPPLICATION_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDAPPLICATION_EXIT
/** \brief Exit point of function PROG_CheckValidApplication()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKVALIDAPPLICATION_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SUBMITSIGNATURE_ENTRY
/** \brief Entry point of function PROG_SubmitSignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SUBMITSIGNATURE_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SUBMITSIGNATURE_EXIT
/** \brief Exit point of function PROG_SubmitSignature()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_SUBMITSIGNATURE_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VALIDATEAPPLICATION_ENTRY
/** \brief Entry point of function PROG_ValidateApplication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VALIDATEAPPLICATION_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VALIDATEAPPLICATION_EXIT
/** \brief Exit point of function PROG_ValidateApplication()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_VALIDATEAPPLICATION_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKUPDATESWITCHINGKEYROUTINE_ENTRY
/** \brief Entry point of function PROG_CheckUpdateSwitchingKeyRoutine()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKUPDATESWITCHINGKEYROUTINE_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKUPDATESWITCHINGKEYROUTINE_EXIT
/** \brief Exit point of function PROG_CheckUpdateSwitchingKeyRoutine()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKUPDATESWITCHINGKEYROUTINE_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATEPSI_ENTRY
/** \brief Entry point of function PROG_UpdatePSI()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATEPSI_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATEPSI_EXIT
/** \brief Exit point of function PROG_UpdatePSI()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_UPDATEPSI_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CONTROLDTCSETTING_ENTRY
/** \brief Entry point of function PROG_ControlDTCSetting()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CONTROLDTCSETTING_ENTRY(pulLen, aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CONTROLDTCSETTING_EXIT
/** \brief Exit point of function PROG_ControlDTCSetting()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CONTROLDTCSETTING_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMMUNICATIONCONTROL_ENTRY
/** \brief Entry point of function PROG_CommunicationControl()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMMUNICATIONCONTROL_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMMUNICATIONCONTROL_EXIT
/** \brief Exit point of function PROG_CommunicationControl()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_COMMUNICATIONCONTROL_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKMEMORY_ENTRY
/** \brief Entry point of function PROG_CheckMemory()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKMEMORY_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKMEMORY_EXIT
/** \brief Exit point of function PROG_CheckMemory()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKMEMORY_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPROGRAMMINGDEPENDENCIES_ENTRY
/** \brief Entry point of function PROG_CheckProgrammingDependencies()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKPROGRAMMINGDEPENDENCIES_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPROGRAMMINGDEPENDENCIES_EXIT
/** \brief Exit point of function PROG_CheckProgrammingDependencies()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKPROGRAMMINGDEPENDENCIES_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_READFINGERPRINT_ENTRY
/** \brief Entry point of function PROG_ReadFingerPrint()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_READFINGERPRINT_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_READFINGERPRINT_EXIT
/** \brief Exit point of function PROG_ReadFingerPrint()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_READFINGERPRINT_EXIT(eUdsStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_STREAMINGFRAMERECEIVED_ENTRY
/** \brief Entry point of function PROG_StreamingFrameReceived()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_STREAMINGFRAMERECEIVED_ENTRY(ulReceivedDataLength,aubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_STREAMINGFRAMERECEIVED_EXIT
/** \brief Exit point of function PROG_StreamingFrameReceived()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_STREAMINGFRAMERECEIVED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_OPENPROGRAMMINGSESSION_ENTRY
/** \brief Entry point of function PROG_OpenProgrammingSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_OPENPROGRAMMINGSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_OPENPROGRAMMINGSESSION_EXIT
/** \brief Exit point of function PROG_OpenProgrammingSession()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_OPENPROGRAMMINGSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DSC01CBK_ENTRY
/** \brief Entry point of function PROG_Dsc01Cbk()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DSC01CBK_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DSC01CBK_EXIT
/** \brief Exit point of function PROG_Dsc01Cbk()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DSC01CBK_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DSC02CBK_ENTRY
/** \brief Entry point of function PROG_Dsc02Cbk()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DSC02CBK_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DSC02CBK_EXIT
/** \brief Exit point of function PROG_Dsc02Cbk()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DSC02CBK_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DSC03CBK_ENTRY
/** \brief Entry point of function PROG_Dsc03Cbk()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DSC03CBK_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DSC03CBK_EXIT
/** \brief Exit point of function PROG_Dsc03Cbk()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DSC03CBK_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETACTIVECURRENTSESSION_ENTRY
/** \brief Entry point of function PROG_GetActiveCurrentSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETACTIVECURRENTSESSION_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETACTIVECURRENTSESSION_EXIT
/** \brief Exit point of function PROG_GetActiveCurrentSession()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETACTIVECURRENTSESSION_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCURRENTDIAGAPP_ENTRY
/** \brief Entry point of function PROG_GetCurrentDiagApp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCURRENTDIAGAPP_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCURRENTDIAGAPP_EXIT
/** \brief Exit point of function PROG_GetCurrentDiagApp()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETCURRENTDIAGAPP_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETBOOTSTATUS_ENTRY
/** \brief Entry point of function PROG_GetBootStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETBOOTSTATUS_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETBOOTSTATUS_EXIT
/** \brief Exit point of function PROG_GetBootStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETBOOTSTATUS_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETPEC_ENTRY
/** \brief Entry point of function PROG_GetPEC()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETPEC_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETPEC_EXIT
/** \brief Exit point of function PROG_GetPEC()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETPEC_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETECUID_ENTRY
/** \brief Entry point of function PROG_GetEcuID()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETECUID_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETECUID_EXIT
/** \brief Exit point of function PROG_GetEcuID()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETECUID_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDIDF0F3_ENTRY
/** \brief Entry point of function PROG_GetDidF0F3()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDIDF0F3_ENTRY(aubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDIDF0F3_EXIT
/** \brief Exit point of function PROG_GetDidF0F3()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDIDF0F3_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETECUADDR_ENTRY
/** \brief Entry point of function PROG_GetEcuAddr()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETECUADDR_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETECUADDR_EXIT
/** \brief Exit point of function PROG_GetEcuAddr()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETECUADDR_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETECUNAME_ENTRY
/** \brief Entry point of function PROG_GetEcuName()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETECUNAME_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETECUNAME_EXIT
/** \brief Exit point of function PROG_GetEcuName()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETECUNAME_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDIDF0F6_ENTRY
/** \brief Entry point of function PROG_GetDidF0F6()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDIDF0F6_ENTRY(aubData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDIDF0F6_EXIT
/** \brief Exit point of function PROG_GetDidF0F6()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDIDF0F6_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSBATICKET_ENTRY
/** \brief Entry point of function PROG_GetSbaTicket()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSBATICKET_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSBATICKET_EXIT
/** \brief Exit point of function PROG_GetSbaTicket()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETSBATICKET_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETBOOTINFO_ENTRY
/** \brief Entry point of function PROG_GetBootInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETBOOTINFO_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETBOOTINFO_EXIT
/** \brief Exit point of function PROG_GetBootInfo()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETBOOTINFO_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETPSIVALUES_ENTRY
/** \brief Entry point of function PROG_GetPSIValues()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETPSIVALUES_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETPSIVALUES_EXIT
/** \brief Exit point of function PROG_GetPSIValues()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETPSIVALUES_EXIT(eUdsStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETSLEEPTIMEOUT_ENTRY
/** \brief Entry point of function PROG_SetSleepTimeout()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETSLEEPTIMEOUT_ENTRY(ulTimeoutValue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETSLEEPTIMEOUT_EXIT
/** \brief Exit point of function PROG_SetSleepTimeout()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETSLEEPTIMEOUT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SLEEP_ENTRY
/** \brief Entry point of function PROG_Entry_Sleep()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SLEEP_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SLEEP_EXIT
/** \brief Exit point of function PROG_Entry_Sleep()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ENTRY_SLEEP_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_WRITEFINGERPRINT_ENTRY
/** \brief Entry point of function PROG_Entry_WriteFingerprint()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_WRITEFINGERPRINT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_WRITEFINGERPRINT_EXIT
/** \brief Exit point of function PROG_Entry_WriteFingerprint()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_WRITEFINGERPRINT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITEFINGERPRINTCHECK_ENTRY
/** \brief Entry point of function PROG_WriteFingerprintCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITEFINGERPRINTCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITEFINGERPRINTCHECK_EXIT
/** \brief Exit point of function PROG_WriteFingerprintCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITEFINGERPRINTCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CUSTOMWRITEFINGERPRINT_ENTRY
/** \brief Entry point of function PROG_CustomWriteFingerprint()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CUSTOMWRITEFINGERPRINT_ENTRY(pubRamBuffer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CUSTOMWRITEFINGERPRINT_EXIT
/** \brief Exit point of function PROG_CustomWriteFingerprint()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CUSTOMWRITEFINGERPRINT_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CUSTOMGETWRITEFINGERPRINTSTATUS_ENTRY
/** \brief Entry point of function PROG_CustomGetWriteFingerprintStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CUSTOMGETWRITEFINGERPRINTSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CUSTOMGETWRITEFINGERPRINTSTATUS_EXIT
/** \brief Exit point of function PROG_CustomGetWriteFingerprintStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CUSTOMGETWRITEFINGERPRINTSTATUS_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ECURESET_ENTRY
/** \brief Entry point of function PROG_Entry_EcuReset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ECURESET_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ECURESET_EXIT
/** \brief Exit point of function PROG_Entry_EcuReset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ECURESET_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RESET_ENTRY
/** \brief Entry point of function PROG_Entry_Reset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RESET_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RESET_EXIT
/** \brief Exit point of function PROG_Entry_Reset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RESET_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_DEFAULTSESSION_ENTRY
/** \brief Entry point of function PROG_Entry_DefaultSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_DEFAULTSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_DEFAULTSESSION_EXIT
/** \brief Exit point of function PROG_Entry_DefaultSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_DEFAULTSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_PROGRAMMINGSESSION_ENTRY
/** \brief Entry point of function PROG_Entry_ProgrammingSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_PROGRAMMINGSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_PROGRAMMINGSESSION_EXIT
/** \brief Exit point of function PROG_Entry_ProgrammingSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_PROGRAMMINGSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_EXTENDEDSESSION_ENTRY
/** \brief Entry point of function PROG_Entry_ExtendedSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_EXTENDEDSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_EXTENDEDSESSION_EXIT
/** \brief Exit point of function PROG_Entry_ExtendedSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_EXTENDEDSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CLOSEPROGRAMMINGSESSION_ENTRY
/** \brief Entry point of function PROG_CloseProgrammingSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CLOSEPROGRAMMINGSESSION_ENTRY(eUdsChangeReason)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CLOSEPROGRAMMINGSESSION_EXIT
/** \brief Exit point of function PROG_CloseProgrammingSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CLOSEPROGRAMMINGSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CLOSEEXTENDEDSESSION_ENTRY
/** \brief Entry point of function PROG_CloseExtendedSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CLOSEEXTENDEDSESSION_ENTRY(eUdsChangeReason)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CLOSEEXTENDEDSESSION_EXIT
/** \brief Exit point of function PROG_CloseExtendedSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CLOSEEXTENDEDSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESBASIGNERINFO_ENTRY
/** \brief Entry point of function PROG_Entry_ValidateSBASignerInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESBASIGNERINFO_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESBASIGNERINFO_EXIT
/** \brief Exit point of function PROG_Entry_ValidateSBASignerInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESBASIGNERINFO_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SBASIGNERINFOCHECK_ENTRY
/** \brief Entry point of function PROG_SBASignerInfoCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SBASIGNERINFOCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SBASIGNERINFOCHECK_EXIT
/** \brief Exit point of function PROG_SBASignerInfoCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SBASIGNERINFOCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESBASIGNATURE_ENTRY
/** \brief Entry point of function PROG_Entry_ValidateSBASignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESBASIGNATURE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESBASIGNATURE_EXIT
/** \brief Exit point of function PROG_Entry_ValidateSBASignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESBASIGNATURE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SBASIGNATURECHECK_ENTRY
/** \brief Entry point of function PROG_SBASignatureCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SBASIGNATURECHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SBASIGNATURECHECK_EXIT
/** \brief Exit point of function PROG_SBASignatureCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SBASIGNATURECHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VALIDATESBATICKET_ENTRY
/** \brief Entry point of function PROG_ValidateSBATicket()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VALIDATESBATICKET_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VALIDATESBATICKET_EXIT
/** \brief Exit point of function PROG_ValidateSBATicket()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VALIDATESBATICKET_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_GETSEED_ENTRY
/** \brief Entry point of function PROG_Entry_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_GETSEED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_GETSEED_EXIT
/** \brief Exit point of function PROG_Entry_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_GETSEED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_GETSEEDCHECK_ENTRY
/** \brief Entry point of function PROG_Entry_GetSeedCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_GETSEEDCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_GETSEEDCHECK_EXIT
/** \brief Exit point of function PROG_Entry_GetSeedCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_GETSEEDCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_GETSEED_ENTRY
/** \brief Entry point of function PROG_Do_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_GETSEED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_GETSEED_EXIT
/** \brief Exit point of function PROG_Do_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_GETSEED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSEED_UNLOCKED_ENTRY
/** \brief Entry point of function PROG_GetSeed_Unlocked()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSEED_UNLOCKED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSEED_UNLOCKED_EXIT
/** \brief Exit point of function PROG_GetSeed_Unlocked()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSEED_UNLOCKED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ANSWERSUCCESIVECHECKMEMORYREQUESTS_ENTRY
/** \brief Entry point of function PROG_AnswerSuccesiveCheckMemoryRequests()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ANSWERSUCCESIVECHECKMEMORYREQUESTS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ANSWERSUCCESIVECHECKMEMORYREQUESTS_EXIT
/** \brief Exit point of function PROG_AnswerSuccesiveCheckMemoryRequests()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ANSWERSUCCESIVECHECKMEMORYREQUESTS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_COMPAREKEY_ENTRY
/** \brief Entry point of function PROG_Do_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_COMPAREKEY_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_COMPAREKEY_EXIT
/** \brief Exit point of function PROG_Do_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_COMPAREKEY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_COMPAREKEY_ENTRY
/** \brief Entry point of function PROG_Entry_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_COMPAREKEY_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_COMPAREKEY_EXIT
/** \brief Exit point of function PROG_Entry_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_COMPAREKEY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_COMPAREKEYCHECK_ENTRY
/** \brief Entry point of function PROG_Entry_CompareKeyCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_COMPAREKEYCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_COMPAREKEYCHECK_EXIT
/** \brief Exit point of function PROG_Entry_CompareKeyCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_COMPAREKEYCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSECURITYLEVEL_ENTRY
/** \brief Entry point of function PROG_GetSecurityLevel()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSECURITYLEVEL_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSECURITYLEVEL_EXIT
/** \brief Exit point of function PROG_GetSecurityLevel()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETSECURITYLEVEL_EXIT(ubSecLev)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASECHECK_ENTRY
/** \brief Entry point of function PROG_Entry_EraseCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASECHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASECHECK_EXIT
/** \brief Exit point of function PROG_Entry_EraseCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASECHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASE_GUARD_ENTRY
/** \brief Entry point of function PROG_Erase_Guard()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ERASE_GUARD_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASE_GUARD_EXIT
/** \brief Exit point of function PROG_Erase_Guard()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ERASE_GUARD_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_ERASE_CHECK_ERASEFINISH_ENTRY
/** \brief Entry point of function PROG_Guard_Erase_Check_EraseFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GUARD_ERASE_CHECK_ERASEFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_ERASE_CHECK_ERASEFINISH_EXIT
/** \brief Exit point of function PROG_Guard_Erase_Check_EraseFinish()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GUARD_ERASE_CHECK_ERASEFINISH_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASE_EXTRACTBLOCKID_ENTRY
/** \brief Entry point of function PROG_Erase_ExtractBlockID()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ERASE_EXTRACTBLOCKID_ENTRY(pubUdsData,pubBlockId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASE_EXTRACTBLOCKID_EXIT
/** \brief Exit point of function PROG_Erase_ExtractBlockID()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ERASE_EXTRACTBLOCKID_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASE_ENTRY
/** \brief Entry point of function PROG_Entry_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASE_EXIT
/** \brief Exit point of function PROG_Entry_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASENRC78_ENTRY
/** \brief Entry point of function PROG_Entry_EraseNRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASENRC78_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASENRC78_EXIT
/** \brief Exit point of function PROG_Entry_EraseNRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASENRC78_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASETRANSMITNRC78_ENTRY
/** \brief Entry point of function PROG_Entry_EraseTransmitNRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASETRANSMITNRC78_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASETRANSMITNRC78_EXIT
/** \brief Exit point of function PROG_Entry_EraseTransmitNRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASETRANSMITNRC78_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDNRC78_ENTRY
/** \brief Entry point of function PROG_SendNRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDNRC78_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDNRC78_EXIT
/** \brief Exit point of function PROG_SendNRC78()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDNRC78_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASEFINISH_ENTRY
/** \brief Entry point of function PROG_Entry_EraseFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASEFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASEFINISH_EXIT
/** \brief Exit point of function PROG_Entry_EraseFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASEFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASE_ENTRY
/** \brief Entry point of function PROG_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ERASE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ERASE_EXIT
/** \brief Exit point of function PROG_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ERASE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASE_ENTRY
/** \brief Entry point of function PROG_Entry_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASE_ENTRY(ulLen,paubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ERASE_EXIT
/** \brief Exit point of function PROG_Entry_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ERASE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_RD_CHECK_ENTRY
/** \brief Entry point of function PROG_RD_Check()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_RD_CHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_RD_CHECK_EXIT
/** \brief Exit point of function PROG_RD_Check()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_RD_CHECK_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_RD_CHECK_RTEFINISH_ENTRY
/** \brief Entry point of function PROG_Guard_RD_Check_RTEFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GUARD_RD_CHECK_RTEFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_RD_CHECK_RTEFINISH_EXIT
/** \brief Exit point of function PROG_Guard_RD_Check_RTEFinish()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GUARD_RD_CHECK_RTEFINISH_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_RD_FLASHENABLED_ENTRY
/** \brief Entry point of function PROG_Guard_RD_FlashEnabled()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GUARD_RD_FLASHENABLED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_RD_FLASHENABLED_EXIT
/** \brief Exit point of function PROG_Guard_RD_FlashEnabled()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GUARD_RD_FLASHENABLED_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_RTE_DECOMP_CHECK_ENTRY
/** \brief Entry point of function PROG_Guard_RTE_Decomp_Check()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GUARD_RTE_DECOMP_CHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_RTE_DECOMP_CHECK_EXIT
/** \brief Exit point of function PROG_Guard_RTE_Decomp_Check()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GUARD_RTE_DECOMP_CHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_ENTRY
/** \brief Entry point of function PROG_Entry_RD()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_EXIT
/** \brief Exit point of function PROG_Entry_RD()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_SIGNATURE_ENTRY
/** \brief Entry point of function PROG_Entry_RD_Signature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_SIGNATURE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_SIGNATURE_EXIT
/** \brief Exit point of function PROG_Entry_RD_Signature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_SIGNATURE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_FINISH_ENTRY
/** \brief Entry point of function PROG_Entry_RD_Finish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_FINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_FINISH_EXIT
/** \brief Exit point of function PROG_Entry_RD_Finish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_FINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_FAILED_ENTRY
/** \brief Entry point of function PROG_Entry_RD_Failed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_FAILED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RD_FAILED_EXIT
/** \brief Exit point of function PROG_Entry_RD_Failed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RD_FAILED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RESUME_FINISH_ENTRY
/** \brief Entry point of function PROG_Entry_Resume_Finish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RESUME_FINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RESUME_FINISH_EXIT
/** \brief Exit point of function PROG_Entry_Resume_Finish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RESUME_FINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_TD_ENTRY
/** \brief Entry point of function PROG_Entry_TD()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_TD_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_TD_EXIT
/** \brief Exit point of function PROG_Entry_TD()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_TD_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_TD_HEADER_ENTRY
/** \brief Entry point of function PROG_Entry_TD_Header()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_TD_HEADER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_TD_HEADER_EXIT
/** \brief Exit point of function PROG_Entry_TD_Header()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_TD_HEADER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_STREAMING_ENTRY
/** \brief Entry point of function PROG_Entry_Streaming()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_STREAMING_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_STREAMING_EXIT
/** \brief Exit point of function PROG_Entry_Streaming()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_STREAMING_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_STREAMING_ENTRY
/** \brief Entry point of function PROG_Streaming()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_STREAMING_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_STREAMING_EXIT
/** \brief Exit point of function PROG_Streaming()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_STREAMING_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_TD_FAILED_ENTRY
/** \brief Entry point of function PROG_Entry_TD_Failed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_TD_FAILED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_TD_FAILED_EXIT
/** \brief Exit point of function PROG_Entry_TD_Failed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_TD_FAILED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SEND_NRC_ENTRY
/** \brief Entry point of function PROG_Send_NRC()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SEND_NRC_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SEND_NRC_EXIT
/** \brief Exit point of function PROG_Send_NRC()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SEND_NRC_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_WRITE_ENTRY
/** \brief Entry point of function PROG_Entry_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_WRITE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_WRITE_EXIT
/** \brief Exit point of function PROG_Entry_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_WRITE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITE_ENTRY
/** \brief Entry point of function PROG_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITE_EXIT
/** \brief Exit point of function PROG_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITECHECK_ENTRY
/** \brief Entry point of function PROG_WriteCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITECHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITECHECK_EXIT
/** \brief Exit point of function PROG_WriteCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITECHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_TD_WRITE_ENTRY
/** \brief Entry point of function PROG_Exit_TD_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_TD_WRITE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_TD_WRITE_EXIT
/** \brief Exit point of function PROG_Exit_TD_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_TD_WRITE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RTEFAILED_ENTRY
/** \brief Entry point of function PROG_Entry_RTEFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RTEFAILED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RTEFAILED_EXIT
/** \brief Exit point of function PROG_Entry_RTEFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RTEFAILED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RTE_ENTRY
/** \brief Entry point of function PROG_Entry_RTE()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RTE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RTE_EXIT
/** \brief Exit point of function PROG_Entry_RTE()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RTE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_RTE_ENTRY
/** \brief Entry point of function PROG_RTE()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_RTE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_RTE_EXIT
/** \brief Exit point of function PROG_RTE()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_RTE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_RTE_DECRYPT_ENTRY
/** \brief Entry point of function PROG_Exit_RTE_Decrypt()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_RTE_DECRYPT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_RTE_DECRYPT_EXIT
/** \brief Exit point of function PROG_Exit_RTE_Decrypt()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_RTE_DECRYPT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETPARTITIONADDRINAPPSWINFO_ENTRY
/** \brief Entry point of function PROG_GetPartitionAddrInAppSWInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETPARTITIONADDRINAPPSWINFO_ENTRY(pubHeaderAddr,ubPartitionId,uwRamAccess)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETPARTITIONADDRINAPPSWINFO_EXIT
/** \brief Exit point of function PROG_GetPartitionAddrInAppSWInfo()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETPARTITIONADDRINAPPSWINFO_EXIT(puwPartitionInfoAddr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RTEFINISH_ENTRY
/** \brief Entry point of function PROG_Entry_RTEFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RTEFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_RTEFINISH_EXIT
/** \brief Exit point of function PROG_Entry_RTEFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_RTEFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MESSAGEDIGESTCHECK_ENTRY
/** \brief Entry point of function PROG_MessageDigestCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MESSAGEDIGESTCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MESSAGEDIGESTCHECK_EXIT
/** \brief Exit point of function PROG_MessageDigestCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MESSAGEDIGESTCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEMESSAGEDIGEST_ENTRY
/** \brief Entry point of function PROG_ComputeMessageDigest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEMESSAGEDIGEST_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEMESSAGEDIGEST_EXIT
/** \brief Exit point of function PROG_ComputeMessageDigest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEMESSAGEDIGEST_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESIGNATURE_ENTRY
/** \brief Entry point of function PROG_Entry_ValidateSignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESIGNATURE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESIGNATURE_EXIT
/** \brief Exit point of function PROG_Entry_ValidateSignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESIGNATURE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIGNATURECHECK_ENTRY
/** \brief Entry point of function PROG_SignatureCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIGNATURECHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIGNATURECHECK_EXIT
/** \brief Exit point of function PROG_SignatureCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIGNATURECHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESIGNERINFO_ENTRY
/** \brief Entry point of function PROG_Entry_ValidateSignerInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESIGNERINFO_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATESIGNERINFO_EXIT
/** \brief Exit point of function PROG_Entry_ValidateSignerInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATESIGNERINFO_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIGNERINFOCHECK_ENTRY
/** \brief Entry point of function PROG_SignerInfoCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIGNERINFOCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIGNERINFOCHECK_EXIT
/** \brief Exit point of function PROG_SignerInfoCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIGNERINFOCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_UPDATEPSI_ENTRY
/** \brief Entry point of function PROG_Entry_UpdatePSI()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_UPDATEPSI_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_UPDATEPSI_EXIT
/** \brief Exit point of function PROG_Entry_UpdatePSI()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_UPDATEPSI_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITEPSIVALUE_ENTRY
/** \brief Entry point of function PROG_WritePSIValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITEPSIVALUE_ENTRY(ubPartitionId,ePsiValue,peUdsStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_WRITEPSIVALUE_EXIT
/** \brief Exit point of function PROG_WritePSIValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_WRITEPSIVALUE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CRC_COMPARE_ENTRY
/** \brief Entry point of function PROG_CRC_Compare()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CRC_COMPARE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CRC_COMPARE_EXIT
/** \brief Exit point of function PROG_CRC_Compare()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CRC_COMPARE_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFICATIONONTHEFLY_ENTRY
/** \brief Entry point of function PROG_VERIFICATIONONTHEFLY()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFICATIONONTHEFLY_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFICATIONONTHEFLY_EXIT
/** \brief Exit point of function PROG_VERIFICATIONONTHEFLY()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_VERIFICATIONONTHEFLY_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKHASH_ENTRY
/** \brief Entry point of function PROG_DO_CHECKHASH()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKHASH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKHASH_EXIT
/** \brief Exit point of function PROG_DO_CHECKHASH()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKHASH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKSIGNATURE_ENTRY
/** \brief Entry point of function PROG_DO_CHECKSIGNATURE()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKSIGNATURE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKSIGNATURE_EXIT
/** \brief Exit point of function PROG_DO_CHECKSIGNATURE()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKSIGNATURE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CRC_ENTRY
/** \brief Entry point of function PROG_CRC()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CRC_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CRC_EXIT
/** \brief Exit point of function PROG_CRC()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CRC_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TD_ENTRY
/** \brief Entry point of function PROG_TD()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_TD_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_TD_EXIT
/** \brief Exit point of function PROG_TD()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_TD_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYCRYPTOSTATE_ENTRY
/** \brief Entry point of function PROG_VerifyCryptoState()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYCRYPTOSTATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYCRYPTOSTATE_EXIT
/** \brief Exit point of function PROG_VerifyCryptoState()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_VERIFYCRYPTOSTATE_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATE_OLDDATALENGTH_ENTRY
/** \brief Entry point of function Prog_Update_OldDataLength()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATE_OLDDATALENGTH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATE_OLDDATALENGTH_EXIT
/** \brief Exit point of function Prog_Update_OldDataLength()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATE_OLDDATALENGTH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATE_NEWDATALENGTH_ENTRY
/** \brief Entry point of function Prog_Update_NewDataLength()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATE_NEWDATALENGTH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATE_NEWDATALENGTH_EXIT
/** \brief Exit point of function Prog_Update_NewDataLength()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATE_NEWDATALENGTH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATE_LASTNEWDATALENGTH_ENTRY
/** \brief Entry point of function Prog_Update_LastNewDataLength()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATE_LASTNEWDATALENGTH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_UPDATE_LASTNEWDATALENGTH_EXIT
/** \brief Exit point of function Prog_Update_LastNewDataLength()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_UPDATE_LASTNEWDATALENGTH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CRCSETPARAM_ENTRY
/** \brief Entry point of function PROG_CRCSetParam()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CRCSETPARAM_ENTRY(ulAddress,ulSize,ubAlgo,ubContinue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CRCSETPARAM_EXIT
/** \brief Exit point of function PROG_CRCSetParam()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CRCSETPARAM_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRCVALUE_ENTRY
/** \brief Entry point of function PROG_GetCrcValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCRCVALUE_ENTRY(puwCrcVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRCVALUE_EXIT
/** \brief Exit point of function PROG_GetCrcValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCRCVALUE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRCVALUE_ENTRY
/** \brief Entry point of function PROG_GetCrcValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCRCVALUE_ENTRY(pulCrcVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRCVALUE_EXIT
/** \brief Exit point of function PROG_GetCrcValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCRCVALUE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETNETWORKSTATUS_ENTRY
/** \brief Entry point of function PROG_SetNetworkStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETNETWORKSTATUS_ENTRY(uwNetworkStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETNETWORKSTATUS_EXIT
/** \brief Exit point of function PROG_SetNetworkStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETNETWORKSTATUS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDDSC02RESP_ENTRY
/** \brief Entry point of function PROG_SendDsc02Resp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDDSC02RESP_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDDSC02RESP_EXIT
/** \brief Exit point of function PROG_SendDsc02Resp()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDDSC02RESP_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATEOPENPROGSESSIONNORESPONSE_ENTRY
/** \brief Entry point of function PROG_SimulateOpenProgSessionNoResponse()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATEOPENPROGSESSIONNORESPONSE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATEOPENPROGSESSIONNORESPONSE_EXIT
/** \brief Exit point of function PROG_SimulateOpenProgSessionNoResponse()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATEOPENPROGSESSIONNORESPONSE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATECLOSEPROGSESSION_ENTRY
/** \brief Entry point of function PROG_SimulateCloseProgSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATECLOSEPROGSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATECLOSEPROGSESSION_EXIT
/** \brief Exit point of function PROG_SimulateCloseProgSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATECLOSEPROGSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATEER_ENTRY
/** \brief Entry point of function PROG_SimulateER()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATEER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATEER_EXIT
/** \brief Exit point of function PROG_SimulateER()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATEER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATEOPENPROGSESSION_ENTRY
/** \brief Entry point of function PROG_SimulateOpenProgSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATEOPENPROGSESSION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SIMULATEOPENPROGSESSION_EXIT
/** \brief Exit point of function PROG_SimulateOpenProgSession()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SIMULATEOPENPROGSESSION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MANAGE_ENTRY
/** \brief Entry point of function PROG_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MANAGE_EXIT
/** \brief Exit point of function PROG_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_BCKDMANAGE_ENTRY
/** \brief Entry point of function PROG_BckdManage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_BCKDMANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_BCKDMANAGE_EXIT
/** \brief Exit point of function PROG_BckdManage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_BCKDMANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSEGMENTBYSEGMENTID_ENTRY
/** \brief Entry point of function PROG_GetSegmentBySegmentId()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSEGMENTBYSEGMENTID_ENTRY(ubBlockId,ubSegmentId,ulMemoryLength,pulMemoryAddress,pubSegmentId )
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSEGMENTBYSEGMENTID_EXIT
/** \brief Exit point of function PROG_GetSegmentBySegmentId()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETSEGMENTBYSEGMENTID_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSEGMENTBYADDRESS_ENTRY
/** \brief Entry point of function PROG_GetSegmentByAddress()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSEGMENTBYADDRESS_ENTRY(ulMemoryAddress,ulMemoryLength,eOperationType,pubSegmentId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSEGMENTBYADDRESS_EXIT
/** \brief Exit point of function PROG_GetSegmentByAddress()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETSEGMENTBYADDRESS_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETSECURITYLEVEL_ENTRY
/** \brief Entry point of function PROG_SetSecurityLevel()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETSECURITYLEVEL_ENTRY(ubSecurityLevel)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETSECURITYLEVEL_EXIT
/** \brief Exit point of function PROG_SetSecurityLevel()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETSECURITYLEVEL_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_FINDBLOCKINDEXINTABLE_ENTRY
/** \brief Entry point of function PROG_FindBlockIndexInTable()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_FINDBLOCKINDEXINTABLE_ENTRY(uwBlockIdent,pubBlockId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_FINDBLOCKINDEXINTABLE_EXIT
/** \brief Exit point of function PROG_FindBlockIndexInTable()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_FINDBLOCKINDEXINTABLE_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETREQUESTSEEDCOUNTER_ENTRY
/** \brief Entry point of function PROG_SetRequestSeedCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETREQUESTSEEDCOUNTER_ENTRY(ubRequestSeedCounter)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETREQUESTSEEDCOUNTER_EXIT
/** \brief Exit point of function PROG_SetRequestSeedCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETREQUESTSEEDCOUNTER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETREQUESTSEEDCOUNTER_ENTRY
/** \brief Entry point of function PROG_GetRequestSeedCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETREQUESTSEEDCOUNTER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETREQUESTSEEDCOUNTER_EXIT
/** \brief Exit point of function PROG_GetRequestSeedCounter()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETREQUESTSEEDCOUNTER_EXIT(ubReqSeedCter)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETREQUESTSEEDTIMER_ENTRY
/** \brief Entry point of function PROG_SetRequestSeedTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETREQUESTSEEDTIMER_ENTRY(ulRequestSeedTimer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETREQUESTSEEDTIMER_EXIT
/** \brief Exit point of function PROG_SetRequestSeedTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETREQUESTSEEDTIMER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETREQUESTSEEDTIMER_ENTRY
/** \brief Entry point of function PROG_GetRequestSeedTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETREQUESTSEEDTIMER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETREQUESTSEEDTIMER_EXIT
/** \brief Exit point of function PROG_GetRequestSeedTimer()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETREQUESTSEEDTIMER_EXIT(ulReqSeedTimer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETNETWORKSTATUS_ENTRY
/** \brief Entry point of function PROG_GetNetworkStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETNETWORKSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETNETWORKSTATUS_EXIT
/** \brief Exit point of function PROG_GetNetworkStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETNETWORKSTATUS_EXIT(uwNetworkStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPSIVALUE_ENTRY
/** \brief Entry point of function PROG_CheckPSIValue()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKPSIVALUE_ENTRY(ubPartitionId,ePsiValue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPSIVALUE_EXIT
/** \brief Exit point of function PROG_CheckPSIValue()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKPSIVALUE_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_DECOMPHEADER_ENTRY
/** \brief Entry point of function PROG_Entry_DecompHeader()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_DECOMPHEADER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_DECOMPHEADER_EXIT
/** \brief Exit point of function PROG_Entry_DecompHeader()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_DECOMPHEADER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDRESPAFTERRESET_ENTRY
/** \brief Entry point of function PROG_SendRespAfterReset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDRESPAFTERRESET_ENTRY(ubResetCause,ubSendResp)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SENDRESPAFTERRESET_EXIT
/** \brief Exit point of function PROG_SendRespAfterReset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SENDRESPAFTERRESET_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKDECOMPHEADERSTATUS_ENTRY
/** \brief Entry point of function PROG_CheckDecompHeaderStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKDECOMPHEADERSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKDECOMPHEADERSTATUS_EXIT
/** \brief Exit point of function PROG_CheckDecompHeaderStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKDECOMPHEADERSTATUS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKMEMORY_ENTRY
/** \brief Entry point of function PROG_Entry_CheckMemory()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKMEMORY_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKMEMORY_EXIT
/** \brief Exit point of function PROG_Entry_CheckMemory()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKMEMORY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKMEMORYFINISH_ENTRY
/** \brief Entry point of function PROG_Entry_CheckMemoryFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKMEMORYFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKMEMORYFINISH_EXIT
/** \brief Exit point of function PROG_Entry_CheckMemoryFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKMEMORYFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_CHECKMEMORYFINISH_ENTRY
/** \brief Entry point of function PROG_Exit_CheckMemoryFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_CHECKMEMORYFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_CHECKMEMORYFINISH_EXIT
/** \brief Exit point of function PROG_Exit_CheckMemoryFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_CHECKMEMORYFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_CHECKMEMORY_ENTRY
/** \brief Entry point of function PROG_Exit_CheckMemory()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_CHECKMEMORY_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_CHECKMEMORY_EXIT
/** \brief Exit point of function PROG_Exit_CheckMemory()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_CHECKMEMORY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SIGNATURECHECK_ENTRY
/** \brief Entry point of function PROG_Entry_SignatureCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SIGNATURECHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SIGNATURECHECK_EXIT
/** \brief Exit point of function PROG_Entry_SignatureCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SIGNATURECHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKMEMORYCOMPUTE_ENTRY
/** \brief Entry point of function PROG_Entry_CheckMemoryCompute()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKMEMORYCOMPUTE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKMEMORYCOMPUTE_EXIT
/** \brief Exit point of function PROG_Entry_CheckMemoryCompute()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKMEMORYCOMPUTE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKSEGMENTLISTCRC_ENTRY
/** \brief Entry point of function PROG_CheckSegmentListCrc()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKSEGMENTLISTCRC_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKSEGMENTLISTCRC_EXIT
/** \brief Exit point of function PROG_CheckSegmentListCrc()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKSEGMENTLISTCRC_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATURE_ENTRY
/** \brief Entry point of function PROG_VerifySignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYSIGNATURE_ENTRY(pstPublicKey,pubData,ulDataSize,pubSignature)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATURE_EXIT
/** \brief Exit point of function PROG_VerifySignature()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_VERIFYSIGNATURE_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATURESTART_ENTRY
/** \brief Entry point of function PROG_VerifySignatureStart()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYSIGNATURESTART_ENTRY(pstPublicKey,pubSignature)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATURESTART_EXIT
/** \brief Exit point of function PROG_VerifySignatureStart()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_VERIFYSIGNATURESTART_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATUREUPDATE_ENTRY
/** \brief Entry point of function PROG_VerifySignatureUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYSIGNATUREUPDATE_ENTRY(pubData,uwDataSize)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATUREUPDATE_EXIT
/** \brief Exit point of function PROG_VerifySignatureUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYSIGNATUREUPDATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATUREFINISH_ENTRY
/** \brief Entry point of function PROG_VerifySignatureFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYSIGNATUREFINISH_ENTRY(pubSignature)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_VERIFYSIGNATUREFINISH_EXIT
/** \brief Exit point of function PROG_VerifySignatureFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_VERIFYSIGNATUREFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRYPTOSTATUS_ENTRY
/** \brief Entry point of function PROG_GetCryptoStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCRYPTOSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRYPTOSTATUS_EXIT
/** \brief Exit point of function PROG_GetCryptoStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETCRYPTOSTATUS_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRYPTOSTATE_ENTRY
/** \brief Entry point of function PROG_GetCryptoState()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCRYPTOSTATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCRYPTOSTATE_EXIT
/** \brief Exit point of function PROG_GetCryptoState()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETCRYPTOSTATE_EXIT(eState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if (PROG_CSM_MAC_USED == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MACGENERATESTART_ENTRY
/** \brief Entry point of function PROG_MacGenerateStart()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MACGENERATESTART_ENTRY(uwCsmConfigId,pubData,ulDataSize,pubMacResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MACGENERATESTART_EXIT
/** \brief Exit point of function PROG_MacGenerateStart()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_MACGENERATESTART_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETMACKEY_ENTRY
/** \brief Entry point of function PROG_GetMacKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETMACKEY_ENTRY(pstMacKey)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETMACKEY_EXIT
/** \brief Exit point of function PROG_GetMacKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETMACKEY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEHASHSTART_ENTRY
/** \brief Entry point of function PROG_ComputeHashStart()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEHASHSTART_ENTRY(uwCsmConfigId,pubData,ulDataSize,pubHashResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEHASHSTART_EXIT
/** \brief Exit point of function PROG_ComputeHashStart()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_COMPUTEHASHSTART_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEHASHUPDATE_ENTRY
/** \brief Entry point of function PROG_ComputeHashUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEHASHUPDATE_ENTRY(pubData,ulDataSize)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEHASHUPDATE_EXIT
/** \brief Exit point of function PROG_ComputeHashUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEHASHUPDATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEHASHFINISH_ENTRY
/** \brief Entry point of function PROG_ComputeHashFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEHASHFINISH_ENTRY(pubHashValue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEHASHFINISH_EXIT
/** \brief Exit point of function PROG_ComputeHashFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEHASHFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CSMNOTIFICATION_ENTRY
/** \brief Entry point of function PROG_CsmNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CSMNOTIFICATION_ENTRY(eResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CSMNOTIFICATION_EXIT
/** \brief Exit point of function PROG_CsmNotification()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CSMNOTIFICATION_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_AUTOCONTROL_ENTRY
/** \brief Entry point of function PROG_Entry_AutoControl()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_AUTOCONTROL_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_AUTOCONTROL_EXIT
/** \brief Exit point of function PROG_Entry_AutoControl()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_AUTOCONTROL_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_AUTOCONTROL_PROCESS_ENTRY
/** \brief Entry point of function PROG_AutoControl_Process()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_AUTOCONTROL_PROCESS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_AUTOCONTROL_PROCESS_EXIT
/** \brief Exit point of function PROG_AutoControl_Process()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_AUTOCONTROL_PROCESS_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMSTARTERASING_ENTRY
/** \brief Entry point of function PROG_MemStartErasing()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMSTARTERASING_EXIT
/** \brief Exit point of function PROG_MemStartErasing()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_MEMSTARTERASING_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_INVALIDATESECTION_ENTRY
/** \brief Entry point of function PROG_InvalidateSection()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_INVALIDATESECTION_ENTRY(ulStartAddress,ulEraseLength,ErrorCode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_INVALIDATESECTION_EXIT
/** \brief Exit point of function PROG_InvalidateSection()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_INVALIDATESECTION_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECK_PRG_DEP_CHECK_ENTRY
/** \brief Entry point of function PROG_Check_Prg_Dep_Check()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECK_PRG_DEP_CHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECK_PRG_DEP_CHECK_EXIT
/** \brief Exit point of function PROG_Check_Prg_Dep_Check()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECK_PRG_DEP_CHECK_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKDEPENDENCIESFINISH_ENTRY
/** \brief Entry point of function PROG_Entry_CheckDependenciesFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKDEPENDENCIESFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKDEPENDENCIESFINISH_EXIT
/** \brief Exit point of function PROG_Entry_CheckDependenciesFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKDEPENDENCIESFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKPRGDEPENDENCIES_ENTRY
/** \brief Entry point of function PROG_Do_CheckPrgDependencies()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKPRGDEPENDENCIES_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKPRGDEPENDENCIES_EXIT
/** \brief Exit point of function PROG_Do_CheckPrgDependencies()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKPRGDEPENDENCIES_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDAPPL_ENTRY
/** \brief Entry point of function PROG_CheckValidAppl()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKVALIDAPPL_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDAPPL_EXIT
/** \brief Exit point of function PROG_CheckValidAppl()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKVALIDAPPL_EXIT(eProgCompStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ISVALIDAPPLICATION_ENTRY
/** \brief Entry point of function PROG_IsValidApplication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ISVALIDAPPLICATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ISVALIDAPPLICATION_EXIT
/** \brief Exit point of function PROG_IsValidApplication()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ISVALIDAPPLICATION_EXIT(eProgBoolean)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPROGRAMMINGREQUEST_ENTRY
/** \brief Entry point of function PROG_CheckProgrammingRequest()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKPROGRAMMINGREQUEST_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKPROGRAMMINGREQUEST_EXIT
/** \brief Exit point of function PROG_CheckProgrammingRequest()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CHECKPROGRAMMINGREQUEST_EXIT(eBootFromAppli)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SWITCHAPPLICATIONMODE_ENTRY
/** \brief Entry point of function PROG_SwitchApplicationMode()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SWITCHAPPLICATIONMODE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SWITCHAPPLICATIONMODE_EXIT
/** \brief Exit point of function PROG_SwitchApplicationMode()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SWITCHAPPLICATIONMODE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKSUMBYRANGE_ENTRY
/** \brief Entry point of function PROG_Entry_ChecksumByRange()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKSUMBYRANGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_CHECKSUMBYRANGE_EXIT
/** \brief Exit point of function PROG_Entry_ChecksumByRange()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_CHECKSUMBYRANGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_RANGECHECKSUMFINISH_ENTRY
/** \brief Entry point of function PROG_RangeChecksumFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_RANGECHECKSUMFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_RANGECHECKSUMFINISH_EXIT
/** \brief Exit point of function PROG_RangeChecksumFinish()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_RANGECHECKSUMFINISH_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CALCCRC16_ENTRY
/** \brief Entry point of function PROG_CalcCrc16()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CALCCRC16_ENTRY(aubCrcData,ulReadLength,uwCrcValue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CALCCRC16_EXIT
/** \brief Exit point of function PROG_CalcCrc16()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CALCCRC16_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CALCCRC32_ENTRY
/** \brief Entry point of function PROG_CalcCrc32()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CALCCRC32_ENTRY(aubCrcData,ulReadLength,uwCrcValue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CALCCRC32_EXIT
/** \brief Exit point of function PROG_CalcCrc32()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CALCCRC32_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ALIVE_ENTRY
/** \brief Entry point of function PROG_Entry_Alive()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ALIVE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ALIVE_EXIT
/** \brief Exit point of function PROG_Entry_Alive()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ALIVE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_INIT_ENTRY
/** \brief Entry point of function PROG_Entry_INIT()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_INIT_EXIT
/** \brief Exit point of function PROG_Entry_INIT()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_INIT_ENTRY
/** \brief Entry point of function PROG_Exit_INIT()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_EXIT_INIT_EXIT
/** \brief Exit point of function PROG_Exit_INIT()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_EXIT_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_PREINIT_ENTRY
/** \brief Entry point of function PROG_Entry_PreInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_PREINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_PREINIT_EXIT
/** \brief Exit point of function PROG_Entry_PreInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_PREINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_PREINIT_ENTRY
/** \brief Entry point of function PROG_PreInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_PREINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_PREINIT_EXIT
/** \brief Exit point of function PROG_PreInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_PREINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ACTIVESBL_ENTRY
/** \brief Entry point of function PROG_Entry_ActiveSBL()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ACTIVESBL_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_ACTIVESBL_EXIT
/** \brief Exit point of function PROG_Entry_ActiveSBL()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_ACTIVESBL_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_JUMPTOSBL_ENTRY
/** \brief Entry point of function PROG_JumpToSBL()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_JUMPTOSBL_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_JUMPTOSBL_EXIT
/** \brief Exit point of function PROG_JumpToSBL()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_JUMPTOSBL_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SBLSYNCH_ENTRY
/** \brief Entry point of function PROG_Entry_SblSynch()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SBLSYNCH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SBLSYNCH_EXIT
/** \brief Exit point of function PROG_Entry_SblSynch()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SBLSYNCH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ACTIVESBL_CHECK_ENTRY
/** \brief Entry point of function PROG_ActiveSBL_Check()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ACTIVESBL_CHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ACTIVESBL_CHECK_EXIT
/** \brief Exit point of function PROG_ActiveSBL_Check()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_ACTIVESBL_CHECK_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPRESSINIT_ENTRY
/** \brief Entry point of function PROG_DecompressInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECOMPRESSINIT_ENTRY(ulCompressedDataSize)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPRESSINIT_EXIT
/** \brief Exit point of function PROG_DecompressInit()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DECOMPRESSINIT_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPINPUTPARAMINIT_ENTRY
/** \brief Entry point of function PROG_DecompInputParamInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECOMPINPUTPARAMINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPINPUTPARAMINIT_EXIT
/** \brief Exit point of function PROG_DecompInputParamInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECOMPINPUTPARAMINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPRESSDATA_ENTRY
/** \brief Entry point of function PROG_DecompressData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECOMPRESSDATA_ENTRY(pubData, ulDataLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPRESSDATA_EXIT
/** \brief Exit point of function PROG_DecompressData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DECOMPRESSDATA_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDECOMPRESSEDDATA_ENTRY
/** \brief Entry point of function PROG_GetDecompressedData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDECOMPRESSEDDATA_ENTRY(pubDecompData,pulDecompressLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDECOMPRESSEDDATA_EXIT
/** \brief Exit point of function PROG_GetDecompressedData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETDECOMPRESSEDDATA_EXIT(eProgDecompState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPWRITEDATACONFIRMATION_ENTRY
/** \brief Entry point of function PROG_DecompWriteDataConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECOMPWRITEDATACONFIRMATION_ENTRY(uwLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECOMPWRITEDATACONFIRMATION_EXIT
/** \brief Exit point of function PROG_DecompWriteDataConfirmation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECOMPWRITEDATACONFIRMATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMINIT_ENTRY
/** \brief Entry point of function PROG_MemInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMINIT_EXIT
/** \brief Exit point of function PROG_MemInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_FLASHPAGE_ENTRY
/** \brief Entry point of function PROG_FlashPage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_FLASHPAGE_ENTRY(ulAddress, ubPages,pulDataBuffer,uwDataBufferLenght)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_FLASHPAGE_EXIT
/** \brief Exit point of function PROG_FlashPage()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_FLASHPAGE_EXIT(ubReturnValue)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SKIPPAGE_ENTRY
/** \brief Entry point of function PROG_SkipPage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SKIPPAGE_ENTRY(uAddr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SKIPPAGE_EXIT
/** \brief Exit point of function PROG_SkipPage()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_SKIPPAGE_EXIT(ubRetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMDATAACCESS_ENTRY
/** \brief Entry point of function PROG_MemDataAccess()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMDATAACCESS_ENTRY(eMemType, eOperationType,uMemAddress,ulLength,paubDataBuffer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMDATAACCESS_EXIT
/** \brief Exit point of function PROG_MemDataAccess()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_MEMDATAACCESS_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMJOBRESULT_ENTRY
/** \brief Entry point of function PROG_MemJobResult()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMJOBRESULT_ENTRY(eMemType)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMJOBRESULT_EXIT
/** \brief Exit point of function PROG_MemJobResult()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_MEMJOBRESULT_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMGETNEXTSECTORADDR_ENTRY
/** \brief Entry point of function PROG_MemGetNextSectorAddr()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMGETNEXTSECTORADDR_ENTRY(eMemType, uCurrentSectorAddr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMGETNEXTSECTORADDR_EXIT
/** \brief Exit point of function PROG_MemGetNextSectorAddr()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_MEMGETNEXTSECTORADDR_EXIT(ulNextSectorAddr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMCHECKPAGEERASING_ENTRY
/** \brief Entry point of function PROG_MemCheckPageErasing()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_MEMCHECKPAGEERASING_ENTRY(eMemType, uMemAddress)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_MEMCHECKPAGEERASING_EXIT
/** \brief Exit point of function PROG_MemCheckPageErasing()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_MEMCHECKPAGEERASING_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_COHERENCYCHECK_ENTRY
/** \brief Entry point of function PROG_Do_CoherencyCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_COHERENCYCHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_COHERENCYCHECK_EXIT
/** \brief Exit point of function PROG_Do_CoherencyCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_COHERENCYCHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COHERENCYCHECK_ENTRY
/** \brief Entry point of function PROG_CoherencyCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COHERENCYCHECK_ENTRY(pulLen,aubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COHERENCYCHECK_EXIT
/** \brief Exit point of function PROG_CoherencyCheck()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_COHERENCYCHECK_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COHERENCYPRECHECK_ENTRY
/** \brief Entry point of function PROG_CoherencyPreCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COHERENCYPRECHECK_ENTRY(pulLen,paubUdsData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COHERENCYPRECHECK_EXIT
/** \brief Exit point of function PROG_CoherencyPreCheck()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_COHERENCYPRECHECK_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_COHERENCYPRECHECK_ENTRY
/** \brief Entry point of function PROG_Entry_CoherencyPreCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_COHERENCYPRECHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_COHERENCYPRECHECK_EXIT
/** \brief Exit point of function PROG_Entry_CoherencyPreCheck()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_COHERENCYPRECHECK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYINIT_ENTRY
/** \brief Entry point of function PROG_SecurityInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYINIT_EXIT
/** \brief Exit point of function PROG_SecurityInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCHECKSUMNOTIFICATION_ENTRY
/** \brief Entry point of function PROG_SecurityChecksumNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCHECKSUMNOTIFICATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCHECKSUMNOTIFICATION_EXIT
/** \brief Exit point of function PROG_SecurityChecksumNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCHECKSUMNOTIFICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYPENDINGOPERATION_ENTRY
/** \brief Entry point of function PROG_SecurityPendingOperation()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYPENDINGOPERATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYPENDINGOPERATION_EXIT
/** \brief Exit point of function PROG_SecurityPendingOperation()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_SECURITYPENDINGOPERATION_EXIT(ubPendingOperation)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_ENTRY
/** \brief Entry point of function PROG_SecurityComputeAppChecksum()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_EXIT
/** \brief Exit point of function PROG_SecurityComputeAppChecksum()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCHECKHSMFWUPDATE_ENTRY
/** \brief Entry point of function PROG_SecurityCheckHsmFwUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCHECKHSMFWUPDATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCHECKHSMFWUPDATE_EXIT
/** \brief Exit point of function PROG_SecurityCheckHsmFwUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCHECKHSMFWUPDATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_ENTRY
/** \brief Entry point of function PROG_SecurityComputeBootChecksum()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_EXIT
/** \brief Exit point of function PROG_SecurityComputeBootChecksum()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYSTOREPENDINGEVENT_ENTRY
/** \brief Entry point of function PROG_SecurityStorePendingEvent()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYSTOREPENDINGEVENT_ENTRY(EventToStore)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SECURITYSTOREPENDINGEVENT_EXIT
/** \brief Exit point of function PROG_SecurityStorePendingEvent()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SECURITYSTOREPENDINGEVENT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if ((PROG_AUTHENTICATED_BOOT_ENABLE == STD_ON) && (PROG_BOOT_VERIFICATION == STD_ON))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_ENTRY
/** \brief Entry point of function PROG_GetComputedBootloaderChecksum()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_ENTRY(pubComputedChecksum)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_EXIT
/** \brief Exit point of function PROG_GetComputedBootloaderChecksum()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if ((PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON) || (PROG_DECOMP_FLASH_ROUTINES == STD_ON))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_VERIFYTRANSITION_ENTRY
/** \brief Entry point of function PROG_DrvDown_VerifyTransition()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_VERIFYTRANSITION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_VERIFYTRANSITION_EXIT
/** \brief Exit point of function PROG_DrvDown_VerifyTransition()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DRVDOWN_VERIFYTRANSITION_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_SETFLASHROUTINESPRESENCE_ENTRY
/** \brief Entry point of function PROG_DrvDown_SetFlashRoutinesPresence()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_SETFLASHROUTINESPRESENCE_ENTRY(eProgPresent)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_SETFLASHROUTINESPRESENCE_EXIT
/** \brief Exit point of function PROG_DrvDown_SetFlashRoutinesPresence()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_SETFLASHROUTINESPRESENCE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ISFLASHROUTINESPRESENT_ENTRY
/** \brief Entry point of function PROG_DrvDown_IsFlashRoutinesPresent()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ISFLASHROUTINESPRESENT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ISFLASHROUTINESPRESENT_EXIT
/** \brief Exit point of function PROG_DrvDown_IsFlashRoutinesPresent()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DRVDOWN_ISFLASHROUTINESPRESENT_EXIT(eProgPresent)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ERASEFLASHROUTINES_ENTRY
/** \brief Entry point of function PROG_DrvDown_EraseFlashRoutines()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ERASEFLASHROUTINES_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ERASEFLASHROUTINES_EXIT
/** \brief Exit point of function PROG_DrvDown_EraseFlashRoutines()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ERASEFLASHROUTINES_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_SETFLASHROUTINESCORRUPTION_ENTRY
/** \brief Entry point of function PROG_DrvDown_SetFlashRoutinesCorruption()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_SETFLASHROUTINESCORRUPTION_ENTRY(eProgCorruption)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_SETFLASHROUTINESCORRUPTION_EXIT
/** \brief Exit point of function PROG_DrvDown_SetFlashRoutinesCorruption()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_SETFLASHROUTINESCORRUPTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ISFLASHROUTINESCORRUPTED_ENTRY
/** \brief Entry point of function PROG_DrvDown_IsFlashRoutinesCorrupted()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ISFLASHROUTINESCORRUPTED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ISFLASHROUTINESCORRUPTED_EXIT
/** \brief Exit point of function PROG_DrvDown_IsFlashRoutinesCorrupted()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DRVDOWN_ISFLASHROUTINESCORRUPTED_EXIT(eProgCorruption)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if PROG_DOWNLOAD_PSEUDO_FLASH_ROUTINES_ENABLE == STD_ON
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ERASEPSEUDOFLASHROUTINES_ENTRY
/** \brief Entry point of function PROG_DrvDown_ErasePseudoFlashRoutines()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ERASEPSEUDOFLASHROUTINES_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ERASEPSEUDOFLASHROUTINES_EXIT
/** \brief Exit point of function PROG_DrvDown_ErasePseudoFlashRoutines()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ERASEPSEUDOFLASHROUTINES_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_SETPSEUDOFLASHROUTINESCORRUPTION_ENTRY
/** \brief Entry point of function PROG_DrvDown_SetPseudoFlashRoutinesCorruption()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_SETPSEUDOFLASHROUTINESCORRUPTION_ENTRY(eProgCorruption)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_SETPSEUDOFLASHROUTINESCORRUPTION_EXIT
/** \brief Exit point of function PROG_DrvDown_SetPseudoFlashRoutinesCorruption()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_SETPSEUDOFLASHROUTINESCORRUPTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ISPSEUDOFLASHROUTINESCORRUPTED_ENTRY
/** \brief Entry point of function PROG_DrvDown_IsPseudoFlashRoutinesCorrupted()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRVDOWN_ISPSEUDOFLASHROUTINESCORRUPTED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRVDOWN_ISPSEUDOFLASHROUTINESCORRUPTED_EXIT
/** \brief Exit point of function PROG_DrvDown_IsPseudoFlashRoutinesCorrupted()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DRVDOWN_ISPSEUDOFLASHROUTINESCORRUPTED_EXIT(eProgCorruption)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if (PROG_DECOMP_FLASH_ROUTINES == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRV_DECOMPRESSFLASHROUTINES_ENTRY
/** \brief Entry point of function PROG_Drv_DecompressFlashRoutines()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRV_DECOMPRESSFLASHROUTINES_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRV_DECOMPRESSFLASHROUTINES_EXIT
/** \brief Exit point of function PROG_Drv_DecompressFlashRoutines()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DRV_DECOMPRESSFLASHROUTINES_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRV_CLEARFLASHROUTINES_ENTRY
/** \brief Entry point of function PROG_Drv_ClearFlashRoutines()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DRV_CLEARFLASHROUTINES_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DRV_CLEARFLASHROUTINES_EXIT
/** \brief Exit point of function PROG_Drv_ClearFlashRoutines()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_DRV_CLEARFLASHROUTINES_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SECURECHECKSUMFAILED_ENTRY
/** \brief Entry point of function PROG_Entry_SecureChecksumFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SECURECHECKSUMFAILED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SECURECHECKSUMFAILED_EXIT
/** \brief Exit point of function PROG_Entry_SecureChecksumFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SECURECHECKSUMFAILED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if((PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31))
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_LOGICALBLOCKHASH_ENTRY
/** \brief Entry point of function PROG_Entry_LogicalBlockHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_LOGICALBLOCKHASH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_LOGICALBLOCKHASH_EXIT
/** \brief Exit point of function PROG_Entry_LogicalBlockHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_LOGICALBLOCKHASH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEBLOCKHASH_ENTRY
/** \brief Entry point of function PROG_ComputeBlockHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEBLOCKHASH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTEBLOCKHASH_EXIT
/** \brief Exit point of function PROG_ComputeBlockHash()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTEBLOCKHASH_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_LOGICALBLOCKHASHFINISH_ENTRY
/** \brief Entry point of function PROG_LogicalBlockHashFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_LOGICALBLOCKHASHFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_LOGICALBLOCKHASHFINISH_EXIT
/** \brief Exit point of function PROG_LogicalBlockHashFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_LOGICALBLOCKHASHFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

#if (PROG_REQUEST_SEED_DELAY_TIMER_ENABLED == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETRSDELAYTIMER_ENTRY
/** \brief Entry point of function PROG_SetRsDelayTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETRSDELAYTIMER_ENTRY(ulRsDelayTimer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SETRSDELAYTIMER_EXIT
/** \brief Exit point of function PROG_SetRsDelayTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SETRSDELAYTIMER_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETRSDELAYTIMER_ENTRY
/** \brief Entry point of function PROG_GetRsDelayTimer()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETRSDELAYTIMER_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETRSDELAYTIMER_EXIT
/** \brief Exit point of function PROG_GetRsDelayTimer()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETRSDELAYTIMER_EXIT(ulRsDelayTimer)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATIONFAILED_ENTRY
/** \brief Entry point of function PROG_Entry_ValidationFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATIONFAILED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATIONFAILED_EXIT
/** \brief Exit point of function PROG_Entry_ValidationFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATIONFAILED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATIONFINISH_ENTRY
/** \brief Entry point of function PROG_Entry_ValidationFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATIONFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATIONFINISH_EXIT
/** \brief Exit point of function PROG_Entry_ValidationFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATIONFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SIGNATUREVERIFY_ENTRY
/** \brief Entry point of function PROG_Entry_SignatureVerify()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SIGNATUREVERIFY_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_SIGNATUREVERIFY_EXIT
/** \brief Exit point of function PROG_Entry_SignatureVerify()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_SIGNATUREVERIFY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATE_APPLICATION_ENTRY
/** \brief Entry point of function PROG_Entry_Validate_Application()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATE_APPLICATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_ENTRY_VALIDATE_APPLICATION_EXIT
/** \brief Exit point of function PROG_Entry_Validate_Application()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_ENTRY_VALIDATE_APPLICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKVALIDATEAPPLICATION_ENTRY
/** \brief Entry point of function PROG_Do_CheckValidateApplication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKVALIDATEAPPLICATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKVALIDATEAPPLICATION_EXIT
/** \brief Exit point of function PROG_Do_CheckValidateApplication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKVALIDATEAPPLICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKANTIROLLBACK_ENTRY
/** \brief Entry point of function PROG_Do_CheckAntiRollback()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKANTIROLLBACK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DO_CHECKANTIROLLBACK_EXIT
/** \brief Exit point of function PROG_Do_CheckAntiRollback()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DO_CHECKANTIROLLBACK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDATEAPPLICATIONFINISH_ENTRY
/** \brief Entry point of function PROG_CheckValidateApplicationFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKVALIDATEAPPLICATIONFINISH_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDATEAPPLICATIONFINISH_EXIT
/** \brief Exit point of function PROG_CheckValidateApplicationFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKVALIDATEAPPLICATIONFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDATEAPPLICATIONFAILED_ENTRY
/** \brief Entry point of function PROG_CheckValidateApplicationFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKVALIDATEAPPLICATIONFAILED_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CHECKVALIDATEAPPLICATIONFAILED_EXIT
/** \brief Exit point of function PROG_CheckValidateApplicationFailed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CHECKVALIDATEAPPLICATIONFAILED_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_SIGNATUREVERIFICATIONENABLE_CHECK_ENTRY
/** \brief Entry point of function PROG_Guard_SignatureVerificationEnable_check()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GUARD_SIGNATUREVERIFICATIONENABLE_CHECK_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_SIGNATUREVERIFICATIONENABLE_CHECK_EXIT
/** \brief Exit point of function PROG_Guard_SignatureVerificationEnable_check()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GUARD_SIGNATUREVERIFICATIONENABLE_CHECK_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_CHECKVALIDAPPLICATION_ENTRY
/** \brief Entry point of function PROG_Guard_CheckValidApplication()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GUARD_CHECKVALIDAPPLICATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GUARD_CHECKVALIDAPPLICATION_EXIT
/** \brief Exit point of function PROG_Guard_CheckValidApplication()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GUARD_CHECKVALIDAPPLICATION_EXIT(eProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDECRYPTIONSTATUS_ENTRY
/** \brief Entry point of function PROG_GetDecryptionStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDECRYPTIONSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDECRYPTIONSTATUS_EXIT
/** \brief Exit point of function PROG_GetDecryptionStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETDECRYPTIONSTATUS_EXIT(eStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDECRYPTIONSTATE_ENTRY
/** \brief Entry point of function PROG_GetDecryptionState()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETDECRYPTIONSTATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETDECRYPTIONSTATE_EXIT
/** \brief Exit point of function PROG_GetDecryptionState()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETDECRYPTIONSTATE_EXIT(eState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSYMDECRYPTIONKEY_ENTRY
/** \brief Entry point of function PROG_GetSymDecryptionKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSYMDECRYPTIONKEY_ENTRY(pstDecryptionKey)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETSYMDECRYPTIONKEY_EXIT
/** \brief Exit point of function PROG_GetSymDecryptionKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETSYMDECRYPTIONKEY_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CSMENCRYPTDECRYPTNOTIFICATION_ENTRY
/** \brief Entry point of function PROG_CsmEncryptDecryptNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CSMENCRYPTDECRYPTNOTIFICATION_ENTRY(eResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CSMENCRYPTDECRYPTNOTIFICATION_EXIT
/** \brief Exit point of function PROG_CsmEncryptDecryptNotification()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_CSMENCRYPTDECRYPTNOTIFICATION_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECRYPTIONSTART_ENTRY
/** \brief Entry point of function PROG_DecryptionStart()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECRYPTIONSTART_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECRYPTIONSTART_EXIT
/** \brief Exit point of function PROG_DecryptionStart()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECRYPTIONSTART_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECRYPTIONUPDATE_ENTRY
/** \brief Entry point of function PROG_DecryptionUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECRYPTIONUPDATE_ENTRY(pubCipherText,ulCipherTextLength,pubPlainText,pulPlainTextLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECRYPTIONUPDATE_EXIT
/** \brief Exit point of function PROG_DecryptionUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECRYPTIONUPDATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECRYPTIONFINISH_ENTRY
/** \brief Entry point of function PROG_DecryptionFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECRYPTIONFINISH_ENTRY(pubplainText,pulPlainTextLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_DECRYPTIONFINISH_EXIT
/** \brief Exit point of function PROG_DecryptionFinish()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_DECRYPTIONFINISH_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CSMDECRYPTIONNOTIFICATION_ENTRY
/** \brief Entry point of function PROG_CsmDecryptionNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CSMDECRYPTIONNOTIFICATION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_CSMDECRYPTIONNOTIFICATION_EXIT
/** \brief Exit point of function PROG_CsmDecryptionNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_CSMDECRYPTIONNOTIFICATION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTETOTALENCRYPTEDDATAWITHAESCBCPKCS7_ENTRY
/** \brief Entry point of function PROG_ComputeTotalEncryptedDataWithAesCbcPkcs7()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_COMPUTETOTALENCRYPTEDDATAWITHAESCBCPKCS7_ENTRY(ulTotalPlainDataSize, pulTotalCipheredDataSize)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_COMPUTETOTALENCRYPTEDDATAWITHAESCBCPKCS7_EXIT
/** \brief Exit point of function PROG_ComputeTotalEncryptedDataWithAesCbcPkcs7()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_COMPUTETOTALENCRYPTEDDATAWITHAESCBCPKCS7_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif
#if (PROG_ENABLE_DOWNGRADE_PROTECTION == STD_ON)
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETBLOCKDOWNGRADEFLAGBYINDEX_ENTRY
/** \brief Entry point of function PROG_GetBlockDowngradeFlagByIndex()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_GETBLOCKDOWNGRADEFLAGBYINDEX_ENTRY(ubLogicalBlockIndex)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_GETBLOCKDOWNGRADEFLAGBYINDEX_EXIT
/** \brief Exit point of function PROG_GetBlockDowngradeFlagByIndex()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_GETBLOCKDOWNGRADEFLAGBYINDEX_EXIT(ubBlockDowngradeFlag)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
#endif

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SBL_ERASE_GUARD_ENTRY
/** \brief Entry point of function PROG_SBL_Erase_Guard()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_SBL_ERASE_GUARD_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_SBL_ERASE_GUARD_EXIT
/** \brief Exit point of function PROG_SBL_Erase_Guard()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_PROG_SBL_ERASE_GUARD_EXIT(tProgStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_HSMFWUPDATE_ENTRY
/** \brief Entry point of function PROG_HsmFwUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_HSMFWUPDATE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_PROG_HSMFWUPDATE_EXIT
/** \brief Exit point of function PROG_HsmFwUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_PROG_HSMFWUPDATE_EXIT()
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

#endif      /* PROG_TRACE_H */
/*==================[end of file]===========================================*/

