/**
 * \file
 *
 * \brief AUTOSAR J1939Rm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Rm.
 *
 * \version 1.1.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 9.3 (Required)
 *    Arrays shall not be partially initialized.
 *
 *    Reason:
 *    - The J1939Rm_GlobalConfig.J1939Rm50MsSupervision is initialized in J1939Rm_Init.
 *
 *  MISRAC2012-2) Deviated Rule 11.1 (Required)
 *    Conversions shall not be performed between a pointer to a function and any other type.
 *
 *    Reason:
 *    Casting must be done to avoid the warning because the Rte_user has a different return type for all its callback functions.
 */

/*
 * tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason: False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 */

/*==================[inclusions]============================================*/
#include <J1939Rm_Cbk.h>
#include <J1939Rm.h>
#include <J1939Rm_Api.h>          /* J1939Rm API definitions (own interface) */
#include <J1939Rm_Int.h>          /* J1939Rm internal interface*/
#include <PduR_J1939Rm.h>
#include <J1939Rm_PBcfg.h>            /* Module post-build generated configuration */
#include <J1939Rm_Types_Int.h>
#include <J1939Rm_Lcfg.h>
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/* If for any User, user type is configured as RTE, then following inclusion will be enabled*/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00110,1 */
#if (J193RM_RTE_SUPPORT == STD_ON)
#include <Rte_J1939Rm.h>
#endif



/*Operation Prototypes*/

#define J1939RM_START_SEC_CODE
#include <J1939Rm_MemMap.h>

#if (J1939RM_SENDREQUEST_SUPPORT == STD_ON)
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidOnlineChannel( NetworkHandleType channel,P2VAR(uint8,AUTOMATIC,J1939RM_APPL_DATA) channel_index);
#endif

#if ((J1939RM_SENDREQUEST_SUPPORT == STD_ON)&&(J1939RM_DEV_ERROR_DETECT == STD_ON))
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_TimeoutSupervision_1250MS( uint8 userId, uint32 requestedPgn, uint8 destAddress, uint8 channel_index, uint8 node_index);
#endif
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_AckTransmission( uint8 AckCode, uint8 AckAddress, uint8 PGN_Byte_0, uint8 PGN_Byte_1, uint8 PGN_Byte_2, PduIdType AckTxPduRef);
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_RequestTransmission( uint8 PGN_Byte_0, uint8 PGN_Byte_1, uint8 PGN_Byte_2, PduIdType RqstTxPduRef);

static FUNC(void, J1939RM_CODE) J1939Rm_Check_Node_and_Pgn( uint32 Rx_PGN, uint8 DA,P2VAR(boolean, AUTOMATIC, J1939RM_APPL_DATA) ValidId, P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) ValidPGN, P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) pgn_index, P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) node_index, P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) Rx_PGN_COMConfigured, P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) userIndex);

static FUNC(boolean, J1939RM_CODE) J1939Rm_ChIndx_ReceivedID( PduIdType RxPduId ,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) channel_index);

static FUNC(void, J1939RM_CODE) J1939Rm_EcuC_SetMetaDataCanId( uint8 BYTE3, uint8 BYTE2, uint8 BYTE1, uint8 BYTE0, EcuC_PduIdType J1939RmTx_Ecuc_PduId, uint8 ApiId);

static FUNC(void, J1939RM_CODE) J1939Rm_TxConfirmationTimer( uint8 ch_idx);

static FUNC(void, J1939RM_CODE) J1939Rm_Requests_Timeout_Supervision( uint8 ch_idx);

static FUNC(void, J1939RM_CODE) J1939Rm_Request_Reception_Handling( PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr);

static FUNC(void, J1939RM_CODE) J1939Rm_Ack_Reception_Handling( PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr);

static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidChannel( NetworkHandleType channel,P2VAR(uint8,AUTOMATIC,J1939RM_APPL_DATA) channel_index);

static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidNode( uint16 UserId,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) node_index);

static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidUser( uint16 UserId,P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) user_index);

#if (J1939RM_SENDREQUEST_SUPPORT == STD_ON)
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_TXPG_RQST( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueSA, uint8 QueueDA, uint8 QueuePriority, boolean QueuecheckTimeout );
#endif

static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_TXPG_ACKM( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueAckCode, uint8 QueueAckAddress, uint8 QueuePriority );

static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_TSV_RQST( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueSA, uint8 QueueDA );

static FUNC(void, J1939RM_CODE) J1939Rm_Dequeue( uint8 QueueType, uint8 channel_index,P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) QueueUserId,P2VAR(uint32, AUTOMATIC,J1939RM_APPL_DATA) QueuePgn,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueSA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueDA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueuePriority,P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) QueuecheckTimeout );

static FUNC(void, J1939RM_CODE) J1939Rm_TXPG_RQST_QueueTop( uint8 channel_index,P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) QueueUserId,P2VAR(uint32, AUTOMATIC,J1939RM_APPL_DATA) QueuePgn,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueSA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueDA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueuePriority,P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) QueuecheckTimeout );

static FUNC(void, J1939RM_CODE) J1939Rm_Flush( uint8 QueueType, uint8 channel_index);

static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidRmvRqstTSVQueue( uint32 PGN, uint16 user_id, uint8 channel_index, uint8 node_addr, uint8 dest_addr );

static FUNC(void, J1939RM_CODE) J1939Rm_ValidateConfig( P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) ConfigPtr );

#if (J1939RM_COM_SUPPORT == STD_ON)
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidRmvRqstCOMQueue( uint32 PGN, uint16 user_index,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueSA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueDA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueChannelId);

static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_COM_RQST( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueSA, uint8 QueueDA );
#endif

#define J1939RM_STOP_SEC_CODE
#include <J1939Rm_MemMap.h>

/*Variables and Constants*/
#define J1939RM_START_SEC_VAR_INIT_8
#include <J1939Rm_MemMap.h>
static VAR(boolean, J1939RM_VAR) J1939Rm_Initialized = (boolean)FALSE; /**< Variable to store the initialization status of J1939RM */
#define J1939RM_STOP_SEC_VAR_INIT_8
#include <J1939Rm_MemMap.h>

#define J1939RM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Rm_MemMap.h>
/* Deviation MISRAC2012-1 <1> */

static VAR(J1939Rm_GlobalConfig_Struct, J1939RM_VAR) J1939Rm_GlobalConfig ; /* Instance of Global J1939RM configuration structure */
static P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_CONST) J1939Rm_PbCfg_Ptr;

#define J1939RM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Rm_MemMap.h>

/*Private and Public Operations*/
/*Private Functions*/
#define J1939RM_START_SEC_CODE
#include <J1939Rm_MemMap.h>

/* *****************************************************************************
 *  Name                 : J1939Rm_RequestTransmission
 *  Description          : this function is used to send the requested PGN through PduR_J1939RmTransmit.
 *  Parameters           : Input : uint8 PGN_Byte_0
 *                         Input : uint8 PGN_Byte_1
 *                         Input : uint8 PGN_Byte_2
 *                         Input : PduIdType RqstTxPduRef
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_RequestTransmission( uint8 PGN_Byte_0, uint8 PGN_Byte_1, uint8 PGN_Byte_2, PduIdType RqstTxPduRef)
{
    PduInfoType Tx_info;
    uint8 Tx_data[3];
    Std_ReturnType PduR_RqstTransRtrnRslt = E_NOT_OK;

    Tx_data[0] =  PGN_Byte_0;   /*Lower Byte of Requested PGN*/
    Tx_data[1] =  PGN_Byte_1;   /*Middle Byte of Requested PGN*/
    Tx_data[2] =  PGN_Byte_2;   /*Upper Byte of Requested PGN*/

    Tx_info.SduDataPtr = &Tx_data[0];
    Tx_info.SduLength = (PduLengthType)3u;           /*Pdu Length */

    PduR_RqstTransRtrnRslt = PduR_J1939RmTransmit(RqstTxPduRef, (&Tx_info));
    return PduR_RqstTransRtrnRslt;

}
/* *****************************************************************************
 *  Name                 : J1939Rm_IsValidConfig
 *  Description          : This function is used to validate the generated signatures.
 *  Parameters           : Input : void voidConfigPtr
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/

FUNC( Std_ReturnType, J1939RM_CODE) J1939Rm_IsValidConfig (P2CONST(void,AUTOMATIC,J1939RM_APPL_CONST) voidConfigPtr)
{
  /* Assume an invalid configuration */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(J1939Rm_ConfigType,AUTOMATIC,J1939RM_APPL_CONST) ConfigPtr = voidConfigPtr;

  if (ConfigPtr != NULL_PTR)
  {
    /* Check if the configuration fits to the platform */
    if (TS_PlatformSigIsValid(ConfigPtr->PlatformSignature) == TRUE )
    {
      /* Validate the post build configuration against the compile time configuration */
      if (J1939RM_CFG_SIGNATURE == ConfigPtr->CfgSignature)
      {
        /* Validate the post build configuration against the link time configuration */
        if (J1939Rm_LcfgSignature == ConfigPtr->LcfgSignature)
        {
          /* Validate the post build configuration against the compile time published information
             configuration */
          if (J1939RM_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
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

/* *****************************************************************************
 *  Name                 : J1939Rm_ValidateConfig
 *  Description          : This function is used by the init function to validate the configuration.
 *  Parameters           : Input : J1939Rm_ConfigType ConfigPtr
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_ValidateConfig( P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) ConfigPtr )
{
#if (J1939RM_PBCFGM_SUPPORT_ENABLED == STD_ON)
    /* If the initialization function is called with a null pointer get the configuration from the
     * post build configuration manager */
  if (ConfigPtr == NULL_PTR)
  {
      PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
      if (E_OK == PbcfgM_GetConfig(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, &ModuleConfig))
      {
          ConfigPtr = (P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST)) ModuleConfig;
      }
  }
#endif /* J1939RM_PBCFGM_SUPPORT_ENABLED == STD_OFF */
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)

  /* check whether parameter ConfigPtr is a NULL_PTR */
  if(ConfigPtr == NULL_PTR)
  {
    /* found a NULL_PTR, report to DET */
    (void)Det_ReportError(J1939RM_MODULE_ID,J1939RM_INSTANCE_ID,J1939RM_INIT_SERVICEID,J1939RM_E_PARAM_POINTER);
  }
  /* check that configuration pointer is valid */
  else
      if ( E_OK != J1939Rm_IsValidConfig(ConfigPtr))
      {
          (void)Det_ReportError(J1939RM_MODULE_ID,J1939RM_INSTANCE_ID,J1939RM_INIT_SERVICEID,J1939RM_E_INIT_FAILED);
      }
      else
#else /* check that configuration is valid */
      if(J1939Rm_IsValidConfig(ConfigPtr) == E_OK)
#endif
    {  /* Configuration is valid use copy config pointer  */
      /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00046,1 */
      /* !LINKSTO J1939Rm.SWS_J1939Rm_00036,1 */
      J1939Rm_PbCfg_Ptr = ConfigPtr;
    }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_AckTransmission
 *  Description          : this function is used to send the Acknowledgement through PduR_J1939RmTransmit.
 *  Parameters           : Input : uint8 AckCode
 *                       : Input : uint8 AckAddress
 *                       : Input : uint8 PGN_Byte_0
 *                       : Input : uint8 PGN_Byte_1
 *                       : Input : uint8 PGN_Byte_2
 *                       : Input : PduIdType AckTxPduRef
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_AckTransmission( uint8 AckCode, uint8 AckAddress, uint8 PGN_Byte_0, uint8 PGN_Byte_1, uint8 PGN_Byte_2, PduIdType AckTxPduRef)
{
    PduInfoType Tx_info;
    uint8 Tx_data[8];
    Std_ReturnType PduR_AckTransRtrnRslt = E_NOT_OK;

    /*PduData Information*/
    Tx_data[0] =  AckCode;
    Tx_data[1] =  (uint8)0xFF;
    Tx_data[2] =  (uint8)0xFF;
    Tx_data[3] =  (uint8)0xFF;
    Tx_data[4] =  AckAddress;     /*Acknowledged Address*/
    Tx_data[5] =  PGN_Byte_0;     /*Lower Byte of Ack PGN*/
    Tx_data[6] =  PGN_Byte_1;     /*Middle Byte of Ack PGN*/
    Tx_data[7] =  PGN_Byte_2;     /*Upper Byte of Ack PGN*/

    Tx_info.SduDataPtr = &Tx_data[0];
    Tx_info.SduLength = (PduLengthType)8u;

    /* !LINKSTO J1939Rm.SWS_J1939Rm_00044,1 */
    PduR_AckTransRtrnRslt = PduR_J1939RmTransmit(AckTxPduRef, (&Tx_info));
    return PduR_AckTransRtrnRslt;

}

/* ******************************************************************************
 *  Name                 : J1939Rm_Requests_Timeout_Supervision
 *  Description          : handles the Timeout Suoervision functionality for Requests
 *  Parameters           : Input : uint8 ch_idx
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
 static FUNC(void, J1939RM_CODE) J1939Rm_Requests_Timeout_Supervision( uint8 ch_idx)
{
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr       = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_ConfigType,          AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_User_Const_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr->J1939RmUserConstStructPtr;
  CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
  CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  P2CONST(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmRqstTSQueueTypeStructPtr;
  P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;

  uint8 TmpJ1939RmRequestTimeoutMonitors = 0u;
  uint16 user_index= (uint16)0;
  uint8 node_index= (uint8)0;

  uint32 TmpQueuePgn = 0u;
  uint16 TmpQueueUserId = 0u;
  uint8 TmpQueueSA = 0u;
  uint8 TmpQueueDA = 0u;
  uint8 TmpQueuePriority = 0u;
  boolean TmpQueuecheckTimeout = 0u;
  uint8 time_idx = 0u;

  /*Timeout supervision for Requests*/
  TmpJ1939RmRqstTSQueueTypeStructPtr    = TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTSQueueTypeStructPtr;
  TmpJ1939RmRqstTSQueueDataStructPtr    = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;
  TmpJ1939RmRequestTimeoutMonitors      = TmpJ1939RmChannelConstStructPtr_Pbcfg[ch_idx].J1939RmRequestTimeoutMonitors;

  for (time_idx= (uint8)0;time_idx<TmpJ1939RmRequestTimeoutMonitors;time_idx++)
  {
      if(TmpJ1939RmRqstTSQueueDataStructPtr[time_idx].J1939RmTimeoutSupervisionEnable == (boolean)TRUE)
      {
          if (TmpJ1939RmRqstTSQueueDataStructPtr[time_idx].J1939RmTimeoutSupervisionTimer >  (uint8)0)
          {
              TmpJ1939RmRqstTSQueueDataStructPtr[time_idx].J1939RmTimeoutSupervisionTimer--;
          }
          /* !LINKSTO J1939Rm.SWS_J1939Rm_00030,1 */
          else
          {
              /*Remove the entry for the User from TSV queue and stop Timeout Supervision timer for it. Provide RequestTimeoutIndication to J1939RM User.*/
              /*Dequeue the RQST from RQST TSV Queue.*/
              J1939Rm_Dequeue( J1939RM_TSV_RQST,     /*Tsv=2*/
                               ch_idx,               /*Channel Index*/
                               &TmpQueueUserId,      /*Calling module's user ID.*/
                               &TmpQueuePgn,         /*PGN of the Requested PG.*/
                               &TmpQueueSA,          /*Address of the Source node for Rqst*/
                               &TmpQueueDA,          /*Address of the destination node for Rqst*/
                               &TmpQueuePriority,    /*Priority of the Requested PG.*/
                               &TmpQueuecheckTimeout );

              (void)J1939Rm_ValidUser(TmpQueueUserId, &user_index);
              (void)J1939Rm_ValidNode(TmpQueueUserId, &node_index);


             (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserRequestTimeoutIndicationFctPtr)(TmpJ1939RmNodeConstStructPtr_Pbcfg[node_index].J1939RmNodeId, TmpJ1939RmChannelConstStructPtr_Pbcfg[ch_idx].J1939RmChannelId, TmpQueuePgn, TmpQueueDA);
          }
      }
      else
      {
          /*The Timeout Supervision for user is disabled*/
      }
  }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_Check_Node_and_Pgn
 *  Description          : This function get the received Pgn and destination address,
 *                         change the value of ValidId, ValidPGN, and Rx_PGN_COMConfigured to TRUE if found,
 *                         and change the index of pgn, user, and node.
 *  Parameters           : Input : uint32 Rx_PGN
 *                                 uint8 DA
 *                                 boolean* ValidId
 *                                 boolean* ValidPGN
 *                                 uint8* pgn_index
 *                                 uint8* node_index
 *                                 boolean* Rx_PGN_COMConfigured
 *                                 uint16* userIndex
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_Check_Node_and_Pgn(
 uint32 Rx_PGN,
 uint8 DA,
P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA)ValidId,
P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA)ValidPGN,
P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA)pgn_index,
P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA)node_index,
P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) Rx_PGN_COMConfigured,
P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) userIndex)
{
    /*pbcfg Structures*/
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeConstStructPtr;
    CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg-> J1939RmUserConstStructPtr;
    P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
    P2CONST(uint16, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeUserRefPtr;
    P2CONST(uint32, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserPGNPtr;

    uint8 nd_idx = 0u;
    uint8 usr_idx = 0u;
    uint32 pgn_idx = 0u;

    if (DA != J1939RM_BROADCAST_ADDR)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00007.configured_addresses,1 */
        /*Validate Node address*/
        for (nd_idx = (uint8) 0;((nd_idx < TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeNr) && (*ValidId == (boolean) FALSE)); nd_idx++)
        {
            /* !LINKSTO J1939Rm.SWS_J1939Rm_00026,1 */
            if (TmpJ1939RmNodeConstStructPtr_Pbcfg[nd_idx].J1939RmNodeAddress == DA)
            {
                *node_index = (uint8)nd_idx;
                *ValidId = (boolean) TRUE;
            }
        }
        if (*ValidId == (boolean) TRUE)
        {
            /*Validate Requested PGN (Rx_PGN)*/
            /* Check if Requested PGN (Rx_PGN) is configured? */
            TmpJ1939RmNodeUserRefPtr = TmpJ1939RmNodeConstStructPtr_Pbcfg[*node_index].J1939RmNodeUserRefPtr;
            for (usr_idx = (uint8) 0;((usr_idx < TmpJ1939RmNodeConstStructPtr_Pbcfg[*node_index].J1939RmNodeUserNr) && (*ValidPGN == (boolean) FALSE)); usr_idx++)
            {
                (void) J1939Rm_ValidUser(TmpJ1939RmNodeUserRefPtr[usr_idx], userIndex);
                if (TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmUserType == (uint8)J1939RM_USER_COM)
                {
                    /*J1939RmUserType is J1939RM_USER_COM*/
                    TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmComIPduConstStructPtr;
                    for (pgn_idx = (uint32) 0; ((pgn_idx < (uint32) TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmComIPduNr) && (*ValidPGN == (boolean) FALSE)); pgn_idx++)
                    {
                        if (Rx_PGN == TmpJ1939RmComIPduConstStructPtr[pgn_idx].J1939RmComIPduPGN)
                        {
                            /*Requested PGN (Rx_PGN) is configured to be handled through COM */
                            *Rx_PGN_COMConfigured = (boolean) 1;
                            *pgn_index = (uint8)pgn_idx;
                            *ValidPGN = (boolean) TRUE;
                        }
                        else
                        {

                        }
                    }
                }
                else
                {
                    /*J1939RmUserType is J1939RM_USER_J1939DCM or */
                    /*J1939RM_USER_J1939NM  or */
                    /*J1939RM_USER_CDD      or */
                    /*J1939RM_USER_RTE*/
                    TmpJ1939RmUserPGNPtr = TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmUserPGNPtr;
                    for (pgn_idx = (uint32) 0; ((pgn_idx < TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmUserPGNNr) && (*ValidPGN == (boolean) FALSE)); pgn_idx++)
                    {
                        if (Rx_PGN == TmpJ1939RmUserPGNPtr[pgn_idx])
                        {
                            /*Requested PGN (Rx_PGN) is configured to be handled through J1939DCM or J1939NM or CDD or RTE*/
                            *ValidPGN = (boolean) TRUE;
                        }
                    }
                }
            }
        }
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00007.global_DA,1 */
        *ValidId = (boolean) TRUE;
        /*Validate Requested PGN (Rx_PGN)*/
        /* Check if Requested PGN (Rx_PGN) is configured? */
        for (nd_idx = (uint8) 0;((nd_idx < TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeNr) && (*ValidPGN == (boolean) FALSE)); nd_idx++)
        {
            TmpJ1939RmNodeUserRefPtr = TmpJ1939RmNodeConstStructPtr_Pbcfg[nd_idx].J1939RmNodeUserRefPtr;
            for (usr_idx = (uint8) 0;((usr_idx < TmpJ1939RmNodeConstStructPtr_Pbcfg[nd_idx].J1939RmNodeUserNr) && (*ValidPGN == (boolean) FALSE)); usr_idx++)
            {
                (void) J1939Rm_ValidUser(TmpJ1939RmNodeUserRefPtr[usr_idx], userIndex);
                if (TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmUserType == (uint8)J1939RM_USER_COM)
                {
                    /*J1939RmUserType is J1939RM_USER_COM*/
                    TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmComIPduConstStructPtr;
                    for (pgn_idx = (uint32) 0; ((pgn_idx < (uint32) TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmComIPduNr) && (*ValidPGN == (boolean) FALSE)); pgn_idx++)
                    {
                        if (Rx_PGN == TmpJ1939RmComIPduConstStructPtr[pgn_idx].J1939RmComIPduPGN)
                        {
                            /*Requested PGN (Rx_PGN) is configured to be handled through COM */
                            *Rx_PGN_COMConfigured = (boolean) 1;
                            *node_index = (uint8)nd_idx;
                            *pgn_index = (uint8)pgn_idx;
                            *ValidPGN = (boolean) TRUE;
                        }
                        else
                        {

                        }
                    }
                }
                else
                {
                    /*J1939RmUserType is J1939RM_USER_J1939DCM or */
                    /*J1939RM_USER_J1939NM  or */
                    /*J1939RM_USER_CDD      or */
                    /*J1939RM_USER_RTE*/
                    TmpJ1939RmUserPGNPtr = TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmUserPGNPtr;
                    for (pgn_idx = (uint32) 0; ((pgn_idx < TmpJ1939RmUserConstStructPtr_Pbcfg[*userIndex].J1939RmUserPGNNr) && (*ValidPGN == (boolean) FALSE)); pgn_idx++)
                    {
                        if (Rx_PGN == (TmpJ1939RmUserPGNPtr[pgn_idx]))
                        {
                            /*Requested PGN (Rx_PGN) is configured to be handled through J1939DCM or J1939NM or CDD or RTE*/
                            *node_index = (uint8)nd_idx;
                            *ValidPGN = (boolean) TRUE;
                        }
                    }
                }
            }
        }
    }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_ChIndx_ReceivedID
 *  Description          : return ture if RxPduId is configured for one of the configured channel.
 *                         change the channel_index
 *  Parameters           : Input : uint8* channel_index
 *                         PduIdType RxPduId
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ChIndx_ReceivedID( PduIdType RxPduId ,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) channel_index)
{
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr -> J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr -> J1939RmChannelConstStructPtr;
    uint8 ch_idx = 0u;
    boolean return_val = (boolean) FALSE;

    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (RxPduId == J1939RM_INVALID_PDU_ID)
    {
    }
    else
    #endif
    {


        for (ch_idx = (uint8) 0;((ch_idx < TmpJ1939RmConfigPtr -> J1939RmChannelNr) && (return_val == (boolean) FALSE)); ch_idx++)
        {
            if (RxPduId == TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRqstRxPduId)
            {
                (*channel_index) = (uint8)ch_idx;
                return_val = (boolean) TRUE;
            }
        }

    }
    return return_val;

}

/* *****************************************************************************
 *  Name                 : J1939Rm_TxConfirmationTimer
 *  Description          : handles the timing functionality related to TxConfirmationTimer
 *  Parameters           : Input : uint8 ch_idx
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/

static FUNC(void, J1939RM_CODE) J1939Rm_TxConfirmationTimer( uint8 ch_idx)
{
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
    CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;

    switch (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation)
    {
        case J1939RM_RQST_TX:
        {
          /*Rqst Transmitted and waiting for TxConfirmation*/
          if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer > (uint8)0)
          {
            TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer--;
          }
          else
          {
            /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00023,1 */
            /*Flush Rqst Queue*/
            J1939Rm_Flush( J1939RM_TXPG_RQST, ch_idx);
            /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_RQST_TX_TIMEOUT,1 */
            TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_NO_TX;
          }
          break;
        }
        case J1939RM_ACKM_TX:
        {
          /*Ackm Transmitted and waiting for TxConfirmation*/
          if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer > (uint8)0)
          {
            TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer--;
          }
          else
          {
            /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00020,1 */
            /*Flush Ackm Queue*/
            J1939Rm_Flush( J1939RM_TXPG_ACKM, ch_idx);
            /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_ACKM_TX_TIMEOUT,1 */
            TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_NO_TX;
          }
          break;
        }
        default:
        {
          break;
        }
    }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_EcuC_SetMetaDataCanId
 *  Description          : Calculates CanId then calls EcuC_SetMetaDataCanId
 *  Parameters           : Input : uint8 BYTE3
 *                                 uint8 BYTE2
 *                                 uint8 BYTE1
 *                                 uint8 BYTE0
 *                                 EcuC_PduIdType J1939RmTx_Ecuc_PduId
 *                                 uint8 ApiId
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_EcuC_SetMetaDataCanId( uint8 BYTE3, uint8 BYTE2, uint8 BYTE1, uint8 BYTE0, EcuC_PduIdType J1939RmTx_Ecuc_PduId, uint8 ApiId)
{
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType SetMetaDataResult = (Std_ReturnType)0;
#endif
    uint32 CanId32;
    PduInfoType dummy_Var;
    P2VAR(PduInfoType, AUTOMATIC,J1939RM_APPL_DATA) dummy_Ptr = &dummy_Var;
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00119,1,J1939Rm.SWS_J1939Rm_00120,1,
                                J1939Rm.SWS_J1939Rm_00121,1*/
    CanId32 = ((uint32)BYTE3 << 8*3 ) | ((uint32)BYTE2 << 8*2 ) | ((uint32)BYTE1 << 8 ) | ((uint32)BYTE0 << 8*0);

#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    SetMetaDataResult = EcuC_SetMetaDataCanId(J1939RmTx_Ecuc_PduId, dummy_Ptr, CanId32);
    if( E_OK != SetMetaDataResult )
    {
      /*Report DET Error*/
      /* !LINKSTO J1939Rm.EB.Invalid_MetaData,1 */
      (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, ApiId, J1939RM_E_INVALID_METADATA_HANDLE);
    }
#else
    (void)EcuC_SetMetaDataCanId(J1939RmTx_Ecuc_PduId, dummy_Ptr, CanId32);
    TS_PARAM_UNUSED(ApiId);
#endif
}

