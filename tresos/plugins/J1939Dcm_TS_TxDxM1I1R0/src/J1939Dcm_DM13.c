/* *--------{ EB Automotive C Source File }-------- */

/*=================================================== INCLUDES ================================================*/
/* Include internal header, this also includes the own header file */
#include <J1939Dcm_internal.h>
#include <TSAutosar.h>        /* Specific standard types */
#include <BswM_J1939Dcm.h>
/*===================================================END OF INCLUDES ===========================================*/
#if( J1939DCM_DM13_AVAILABLE == STD_ON )

#include <J1939Dcm_Lcfg.h>

/* Includes Development Error Tracer interfaces if enabled. */
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */

#define  J1939DCM_START_SEC_CODE
#include <J1939Dcm_MemMap.h>

/* ================start internal functions prototype section ====================== */
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_NetworkMask_Update(uint8 BusType,uint8 DataInfo);
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_UpdateBroadcastStatus(uint8 ComMChannelIdx, P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer);
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_CurrentDataLinkNetworkMask_Update(uint8 ComMChannelId, uint8 DataInfo);
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_Update_NetworkMask_Byte1(P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer);
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_Update_NetworkMask_Byte2(P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer);
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_Update_NetworkMask_Byte3(P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer);
/* ================stop internal functions prototype section ====================== */

/* !LINKSTO J1939Dcm.EB.DM13TransmissionControl,1 */
/* Function used by the Application to control the Broadcast Transmission Mode */
FUNC(Std_ReturnType, J1939DCM_CODE)J1939Dcm_Broadcast_Transmission_Mode(boolean tTransmissionMode)
{
    /* Return value of this function. */
    Std_ReturnType tRetval = E_NOT_OK;

    DBG_J1939DCM_BROADCAST_TRANSMISSION_MODE_ENTRY(tTransmissionMode);
    if(J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode != J1939DCM_DM13_NORMAL_MODE)
    {
        J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastStatus = tTransmissionMode;
        tRetval = E_OK;
    }
    DBG_J1939DCM_BROADCAST_TRANSMISSION_MODE_EXIT(tRetval, tTransmissionMode);
    return tRetval;
}

/* Function handles the Timer Supervision used for DM-13 Handling */
FUNC(void, J1939DCM_CODE)J1939Dcm_DM13TimeoutSupervision( void )
{
    DBG_J1939DCM_DM13TIMEOUTSUPERVISION_ENTRY();
    /* Check if the hold time is expired */
    if( (J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode != J1939DCM_DM13_NORMAL_MODE) &&
            (J1939Dcm_DM13_StatusInfo.J1939DcmTimerState == J1939DCM_DM13_TIMER_SET) &&
            (J1939Dcm_DM13_StatusInfo.J1939Dcm_HoldTimerTicks < J1939DCM_CYCLESWAIT_HOLDSIGNAL))
    {
        J1939Dcm_DM13_StatusInfo.J1939Dcm_HoldTimerTicks++;
    }
    else if( (J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode != J1939DCM_DM13_NORMAL_MODE) &&
        (J1939Dcm_DM13_StatusInfo.J1939DcmTimerState == J1939DCM_DM13_TIMER_SET) &&
        (J1939Dcm_DM13_StatusInfo.J1939Dcm_HoldTimerTicks >= J1939DCM_CYCLESWAIT_HOLDSIGNAL))
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00135,1 */
        J1939Dcm_DM13_StatusInfo.J1939Dcm_HoldTimerTicks = 0;
        J1939Dcm_DM13_BroadcastStatusMask = J1939DCM_DM13_RESET_NORMAL_BROADCAST_MODE;
        /* Report the Broadcast Status to BSWM layer*/
        BswM_J1939DcmBroadcastStatus(J1939Dcm_DM13_BroadcastStatusMask);
        J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode = J1939DCM_DM13_NORMAL_MODE;
        J1939Dcm_DM13_StatusInfo.J1939DcmTimerState = J1939DCM_DM13_TIMER_CLEAR;
        /* Clearing the Broadcast Status upon timeout, which can also be cleared by Application */
        J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastStatus = TRUE;
    }
    else
    {
        /* Only for misra. */
    }
    DBG_J1939DCM_DM13TIMEOUTSUPERVISION_EXIT();
}
/* Function used to update the current Data link Network Mask variable to be reported to BSWM Module*/
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_CurrentDataLinkNetworkMask_Update(uint8 ComMChannelId,
                                                                uint8 DataInfo)
{
    uint16 tValue = 0x00;
    uint8 tRetval = J1939DCM_CLEAR;

    DBG_J1939DCM_CURRENTDATALINKNETWORKMASK_UPDATE_ENTRY(ComMChannelId,DataInfo);
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00058,1 */
    /* Validate the Don't care and Reserved bit of the DM13 message */
    if( (DataInfo != J1939DCM_DM13_DONT_CARE) && (DataInfo != J1939DCM_DM13_RESERVED) )
    {
        if(DataInfo != J1939DCM_DM13_STOP_BROADCAST)
        {
            /* Updated the Start Broadcast Status */
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00057,1 */
            J1939Dcm_DM13_BroadcastStatusMask |= ((uint16)1u << ComMChannelId);
        }
        else
        {
            /* Update the Stop Broadcast Status */
            /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00056,1 */
            tValue = ((uint16)1u << ComMChannelId);
            J1939Dcm_DM13_BroadcastStatusMask = (J1939Dcm_DM13_BroadcastStatusMask & ((uint16)(~tValue)));
        }
        tRetval = J1939DCM_SET;
    }
    DBG_J1939DCM_CURRENTDATALINKNETWORKMASK_UPDATE_EXIT(tRetval,ComMChannelId,DataInfo);
    return tRetval;
}

