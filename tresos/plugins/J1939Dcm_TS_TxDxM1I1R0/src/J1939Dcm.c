/* --------{ EB Automotive C Source File }-------- */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 2.7 (Advisory)
 *    There should be no unused parameters in functions.
 *
 *    Reason:
 *    - The J1939Dcm module doesn't implement reception API related to PDUR ,
 *    so related API's are defined for bypass compilation errors or related
 *    feature not implemented or it is already used based on conditional directive.
 *
 *  MISRAC2012-2) Deviated Rule: Dir 4.5 (Advisory)
 *    Identifiers in the same name space with overlapping visibility should be typographically unambiguous.
 *
 *    Reason:
 *    - it is OK , no need to change it .
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason: False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * False positive from tasking compiler, the values are changed
 * inside the J1939Dcm_DM05_RequestProcessing and J1939Dcm_ReportDTC_RequestProcessing
 * only relevant for tasking 63r1p2 on TC38XQ
 */

/* General requirements that are satisfied by this code */

/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00085,1 */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00089,1 */

/* Include own header file. */
#include <J1939Dcm.h>

/* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00109,1 */
#include <J1939Rm.h>

#include <TSAutosar.h>                   /* Specific standard types */

/* include internal header */
#include <J1939Dcm_internal.h>

#include <PduR_J1939Dcm.h>

/* #include <SchM_J1939Dcm.h> */

#include <J1939Dcm_Lcfg.h>
#include <J1939Rm.h>

#include <J1939Dcm_Trace.h>              /* Dbg related macros for J1939Dcm */
/* Includes Development Error Tracer interfaces if enabled. */
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

#define  J1939DCM_START_SEC_VAR_INIT_8
#include <J1939Dcm_MemMap.h>

#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
VAR(uint8, J1939DCM_VAR) J1939Dcm_TimeoutMonitorFlag=0;
#endif /*( J1939DCM_IF_TX_AVAILABLE == STD_ON )*/

#define J1939DCM_STOP_SEC_VAR_INIT_8
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_VAR_CLEARED_8
#include <J1939Dcm_MemMap.h>

/* VARIABLES*/
/* Checks if for every DM except J1939Dcm_Init() if the J1939DCM is initialised or not */
static VAR(uint8, J1939DCM_VAR) J1939Dcm_InitStatus;

/* Variable that holds J1939Dcm general status, shows if a request is active...*/
VAR(uint8, J1939DCM_VAR) J1939Dcm_GeneralStatus;

VAR(uint8, J1939DCM_VAR) J1939Dcm_ChannelsState[J1939DCM_NB_OF_GENERIC_COMMCHANNELS];

static VAR(uint8, J1939DCM_VAR) J1939Dcm_TxPduIdState[J1939DCM_TX_SIZE];

/* dedicated buffer for DMx request processing */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00115,1 */
VAR(uint8, J1939DCM_VAR) J1939Dcm_CommonBuffer[J1939DCM_COMMON_BUFFER_SIZE];

#if(J1939DCM_DM01_AVAILABLE == STD_ON)
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00114,1 */
/* dedicated buffer for DM1 request processing */
VAR(uint8, J1939DCM_VAR) J1939Dcm_DM1Buffer[J1939DCM_DM01_BUFFER_SIZE];
/* Stores number of DTC reported by Dem for the current cycle */
VAR(uint8, J1939DCM_VAR) J1939Dcm_NbOfDTCTrigeredByDEM;
/* Store the node index of processed cyclic DM1 per each seconds. */
static VAR(uint8, J1939DCM_VAR) J1939Dcm_IdxInConfiguredNodes;
#endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */
#if( J1939DCM_MSG_LENGTH_8_BITS == STD_ON)
VAR(J1939Dcm_MsgLenType, J1939DCM_VAR) J1939Dcm_CurPosInTxBuff;
#endif /* ( J1939DCM_MSG_LENGTH_8_BITS == STD_ON) */

VAR(NetworkHandleType, J1939DCM_VAR) J1939Dcm_ComMChannels[J1939DCM_NB_OF_GENERIC_COMMCHANNELS] ;

static VAR(uint8, J1939DCM_VAR) J1939Dcm_RmUserRef[J1939DCM_NB_OF_CONFIGURED_NODES] ;

#define  J1939DCM_STOP_SEC_VAR_CLEARED_8
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Dcm_MemMap.h>
/* used to send DM Acknowledgment code via J1939Rm_SendAck ,after
   mapping from J1939Dcm internal Ack codes to J1939Rm Ack codes */
static VAR(J1939Rm_AckCode, J1939DCM_VAR) J1939Rm_Acknowledge;  /* J1939Rm DM Acknowledge type */

/* used to store the meta data info for DMX message */
static VAR(J1939Dcm_MetaDataInfoType, J1939DCM_VAR) J1939Dcm_DMxMetaDataInfo;

#if( J1939DCM_DM01_AVAILABLE == STD_ON )
/* used to store the meta data info for DM1 message */
static VAR(J1939Dcm_MetaDataInfoType, J1939DCM_VAR) J1939Dcm_DM1MetaDataInfo;
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */

#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
/* Table for Tx buffers specific information */
static VAR(J1939Dcm_TPTxInfoType, J1939DCM_VAR) J1939Dcm_TxBuffInfo[J1939DCM_TP_TX_SIZE];
#endif /* (J1939DCM_TP_TX_AVAILABLE == STD_ON) */

/* message context used by J1939Dcm */
VAR(J1939Dcm_MsgContextType, J1939DCM_VAR) J1939Dcm_MsgContext;

#if(J1939DCM_DM13_AVAILABLE == STD_ON)
/* Holds the J1939Dcm DM-13 status information*/
VAR(J1939Dcm_DM13_StatusInfoType, J1939DCM_VAR) J1939Dcm_DM13_StatusInfo;
#endif
/*Post Build Configuration pointer*/
P2CONST( J1939Dcm_ConfigType, J1939DCM_VAR, J1939DCM_APPL_CONST )
  J1939Dcm_ConfigPtr;
#define  J1939DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_VAR_INIT_16
#include <J1939Dcm_MemMap.h>

#if(J1939DCM_DM13_AVAILABLE == STD_ON)
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00129,1 */
/* Holds the BroadcastStatusMask information to be reported to BSWM Module*/
VAR(uint16, J1939DCM_VAR) J1939Dcm_DM13_BroadcastStatusMask = J1939DCM_DM13_RESET_NORMAL_BROADCAST_MODE;
#endif
#define  J1939DCM_STOP_SEC_VAR_INIT_16
#include <J1939Dcm_MemMap.h>

#define  J1939DCM_START_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

#if(J1939DCM_DM01_AVAILABLE == STD_ON)
/* Variable that holds for module J1939Dcm the number of main function till the next DM1 transmit should be triggered. */
VAR(uint16, J1939DCM_VAR) J1939Dcm_CyclesTillNextDM1Transmit;
#endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */
#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
VAR(uint16, J1939DCM_VAR) J1939Dcm_TimeoutCycles;
#endif /* ( J1939DCM_IF_TX_AVAILABLE == STD_ON )*/
#if( J1939DCM_MSG_LENGTH_16_BITS == STD_ON)

VAR(J1939Dcm_MsgLenType, J1939DCM_VAR) J1939Dcm_CurPosInTxBuff;

#endif /* ( J1939DCM_MSG_LENGTH_16_BITS == STD_ON) */

#if(J1939DCM_DM04_25_AVAILABLE == STD_ON)
/* Variable that holds the number of processed Freeze frames per DM04/DM25 request. */
VAR(uint16, J1939DCM_VAR) J1939Dcm_NbOfProcessedFFPerRequest;
#endif /* (J1939DCM_DM04_25_AVAILABLE == STD_ON) */

#define  J1939DCM_STOP_SEC_VAR_CLEARED_16
#include <J1939Dcm_MemMap.h>

#define J1939DCM_START_SEC_VAR_CLEARED_32
#include <J1939Dcm_MemMap.h>

#if(J1939DCM_DM01_AVAILABLE == STD_ON)
static VAR(uint32, J1939DCM_VAR) J1939Dcm_TrigeredDTCByDEM[J1939DCM_MAX_NB_OF_DTC_TRIGGERED_BY_DEM];
#endif /* J1939DCM_DM01_AVAILABLE == STD_ON */

#define J1939DCM_STOP_SEC_VAR_CLEARED_32
#include <J1939Dcm_MemMap.h>


#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
#define J1939Dcm_InitCheck(J1939Dcm_ModulId, J1939Dcm_ApiId, J1939Dcm_ErrId)    \
if( J1939Dcm_InitStatus != J1939DCM_INIT_OK )          \
{                                \
    (void)Det_ReportError( J1939Dcm_ModulId, (uint8)0, J1939Dcm_ApiId, J1939Dcm_ErrId); \
}\
else
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

#define  J1939DCM_START_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

/* ================start internal functions prototype section ====================== */

static FUNC(Std_ReturnType, J1939DCM_CODE) J1939Dcm_SetAndCheckChannelState(    VAR(NetworkHandleType, AUTOMATIC) channel,
                                        P2VAR(uint8, AUTOMATIC, AUTOMATIC) node,
                                        VAR(J1939Dcm_StateType, AUTOMATIC) newState,
                                        VAR(uint8, AUTOMATIC) ApiId );

static FUNC(Std_ReturnType, J1939DCM_CODE) J1939Dcm_GetChannelState( VAR(uint8, AUTOMATIC) TxPduIdIndex );