#if (J1939RM_SENDREQUEST_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_ValidOnlineChannel
 *  Description          : Check if channel is configured for channel id, and if it is online.
 *  Parameters           : Input : NetworkHandleType channel
 *                                 uint8*            channel_index
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidOnlineChannel( NetworkHandleType channel,P2VAR(uint8,AUTOMATIC,J1939RM_APPL_DATA) channel_index)
{
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
    boolean retVal = (boolean)FALSE;
    if (J1939Rm_ValidChannel(channel, channel_index))
    {
        if (TmpJ1939RmChannelRamStructPtr[(uint8)(*channel_index)].J1939RmState == J1939RM_STATE_ONLINE)
        {
            /*Request Handling in ONLINE state*/
            retVal = (boolean)TRUE;
        }
        else
        {
        }
    }
    else
    {
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00041.J1939Rm_SendRequest,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_INVALID_NETWORK_ID.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_NETWORK_ID);
    #endif
    }
    return retVal;
}
#endif

#if ((J1939RM_SENDREQUEST_SUPPORT == STD_ON)&&(J1939RM_DEV_ERROR_DETECT == STD_ON))
/* *****************************************************************************
 *  Name                 : J1939Rm_TimeoutSupervision_1250MS
 *  Description          : this function is used to handle 1250ms TimeoutSupervision.
 *  Parameters           : Input : uint8 userId
 *                                 uint32 requestedPgn
                                   uint8 destAddress
                                   uint8 channel_index
                                   uint8 node_index
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_TimeoutSupervision_1250MS( uint8 userId, uint32 requestedPgn, uint8 destAddress, uint8 channel_index, uint8 node_index)
{
    uint8 TSQueueIterator;
    Std_ReturnType retVal = E_OK;
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
    CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
    CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
    P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;
    P2VAR(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA)TmpJ1939RmRqstTSQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTSQueueTypeStructPtr;
    uint8 TmpJ1939RmRequestTimeoutMonitors = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestTimeoutMonitors;
    TmpJ1939RmRqstTSQueueDataStructPtr = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;
    if (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount < TmpJ1939RmRequestTimeoutMonitors && TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount > 0u )
    {
        for (TSQueueIterator = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront; (TSQueueIterator < (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount+TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront)); TSQueueIterator++)
        {
            if(((TmpJ1939RmRqstTSQueueDataStructPtr[TSQueueIterator].J1939RmRqstUserId == userId) &&
               (TmpJ1939RmRqstTSQueueDataStructPtr[TSQueueIterator].J1939RmRqstPgn == requestedPgn)) &&
               ((((TmpJ1939RmRqstTSQueueDataStructPtr[TSQueueIterator].J1939RmRqstSA) == (TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeAddress)) &&
               ((TmpJ1939RmRqstTSQueueDataStructPtr[TSQueueIterator].J1939RmRqstDA) == (destAddress))) &&
               (TmpJ1939RmRqstTSQueueDataStructPtr[TSQueueIterator].J1939RmTimeoutSupervisionEnable == TRUE))
            )
            {
                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_TimeoutSupervision_1250MS);
                retVal = E_NOT_OK;
                break;
            }
        }
    }
    return retVal;
}
#endif

/* *****************************************************************************
 *  Name                 : J1939Rm_Ack_Reception_Handling
 *  Description          : Hanles the reception of Acknowledgements
 *  Parameters           : Input : PduIdType RxPduId
 *                         Input : PduInfoType *PduInfoPtr
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_Ack_Reception_Handling( PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr)
{
    /*Local Variables*/
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg -> J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = & J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_RealStructType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr -> J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmChannelConstStructPtr;
    CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeConstStructPtr;
    CONSTP2CONST(J1939Rm_User_Const_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr -> J1939RmUserConstStructPtr;
    CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmUserConstStructPtr;
    CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr -> J1939RmChannelRamStructPtr;
    P2CONST(uint16, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeUserRefPtr;
    P2CONST(uint32, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserAckPGNPtr;
    P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;

    uint32 Rx_PGN = 0u;
    uint8 usr_idx = 0u;
    uint32 pgn_idx = 0u;
    uint16 user_index = (uint8)0;
    uint8 nd_idx = 0u;
    uint8 ch_idx = 0u;
    uint8 ndch_idx = 0u;
    uint8 channel_index = (uint8)0;
    uint8 node_index = (uint8)0;
    uint8 PrioByte = (uint8)0;
    boolean ValidId = (boolean)FALSE;
    Std_ReturnType getMetaDataResult = (Std_ReturnType)E_NOT_OK;
    uint32 CanId;
    uint8 SA;
    uint8 Priority;
    ValidId = (boolean) FALSE;

    /*Search RxPduId(J1939RmAckmRxPduId) in configured Channels to know the channel handling the Acknowledgement*/
    for (ch_idx = (uint8) 0; ((ch_idx < TmpJ1939RmConfigPtr_Pbcfg -> J1939RmChannelNr) && (ValidId == (boolean) FALSE)); ch_idx++)
    {
        if (RxPduId == TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckmRxPduId)
        {
            channel_index = ch_idx;
            ValidId = (boolean) TRUE;
        }
    }
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (ValidId != (boolean) TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_RxIndication,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_RXINDICATION_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);
    }
    else
#endif
    {   /* !LINKSTO J1939Rm.SWS_J1939Rm_00125,1*/
        getMetaDataResult = EcuC_GetMetaDataCanId((EcuC_PduIdType)(TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmAckmRx_Ecuc_PduId), PduInfoPtr, & CanId);

        if (E_OK != getMetaDataResult)
        {
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
            /*Report DET Error*/
            /* !LINKSTO J1939Rm.EB.Invalid_MetaData,1 */
            (void) Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_RXINDICATION_SERVICEID, J1939RM_E_INVALID_METADATA_HANDLE);
#endif
        }

        SA = (uint8)(CanId);
        Priority = (uint8)(((uint32)CanId & 0x1C000000U) >> 24);
        if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmState == J1939RM_STATE_ONLINE)
        {
            /*Validate Destination Node address*/
            ValidId = (boolean) FALSE;
            for (nd_idx = (uint8) 0; ((nd_idx < TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeNr) && (ValidId == (boolean) FALSE)); nd_idx++)
            {
                if (TmpJ1939RmNodeConstStructPtr[nd_idx].J1939RmNodeAddress == PduInfoPtr -> SduDataPtr[4])
                {
                    node_index = nd_idx;
                    ValidId = (boolean) TRUE;
                }
            }
            if (ValidId == (boolean) TRUE)
            {
                /*Check if Node on which User is configured is handled through the Channel Id*/
                /*Check if Node on which User is configured is configured with the Channel */
                ValidId = (boolean) FALSE;
                TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
                for (ndch_idx = (uint8) 0; ((ndch_idx < TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr) && (ValidId == (boolean) FALSE)); ndch_idx++)
                {
                    if (TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId == TmpJ1939RmNodeChannelRefPtr[ndch_idx])
                    {
                        ValidId = (boolean) TRUE;
                    }
                }
                if (ValidId == (boolean) TRUE)
                {
                    /*Rx_PGN - Received Acknowledgement PGN*/
                    Rx_PGN = (((uint32) PduInfoPtr -> SduDataPtr[7] << 16) |
                              ((uint32) PduInfoPtr -> SduDataPtr[6] << 8)  |
                               (uint32) PduInfoPtr -> SduDataPtr[5]);

                    /*Validate Acknowledged PGN (Rx_PGN)*/
                    /* Check if Received Acknowledgement PGN (Rx_PGN) is configured? */
                    ValidId = (boolean) FALSE;
                    TmpJ1939RmNodeUserRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeUserRefPtr;
                    for (usr_idx = (uint8) 0; ((usr_idx < TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeUserNr) && (ValidId == (boolean) FALSE)); usr_idx++)
                    {
                        (void) J1939Rm_ValidUser(TmpJ1939RmNodeUserRefPtr[usr_idx], & user_index);
                        TmpJ1939RmUserAckPGNPtr = TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmUserAckPGNPtr;
                        for (pgn_idx = (uint32) 0; ((pgn_idx < TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmUserAckPGNNr) && (ValidId == (boolean) FALSE)); pgn_idx++)
                        {
                            if (Rx_PGN == TmpJ1939RmUserAckPGNPtr[pgn_idx])
                            {
                                /* Received Acknowledgement PGN (Rx_PGN) is configured to be handled */
                                ValidId = (boolean) TRUE;
                            }
                        }
                    }
                    if (ValidId != (boolean) TRUE)
                    {
                        ValidId = (boolean) FALSE;
                        user_index = 0;
                        for (usr_idx = (uint8) 0; ((usr_idx < TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeUserNr) && (ValidId == (boolean) FALSE)); usr_idx++)
                        {
                            (void) J1939Rm_ValidUser(TmpJ1939RmNodeUserRefPtr[usr_idx], & user_index);
                            /*Rx_PGN - Acknowledge the Requested PGN*/
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00029.Acknowledgement_Received,1 */
                            if (J1939Rm_ValidRmvRqstTSVQueue(Rx_PGN, (uint16) TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmUserId, channel_index, PduInfoPtr -> SduDataPtr[4], SA))
                            {
                                ValidId = (boolean) TRUE;

                                if (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserAckIndicationFctPtr != NULL_PTR)
                                {
                                    /* CanIf has sent priority left shifted by 2 bits. So right shift priority here again before calling User_AckIndication API */
                                    PrioByte = (uint8)(Priority >> 2);

                                    /* !LINKSTO EB_Ref.SWS_J1939Rm_00066.CDD,1 */
                                    /* !LINKSTO EB_Ref.SWS_J1939Rm_00066.RTE,1 */
                                    (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserAckIndicationFctPtr)
                                    (TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeId, /*node*/
                                     TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId, /*channel*/
                                     Rx_PGN, /*ackPgn*/
                                     (J1939Rm_AckCode) PduInfoPtr -> SduDataPtr[0], /*ackCode*/
                                     PduInfoPtr -> SduDataPtr[4], /*ackAddress*/
                                     SA, /*sourceAddress*/
                                     PrioByte /*priority*/
                                    );
                                }
                            }

                        }
                    }
                    else
                    {
                        if (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserAckIndicationFctPtr != NULL_PTR)
                        {
                            /* CanIf has sent priority left shifted by 2 bits. So right shift priority here again before calling User_AckIndication API */
                            PrioByte = (uint8)(Priority >> 2);

                            /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00027,1 */
                            /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00028,1 */
                            (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserAckIndicationFctPtr)
                            (TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeId, /*node*/
                             TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId, /*channel*/
                             Rx_PGN, /*ackPgn*/
                             (J1939Rm_AckCode) PduInfoPtr -> SduDataPtr[0], /*ackCode*/
                             PduInfoPtr -> SduDataPtr[4], /*ackAddress*/
                             SA, /*sourceAddress*/
                             PrioByte /*priority*/
                            );
                        }
                    }
                }
                else
                {
                    /*Destination Node is not configured to channel on which RxPduId is configured*/
                }
            }
            else
            {
                /*Invalid acknowledged address*/
            }
        }
    }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_Request_Reception_Handling
 *  Description          : Hanles the reception of Requests
 *  Parameters           : Input : PduIdType RxPduId
 *                         Input : PduInfoType *PduInfoPtr
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_Request_Reception_Handling( PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr)
{
    /*Local Variables*/
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg -> J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = & J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_RealStructType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr -> J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmChannelConstStructPtr;
    CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeConstStructPtr;
    CONSTP2CONST(J1939Rm_User_Const_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr -> J1939RmUserConstStructPtr;
    CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg -> J1939RmUserConstStructPtr;
    CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr -> J1939RmChannelRamStructPtr;
    P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;
#if (J1939RM_COM_SUPPORT == STD_ON)
    P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
#endif
    uint32 Rx_PGN = 0u;
    uint16 user_index = (uint16)0;
    uint8 pgn_index = (uint8)0;
    uint8 ndch_idx = 0u;
    uint8 channel_index = (uint8)0;
    uint8 node_index = (uint8)0;
    uint8 PrioByte = (uint8)0;
    boolean ValidId = (boolean)FALSE;
    boolean ValidPGN = (boolean)FALSE;
    boolean Rx_PGN_COMConfigured = (boolean)0;
    Std_ReturnType getMetaDataResult = (Std_ReturnType)E_NOT_OK;
    uint32 CanId;
    uint8 DA;
    uint8 SA;
    uint8 Priority;

    /*Search for RxPduId(J1939RmRqstRxPduId) in configured Channels to know the channel handling the Request*/
    ValidId = J1939Rm_ChIndx_ReceivedID(RxPduId ,&channel_index );
    if (ValidId != (boolean) TRUE)
    {
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        /*Invalid RxPduId*/
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_RxIndication,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.Det_ReportError,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_RXINDICATION_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID );
#endif
 }
    else

    {
        /*Rx_PGN - Received Requested PGN*/
        Rx_PGN = (((uint32) PduInfoPtr -> SduDataPtr[2] << 16) |
                  ((uint32) PduInfoPtr -> SduDataPtr[1] << 8) |
                  ((uint32) PduInfoPtr -> SduDataPtr[0]));

        ValidId = (boolean) FALSE;
        /* !LINKSTO J1939Rm.SWS_J1939Rm_00122,1*/
        getMetaDataResult = EcuC_GetMetaDataCanId((EcuC_PduIdType)(TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRqstRx_Ecuc_PduId), PduInfoPtr, & CanId);

            if (E_OK != getMetaDataResult)
            {
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
                /*Report DET Error*/
                /* !LINKSTO J1939Rm.EB.Invalid_MetaData,1 */
                (void) Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_RXINDICATION_SERVICEID, J1939RM_E_INVALID_METADATA_HANDLE);
#endif
            }

        DA = (uint8)(((uint32)CanId & 0x0000FF00U) >> 8);
        SA = (uint8)(CanId);
        Priority = (uint8)((uint32)(CanId & 0x1C000000U) >> 24);
        if(J1939RM_NULL_ADDRESS>SA)
        {
            J1939Rm_Check_Node_and_Pgn( Rx_PGN, DA, &ValidId, &ValidPGN, &pgn_index, &node_index, &Rx_PGN_COMConfigured, &user_index);

            if (ValidId == (boolean) TRUE)
            {
                if (ValidPGN == (boolean) TRUE)
                {
                    if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmState == J1939RM_STATE_ONLINE)
                    {
                        /*Check if Node on which User is configured is handled through the Channel Id*/
                        ValidId = (boolean) FALSE;
                        TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
                        for (ndch_idx = (uint8) 0; ((ndch_idx < TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr) && (ValidId == (boolean) FALSE)); ndch_idx++)
                        {
                            if (TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId == TmpJ1939RmNodeChannelRefPtr[ndch_idx])
                            {
                                ValidId = (boolean) TRUE;
                            }
                        }
                        if (ValidId == (boolean) TRUE)
                        {
                            if (Rx_PGN_COMConfigured != (boolean) TRUE)
                            {
                                /* Rx_PGN - Configured to be handled through J1939DCM, J1939NM, CDD or RTE*/
                                if (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserRequestIndicationFctPtr != NULL_PTR)
                                {
                                    /* CanIf has sent priority left shifted by 2 bits. So right shift priority here again before calling User_RequestIndication API */
                                    PrioByte = (uint8)((Priority) >> 2);
                                    (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserRequestIndicationFctPtr)
                                    (TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeId, /*nodeId*/
                                        TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId, /*channelId */
                                        Rx_PGN,     /*requestedPgn */
                                        SA,         /*sourceAddress*/
                                        DA,         /*destAddress  */
                                        PrioByte    /*priority     */
                                    );
                                }
                                else
                                {
                                    /*Request Indication is not configured*/
                                }
                            }
                            else
                            {
                                #if (J1939RM_COM_SUPPORT == STD_ON)
                                /*Rx_PGN - Configured to be handled through COM*/
                                TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmComIPduConstStructPtr;
                                /*Queue the Source address and Request type received (global/specific) received via Metadata of Received requests*/
                                /* Queue the Source address and Request type received (global/specific) received via Metadata of Received requests */
                                /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00005,1 */
                                (void) J1939Rm_Enqueue_COM_RQST(channel_index, (uint16) TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmUserId,
                                                                TmpJ1939RmComIPduConstStructPtr[pgn_index].J1939RmComIPduPGN,SA,DA);
                                if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation == J1939RM_NO_TX)
                                {
                                    /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_COM_RX,1 */
                                    TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation = J1939RM_COM_RX;
                                    /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00004,1 */
                                    (void)Com_TriggerIPDUSend(TmpJ1939RmComIPduConstStructPtr[pgn_index].J1939RmUpperComIPduRef);
                                }
                                #endif
                            }
                        }
                        else
                        {
                            /*Destination Node is not configured to channel on which RxPduId is configured*/
                        }
                    }
                    else
                    {
                        /*Only Address Claim PGs are Handled in OFFLINE STATE*/
                        /*Only Address Claimed PGs are handled in OFFLINE state*/
                        /* !LINKSTO J1939Rm.SWS_J1939Rm_00015,1 */
                            /*J1939RM_ADDR_CLAIM_PG_PGN = 0x0EE00*/
                            if ((Rx_PGN == J1939RM_ADDR_CLAIM_PG_PGN) && (Rx_PGN_COMConfigured == (boolean)0) && (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserRequestIndicationFctPtr != NULL_PTR))
                            {
                                /* CanIf has sent priority left shifted by 2 bits. So right shift priority here again before calling User_RequestIndication API */
                                PrioByte = (uint8)(Priority >> 2);
                                /* !LINKSTO EB_Ref.SWS_J1939Rm_00002.J1939Nm,1 */
                                /* !LINKSTO EB_Ref.SWS_J1939Rm_00002.J1939Dcm,1 */
                                /* !LINKSTO EB_Ref.SWS_J1939Rm_00002.CDD,1 */
                                /* !LINKSTO J1939Rm.SWS_J1939Rm_00003,1 */
                                /* !LINKSTO J1939Rm.SWS_J1939Rm_00116,1 */
                                (TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserRequestIndicationFctPtr)
                                (TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeId, /* node */
                                    TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId, /* channel */
                                    J1939RM_ADDR_CLAIM_PG_PGN, /* requestedPgn  */
                                    SA, /* sourceAddress */
                                    DA, /* destAddress */
                                    PrioByte /* priority */
                                );
                            }
                    }
                }
                else
                {
                    /*Rx_PGN - Not configured*/
                    if (DA != J1939RM_BROADCAST_ADDR)
                    {
                        /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00008,1 */
                        /* !LINKSTO EB_Ref.SWS_J1939Rm_00008.RequestedPGN_NotConfigured,1 */
                        /*Send NACK!!!*/
                        (void) J1939Rm_Enqueue_TXPG_ACKM(
                            channel_index,                                                   /*Derive the Queue to be updated based on channel index and QueueType*/
                            (uint16) TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmUserId, /*First user ID in valid node.*/
                            Rx_PGN,                                                          /*PGN of the Requested PG.*/
                            (uint8) J1939RM_ACK_NEGATIVE,                                    /*Type of acknowledgement for Ackm.*/
                            SA,                                                              /*Address to be Aknowledged (Address of the node that sent the request).*/
                            Priority                                                        /*Priority of the Requested PG.*/
                        );
                    }
                }
            }
            else
            {
                /*Invalid Node address*/
            }
        }
        else
        {
            /*Do nothing, Source address is 0xFF or 0xFE : config error, invalid*/
        }
    }

}