/* Function used to update the Network Mask variable to be reported to BSWM Module*/
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_NetworkMask_Update(uint8 BusType,
                                                                uint8 DataInfo)
{
    uint16 tValue = 0x00;
    uint8 tRetval = J1939DCM_CLEAR;
    uint8 tChannelIndex = 0x00u;
    uint8 ComMChannelId = 0x00u;

    DBG_J1939DCM_NETWORKMASK_UPDATE_ENTRY(BusType,DataInfo);
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00058,1 */
    /* Validate the Don't care and Reserved bit of the DM13 message */
    if( (DataInfo != J1939DCM_DM13_DONT_CARE) && (DataInfo != J1939DCM_DM13_RESERVED) )
    {
      for(tChannelIndex = 0; tChannelIndex < J1939DCM_NB_OF_GENERIC_COMMCHANNELS; tChannelIndex++)
      {
        if(BusType == J1939Dcm_BusTypes[tChannelIndex])
        {
          ComMChannelId = J1939Dcm_ComMChannels[tChannelIndex];
          if(DataInfo != J1939DCM_DM13_STOP_BROADCAST)
          {
              /* Updated the Start Broadcast Status */
              /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00057,1 */
              J1939Dcm_DM13_BroadcastStatusMask |= ((uint16)1u << ComMChannelId);
          }
          else
          {
              /* Update the Stop Broadcast Status */
              /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00056,1 */
              tValue = ((uint16)1u << ComMChannelId);
              J1939Dcm_DM13_BroadcastStatusMask = (J1939Dcm_DM13_BroadcastStatusMask & ((uint16)(~tValue)));
          }
        }
      }
        tRetval = J1939DCM_SET;
    }
    DBG_J1939DCM_NETWORKMASK_UPDATE_EXIT(tRetval,BusType,DataInfo);
    return tRetval;
}

/* Function used to parse the Byte 1 of the data pay-load*/
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_Update_NetworkMask_Byte1(P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer)
{
    uint8 tDataInfo;
    uint8 tRetval = J1939DCM_CLEAR;
    uint16 tBusTypeMask = J1939Dcm_BusTypeMask;

    DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE1_ENTRY(LocalBuffer);
    /* SAE J1587 Network */
    if (((tBusTypeMask >> J1939DCM_J1587) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[0]) & ((uint8)0x30u)) >> 4u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1587,tDataInfo);
    }
    /* SAE J1922 Network */
    if (((tBusTypeMask >> J1939DCM_J1922) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[0]) & ((uint8)0x0Cu)) >> 2u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1922,tDataInfo);
    }
    /* SAE J1939 Network #1 */
    if (((tBusTypeMask >> J1939DCM_J1939_NETWORK_1) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((LocalBuffer[0]) & ((uint8)0x03u));
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1939_NETWORK_1,tDataInfo);
    }
    DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE1_EXIT(tRetval,LocalBuffer);
    return tRetval;
}

/* Function used to parse the Byte 2 of the data pay-load*/
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_Update_NetworkMask_Byte2(P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer)
{
    uint8 tDataInfo;
    uint8 tRetval = J1939DCM_CLEAR;
    uint16 tBusTypeMask = J1939Dcm_BusTypeMask;

    DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE2_ENTRY(LocalBuffer);
    /* SAE J1939 Network #2 */
    if (((tBusTypeMask >> J1939DCM_J1939_NETWORK_2) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[1]) & ((uint8)0xC0u)) >> 6u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1939_NETWORK_2,tDataInfo);
    }
    /* ISO 9141 Network */
    if (((tBusTypeMask >> J1939DCM_ISO9141) & 0x01u)  == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[1]) & ((uint8)0x30u)) >> 4u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_ISO9141,tDataInfo);
    }
    /* SAE 1850 Network */
    if (((tBusTypeMask >> J1939DCM_J1850) & 0x01u)  == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[1]) & ((uint8)0x0Cu)) >> 2u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1850,tDataInfo);
    }
    /* Other, manufacturer-specified port */
    if (((tBusTypeMask >> J1939DCM_OTHER) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((LocalBuffer[1]) & ((uint8)0x03u));
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_OTHER,tDataInfo);
    }
    DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE2_EXIT(tRetval,LocalBuffer);
    return tRetval;
}