INLINE FUNC(void, J1939DCM_CODE) J1939Dcm_TransmitInternal( VAR(J1939Dcm_MetaDataInfoType, AUTOMATIC) MetaData );


/* ================stop internal functions prototype section ====================== */

INLINE FUNC(void, J1939DCM_CODE) J1939Dcm_TransmitInternal( VAR(J1939Dcm_MetaDataInfoType, AUTOMATIC) MetaData )
{
    VAR(PduInfoType, AUTOMATIC) tPduInfoVar;

    /* TX information */
    VAR(uint8, AUTOMATIC)    tTXInfo = (uint8)0;

    VAR(Std_ReturnType, AUTOMATIC)    tResult = (Std_ReturnType)0;

#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
    VAR(Std_ReturnType, AUTOMATIC)    setMetaDataSrcResult = (Std_ReturnType)E_OK;
    VAR(Std_ReturnType, AUTOMATIC)    setMetaDataDestResult = (Std_ReturnType)E_OK;
    VAR(Std_ReturnType, AUTOMATIC)    setMetaDataPrioResult = (Std_ReturnType)E_OK;
#endif
    VAR(Std_ReturnType, AUTOMATIC)    setMetaDataResult = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC)    metaDataCanId = (uint32)0;

    VAR(sint8, AUTOMATIC)    metaDataPositionIdx = (sint8)0;

    VAR(uint8, AUTOMATIC)    metaDataShiftVal = (uint8)0;

    VAR(uint32, AUTOMATIC)    currMetaDataVal = (uint32)0;

    VAR(uint8, AUTOMATIC)    metaDataInfo[4];
    /* used for reseting the request status, prepared for reseting DMx info */
    /* prepared for reseting the DMx info */
    VAR(uint8, AUTOMATIC) tResetInfo = J1939DCM_RESET_COMMON_REQUEST_INFO;
    /* Keep common buffer locked for situation when no negative acknowledgment will be send. */
    VAR(uint8, AUTOMATIC) tKeepBuffer = (uint8)0x01;
    VAR(PduInfoType, AUTOMATIC) PduInfoTemp;
    VAR(PduIdType, AUTOMATIC) TxPduRefId = 0 ;
    /*Used for internal loop to get TxPduRefId*/
    VAR(uint8, AUTOMATIC) i_pduId = 0 ;
    DBG_J1939DCM_TRANSMITINTERNAL_ENTRY(MetaData);

    /* Set the destination address (via MetaData) according to the source
    address of the request, or to 0xFF when the destination of the request was 0xFF */
    if( MetaData.destAddress != (uint8)0xFF )
    {
        metaDataInfo[0] = MetaData.destAddress;
        metaDataInfo[1] = MetaData.receivedsourceAddress;    /* dest address */
    }
    else
    {
        metaDataInfo[0] = MetaData.NodePreferredAddress;
        metaDataInfo[1] = (uint8)0xFF;
    }

    /* Add the information used for metadata. */

    metaDataInfo[2] = (uint8)0xFF;
    metaDataInfo[3] = (uint8)(MetaData.priority << 2);

#if( J1939DCM_DM01_AVAILABLE == STD_ON )
    if( J1939DCM_CHECK_DM1_REQUEST_PROCESSING_ACTIVE() )
    {
        /* Set information that transmission is for DM1 */
        tTXInfo |= J1939DCM_TX_DM1;

        /* Point to data information. */
        tPduInfoVar.SduDataPtr = J1939Dcm_DM1Buffer;

        /* prepared for reseting the DM1 info */
        tResetInfo = J1939DCM_RESET_DM1_REQUEST_INFO;

        /* Keep DM1 buffer locked if the transmission will be through TP or IF.  */
        tKeepBuffer = (uint8)0x10;
    }
    else
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */
    {
        /* Set information that transmission is for DMX */
        tTXInfo |= J1939DCM_TX_DMX;

        /* Point to data information. */
        tPduInfoVar.SduDataPtr = J1939Dcm_CommonBuffer;
    }

    /* A positive response will be received. */
    /* Deviation TASKING-2 */
    if( J1939Dcm_MsgContext.Response == J1939DCM_NORMAL_RESPONSE )
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00127,1 */
        /* Check if the channel for DM is online and the corresponding Pdu is on idle state. */
        if((J1939Dcm_ChannelsState[J1939Dcm_ConfigPtr->J1939DcmTxPduRef[J1939Dcm_MsgContext.DMIdx].J1939DcmChannelIdx] == J1939DCM_STATE_ONLINE) && /*Check Node Channel state*/
        ( J1939Dcm_TxPduIdState[ J1939DCM_TXPDUID_IDX() ] == J1939DCM_TX_PDU_ID_IDLE ))
        {
            /*Get TxRefID from postbuild configuration*/
            J1939DCM_TXPDUID_REF(i_pduId,TxPduRefId);

#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
            /* check if for current DM transmission is via TP */
            if( J1939DCM_CHECK_DM_TRANSMISSION_MODE_IS_TP() )
            {
                /* Set information that transmission to be performed on TP */
                tTXInfo |= J1939DCM_TX_TP;

                /* For Tp transmission the transmitted data should be only MetadaData values so
                 * the pointer will be increased accordingly with payload length. */
                tPduInfoVar.SduDataPtr = NULL_PTR ;

                /* Cyclic DM will always stay on the second position in J1939Dcm_TxBuffInfo. */
                J1939Dcm_TxBuffInfo[ J1939DCM_TXPDUID_IDX() ].Sent_Bytes_Tx = (J1939Dcm_MsgLenType)0;

                J1939Dcm_TxBuffInfo[ J1939DCM_TXPDUID_IDX() ].Bytes_To_Send_Tx = J1939Dcm_MsgContext.resDataLen;

                if(J1939Dcm_TxPduIds[ J1939DCM_TXPDUID_IDX() ].MetaDataLength==1u)
                {
                    setMetaDataSrcResult=EcuC_SetMetaDataSourceAddr(TxPduRefId,&PduInfoTemp,(uint16)metaDataInfo[0]);
                }
                else if (J1939Dcm_TxPduIds[ J1939DCM_TXPDUID_IDX() ].MetaDataLength==2u)
                {
                    setMetaDataSrcResult=EcuC_SetMetaDataSourceAddr(TxPduRefId,&PduInfoTemp,(uint16)metaDataInfo[0]);
                    setMetaDataDestResult=EcuC_SetMetaDataTargetAddr(TxPduRefId,&PduInfoTemp,(uint16)metaDataInfo[1]);
                }
                else
                {
                    setMetaDataSrcResult=EcuC_SetMetaDataSourceAddr(TxPduRefId,&PduInfoTemp,(uint16)metaDataInfo[0]);
                    setMetaDataDestResult=EcuC_SetMetaDataTargetAddr(TxPduRefId,&PduInfoTemp,(uint16)metaDataInfo[1]);
                    setMetaDataPrioResult=EcuC_SetMetaDataPriority(TxPduRefId,&PduInfoTemp,metaDataInfo[3]);
                }

                if( ( (setMetaDataDestResult==E_OK) && (setMetaDataPrioResult==E_OK) ) && (setMetaDataSrcResult==E_OK) )
                {
                    setMetaDataResult=E_OK;
                }
            }
            else
#endif /* (J1939DCM_TP_TX_AVAILABLE == STD_ON) */
            {
                /* transmission is via Interface */
                tTXInfo |= J1939DCM_TX_IF;
                /* get related canid. */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00194,1 */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00195,1 */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00196,1 */
                for(metaDataPositionIdx=3;metaDataPositionIdx>=0;metaDataPositionIdx--)
                {
                    metaDataShiftVal= metaDataPositionIdx*8;
                    currMetaDataVal=(uint32)metaDataInfo[metaDataPositionIdx];
                    currMetaDataVal <<= metaDataShiftVal;
                    metaDataCanId |= (currMetaDataVal);
                }

                /* Set metadata in ecuc. */
                setMetaDataResult = EcuC_SetMetaDataCanId(TxPduRefId,&PduInfoTemp,metaDataCanId);
            }
            /* Transmit data length only which doesn't include MetaData length. */
            tPduInfoVar.SduLength = J1939Dcm_MsgContext.resDataLen;
            if(setMetaDataResult == E_OK)
            {


#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
                /* check if for current DM transmission is via TP */
                if(J1939DCM_CHECK_DM_TRANSMISSION_MODE_IS_TP())
                {
                    /* !LINKSTO J1939Dcm.EB.Transmit.Tp,1 */
                    /* Transmit the information via J1939Tp. */
                    tResult = PduR_J1939DcmTpTransmit( J1939Dcm_TxPduIds[ J1939DCM_TXPDUID_IDX() ].PduSymbolicName, &tPduInfoVar );
                }
                else
#endif /* J1939DCM_TP_TX_AVAILABLE == STD_ON */
                {
                    /* the current DM transmission is via IF. */
                    /* !LINKSTO J1939Dcm.EB.Transmit.If,1 */
                    /* Transmit the information via CanIf. */
                    tResult = PduR_J1939DcmIfTransmit( J1939Dcm_TxPduIds[ J1939DCM_TXPDUID_IDX() ].PduSymbolicName, &tPduInfoVar );
                }
                /* If transmission was OK */
                if( tResult == E_OK )
                {
                    /* set current state for the PduId  */
                    J1939Dcm_TxPduIdState[ J1939DCM_TXPDUID_IDX() ] = tTXInfo;

                    /* Keep buffer locked until corresponding confirmation come. */
                    tResetInfo |= tKeepBuffer;
#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
                    if(J1939DCM_TX_IF == (tTXInfo & J1939DCM_TX_IF) )
                    {
                       /* Start Confirmation Timeout Timer for IF Transmission*/
                       /* !LINKSTO J1939Dcm.EB.IfTxConfTimeout.Start,1 */
                       J1939Dcm_TimeoutCycles = (uint16)0;
                       J1939Dcm_TimeoutMonitorFlag = (uint8)1;
                    }
#endif/*( J1939DCM_IF_TX_AVAILABLE == STD_ON ) */
                }
            }
            else
            {

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.WrongPDUSDU,1 */
        (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_MAINFUNCTION, J1939DCM_E_INVALID_PDU_SDU_ID);
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

            }
        }
        else
        {
            /* if not yet online or no connection available, wait another cycle */
            /* set information that processing is done and TX is needed */
            J1939DCM_SET_DM_PROCESSING_DONE_TX_NEEDED();

            /* keep request information */
            tResetInfo = (uint8)0xFF;

        }

    }
    else
    {
        /* Deviation TASKING-2 */
        if( J1939Dcm_MsgContext.Response != J1939DCM_NO_RESPONSE )
        {

            /* If destination address was broadcast (0xFF) then no acknowledgment shall be send.
             * This is according with SAE J1939-73 [ J1939Dcm.ASR42.SWS_J1939Dcm_00113 ] */
            if( MetaData.destAddress != (uint8)0xFF )
            {
                /* J1939Dcm ack codes can't be passed directly to J1939Rm_SendAck ,
                   it is required to map between J1939Dcm internal ack codes and J1939Rm ack codes
                   to avoid future changes in j1939Rm ack codes values */
                /* Deviation TASKING-2 */
                switch (J1939Dcm_MsgContext.Acknowledge)
                {
                    case (J1939DCM_ACK_POSITIVE):
                        J1939Rm_Acknowledge=J1939RM_ACK_POSITIVE;
                        break;
                    case (J1939DCM_ACK_NEGATIVE):
                        J1939Rm_Acknowledge=J1939RM_ACK_NEGATIVE;
                        break;
                    default:
                        J1939Rm_Acknowledge=J1939RM_ACK_NEGATIVE;
                        break;
                }
                /* Inform RM regarding this negative ACK. */
                if(    E_OK == J1939Rm_SendAck(MetaData.J1939RmUserId, J1939Dcm_ComMChannels[J1939Dcm_ConfigPtr->J1939DcmTxPduRef[J1939Dcm_MsgContext.DMIdx].J1939DcmChannelIdx],
                               (uint32)J1939Dcm_ConfiguredDMs[J1939Dcm_MsgContext.DMIdx].PGN,
                                J1939Rm_Acknowledge, MetaData.receivedsourceAddress, MetaData.priority )
                )
                {
                    /* Only for misra. */
                }
            }

        }

    }

    /* reset request information */
    J1939DCM_RESET_DM_INFO( tResetInfo );

    DBG_J1939DCM_TRANSMITINTERNAL_EXIT(MetaData);

}

