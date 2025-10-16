/* --------{ EB Automotive C Source File }-------- */

/*
 * tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason: False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 */


/* General requirements that are satisfied by this code */
/* !LINKSTO J1939Tp.SWS_J1939Tp_00076,1 */
/*==================[inclusions]============================================*/
#include <J1939Tp.h>
#include <J1939Tp_Api.h>          /* J1939Tp API definitions (own interface) */
#include <J1939Tp_Int.h>          /* J1939Tp internal interface */
#include <J1939Tp_Cbk.h>
#include <J1939Tp_PBcfg.h>            /* Module post-build generated configuration */
#include <J1939Tp_Lcfg.h>
#include <TSAutosar.h>        /* Specific standard types */
/* !LINKSTO J1939Tp.EB.Header.CanIf,1 */
#include <CanIf.h>
/* !LINKSTO J1939Tp.EB.Header.PduRJ1939Tp,1 */
#include <PduR_J1939Tp.h>
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO J1939Tp.EB.Header.Det,1 */
#include <Det.h>
#endif
#include <J1939Tp_Trace.h>  /* Dbg related macros for J1939Tp */
/*====================Private Function Prototypes=============================*/

/* Operation Prototypes*/
#define J1939TP_START_SEC_CODE
#include <J1939Tp_MemMap.h>
/* !LINKSTO EB_Ref.SWS_J1939Tp_00007.functions,1 */
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_CTS(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_EOM(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_BAM_Set_EOMS_Frame(P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_FD_Data_Transmition (P2VAR(PduInfoType,AUTOMATIC,J1939TP_APPL_DATA) tPduInfo,uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_FD_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_Send_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_Data_Timeout(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_FD_Transmit_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(uint8, J1939TP_CODE) J1939Tp_FD_Transmit_Calculate_Frame_Size(uint8 data);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_FD_Transmit_EOMS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_EOMS_Handling(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_CMDT_EOMS(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 Chan_Idx, Std_ReturnType result);

static FUNC(uint8 , J1939TP_CODE) J1939Tp_Set_Session_Number(uint8 MaxSessions, uint8 u8SA_val, uint8 u8DA_val);
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_CM_BAM_Transmit(P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_Data_Timeout(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_DirectPg_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_DirectPg_Data_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Reception(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Reception_CopyRxData(P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_Rx_CMDT_Wait_TxConfirmation(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_EOMS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_EOMS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr);
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_CTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3, boolean request_EOMS);

static FUNC(uint8, J1939TP_CODE) J1939Tp_CMDT_Reception_CTS_Data(P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr, boolean request_EOMS, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) new_State, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) request_Code, P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) Seq_num);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_Data_Complete(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_CTS0(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_RTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_Send_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_RTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Build_RTS(P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) tBuf, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(boolean, J1939TP_CODE) J1939Tp_Calculate_MaxPacketsPerBlock(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) tPduInfo,P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) tBuf);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_Send_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_CopyRxData(P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_Reinit_Tx(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx);

#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
#if(J1939TP_TX_PARALLEL_CHANNEL_HANDLING == STD_OFF)
static FUNC(void, J1939TP_CODE) J1939Tp_PendingRequests_Handling(void);
#else
static FUNC(void, J1939TP_CODE) J1939Tp_PendingRequests_Handling(uint16 u16Ch_Idx);
#endif
static FUNC(boolean, J1939TP_CODE) J1939Tp_GetPendingAvabilityStatus(uint16 u16Ch_Idx);
static FUNC(void, J1939TP_CODE) J1939TpSetPendingRequestAvaialblity(uint16 u16Ch_Idx, boolean PendingStatus);
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_Reinit_Rx(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx);

static FUNC(void,J1939TP_CODE) J1939_AbortFrame_Build(P2VAR(uint8,AUTOMATIC,J1939TP_APPL_DATA) DataPtr, uint8 reason,uint32 pgn,uint8 session_num, boolean CanFDSupport);

static FUNC(J1939TP_FrameStateType, J1939TP_CODE) J1939Tp_Abort_Conn(uint8 reason, P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TxChannel, P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannel, uint32 pgn, J1939Tp_SaDa_Type SaDa, uint8 session_num, P2VAR(J1939Tp_NsduAbortCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_abort_ptr,uint16 ChannelNumber);

static FUNC(J1939TP_FrameStateType, J1939TP_CODE) J1939Tp_EndOfMsgAck(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_TxTimerJob(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_RxTimerJob(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmationTimerJob(P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_pointer);
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_SendFCWait_CTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3);

static FUNC(void, J1939TP_CODE) J1939Tp_NrOfRxPacketsInCts(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 loop_idx1,PduLengthType tRxbufferSize);

static FUNC(boolean, J1939TP_CODE) J1939Tp_CheckAvailableBuffer(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 loop_idx1,PduLengthType tRxbufferSize);

static FUNC(void, J1939TP_CODE) J1939Tp_RxChannelAbortHandler(P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannel);

static FUNC(void, J1939TP_CODE) J1939Tp_NSDU_ChangeState(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint8 new_state);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_BAM_IDLE(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_BAM(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_RTS_IDLE(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_RTS(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);

static FUNC(boolean, J1939TP_CODE) J1939Tp_CM_Validation(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

static FUNC(boolean, J1939TP_CODE) J1939Tp_CM_Type_check(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo, P2VAR(boolean, AUTOMATIC, J1939TP_APPL_DATA) CorrectLength, P2VAR(boolean, AUTOMATIC, J1939TP_APPL_DATA) ValidSession);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_DT(PduIdType RxPduId,uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_DT(uint16 Chan_Idx,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,uint8 u8SA_val,uint8 u8DA_val );

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_TxFcN_CM(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);

static FUNC(boolean, J1939TP_CODE) J1939Tp_Validate_TxFcN_CM_Length(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) CM_Type_ptr, P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) NrPackets_ptr, P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) MsgLength_ptr, P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) c_pgn_ptr);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_TxFcN_CTS(uint16 Chan_Idx,uint16 Pg_Idx,uint16 Nsdu_Idx,P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) c_RxDataPtr);

static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Tx_Store_MetaData(P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) metaDataInfo, uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx);

static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Transmit_Internal(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx, uint8 u8SA_val, uint8 u8DA_val, uint8 MetaDataLen, uint8 metaDataInfo[]);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_DirectPg(uint16 Chan_Idx,uint16 Pg_Idx,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,uint32 metaDataCanId);

static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_RxGet_nsdu_id(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_RxGet_pg_id(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

static FUNC(void, J1939TP_CODE) J1939Tp_RxGet_MetaDataInfo (P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,uint16 J1939TpEcucId);

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_Validate_RxPduId(PduIdType RxPduId,P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_CM(uint16 Chan_Idx , Std_ReturnType result);

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_DT(uint16 Chan_Idx , Std_ReturnType result);

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_CMDT_Data(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 Chan_Idx, Std_ReturnType result);

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_Validate_TxPduId(PduIdType TxPduId,P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo);

/* This function is used to handle NPdu MetaData for CM,DT,Direct NPdu. */
static FUNC(void, J1939TP_CODE) J1939Tp_NPduMetaData_Handle(uint8 NPduMetaData,uint8 NSduMetaData,P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) J1939TpTxPduInfoSrc,uint8 MetaDataInfo[],uint8 J1939TpPGN,uint16 J1939TpEcucId);

/* This function is used to handle NPdu MetaData for fc. */
static FUNC(void, J1939TP_CODE) J1939Tp_FCNPduMetaData_Handle(uint8 FcNPduMetaData, uint8 CmNPduMetaData, P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint8 MetaDataInfo[], uint16 loop_idx1);

/* This function is used to Set MetaData for Rx NPdu. */
static FUNC(void, J1939TP_CODE) J1939Tp_SetEcuCMetaDataRx(uint8 MetaDataLen,uint8 metaDataInfo[],uint16 J1939TpEcucId);

static FUNC(void, J1939TP_CODE) J1939Tp_TxPgNsduSerialization(uint16 Chan_Idx,uint16 Pg_Idx);

static FUNC(void, J1939TP_CODE) J1939Tp_TxChannelPgSerialization(uint16 Chan_Idx);

static FUNC(void, J1939TP_CODE) J1939Tp_RxPgNsduSerialization(uint16 Chan_Idx,uint16 Pg_Idx);

static FUNC(void, J1939TP_CODE) J1939Tp_RxChannelPgSerialization(uint16 Chan_Idx);



/* BAM Wait Confirmation state handling*/
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_NsduTxWaitConfirmationHandling(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx);

#if (J1939TP_CANCELLATION_SUPPORT == STD_ON)
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_CancelationHandle(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx);
#endif

#define J1939TP_STOP_SEC_CODE
#include <J1939Tp_MemMap.h>

/*============================================================================*/
/* Definition of RAM variables                                                */
/*============================================================================*/
/* !LINKSTO EB_Ref.SWS_J1939Tp_00007.data,1 */

#define J1939TP_START_SEC_VAR_INIT_8
#include <J1939Tp_MemMap.h>
/* !LINKSTO J1939Tp.SWS_J1939Tp_00020,1 */
static VAR(uint8, J1939TP_VAR) J1939Tp_Int_State = J1939TP_OFF; /*< contains the state of J1939Tp */
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
static VAR(boolean, J1939TP_VAR) J1939Tp_PendingRequestStatus[J1939Tp_TX_CHANNAEL_NUMB];
static VAR(uint8, J1939TP_VAR) J1939TpPendingRequestCount[J1939Tp_TX_CHANNAEL_NUMB];
#endif
#define J1939TP_STOP_SEC_VAR_INIT_8
#include <J1939Tp_MemMap.h>

#define J1939TP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Tp_MemMap.h>
static P2CONST(J1939Tp_GeneralConfigType,AUTOMATIC,J1939TP_CONST) J1939Tp_Cfg_Ptr;
static P2CONST(J1939Tp_ConfigType, AUTOMATIC, J1939TP_CONST) J1939Tp_PbCfg_Ptr;
#define J1939TP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Tp_MemMap.h>


#define J1939TP_START_SEC_CODE
#include <J1939Tp_MemMap.h>
FUNC( Std_ReturnType, J1939TP_CODE) J1939Tp_IsValidConfig
(
  P2CONST(void,AUTOMATIC,J1939TP_APPL_CONST) voidConfigPtr
)
{
  /* Assume an invalid configuration */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(J1939Tp_ConfigType,AUTOMATIC,J1939TP_APPL_CONST) ConfigPtr = voidConfigPtr;

  if (ConfigPtr != NULL_PTR)
  {
    /* Check if the configuration fits to the platform */
    if (TS_PlatformSigIsValid(ConfigPtr->PlatformSignature) == TRUE )
    {
      /* Validate the post build configuration against the compile time configuration */
      if (J1939TP_CFG_SIGNATURE == ConfigPtr->CfgSignature)
      {
        /* Validate the post build configuration against the link time configuration */
        if (J1939Tp_LcfgSignature == ConfigPtr->LcfgSignature)
        {
          /* Validate the post build configuration against the compile time published information
             configuration */
          if (J1939TP_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
          {
            /* Indicate that the configuration is valid */
            RetVal = E_OK;
          }
        }
      }
    }
  }
  return RetVal;
}

static FUNC(void, J1939TP_CODE) J1939Tp_CM_BAM_Transmit(P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    uint8 MetaDataInfo[4]={0x00,0x00,0x00,0x00};
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 CmNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCmNPduMetaData;
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);

    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType tPduInfo = {NULL_PTR, 0U};

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    uint8 tBuf[60];
    Std_ReturnType TxBuff = E_OK;
    uint8 AssuranceDataType = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].AssuranceDataType;
#else
    uint8 tBuf[8];
#endif
    uint8 pgn = 0U;

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    MetaDataInfo[0] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3] = PrioBit;
    tPduInfo.SduDataPtr = &tBuf[0U];

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
    {
        if(J1939TP_BAM_TX_STATE_EOMS_TRANSMISSION == nsdu_ctrl_ptr->state)
        {
            /* EOMS is ready to be transmitted */
            /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.EOMS.Tx,1 */
            /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.EOMS.WaitConfirmation,1 */
            TxBuff = J1939Tp_BAM_Set_EOMS_Frame(&tPduInfo, loop_idx1, loop_idx2, loop_idx3);
        }
        else
        {
            /* BAM frame is to be transmitted */
            /* Forming BAM Frame */
            /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.Initiation.Tx,1 */
            tBuf[0U] = (uint8)(((nsdu_ctrl_ptr->session_num) << 4U) | (J1939TP_CANFD_TPCM_BAM));          /* Session number concatenated to control field */
            tBuf[1U] = (uint8)nsdu_ctrl_ptr->msglength;                                                   /* LSB of the message length */
            tBuf[2U] = (uint8)(nsdu_ctrl_ptr->msglength>>8U);                                             /* 2nd byte of the message length */
            tBuf[3U] = (uint8)(nsdu_ctrl_ptr->msglength>>16U);                                            /* MSB of the message length */
            tBuf[4U] = (uint8)(nsdu_ctrl_ptr->msglength / J1939TP_MAX_CANFD_DT_MSGLENGTH);                /* 2nd byte of the number of segments */
            if((nsdu_ctrl_ptr->msglength % J1939TP_MAX_CANFD_DT_MSGLENGTH) != 0U)
            {
                tBuf[4U] =  tBuf[4U] + 1U;                                                                /* LSB of the number of segments */
            }
            else
            {
                /* Nothing to do*/
            }
            tBuf[5U] = 0U;                                                                           /* 2nd byte of the number of segments */
            tBuf[6U] = 0U;                                                                           /* MSB of the number of segments */
            tBuf[7U] = 0xFF;                                                                         /* Reserved */
            tBuf[8U] = AssuranceDataType;                                                            /* Assurance Data Type */
            tBuf[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                                                  /* LSB of pgn */
            tBuf[10U] = (uint8)(nsdu_ctrl_ptr->pgn>>8U);                                             /* 2nd byte of pgn */
            tBuf[11U] = (uint8)(nsdu_ctrl_ptr->pgn>>16U);                                            /* MSB of pgn */

            tPduInfo.SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
        }
        pgn = J1939TP_CANFD_TP_CM_PGN;
    }
    else
#endif
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00047.BAM,1 */
        /* For the state J1939TP_BAM_TX_STATE_REQ*/
        /* Making BAM Frame */
        tBuf[0U] = J1939TP_TPCM_BAM;                                              /* Control byte of the BAM frame */
        tBuf[1U] = (uint8)nsdu_ctrl_ptr->msglength;                               /* LSB byte of the message length */
        tBuf[2U] = (uint8)(nsdu_ctrl_ptr->msglength>> 8U);                        /* MSB byte of the message length */
        tBuf[3U] = (uint8)(nsdu_ctrl_ptr->msglength / J1939TP_MAX_DT_MSGLENGTH);  /* number of packets */
        if ((nsdu_ctrl_ptr->msglength % J1939TP_MAX_DT_MSGLENGTH) != 0U)
        {
            tBuf[3U] = tBuf[3U] + 1U;
        }
        tBuf[4U] = J1939TP_UNUSED_BYTE_PADDING;
        tBuf[5U] = (uint8)(nsdu_ctrl_ptr->pgn);         /* LSB of pgn */
        tBuf[6U] = (uint8)(nsdu_ctrl_ptr->pgn >> 8U);   /* 2nd byte of pgn */
        tBuf[7U] = (uint8)(nsdu_ctrl_ptr->pgn >> 16U);  /* MSB of pgn */

        tPduInfo.SduLength = J1939TP_FRAME_LENGTH;
        pgn = J1939TP_TP_CM_PGN;
    }

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if(E_OK != TxBuff)
    {
        /* Frame is not ready to be transmitted */
    }
    else
#endif
    {
        if(nsdu_ctrl_ptr->StartTrTime == TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = FALSE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00198.NPDU.NoMetaData,1 */
        if(CmNPduMetaData > 0U)
        {
            J1939Tp_NPduMetaData_Handle(CmNPduMetaData, TxNSduMetaData, nsdu_ctrl_ptr, MetaDataInfo, pgn, (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxCmNPduTxConfIdEcuCPbcfg);
        }
        /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
        (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = FALSE;
        /* Change the state */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        if(J1939TP_BAM_TX_STATE_EOMS_TRANSMISSION == nsdu_ctrl_ptr->state)
        {
          /* EOMS Message transmitted */
          J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_EOMS);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
          nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
          nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
          nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
        }
        else
#endif
        {
          /* BAM Message transmitted */
          /* !LINKSTO EB_Ref.SWS_J1939Tp_00121.tbammin,1 */
          /* Start Tbammin timer */
          nsdu_ctrl_ptr->StartTbamminTime = TRUE;
          nsdu_ctrl_ptr->TbamminTimeElapsed = FALSE;
          nsdu_ctrl_ptr->TbamminTimeCounter = 0U;
          /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.CM.WaitConfirmation,1 */
          J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM);
          nsdu_ctrl_ptr->sn = 1U;
          nsdu_ctrl_ptr->data_cnt = 0U;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
          nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
          nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
          nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
        }

        /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.CM.BAM,1 */
        /* Frame is ready to be transmitted */
        if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCmNPduTxRTSCanIf, &tPduInfo))
        {
            (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
            J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            /* Abort the connection silently */
            PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);

        }
        else
        {
        }
    }
}

/*For BAM Wait Confirmation state handling*/
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_NsduTxWaitConfirmationHandling(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]);

    DBG_J1939TP_BAM_NSDU_WAIT_CONFIRMATION_HANDLING_ENTRY(Chan_Idx,Pg_Idx,Nsdu_Idx);

    /* For the state J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT and J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM*/
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
        if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
        {
            /* TxConfirmation TimeOut elapsed */
            nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
            nsdu_ctrl_ptr->txconfirmation = TRUE;
            nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
            if(J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT == nsdu_ctrl_ptr->state)
            {
                /* Data message TxConfirmationTimeOut elapsed */
                /* Reset the status */
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
            }
            else
            {
                /* CM message TxConfirmationTimeOut elapsed */
                /* Reset the status */
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
            }
        }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */
        if(((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult == E_OK))
        && ((nsdu_ctrl_ptr->TbamminTimeElapsed == TRUE) || (nsdu_ctrl_ptr->data_cnt >= nsdu_ctrl_ptr->msglength)))
        {
            nsdu_ctrl_ptr->txconfirmation = FALSE;
            nsdu_ctrl_ptr->StartTbamminTime = FALSE;
            nsdu_ctrl_ptr->TbamminTimeElapsed = FALSE;
            if(nsdu_ctrl_ptr->data_cnt < nsdu_ctrl_ptr->msglength)
            {
                /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.Data,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_DATA_TRANSMISSION);
            }
            else
            {
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)
                    &&(nsdu_ctrl_ptr->data_cnt == nsdu_ctrl_ptr->msglength)
                    &&(J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED == nsdu_ctrl_ptr->state))
                {
                    /* to handle EOMS transmission*/
                    /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.EOMS,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_EOMS_TRANSMISSION);
                }
                else
#endif
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00119.Trans.BAM,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.Reset,1 */
                    /* Data transmission is completed inform the upper layer */
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_OK);
                    J1939Tp_Reinit_Tx(Chan_Idx, Pg_Idx, Nsdu_Idx);
                }
            }
        }
        else if((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
        {
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00035,1 */
            /* Timeout - abort the connection silently */
            /* !LINKSTO J1939Tp.EB.Dsn.CANFD.EOMS.BAM.Tx.Reset,1 */
            PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
            J1939Tp_Reinit_Tx(Chan_Idx, Pg_Idx, Nsdu_Idx);
        }
        else
        {
            /* Nothing to do-2 */
        }

    DBG_J1939TP_BAM_NSDU_WAIT_CONFIRMATION_HANDLING_EXIT(Chan_Idx,Pg_Idx,Nsdu_Idx);
}

/* J1939Tp_BAM_Transmit*/
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    DBG_J1939TP_BAM_TRANSMIT_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    switch (nsdu_ctrl_ptr->state)
    {
        case J1939TP_BAM_TX_STATE_REQ:
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        case J1939TP_BAM_TX_STATE_EOMS_TRANSMISSION:
#endif
        {
            if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
            {
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif
                /* Reset tr timeElapsed flag */
                nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                /* Tr timeout due to PduR_J1939TpCopyTxData keep returns BUFREQ_E_BUSY */
                if (nsdu_ctrl_ptr->TrTimeout_SendAbort == TRUE)
                {
                    nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00100.Tx.Tr,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.DT.Timeout,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.EOMS.Abort,1 */
                    /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                    /* Abort transmission and notify upper layer */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_ABORT);
                    nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                }
                else
#endif
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00032.BAM,1 */
                    /* Report to the upper layer */
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
                    J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
                }
            }
            /* If N-PDU is available,  */
            else if((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable == TRUE)
            {
                nsdu_ctrl_ptr->pgn = ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxPgPGN;
                J1939Tp_CM_BAM_Transmit(nsdu_ctrl_ptr, loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* N-Pdu is not available, so start Tr timer and wait for it */
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00121.Tr,1 */
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }
            }
            break;
        }

        case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT:
        case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM:
        case J1939TP_BAM_TX_STATE_CONFIRMATION_CM_RECEIVED:
        case J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED:
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_EOMS:
        case J1939TP_BAM_TX_STATE_CONFIRMATION_EOMS_RECEIVED:

#endif
        {
            /* For the state J1939TP_BAM_TX_STATE_CONFIRMATION_CM_RECEIVED and J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED*/
            J1939Tp_BAM_NsduTxWaitConfirmationHandling(loop_idx1,loop_idx2,loop_idx3);
            break;
        }

        case J1939TP_BAM_TX_STATE_DATA_TRANSMISSION:
        {
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
                {
                    /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.DT.Tx,1 */
                    J1939Tp_BAM_Transmit_FD_Data(loop_idx1,loop_idx2,loop_idx3);
                }
                else
#endif
                {
                    J1939Tp_BAM_Transmit_Data(loop_idx1,loop_idx2,loop_idx3);
                }
            break;
        }

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        case J1939TP_BAM_TX_STATE_ABORT:
        {
            /* Send the Abort Frame - Call the local function to abort */
            /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.Abort.WaitConfirmation,1 */
            J1939Tp_BAM_Transmit_Send_Abort(loop_idx1, loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_ABORT:
        {
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
            {
                /* TxConfirmation TimeOut elapsed */
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
                nsdu_ctrl_ptr->txconfirmation = TRUE;
                nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
            }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

            if(nsdu_ctrl_ptr->txconfirmation == TRUE)
            {
                /* Call notification function*/
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                /* !LINKSTO J1939Tp.EB.Dsn.CANFD.ABORT.BAM.Tx.Reset,1 */
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }
#endif

        default:
        {
            /* Nothing to do-2 */
            break;
        }
    }
    DBG_J1939TP_BAM_TRANSMIT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType;

    /*Remaining bytes to be transfered*/
    PduLengthType tTxDataRem = 0U;

    uint8 i, MetaDataInfo[4]={0};
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 DtNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduMetaData;

    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);

    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType tPduInfo = {NULL_PTR, 0U};

    uint8 tBuf[8] = {0U};

    PduInfoType J1939TpTxPduInfo;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00068.Padding.BAM,1 */
    /* Add the 0xFF if that data value is not present for the data frame */
    uint8 frame[8] = {0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu};

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    /* For Issue 260555 */
    MetaDataInfo[0] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3] = PrioBit;

    DBG_J1939TP_BAM_TRANSMIT_DATA_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.BAM.Timeout,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif
        /* Reset tr timeElapsed flag */
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
        /* Report to the upper layer */
        PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
        J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
    }
    /* If N-PDU is available,  */
    else if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable == TRUE)
    {
        /* For the state J1939TP_BAM_TX_STATE_DATA_TRANSMISSION*/
        if ((nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) > (uint8)7)
        {
            tPduInfo.SduLength = J1939TP_DATA_LENGTH;
        }
        else
        {
            tPduInfo.SduLength = (PduLengthType)nsdu_ctrl_ptr->msglength - (PduLengthType)nsdu_ctrl_ptr->data_cnt;
        }
        /* Initialize the data pointer */
        tPduInfo.SduDataPtr = &tBuf[0];
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00219,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.BAM,1 */
        /* Retry mechanism for BAM is never supported. So retry parameter is always NULL_PTR for BAM */
        tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, &tPduInfo, NULL_PTR,  &tTxDataRem);
        switch (tBufReq_ReturnType)
        {
            case BUFREQ_OK:
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.BAM.DataAvailable,1 */
                /* Prepared the DATA frame for BAM transmission */
                frame[0U] = (uint8)nsdu_ctrl_ptr->sn;
                if ( nsdu_ctrl_ptr->sn >= J1939TP_SN_MAX)
                {
                    /* reset sequence number */
                    nsdu_ctrl_ptr->sn = 1U;
                }
                else
                {
                    /* Increment the sequence number */
                    nsdu_ctrl_ptr->sn++;
                }
                /* Copy the data for DATA frame */
                for (i=0U; i<tPduInfo.SduLength; i++)
                {
                    frame[i + 1U] = (tPduInfo.SduDataPtr[i]);
                }
                nsdu_ctrl_ptr->data_cnt = (uint16)(nsdu_ctrl_ptr->data_cnt + tPduInfo.SduLength);
                /* Start Tbammin timer */
                nsdu_ctrl_ptr->StartTbamminTime = TRUE;
                nsdu_ctrl_ptr->TbamminTimeElapsed = FALSE;
                nsdu_ctrl_ptr->TbamminTimeCounter = 0U;

                /* Tr Timer is ON means previously PduR_J1939TpCopyTxData had returned BUFREQ_E_BUSY/BUFREQ_E_OVFL.
                 * Now as PduR_J1939TpCopyTxData has returned BUFREQ_OK, we can stop this Tr timer */
                if(nsdu_ctrl_ptr->StartTrTime == TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = FALSE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }

                J1939TpTxPduInfo.SduLength = J1939TP_FRAME_LENGTH;
                J1939TpTxPduInfo.SduDataPtr = &frame[0];

                if(DtNPduMetaData > 0U)
                {
                    J1939Tp_NPduMetaData_Handle(DtNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_TP_DT_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDtNPduTxConfIdEcuCPbcfg);
                }
                /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = FALSE;
                /* Change the state */
                /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.WaitConfirmation,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.DT.BAM,1 */
                /* Transmit the BAM DATA frame to CanIf */
                if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduTxConfIdCanIf, &J1939TpTxPduInfo))
                {
                    (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
                    /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
                    J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
                    /* indicate upper layer regarding the error */
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                }
                else
                {
                }
                break;
            }

            case BUFREQ_E_BUSY:
            case BUFREQ_E_OVFL:
            {
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */

                /* Report to the upper layer */
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }
                break;
            }

            case BUFREQ_E_NOT_OK:
            {
                /* BUFREQ_E_NOT_OK*/
                /* call reinit Tx so state also change to IDLE ***/
                J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CopyTxData.BAM,1 */
                /* indicate upper layer regarding the error */
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);

                break;
            }
            default:
            {
                /* Nothing to do-6 */
                break;
            }
        }
    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_BAM_TRANSMIT_DATA_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_BAM_Set_EOMS_Frame(P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    Std_ReturnType TxBuff = E_OK;
    BufReq_ReturnType BufReq_Return;

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    uint8 AssuranceDataType = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].AssuranceDataType;
    uint8 AssuranceDataLength = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].AssuranceDataLength;
    /* Prepare the frame for EOMS transmission */
    PduInfoPtr->SduDataPtr[0U] = (uint8)(((nsdu_ctrl_ptr->session_num) << 4U) | (J1939TP_CANFD_TPCM_ENDOFMSGSTATUS));
    PduInfoPtr->SduDataPtr[1U] = (uint8)nsdu_ctrl_ptr->msglength;                                     /* LSB byte of the message length */
    PduInfoPtr->SduDataPtr[2U] = (uint8)(nsdu_ctrl_ptr->msglength >> 8U);                             /* 2nd byte of the message length */
    PduInfoPtr->SduDataPtr[3U] = (uint8)(nsdu_ctrl_ptr->msglength >> 16U);                            /* MSB byte of the message length */
    PduInfoPtr->SduDataPtr[4U] = (uint8)(nsdu_ctrl_ptr->msglength / J1939TP_MAX_CANFD_DT_MSGLENGTH);  /* LSB of the number of segments */
    if((nsdu_ctrl_ptr->msglength % J1939TP_MAX_CANFD_DT_MSGLENGTH) != 0U)
    {
        PduInfoPtr->SduDataPtr[4U] =  PduInfoPtr->SduDataPtr[4U] + 1U;                                                 /* LSB of the number of segments */
    }
    PduInfoPtr->SduDataPtr[5U] = 0U;                                                                  /* 2nd byte of the number of segments, shall be set to zero as the max. number of segments is 255 */
    PduInfoPtr->SduDataPtr[6U] = 0U;                                                                  /* MSB of the number of segments, shall be set to zero as the max. number of segments is 255 */
    PduInfoPtr->SduDataPtr[7U] = AssuranceDataLength;                                                 /* Assurance Data Length */
    PduInfoPtr->SduDataPtr[8U] = AssuranceDataType;                                                   /* Assurance Data Type */
    PduInfoPtr->SduDataPtr[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                                         /* LSB of pgn */
    PduInfoPtr->SduDataPtr[10U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);                                     /* 2nd byte of pgn */
    PduInfoPtr->SduDataPtr[11U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);                                    /* MSB of pgn */

    if(AssuranceDataLength > 0U)
    {
        /* Assurance data present */
        PduLengthType tTxDataRem = 0U;
        PduInfoType tPduInfo = {NULL_PTR, 0U};
        tPduInfo.SduLength = (PduLengthType)AssuranceDataLength;
        tPduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[12U]);
        /*Retry mechanism for BAM is never supported. So retry parameter is always NULL_PTR for BAM */
        BufReq_Return = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, &tPduInfo, NULL_PTR, &tTxDataRem);
        switch (BufReq_Return)
        {
            case BUFREQ_OK:
            {
                uint8 MessageLength = AssuranceDataLength + J1939TP_CANFD_CONTROL_FRAME_LENGTH;
                uint8 i = 0U;
                /* Tr Timer is ON means previously PduR_J1939TpCopyTxData had returned BUFREQ_E_BUSY/BUFREQ_E_OVFL.
                * Now as PduR_J1939TpCopyTxData has returned BUFREQ_OK, we can stop this Tr timer */
                if(nsdu_ctrl_ptr->StartTrTime == TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = FALSE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }
                PduInfoPtr->SduLength = J1939Tp_FD_Transmit_Calculate_Frame_Size(MessageLength);

                /* Message padding if needed */
                for(i = MessageLength; i < PduInfoPtr->SduLength; i++)
                {
                    PduInfoPtr->SduDataPtr[i] = J1939TP_CANFD_PADDING;
                }

                break;
            }
            case BUFREQ_E_BUSY:
            case BUFREQ_E_OVFL:
            {
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
                /* Report to the upper layer */
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                    nsdu_ctrl_ptr->TrTimeout_SendAbort = TRUE;
                }
                TxBuff = E_NOT_OK;
                break;
            }
            default:
            {
                /* BUFREQ_E_NOT_OK*/
                /* Abort transmission and notify upper layer */
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_ABORT);
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                TxBuff = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        /* No assurance data configured, The frame length should be set to 12 */
        PduInfoPtr->SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
    }
    return TxBuff;
}

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_FD_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType = BUFREQ_E_NOT_OK;

    /*Remaining bytes to be transfered*/
    PduLengthType tTxDataRem = 0U;

    uint8 i, MetaDataInfo[4]={0U};
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 DtNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduMetaData;

    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2U);

    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType tPduInfo = {NULL_PTR, 0U};

    uint8 tBuf[60] = {0U};

    PduInfoType J1939TpTxPduInfo;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00068.Padding.BAM,1 */
    /* Add the 0xFF if that data value is not present for the data frame */
    uint8 frame[64];

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    /* For Issue 260555 */
    MetaDataInfo[0U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2U] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3U] = PrioBit;

    DBG_J1939TP_BAM_TRANSMIT_FD_DATA_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        J1939Tp_BAM_Transmit_Data_Timeout(loop_idx1,loop_idx2,loop_idx3);
    }
    /* If N-PDU is available,  */
    else if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable == TRUE)
    {
        /* For the state J1939TP_BAM_TX_STATE_DATA_TRANSMISSION*/
        if ((nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) > (uint8)J1939TP_MAX_CANFD_DT_MSGLENGTH)
        {
            tPduInfo.SduLength = J1939TP_MAX_CANFD_DT_MSGLENGTH;
        }
        else
        {
            tPduInfo.SduLength = (PduLengthType)nsdu_ctrl_ptr->msglength - (PduLengthType)nsdu_ctrl_ptr->data_cnt;
        }
        /* Initialize the data pointer */
        tPduInfo.SduDataPtr = &tBuf[0U];
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00219,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.BAM,1 */
        /*Retry mechanism for BAM is never supported. So retry parameter is always NULL_PTR for BAM */
        tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, &tPduInfo, NULL_PTR, &tTxDataRem);
        switch (tBufReq_ReturnType)
        {
            case BUFREQ_OK:
            {
                uint8 MessageLength = (uint8)tPduInfo.SduLength + (uint8)J1939TP_DT_CANFD_OVERHEAD_LENGTH;
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.BAM.DataAvailable,1 */
                /* !LINKSTO J1939Tp.SAE.FD.TP_DT.FrameFormat,1 */
                /* Prepared the DATA frame for BAM transmission */
                J1939TP_SET_SESSION_NUMBER(nsdu_ctrl_ptr->session_num, frame[0U]);
                frame[1U] = (uint8)nsdu_ctrl_ptr->sn;                    /* LSB of segment number */
                frame[2U] = 0U;                                          /* 2nd byte of segment number */
                frame[3U] = 0U;                                          /* MSB of segment number */

                /* Increment the sequence number */
                nsdu_ctrl_ptr->sn++;
                /* Copy the data for DATA frame */
                for(i = 0U; i < tPduInfo.SduLength; i++)
                {
                    frame[i + J1939TP_DT_CANFD_OVERHEAD_LENGTH] = (tPduInfo.SduDataPtr[i]);
                }
                nsdu_ctrl_ptr->data_cnt = (uint16)(nsdu_ctrl_ptr->data_cnt + tPduInfo.SduLength);

                /* Tr Timer is ON means previously PduR_J1939TpCopyTxData had returned BUFREQ_E_BUSY/BUFREQ_E_OVFL.
                * Now as PduR_J1939TpCopyTxData has returned BUFREQ_OK, we can stop this Tr timer */
                if(nsdu_ctrl_ptr->StartTrTime == TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = FALSE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }
                /* !LINKSTO EB_Ref.SAE.FD.TP_DT.DataField.Tx,1 */
                J1939TpTxPduInfo.SduLength = J1939Tp_FD_Transmit_Calculate_Frame_Size(MessageLength);

                /* Message padding if needed */
                for(i= MessageLength; i < J1939TpTxPduInfo.SduLength; i++)
                {
                    frame[i] = J1939TP_CANFD_PADDING;
                }

                break;
            }
            case BUFREQ_E_BUSY:
            case BUFREQ_E_OVFL:
            {
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
                /* Report to the upper layer */
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                    nsdu_ctrl_ptr->TrTimeout_SendAbort = TRUE;
                }
                break;
            }
            default:
            {
                /* BUFREQ_E_NOT_OK */
                /* Abort transmission and notify upper layer */
                /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.Data.Abort,1 */
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_ABORT);
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                break;
            }
        }
        if(BUFREQ_OK == tBufReq_ReturnType)
        {
            /* Start Tbammin timer */
            nsdu_ctrl_ptr->StartTbamminTime = TRUE;
            nsdu_ctrl_ptr->TbamminTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TbamminTimeCounter = 0U;
            J1939TpTxPduInfo.SduDataPtr = &frame[0U];

            if(DtNPduMetaData > 0U)
            {
                /* !LINKSTO J1939Tp.SAE.FD.TP_DT.Frame,1 */
                J1939Tp_NPduMetaData_Handle(DtNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_CANFD_TP_DT_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDtNPduTxConfIdEcuCPbcfg);
            }
            /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
            (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = FALSE;
            /* Change the state */
            /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.WaitConfirmation,1 */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif

            /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.DT.BAM,1 */
            /* Transmit the BAM DATA frame to CanIf */
            if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduTxConfIdCanIf, &J1939TpTxPduInfo))
            {
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
                /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
                J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
                /* indicate upper layer regarding the error */
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
            }
            else
            {
            }
        }
    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_BAM_TRANSMIT_FD_DATA_EXIT(loop_idx1,loop_idx2,loop_idx3);
}
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Reception_CopyRxData(P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,
uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType = BUFREQ_E_NOT_OK;
    PduInfoType J1939TpRxPduInfo;
    uint32 sn;

    /*Remaining bytes to be transfered*/
    PduLengthType tRxbufferSize = (PduLengthType)0U;

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    DBG_J1939TP_BAM_RECEPTION_COPYRXDATA_ENTRY(PduInfoPtr, loop_idx1, loop_idx2, loop_idx3);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport)
    {
        /* !LINKSTO J1939Tp.SAE.FD.TP_DT.FrameFormat,1 */
        /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.DT.Rx,1 */
        /* Set the length */
        J1939TpRxPduInfo.SduLength = (nsdu_ctrl_ptr->SduLength)-(PduLengthType)J1939TP_DT_CANFD_OVERHEAD_LENGTH;

        /* Initialize the data pointer added one to omit the sequence number and added three to omit the sequence number */
        J1939TpRxPduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[J1939TP_DT_CANFD_OVERHEAD_LENGTH]);

        sn = (uint32)(PduInfoPtr->SduDataPtr[1U]) + (uint32)((uint32)PduInfoPtr->SduDataPtr[2U] << 8U) + (uint32)((uint32)PduInfoPtr->SduDataPtr[3U] << 16U);
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        /* Set the length */
        J1939TpRxPduInfo.SduLength = (nsdu_ctrl_ptr->SduLength)-(PduLengthType)J1939TP_DT_OVERHEAD_LENGTH;

        /* Initialize the data pointer added one to omit the sequence number */
        J1939TpRxPduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[J1939TP_DT_OVERHEAD_LENGTH]);

        sn = PduInfoPtr->SduDataPtr[0U];
    }

    /* Count the data after each DT frame */
    nsdu_ctrl_ptr->data_cnt = (uint16)(nsdu_ctrl_ptr->data_cnt + J1939TpRxPduInfo.SduLength);
    if (nsdu_ctrl_ptr->sn == sn)
    {
        /* Increment the sequence number */
        nsdu_ctrl_ptr->sn++;
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00162.BAM,1 */
        /*Retry mechanism for BAM is never supported. So retry parameter is always NULL_PTR for BAM*/
        tBufReq_ReturnType = PduR_J1939TpCopyRxData(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,&J1939TpRxPduInfo,&tRxbufferSize);

        switch (tBufReq_ReturnType)
        {
            case BUFREQ_OK:
            {
                /* BUFREQ_OK*/
                if ((uint8)(nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) > 0U)
                {
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.DT.All,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_RX_STATE_WAIT_DATA);

                    /* Start the T1 Timer */
                    nsdu_ctrl_ptr->StartT1Time = TRUE;
                    nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                    nsdu_ctrl_ptr->T1TimeCounter = 0U;
                }
                else
                {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                    if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport)
                    {
                        /* Change the status to waiting for EOMS message */
                        /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.DT.End.EOMS,1 */
                        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_RX_STATE_BAM_WAIT_EOMS);
                        /* !LINKSTO J1939Tp.SAE.FD.BamTransfer.EOMS.TimeOut,1 */
                        /* Start the T1 Timer */
                        nsdu_ctrl_ptr->StartT1Time = TRUE;
                        nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                        nsdu_ctrl_ptr->T1TimeCounter = 0U;
                    }
                    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
                    {
                        /* Call notification function*/
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00118.BAM,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.Reset,1 */
                        PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_OK);

                        /* Change the state */
                        J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
                    }
                }
                break;
            }
            case BUFREQ_E_NOT_OK:
            case BUFREQ_E_OVFL:
            case BUFREQ_E_BUSY:
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00040.CopyRxData.BAM,2 */
                /* Other Than BUFREQ_OK*/
                /* Call notification function*/
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);

                /* Change the state */
                J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
                break;
            }
            default:
            {
                /* Nothing to do-4 */
                break;
            }
        }
    }
    else
    {
        /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SN */
        /* No retry for BAM connection in case a wrong SN is received */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_SN,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_SN);
#endif
        /* Abort Silently for sequence error and change the state idle */
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00192,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00232.BAM,1 */
        /* Reinitialization ****/
        J1939Tp_Reinit_Rx(loop_idx1,loop_idx2,loop_idx3);

        /* Set the error */
        nsdu_ctrl_ptr->error_code = E_NOT_OK;

        /* Call notification function*/
        PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);
    }
    DBG_J1939TP_BAM_RECEPTION_COPYRXDATA_EXIT(PduInfoPtr, loop_idx1, loop_idx2, loop_idx3);
}

/* J1939Tp_CMDT_Transmit*/
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables*/
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    DBG_J1939TP_CMDT_TRANSMIT_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    switch (nsdu_ctrl_ptr->state)
    {
        case J1939TP_CMDT_TX_STATE_RTS_SEND:
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00047.CMDT,1 */
            J1939Tp_CMDT_Transmit_RTS(loop_idx1,loop_idx2,loop_idx3);
            break;
        }

        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_RTS:
        {
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
            {
                /* TxConfirmation TimeOut elapsed */
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
                nsdu_ctrl_ptr->txconfirmation = TRUE;
                nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
            }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

            if ((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
            {
                /* Silent Abort- Report to the upper layer */

                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }

            break;
        }

        case J1939TP_CMDT_STATE_CTS:
        {
            /* For the state J1939TP_CMDT_STATE_CTS*/
            J1939Tp_CMDT_Wait_CTS(nsdu_ctrl_ptr);
            break;
        }

        case J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION:
        {
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
            {
                J1939Tp_CMDT_FD_Transmit_Data(loop_idx1,loop_idx2,loop_idx3);
            }
            else
#endif
            {
                J1939Tp_CMDT_Transmit_Data(loop_idx1,loop_idx2,loop_idx3);
            }
            break;
        }

        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA:
        {
            /* For the state J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA*/
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
            {
                /* TxConfirmation TimeOut elapsed */
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
                nsdu_ctrl_ptr->txconfirmation = TRUE;
                nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
            }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

            if ((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
            {
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00035,1 */
                /* Silent Abort- Report to the upper layer */
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }

        case J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK:
        {
            J1939Tp_CMDT_Wait_EOM(loop_idx1, loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_CMDT_TX_STATE_ABORT:
        {
            /* Send the Abort Frame - Call the local function to abort */
            J1939Tp_CMDT_Transmit_Send_Abort(loop_idx1, loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT:
        {
            /* For the state J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT*/
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
            {
                /* TxConfirmation TimeOut elapsed */
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
                nsdu_ctrl_ptr->txconfirmation = TRUE;
                nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
            }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

            if(nsdu_ctrl_ptr->txconfirmation == TRUE)
            {
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.Abort.Reset,1 */
                /* Call notification function*/
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        case J1939TP_CMDT_TX_STATE_EOMS_TRANSMISSION:
        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_EOMS:
        {
            J1939Tp_CMDT_EOMS_Handling(loop_idx1, loop_idx2, loop_idx3);
            break;
        }
#endif

        default:
        {
            /* Nothing to do */
            break;
        }
    }

    DBG_J1939TP_CMDT_TRANSMIT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_Data_Timeout(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_TR,1 */
    /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
    #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
    #endif
    /* Reset tr timeElapsed flag */
    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

    DBG_J1939TP_CMDT_TRANSMIT_DATA_TIMEOUT_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* Tr timeout due to PduR_J1939TpCopyTxData keep returns BUFREQ_E_BUSY */
    if (nsdu_ctrl_ptr->TrTimeout_SendAbort == TRUE)
    {
        nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00100.Tx.Tr,1 */
        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.DT.Timeout,1 */
        /* Abort transmission and notify upper layer */
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
        nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00032.CMDT,1 */
        /* Call notification function*/
        PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
        /* Reinitialization ****/
        J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
    }

    DBG_J1939TP_CMDT_TRANSMIT_DATA_TIMEOUT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_Data_Timeout(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_TR,1 */
    /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
    #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
    #endif
    /* Reset tr timeElapsed flag */
    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

    DBG_J1939TP_BAM_TRANSMIT_DATA_TIMEOUT_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* Tr timeout due to PduR_J1939TpCopyTxData keep returns BUFREQ_E_BUSY */
    if (nsdu_ctrl_ptr->TrTimeout_SendAbort == TRUE)
    {
        nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_ABORT);
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
        nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
    }
    else
    {
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_ABORT);
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
        nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
    }

    DBG_J1939TP_BAM_TRANSMIT_DATA_TIMEOUT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_RTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType = BUFREQ_E_NOT_OK;
    boolean BufferStatus = FALSE;

    uint8 MetaDataInfo[4U]={0x00,0x00,0x00,0x00};
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2U);

    /* Remaining bytes to be transfered - Call the Pdur Function StartOfReception */
    PduLengthType tRxbufferSize = 0U;

    /* The total length of the received NSDU */
    PduLengthType RxNsduLength = 0U;

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);
    P2CONST(J1939Tp_RxNSduTypePbcfg,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr_pbcfg  = &(((J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxPgPbcfg[loop_idx2]).J1939TpRxNSduPbcfg[loop_idx3]);

    uint8 metaDataPositionIdx;
    uint8 MetaDataLen = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCmNPduMetaDataLen;

    /* J1939TpRxSa: address of the Tx node, J1939TpRxDa: address of the Rx node*/
    MetaDataInfo[METADATA_SA_INDEX_0] = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxDaPbcfg;
    MetaDataInfo[METADATA_DA_INDEX_1] = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxSaPbcfg;
    MetaDataInfo[METADATA_PGN_INDEX_2] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[METADATA_PRIORITY_INDEX_3] = PrioBit;

    DBG_J1939Tp_CMDT_Reception_RTS_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* For the state J1939TP_CMDT_RX_STATE_RTS_RECEIVED*/
    /* get metadata for the received pdu*/

    for(metaDataPositionIdx=0U; metaDataPositionIdx < MetaDataLen; metaDataPositionIdx++)
    {
        MetaDataInfo[metaDataPositionIdx] = (uint8)nsdu_ctrl_ptr->J1939TpMetaDataInfo[metaDataPositionIdx];
    }

    MetaDataLen = nsdu_cfg_ptr->RxNsduMetaDataLen;
    if(MetaDataLen > 0U)
    {
        J1939Tp_SetEcuCMetaDataRx(MetaDataLen,MetaDataInfo,nsdu_cfg_ptr_pbcfg->J1939TpRxNSduIdEcuCPbcfg);
    }

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCanFDSupport)
    {
        if(J1939TP_DYNAMIC_ASSURANCE_DATA_LENGTH == nsdu_cfg_ptr->AssuranceDataLength)
        {
            /* The assurance data length is unknown/dynamic */
            /* !LINKSTO J1939Tp.EB.FD.AssuranceData.DynamicSduLength.Rx,1 */
            /* set the N-SDU length to 0 for the PduR_J1939TpStartOfReception */
            RxNsduLength = 0U;
        }
        else
        {
            /* The assurance data length is known */
            /* !LINKSTO J1939Tp.EB.FD.AssuranceData.DynamicSduLength.Rx,1 */
            /* The total N-SDU length is the message length received added to the assurance data length */
            RxNsduLength = (PduLengthType)((PduLengthType)nsdu_ctrl_ptr->msglength + (PduLengthType)nsdu_cfg_ptr->AssuranceDataLength);
        }
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        RxNsduLength = (PduLengthType)nsdu_ctrl_ptr->msglength;
    }

    /* !LINKSTO EB_Ref.SWS_J1939Tp_00038.RTS,1 */
    /* EB stack supports PduR AR403 where it takes only 3 parameters  */
    tBufReq_ReturnType = PduR_J1939TpStartOfReception(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,RxNsduLength,&tRxbufferSize);

    nsdu_ctrl_ptr->sn = 1U;
    nsdu_ctrl_ptr->RxNoPacketReceived = 0U;
    nsdu_ctrl_ptr->data_cnt = 0U;

    switch (tBufReq_ReturnType)
    {
        case BUFREQ_OK:
        {
            /* Calculation for number of packets for CTS frame.*/
            /* Number of packets that can be sent. This value shall be no larger than the value in byte 5(Maximum number of packets that can be sent in response to one CTS. 0xFF indicates that no limit exists for the originator.) of the RTS message. */

            /* !LINKSTO J1939Tp.SWS_J1939Tp_00210,1 */
            nsdu_ctrl_ptr->RxStartOfReceptionFlag = TRUE;
            nsdu_ctrl_ptr->RxStartOfReceptionResult = TRUE;
            if(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxRetrySupport == TRUE) &&
                ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxDynamicBlockCalculation == TRUE))
            {
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00212,1 */
                tRxbufferSize = (PduLengthType)((tRxbufferSize * (PduLengthType)(J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxDynamicBufferRatio)
                                 /J1939TP_BUFFER_MAX_PERCENT);
            }
            /* Calculate NrOfRxPacketsInCts */
            BufferStatus = J1939Tp_CheckAvailableBuffer(nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);

            if (BufferStatus == TRUE)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00227.StartOfReception.EnoughBuff,1 */
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CTS,1 */
                /* Change the state to J1939TP_CMDT_RX_STATE_CTS in order to send CTS frame in next MainFunction */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS);
            }
            else
            {

                /* tRxbufferSize returned in PduR_J1939TpStartOfReception is 0. So call J1939Tp_SendFCWait_CTS API to send CTS0 frame */
                J1939Tp_SendFCWait_CTS(loop_idx1, loop_idx2, loop_idx3);
            }
            break;
        }

        case BUFREQ_E_NOT_OK:
        case BUFREQ_E_OVFL:
        default:
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00173.StartOfReception.CMDT,2 */
            /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.RTS.Abort,1 */
            /* BUFREQ_E_NOT_OK or BUFREQ_E_OVFL*/
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.CanNotSupportAnotherSession,1 */
            /* Reception is abort and Sent the Abort Frame */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_CONNECTION;
            break;
        }
    }

    DBG_J1939Tp_CMDT_Reception_RTS_EXIT(loop_idx1,loop_idx2,loop_idx3);
}
static FUNC(boolean, J1939TP_CODE) J1939Tp_Calculate_MaxPacketsPerBlock(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) tPduInfo,P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) tBuf)
{
    /* Local Variables*/
    BufReq_ReturnType tBufReq_ReturnType;
    boolean SendRTS = FALSE;
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /*Remaining bytes to be transfered*/
    PduLengthType availabledataPtr = (PduLengthType)0U;
    uint32 NrOfPackets = 0U;

    DBG_J1939TP_CALCULATE_MAXPACKETSPERBLOCK_ENTRY(loop_idx1,loop_idx2,loop_idx3,tPduInfo,tBuf);

    if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDynamicBlockCalculation)
    {
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00165,1 */
        tPduInfo->SduLength = 0U;
        tPduInfo->SduDataPtr = &tBuf[0];

        tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, tPduInfo, NULL_PTR, &availabledataPtr);

        if((tBufReq_ReturnType == BUFREQ_OK) && (availabledataPtr != 0U))
        {
            SendRTS = TRUE;
            nsdu_ctrl_ptr->StartTrTime = FALSE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
            nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
            {
                if(availabledataPtr > nsdu_ctrl_ptr->msglength)
                {
                    /* In case the upper layer is ready to send all of the data including the Assurance Data */
                    /* Exclude the Assurance Data from the calculations */
                    availabledataPtr = (PduLengthType)(nsdu_ctrl_ptr->msglength);
                }
                NrOfPackets = (uint32)(((uint32)availabledataPtr) / ((uint32)J1939TP_MAX_CANFD_DT_MSGLENGTH));
                if((availabledataPtr % J1939TP_MAX_CANFD_DT_MSGLENGTH) != 0U)
                {
                    NrOfPackets = NrOfPackets + 1U;
                }
                else
                {
                    /* Nothing to do */
                }
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00207,1 */
                if(NrOfPackets > (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxMaxPacketsPerBlock)
                {
                    tBuf[7] = (uint8)(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxMaxPacketsPerBlock;
                }
                else
                {
                    tBuf[7] = (uint8)NrOfPackets;
                }
            }
            else
#endif
            {
                NrOfPackets = (uint8)(availabledataPtr / J1939TP_MAX_DT_MSGLENGTH);
                if ((availabledataPtr % J1939TP_MAX_DT_MSGLENGTH) != 0U)
                {
                    NrOfPackets = NrOfPackets + 1U;
                }
                else
                {
                    /* Nothing to do */
                }
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00207,1 */
                if((uint8)NrOfPackets > (uint8)((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxMaxPacketsPerBlock))
                {
                    tBuf[4] = (uint8)((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxMaxPacketsPerBlock);
                }
                else
                {
                    tBuf[4] = (uint8)NrOfPackets;
                }
            }
        }
        else if(tBufReq_ReturnType == BUFREQ_E_NOT_OK)
        {
            /* Abort transmission and notify upper layer */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
        }
        else
        {
            if(nsdu_ctrl_ptr->StartTrTime != TRUE)
            {
                nsdu_ctrl_ptr->StartTrTime = TRUE;
                nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                nsdu_ctrl_ptr->TrTimeCounter = 0U;
                nsdu_ctrl_ptr->TrTimeout_SendAbort = TRUE;
            }
        }
    }
    else
    {
        SendRTS = TRUE;
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00209,1 */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
        {
            tBuf[7] = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxMaxPacketsPerBlock;

        }
        else
#endif
        {
            tBuf[4] = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxMaxPacketsPerBlock;
        }
    }

    DBG_J1939TP_CALCULATE_MAXPACKETSPERBLOCK_EXIT(SendRTS,loop_idx1,loop_idx2,loop_idx3,tPduInfo,tBuf);

    /* End- Calculation of maximum number of packet field */
    return SendRTS;
}
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_Send_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    J1939TP_FrameStateType FrameState;
    J1939Tp_NsduAbortCtrlType Nsdu_AbortInfo ;
    J1939Tp_SaDa_Type SaDa;

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    Nsdu_AbortInfo.NsduCtrlPrt = nsdu_ctrl_ptr;
    Nsdu_AbortInfo.NsduNextState = J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT;

    DBG_J1939TP_CMDT_RECEPTION_SEND_ABORT_ENTRY(loop_idx1,loop_idx2,loop_idx3);
    /*RxChannel: Swap SA and DA */
    SaDa.J1939TpSa = nsdu_ctrl_ptr->da;
    SaDa.J1939TpDa = nsdu_ctrl_ptr->sa;
     /* !LINKSTO EB_Ref.SWS_J1939Tp_00097.Reception,1 */
#if ((J1939TP_TX_CANFD_SUPPORT == STD_OFF) && (J1939TP_RX_CANFD_SUPPORT == STD_OFF))
    FrameState = J1939Tp_Abort_Conn(nsdu_ctrl_ptr->AbortReason, NULL_PTR, (&(J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1])), nsdu_ctrl_ptr->pgn, SaDa,0u, &Nsdu_AbortInfo,loop_idx1);
#else
    FrameState = J1939Tp_Abort_Conn(nsdu_ctrl_ptr->AbortReason, NULL_PTR, (&(J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1])), nsdu_ctrl_ptr->pgn, SaDa, nsdu_ctrl_ptr->session_num, &Nsdu_AbortInfo,loop_idx1);
#endif
    if(FrameState == J1939TP_FRAME_SENT)
    {
       /* Already updated the state before calling CanIf_transmit as ealier confirmation may be received*/
    }
    else if (FrameState == J1939TP_FRAME_REJECTED)
    {
        /* Reinitialization ****/
        J1939Tp_Reinit_Rx(loop_idx1,loop_idx2,loop_idx3);
        /* Silently abort transmission and notify upper layer */
        /* Call notification function*/
        PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);

    }
    else
    {  /*FrameState == J1939TP_FRAME_PENDING*/
        if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
        {
            #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_TR);
            #endif
            /* Reset tr timeElapsed flag */
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

            /* Silently abort transmission and notify upper layer */
            /* Call notification function*/
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
            /* Reinitialization ****/
            J1939Tp_Reinit_Rx(loop_idx1,loop_idx2,loop_idx3);
        }
        /* Start Tr timer because maybe N-PDU will not be available */
        else if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_CMDT_RECEPTION_SEND_ABORT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_Send_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    J1939TP_FrameStateType FrameState;
    J1939Tp_NsduAbortCtrlType Nsdu_AbortInfo ;
    J1939Tp_SaDa_Type SaDa;
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    Nsdu_AbortInfo.NsduCtrlPrt = nsdu_ctrl_ptr;
    Nsdu_AbortInfo.NsduNextState = J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT;

    DBG_J1939TP_CMDT_TRANSMIT_SEND_ABORT_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* !LINKSTO EB_Ref.SWS_J1939Tp_00097.Transmission,1 */
    SaDa.J1939TpSa = nsdu_ctrl_ptr->sa;
    SaDa.J1939TpDa = nsdu_ctrl_ptr->da;
#if ((J1939TP_TX_CANFD_SUPPORT == STD_OFF) && (J1939TP_RX_CANFD_SUPPORT == STD_OFF))
    FrameState = J1939Tp_Abort_Conn(nsdu_ctrl_ptr->AbortReason, (&(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1])),NULL_PTR , nsdu_ctrl_ptr->pgn, SaDa,0u, &Nsdu_AbortInfo,loop_idx1);
#else
    FrameState = J1939Tp_Abort_Conn(nsdu_ctrl_ptr->AbortReason, (&(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1])),NULL_PTR , nsdu_ctrl_ptr->pgn, SaDa, nsdu_ctrl_ptr->session_num, &Nsdu_AbortInfo,loop_idx1);
#endif
    /* change the state */
    if(FrameState == J1939TP_FRAME_SENT)
    {
     /* Already updated the state before calling CanIf_transmit as ealier confirmation may be received*/
    }
    else if (FrameState == J1939TP_FRAME_REJECTED)
    {
        /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
        /* Silently abort transmission and notify upper layer */
        /* Call notification function*/
        PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
        /* Reinitialization ****/
        J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
    }
    else
    {  /*FrameState == J1939TP_FRAME_PENDING*/
        if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
        {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif
            /* Reset tr timeElapsed flag */
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

            /* Silently abort transmission and notify upper layer */
            /* Call notification function*/
            PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
            /* Reinitialization ****/
            J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
        }
        /* Start Tr timer because maybe N-PDU will not be available */
        else if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do-8 */
        }
    }

    DBG_J1939TP_CMDT_TRANSMIT_SEND_ABORT_EXIT(loop_idx1,loop_idx2,loop_idx3);

}

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Transmit_Send_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    J1939TP_FrameStateType FrameState;
    J1939Tp_NsduAbortCtrlType Nsdu_AbortInfo ;
    J1939Tp_SaDa_Type SaDa;
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    Nsdu_AbortInfo.NsduCtrlPrt = nsdu_ctrl_ptr;
    Nsdu_AbortInfo.NsduNextState = J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_ABORT;

    DBG_J1939TP_BAM_TRANSMIT_SEND_ABORT_ENTRY(loop_idx1,loop_idx2,loop_idx3);
    SaDa.J1939TpSa = nsdu_ctrl_ptr->sa;
    SaDa.J1939TpDa = 0xFF;
    FrameState = J1939Tp_Abort_Conn(nsdu_ctrl_ptr->AbortReason, (&(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1])),NULL_PTR , nsdu_ctrl_ptr->pgn, SaDa, nsdu_ctrl_ptr->session_num, &Nsdu_AbortInfo,loop_idx1);
    /* change the state */
    if(FrameState == J1939TP_FRAME_SENT)
    {
     /* Already updated the state before calling CanIf_transmit as ealier confirmation may be received*/
    }
    else if (FrameState == J1939TP_FRAME_REJECTED)
    {
        /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
        /* Reinitialization ****/
        J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
        /* Silently abort transmission and notify upper layer */
        /* Call notification function*/
        PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);

    }
    else
    { /*FrameState == J1939TP_FRAME_PENDING*/
        if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
        {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif
            /* Reset tr timeElapsed flag */
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

            /* Silently abort transmission and notify upper layer */
            /* Call notification function*/
            PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
            /* Reinitialization ****/
            J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
        }
        /* Start Tr timer because maybe N-PDU will not be available */
        else if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_BAM_TRANSMIT_SEND_ABORT_EXIT(loop_idx1,loop_idx2,loop_idx3);

}
#endif

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    P2VAR(RetryInfoType, AUTOMATIC, J1939TP_APPL_DATA) RetryInfoPtr = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxRetryInfo;
    uint8 i, MetaDataInfo[4];
    PduInfoType J1939TpTxPduInfo = {NULL_PTR,0U};
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 DtNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduMetaData;
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);
    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType tPduInfo = {NULL_PTR, 0U};
    /*Remaining bytes to be transfered*/
    PduLengthType availabledataPtr;
    BufReq_ReturnType tBufReq_ReturnType;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00068.Padding.CMDT,1 */
    /* Add the 0xFF if that data value is not present for the data frame */
    uint8 tData[8] ={0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu};
    uint8 tBuf[8] = {0U};
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);
    MetaDataInfo[0] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3] = PrioBit;

    DBG_J1939TP_CMDT_TRANSMIT_DATA_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.CMDT.timeout,1 */
        J1939Tp_CMDT_Transmit_Data_Timeout(loop_idx1,loop_idx2,loop_idx3);
    }
    /* If N-PDU is available,  */
    else if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable == TRUE)
    {
        /* For the state J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION*/
        if ((nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) > (uint8)7)
        {
            tPduInfo.SduLength = J1939TP_DATA_LENGTH;
        }
        else
        {
            tPduInfo.SduLength = (PduLengthType)(nsdu_ctrl_ptr->msglength) - (PduLengthType)(nsdu_ctrl_ptr->data_cnt);
        }
        tPduInfo.SduDataPtr = &tBuf[0];

        if(RetryInfoPtr != NULL_PTR)
        {
            if(nsdu_ctrl_ptr->retry_cts_flag == TRUE)
            {
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00221,1 */
                /* If retry flag is on, change TpDataState to TP_DATARETRY and set new TxTpDataCnt to data_cnt */
                nsdu_ctrl_ptr->retry_cts_flag = FALSE;
                RetryInfoPtr->TpDataState = TP_DATARETRY;
                RetryInfoPtr->TxTpDataCnt = (PduLengthType)(nsdu_ctrl_ptr->data_cnt);
            }
            else if(nsdu_ctrl_ptr->sn == 1U)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00217.FirstDT,1 */
                /* sn is 0 which means this is the first DT frame after reception of CTS. So initialize TpDataState as TP_DATACONF */
                RetryInfoPtr->TpDataState = TP_DATACONF;
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00217.NextDT,1 */
                /* sn is not 0 which means this is not first DT frame after reception of CTS. So assign TpDataState to TP_CONFPENDING */
                RetryInfoPtr->TpDataState = TP_CONFPENDING;
            }
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.CMDT.Retry,1 */
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00220,1 */
            tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,&tPduInfo,RetryInfoPtr, &availabledataPtr);
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.CMDT.NoRetry,1 */
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00218,1 */
            /*Retry mechanism is not enabled. So retry parameter is NULL_PTR */
            tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,&tPduInfo,NULL_PTR, &availabledataPtr);
        }

        switch (tBufReq_ReturnType)
        {
            case BUFREQ_OK:
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.CMDT.DataAvailable,1 */
                /* BUFREQ_OK*/
                /* Prepared the DATA frame for CMDT transmission */
                tData[0] = (uint8)nsdu_ctrl_ptr->sn; /* Sequence number- 1st byte of the data frame */
                if ( nsdu_ctrl_ptr->sn > J1939TP_SN_MAX)
                {
                    /* reset sequence number */
                    nsdu_ctrl_ptr->sn = 1U;
                }
                else
                {
                    /* Increment the sequence number */
                    nsdu_ctrl_ptr->sn++;
                }
                /* Copy the data for DATA frame */
                for (i=0U; i<tPduInfo.SduLength; i++)
                {
                    tData[i + 1U] = tPduInfo.SduDataPtr[i];
                    nsdu_ctrl_ptr->data_cnt++;
                }

                /* Tr Timer is ON means previously PduR_J1939TpCopyTxData had returned BUFREQ_E_BUSY/BUFREQ_E_OVFL.
            * Now as PduR_J1939TpCopyTxData has returned BUFREQ_OK, we can stop this Tr timer */
                if(nsdu_ctrl_ptr->StartTrTime == TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = FALSE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                    nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
                }

                /* Initialize the data pointer */
                J1939TpTxPduInfo.SduDataPtr = &tData[0];
                J1939TpTxPduInfo.SduLength = J1939TP_FRAME_LENGTH;

                if(DtNPduMetaData > 0U)
                {
                    J1939Tp_NPduMetaData_Handle(DtNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_TP_DT_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDtNPduTxConfIdEcuCPbcfg);
                }
                /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
                /* Lock DT PDU until J1939Tp_TxConfirmation is received for this PDU */
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = FALSE;
                nsdu_ctrl_ptr->cnt_packets++;

                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.DT.Sent,1 */
                /* Change the state */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.DT.CMDT,1 */
                /* Transmit the CMDT DATA frame to CanIf */
                if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduTxConfIdCanIf, &J1939TpTxPduInfo))
                {
                    /* Unlock DT PDU */
                    (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
                    nsdu_ctrl_ptr->cnt_packets--;
                    /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
                    J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
                    /* indicate upper layer regarding the error */
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                }
                else
                {
                }
                break;
            }
            case BUFREQ_E_BUSY:
            case BUFREQ_E_OVFL:
            {
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                    nsdu_ctrl_ptr->TrTimeout_SendAbort = TRUE;
                }
                break;
            }
            case BUFREQ_E_NOT_OK:
            {
                /* BUFREQ_E_NOT_OK*/
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CopyTxData.CMDT,1 */
                /* Abort transmission and notify upper layer */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                break;
            }
            default:
            {
                /* Nothing to do-7 */
                break;
            }
        }

    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
            nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_CMDT_TRANSMIT_DATA_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_CTS(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr)
{
    DBG_J1939TP_CMDT_WAIT_CTS_ENTRY(nsdu_ctrl_ptr);

    /* For the state J1939TP_CMDT_STATE_CTS*/
    if ((nsdu_ctrl_ptr->T3TimeElapsed != FALSE) ||(nsdu_ctrl_ptr->T4TimeElapsed != FALSE))
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_T4,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_T3 or J1939TP_E_TIMEOUT_T4 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        if(nsdu_ctrl_ptr->T4TimeElapsed != FALSE)
        { /* !LINKSTO EB_Ref.SWS_J1939Tp_00100.Tx.T4,1 */
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T4);
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00100.Tx.T3,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_T3,1 */
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T3);
        }
#endif
        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.CTS.Timeout,1 */
        /* Abort transmission and notify upper layer */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
        nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_CMDT_WAIT_CTS_EXIT(nsdu_ctrl_ptr);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_EOM(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables*/
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    DBG_J1939TP_CMDT_WAIT_EOM_ENTRY(loop_idx1,loop_idx2,loop_idx3);

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if(TRUE == ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport))
    {
        /* !LINKSTO J1939Tp.SAE.FD.TimingConstraints.Tx.T5,1 */
        if (TRUE == nsdu_ctrl_ptr->T5TimeElapsed)
        {
            /* !LINKSTO J1939Tp.EB.FD.TIMEOUT_T5,1 */
            /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_T5 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T5);
#endif
            /* Stop T5 timer */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
#endif
    {
        if (nsdu_ctrl_ptr->T3TimeElapsed == TRUE)
        {   /* !LINKSTO EB_Ref.SWS_J1939Tp_00100.Tx.T3,1 */
            /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_T3 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T3);
#endif
            /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.EOMACK.Timeout,1 */
            /* Stop T3 timer */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_CMDT_WAIT_EOM_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

/* J1939Tp_DirectPg_Transmit */
static FUNC(void, J1939TP_CODE) J1939Tp_DirectPg_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    DBG_J1939TP_DIRECTPG_TRANSMIT_ENTRY(loop_idx1, loop_idx2, loop_idx3);

    switch (nsdu_ctrl_ptr->state)
    {
        case J1939TP_DIRECTPG_TX_STATE_REQ:
        {
            J1939Tp_DirectPg_Data_Transmit(loop_idx1, loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_DIRECTPG_TX_STATE_WAIT_CONFIRMATION:
        {
            /* For the state J1939TP_DIRECTPG_TX_STATE_WAIT_CONFIRMATION*/
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
            {
                /* TxConfirmation TimeOut elapsed */
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
                nsdu_ctrl_ptr->txconfirmation = TRUE;
                nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
                ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDirectNPduAvailable[loop_idx2]) = TRUE;
            }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

            if(TRUE == nsdu_ctrl_ptr->txconfirmation)
            {
                if(E_OK == nsdu_ctrl_ptr->txconfirmationResult)
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00119.Trans.Direct,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.DirectPg.Tx.Reset,1 */
                    /*  "Report to the upper layer" */
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_OK);
                }
                else
                {
                    /* !LINKSTO J1939Tp.SWS_J1939Tp_00035,1 */
                    /* "Silent Abort" */
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
                }
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }

        default:
        {
            /* Nothing to do */
            break;
        }
    }

    DBG_J1939TP_DIRECTPG_TRANSMIT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

/* J1939Tp_DirectPg_Data_Transmit */
static FUNC(void, J1939TP_CODE) J1939Tp_DirectPg_Data_Transmit(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables*/
    BufReq_ReturnType tBufReq_ReturnType;

    /*Remaining bytes to be transfered*/
    PduLengthType tTxDataRem = 0U;
    uint8 i;
    uint8 MetaDataInfo[4];

    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType J1939TpTxPduInfo;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    uint8 tBuf[60] = {0U};
#else
    uint8 tBuf[8] = {0U};
#endif

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 DirectNPduMetaData = ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxDirectNPduMetaDataLen;

    MetaDataInfo[0] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3] = PrioBit;

    DBG_J1939TP_DIRECTPG_DATA_TRANSMIT_ENTRY(loop_idx1, loop_idx2, loop_idx3);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.Direct.Timeout,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif

        /* Reset tr timeElapsed flag */
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

        /* call reinit Tx so state also change to IDLE ***/
        J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00032.DirectPg,1 */
        /* indicate upper layer regarding the error */
        PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
    }
    /* If N-PDU is available,  */
    else if (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDirectNPduAvailable[loop_idx2]) == TRUE)
    {
        /* For the state J1939TP_DIRECTPG_TX_STATE_REQ */
        /* PduInfo which holds the transmit data and the length info */
        J1939TpTxPduInfo.SduLength = (PduLengthType)(nsdu_ctrl_ptr->msglength);

        J1939TpTxPduInfo.SduDataPtr = &tBuf[0];
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.DirectPg,1 */
        /*Retry mechanism for DirectPg is not supported. So retry parameter is always NULL_PTR */
        tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,&J1939TpTxPduInfo,NULL_PTR, &tTxDataRem);
        switch (tBufReq_ReturnType)
        {
            case BUFREQ_OK:
            {
                Std_ReturnType TxRet = E_NOT_OK;
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.Direct.DataAvailable,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00068.Padding.DirectPg,1 */
                /* BUFREQ_OK */
                /* Tr Timer is ON means previously N-Pdu was not available
                 * Now we can stop this Tr timer */
                if(nsdu_ctrl_ptr->StartTrTime == TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = FALSE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }

                if(DirectNPduMetaData > 0U)
                {
                    uint8 pgn = 0U;
                    (J1939TP_GET_PGN(nsdu_ctrl_ptr->pgn, pgn));
                    if(TRUE == J1939TP_PGN_PDU_2(pgn))
                    {
                        /* PDU2 Format */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
                        {
                            /* PDU2 Format for a CanFD transmission */
                            /* The destination should be reported to the IpduM for multi-PG operations */
                            /* no need to report the GE */
                            /* Global destination */
                            MetaDataInfo[1] = J1939TP_GLOBAL_ADDRESS;
                            nsdu_ctrl_ptr->J1939TpMetaDataInfo[1U] = J1939TP_GLOBAL_ADDRESS;
                        }
                        else
#endif
                        {
                            /* PDU2 Format for a classic Can transmission */
                            /* Store the Group extension in place of the destination */
                            /* !LINKSTO EB_Ref.SAE.PDU_Specific.PDU2,1 */
                            (J1939TP_GET_GE(nsdu_ctrl_ptr->pgn, MetaDataInfo[1U]));
                            (J1939TP_GET_GE(nsdu_ctrl_ptr->pgn, nsdu_ctrl_ptr->J1939TpMetaDataInfo[1U]));
                        }
                    }
                    else
                    {
                        /* PDU1 Format */
                        /* !LINKSTO EB_Ref.SAE.PDU_Specific.PDU1,1 */
                        /* The SA, DA should be put in the Can Id, as done before */
                        /* Do nothing */
                    }
                    J1939Tp_NPduMetaData_Handle(DirectNPduMetaData, TxNSduMetaData, nsdu_ctrl_ptr, MetaDataInfo, pgn, ((J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxPgPbcfg[loop_idx2]).J1939TpTxDirectNPduTxConfIdEcuCPbcfg);
                }
                /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
                /* Lock Direct PDU until J1939Tp_TxConfirmation is received for this PDU */
                ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDirectNPduAvailable[loop_idx2]) = FALSE;

                /* Change the state */
                /* !LINKSTO J1939Tp.EB.Dsn.DirectPg.Tx.WaitConfirmation,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_DIRECTPG_TX_STATE_WAIT_CONFIRMATION);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
                {
                    J1939TpTxPduInfo.SduLength = (PduLengthType)(nsdu_ctrl_ptr->msglength);
                    /* !LINKSTO J1939Tp.EB.FD.C_PGN.Tx,1 */
                    TxRet = PduR_J1939TpTransmit(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxDirectNPduTxConfIdTxIf, &J1939TpTxPduInfo);
                }
                else
#endif
                {
                    /* Add the 0xFF if that data value is not present for the data frame */
                    for (i = (uint8)J1939TpTxPduInfo.SduLength; i < J1939TP_FRAME_LENGTH ;i++)
                    {
                        J1939TpTxPduInfo.SduDataPtr[i] = J1939TP_UNUSED_BYTE_PADDING;
                    }
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.directPg,1 */
                    J1939TpTxPduInfo.SduLength = J1939TP_FRAME_LENGTH;
                    TxRet = CanIf_Transmit(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxDirectNPduTxConfIdTxIf, &J1939TpTxPduInfo);
                }

                /* Transmit the DIRECTPG DATA frame to CanIf */
                if(TxRet != E_OK)
                {
                    /* Unlock Direct PDU  */
                    ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDirectNPduAvailable[loop_idx2]) = TRUE;
                    /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
                    /* !LINKSTO J1939Tp.EB.PduR_J1939TpTransmit.Tx.ENOTOK,1 */
                    /* Silent Abort- Report to the upper layer */
                    J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);

                }
                else
                {
                }

                break;
            }
            case BUFREQ_E_BUSY:
            case BUFREQ_E_OVFL:
            {
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
                /* Report to the upper layer */
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }
                break;
            }
            case BUFREQ_E_NOT_OK:
            {
                /* BUFREQ_E_NOT_OK*/
                /* call reinit Tx so state also change to IDLE ***/
                J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CopyTxData.Direct,1 */
                /* indicate upper layer regarding the error */
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                break;
            }
            default:
            {
                /* Nothing to do-3 */
                break;
            }
        }
    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_DIRECTPG_DATA_TRANSMIT_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

/* J1939Tp_BAM_Reception */
static FUNC(void, J1939TP_CODE) J1939Tp_BAM_Reception(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType = BUFREQ_E_NOT_OK;

    /* Call the PduR Function StartOfReception */
    /*Remaining bytes to be transfered*/
    PduLengthType tRxbufferSize = (PduLengthType)0U;

    /* The total length of the received NSDU */
    PduLengthType RxNsduLength = 0U;

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);
    P2CONST(J1939Tp_RxNSduTypePbcfg,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr_pbcfg = &(((J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxPgPbcfg[loop_idx2]).J1939TpRxNSduPbcfg[loop_idx3]);

    uint8 metaDataPositionIdx;
    uint8 metaDataInfo[4]={0x00, 0x00, 0x00, 0x00};
    uint8 MetaDataLen = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCmNPduMetaDataLen;

    DBG_J1939TP_BAM_RECEPTION_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    switch (nsdu_ctrl_ptr->state)
    {
    case J1939TP_BAM_RX_STATE_NOTIFY_PDUR:
        {
            /* For the state J1939TP_BAM_RX_STATE_NOTIFY_PDUR*/
            /* get metadata for the received pdu*/
            for(metaDataPositionIdx=0U; metaDataPositionIdx < MetaDataLen; metaDataPositionIdx++)
            {
                metaDataInfo[metaDataPositionIdx] =(uint8)nsdu_ctrl_ptr->J1939TpMetaDataInfo[metaDataPositionIdx];
            }

            MetaDataLen = nsdu_cfg_ptr->RxNsduMetaDataLen;
            if(MetaDataLen > 0U)
            {
                J1939Tp_SetEcuCMetaDataRx(MetaDataLen,metaDataInfo,nsdu_cfg_ptr_pbcfg->J1939TpRxNSduIdEcuCPbcfg);
            }

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCanFDSupport)
            {
                if(J1939TP_DYNAMIC_ASSURANCE_DATA_LENGTH == nsdu_cfg_ptr->AssuranceDataLength)
                {
                    /* The assurance data length is unknown/dynamic */
                    /* !LINKSTO J1939Tp.EB.FD.AssuranceData.DynamicSduLength.Rx,1 */
                    /* set the N-SDU length to 0 for the PduR_J1939TpStartOfReception */
                    RxNsduLength = 0U;
                }
                else
                {
                    /* The assurance data length is known */
                    /* !LINKSTO J1939Tp.EB.FD.AssuranceData.StaticSduLength.Rx,1 */
                    /* The total N-SDU length is the message length received added to the assurance data length */
                    RxNsduLength = (PduLengthType)((PduLengthType)nsdu_ctrl_ptr->msglength + (PduLengthType)nsdu_cfg_ptr->AssuranceDataLength);
                }
            }
            else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
            {
                RxNsduLength = (PduLengthType)nsdu_ctrl_ptr->msglength;
            }

            /* !LINKSTO EB_Ref.SWS_J1939Tp_00038.CM_BAM,1 */
            /* EB stack supports PduR AR403 where it takes only 3 parameters  */
            tBufReq_ReturnType = PduR_J1939TpStartOfReception((PduIdType)(nsdu_cfg_ptr->J1939TpRxNSduIdPduR),RxNsduLength,&tRxbufferSize);

            nsdu_ctrl_ptr->data_cnt = 0U;

            nsdu_ctrl_ptr->sn = 1U;
            switch (tBufReq_ReturnType)
            {
                case BUFREQ_OK:
                {
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.DT.start,1 */
                    /* Change the state */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_RX_STATE_WAIT_DATA);
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00121.T1,1 */
                    /* Start the T1 Timer */
                    nsdu_ctrl_ptr->StartT1Time =TRUE;
                    nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                    nsdu_ctrl_ptr->T1TimeCounter = 0U;
                    break;
                }
                case BUFREQ_E_NOT_OK:
                case BUFREQ_E_OVFL:
                default:
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00173.StartOfReception.BAM,1 */
                    /* Silent abort connection */
                    /* Change the state to IDLE */
                    J1939Tp_Reinit_Rx(loop_idx1,loop_idx2,loop_idx3);
                    break;
                }

            }
            break;
        }
    case J1939TP_BAM_RX_STATE_WAIT_DATA:
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    case J1939TP_RX_STATE_BAM_WAIT_EOMS:
#endif
        {
            /* For the state J1939TP_BAM_RX_STATE_WAIT_DATA*/
            if(TRUE == nsdu_ctrl_ptr->T1TimeElapsed)
            {
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00160,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_T1,1 */
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_T1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T1);
#endif

                /* !LINKSTO EB_Ref.SWS_J1939Tp_00031.BAM,1 */
                /* Call notification function*/
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);

                /* Change the state */
                J1939Tp_Reinit_Rx(loop_idx1,loop_idx2,loop_idx3);
            }
            else
            {
                /* Nothing to do-3 */
            }
            break;
        }
    default:
        {
            /* Nothing to do-1 */
            break;
        }
    }
    DBG_J1939TP_BAM_RECEPTION_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

/* J1939Tp_CMDT_Reception*/
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    DBG_J1939TP_CMDT_RECEPTION_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    switch (nsdu_ctrl_ptr->state)
    {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        case J1939TP_RX_STATE_CMDT_WAIT_EOMS:
        {
            /* For the state J1939TP_RX_STATE_CMDT_WAIT_EOMS */
            J1939Tp_CMDT_Wait_EOMS(loop_idx1,loop_idx2,loop_idx3);
            break;
        }
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */

        case J1939TP_CMDT_RX_STATE_RTS_RECEIVED:
        {
            J1939Tp_CMDT_Reception_RTS(loop_idx1,loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_CMDT_RX_STATE_CTS:
        {
            J1939Tp_CMDT_Reception_CTS(loop_idx1,loop_idx2, loop_idx3, FALSE);
            break;
        }

        case J1939TP_CMDT_RX_STATE_CTS0:
        {
            /* For the state J1939TP_CMDT_RX_STATE_CTS0*/
            J1939Tp_CMDT_Reception_CTS0(loop_idx1,loop_idx2, loop_idx3);
            break;
        }

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        case J1939TP_RX_STATE_CMDT_WAIT_CONFIRMATION_EOMS_RQST:
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS:
        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS0:
        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_DATA_COMPLETE:
        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT:
        {
            J1939Tp_Rx_CMDT_Wait_TxConfirmation(loop_idx1, loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_CMDT_RX_STATE_WAIT_DATA:
        {
            /* For the state J1939TP_CMDT_RX_STATE_WAIT_DATA */
            J1939Tp_CMDT_Wait_Data(loop_idx1,loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_CMDT_RX_STATE_DATA_COMPLETE:
        {
            /* For the state J1939TP_CMDT_RX_STATE_DATA_COMPLETE */
            J1939Tp_CMDT_Reception_Data_Complete(loop_idx1,loop_idx2, loop_idx3);
            break;
        }

        case J1939TP_CMDT_RX_STATE_ABORT:
        {
            /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Reject.Rx,1 */
            J1939Tp_CMDT_Reception_Send_Abort(loop_idx1,loop_idx2,loop_idx3);
            break;
        }

        default:
        {
            /* Nothing to do */
            break;
        }
    }

    DBG_J1939TP_CMDT_RECEPTION_EXIT(loop_idx1, loop_idx2, loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_Rx_CMDT_Wait_TxConfirmation(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    DBG_J1939TP_RX_CMDT_WAIT_TXCONFIRMATION_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* For the state J1939TP_RX_STATE_CMDT_WAIT_CONFIRMATION_EOMS_RQST */
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
    {
        /* TxConfirmation TimeOut elapsed */
        nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
        nsdu_ctrl_ptr->txconfirmation = TRUE;
        nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
        (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;
    }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

    switch(nsdu_ctrl_ptr->state)
    {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        case J1939TP_RX_STATE_CMDT_WAIT_CONFIRMATION_EOMS_RQST:
#endif
        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS:
        {
            if((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
            {
                /* Silent Abort- Report to the upper layer */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00031.CMDT,1 */
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);
                /* change the state */
                J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }

        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS0:
        {
            if((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult == E_OK))
            {
                /* Got Confirmation, change the state */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS0);

                /* Reset the flag */
                nsdu_ctrl_ptr->txconfirmation = FALSE;
            }
            else if((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
            {
              /* Silent Abort- Report to the upper layer */
              PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);

              /* change the state */
              J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
            }
            else
            {
               /* Nothing to do */
            }
            break;
        }

        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_DATA_COMPLETE:
        {
            if((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult == E_OK))
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00118.CMDT,1 */
                /* Call notification function*/
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_OK);
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.Reset,1 */
                /* Change the state */
                J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
            }
            else if((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
            {
                /* Silent Abort- Report to the upper layer */
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
                J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }

        default:
        {
            /* J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT */
            if(nsdu_ctrl_ptr->txconfirmation == TRUE)
            {
            /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.Data.abort.Reset,1 */

                /* Call notification function if the connection established (PduR_J1939TpStartOfReception returned BUFREQ_OK) */
                if (TRUE == nsdu_ctrl_ptr->RxStartOfReceptionResult)
                {
                    PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
                }
                else
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00173.StartOfReception.CMDT,2 */
                    /* Do nothing, Connection Aborted due to PduR_J1939TpStartOfReception return BUFREQ_E_OVFL, BUFREQ_E_NOT_OK, or Invalid Value */
                    /* No report to the upper layer required as no established connection*/
                }

                /* Reinitialization ****/
                J1939Tp_Reinit_Rx(loop_idx1,loop_idx2,loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }
    }

    DBG_J1939TP_RX_CMDT_WAIT_TXCONFIRMATION_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_EOMS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);
    uint8 AssuranceDataType = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).AssuranceDataType);

    DBG_J1939TP_CMDT_WAIT_EOMS_ENTRY(loop_idx1, loop_idx2, loop_idx3);

    if(TRUE == nsdu_ctrl_ptr->T1TimeElapsed)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_T1,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_T1 */
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T1);
#endif
        nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
        if(FALSE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxRetrySupport)
        {
            /* Check if the retry is disabled to report E_NOT_OK to the upper layer in case of T1 timeout */
            if(J1939TP_NO_ASSURANCE_DATA == AssuranceDataType)
            {
                /* If no assurance data is configured, then Abort due to T1 time-out */
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00160,1 */
                /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Rx.EOMS.TimeOut.Elapsed.RetryDisabled.NoAssuranceData,1 */
                /* Reception is abort, Send the Abort Frame */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
            }
            else
            {
                /* If assurance data is configured, then Abort due to missing assurance data */
                /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Rx.EOMS.TimeOut.Elapsed.RetryDisabled.AssuranceData,1 */
                /* Reception is abort and Send the Abort Frame */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.AssuranceDataNotReceived,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_ASSURANCE_DATA_NOT_RECEIVED;
            }
        }
        else
        {
            /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Rx.EOMS.TimeOut.Elapsed.RetryEnabled,1 */
            /* T1 elapsed, if the retry is enabled, retry the request for the EOMS. */
            J1939Tp_CMDT_Reception_CTS(loop_idx1, loop_idx2, loop_idx3, TRUE);
        }
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_CMDT_WAIT_EOMS_EXIT(loop_idx1, loop_idx2, loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_EOMS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    DBG_J1939TP_RXINDICATION_CM_EOMS_ENTRY(loop_idx1, loop_idx2, loop_idx3, SduDataPtr);

    /* Check if the EOMS is expected, if not then ignore the message */
    if((J1939TP_RX_STATE_BAM_WAIT_EOMS == nsdu_ctrl_ptr->state) || (J1939TP_RX_STATE_CMDT_WAIT_EOMS == nsdu_ctrl_ptr->state))
    {
        /* Total message length and number of bytes supposed to be received */
        boolean ValidLength = FALSE;
        uint8 AssuranceDataLength = SduDataPtr[7U];
        boolean ValidType = (boolean)(nsdu_cfg_ptr->AssuranceDataType == SduDataPtr[8U]);
        uint32 RtsMsgLen = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U])<<8U) + (uint32)((uint32)(SduDataPtr[3U])<<16U));
        uint32 RtsNoOfPackets = (((uint32)(SduDataPtr[4U])) + (uint32)((uint32)(SduDataPtr[5U])<<8U) + (uint32)((uint32)(SduDataPtr[6U])<<16U));
        /* Check the Assurance Data type and length */
        switch(SduDataPtr[8U])
        {
            case J1939TP_NO_ASSURANCE_DATA:
            {
                if(0U == AssuranceDataLength)
                {
                    /* No assurance data and the length is set to 0 in the frame */
                    ValidLength = TRUE;
                }
                break;
            }
            case J1939TP_CYBERSECURITY_ASSURANCE_DATA:
            case J1939TP_FUNCTIONAL_SAFETY_ASSURANCE_DATA:
            case J1939TP_COMBINED_CYBERSECURITY_FUNCTIONAL_SAFETY_ASSURANCE_DATA:
            {
                if((0U != AssuranceDataLength)
                && ((AssuranceDataLength == nsdu_cfg_ptr->AssuranceDataLength)
                 || (J1939TP_DYNAMIC_ASSURANCE_DATA_LENGTH == nsdu_cfg_ptr->AssuranceDataLength)))
                {
                    /* The assurance data length is present with the precense of assurance data */
                    ValidLength = TRUE;
                }
                break;
            }
            default:
            {
                /* Unknown/Invalid Assurance Data Type, Do nothing */
                break;
            }
        }
        /* Check if the length reported in the EOMS is matching the current connection, if not then ignore the message */
        /* !LINKSTO J1939Tp.SAE.FD.TP_CM_EndOfMsgStatus.FrameFormat,1 */
        if((RtsMsgLen == nsdu_ctrl_ptr->msglength) && (RtsNoOfPackets == nsdu_ctrl_ptr->RxNoPacketsInRTS))
        {
            BufReq_ReturnType tBufReq_Return = BUFREQ_E_NOT_OK;
            /* Remaining bytes to be transfered */
            PduLengthType tRxbufferSize = (PduLengthType)0U;
            /* PduInfo which holds the received data and the length info */
            PduInfoType J1939TpRxPduInfo;
            if((J1939TP_RX_STATE_BAM_WAIT_EOMS == nsdu_ctrl_ptr->state) && (TRUE == ValidType) && (TRUE == ValidLength))
            {
                if(J1939TP_NO_ASSURANCE_DATA != SduDataPtr[8U])
                {
                    /* Assurance data exists for this N-SDU */
                    /* The data needs to be reported to the upper layer */
                    /* Set the length which is reported in the EOMS */
                    J1939TpRxPduInfo.SduLength = (PduLengthType)AssuranceDataLength;
                    /* Initialize the data pointer at the beginning of the assurance data */
                    J1939TpRxPduInfo.SduDataPtr = &SduDataPtr[12U];
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.FD.Rx.DataComplete.AssuranceData,1 */
                    tBufReq_Return = PduR_J1939TpCopyRxData(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, &J1939TpRxPduInfo, &tRxbufferSize);
                }
                else
                {
                    /* No Assurance data for this N-SDU */
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.FD.Rx.Reset.NoAssuranceData,1 */
                    tBufReq_Return = BUFREQ_OK;
                }

                if(tBufReq_Return == BUFREQ_OK)
                {
                    /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.EOMS.Rx,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.FD.Rx.Reset.AssuranceData,1 */
                    /* Indicate the upper layer */
                    PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_OK);
                    J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
                }
                else
                {
                    /* BUFREQ_E_NOT_OK */
                    /* BUFREQ_E_OVFL */
                    /* BUFREQ_E_BUSY */
                    /* Silent Abort */
                    /* Indicate the upper layer */
                    /* !LINKSTO J1939Tp.EB.FD.BAM.CopyAssuranceData.NOTOK,1 */
                    PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
                    J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
                }
            }
            else if((J1939TP_RX_STATE_CMDT_WAIT_EOMS == nsdu_ctrl_ptr->state) && (TRUE == ValidType) && (TRUE == ValidLength))
            {
                if(J1939TP_NO_ASSURANCE_DATA != SduDataPtr[8U])
                {
                    /* Assurance data exists for this N-SDU */
                    /* The data needs to be reported to the upper layer */
                    /* Set the length which is reported in the EOMS */
                    J1939TpRxPduInfo.SduLength = (PduLengthType)AssuranceDataLength;
                    /* Initialize the data pointer at the beginning of the assurance data */
                    J1939TpRxPduInfo.SduDataPtr = &SduDataPtr[12U];
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.FD.Rx.DataComplete.AssuranceData,1 */
                    tBufReq_Return = PduR_J1939TpCopyRxData(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, &J1939TpRxPduInfo, &tRxbufferSize);
                }
                else
                {
                    /* No Assurance data for this N-SDU */
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.FD.Rx.DataComplete.NoAssuranceData,1 */
                    tBufReq_Return = BUFREQ_OK;
                }

                if(tBufReq_Return == BUFREQ_OK)
                {
                    /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.EOMS.Rx,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.FD.Rx.AssuranceData.CopySuccess,1 */
                    nsdu_ctrl_ptr->retry_cts_flag = FALSE;
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_DATA_COMPLETE);
                }
                else
                {
                    /* BUFREQ_E_NOT_OK */
                    /* BUFREQ_E_OVFL */
                    /* BUFREQ_E_BUSY */
                    /* Reception is aborted and Sent the Abort Frame */
                    /* !LINKSTO J1939Tp.EB.FD.CMDT.CopyAssuranceData.NOTOK,1 */
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.FD.Rx.AssuranceData.CopyFail,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                    /* Call notification function*/
                    /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                    nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                }
            }
            else
            {
                /* Either the length or the type of assurance data received is mismatching */
                if(J1939TP_RX_STATE_BAM_WAIT_EOMS == nsdu_ctrl_ptr->state)
                {
                    /* Silent abort if BAM transfer is in progress */
                    /* Indicate the upper layer */
                    /* !LINKSTO J1939Tp.EB.FD.BAM.AssuranceData.MisMatch,1 */
                    PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
                    J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
                }
                else
                {
                    /* Abort if CMDT transfer is in progress */
                    /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.AssuranceDataMismatch,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                    nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_ASSURANCE_DATA_MISMATCH;
                }
            }
        }
    }

    DBG_J1939TP_RXINDICATION_CM_EOMS_EXIT(loop_idx1, loop_idx2, loop_idx3, SduDataPtr);
}
#endif /* J1939TP_RX_CANFD_SUPPORT == STD_ON */

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_CTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3, boolean request_EOMS)
{
    /* Local Variables */
    uint8 MetaDataInfo[4]={0x00,0x00,0x00,0x00};
    uint8 FcNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpTxFcNPduMetaDataLen;
    uint8 CmNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCmNPduMetaDataLen;
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);
    uint8 new_State;
    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType  J1939TpRxPduInfo;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    uint8 frame[12];
#else
    uint8 frame[8];
#endif
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);
    /* J1939TpRxSa: address of the Tx node, J1939TpRxDa: address of the Rx node*/
    MetaDataInfo[METADATA_SA_INDEX_0] = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxDaPbcfg;
    MetaDataInfo[METADATA_DA_INDEX_1] = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxSaPbcfg;
    MetaDataInfo[METADATA_PGN_INDEX_2] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[METADATA_PRIORITY_INDEX_3] = PrioBit;

#if (J1939TP_RX_CANFD_SUPPORT == STD_OFF)
    TS_PARAM_UNUSED(request_EOMS);
#endif

    DBG_J1939TP_CMDT_RECEPTION_CTS_ENTRY(loop_idx1, loop_idx2, loop_idx3, request_EOMS);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00159.Rx.Tr,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif

        /* Reset tr timeElapsed flag */
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

        /* Call notification function*/
        PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
        /* Reinitialization ****/
        J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
    }
    /* If N-PDU is available,  */
    else if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable == TRUE)
    {
        /* For the state J1939TP_CMDT_RX_STATE_CTS*/
        /* Send the CTS frame  */
        uint8 NrOfPackets = 0U;
        uint8 request_Code = 0U;
        uint32 Seq_num = 0U;
        NrOfPackets = J1939Tp_CMDT_Reception_CTS_Data(nsdu_ctrl_ptr, request_EOMS, &new_State, &request_Code, &Seq_num);

#if (J1939TP_RX_CANFD_SUPPORT == STD_OFF)
        TS_PARAM_UNUSED(request_Code);
#endif

        J1939TpRxPduInfo.SduDataPtr = &frame[0U];
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport))
        {
            /* !LINKSTO J1939Tp.SAE.FD.TP_CM_CTS.FrameFormat,1 */
            J1939TpRxPduInfo.SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
            frame[0U] = (uint8)((nsdu_ctrl_ptr->session_num << 4U) | (J1939TP_CANFD_TPCM_CTS)); /* Session number concatenated to control field */;
            frame[1U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Reserved for assignment by SAE */
            frame[2U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Reserved for assignment by SAE */
            frame[3U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Reserved for assignment by SAE */
            frame[4U] = (uint8)Seq_num;                                                         /* Next segment number to be sent */
            frame[5U] = (uint8)(Seq_num >> 8U);                                                 /* Next segment number to be sent */
            frame[6U] = (uint8)(Seq_num >> 16U);                                                /* Next segment number to be sent */
            frame[7U] = NrOfPackets;                                                            /* Number of segments that can be sent */
            /* !LINKSTO EB_Ref.SAE.FD.TP_CM_CTS.RequestCode.Rx,1 */
            frame[8U] = request_Code;                                                           /* Request code */
            frame[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                                            /* LSB of pgn for receive RTS */
            frame[10U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);                                        /* 2nd byte of pgn for receive RTS */
            frame[11U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);                                       /* MSB of pgn for receive RTS */
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            J1939TpRxPduInfo.SduLength = J1939TP_FRAME_LENGTH;
            frame[0U] = J1939TP_TPCM_CTS;
            frame[1U] = NrOfPackets;
            /* Next packet number to be sent */
            frame[2U] = (uint8)Seq_num;
            frame[3U] = J1939TP_UNUSED_BYTE_PADDING;
            frame[4U] = J1939TP_UNUSED_BYTE_PADDING;
            frame[5U] = (uint8)(nsdu_ctrl_ptr->pgn);       /* LSB of pgn for CTS frame */
            frame[6U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);    /* 2nd byte of pgn for CTS frame */
            frame[7U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);   /* MSB of pgn for CTS frame */
        }

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == request_EOMS)
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.T1,1 */
            /* Start T3 timer */
            nsdu_ctrl_ptr->StartT1Time = TRUE;
            nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
            nsdu_ctrl_ptr->T1TimeCounter = 0U;
        }
        else
#endif
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.T2,1 */
            /* Start T2 timer */
            nsdu_ctrl_ptr->StartT2Time = TRUE;
            nsdu_ctrl_ptr->T2TimeElapsed = FALSE;
            nsdu_ctrl_ptr->T2TimeCounter = 0U;
        }

        /* Tr Timer is ON means previously N-Pdu was not available
            * Now we can stop this Tr timer */
        if(nsdu_ctrl_ptr->StartTrTime == TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = FALSE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }

        if(FcNPduMetaData >0U)
        {
            J1939Tp_FCNPduMetaData_Handle(FcNPduMetaData ,CmNPduMetaData, nsdu_ctrl_ptr, MetaDataInfo, loop_idx1);
        }
        nsdu_ctrl_ptr->retry_cts_flag = FALSE;
        /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
        /* Lock Tx CTS PDU until J1939Tp_TxConfirmation is received for this PDU */
        (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable = FALSE;

        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CTS.Confirmation,1 */
        /* Change the state to Wait CTS frame Confirmation */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, new_State);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
        nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Accept.Rx,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.CM.CTS,1 */
        /* Send the CTS Frame */
        if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpTxCTSCanIf,&J1939TpRxPduInfo))
        {
            /* Unlock Tx CTS PDU */
            (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;
            /* !LINKSTO J1939Tp.EB.CanIfTransmit.Rx.ENOTOK,1 */
            /* Reinitialization ****/
            J1939Tp_Reinit_Rx(loop_idx1,loop_idx2, loop_idx3);
            /* Call notification function*/
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
        }
        else
        {
        }
    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.Tr,1 */
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_CMDT_RECEPTION_CTS_EXIT(loop_idx1, loop_idx2, loop_idx3, request_EOMS);
}

static FUNC(uint8, J1939TP_CODE) J1939Tp_CMDT_Reception_CTS_Data(P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr, boolean request_EOMS, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) new_State, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) request_Code, P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) Seq_num)
{
    /* Local Variables */
    uint8 NrOfPacketsInCts = 0U;
#if (J1939TP_RX_CANFD_SUPPORT == STD_OFF)
    TS_PARAM_UNUSED(request_EOMS);
    TS_PARAM_UNUSED(request_Code);
#endif

    DBG_J1939TP_CMDT_RECEPTION_CTS_DATA_ENTRY(nsdu_ctrl_ptr, request_EOMS, new_State, request_Code, Seq_num);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == request_EOMS)
    {
        *request_Code = 1U;
        /* No need to calculate the NrOfPacketsInCts nor the sequence num */
        NrOfPacketsInCts = J1939TP_UNUSED_BYTE_PADDING;
        *Seq_num = J1939TP_INVALID_SEQUENCE_NUMBER;
        *new_State = J1939TP_RX_STATE_CMDT_WAIT_CONFIRMATION_EOMS_RQST;
    }
    else
#endif
    {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        *request_Code = 0U;
#endif
        *Seq_num = nsdu_ctrl_ptr->sn;
        *new_State = J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS;
        if((nsdu_ctrl_ptr->RxNoPacketsInRTS - nsdu_ctrl_ptr->RxNoPacketReceived) >= nsdu_ctrl_ptr->NrOfRxPacketsInCts)
        {
            if(nsdu_ctrl_ptr->retry_cts_flag == TRUE)
            {
                if(nsdu_ctrl_ptr->RxNoPacketReceived < nsdu_ctrl_ptr->NrOfRxPacketsInCts)
                {
                    NrOfPacketsInCts = nsdu_ctrl_ptr->NrOfRxPacketsInCts - nsdu_ctrl_ptr->RxNoPacketReceived;
                }
                else
                {
                    NrOfPacketsInCts = nsdu_ctrl_ptr->NrOfRxPacketsInCts - (nsdu_ctrl_ptr->RxNoPacketReceived % nsdu_ctrl_ptr->NrOfRxPacketsInCts);
                }
            }
            else
            {
                NrOfPacketsInCts = nsdu_ctrl_ptr->NrOfRxPacketsInCts;
            }
        }
        else
        {
            NrOfPacketsInCts =  nsdu_ctrl_ptr->RxNoPacketsInRTS - nsdu_ctrl_ptr->RxNoPacketReceived;
        }
    }

    DBG_J1939TP_CMDT_RECEPTION_CTS_DATA_EXIT(nsdu_ctrl_ptr, request_EOMS, new_State, request_Code, Seq_num);

    return NrOfPacketsInCts;
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Wait_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    DBG_J1939TP_CMDT_WAIT_DATA_ENTRY(loop_idx1, loop_idx2, loop_idx3);

    if((nsdu_ctrl_ptr->T2TimeElapsed == TRUE) || (nsdu_ctrl_ptr->T1TimeElapsed == TRUE))
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_T2,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_T1 or J1939TP_E_TIMEOUT_T2 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        if(TRUE == nsdu_ctrl_ptr->T1TimeElapsed)
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00159.Rx.T1,1 */
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T1);
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00159.Rx.T2,1 */
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_T2);
        }
#endif
        /* Reception is abort and Send the Abort Frame */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
        nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_CMDT_WAIT_DATA_EXIT(loop_idx1, loop_idx2, loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Transmit_RTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables*/
    boolean SendRTS = FALSE;
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 CmNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCmNPduMetaData;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    uint8 tBuf[12U] = {0U};
#else
    uint8 tBuf[8U] = {0U};
#endif

    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType tPduInfo = {NULL_PTR, 0U};

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    DBG_J1939TP_CMDT_TRANSMIT_RTS_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif
        /* Send the Abort Frame - Call the local function to abort */
        /* Reset tr timeElapsed flag */
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

        /* Tr timeout due to PduR_J1939TpCopyTxData keep returns BUFREQ_E_BUSY */
        if (nsdu_ctrl_ptr->TrTimeout_SendAbort == TRUE)
        {
            nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
            /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.RTS.Timeout,1 */
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
            /* Abort transmission and notify upper layer */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;
        }
        /* Tr timeout due to CM Pdu is not available */
        else
        {
            /* Call notification function*/
            PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
            /* Reinitialization ****/
            J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
        }
    }
    /* If N-PDU is available,  */
    else if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable == TRUE)
    {
        /* Start- Calculation of maximum number of packet field */
        SendRTS = J1939Tp_Calculate_MaxPacketsPerBlock(loop_idx1, loop_idx2, loop_idx3, &tPduInfo, &tBuf[0U]);
        if(SendRTS == TRUE)
        {
            J1939Tp_CMDT_Build_RTS(&tBuf[0U], loop_idx1, loop_idx2, loop_idx3);
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
            {
                tPduInfo.SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
            }
            else
#endif
            {
                tPduInfo.SduLength = J1939TP_FRAME_LENGTH;
            }

            tPduInfo.SduDataPtr = &tBuf[0U];
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.T3,1 */
            /* Start T3 timer */
            nsdu_ctrl_ptr->StartT3Time = TRUE;
            nsdu_ctrl_ptr->T3TimeElapsed = FALSE;
            nsdu_ctrl_ptr->T3TimeCounter = 0U;

            if(CmNPduMetaData>0U)
            {
                uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2U);
                uint8 MetaDataInfo[4U]={0U};

                MetaDataInfo[0U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
                MetaDataInfo[1U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
                MetaDataInfo[2U] = J1939TP_UNUSED_BYTE_PADDING;
                MetaDataInfo[3U] = PrioBit;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
                {
                    J1939Tp_NPduMetaData_Handle(CmNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_CANFD_TP_CM_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxCmNPduTxConfIdEcuCPbcfg);
                }
                else
#endif
                {
                    J1939Tp_NPduMetaData_Handle(CmNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_TP_CM_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxCmNPduTxConfIdEcuCPbcfg);
                }
            }
            /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
            /* Lock CM PDU until J1939Tp_TxConfirmation is received for this PDU */
            (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = FALSE;
            /* Change the state */
            /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.RTS.Confirmation,1 */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_RTS);
            nsdu_ctrl_ptr->sn = 1U;
            nsdu_ctrl_ptr->data_cnt = 0U;
            nsdu_ctrl_ptr->cnt_packets = 0U;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.CM.RTS,1 */
            /* Transmit the RTS frame to CanIf */
            if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCmNPduTxRTSCanIf, &tPduInfo))
            {
                /* Unlock CM PDU Transmision failed */
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
                /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
                /* Reinitialization ****/
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
                /* Call notification function*/
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);

            }
            else
            {
            }
        }
    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
            nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
        }
        else
        {
            /* Tr started, Do nothing */
        }
    }

    DBG_J1939TP_CMDT_TRANSMIT_RTS_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Build_RTS(P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) tBuf, uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    uint32 Segments_Num = 0U;
    uint8 AssuranceDataType = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].AssuranceDataType;
#endif

    DBG_J1939TP_CMDT_BUILD_RTS_ENTRY(tBuf, loop_idx1, loop_idx2, loop_idx3);

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCanFDSupport)
    {
        Segments_Num = nsdu_ctrl_ptr->msglength / J1939TP_MAX_CANFD_DT_MSGLENGTH;
        if((nsdu_ctrl_ptr->msglength % J1939TP_MAX_CANFD_DT_MSGLENGTH) != 0U)
        {
            Segments_Num = Segments_Num +(uint32) 1U;
        }
        else
        {
            /* Nothing to do*/
        }
        /* For the state J1939TP_CMDT_TX_STATE_RTS_SEND*/
        /* Making RTS Frame */
        tBuf[0U] = (uint8)(nsdu_ctrl_ptr->session_num << 4U);             /* control byte of the RTS frame */
        tBuf[1U] = (uint8)nsdu_ctrl_ptr->msglength;                       /* LSB byte of the message length */
        tBuf[2U] = (uint8)(nsdu_ctrl_ptr->msglength >> 8U);               /* 2nd byte of the message length */
        tBuf[3U] = (uint8)(nsdu_ctrl_ptr->msglength >> 16U);              /* MSB byte of the message length */
        tBuf[4U] = (uint8)Segments_Num;                                   /* LSB byte of the Number of Segments */
        tBuf[5U] = (uint8)(Segments_Num >> 8U);                           /* 2nd byte of the Number of Segments */
        tBuf[6U] = (uint8)(Segments_Num >> 16U);                          /* MSB byte of the Number of Segments */
        tBuf[8U] = AssuranceDataType;                                     /* Assurance Data Type */
        tBuf[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                           /* LSB of pgn */
        tBuf[10U] = (uint8)(nsdu_ctrl_ptr->pgn >> 8U);                    /* 2nd byte of pgn */
        tBuf[11U] = (uint8)(nsdu_ctrl_ptr->pgn >> 16U);                   /* MSB of pgn */
        /* Take backup of maximum number of packets in nsdu_ctrl_ptr to compare it with byte 2 of CTS when CTS is received in RxIndication */
        nsdu_ctrl_ptr->RxNoPacketsInRTS = tBuf[7U];
    }
    else
#endif
    {
        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Initiation.Tx,1 */
        /* For the state J1939TP_CMDT_TX_STATE_RTS_SEND*/
        /* Making RTS Frame */
        tBuf[0U] = J1939TP_TPCM_RTS;                                              /* control byte of the RTS frame */
        tBuf[1U] = (uint8)nsdu_ctrl_ptr->msglength;                               /* LSB byte of the message length */
        tBuf[2U] = (uint8)(nsdu_ctrl_ptr->msglength >> 8U);                       /* MSB byte of the message length */
        tBuf[3U] = (uint8)(nsdu_ctrl_ptr->msglength / J1939TP_MAX_DT_MSGLENGTH);  /* number of packets */
        if((nsdu_ctrl_ptr->msglength % J1939TP_MAX_DT_MSGLENGTH) != 0U)
        {
            tBuf[3U] = tBuf[3U] + 1U;
        }
        else
        {
            /* Nothing to do */
        }
        tBuf[5U] = (uint8)(nsdu_ctrl_ptr->pgn);        /* LSB of pgn */
        tBuf[6U] = (uint8)(nsdu_ctrl_ptr->pgn >> 8U);  /* 2nd byte of pgn */
        tBuf[7U] = (uint8)(nsdu_ctrl_ptr->pgn >> 16U); /* MSB of pgn */
        /* Take backup of maximum number of packets in nsdu_ctrl_ptr to compare it with byte 2 of CTS when CTS is received in RxIndication */
        nsdu_ctrl_ptr->RxNoPacketsInRTS = tBuf[4U];
    }

    DBG_J1939TP_CMDT_BUILD_RTS_EXIT(tBuf, loop_idx1, loop_idx2, loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_CopyRxData(P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,
uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType = BUFREQ_E_NOT_OK;
    boolean BufferStatus = FALSE;
    /* PduInfo which holds the transmit data and the length info */
    PduInfoType J1939TpRxPduInfo;

    /* Remaining bytes to be transfered - Call the Pdur Function StartOfReception */
    PduLengthType tRxbufferSize = (PduLengthType)0U;

    /* Length of the overhead of the DT received */
    PduLengthType overheadLength = (PduLengthType)0U;

    /* Current sequence number */
    uint32 sn = 0U;

    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    DBG_J1939TP_CMDT_RECEPTION_COPYRXDATA_ENTRY(PduInfoPtr, loop_idx1, loop_idx2, loop_idx3);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport)
    {
        sn = (uint32)((uint32)PduInfoPtr->SduDataPtr[1U] + ((uint32)PduInfoPtr->SduDataPtr[2U] << 8U) + ((uint32)PduInfoPtr->SduDataPtr[3U] << 16U));
        overheadLength = J1939TP_DT_CANFD_OVERHEAD_LENGTH;
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        sn = (uint32)PduInfoPtr->SduDataPtr[0U];
        overheadLength = J1939TP_DT_OVERHEAD_LENGTH;
    }

    if ((nsdu_ctrl_ptr->sn == sn) && (FALSE == nsdu_ctrl_ptr->retry_cts_flag))
    {
        nsdu_ctrl_ptr->sn++;

        nsdu_ctrl_ptr->RxNoPacketReceived++;

        /* Set the length - Remove on byte as length as 1st byte sequence number not data */
        J1939TpRxPduInfo.SduLength = (PduLengthType)(nsdu_ctrl_ptr->SduLength) - overheadLength;

        /* Initialize the data pointer - increment the pointer as previous byte/s are overhead */
        J1939TpRxPduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[overheadLength]);
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00162.CMDT,1 */
        /*Retry mechanism for CMDT is not supported currently. So retry parameter is always NULL_PTR */
        tBufReq_ReturnType = PduR_J1939TpCopyRxData(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,&J1939TpRxPduInfo,&tRxbufferSize);
        if(tBufReq_ReturnType == BUFREQ_OK)
        {
            /* BUFREQ_OK*/
            /* Count the data after each DT frame */
            nsdu_ctrl_ptr->data_cnt = (uint16)(nsdu_ctrl_ptr->data_cnt + J1939TpRxPduInfo.SduLength);
            if ((nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) > 0U)
            {
                /* Here we are comparing No of DT packet received to No of packets set in the CTS */
                if (((nsdu_ctrl_ptr->RxNoPacketReceived)%(nsdu_ctrl_ptr->NrOfRxPacketsInCts)) != 0U)
                {
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.Dt.all,1 */
                    /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.DT.Rx,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_WAIT_DATA);

                    /* Start the T1 Timer */
                    nsdu_ctrl_ptr->StartT1Time =TRUE;
                    nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                    nsdu_ctrl_ptr->T1TimeCounter = 0U;
                }
                else
                {
                    BufferStatus = J1939Tp_CheckAvailableBuffer(nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);
                    if (BufferStatus == TRUE)
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00227.CopyRxData.EnoughBuff,1 */
                        /* Change the state to J1939TP_CMDT_RX_STATE_CTS in order to send CTS frame in next MainFunction */
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00226.NewCTS,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CTS.New,1 */
                        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.ContinueDT.Rx,1 */
                        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS);
                    }
                    else
                    {
                        /* Available buffer returned from PduR_J1939TpStartOfReception is less than block size. So call J1939Tp_SendFCWait_CTS API to send CTS0 frame */
                        J1939Tp_SendFCWait_CTS(loop_idx1, loop_idx2, loop_idx3);
                    }
                }
            }
            else
            {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport)
                {
                    /* Change the status to waiting for EOMS message */
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.DT.End.EOMS,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_RX_STATE_CMDT_WAIT_EOMS);
                    /* !LINKSTO J1939Tp.SAE.FD.CmdtTransfer.EOMS.TimeOut,1 */
                    /* Start the T1 Timer */
                    nsdu_ctrl_ptr->StartT1Time = TRUE;
                    nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                    nsdu_ctrl_ptr->T1TimeCounter = 0U;
                }
                else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
                {
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.Data.Com,1 */
                    nsdu_ctrl_ptr->retry_cts_flag = FALSE;
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_DATA_COMPLETE);
                }
            }
        }
        else
        {
            /* BUFREQ_E_NOT_OK */
            /* BUFREQ_E_OVFL */
            /* BUFREQ_E_BUSY */
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00040.CopyRxData.CMDT,1 */
            /* BUFREQ_E_NOT_OK or BUFREQ_E_OVFL   or BUFREQ_E_BUSY*/
            /* Reception is aborted and Sent the Abort Frame */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
            /* Call notification function*/
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
            /* Change the state */
        }
    }
    else
    {
        if(FALSE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxRetrySupport)
        {
          /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SN */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_SN);
#endif
          /* !LINKSTO EB_Ref.SWS_J1939Tp_00232.CMDT,1 */
          /* !LINKSTO J1939Tp.SWS_J1939Tp_00216,1 */
          /* Reception is abort and Sent the Abort Frame */
          J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
          /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.WrongSequenceNumberReceived,1 */
          nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_BAD_SEQUENCE_NUMBER;

          /* Set the error */
          nsdu_ctrl_ptr->error_code = E_NOT_OK;
        }
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00222,1 */
        else
        {
          nsdu_ctrl_ptr->retry_cts_flag = TRUE;
          /* Look for the SN of the last packet in the current block*/
          /* Check if the number of packets in CTS is less than that of the RTS
           * then the SN of the last packet is the Number of packets in CTS
           * else it will be the number of packets in RTS */
          if(nsdu_ctrl_ptr->NrOfRxPacketsInCts < nsdu_ctrl_ptr->RxNoPacketsInRTS)
          {
              /* Calculate the expected SN in case a wrong frame is received in a multi block transmission*/
              uint32 NrOfBlocksRcv = (uint32)(nsdu_ctrl_ptr->RxNoPacketReceived / ((uint32)(nsdu_ctrl_ptr->NrOfRxPacketsInCts) + 1U));
              uint32 NrOfPktsRcvThisBlock = nsdu_ctrl_ptr->NrOfRxPacketsInCts * NrOfBlocksRcv;
              if((((uint32)NrOfPktsRcvThisBlock + (uint32)nsdu_ctrl_ptr->NrOfRxPacketsInCts)) == sn)
              {
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS);
              }
              else
              {
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_WAIT_DATA);
                /* Start the T1 Timer */
                nsdu_ctrl_ptr->StartT1Time =TRUE;
                nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                nsdu_ctrl_ptr->T1TimeCounter = 0U;
              }
          }
          else
          {
              if(nsdu_ctrl_ptr->RxNoPacketsInRTS == sn)
              {
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS);
              }
              else
              {
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_WAIT_DATA);
                /* Start the T1 Timer */
                nsdu_ctrl_ptr->StartT1Time =TRUE;
                nsdu_ctrl_ptr->T1TimeElapsed = FALSE;
                nsdu_ctrl_ptr->T1TimeCounter = 0U;
              }
          }
        }
    }

    DBG_J1939TP_CMDT_RECEPTION_COPYRXDATA_EXIT(PduInfoPtr, loop_idx1, loop_idx2, loop_idx3);

}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_Data_Complete(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    J1939TP_FrameStateType FrameState;

    DBG_J1939TP_CMDT_RECEPTION_DATA_COMPLETE_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    FrameState = J1939Tp_EndOfMsgAck( loop_idx1,  loop_idx2,  loop_idx3) ;
    if(FrameState == J1939TP_FRAME_PENDING)
    {
        if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
        {
            /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
            #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_TR);
            #endif
            /* Reset tr timeElapsed flag */
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            /* Call notification function*/
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);
            J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
        }
        /* Start Tr timer because maybe N-PDU will not be available */
        else if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
    }

    DBG_J1939TP_CMDT_RECEPTION_DATA_COMPLETE_EXIT(loop_idx1,loop_idx2,loop_idx3);
}
static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_Reception_CTS0(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Local Variables */
    BufReq_ReturnType tBufReq_ReturnType = BUFREQ_E_NOT_OK;
    boolean BufferStatus = FALSE;
    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType  J1939TpRxPduInfo;
    /* Remaining bytes to be transfered - Call the Pdur Function StartOfReception */
    PduLengthType  tRxbufferSize = (PduLengthType)0;
    uint8 TempBuffer;
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

    DBG_J1939TP_CMDT_RECEPTION_CTS0_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    if (nsdu_ctrl_ptr->ThTimeElapsed == FALSE)
    {
        J1939TpRxPduInfo.SduDataPtr = &TempBuffer;
        J1939TpRxPduInfo.SduLength = 0U;

        tBufReq_ReturnType = PduR_J1939TpCopyRxData(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,&J1939TpRxPduInfo,&tRxbufferSize);
        switch (tBufReq_ReturnType)
        {
            case BUFREQ_OK:
            {
                BufferStatus = J1939Tp_CheckAvailableBuffer(nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);
                if (BufferStatus == TRUE)
                {
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CTS0.CTS,1 */
                    /* Change the state */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS);
                    /* Reset the timer */
                    nsdu_ctrl_ptr->StartThTime = FALSE;
                    nsdu_ctrl_ptr->ThTimeElapsed = FALSE;
                }
                break;
            }
            case BUFREQ_E_BUSY:
            /* Nothing to do, stay in the same state and again request for buffer */
            {
                break;
            }
            case BUFREQ_E_NOT_OK:
            case BUFREQ_E_OVFL:
            {
                /* Reception is abort and Sent the Abort Frame */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.Timeout,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_TIMEOUT;

                break;
            }
            default:
            {
                /* Nothing to do-6 */
                break;
            }
        }
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00227.StartOfReception.Timeout,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00227.CopyRxData.Timeout,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_TH,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TH */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00229.StartOfReception,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00229.CopyRxData,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_TH);
#endif
        /* Send CTS0 repeatedly as long as there is no enough buffer for reception */

        J1939Tp_SendFCWait_CTS(loop_idx1, loop_idx2, loop_idx3);
    }

    DBG_J1939TP_CMDT_RECEPTION_CTS0_EXIT(loop_idx1,loop_idx2,loop_idx3);

}
/* J1939Tp_NSDU_ChangeState */
static FUNC(void, J1939TP_CODE) J1939Tp_NSDU_ChangeState(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint8 new_state)
{

    DBG_J1939TP_NSDU_CHANGESTATE_ENTRY(nsdu_ctrl_ptr,new_state);

    switch (new_state)
    {
        /* When new state is IDLE or ABORT, change to them directly */
        case 0U:      /* J1939TP_TX_IDLE or J1939TP_RX_IDLE */
        case J1939TP_CMDT_TX_STATE_ABORT:
        case J1939TP_CMDT_RX_STATE_ABORT:
        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT:
        case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT:
        {
            nsdu_ctrl_ptr->state = new_state;
            break;
        }
        default:
        {
            /* guard to NSDU in Abort state to not return to any other state */
            /* CHECK: NOPARSE */
            if ((nsdu_ctrl_ptr->state != J1939TP_CMDT_TX_STATE_ABORT) &&
                (nsdu_ctrl_ptr->state != J1939TP_CMDT_RX_STATE_ABORT) &&
                (nsdu_ctrl_ptr->state != J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT) &&
                (nsdu_ctrl_ptr->state != J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT)
               )
            {
                nsdu_ctrl_ptr->state = new_state;
            }
            else
            {
                /* Do nothing as it is not possible to change SDU from abort state to any other state */
                /* it is already protected by design */
            }
            /* CHECK: PARSE */
            break;
        }
    }

    DBG_J1939TP_NSDU_CHANGESTATE_EXIT(nsdu_ctrl_ptr,new_state);
}
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
#if(J1939TP_TX_PARALLEL_CHANNEL_HANDLING == STD_OFF)
static FUNC(void, J1939TP_CODE) J1939Tp_PendingRequests_Handling(void)
#else
static FUNC(void, J1939TP_CODE) J1939Tp_PendingRequests_Handling(uint16 u16Ch_Idx)
#endif
{
    uint16 loop_idx1;
    uint16 loop_idx2;
    uint16 loop_idx3;
    boolean PendingNsduIsFound = FALSE;

    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_Checking_ctrl_ptr = NULL_PTR;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC, J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;

#if (J1939TP_TX_PARALLEL_CHANNEL_HANDLING == STD_OFF)
    for (loop_idx1=0U; (loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels)); loop_idx1++)
#else
    /* !LINKSTO J1939Tp.EB.J1939TpTxConcurent,1 */
    /* check only if there is same SA & DA transmission on-going for the selected channel, not in all channels */
    loop_idx1 = u16Ch_Idx;
#endif
    {
        /*Check Availablity of pending requests,then check the ongoing request status*/
        if(J1939Tp_GetPendingAvabilityStatus(loop_idx1) ==  PENDING_REQUEST_AVAILABLE)
        {
            /*Check if there is a pending connection for the same Sa/Da combination for any nsdu relative to the one that is about to be Reinitialized*/
            TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]);
            for (loop_idx2=0U;(loop_idx2<(TempPtrTxChannel->J1939TpNumberOfTxPg)) && (!PendingNsduIsFound);loop_idx2++)
            {
                for (loop_idx3=0U;(loop_idx3<(TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpNumberOfTxNSdu)&&(!PendingNsduIsFound);loop_idx3++)
                {
                    nsdu_Checking_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
                    if (nsdu_Checking_ctrl_ptr->state == J1939TP_BAM_TX_STATE_REQ_PENDING)
                    {
                        /*Found an NSDU with the same Sa/Da, change state from pending to normal state*/
                        J1939Tp_NSDU_ChangeState(nsdu_Checking_ctrl_ptr, J1939TP_BAM_TX_STATE_REQ);
                        J1939TpPendingRequestCount[loop_idx1]-- ;
                        if(J1939TpPendingRequestCount[loop_idx1] == 0U)
                        {
                            J1939TpSetPendingRequestAvaialblity(loop_idx1,NO_PENDING_REQUEST_AVAILABLE);                        
                        }
                        else
                        {
                        }
                        /*Pending NSDU Found*/
                        PendingNsduIsFound = TRUE ;
                    }
                    else
                    if (nsdu_Checking_ctrl_ptr->state == J1939TP_CMDT_TX_STATE_RTS_SEND_PENDING)
                    {
                        /*Found an NSDU with the same Sa/Da, change state from pending to normal state*/
                        J1939Tp_NSDU_ChangeState(nsdu_Checking_ctrl_ptr, J1939TP_CMDT_TX_STATE_RTS_SEND);
                        J1939TpPendingRequestCount[loop_idx1]-- ;
                        if(J1939TpPendingRequestCount[loop_idx1] == 0U)
                        {
                            J1939TpSetPendingRequestAvaialblity(loop_idx1,NO_PENDING_REQUEST_AVAILABLE);                        
                        }
                        else
                        {
                        }
                        /*Pending NSDU Found*/
                        PendingNsduIsFound = TRUE ;
                    }
                    else
                    {
                        /*Do nothing, there are no pending connections for nsdu with same SA/DA */
                    }
                }
            }
        }
        else
        {
        }
#if (J1939TP_TX_PARALLEL_CHANNEL_HANDLING == STD_OFF)        
        PendingNsduIsFound = FALSE ;
#endif
    }
}

static FUNC(boolean, J1939TP_CODE) J1939Tp_GetPendingAvabilityStatus(uint16 u16Ch_Idx)
{
    return J1939Tp_PendingRequestStatus[u16Ch_Idx] ;
}

static FUNC(void, J1939TP_CODE) J1939TpSetPendingRequestAvaialblity(uint16 u16Ch_Idx, boolean PendingStatus)
{
    J1939Tp_PendingRequestStatus[u16Ch_Idx] = PendingStatus ;
}
#endif
/* J1939Tp_Reinit_Tx*/
static FUNC(void, J1939TP_CODE) J1939Tp_Reinit_Tx(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx)
{
    /* Definition of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl);

    DBG_J1939TP_REINIT_TX_ENTRY(Chan_Idx,Pg_Idx,Nsdu_Idx);

    (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
    (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;

#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
    if((FALSE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)&&(nsdu_ctrl_ptr->IsMultipleFrameType == TRUE))
    {
#if(J1939TP_TX_PARALLEL_CHANNEL_HANDLING == STD_OFF)
        J1939Tp_PendingRequests_Handling();
#else
        J1939Tp_PendingRequests_Handling(Chan_Idx);
#endif
    }
    else
    {
        /* do nothing*/
    }
#endif
    /* Set nsdu object control data bytewise to 0x00. */
    nsdu_ctrl_ptr->SduLength = 0U;
    nsdu_ctrl_ptr->pgn = 0U;
    nsdu_ctrl_ptr->msglength = 0U;
    nsdu_ctrl_ptr->data_cnt = 0U;
    nsdu_ctrl_ptr->sn = 0U;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00062.Tx.Timer,1 */
    nsdu_ctrl_ptr->T1TimeCounter = 0U;
    nsdu_ctrl_ptr->T2TimeCounter = 0U;
    nsdu_ctrl_ptr->T3TimeCounter = 0U;
    nsdu_ctrl_ptr->T4TimeCounter = 0U;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    nsdu_ctrl_ptr->T5TimeCounter = 0U;
#endif
    nsdu_ctrl_ptr->ThTimeCounter = 0U;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00062.Tx.State,1 */
    nsdu_ctrl_ptr->state = 0U;
    nsdu_ctrl_ptr->error_code = 0U;
    nsdu_ctrl_ptr->cts_packets = 0U;
    nsdu_ctrl_ptr->cnt_packets = 0U;
    nsdu_ctrl_ptr->NrOfRxPacketsInCts= 0U;
    nsdu_ctrl_ptr->RxNoPacketsInRTS= 0U;
    nsdu_ctrl_ptr->RxNoPacketReceived= 0U;
    nsdu_ctrl_ptr->TbamminTimeElapsed= 0U;
    nsdu_ctrl_ptr->StartTbamminTime= 0U;
    nsdu_ctrl_ptr->TbamminTimeCounter= 0U;
    nsdu_ctrl_ptr->StartT3Time= 0U;
    nsdu_ctrl_ptr->T3TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartThTime= 0U;
    nsdu_ctrl_ptr->ThTimeElapsed= 0U;
    nsdu_ctrl_ptr->StartT4Time= 0U;
    nsdu_ctrl_ptr->T4TimeElapsed= 0U;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    nsdu_ctrl_ptr->StartT5Time= 0U;
    nsdu_ctrl_ptr->T5TimeElapsed= FALSE;
#endif
    nsdu_ctrl_ptr->StartT1Time= 0U;
    nsdu_ctrl_ptr->T1TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartT2Time= 0U;
    nsdu_ctrl_ptr->T2TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartTrTime= 0U;
    nsdu_ctrl_ptr->TrTimeElapsed= FALSE;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    nsdu_ctrl_ptr->StartTxConfirmationTimeOut= FALSE;
    nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed= FALSE;
#endif
    nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
    nsdu_ctrl_ptr->txconfirmation = 0U;
    nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
    nsdu_ctrl_ptr->SN_Confirmed_in_CTS = 0U;
    nsdu_ctrl_ptr->IsMultipleFrameType= FALSE;
    nsdu_ctrl_ptr->retry_cts_flag = FALSE;
    nsdu_ctrl_ptr->AbortReason = 0U;

    DBG_J1939TP_REINIT_TX_EXIT(Chan_Idx,Pg_Idx,Nsdu_Idx);
}
/* J1939Tp_Reinit_Rx*/
static FUNC(void, J1939TP_CODE) J1939Tp_Reinit_Rx(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx)
{
    /* Definition of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[Pg_Idx]).J1939TpRxNSdu[Nsdu_Idx]).J1939TpRxNSduCtrl);

    DBG_J1939TP_REINIT_RX_ENTRY(Chan_Idx,Pg_Idx,Nsdu_Idx);
    (J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;
    nsdu_ctrl_ptr->SduLength = 0U;
    nsdu_ctrl_ptr->pgn = 0U;
    nsdu_ctrl_ptr->msglength = 0U;
    nsdu_ctrl_ptr->data_cnt = 0U;
    nsdu_ctrl_ptr->sn = 0U;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00062.Rx.Timer,1 */
    nsdu_ctrl_ptr->T1TimeCounter = 0U;
    nsdu_ctrl_ptr->T2TimeCounter = 0U;
    nsdu_ctrl_ptr->T3TimeCounter = 0U;
    nsdu_ctrl_ptr->T4TimeCounter = 0U;
    nsdu_ctrl_ptr->ThTimeCounter = 0U;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00062.Rx.State,1 */
    nsdu_ctrl_ptr->state = 0U;
    nsdu_ctrl_ptr->error_code = 0U;
    nsdu_ctrl_ptr->cts_packets = 0U;
    nsdu_ctrl_ptr->cnt_packets = 0U;
    nsdu_ctrl_ptr->NrOfRxPacketsInCts= 0U;
    nsdu_ctrl_ptr->RxNoPacketsInRTS= 0U;
    nsdu_ctrl_ptr->RxNoPacketReceived= 0U;
    nsdu_ctrl_ptr->TbamminTimeElapsed= 0U;
    nsdu_ctrl_ptr->StartTbamminTime= 0U;
    nsdu_ctrl_ptr->TbamminTimeCounter= 0U;
    nsdu_ctrl_ptr->StartT3Time= 0U;
    nsdu_ctrl_ptr->T3TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartThTime= 0U;
    nsdu_ctrl_ptr->ThTimeElapsed= 0U;
    nsdu_ctrl_ptr->StartT4Time= 0U;
    nsdu_ctrl_ptr->T4TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartT1Time= 0U;
    nsdu_ctrl_ptr->T1TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartT2Time= 0U;
    nsdu_ctrl_ptr->T2TimeElapsed= 0U;
    nsdu_ctrl_ptr->StartTrTime= 0U;
    nsdu_ctrl_ptr->TrTimeElapsed= FALSE;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    nsdu_ctrl_ptr->StartTxConfirmationTimeOut= FALSE;
    nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed= FALSE;
#endif
    nsdu_ctrl_ptr->txconfirmation = 0U;
    nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
    nsdu_ctrl_ptr->sa = J1939TP_INVALID_ADDRESS;
    nsdu_ctrl_ptr->da = J1939TP_INVALID_ADDRESS;
    nsdu_ctrl_ptr->RxStartOfReceptionFlag = FALSE;
    nsdu_ctrl_ptr->RxStartOfReceptionResult = FALSE;
    nsdu_ctrl_ptr->AbortReason = 0U;
    nsdu_ctrl_ptr->retry_cts_flag = FALSE;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    nsdu_ctrl_ptr->session_num = J1939TP_INVALID_SESSION_NUMBER;
#endif

    DBG_J1939TP_REINIT_RX_EXIT(Chan_Idx,Pg_Idx,Nsdu_Idx);
}

/* J1939Tp_RxChannelAbortHandler */
/* Handle any abort frame on the channel not related to any N_SDU. */
static FUNC(void, J1939TP_CODE) J1939Tp_RxChannelAbortHandler(P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannel)
{   uint16 loop_idx1=0;
    J1939TP_FrameStateType FrameState;
    J1939Tp_NsduAbortCtrlType Nsdu_AbortInfo ;
    P2VAR(J1939Tp_ChannelAbortType, AUTOMATIC, J1939TP_APPL_DATA) ChannelAbort;
    J1939Tp_SaDa_Type SaDa;

    /* Definition of working pointer to selected NSdu control structure */
    ChannelAbort = RxChannel->J1939TpRxChannelAbort;

    Nsdu_AbortInfo.NsduCtrlPrt = NULL_PTR;
    Nsdu_AbortInfo.NsduNextState = J1939TP_IDLE;

    DBG_J1939TP_RXCHANNELABORTHANDLER_ENTRY(RxChannel);

    /* Wait confirmation if any abort frame is sent before checking for any other frame */
    if(ChannelAbort->txconfirmation == TRUE)
    {
        /* Reset the TxConfTimeout flag */
        ChannelAbort->txconfirmation = FALSE;
        /* Unlock Tx PDU to allow further transmissions */
        RxChannel->ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;
    }
    else if(ChannelAbort->AbortFlag == TRUE)
    {
        /* Send the Abort Frame - Call the local function to abort */
        SaDa.J1939TpSa = ChannelAbort->sa;
        SaDa.J1939TpDa = ChannelAbort->da;
#if ((J1939TP_TX_CANFD_SUPPORT == STD_OFF) && (J1939TP_RX_CANFD_SUPPORT == STD_OFF))
        FrameState = J1939Tp_Abort_Conn(ChannelAbort->AbortReason,NULL_PTR , RxChannel, ChannelAbort->pgn , SaDa, 0u,&Nsdu_AbortInfo,loop_idx1); /*RxChannel: Swap SA and DA */
#else
        FrameState = J1939Tp_Abort_Conn(ChannelAbort->AbortReason,NULL_PTR , RxChannel, ChannelAbort->pgn , SaDa, ChannelAbort->session_num,&Nsdu_AbortInfo,loop_idx1); /*RxChannel: Swap SA and DA */
#endif        /* Reinit ChannelAbortType struct */
        if( (FrameState == J1939TP_FRAME_SENT) || (FrameState == J1939TP_FRAME_REJECTED))
        {
            ChannelAbort->AbortFlag = FALSE;
            ChannelAbort->AbortReason = 0U;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            ChannelAbort->session_num = J1939TP_INVALID_SESSION_NUMBER;
#endif
            ChannelAbort->pgn = 0U;
            ChannelAbort->sa = J1939TP_INVALID_ADDRESS;
            ChannelAbort->da = J1939TP_INVALID_ADDRESS;
        }
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_RXCHANNELABORTHANDLER_EXIT(RxChannel);
}

/*J1939_AbortFrame_Build*/
static FUNC(void,J1939TP_CODE) J1939_AbortFrame_Build(P2VAR(uint8,AUTOMATIC,J1939TP_APPL_DATA) DataPtr, uint8 reason,uint32 pgn,uint8 session_num,boolean CanFDSupport)
{

    DBG_J1939TP_ABORT_FRAME_BUILD_ENTRY(DataPtr,reason,pgn,session_num,CanFDSupport);

#if ((J1939TP_TX_CANFD_SUPPORT == STD_OFF) && (J1939TP_RX_CANFD_SUPPORT == STD_OFF))
    TS_PARAM_UNUSED(session_num);
    TS_PARAM_UNUSED(CanFDSupport);
#endif

#if ((J1939TP_TX_CANFD_SUPPORT == STD_ON) || (J1939TP_RX_CANFD_SUPPORT == STD_ON))
    if(CanFDSupport)
    {
        /*CAN FD Support*/
        DataPtr[0U] = (uint8)((session_num << 4U) | (J1939TP_CANFD_TPCM_ABORT)); /* Session number concatenated to control field */;
        DataPtr[1U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[2U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[3U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[4U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[5U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[6U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[7U] = J1939TP_UNUSED_BYTE_PADDING;                               /* Reserved byte */
        DataPtr[8U] = reason;                                                    /* Connection abort reason byte */
        DataPtr[9U] = (uint8)(pgn);                                              /*LSB byte of pgn */
        DataPtr[10U] = (uint8)(pgn>>8);                                          /* 2nd byte of pgn */
        DataPtr[11U] = (uint8)(pgn>>16);                                         /* MSB byte of pgn*/
    }
    else
#endif
    {
        DataPtr[0U] = J1939TP_TPCM_ABORT;           /* Control byte of the Conn_Abort DataPtr */
        DataPtr[1U] = reason;                            /* Connection abort reason byte */
        DataPtr[2U] = J1939TP_UNUSED_BYTE_PADDING;  /* Reserved byte */
        DataPtr[3U] = J1939TP_UNUSED_BYTE_PADDING;  /* Reserved byte */
        DataPtr[4U] = J1939TP_UNUSED_BYTE_PADDING;  /* Reserved byte */
        DataPtr[5U] = (uint8)(pgn);                      /*LSB byte of pgn */
        DataPtr[6U] = (uint8)(pgn>>8);                   /* 2nd byte of pgn */
        DataPtr[7U] = (uint8)(pgn>>16);                  /* MSB byte of pgn*/
    }

    DBG_J1939TP_ABORT_FRAME_BUILD_EXIT(DataPtr,reason,pgn,session_num,CanFDSupport);
}

static FUNC(J1939TP_FrameStateType, J1939TP_CODE) J1939Tp_Abort_Conn(uint8 reason, P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TxChannel, P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannel, uint32 pgn, J1939Tp_SaDa_Type SaDa, uint8 session_num, P2VAR(J1939Tp_NsduAbortCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_abort_ptr,uint16 ChannelNumber)
{
    /* Local Variables*/
    PduIdType Id, EcuCId;
#if ((J1939TP_TX_CANFD_SUPPORT == STD_ON) || (J1939TP_RX_CANFD_SUPPORT == STD_ON))
    uint8 frame[12U]={0U};
    boolean CanFDSupport = FALSE;
#else
    uint8 frame[8U]={0U};
#endif
    uint8 MetaDataLen, MetaDataInfo[4U]={0U};
    PduInfoType J1939TpPduInfo, PduInfoTemp;
    P2VAR(boolean, AUTOMATIC, J1939TP_APPL_DATA) PduAvailable = NULL_PTR;
    P2VAR(boolean, AUTOMATIC, J1939TP_APPL_DATA) TxConfirmation = NULL_PTR;
    J1939TP_FrameStateType FrameState = J1939TP_FRAME_PENDING;
    uint32 metaDataCanId=0x00000000;
    sint8 metaDataPositionIdx;
    Std_ReturnType EcuC_Ret = E_OK;
    uint8 metaDataShiftVal = (uint8)0U;
    uint32 currMetaDataVal = (uint32)0U;

#if ((J1939TP_TX_CANFD_SUPPORT == STD_OFF) && (J1939TP_RX_CANFD_SUPPORT == STD_OFF))
    TS_PARAM_UNUSED(session_num);
#endif

    DBG_J1939TP_ABORT_CONN_ENTRY(reason,TxChannel,RxChannel,pgn,SaDa,session_num,nsdu_abort_ptr,ChannelNumber);
    if(TxChannel != NULL_PTR)
    {
        /* Abort Connection is called for a TxChannel */
        MetaDataLen = TxChannel->J1939TpTxCmNPduMetaData;
        Id = TxChannel->J1939TpTxCmNPduTxRTSCanIf;
        PduAvailable = &(TxChannel->ChannelStatus->J1939TpTxCmNPduAvailable);
        TxConfirmation = &(TxChannel->J1939TpTxPg->J1939TpTxNSdu->J1939TpTxNSduCtrl->txconfirmation);
        EcuCId = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[ChannelNumber]).J1939TpTxCmNPduTxConfIdEcuCPbcfg;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        CanFDSupport = TxChannel->J1939TpTxCanFDSupport;
#endif
    }
    else
    {
        /* Abort Connection is called for an RxChannel */
        MetaDataLen = RxChannel->J1939TpTxFcNPduMetaDataLen;
        Id = RxChannel->J1939TpTxCTSCanIf;
        PduAvailable = &(RxChannel->ChannelStatus->J1939TpTxFcNPduAvailable);
        TxConfirmation = &(RxChannel->J1939TpRxChannelAbort->txconfirmation);
        EcuCId = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[ChannelNumber]).J1939TpTxFcNPduRxConfIdEcuCPbcfg;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        CanFDSupport = RxChannel->J1939TpRxCanFDSupport;
#endif
    }

    /* If N-PDU is available,  */
    if(*(PduAvailable) == TRUE)
    {
        uint8 Cm_pgn;
        MetaDataInfo[METADATA_SA_INDEX_0] = SaDa.J1939TpSa;
        MetaDataInfo[METADATA_DA_INDEX_1] = SaDa.J1939TpDa;
        MetaDataInfo[METADATA_PRIORITY_INDEX_3] = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);

        J1939TpPduInfo.SduDataPtr = &frame[0U];
#if ((J1939TP_TX_CANFD_SUPPORT == STD_ON) || (J1939TP_RX_CANFD_SUPPORT == STD_ON))
        if(TRUE == CanFDSupport)
        {
            /* !LINKSTO J1939Tp.SAE.FD.Conn_Abort.FrameFormat,1 */
            J1939TpPduInfo.SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
            /*Construct Abort Frame*/
            J1939_AbortFrame_Build(frame,reason,pgn,session_num,CanFDSupport);
            /* !LINKSTO J1939Tp.SAE.FD.TP_CM.Frame,1 */
            Cm_pgn = J1939TP_CANFD_TP_CM_PGN;
        }
        else
#endif /* ((J1939TP_TX_CANFD_SUPPORT == STD_ON) || (J1939TP_RX_CANFD_SUPPORT == STD_ON)) */
        {
            J1939TpPduInfo.SduLength = J1939TP_FRAME_LENGTH;
            /*Construct Abort Frame*/
            J1939_AbortFrame_Build(frame,reason,pgn,(uint8)0U,FALSE);
            Cm_pgn = J1939TP_TP_CM_PGN;
        }

        if(MetaDataLen == (uint8)4U)
        {
            MetaDataInfo[METADATA_PGN_INDEX_2] = Cm_pgn;
        }

        /* get related canid. */
        for(metaDataPositionIdx=3;metaDataPositionIdx>=0;metaDataPositionIdx--)
        {
            metaDataShiftVal= metaDataPositionIdx*8;
            currMetaDataVal=(uint32)MetaDataInfo[metaDataPositionIdx];
            currMetaDataVal <<= metaDataShiftVal;
            metaDataCanId |= (currMetaDataVal);
        }

        if(MetaDataLen >0U)
        {
            EcuC_Ret=EcuC_SetMetaDataCanId(EcuCId,&PduInfoTemp,metaDataCanId);
        }

        if(EcuC_Ret==E_OK)
        {
            /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
            if((nsdu_abort_ptr != NULL_PTR) && ((nsdu_abort_ptr->NsduCtrlPrt != NULL_PTR) || (nsdu_abort_ptr->NsduNextState != J1939TP_IDLE)) )
            {
                /* Reset Tr timer */
                nsdu_abort_ptr->NsduCtrlPrt->StartTrTime = FALSE;
                nsdu_abort_ptr->NsduCtrlPrt->TrTimeElapsed = FALSE;
                nsdu_abort_ptr->NsduCtrlPrt->TrTimeCounter = 0U;
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.Data.abort.Confirm,1 */
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.Abort.Sent,1 */
                J1939Tp_NSDU_ChangeState(nsdu_abort_ptr->NsduCtrlPrt, nsdu_abort_ptr->NsduNextState);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
                nsdu_abort_ptr->NsduCtrlPrt->StartTxConfirmationTimeOut = TRUE;
                nsdu_abort_ptr->NsduCtrlPrt->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_abort_ptr->NsduCtrlPrt->TxConfirmationTimeOutCounter = 0U;
#endif
                /* Lock PDU until J1939Tp_TxConfirmation is received for this PDU */
                *(PduAvailable) = FALSE;
                *(TxConfirmation) = FALSE;
            }

            /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.CM.Abort,1 */
            /* Send the Abort Frame */
            if(E_OK != CanIf_Transmit(Id,&J1939TpPduInfo))
            {
                FrameState = J1939TP_FRAME_REJECTED;
                /* Unlock PDU as CanIf returned E_NOT_OK */
                *(PduAvailable) = TRUE;
                *(TxConfirmation) = TRUE;
            }
            else
            {
                FrameState = J1939TP_FRAME_SENT;
            }
        }
        else
        {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
        }

    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_ABORT_CONN_EXIT(reason,TxChannel,RxChannel,pgn,SaDa,session_num,nsdu_abort_ptr,ChannelNumber);

    return FrameState;
}

/* J1939Tp_EndOfMsgAck*/
static FUNC(J1939TP_FrameStateType, J1939TP_CODE) J1939Tp_EndOfMsgAck( uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)

{
    /* Initialization of working pointer to selected NSdu control structure */
    J1939Tp_NSduCtrlType * nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2].J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl);
    J1939Tp_RxChannelType * RxChannel = &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]);
    const J1939Tp_RxChannelTypePbcfg * RxChannelPbcfg = &(J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]);
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);
    /* Local Variables*/
    PduIdType Id = RxChannel->J1939TpTxCTSCanIf;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    uint8 frame[12];
#else
    uint8 frame[8];
#endif
    uint8 MetaDataLen;
    PduInfoType J1939TpPduInfo;
    J1939TP_FrameStateType EndOfMsgAckState = J1939TP_FRAME_PENDING;
    sint8 metaDataPositionIdx;
    uint32 metaDataCanId=0x00000000;
    uint8 MetaDataInfo[4]={0xff,0xff,0xff,0xff};
    Std_ReturnType EcuC_Ret = E_OK;
    PduInfoType PduInfoTemp;
    uint8 metaDataShiftVal = (uint8)0U;
    uint8 pgn = (uint8)0U;
    uint32 currMetaDataVal = (uint32)0U;

    DBG_J1939TP_ENDOFMSGACK_ENTRY(loop_idx1, loop_idx2, loop_idx3);

    /* If N-PDU is available,  */
    if (RxChannel->ChannelStatus->J1939TpTxFcNPduAvailable == TRUE)
    {
        MetaDataLen = RxChannel->J1939TpTxFcNPduMetaDataLen;
        J1939TpPduInfo.SduDataPtr = &frame[0U];
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (RxChannel->J1939TpRxCanFDSupport))
        {
            /* !LINKSTO J1939Tp.SAE.FD.TP_CM_EndOfMsgACK.FrameFormat,1 */
            J1939TpPduInfo.SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
            frame[0U] = (uint8)((nsdu_ctrl_ptr->session_num << 4U) | (J1939TP_CANFD_TPCM_ENDOFMSGACK)); /* Session number concatenated to control field */;
            frame[1U] = (uint8)(nsdu_ctrl_ptr->msglength);                                              /* LSB byte of the message length */
            frame[2U] = (uint8)(nsdu_ctrl_ptr->msglength>>8);                                           /* 2nd byte of the message length */
            frame[3U] = (uint8)(nsdu_ctrl_ptr->msglength>>16);                                          /* MSB byte of the message length */
            frame[4U] = (uint8)(nsdu_ctrl_ptr->RxNoPacketsInRTS);                                       /* LSB byte of number of packets */
            frame[5U] = (uint8)(nsdu_ctrl_ptr->RxNoPacketsInRTS>>8);                                    /* 2nd byte of number of packets */
            frame[6U] = (uint8)(nsdu_ctrl_ptr->RxNoPacketsInRTS>>16);                                   /* MSB byte of number of packets */
            frame[7U] = J1939TP_UNUSED_BYTE_PADDING;                                                    /* Reserved for assignment by SAE */
            frame[8U] = J1939TP_UNUSED_BYTE_PADDING;                                                    /* Reserved for assignment by SAE */
            frame[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                                                    /* LSB of pgn for receive RTS */
            frame[10U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);                                                /* 2nd byte of pgn for receive RTS */
            frame[11U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);                                               /* MSB of pgn for receive RTS */
            /* !LINKSTO J1939Tp.SAE.FD.TP_CM.Frame,1 */
            pgn = J1939TP_CANFD_TP_CM_PGN;
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            J1939TpPduInfo.SduLength = J1939TP_FRAME_LENGTH;
            frame[0U] = J1939TP_TPCM_ENDOFMSGACK;                      /* Control byte of the ENDOFMSGACK frame */
            frame[1U] = (uint8)(nsdu_ctrl_ptr->msglength);             /* LSB byte of the message length */
            frame[2U] = (uint8)(nsdu_ctrl_ptr->msglength>>8);          /* MSB byte of the message length */
            frame[3U] = (uint8)(nsdu_ctrl_ptr->RxNoPacketsInRTS);      /* number of packets */
            frame[4U] = J1939TP_UNUSED_BYTE_PADDING;                   /* Reserved byte */
            frame[5U] = (uint8)(nsdu_ctrl_ptr->pgn);                   /* LSB byte of pgn */
            frame[6U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);                /* 2nd byte of pgn */
            frame[7U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);               /* MSB byte of pgn*/
            pgn = J1939TP_TP_CM_PGN;
        }
        if (MetaDataLen != 0U)
        {
            MetaDataInfo[0] = nsdu_ctrl_ptr->da; /*Issue 462246: RxDa to be source address of the EndOfMsgAck */
            MetaDataInfo[1] = nsdu_ctrl_ptr->sa; /*Issue 462246: RxSa to be destination address of the EndOfMsgAck  */
            MetaDataInfo[2] = pgn;
            MetaDataInfo[3] = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);
        }

        /* get related canid. */
        for(metaDataPositionIdx=3;metaDataPositionIdx>=0;metaDataPositionIdx--)
        {
            metaDataShiftVal= metaDataPositionIdx*8;
            currMetaDataVal=(uint32)MetaDataInfo[metaDataPositionIdx];
            currMetaDataVal <<= metaDataShiftVal;
            metaDataCanId |= (currMetaDataVal);
        }

        if (MetaDataLen != 0U)
        {
            EcuC_Ret=EcuC_SetMetaDataCanId(RxChannelPbcfg->J1939TpTxFcNPduRxConfIdEcuCPbcfg,&PduInfoTemp,metaDataCanId);
        }

        if(EcuC_Ret != E_OK)
        {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
        }

        /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
        /* Reset Tr timer */
        nsdu_ctrl_ptr->StartTrTime = FALSE;
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
        nsdu_ctrl_ptr->TrTimeCounter = 0U;
         /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.Data.Com.Confirm,1 */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_DATA_COMPLETE);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
        nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
        /* Lock Tx CTS PDU until J1939Tp_TxConfirmation is received for this PDU */
        RxChannel->ChannelStatus->J1939TpTxFcNPduAvailable = FALSE;


        /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.EndOfMsgAck,1 */
        /* Send the EndOfMsgAck Frame */
        if(E_OK != CanIf_Transmit(Id, &J1939TpPduInfo))
        {
           J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
           RxChannel->ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;
           /* Call notification function*/
           PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);
           EndOfMsgAckState = J1939TP_FRAME_REJECTED;
        }
        else
        {
           EndOfMsgAckState = J1939TP_FRAME_SENT;
        }

    }
    else
    {
      /* Nothing to do */
    }

    DBG_J1939TP_ENDOFMSGACK_EXIT(loop_idx1, loop_idx2, loop_idx3);

    return EndOfMsgAckState;
}


/* J1939Tp_TxTimerJob*/
static FUNC(void, J1939TP_CODE) J1939Tp_TxTimerJob(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_pointer =(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl;

    DBG_J1939TP_TXTIMERJOB_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* Implementation of J1939Tp_TimerJob*/
    /* For Tbammin timer job */
    if (nsdu_ctrl_pointer->StartTbamminTime == TRUE)
    {
        /* Check If Tbammin is elapsed*/
        if (nsdu_ctrl_pointer->TbamminTimeElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer->TbamminTimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->Tbammin)
            {
                /* Set Tbammin elapsed flag */
                nsdu_ctrl_pointer->TbamminTimeElapsed = TRUE;
                /* Reset the counter */
                nsdu_ctrl_pointer->TbamminTimeCounter = 0U;
                /* Reset the Tbammin flag */
                nsdu_ctrl_pointer->StartTbamminTime = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer->TbamminTimeCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }

    /* For T3 timer job */
    if (nsdu_ctrl_pointer->StartT3Time == TRUE)
    {
        /* Check If StartT3Time is elapsed*/
        if (nsdu_ctrl_pointer->T3TimeElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer->T3TimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->T3)
            {
                /* Set T3TimeElapsed elapsed flag */
                nsdu_ctrl_pointer->T3TimeElapsed = TRUE;
                /* Reset the counter */
                nsdu_ctrl_pointer->T3TimeCounter = 0U;
                /* Reset the StartT3Time flag */
                nsdu_ctrl_pointer->StartT3Time = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer->T3TimeCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }

    /* For T4 timer job */
    if (nsdu_ctrl_pointer->StartT4Time == TRUE)
    {
        /* Check If StartT4Time is elapsed*/
        if (nsdu_ctrl_pointer->T4TimeElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer->T4TimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->T4)
            {
                /* Set T4TimeElapsed elapsed flag */
                nsdu_ctrl_pointer->T4TimeElapsed = TRUE;

                /* Reset the counter */
                nsdu_ctrl_pointer->T4TimeCounter = 0U;

                /* Reset the StartT4Time flag */
                nsdu_ctrl_pointer->StartT4Time = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer->T4TimeCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    J1939Tp_TxConfirmationTimerJob(nsdu_ctrl_pointer);
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    /* For T5 timer job */
    /* Check if counter has reached the max count */
    if ((nsdu_ctrl_pointer->T5TimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->T5) &&
        (nsdu_ctrl_pointer->T5TimeElapsed == FALSE) &&
        (nsdu_ctrl_pointer->StartT5Time == TRUE))
    {
        /* Set T5TimeElapsed elapsed flag */
        nsdu_ctrl_pointer->T5TimeElapsed = TRUE;

        /* Reset the counter */
        nsdu_ctrl_pointer->T5TimeCounter = 0U;

        /* Reset the StartT5Time flag */
        nsdu_ctrl_pointer->StartT5Time = 0U;
    }
    else if ((nsdu_ctrl_pointer->StartT5Time == TRUE) &&
             (nsdu_ctrl_pointer->T5TimeElapsed == FALSE) &&
             (nsdu_ctrl_pointer->T5TimeCounter != J1939Tp_Cfg_Ptr->J1939TpGeneral->T5))
    {
        /* Increment the counter */
        nsdu_ctrl_pointer->T5TimeCounter++;
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (J1939TP_TX_CANFD_SUPPORT == STD_ON) */

    /* For Tr timer */
    if (nsdu_ctrl_pointer->StartTrTime == TRUE)
    {
        /* Check If StartTrTime is elapsed*/
        /* Check if counter has reached the max count */
        if (nsdu_ctrl_pointer->TrTimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->Tr)
        {
            /* Set TrTimeElapsed elapsed flag */
            nsdu_ctrl_pointer->TrTimeElapsed = TRUE;

            /* Reset the counter */
            nsdu_ctrl_pointer->TrTimeCounter = 0U;

            /* Reset the StartTrTime flag */
            nsdu_ctrl_pointer->StartTrTime = 0U;
        }
        else
        {
            /* Increment the counter */
            nsdu_ctrl_pointer->TrTimeCounter++;
        }
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_TXTIMERJOB_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

/* J1939Tp_RxTimerJob*/
static FUNC(void, J1939TP_CODE) J1939Tp_RxTimerJob(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_pointer_rx = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl;

    DBG_J1939TP_RXTIMERJOB_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* For Th timer job */
    if (nsdu_ctrl_pointer_rx->StartThTime == TRUE)
    {
        /* Check If StartThTime is elapsed*/
        if (nsdu_ctrl_pointer_rx->ThTimeElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer_rx->ThTimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->Th)
            {
                /* Set ThTimeElapsed elapsed flag */
                nsdu_ctrl_pointer_rx->ThTimeElapsed = TRUE;
                /* Reset the counter */
                nsdu_ctrl_pointer_rx->ThTimeCounter = 0U;
                /* Reset the StartThTime flag */
                nsdu_ctrl_pointer_rx->StartThTime = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer_rx->ThTimeCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }
    /* For T1 timer job */
    if (nsdu_ctrl_pointer_rx->StartT1Time == TRUE)
    {
        /* Check If StartT1Time is elapsed*/
        if (nsdu_ctrl_pointer_rx->T1TimeElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer_rx->T1TimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->T1)
            {
                /* Set T1TimeElapsed elapsed flag */
                nsdu_ctrl_pointer_rx->T1TimeElapsed = TRUE;

                /* Reset the counter */
                nsdu_ctrl_pointer_rx->T1TimeCounter = 0U;

                /* Reset the StartT1Time flag */
                nsdu_ctrl_pointer_rx->StartT1Time = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer_rx->T1TimeCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }
    /* For T2 timer job */
    if (nsdu_ctrl_pointer_rx->StartT2Time == TRUE)
    {
        /* Check If StartT2Time is elapsed*/
        if (nsdu_ctrl_pointer_rx->T2TimeElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer_rx->T2TimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->T2)
            {
                /* Set T2TimeElapsed elapsed flag */
                nsdu_ctrl_pointer_rx->T2TimeElapsed = TRUE;
                /* Reset the counter */
                nsdu_ctrl_pointer_rx->T2TimeCounter = 0U;
                /* Reset the StartT1Time flag */
                nsdu_ctrl_pointer_rx->StartT2Time = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer_rx->T2TimeCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }

    /* For Tr timer */
    if (nsdu_ctrl_pointer_rx->StartTrTime == TRUE)
    {
        /* Check If StartTrTime is elapsed*/
        /* Check if counter has reached the max count */
        if (nsdu_ctrl_pointer_rx->TrTimeCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->Tr)
        {
            /* Set TrTimeElapsed elapsed flag */
            nsdu_ctrl_pointer_rx->TrTimeElapsed = TRUE;

            /* Reset the counter */
            nsdu_ctrl_pointer_rx->TrTimeCounter = 0U;

            /* Reset the StartTrTime flag */
            nsdu_ctrl_pointer_rx->StartTrTime = 0U;
        }
        else
        {
            /* Increment the counter */
            nsdu_ctrl_pointer_rx->TrTimeCounter++;
        }
    }
    else
    {
        /* Nothing to do */
    }

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    J1939Tp_TxConfirmationTimerJob(nsdu_ctrl_pointer_rx);
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

    DBG_J1939TP_RXTIMERJOB_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmationTimerJob(P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_pointer)
{
    DBG_J1939TP_TXCONFIRMATIONTIMERJOB_ENTRY(nsdu_ctrl_pointer);

    /* For TxConfirmationTimeOut timer job */
    if (nsdu_ctrl_pointer->StartTxConfirmationTimeOut == TRUE)
    {
        /* Check If StartTxConfirmationTimeOut is elapsed*/
        if (nsdu_ctrl_pointer->TxConfirmationTimeOutElapsed == FALSE)
        {
            /* Check if counter has reached the max count */
            if (nsdu_ctrl_pointer->TxConfirmationTimeOutCounter == J1939Tp_Cfg_Ptr->J1939TpGeneral->TxConfirmationTimeOut)
            {
                /* Set TxConfirmationTimeOutElapsed elapsed flag */
                nsdu_ctrl_pointer->TxConfirmationTimeOutElapsed = TRUE;

                /* Reset the counter */
                nsdu_ctrl_pointer->TxConfirmationTimeOutCounter = 0U;

                /* Reset the StartTxConfirmationTimeOut flag */
                nsdu_ctrl_pointer->StartTxConfirmationTimeOut = 0U;
            }
            else
            {
                /* Increment the counter */
                nsdu_ctrl_pointer->TxConfirmationTimeOutCounter++;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939TP_TXCONFIRMATIONTIMERJOB_EXIT(nsdu_ctrl_pointer);
}
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

/* J1939Tp_SendFCWait_CTS*/
static FUNC(void, J1939TP_CODE) J1939Tp_SendFCWait_CTS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    PduInfoType  J1939TpRxPduInfo;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    uint8 frame[12U] = {0U};
#else
    uint8 frame[8U] = {0U};
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */

    uint8 MetaDataInfo[4U]={0x00,0x00,0x00,0x00};
    uint8 FcNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpTxFcNPduMetaDataLen;
    uint8 CmNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCmNPduMetaDataLen;
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2);

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr =
    &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = nsdu_cfg_ptr->J1939TpRxNSduCtrl;

    DBG_J1939TP_SENDFCWAIT_CTS_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    /* If N-PDU is available,  */
    if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable == TRUE)
    {
        /* J1939TpRxSa: address of the Tx node, J1939TpRxDa: address of the Rx node*/
        MetaDataInfo[METADATA_SA_INDEX_0] = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxDaPbcfg;
        MetaDataInfo[METADATA_DA_INDEX_1] = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxSaPbcfg;
        MetaDataInfo[METADATA_PGN_INDEX_2] = J1939TP_UNUSED_BYTE_PADDING;
        MetaDataInfo[METADATA_PRIORITY_INDEX_3] = PrioBit;

        /* Send the CTS0 frame */
        J1939TpRxPduInfo.SduDataPtr = &frame[0U];
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport))
        {
            J1939TpRxPduInfo.SduLength = J1939TP_CANFD_CONTROL_FRAME_LENGTH;
            frame[0U] = (uint8)((nsdu_ctrl_ptr->session_num << 4U) | (J1939TP_CANFD_TPCM_CTS)); /* Session number concatenated to control field */;
            frame[1U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Reserved for assignment by SAE */
            frame[2U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Reserved for assignment by SAE */
            frame[3U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Reserved for assignment by SAE */
            frame[4U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Next segment number to be sent */
            frame[5U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Next segment number to be sent */
            frame[6U] = J1939TP_UNUSED_BYTE_PADDING;                                            /* Next segment number to be sent */
            frame[7U] = 0U;                                                                     /* Number of segments that can be sent */
            frame[8U] = 0U;                                                                     /* Request code */
            frame[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                                            /* LSB of pgn for receive RTS */
            frame[10U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);                                        /* 2nd byte of pgn for receive RTS */
            frame[11U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);                                       /* MSB of pgn for receive RTS */
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            J1939TpRxPduInfo.SduLength = J1939TP_FRAME_LENGTH;
            frame[0U] = J1939TP_TPCM_CTS;
            frame[1U] = 0U;   /*  number of packets */
            frame[2U] = J1939TP_UNUSED_BYTE_PADDING;
            frame[3U] = J1939TP_UNUSED_BYTE_PADDING;
            frame[4U] = J1939TP_UNUSED_BYTE_PADDING;
            frame[5U] = (uint8)(nsdu_ctrl_ptr->pgn);         /* LSB of pgn for receive RTS */
            frame[6U] = (uint8)(nsdu_ctrl_ptr->pgn>>8);      /* 2nd byte of pgn for receive RTS */
            frame[7U] = (uint8)(nsdu_ctrl_ptr->pgn>>16);     /* MSB of pgn for receive RTS */
        }

        nsdu_ctrl_ptr->StartTrTime = FALSE;
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
        nsdu_ctrl_ptr->TrTimeCounter = 0U;

        if (FcNPduMetaData >0U)
        {
            J1939Tp_FCNPduMetaData_Handle(FcNPduMetaData, CmNPduMetaData, nsdu_ctrl_ptr, MetaDataInfo, loop_idx1);
        }
        /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
        /* Lock Tx CTS PDU until J1939Tp_TxConfirmation is received for this PDU */
        (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable = FALSE;

        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CTS0.WaitConfirm,1 */
        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CT0.Sent,1 */
        /* Change the state */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS0);
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.Th,1 */
        /* Start the Th timer */
        nsdu_ctrl_ptr->StartThTime = TRUE;
        nsdu_ctrl_ptr->ThTimeElapsed = FALSE;
        nsdu_ctrl_ptr->ThTimeCounter = 0U;
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
        nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
        nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif

        /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.CM.CTS0,1 */
        /* Send the CTS0 Frame */
        if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpTxCTSCanIf,&J1939TpRxPduInfo))
        {
            /* !LINKSTO J1939Tp.EB.CanIfTransmit.Rx.ENOTOK,1 */
            /* Unlock Tx CTS PDU  */
            (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;
            /* Reinitialization */
            J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
            /* Call notification function*/
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
         }
        else
        {
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.CTS0,1 */
        /* If N-PDU is not available, Enter state J1939TP_CMDT_RX_STATE_CTS0 and Elapse the timer to be able to try to SendFCWait_CTS in the next MainFunction */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_CTS0);
        nsdu_ctrl_ptr->ThTimeElapsed = TRUE;

        if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
        {
            /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif

            /* Reset tr timeElapsed flag */
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;

            /* Call notification function*/
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
            /* Reinitialization ****/
            J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);
        }
        else if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_SENDFCWAIT_CTS_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

static FUNC(boolean, J1939TP_CODE) J1939Tp_CheckAvailableBuffer(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 loop_idx1,PduLengthType tRxbufferSize)
{
    boolean BufferStatus = FALSE;

    /* Number of packets available from PduR */
    uint8 PdurPackets = 0U;

    /* Remaining bytes needed to complete this N-SDU */
    uint32 RemainingBytes = 0U;
    /* Constant number of bytes in each CTS */
    uint16 NrOfRxBytesInCts = 0U;

    DBG_J1939TP_CHECKAVAILABLEBUFFER_ENTRY(nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCanFDSupport)
    {
        /* Number of packets that can be sent. This value shall be no larger than the value in byte 8(Maximum number of packets that can be sent in response to one CTS. */
        PdurPackets = (uint8)(tRxbufferSize / J1939TP_MAX_CANFD_DT_MSGLENGTH);
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        /* Number of packets that can be sent. This value shall be no larger than the value in byte 5(Maximum number of packets that can be sent in response to one CTS. 0xFF indicates that no limit exists for the originator.) of the RTS message. */
        PdurPackets = (uint8)(tRxbufferSize / J1939TP_MAX_DT_MSGLENGTH);
    }

    /* Handle Start of Reception case, after receiving RTS CMDT */
    if (nsdu_ctrl_ptr->RxStartOfReceptionFlag == TRUE)
    {
        if(PdurPackets > 0U)
        {
            J1939Tp_NrOfRxPacketsInCts(nsdu_ctrl_ptr, loop_idx1, tRxbufferSize);
            /* check if the buffer has enough size to recieve the NrOfRxPacketsInCts,
             * or if the buffer has enough size to recieve the whole PDU in case only 1 CTS transmission is needed */
            if((PdurPackets >= nsdu_ctrl_ptr->NrOfRxPacketsInCts) || (tRxbufferSize >= nsdu_ctrl_ptr->msglength))
            {
                nsdu_ctrl_ptr->RxStartOfReceptionFlag = FALSE;
                BufferStatus = TRUE;
            }
            else
            {
                BufferStatus = FALSE;
            }
        }
        else
        {
            BufferStatus = FALSE;
        }
    }
    /* Handle packets transmissions */
    else
    {
        RemainingBytes = (uint32)(nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt);
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCanFDSupport)
        {
            NrOfRxBytesInCts = (uint32)((uint32)nsdu_ctrl_ptr->NrOfRxPacketsInCts * (uint32)60U);
        }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            NrOfRxBytesInCts = (uint32)((uint32)nsdu_ctrl_ptr->NrOfRxPacketsInCts * (uint32)7U);
        }

        /* This is the last CTS, last packet may contain data less than seven bytes */
        if(NrOfRxBytesInCts >= RemainingBytes)
        {
            if (tRxbufferSize >= RemainingBytes)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00226.BuffSize,1 */
                BufferStatus = TRUE;
            }
            else
            {
                BufferStatus = FALSE;
            }
        }
        /* Handle CTS*/
        else
        {
            if(PdurPackets >= nsdu_ctrl_ptr->NrOfRxPacketsInCts)
            {
                BufferStatus = TRUE;
            }
            else
            {
                BufferStatus = FALSE;
            }
        }
    }

    DBG_J1939TP_CHECKAVAILABLEBUFFER_EXIT(BufferStatus,nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);

    return BufferStatus;
}

/* Calculation for number of packets for CTS frame.*/
static FUNC(void, J1939TP_CODE) J1939Tp_NrOfRxPacketsInCts(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 loop_idx1,PduLengthType tRxbufferSize)
{
    uint32 RxNrOfPackets = 0U;

    DBG_J1939TP_NROFRXPACKETSINCTS_ENTRY(nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);

    if(tRxbufferSize >= nsdu_ctrl_ptr->msglength)
    {
        /* Check if the buffer has enough size to recieve the whole number of message in one go. */
        RxNrOfPackets = (uint32)nsdu_ctrl_ptr->RxNoPacketsInRTS;
    }
    else
    {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCanFDSupport)
        {
            /* Number of packets that can be sent. This value shall be no larger than the value in byte 8(Maximum number of packets that can be sent in response to one CTS. */
            RxNrOfPackets = (uint32)(tRxbufferSize / J1939TP_MAX_CANFD_DT_MSGLENGTH);
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            /* Number of packets that can be sent. This value shall be no larger than the value in byte 5(Maximum number of packets that can be sent in response to one CTS. 0xFF indicates that no limit exists for the originator.) of the RTS message. */
            RxNrOfPackets = (uint32)((uint32)tRxbufferSize / J1939TP_MAX_DT_MSGLENGTH);
        }
    }

    if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxDynamicBlockCalculation == TRUE)
    {
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00210,1 */
        if (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPacketsPerBlock) < RxNrOfPackets)
        {
            nsdu_ctrl_ptr->NrOfRxPacketsInCts = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPacketsPerBlock;
        }
        else
        {
            nsdu_ctrl_ptr->NrOfRxPacketsInCts = (uint8)RxNrOfPackets;
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00213,1 */
        nsdu_ctrl_ptr->NrOfRxPacketsInCts = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPacketsPerBlock;
    }

    /* If the NrOfRxPacketsInCts calculated is larger than what's received from the RTS
     * then set it to the the maximum of what's received from the RTS */
    if ((nsdu_ctrl_ptr->u8MAx_Nr_Pkts_Per_CTS) < nsdu_ctrl_ptr->NrOfRxPacketsInCts)
    {
        nsdu_ctrl_ptr->NrOfRxPacketsInCts = (nsdu_ctrl_ptr->u8MAx_Nr_Pkts_Per_CTS);
    }

    /* If the NrOfRxPacketsInCts calculated is larger than what's needed for this transmission
     * then set it to the the maximum of what's needed for this transmission */
    if ((nsdu_ctrl_ptr->RxNoPacketsInRTS) < ((uint32)nsdu_ctrl_ptr->NrOfRxPacketsInCts))
    {
        nsdu_ctrl_ptr->NrOfRxPacketsInCts = ((uint8)nsdu_ctrl_ptr->RxNoPacketsInRTS);
    }

    DBG_J1939TP_NROFRXPACKETSINCTS_EXIT(nsdu_ctrl_ptr,loop_idx1,tRxbufferSize);
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxPgNsduSerialization(uint16 Chan_Idx,uint16 Pg_Idx)
{
    uint16 Nsdu_idx = 0U;
    uint8 NsduState ;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;
    DBG_J1939TP_TX_PG_NSDU_SERAILIZATION_ENTRY(Chan_Idx,Pg_Idx);

    TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]);

    for (Nsdu_idx=0U;Nsdu_idx<(TempPtrTxChannel->J1939TpTxPg[Pg_Idx]).J1939TpNumberOfTxNSdu;Nsdu_idx++)
    {
        NsduState = ((TempPtrTxChannel->J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_idx]).J1939TpTxNSduCtrl->state;
        if((NsduState == J1939TP_BAM_TX_STATE_REQ) || (NsduState == J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT) ||
           (NsduState == J1939TP_BAM_TX_STATE_CONFIRMATION_CM_RECEIVED) || (NsduState == J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED) ||
           (NsduState == J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM) || (NsduState == J1939TP_BAM_TX_STATE_DATA_TRANSMISSION) ||
           (NsduState == J1939TP_BAM_TX_STATE_ABORT) || (NsduState == J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_ABORT)
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
           || (NsduState == J1939TP_BAM_TX_STATE_EOMS_TRANSMISSION) ||
           (NsduState == J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_EOMS) || (NsduState == J1939TP_BAM_TX_STATE_CONFIRMATION_EOMS_RECEIVED)
#endif
           )
        {
            /* Call the BAM Transmit function*/
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00155.BAMTransmission,1 */
            J1939Tp_BAM_Transmit(Chan_Idx,Pg_Idx,Nsdu_idx);

            /* Call the Timer Job */
            J1939Tp_TxTimerJob(Chan_Idx,Pg_Idx,Nsdu_idx);
        }
        else if ((NsduState == J1939TP_CMDT_TX_STATE_RTS_SEND) || (NsduState == J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_RTS) ||
                (NsduState == J1939TP_CMDT_STATE_CTS) || (NsduState == J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION) ||
                (NsduState == J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA) || (NsduState == J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK) ||
                (NsduState == J1939TP_CMDT_TX_STATE_ABORT) || (NsduState == J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT) 
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                || (NsduState == J1939TP_CMDT_TX_STATE_EOMS_TRANSMISSION) || (NsduState == J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_EOMS)
#endif
                )
        {
            /* Call the CMDT Transmit function */
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00155.CMDTTransmission,1 */
            J1939Tp_CMDT_Transmit(Chan_Idx,Pg_Idx,Nsdu_idx);

            /* Call the Timer Job */
            J1939Tp_TxTimerJob(Chan_Idx,Pg_Idx,Nsdu_idx);
        }
        else /*J1939TP_DIRECTPG_TX_STATE_REQ,J1939TP_DIRECTPG_TX_STATE_WAIT_CONFIRMATION*/
        {
             /* Call the DirectPg Transmit function*/
            J1939Tp_DirectPg_Transmit(Chan_Idx,Pg_Idx,Nsdu_idx);
            /* Call the Timer Job */
            J1939Tp_TxTimerJob(Chan_Idx,Pg_Idx,Nsdu_idx);
        }
    }

    DBG_J1939TP_TX_PG_NSDU_SERAILIZATION_EXIT(Chan_Idx,Pg_Idx);
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxChannelPgSerialization(uint16 Chan_Idx)
{
    uint16 Pg_idx = 0;

    P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;

    DBG_J1939TP_TX_CHANNEL_PG_SERAILIZATION_ENTRY(Chan_Idx);

    TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]);

    for (Pg_idx=0U;Pg_idx<TempPtrTxChannel->J1939TpNumberOfTxPg;Pg_idx++)
    {
        /*Handlle each NSDU inside respictive configured PG*/
        J1939Tp_TxPgNsduSerialization(Chan_Idx,Pg_idx);
    }

    DBG_J1939TP_TX_CHANNEL_PG_SERAILIZATION_EXIT(Chan_Idx);
}

static FUNC(void, J1939TP_CODE) J1939Tp_RxPgNsduSerialization(uint16 Chan_Idx,uint16 Pg_Idx)
{
    uint16 Nsdu_idx = 0U;

    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrRxChannel = NULL_PTR;

    DBG_J1939TP_RX_PG_NSDU_SERAILIZATION_ENTRY(Chan_Idx,Pg_Idx);

    TempPtrRxChannel = &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]);

    for(Nsdu_idx=0U;Nsdu_idx<(TempPtrRxChannel->J1939TpRxPg[Pg_Idx]).J1939TpNumberOfRxNSdu;Nsdu_idx++)
    {
        switch(((TempPtrRxChannel->J1939TpRxPg[Pg_Idx]).J1939TpRxNSdu[Nsdu_idx]).J1939TpRxNSduCtrl[0].state)
        {
            case J1939TP_BAM_RX_STATE_NOTIFY_PDUR:
            case J1939TP_BAM_RX_STATE_WAIT_DATA:
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            case J1939TP_RX_STATE_BAM_WAIT_EOMS:
#endif
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00043.BAM,1 */
                /* Call the BAM reception function*/
                J1939Tp_BAM_Reception(Chan_Idx,Pg_Idx,Nsdu_idx);
                /* Call the Timer Job */
                J1939Tp_RxTimerJob(Chan_Idx, Pg_Idx, Nsdu_idx);
                break;
            }
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            case J1939TP_RX_STATE_CMDT_WAIT_EOMS:
            case J1939TP_RX_STATE_CMDT_WAIT_CONFIRMATION_EOMS_RQST:
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
            case J1939TP_CMDT_RX_STATE_RTS_RECEIVED:
            case J1939TP_CMDT_RX_STATE_CTS0:
            case J1939TP_CMDT_RX_STATE_CTS:
            case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS:
            case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS0:
            case J1939TP_CMDT_RX_STATE_WAIT_DATA:
            case J1939TP_CMDT_RX_STATE_DATA_COMPLETE:
            case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_DATA_COMPLETE:
            case J1939TP_CMDT_RX_STATE_ABORT:
            case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT:
            {
                /* Call the CMDT reception function*/
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00043.RTS,1 */
                 J1939Tp_CMDT_Reception(Chan_Idx,Pg_Idx,Nsdu_idx);

                /* Call the Timer Job */
                J1939Tp_RxTimerJob(Chan_Idx, Pg_Idx, Nsdu_idx);
                break;
            }
            default:
            {
                /* Nothing to do */
                break;
            }
        }
    }

    DBG_J1939TP_RX_PG_NSDU_SERAILIZATION_EXIT(Chan_Idx,Pg_Idx);
}

static FUNC(void, J1939TP_CODE) J1939Tp_RxChannelPgSerialization(uint16 Chan_Idx)
{
    uint16 Pg_idx = 0;

    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrRxChannel = NULL_PTR;

    DBG_J1939TP_RX_CHANNEL_PG_SERAILIZATION_ENTRY(Chan_Idx);

    TempPtrRxChannel = &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]);

    for (Pg_idx=0U;Pg_idx<TempPtrRxChannel->J1939TpNumberOfRxPg;Pg_idx++)
    {
        /*Handlle each NSDU inside respictive configured PG*/
        J1939Tp_RxPgNsduSerialization(Chan_Idx,Pg_idx);
    }

    DBG_J1939TP_RX_CHANNEL_PG_SERAILIZATION_EXIT(Chan_Idx);
}
/* !LINKSTO J1939Tp.SWS_J1939Tp_00104,1 */
/* ***************************************************************************
*  Name                 : J1939Tp_MainFunction
*  Description          : Main function of the J1939Tp. Used for scheduling
*                       : purposes and time-out supervision.
*  Parameters           : None
*  Return               : None
*  Critical/explanation : [No]
******************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_MainFunction(void)
{
    /* Local Variables */
    uint16 Ch_idx = 0U;

    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrRxChannel = NULL_PTR;

    DBG_J1939TP_MAINFUNCTION_ENTRY();

    if (J1939Tp_Int_State == J1939TP_ON)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00023.Segmentation,1 */
        /* Tx states handling*/
        for (Ch_idx=0U;Ch_idx<J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels;Ch_idx++)
        {
            J1939Tp_TxChannelPgSerialization(Ch_idx);
        }
         /* !LINKSTO EB_Ref.SWS_J1939Tp_00023.Reassembly,1 */
        /* Rx states handling*/
        for (Ch_idx=0U;Ch_idx<J1939Tp_Cfg_Ptr->J1939TpNumberOfRxChannels;Ch_idx++)
        {
            TempPtrRxChannel = &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[Ch_idx]);

            J1939Tp_RxChannelPgSerialization(Ch_idx);
            /* Handle abort frames on the channel not related to any N-SDU */
            J1939Tp_RxChannelAbortHandler(TempPtrRxChannel);
        }
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00115.E_UNINIT,1 */
        /* !LINKSTO J1939Tp.EB.DET.MAINFUNCTION,1 */
        /* J1939Tp_MainFunction used in state J1939TP_OFF. */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_UNINIT);
        #endif
    }

    DBG_J1939TP_MAINFUNCTION_EXIT();
}

#if (J1939TP_VERSION_INFO_API == STD_ON)
/* ***************************************************************************
*  Name                 : J1939Tp_GetVersionInfo
*  Description          : Returns the version information of J1939Tp.
*  Parameters           : Input: Std_VersionInfoType VersionInfo
*  Return               : None
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00089,1 */
FUNC(void, J1939TP_CODE) J1939Tp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939TP_APPL_DATA) VersionInfo)
{

    DBG_J1939TP_GETVERSIONINFO_ENTRY(VersionInfo);

    if (VersionInfo != NULL_PTR)
    {
        /* Vendor ID of the dedicated implementation of this module according to AUTOSAR Vendor List */
        VersionInfo->vendorID = J1939TP_VENDOR_ID;

        /* Module ID of this module from Module List */
        VersionInfo->moduleID = J1939TP_MODULE_ID;

        /* Major version number of the vendor specific implementation of the module. */
        VersionInfo->sw_major_version = J1939TP_SW_MAJOR_VERSION;

        /* Minor version number of the vendor specific implementation of the module. */
        VersionInfo->sw_minor_version = J1939TP_SW_MINOR_VERSION;

        /* Patch level version number of the vendor specific implementation of the module. */
        VersionInfo->sw_patch_version = J1939TP_SW_PATCH_VERSION;
    }
    else
    {
        /* J1939Tp_GetVersionInfo called with null pointer */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_GETVERSIONINFO_SERVICEID, J1939TP_E_PARAM_POINTER);
        #endif
    }

    DBG_J1939TP_GETVERSIONINFO_EXIT(VersionInfo);
}
#endif /* J1939TP_VERSION_INFO_API == STD_ON */

/* ***************************************************************************
*  Name                 : J1939Tp_Init
*  Description          : This function initializes the J1939Tp module.
*  Parameters           : Input: J1939Tp_ConfigType ConfigPtr
*  Return               : None
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00087,1 */
FUNC(void, J1939TP_CODE) J1939Tp_Init(P2CONST(J1939Tp_ConfigType,AUTOMATIC,J1939TP_APPL_CONST) ConfigPtr)
{
    /* Local Variable */
    uint16 Chan_Idx;
    uint16 Pg_Idx;
    uint16 Nsdu_Idx;
    P2VAR(J1939Tp_ChannelAbortType, AUTOMATIC, J1939TP_APPL_DATA) ChannelAbort;
    P2VAR(J1939Tp_ChannelInfoType, AUTOMATIC, J1939TP_APPL_DATA) ChannelStatus;
    P2CONST(J1939Tp_ConfigType,AUTOMATIC,J1939TP_APPL_DATA) LocalConfigPtr = ConfigPtr;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00024.InitGlobalVar,1 */
    /* Initialize the global static pointer */
    J1939Tp_Cfg_Ptr = &J1939TpConfiguration_0_config;

#if (J1939TP_PBCFGM_SUPPORT_ENABLED == STD_ON)
    /* If the initialization function is called with a null pointer get the configuration from the
     * post build configuration manager */
    /* !LINKSTO J1939Tp.SWS_J1939Tp_00187,1 */
  if (LocalConfigPtr == NULL_PTR)
  {
      PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
      if (E_OK == PbcfgM_GetConfig(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, &ModuleConfig))
      {
          LocalConfigPtr = (P2CONST(J1939Tp_ConfigType, AUTOMATIC, J1939TP_APPL_CONST)) ModuleConfig;
      }
  }
#endif /* J1939TP_PBCFGM_SUPPORT_ENABLED == STD_OFF */

#if (J1939TP_DEV_ERROR_DETECT == STD_ON)

  /* check whether parameter LocalConfigPtr is a NULL_PTR */
  if(LocalConfigPtr == NULL_PTR)
  {
    /* found a NULL_PTR, report to DET */
    (void)Det_ReportError(J1939TP_MODULE_ID,J1939TP_INSTANCE_ID,J1939TP_INIT_SERVICEID,J1939TP_E_PARAM_POINTER);
  }
  /* check that configuration pointer is valid */
  else
      if ( E_OK != J1939Tp_IsValidConfig(LocalConfigPtr))
      {
          (void)Det_ReportError(J1939TP_MODULE_ID,J1939TP_INSTANCE_ID,J1939TP_INIT_SERVICEID,J1939TP_E_INIT_FAILED);
      }
      else
#else /* check that configuration is valid */
      if(J1939Tp_IsValidConfig(LocalConfigPtr) == E_OK)
#endif
    {  /* Configuration is valid use copy config pointer  */
      J1939Tp_PbCfg_Ptr = LocalConfigPtr;
    }

    DBG_J1939TP_INIT_ENTRY(ConfigPtr);

    if (J1939Tp_Int_State != J1939TP_ON)
    {
        if ((J1939Tp_Cfg_Ptr != NULL_PTR) && (LocalConfigPtr != NULL_PTR))
        {
            /* Initialization of TxNSdu control data */
            for ( Chan_Idx = 0U; Chan_Idx < J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels; Chan_Idx++)
            {
                for (Pg_Idx=0U; Pg_Idx < (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpNumberOfTxPg; Pg_Idx++)
                {
                    for (Nsdu_Idx=0U; Nsdu_Idx < ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpNumberOfTxNSdu; Nsdu_Idx++)
                    {
                        /*Reset the TxNSdu control parameters.*/
                        /* Initialize the NSdu */
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00024.Reset.Tx,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.initState,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.initState,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.DirectPg.Tx.initState,1 */
                        J1939Tp_Reinit_Tx(Chan_Idx,Pg_Idx,Nsdu_Idx);
                    }
                    ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxDirectNPduAvailable[Pg_Idx]) = TRUE;
                }

                ChannelStatus = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).ChannelStatus;

                /* Initialize Tx channel PDU's */
                ChannelStatus->J1939TpChannelBusy = FALSE;
                ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
                ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
            }
            /* Initialization of RxNSdu control data */
            for ( Chan_Idx = 0U; Chan_Idx < J1939Tp_Cfg_Ptr->J1939TpNumberOfRxChannels; Chan_Idx++)
            {
                for (Pg_Idx=0U; Pg_Idx < (J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpNumberOfRxPg; Pg_Idx++)
                {
                    for (Nsdu_Idx=0U; Nsdu_Idx < ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[Pg_Idx]).J1939TpNumberOfRxNSdu; Nsdu_Idx++)
                    {
                        /* Reset the RxNSdu control parameters */
                        /* Initialize the RxNSdu */
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00024.Reset.Rx,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.initState,1 */
                        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.InitState,1 */

                        J1939Tp_Reinit_Rx(Chan_Idx,Pg_Idx,Nsdu_Idx);
                    }
                }

                ChannelStatus = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).ChannelStatus;
                ChannelAbort = (J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxChannelAbort;

                /* Initialize Rx channel PDU's */
                ChannelStatus->J1939TpChannelBusy = FALSE;
                ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;

                /* Initialize Rx channel abort parameters */
                ChannelAbort->AbortFlag = FALSE;
                ChannelAbort->AbortReason = 0U;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                ChannelAbort->session_num = J1939TP_INVALID_SESSION_NUMBER;
#endif
                ChannelAbort->pgn = 0U;
                ChannelAbort->sa = 0U;
                ChannelAbort->da = 0U;
                ChannelAbort->txconfirmation = FALSE;
            }
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00022,1 */
            /* J1939Tp Initialization is proper. Hence change the state to "J1939TP_ON" */
            J1939Tp_Int_State = J1939TP_ON;
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00115.E_INIT_FAILED,1 */
            /* J1939Tp_Init was called in state J1939TP_ON. */
            #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_INIT_SERVICEID, J1939TP_E_INIT_FAILED);
            #endif
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00026,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00115.E_REINIT,1 */
        /* J1939Tp_Init was called in state J1939TP_ON. */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_INIT_SERVICEID, J1939TP_E_REINIT);
        #endif
    }
    DBG_J1939TP_INIT_EXIT(ConfigPtr)
}

/* ***************************************************************************
*  Name                 : J1939Tp_Shutdown
*  Description          : This function is used to shutdown the J1939Tp module.
*  Parameters           : None
*  Return               : None
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00093,1 */
FUNC(void, J1939TP_CODE) J1939Tp_Shutdown(void)
{

    DBG_J1939TP_SHUTDOWN_ENTRY();

    if (J1939Tp_Int_State == J1939TP_ON)
    {
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00094,1 */
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00095,1 */
        /* assign the null pointer so TP will not work, when again it will start by init function then correct pointer will assign to it */
        J1939Tp_Cfg_Ptr = NULL_PTR;

        /* Shutdown the J1939Tp so that it does not process any frames. */
        J1939Tp_Int_State = J1939TP_OFF;
    }
    else
    {
        /* J1939Tp_Shutdown used in state J1939TP_OFF */

        /* !LINKSTO J1939Tp.EB.DET.SHUTDOWN,1 */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_SHUTDOWN_SERVICEID, J1939TP_E_UNINIT);
        #endif
    }

    DBG_J1939TP_SHUTDOWN_EXIT();
}

/* ***************************************************************************
*  Name                 : J1939Tp_Transmit
*  Description          : This service function is used to request the
*                       : transmission of a PDU.
*  Parameters           : Input: PduIdType TxPduId
*                       : Input: PduInfoType PduInfoPtr
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00096,1 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Transmit(PduIdType TxPduId, P2CONST(PduInfoType,AUTOMATIC,J1939TP_APPL_CONST) PduInfoPtr)
{
    /* Initialization of local variables*/
    uint16 loop_idx1;
    uint16 loop_idx2;
    uint16 loop_idx3;
    uint8 MetaDataLen;
    uint16 Chan_Idx = 0U;
    uint16 Pg_Idx = 0U;
    uint16 Nsdu_Idx = 0U;
    boolean tTxNSduOk = FALSE;

    uint8 u8SA_val = 0U;
    uint8 u8DA_val = 0U;

    Std_ReturnType status_code = E_NOT_OK;

    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC,  J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = NULL_PTR;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;
    uint8 metaDataInfo[4]={0x00,0x00,0x00,0x00};

    DBG_J1939TP_TRANSMIT_ENTRY(TxPduId,PduInfoPtr);

    /* !LINKSTO J1939Tp.EB.DET.TRANSMIT,1 */
    if (J1939Tp_Int_State == J1939TP_OFF)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_UNINIT);
#endif
    }
    else if (PduInfoPtr == NULL_PTR)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00115.E_PARAM_POINTER,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_PARAM_POINTER);
#endif
    }
    else
    {
        /* We have to checked the null pointer for channel as multiplicity is 0..* otherwise reset may happen for null pointer assignment */
        if (J1939Tp_Cfg_Ptr->J1939TpTxChannel !=NULL_PTR)
        {
            /* Initialization of working pointer to selected NSdu control structure */
            nsdu_ctrl_ptr = J1939Tp_Cfg_Ptr->J1939TpTxChannel->J1939TpTxPg->J1939TpTxNSdu->J1939TpTxNSduCtrl;
            /* Initialization of configuration pointer for selected NSdu structure */
            nsdu_cfg_ptr = J1939Tp_Cfg_Ptr->J1939TpTxChannel->J1939TpTxPg->J1939TpTxNSdu;

            /* Validate the J1939TpTxSduId and set the control structures */
            for (loop_idx1=0U;(loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels)) && (tTxNSduOk != TRUE);loop_idx1++)
            {
                TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]);
                for (loop_idx2=0U;(loop_idx2<(TempPtrTxChannel->J1939TpNumberOfTxPg)) && (tTxNSduOk != TRUE);loop_idx2++)
                {
                    for (loop_idx3=0U;(loop_idx3<(TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpNumberOfTxNSdu) && (tTxNSduOk != TRUE);loop_idx3++)
                    {  /* !LINKSTO EB_Ref.SWS_J1939Tp_00045.NSduId,1 */
                        /*Check whether the SduId transmit is configured for any channel and Pg */
                        if (((TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduId == TxPduId)
                        {
                            /* The channel is found. Breaking the loop */
                            tTxNSduOk = TRUE;

                            Chan_Idx = loop_idx1;
                            Pg_Idx = loop_idx2;
                            Nsdu_Idx = loop_idx3;

                            /* Initialization of working pointer to selected NSdu control structure */
                            nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl);

                            /* Initialization of configuration pointer for selected NSdu structure */
                            nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]);
                        }
                        else
                        {
                            /* Raise the development error if it is supported as TxPduId is not configured-1 */
                        }
                    }
                }
            }
            /* Has a valid NSdu number has been selected ? */
            if (tTxNSduOk == TRUE)
            {
                /* Is no transmission in progress on this NSdu means IDLE state */
                if (nsdu_ctrl_ptr->state == J1939TP_TX_IDLE)
                {
                    MetaDataLen = nsdu_cfg_ptr->txnsdumetadatalength;
                    status_code = J1939Tp_Tx_Store_MetaData(metaDataInfo, Chan_Idx, Pg_Idx, Nsdu_Idx);

                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00045.SduLength,1 */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)
                    {
                        /* set the length of the data to be transmitted */
                        /* The Assurance Data is sent separately during the context of the EOMS */
                        /* !LINKSTO J1939Tp.EB.FD.AssuranceData.SduLength.Tx,1 */
                        nsdu_ctrl_ptr->msglength = (uint32)((uint32)(PduInfoPtr->SduLength) - (uint32)(nsdu_cfg_ptr->AssuranceDataLength));
                    }
                    else
#endif /* (J1939TP_TX_CANFD_SUPPORT == STD_ON) */
                    {
                        /* set the length of the data to be transmitted */
                        nsdu_ctrl_ptr->msglength = (PduLengthType)(PduInfoPtr->SduLength);
                    }
                    /* set the pgn */
                    nsdu_ctrl_ptr->pgn = ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxPgPGN;

                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00039.ConfigSaDa,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00199.MetaData,1 */
                    if(MetaDataLen != 0U)
                    {
                        u8SA_val = metaDataInfo[0U];
                        if (MetaDataLen > 1U)
                        {
                            u8DA_val = metaDataInfo[1U] ;
                        }
                        else
                        {
                            if((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxProtocolType == J1939TP_PROTOCOL_BAM)
                            {
                                u8DA_val = J1939TP_GLOBAL_ADDRESS;
                            }
                            else
                            {
                                u8DA_val = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[Chan_Idx]).J1939TpTxDaPbcfg;
                            }
                        }
                    }
                    else
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00199.NoMetaData,1 */
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00198.NSDU.NoMetaData,1 */
                        /* get the configured SA & DA */
                        u8SA_val = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[Chan_Idx]).J1939TpTxSaPbcfg;
                        if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxProtocolType == J1939TP_PROTOCOL_BAM)
                        {
                            u8DA_val = J1939TP_GLOBAL_ADDRESS;
                        }
                        else
                        {
                            u8DA_val = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[Chan_Idx]).J1939TpTxDaPbcfg;
                        }
                    }

                    /* !LINKSTO J1939Tp.SAE.MaxPDUSize,1 */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                    if((((FALSE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (nsdu_ctrl_ptr->msglength <= J1939TP_MAX_SAE_ALLOWED_MSGLENGTH ))
                     ||  ((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (nsdu_ctrl_ptr->msglength <= J1939TP_MAX_SAE_22_BAM_ALLOWED_MSGLENGTH )&&(u8DA_val == 0xFFU))
                     ||  ((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (nsdu_ctrl_ptr->msglength <= J1939TP_MAX_SAE_22_CMDT_ALLOWED_MSGLENGTH )&&(u8DA_val != 0xFFU)))
                    && (status_code==E_OK))
#else
                    if((nsdu_ctrl_ptr->msglength <= J1939TP_MAX_SAE_ALLOWED_MSGLENGTH) && (status_code==E_OK))
#endif
                    {
                        /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.MaxPDUSize.Tx,1 */
                        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.MaxPDUSize.Tx,1 */
                        status_code = J1939Tp_Transmit_Internal(Chan_Idx, Pg_Idx, Nsdu_Idx, u8SA_val, u8DA_val, MetaDataLen, metaDataInfo);
                    }
                    else
                    {

                        status_code = E_NOT_OK;
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif
                    }
                }
                else
                {
                    /* !LINKSTO J1939Tp.SWS_J1939Tp_00030,1 */
                    /* !LINKSTO J1939Tp.SWS_J1939Tp_00101,1 */
                    /* Message transmission already in progress, reject service call. The status_code is already set with default value. */
                }
            }
            else
            {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif
            }
        }
        else
        {
            /* Nothing to do-1 */
        }
    }

    DBG_J1939TP_TRANSMIT_EXIT(status_code,TxPduId,PduInfoPtr);

    return status_code;
}

#if (J1939TP_CANCELLATION_SUPPORT == STD_ON)

static FUNC(void, J1939TP_CODE) J1939Tp_BAM_CancelationHandle(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx)
{

    P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]);

    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &((TempPtrTxChannel->J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]);
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((TempPtrTxChannel->J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl;
#endif

    DBG_J1939TP_BAM_CANCELATION_HANDLE_ENTRY(Chan_Idx, Pg_Idx, Nsdu_Idx);

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)&&
       ((nsdu_ctrl_ptr->state == J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT)|| (nsdu_ctrl_ptr->state == J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED) ||
        (nsdu_ctrl_ptr->state == J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM)|| (nsdu_ctrl_ptr->state == J1939TP_BAM_TX_STATE_CONFIRMATION_CM_RECEIVED) ||
        (nsdu_ctrl_ptr->state == J1939TP_BAM_TX_STATE_DATA_TRANSMISSION)))
    {
       /* Case of  BAM Transmit*/
       /* It is BAM case */
       /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.EOMS.Confirmation.Abort,1 */
       /* !LINKSTO J1939Tp.EB.Dsn.CANFD.BAM.Tx.Req.Abort,1 */
       J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_ABORT);
       /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
       nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
    }
    else
#endif
    {
       /* Reset the  NSdu control data */
       J1939Tp_Reinit_Tx(Chan_Idx,Pg_Idx, Nsdu_Idx);
       /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CancelTransmit.BAM,1 */
       /* Notify the upper layer */
       PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
    }

    DBG_J1939TP_BAM_CANCELATION_HANDLE_EXIT(Chan_Idx, Pg_Idx, Nsdu_Idx);
}


/* ***************************************************************************
*  Name                 : J1939Tp_CancelTransmit
*  Description          : This service function is used to cancel the ongoing
*                       : transmission of a PDU in a lower layer communication
*                       : module
*  Parameters           : Input: PduIdType TxPduId
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00177,1 */
/* !LINKSTO J1939Tp.SWS_J1939Tp_00214,1 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CancelTransmit(PduIdType TxPduId)
{
    /* Implementation of J1939Tp_CancelTransmit*/
    Std_ReturnType tReturn = E_NOT_OK;
    /* Local Variables*/
    uint16  loop_idx1;
    uint16  loop_idx2;
    uint16  loop_idx3;
    uint16  Chan_Idx = 0U;
    uint16  Pg_idx = 0U;
    uint16  Nsdu_idx = 0U;
    boolean tChFound = FALSE;

    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;

    DBG_J1939TP_CANCELTRANSMIT_ENTRY(TxPduId);

    if (J1939Tp_Int_State == J1939TP_ON)
    {
        /* We have to checked the null pointer for channel as multiplicity is 0..* otherwise reset may happen for null pointer assignment */
        if (J1939Tp_Cfg_Ptr->J1939TpTxChannel != NULL_PTR)
        {
            /* Check whether the Tx SduId is configured */
            /* Validate the J1939TpTxSduId and then set the control structures*/
            for (loop_idx1=0U;((loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels))&& (tChFound != TRUE));loop_idx1++)
            {
                TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]);
                for (loop_idx2=0U;(loop_idx2<(TempPtrTxChannel->J1939TpNumberOfTxPg))&& (tChFound != TRUE);loop_idx2++)
                {
                    for (loop_idx3=0U;(loop_idx3<((TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpNumberOfTxNSdu))&& (tChFound != TRUE);loop_idx3++)
                    {
                        /* Check whether the Tx SduId is configured for any channel and Pg */
                        if (((TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduId == TxPduId)
                        {
                            /* The channel is found. Initialize the channel */
                            tChFound = TRUE;
                            Chan_Idx = loop_idx1;
                            Pg_idx = loop_idx2;
                            Nsdu_idx = loop_idx3;
                        }
                        else
                        {
                            /* TxPduId is not configured. Raise the development error if it is supported */
                        }
                    }
                }
            }
            if(tChFound == TRUE)
            {
                TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]);
                /* Initialization of working pointer to selected NSdu control structure */
                nsdu_ctrl_ptr = ((TempPtrTxChannel->J1939TpTxPg[Pg_idx]).J1939TpTxNSdu[Nsdu_idx]).J1939TpTxNSduCtrl;

                /* Initialization of working pointer to selected NSdu configuration structure */
                if (TempPtrTxChannel->J1939TpTxCancellationSupport)
                {
                    switch (nsdu_ctrl_ptr->state)
                    {
                        case J1939TP_BAM_TX_STATE_REQ:
                        case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT:
                        case J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED:
                        case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM:
                        case J1939TP_BAM_TX_STATE_CONFIRMATION_CM_RECEIVED:
                        case J1939TP_BAM_TX_STATE_DATA_TRANSMISSION:
                        {
                            tReturn = E_OK;
                            /* Case of  BAM Transmit*/
                            J1939Tp_BAM_CancelationHandle(Chan_Idx,Pg_idx,Nsdu_idx);
                            break;
                        }
                        case J1939TP_CMDT_TX_STATE_RTS_SEND:
                        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_RTS:
                        case J1939TP_CMDT_STATE_CTS:
                        case J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION:
                        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA:
                        case J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK:
                        case J1939TP_CMDT_TX_STATE_ABORT:
                        {
                            /* Case of CMDT Transmit */
                            tReturn = E_OK;
                            /* It is CMDT case */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CancelTransmit.CMDT,1 */
                            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
                            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;

                            break;
                        }
                        default:
                        {
                            /* Nothing to do-2 */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00203.TxPduId.NotActive,1 */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00203.Transmitted.DirectPg,1 */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00203.Transmitted.BAM,1 */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00203.Transmitted.CMDT,1 */
                            break;
                        }
                    }
                }
                else
                {
                    /* Cancellation is not supported in the channel level.*/
                }
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00203.TxPduId.invalid,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00188.CancelTransmit,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_CANCELTRANSMIT_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif
            }
        }
        else
        {
            /* Nothing to do-1 */
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.EB.DET.CANCELTRANSMIT,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_CANCELTRANSMIT_SERVICEID, J1939TP_E_UNINIT);
#endif
    }

    DBG_J1939TP_CANCELTRANSMIT_EXIT(tReturn,TxPduId);

    return (tReturn);
}

/* ***************************************************************************
*  Name                 : J1939Tp_CancelReceive
*  Description          : This service function is used to cancel the ongoing
*                       : reception of a PDU in a lower layer transport
*                       : protocol module.
*  Parameters           : Input: PduIdType RxPduId
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00176,1 */
/* !LINKSTO J1939Tp.SWS_J1939Tp_00215,1 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CancelReceive(PduIdType RxPduId)
{
    Std_ReturnType tReturn = E_NOT_OK;
    uint16  loop_idx1;
    uint16  loop_idx2;
    uint16  loop_idx3;
    uint16  Chan_Idx = 0U;
    uint16  Pg_idx = 0U;
    uint16  Nsdu_idx = 0U;
    boolean tChFound = FALSE;

    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = NULL_PTR;
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrRxChannel = NULL_PTR;

    DBG_J1939TP_CANCELRECEIVE_ENTRY(RxPduId);

    if (J1939Tp_Int_State == J1939TP_ON)
    {
        /* We have to checked the null pointer for channel as multiplicity is 0..* otherwise reset may happen for null pointer assignment */
        if (J1939Tp_Cfg_Ptr->J1939TpRxChannel !=NULL_PTR )
        {
            /* check whether the Rx SduId is configured */
            /* Validate the RxPduId and then set the control structures*/
            for (loop_idx1=0U;(loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfRxChannels))&& (tChFound != TRUE);loop_idx1++)
            {
                TempPtrRxChannel = &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]);
                for (loop_idx2=0U;(loop_idx2<(TempPtrRxChannel->J1939TpNumberOfRxPg))&& (tChFound != TRUE);loop_idx2++)
                {
                    for (loop_idx3=0U;(loop_idx3<((TempPtrRxChannel->J1939TpRxPg[loop_idx2]).J1939TpNumberOfRxNSdu))&& (tChFound != TRUE);loop_idx3++)
                    {
                        /* Check whether the Rx SduId is configured for any channel and Pg */
                        if (((TempPtrRxChannel->J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduId == RxPduId)
                        {
                            /* The channel is found. Initialize the channel */
                            tChFound = TRUE;
                            Chan_Idx = loop_idx1;
                            Pg_idx = loop_idx2;
                            Nsdu_idx = loop_idx3;
                        }
                        else
                        {
                            /* nothing to do */
                        }
                    }
                }
            }
            if(tChFound == TRUE)
            {
                TempPtrRxChannel = &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]);
                /* Initialization of working pointer to selected NSdu control structure */
                nsdu_ctrl_ptr = ((TempPtrRxChannel->J1939TpRxPg[Pg_idx]).J1939TpRxNSdu[Nsdu_idx]).J1939TpRxNSduCtrl;

                /* Initialization of working pointer to selected NSdu configuration structure */
                nsdu_cfg_ptr = &((TempPtrRxChannel->J1939TpRxPg[Pg_idx]).J1939TpRxNSdu[Nsdu_idx]);

                if (TempPtrRxChannel->J1939TpRxCancellationSupport == TRUE)
                {
                    if ((nsdu_ctrl_ptr->state != J1939TP_RX_IDLE))
                    {
                        tReturn = E_OK;
                        if (TempPtrRxChannel->J1939TpRxProtocolType == J1939TP_PROTOCOL_BAM)
                        {
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00040.CancelReceive.BAM,1 */
                            /* Reset the  NSdu control data */
                            J1939Tp_Reinit_Rx(Chan_Idx,Pg_idx, Nsdu_idx);

                            /* Notify the upper layer */
                            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduId, E_NOT_OK);
                        }
                        else
                        {
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00040.CancelReceive.CMDT,1 */
                            /* In case of CMDT */
                            /* Reception is abort and Sent the Abort Frame */
                            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                        }
                    }
                    else
                    {
                       /* !LINKSTO EB_Ref.SWS_J1939Tp_00204.RxPduId.NotActive,1 */
                       /* !LINKSTO EB_Ref.SWS_J1939Tp_00204.received.DirectPg,1 */
                       /* !LINKSTO EB_Ref.SWS_J1939Tp_00204.received.BAM,1 */
                       /* !LINKSTO EB_Ref.SWS_J1939Tp_00204.received.CMDT,1 */
                       /* Cannot cancel the request */
                    }
                }
                else
                {
                    /* Cancellation is not supported in the Rx channel level. */
                }
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00188.CancelReceive,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00204.RxPduId.Invalid,1 */
                #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_CANCELRECEIVE_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
                #endif
            }
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.EB.DET.CANCELRECEIVE,1 */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_CANCELRECEIVE_SERVICEID, J1939TP_E_UNINIT);
        #endif
    }

    DBG_J1939TP_CANCELRECEIVE_EXIT(tReturn,RxPduId);

    return (tReturn);
}

#endif /* J1939TP_CANCELLATION_SUPPORT == STD_ON */

/* **************************************************************************
*  Name                 : J1939Tp_ChangeParameter
*  Description          : This service function is used to change a
*                       : specific transport protocol parameter.
*  Parameters           : Input: PduIdType id
*                       : Input: TPParameterType parameter
*                       : Input: uint16 value
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
/* !LINKSTO J1939Tp.SWS_J1939Tp_00180,1 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
    /* Local Variables*/
    uint16 loop_idx1;
    uint16 loop_idx2;
    uint16 loop_idx3;
    uint16 Chan_Idx = 0U;
    boolean tChFound = FALSE;
    Std_ReturnType tReturn = E_NOT_OK;

    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC,  J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;

    DBG_J1939TP_CHANGEPARAMETER_ENTRY(id,parameter,value);

    if (J1939Tp_Int_State == J1939TP_ON)
    {
        /* We have to checked the null pointer for channel as multiplicity is 0..* otherwise reset may happen for null pointer assignment */
        if (J1939Tp_Cfg_Ptr->J1939TpRxChannel !=NULL_PTR)
        {
            /* Initialization of working pointer to selected NSdu control structure */
            nsdu_ctrl_ptr = J1939Tp_Cfg_Ptr->J1939TpRxChannel->J1939TpRxPg->J1939TpRxNSdu->J1939TpRxNSduCtrl;

            /* check whether the Rx SduId is configured */
            /* Validate the Rx SduId and then set the control structures*/
            for (loop_idx1=0U;(loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfRxChannels))&& (tChFound != TRUE);loop_idx1++)
            {
                for (loop_idx2=0U;(loop_idx2<((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpNumberOfRxPg))&& (tChFound != TRUE);loop_idx2++)
                {
                    for (loop_idx3=0U;(loop_idx3<(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpNumberOfRxNSdu))&& (tChFound != TRUE);loop_idx3++)
                    {
                        /* Check whether the Rx SduId is configured for any channel and Pg */
                        if ((((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduId == id)
                        {
                            /* The channel is found. Initialize the channel */
                            tChFound = TRUE;
                            Chan_Idx = loop_idx1;
                            /* Initialization of working pointer to selected NSdu control structure */
                            nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]).J1939TpRxNSduCtrl;
                        }
                        else
                        {
                            /* nothing to do */
                        }
                    }
                }
            }
            if (tChFound)
            {
                if ((nsdu_ctrl_ptr->state == J1939TP_RX_IDLE))
                {
                    if (value <= (uint16)0xFF)
                    {
                        if (parameter == TP_BS )
                        {
                            (J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPacketsPerBlock = (uint8)value;
                            tReturn = E_OK;
                        }
                        else
                        {
                            /* Ignore the other parameter other than BS */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00206.Param.NotTP_BS,1 */
                        }
                    }
                    else
                    {
                        /* Correct value is not passed */
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00206.LargerVal,1 */
                    }
                }
                else
                {
                    /* Not Correct state to change the parameter */
                }
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00188.ChangeParameter,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00206.Invalid.SduId,1 */
                #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_CHANGEPARAMETER_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
                #endif
            }
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {

        /* !LINKSTO J1939Tp.EB.DET.CHANGEPARAMETER,1 */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_CHANGEPARAMETER_SERVICEID, J1939TP_E_UNINIT);
        #endif
    }

    DBG_J1939TP_CHANGEPARAMETER_EXIT(tReturn,id,parameter,value);

    return (tReturn);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_CM_Abort
*  Description          : Handling of TP.CM_ABORT frame.
*                       : Check if the abort reason if correct and if not then report Det error
*                       : and abort the message regardless of the abort reason.
*  Parameters           : Input: loop_idx1, loop_idx2, loop_idx3, SduDataPtr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_Abort(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3, P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr)
{
    /* Local Variables */
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxNSdu[loop_idx3]);

#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
    boolean ValidAbortReason = TRUE;
#else
    TS_PARAM_UNUSED(SduDataPtr);
#endif

    DBG_J1939TP_RXINDICATION_CM_ABORT_ENTRY(loop_idx1, loop_idx2, loop_idx3, SduDataPtr);

#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1].J1939TpRxCanFDSupport)
    {
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.ApplicationLayerReasons,1 */
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.UnexpectedDatasegmentReceived,1 */
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.DuplicateSequenceNumberReceived,1 */
        ValidAbortReason = (((SduDataPtr[8U] < 12U) && (SduDataPtr[8U] > 0U)) || (SduDataPtr[8U] > 249U));
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        ValidAbortReason = (((SduDataPtr[1U] < 10U) && (SduDataPtr[1U] > 0U)) || (SduDataPtr[1U] > 249U));
    }
    /* Check if Abort reason is invalid */
    if(TRUE != ValidAbortReason)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_CAR,1 */
        /* If Abort reason is invalid then raise DET error with error Id J1939TP_E_INVALID_CAR */
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
        J1939TP_E_INVALID_CAR);
    }
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */

    /* !LINKSTO J1939Tp.SWS_J1939Tp_00098,1 */
    /* !LINKSTO J1939Tp.SWS_J1939Tp_00163,1 */
    /* Indicate the upper layer */
    PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);
    J1939Tp_Reinit_Rx(loop_idx1, loop_idx2, loop_idx3);

    DBG_J1939TP_RXINDICATION_CM_ABORT_EXIT(loop_idx1, loop_idx2, loop_idx3, SduDataPtr);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_CM_BAM_IDLE
*  Description          : Handling of TP.CM_BAM frame if nsdu in IDLE state.
*                       : Check if the Same SA ongoing with different PGN on same Rx BAM-Channel and discard it if
*                       : found by new message by sending Abort message.
*  Parameters           : Input: SduInfo
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_BAM_IDLE(
P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannelPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]);
    boolean SduFound = FALSE;
    uint16 i, j;

    DBG_J1939Tp_RxIndication_CM_BAM_IDLE_ENTRY(SduInfo);

    for (i = 0U; (i < RxChannelPtr->J1939TpNumberOfRxPg) && (SduFound == FALSE); i++)
    {
        for (j = 0U; (j < (RxChannelPtr->J1939TpRxPg[i]).J1939TpNumberOfRxNSdu) && (SduFound == FALSE); j++)
        {
            /* check if there another Reception with same SA and session_num on-going for this SDU */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if((((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->state != J1939TP_RX_IDLE)
             && ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->sa ==  SduInfo->sa))
             && ((FALSE == RxChannelPtr->J1939TpRxCanFDSupport)
             || ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->session_num ==  SduInfo->session_num)))
#else
            if((((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->state != J1939TP_RX_IDLE)
             && ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->sa ==  SduInfo->sa)))
#endif
            {
                /* break the loop */
                SduFound = TRUE;

                /* safe error mechanism */
                /* same SA Reception with different PGN on Going on other SDU  */
                /* discard the old Connection and start new connection*/
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00233,1 */
                /* !LINKSTO EB_Ref.SAE.FD.UniqueSession.Rx,1 */
                /* Call error indication function for old connection */
                PduR_J1939TpRxIndication(((RxChannelPtr->J1939TpRxPg[i]).J1939TpRxNSdu[j]).J1939TpRxNSduIdPduR,
                E_NOT_OK);
                J1939Tp_Reinit_Rx(SduInfo->ch_idx, i, j);
            }
            else
            {
                /* nothing , continue the loop to check other SDUs */
            }
        }
    }

    DBG_J1939Tp_RxIndication_CM_BAM_IDLE_EXIT(SduInfo);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_CM_BAM
*  Description          : Handling of TP.CM_BAM frame
*  Parameters           : Input: SduInfo PduInfoPtr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_BAM(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
    boolean AcceptBam = FALSE;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    boolean AcceptAssurnaceData = FALSE;
    uint16 i = 0U;
    uint16 j = 0U;
    P2CONST(J1939Tp_RxPgType,AUTOMATIC,J1939TP_APPL_CONST) RxPgPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxPg[SduInfo->pg_idx]);
#endif
    P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr = PduInfoPtr->SduDataPtr;
    /* Initialization of pointer to selected Rx NSdu configuration structure */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr =
    &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxPg[SduInfo->pg_idx]).J1939TpRxNSdu[SduInfo->nsdu_idx]);
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = nsdu_cfg_ptr->J1939TpRxNSduCtrl;

    DBG_J1939Tp_RxIndication_CM_BAM_ENTRY(SduInfo,PduInfoPtr);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxCanFDSupport)
    {
        AcceptBam = (boolean)(SduDataPtr[7U] == 0xFFU);
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        AcceptBam = (boolean)(SduDataPtr[4U] == 0xFFU);
    }

    /* Abort the connection if J1939TP_PROTOCOL_CMDT is configured, otherwise its J1939TP_PROTOCOL_BAM or J1939TP_PROTOCOL_ACCEPT_ANY*/
    if (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxProtocolType == J1939TP_PROTOCOL_CMDT))
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00173.TransProtocol.BAM,1 */
        /* Silently Abort the connection as  the Rx channel not configured as BAM protocol */

        /* discard current message and change the state to IDLE */
        J1939Tp_Reinit_Rx(SduInfo->ch_idx, SduInfo->pg_idx, SduInfo->nsdu_idx);
    }
    /* Correct BAM frame */
    else if (TRUE == AcceptBam)
    {
        if (nsdu_ctrl_ptr->state == J1939TP_RX_IDLE)
        {
            /*The state of this NSDu is  J1939TP_RX_IDLE */
            /* Check if the Same SA ongoing with different PGN on same Rx BAM-Channel and discard it if found */
            /* In case of CanFD channel, check the session number as well as checking the SA, discard if both found*/
            J1939Tp_RxIndication_CM_BAM_IDLE(SduInfo);
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            AcceptAssurnaceData = TRUE;
#endif
        }
        /* For not IDLE SDU, discard current message */
        else
        {
            /* Call error indication function if configured */
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);

            /* Multiple frame BAM reception is currently ongoing, with same SA & DA */
            /* abort MF reception and proceed with new BAM reception */
            /* discard current message and change the state to IDLE */
            /* silent abort for 1st connection and reinitialize the N-SDU BAM case*/
            J1939Tp_Reinit_Rx(SduInfo->ch_idx, SduInfo->pg_idx, SduInfo->nsdu_idx);
            /* Make sure the current NSDU is compatible with the assurance data of the BAM */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if(FALSE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxCanFDSupport)
            {
                /* No assurance data check is needed, the channel doesn't support Can reception */
                AcceptAssurnaceData = TRUE;
            }
            else
            {
                if(nsdu_cfg_ptr->AssuranceDataType == SduInfo->AssuranceDataType)
                {
                    /* The assurance data type is similar to the already chosen N-SDU */
                    AcceptAssurnaceData = TRUE;
                }
                else
                {
                    /* search for a new N-SDU with compatible assurance data type to receive the data */
                    for (i = 0U; (i < RxPgPtr->J1939TpNumberOfRxNSdu) && (AcceptAssurnaceData == FALSE); i++)
                    {
                        if((RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->state == J1939TP_RX_IDLE)
                        && (SduInfo->AssuranceDataType == RxPgPtr->J1939TpRxNSdu[i].AssuranceDataType))
                        {
                            /* Break the loop */
                            AcceptAssurnaceData = TRUE;
                            /* Re assign the meta data info for before to the new N-SDU */
                            for(j = 0U; j < SduInfo->MetaDataLen; j++)
                            {
                                RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->J1939TpMetaDataInfo[j] = nsdu_ctrl_ptr->J1939TpMetaDataInfo[j];
                            }
                            /* Assign the new N-SDU to be used for the reception */
                            nsdu_ctrl_ptr = RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl;
                        }
                    }
                }
            }
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        }

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(FALSE == AcceptAssurnaceData)
        {
            /* The assurance data type is incompatible with any N-SDU of this PGN */
            /* Discard the communication */
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            /* Start connection with changing the state */
            /* Store SA, DA, msglength, RxNoPacketsInRTS, SduLength and Session_num variables for the current SDU */
            nsdu_ctrl_ptr->sa = SduInfo->sa;
            nsdu_ctrl_ptr->da = SduInfo->da;
            nsdu_ctrl_ptr->SduLength = SduInfo->ReceivedLength;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxCanFDSupport)
            {
                nsdu_ctrl_ptr->session_num = SduInfo->session_num;
                nsdu_ctrl_ptr->msglength = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U])<< 8U) + (uint32)((uint32)(SduDataPtr[3U])<< 16U));
                nsdu_ctrl_ptr->RxNoPacketsInRTS = (((uint32)(SduDataPtr[4U])) + (uint32)((uint32)(SduDataPtr[5U])<< 8U) + (uint32)((uint32)(SduDataPtr[6U])<< 16U));
            }
            else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
            {
                nsdu_ctrl_ptr->msglength = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U]) << 8U));
                nsdu_ctrl_ptr->RxNoPacketsInRTS = (uint32)(SduDataPtr[3U]);
            }
            /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.CM_BAM,1 */
            /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.Initiation.Rx,1 */
            /* change state */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_RX_STATE_NOTIFY_PDUR);
        }
    }
    else
    {
        /* Nothing to do */
    }

    DBG_J1939Tp_RxIndication_CM_BAM_EXIT(SduInfo,PduInfoPtr);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_CM_RTS_IDLE
*  Description          : Handling of TP.CM_BAM frame if nsdu in IDLE state.
*                       : Check if the Same SA ongoing with different PGN on same Rx CMDT-Channel,
*                       : and check the session Id for CanFD channels. If found, discard
*                       : new message by sending Abort message.
*  Parameters           : Input: SduInfo
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_RTS_IDLE( P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannelPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]);
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    boolean SduFound = FALSE;
    uint16 i, j;

    DBG_J1939TP_RXINDICATION_CM_RTS_IDLE_ENTRY(SduInfo);

    for (i=0U; (i<(RxChannelPtr->J1939TpNumberOfRxPg)) && (SduFound == FALSE); i++)
    {
        for (j=0U; (j<(RxChannelPtr->J1939TpRxPg[i]).J1939TpNumberOfRxNSdu) && (SduFound == FALSE); j++)
        {
            /* check if there another Reception for same SA & Da session_num on-going for this SDU */

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if (((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->state != J1939TP_RX_IDLE)
             && ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->sa ==  SduInfo->sa)
             && ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->da ==  SduInfo->da)
             && ((FALSE == RxChannelPtr->J1939TpRxCanFDSupport)
             || ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->session_num ==  SduInfo->session_num)))
#else
            if (((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->state != J1939TP_RX_IDLE)
             && ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->sa ==  SduInfo->sa)
             && ((RxChannelPtr->J1939TpRxPg[i].J1939TpRxNSdu[j].J1939TpRxNSduCtrl)->da ==  SduInfo->da))
#endif
            {
                /* break the loop */
                SduFound = TRUE ;
                nsdu_ctrl_ptr = ((RxChannelPtr->J1939TpRxPg[i]).J1939TpRxNSdu[j]).J1939TpRxNSduCtrl;
                /* !LINKSTO EB_Ref.SAE.FD.UniqueSession.Rx,1 */
                /* same SA & DA Reception with different PGN on Going on other SDU  */
                /* Send abort Connection for old CMDT connection with the Same SA/DA/SN and keep the new connection*/
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.CanNotSupportAnotherSession,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_CONNECTION;
            }
            else
            {
                /* nothing , continue the loop to check other SDUs*/
            }
        }
    }

    DBG_J1939TP_RXINDICATION_CM_RTS_IDLE_EXIT(SduInfo);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_CM_RTS
*  Description          : Handling of TP.CM_BAM frame
*  Parameters           : Input: SduInfo PduInfoPtr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_RTS(
P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo,
P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
    boolean AcceptRts = FALSE;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    uint16 i = 0U;
    uint16 j = 0U;
    P2CONST(J1939Tp_RxPgType,AUTOMATIC,J1939TP_APPL_CONST) RxPgPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxPg[SduInfo->pg_idx]);
#endif
    P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr = PduInfoPtr->SduDataPtr;
    /* Initialization of pointer to selected Rx NSdu configuration structure */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr =
    &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxPg[SduInfo->pg_idx]).J1939TpRxNSdu[SduInfo->nsdu_idx]);
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC,  J1939TP_APPL_DATA) nsdu_ctrl_ptr = nsdu_cfg_ptr->J1939TpRxNSduCtrl;
    DBG_J1939TP_RXINDICATION_CM_RTS_ENTRY(SduInfo,PduInfoPtr);

    /* Abort the connection if J1939TP_PROTOCOL_BAM is configured, otherwise its J1939TP_PROTOCOL_CMDT or J1939TP_PROTOCOL_ACCEPT_ANY*/
    if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxProtocolType == J1939TP_PROTOCOL_BAM)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00173.TransProtocol.CMDT,2 */
        /* Abort the connection as the Rx channel not configured as CMDT protocol */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
        nsdu_ctrl_ptr->pgn = SduInfo->pgn;
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.CanNotSupportAnotherSession,1 */
        nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_CONNECTION;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        nsdu_ctrl_ptr->session_num = SduInfo->session_num;
#endif
    }
    /* Max No of packets that can be sent in response to one CTS should not be 0 */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    else if(((SduDataPtr[4U] == 0U) && (FALSE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxCanFDSupport))
          || ((SduDataPtr[7U] == 0U) && (TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxCanFDSupport)))
#else
    else if(SduDataPtr[4U] == 0U)
#endif
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_MNOP,1 */
        /* As 5th byte in RTS frame is 0 this is an invalid RTS. So report to DET if DET is enabled */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
        J1939TP_E_INVALID_MNOP);
#endif
    }
    /* NSDU is in IDLE state */
    else if (nsdu_ctrl_ptr->state == J1939TP_RX_IDLE)
    {
        /* The state of this NSDu is J1939TP_RX_IDLE*/
        /* Check if the Same SA/DA Rx ongoing in different PGN on same Rx Channel*/
        J1939Tp_RxIndication_CM_RTS_IDLE(SduInfo);
        AcceptRts = TRUE;
    }
    /* SDU in not in IDLE state */
    else
    {
        /* same SA & DA Reception on Going */
        /* Make sure the current NSDU is compatible with the assurance data of the RTS */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(FALSE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxCanFDSupport)
        {
            /* No assurance data check is needed, the channel doesn't support Can reception */
            AcceptRts = TRUE;
        }
        else
        {
            if(nsdu_cfg_ptr->AssuranceDataType == SduInfo->AssuranceDataType)
            {
                /* The assurance data type is similar to the already chosen N-SDU */
                AcceptRts = TRUE;
            }
            else
            {
                /* search for a new N-SDU with compatible assurance data type to receive the data */
                for(i = 0U; (i < RxPgPtr->J1939TpNumberOfRxNSdu) && (AcceptRts == FALSE); i++)
                {
                    if((RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->state == J1939TP_RX_IDLE)
                    && (SduInfo->AssuranceDataType == RxPgPtr->J1939TpRxNSdu[i].AssuranceDataType))
                    {
                        /* Break the loop */
                        AcceptRts = TRUE;
                        /* Re assign the meta data info for before to the new N-SDU */
                        for(j = 0U; j < SduInfo->MetaDataLen; j++)
                        {
                            RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->J1939TpMetaDataInfo[j] = nsdu_ctrl_ptr->J1939TpMetaDataInfo[j];
                        }
                        /* Assign the new N-SDU to be used for the reception */
                        nsdu_ctrl_ptr = RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl;
                    }
                }
            }
        }

        if(FALSE == AcceptRts)
        {
            /* No N-SDU is compatible to handle the current CMDT request */
            /* Send abort Connection for new RTS */
            /* After the connection PduR_J1939TpRxIndication will be called with E_NOT_OK indicating the transfer end */
            /* Abort reason will be J1939TP_TPCM_ABORT_REASON_CONNECTION due to incompatible (assurance data type)/resourses */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_ABORT);
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.CanNotSupportAnotherSession,1 */
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_CONNECTION;
        }
        else
        {
            /* As per SAE J1939-22 document, if multiple RTSs are received from the same source address for the same
             * PGN with the same session number, then the most recent RTS shall be acted on and the previous RTS will be abandoned.
             * No abort message shall be sent for the abandoned RTS in this specific case */
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);

            /* silent abort for the old connection and reinitialize the N-SDU */
            J1939Tp_Reinit_Rx(SduInfo->ch_idx, SduInfo->pg_idx, SduInfo->nsdu_idx);
        }
#else
        AcceptRts = TRUE;
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00225,1 */
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00233,1 */
        /* As per SAE J1939-21 document, if multiple RTSs are received from the same source address for the same
         * PGN, then the most recent RTS shall be acted on and the previous RTS will be abandoned. No abort message
         * shall be sent for the abandoned RTS in this specific case */
        PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, E_NOT_OK);

        /* silent abort for the old connection and reinitialize the N-SDU */
        J1939Tp_Reinit_Rx(SduInfo->ch_idx, SduInfo->pg_idx, SduInfo->nsdu_idx);
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    }

    /* Accept the new RTS */
    if(AcceptRts == TRUE)
    {
        /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.RTS,1 */
        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Initiation.Rx,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Rts,1 */
        /* Start new connection with changing the state */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_RX_STATE_RTS_RECEIVED);

        /* store the pgn in the ram structure which will be used in CMDT reception function */
        nsdu_ctrl_ptr->pgn = SduInfo->pgn;
        /* Store SA, DA, msglength, RxNoPacketsInRTS, SduLength variables for the current SDU */
        nsdu_ctrl_ptr->sa = SduInfo->sa;
        nsdu_ctrl_ptr->da = SduInfo->da;
        nsdu_ctrl_ptr->SduLength = SduInfo->ReceivedLength;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxCanFDSupport)
        {
            nsdu_ctrl_ptr->session_num = SduInfo->session_num;
            nsdu_ctrl_ptr->msglength = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U])<< 8U) + (uint32)((uint32)(SduDataPtr[3U])<< 16U));
            nsdu_ctrl_ptr->RxNoPacketsInRTS = (((uint32)(SduDataPtr[4U])) + (uint32)((uint32)(SduDataPtr[5U])<< 8U) + (uint32)((uint32)(SduDataPtr[6U])<< 16U));
            nsdu_ctrl_ptr->u8MAx_Nr_Pkts_Per_CTS =  (uint8)(SduDataPtr[7U]);
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            nsdu_ctrl_ptr->msglength = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U]) << 8U));
            nsdu_ctrl_ptr->RxNoPacketsInRTS = (uint32)(SduDataPtr[3U]);
            nsdu_ctrl_ptr->u8MAx_Nr_Pkts_Per_CTS =  (uint8)(SduDataPtr[4U]);
        }
    }

    DBG_J1939TP_RXINDICATION_CM_RTS_EXIT(SduInfo,PduInfoPtr);
}

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM_DT(PduIdType RxPduId,uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
    sint8 metaDataPositionIdx;
    uint8 metaDataInfo[4]={0x00,0x00,0x00,0x00};
    Std_ReturnType EcuC_Ret = E_OK;
    uint16 EcuC_Pdu_ID;
    uint8 MetaDataLen = 0U;
    uint32 metaDataCanId=0x00000000;
    uint8 u8SA_val = 0U;
    uint8 u8DA_val = 0U;
    uint8    metaDataShiftVal = (uint8)0;
    uint32    currMetaDataVal = (uint32)0;

    DBG_J1939TP_RXINDICATION_CM_DT_ENTRY(RxPduId,Chan_Idx,PduInfoPtr);

    if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxCmNPduId == RxPduId)
    {
        MetaDataLen = J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxCmNPduMetaDataLen;
        EcuC_Pdu_ID=J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[Chan_Idx].J1939TpRxCmNPduRxConfIdEcuCPbcfg;
    }
    else
    {
        MetaDataLen = J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxDtNPduMetaDataLen;
        EcuC_Pdu_ID=J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[Chan_Idx].J1939TpRxDtNPduRxConfIdEcuCPbcfg;
    }

    if(MetaDataLen>0U)
    {
        EcuC_Ret=EcuC_GetMetaDataCanId(EcuC_Pdu_ID,NULL_PTR,&metaDataCanId);
    }

    if(EcuC_Ret != E_OK)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
    }

    /* unpack received metadata info */
    for(metaDataPositionIdx=0;metaDataPositionIdx<4;metaDataPositionIdx++)
    {
        metaDataShiftVal=metaDataPositionIdx*8;
        currMetaDataVal=metaDataCanId>>metaDataShiftVal;
        metaDataInfo[metaDataPositionIdx] =(uint8)(currMetaDataVal);
    }

    /* get SA  and DA for current SDU */
    if(MetaDataLen >(uint8)0)
    {
        u8SA_val = metaDataInfo[(PduLengthType)METADATA_SA_INDEX_0];
    }
    else
    {
        /* get the configured SA & DA */
        u8SA_val  = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[Chan_Idx]).J1939TpRxSaPbcfg;
    }
    if(MetaDataLen >(uint8)1)
    {
        u8DA_val = metaDataInfo[(PduLengthType)METADATA_DA_INDEX_1];
    }
    else
    {
        /* get the configured DA */
        if((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxProtocolType == J1939TP_PROTOCOL_BAM)
        {
            u8DA_val = J1939TP_GLOBAL_ADDRESS;
        }
        else
        {
            /* get the configured DA */
            u8DA_val = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[Chan_Idx]).J1939TpRxDaPbcfg ;
        }
    }

    /* Handling of TP.CM frame*/
    /* Handling of BAM or RTS frame or Conn_Abort or EndOfMsgAck or Data frame */
    if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxCmNPduId == RxPduId)
    {
        J1939Tp_RxIndication_CM(Chan_Idx, PduInfoPtr);
    }
    else
    {
        /* Handling of DT frame*/
        J1939Tp_RxIndication_DT(Chan_Idx, PduInfoPtr,u8SA_val,u8DA_val);
    }

    DBG_J1939TP_RXINDICATION_CM_DT_EXIT(RxPduId,Chan_Idx,PduInfoPtr);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxGet_nsdu_id
*  Description          : Get nsdu ID that equals SA in SduInfo or an idle nsdu.
*  Parameters           : Input: SduInfo
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_RxGet_nsdu_id(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    Std_ReturnType status = E_NOT_OK;
    P2CONST(J1939Tp_RxPgType,AUTOMATIC,J1939TP_APPL_CONST) RxPgPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxPg[SduInfo->pg_idx]);
    uint16 idle_Nsdu_Idx = 0U;
    uint16 i = 0U;
    boolean idle_nsdu_found = FALSE;

    DBG_J1939TP_RXGET_NSDU_ID_ENTRY(SduInfo);

    for (i = 0U; (i < RxPgPtr->J1939TpNumberOfRxNSdu) && (status != E_OK); i++)
    {
        /* check if there is an ongoing connection with the same SA and DA */
        /* check the Session number besides the SA and DA in case of CanFD channel */
#if(J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(((RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->state != J1939TP_RX_IDLE)
         && (RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->sa == SduInfo->sa)
         && (RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->da == SduInfo->da))
         && ((FALSE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxCanFDSupport)
          || (RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->session_num == SduInfo->session_num)))
#else
        if(((RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->state != J1939TP_RX_IDLE)
         && (RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->sa == SduInfo->sa)
         && (RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->da == SduInfo->da)))
#endif
        {
            /* Found NSDU with same SA, DA and (session_num with compatible assurance data type) on-going for this SDU as the message */
            status = E_OK;
            SduInfo->nsdu_idx = i;
        }
        /* Get first idle SDU */
#if(J1939TP_RX_CANFD_SUPPORT == STD_ON)
        else if ((RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->state == J1939TP_RX_IDLE)
              && (idle_nsdu_found == FALSE)
              && ((FALSE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx].J1939TpRxCanFDSupport)
               || ((J1939TP_TPCM_ABORT == SduInfo->MessageType)
                || (SduInfo->AssuranceDataType == RxPgPtr->J1939TpRxNSdu[i].AssuranceDataType))))
#else
        else if ((RxPgPtr->J1939TpRxNSdu[i].J1939TpRxNSduCtrl->state == J1939TP_RX_IDLE)
              && (idle_nsdu_found == FALSE))
#endif
        {
            /* This nsdu is idle and has compatible assurance data type if needed, save it for later */
            idle_Nsdu_Idx = i;
            idle_nsdu_found = TRUE;
        }
        else
        {
            /* Nothing to do */
        }
    }

    /* If there is no ongoing nsdu with same SA, check any ideal nsdu on the channel */
    if ((status == E_NOT_OK) && (idle_nsdu_found == TRUE))
    {
        status = E_OK;
        SduInfo->nsdu_idx = idle_Nsdu_Idx;
    }
    else
    {
        /* Couldn't find any SDU. All of SDU's are busy */
    }

    DBG_J1939TP_RXGET_NSDU_ID_EXIT(status,SduInfo);

    return status;
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxGet_pg_id
*  Description          : Get pg ID that equals to pgn in SduInfo
*  Parameters           : Input: SduInfo
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_RxGet_pg_id(P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    Std_ReturnType status = E_NOT_OK;
    uint16 i;

    DBG_J1939TP_RXGET_PG_ID_ENTRY(SduInfo);

    for (i=0u; (i<((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpNumberOfRxPg)) &&
    (status != E_OK); i++)
    {
        if (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxPg[i]).J1939TpRxPgPGN == SduInfo->pgn)
        {
            status = E_OK;
            SduInfo->pg_idx = i;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_RXGET_PG_ID_EXIT(status,SduInfo);
    return status;
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxGet_MetaDataInfo
*  Description          : Get SA and DA from metadata or from channel constant values based on confiuration
*  Parameters           : Input: SduInfo PduInfoPtr
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxGet_MetaDataInfo (
P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo,
P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,uint16 J1939TpEcucId)
{
    uint32 metaDataCanId=0x00000000;
    uint8 sa;
    uint32 da;
    Std_ReturnType EcuC_Ret = E_OK;
    /* suppress compiler warning */
    TS_PARAM_UNUSED(PduInfoPtr);

    DBG_J1939TP_RXGET_METADATAINFO_ENTRY(SduInfo,PduInfoPtr,J1939TpEcucId);

    if(SduInfo->MetaDataLen >(uint8)0)
    {
        EcuC_Ret = EcuC_GetMetaDataCanId(J1939TpEcucId,NULL_PTR,&metaDataCanId);
    }
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00057.SaDa,1 */
    if(EcuC_Ret == E_OK)
    {
        /* get SA and DA for current SDU */
        if(SduInfo->MetaDataLen >(uint8)0)
        {
            sa= (uint8)(metaDataCanId&((uint8)0xff ));
            SduInfo->sa = (uint8)(sa);
        }
        else
        {
            /* get the configured SA & DA */
            SduInfo->sa  = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[SduInfo->ch_idx]).J1939TpRxSaPbcfg;
        }

        if(SduInfo->MetaDataLen >(uint8)1)
        {
            da =(metaDataCanId>>8);
            da &= ((uint8)0xff );
            SduInfo->da = (uint8)(da);
        }
        else
        {
            /* get the configured DA */
            if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo->ch_idx]).J1939TpRxProtocolType == J1939TP_PROTOCOL_BAM)
            {
                SduInfo->da  =(uint8) 255;
            }
            else
            {
                /* get the configured DA */
                SduInfo->da = (J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[SduInfo->ch_idx]).J1939TpRxDaPbcfg;
            }
        }
    }
    else
    {
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)

        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);

        #endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
    }

    DBG_J1939TP_RXGET_METADATAINFO_EXIT(SduInfo,PduInfoPtr,J1939TpEcucId);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_CM
*  Description          : Handling of Rx TP.CM frame
*                       : Handling of RTS (BAM/CMDT) frame or Conn_Abort frame
*  Parameters           : Input: Chan_Idx PduInfoPtr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_CM(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
    uint8 i;
    J1939Tp_SduInfoType SduInfo;
    P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) SduDataPtr = PduInfoPtr->SduDataPtr;
    PduLengthType SduLength = PduInfoPtr->SduLength;
    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannelPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]);
    /* Initialization of pointer to selected Rx NSdu configuration structure */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = NULL_PTR;
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC,  J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    uint32 RtsMsgLen;       /*  length of the message */
    uint32 RtsNoOfPackets;   /* No of packets in the RTS frame */
    uint32 VerfiyNrPackets;

    uint32 metaDataCanId=0x00000000U;
    uint8 metaDataVal;
    uint8 metaDataShiftVal = (uint8)0U;
    Std_ReturnType EcuC_Ret = E_OK;
    SduInfo.ch_idx = Chan_Idx;
    SduInfo.MetaDataLen = J1939Tp_Cfg_Ptr->J1939TpRxChannel[SduInfo.ch_idx].J1939TpRxCmNPduMetaDataLen;
    SduInfo.ReceivedLength =(uint8)SduLength;

    DBG_J1939TP_RXINDICATION_CM_ENTRY(Chan_Idx, PduInfoPtr);

    if (TRUE == J1939Tp_CM_Validation(Chan_Idx, PduInfoPtr, &SduInfo))
    {
        nsdu_cfg_ptr = &((RxChannelPtr->J1939TpRxPg[SduInfo.pg_idx]).J1939TpRxNSdu[SduInfo.nsdu_idx]);
        nsdu_ctrl_ptr = nsdu_cfg_ptr->J1939TpRxNSduCtrl;
        switch(SduInfo.MessageType)
        {
            case J1939TP_TPCM_ABORT:
            {
                if(J1939TP_RX_IDLE != nsdu_ctrl_ptr->state)
                {
                    J1939Tp_RxIndication_CM_Abort(SduInfo.ch_idx, SduInfo.pg_idx, SduInfo.nsdu_idx, SduDataPtr);
                }
                else
                {
                    /* The N-SDU is idle, ignore the Abort message received */
                }
                break;
            }

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            case J1939TP_CANFD_TPCM_ENDOFMSGSTATUS:
            {
                J1939Tp_RxIndication_CM_EOMS(SduInfo.ch_idx, SduInfo.pg_idx, SduInfo.nsdu_idx, SduDataPtr);
                break;
            }
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */

            case J1939TP_TPCM_BAM:
            case J1939TP_TPCM_RTS:
            {
                uint32 MaxMsgLength;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                if(TRUE == RxChannelPtr->J1939TpRxCanFDSupport)
                {
                    if (SduInfo.MessageType == J1939TP_TPCM_BAM)
                    {
                        /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.MaxPDUSize.Rx,1 */
                        MaxMsgLength = J1939TP_MAX_SAE_22_BAM_ALLOWED_MSGLENGTH;
                    }
                    else
                    {
                        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.MaxPDUSize.Rx,1 */
                        MaxMsgLength = J1939TP_MAX_SAE_22_CMDT_ALLOWED_MSGLENGTH;
                    }
                    /* Total message length or number of bytes need to be received */
                    RtsMsgLen = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U])<<8U) + (uint32)((uint32)(SduDataPtr[3U])<<16U));
                    RtsNoOfPackets = (((uint32)(SduDataPtr[4U])) + (uint32)((uint32)(SduDataPtr[5U])<<8U) + (uint32)((uint32)(SduDataPtr[6U])<<16U));
                    /* Calculate number of packets from message length in SDU data */
                    VerfiyNrPackets = (uint32)(RtsMsgLen/J1939TP_MAX_CANFD_DT_MSGLENGTH);
                    if((RtsMsgLen % (uint32)J1939TP_MAX_CANFD_DT_MSGLENGTH) != 0U)
                    {
                        VerfiyNrPackets = VerfiyNrPackets + 1U;
                    }
                }
                else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
                {
                    MaxMsgLength = J1939TP_MAX_SAE_ALLOWED_MSGLENGTH;
                    /* Total message length or number of bytes need to be received */
                    RtsMsgLen = (((uint32)(SduDataPtr[1U])) + (uint32)((uint32)(SduDataPtr[2U])<<8U));
                    RtsNoOfPackets = (uint32)(SduDataPtr[3U]) ;
                    /* Calculate number of packets from message length in SDU data */
                    VerfiyNrPackets = (uint32)(RtsMsgLen/J1939TP_MAX_DT_MSGLENGTH);
                    if((RtsMsgLen % (uint32)J1939TP_MAX_DT_MSGLENGTH) != 0U)
                    {
                        VerfiyNrPackets = VerfiyNrPackets + 1U;
                    }
                }

                /* Valid message length should be greater then ZERO and less than the max length */
                if((RtsMsgLen > 0U) && ((RtsMsgLen <= MaxMsgLength) &&
                            (RtsNoOfPackets == VerfiyNrPackets)))
                {
                    if(SduInfo.MetaDataLen > 0U)
                    {
                        EcuC_Ret = EcuC_GetMetaDataCanId(J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[SduInfo.ch_idx].J1939TpRxCmNPduRxConfIdEcuCPbcfg,NULL_PTR,&metaDataCanId);

                        if(EcuC_Ret != E_OK)
                        {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
                        }
                    }

                    /* Copy the MetaDataInfo from received Sdu to nsdu_ctrl_ptr */
                    for(i=0u; i<SduInfo.MetaDataLen; i++)
                    {
                        metaDataShiftVal=i*8u;
                        metaDataVal= (uint8)(metaDataCanId>>metaDataShiftVal);
                        nsdu_ctrl_ptr->J1939TpMetaDataInfo[i] =metaDataVal;
                    }

                    if(SduInfo.MessageType == J1939TP_TPCM_BAM)
                    {
                        J1939Tp_RxIndication_CM_BAM(&SduInfo, PduInfoPtr);
                    }
                    else
                    {
                        J1939Tp_RxIndication_CM_RTS(&SduInfo, PduInfoPtr);
                    }
                }
                else
                {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                    if((RtsMsgLen <= 0U) || ((RtsMsgLen > MaxMsgLength)))
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_TMS,1 */
                        /* RTS message is not consistent, something wrong on message length */
                        /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_TMS */
                        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
                        J1939TP_E_INVALID_TMS);
                    }
                    else
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_TNOP,1 */
                        /* RTS message is not consistent, something wrong on number of packets */
                        /* DET Reporting needs to be done here with error Id E_INVALID_TNOP */
                        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
                        J1939TP_E_INVALID_TNOP);
                    }
#endif /* J1939TP_DEV_ERROR_DETECT == STD_ON) */
                }
                break;
            }
            /* CHECK: NOPARSE */
            default:
            {
                /* Unknown MessageType Nothing to do */
                break;
            }
            /* CHECK: PARSE */
        }
    }

    DBG_J1939TP_RXINDICATION_CM_EXIT(Chan_Idx,PduInfoPtr);
}

/* ***************************************************************************
*  Name                 : J1939Tp_CM_Validation
*  Description          : Handling of Rx TP.CM frame validation
*                       : Handling of RTS (BAM/CMDT) frame or Conn_Abort frame
*  Parameters           : Input: Chan_Idx, PduInfoPtr, SduInfo
*  Return               : boolean
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(boolean, J1939TP_CODE) J1939Tp_CM_Validation(uint16 Chan_Idx,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    boolean SduOK = FALSE;
    boolean CorrectLength = FALSE;
    boolean ValidSession = FALSE;
    P2CONST(J1939Tp_RxChannelType,AUTOMATIC,J1939TP_APPL_CONST) RxChannelPtr =
    &(J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]);

    DBG_J1939TP_CM_VALIDATION_ENTRY(Chan_Idx,PduInfoPtr, SduInfo);

    /* Check Received data type */
    if(TRUE != J1939Tp_CM_Type_check(Chan_Idx, PduInfoPtr, SduInfo, &CorrectLength, &ValidSession))
    {
        /* Do nothing, ignore the message  */
    }
    else
    {
        /* Check Received data length */
        if(TRUE != CorrectLength)
        {
            /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength,1 */
            /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength.FD.CM,1 */
            /* Invalid length, Discard the message */
            /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SDU_LENGTH */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
            J1939TP_E_INVALID_SDU_LENGTH);
#endif
        }
        else
        {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if((TRUE == RxChannelPtr->J1939TpRxCanFDSupport) && (FALSE == ValidSession))
            {
                /* !LINKSTO J1939Tp.EB.FD.InvalidSession.Rx,1 */
                /* Invalid session, Discard the message */
                /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SESSION_NUMBER */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
                J1939TP_E_INVALID_SESSION_NUMBER);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
            }
            else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
            {
                J1939Tp_RxGet_MetaDataInfo(SduInfo, PduInfoPtr,J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[SduInfo->ch_idx].J1939TpRxCmNPduRxConfIdEcuCPbcfg);
                /* Check if the PGN in the message is configured in the channel */
                if(J1939Tp_RxGet_pg_id(SduInfo) == E_OK)
                {
                    /* check the availability of an N-SDU in the current PGN */
                    if(J1939Tp_RxGet_nsdu_id(SduInfo) == E_OK)
                    {
                        SduOK = TRUE;
                    }
                    /* All SDU's are busy */
                    else
                    {
                        if(SduInfo->MessageType == J1939TP_TPCM_RTS)
                        {
                            /* different SA but with same PGN*/
                            /* Send abort connection for the new RTS as limited resources with the received SA/DA for same PGN*/
                            /* keep current reception on this NSDu without any changes */
                            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.CanNotSupportAnotherSession,1 */
                            RxChannelPtr->J1939TpRxChannelAbort->AbortReason = J1939TP_TPCM_ABORT_REASON_CONNECTION;
                            RxChannelPtr->J1939TpRxChannelAbort->pgn = SduInfo->pgn;
                            RxChannelPtr->J1939TpRxChannelAbort->sa = SduInfo->da;   /*RxChannel: Swap SA and DA */
                            RxChannelPtr->J1939TpRxChannelAbort->da = SduInfo->sa;   /*RxChannel: Swap SA and DA */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                            RxChannelPtr->J1939TpRxChannelAbort->session_num = SduInfo->session_num;
#endif
                            RxChannelPtr->J1939TpRxChannelAbort->AbortFlag = TRUE;
                        }
                        else
                        {
                            /* Different SA for on-going PGN , Ignore this BAM/ABORT reception */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Bam,1 */
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Abort,1 */
                        }
                    }
                }
                /* PGN not found */
                else
                {
                    /* Abort the connection as unsupported or unknown PGN is received. reason =  250 */
                    /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.NotListed,1 */
                    RxChannelPtr->J1939TpRxChannelAbort->AbortReason = J1939TP_TPCM_ABORT_REASON_UNLISTED;
                    RxChannelPtr->J1939TpRxChannelAbort->pgn = SduInfo->pgn;
                    RxChannelPtr->J1939TpRxChannelAbort->sa = SduInfo->da;   /*RxChannel: Swap SA and DA */
                    RxChannelPtr->J1939TpRxChannelAbort->da = SduInfo->sa;   /*RxChannel: Swap SA and DA */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                    RxChannelPtr->J1939TpRxChannelAbort->session_num = SduInfo->session_num;
#endif
                    RxChannelPtr->J1939TpRxChannelAbort->AbortFlag = TRUE;

                    /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_PGN */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
                    J1939TP_E_INVALID_PGN);
#endif
                }
            }
        }
    }

    DBG_J1939TP_CM_VALIDATION_EXIT(Chan_Idx,PduInfoPtr, SduInfo);

    return SduOK;
}

/* ***************************************************************************
*  Name                 : J1939Tp_CM_Type_check
*  Description          : check the CM frame type according to the network type
*                       :
*  Parameters           : Input: Chan_Idx, PduInfoPtr, SduInfo, CorrectLength, ValidSession
*  Return               : boolean
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(boolean, J1939TP_CODE) J1939Tp_CM_Type_check(uint16 Chan_Idx,
P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,
P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo,
P2VAR(boolean, AUTOMATIC, J1939TP_APPL_DATA) CorrectLength,
P2VAR(boolean, AUTOMATIC, J1939TP_APPL_DATA) ValidSession)
{
    /* Local Variables */
    boolean CorrectType = FALSE;

#if (J1939TP_RX_CANFD_SUPPORT == STD_OFF)
    TS_PARAM_UNUSED(Chan_Idx);
    TS_PARAM_UNUSED(ValidSession);
#endif

    DBG_J1939TP_CM_TYPE_CHECK_ENTRY(Chan_Idx, PduInfoPtr, SduInfo, CorrectLength, ValidSession);

    if(SduInfo->ReceivedLength > 0U)
    {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxCanFDSupport)
        {
            uint8 FrameType;
            uint8 Session_num;
            (J1939TP_GET_FRAME_TYPE(PduInfoPtr->SduDataPtr[0U], FrameType));
            (J1939TP_GET_SESSION_NUMBER(PduInfoPtr->SduDataPtr[0U], Session_num));
            /* assign inital value to session_num, AssuranceDataType to avoid compiler warnings */
            SduInfo->session_num = 254U;
            SduInfo->AssuranceDataType = 254U;
            switch(FrameType)
            {
                case J1939TP_CANFD_TPCM_RTS:
                {
                    CorrectType = TRUE;
                    if((PduLengthType)J1939TP_CANFD_CONTROL_FRAME_LENGTH == SduInfo->ReceivedLength)
                    {
                        *CorrectLength = TRUE;
                        /* !LINKSTO J1939Tp.SAE.FD.TP_CM_RTS.FrameFormat,1 */
                        SduInfo->pgn = ((uint32)(PduInfoPtr->SduDataPtr[9U])) + ((uint32)(PduInfoPtr->SduDataPtr[10U])<<8U) + ((uint32)(PduInfoPtr->SduDataPtr[11U])<<16U);
                        SduInfo->MessageType = J1939TP_TPCM_RTS;
                        /* check the session_num boundries */
                        /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.ConcurrentSessions.Rx,1 */
                        if(Session_num < J1939TP_CANFD_CMDT_MAX_CONCURRENT_SESSIONS)
                        {
                            *ValidSession = TRUE;
                            SduInfo->session_num = Session_num;
                            SduInfo->AssuranceDataType = PduInfoPtr->SduDataPtr[8U];
                        }
                    }
                    break;
                }

                case J1939TP_CANFD_TPCM_ENDOFMSGSTATUS:
                {
                    CorrectType = TRUE;
                    if((PduLengthType)J1939TP_CANFD_CONTROL_FRAME_LENGTH <= SduInfo->ReceivedLength)
                    {
                        PduLengthType EOMS_Length = (PduLengthType)((PduLengthType)J1939TP_CANFD_CONTROL_FRAME_LENGTH + (PduLengthType)PduInfoPtr->SduDataPtr[7U]);
                        if(SduInfo->ReceivedLength >= EOMS_Length)
                        {
                            *CorrectLength = TRUE;
                            /* !LINKSTO J1939Tp.SAE.FD.TP_CM_EndOfMsgStatus.FrameFormat,1 */
                            SduInfo->pgn = ((uint32)(PduInfoPtr->SduDataPtr[9U])) + ((uint32)(PduInfoPtr->SduDataPtr[10U])<<8U) + ((uint32)(PduInfoPtr->SduDataPtr[11U])<<16U);
                            SduInfo->MessageType = J1939TP_CANFD_TPCM_ENDOFMSGSTATUS;
                            /* Check for the Session_num done with below within the check of the Message type */
                            *ValidSession = TRUE;
                            SduInfo->session_num = Session_num;
                            SduInfo->AssuranceDataType = PduInfoPtr->SduDataPtr[8U];
                        }
                    }
                    break;
                }

                case J1939TP_CANFD_TPCM_ABORT:
                {
                    CorrectType = TRUE;
                    if((PduLengthType)J1939TP_CANFD_CONTROL_FRAME_LENGTH == SduInfo->ReceivedLength)
                    {
                        *CorrectLength = TRUE;
                        /* !LINKSTO J1939Tp.SAE.FD.Conn_Abort.FrameFormat,1 */
                        SduInfo->pgn = ((uint32)(PduInfoPtr->SduDataPtr[9U])) + ((uint32)(PduInfoPtr->SduDataPtr[10U])<<8U) + ((uint32)(PduInfoPtr->SduDataPtr[11U])<<16U);
                        SduInfo->MessageType = J1939TP_TPCM_ABORT;
                        /* Check for the Session_num done with below within the check of the Message type */
                        *ValidSession = TRUE;
                        SduInfo->session_num = Session_num;
                        SduInfo->AssuranceDataType = 0U;
                    }
                    break;
                }

                case J1939TP_CANFD_TPCM_BAM:
                {
                    CorrectType = TRUE;
                    if((PduLengthType)J1939TP_CANFD_CONTROL_FRAME_LENGTH == SduInfo->ReceivedLength)
                    {
                        *CorrectLength = TRUE;
                        /* !LINKSTO J1939Tp.SAE.FD.TP_CM_BAM.FrameFormat,1 */
                        SduInfo->pgn = ((uint32)(PduInfoPtr->SduDataPtr[9U])) + ((uint32)(PduInfoPtr->SduDataPtr[10U])<<8U) + ((uint32)(PduInfoPtr->SduDataPtr[11U])<<16U);
                        SduInfo->MessageType = J1939TP_TPCM_BAM;
                        /* check the session_num boundries */
                        /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.ConcurrentSessions.Rx,1 */
                        if(Session_num < J1939TP_CANFD_BAM_MAX_CONCURRENT_SESSIONS)
                        {
                            *ValidSession = TRUE;
                            SduInfo->session_num = Session_num;
                            SduInfo->AssuranceDataType = PduInfoPtr->SduDataPtr[8U];
                        }
                    }
                    break;
                }

                default:
                {
                    /* Unknown MessageType, ignore the message */
                    break;
                }
            }
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            switch(PduInfoPtr->SduDataPtr[0])
            {
                case J1939TP_TPCM_RTS:
                case J1939TP_TPCM_ABORT:
                case J1939TP_TPCM_BAM:
                {
                    CorrectType = TRUE;
                    if (SduInfo->ReceivedLength == (PduLengthType)J1939TP_FRAME_LENGTH)
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Tp_00057.PGN,1 */
                        *CorrectLength = TRUE;
                        SduInfo->pgn = ((uint32)(PduInfoPtr->SduDataPtr[5])) + ((uint32)(PduInfoPtr->SduDataPtr[6])<<8) + ((uint32)(PduInfoPtr->SduDataPtr[7])<<16);
                        SduInfo->MessageType = PduInfoPtr->SduDataPtr[0];
                    }
                    break;
                }

                default:
                {
                    /* Unknown MessageType, ignore the message */
                    break;
                }
            }
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength,1 */
        /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength.FD.CM,1 */
        /* If the pdu length received is 0, no need to check the type. */
        /* Invalid length, Discard the message */
        /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SDU_LENGTH */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
        J1939TP_E_INVALID_SDU_LENGTH);
#endif
    }
    DBG_J1939TP_CM_TYPE_CHECK_EXIT(Chan_Idx, PduInfoPtr, SduInfo, CorrectLength, ValidSession);

    return CorrectType;
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_DirectPg
*  Description          : Handling of Rx DirectPg frame
*                       :
*  Parameters           : Input: Chan_Idx Pg_Idx nsdu_ctrl_ptr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_DirectPg(uint16 Chan_Idx,uint16 Pg_Idx,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,uint32 metaDataCanId)
{
    uint16 loop_idx4;
    /* Initialization of pointer to selected Rx NSdu configuration structure */
    P2CONST(J1939Tp_RxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = NULL_PTR;
    P2CONST(J1939Tp_RxNSduTypePbcfg,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr_pbcfg = NULL_PTR;
    /* Remaining bytes to be transferred */
    PduLengthType tRxbufferSize;
    P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) c_RxDataPtr = PduInfoPtr->SduDataPtr;
    BufReq_ReturnType tBufReq_ReturnType;
    PduInfoType J1939TpRxPduInfo;
    boolean tNSDUAvailable = FALSE;

    DBG_J1939TP_RXINDICATION_DIRECTPG_ENTRY(Chan_Idx, Pg_Idx,PduInfoPtr,metaDataCanId);

    for (loop_idx4=0U; (loop_idx4<(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[Pg_Idx]).J1939TpNumberOfRxNSdu)) && (tNSDUAvailable != TRUE) ;loop_idx4++)
    {
        if ((((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[Pg_Idx]).J1939TpRxNSdu[loop_idx4]).J1939TpRxNSduCtrl[0].state == J1939TP_RX_IDLE )
        {
            /* Break the loop */
            tNSDUAvailable = TRUE;

            nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[Pg_Idx]).J1939TpRxNSdu[loop_idx4]);
            nsdu_cfg_ptr_pbcfg = &(((J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[Chan_Idx]).J1939TpRxPgPbcfg[Pg_Idx]).J1939TpRxNSduPbcfg[loop_idx4]);
        }
        else
        {
            /* Nothing to do-1 */
        }
    }

    if (tNSDUAvailable == TRUE)
    {
        /* Provide actual Payload length as TpSduLength to StartOfReception API */
        PduLengthType ReceivedLength = (PduInfoPtr->SduLength);
        uint8 MetaDataLen = nsdu_cfg_ptr->RxNsduMetaDataLen;
        if(MetaDataLen > 0U)
        {
            uint8 metaDataInfo[4] = {0x00,0x00,0x00,0x00};
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
            if((TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxCanFDSupport)
            && (FALSE == J1939TP_CANID_EXTENDED(metaDataCanId)))
            {
                /* Standard Can ID, PDU type 3, only supported in case of CanFD channel */
                /* !LINKSTO EB_Ref.SAE.FD.D_PDU3.Format.SA,1 */
                metaDataInfo[0U] = (uint8)(metaDataCanId);
                /* Always global destination address */
                /* !LINKSTO EB_Ref.SAE.FD.D_PDU3.Format.DA,1 */
                metaDataInfo[1U] = J1939TP_GLOBAL_ADDRESS;
                metaDataInfo[2U] = J1939TP_UNUSED_BYTE_PADDING;
                /* !LINKSTO EB_Ref.SAE.FD.D_PDU3.Format.Priority,1 */
                /* save the last (unnecessary) 3 bits in the last byte of the meta data */
                metaDataInfo[3U] = (uint8)(metaDataCanId >> 8U);
            }
            else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
            {
                /* Extended Can ID, PDU type 1 */
                /* unpack received metadata info */
                uint8 metaDataPositionIdx;
                uint8 metaDataShiftVal = 0U;
                uint32 currMetaDataVal = 0U;
                for(metaDataPositionIdx = 0U; metaDataPositionIdx < 4U; metaDataPositionIdx++)
                {
                    metaDataShiftVal = metaDataPositionIdx * 8U;
                    currMetaDataVal = metaDataCanId >> metaDataShiftVal;
                    metaDataInfo[metaDataPositionIdx] =(uint8)(currMetaDataVal);
                }
            }
            J1939Tp_SetEcuCMetaDataRx(MetaDataLen,metaDataInfo,nsdu_cfg_ptr_pbcfg->J1939TpRxNSduIdEcuCPbcfg);
        }

        tBufReq_ReturnType = PduR_J1939TpStartOfReception(nsdu_cfg_ptr->J1939TpRxNSduIdPduR, ReceivedLength, &tRxbufferSize);
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00040.StartOfReception.Direct,1 */
        if((tBufReq_ReturnType == BUFREQ_OK) && (tRxbufferSize >= ReceivedLength))
        {
            J1939TpRxPduInfo.SduDataPtr = c_RxDataPtr;
            J1939TpRxPduInfo.SduLength = ReceivedLength;
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00162.DirectPg,1 */
            tBufReq_ReturnType = PduR_J1939TpCopyRxData(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,&J1939TpRxPduInfo,&tRxbufferSize);
            if (tBufReq_ReturnType == BUFREQ_OK)
            {
                /* Indicate the upper layer */
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_OK);
            }
            else
            {
                /* Silent Abort- Report to the upper layer */
                PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);
            }
        }
        else if ((tBufReq_ReturnType == BUFREQ_OK) && (tRxbufferSize < ReceivedLength))
        {
            /* Report to the upper layer, message length > available buffer*/
            PduR_J1939TpRxIndication(nsdu_cfg_ptr->J1939TpRxNSduIdPduR,E_NOT_OK);
        }
        else
        {
            /* BUFREQ_E_NOT_OK */
            /* BUFREQ_E_OVFL */
            /* Silent Abort- don't report to the upper layer, as no established connection */
        }
    }
    else
    {
            /* Nothing to do-3 */
    }
    DBG_J1939TP_RXINDICATION_DIRECTPG_EXIT(Chan_Idx, Pg_Idx,PduInfoPtr,metaDataCanId);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_TxFcN_CM
*  Description          : Handling of Tx TP.CM frame
*                       : Handling of CTS (BAM/CMDT) frame or Conn_Abort frame or TP.CM_EndOfMsgAck
*  Parameters           : Input: Chan_Idx PduInfoPtr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_TxFcN_CM(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
    /* pgn number in the frame */
    uint32 NrPackets = 0U;
    uint32 MsgLength = 0U;
    uint32 c_pgn = 0U;
    uint32 metaDataCanId=0x00000000;
    uint8 CM_Type = 0U;
    /* Local data initialization*/
    P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) c_RxDataPtr = PduInfoPtr->SduDataPtr;

    Std_ReturnType EcuC_Ret = E_OK;
    uint16 loop_idx8;
    uint16 loop_idx9;
    boolean tTxPduOk2 = FALSE;
    boolean tTxPduOk3 = FALSE;
    uint16 Pg_Idx = 0U;
    uint16 Nsdu_Idx = 0U;
    uint8 MetaDataLen = 0U;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    uint8 Session_num = 0U;
#endif

    /* Initialization of pointer to selected Tx NSdu configuration structure */
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr_tx = NULL_PTR;
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_pointer_tx = NULL_PTR;

    DBG_J1939TP_RXINDICATION_TXFCN_CM_ENTRY(Chan_Idx,PduInfoPtr);

    if(TRUE == J1939Tp_Validate_TxFcN_CM_Length(Chan_Idx, PduInfoPtr, &CM_Type, &NrPackets, &MsgLength, &c_pgn))
    {
        for(loop_idx8 = 0U; (loop_idx8<((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpNumberOfTxPg))&& (tTxPduOk2 != TRUE); loop_idx8++)
        {
            if(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[loop_idx8]).J1939TpTxPgPGN == c_pgn)
            {
                tTxPduOk2 = TRUE;
                Pg_Idx = loop_idx8;
            }
            else
            {
                /* Ignore the CTS,or ENDOGACK or Abort frame-0 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.CTS,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Eom,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Abort,1 */
            }
        }
        if(tTxPduOk2 == TRUE)
        {
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
            (J1939TP_GET_SESSION_NUMBER(c_RxDataPtr[0U], Session_num));
#endif
            for (loop_idx9 = 0U; (loop_idx9<(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpNumberOfTxNSdu))&& (tTxPduOk3 != TRUE); loop_idx9++)
            {
                /* Optimize access to structure element */
                nsdu_ctrl_ptr_tx = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[loop_idx9]).J1939TpTxNSduCtrl;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                if (((FALSE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) || (nsdu_ctrl_ptr_tx->session_num == Session_num))
                    && ((nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_STATE_CTS) || (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK) ||
                    (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION) || (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA) || ((CM_Type == J1939TP_TPCM_ABORT) && (nsdu_ctrl_ptr_tx->state != J1939TP_TX_IDLE))))
#else
                if ((nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_STATE_CTS) || (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK) ||
                     (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION) || (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA) || ((CM_Type == J1939TP_TPCM_ABORT) && (nsdu_ctrl_ptr_tx->state != J1939TP_TX_IDLE)))
#endif  /*J1939TP_TX_CANFD_SUPPORT == STD_ON*/
                {
                    tTxPduOk3 = TRUE;
                    Nsdu_Idx = loop_idx9;
                    MetaDataLen = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpRxFcNPduMetaData;
                    if(MetaDataLen > 0U)
                    {
                        EcuC_Ret= EcuC_GetMetaDataCanId((J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[Chan_Idx]).J1939TpRxFcNPduTxConfIdEcuCPbcfg,NULL_PTR,&metaDataCanId);

                        if(EcuC_Ret != E_OK)
                        {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
                        }
                    }
                }
                else
                {
                    /* Ignore the CTS,or EOMACK or Abort frame-2 */
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.CTS,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Eom,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Abort,1 */
                }
            }
            if (tTxPduOk3 == TRUE)
            {
                nsdu_ctrl_ptr_tx = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl;
                nsdu_cfg_pointer_tx = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]);

                switch (CM_Type)
                {
                    case J1939TP_TPCM_CTS:
                    {
                        J1939Tp_RxIndication_TxFcN_CTS(Chan_Idx, Pg_Idx, Nsdu_Idx, c_RxDataPtr);
                        break;
                    }
                    case J1939TP_TPCM_ABORT:
                    {
                        /* Check if Abort reason is valid or not */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                        if(((FALSE == J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxCanFDSupport) &&((c_RxDataPtr[1U] < 10U) || (c_RxDataPtr[1U] > 249U)))
                        || ((TRUE == J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxCanFDSupport) &&((c_RxDataPtr[8U] < 12U) || (c_RxDataPtr[8U] > 249U))))
#else
                        if((c_RxDataPtr[1U] < 10U) || (c_RxDataPtr[1U] > 249U))
#endif
                        {
                            /* Report to the upper layer */
                            /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Reject.Tx,1 */
                            PduR_J1939TpTxConfirmation(nsdu_cfg_pointer_tx->J1939TpTxNSduIdPduR,E_NOT_OK);
                            J1939Tp_Reinit_Tx(Chan_Idx, Pg_Idx, Nsdu_Idx);
                        }
                        else
                        {
                            /* Report to the upper layer */
                            PduR_J1939TpTxConfirmation(nsdu_cfg_pointer_tx->J1939TpTxNSduIdPduR,E_NOT_OK);
                            J1939Tp_Reinit_Tx(Chan_Idx, Pg_Idx, Nsdu_Idx);
                            /* If Abort reason is invalid then raise DET error with error Id J1939TP_E_INVALID_CAR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_CAR);
#endif
                        }
                        break;
                    }
                    case J1939TP_TPCM_ENDOFMSGACK:
                    {
                        /* ENDOFMSGACK Frame is received*/
                        /* Issue 250538: Check the PGN & MsgLength of received EOMAck frame against PGN & MsgLength of the RTS frame */
                        if((nsdu_ctrl_ptr_tx->pgn == c_pgn) && (MsgLength == nsdu_ctrl_ptr_tx->msglength))
                        {
                            /* Check if Total no. of packets is same as sequence number of last transmitted message.
                             * This check is required to ensure that we have received correct EOMAck frame (Issue 250538) */
                            if(NrPackets == ((nsdu_ctrl_ptr_tx->sn - 1U)))
                            {
                                /* !LINKSTO EB_Ref.SWS_J1939Tp_00119.Trans.CMDT,1 */
                                /* Confirm to the upper layer */
                                PduR_J1939TpTxConfirmation(nsdu_cfg_pointer_tx->J1939TpTxNSduIdPduR,E_OK);
                                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.Reset,1 */
                                J1939Tp_Reinit_Tx(Chan_Idx, Pg_Idx, Nsdu_Idx);
                            }
                        }
                        break;
                    }
                    default:
                    {
                        /* Nothing to do-11 */
                        break;
                    }
                }
            }
            else
            {
                /* Ignore the CTS,or ENDOGACK or Abort frame-3 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.CTS,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Eom,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Abort,1 */
            }
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_PGN,1 */
            /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_PGN */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PGN);
#endif
        }
    }
    else
    {
        /* Invalid length-Discard the message */
        /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength,1 */
        /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SDU_LENGTH */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
        J1939TP_E_INVALID_SDU_LENGTH);
#endif
    }

    DBG_J1939TP_RXINDICATION_TXFCN_CM_EXIT(Chan_Idx,PduInfoPtr);

}

/* ***************************************************************************
*  Name                 : J1939Tp_Validate_TxFcN_CM_Length
*  Description          : validate the length of Tx TP.CM frame
*  Parameters           : Input: Chan_Idx PduInfoPtr
*                         Output: CM_Type_ptr NrPackets_ptr MsgLength_ptr c_pgn_ptr
*  Return               : boolean
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(boolean, J1939TP_CODE) J1939Tp_Validate_TxFcN_CM_Length(uint16 Chan_Idx, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr,
P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) CM_Type_ptr,
P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) NrPackets_ptr,
P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) MsgLength_ptr,
P2VAR(uint32, AUTOMATIC, J1939TP_APPL_DATA) c_pgn_ptr)
{
    /* Local data initialization */
    boolean validLength = FALSE;
    /* Buffer received */
    P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) c_RxDataPtr = PduInfoPtr->SduDataPtr;
    /* Remaining bytes to be transferred */
    PduLengthType ReceivedLength = (PduInfoPtr->SduLength);

#if (J1939TP_TX_CANFD_SUPPORT == STD_OFF)
    TS_PARAM_UNUSED(Chan_Idx);
#endif

    DBG_J1939TP_VALIDATE_TXFCN_CM_LENGTH_ENTRY(Chan_Idx, PduInfoPtr, CM_Type_ptr, NrPackets_ptr, MsgLength_ptr, c_pgn_ptr);

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if((TRUE == J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxCanFDSupport) && (ReceivedLength == J1939TP_CANFD_CONTROL_FRAME_LENGTH))
    {
        /* To know which Frame based on control byte */
        J1939TP_GET_FRAME_TYPE(c_RxDataPtr[0U], (*CM_Type_ptr));

        /* check the CanFD FC message type */
        switch(*CM_Type_ptr)
        {
            case J1939TP_CANFD_TPCM_CTS:
            {
                *CM_Type_ptr = J1939TP_TPCM_CTS;
                break;
            }
            case J1939TP_CANFD_TPCM_ENDOFMSGACK:
            {
                *CM_Type_ptr = J1939TP_TPCM_ENDOFMSGACK;
                break;
            }
            case J1939TP_CANFD_TPCM_ABORT:
            {
                *CM_Type_ptr = J1939TP_TPCM_ABORT;
                break;
            }
            default:
            {
                /* Unknown MessageType, ignore the message */
                break;
            }
        }

        /* Calculation of pgn, message length and number of packets from the frame */
        *c_pgn_ptr = ((uint32)(c_RxDataPtr[9U])) + ((uint32)(c_RxDataPtr[10U]) << 8U) + ((uint32)(c_RxDataPtr[11U]) << 16U);
        *MsgLength_ptr = (((uint32)(c_RxDataPtr[1U])) + (uint32)((uint32)(c_RxDataPtr[2U]) << 8U) + (uint32)((uint32)(c_RxDataPtr[3U]) << 16U));
        *NrPackets_ptr = (((uint32)(c_RxDataPtr[4U])) + (uint32)((uint32)(c_RxDataPtr[5U]) << 8U) + (uint32)((uint32)(c_RxDataPtr[6U]) << 16U));
        /* The message length is valid for CanFD channel */
        validLength = TRUE;
    }
    else if((FALSE == J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxCanFDSupport) && (ReceivedLength == J1939TP_FRAME_LENGTH))
#else
    if(ReceivedLength == J1939TP_FRAME_LENGTH)
#endif
    {
        /* To know which Frame based on control byte */
        *CM_Type_ptr = c_RxDataPtr[0U];
        /* Calculation of pgn, message length and number of packets from the frame */
        *c_pgn_ptr = ((uint32)(c_RxDataPtr[5U])) + ((uint32)(c_RxDataPtr[6U]) << 8U) + ((uint32)(c_RxDataPtr[7U]) << 16U);
        *MsgLength_ptr = (((uint32)(c_RxDataPtr[1U])) + ((uint32)(c_RxDataPtr[2U]) << 8U));
        *NrPackets_ptr = c_RxDataPtr[3U];
        /* The message length is valid for Can channel */
        validLength = TRUE;
    }
    else
    {
        /* Invalid length-Discard the message */
        validLength = FALSE;
    }

    DBG_J1939TP_VALIDATE_TXFCN_CM_LENGTH_EXIT(Chan_Idx, PduInfoPtr, CM_Type_ptr, NrPackets_ptr, MsgLength_ptr, c_pgn_ptr);

    return validLength;
}

static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_TxFcN_CTS(uint16 Chan_Idx,uint16 Pg_Idx,uint16 Nsdu_Idx,P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) c_RxDataPtr)
{
    /* Initialization of pointer to selected Tx NSdu configuration structure */
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr_tx = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    uint32 Nxt_pckt_to_be_sent;
#else
    uint8 Nxt_pckt_to_be_sent;
#endif

    DBG_J1939TP_RXINDICATION_TXFCN_CTS_ENTRY(Chan_Idx,Pg_Idx,Nsdu_Idx,c_RxDataPtr);

    /* Indication of CTS Frame */
    if((nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_STATE_CTS) || (nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK))
    {
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        /* Check if the request code is set to request the retransmission of the EOMS message */
        if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (1U == c_RxDataPtr[8U]))
        {
            /* Check request code, request the retransmission of the EOMS */
            /* Check if the EOMS is transmitted already, if the retry is enabled and if T3 hasn't elapsed yet */
            if((nsdu_ctrl_ptr_tx->state == J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK)
            && (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxRetryInfo != NULL_PTR)
            && (FALSE == nsdu_ctrl_ptr_tx->T3TimeElapsed))
            {
                /* !LINKSTO J1939Tp.SAE.FD.CmdtTransfer.Tx.EOMS.TimeOut.Elapsed,1 */
                /* If retry is valid, raise retry_cts_flag and change sequence number and data_cnt */
                nsdu_ctrl_ptr_tx->retry_cts_flag = TRUE;
                /* Change the State */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr_tx, J1939TP_CMDT_TX_STATE_EOMS_TRANSMISSION);
            }
            else
            {
                /* The retry isn't enabled, the EOMS isn't transmitted yet or T3 elapsed */
                /* Do nothing */
            }
        }
        else if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (1U < c_RxDataPtr[8U]))
        {
            /* Wrong request code, Do nothing */
        }
        else
#endif
        {
            /* Read the number of packets */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)
            {
                nsdu_ctrl_ptr_tx->cts_packets = c_RxDataPtr[7U];        /*The number of packets that can be sent*/
            }
            else
#endif
            {
                nsdu_ctrl_ptr_tx->cts_packets = c_RxDataPtr[1U];        /*The number of packets that can be sent*/
            }

            /* Issue 249859: No. of packets in received CTS frame must be less than Maximum no. of packets in RTS */
            if(nsdu_ctrl_ptr_tx->cts_packets <= nsdu_ctrl_ptr_tx->RxNoPacketsInRTS)
            {
                /* stop the T3 timer as we have received a valid CTS */
                nsdu_ctrl_ptr_tx->T3TimeElapsed = FALSE;
                nsdu_ctrl_ptr_tx->StartT3Time = FALSE;
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)
                {
                    Nxt_pckt_to_be_sent = (((uint32)(c_RxDataPtr[4U])) + (uint32)((uint32)(c_RxDataPtr[5U]) << 8U) + (uint32)((uint32)(c_RxDataPtr[6U]) << 16U));    /*Next packet number that expected to be sent*/
                }
                else
#endif
                {
                    Nxt_pckt_to_be_sent = c_RxDataPtr[2U];    /*Next packet number that expected to be sent*/
                }

                /* Check the number of packets that can be sent is equal to 0 */
                if(nsdu_ctrl_ptr_tx->cts_packets == 0U)
                {
                    /* !LINKSTO J1939Tp.SWS_J1939Tp_00195,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.T4,1 */
                    /* Start the T4 timer */
                    nsdu_ctrl_ptr_tx->StartT4Time = TRUE;
                    nsdu_ctrl_ptr_tx->T4TimeElapsed = FALSE;
                    nsdu_ctrl_ptr_tx->T4TimeCounter = 0U;
                }
                /*Next packet number to be sent*/
                else if(Nxt_pckt_to_be_sent == nsdu_ctrl_ptr_tx->sn)
                {
                    nsdu_ctrl_ptr_tx->SN_Confirmed_in_CTS = (uint32)Nxt_pckt_to_be_sent - (uint32)1U;
                    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.CTS.Received,1 */
                    /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.Accept.Tx,1 */
                    /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.ContinueDT.Tx,1 */
                    /* Change the State */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr_tx, J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION);
                    /* As we have received valid CTS with non zero value for no. of packets, Timer T4 need not be running anymore */
                    nsdu_ctrl_ptr_tx->StartT4Time = FALSE;
                    nsdu_ctrl_ptr_tx->T4TimeElapsed = FALSE;
                }
                else
                {
                    /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_NPN */
                    /* Check if Retry support is enabled for this Tx channel. If Retry is not enabled then abort the transmission with reason 255 (unassigned) */
                    if(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxRetryInfo != NULL_PTR)
                    {
                        if((Nxt_pckt_to_be_sent < nsdu_ctrl_ptr_tx->sn)  && (Nxt_pckt_to_be_sent > nsdu_ctrl_ptr_tx->SN_Confirmed_in_CTS))
                        {
                            /* If retry is valid, raise retry_cts_flag and change sequence number and data_cnt */
                            nsdu_ctrl_ptr_tx->retry_cts_flag = TRUE;
                            nsdu_ctrl_ptr_tx->sn = Nxt_pckt_to_be_sent;

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                            if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)
                            {
                                nsdu_ctrl_ptr_tx->data_cnt = ((uint32)Nxt_pckt_to_be_sent - (uint32)1U) * (uint32)J1939TP_MAX_CANFD_DT_MSGLENGTH;
                            }
                            else
#endif
                            {
                                nsdu_ctrl_ptr_tx->data_cnt = ((uint32)Nxt_pckt_to_be_sent - (uint32)1U) * (uint32)J1939TP_DATA_LENGTH;
                            }
                            nsdu_ctrl_ptr_tx->SN_Confirmed_in_CTS = (uint32)Nxt_pckt_to_be_sent - (uint32)1U;
                            /* Change the State */
                            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr_tx, J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION);
                        }
                        else
                        {
                            /* !LINKSTO J1939Tp.SWS_J1939Tp_00223,1 */
                            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr_tx, J1939TP_CMDT_TX_STATE_ABORT);
                            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.WrongSequenceNumberReceived,1 */
                            nsdu_ctrl_ptr_tx->AbortReason = J1939TP_TPCM_ABORT_REASON_BAD_SEQUENCE_NUMBER;
                            /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_NPN,1 */
                            /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_NOP */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_NPN);
#endif
                        }
                    }
                    else
                    {
                        /* !LINKSTO J1939Tp.SWS_J1939Tp_00194,1 */
                        /* Abort transmission as the retry not supported with reason 5:Maximum retransmit request limit reached and notify upper layer */
                        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr_tx, J1939TP_CMDT_TX_STATE_ABORT);
                        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.MaxRetransmitLimitReached,1 */
                        nsdu_ctrl_ptr_tx->AbortReason = J1939TP_TPCM_ABORT_REASON_MAX_RETRANSMIT_REACHED;
                    }
                }
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_INVALID_NOP,1 */
                /* No. of packets that can be sent in received CTS frame must be less than Maximum no. of packets in RTS */
                /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_NOP */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_NOP);
#endif
            }
        }
    }
    else
    {
        /* !LINKSTO J1939Tp.SWS_J1939Tp_00224,1 */
        /* Abort transmission as CTS message received when data transfer is in progress and notify upper layer */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr_tx, J1939TP_CMDT_TX_STATE_ABORT);
        /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.UnexpectedCtsReceived,1 */
        nsdu_ctrl_ptr_tx->AbortReason = J1939TP_TPCM_ABORT_REASON_CTS_RX_WHEN_DATA_TRANSMIT;
    }

    DBG_J1939TP_RXINDICATION_TXFCN_CTS_EXIT(Chan_Idx,Pg_Idx,Nsdu_Idx,c_RxDataPtr);
}

/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_DT
*  Description          : Handling of Rx TP.DT frame
*                       : Handling of DT (BAM/CMDT) frame
*  Parameters           : Input: Chan_Idx PduInfoPtr u8SA_val u8DA_val
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_DT(uint16 Chan_Idx,P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr, uint8 u8SA_val,uint8 u8DA_val)
{
    uint16 loop_idx5;
    uint16 loop_idx6;
    boolean tRxPduOk4 = FALSE;
    uint16 Pg_Idx = 0U;
    uint16 Nsdu_Idx = 0U;
    uint8 metaDataPositionIdx;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    uint8 Session_num = J1939TP_INVALID_SESSION_NUMBER;
    boolean ValidFrame = TRUE;
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    Std_ReturnType EcuC_Ret = E_OK;
    uint32 metaDataCanId=0x00000000;
    uint8 metaDataShiftVal = 0U;
    uint32 currMetaDataVal = 0U;
    uint8 MetaDataLen = J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxDtNPduMetaDataLen;
    /* Initialization of pointer to selected Rx NSdu configuration structure */
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC,  J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    /* Remaining bytes to be transferred */
    PduLengthType ReceivedLength = PduInfoPtr->SduLength;
    PduLengthType ExpectedLength;
    DBG_J1939TP_RXINDICATION_DT_ENTRY(Chan_Idx,PduInfoPtr,u8SA_val,u8DA_val);

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    /* check that the length is larger than 1 and get the session_num for the data */
    if((TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxCanFDSupport) && (ReceivedLength >= 1U))
    {
        /* !LINKSTO J1939Tp.SAE.FD.TP_DT.FrameFormat,1 */
        (J1939TP_CANFD_DT_SESSION_NUMBER(PduInfoPtr->SduDataPtr[0U], Session_num));
        (J1939TP_VALID_DT_CANFD_FRAME(PduInfoPtr->SduDataPtr[0U], ValidFrame));
    }
    if(TRUE != ValidFrame)
    {
        /* Do nothing, invalid DT frame for CanFD channel */
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        for (loop_idx5=0U;(loop_idx5<((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpNumberOfRxPg))&& (tRxPduOk4 != TRUE);loop_idx5++)
        {
            for (loop_idx6=0U;(loop_idx6<(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[loop_idx5]).J1939TpNumberOfRxNSdu))&& (tRxPduOk4 != TRUE);loop_idx6++)
            {
                /*Optimize access to structure element*/
                nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[loop_idx5]).J1939TpRxNSdu[loop_idx6]).J1939TpRxNSduCtrl;
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                if  (((nsdu_ctrl_ptr->state == J1939TP_CMDT_RX_STATE_WAIT_DATA) || (nsdu_ctrl_ptr->state == J1939TP_BAM_RX_STATE_WAIT_DATA))
                  && ((nsdu_ctrl_ptr->sa ==  u8SA_val)&& (nsdu_ctrl_ptr->da ==  u8DA_val)
                  && ((FALSE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxCanFDSupport) || (nsdu_ctrl_ptr->session_num == Session_num))))
#else
                if (((nsdu_ctrl_ptr->state == J1939TP_CMDT_RX_STATE_WAIT_DATA) || (nsdu_ctrl_ptr->state == J1939TP_BAM_RX_STATE_WAIT_DATA))
                 && ((nsdu_ctrl_ptr->sa ==  u8SA_val)&& (nsdu_ctrl_ptr->da ==  u8DA_val)))
#endif  /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
                {
                    /* !LINKSTO EB_Ref.SAE.FD.UniqueSession.Rx,1 */
                    tRxPduOk4 = TRUE;
                    Pg_Idx = loop_idx5;
                    Nsdu_Idx = loop_idx6;
                }
                else
                {
                    /* Nothing to do-5 */
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00064.Data,1 */
                    /* If DT frame is received when the J1939Tp module is not in wait data state.*/
                }
            }
        }
    }
    if (tRxPduOk4 == TRUE )
    {
        nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[Pg_Idx]).J1939TpRxNSdu[Nsdu_Idx]).J1939TpRxNSduCtrl;

        /* check the length of the message received is correct */
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
        if(TRUE == J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx].J1939TpRxCanFDSupport)
        {
            /* !LINKSTO EB_Ref.SAE.FD.TP_DT.DataField.Rx,1 */
            ExpectedLength = (PduLengthType)(nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) + (PduLengthType) J1939TP_DT_CANFD_OVERHEAD_LENGTH;

            if (ExpectedLength > J1939TP_MAX_CANFD_FRAME_LENGTH)
            {
                ExpectedLength = J1939TP_MAX_CANFD_FRAME_LENGTH;
            }
        }
        else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
        {
            ExpectedLength = (PduLengthType)(nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) + (PduLengthType) J1939TP_DT_OVERHEAD_LENGTH;

            if (ExpectedLength > J1939TP_MAX_CAN_FRAME_LENGTH)
            {
                ExpectedLength = J1939TP_MAX_CAN_FRAME_LENGTH;
            }
        }

        if(ReceivedLength >= ExpectedLength)
        {
            /* Copy the SduLength which is required in the main function for BAM and CMDT reception */
            nsdu_ctrl_ptr->SduLength = ExpectedLength;

            if(MetaDataLen != 0U)
            {
                /* Copy the MetaDataInfo from received DtNPdu to nsdu_ctrl_ptr */
                EcuC_Ret=EcuC_GetMetaDataCanId(J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[Chan_Idx].J1939TpRxDtNPduRxConfIdEcuCPbcfg,NULL_PTR,&metaDataCanId);

                if(EcuC_Ret != E_OK)
                {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
                }

            }
            for(metaDataPositionIdx=0u; metaDataPositionIdx<MetaDataLen; metaDataPositionIdx++)
            {
                metaDataShiftVal= metaDataPositionIdx*8u;
                currMetaDataVal= metaDataCanId>>metaDataShiftVal;
                nsdu_ctrl_ptr->J1939TpMetaDataInfo[metaDataPositionIdx] = (uint8)(currMetaDataVal);
            }

            if(nsdu_ctrl_ptr->state == J1939TP_BAM_RX_STATE_WAIT_DATA)
            {
                /* !LINKSTO J1939Tp.EB.Dsn.BAM.Rx.Received.DT,1 */
                /* Moved the copying of the Data Frame from J1939Tp_Mainunction to J1939Tp_Rx_Indication(ISR) to address
                the issue of dropping the Data frame when J1939Tp module receives the consecutive Data frames when
                configured J1939TpMainFunctionPeriod is greater than J1939TpTBAMMinTimeout*/
                J1939Tp_BAM_Reception_CopyRxData(PduInfoPtr, Chan_Idx, Pg_Idx, Nsdu_Idx);
            }
            else
            {
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.DT,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00123.T1,1 */
                /* Stop the Timer T1 as we have received the data frame. It will be restarted again in J1939Tp_CMDT_Reception
                 * function once PduR_J1939TpCopyRxData API finishes copying of this data frame */
                nsdu_ctrl_ptr->StartT1Time = FALSE;
                nsdu_ctrl_ptr->T1TimeCounter = 0U;
                nsdu_ctrl_ptr->T1TimeElapsed = FALSE;

                if(nsdu_ctrl_ptr->StartT2Time == TRUE)
                {
                    /* If T2 timer is ON that means we were waiting for the TP.DT frame after sending CTS.
                     * Now as we have received TP.DT frame, T2 timer needs to be stopped */
                    nsdu_ctrl_ptr->StartT2Time = FALSE;
                    nsdu_ctrl_ptr->T2TimeCounter = 0U;
                    nsdu_ctrl_ptr->T2TimeElapsed = FALSE;
                }
                /* Moved the copying of the Data Frame from J1939Tp_Mainunction to J1939Tp_Rx_Indication(ISR) to address
                   the issue of dropping the Data frame when J1939Tp module receives the consecutive Data frames with time
                   space interval less than J1939TpMainFunctionPeriod */
                J1939Tp_CMDT_Reception_CopyRxData(PduInfoPtr, Chan_Idx, Pg_Idx, Nsdu_Idx);
            }
        }
        else
        {
            /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength,1 */
            /* !LINKSTO J1939Tp.EB.RxIndication.InvalidSduLength.FD.DT,1 */
            /* Invalid length-Discard the message */
            /* DET Reporting needs to be done here with error Id J1939TP_E_INVALID_SDU_LENGTH */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID,
            J1939TP_E_INVALID_SDU_LENGTH);
#endif
        }
    }
    else
    {
        /* Nothing to do-6 */
    }

    DBG_J1939TP_RXINDICATION_DT_EXIT(Chan_Idx,PduInfoPtr,u8SA_val,u8DA_val);
}

/* ***************************************************************************
*  Name                 : J1939Tp_Tx_Store_MetaData
*  Description          : Storing metadata of Tx N-SDU
*                       :
*  Parameters           : Input: Chan_Idx Pg_Idx Nsdu_Idx u8SA_val u8DA_val
*                         Output: metaDataInfo
*  Return               : Std_ReturnType
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Tx_Store_MetaData(P2VAR(uint8, AUTOMATIC, J1939TP_APPL_DATA) metaDataInfo, uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx)
{
    /* Local variables */
    Std_ReturnType status_code = E_NOT_OK;
    Std_ReturnType ecuC_source_Ret = E_OK;
    Std_ReturnType ecuC_target_Ret = E_OK;
    Std_ReturnType ecuC_priority_Ret = E_OK;
    uint16 ecuCSAAddress=0xFFFF;
    uint16 ecuCDAAddress=0xFFFF;
    uint8 metaDataPriority=0xFF;

    /* Initialization of configuration pointer for selected NSdu structure */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]);
    P2CONST(J1939Tp_TxNSduTypePbcfg,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr_pbcfg = &(((J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[Chan_Idx]).J1939TpTxPgPbcfg[Pg_Idx]).J1939TpTxNSduPbcfg[Nsdu_Idx]);

    uint8 MetaDataLen = nsdu_cfg_ptr->txnsdumetadatalength;

    DBG_J1939TP_TX_STORE_METADATA_ENTRY(metaDataInfo ,Chan_Idx ,Pg_Idx, Nsdu_Idx);

    if(MetaDataLen == 1U)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00198.NSDU.Sa,1 */
        ecuC_source_Ret=EcuC_GetMetaDataSourceAddr(nsdu_cfg_ptr_pbcfg->J1939TpTxNSduIdEcuCPbcfg, NULL_PTR, &ecuCSAAddress);
        metaDataInfo[0U]=(uint8)ecuCSAAddress;
    }
    else if(MetaDataLen == 2U)
    {
         /* !LINKSTO EB_Ref.SWS_J1939Tp_00198.NSDU.SaDa,1 */
        ecuC_source_Ret=EcuC_GetMetaDataSourceAddr(nsdu_cfg_ptr_pbcfg->J1939TpTxNSduIdEcuCPbcfg, NULL_PTR, &ecuCSAAddress);
        metaDataInfo[0U] = (uint8)ecuCSAAddress;
        ecuC_target_Ret = EcuC_GetMetaDataTargetAddr(nsdu_cfg_ptr_pbcfg->J1939TpTxNSduIdEcuCPbcfg, NULL_PTR, &ecuCDAAddress);
        metaDataInfo[1U] = (uint8)ecuCDAAddress;
    }
    else if(MetaDataLen == 4U)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00198.NSDU.SaDaPrio,1 */
        ecuC_source_Ret = EcuC_GetMetaDataSourceAddr(nsdu_cfg_ptr_pbcfg->J1939TpTxNSduIdEcuCPbcfg, NULL_PTR, &ecuCSAAddress);
        metaDataInfo[0U] = (uint8)ecuCSAAddress;
        ecuC_target_Ret = EcuC_GetMetaDataTargetAddr(nsdu_cfg_ptr_pbcfg->J1939TpTxNSduIdEcuCPbcfg, NULL_PTR, &ecuCDAAddress);
        metaDataInfo[1U] = (uint8)ecuCDAAddress;
        ecuC_priority_Ret = EcuC_GetMetaDataPriority(nsdu_cfg_ptr_pbcfg->J1939TpTxNSduIdEcuCPbcfg, NULL_PTR, &metaDataPriority);
        metaDataInfo[3U] = metaDataPriority;
    }
    else
    {
        /* do nothing */
    }

    if((ecuC_source_Ret == E_OK) && (ecuC_target_Ret == E_OK) && (ecuC_priority_Ret == E_OK))
    {
        status_code=E_OK;
    }
    else
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00188.Transmit,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00115.E_INVALID_PDU_SDU_ID,1 */
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
    }

    DBG_J1939TP_TX_STORE_METADATA_EXIT(metaDataInfo ,Chan_Idx ,Pg_Idx, Nsdu_Idx);

    return status_code;
}

/* ***************************************************************************
*  Name                 : J1939Tp_Transmit_Internal
*  Description          : Handling of Tx TP.DT frame
*                       :
*  Parameters           : Input: Chan_Idx Pg_Idx Nsdu_Idx u8SA_val u8DA_val
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Transmit_Internal(uint16 Chan_Idx, uint16 Pg_Idx, uint16 Nsdu_Idx,
uint8 u8SA_val, uint8 u8DA_val, uint8 MetaDataLen, uint8 metaDataInfo[])
{
    /* Initialization of local variables*/
    uint16 loop_idx1;
    uint16 loop_idx2;
    uint16 loop_idx3;
    uint8 same_counter = 0U;
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
    uint8 same_SA_DA_counter = 0U;
#endif /*J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN*/
#if ((J1939TP_TX_CANFD_SUPPORT == STD_ON) || (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_OFF))
    boolean tTxNSduSaDaOk = TRUE;
#endif
    Std_ReturnType status_code = E_NOT_OK;
    boolean bMultipleFrameVar = FALSE;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC, J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr_1 = NULL_PTR;
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxPg[Pg_Idx].J1939TpTxNSdu[Nsdu_Idx].J1939TpTxNSduCtrl;

    DBG_J1939TP_TRANSMIT_INTERNAL_ENTRY(Chan_Idx, Pg_Idx, Nsdu_Idx, u8SA_val, u8DA_val, MetaDataLen ,metaDataInfo);

    /* Check if the message is Multiple Frame (CMDT/BAM) or single direct message */
    /* The full message length is checked, in case of CanFD transmission, the Assurance data length is checked as well */
    /* !LINKSTO J1939Tp.EB.FD.SduLength.Tx,1 */
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    if(((FALSE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)&&
       ((nsdu_ctrl_ptr->msglength <= 8U) && (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxPgDynLength == TRUE)))
    || ((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) &&
       ((((nsdu_ctrl_ptr->msglength) + (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxPg[Pg_Idx].J1939TpTxNSdu[Nsdu_Idx].AssuranceDataLength)) <= 60U) && (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxPgDynLength == TRUE))))
#else
    if((nsdu_ctrl_ptr->msglength <= 8U) && (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxPgDynLength == TRUE))
#endif
    {
        bMultipleFrameVar = FALSE;
    }
    else
    {
        bMultipleFrameVar = TRUE;
    }

#if (J1939TP_TX_PARALLEL_CHANNEL_HANDLING == STD_OFF)
    for (loop_idx1=0U; (loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels)); loop_idx1++)
#else
    /* !LINKSTO J1939Tp.EB.J1939TpTxConcurent,1 */
    /* check only if there is same SA & DA transmission on-going for the selected channel, not in all channels */
    loop_idx1 = Chan_Idx;
#endif
    {
        TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]);
        for (loop_idx2=0U; (loop_idx2<(TempPtrTxChannel->J1939TpNumberOfTxPg)); loop_idx2++)
        {
            for (loop_idx3=0U; (loop_idx3<(TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpNumberOfTxNSdu); loop_idx3++)
            {
                /*Optimize access to structure element*/
                nsdu_ctrl_ptr_1 = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].J1939TpTxNSduCtrl;
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00120,1 */
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00231,1 */
                /* check if there another transmission for same SA & Da and CMDT/BAM multiple frames on going for this SDU*/
                if ((nsdu_ctrl_ptr_1->state != J1939TP_TX_IDLE) && (nsdu_ctrl_ptr_1->sa ==  u8SA_val) && (nsdu_ctrl_ptr_1->da ==  u8DA_val) && (nsdu_ctrl_ptr_1->IsMultipleFrameType == TRUE) && (bMultipleFrameVar == TRUE))
                {
                    /* count the same SA & DA transmission on Going*/
                    same_counter++;
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
                    if(FALSE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)
                   {    /*increment counter to mark that there is an attempted connetion for an nsdu with same SA DA that is not CANFD*/
                        same_SA_DA_counter++;
                   }
                    else
                   {
                       /*do nothing*/
                   }
#endif /*J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN*/
                }
                else
                {
                    /* nothing , continue the loop to check other SDUs*/
                }
            }
        }
    }
    if(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport == FALSE) && (same_counter > 0U))
    {
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_OFF)
        /*  reject request and return status as E_NOT_OK */
        tTxNSduSaDaOk =FALSE ;
        status_code = E_NOT_OK;
#endif
    }
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
    else if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (u8DA_val == J1939TP_GLOBAL_ADDRESS))
    {
        /* !LINKSTO EB_Ref.SAE.FD.UniqueSession.Tx,1 */
        if(same_counter < J1939TP_CANFD_BAM_MAX_CONCURRENT_SESSIONS)
        {
            /* !LINKSTO EB_Ref.SAE.FD.BamTransfer.ConcurrentSessions.Tx,1 */
            nsdu_ctrl_ptr->session_num = J1939Tp_Set_Session_Number(J1939TP_CANFD_BAM_MAX_CONCURRENT_SESSIONS, u8SA_val, u8DA_val );
        }
        else
        {
            /*  reject request and return status as E_NOT_OK */
            tTxNSduSaDaOk = FALSE ;
            status_code = E_NOT_OK;
        }
    }
    else if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport) && (u8DA_val != J1939TP_GLOBAL_ADDRESS))
    {
        if(same_counter < J1939TP_CANFD_CMDT_MAX_CONCURRENT_SESSIONS)
        {
            /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.ConcurrentSessions.Tx,1 */
            nsdu_ctrl_ptr->session_num = J1939Tp_Set_Session_Number(J1939TP_CANFD_CMDT_MAX_CONCURRENT_SESSIONS, u8SA_val, u8DA_val );
        }
        else
        {
            /*  reject request and return status as E_NOT_OK */
            tTxNSduSaDaOk = FALSE ;
            status_code = E_NOT_OK;
        }
    }
#endif
    else
    {
        /* Do nothing */
    }
#if ((J1939TP_TX_CANFD_SUPPORT == STD_ON) || (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_OFF))
    if(tTxNSduSaDaOk == TRUE)
#endif
    {
        /* first SA & DA transmission  */
        /* Everything 'OK ' to transmit the data. */
        status_code = E_OK;
        if(MetaDataLen != (uint8) 0U)
        {
            /* For Issue 268265: Store the MetaData Information in nsdu_ctrl_ptr*/
            for(loop_idx1 = 0U; loop_idx1 < MetaDataLen; loop_idx1++)
            {
                nsdu_ctrl_ptr->J1939TpMetaDataInfo[loop_idx1] = metaDataInfo[loop_idx1];
            }
        }
        else
        {
            /* No metadata for this NSdu, Do nothing */
        }

        nsdu_ctrl_ptr->sa = u8SA_val;
        nsdu_ctrl_ptr->da = u8DA_val;
        nsdu_ctrl_ptr->IsMultipleFrameType= bMultipleFrameVar;

        if(FALSE == bMultipleFrameVar)
        {
            /* !LINKSTO J1939Tp.EB.Dsn.DirectPg.Tx.REQ,1 */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_DIRECTPG_TX_STATE_REQ);
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00039.NOTransProtocol,1 */
            /* DA is present in 2nd byte of MetaDataInfo sent by upper layer */
            if(J1939TP_GLOBAL_ADDRESS == u8DA_val)
            {
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
                if(same_SA_DA_counter > 0U)
                {
                    /*set pending state for this Nsdu , as a connection with the same SA/DA is already ongoing*/
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_REQ_PENDING);
                    J1939TpSetPendingRequestAvaialblity(Chan_Idx,PENDING_REQUEST_AVAILABLE);
                    J1939TpPendingRequestCount[Chan_Idx]++ ;
                }
                else
#endif /*J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN*/
                {
                    /*set state for this nsdu*/
                    /* !LINKSTO J1939Tp.EB.Dsn.BAM.Tx.REQ,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_BAM_TX_STATE_REQ);
                }
            }
            else
            {
#if (J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN == STD_ON)
                if(same_SA_DA_counter > 0U)
                {
                    /*set pending state for this Nsdu , as a connection with the same SA/DA is already ongoing*/
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_RTS_SEND_PENDING);
                    J1939TpSetPendingRequestAvaialblity(Chan_Idx,PENDING_REQUEST_AVAILABLE);
                    J1939TpPendingRequestCount[Chan_Idx]++ ;
                }
                else
#endif /*J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN*/
                {
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.RTS,1 */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_RTS_SEND);
                }
            }
        }
    }

    DBG_J1939TP_TRANSMIT_INTERNAL_EXIT(Chan_Idx, Pg_Idx, Nsdu_Idx, u8SA_val, u8DA_val, MetaDataLen ,metaDataInfo);

    return status_code;
}


/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication_Validate_RxPduId
*  Description          : Validate the RxPduId and then set the control structures
*  Parameters           : Input: SduInfo
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
static FUNC(void, J1939TP_CODE) J1939Tp_RxIndication_Validate_RxPduId(PduIdType RxPduId,P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    uint16 loop_idx1;
    uint16 loop_idx2;
    Std_ReturnType EcuC_Ret = E_OK;
    boolean tRxPduOk1 = FALSE;
    boolean tRxPduOk2 = FALSE;

    SduInfo->PduIdDirectPg=FALSE;
    SduInfo->PduId_CM_BAM=FALSE;

    DBG_J1939TP_RXINDICATION_VALIDATE_RXPDUID_ENTRY(RxPduId,SduInfo);

    for (loop_idx1=0U;(loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfRxChannels))&& (tRxPduOk1 != TRUE);loop_idx1++)
    {
        if (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCmNPduId == RxPduId) || ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxDtNPdu == RxPduId))
        {
            /* The channel is found. Initialize the channel */
            tRxPduOk1 = TRUE;
            SduInfo->ch_idx = loop_idx1;
        }
        else
        {
            /* Handling of DirectPg Frame */
            for (loop_idx2=0U;(loop_idx2<((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpNumberOfRxPg))&& (tRxPduOk2 != TRUE);loop_idx2++)
            {
                if (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxDirectNPduId == RxPduId)
                {
                    /* The channel is found. Initialize the channel */
                    tRxPduOk2 = TRUE;
                    tRxPduOk1 = TRUE;
                    SduInfo->ch_idx = loop_idx1;
                    SduInfo->pg_idx = loop_idx2;
                    /* Get the MetaData information for the DirectNPdu */
                    SduInfo->MetaDataLen = ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxPg[loop_idx2]).J1939TpRxDirectNPduMetaDataLen;
                    if(SduInfo->MetaDataLen >0U)
                    {
                        EcuC_Ret = EcuC_GetMetaDataCanId(((J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpRxPgPbcfg[loop_idx2]).J1939TpTxDirectNPduRxConfIdEcuCPbcfg,NULL_PTR,&SduInfo->metaDatacanId);
                    }
                    if(EcuC_Ret != E_OK)
                    {
                        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)

                        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);

                        #endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
                    }

                }
                else
                {
                    /* do nothing*/
                }
            }

        }
    }

    if ((tRxPduOk1 == TRUE) && (tRxPduOk2 == TRUE))
    {
        SduInfo->PduIdDirectPg=TRUE;

    }
    else
    {
        if (tRxPduOk1 == TRUE )
        {
            SduInfo->PduId_CM_BAM=TRUE;
        }
    }

    DBG_J1939TP_RXINDICATION_VALIDATE_RXPDUID_EXIT(RxPduId,SduInfo);

}
/* !LINKSTO EB_Ref.SWS_J1939Tp_00157.RxIndication,1 */
/* ***************************************************************************
*  Name                 : J1939Tp_RxIndication
*  Description          : Indication of a received I-PDU from a lower layer
*                       : communication interface module.
*  Parameters           : Input: PduIdType RxPduId
*                       : Input: PduInfoType * PduInfoPtr
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_RxIndication(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{

    uint16 loop_idx7;
    uint16 Chan_Idx = 0U;
    uint16 Pg_Idx = 0U;
    uint32 metaDataCanId=0x00000000;
    boolean tTxPduOk1 = FALSE;


    boolean IDDetCheckRx = FALSE;
    boolean IDDetCheckTx = FALSE;

    J1939Tp_SduInfoType SduInfo;

    DBG_J1939TP_RXINDICATION_ENTRY(RxPduId,PduInfoPtr);

    if (J1939Tp_Int_State == J1939TP_OFF)
    {

        /* !LINKSTO J1939Tp.EB.DET.RXINDICATION,1 */
        #if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_UNINIT);
        #endif
    }
    else if (PduInfoPtr == NULL_PTR)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00115.E_PARAM_POINTER,1 */
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_PARAM_POINTER);
#endif
    }
    else
    {
        /* We have to checked the null pointer for channel as multiplicity is 0..* otherwise reset may happen for null pointer assignment */
        if (J1939Tp_Cfg_Ptr->J1939TpRxChannel !=NULL_PTR)
        {
            /* Validate the RxPduId and then set the control structures*/
            J1939Tp_RxIndication_Validate_RxPduId(RxPduId,&SduInfo);
            metaDataCanId=SduInfo.metaDatacanId;
            Chan_Idx=SduInfo.ch_idx;
            Pg_Idx=SduInfo.pg_idx;

            if (SduInfo.PduIdDirectPg == TRUE)
            {
                /* DirectPg Handling*/
                J1939Tp_RxIndication_DirectPg(Chan_Idx,Pg_Idx,PduInfoPtr,metaDataCanId);
            }
            else
            {
                if (SduInfo.PduId_CM_BAM== TRUE)
                {
                    /* Handling of TP.CM frame or TP.DT */
                    J1939Tp_RxIndication_CM_DT(RxPduId,Chan_Idx,PduInfoPtr);
                }
                else
                {
                    /* Raise the flag to report DET as RxPduId might be invalid */
                    IDDetCheckRx = TRUE;
                }
            }
        }
        else
        {
            /* There are no RxChannels configured */
            /* Raise the flag to report DET as RxPduId might be invalid */
            IDDetCheckRx = TRUE;
        }

        if (J1939Tp_Cfg_Ptr->J1939TpTxChannel !=NULL_PTR)
        {
            for (loop_idx7=0U;(loop_idx7<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels)) && (tTxPduOk1 != TRUE);loop_idx7++)
            {
                if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx7]).J1939TpRxFcNPduIdCTS == RxPduId)
                {
                    /* Found the channel */
                    tTxPduOk1 = TRUE;
                    Chan_Idx = loop_idx7;
                }
                else
                {
                    /* RxPduId is not configured for CTS or ENDOFACK or Abort. Raise the development error if it is supported */
                }
            }
            if (tTxPduOk1 == TRUE)
            {
                /* Handling of CTS frame Reception for Tx Channel */
                J1939Tp_RxIndication_TxFcN_CM(Chan_Idx, PduInfoPtr);

            }
            else
            {
                /* Raise the flag to report DET as RxPduId might be invalid */
                IDDetCheckTx = TRUE;
            }
        }
        else
        {
            /* There are no TxChannels configured */
            /* Raise the flag to report DET as RxPduId might be invalid */
            IDDetCheckTx = TRUE;
        }

        if((IDDetCheckRx == TRUE) && (IDDetCheckTx == TRUE))
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00188.RxIndication,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_RXINDICATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif
        }
    }

    DBG_J1939TP_RXINDICATION_EXIT(RxPduId,PduInfoPtr);
}

/* !LINKSTO J1939Tp.SWS_J1939Tp_00112,1 */
/* !LINKSTO EB_Ref.SWS_J1939Tp_00157.TxConfirmation,1 */
/* ***************************************************************************
*  Name                 : J1939Tp_TxConfirmation
*  Description          : The lower layer communication interface module
*                       : confirms the transmission of an I-PDU.
*  Parameters           : Input: PduIdType TxPduId
*                                ID of the PDU that has been transmitted.
*                       : Input: Std_ReturnType result
*                                E_OK:The PDU was transmitted.
*                                E_NOT_OK:Transmission of the PDU failed.
*  Return               : none
*  Critical/explanation : [No]
******************************************************************************/
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_ON)
FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
#else
FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation(PduIdType TxPduId)
#endif
{
    /* Initialization of local variables*/
    uint16 loop_idx3;
    uint16 loop_idx6;
    uint16 loop_idx7;
    uint16 loop_idx8;

    uint16 Chan_Idx = 0U;
    uint16 Pg_Idx = 0U;

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    Std_ReturnType result = E_OK;
#endif

    boolean tRxNPduOk1  = FALSE;
    boolean tRxNPduOk2  = FALSE;
    J1939Tp_SduInfoType SduInfo;
    SduInfo.PduIdDirectPg=FALSE;
    SduInfo.PduId_CM_BAM=FALSE;
    SduInfo.ch_idx=0U;
    SduInfo.pg_idx=0U;

    DBG_J1939TP_TXCONFIRMATION_ENTRY(TxPduId,result);

    /* Operation body start */
    if(J1939Tp_Int_State == J1939TP_OFF)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Tp.EB.DET.TXCONFIRMATION,1 */
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TXCONFIRMATION_SERVICEID, J1939TP_E_UNINIT);
#endif
    }
    else
    {
        /* Validate the TxPduId and then set the control structures */
        J1939Tp_TxConfirmation_Validate_TxPduId(TxPduId,&SduInfo);
        Chan_Idx=SduInfo.ch_idx;
        Pg_Idx=SduInfo.pg_idx;

        if (SduInfo.PduIdDirectPg == TRUE)
        {
            /* DirectPg Handling*/
            for (loop_idx3=0U;loop_idx3<(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpNumberOfTxNSdu);loop_idx3++)
            {
                if ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl->state == J1939TP_DIRECTPG_TX_STATE_WAIT_CONFIRMATION)
                {
                    /* Set the Tx Confirmation flag */
                    (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl->txconfirmation = TRUE;
                    /* Stores the Tx Confirmation result flag */
                    (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl->txconfirmationResult = result;
                }
                else
                {
                    /* Nothing to do */
                }
            }
        }
        else
        {
            if (SduInfo.PduId_CM_BAM== TRUE)
            {
                if(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxCmNPduTxRTS == TxPduId)
                {
                     /* Handling of TP.CM/BAM frame confirmation */
                     J1939Tp_TxConfirmation_CM(Chan_Idx, result);
                }
                else
                {
                      /* Handling RTS or DT frame confirmation */
                     J1939Tp_TxConfirmation_DT(Chan_Idx, result);
                }
            }

            else
            {
                for (loop_idx6=0U;(loop_idx6<(J1939Tp_Cfg_Ptr->J1939TpNumberOfRxChannels))&& (tRxNPduOk1 != TRUE);loop_idx6++)
                {
                    if ((J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx6]).J1939TpTxCTSCanIfConf == TxPduId)
                    {
                        /* The PduId is found in the channel */
                        tRxNPduOk1 = TRUE;
                        Chan_Idx = loop_idx6;

                        /* Clear TxCTSCanIf Lock Flag to allow concurrent transmissions on the same channel */
                        (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx6]).ChannelStatus->J1939TpTxFcNPduAvailable = TRUE;

                        /* If the confirmation received is for channel abort frame, reset the flag*/
                        (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx6]).J1939TpRxChannelAbort->txconfirmation = TRUE;
                    }
                    else
                    {
                        /* TxPduId is not configured for CTS.  Raise the development error if it is supported */
                    }
                }
                if (tRxNPduOk1 == TRUE)
                {
                    /* CTS frame handling*/
                    for (loop_idx7=0U;(loop_idx7<((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpNumberOfRxPg))&& (tRxNPduOk2 != TRUE);loop_idx7++)
                    {
                        for (loop_idx8=0U;(loop_idx8<(((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[loop_idx7]).J1939TpNumberOfRxNSdu))&& (tRxNPduOk2 != TRUE);loop_idx8++)
                        {
                            J1939Tp_NSduCtrlType * TempPtr = (((J1939Tp_Cfg_Ptr->J1939TpRxChannel[Chan_Idx]).J1939TpRxPg[loop_idx7]).J1939TpRxNSdu[loop_idx8]).J1939TpRxNSduCtrl;
                            switch (TempPtr->state)
                            {
#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
                                case J1939TP_RX_STATE_CMDT_WAIT_CONFIRMATION_EOMS_RQST:
                                {
                                    /* Break the loop */
                                    tRxNPduOk2 = TRUE;
                                    /* Update the Tx confirmation Result flag */
                                    TempPtr->txconfirmationResult = result;
                                    /* Deviation TASKING-1 */
                                    if(E_OK == result)
                                    {
                                      /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.DT.Start,1 */
                                      /* Got Confirmation, change the state */
                                      J1939Tp_NSDU_ChangeState(TempPtr, J1939TP_RX_STATE_CMDT_WAIT_EOMS);

                                      /* Reset the flags */
                                      TempPtr->txconfirmation = FALSE;
                                    }
                                    else
                                    {
                                      /* Reset the flags */
                                      TempPtr->txconfirmation = TRUE;
                                    }
                                    break;
                                }
#endif
                                case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS:
                                {
                                    /* Break the loop */
                                    tRxNPduOk2 = TRUE;
                                    /* Update the Tx confirmation Result flag */
                                    TempPtr->txconfirmationResult = result;
                                    /* Deviation TASKING-1 */
                                    if(E_OK == result)
                                    {
                                      /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Rx.DT.Start,1 */
                                      /* Got Confirmation, change the state */
                                      J1939Tp_NSDU_ChangeState(TempPtr, J1939TP_CMDT_RX_STATE_WAIT_DATA);

                                      /* Reset the flags */
                                      TempPtr->txconfirmation = FALSE;
                                    }
                                    else
                                    {
                                      /* Reset the flags */
                                      TempPtr->txconfirmation = TRUE;
                                    }
                                    break;
                                }

                                case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_CTS0:
                                case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_DATA_COMPLETE:
                                case J1939TP_CMDT_RX_STATE_WAIT_CONFIRMATION_ABORT:
                                {
                                    /* Break the loop */
                                    tRxNPduOk2 = TRUE;
                                    /* Reset the flags */
                                    TempPtr->txconfirmation = TRUE;
                                    /* Update the Tx confirmation Result flag */
                                    TempPtr->txconfirmationResult = result;
                                    break;
                                }
                                default:
                                {
                                    /* Nothing to do */
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Tp_00188.TxConfirmation,1 */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TXCONFIRMATION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif
                }
            }
        }
    }

    DBG_J1939TP_TXCONFIRMATION_EXIT(TxPduId,result);
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_DT(uint16 Chan_Idx, Std_ReturnType result)
{
    /* Initialization of local variables*/
    uint16 Pg_Idx;
    uint16 Nsdu_Idx;
    boolean tTxNPduOk3 = FALSE;

    DBG_J1939TP_TXCONFIRMATION_DT_ENTRY(Chan_Idx,result);

    for (Pg_Idx=0U;(Pg_Idx<((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpNumberOfTxPg))&& (tTxNPduOk3 != TRUE);Pg_Idx++)
    {
        for (Nsdu_Idx=0U;(Nsdu_Idx<(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpNumberOfTxNSdu))&& (tTxNPduOk3 != TRUE);Nsdu_Idx++)
        {
            J1939Tp_NSduCtrlType * TempPtr = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl;
            switch (TempPtr->state)
            {
                case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_DT:
                {
                    J1939Tp_NSDU_ChangeState(TempPtr,J1939TP_BAM_TX_STATE_CONFIRMATION_DT_RECEIVED);
                    tTxNPduOk3 = TRUE;                    /* Break the loop */
                    TempPtr->txconfirmation = TRUE;       /* Set the Tx Confirmation flag */
                    TempPtr->txconfirmationResult = result;
                    break;
                }
                case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA:
                {
                    tTxNPduOk3 = TRUE;  /* Break the loop */
                    J1939Tp_TxConfirmation_CMDT_Data(TempPtr, Chan_Idx, result);
                    break;
                }
                default:
                {
                    break;     /* Nothing to do */
                }
            }
        }
    }
      DBG_J1939TP_TXCONFIRMATION_DT_EXIT(Chan_Idx,result);
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_CM(uint16 Chan_Idx, Std_ReturnType result)
{
    /* Initialization of local variables*/
    uint16 Pg_Idx;
    uint16 Nsdu_Idx;
    boolean tTxNPduOk3 = FALSE;

    DBG_J1939TP_TXCONFIRMATION_CM_ENTRY(Chan_Idx,result);

    for (Pg_Idx=0U;(Pg_Idx<((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpNumberOfTxPg))&& (tTxNPduOk3 != TRUE);Pg_Idx++)
    {
        for (Nsdu_Idx=0U;(Nsdu_Idx<(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpNumberOfTxNSdu))&& (tTxNPduOk3 != TRUE);Nsdu_Idx++)
        {
            J1939Tp_NSduCtrlType * TempPtr = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxPg[Pg_Idx]).J1939TpTxNSdu[Nsdu_Idx]).J1939TpTxNSduCtrl;
            switch (TempPtr->state)
            {
                case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_CM:
                {
                   J1939Tp_NSDU_ChangeState(TempPtr,J1939TP_BAM_TX_STATE_CONFIRMATION_CM_RECEIVED); /*Received confirmation, change to intermediary state to not block other confirmations*/
                   tTxNPduOk3 = TRUE;                /* Break the loop */
                   TempPtr->txconfirmation = TRUE;   /* Set the Tx Confirmation flag */
                   TempPtr->txconfirmationResult = result;
                   break;
                }
                case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_ABORT:
                {
                   tTxNPduOk3 = TRUE;                /* Break the loop */
                   TempPtr->txconfirmation = TRUE;   /* Set the Tx Confirmation flag */
                   TempPtr->txconfirmationResult = result;
                   break;
                }
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                case J1939TP_BAM_TX_STATE_WAIT_CONFIRMATION_EOMS:
                {
                   J1939Tp_NSDU_ChangeState(TempPtr,J1939TP_BAM_TX_STATE_CONFIRMATION_EOMS_RECEIVED);
                   tTxNPduOk3 = TRUE;                /* Break the loop */
                   TempPtr->txconfirmation = TRUE;   /* Set the Tx Confirmation flag */
                   TempPtr->txconfirmationResult = result;
                   break;
                }
#endif
                case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_RTS:
                {
                   tTxNPduOk3 = TRUE;                       /* Break the loop */
                   TempPtr->txconfirmationResult = result;  /* Update the Tx confirmation Result flag */
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_ON)
                   if(E_OK != result)
                   {
                       TempPtr->txconfirmation = TRUE;      /* Set the confirmation flag */
                   }
                   else
#endif
                   {
                       /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.CTS,1 */
                       J1939Tp_NSDU_ChangeState(TempPtr, J1939TP_CMDT_STATE_CTS);   /* change the state */
                       TempPtr->txconfirmation = FALSE;                             /* Reset the confirmation flag */
                   }
                    break;
                }
                case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT:
                {
                    tTxNPduOk3 = TRUE;                  /* Break the loop */
                    TempPtr->txconfirmation = TRUE;     /* Set the Tx Confirmation flag */
                    TempPtr->txconfirmationResult = result;
                    break;
                }
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
                case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_EOMS:
                {
                    /* Break the loop */
                    tTxNPduOk3 = TRUE;
                    J1939Tp_TxConfirmation_CMDT_EOMS(TempPtr, Chan_Idx, result);
                    break;
                }
#endif

                default:
                {
                    /* Nothing to do */
                    break;
                }
            }
        }
    }
    DBG_J1939TP_TXCONFIRMATION_CM_EXIT(Chan_Idx,result);
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_CMDT_Data(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 Chan_Idx, Std_ReturnType result)
{
    /* Update the Tx confirmation Result flag */
    nsdu_ctrl_ptr->txconfirmationResult = result;

#if (J1939TP_TX_CANFD_SUPPORT == STD_OFF)
    TS_PARAM_UNUSED(Chan_Idx);
#endif

    DBG_J1939TP_TXCONFIRMATION_CMDT_DATA_ENTRY(nsdu_ctrl_ptr, Chan_Idx, result);

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_ON)
    if(E_OK != result)
    {
        /* Set the confirmation flag */
        nsdu_ctrl_ptr->txconfirmation = TRUE;
    }
    else
#endif
    {
        /* Reset the confirmation flag */
        nsdu_ctrl_ptr->txconfirmation = FALSE;

        if (nsdu_ctrl_ptr->msglength != nsdu_ctrl_ptr->data_cnt)
        {
            if (nsdu_ctrl_ptr->cnt_packets == nsdu_ctrl_ptr->cts_packets)
            {
                nsdu_ctrl_ptr->cnt_packets = 0U;
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.CTS.NEW,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_STATE_CTS);

                /* Start T3 timer */
                nsdu_ctrl_ptr->StartT3Time = TRUE;
                nsdu_ctrl_ptr->T3TimeElapsed = FALSE;
                nsdu_ctrl_ptr->T3TimeCounter = 0U;
            }
            else
            {
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.DT.All,1 */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION);
            }
        }
#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
        /* Deviation TASKING-1 */
        else if((TRUE == (J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx]).J1939TpTxCanFDSupport)&&(nsdu_ctrl_ptr->msglength == nsdu_ctrl_ptr->data_cnt))
        {
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_EOMS_TRANSMISSION);
        }
#endif
        else
        {
            /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.EOMACK,1 */
            /* change the state */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK);

            /* Start T3 timer */
            nsdu_ctrl_ptr->StartT3Time = TRUE;
            nsdu_ctrl_ptr->T3TimeElapsed = FALSE;
            nsdu_ctrl_ptr->T3TimeCounter = 0U;
        }
    }

    DBG_J1939TP_TXCONFIRMATION_CMDT_DATA_EXIT(nsdu_ctrl_ptr, Chan_Idx, result);
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_Validate_TxPduId(PduIdType TxPduId,P2VAR(J1939Tp_SduInfoType, AUTOMATIC, J1939TP_APPL_DATA) SduInfo)
{
    uint16 loop_idx1;
    uint16 loop_idx2;
    boolean tTxNPduOk1 = FALSE;
    boolean tTxNPduOk2 = FALSE;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC,J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;

    DBG_J1939TP_TXCONFIRMATION_VALIDATE_TXPDUID_ENTRY(TxPduId,SduInfo);

    for (loop_idx1=0U; (loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels)) && (tTxNPduOk1 != TRUE); loop_idx1++)
    {
        TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]);
        if (TempPtrTxChannel->J1939TpTxCmNPduTxRTS == TxPduId)
        {
            /* The PduId is found in the channel */
            tTxNPduOk1 = TRUE;
            SduInfo->ch_idx = loop_idx1;
            TempPtrTxChannel->ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
        }
        else if (TempPtrTxChannel->J1939TpTxDtNPduTxConfId == TxPduId)
        {
            /* The PduId is found in the channel */
            tTxNPduOk1 = TRUE;
            SduInfo->ch_idx = loop_idx1;
            TempPtrTxChannel->ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
        }
        else
        {
            /* Handling of DirectPg Frame */
            for (loop_idx2=0U;(loop_idx2<((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpNumberOfTxPg))&& (tTxNPduOk2 != TRUE);loop_idx2++)
            {
                if ((TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpTxDirectNPduTxConfId == TxPduId)
                {
                    /* The PduId is found in the Pg */
                    tTxNPduOk1 = TRUE;
                    tTxNPduOk2 = TRUE;

                    SduInfo->ch_idx = loop_idx1;
                    SduInfo->pg_idx = loop_idx2;

                    /* Clear TxDirectNPduTxConfId Lock Flag to allow concurrent transmissions on the same channel */
                    ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDirectNPduAvailable[loop_idx2]) = TRUE;
                }
                else
                {
                    /* nothing to do */
                }
            }
        }
    }

    if ((tTxNPduOk1 == TRUE) && (tTxNPduOk2 == TRUE))
    {
        SduInfo->PduIdDirectPg=TRUE;

    }
    else
    {
        if (tTxNPduOk1)
        {
            SduInfo->PduId_CM_BAM=TRUE;
        }
    }

    DBG_J1939TP_TXCONFIRMATION_VALIDATE_TXPDUID_EXIT(TxPduId,SduInfo);

}
static FUNC(void, J1939TP_CODE) J1939Tp_NPduMetaData_Handle(uint8 NPduMetaData, uint8 NSduMetaData, P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) J1939TpTxPduInfoSrc, uint8 MetaDataInfo[], uint8 J1939TpPGN, uint16 J1939TpEcucId)
{
    uint8 metaDataPositionIdx;
    sint8 metaDataPositionIdx2;
    uint32 metaDataCanId=0x00000000;
    uint8 canIdArray[4]= {0};
    uint8 metaDataPositionShift;
    uint32 metaDataTemp;
    Std_ReturnType EcuC_Ret = E_OK;
    PduInfoType PduInfoTemp;

    DBG_J1939TP_NPDUMETADATA_HANDLE_ENTRY(NPduMetaData,NSduMetaData,J1939TpTxPduInfoSrc,MetaDataInfo,J1939TpPGN,J1939TpEcucId);

    /* !LINKSTO EB_Ref.SWS_J1939Tp_00198.NPDU.SaDaPrio,1 */
    /* Append the MetaData information in SduDataPtr after the payload */
    for(metaDataPositionIdx=0u ; metaDataPositionIdx < NSduMetaData ; metaDataPositionIdx++)
    {
        canIdArray[metaDataPositionIdx] = J1939TpTxPduInfoSrc->J1939TpMetaDataInfo[metaDataPositionIdx];
    }

    if(NPduMetaData > NSduMetaData)
    {
        for(metaDataPositionIdx=NSduMetaData ; metaDataPositionIdx < NPduMetaData ; metaDataPositionIdx++)
        {
            canIdArray[metaDataPositionIdx] = MetaDataInfo[metaDataPositionIdx];
        }
    }


    canIdArray[(PduLengthType)METADATA_PGN_INDEX_2]=J1939TpPGN;


    /* get related metaDataCanId. */
    for(metaDataPositionIdx2=3;metaDataPositionIdx2>=0;metaDataPositionIdx2--)
    {
        metaDataPositionShift=metaDataPositionIdx2*8;
        metaDataTemp =(uint32)canIdArray[metaDataPositionIdx2];
        metaDataCanId |= ((uint32)(metaDataTemp<<metaDataPositionShift));
    }

    EcuC_Ret=EcuC_SetMetaDataCanId(J1939TpEcucId,&PduInfoTemp,metaDataCanId);
    if(EcuC_Ret != E_OK)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
    }

    DBG_J1939TP_NPDUMETADATA_HANDLE_EXIT(NPduMetaData,NSduMetaData,J1939TpTxPduInfoSrc,MetaDataInfo,J1939TpPGN,J1939TpEcucId);
}

static FUNC(void, J1939TP_CODE) J1939Tp_FCNPduMetaData_Handle(uint8 FcNPduMetaData,uint8 CmNPduMetaData,P2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr,uint8 MetaDataInfo[],uint16 loop_idx1)
{
    uint8 metaDataPositionIdx;
    sint8 metaDataPositionIdx2;
    uint32 metaDataCanId=0x00000000;
    uint8 canIdArray[4]={0};
    uint8 metaDataPositionShift;
    uint32 metaDataTemp;
    Std_ReturnType EcuC_Ret = E_OK;
    PduInfoType PduInfoTemp;

    DBG_J1939TP_FCNPDUMETADATA_HANDLE_ENTRY(FcNPduMetaData,CmNPduMetaData,nsdu_ctrl_ptr,MetaDataInfo,loop_idx1);

    if(CmNPduMetaData == 4U)
    {
        /* Swap SA & DA of CMDT.RTS frame & put it here in CTS frame */
        canIdArray[0] = nsdu_ctrl_ptr->J1939TpMetaDataInfo[1];
        canIdArray[1] = nsdu_ctrl_ptr->J1939TpMetaDataInfo[0];

        /* Use priority byte as it is from CMDT.RTS frame because it is already shifted by CanIf while calling J1939Tp_RxIndication for CmNPdu */
        canIdArray[3] = nsdu_ctrl_ptr->J1939TpMetaDataInfo[3];
    }


    if(FcNPduMetaData > CmNPduMetaData)
    {
        for(metaDataPositionIdx=CmNPduMetaData ; metaDataPositionIdx < FcNPduMetaData ; metaDataPositionIdx++)
        {
            canIdArray[metaDataPositionIdx] = MetaDataInfo[metaDataPositionIdx];
        }
    }

    /* Npdu metadata length is either 0 or 4 */
    /* 0 case can't happen in this function as 0 check performed on caller side */

#if (J1939TP_RX_CANFD_SUPPORT == STD_ON)
    if(TRUE == (J1939Tp_Cfg_Ptr->J1939TpRxChannel[loop_idx1]).J1939TpRxCanFDSupport)
    {
        /* !LINKSTO J1939Tp.SAE.FD.TP_CM.Frame,1 */
        canIdArray[METADATA_PGN_INDEX_2] = J1939TP_CANFD_TP_CM_PGN;
    }
    else
#endif /* (J1939TP_RX_CANFD_SUPPORT == STD_ON) */
    {
        canIdArray[METADATA_PGN_INDEX_2] = J1939TP_TP_CM_PGN;
    }

    /* get related metaDataCanId */
    for(metaDataPositionIdx2=3;metaDataPositionIdx2>=0;metaDataPositionIdx2--)
    {
        metaDataPositionShift=metaDataPositionIdx2*8;
        metaDataTemp =(uint32)canIdArray[metaDataPositionIdx2];
        metaDataCanId |= ((uint32)(metaDataTemp<<metaDataPositionShift));
    }

    EcuC_Ret=EcuC_SetMetaDataCanId((J1939Tp_PbCfg_Ptr->J1939TpRxChannelPbcfg[loop_idx1]).J1939TpTxFcNPduRxConfIdEcuCPbcfg, &PduInfoTemp, metaDataCanId);

    if(EcuC_Ret != E_OK)
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
    }

    DBG_J1939TP_FCNPDUMETADATA_HANDLE_EXIT(FcNPduMetaData,CmNPduMetaData,nsdu_ctrl_ptr,MetaDataInfo,loop_idx1);
}


static FUNC(void, J1939TP_CODE) J1939Tp_SetEcuCMetaDataRx(uint8 MetaDataLen,uint8 metaDataInfo[],uint16 J1939TpEcucId)
{
    Std_ReturnType tSrcReturn = E_OK;
    Std_ReturnType tDestReturn = E_OK;
    Std_ReturnType tPrioReturn = E_OK;
    PduInfoType PduInfoTemp;

    DBG_J1939TP_SETECUCMETADATARX_ENTRY(MetaDataLen,metaDataInfo,J1939TpEcucId);

    tSrcReturn=EcuC_SetMetaDataSourceAddr(J1939TpEcucId,&PduInfoTemp,(uint16)metaDataInfo[0]);

    if(MetaDataLen== 2U)
    {
        tDestReturn=EcuC_SetMetaDataTargetAddr(J1939TpEcucId,&PduInfoTemp,(uint16)metaDataInfo[1]);
    }
    else if(MetaDataLen== 4U)
    {
        tDestReturn=EcuC_SetMetaDataTargetAddr(J1939TpEcucId,&PduInfoTemp,(uint16)metaDataInfo[1]);
        tPrioReturn=EcuC_SetMetaDataPriority(J1939TpEcucId,&PduInfoTemp,metaDataInfo[3]);
    }
    else
    {
     /* nothing to do */
    }

    if( ( (tPrioReturn !=E_OK) || (tSrcReturn!=E_OK) ) || (tDestReturn!=E_OK))
    {
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_MAINFUNCTION_SERVICEID, J1939TP_E_INVALID_PDU_SDU_ID);
#endif /* (J1939TP_DEV_ERROR_DETECT == STD_ON) */
    }

    DBG_J1939TP_SETECUCMETADATARX_EXIT(MetaDataLen,metaDataInfo,J1939TpEcucId);
}

#if (J1939TP_TX_CANFD_SUPPORT == STD_ON)
static FUNC(uint8, J1939TP_CODE) J1939Tp_FD_Transmit_Calculate_Frame_Size(uint8 data)
{
    uint8 frameSize = data;
    if(data > 48U)
    {
        frameSize = 64U;
    }
    else if(data > 32U)
    {
        frameSize = 48U;
    }
    else if(data > 24U)
    {
        frameSize = 32U;
    }
    else if(data > 20U)
    {
        frameSize = 24U;
    }
    else if(data > 16U)
    {
        frameSize = 20U;
    }
    else if(data > 12U)
    {
        frameSize = 16U;
    }
    else if(data > 8U)
    {
        frameSize = 12U;
    }
    else
    {
        /* Length is allowed for CanFD Transmission */
        /* Do nothing */
    }
    return frameSize;
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_FD_Transmit_EOMS(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    /* Initialization of pointer to selected Tx NSdu configuration structure */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);
    uint8 tData[64U];
    uint8 MetaDataInfo[4U];
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 CmNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCmNPduMetaData;
    uint8 AssuranceDataType = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].AssuranceDataType;
    uint8 AssuranceDataLength = J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1].J1939TpTxPg[loop_idx2].J1939TpTxNSdu[loop_idx3].AssuranceDataLength;
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2U);
    uint32 Segments_Num;
    PduInfoType J1939TpTxPduInfo = {NULL_PTR, 0U};
    BufReq_ReturnType BufReq_Return = BUFREQ_OK;
    MetaDataInfo[0U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2U] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3U] = PrioBit;
    /* Prepare the frame for EOMS transmission */
    tData[0U] = (uint8)(((nsdu_ctrl_ptr->session_num) << 4U) | (J1939TP_CANFD_TPCM_ENDOFMSGSTATUS));
    tData[1U] = (uint8)nsdu_ctrl_ptr->msglength;                           /* LSB byte of the message length */
    tData[2U] = (uint8)(nsdu_ctrl_ptr->msglength >> 8U);                   /* 2nd byte of the message length */
    tData[3U] = (uint8)(nsdu_ctrl_ptr->msglength >> 16U);                  /* MSB byte of the message length */
    Segments_Num = nsdu_ctrl_ptr->msglength / J1939TP_MAX_CANFD_DT_MSGLENGTH;
    if((nsdu_ctrl_ptr->msglength % J1939TP_MAX_CANFD_DT_MSGLENGTH) != 0U)
    {
        Segments_Num = Segments_Num + (uint8)1U;                          /* LSB of the number of segments */
    }
    tData[4U] = (uint8)Segments_Num;                                       /* LSB byte of Number of Segments */
    tData[5U] = (uint8)(Segments_Num >> 8U);                               /* 2nd byte of Number of Segments */
    tData[6U] = (uint8)(Segments_Num >> 16U);                              /* MSB byte of Number of Segments */
    tData[7U] = AssuranceDataLength;                                       /* Assurance Data Length */
    tData[8U] = AssuranceDataType;                                         /* Assurance Data Type */
    tData[9U] = (uint8)(nsdu_ctrl_ptr->pgn);                               /* LSB of pgn */
    tData[10U] = (uint8)(nsdu_ctrl_ptr->pgn >> 8U);                        /* 2nd byte of pgn */
    tData[11U] = (uint8)(nsdu_ctrl_ptr->pgn >> 16U);                       /* MSB of pgn */

    if(0U != AssuranceDataLength)
    {
        /*PduInfo which holds the transmit data and the length info*/
        PduInfoType tPduInfo = {NULL_PTR, 0U};
        PduLengthType availabledataPtr;
        P2VAR(RetryInfoType, AUTOMATIC, J1939TP_APPL_DATA) RetryInfoPtr = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxRetryInfo;
        tPduInfo.SduLength = (PduLengthType)AssuranceDataLength;
        tPduInfo.SduDataPtr = &tData[12U];
        if(RetryInfoPtr != NULL_PTR)
        {
            if(nsdu_ctrl_ptr->retry_cts_flag == TRUE)
            {
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00221,1 */
                /* If retry flag is on, change TpDataState to TP_DATARETRY and set new TxTpDataCnt to data_cnt */
                nsdu_ctrl_ptr->retry_cts_flag = FALSE;
                RetryInfoPtr->TpDataState = TP_DATARETRY;
                RetryInfoPtr->TxTpDataCnt = (PduLengthType)(nsdu_ctrl_ptr->data_cnt);
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00217.NextDT,1 */
                /* Last packet of the EOMS. So assign TpDataState to TP_CONFPENDING */
                RetryInfoPtr->TpDataState = TP_CONFPENDING;
            }
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.CMDT.Retry,1 */
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00220,1 */
            BufReq_Return = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, &tPduInfo, RetryInfoPtr, &availabledataPtr);
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.CMDT.NoRetry,1 */
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00218,1 */
            /*Retry mechanism is not enabled. So retry parameter is NULL_PTR */
            BufReq_Return = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, &tPduInfo, NULL_PTR, &availabledataPtr);
        }
    }

    switch(BufReq_Return)
    {
        case BUFREQ_OK:
        {
            uint8 MessageLength = AssuranceDataLength + J1939TP_CANFD_CONTROL_FRAME_LENGTH;
            uint8 i = 0U;
            J1939TpTxPduInfo.SduDataPtr = &tData[0U];
            J1939TpTxPduInfo.SduLength = J1939Tp_FD_Transmit_Calculate_Frame_Size(MessageLength);

            /* Message padding if needed */
            for(i = MessageLength; i < J1939TpTxPduInfo.SduLength; i++)
            {
                tData[i] = J1939TP_CANFD_PADDING;
            }

            if(CmNPduMetaData > 0U)
            {
                J1939Tp_NPduMetaData_Handle(CmNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_CANFD_TP_CM_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxCmNPduTxConfIdEcuCPbcfg);
            }
            /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
            (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = FALSE;
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_EOMS);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
            nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif
            if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxCmNPduTxRTSCanIf, &J1939TpTxPduInfo))
            {
                /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
                J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
                /* indicate upper layer regarding the error */
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
            }
            else
            {
            }
            break;
        }
        case BUFREQ_E_BUSY:
        case BUFREQ_E_OVFL:
        {
            if(nsdu_ctrl_ptr->StartTrTime != TRUE)
            {
                nsdu_ctrl_ptr->StartTrTime = TRUE;
                nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                nsdu_ctrl_ptr->TrTimeCounter = 0U;
                nsdu_ctrl_ptr->TrTimeout_SendAbort = TRUE;
            }
            break;
        }
        default:
        {
            /* BUFREQ_E_NOT_OK*/
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CopyTxData.CMDT,1 */
            /* Abort transmission and notify upper layer */
            J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
            /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
            nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
            break;
        }
    }
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_FD_Data_Transmition(P2VAR(PduInfoType,AUTOMATIC,J1939TP_APPL_DATA) tPduInfo,uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    uint8 tData[64];
    uint8 i,MetaDataInfo[4];
    uint8 DtNPduMetaData = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduMetaData;
    uint8 TxNSduMetaData = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).txnsdumetadatalength;
    uint8 PrioBit = (uint8)(J1939TP_DEFAULT_PRIORITY << 2U);
    PduInfoType J1939TpTxPduInfo = {NULL_PTR, 0U};
    uint8 MessageLength = 0U;
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.CMDT.DataAvailable,1 */
    /* BUFREQ_OK*/
    /* Prepared the DATA frame for CMDT transmission */
    J1939TP_SET_SESSION_NUMBER(nsdu_ctrl_ptr->session_num, tData[0U]);
    tData[1U] = (uint8)(nsdu_ctrl_ptr->sn);          /* Sequence number- 1st byte of the data frame */
    tData[2U] = (uint8)(nsdu_ctrl_ptr->sn >> 8U);    /* Sequence number- 1st byte of the data frame */
    tData[3U] = (uint8)(nsdu_ctrl_ptr->sn >> 16U);   /* Sequence number- 1st byte of the data frame */

    MetaDataInfo[0U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxSaPbcfg;
    MetaDataInfo[1U] = (J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDaPbcfg;
    MetaDataInfo[2U] = J1939TP_UNUSED_BYTE_PADDING;
    MetaDataInfo[3U] = PrioBit;

    nsdu_ctrl_ptr->sn++;
    /* Copy the data for DATA frame */
    for (i=0U; i < tPduInfo->SduLength; i++)
    {
        tData[i + J1939TP_DT_CANFD_OVERHEAD_LENGTH] = (tPduInfo->SduDataPtr[i]);
    }
    nsdu_ctrl_ptr->data_cnt = nsdu_ctrl_ptr->data_cnt + tPduInfo->SduLength;
    /* Tr Timer is ON means previously PduR_J1939TpCopyTxData had returned BUFREQ_E_BUSY/BUFREQ_E_OVFL.
    * Now as PduR_J1939TpCopyTxData has returned BUFREQ_OK, we can stop this Tr timer */
    if(nsdu_ctrl_ptr->StartTrTime == TRUE)
    {
        nsdu_ctrl_ptr->StartTrTime = FALSE;
        nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
        nsdu_ctrl_ptr->TrTimeCounter = 0U;
        nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
    }
    MessageLength = (uint8)tPduInfo->SduLength + (uint8)J1939TP_DT_CANFD_OVERHEAD_LENGTH;
    J1939TpTxPduInfo.SduLength = J1939Tp_FD_Transmit_Calculate_Frame_Size(MessageLength);

    /* Message padding if needed */
    for(i= MessageLength; i < J1939TpTxPduInfo.SduLength; i++)
    {
        tData[i] = J1939TP_CANFD_PADDING;
    }

    /* Initialize the data pointer */
    J1939TpTxPduInfo.SduDataPtr = &tData[0U];

    if(DtNPduMetaData > 0U)
    {
        J1939Tp_NPduMetaData_Handle(DtNPduMetaData,TxNSduMetaData,nsdu_ctrl_ptr,MetaDataInfo,J1939TP_CANFD_TP_DT_PGN,(J1939Tp_PbCfg_Ptr->J1939TpTxChannelPbcfg[loop_idx1]).J1939TpTxDtNPduTxConfIdEcuCPbcfg);
    }

    /* Update the state before the calling of CanIf_Transmit as fast confirmation may be received within the call of CanIf_Transmit*/
    /* Lock DT PDU until J1939Tp_TxConfirmation is received for this PDU */
    (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = FALSE;
    nsdu_ctrl_ptr->cnt_packets++;
    /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.DT.Sent,1 */
    /* Change the state */
    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_DATA);
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
    nsdu_ctrl_ptr->StartTxConfirmationTimeOut = TRUE;
    nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
    nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
#endif

    /* !LINKSTO EB_Ref.SWS_J1939Tp_00041.DT.CMDT,1 */
    /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.DT.Tx,1 */
    /* Transmit the CMDT DATA frame to CanIf */
    if(E_OK != CanIf_Transmit((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxDtNPduTxConfIdCanIf, &J1939TpTxPduInfo))
    {
        /* !LINKSTO J1939Tp.EB.CanIfTransmit.Tx.ENOTOK,1 */
        J1939Tp_Reinit_Tx(loop_idx1,loop_idx2,loop_idx3);
        /* Unlock DT PDU as CanIf_Transmit is returned E_NOT_OK */
        (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable = TRUE;
        /* indicate upper layer regarding the error */
        PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
    }
    else
    {
    }

}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_FD_Transmit_Data(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    /* Initialization of working pointer to selected NSdu control structure */
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);

    P2VAR(RetryInfoType, AUTOMATIC, J1939TP_APPL_DATA) RetryInfoPtr = (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxRetryInfo;
    /*PduInfo which holds the transmit data and the length info*/
    PduInfoType tPduInfo = {NULL_PTR, 0U};
    /*Remaining bytes to be transfered*/
    PduLengthType availabledataPtr;
    BufReq_ReturnType tBufReq_ReturnType;
    /* !LINKSTO EB_Ref.SWS_J1939Tp_00068.Padding.CMDT,1 */

    uint8 tBuf[60U] = {0U};

    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);

    DBG_J1939TP_CMDT_FD_TRANSMIT_DATA_ENTRY(loop_idx1,loop_idx2,loop_idx3);

    if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Tp_00228.CMDT.timeout,1 */
        J1939Tp_CMDT_Transmit_Data_Timeout(loop_idx1,loop_idx2,loop_idx3);
    }
    /* If N-PDU is available */
    else if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxDtNPduAvailable == TRUE)
    {
        /* For the state J1939TP_CMDT_TX_STATE_DATA_TRANSMISSION*/
        if ((nsdu_ctrl_ptr->msglength - nsdu_ctrl_ptr->data_cnt) > (uint8)J1939TP_MAX_CANFD_DT_MSGLENGTH)
        {
            tPduInfo.SduLength = J1939TP_MAX_CANFD_DT_MSGLENGTH;
        }
        else
        {
            tPduInfo.SduLength = (PduLengthType)(nsdu_ctrl_ptr->msglength) - (PduLengthType)(nsdu_ctrl_ptr->data_cnt);
        }
        tPduInfo.SduDataPtr = &tBuf[0U];

        if(RetryInfoPtr != NULL_PTR)
        {
            if(nsdu_ctrl_ptr->retry_cts_flag == TRUE)
            {
                /* !LINKSTO J1939Tp.SWS_J1939Tp_00221,1 */
                /* If retry flag is on, change TpDataState to TP_DATARETRY and set new TxTpDataCnt to data_cnt */
                nsdu_ctrl_ptr->retry_cts_flag = FALSE;
                RetryInfoPtr->TpDataState = TP_DATARETRY;
                RetryInfoPtr->TxTpDataCnt = (PduLengthType)(nsdu_ctrl_ptr->data_cnt);
            }
            else if(nsdu_ctrl_ptr->sn == 1U)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00217.FirstDT,1 */
                /* sn is 0 which means this is the first DT frame after reception of CTS. So initialize TpDataState as TP_DATACONF */
                RetryInfoPtr->TpDataState = TP_DATACONF;
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00217.NextDT,1 */
                /* sn is not 0 which means this is not first DT frame after reception of CTS. So assign TpDataState to TP_CONFPENDING */
                RetryInfoPtr->TpDataState = TP_CONFPENDING;
            }
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.CMDT.Retry,1 */
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00220,1 */
            tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,&tPduInfo,RetryInfoPtr, &availabledataPtr);
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Tp_00046.CMDT.NoRetry,1 */
            /* !LINKSTO J1939Tp.SWS_J1939Tp_00218,1 */
            /*Retry mechanism is not enabled. So retry parameter is NULL_PTR */
            tBufReq_ReturnType = PduR_J1939TpCopyTxData(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,&tPduInfo,NULL_PTR, &availabledataPtr);
        }

        switch (tBufReq_ReturnType)
        {
        case BUFREQ_OK:
            {
                J1939Tp_CMDT_FD_Data_Transmition ( &tPduInfo, loop_idx1, loop_idx2, loop_idx3);
                break;
            }

        case BUFREQ_E_BUSY:
        case BUFREQ_E_OVFL:
            {
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                    nsdu_ctrl_ptr->TrTimeout_SendAbort = TRUE;
                }
                break;
            }
        default:
            {
                /* BUFREQ_E_NOT_OK*/
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00048.CopyTxData.CMDT,1 */
                /* Abort transmission and notify upper layer */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                break;
            }
        }
    }
    else
    {
        /* N-Pdu is not available, so start Tr timer and wait for it */
        if(nsdu_ctrl_ptr->StartTrTime != TRUE)
        {
            nsdu_ctrl_ptr->StartTrTime = TRUE;
            nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
            nsdu_ctrl_ptr->TrTimeCounter = 0U;
            nsdu_ctrl_ptr->TrTimeout_SendAbort = FALSE;
        }
        else
        {
            /* Nothing to do */
        }
    }

    DBG_J1939TP_CMDT_FD_TRANSMIT_DATA_EXIT(loop_idx1,loop_idx2,loop_idx3);
}

static FUNC(void, J1939TP_CODE) J1939Tp_CMDT_EOMS_Handling(uint16 loop_idx1, uint16 loop_idx2, uint16 loop_idx3)
{
    CONSTP2VAR(J1939Tp_NSduCtrlType,AUTOMATIC,J1939TP_APPL_DATA) nsdu_ctrl_ptr = ((((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl);
    /* Initialization of working pointer to selected NSdu configuration structure. */
    P2CONST(J1939Tp_TxNSduType,AUTOMATIC,J1939TP_APPL_CONST) nsdu_cfg_ptr  = &(((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]);
    switch (nsdu_ctrl_ptr->state)
    {
        case J1939TP_CMDT_TX_STATE_EOMS_TRANSMISSION:
        {
            if(nsdu_ctrl_ptr->TrTimeElapsed == TRUE)
            {
                /* !LINKSTO J1939Tp.SAE.TimingConstraints.EOMS.Tr,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00234.E_TIMEOUT_TR,1 */
                /* DET Reporting needs to be done here with error Id J1939TP_E_TIMEOUT_TR */
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID, J1939TP_TRANSMIT_SERVICEID, J1939TP_E_TIMEOUT_TR);
#endif
                /* !LINKSTO EB_Ref.SWS_J1939Tp_00100.Tx.Tr,1 */
                /* !LINKSTO J1939Tp.EB.Dsn.CMDT.Tx.DT.Timeout,1 */
                if(TRUE == nsdu_ctrl_ptr->TrTimeout_SendAbort)
                {
                    /* Abort transmission and notify upper layer */
                    J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
                    /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                    nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
                }
                else
                {
                    /* Reset tr timeElapsed flag */
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    /* Call notification function*/
                    PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR, E_NOT_OK);
                    /* Reinitialization ****/
                    J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
                }
                /* Abort transmission and notify upper layer */
                J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_ABORT);
                /* !LINKSTO EB_Ref.SAE.FD.ConnectionAbortReasons.SystemResourcesBusy,1 */
                nsdu_ctrl_ptr->AbortReason = J1939TP_TPCM_ABORT_REASON_RESOURCES;
            }
            /* If N-PDU is available,  */
            else if ((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable == TRUE)
            {
                /* !LINKSTO EB_Ref.SAE.FD.CmdtTransfer.EOMS.Tx,1 */
                J1939Tp_CMDT_FD_Transmit_EOMS(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* N-Pdu is not available, so start Tr timer and wait for it */
                if(nsdu_ctrl_ptr->StartTrTime != TRUE)
                {
                    nsdu_ctrl_ptr->StartTrTime = TRUE;
                    nsdu_ctrl_ptr->TrTimeElapsed = FALSE;
                    nsdu_ctrl_ptr->TrTimeCounter = 0U;
                }
                else
                {
                    /* Nothing to do */
                }
            }
            break;
        }

        case J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_EOMS:
        {
            /* For the state J1939TP_CMDT_TX_STATE_WAIT_CONFIRMATION_ABORT*/
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF)
            if(TRUE == nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed)
            {
                /* TxConfirmation TimeOut elapsed */
                nsdu_ctrl_ptr->StartTxConfirmationTimeOut = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutElapsed = FALSE;
                nsdu_ctrl_ptr->TxConfirmationTimeOutCounter = 0U;
                nsdu_ctrl_ptr->txconfirmation = TRUE;
                nsdu_ctrl_ptr->txconfirmationResult = E_NOT_OK;
                (J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).ChannelStatus->J1939TpTxCmNPduAvailable = TRUE;
            }
#endif /* (J1939TP_RELIABLE_TXCONFIRMATION == STD_OFF) */

            if ((nsdu_ctrl_ptr->txconfirmation == TRUE) && (nsdu_ctrl_ptr->txconfirmationResult != E_OK))
            {
                /* Silent Abort- Report to the upper layer */
                PduR_J1939TpTxConfirmation(nsdu_cfg_ptr->J1939TpTxNSduIdPduR,E_NOT_OK);
                J1939Tp_Reinit_Tx(loop_idx1, loop_idx2, loop_idx3);
            }
            else
            {
                /* Nothing to do */
            }
            break;
        }

        /* CHECK: NOPARSE */
        default:
        {
            /* Nothing to do */
            break;
        }
        /* CHECK: PARSE */
    }
}

static FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation_CMDT_EOMS(P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr, uint16 Chan_Idx, Std_ReturnType result)
{
    /* Update the Tx confirmation Result flag */
    nsdu_ctrl_ptr->txconfirmationResult = result;

    DBG_J1939TP_TXCONFIRMATION_CMDT_EOMS_ENTRY(nsdu_ctrl_ptr, Chan_Idx, result);

#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_ON)
    if(E_OK != result)
    {
        /* Set the confirmation flag */
        nsdu_ctrl_ptr->txconfirmation = TRUE;
    }
    else
#endif
    {
        /* change the state */
        J1939Tp_NSDU_ChangeState(nsdu_ctrl_ptr, J1939TP_CMDT_TX_STATE_WAIT_ENDOFMSGACK);
        /* Reset the confirmation flag */
        nsdu_ctrl_ptr->txconfirmation = FALSE;

        /* Start T3 timer in case the retry is enabled */
        if(J1939Tp_Cfg_Ptr->J1939TpTxChannel[Chan_Idx].J1939TpTxRetryInfo != NULL_PTR)
        {
            nsdu_ctrl_ptr->StartT3Time = TRUE;
            nsdu_ctrl_ptr->T3TimeElapsed = FALSE;
            nsdu_ctrl_ptr->T3TimeCounter = 0U;
        }

        /* Start T5 timer */
        nsdu_ctrl_ptr->StartT5Time = TRUE;
        nsdu_ctrl_ptr->T5TimeElapsed = FALSE;
        nsdu_ctrl_ptr->T5TimeCounter = 0U;
    }

    DBG_J1939TP_TXCONFIRMATION_CMDT_EOMS_EXIT(nsdu_ctrl_ptr, Chan_Idx, result);
}

static FUNC(uint8 , J1939TP_CODE) J1939Tp_Set_Session_Number(uint8 MaxSessions, uint8 u8SA_val, uint8 u8DA_val)
{
    uint16 loop_idx1;
    uint16 loop_idx2;
    uint16 loop_idx3;
    uint8 loopCounter;
    uint8 Session = 0;
    boolean StopInnerLoops = FALSE;
    boolean StopOuterLoop = FALSE;
    P2VAR(J1939Tp_NSduCtrlType, AUTOMATIC, J1939TP_APPL_DATA) nsdu_ctrl_ptr = NULL_PTR;
    P2CONST(J1939Tp_TxChannelType,AUTOMATIC, J1939TP_APPL_CONST) TempPtrTxChannel = NULL_PTR;

    for (loopCounter = 0 ; ((loopCounter < MaxSessions) && (FALSE == StopOuterLoop)) ; loopCounter++)
    {

        for (loop_idx1=0U; ((loop_idx1<(J1939Tp_Cfg_Ptr->J1939TpNumberOfTxChannels)) && (StopInnerLoops == FALSE)); loop_idx1++)
        {
            TempPtrTxChannel = &(J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]);
            for (loop_idx2=0U; ((loop_idx2<(TempPtrTxChannel->J1939TpNumberOfTxPg))&& (StopInnerLoops == FALSE)); loop_idx2++)
            {
                for (loop_idx3=0U; ((loop_idx3<(TempPtrTxChannel->J1939TpTxPg[loop_idx2]).J1939TpNumberOfTxNSdu) && (StopInnerLoops == FALSE)); loop_idx3++)
                {
                    /* Optimize access to structure element */
                    nsdu_ctrl_ptr = (((J1939Tp_Cfg_Ptr->J1939TpTxChannel[loop_idx1]).J1939TpTxPg[loop_idx2]).J1939TpTxNSdu[loop_idx3]).J1939TpTxNSduCtrl;
                    /* Check if there another transmission for same Session */
                    if ((nsdu_ctrl_ptr->state != J1939TP_TX_IDLE) && (nsdu_ctrl_ptr->session_num == loopCounter) && (nsdu_ctrl_ptr->sa == u8SA_val) && (nsdu_ctrl_ptr->da == u8DA_val) && (nsdu_ctrl_ptr->IsMultipleFrameType == TRUE))
                    {
                        StopInnerLoops = TRUE;
                    }
                    else
                    {
                        /* nothing , continue the loop to check other SDUs*/
                    }
                }
            }
        }

        if(TRUE == StopInnerLoops)
        {
            StopInnerLoops = FALSE;
        }
        else
        {
            Session = loopCounter;
            StopOuterLoop = TRUE;
        }
    }
    return Session;
}
#endif

#define J1939TP_STOP_SEC_CODE
#include <J1939Tp_MemMap.h>
/*==================[end of file]===========================================*/

