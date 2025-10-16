/**
 * \file
 *
 * \brief AUTOSAR J1939Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Dcm.
 *
 * \version 1.1.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef J1939DCM_TRACE_H
#define J1939DCM_TRACE_H

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


#ifndef DBG_J1939DCM_TRANSMITINTERNAL_ENTRY
/** \brief Entry point of function TransmitInternal() */
#define DBG_J1939DCM_TRANSMITINTERNAL_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_TRANSMITINTERNAL_EXIT
/** \brief Exit point of function TransmitInternal() */
#define DBG_J1939DCM_TRANSMITINTERNAL_EXIT(a)
#endif

#ifndef DBG_J1939DCM_SETANDCHECKCHANNELSTATE_ENTRY
/** \brief Entry point of function J1939Dcm_SetAndCheckChannelState() */
#define DBG_J1939DCM_SETANDCHECKCHANNELSTATE_ENTRY(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_SETANDCHECKCHANNELSTATE_EXIT
/** \brief Exit point of function J1939Dcm_SetAndCheckChannelState() */
#define DBG_J1939DCM_SETANDCHECKCHANNELSTATE_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_J1939DCM_REQUESTINDICATION_ENTRY
/** \brief Entry point of function J1939Dcm_RequestIndication() */
#define DBG_J1939DCM_REQUESTINDICATION_ENTRY(a, b, c, d, e, f)
#endif

#ifndef DBG_J1939DCM_REQUESTINDICATION_EXIT
/** \brief Exit point of function J1939Dcm_RequestIndication() */
#define DBG_J1939DCM_REQUESTINDICATION_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_J1939DCM_RXINDICATION_ENTRY
/** \brief Entry point of function J1939Dcm_RxIndication() */
#define DBG_J1939DCM_RXINDICATION_ENTRY(a, b)
#endif

#ifndef DBG_J1939DCM_RXINDICATION_EXIT
/** \brief Exit point of function J1939Dcm_RxIndication() */
#define DBG_J1939DCM_RXINDICATION_EXIT(a, b)
#endif

#ifndef DBG_J1939DCM_TXCONFIRMATION_ENTRY
/** \brief Entry point of function J1939Dcm_TxConfirmation() */
#define DBG_J1939DCM_TXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_TXCONFIRMATION_EXIT
/** \brief Exit point of function J1939Dcm_TxConfirmation() */
#define DBG_J1939DCM_TXCONFIRMATION_EXIT(a)
#endif

#ifndef DBG_J1939DCM_STARTOFRECEPTION_ENTRY
/** \brief Entry point of function J1939Dcm_StartOfReception() */
#define DBG_J1939DCM_STARTOFRECEPTION_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_STARTOFRECEPTION_EXIT
/** \brief Exit point of function J1939Dcm_StartOfReception() */
#define DBG_J1939DCM_STARTOFRECEPTION_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_COPYRXDATA_ENTRY
/** \brief Entry point of function J1939Dcm_CopyRxData() */
#define DBG_J1939DCM_COPYRXDATA_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_COPYRXDATA_EXIT
/** \brief Exit point of function J1939Dcm_CopyRxData() */
#define DBG_J1939DCM_COPYRXDATA_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_TPRXINDICATION_ENTRY
/** \brief Entry point of function J1939Dcm_TpRxIndication() */
#define DBG_J1939DCM_TPRXINDICATION_ENTRY(a, b)
#endif

#ifndef DBG_J1939DCM_TPRXINDICATION_EXIT
/** \brief Exit point of function J1939Dcm_TpRxIndication() */
#define DBG_J1939DCM_TPRXINDICATION_EXIT(a, b)
#endif

#ifndef DBG_J1939DCM_COPYTXDATA_ENTRY
/** \brief Entry point of function J1939Dcm_CopyTxData() */
#define DBG_J1939DCM_COPYTXDATA_ENTRY(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_COPYTXDATA_EXIT
/** \brief Exit point of function J1939Dcm_CopyTxData() */
#define DBG_J1939DCM_COPYTXDATA_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_J1939DCM_TPTXCONFIRMATION_ENTRY
/** \brief Entry point of function J1939Dcm_TpTxConfirmation() */
#define DBG_J1939DCM_TPTXCONFIRMATION_ENTRY(a, b)
#endif

#ifndef DBG_J1939DCM_TPTXCONFIRMATION_EXIT
/** \brief Exit point of function J1939Dcm_TpTxConfirmation() */
#define DBG_J1939DCM_TPTXCONFIRMATION_EXIT(a, b)
#endif

#ifndef DBG_J1939DCM_MAINFUNCTION_ENTRY
/** \brief Entry point of function J1939Dcm_MainFunction() */
#define DBG_J1939DCM_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_J1939DCM_MAINFUNCTION_EXIT
/** \brief Exit point of function J1939Dcm_MainFunction() */
#define DBG_J1939DCM_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_J1939DCM_SETSTATE_ENTRY
/** \brief Entry point of function J1939Dcm_SetState() */
#define DBG_J1939DCM_SETSTATE_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_SETSTATE_EXIT
/** \brief Exit point of function J1939Dcm_SetState() */
#define DBG_J1939DCM_SETSTATE_EXIT(a, b, c,d)
#endif