/* Deviation MISRAC2012-1 <1> */
/* Deviation MISRAC2012-2 <1> */
static FUNC(Std_ReturnType, J1939DCM_CODE) J1939Dcm_SetAndCheckChannelState(VAR(NetworkHandleType, AUTOMATIC) channel, P2VAR(uint8, AUTOMATIC, AUTOMATIC) node,
                                                                            VAR(J1939Dcm_StateType,AUTOMATIC) newState, VAR(uint8, AUTOMATIC) ApiId)
{
    /*Local Variables*/
    VAR(Std_ReturnType, AUTOMATIC) tRetval =      E_NOT_OK;    /*Standard return value*/
    VAR(uint8, AUTOMATIC) u8NodeIndex =          (uint8)0x00;  /*Local Variable used to loop through configured nodes*/
    VAR(uint8, AUTOMATIC) u8ChannelIndex =       (uint8)0x00;  /*Local variable used to loop through channels*/
    VAR(uint8, AUTOMATIC) u8RealChannelIndex =   (uint8)0x00;  /*Local variable used get the index in the J1939DcmChannel array*/
    VAR(uint8, AUTOMATIC) u8DmIndex =            (uint8)0x00;  /*Local counter used to loop through configured DMS*/
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00138,1 */
    VAR(uint8, AUTOMATIC) u8tErrorId = J1939DCM_E_INVALID_STATE; /*Local Variable for ErrorID*/
#else
    TS_PARAM_UNUSED(ApiId);      /* suppress compiler warning */
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    DBG_J1939DCM_SETANDCHECKCHANNELSTATE_ENTRY(channel, node, newState, ApiId);
    /* Deviation TASKING-1 */
    for(u8NodeIndex = (uint8)0x00; u8NodeIndex < J1939DCM_NB_OF_CONFIGURED_NODES; u8NodeIndex++)  /* Search in all configured nodes. */
    {
        if( *node == J1939Dcm_ConfiguredNodes[u8NodeIndex].NodeSymbolicName )  /* check if the desired node match with one that is configured. */
        {
            break;  /* The desired node is found then save the index */
        }
    }
    if( u8NodeIndex < J1939DCM_NB_OF_CONFIGURED_NODES )  /* Check if all nodes were checks and the desired one was found. */
    {
        *node = u8NodeIndex;    /* node is an in/out parameter set the value of the index in the node */
        /* For all configured channel from this node is search the desired channel. */
        for(u8ChannelIndex = J1939Dcm_ConfiguredNodes[u8NodeIndex].FirstComMChannelIdx; u8ChannelIndex <= J1939Dcm_ConfiguredNodes[u8NodeIndex].LastComMChannelIdx; u8ChannelIndex++ )
        {
            if( channel == J1939Dcm_ConfigPtr->J1939DcmConfiguredChannels[u8ChannelIndex] )  /* The channel is found. */
            {
                /*Macro used getting the real channel from J1939DcmConfiguredChannels to the list of all available channels J1939Dcm_ComMChannels*/
                J1939DCM_GET_REAL_CHANNEL_INDEX(u8RealChannelIndex,u8ChannelIndex);
                if( newState < J1939DCM_CHECKSTATE )      /* Now the desired operation is to set the node-channel state. */
                {
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00126.Online,1 */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00126.Offline,1 */
                    J1939Dcm_ChannelsState[u8RealChannelIndex] = newState; /*Set the channel State*/
                    if( newState == J1939DCM_STATE_OFFLINE)
                    {
                        J1939Dcm_GeneralStatus &= (uint8)0xFE;           /*Reset Buffer locked*/
                        /* Deviation TASKING-1 */
                        for(u8DmIndex = 0; u8DmIndex < J1939DCM_TX_SIZE; u8DmIndex++)     /* Cycle between all configured DMs. */
                        {
                           if(J1939Dcm_ConfigPtr->J1939DcmTxPduRef[u8DmIndex].J1939DcmNodeId == J1939Dcm_ConfiguredNodes[u8NodeIndex].NodeSymbolicName) /*Check to see if this DM is configured for this node*/
                           {
                                J1939Dcm_TxPduIdState[u8DmIndex] = J1939DCM_TX_PDU_ID_IDLE; /*State is offline, Reset TxState to idle , no more transmissions for this DM*/
                           }
                           else
                           {
                                /*do nothing the current dm we are checking is not configured on this speciffic node*/
                           }
                        }
                    }
                    else
                    {
                        /*Nothing to do, nothing relevant for setting a node-channel state to J1939DCM_STATE_ONLINE*/   
                    }
                        tRetval = E_OK;        /* Exit the function with success. */
                }
                else
                {
                    if(J1939Dcm_ChannelsState[u8RealChannelIndex] == J1939DCM_STATE_ONLINE)  /* Check the channel state, see if it is online. */
                    {
                        tRetval = E_OK;    /* Exit the function with success. */
                    }
                }
                break;
            }
        }
    }
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    if( tRetval != E_OK)
    {
        if( u8NodeIndex >= J1939DCM_NB_OF_CONFIGURED_NODES )
        {
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00147,1 */
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00149,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.INVALIDNODE,1 */
            u8tErrorId = J1939DCM_E_INVALID_NODE;
        }
        else
        {
            if(u8ChannelIndex > J1939Dcm_ConfiguredNodes[u8NodeIndex].LastComMChannelIdx )
            {
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00148,1 */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00150,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.INVALIDCHANNEL,1 */
                u8tErrorId = J1939DCM_E_INVALID_CHANNEL;
            }
        }
        (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, ApiId, u8tErrorId);
    }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

    DBG_J1939DCM_SETANDCHECKCHANNELSTATE_EXIT(tRetval, channel, node, newState, ApiId);
    return tRetval;

}