/* *****************************************************************************
 *  Name                 : J1939Rm_ValidChannel
 *  Description          : Check if channel is configured for channel id.
 *  Parameters           : Input : NetworkHandleType channel
 *                         Input : uint8 *channel_index
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidChannel( NetworkHandleType channel,P2VAR(uint8,AUTOMATIC,J1939RM_APPL_DATA) channel_index )
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr->J1939RmChannelConstStructPtr;
  uint8 ch_idx = 0u;
  boolean ValidId = (boolean)FALSE;

  for (ch_idx= (uint8)0; ((ch_idx < TmpJ1939RmConfigPtr->J1939RmChannelNr) && (ValidId == (boolean)FALSE)); ch_idx++)
  {
    if (TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmChannelId == channel)
    {
      *channel_index = ch_idx;
      ValidId = (boolean)TRUE;
    }
  }
  return ValidId;
}

/* *****************************************************************************
 *  Name                 : J1939Rm_ValidNode
 *  Description          : Check if node is configured with user having user id.
 *  Parameters           : Input : uint16 UserId
 *                         Input : uint8 *node_index
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidNode( uint16 UserId,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) node_index)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr->J1939RmNodeConstStructPtr;
  P2CONST(uint16, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeUserRefPtr;
  uint8 nd_idx = 0u;
  uint8 usr_idx = 0u;
  boolean ValidId = (boolean)FALSE;

  for (nd_idx= (uint8)0; ((nd_idx<TmpJ1939RmConfigPtr->J1939RmNodeNr)&&(ValidId == (boolean)FALSE)); nd_idx++)
  {
    TmpJ1939RmNodeUserRefPtr = TmpJ1939RmNodeConstStructPtr[nd_idx].J1939RmNodeUserRefPtr;
    for (usr_idx= (uint8)0; ((usr_idx<TmpJ1939RmNodeConstStructPtr[nd_idx].J1939RmNodeUserNr)&&(ValidId == (boolean)FALSE)); usr_idx++)
    {
      if (TmpJ1939RmNodeUserRefPtr[usr_idx] == UserId)
      {
        *node_index = nd_idx;
        ValidId = (boolean)TRUE;
      }
    }
  }
  return ValidId;
}

/* *****************************************************************************
 *  Name                 : J1939Rm_ValidUser
 *  Description          : Check if user is configured with user id.
 *  Parameters           : Input : uint16 UserId
 *                         Input : uint16 *user_index
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidUser( uint16 UserId,P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) user_index)
{
  /*Local Variables*/
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr->J1939RmUserConstStructPtr;
  uint8 usr_idx  = 0u;
  boolean ValidId = (boolean)FALSE;

  for (usr_idx= (uint8)0; ((usr_idx<TmpJ1939RmConfigPtr->J1939RmUserNr)&&(ValidId == (boolean)FALSE)); usr_idx++)
  {
    if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserId == UserId)
    {
      *user_index = usr_idx;
      ValidId = (boolean)TRUE;
    }
  }
  return ValidId;
}

#if (J1939RM_SENDREQUEST_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_Enqueue_TXPG_RQST
 *  Description          : Enqueue data into the TXPG_RQST Queue.
 *  Parameters           : Input : uint8 channel_index
 *                         Input : uint16 QueueUserId
 *                         Input : uint32 QueuePgn
 *                         Input : uint8 QueueSA
 *                         Input : uint8 QueueDA
 *                         Input : uint8 QueuePriority
 *                         Input : boolean QueuecheckTimeout
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_TXPG_RQST( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueSA, uint8 QueueDA, uint8 QueuePriority, boolean QueuecheckTimeout)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  P2VAR(J1939Rm_RqstTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTxQueueTypePtr;
  P2VAR(J1939Rm_RqstTxQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTxQueueDataPtr;
  uint8 TmpJ1939RmRequestQueueSize = 0u;
  uint8 rear = 0u;
  uint8 front = 0u;
  uint8 queuesize = 0u;
  uint8 priobasedentry = 0u;
  boolean prioritycheck = (boolean)0;
  Std_ReturnType TmpResult = E_OK;

  /*RQST Queue Handling*/
  TmpJ1939RmRqstTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTxQueueTypeStructPtr;
  TmpJ1939RmRequestQueueSize = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestQueueSize;

  if (TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount < TmpJ1939RmRequestQueueSize)
  {
    front = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront;
    TmpJ1939RmRqstTxQueueDataPtr = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueDataPtr;

    /* Rearrange the queue to set front to zero, when rear has reached maximum count index. */
    if((TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront != (uint8)0) && (TmpJ1939RmRequestQueueSize != (uint8)0) &&
        ( (TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear) >= (TmpJ1939RmRequestQueueSize - (uint8)1)) )
    {
      for (queuesize=0;queuesize<TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount;queuesize++)
      {
        TmpJ1939RmRqstTxQueueDataPtr[queuesize] = TmpJ1939RmRqstTxQueueDataPtr[queuesize + front];
      }
      /* Update Queue Front and Rare */
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront = (uint8)0;
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear = (queuesize - (uint8)1);
    }

    /*Enqueue data based on priority*/
    /*Increment Rear, using modulo arithmetic*/
    TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear = (TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear +  (uint8)1) % TmpJ1939RmRequestQueueSize;
    /*Sort and insert based on Priority*/
    rear = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear;
    /*Sort based on Priority*/
    priobasedentry = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront;
    for (queuesize=rear; ((queuesize!=TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront) && (prioritycheck == (boolean)0)); queuesize--)
    {
      if (QueuePriority >= TmpJ1939RmRqstTxQueueDataPtr[queuesize - (uint8)1].J1939RmRqstPriority)
      {
        prioritycheck = (boolean)1;
        priobasedentry = queuesize;
      }
    }
    for (queuesize=rear;queuesize>priobasedentry;queuesize--)
    {
      TmpJ1939RmRqstTxQueueDataPtr[queuesize] = TmpJ1939RmRqstTxQueueDataPtr[queuesize- (uint8)1];
    }
    /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00024,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Rm_00024.SendRequest,1 */
    /*Insert Data based on priority into Queue*/
    TmpJ1939RmRqstTxQueueDataPtr[priobasedentry].J1939RmRqstUserId = QueueUserId;
    TmpJ1939RmRqstTxQueueDataPtr[priobasedentry].J1939RmRqstPgn = QueuePgn;
    TmpJ1939RmRqstTxQueueDataPtr[priobasedentry].J1939RmRqstSA = QueueSA;
    TmpJ1939RmRqstTxQueueDataPtr[priobasedentry].J1939RmRqstDA = QueueDA;
    TmpJ1939RmRqstTxQueueDataPtr[priobasedentry].J1939RmRqstPriority = QueuePriority;
    TmpJ1939RmRqstTxQueueDataPtr[priobasedentry].J1939RmRqstcheckTimeout = QueuecheckTimeout;
    /*Increment count*/
    TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount + (uint8)1;
  }
  else
  {
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00068,1 */
    /*On Overflow - Empty Queue*/
    TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront =  (uint8)0;
    TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear = TmpJ1939RmRequestQueueSize- (uint8)1;
    TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount =  (uint8)0;
    TmpResult = E_NOT_OK;
  }
  return TmpResult;
}
#endif

/* *****************************************************************************
 *  Name                 : J1939Rm_Enqueue_TXPG_ACKM
 *  Description          : Enqueue data into the TXPG_ACKM Queue.
 *  Parameters           : Input : uint8 channel_index
 *                         Input : uint16 QueueUserId
 *                         Input : uint32 QueuePgn
 *                         Input : uint8 QueueAckCode
 *                         Input : uint8 QueueAckAddress
 *                         Input : uint8 QueuePriority
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_TXPG_ACKM( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueAckCode, uint8 QueueAckAddress, uint8 QueuePriority )
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  P2VAR(J1939Rm_AckmTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmAckmTxQueueTypePtr;
  P2VAR(J1939Rm_AckmTxQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmAckmTxQueueDataPtr;

  uint8 TmpJ1939RmAckQueueSize = 0u;
  uint8 rear = 0u;
  uint8 front = 0u;
  uint8 queuesize = 0u;
  uint8 priobasedentry = 0u;
  boolean prioritycheck = (boolean)0;
  Std_ReturnType TmpResult = E_OK;

  /*ACKM Queue Handling*/
  TmpJ1939RmAckmTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmAckmTxQueueTypeStructPtr;
  TmpJ1939RmAckQueueSize = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmAckQueueSize;
  if (TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount < TmpJ1939RmAckQueueSize)
  {
    front = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront;
    TmpJ1939RmAckmTxQueueDataPtr = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueDataPtr;

    /* Rearrange the queue to set front to zero, when rear has reached maximum count index. */
    if((TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront != (uint8)0) && (TmpJ1939RmAckQueueSize != (uint8)0) &&
        ( (TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear) >= (TmpJ1939RmAckQueueSize - (uint8)1)) )
    {
        for (queuesize=0;queuesize<TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount;queuesize++)
        {
          TmpJ1939RmAckmTxQueueDataPtr[queuesize] = TmpJ1939RmAckmTxQueueDataPtr[queuesize + front];
        }
        /* Update Queue Front and Rare */
        TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront = (uint8)0;
        TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear = (queuesize - (uint8)1);
    }

    /*Enqueue data based on priority*/
    /*Increment Rear, using modulo arithmetic*/
    TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear = (TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear +  (uint8)1) % TmpJ1939RmAckQueueSize;
    /*Sort and insert based on Priority*/
    rear = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear;
    /*Sort based on Priority*/
    priobasedentry = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront;
    for (queuesize=rear; ((queuesize!=TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront) && (prioritycheck == (boolean)0)); queuesize--)
    {
      /* When we get QueuePriority for ACK PG, it is left shifted by 2 bits. Therefore we have to right shift QueuePriority before checking it against J1939RmAckmPriority*/
      if ( QueuePriority >= (TmpJ1939RmAckmTxQueueDataPtr[queuesize - (uint8)1].J1939RmAckmPriority))
      {
        prioritycheck = (boolean)1;
        priobasedentry = queuesize;
      }
    }
    for (queuesize=rear;queuesize>priobasedentry;queuesize--)
    {
      TmpJ1939RmAckmTxQueueDataPtr[queuesize] = TmpJ1939RmAckmTxQueueDataPtr[queuesize- (uint8)1];
    }
    /*Insert Data based on priority into Queue*/
    TmpJ1939RmAckmTxQueueDataPtr[priobasedentry].J1939RmAckmUserId = QueueUserId;
    TmpJ1939RmAckmTxQueueDataPtr[priobasedentry].J1939RmAckmPgn = QueuePgn;
    TmpJ1939RmAckmTxQueueDataPtr[priobasedentry].J1939RmAckmCode = QueueAckCode;
    TmpJ1939RmAckmTxQueueDataPtr[priobasedentry].J1939RmAckmAddr = QueueAckAddress;
    TmpJ1939RmAckmTxQueueDataPtr[priobasedentry].J1939RmAckmPriority = QueuePriority;
    /*Increment count*/
    TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount + (uint8)1;
  }
  else
  {
    /*On Overflow - Empty Queue*/
    TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront = (uint8)0;
    TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear = TmpJ1939RmAckQueueSize - (uint8)1;
    TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount = (uint8)0;
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00071,1 */
    TmpResult = E_NOT_OK;
  }
  return TmpResult;
}