#ifndef DBG_J1939DCM_INIT_ENTRY
/** \brief Entry point of function J1939Dcm_Init() */
#define DBG_J1939DCM_INIT_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_INIT_EXIT
/** \brief Exit point of function J1939Dcm_Init() */
#define DBG_J1939DCM_INIT_EXIT(a)
#endif

#ifndef DBG_J1939DCM_DEINIT_ENTRY
/** \brief Entry point of function J1939Dcm_DeInit() */
#define DBG_J1939DCM_DEINIT_ENTRY()
#endif

#ifndef DBG_J1939DCM_DEINIT_EXIT
/** \brief Exit point of function J1939Dcm_DeInit() */
#define DBG_J1939DCM_DEINIT_EXIT()
#endif

#ifndef DBG_J1939DCM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function J1939Dcm_GetVersionInfo() */
#define DBG_J1939DCM_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_GETVERSIONINFO_EXIT
/** \brief Exit point of function J1939Dcm_GetVersionInfo() */
#define DBG_J1939DCM_GETVERSIONINFO_EXIT(a)
#endif


#ifndef DBG_J1939DCM_DEMTRIGGERONDTCSTATUS_ENTRY
/** \brief Entry point of function J1939Dcm_DemTriggerOnDTCStatus() */
#define DBG_J1939DCM_DEMTRIGGERONDTCSTATUS_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_DEMTRIGGERONDTCSTATUS_EXIT
/** \brief Exit point of function J1939Dcm_DemTriggerOnDTCStatus() */
#define DBG_J1939DCM_DEMTRIGGERONDTCSTATUS_EXIT(a)
#endif

#ifndef DBG_J1939DCM_GETCHANNELSTATE_ENTRY
/** \brief Entry point of function J1939Dcm_GetChannelState() */
#define DBG_J1939DCM_GETCHANNELSTATE_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_GETCHANNELSTATE_EXIT
/** \brief Exit point of function J1939Dcm_GetChannelState() */
#define DBG_J1939DCM_GETCHANNELSTATE_EXIT(a, b)
#endif

#ifndef DBG_J1939DCM_DM03_11_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM03_11_RequestProcessing() */
#define DBG_J1939DCM_DM03_11_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM03_11_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM03_11_RequestProcessing() */
#define DBG_J1939DCM_DM03_11_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM04_25_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM04_25_RequestProcessing() */
#define DBG_J1939DCM_DM04_25_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM04_25_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM04_25_RequestProcessing() */
#define DBG_J1939DCM_DM04_25_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM05_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM05_RequestProcessing() */
#define DBG_J1939DCM_DM05_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM05_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM05_RequestProcessing() */
#define DBG_J1939DCM_DM05_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM19_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM19_RequestProcessing() */
#define DBG_J1939DCM_DM19_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM19_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM19_RequestProcessing() */
#define DBG_J1939DCM_DM19_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM20_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM20_RequestProcessing() */
#define DBG_J1939DCM_DM20_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM20_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM20_RequestProcessing() */
#define DBG_J1939DCM_DM20_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM21_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM21_RequestProcessing() */
#define DBG_J1939DCM_DM21_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM21_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM21_RequestProcessing() */
#define DBG_J1939DCM_DM21_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM26_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM26_RequestProcessing() */
#define DBG_J1939DCM_DM26_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM26_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM26_RequestProcessing() */
#define DBG_J1939DCM_DM26_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_DM29_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_DM29_RequestProcessing() */
#define DBG_J1939DCM_DM29_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_DM29_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_DM29_RequestProcessing() */
#define DBG_J1939DCM_DM29_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_MEMCPY_ENTRY
/** \brief Entry point of function J1939Dcm_Memcpy() */
#define DBG_J1939DCM_MEMCPY_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_MEMCPY_EXIT
/** \brief Exit point of function J1939Dcm_Memcpy() */
#define DBG_J1939DCM_MEMCPY_EXIT(a, b, c)
#endif

#ifndef DBG_J1939DCM_INTERNALGETNUMBEROFFILTEREDDTC_ENTRY
/** \brief Entry point of function J1939Dcm_InternalGetNumberOfFilteredDTC() */
#define DBG_J1939DCM_INTERNALGETNUMBEROFFILTEREDDTC_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_INTERNALGETNUMBEROFFILTEREDDTC_EXIT
/** \brief Exit point of function J1939Dcm_InternalGetNumberOfFilteredDTC() */
#define DBG_J1939DCM_INTERNALGETNUMBEROFFILTEREDDTC_EXIT(a)
#endif

#ifndef DBG_J1939DCM_REPORTDTC_REQUESTPROCESSING_ENTRY
/** \brief Entry point of function J1939Dcm_ReportDTC_RequestProcessing() */
#define DBG_J1939DCM_REPORTDTC_REQUESTPROCESSING_ENTRY(a, b, c)
#endif

#ifndef DBG_J1939DCM_REPORTDTC_REQUESTPROCESSING_EXIT
/** \brief Exit point of function J1939Dcm_ReportDTC_RequestProcessing() */
#define DBG_J1939DCM_REPORTDTC_REQUESTPROCESSING_EXIT(a, b, c, d)
#endif