/* Function used to parse the Byte 3 of the data pay-load*/
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_Update_NetworkMask_Byte3(P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer)
{
    uint8 tDataInfo;
    uint8 tRetval = J1939DCM_CLEAR;
    uint16 tBusTypeMask = J1939Dcm_BusTypeMask;

    DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE3_ENTRY(LocalBuffer);
    /* SAE J1939 Network #3 */
    if (((tBusTypeMask >> J1939DCM_J1939_NETWORK_3) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[2]) & ((uint8)0xC0u)) >> 6u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1939_NETWORK_3,tDataInfo);
    }
    /* Proprietary network #1 */
    if (((tBusTypeMask >> J1939DCM_PROPRIETARY_NETWORK_1) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[2]) & ((uint8)0x30u)) >> 4u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_PROPRIETARY_NETWORK_1,tDataInfo);
    }
    /* Proprietary network #2 */
    if (((tBusTypeMask >> J1939DCM_PROPRIETARY_NETWORK_2) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((uint8)((LocalBuffer[2]) & ((uint8)0x0Cu)) >> 2u);
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_PROPRIETARY_NETWORK_2,tDataInfo);
    }
    /* SAE J1939 Network #4 */
    if (((tBusTypeMask >> J1939DCM_J1939_NETWORK_4) & 0x01u) == TRUE)
    {
        tDataInfo = (uint8)((LocalBuffer[2]) & ((uint8)0x03u));
        tRetval |= J1939Dcm_NetworkMask_Update(J1939DCM_J1939_NETWORK_4,tDataInfo);
    }
    DBG_J1939DCM_UPDATE_NETWORKMASK_BYTE3_EXIT(tRetval,LocalBuffer);
    return tRetval;
}

/* Function validates if the Broadcast status to be updated to BSWM Module*/
static FUNC(uint8, J1939DCM_CODE) J1939Dcm_UpdateBroadcastStatus(uint8 ComMChannelIdx, P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer)
{
    /* Parse based on the Network Type */
    /* Byte 1 : Current data link, SAE J1587 network, SAE J1922 network, SAE J1939 network #1*/
    /* Byte 2 : SAE J1939 network#2, ISO 9141 network, SAE J1850 network, Other manufacturer-specified port*/
    /* Byte 3 : SAE J1939 network#3, Proprietary network1, Proprietary network2,SAE J1939 network#4*/

    uint8 tDataInfo;
    uint8 tRetval = J1939DCM_CLEAR;

    DBG_J1939DCM_UPDATEBROADCASTSTATUS_ENTRY(ComMChannelIdx,LocalBuffer);

    /* Current Data Link */
    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00055,1 */
    tDataInfo = (uint8)((uint8)((LocalBuffer[0]) & ((uint8)0xC0u)) >> 6u);
    if (J1939Dcm_ComMChannels[ComMChannelIdx] <= J1939DCM_DM13_MAX_CHANNEL)
    {
        tRetval |= J1939Dcm_CurrentDataLinkNetworkMask_Update(J1939Dcm_ComMChannels[ComMChannelIdx],tDataInfo);
    }

    /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00092,1 */
    tRetval |= J1939Dcm_Update_NetworkMask_Byte1(LocalBuffer);

    tRetval |= J1939Dcm_Update_NetworkMask_Byte2(LocalBuffer);

    tRetval |= J1939Dcm_Update_NetworkMask_Byte3( LocalBuffer);

    DBG_J1939DCM_UPDATEBROADCASTSTATUS_EXIT(tRetval,ComMChannelIdx,LocalBuffer);
    return tRetval;
}