/* *****************************************************************************
 *  Name                 : J1939Rm_Enqueue_TSV_RQST
 *  Description          : Enqueue data into the TSV_RQST Queue.
 *  Parameters           : Input : uint8 channel_index
 *                         Input : uint16 QueueUserId
 *                         Input : uint32 QueuePgn
 *                         Input : uint8 QueueSA
 *                         Input : uint8 QueueDA
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_TSV_RQST( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueSA, uint8 QueueDA)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  P2VAR(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueTypeStructPtr;
  P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;
  uint8 TmpJ1939RmRequestTimeoutMonitors = 0u;
  uint8 rear = 0u;
  Std_ReturnType TmpResult = E_OK;


  /*RQST TSV Queue Handling*/
  TmpJ1939RmRqstTSQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTSQueueTypeStructPtr;
  TmpJ1939RmRequestTimeoutMonitors = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestTimeoutMonitors;
  if (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount < TmpJ1939RmRequestTimeoutMonitors)
  {
    /*Enqueue data*/
    /*Increment Rear, using modulo arithmetic*/
    TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear = (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear + (uint8)1) % TmpJ1939RmRequestTimeoutMonitors;

    /*Insert Data based on priority into Queue*/
    rear = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear;
    TmpJ1939RmRqstTSQueueDataStructPtr = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;

    TmpJ1939RmRqstTSQueueDataStructPtr[rear].J1939RmRqstUserId = QueueUserId;
    TmpJ1939RmRqstTSQueueDataStructPtr[rear].J1939RmRqstPgn = QueuePgn;
    TmpJ1939RmRqstTSQueueDataStructPtr[rear].J1939RmRqstSA = QueueSA;
    TmpJ1939RmRqstTSQueueDataStructPtr[rear].J1939RmRqstDA = QueueDA;
    TmpJ1939RmRqstTSQueueDataStructPtr[rear].J1939RmTimeoutSupervisionTimer = TmpJ1939RmConfigPtr_Pbcfg->J1939RmTimeoutSupervision;
    TmpJ1939RmRqstTSQueueDataStructPtr[rear].J1939RmTimeoutSupervisionEnable = (boolean)TRUE;
    /*Increment count*/
    TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount + (uint8)1;
  }
  else
  {
    /*Overflow*/
    TmpResult = E_NOT_OK;
  }
  return TmpResult;
}

#if (J1939RM_COM_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_Enqueue_COM_RQST
 *  Description          : Enqueue data into the COM_RQST Queue.
 *  Parameters           : Input : uint8 channel_index
 *                         Input : uint16 QueueUserId
 *                         Input : uint32 QueuePgn
 *                         Input : uint8 QueueSA
 *                         Input : uint8 QueueDA
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Enqueue_COM_RQST( uint8 channel_index, uint16 QueueUserId, uint32 QueuePgn, uint8 QueueSA, uint8 QueueDA)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
  CONSTP2VAR(J1939Rm_ComIpduRqstQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIpduRqstQueueTypeStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmComIpduRqstQueueTypeStructPtr;
  P2VAR(J1939Rm_ComIpduRqstQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmComIpduRqstQueueDataPtr;

  uint8 TmpJ1939RmUserComIPduRequestQueueSize = 0u;
  uint16 user_index = 0u;
  uint8 rear = 0u;
  Std_ReturnType TmpResult = E_OK;

  /*COM RQST Handling*/
  (void)J1939Rm_ValidUser(QueueUserId, &user_index);
  TmpJ1939RmUserComIPduRequestQueueSize = TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserComIPduRequestQueueSize;
  if (TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueCount < TmpJ1939RmUserComIPduRequestQueueSize)
  {
    /*Enqueue data*/
    /*Increment Rear, using modulo arithmetic*/
    TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear = (TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear + (uint8)1) % TmpJ1939RmUserComIPduRequestQueueSize;
    /*Insert Data into Queue*/
    rear = TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear;
    TmpJ1939RmComIpduRqstQueueDataPtr = TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueDataPtr;
    TmpJ1939RmComIpduRqstQueueDataPtr[rear].J1939RmComIpduRqstPgn = QueuePgn;
    TmpJ1939RmComIpduRqstQueueDataPtr[rear].J1939RmComIpduRqstUserId = QueueUserId;
    TmpJ1939RmComIpduRqstQueueDataPtr[rear].J1939RmComIpduRqstSA = QueueSA;
    TmpJ1939RmComIpduRqstQueueDataPtr[rear].J1939RmComIpduRqstDA = QueueDA;
    TmpJ1939RmComIpduRqstQueueDataPtr[rear].J1939RmComIpduRqstChannelId = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId;
    /*Increment count*/
    TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueCount = TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueCount + (uint8)1;
  }
  else
  {
    /*Overflow*/
    TmpResult = E_NOT_OK;
  }
  return TmpResult;
}
#endif

/* *****************************************************************************
 *  Name                 : J1939Rm_TXPG_RQST_QueueTop
 *  Description          : return data from TXPG_RQST Queue without changing the queue itself.
 *  Parameters           : Input : uint8 channel_index
 *                         Input : uint16 *QueueUserId
 *                         Input : uint32 *QueuePgn
 *                         Input : uint8 *QueueSA
 *                         Input : uint8 *QueueDA
 *                         Input : uint8 *QueuePriority
 *                         Input : boolean *QueuecheckTimeout
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_TXPG_RQST_QueueTop( uint8 channel_index,P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) QueueUserId,P2VAR(uint32, AUTOMATIC,J1939RM_APPL_DATA) QueuePgn,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueSA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueDA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueuePriority,P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) QueuecheckTimeout)
{
    /*Local Variables*/
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
    P2CONST(J1939Rm_RqstTxQueueData_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmRqstTxQueueDataPtr;
    uint8 front = 0u;
    P2VAR(J1939Rm_RqstTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTxQueueTypePtr;

    /*RQST Queue Handling*/
    TmpJ1939RmRqstTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTxQueueTypeStructPtr;
    TmpJ1939RmRqstTxQueueDataPtr = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueDataPtr;

    front = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront;
    /*Read Data from the Queue*/
    *QueueUserId = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstUserId;
    *QueuePgn = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstPgn;
    *QueueSA = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstSA;
    *QueueDA = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstDA;
    *QueuePriority = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstPriority;
    *QueuecheckTimeout = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstcheckTimeout;

}


/* *****************************************************************************
 *  Name                 : J1939Rm_Dequeue
 *  Description          : Dequeue data from the Queue.
 *  Parameters           : Input : uint8 QueueType
 *                         Input : uint8 channel_index
 *                         Input : uint16 *QueueUserId
 *                         Input : uint32 *QueuePgn
 *                         Input : uint8 *QueueSA
 *                         Input : uint8 *QueueDA
 *                         Input : uint8 *QueuePriority
 *                         Input : boolean *QueuecheckTimeout
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_Dequeue( uint8 QueueType, uint8 channel_index,P2VAR(uint16, AUTOMATIC,J1939RM_APPL_DATA) QueueUserId,P2VAR(uint32, AUTOMATIC,J1939RM_APPL_DATA) QueuePgn,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueSA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueDA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueuePriority,P2VAR(boolean, AUTOMATIC,J1939RM_APPL_DATA) QueuecheckTimeout)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  P2CONST(J1939Rm_RqstTxQueueData_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmRqstTxQueueDataPtr;
  P2CONST(J1939Rm_AckmTxQueueData_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmAckmTxQueueDataPtr;

  uint8 TmpJ1939RmRequestQueueSize = 0u;
  uint8 TmpJ1939RmAckQueueSize = 0u;
  uint8 TmpJ1939RmRequestTimeoutMonitors = 0u;
  uint8 front = 0u;

  P2VAR(J1939Rm_RqstTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTxQueueTypePtr;
  P2VAR(J1939Rm_AckmTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmAckmTxQueueTypePtr;
  P2VAR(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueTypeStructPtr;
  P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;

  switch (QueueType)
  {
    case J1939RM_TXPG_RQST:
    {
      /*RQST Queue Handling*/
      TmpJ1939RmRqstTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTxQueueTypeStructPtr;
      TmpJ1939RmRqstTxQueueDataPtr = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueDataPtr;
      TmpJ1939RmRequestQueueSize = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestQueueSize;

      front = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront;
      /*Read Data from the Queue*/
      *QueueUserId = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstUserId;
      *QueuePgn = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstPgn;
      *QueueSA = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstSA;
      *QueueDA = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstDA;
      *QueuePriority = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstPriority;
      *QueuecheckTimeout = TmpJ1939RmRqstTxQueueDataPtr[front].J1939RmRqstcheckTimeout;
      /*Increment Front, using modulo arithmetic*/
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront = (front + (uint8)1) % TmpJ1939RmRequestQueueSize;
      /*Decrement count*/
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount = TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount - (uint8)1;

      break;
    }

    case J1939RM_TXPG_ACKM:
    {
      /*ACKM Queue Handling*/
      TmpJ1939RmAckmTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmAckmTxQueueTypeStructPtr;
      TmpJ1939RmAckmTxQueueDataPtr = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueDataPtr;
      TmpJ1939RmAckQueueSize = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmAckQueueSize;

      front = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront;
      /*Read Data from the Queue*/
      *QueueUserId = TmpJ1939RmAckmTxQueueDataPtr[front].J1939RmAckmUserId;
      *QueuePgn = TmpJ1939RmAckmTxQueueDataPtr[front].J1939RmAckmPgn;
      *QueueSA = TmpJ1939RmAckmTxQueueDataPtr[front].J1939RmAckmCode;
      *QueueDA = TmpJ1939RmAckmTxQueueDataPtr[front].J1939RmAckmAddr;
      *QueuePriority = TmpJ1939RmAckmTxQueueDataPtr[front].J1939RmAckmPriority;
      /*Increment Front, using modulo arithmetic*/
      TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront = (front + (uint8)1) % TmpJ1939RmAckQueueSize;
      /*Decrement count*/
      TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount = TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount - (uint8)1;

      break;
    }

    default:
    {
      /*RQST TSV Queue Handling*/

      TmpJ1939RmRqstTSQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTSQueueTypeStructPtr;
      TmpJ1939RmRqstTSQueueDataStructPtr = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;
      TmpJ1939RmRequestTimeoutMonitors = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestTimeoutMonitors;

      front = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront;
      /*Read Data from the Queue*/
      *QueueUserId = TmpJ1939RmRqstTSQueueDataStructPtr[front].J1939RmRqstUserId;
      *QueuePgn = TmpJ1939RmRqstTSQueueDataStructPtr[front].J1939RmRqstPgn;
      *QueueSA = TmpJ1939RmRqstTSQueueDataStructPtr[front].J1939RmRqstSA;
      *QueueDA = TmpJ1939RmRqstTSQueueDataStructPtr[front].J1939RmRqstDA;
      *QueuePriority = (uint8)0;
      TmpJ1939RmRqstTSQueueDataStructPtr[front].J1939RmTimeoutSupervisionEnable = (boolean)FALSE;
      /*Increment Front, using modulo arithmetic*/
      TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront = (front + (uint8)1) % TmpJ1939RmRequestTimeoutMonitors;
      /*Decrement count*/
      TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount - (uint8)1;
      break;
    }
  }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_Flush
 *  Description          : Flush data from Queue.
 *  Parameters           : Input : uint8 QueueType
 *                         Input : uint8 channel_index
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(void, J1939RM_CODE) J1939Rm_Flush( uint8 QueueType, uint8 channel_index)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  uint8 TmpJ1939RmRequestQueueSize = 0u;
  uint8 TmpJ1939RmAckQueueSize = 0u;
  P2VAR(J1939Rm_RqstTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTxQueueTypePtr;
  P2VAR(J1939Rm_AckmTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmAckmTxQueueTypePtr;

  switch (QueueType)
  {
    case J1939RM_TXPG_RQST:
    {
      /*Flush Rqst Queue*/
      TmpJ1939RmRqstTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTxQueueTypeStructPtr;
      TmpJ1939RmRequestQueueSize = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestQueueSize;
      /*Empty Rqst Queue*/
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueFront = (uint8)0;
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueRear = TmpJ1939RmRequestQueueSize - (uint8)1;
      TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount = (uint8)0;
      break;
    }

    default:
    {
      /*Flush Ackm Queue*/
      TmpJ1939RmAckmTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmAckmTxQueueTypeStructPtr;
      TmpJ1939RmAckQueueSize = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmAckQueueSize;
      /*Empty Ackm Queue*/
      TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueFront = (uint8)0;
      TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueRear = TmpJ1939RmAckQueueSize - (uint8)1;
      TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount = (uint8)0;
      break;
    }
  }
}

/* *****************************************************************************
 *  Name                 : J1939Rm_ValidRmvRqstTSVQueue
 *  Description          : Validate RQST and if exists in TSV Queue.
 *                         Remove the entry for the same from the queue.
 *  Parameters           : Input : uint32 PGN
 *                         Input : uint16 user_id
 *                         Input : uint8 channel_index
 *                         Input : uint8 node_addr
 *                         Input : uint8 dest_addr
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidRmvRqstTSVQueue( uint32 PGN, uint16 user_id, uint8 channel_index, uint8 node_addr, uint8 dest_addr)
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
  CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
  P2VAR(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueTypeStructPtr;
  P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;

  uint8 TmpJ1939RmRequestTimeoutMonitors = 0u;
  uint8 queue_idx = 0u;
  uint8 queue_index = (uint8)0;
  boolean Valid = (boolean)FALSE;

  /*Validate the userid, PGN, Source and destination address */
  TmpJ1939RmRqstTSQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTSQueueTypeStructPtr;
  TmpJ1939RmRqstTSQueueDataStructPtr = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;
  TmpJ1939RmRequestTimeoutMonitors = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestTimeoutMonitors;

  if (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount != (uint8)0)
  {
    for (queue_idx = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront; ((queue_idx != TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear) && (Valid == (boolean)FALSE)); queue_idx= (queue_idx+ (uint8)1)% TmpJ1939RmRequestTimeoutMonitors)
    {
      if (
          ((user_id == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstUserId)
              && (PGN == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstPgn))
              && ((node_addr == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstSA)
              && (dest_addr == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstDA))
        )
      {
        queue_index = queue_idx;
        Valid = (boolean)TRUE;
      }
      else
      {

      }
    }
    if (Valid == (boolean)FALSE) /*Check for last entry in queue*/
    {
      if (((user_id == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstUserId) && (PGN == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstPgn))
      && ((node_addr == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstSA) && (dest_addr == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstDA)))
      {
        queue_index = queue_idx;
        Valid = (boolean)TRUE;
      }
      else
      {
        /*No suitable entry found in the list of pending requests*/
      }
    }
  }
  else
  {
      /*Rqst TSV Queue is Empty*/
  }

  if (Valid == (boolean)TRUE)
  {
    /*Remove RQST from RQST TSV Queue*/
    for (queue_idx = queue_index; queue_idx != TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear; queue_idx++)
    {
      TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx] = TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx + (uint8)1];
    }
    TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmTimeoutSupervisionEnable = (boolean)FALSE;
    TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount - (uint8)1;
    TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear = (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear + TmpJ1939RmRequestTimeoutMonitors - (uint8)1)%TmpJ1939RmRequestTimeoutMonitors;
  }
  return Valid;
}