/* Indicates reception of a Request PG. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00101,1 */
/* Deviation MISRAC2012-2 <1> */
FUNC(void, J1939DCM_CODE) J1939Dcm_RequestIndication(    VAR(uint8, AUTOMATIC) node,
                            VAR(NetworkHandleType, AUTOMATIC) channel,
                            VAR(uint32, AUTOMATIC) requestedPgn,
                            VAR(uint8, AUTOMATIC) sourceAddress,
                            VAR(uint8, AUTOMATIC) destAddress,
                            VAR(uint8, AUTOMATIC) priority )
{

    /* Return value of this function. */
    VAR(Std_ReturnType, AUTOMATIC) tRetval = E_NOT_OK;

    /* Local variable used for parsing */
    VAR(uint8, AUTOMATIC) tIdx = (uint8)0x00;

    VAR(uint8, AUTOMATIC) tnode = node;

    DBG_J1939DCM_REQUESTINDICATION_ENTRY(node, channel, requestedPgn, sourceAddress, destAddress, priority);

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00004,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.UNINIT,1 */
    J1939Dcm_InitCheck(J1939DCM_MODULE_ID, J1939DCM_REQUESTINDICATION,J1939DCM_E_UNINIT)
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    {

        /* Check if the ComMChannel is online for the desired node. */
        tRetval = J1939Dcm_SetAndCheckChannelState( channel, &tnode, J1939DCM_CHECKSTATE, J1939DCM_REQUESTINDICATION );

        /* If the channel is online then go further. */
        if( tRetval == E_OK )
        {

            /* Check if request is allowed to go through */
            /* if buffer is locked request will receive a N_ACK */
            if( J1939DCM_CHECK_COMMON_BUFFER_UNLOCKED() )
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00007.LockBuff,1 */
                /* !LINKSTO J1939Dcm.EB.Dsn.commonBuffer.lock,1 */
                /* lock the buffer */
                J1939DCM_SET_COMMON_BUFFER_LOCKED();

                /* Extract the start index in supported DM */
                tIdx = J1939Dcm_ConfiguredNodes[tnode].FirstDMIdx;

                /* Cycle between all configured DMs. */
                for( ; tIdx <= J1939Dcm_ConfiguredNodes[tnode].LastDMIdx; tIdx++)
                {
                    /* check after the desired PGN. */
                    if( requestedPgn == (uint32)J1939Dcm_ConfiguredDMs[tIdx].PGN )
                    {
                        /* Stop searching because the PGN was found. */
                        break;
                    }
                }

                /* Check if the PGN was found. */
                if( tIdx <= J1939Dcm_ConfiguredNodes[tnode].LastDMIdx )
                {
                    /* set meta data info */

                    /* store DM index */
                    J1939Dcm_DMxMetaDataInfo.DMIdx = tIdx;

                    /* store node symbolic name\node address */
                    J1939Dcm_DMxMetaDataInfo.NodeId = J1939Dcm_ConfiguredNodes[tnode].NodeSymbolicName;
                    /* store J1939Rm User Id  */
                    J1939Dcm_DMxMetaDataInfo.J1939RmUserId = J1939Dcm_RmUserRef[tnode];
                    /* store destination address */
                    J1939Dcm_DMxMetaDataInfo.destAddress = destAddress;
                    /* store source address */
                    J1939Dcm_DMxMetaDataInfo.receivedsourceAddress = sourceAddress;
                    /* store Node Preferred address */
                    J1939Dcm_DMxMetaDataInfo.NodePreferredAddress = J1939Dcm_ConfiguredNodes[tnode].J1939NmNodePreferredAddress;
                    /* store priority */
                    J1939Dcm_DMxMetaDataInfo.priority = priority;
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00007.ProcessDM,1 */
                    J1939DCM_SET_DMX_REQUEST_PRESENT();
                }
                else
                {
                    /* PGN\DM is not configured for the current node */
                    /* we need to unlock the buffer */
                    J1939DCM_RESET_COMMON_BUFFER_LOCKED();

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
                    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00006,1 */
                   /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.INVALIDPGN,1 */
                    (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_REQUESTINDICATION,J1939DCM_E_INVALID_PGN);

#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
                }
            }
            else
            {
                /* Send an negative ACK only if the destination address is not the global one. */
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00113,1 */
                if(destAddress != (uint8)0xFF)
                {
                    /* Inform RM regarding this negative ACK. */
                    /* !LINKSTO EB_Ref.SWS_J1939Dcm_00008.SendACK.DM01,1 */
                    if(E_OK == J1939Rm_SendAck( J1939Dcm_RmUserRef[tnode], channel, requestedPgn, J1939RM_ACK_CANNOT_RESPOND, sourceAddress, priority ) )
                    {

                        /* Nothing to do. */

                    }
                }
            }
        }
    }
    DBG_J1939DCM_REQUESTINDICATION_EXIT(node, channel, requestedPgn, sourceAddress, destAddress, priority);
}

/* Indication of a received I-PDU from a lower layer communication interface module. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00128,1 */
/* !LINKSTO EB_Ref.SWS_J1939Dcm_00193.IfRx,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(void, J1939DCM_CODE) J1939Dcm_RxIndication( PduIdType RxPduId,
                            P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr )
{
#if (J1939DCM_DM13_AVAILABLE == STD_ON)
    uint8 tComMChannelIdx = 0x00;
    uint8 tRxDMsIndex = 0x00;
    /* Flag for found RxPduId*/
    boolean rIdFoundFlag =  FALSE;
#endif

#if( ( J1939DCM_DEV_ERROR_DETECT == STD_ON ) && ( J1939DCM_DM13_AVAILABLE == STD_ON ))
    uint8 tErrorId = 0xFF;
#endif

#if (J1939DCM_DM13_AVAILABLE == STD_OFF)
    /* suppress compiler warning */
    TS_PARAM_UNUSED(RxPduId);
    TS_PARAM_UNUSED(PduInfoPtr);
#endif
    DBG_J1939DCM_RXINDICATION_ENTRY(RxPduId, PduInfoPtr);

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00004,1 */
    J1939Dcm_InitCheck(J1939DCM_MODULE_ID, J1939DCM_RXINDICATION,J1939DCM_E_UNINIT)
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    {
#if (J1939DCM_DM13_AVAILABLE == STD_ON)
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
          if (PduInfoPtr == NULL_PTR)
          {
              /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.NULLPointer,1*/
              tErrorId = J1939DCM_E_PARAM_POINTER;
          }
          else if ( (PduInfoPtr->SduLength != 8u ) || (PduInfoPtr->SduDataPtr == NULL_PTR ) )
          {
              /* !LINKSTO J1939Dcm.EB.InvalidSduLength.DET,1*/
              /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.NULLPointer,1*/
              tErrorId = J1939DCM_E_PARAM_POINTER;
          }
          else
#endif/* (J1939DCM_DEV_ERROR_DETECT == STD_ON)*/
          {
              /*Loop through the Configured DMs to find the right RxPduId and corresponding Channel*/
              for(tRxDMsIndex = 0; tRxDMsIndex < J1939DCM_RX_SIZE ; tRxDMsIndex++)
              {
                  if( RxPduId == J1939Dcm_RxPduIds[J1939Dcm_ConfiguredRxDMs[tRxDMsIndex].RxPduIdIdx].J1939DcmRxPduId)
                  {
                      rIdFoundFlag = TRUE;
                      break;
                  }
              }
              if(rIdFoundFlag == TRUE)
              {
                  /* Found a valid RxPduId*/
                  /* Note : Few Validations before processing the request */
                  /* 1. Validate the DA from the received CanId */
                  /* 2. We should accept the connection only if the channel is online */
                  /* 3. Vehicle speed and rpm should be Zero : Limitation */

                  tComMChannelIdx = J1939Dcm_ConfiguredRxDMs[tRxDMsIndex].ComMChannelIdx;

                  if( J1939Dcm_ChannelsState[tComMChannelIdx] == J1939DCM_STATE_ONLINE)
                  {
                      if ( J1939Dcm_ValidateMetadata(tRxDMsIndex) == E_OK )
                      {
                          J1939Dcm_DM13_ProcessRequest(tComMChannelIdx, PduInfoPtr);
                      }
                  }
                  else
                  {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
                        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00139,1 */
                        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.INVALIDSTATE,1 */
                        /* report the DET Error */
                        tErrorId = J1939DCM_E_INVALID_STATE;
#endif
                  }
              }
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
              else
              {
                  /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00151,1 */
                  /* report the DET Error */
                  tErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
              }
#endif
          }
#endif/* (J1939DCM_DM13_AVAILABLE == STD_ON)*/
#if( ( J1939DCM_DEV_ERROR_DETECT == STD_ON ) && ( J1939DCM_DM13_AVAILABLE == STD_ON ))
          if(tErrorId != (uint8)0xFF)
          {
               /* report the DET Error */
               (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_RXINDICATION, tErrorId);
          }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    }
    DBG_J1939DCM_RXINDICATION_EXIT(RxPduId, PduInfoPtr);
}

/* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00145,1 */
/* !LINKSTO EB_Ref.SWS_J1939Dcm_00193.IfTx,1 */
FUNC(void, J1939DCM_CODE) J1939Dcm_TxConfirmation( VAR(PduIdType, AUTOMATIC) TxPduId )
{
    /* Loop Index */
    VAR(uint8, AUTOMATIC) tLoopIdIndex = (uint8)0x00;

        /* Flag for found TxPduId*/
    VAR(boolean, AUTOMATIC) tIdFoundFlag =  FALSE;

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) tErrorId = (uint8)0xFF;
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00004,1 */
    J1939Dcm_InitCheck(J1939DCM_MODULE_ID, J1939DCM_TXCONFIRMATION,J1939DCM_E_UNINIT)
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

    {
      DBG_J1939DCM_TXCONFIRMATION_ENTRY(TxPduId);
      /*Find the right Id Index corresponding for TxPduId*/

      /* Deviation TASKING-1 */
      for(tLoopIdIndex = 0; tLoopIdIndex < J1939DCM_TX_SIZE ; tLoopIdIndex++)
      {
         if (J1939Dcm_TxPduIds[tLoopIdIndex].J1939DcmTxPduId == TxPduId)
         {
            tIdFoundFlag = TRUE;
            break;
         }
      }
      if (tIdFoundFlag == TRUE)
      {
        if( ( J1939Dcm_TxPduIdState[tLoopIdIndex] & J1939DCM_TX_IF ) != (uint8) 0  )
        {
            /* reset buffer locked information */
           /* !LINKSTO EB_Ref.SWS_J1939Dcm_00146.ReleaseBuff,1 */
          J1939DCM_RESET_COMMON_BUFFER_LOCKED();
#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
                /* reset Timeout Monitor as TxConfirmation received*/
                /* !LINKSTO J1939Dcm.EB.IfTxConfTimeout.Stop,1 */
                J1939Dcm_TimeoutMonitorFlag = (uint8)0;
                J1939Dcm_TimeoutCycles = (uint16)0;
#endif /* ( J1939DCM_IF_TX_AVAILABLE == STD_ON ) */
          /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00164,1 */
          /* reset TX state */
          J1939Dcm_TxPduIdState[tLoopIdIndex] = J1939DCM_TX_PDU_ID_IDLE;
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
            if( J1939Dcm_GetChannelState(tLoopIdIndex) == E_NOT_OK )
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00146.InvalidState,1 */
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.INVALIDSTATE,1 */
                tErrorId = J1939DCM_E_INVALID_STATE;
            }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
        }
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        else
        {
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00163,1 */
            tErrorId = J1939DCM_E_INVALID_STATE;
        }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
      }
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* check if received TxConfirmationPduID is an expected one */
    else
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00162,1 */
        tErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
    }
    if(tErrorId != (uint8)0xFF)
    {
         /* report the DET wrong parameter */
        (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_TXCONFIRMATION, tErrorId);

    }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    DBG_J1939DCM_TXCONFIRMATION_EXIT(TxPduId);
    }
}

/* This function is called at the start of receiving an N-SDU. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00102,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(BufReq_ReturnType, J1939DCM_CODE) J1939Dcm_StartOfReception(    VAR(PduIdType, AUTOMATIC) id,

                                    VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                    P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) bufferSizePtr )
{


    CONST(BufReq_ReturnType, AUTOMATIC) tRetval = BUFREQ_E_NOT_OK;

    DBG_J1939DCM_STARTOFRECEPTION_ENTRY(id, TpSduLength, bufferSizePtr);
    /* empty for now */
    /* suppress compiler warning */
    TS_PARAM_UNUSED(id);
    TS_PARAM_UNUSED(TpSduLength);
    TS_PARAM_UNUSED(bufferSizePtr);
    /* needed just by DM13 */

    DBG_J1939DCM_STARTOFRECEPTION_EXIT(tRetval, id, TpSduLength, bufferSizePtr);
    return tRetval;
}

/* This function is called to provide the received data of an I-PDU segment (N-PDU) to the upper layer. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00103,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(BufReq_ReturnType, J1939DCM_CODE) J1939Dcm_CopyRxData(    VAR(PduIdType, AUTOMATIC) id,
                                P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) info,
                                P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) bufferSizePtr )
{

    VAR(BufReq_ReturnType, AUTOMATIC) tRetval = BUFREQ_E_NOT_OK;

    DBG_J1939DCM_COPYRXDATA_ENTRY(id, info, bufferSizePtr);

    /* empty for now */
    /* suppress compiler warning */
    TS_PARAM_UNUSED(id);
    TS_PARAM_UNUSED(info);
    TS_PARAM_UNUSED(bufferSizePtr);
    /* needed just by DM13 */

    DBG_J1939DCM_COPYRXDATA_EXIT(tRetval, id, info, bufferSizePtr);
    return tRetval;
}

/* Called after an I-PDU has been received, the result indicates whether the transmission was successful or not. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00104,1 */
/* Deviation MISRAC2012-1 <1> */
/* Deviation MISRAC2012-2 <1> */
FUNC(void, J1939DCM_CODE) J1939Dcm_TpRxIndication(    VAR(PduIdType, AUTOMATIC) id,
                            VAR(NotifResultType, AUTOMATIC) result )
{
    DBG_J1939DCM_TPRXINDICATION_ENTRY(id, result);
    /* empty for now */
    /* suppress compiler warning */
    TS_PARAM_UNUSED(id);
    TS_PARAM_UNUSED(result);
    /* needed just by DM13 */
    DBG_J1939DCM_TPRXINDICATION_EXIT(id, result);
}

#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
/* This function is called to acquire the transmit data of an I-PDU segment (N-PDU). */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00105,1 */
/* !LINKSTO EB_Ref.SWS_J1939Dcm_00193.TPTx,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(BufReq_ReturnType, J1939DCM_CODE) J1939Dcm_CopyTxData(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) info,
                                                           P2VAR(RetryInfoType, AUTOMATIC, AUTOMATIC) retry, P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) availableDataPtr )
{
    /*Local Variables*/
    VAR(BufReq_ReturnType, AUTOMATIC) tRetval = BUFREQ_E_NOT_OK;     /* Standard return value of function*/
    VAR(uint32, AUTOMATIC) u32tRemainingBytesToSend = (uint32)0x00;  /* Holds the number of bytes that are still to be send */
    VAR(uint16, AUTOMATIC) u16tLoopIdIndex = (uint16)0x00;           /* Loop Index */
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) pu8tSourcePtr = NULL_PTR;   /* Pointer to Tx buffer start position. */
    VAR(boolean, AUTOMATIC) tIdFoundFlag =  FALSE;                   /* Local Flag used to break the loop*/
    if( J1939Dcm_InitStatus == J1939DCM_INIT_OK )
    {
        DBG_J1939DCM_COPYTXDATA_ENTRY(id, info, retry, availableDataPtr);
        TS_PARAM_UNUSED(retry);   /* suppress compiler warning */
        /* Deviation TASKING-1 */
        for(u16tLoopIdIndex = 0; u16tLoopIdIndex < J1939DCM_TX_SIZE ; u16tLoopIdIndex++)  /*Find the right Id Index corresponding for TxPduId*/
        {
           if (J1939Dcm_TxPduIds[u16tLoopIdIndex].J1939DcmTxPduId == id)
           {
              tIdFoundFlag = TRUE;
              break;
           }
        }
        if( tIdFoundFlag == TRUE )
        {
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00143,1 */
            if((J1939Dcm_TxPduIdState[u16tLoopIdIndex] & J1939DCM_TX_TP ) != (uint8)0)
            {
#if(J1939DCM_DM01_AVAILABLE == STD_ON)
                if( J1939Dcm_TxPduIdState[u16tLoopIdIndex] == J1939DCM_TX_TP_DM1_ACTIVE )   /* Check if we have a DM1 transmission */
                {
                    pu8tSourcePtr = J1939Dcm_DM1Buffer;    /* Update TX buffer if DM1 is requested */
                }
                else
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */
                {
                    pu8tSourcePtr = J1939Dcm_CommonBuffer;
                }
                if ((uint32)(info->SduLength) <= ((uint32)J1939Dcm_TxBuffInfo[u16tLoopIdIndex].Bytes_To_Send_Tx - (uint32)J1939Dcm_TxBuffInfo[u16tLoopIdIndex].Sent_Bytes_Tx ) )
                {
                    J1939Dcm_Memcpy(info->SduDataPtr, &pu8tSourcePtr[J1939Dcm_TxBuffInfo[u16tLoopIdIndex].Sent_Bytes_Tx], (uint32)info->SduLength);/* copy intended bytes */
                    J1939Dcm_TxBuffInfo[u16tLoopIdIndex].Sent_Bytes_Tx += ( (J1939Dcm_MsgLenType)info->SduLength );                                /* update the number of sent bytes */
                    tRetval = BUFREQ_OK;
                }
                /* calculate the number of bytes still to send */
                u32tRemainingBytesToSend = (uint32)J1939Dcm_TxBuffInfo[u16tLoopIdIndex].Bytes_To_Send_Tx - (uint32)J1939Dcm_TxBuffInfo[u16tLoopIdIndex].Sent_Bytes_Tx;
                *availableDataPtr = (PduLengthType)u32tRemainingBytesToSend;
                }
            else
            {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
                /* Raise Det Error, the state of the TxPduId is invalid*/
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00143,1 */
                (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_COPYTXDATA, J1939DCM_E_INVALID_STATE);
#endif
            }
        }
        else
        {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
          /* Raise Det Error, Api was called with unexpected pduID*/
          /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00158,1 */
          (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_COPYTXDATA, J1939DCM_E_INVALID_PDU_SDU_ID);
#endif
        }
    }
    else
    {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
       /* Raise Det Error, API was called before J1939Dcm was propperly initialized*/
       /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00004,1 */
       (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_COPYTXDATA, J1939DCM_E_UNINIT);
#endif
    }
    return tRetval;
}
#endif /* (J1939DCM_TP_TX_AVAILABLE == STD_ON) */