/* Function reports the DM13 Broadcast status to BSWM module based on the processed pay-load*/
FUNC(void, J1939DCM_CODE) J1939Dcm_DM13_ProcessRequest(uint8 ComMChannelIdx, P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr)
{
    uint8 tHoldSignalValue = 0u;

    /* Save the PduInfoPtr locally to a buffer to undergo parsing */
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) LocalBuffer = PduInfoPtr->SduDataPtr;

    DBG_J1939DCM_DM13_PROCESSREQUEST_ENTRY(ComMChannelIdx,PduInfoPtr);
    /* Read the Hold Signal byte from the buffer */
    tHoldSignalValue = (uint8)(LocalBuffer[3] & ((uint8)0xF0));
    if( ((tHoldSignalValue == J1939_DM13_HOLDSIGNAL_ALL_DEVICE) ||
        (tHoldSignalValue == J1939_DM13_HOLDSIGNAL_MODIFIED_DEVICES)) &&
        (J1939Dcm_DM13_StatusInfo.J1939DcmTimerState == J1939DCM_DM13_TIMER_SET))
    {
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00134.AllDevices,1*/
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00134.ModifiedDevices,1*/
        J1939Dcm_DM13_StatusInfo.J1939Dcm_HoldTimerTicks = 0;
        J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode = J1939DCM_DM13_HOLD_MODE;
    }
    else if (tHoldSignalValue == J1939_DM13_HOLDSIGNAL_NOT_AVAILABLE)
    {
        /* !LINKSTO J1939Dcm.SWS_J1939Dcm_00054,1 */
        if(J1939Dcm_UpdateBroadcastStatus(ComMChannelIdx, LocalBuffer) == J1939DCM_SET)
        {
          J1939Dcm_DM13_StatusInfo.J1939Dcm_HoldTimerTicks = 0;
          J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode = J1939DCM_DM13_SETUP_MODE;
          /* Report the Broadcast Status to BSWM Module*/
          BswM_J1939DcmBroadcastStatus(J1939Dcm_DM13_BroadcastStatusMask);
          J1939Dcm_DM13_StatusInfo.J1939DcmTimerState = J1939DCM_DM13_TIMER_SET;
        }
    }
    else
    {
        J1939Dcm_DM13_StatusInfo.J1939DcmBroadcastMode = J1939DCM_DM13_NORMAL_MODE;
    }
    DBG_J1939DCM_DM13_PROCESSREQUEST_EXIT(ComMChannelIdx,PduInfoPtr);
}

/* Function used to validate the Meta data information received via CanIf */
FUNC(Std_ReturnType, J1939DCM_CODE)J1939Dcm_ValidateMetadata(uint8 tRxDMsIndex)
{
    Std_ReturnType EcuC_Ret = E_NOT_OK;
    uint32 metaDataCanId=0x00000000;
    PduIdType RxPduRef = 0 ;
    uint8 NodePreferredAddress;
    uint8 da;
    uint16 RxPduId = 0 ;
    uint8 i_pduId = 0 ;

    DBG_J1939DCM_VALIDATEMETADATA_ENTRY(tRxDMsIndex);

    RxPduId = J1939Dcm_RxPduIds[J1939Dcm_ConfiguredRxDMs[tRxDMsIndex].RxPduIdIdx].J1939DcmRxPduId ;

    /*Get RxRefID from postbuild configuration*/
    /*Checking on RX_SIZE to avoid nothing processing*/
#if (J1939DCM_RX_SIZE > 0)
    J1939DCM_RXPDUID_REF(i_pduId,RxPduId,RxPduRef);
#endif
    if( EcuC_GetMetaDataCanId(RxPduRef,NULL_PTR,&metaDataCanId) == E_OK)
    {
        /* Extract the DA from the metaDataCanId */
        da = (uint8)(((uint32)metaDataCanId & 0x0000FF00U) >> 8);
        /* Node Preferred Address of J1939NM modules is extracted to compare it with the received destination address */
        NodePreferredAddress = J1939Dcm_ConfiguredNodes[J1939Dcm_ConfiguredRxDMs[tRxDMsIndex].ComMChannelIdx].J1939NmNodePreferredAddress;
        if( (NodePreferredAddress == da) || (da == 0xFFu))
        {
          /* Request is accepted only if DA is a broadcast or configured in J1939Nm */
          EcuC_Ret = E_OK;
        }
        else
        {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.WrongPDUSDU,1 */
          (void)Det_ReportError(J1939DCM_MODULE_ID, (uint8)0, J1939DCM_RXINDICATION, J1939DCM_E_INVALID_PDU_SDU_ID);
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
        }
    }
    else
    {
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO EB_Ref.SWS_J1939Dcm_00090.WrongPDUSDU,1 */
        (void)Det_ReportError(J1939DCM_MODULE_ID, (uint8)0, J1939DCM_RXINDICATION, J1939DCM_E_INVALID_PDU_SDU_ID);
#endif /* (J1939DCM_DEV_ERROR_DETECT == STD_ON) */
    }
    DBG_J1939DCM_VALIDATEMETADATA_EXIT(EcuC_Ret,tRxDMsIndex);
    return EcuC_Ret;
}

#define  J1939DCM_STOP_SEC_CODE
#include <J1939Dcm_MemMap.h>

#endif /* J1939DCM_DM13_AVAILABLE */