#if (J1939RM_COM_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_ValidRmvRqstCOMQueue
 *  Description          : Validate COM PGN and if exists in COM Queue.
 *                         Remove the entry for the same from the queue.
 *  Parameters           : Input : uint32 PGN
 *                         Input : uint16 user_index
 *                         Input : uint8 *QueueSA
 *                         Input : uint8 *QueueDA
 *                         Input : uint8 *QueueChannelId
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
static FUNC(boolean, J1939RM_CODE) J1939Rm_ValidRmvRqstCOMQueue( uint32 PGN, uint16 user_index,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueSA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueDA,P2VAR(uint8, AUTOMATIC,J1939RM_APPL_DATA) QueueChannelId )
{
  /*Local Variables*/
  CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
  CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
  CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
  CONSTP2VAR(J1939Rm_ComIpduRqstQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIpduRqstQueueTypeStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmComIpduRqstQueueTypeStructPtr;
  CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
  P2VAR(J1939Rm_ComIpduRqstQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmComIpduRqstQueueDataPtr;
  uint8 TmpJ1939RmUserComIPduRequestQueueSize = 0u;
  uint8 queue_idx = 0u;
  uint8 queue_index = (uint8)0;
  boolean Valid = (boolean)FALSE;
  TmpJ1939RmComIpduRqstQueueDataPtr = TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueDataPtr;
  TmpJ1939RmUserComIPduRequestQueueSize = TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserComIPduRequestQueueSize;

  /*Validate the PGN*/
    for (queue_idx= (uint8)0; ((queue_idx != TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear) && (Valid==(boolean)FALSE)); queue_idx=(queue_idx+ (uint8)1)%TmpJ1939RmUserComIPduRequestQueueSize)
    {
      if (PGN == TmpJ1939RmComIpduRqstQueueDataPtr[queue_idx].J1939RmComIpduRqstPgn)
      {
        queue_index = queue_idx;
        Valid = (boolean)TRUE;
      }
      else
      {

      }
    }
    if (Valid == (boolean)FALSE) /*Check for last entry in queue*/
    {
      if (PGN == TmpJ1939RmComIpduRqstQueueDataPtr[queue_idx].J1939RmComIpduRqstPgn)
      {
        queue_index = queue_idx;
        Valid = (boolean)TRUE;
      }
      else
      {
          /*No suitable entry found in the COM queue*/
      }
    }
    else
    {
        /* Valid entry found in the COM queue*/
    }

  if (Valid == (boolean)TRUE)
  {
    /*Remove COM RQST from COM Queue*/
    *QueueSA = TmpJ1939RmComIpduRqstQueueDataPtr[queue_index].J1939RmComIpduRqstSA;
    *QueueDA = TmpJ1939RmComIpduRqstQueueDataPtr[queue_index].J1939RmComIpduRqstDA;
    *QueueChannelId = TmpJ1939RmComIpduRqstQueueDataPtr[queue_index].J1939RmComIpduRqstChannelId;
    for (queue_idx = queue_index; queue_idx != TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear; queue_idx++)
    {
        TmpJ1939RmComIpduRqstQueueDataPtr[queue_idx] = TmpJ1939RmComIpduRqstQueueDataPtr[queue_idx+ (uint8)1];
    }
    TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueCount = TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueCount - (uint8)1;
    TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear = (TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueRear + TmpJ1939RmUserComIPduRequestQueueSize -  (uint8)1)%TmpJ1939RmUserComIPduRequestQueueSize;
  }
  return Valid;
}
#endif

#define J1939RM_STOP_SEC_CODE
#include <J1939Rm_MemMap.h>

#define J1939RM_START_SEC_CODE
#include <J1939Rm_MemMap.h>
/*Public Functions*/

/* !LINKSTO J1939Rm.SWS_J1939Rm_00037,1 */
/* *****************************************************************************
 *  Name                 : J1939Rm_Init
 *  Description          : This function initializes the J1939 Request Manager.
 *  Parameters           : Input : J1939Rm_ConfigType *ConfigPtr
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939RM_CODE) J1939Rm_Init(P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) ConfigPtr)
{
  if (J1939Rm_Initialized == (boolean)FALSE)
  {
    /*Local Variables*/
    P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg ;
    P2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg;
    P2VAR(J1939Rm_GlobalConfig_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmGlobalConfigPtr;
    P2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmChannelRamStructPtr;
    P2VAR(J1939Rm_AckmTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmAckmTxQueueTypeStructPtr;
    P2VAR(J1939Rm_RqstTxQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTxQueueTypeStructPtr;
    P2VAR(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueTypeStructPtr;
    P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;
    P2VAR(J1939Rm_ComIpduRqstQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmComIpduRqstQueueTypeStructPtr;
    P2CONST(J1939Rm_RealStructType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr;
    P2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr;
    P2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr;
    uint16 queueStartIndex;
    uint8 TmpJ1939RmRequestTimeoutMonitors = 0u;
    uint8 usr_idx = 0u;
    uint8 ch_idx = 0u;
    uint8 time_idx = 0u;
    uint8 AckmTxQueueData_idx = 0u;
    uint8 RqstTxQueueData_idx = 0u;
    uint8 RqstTSQueueData_idx = 0u;
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    uint16 FiftyMSSupervision = 0u;
#endif
    P2CONST(J1939Rm_ConfigType,AUTOMATIC,J1939RM_APPL_DATA) LocalConfigPtr = ConfigPtr;
    J1939Rm_ValidateConfig(LocalConfigPtr);
    if(J1939Rm_PbCfg_Ptr != NULL_PTR)
    {
       /* Store the global RAM structure locally*/
       TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
       TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
       TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
       /* Store the configuration address in the global configuration pointer */
       TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr = &J1939Rm_Cfg_J1939RmConfig;
       TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr;
       /*Store the Channel Ram structure */
       TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr = TmpJ1939RmConfigPtr->J1939Rm_GlobalChannel_Ram_StructPtr;
       TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
       /* J1939RmRqstTxQueueType, J1939RmRqstTxDataType and J1939RmRqstTSQueueType, J1939RmRqstTSDataType structures */
       TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
       for (ch_idx= (uint8)0;ch_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelNr;ch_idx++)
       {
         /*Store the J1939RmAckmTxQueueType structure */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmAckmTxQueueTypeStructPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalAckmTxQueueType_StructPtr[ch_idx]);
         /*Store the J1939RmAckmTxQueueData structure */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmAckmTxQueueTypeStructPtr->J1939RmAckmTxQueueDataPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalAckmTxQueueData_StructPtr[AckmTxQueueData_idx]);
         /*Store the J1939RmRqstTxQueueType structure */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTxQueueTypeStructPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalRqstTxQueueType_StructPtr[ch_idx]);
         /*Store the J1939RmRqstTxQueueData structure */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTxQueueTypeStructPtr->J1939RmRqstTxQueueDataPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalRqstTxQueueData_StructPtr[RqstTxQueueData_idx]);
         /*Store the J1939RmRqstTSQueueType structure */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTSQueueTypeStructPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalRqstTSQueueType_StructPtr[ch_idx]);
         /*Store the J1939RmRqstTSQueueData structure */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalRqstTSQueueData_StructPtr[RqstTSQueueData_idx]);
         AckmTxQueueData_idx += TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckQueueSize ;
         RqstTxQueueData_idx += TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRequestQueueSize ;
         RqstTSQueueData_idx += TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRequestTimeoutMonitors;
       }
       /*Store the ComIpduRqstQueueType Ram structure */
       TmpJ1939RmGlobalConfigPtr->J1939RmComIpduRqstQueueTypeStructPtr = TmpJ1939RmConfigPtr->J1939Rm_GlobalComIpduRqstQueueType_StructPtr;
       TmpJ1939RmComIpduRqstQueueTypeStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmComIpduRqstQueueTypeStructPtr;
       /*Store the ComIpduRqstDataType structures*/
       TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
       queueStartIndex =0;
       for (usr_idx= (uint8)0;usr_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr;usr_idx++)
       {
         if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
         {
           /*Store the memory for the ComIpduRqstQueueData structure */
           TmpJ1939RmComIpduRqstQueueTypeStructPtr[usr_idx].J1939RmComIpduRqstQueueDataPtr = &(TmpJ1939RmConfigPtr->J1939Rm_GlobalComIpduRqstQueueData_StructPtr[queueStartIndex]);
           queueStartIndex = queueStartIndex + TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserComIPduRequestQueueSize;
         }
       }
       /* !LINKSTO EB_Ref.SWS_J1939Rm_00012.InternalVariables,1 */
       /*Initialize RAM Structures elements*/
       for (ch_idx= (uint8)0; ch_idx < TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelNr; ch_idx++)
       {
         /*AckmTxQueue Initialization*/
         TmpJ1939RmAckmTxQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmAckmTxQueueTypeStructPtr;
         TmpJ1939RmAckmTxQueueTypeStructPtr->J1939RmAckmTxQueueFront = (uint8)0;
         if (TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckQueueSize > (uint8)0)
         {
           TmpJ1939RmAckmTxQueueTypeStructPtr->J1939RmAckmTxQueueRear = TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckQueueSize - (uint8)1;
         }
         else
         {
           TmpJ1939RmAckmTxQueueTypeStructPtr->J1939RmAckmTxQueueRear = (uint8)0;
         }
         TmpJ1939RmAckmTxQueueTypeStructPtr->J1939RmAckmTxQueueCount = (uint8)0;
         /*RqstTxQueue Initialization*/
         TmpJ1939RmRqstTxQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTxQueueTypeStructPtr;
         TmpJ1939RmRqstTxQueueTypeStructPtr->J1939RmRqstTxQueueFront = (uint8)0;
         if (TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRequestQueueSize > (uint8)0)
         {
           TmpJ1939RmRqstTxQueueTypeStructPtr->J1939RmRqstTxQueueRear = TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRequestQueueSize - (uint8)1;
         }
         else
         {
           TmpJ1939RmRqstTxQueueTypeStructPtr->J1939RmRqstTxQueueRear = (uint8)0;
         }
         TmpJ1939RmRqstTxQueueTypeStructPtr->J1939RmRqstTxQueueCount = (uint8)0;
         /*RqstTSQueue Initialization*/
         TmpJ1939RmRqstTSQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTSQueueTypeStructPtr;
         TmpJ1939RmRqstTSQueueDataStructPtr = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;
         TmpJ1939RmRequestTimeoutMonitors   = TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRequestTimeoutMonitors;
         TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront = (uint8)0;
         if (TmpJ1939RmRequestTimeoutMonitors > (uint8)0)
         {
           TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear = TmpJ1939RmRequestTimeoutMonitors - (uint8)1;
           for (time_idx= (uint8)0;time_idx<TmpJ1939RmRequestTimeoutMonitors;time_idx++)
           {
             TmpJ1939RmRqstTSQueueDataStructPtr[time_idx].J1939RmTimeoutSupervisionTimer = TmpJ1939RmConfigPtr_Pbcfg->J1939RmTimeoutSupervision;
             TmpJ1939RmRqstTSQueueDataStructPtr[time_idx].J1939RmTimeoutSupervisionEnable = (boolean)FALSE;
           }
         }
         else
         {
           TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear = (uint8)0;
         }
         TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount = (uint8)0;
         /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.Init,1 */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer = TmpJ1939RmConfigPtr_Pbcfg->J1939RmTxConfirmationTimeout;
         /* !LINKSTO J1939Rm.SWS_J1939Rm_00073,1 */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmState = J1939RM_STATE_OFFLINE; /* All Channels initialized to offline state */
         TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_NO_TX; /* No Transmission and TxConfirmation*/
       }
       for (usr_idx= (uint8)0; usr_idx < TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr; usr_idx++)
       {
      /*ComIpduRqstQueue Initialization*/
      if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
      {
        TmpJ1939RmComIpduRqstQueueTypeStructPtr[usr_idx].J1939RmComIpduRqstQueueRear = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserComIPduRequestQueueSize - (uint8)1;
        TmpJ1939RmComIpduRqstQueueTypeStructPtr[usr_idx].J1939RmComIpduRqstQueueCount = (uint8)0;
      }
    }
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            /*Intalizing the 50 Ms timeout supervision DataStructure*/
            for (ch_idx= (uint8)0; ch_idx < TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelNr; ch_idx++)
            {
                TmpJ1939RmGlobalConfigPtr->J1939Rm50MsSupervision.Rear[ch_idx] = J1939_TOTAL_NUMBER_OF_PGS - (uint16)1;
                /* Deviation TASKING-1 */
                for(FiftyMSSupervision = 0u;FiftyMSSupervision<J1939_TOTAL_NUMBER_OF_PGS;FiftyMSSupervision++)
                {
                    TmpJ1939RmGlobalConfigPtr->J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[ch_idx][FiftyMSSupervision].PGNumber = 0u;
                    TmpJ1939RmGlobalConfigPtr->J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[ch_idx][FiftyMSSupervision].FiftyMsTimeoutTimer = 0u;
                }
            }
#endif
       /* !LINKSTO EB_Ref.SWS_J1939Rm_00012.InitializedState,1 */
       J1939Rm_Initialized = (boolean)TRUE;
    }
    else
    {
        /* J1939Rm_Init was called in state Null Poiinter. */
        #if (J1939RM_DEV_ERROR_DETECT == STD_ON)
       (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_INIT_SERVICEID, J1939RM_E_INIT_FAILED);
       #endif
    }
  }
  #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00011,1 */
    /*Raise Det_ReportError with the error code J1939RM_E_REINIT if DET reporting is enabled.*/
    (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_INIT_SERVICEID, J1939RM_E_REINIT);
  }
  #endif
}

/* !LINKSTO J1939Rm.SWS_J1939Rm_00038,1 */
/* *****************************************************************************
 *  Name                 : J1939Rm_DeInit
 *  Description          : This function resets the J1939 Request Manager
 *                         to the uninitialized state.
 *  Parameters           : None
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939RM_CODE) J1939Rm_DeInit(void)
{
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
  if (J1939Rm_Initialized != (boolean)TRUE)
  {
    /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_DeInit,1 */
    (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_DEINIT_SERVICEID, J1939RM_E_UNINIT);
  }
  else
  #endif
  {
    /* !LINKSTO J1939Rm.SWS_J1939Rm_00013,1 */
    J1939Rm_Initialized = (boolean)FALSE;
  }
}

/* !LINKSTO J1939Rm.SWS_J1939Rm_00039,1 */
/* *****************************************************************************
 *  Name                 : J1939Rm_GetVersionInfo
 *  Description          : Returns the version information of J1939Rm module.
 *  Parameters           : Output : Std_VersionInfoType * versionInfo
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939RM_CODE) J1939Rm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,J1939RM_APPL_DATA) versionInfo)
{
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if(versionInfo == NULL_PTR )
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00034.J1939Rm_GetVersionInfo,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_GETVERSIONINFO_SERVICEID, J1939RM_E_PARAM_POINTER);
    }
    else
#endif
    {
    versionInfo->moduleID = J1939RM_MODULE_ID;
    versionInfo->vendorID = J1939RM_VENDOR_ID;
    versionInfo->sw_major_version = J1939RM_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = J1939RM_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = J1939RM_SW_PATCH_VERSION;
    }
}

/* !LINKSTO J1939Rm.SWS_J1939Rm_00048,1 */
/* *****************************************************************************
 *  Name                 : J1939Rm_SetState
 *  Description          : Changes the communication state of J1939Rm to
 *                         off-line(only Request for AC supported) or on-line.
 *  Parameters           : Input : NetworkHandleType channel
 *                         Input : uint8 node
 *                         Input : J1939Rm_StateType newState
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_SetState( NetworkHandleType channel, uint8 node, J1939Rm_StateType newState)
{
   Std_ReturnType TmpResult = E_OK;

  if (J1939Rm_Initialized == (boolean)TRUE)
  {
    /*Local Variables*/
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
    CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
    P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;
    uint8 nd_idx = 0u;
    uint8 ndch_idx = 0u;
    uint8 node_index =  (uint8)0;
    uint8 channel_index = 0u;
    boolean ValidId = (boolean)FALSE;

    for (nd_idx=(uint8)0; ((nd_idx < TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeNr)&&(ValidId == (boolean)FALSE)); nd_idx++)
    {
      if (TmpJ1939RmNodeConstStructPtr[nd_idx].J1939RmNodeId == node)
      {
        node_index = nd_idx;
        ValidId = (boolean)TRUE;
      }
    }
    if (ValidId == (boolean)TRUE)
    {
      if (J1939Rm_ValidChannel(channel, &channel_index))
      {
        ValidId = (boolean)FALSE;
        TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
        for (ndch_idx=(uint8)0; ((ndch_idx < TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr)&&(ValidId == (boolean)FALSE)); ndch_idx++)
        {
          if (TmpJ1939RmNodeChannelRefPtr[ndch_idx] == channel)
          {
            ValidId = (boolean)TRUE;
          }
        }
        if (ValidId == (boolean)TRUE)
        {
          /*Valid NODE and CHANNEL combination*/
          if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmState != newState)
          {
            if ((newState == J1939RM_STATE_ONLINE) ||
                    (newState == J1939RM_STATE_OFFLINE))
            {
              /* !LINKSTO J1939Rm.SWS_J1939Rm_00014,1 */
              TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmState = newState;
            }
            else
            {
              /* !LINKSTO EB_Ref.SWS_J1939Rm_00040.DET,1 */
              /*Raise Det_ReportError with the error code J1939RM_E_INVALID_STATE when the newState is not in the valid range.*/
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SET_STATE_SERVICEID, J1939RM_E_INVALID_STATE);
            #endif
              /* !LINKSTO EB_Ref.SWS_J1939Rm_00040.rejection,1 */
              TmpResult = E_NOT_OK;
            }
          }
          else
          {
            /*Current state of Channel is same as newState*/
          }
        }
        else
        {
            /*Channel not configured to be handledd by Node*/
            TmpResult = E_NOT_OK;
        }
      }
      else
      {
          /* !LINKSTO EB_Ref.SWS_J1939Rm_00041.J1939Rm_SetState,1 */
          /*Raise Det_ReportError with the error code J1939RM_E_INVALID_NETWORK_ID when J1939Rm_SetState was called with wrong network handle.*/
          TmpResult = E_NOT_OK;
          #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SET_STATE_SERVICEID, J1939RM_E_INVALID_NETWORK_ID);
          #endif
      }
    }
    else
    {
        /*Raise Det_ReportError with the error code J1939RM_E_INVALID_NODE when J1939Rm_SetState was called with an illegal node ID.*/
        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Rm.SWS_J1939Rm_00096,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SET_STATE_SERVICEID, J1939RM_E_INVALID_NODE);
        #endif

        TmpResult = E_NOT_OK;
    }
  }
  else
  {
    /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_SetState,1 */
    /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SET_STATE_SERVICEID, J1939RM_E_UNINIT);
    #endif
    TmpResult = E_NOT_OK;
  }
  return TmpResult;
}
#if ((defined J1939RM_SUPPORT_REQUESTINDICATION) || (defined J1939RM_ACKINDICATION_SUPPORT))
/* !LINKSTO J1939Rm.SWS_J1939Rm_00058,1 */
/* !LINKSTO J1939Rm.SWS_J1939Rm_00080,1*/
/* *****************************************************************************
 *  Name                 : J1939Rm_RxIndication
 *  Description          : Indication of a received I-PDU from a
 *                         lower layer communication interface module.
 *  Parameters           : Input : PduIdType RxPduId
 *                         Input : PduInfoType *PduInfoPtr
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939RM_CODE) J1939Rm_RxIndication( PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr) {

    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (J1939Rm_Initialized != (boolean) TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_RxIndication,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_RXINDICATION_SERVICEID, J1939RM_E_UNINIT);
    }
    else if(PduInfoPtr == NULL_PTR )
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00034.J1939Rm_RxIndication,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_RXINDICATION_SERVICEID, J1939RM_E_PARAM_POINTER);
    }
    else
    #endif
    {
        if ((PduLengthType)(PduInfoPtr -> SduLength) == (PduLengthType) J1939RM_RQSTPG_LENGTH) /*Data Length is 3 bytes - RQST PG*/
        {
            (void)J1939Rm_Request_Reception_Handling(RxPduId , PduInfoPtr);
        }
        else
        {
            if ((PduLengthType)(PduInfoPtr -> SduLength) == (PduLengthType) J1939RM_ACKMPG_LENGTH) /*Data Length is 8 bytes - ACKM PG*/
            {
                (void)J1939Rm_Ack_Reception_Handling(RxPduId , PduInfoPtr);
            }
        }
    }
}
#endif
/* !LINKSTO J1939Rm.SWS_J1939Rm_00081,1 */
#if ((J1939RM_SENDREQUEST_SUPPORT == STD_ON)||(J1939RM_SENDACK_SUPPORT == STD_ON)||(J1939RM_COM_SUPPORT == STD_ON))
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00059,1 */
/* *****************************************************************************
 *  Name                 : J1939Rm_TxConfirmation
 *  Description          : The lower layer communication interface module confirms
 *                         the transmission of an I-PDU by calling this API.
 *  Parameters           : Input : PduIdType TxPduId
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939RM_CODE) J1939Rm_TxConfirmation( PduIdType TxPduId)
{
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (J1939Rm_Initialized == (boolean)TRUE)
    {
    #endif
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
        P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
        P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;

        uint8 ch_idx = 0u;
        uint8 ndch_idx = 0u;
        uint8 usr_idx = 0u;
        uint16 comipdu_idx = 0u;
        uint8 node_index = 0u;
        uint8 channel_index = 0u;
        boolean ValidId = (boolean)FALSE;

        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        if (TxPduId != J1939RM_INVALID_PDU_ID)
        {
        #endif
            /*Search for TxPduId in configured Channels to know the TxConfirmation is for Rqst or Ackm*/
            for (ch_idx= (uint8)0;((ch_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelNr)&&(ValidId==(boolean)FALSE));ch_idx++)
            {
                if (TxPduId == TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRqstTxPduId)
                {
                    if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation == J1939RM_RQST_TX)
                    {
                        /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.RQST_TX_CONFIRMED,1 */
                        /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00022,1 */
                        TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_RQST_TX_CONFIRMED; /*Rqst Transmitted and got confirmation for the same*/

                        ValidId = (boolean)TRUE;
                    }
                }
                else
                {
                    if (TxPduId == TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckmTxPduId)
                    {
                        if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation == J1939RM_ACKM_TX)
                        {
                            /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.ACKM_TX_CONFIRMED,1 */
                            /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00019,1 */
                            TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_ACKM_TX_CONFIRMED; /*Ackm Transmitted and got confirmation for the same*/
                            ValidId = (boolean)TRUE;
                        }
                    }
                }
            }
            if (ValidId == (boolean)FALSE)/*TxConfirmation not for RQST and ACKM*/
            {
                for (usr_idx= (uint8)0;((usr_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr)&&(ValidId==(boolean)FALSE));usr_idx++)
                {
                    if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
                    {
                        /*Txconfirmation is for COMIPDUs*/
                        TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduConstStructPtr;
                        for (comipdu_idx= (uint8)0; ((comipdu_idx<TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduNr)&&(ValidId==(boolean)FALSE)); comipdu_idx++)
                        {
                            if (TxPduId == TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmLowerComIPduId)
                            {
                                (void)J1939Rm_ValidNode((uint16)TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserId, &node_index);
                                TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
                                for (ndch_idx= (uint8)0;((ndch_idx<TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr)&&(ValidId==(boolean)FALSE));ndch_idx++)
                                {
                                    (void)J1939Rm_ValidChannel(TmpJ1939RmNodeChannelRefPtr[ndch_idx], &channel_index);
                                    if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation == J1939RM_COM_TX)
                                    {
                                        /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_COM_TX_CONFIRMED,1 */
                                        TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation = J1939RM_COM_TX_CONFIRMED;
                                        /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00050,1 */
                                        /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.PduR_J1939RmTxConfirmation,1 */
                                        PduR_J1939RmTxConfirmation(TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmUpperComIPduRef_PDUR);/* TxConfirmation to Upper layer*/
                                        ValidId = (boolean)TRUE;
                                    }
                                }
                            }
                            else
                            {

                            }
                        }
                    }
                }
            }
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            if (ValidId == (boolean)FALSE)
            {
                /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_TxConfirmation,1 */
                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TXCONFIRMATION_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);
            }
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_TxConfirmation,1 */
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TXCONFIRMATION_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);
        }
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_TxConfirmation,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TXCONFIRMATION_SERVICEID, J1939RM_E_UNINIT);
    }
    #endif
    /* ## Operation body end [e9788378-2326-4957-8f0d-cf1396053940] */
}
#endif

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00077,1 */
#if (J1939RM_J1939TP_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_CopyTxData
 *  Description          : This function is called to acquire the transmit data of an
 *                         I-PDU segment (N-PDU). Each call to this function provides
 *                         next part of the I-PDU data unless retry->TpDataState is
 *                         TP_DATARETRY. In this case function restarts to copy data
 *                         beginning at the offset from current position indicated by
 *                         retry->TxTpDataCnt. The size of remaining data is written
 *                         to the position indicated by availableDataPtr.
 *  Parameters           : Input : PduIdType id
 *                         Input : PduInfoType *info
 *                         Input : RetryInfoType *retry
 *                         Output : PduLengthType *availableDataPtr
 *  Return               : BufReq_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00060,1 */
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00035,1 */
FUNC(BufReq_ReturnType, J1939RM_CODE) J1939Rm_CopyTxData( PduIdType id, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) info,P2VAR(RetryInfoType, AUTOMATIC,J1939RM_APPL_DATA) retry,P2VAR(PduLengthType, AUTOMATIC,J1939RM_APPL_DATA) availableDataPtr)
{
    /* ## Operation body start [cb5c894f-dabf-437a-856c-abbb52aad9cb] */
     BufReq_ReturnType TmpResult = BUFREQ_E_NOT_OK;
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if(J1939Rm_Initialized != (boolean)TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_CopyTxData,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_COPYTXDATA_SERVICEID, J1939RM_E_UNINIT);
    }
    else if(availableDataPtr == NULL_PTR )
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00034.J1939Rm_CopyTxData,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_COPYTXDATA_SERVICEID, J1939RM_E_PARAM_POINTER);
    }
    else if(info == NULL_PTR )
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00034.J1939Rm_CopyTxData,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_COPYTXDATA_SERVICEID, J1939RM_E_PARAM_POINTER);
    }
    else
    #endif
    {
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
        P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
        uint8 usr_idx = 0u;
        uint16 comipdu_idx = 0u;
        boolean ValidId = (boolean)FALSE;

        for (usr_idx= (uint8)0;((usr_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr)&&(ValidId==(boolean)FALSE));usr_idx++)
        {
            if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
            {
                /*TpTxconfirmation is for COMIPDUs*/
                TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduConstStructPtr;
                for (comipdu_idx= (uint8)0; ((comipdu_idx<TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduNr)&&(ValidId==(boolean)FALSE)); comipdu_idx++)
                {
                    if ((PduIdType)id == (TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmLowerComIPduId))
                    {
                        ValidId = (boolean)TRUE;

                        /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00051,1 */
                        /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.PduR_J1939RmCopyTxData,1 */
                        TmpResult = PduR_J1939RmCopyTxData(TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmUpperComIPduRef_PDUR, info, retry, availableDataPtr);
                    }
                    else
                    {

                    }
                }
            }
        }
        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        if (ValidId == (boolean)FALSE)
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_CopyTxData,1 */
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_COPYTXDATA_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);
        }
        #endif
    }
    return TmpResult;
    /* ## Operation body end [cb5c894f-dabf-437a-856c-abbb52aad9cb] */
}
#endif

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00078,1 */
#if (J1939RM_J1939TP_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_TpTxConfirmation
 *  Description          : This function is called after the I-PDU has been transmitted
 *                         on its network, the result indicates whether the transmission
 *                         was successful or not.
 *  Parameters           : Input : PduIdType id
 *                         Input : Std_ReturnType result
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00061,1 */
FUNC(void, J1939RM_CODE) J1939Rm_TpTxConfirmation( PduIdType id, Std_ReturnType result)
{
    /* ## Operation body start [79ee6e8f-564b-40a1-8aca-30a8da11dd34] */
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (J1939Rm_Initialized == (boolean)TRUE)
    {
    #endif

        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
        CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
        P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
        P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;

        uint8 usr_idx = 0u;
        uint16 comipdu_idx = 0u;
        uint8 ndch_idx = 0u;
        uint8 node_index = 0u;
        uint8 channel_index = 0u;
        boolean ValidId = (boolean)FALSE;

        for (usr_idx= (uint8)0;((usr_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr)&&(ValidId==(boolean)FALSE));usr_idx++)
        {
            if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
            {

                /*TpTxconfirmation is for COMIPDUs*/
                TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduConstStructPtr;
                for (comipdu_idx= (uint8)0; ((comipdu_idx<TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduNr)&&(ValidId==(boolean)FALSE)); comipdu_idx++)
                {
                    if (id == TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmLowerComIPduId)
                    {
                        (void)J1939Rm_ValidNode((uint16)TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserId, &node_index);
                        TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
                        for (ndch_idx= (uint8)0;((ndch_idx<TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr)&&(ValidId==(boolean)FALSE));ndch_idx++)
                        {
                            (void)J1939Rm_ValidChannel(TmpJ1939RmNodeChannelRefPtr[ndch_idx], &channel_index);
                            if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation == J1939RM_COM_TX)
                            {
                                /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_COM_TX_CONFIRMED,1 */
                                TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation = J1939RM_COM_TX_CONFIRMED;

                                /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00052,1 */
                                /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.PduR_J1939RmTpTxConfirmation,1 */
                                PduR_J1939RmTpTxConfirmation(TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmUpperComIPduRef_PDUR, result); /*TxConfirmation to Upper layer*/

                                ValidId = (boolean)TRUE;
                            }
                        }
                    }
                    else
                    {

                    }
                }
            }
        }
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        if(ValidId == (boolean)FALSE)
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_TpTxConfirmation,1 */
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TPTXCONFIRMATION_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);
        }
        else
        {
        }
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_TpTxConfirmation,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TPTXCONFIRMATION_SERVICEID, J1939RM_E_UNINIT);
    }
    #endif
    /* ## Operation body end [79ee6e8f-564b-40a1-8aca-30a8da11dd34] */
}
#endif

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00079,1 */
#if (J1939RM_COM_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_ComRxIpduCallout
 *  Description          : The I-PDU call out on receiver side can be configured
 *                         to implement user-defined receive filtering mechanisms.
 *  Parameters           : Input : PduIdType PduId
 *                         Input : PduInfoType *PduInfoPtr
 *  Return               : boolean
 *  Critical/explanation : [No]
 ******************************************************************************/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00062,1 */