#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
/* This function is called after the I-PDU has been transmitted, the result indicates whether the transmission was successful or not. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00106,1*/
/* !LINKSTO EB_Ref.SWS_J1939Dcm_00193.TPTx,1 */
/* Deviation MISRAC2012-1 <1> */
/* Deviation MISRAC2012-2 <1> */
FUNC(void, J1939DCM_CODE) J1939Dcm_TpTxConfirmation(VAR(PduIdType, AUTOMATIC) id, VAR(Std_ReturnType, AUTOMATIC) result)
{
    /*Local Variables*/
    VAR(uint8, AUTOMATIC) u8tLoopIdIndex = (uint8)0x00;    /* Temporally index used to cycle between J1939Dcm_TxPduIds array elements*/
    VAR(boolean, AUTOMATIC) tIdFoundFlag =  FALSE;         /* Flag for found TxPduId used to break the loop*/
    if( J1939Dcm_InitStatus == J1939DCM_INIT_OK )
    {
         DBG_J1939DCM_TPTXCONFIRMATION_ENTRY(id, result);
         /* Deviation TASKING-1 */
         for(u8tLoopIdIndex = 0; u8tLoopIdIndex < J1939DCM_TX_SIZE ; u8tLoopIdIndex++)  /*Find the right Id Index corresponding for TxPduId*/
         {
            if (J1939Dcm_TxPduIds[u8tLoopIdIndex].J1939DcmTxPduId == id)
            {
               tIdFoundFlag = TRUE;
               break;
            }
         }
         TS_PARAM_UNUSED(result);    /* suppress compiler warning */
         if( tIdFoundFlag == TRUE )
         {
             if( J1939Dcm_GetChannelState(u8tLoopIdIndex) == E_OK )
             {
                  if(( J1939Dcm_TxPduIdState[u8tLoopIdIndex] & J1939DCM_TX_TP ) != (uint8)0)
                  {
#if(J1939DCM_DM01_AVAILABLE == STD_ON)
                      if( J1939Dcm_TxPduIdState[u8tLoopIdIndex] == J1939DCM_TX_TP_DM1_ACTIVE )  /* reset request processing information for the corresponding DM */
                      {
                          /* !LINKSTO J1939Dcm.EB.Dsn.DM01Buffer.Unlock,1 */
                          J1939Dcm_GeneralStatus &= (uint8)0xEF;        /* Reset DM1 buffer. New DM1 processing can start. */
                      }
                      else
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */
                      {
                           /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00009,1 */
                           /* !LINKSTO J1939Dcm.EB.Dsn.commonBuffer.Unlock,1 */
                           J1939Dcm_GeneralStatus &= (uint8)0xFE;    /* reset buffer locked information */
                      }
                      J1939Dcm_TxPduIdState[u8tLoopIdIndex] = J1939DCM_TX_PDU_ID_IDLE;   /* reset TX state */
                  }
                  else
                  {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
                     /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00161,1 */
                     (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_TPTXCONFIRMATION, J1939DCM_E_INVALID_STATE);
#endif
                  }
             }
             else
             {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
               /* Raise Det Error, node channel state is offline, cant communicate*/
               (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_TPTXCONFIRMATION, J1939DCM_E_WRONG_NODE_CHANNEL_STATE);
#endif
             }
         }
         else
         {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
         /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00160,1 */
         (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_TPTXCONFIRMATION, J1939DCM_E_INVALID_PDU_SDU_ID);
#endif
         }
     }
     else
     {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.UNINIT,1 */
        (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, J1939DCM_TPTXCONFIRMATION, J1939DCM_E_UNINIT);
#endif
     }
     DBG_J1939DCM_TPTXCONFIRMATION_EXIT(id, result);
}
#endif /* (J1939DCM_TP_TX_AVAILABLE == STD_ON) */

/* void J1939Dcm_MainFunction(void)
 *  Used for  main loop. Shall be called periodically as cyclic
 *  task by the software system. All scheduled functions are integrated. */
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00107,1 */
FUNC(void, J1939DCM_CODE) J1939Dcm_MainFunction( void )
{

    /* meta data info variable */
    P2VAR(J1939Dcm_MetaDataInfoType, AUTOMATIC, J1939DCM_VAR) tMetaDataInfoPtr = &J1939Dcm_DMxMetaDataInfo;

    VAR(J1939Dcm_OpStatusType, AUTOMATIC) tOperationStatus = J1939DCM_INITIAL;

    /* holds function result */
    VAR(J1939Dcm_DmResponseType, AUTOMATIC) tDmResponse = J1939DCM_DM_FUNCTION_OK;

#if( J1939DCM_DM01_AVAILABLE == STD_ON )
    VAR(uint8, AUTOMATIC) tCtr = (uint8)0x00;
#endif/*( J1939DCM_DM01_AVAILABLE == STD_ON ) */
    DBG_J1939DCM_MAINFUNCTION_ENTRY();
    /* Check if the J1939Dcm module was initialized. */
    if( J1939Dcm_InitStatus == J1939DCM_INIT_OK )
    {
#if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
        /*  To check if Confirmation Timeout is active and increment it by one cycle*/
        if (J1939Dcm_TimeoutMonitorFlag == (uint8)1)
        {
           /* !LINKSTO J1939Dcm.EB.IfTxConfTimeout.Expired,1 */
           if( J1939Dcm_TimeoutCycles < J1939DCM_TIMEOUTCYCLES_MAX )
           {
               /* Time is not expired so increment the time cycles */
               J1939Dcm_TimeoutCycles++;
           }
           else
           {
                /* Loop Index */
                VAR(uint16, AUTOMATIC) tLoopIdIndex ;
               /* Timeout expired release the Transmission by resetting the lock of the buffer DMx */
               J1939DCM_RESET_COMMON_BUFFER_LOCKED(); /* reset buffer locked information */
               /* CHECK: NOPARSE */
                /* reset TX state */

                /* Deviation TASKING-1 */
                for( tLoopIdIndex = (uint16)0 ; tLoopIdIndex < J1939DCM_TX_SIZE ; tLoopIdIndex++ )
                {
                    if( ( J1939Dcm_TxPduIdState[tLoopIdIndex] & J1939DCM_TX_IF_DMX) == J1939DCM_TX_IF_DMX  )
                    {
                        J1939Dcm_TxPduIdState[tLoopIdIndex] = J1939DCM_TX_PDU_ID_IDLE;
                        break;
                    }
                }
                /* CHECK: PARSE */
               /* re-init Timeout*/
               J1939Dcm_TimeoutMonitorFlag = (uint8)0;
               J1939Dcm_TimeoutCycles = (uint16)0;
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
               /* report the DET for TX Confirmation Timeout */
               /* !LINKSTO J1939Dcm.EB.IfTxConfTimeout.DET,1 */
               (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_MAINFUNCTION, J1939DCM_E_IF_TX_CONFIRMATION_TIMEOUT);
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
           }
        }
#endif/*( J1939DCM_IF_TX_AVAILABLE == STD_ON ) */

        /* check if request is pending */
        if( J1939DCM_CHECK_DM_REQUEST_PROCESSING_ACTIVE() )
        {
            /* request is pending */
            tOperationStatus = J1939DCM_PENDING;
        }
#if(J1939DCM_DM13_AVAILABLE == STD_ON)
        J1939Dcm_DM13TimeoutSupervision();
#endif

#if( J1939DCM_DM01_AVAILABLE == STD_ON )
#if( J1939DCM_DM13_AVAILABLE == STD_ON )
        /* !LINKSTO J1939Dcm.EB.DM13StopsDM1BroadcastMessages,1 */
        if(J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastStatus)
#endif/*( J1939DCM_DM13_AVAILABLE == STD_ON )*/
        {
            /* Check if it the time to send an cyclic response. */
            if( J1939Dcm_CyclesTillNextDM1Transmit < J1939DCM_CYCLESTILLNEXTDM1_TRANMIT )
            {
                /* Time is not expired so increment the time until the response should be send. */
                J1939Dcm_CyclesTillNextDM1Transmit++;
            }
            else
            {
                /* !LINKSTO EB_Ref.SWS_J1939Dcm_00031.PeriodicDM01,1 */

                /* time to send the next DM1 message has elapsed */
                /* re-init timer and set DM1 request as present */
                J1939Dcm_CyclesTillNextDM1Transmit = (uint16)0;

                /* At every second that pass the number of DTC that are triggered by DEM is reseted. */
                J1939Dcm_NbOfDTCTrigeredByDEM = (uint8)0x00;

                /* This will trigger processing of all nodes which have DM1 available starting with first one. */
                J1939Dcm_IdxInConfiguredNodes = (uint8)0x00;

                /* Mark information that the cyclic DM is present. */
                J1939DCM_SET_DM1_REQUEST_PRESENT();
            }
        }
#endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */

        /* check if request processing is pending */
        /* in this case message context is prepared already */
        /* in this case fewer actions are needed */
        if( tOperationStatus == J1939DCM_PENDING  )
        {
#if( J1939DCM_DM01_AVAILABLE == STD_ON )
            if( J1939DCM_CHECK_DM1_REQUEST_PROCESSING_ACTIVE() )
            {
                /* set meta data info according to DM1 */
                tMetaDataInfoPtr = &J1939Dcm_DM1MetaDataInfo;
            }
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */
        }
        else
        {
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00133,1 */
            /* check if we need to respond to a DMx request */
            /* request will be processed only if DM1 request is currently processing */
            if(    J1939DCM_CHECK_DMX_REQUEST_PRESENT() )

            {
                /* Set DMx request processing active */
                J1939DCM_SET_DMX_REQUEST_PROCESSING_ACTIVE();

                /* set message context specific information */
                J1939Dcm_MsgContext.resData = J1939Dcm_CommonBuffer;
                J1939Dcm_MsgContext.resMaxDataLen = J1939DCM_COMMON_BUFFER_SIZE;
                J1939Dcm_MsgContext.Response = J1939DCM_NO_RESPONSE;
            }
#if( J1939DCM_DM01_AVAILABLE == STD_ON )
#if (J1939DCM_DM13_AVAILABLE == STD_ON)
            else if( J1939DCM_CHECK_DM1_REQUEST_PRESENT() &&
                        J1939DCM_CHECK_DM1_BUFFER_UNLOCKED()
                        && J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastStatus
                        )
#else
            else if( J1939DCM_CHECK_DM1_REQUEST_PRESENT() &&
                        J1939DCM_CHECK_DM1_BUFFER_UNLOCKED()
                        )
#endif /* J1939DCM_DM13_AVAILABLE == STD_ON */
            {
                /* Parse all configured nodes to check if contain cyclic DM1.
                 * After each 1 second for all nodes which have configured DM1 an response should be triggered. */
                for(tCtr = J1939Dcm_IdxInConfiguredNodes; tCtr < J1939DCM_NB_OF_CONFIGURED_NODES; tCtr++)
                {
                    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00033,1 */
                    /* Check if current node has configured cyclic DM1. */
                    if(J1939Dcm_ConfiguredNodes[tCtr].DM1Idx != (uint8)0xFF)
                    {
                         /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00030,1 */
                         /* !LINKSTO EB_Ref.SWS_J1939Dcm_00031.LockDM01Buffer,1 */
                         /* !LINKSTO J1939Dcm.EB.Dsn.DM01Buffer.lock,1 */
                        /* Set DM1 buffer as locked. */
                        J1939DCM_SET_DM1_BUFFER_LOCKED();

                        /* set meta data info according to DM1 */
                        tMetaDataInfoPtr = &J1939Dcm_DM1MetaDataInfo;

                        /* store DM index */
                        tMetaDataInfoPtr->DMIdx = J1939Dcm_ConfiguredNodes[tCtr].DM1Idx;
                        /* store node symbolic name\node address */
                        tMetaDataInfoPtr->NodeId = J1939Dcm_ConfiguredNodes[tCtr].NodeSymbolicName;
                        /* store J1939Rm User Id */
                        tMetaDataInfoPtr->J1939RmUserId = J1939Dcm_RmUserRef[tCtr];
                        /* store destination address */
                        tMetaDataInfoPtr->destAddress = (uint8)0xFF;
                        /* store source address */
                        tMetaDataInfoPtr->NodePreferredAddress = J1939Dcm_ConfiguredNodes[tCtr].J1939NmNodePreferredAddress;
                        /* store priority */
                        tMetaDataInfoPtr->priority = J1939DCM_DM01_PRIORITY;

                        /* Node has cyclic DM1 configured. Process DM1 message and come back on next
                         * main function to see if other nodes also has DM1 configured. */
                        break;
                    }
                }

                /* All nodes has been searched if DM1 is available. */
                if(tCtr == J1939DCM_NB_OF_CONFIGURED_NODES)
                {
                    J1939DCM_RESET_DM1_REQUEST_PRESENT();

                    /* we have no request to process, we mark it as pending */
                    /* this will avoid request processing and transmission */
                    tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
                }
                else
                {
                    /* Set DMx request processing active */
                    J1939DCM_SET_DM1_REQUEST_PROCESSING_ACTIVE();

                    /* set message context specific information */
                    J1939Dcm_MsgContext.resData = J1939Dcm_DM1Buffer;
                    J1939Dcm_MsgContext.resMaxDataLen = J1939DCM_DM01_BUFFER_SIZE;
                    J1939Dcm_MsgContext.Response = J1939DCM_NO_RESPONSE;

                    /* Save the index with all processed DM1 messages. */
                    J1939Dcm_IdxInConfiguredNodes = (tCtr + (uint8)0x01);
                }
            }
#endif    /* J1939DCM_DM01_AVAILABLE == STD_ON */
            else
            {
                /* we have no request to process, we mark it as pending */
                /* this will avoid request processing and transmission */
                tDmResponse = J1939DCM_DM_FUNCTION_PENDING;
            }
        }

        /* check if any request needs to be processed */
        if(    ( tDmResponse == J1939DCM_DM_FUNCTION_OK )    &&    /* if response is still OK */
                ( !J1939DCM_CHECK_DM_PROCESSING_DONE_TX_NEEDED() )    /* and request processing not yet done */
        )
        {
            /* complete message context info */
            J1939Dcm_MsgContext.DMIdx = tMetaDataInfoPtr->DMIdx;

            /* call DM processing function */
            /* !LINKSTO J1939Dcm.EB.DiscardDM.UserFnc,1 */
            tDmResponse = (*J1939DCM_DM_FUNCTION())( tOperationStatus, &J1939Dcm_MsgContext, tMetaDataInfoPtr->NodeId );
        }

        /* check if request processing is done */
        if( tDmResponse != J1939DCM_DM_FUNCTION_PENDING )
        {
            /* call transmit function */
            J1939Dcm_TransmitInternal( *tMetaDataInfoPtr );

        }

    }
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    else
    {
        (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_MAINFUNCTION, J1939DCM_E_UNINIT);

    }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

    DBG_J1939DCM_MAINFUNCTION_EXIT();
}