#ifndef DBG_J1939DCM_BROADCAST_TRANSMISSION_MODE_ENTRY
/** \brief Entry point of function J1939Dcm_Broadcast_Transmission_Mode() */
#define DBG_J1939DCM_BROADCAST_TRANSMISSION_MODE_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_BROADCAST_TRANSMISSION_MODE_EXIT
/** \brief Exit point of function J1939Dcm_Broadcast_Transmission_Mode() */
#define DBG_J1939DCM_BROADCAST_TRANSMISSION_MODE_EXIT(a,b)
#endif

#ifndef DBG_J1939DCM_DM13TIMEOUTSUPERVISION_ENTRY
/** \brief Entry point of function J1939Dcm_DM13TimeoutSupervision() */
#define DBG_J1939DCM_DM13TIMEOUTSUPERVISION_ENTRY()
#endif

#ifndef DBG_J1939DCM_DM13TIMEOUTSUPERVISION_EXIT
/** \brief Exit point of function J1939Dcm_DM13TimeoutSupervision() */
#define DBG_J1939DCM_DM13TIMEOUTSUPERVISION_EXIT()
#endif

#ifndef DBG_J1939DCM_CURRENTDATALINKNETWORKMASK_UPDATE_ENTRY
/** \brief Entry point of function J1939Dcm_CurrentDataLinkNetworkMask_Update() */
#define DBG_J1939DCM_CURRENTDATALINKNETWORKMASK_UPDATE_ENTRY(a,b)
#endif

#ifndef DBG_J1939DCM_CURRENTDATALINKNETWORKMASK_UPDATE_EXIT
/** \brief Exit point of function J1939Dcm_CurrentDataLinkNetworkMask_Update() */
#define DBG_J1939DCM_CURRENTDATALINKNETWORKMASK_UPDATE_EXIT(a,b,c)
#endif

#ifndef DBG_J1939DCM_NETWORKMASK_UPDATE_ENTRY
/** \brief Entry point of function J1939Dcm_NetworkMask_Update() */
#define DBG_J1939DCM_NETWORKMASK_UPDATE_ENTRY(a,b)
#endif

#ifndef DBG_J1939DCM_NETWORKMASK_UPDATE_EXIT
/** \brief Exit point of function J1939Dcm_NetworkMask_Update() */
#define DBG_J1939DCM_NETWORKMASK_UPDATE_EXIT(a,b,c)
#endif

#ifndef DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE1_ENTRY
/** \brief Entry point of function J1939Dcm_Update_NetworkMask_Byte1() */
#define DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE1_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE1_EXIT
/** \brief Exit point of function J1939Dcm_Update_NetworkMask_Byte1() */
#define DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE1_EXIT(a,b)
#endif

#ifndef DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE2_ENTRY
/** \brief Entry point of function J1939Dcm_Update_NetworkMask_Byte2() */
#define DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE2_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE2_EXIT
/** \brief Exit point of function J1939Dcm_Update_NetworkMask_Byte2() */
#define DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE2_EXIT(a,b)
#endif

#ifndef DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE3_ENTRY
/** \brief Entry point of function J1939Dcm_Update_NetworkMask_Byte3() */
#define DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE3_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE3_EXIT
/** \brief Exit point of function J1939Dcm_Update_NetworkMask_Byte3() */
#define DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE3_EXIT(a,b)
#endif

#ifndef DBG_J1939DCM_UPDATEBROADCASTSTATUS_ENTRY
/** \brief Entry point of function J1939Dcm_UpdateBroadcastStatus() */
#define DBG_J1939DCM_UPDATEBROADCASTSTATUS_ENTRY(a,b)
#endif

#ifndef DBG_J1939DCM_UPDATEBROADCASTSTATUS_EXIT
/** \brief Exit point of function J1939Dcm_UpdateBroadcastStatus() */
#define DBG_J1939DCM_UPDATEBROADCASTSTATUS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939DCM_DM13_PROCESSREQUEST_ENTRY
/** \brief Entry point of function J1939Dcm_DM13_ProcessRequest() */
#define DBG_J1939DCM_DM13_PROCESSREQUEST_ENTRY(a,b)
#endif

#ifndef DBG_J1939DCM_DM13_PROCESSREQUEST_EXIT
/** \brief Exit point of function J1939Dcm_DM13_ProcessRequest() */
#define DBG_J1939DCM_DM13_PROCESSREQUEST_EXIT(a,b)
#endif

#ifndef DBG_J1939DCM_VALIDATEMETADATA_ENTRY
/** \brief Entry point of function J1939Dcm_ValidateMetadata() */
#define DBG_J1939DCM_VALIDATEMETADATA_ENTRY(a)
#endif

#ifndef DBG_J1939DCM_VALIDATEMETADATA_EXIT
/** \brief Exit point of function J1939Dcm_ValidateMetadata() */
#define DBG_J1939DCM_VALIDATEMETADATA_EXIT(a,b)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* ifndef J1939DCM_TRACE_H */
/*==================[end of file]===========================================*/