FUNC(boolean, J1939RM_CODE) J1939Rm_ComRxIpduCallout( PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr)
{
     boolean ValidId=(boolean)FALSE;
    if (J1939Rm_Initialized == (boolean)TRUE)
    {
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
        P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
        CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
        CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
        P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;
        P2VAR(J1939Rm_RqstTSQueueType_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueTypeStructPtr;
        P2VAR(J1939Rm_RqstTSQueueData_Struct, AUTOMATIC,J1939RM_APPL_DATA) TmpJ1939RmRqstTSQueueDataStructPtr;
        uint8 TmpJ1939RmRequestTimeoutMonitors = 0u;
        uint8 queue_idx = 0u;
        uint8 queue_index = (uint8)0;
        boolean Valid = (boolean)FALSE;
        uint32 COM_PGN= (uint32)0;
        uint8 usr_idx = 0u;
        uint16 user_index= (uint16)0;
        uint16 comipdu_idx = 0u;
        uint8 node_index= (uint8)0;
        uint8 ndch_idx = 0u;
        uint8 channel_index = 0u;

        TS_PARAM_UNUSED(PduInfoPtr);

        /*Check if PduId is valid COM request*/
        /*Obtain User Index based on valid PduId */
        for (usr_idx= (uint8)0;((usr_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr)&&(ValidId==(boolean)FALSE));usr_idx++)
        {
            /* looking for the received PduId in all configured J1939RmUpperComIPduId */
            if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
            {
                TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduConstStructPtr;
                for (comipdu_idx= (uint8)0; ((comipdu_idx<TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduNr)&&(ValidId==(boolean)FALSE)); comipdu_idx++)
                {
                    if (PduId == TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmUpperComIPduId)
                    {
                        user_index = usr_idx;
                        COM_PGN = TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmComIPduPGN;
                        ValidId = (boolean)TRUE;
                    }
                    else
                    {
                    }
                }
            }
        }
        if (ValidId == (boolean)TRUE)
        {
            (void)J1939Rm_ValidNode((uint16)TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserId, &node_index);
            TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
            for (ndch_idx= (uint8)0;((ndch_idx<TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr) && (Valid==(boolean)FALSE));ndch_idx++)
            {
                (void)J1939Rm_ValidChannel(TmpJ1939RmNodeChannelRefPtr[ndch_idx], &channel_index);

                  TmpJ1939RmRqstTSQueueTypeStructPtr = TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmRqstTSQueueTypeStructPtr;
                  TmpJ1939RmRqstTSQueueDataStructPtr = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueDataStructPtr;
                  TmpJ1939RmRequestTimeoutMonitors   = TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmRequestTimeoutMonitors;


                    if (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount != (uint8)0)
                    {
                      for (queue_idx = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueFront; ((queue_idx != TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear) && (Valid == (boolean)FALSE)); queue_idx= (queue_idx+ (uint8)1)% TmpJ1939RmRequestTimeoutMonitors)
                      {
                        if (COM_PGN == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstPgn)
                        {
                          queue_index = queue_idx;
                          Valid = (boolean)TRUE;
                        }
                        else
                        {

                        }
                      }
                      if (Valid == (boolean)FALSE) /*Check for last entry in queue*/
                      {
                        if (COM_PGN == TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmRqstPgn)
                        {
                          queue_index = queue_idx;
                          Valid = (boolean)TRUE;
                        }
                        else
                        {
                          /*No suitable entry found in the list of pending requests*/
                        }
                      }
                    }
                    else
                    {
                        /*Rqst TSV Queue is Empty*/
                    }

                    if (Valid == (boolean)TRUE)
                    {
                      /*Remove RQST from RQST TSV Queue*/
                      /* !LINKSTO EB_Ref.SWS_J1939Rm_00029.COM_RxIPduCallout,1 */
                      for (queue_idx = queue_index; queue_idx != TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear; queue_idx++)
                      {
                        TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx] = TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx+ (uint8)1];
                      }
                      TmpJ1939RmRqstTSQueueDataStructPtr[queue_idx].J1939RmTimeoutSupervisionEnable = (boolean)FALSE;
                      TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount = TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueCount - (uint8)1;
                      TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear = (TmpJ1939RmRqstTSQueueTypeStructPtr->J1939RmRqstTSQueueRear + TmpJ1939RmRequestTimeoutMonitors -  (uint8)1)%TmpJ1939RmRequestTimeoutMonitors;
                    }
            }

        }
        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_ComRxIpduCallout,1 */
            /*PduId is not the configured one*/
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_COMRXIPDUCALLOUT_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);

        }
        #endif
    }
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_ComRxIpduCallout,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_COMRXIPDUCALLOUT_SERVICEID, J1939RM_E_UNINIT);
    }
    #endif
    return ValidId;
}
#endif

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00047,1 */
#if (J1939RM_COM_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_Transmit
 *  Description          : This function requests transmission of an I-PDU.
 *  Parameters           : Input : PduIdType id
 *                         Input : PduInfoType *info
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00053,1 */
FUNC(Std_ReturnType, J1939RM_CODE)J1939Rm_Transmit( PduIdType id, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) info)
{
    Std_ReturnType TmpResult = E_OK;
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (J1939Rm_Initialized != (boolean)TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_Transmit,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TRANSMIT_SERVICEID, J1939RM_E_UNINIT);
        TmpResult = E_NOT_OK;
    }
    else if (info == NULL_PTR)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00034.J1939Rm_Transmit,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TRANSMIT_SERVICEID, J1939RM_E_PARAM_POINTER);
        TmpResult = E_NOT_OK;
    }
    else
#endif
    {
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
        CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
        P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmComIPduConstStructPtr;
        CONSTP2CONST(J1939Rm_ComIpduRqstQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmComIpduRqstQueueTypeStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmComIpduRqstQueueTypeStructPtr;
        uint32 COM_PGN = (uint32)0;
        uint8 TmpQueueSA = 0u;
        uint8 TmpQueueDA = 0u;
        uint8 TmpQueueChannelId = 0u;
        uint8 usr_idx = 0u;
        uint8 user_index = (uint8)0;
        uint8 channel_index = (uint8)0;
        uint16 comipdu_idx = 0u;
        uint16 compgn_index = (uint16)0;
        uint8 NodeIdx = 0 ;
        boolean ValidId = (boolean)FALSE;
        Std_ReturnType PduR_ReturnResult = E_OK;
#if (J1939RM_J1939TP_SUPPORT == STD_ON)
        uint8 MetaDataLen = 0;
        Std_ReturnType SetMetaDataResult_SA = (Std_ReturnType)E_OK;
        Std_ReturnType SetMetaDataResult_TA = (Std_ReturnType)E_OK;
        Std_ReturnType SetMetaDataResult_pri = (Std_ReturnType)E_OK;
#endif

        /*"id" is the configured one?*/
        for (usr_idx = (uint8)0; ((usr_idx < TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr) && (ValidId == (boolean)FALSE)); usr_idx++)
        {
            if (TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM)
            {
                TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduConstStructPtr;
                for (comipdu_idx = (uint8)0; ((comipdu_idx < TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduNr) && (ValidId == (boolean)FALSE)); comipdu_idx++)
                {
                    if (id == TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmUpperComIPduId)
                    {
                        user_index = usr_idx;
                        COM_PGN = TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmComIPduPGN;
                        compgn_index = comipdu_idx;
                        ValidId = (boolean)TRUE;
                    }

                }
            }
        }

        if (ValidId == (boolean)TRUE)
        {
            if (TmpJ1939RmComIpduRqstQueueTypeStructPtr[user_index].J1939RmComIpduRqstQueueCount > (uint8)0)
            {
                /*Dequeue data from COM RQST Queue and Enqueue data on RQST Queue based on Priority*/
                if (J1939Rm_ValidRmvRqstCOMQueue(COM_PGN, (uint16)user_index, &TmpQueueSA, &TmpQueueDA, &TmpQueueChannelId))
                {
                    (void)J1939Rm_ValidChannel(TmpQueueChannelId, &channel_index);
                    (void)J1939Rm_ValidNode(TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserId,&NodeIdx);
                    if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation == J1939RM_COM_RX)
                    {
                      /* In case of transmission of Com User response that was received as global request
                        SA, DA could not be swapped, instead as per SAE J1939-21 Table 5, DA = J1939RM_BROADCAST_ADDR and SA = NodeAddress.
                        The correct assignment of SA and DA is done before calling Transmit API.
                        This is to avoid Transmitting an invalid response with SA = J1939RM_BROADCAST_ADDR*/
                      if (TmpQueueDA == J1939RM_BROADCAST_ADDR)
                      {
                        /* Transmitted SA: DA will be sawpped, and placed as a SA*/
                        TmpQueueDA = TmpJ1939RmNodeConstStructPtr[NodeIdx].J1939RmNodeAddress;
                        /* Transmitted DA: SA will be sawpped, and placed as a DA*/
                        TmpQueueSA = J1939RM_BROADCAST_ADDR; 
                      }
                        TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[user_index].J1939RmComIPduConstStructPtr;

                        if (TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939Rm_IfTransmit)
                        {
                            /*Copy MetaData Information into the Pdu to Send it to PduR*/
                            /* !LINKSTO J1939Rm.SWS_J1939Rm_00124,1*/
                            (void)J1939Rm_EcuC_SetMetaDataCanId((uint8)(J1939RM_DEFAULT_PRIORITY << 2),
                                                                (uint8)(COM_PGN >> 8),
                                                                (uint8)TmpQueueSA,  /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.Set_DA,1 */
                                                                (uint8)TmpQueueDA,  /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.Set_SA,1 */
                                                                (EcuC_PduIdType)(TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerComIPdu_Ecuc_PduId),
                                                                J1939RM_TRANSMIT_SERVICEID);
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.PduR_J1939RmTransmit.PduId,1 */
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.PduR_J1939RmTransmit.Interface_Path,1 */
                                PduR_ReturnResult = PduR_J1939RmTransmit(TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerComIPduRef, info);
                        }
#if (J1939RM_J1939TP_SUPPORT == STD_ON)
                        else
                        {
                            /*TP transmission  handle */
                            PduInfoType dummy_Var;
                            P2VAR(PduInfoType, AUTOMATIC,J1939RM_APPL_DATA) dummy_Ptr = &dummy_Var;
                            MetaDataLen = TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerPduMetaData;
                            /* SA of sent PGN will be DA of received PGN & DA of sent PGN will be SA of received PGN */

                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.Set_SA,1 */
                            SetMetaDataResult_SA = EcuC_SetMetaDataSourceAddr((EcuC_PduIdType)(TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerComIPdu_Ecuc_PduId), dummy_Ptr, (uint16)TmpQueueDA);
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.Set_DA,1 */
                            SetMetaDataResult_TA = EcuC_SetMetaDataTargetAddr((EcuC_PduIdType)(TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerComIPdu_Ecuc_PduId), dummy_Ptr, (uint16)TmpQueueSA);
                            if (MetaDataLen == (uint8)4u)
                            {
                                SetMetaDataResult_pri = EcuC_SetMetaDataPriority((EcuC_PduIdType)(TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerComIPdu_Ecuc_PduId), dummy_Ptr, (uint8)(J1939RM_DEFAULT_PRIORITY << 2));
                            }
                            if ((E_OK != SetMetaDataResult_SA) || (E_OK != SetMetaDataResult_TA) || (E_OK != SetMetaDataResult_pri))
                            {
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
                                /* !LINKSTO J1939Rm.EB.Invalid_MetaData,1 */
                                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TRANSMIT_SERVICEID, J1939RM_E_INVALID_METADATA_HANDLE);
#endif
                            }

                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00006.PduR_J1939RmTransmit.PduId,1 */
                            PduR_ReturnResult = PduR_J1939RmTpTransmit(TmpJ1939RmComIPduConstStructPtr[compgn_index].J1939RmLowerComIPduRef, info);
                        }
#endif

                        if (PduR_ReturnResult == E_OK)
                        {
                            /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_COM_TX,1 */
                            TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation = J1939RM_COM_TX;
                        }
                        else
                        {
                            TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmTxConfirmation = J1939RM_NO_TX;
                            TmpResult = E_NOT_OK;
                        }
                    }
                }
            }
            else
            {
                TmpResult = E_NOT_OK;
            }
        }
        else
        {
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00033.J1939Rm_Transmit,1 */
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_TRANSMIT_SERVICEID, J1939RM_E_INVALID_PDU_SDU_ID);
#endif
            TmpResult = E_NOT_OK;
        }
    }
    return TmpResult;
}
#endif