/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00124,1 */
/* Deviation MISRAC2012-2 <1> */
FUNC(Std_ReturnType, J1939DCM_CODE) J1939Dcm_SetState(     VAR(NetworkHandleType, AUTOMATIC) channel,
                            VAR(uint8, AUTOMATIC) node,
                            VAR(J1939Dcm_StateType, AUTOMATIC) newState )
{

    /* Return value of this function. */
    VAR(Std_ReturnType, AUTOMATIC) tRetval = E_NOT_OK;

    DBG_J1939DCM_SETSTATE_ENTRY(channel, node, newState);

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00004,1 */
    J1939Dcm_InitCheck(J1939DCM_MODULE_ID, J1939DCM_SETSTATE, J1939DCM_E_UNINIT)
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Check if the new state is in the valid range. */
        if( newState < J1939DCM_CHECKSTATE )
        {
            tRetval = J1939Dcm_SetAndCheckChannelState( channel, &node, newState, J1939DCM_SETSTATE );
        }
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        else
        {
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00130,1 */
            (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_SETSTATE, J1939DCM_E_INVALID_STATE);

        }
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    }

    DBG_J1939DCM_SETSTATE_EXIT(tRetval, channel, node, newState);

    return tRetval;
}


/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00098,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(void, J1939DCM_CODE) J1939Dcm_Init( P2CONST(J1939Dcm_ConfigType, AUTOMATIC, J1939DCM_APPL_CONST) configPtr )
{
    P2CONST(J1939Dcm_ConfigType, AUTOMATIC, J1939DCM_APPL_CONST) LocalConfigPtr = configPtr;

    VAR(uint8, AUTOMATIC) tCtr = (uint8)0x00;

    DBG_J1939DCM_INIT_ENTRY(configPtr);

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* Initialize internal variables only first time. */
    if(J1939Dcm_InitStatus == J1939DCM_INIT_OK)
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00005,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.REINIT,1 */
        (void)Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_INIT, J1939DCM_E_REINIT);
    }
    else
#endif /* #if (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    {
  /* Save the configuration pointer */
#if (J1939DCM_PBCFGM_SUPPORT_ENABLED == STD_ON)
      /* If the initialization function is called with an null pointer get the configuration from the
       * post build configuration manager */
      if (LocalConfigPtr == NULL_PTR)
      {
        PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
        if (E_OK == PbcfgM_GetConfig( J1939DCM_MODULE_ID,
                                      J1939DCM_INSTANCE_ID,
                                      &ModuleConfig)
                                    )
        {
          LocalConfigPtr = (P2CONST(J1939Dcm_ConfigType, AUTOMATIC, J1939DCM_APPL_CONST)) ModuleConfig;
        }
      }
#endif /* J1939NM_PBCFGM_SUPPORT_ENABLED == STD_ON */

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
      /* check whether parameter LocalConfigPtr is a NULL_PTR or invalid*/
      if (LocalConfigPtr == NULL_PTR)
      {
        /* found a NULL_PTR, report to DET */
        (void) Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_INIT, J1939DCM_E_INIT_FAILED);
      }
      else