/* !LINKSTO J1939Rm.SWS_J1939Rm_00074,1 */
#if (J1939RM_SENDREQUEST_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_SendRequest
 *  Description          : This function requests transmission of a Request PG.
 *  Parameters           : Input : uint8 userId
 *                         Input : NetworkHandleType channel
 *                         Input : uint32 requestedPgn
 *                         Input : uint8 destAddress
 *                         Input : uint8 priority
 *                         Input : boolean checkTimeout
 *  Return               : Std_ReturnType
 *  Critical/explanation : [No]
 ******************************************************************************/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00054,1 */
/* !LINKSTO EB_Ref.SWS_J1939Rm_00054.SendRequestAPI,1 */
FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_SendRequest( uint8 userId, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress, uint8 priority, boolean checkTimeout)
{
    Std_ReturnType TmpResult = E_NOT_OK;

    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (J1939Rm_Initialized == (boolean)TRUE)
    {
    #endif
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_RealStructType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr = TmpJ1939RmGlobalConfigPtr->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr->J1939RmUserConstStructPtr;
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr_Pbcfg = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
    #endif
        P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;
        uint16 user_index = (uint16)0;
        uint8 ndch_idx = 0u;
        uint8 node_index = (uint8)0;
        uint8 channel_index = 0u;
        boolean ValidId = (boolean)FALSE;
        boolean ValidOnlineChannel = (boolean)FALSE;
        boolean Validpriority = (boolean)FALSE;
        boolean ValidUser = (boolean)FALSE;
        boolean ValidDestAdd = (boolean)FALSE;

        ValidOnlineChannel = J1939Rm_ValidOnlineChannel( channel, &channel_index);

        if (priority <= (uint8)7)
        {
            Validpriority = (boolean)TRUE;
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00067.Invalid_priority,1 */
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            /*priority is not in the valid range. Raise Det_ReportError with the error code J1939RM_E_INVALID_PRIO*/
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_PRIO);
            #endif
        }
        if (J1939Rm_ValidUser((uint16)userId, &user_index))
        {
            ValidUser = (boolean)TRUE;
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00067.Invalid_userId,1 */
            /*UserId is not a configured user, Raise Det_ReportError with the error code J1939RM_E_INVALID_USER*/
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_USER);
            #endif
        }

        if (destAddress != J1939RM_NULL_ADDRESS)
        {
            ValidDestAdd = (boolean) TRUE;
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00067.Invalid_destAddress,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00031.J1939RM_E_INVALID_ADDRESS,1 */
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            /*Raise Det_ReportError with the error code J1939RM_E_INVALID_ADDRESS.*/
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_ADDRESS);
            #endif
        }
        if ((ValidDestAdd == (boolean)TRUE) && (ValidOnlineChannel == (boolean)TRUE) && (Validpriority == (boolean)TRUE) && (ValidUser == (boolean)TRUE))
        {
            /* Check if J1939RmUserSendRequest is enabled for this user */
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            if (TmpJ1939RmUserConstStructPtr_Pbcfg[user_index].J1939RmUserSendRequestSupport == FALSE)
            {
                /* Raise Det_ReportError with the error code J1939RM_E_INVALID_SEND_REQUEST*/
                /* !LINKSTO J1939Rm.EB.Invalid_SendRequest,1 */
                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_SEND_REQUEST);
            }
            else
            #endif
            {
                /*UserId is configured*/
                /*Check if Node on which User is configured is handled through the Channel Id*/
                /*Check if Node on which User is configured is handled through the Channel Id passed on SendRequest*/
                (void)J1939Rm_ValidNode((uint16)userId, &node_index);
                ValidId = (boolean)FALSE;
                TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
                for (ndch_idx= (uint8)0;((ndch_idx<TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr) && (ValidId==(boolean)FALSE));ndch_idx++)
                {
                    if (TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId == TmpJ1939RmNodeChannelRefPtr[ndch_idx])
                    {
                        ValidId = (boolean)TRUE;
                    }
                }
                if (ValidId == (boolean)TRUE)
                {
                    if (requestedPgn <= J1939RM_PGN_MAX)
                    {

                        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                        /* !LINKSTO J1939Rm.EB.Fifty_ms_TimeSupervision,1 */
                        /*Check if the 50 Ms time has passed between the send of the request and try to enqueue another request*/
                        uint8 FiftyMsTimeSupervisionIterator = 0u;
                        /* Deviation TASKING-1 */
                        for(FiftyMsTimeSupervisionIterator = 0u;FiftyMsTimeSupervisionIterator<(J1939_TOTAL_NUMBER_OF_PGS);FiftyMsTimeSupervisionIterator++)
                        {
                            if((J1939Rm_GlobalConfig.J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[channel_index][FiftyMsTimeSupervisionIterator].PGNumber == requestedPgn)
                                    && (J1939Rm_GlobalConfig.J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[channel_index][FiftyMsTimeSupervisionIterator].FiftyMsTimeoutTimer > (uint8)0))
                            {
                                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_TimeoutSupervision_50MS);
                                break;
                            }
                        }
                        #endif
                        TmpResult = E_OK;

                        if ((TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserRequestTimeoutIndicationFctPtr == NULL_PTR)&&(checkTimeout == (boolean)TRUE))
                        {
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00067.Invalid_checkTimeout,1 */
                            /* !LINKSTO J1939Rm.SWS_J1939Rm_00017,1 */
                            /*CheckTimeout is true but timeout handling is disabled for the calling module (J1939RmUserTimeoutSupervision). Raise Det_ReportError with the error code J1939RM_E_INVALID_OPTION*/
                            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_OPTION);
                            #endif
                            TmpResult = E_NOT_OK;
                        }
                        /* Deviation TASKING-1 */
                        else if((TmpResult == E_OK )&&(checkTimeout == (boolean)TRUE))
                        {
                            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                            /* !LINKSTO J1939Rm.EB.1250MS_TimeoutSupervision,1 */
                            /*Check the timeout supervision of 1.25 s have passed between the request sent and another request is sent*/
                            TmpResult = J1939Rm_TimeoutSupervision_1250MS(userId, requestedPgn, destAddress, channel_index, node_index);
                            #endif
                        }
                        else
                        {

                        }

                        if (TmpResult != E_NOT_OK)
                        {
                            /*Enqueue Data*/
                            /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00024,1 */
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00024.SendRequest,1*/
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00021.queueing_Rqst_PG,1 */
                            TmpResult = J1939Rm_Enqueue_TXPG_RQST(
                                    channel_index,                                                     /*Derive the Queue to be updated based on channel index and QueueType*/
                                    (uint16)userId,                                                    /*Calling module's user ID.*/
                                    requestedPgn,                                                      /*PGN of the Requested PG.*/
                                    TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeAddress,       /*Address of the Source node for Rqst.*/
                                    destAddress,                                                       /*Address of the destination node for Rqst.*/
                                    priority,                                                          /*Priority of the Requested PG.*/
                                    checkTimeout
                            );
                        }
                    }
                    else
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Rm_00067.Invalid_requestedPGN,1 */
                        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                        /*requestedPgn is not configured to be handled on User with identifier userId. Raise Det_ReportError with the error code J1939RM_E_INVALID_PGN*/
                        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_INVALID_PGN);
                        #endif
                    }

                }
                else
                {
                    /*Node on which User is configured is not handled through the Channel Id passed on SendRequest.*/
                }
            }
        }
        else
        {
        }

    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    }
    else
    {
      /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_SendRequest,1 */
      /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
      (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SEND_REQUEST_SERVICEID, J1939RM_E_UNINIT);
    }
    #endif
    return TmpResult;
}
#endif

/* !LINKSTO J1939Rm.SWS_J1939Rm_00075,1 */
#if (J1939RM_TIMEOUTSUPERVISION_SUPPORT == STD_ON)
/* *****************************************************************************
 *  Name                 : J1939Rm_CancelRequestTimeout
 *  Description          : Cancels time out monitoring of a Request. If request is
 *                         not active, or time out monitoring was not requested,
 *                         then this call has no effect.
 *  Parameters           : Input : uint8 userId
 *                         Input : NetworkHandleType channel
 *                         Input : uint32 requestedPgn
 *                         Input : uint8 destAddress
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00055,1 */
/* !LINKSTO EB_Ref.SWS_J1939Rm_00055.CancelRequestTimeoutAPI,1 */
FUNC(void, J1939RM_CODE) J1939Rm_CancelRequestTimeout( uint8 userId, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress)
{
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
     uint16 user_index= (uint16)0;
    if (J1939Rm_Initialized != (boolean)TRUE)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_CancelRequestTimeout,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_CANCELREQUESTTIMEOUT_SERVICEID, J1939RM_E_UNINIT);
    }
    else if(!(J1939Rm_ValidUser((uint16)userId, &user_index)))
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00069.invalid_userId,1 */
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_CANCELREQUESTTIMEOUT_SERVICEID, J1939RM_E_INVALID_USER);
    }
    else if (requestedPgn > J1939RM_PGN_MAX)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00069.invalid_requestedPGN,1 */

        /*requestedPgn is not configured to be handled on User with identifier userId. Raise Det_ReportError with the error code J1939RM_E_INVALID_PGN*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_CANCELREQUESTTIMEOUT_SERVICEID, J1939RM_E_INVALID_PGN);

    }
    else
    #endif
    {
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        uint8 channel_index= (uint8)0;
        uint8 node_index= (uint8)0;
        uint8 nd_idx = 0u;
        boolean ValidId = (boolean)FALSE;

        for (nd_idx = (uint8) 0; ((nd_idx < TmpJ1939RmConfigPtr_Pbcfg -> J1939RmNodeNr) && (ValidId == (boolean) FALSE)); nd_idx++)
            {
                if (TmpJ1939RmNodeConstStructPtr[nd_idx].J1939RmNodeAddress == destAddress)
                {
                    ValidId = (boolean) TRUE;
                }
            }
        if ((ValidId == (boolean) TRUE) || (destAddress == 0xFFu))
        {
            if (J1939Rm_ValidChannel(channel, &channel_index))
            {
                if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmState == J1939RM_STATE_ONLINE)
                {
                    /*Timeout Handling only in ONLINE state*/
                    (void)J1939Rm_ValidNode((uint16)userId, &node_index);

                    /*Check for the valid entry of userId, requestedPgn, and destAddress in RQST TSV QUEUE and Remove RQST from RQST TSV Queue and Disable TSV Timer */
                    /* !LINKSTO EB_Ref.SWS_J1939Rm_00029.J1939Rm_CancelRequestTimeout,1 */
                    (void)J1939Rm_ValidRmvRqstTSVQueue(requestedPgn, (uint16)userId, channel_index, TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeAddress, destAddress);

                    /* !LINKSTO EB_Ref.SWS_J1939Rm_00069.NoSuitableEntry,1 */
                }
                else
                {
                    /*No Timeout Handling in OFFLINE state*/
                }
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Rm_00041.J1939Rm_CancelRequestTimeout,1 */
                #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                /*Raise Det_ReportError with the error code J1939RM_E_INVALID_NETWORK_ID.*/
                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_CANCELREQUESTTIMEOUT_SERVICEID, J1939RM_E_INVALID_NETWORK_ID);
                #endif
            }
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00069.invalid_destAddress,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00031.J1939RM_E_INVALID_ADDRESS,1 */
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            /*Raise Det_ReportError with the error code J1939RM_E_INVALID_ADDRESS.*/
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_CANCELREQUESTTIMEOUT_SERVICEID, J1939RM_E_INVALID_ADDRESS);
            #endif
        }
    }
}
#endif
/* !LINKSTO J1939Rm.SWS_J1939Rm_00076,1 */
#if (J1939RM_SENDACK_SUPPORT == STD_ON)
/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00056,1 */
/* !LINKSTO EB_Ref.SWS_J1939Rm_00056.SendAckAPI,1*/
/* *****************************************************************************
 *  Name                 : J1939Rm_SendAck
 *  Description          : This API requests transmission of Acknowledgement PG.
 *  Parameters           : Input : uint8 userId
 *                         Input : NetworkHandleType channel
 *                         Input : uint32 ackPgn
 *                         Input : J1939Rm_AckCode ackCode
 *                         Input : uint8 ackAddress
 *                         Input : uint8 priority
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_SendAck( uint8 userId, NetworkHandleType channel, uint32 ackPgn, J1939Rm_AckCode ackCode, uint8 ackAddress, uint8 priority)
{
    Std_ReturnType TmpResult = E_OK;
    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    if (J1939Rm_Initialized == (boolean)TRUE)
    {
    #endif
        /*Local Variables*/
        CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
        CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
        CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
        CONSTP2CONST(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
        CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
        CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;
        CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
        P2CONST(uint32, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserReqPGNPtr;
        P2CONST(uint8, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeChannelRefPtr;

        uint32 pgn_idx = 0u;
        uint16 user_index= (uint8)0;
        uint8 ndch_idx = 0u;
        uint8 node_index= (uint8)0;
        uint8 channel_index = 0u;
        boolean ValidId = (boolean)FALSE;

        if (ackAddress != J1939RM_NULL_ADDRESS)
        {
            if (J1939Rm_ValidChannel(channel, &channel_index))
            {
                if (TmpJ1939RmChannelRamStructPtr[channel_index].J1939RmState == J1939RM_STATE_ONLINE)
                {
                    /*Acknowledgement handling only in ONLINE state*/
                    if (priority <= (uint8)7)
                    {
                        if (   ((ackCode == J1939RM_ACK_POSITIVE)
                                || (ackCode == J1939RM_ACK_NEGATIVE))
                                || ((ackCode == J1939RM_ACK_ACCESS_DENIED)
                                || (ackCode == J1939RM_ACK_CANNOT_RESPOND))
                        )
                        {
                            if (J1939Rm_ValidUser((uint16)userId,&user_index))
                            {
                                /*UserId is configured*/
                                /*Check if Node on which User is configured is handled through the Channel Id*/
                                /*Check if Node on which User is configured is handled through the Channel Id passed on SendAck*/
                                (void)J1939Rm_ValidNode((uint16)userId, &node_index);
                                TmpJ1939RmNodeChannelRefPtr = TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelRefPtr;
                                for (ndch_idx= (uint8)0;((ndch_idx<TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeChannelNr)&&(ValidId==(boolean)FALSE));ndch_idx++)
                                {
                                    if (TmpJ1939RmChannelConstStructPtr[channel_index].J1939RmChannelId == TmpJ1939RmNodeChannelRefPtr[ndch_idx])
                                    {
                                        ValidId = (boolean)TRUE;
                                    }
                                }
                                if (ValidId == (boolean)TRUE)
                                {
                                    /*Node on which User is configured is handled through the Channel Id passed on SendAck*/
                                    /*Check if RequestedPGN is configured to be handled by User*/
                                    ValidId = (boolean)FALSE;
                                    TmpJ1939RmUserReqPGNPtr = TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserPGNPtr;
                                    for (pgn_idx= (uint32)0; ((pgn_idx<TmpJ1939RmUserConstStructPtr[user_index].J1939RmUserPGNNr) && (ValidId==(boolean)FALSE)); pgn_idx++)
                                    {
                                        if (ackPgn == TmpJ1939RmUserReqPGNPtr[pgn_idx])
                                        {
                                            /*Requested PGN is configured*/
                                            ValidId = (boolean)TRUE;
                                        }
                                    }

                                    if (ValidId == (boolean)TRUE)
                                    {
                                        /*Enqueue data*/
                                      /* !LINKSTO EB_Ref.SWS_J1939Rm_00018.queueing_Ack_PG,1 */
                                        TmpResult = J1939Rm_Enqueue_TXPG_ACKM(
                                                channel_index,            /*Channel Index*/
                                                (uint16)userId,           /*Calling module's user ID.*/
                                                ackPgn,                   /*PGN of the Acknowledged PG.*/
                                                (uint8)ackCode,           /*Type of acknowledgement for Ackm.*/
                                                ackAddress,               /*Address of the node that sent the request for Ackm*/
                                                ((uint8)(priority << 2))  /*Priority of the Acknowledgement PG.*/
                                        );
                                    }
                                    else
                                    {
                                        /* !LINKSTO EB_Ref.SWS_J1939Rm_00070.invalid_ackPgn,1 */
                                        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                                        /*ackPgn is not configured to be handled on User with identifier userId. Raise Det_ReportError with the error code J1939RM_E_INVALID_PGN*/
                                        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_INVALID_PGN);
                                        #endif
                                        TmpResult = E_NOT_OK;
                                    }
                                }
                                else
                                {
                                    /*Node on which User is configured is not handled through the Channel Id passed on SendAck*/
                                    TmpResult = E_NOT_OK;
                                }
                            }
                            else
                            {
                                /* !LINKSTO EB_Ref.SWS_J1939Rm_00070.invalid_userId,1 */
                                #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                                /*UserId is not configured on any Node, Raise Det_ReportError with the error code J1939RM_E_INVALID_USER*/
                                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_INVALID_USER);
                                #endif
                                TmpResult = E_NOT_OK;
                            }
                        }
                        else
                        {
                            /* !LINKSTO EB_Ref.SWS_J1939Rm_00070.invalid_ackCode,1 */
                            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                            /*ackCode is not in the valid range. Raise Det_ReportError with the error code J1939RM_E_INVALID_ACK_CODE*/
                            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_INVALID_ACK_CODE);
                            #endif
                            TmpResult = E_NOT_OK;
                        }
                    }
                    else
                    {
                        /* !LINKSTO EB_Ref.SWS_J1939Rm_00070.invalid_priority,1 */
                        #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                        /*priority is not in the valid range. Raise Det_ReportError with the error code J1939RM_E_INVALID_PRIO*/
                        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_INVALID_PRIO);
                        #endif
                        TmpResult = E_NOT_OK;
                    }
                }
                else
                {
                    /*Acknowledgement handling disabled in OFFLINE state*/
                    TmpResult = E_NOT_OK;
                }
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Rm_00041.J1939Rm_SendAck,1 */
                #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
                /*Raise Det_ReportError with the error code J1939RM_E_INVALID_NETWORK_ID.*/
                (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_INVALID_NETWORK_ID);
                #endif
                TmpResult = E_NOT_OK;
            }
        }
        else
        {
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00070.invalid_ackAddress,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Rm_00031.J1939RM_E_INVALID_ADDRESS,1 */
            #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
            /*Raise Det_ReportError with the error code J1939RM_E_INVALID_ADDRESS.*/
            (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_INVALID_ADDRESS);
            #endif
            TmpResult = E_NOT_OK;
        }

    #if(J1939RM_DEV_ERROR_DETECT == STD_ON)
    }
    else
    {
        /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_SendAck,1 */
        /*Raise Det_ReportError with the error code J1939RM_E_UNINIT when any API other than J1939Rm_Init or J1939Rm_GetVersionInfo is called in uninitialized state.*/
        (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SENDACK_SERVICEID, J1939RM_E_UNINIT);
        TmpResult = E_NOT_OK;
    }
    #endif
    return TmpResult;
}
#endif

/* !LINKSTO J1939Rm.SWS_J1939Rm_00072,1 */
/* !LINKSTO J1939Rm.SWS_J1939Rm_00042,1 */
/* *****************************************************************************
 *  Name                 : J1939Rm_MainFunction
 *  Description          : Main function of the J1939 Request Manager. Used for
 *                         scheduling purposes and time out supervision.
 *  Parameters           : None
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939RM_CODE) J1939Rm_MainFunction(void)
{
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
  if (J1939Rm_Initialized != (boolean)TRUE)
  {
    /* !LINKSTO EB_Ref.SWS_J1939Rm_00010.J1939Rm_MainFunction,1 */
    (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_MAINFUNCTION_SERVICEID, J1939RM_E_UNINIT);
  }
  else
#endif
  {
    /*Local Variables*/
    CONSTP2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr_Pbcfg = J1939Rm_PbCfg_Ptr;
    CONSTP2CONST(J1939Rm_RealStructType_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmConfigPtr_Pbcfg = TmpJ1939RmGlobalConfigPtr_Pbcfg->J1939RmConfigPtr;
    CONSTP2CONST(J1939Rm_GlobalConfig_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmGlobalConfigPtr = &J1939Rm_GlobalConfig;
    CONSTP2CONST(J1939Rm_Channel_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmChannelConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelConstStructPtr;
    CONSTP2CONST(J1939Rm_Node_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmNodeConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmNodeConstStructPtr;

    #if (J1939RM_COM_SUPPORT == STD_ON)
    CONSTP2CONST(J1939Rm_User_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmUserConstStructPtr = TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserConstStructPtr;
    CONSTP2CONST(J1939Rm_ComIpduRqstQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIpduRqstQueueTypeStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmComIpduRqstQueueTypeStructPtr;
    P2CONST(J1939Rm_ComIPdu_Const_Struct_Pbcfg, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIPduConstStructPtr;
    P2CONST(J1939Rm_ComIpduRqstQueueData_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmComIpduRqstQueueDataPtr;
    uint8 usr_idx = 0u;
    uint16 comipdu_idx = 0u;
    boolean ValidId=(boolean)FALSE;
    #endif

    P2CONST(J1939Rm_RqstTxQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmRqstTxQueueTypePtr;
    P2CONST(J1939Rm_AckmTxQueueType_Struct, AUTOMATIC, J1939RM_APPL_CONST) TmpJ1939RmAckmTxQueueTypePtr;
    CONSTP2VAR(J1939Rm_Channel_Ram_Struct, AUTOMATIC, J1939RM_APPL_CONST)TmpJ1939RmChannelRamStructPtr = TmpJ1939RmGlobalConfigPtr->J1939RmChannelRamStructPtr;
    uint32 TmpQueuePgn = 0u;
    uint16 TmpQueueUserId = 0u;
    uint8 TmpQueueSA = 0u;
    uint8 TmpQueueDA = 0u;
    uint8 QueueAckCode = 0u;
    uint8 QueueAckAddress = 0u;
    uint8 TmpQueuePriority = 0u;
    uint8 node_index= (uint8)0;
    uint8 ch_idx = 0u;
    boolean TmpQueuecheckTimeout = 0u;

    Std_ReturnType RqstRtrnRslt = E_NOT_OK;
    Std_ReturnType AckmRtrnRslt = E_NOT_OK;


    for (ch_idx= (uint8)0; ch_idx < TmpJ1939RmConfigPtr_Pbcfg->J1939RmChannelNr; ch_idx++)
    {
      if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmState == J1939RM_STATE_ONLINE)
      {
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
          /* SWR_R_J1939Rm004 */
          /*Decrement the 50Ms timer in the Main function and check if equal to 0 remove from the queue*/
           uint8 FiftyMsFeatureIterator = 0u;
          /* Deviation TASKING-1 */
          for(FiftyMsFeatureIterator= 0u;FiftyMsFeatureIterator<(J1939_TOTAL_NUMBER_OF_PGS);FiftyMsFeatureIterator++)
          {
              if(J1939Rm_GlobalConfig.J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[ch_idx][FiftyMsFeatureIterator].FiftyMsTimeoutTimer > (uint8)0)
              {
                  J1939Rm_GlobalConfig.J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[ch_idx][FiftyMsFeatureIterator].FiftyMsTimeoutTimer--;
              }
          }
#endif
          /*TxConfirmation Timer*/
          (void)J1939Rm_TxConfirmationTimer(ch_idx);

          /*Timeout supervision for Requests*/
          (void)J1939Rm_Requests_Timeout_Supervision(ch_idx);

          /*Transmission Handling*/
          if ((TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation == J1939RM_ACKM_TX_CONFIRMED) || (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation == J1939RM_COM_TX_CONFIRMED))
          {
              /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.COM_CONFIRMED_TO_NO_TX,1 */
              /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.ACKM_CONFIRMED_TO_NO_TX,1 */
              /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00019,1 */
              TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_NO_TX;
          }
          else
          {
            if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation == J1939RM_RQST_TX_CONFIRMED)
            {
              /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00022,1 */
              /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.RQST_CONFIRMED_TO_NO_TX,1 */
              TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_NO_TX;
              /*Entry of Rqst data on TxConfirmation into TimeoutSupervision Queue if CheckTimeout is (boolean)TRUE for the same User.*/
              /*Read Data from the Queue (Data transmitted and TxConfirmation is received now) to check if checktimeout is enabled for the User.*/

              /*Dequeue RQST*/
              /*Set J1939RmTxConfirmation = J1939RM_RQST_TX*/
              /*Set J1939RmTxConfirmationTimer = J1939RmTxConfirmationTimeout*/
              J1939Rm_Dequeue( J1939RM_TXPG_RQST,      /*Rqst=0*/
                               ch_idx,                 /*Channel Index*/
                               &TmpQueueUserId,        /*Calling module's user ID.*/
                               &TmpQueuePgn,           /*PGN of the Requested PG.*/
                               &TmpQueueSA,            /*Address of the Source node for Rqst*/
                               &TmpQueueDA,            /*Address of the destination node for Rqst*/
                               &TmpQueuePriority,      /*Priority of the Requested PG.*/
                               &TmpQueuecheckTimeout);
              /* !LINKSTO J1939Rm.SWS_J1939Rm_00017,1 */
              /* !LINKSTO EB_Ref.SWS_J1939Rm_00024.SendRequest,1*/
              if ((TmpQueuecheckTimeout == (boolean)TRUE) && (TmpQueueDA != J1939RM_BROADCAST_ADDR))
              {
                /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00024,1 */
                /*CheckTimeout is TRUE - Enqueue RQST from RQST Queue to TSV Queue for Timeout Supervision Monitoring.*/
                /*Enqueue data in TimerSupervision Queue and set Timeout Supervision Timer to time, to be monitored for timeout*/
                (void)J1939Rm_Enqueue_TSV_RQST( ch_idx, TmpQueueUserId, TmpQueuePgn, TmpQueueSA, TmpQueueDA );
              }
              else
              {
              }
            }
            else
            {

            }
          }
          if (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation == J1939RM_NO_TX)
          {
#if (J1939RM_COM_SUPPORT == STD_ON)
            /*COM Transmission Handling*/
            for (usr_idx= (uint8)0;((usr_idx<TmpJ1939RmConfigPtr_Pbcfg->J1939RmUserNr) && (ValidId == (boolean)FALSE));usr_idx++)
            {
              /*ComUser and COM Queue not empty*/
              if ((TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmUserType == (uint8)J1939RM_USER_COM) && (TmpJ1939RmComIpduRqstQueueTypeStructPtr[usr_idx].J1939RmComIpduRqstQueueCount !=  (uint8)0))
              {
                /*Dequeue COM*/
                /*Set J1939RmTxConfirmation = J1939RM_COM_RX*/
                TmpJ1939RmComIPduConstStructPtr = TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduConstStructPtr;
                TmpJ1939RmComIpduRqstQueueDataPtr = TmpJ1939RmComIpduRqstQueueTypeStructPtr[usr_idx].J1939RmComIpduRqstQueueDataPtr;
                for (comipdu_idx= (uint8)0; ((comipdu_idx<TmpJ1939RmUserConstStructPtr[usr_idx].J1939RmComIPduNr) && (ValidId == (boolean)FALSE)); comipdu_idx++)
                {
                  if ((TmpJ1939RmComIpduRqstQueueDataPtr[0].J1939RmComIpduRqstPgn == TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmComIPduPGN) && (TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation != J1939RM_COM_RX) && (TmpJ1939RmComIpduRqstQueueDataPtr[0].J1939RmComIpduRqstChannelId == TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmChannelId) )
                  {
                    /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_COM_RX,1 */
                    TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_COM_RX;
                    /* !LINKSTO EB_Ref.SWS_J1939Rm_00045.Com_TriggerIPDUSend,1 */
                    /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00004,1 */
                    Com_TriggerIPDUSend(TmpJ1939RmComIPduConstStructPtr[comipdu_idx].J1939RmUpperComIPduRef);
                    ValidId = (boolean)TRUE;
                  }
                  else
                  {

                  }
                }
              }
            }
#endif

            /*Requests Transmission Handling*/
            TmpJ1939RmRqstTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmRqstTxQueueTypeStructPtr;
            if (TmpJ1939RmRqstTxQueueTypePtr->J1939RmRqstTxQueueCount !=  (uint8)0) /*RQST Queue not empty*/
            {
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
              uint16 rear = 0u;
              J1939Rm_GlobalConfig.J1939Rm50MsSupervision.Rear[ch_idx] = (J1939Rm_GlobalConfig.J1939Rm50MsSupervision.Rear[ch_idx] +(uint16)1)%J1939_TOTAL_NUMBER_OF_PGS;
              rear = J1939Rm_GlobalConfig.J1939Rm50MsSupervision.Rear[ch_idx];
#endif

              J1939Rm_TXPG_RQST_QueueTop(
                              ch_idx,                 /*Channel Index*/
                              &TmpQueueUserId,        /*Calling module's user ID.*/
                              &TmpQueuePgn,           /*PGN of the Requested PG.*/
                              &TmpQueueSA,            /*Address of the Source node for Rqst*/
                              &TmpQueueDA,            /*Address of the destination node for Rqst*/
                              &TmpQueuePriority,      /*Priority of the Requested PG.*/
                              &TmpQueuecheckTimeout);
#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
              /* SWR_R_J1939RM004*/
              /*Intalizing the 50Ms timeout*/
              J1939Rm_GlobalConfig.J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[ch_idx][rear].PGNumber = TmpQueuePgn;
              J1939Rm_GlobalConfig.J1939Rm50MsSupervision.J1939Rm50MsSupervisionData[ch_idx][rear].FiftyMsTimeoutTimer = FIFTY_MS_TIME_OUT;
#endif

              /* !LINKSTO EB_Ref.SWS_J1939Rm_00009.BSW_CDD,1 */
              /* !LINKSTO EB_Ref.SWS_J1939Rm_00009.RTE,1 */
              (void)J1939Rm_EcuC_SetMetaDataCanId((uint8)(TmpQueuePriority << 2), (uint8)(TmpQueuePgn>>8), (uint8)TmpQueueDA, (uint8)TmpQueueSA, (EcuC_PduIdType)(TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRqstTx_Ecuc_PduId), J1939RM_MAINFUNCTION_SERVICEID);

              /* !LINKSTO EB_Ref.SWS_J1939Rm_00016.BSW_CDD,1 */
              /* !LINKSTO EB_Ref.SWS_J1939Rm_00016.RTE,1 */
              /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00022,1 */
              RqstRtrnRslt = J1939Rm_RequestTransmission((uint8)TmpQueuePgn, (uint8)(TmpQueuePgn>>8), (uint8)(TmpQueuePgn>>16), TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmRqstTxPduRef);
              if (RqstRtrnRslt == E_OK) /*Transmission was successful*/
              {
                /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_RQST_TX,1 */
                TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_RQST_TX;
                TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer = TmpJ1939RmConfigPtr_Pbcfg->J1939RmTxConfirmationTimeout;
              }
              else
              {
              }
            }
            else
            {
              /*RqstTxQueue is Empty*/
            }

            /*Acknowledgements Transmission Handling*/
            TmpJ1939RmAckmTxQueueTypePtr = TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmAckmTxQueueTypeStructPtr;
            if (TmpJ1939RmAckmTxQueueTypePtr->J1939RmAckmTxQueueCount !=  (uint8)0) /*ACKM Queue not empty*/
            {
              /* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00019,1 */
              /*Dequeue ACKM*/
              /*Set J1939RmTxConfirmation = J1939RM_ACKM_TX*/
              /*Set J1939RmTxConfirmationTimer = J1939RmTxConfirmationTimeout*/
              /*AckmTxQueue is not Empty. Read Data to be transmitted next*/
              J1939Rm_Dequeue(J1939RM_TXPG_ACKM,     /*Ackm=1*/
                              ch_idx,                /*Channel Index*/
                              &TmpQueueUserId,       /*Calling module's user ID.*/
                              &TmpQueuePgn,          /*PGN of the Acknowledged PG.*/
                              &QueueAckCode,         /*Type of acknowledgement for Ackm*/
                              &QueueAckAddress,      /*Address of the node that sent the request for Ackm*/
                              &TmpQueuePriority,     /*Priority of the Acknowledgement PG.*/
                              &TmpQueuecheckTimeout );
              /*Transmit Acknowledgement*/

              /*MetaData Information*/
              (void)J1939Rm_ValidNode(TmpQueueUserId, &node_index);
              /* !LINKSTO J1939Rm.SWS_J1939Rm_00123,1*/
              (void)J1939Rm_EcuC_SetMetaDataCanId((uint8)(TmpQueuePriority), (uint8)(TmpQueuePgn>>8), (uint8)0xFF, TmpJ1939RmNodeConstStructPtr[node_index].J1939RmNodeAddress, 
              (EcuC_PduIdType)(TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckmTx_Ecuc_PduId), J1939RM_MAINFUNCTION_SERVICEID);

              /* !LINKSTO J1939Rm.SWS_J1939Rm_00044,1 */
              AckmRtrnRslt = J1939Rm_AckTransmission(QueueAckCode, QueueAckAddress, (uint8)TmpQueuePgn, (uint8)(TmpQueuePgn>>8), (uint8)(TmpQueuePgn>>16), TmpJ1939RmChannelConstStructPtr[ch_idx].J1939RmAckmTxPduRef);
              if (AckmRtrnRslt == E_OK) /*Transmission was successful*/
              {
                /* !LINKSTO J1939Rm.EB.Dsn.J1939RmTxConfirmation.J1939RM_ACKM_TX,1 */
                TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmation = J1939RM_ACKM_TX;
                TmpJ1939RmChannelRamStructPtr[ch_idx].J1939RmTxConfirmationTimer = TmpJ1939RmConfigPtr_Pbcfg->J1939RmTxConfirmationTimeout;
              }
              else
              {
                (void)J1939Rm_Enqueue_TXPG_ACKM(
                                       ch_idx,            /*Channel Index*/
                                       TmpQueueUserId,    /*Calling module's user ID.*/
                                       TmpQueuePgn,       /*PGN of the Acknowledged PG.*/
                                       QueueAckCode,      /*Type of acknowledgement for Ackm.*/
                                       QueueAckAddress,   /*Address of the node that sent the request for Ackm*/
                                       TmpQueuePriority   /*Priority of the Acknowledgement PG.*/
                                     );
              }
            }
            else
            {
                /* AckmTxQueue is Empty */
            }
          }
        }
    }
  }
}

#if (J1939RM_TIMEOUTSUPERVISION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_CancelRequestTimeout_Operation (uint8 UserId, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress)
{
  J1939Rm_CancelRequestTimeout(UserId, channel, requestedPgn, destAddress);
  return E_OK;

}
#endif

FUNC(BufReq_ReturnType, J1939RM_CODE) J1939Rm_PduRTpStartOfReception
(
  PduIdType PduId,
  PduLengthType PduLength,
  P2VAR(PduLengthType, AUTOMATIC,J1939RM_APPL_DATA) RxBufferSizePtr
)
{
  TS_PARAM_UNUSED(PduId);
  TS_PARAM_UNUSED(PduLength);
  TS_PARAM_UNUSED(RxBufferSizePtr);

#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Rm.EB._Invalid_Call,1 */
  (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SID_PDURTPSTARTOFRECEPTION, J1939RM_E_INVALID_CALL);
#endif /* J1939RM_DEV_ERROR_DETECT == STD_ON */

  return BUFREQ_E_NOT_OK;
}

FUNC(BufReq_ReturnType, J1939RM_CODE) J1939Rm_PduRTpCopyRxData
(
  PduIdType PduId,
  P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPointer,
  P2VAR(PduLengthType, AUTOMATIC,J1939RM_APPL_DATA) RxBufferSizePtr
)
{
  TS_PARAM_UNUSED(PduId);
  TS_PARAM_UNUSED(PduInfoPointer);
  TS_PARAM_UNUSED(RxBufferSizePtr);

#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Rm.EB._Invalid_Call,1 */
  (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID, J1939RM_SID_PDURTPCOPYRXDATA, J1939RM_E_INVALID_CALL);
#endif /* J1939RM_DEV_ERROR_DETECT == STD_ON */

  return BUFREQ_E_NOT_OK;
}


FUNC(void, J1939RM_CODE) J1939Rm_PduRTpRxIndication
(
    PduIdType RxPduId,
    NotifResultType Result
)
{
  TS_PARAM_UNUSED(RxPduId);
  TS_PARAM_UNUSED(Result);

#if(J1939RM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Rm.EB._Invalid_Call,1 */
  (void)Det_ReportError(J1939RM_MODULE_ID, J1939RM_INSTANCE_ID,J1939RM_SID_PDURTPRXINDICATION, J1939RM_E_INVALID_CALL);
#endif /* J1939RM_DEV_ERROR_DETECT == STD_ON */

  return;
}


#define J1939RM_STOP_SEC_CODE
#include <J1939Rm_MemMap.h>

/*==================[end of file]============================================*/