#endif /* J1939DCM_DEV_ERROR_DETECT */
      {
        if ( E_OK != J1939Dcm_IsValidConfig(LocalConfigPtr) )
        {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
          /* check that configuration pointer is valid */
          (void) Det_ReportError( J1939DCM_MODULE_ID, (uint8)0, J1939DCM_INIT,
                                  J1939DCM_E_PARAM_POINTER
                                );
#endif /* J1939DCM_DEV_ERROR_DETECT */
        }
        else
        {
            /*Set Global Initialize Post build Configuration pointer */
            J1939Dcm_ConfigPtr = LocalConfigPtr;

                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00002,1 */
            /* initialize channels states */
            /* Deviation TASKING-1 */
            for ( tCtr = (uint8)0; tCtr < J1939DCM_NB_OF_GENERIC_COMMCHANNELS; tCtr++ )
            {
                /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00125,1 */
                /* set the offline state. */
                J1939Dcm_ChannelsState[tCtr] = J1939DCM_STATE_OFFLINE;
            }
            /* Deviation TASKING-1 */
            for ( tCtr = (uint8)0; tCtr < J1939DCM_TX_SIZE; tCtr++ )
            {
                J1939Dcm_TxPduIdState[tCtr] = J1939DCM_TX_PDU_ID_IDLE;
            }
            /* Deviation TASKING-1 */
            for ( tCtr = (uint8)0; tCtr < J1939DCM_NB_OF_GENERIC_COMMCHANNELS; tCtr++ )
            {
                J1939Dcm_ComMChannels[tCtr] = J1939Dcm_ConfigPtr->J1939DcmChannelRef[tCtr].ComMRefId;
            }
            /* Deviation TASKING-1 */
            for(tCtr = (uint8)0; tCtr < J1939DCM_NB_OF_CONFIGURED_NODES; tCtr++ )
            {
                J1939Dcm_RmUserRef[tCtr] = J1939Dcm_ConfigPtr->J1939DcmNodeRef[tCtr].J1939DcmRmUserRef;
            }

    #if(J1939DCM_DM01_AVAILABLE == STD_ON)
            /* Initialize the currently number of DTC triggered by DEM. */
            J1939Dcm_NbOfDTCTrigeredByDEM = (uint8)0x00;

            /* Init cycles till next DM1 transmit.
             * Set to maximum in order to transmit starting with first MainFunction. */
            J1939Dcm_CyclesTillNextDM1Transmit = J1939DCM_CYCLESTILLNEXTDM1_TRANMIT;
    #endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */

            /* !LINKSTO J1939Dcm.EB.Dsn.commonBuffer.InitUnlocked,1 */
            /* !LINKSTO J1939Dcm.EB.Dsn.DM01Buffer.InitUnlocked,1 */
            /* Reset all information about request */
            J1939Dcm_GeneralStatus = (uint8)0x00;
    #if( J1939DCM_IF_TX_AVAILABLE == STD_ON )
            J1939Dcm_TimeoutMonitorFlag = (uint8)0;
    #endif /*( J1939DCM_IF_TX_AVAILABLE == STD_ON )*/
            J1939Dcm_InitStatus = J1939DCM_INIT_OK;
    #if(J1939DCM_DM13_AVAILABLE == STD_ON)
            /* Reset all the variables used to handle the DM13 functionality */
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00129,1 */
            J1939Dcm_DM13_BroadcastStatusMask = J1939DCM_DM13_RESET_NORMAL_BROADCAST_MODE;
            J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode = J1939DCM_DM13_NORMAL_MODE;
            J1939Dcm_DM13_StatusInfo.J1939DcmTimerState = J1939DCM_DM13_TIMER_CLEAR;
            J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastStatus = TRUE;
    #endif
        }
      }
    }

    DBG_J1939DCM_INIT_EXIT(configPtr);
}


/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00099,1 */
FUNC(void, J1939DCM_CODE) J1939Dcm_DeInit(void)
{

    DBG_J1939DCM_DEINIT_ENTRY();
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00003,1 */
    J1939Dcm_InitStatus = J1939DCM_INIT_NOK;
    DBG_J1939DCM_DEINIT_EXIT();

}

FUNC( Std_ReturnType, J1939DCM_CODE) J1939Dcm_IsValidConfig
(
  P2CONST(void,AUTOMATIC,J1939DCM_APPL_CONST) voidConfigPtr
)
{
  /* Assume an invalid configuration */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(J1939Dcm_ConfigType,AUTOMATIC,J1939DCM_APPL_CONST) ConfigPtr = voidConfigPtr;

    /* Check if the configuration fits to the platform */
    if (ConfigPtr != NULL_PTR)
    {
      if (TS_PlatformSigIsValid(ConfigPtr->PlatformSignature) == TRUE )
      {
        /* Validate the post build configuration against the compile time configuration */
        if (J1939DCM_CFG_SIGNATURE == ConfigPtr->CfgSignature)
        {
          /* Validate the post build configuration against the link time configuration */
          if (J1939Dcm_LcfgSignature == ConfigPtr->LcfgSignature)
          {
            /* Validate the post build configuration against the compile time published information
               configuration */
            if (J1939DCM_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
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
/* !LINKSTO J1939Dcm.SWS_J1939Dcm_00100,1 */
/* *****************************************************************************
 *  Name                 : J1939Dcm_GetVersionInfo
 *  Description          : Returns the version information of J1939Dcm module.
 *  Parameters           : Output : Std_VersionInfoType * versionInfo
 *  Return               : None
 *  Critical/explanation : [No]
 ******************************************************************************/
FUNC(void, J1939DCM_CODE) J1939Dcm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,J1939DCM_VAR) versionInfo)
{
    DBG_J1939DCM_GETVERSIONINFO_ENTRY(versionInfo);
#if(J1939DCM_DEV_ERROR_DETECT == STD_ON)
    if(versionInfo == NULL_PTR )
    {   /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.J1939Dcm_GetVersionInfo,1 */
        (void)Det_ReportError(J1939DCM_MODULE_ID, (uint8)J1939DCM_INSTANCE_ID, J1939DCM_GETVERSIONINFO, J1939DCM_E_PARAM_POINTER);
    }
    else
#endif
    {
        /* Module ID of this module from Module List */
        versionInfo->moduleID = J1939DCM_MODULE_ID;

        /* Vendor ID of the dedicated implementation of this module according to AUTOSAR Vendor List */
        versionInfo->vendorID = J1939DCM_VENDOR_ID;

        /* Major version number of the vendor specific implementation of the module. */
        versionInfo->sw_major_version = J1939DCM_SW_MAJOR_VERSION;

        /* Minor version number of the vendor specific implementation of the module. */
        versionInfo->sw_minor_version = J1939DCM_SW_MINOR_VERSION;

        /* Patch level version number of the vendor specific implementation of the module. */
        versionInfo->sw_patch_version = J1939DCM_SW_PATCH_VERSION;
    }
    DBG_J1939DCM_GETVERSIONINFO_EXIT(versionInfo);
}

/* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00122,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(void, J1939DCM_CODE) J1939Dcm_DemTriggerOnDTCStatus(VAR(uint32, AUTOMATIC) DTC)
{

#if(J1939DCM_DM01_AVAILABLE == STD_ON)
    VAR(uint8, AUTOMATIC) tCtr = (uint8)0x00;

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Dcm.ASR42.SWS_J1939Dcm_00004,1 */
    J1939Dcm_InitCheck(J1939DCM_MODULE_ID, J1939DCM_TRIGGER_ON_DTCSTATUS,J1939DCM_E_UNINIT)
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    {
        DBG_J1939DCM_DEMTRIGGERONDTCSTATUS_ENTRY(DTC);
        /* Check if the current DTC is found. */
        for(tCtr = (uint8)0x00; tCtr < J1939Dcm_NbOfDTCTrigeredByDEM; tCtr++)
        {
            if(J1939Dcm_TrigeredDTCByDEM[tCtr] == DTC)
            {
                /* The DTC is found that means this DTC is triggered twice in one second. */
                break;
            }
        }

        /* If the DTC is not found. */
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00032.DemTriggerOnDTCS.sameDTC,1 */
        if( tCtr == J1939Dcm_NbOfDTCTrigeredByDEM )
        {
            /* The current DTC was trigger for the first time in one second.
             * Check if maximum number of DTC that can be handled is reach.  */
            if(J1939Dcm_NbOfDTCTrigeredByDEM < J1939DCM_MAX_NB_OF_DTC_TRIGGERED_BY_DEM)
            {
                /* Insert the new DTC. */
                /* to prevent sending two response in the same 1s cycle for the same DTC */
                J1939Dcm_TrigeredDTCByDEM[J1939Dcm_NbOfDTCTrigeredByDEM] = DTC;

                /* Increment the number of DTC reported for the current 1s cycle */
                J1939Dcm_NbOfDTCTrigeredByDEM++;

            }

            /* if DTC is not stored yet the DM1 response is always triggered */
            /* even if the new DTC can be stored or not in the table  */
            /* Set information that cyclic DM is triggered by DEM. */
            J1939DCM_SET_DM1_REQUEST_PRESENT();

            /* This will trigger processing of all nodes which have DM1 available. */
            J1939Dcm_IdxInConfiguredNodes = (uint8)0x00;
        }
    DBG_J1939DCM_DEMTRIGGERONDTCSTATUS_EXIT(DTC);
    }
#else
    /* suppress compiler warning */
    TS_PARAM_UNUSED(DTC);
#endif /* (J1939DCM_DM01_AVAILABLE == STD_ON) */
}

static FUNC(Std_ReturnType, J1939DCM_CODE) J1939Dcm_GetChannelState( VAR(uint8, AUTOMATIC) TxPduIdIndex )
{
    /* Return value of this function. */
    VAR(Std_ReturnType, AUTOMATIC) tRetval = E_NOT_OK;
    VAR(uint8, AUTOMATIC) tIdx = (uint8)0x00;
    VAR(uint8, AUTOMATIC) tComMChannelIdx = (uint8)0x00;
    DBG_J1939DCM_GETCHANNELSTATE_ENTRY(TxPduIdIndex);

    /* Deviation TASKING-1 */
    for(tIdx=0;tIdx<J1939DCM_NB_OF_CONFIGURED_DMS;tIdx++)
    {
        VAR(uint8, AUTOMATIC) currTxPduIdIdx = ((uint8)J1939Dcm_ConfiguredDMs[tIdx].TxInfo) & ((uint8)0x7F);
       if(currTxPduIdIdx == TxPduIdIndex)
        {
            /* TxPduIdIndex is found */
            break;
        }
    }
    if( tIdx < J1939DCM_NB_OF_CONFIGURED_DMS)
    {
        tComMChannelIdx = (uint8)(J1939Dcm_ConfigPtr->J1939DcmTxPduRef[J1939Dcm_MsgContext.DMIdx].J1939DcmChannelIdx);
        /* Here the state of the channel is check to see if this is in ONLINE state. */
        if( J1939Dcm_ChannelsState[tComMChannelIdx] == J1939DCM_STATE_ONLINE )
        {
            /* Exit the function with success. */
            tRetval = E_OK;
        }
    }

    DBG_J1939DCM_GETCHANNELSTATE_EXIT(tRetval, TxPduIdIndex);

    return tRetval;
}
#define  J1939DCM_STOP_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>
